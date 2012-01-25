/***************************************************************
 * Name:      xlights_out.cpp
 * Purpose:
    Defines a common API for LOR, D-Light, DMX, Renard, Pixelnet, and E1.31 networks
    All calls should be made to xOutput class
 *
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-05-07
 * Copyright: 2010-2011 by Matt Brown
 * License:
     This file is part of xLights.

    xLights is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    xLights is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with xLights.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************************/

#include "globals.h"
#include "serial/serport.cpp"
#include <vector>
#include <list>
#include <time.h>
#include <wx/socket.h>


// *************************************************
// * Base class to define a collection of channels
// *************************************************
class xNetwork {
protected:
  ctb::SerialPort* serptr;
  wxByte IntensityMap[256];
  char SerialConfig[4];
  long timer_msec;
  int max_intensity;
  int num_channels;
  wxString netdesc;
  friend class xChannel_Dimmer;

  virtual void SetMappedIntensity (int chindex, wxByte intensity) =0;

public:

  xNetwork() {
    serptr=0;
    timer_msec=0;
    num_channels=0;
    strcpy(SerialConfig,"8N1");
  };

  virtual ~xNetwork() {
    if (serptr) delete serptr;
  };

  void CloseSerialPort() {
    if (serptr) serptr->Close();
  };

  bool TxEmpty() {
    if (serptr) return (serptr->WaitingToWrite() == 0);
    return true;
  };
  
  wxByte MapIntensity(wxByte intensity) {
    return IntensityMap[intensity];
  };

  void SetNetworkDesc(wxString& NetworkDesc) {
    netdesc=NetworkDesc;
  };

  wxString GetNetworkDesc() {
    return netdesc;
  };

  int GetChannelCount() {
    return num_channels;
  };

  virtual void SetChannelCount(int numchannels) = 0;

  virtual void SetMaxIntensity(int maxintensity) = 0;

  void InitSerialPort(const wxString& portname, int baudrate) {
    static char errmsg[100];
    if (portname == wxT("NotConnected")) return;
    serptr=new ctb::SerialPort();
    int errcode=serptr->Open(portname, baudrate, SerialConfig);
    if (errcode < 0) {
      sprintf(errmsg,"unable to open serial port, error code=%d",errcode);
      throw errmsg;
    }
  };

  virtual void InitNetwork(const wxString& ipaddr, wxUint16 UniverseNumber, wxUint16 NetNum) {
  };

  virtual void TimerStart(long msec) {
    timer_msec=msec;
  };

  long GetTimer() {
    return timer_msec;
  };

  virtual void TimerEnd() =0;

  virtual void ResetTimer() {
  };

  virtual void SetIntensity (int chindex, wxByte intensity) {
    SetMappedIntensity(chindex, IntensityMap[intensity]);
  };

  virtual void ramp (int chindex, int duration, int startintensity, int endintensity) =0;

  virtual void twinkle (int chindex, int period, int intensity) =0;

  virtual void twinklefade (int chindex, int period, int duration, int startintensity, int endintensity) =0;

  virtual void shimmer (int chindex, int period, int intensity) =0;

  virtual void shimmerfade (int chindex, int period, int duration, int startintensity, int endintensity) =0;

  virtual void off (int chindex) =0;

  virtual void alloff () =0;
};



// *************************************************
// * This class represents a single dimmer channel
// * It converts ramp, shimmer, and twinkle
// * into a series of SetIntensity calls
// *************************************************
class xChannel_Dimmer {
protected:
  xNetwork* mynet;
  int myindex, twinklestate, effectperiod;
  char optype;
  long optimestart, optimeend, periodend;
  wxByte rampstart,rampend;
  double opduration, rampdiff;

  // returns a random value between 100 and 1100 (0.1 - 1.1 seconds)
  int NextTwinkleTime() {
    return static_cast<int>(rand01()*effectperiod)+100;
  }

  // return a random number between 0 and 1 inclusive
  double rand01() {
    return (double)rand()/(double)RAND_MAX;
  };

public:
  xChannel_Dimmer(xNetwork* parentnet, int index) {
    mynet=parentnet;
    myindex=index;
    optype=' ';
  };

  void ramp (int duration, wxByte startintensity, wxByte endintensity) {
    optype='R';
    opduration=duration;
    rampstart=mynet->MapIntensity(startintensity);
    rampend=mynet->MapIntensity(endintensity);
    rampdiff=rampend - rampstart;
    optimestart=mynet->GetTimer();
    optimeend=optimestart + duration;
    mynet->SetMappedIntensity(myindex,rampstart);
  };

  // period - sets the upper bound on an individual twinkle (msec)
  void twinkle (int period, wxByte intensity) {
    optype='T';
    optimestart=mynet->GetTimer();
    effectperiod=period;
    periodend=optimestart + NextTwinkleTime();
    rampend=mynet->MapIntensity(intensity);
    twinklestate= rand01() < 0.5 ? 0 : 1;
    mynet->SetMappedIntensity(myindex,twinklestate*rampend);
  };

  // duration - total duration of the effect (msec)
  // period - sets the upper bound on an individual twinkle (msec)
  void twinklefade (int period, int duration, wxByte startintensity, wxByte endintensity) {
    optype='t';
    opduration=duration;
    rampstart=mynet->MapIntensity(startintensity);
    rampend=mynet->MapIntensity(endintensity);
    rampdiff=rampend - rampstart;
    optimestart=mynet->GetTimer();
    optimeend=optimestart + duration;
    effectperiod=period;
    periodend=optimestart + NextTwinkleTime();
    twinklestate= rand01() < 0.5 ? 0 : 1;
    mynet->SetMappedIntensity(myindex,twinklestate*rampstart);
  };

  // period - sets the length of each shimmer, typically 50-100 (msec)
  void shimmer (int period, wxByte intensity) {
    optype='S';
    optimestart=mynet->GetTimer();
    effectperiod=period;
    periodend=optimestart + effectperiod;
    rampend=mynet->MapIntensity(intensity);
    twinklestate=1;
    mynet->SetMappedIntensity(myindex,rampend);
  };

  // duration - total duration of the effect (msec)
  // period - sets the length of each shimmer, typically 50-100 (msec)
  void shimmerfade (int period, int duration, wxByte startintensity, wxByte endintensity) {
    optype='s';
    opduration=duration;
    rampstart=mynet->MapIntensity(startintensity);
    rampend=mynet->MapIntensity(endintensity);
    rampdiff=rampend - rampstart;
    optimestart=mynet->GetTimer();
    optimeend=optimestart + duration;
    effectperiod=period;
    periodend=optimestart + effectperiod;
    twinklestate=1;
    mynet->SetMappedIntensity(myindex,rampstart);
  };

  void off () {
    mynet->SetMappedIntensity(myindex,0);
  };

  // implements all of the channel lighting effects
  // returns true if the callback is no longer needed, false otherwise
  int ChannelCallback(long curtime) {
    //printf("xChannel_Dimmer::ChannelCallback curtime=%d optype=%c\n",curtime,optype);
    int intensity;
    switch (optype) {
      case 'R':
        if (curtime >= optimeend) {
          mynet->SetMappedIntensity(myindex, rampend);
          return 1;
        } else {
          intensity=(int)((double)(curtime - optimestart) / opduration * rampdiff + rampstart);
          mynet->SetMappedIntensity(myindex, intensity);
        }
        break;
      case 'T':
        if (curtime > periodend) {
          periodend+=NextTwinkleTime();
          twinklestate=1 - twinklestate;
          mynet->SetMappedIntensity(myindex, twinklestate*rampend);
        }
        break;
      case 't':
        if (curtime >= optimeend) {
          optype='T';
        } else if (curtime > periodend) {
          periodend+=NextTwinkleTime();
          twinklestate=1 - twinklestate;
          intensity=(int)((double)(curtime - optimestart) / opduration * rampdiff + rampstart);
          mynet->SetMappedIntensity(myindex, twinklestate*intensity);
        }
        break;
      case 'S':
        if (curtime >= periodend) {
          periodend+=effectperiod;
          twinklestate=1 - twinklestate;
          mynet->SetMappedIntensity(myindex, twinklestate*rampend);
        }
        break;
      case 's':
        if (curtime >= optimeend) {
          optype='S';
        } else if (curtime >= periodend) {
          periodend+=effectperiod;
          twinklestate=1 - twinklestate;
          intensity=(int)((double)(curtime - optimestart) / opduration * rampdiff + rampstart);
          mynet->SetMappedIntensity(myindex, twinklestate*intensity);
        }
        break;
    }
    return 0;
  };
};


// ******************************************************
// * This class represents a network of dimmer channels
// * Used by DMX and Renard classes
// ******************************************************
class xNetwork_Dimmer: public xNetwork {
protected:
  std::list<int> timerCallbackList;
  std::vector<xChannel_Dimmer*> channels;
  int datalen,changed;

  void AddChannelCallback (int channel) {
    timerCallbackList.remove(channel);  // ensure there are no lingering callbacks for this channel
    timerCallbackList.push_front(channel);
  };

public:
  xNetwork_Dimmer() {
  };

  ~xNetwork_Dimmer() {
    for(unsigned int i=0; i < channels.size(); ++i) {
      delete channels[i];
    }
  };

  void SetMaxIntensity(int maxintensity) {
    max_intensity=maxintensity;
    for (int i=0; i<=maxintensity; i++) {
      IntensityMap[i]=(int)(255.0*(double)i/(double)maxintensity+0.5);
    }
  };

  void ResetTimer() {
    timerCallbackList.clear();
  };

  // callbacks return true if they are finished, false if they will continue to run
  virtual void TimerStart(long msec) {
    timer_msec=msec;
    int cnt=0;
    // process list of channels needing callbacks
    std::list<int>::iterator temp,it = timerCallbackList.begin();
    while (it != timerCallbackList.end()) {
      cnt++;
      if (channels[*it]->ChannelCallback(msec)) {
        temp=it;
        ++it; // move past the one we are about to erase
        timerCallbackList.erase(temp);
      } else {
        ++it;
      }
    }
#ifdef _WX_LOG_H_
    wxLogTrace(wxT("xout"),wxT("xNetwork_Dimmer TimerStart %d chan"),cnt);
#endif
  };

  void CreateChannels(int numchannels) {
    for (int i=0; i<numchannels; i++) {
      channels.push_back(new xChannel_Dimmer(this,i));
    }
    num_channels=numchannels;
  };

  virtual void ramp (int chindex, int duration, int startintensity, int endintensity) {
    timerCallbackList.remove(chindex);  // ensure there are no lingering callbacks for this channel
    channels.at(chindex)->ramp(duration, startintensity, endintensity);
    AddChannelCallback(chindex);
  };

  virtual void twinkle (int chindex, int period, int intensity) {
    timerCallbackList.remove(chindex);  // ensure there are no lingering callbacks for this channel
    channels.at(chindex)->twinkle(period,intensity);
    AddChannelCallback(chindex);
  };

  virtual void twinklefade (int chindex, int period, int duration, int startintensity, int endintensity) {
    timerCallbackList.remove(chindex);  // ensure there are no lingering callbacks for this channel
    channels.at(chindex)->twinklefade(period,duration,startintensity,endintensity);
    AddChannelCallback(chindex);
  };

  virtual void shimmer (int chindex, int period, int intensity) {
    timerCallbackList.remove(chindex);  // ensure there are no lingering callbacks for this channel
    channels.at(chindex)->shimmer(period,intensity);
    AddChannelCallback(chindex);
  };

  virtual void shimmerfade (int chindex, int period, int duration, int startintensity, int endintensity) {
    timerCallbackList.remove(chindex);  // ensure there are no lingering callbacks for this channel
    channels.at(chindex)->shimmerfade(period,duration,startintensity,endintensity);
    AddChannelCallback(chindex);
  };

  virtual void SetIntensity (int chindex, wxByte intensity) {
    timerCallbackList.remove(chindex);  // ensure there are no lingering callbacks for this channel
    SetMappedIntensity(chindex, IntensityMap[intensity]);
  };

  void off (int chindex) {
    SetIntensity(chindex, 0);
  };

  virtual void alloff () {
    for(unsigned int i=0; i < channels.size(); ++i) {
      off(i);
    }
  };
};


// ******************************************************
// * This class represents a single DMX universe
// * Compatible with Entec Pro, Lynx DMX, and DIYC RPM dongles
// * Methods should be called with: 0 <= chindex <= 511
// ******************************************************
class xNetwork_DMXpro: public xNetwork_Dimmer {
protected:
  wxByte data[518];

  void SetMappedIntensity(int chindex, wxByte mappedintensity) {
    data[chindex+5]=mappedintensity;
    //printf("DMXentec::SetMappedIntensity channel=%d mapped-value=%d\n",chindex,(int)mappedintensity);
    changed=1;
  };

public:
  void SetChannelCount(int numchannels) {
    if (numchannels > 512) {
      throw "max channels on DMX is 512";
    }
    int len=513;   // entec supports this, but lynx does not: len=numchannels < 24 ? 25 : numchannels+1;
    datalen=len+5;
    data[0]=0x7E;               // start of message
    data[1]=6;                  // dmx send
    data[2]=len & 0xFF;         // length LSB
    data[3]=(len >> 8) & 0xFF;  // length MSB
    data[4]=0;                  // DMX start
    data[datalen-1]=0xE7;       // end of message
    changed=0;
    CreateChannels(numchannels);
  };

  void TimerEnd() {
    if (changed && serptr) {
      serptr->Write((char *)data,datalen);
      changed=0;
    }
  };
};


// ******************************************************
// * This class represents a single DMX universe
// * Compatible with Entec Open DMX, LOR dongle, D-Light dongle,
// * and any other FTDI-based USB to RS-485 converter
// * Methods should be called with: 0 <= chindex <= 511
// ******************************************************
class xNetwork_DMXopen: public xNetwork_Dimmer {
protected:
  wxByte data[513];

  void SetMappedIntensity(int chindex, wxByte mappedintensity) {
    data[chindex+1]=mappedintensity;
    //printf("DMXentec::SetMappedIntensity channel=%d mapped-value=%d\n",chindex,(int)mappedintensity);
    changed=1;
  };

public:
  void SetChannelCount(int numchannels) {
    if (numchannels > 512) {
      throw "max channels on DMX is 512";
    }
    data[0]=0;   // dmx start code
    changed=0;
    CreateChannels(numchannels);
    SerialConfig[2]='2'; // use 2 stop bits so padding chars are not required
  };

  void TimerEnd() {
    if (serptr) {
      serptr->SendBreak();  // sends a 1 millisecond break
      wxMilliSleep(1);      // mark after break (MAB) - 1 millisecond is overkill (8 microseconds is the minimum dmx requirement)
      serptr->Write((char *)data,513);
      changed=0;
    }
  };
};


#define E131_PACKET_LEN 638
#define E131_PORT 5568
#define XLIGHTS_UUID "c0de0080-c69b-11e0-9572-0800200c9a66"

// ******************************************************
// * This class represents a single universe for E1.31
// * Methods should be called with: 0 <= chindex <= 511
// ******************************************************
class xNetwork_E131: public xNetwork_Dimmer {
protected:
  wxByte data[E131_PACKET_LEN];
  wxByte SequenceNum;
  int SkipCount;
  wxIPV4address remoteAddr;
  wxDatagramSocket *datagram;

  void SetMappedIntensity(int chindex, wxByte mappedintensity) {
    data[chindex+126]=mappedintensity;
    changed=1;
  };

public:
  void InitNetwork(const wxString& ipaddr, wxUint16 UniverseNumber, wxUint16 NetNum) {
    if (UniverseNumber == 0 || UniverseNumber >= 64000) {
      throw "universe number must be between 1 and 63999";
    }
    SequenceNum=0;
    SkipCount=0;

    data[0]=0x00;   // RLP preamble size (high)
    data[1]=0x10;   // RLP preamble size (low)
    data[2]=0x00;   // RLP postamble size (high)
    data[3]=0x00;   // RLP postamble size (low)
    data[4]=0x41;   // ACN Packet Identifier (12 bytes)
    data[5]=0x53;
    data[6]=0x43;
    data[7]=0x2d;
    data[8]=0x45;
    data[9]=0x31;
    data[10]=0x2e;
    data[11]=0x31;
    data[12]=0x37;
    data[13]=0x00;
    data[14]=0x00;
    data[15]=0x00;
    data[16]=0x72;  // RLP Protocol flags and length (high)
    data[17]=0x6e;  // 0x26e = 638 - 16
    data[18]=0x00;  // RLP Vector (Identifies RLP Data as 1.31 Protocol PDU)
    data[19]=0x00;
    data[20]=0x00;
    data[21]=0x04;

    // CID/UUID

    wxChar msb,lsb;
    wxString id=wxT(XLIGHTS_UUID);
    id.Replace(wxT("-"), wxT(""));
    id.MakeLower();
    if (id.Len() != 32) throw "invalid CID";
    for (int i=0,j=22; i < 32; i+=2) {
      msb=id.GetChar(i);
      lsb=id.GetChar(i+1);
      msb -= isdigit(msb) ? 0x30 : 0x57;
      lsb -= isdigit(lsb) ? 0x30 : 0x57;
      data[j++] = (wxByte)((msb << 4) | lsb);
    }

    data[38]=0x72;  // Framing Protocol flags and length (high)
    data[39]=0x58;  // 0x258 = 638 - 38
    data[40]=0x00;  // Framing Vector (indicates that the E1.31 framing layer is wrapping a DMP PDU)
    data[41]=0x00;
    data[42]=0x00;
    data[43]=0x02;
    data[44]='x';   // Source Name (64 bytes)
    data[45]='L';
    data[46]='i';
    data[47]='g';
    data[48]='h';
    data[49]='t';
    data[50]='s';
    data[51]=0x00;
    data[52]=0x00;
    data[53]=0x00;
    data[54]=0x00;
    data[55]=0x00;
    data[56]=0x00;
    data[57]=0x00;
    data[58]=0x00;
    data[59]=0x00;
    data[60]=0x00;
    data[61]=0x00;
    data[61]=0x00;
    data[62]=0x00;
    data[63]=0x00;
    data[64]=0x00;
    data[65]=0x00;
    data[66]=0x00;
    data[67]=0x00;
    data[68]=0x00;
    data[69]=0x00;
    data[70]=0x00;
    data[71]=0x00;
    data[71]=0x00;
    data[72]=0x00;
    data[73]=0x00;
    data[74]=0x00;
    data[75]=0x00;
    data[76]=0x00;
    data[77]=0x00;
    data[78]=0x00;
    data[79]=0x00;
    data[80]=0x00;
    data[81]=0x00;
    data[81]=0x00;
    data[82]=0x00;
    data[83]=0x00;
    data[84]=0x00;
    data[85]=0x00;
    data[86]=0x00;
    data[87]=0x00;
    data[88]=0x00;
    data[89]=0x00;
    data[90]=0x00;
    data[91]=0x00;
    data[91]=0x00;
    data[92]=0x00;
    data[93]=0x00;
    data[94]=0x00;
    data[95]=0x00;
    data[96]=0x00;
    data[97]=0x00;
    data[98]=0x00;
    data[99]=0x00;
    data[100]=0x00;
    data[101]=0x00;
    data[101]=0x00;
    data[102]=0x00;
    data[103]=0x00;
    data[104]=0x00;
    data[105]=0x00;
    data[106]=0x00;
    data[107]=0x00;
    data[108]=100;  // Priority
    data[109]=0x00; // Reserved
    data[110]=0x00; // Reserved
    data[111]=0x00; // Sequence Number
    data[112]=0x00; // Framing Options Flags
    data[113]=UniverseNumber >> 8;   // Universe Number (high)
    data[114]=UniverseNumber & 0xff; // Universe Number (low)

    data[115]=0x72;  // DMP Protocol flags and length (high)
    data[116]=0x0b;  // 0x20b = 638 - 115
    data[117]=0x02;  // DMP Vector (Identifies DMP Set Property Message PDU)
    data[118]=0xa1;  // DMP Address Type & Data Type
    data[119]=0x00;  // First Property Address (high)
    data[120]=0x00;  // First Property Address (low)
    data[121]=0x00;  // Address Increment (high)
    data[122]=0x01;  // Address Increment (low)
    data[123]=0x02;  // Property value count (high)
    data[124]=0x01;  // Property value count (low)
    data[125]=0x00;  // DMX512-A START Code

    wxIPV4address localaddr;
    localaddr.AnyAddress();
    localaddr.Service(0x8000 | NetNum);
    datagram = new wxDatagramSocket(localaddr, wxSOCKET_NOWAIT);

    remoteAddr.Hostname (ipaddr);
    remoteAddr.Service (E131_PORT);
  };

  void SetChannelCount(int numchannels) {
    if (numchannels > 512) {
      throw "max channels on DMX is 512";
    }
    changed=0;
    CreateChannels(numchannels);
  };

  void TimerEnd() {
    if (changed || SkipCount > 10) {
      data[111]=SequenceNum;
      datagram->SendTo(remoteAddr, data, E131_PACKET_LEN);
      SequenceNum= SequenceNum==255 ? 0 : SequenceNum+1;
      changed=0;
      SkipCount=0;
    } else {
      SkipCount++;
    }
  };
};



// Should be called with: 0 <= chindex <= 1015 (max channels=127*8)
class xNetwork_Renard: public xNetwork_Dimmer {
protected:
  wxByte data[1024];

  void SetMappedIntensity (int chindex, wxByte mappedintensity) {
    wxByte RenIntensity;
    switch (mappedintensity) {
      case 0x7D:
      case 0x7E: RenIntensity=0x7C; break;
      case 0x7F: RenIntensity=0x80; break;
      default: RenIntensity=mappedintensity;
    }
    data[chindex+2]=RenIntensity;
    changed=1;
  };

public:
  void SetChannelCount(int numchannels) {
    if (numchannels > 1016) {
      throw "max channels on a Renard network is 1016";
    }
    if (numchannels % 8 != 0) {
      throw "Number of Renard channels must be a multiple of 8";
    }
    datalen=numchannels+2;
    data[0]=0x7E;               // start of message
    data[1]=0x80;               // start address
    changed=0;
    CreateChannels(numchannels);
    SerialConfig[2]='2'; // use 2 stop bits so padding chars are not required
  };

  void TimerEnd() {
    if (changed && serptr) {
      serptr->Write((char *)data,datalen);
      changed=0;
    }
  };
};



// Should be called with: 0 <= chindex <= 4095
class xNetwork_Pixelnet: public xNetwork_Dimmer {
protected:
  wxByte data[4096];
  wxByte SerialBuffer[4097];

  void SetMappedIntensity (int chindex, wxByte mappedintensity) {
    data[chindex]=mappedintensity==170 ? 171 : mappedintensity;
  };

public:
  void SetChannelCount(int numchannels) {
    if (numchannels > 4096) {
      throw "max channels on a Pixelnet network is 4096";
    }
    datalen=numchannels;
    CreateChannels(numchannels);
    memset(data,0,sizeof(data));
  };

  void TimerEnd() {
    if (serptr && serptr->WaitingToWrite()==0) {
      memcpy(&SerialBuffer[1],data,sizeof(data));
      SerialBuffer[0]=170;    // start of message
      serptr->Write((char *)SerialBuffer,sizeof(SerialBuffer));
    }
  };
};



// Should be called with: 0 <= chindex <= 3839 (max channels=240*16)
class xNetwork_LOR: public xNetwork {
protected:
  long lastheartbeat;

  // set intensity to a value that has already been mapped
  void SetMappedIntensity (int chindex, wxByte intensity) {
    wxByte d[6];
    d[0]=0;
    d[1]=chindex >> 4;
    if (d[1] < 0xF0) d[1]++;
    d[2]=3;
    d[3]=intensity;
    d[4]=0x80 | (chindex % 16);
    d[5]=0;
    //printf("LOR SetMappedIntensity 1=%02X 2=%02X 3=%02X 4=%02X\n",d[1],d[2],d[3],d[4]);
    if (serptr) serptr->Write((char *)d,6);
  };

  // shimmer or twinkle at constant intensity
  void shimtwink (wxByte cmd, int chindex, int period, int intensity) {
    wxByte d[8];
    d[0]=0;
    d[1]=chindex >> 4;
    if (d[1] < 0xF0) d[1]++;
    d[2]=cmd;
    d[3]=0x80 | (chindex % 16);
    if (intensity == max_intensity) {
      d[4]=0;
      if (serptr) serptr->Write((char *)d,5);
    } else {
      d[4]=0x81;
      d[5]=3;  // intensity command
      d[6]=IntensityMap[intensity];
      d[7]=0;
      if (serptr) serptr->Write((char *)d,8);
    }
  };

  // shimmer or twinkle while ramping intensity up or down
  virtual void shimtwinkfade (wxByte cmd, int chindex, int period, int duration, int startintensity, int endintensity) {
    wxByte d[11];
    d[0]=0;
    d[1]=chindex >> 4;
    if (d[1] < 0xF0) d[1]++;
    d[2]=cmd;
    d[3]=0x80 | (chindex % 16);
    d[4]=0x81;
    d[6]=IntensityMap[startintensity];
    d[7]=IntensityMap[endintensity];
    if (d[6] == d[7]) {
      d[5]=3;  // intensity command
      d[7]=0;
      if (serptr) serptr->Write((char *)d,8);
    } else {
      d[5]=4;  // ramp command
      int deltaInt=abs((int)d[6] - (int)d[7]);
      int ramp=(int)((double)deltaInt/239.0*510.0*1000.0/(double)duration+0.5);
      d[8]=ramp >> 8;
      d[9]=ramp & 0xFF;
      if (d[9] == 0) {
        d[9]=1;
        d[8] |= 0x40;
      } else if (d[8] == 0) {
        d[8] |= 0x80;
      }
      d[10]=0;
      if (serptr) serptr->Write((char *)d,11);
    }
  };

public:
  void SendHeartbeat () {
    wxByte d[5];
    d[0]=0;
    d[1]=0xFF;
    d[2]=0x81;
    d[3]=0x56;
    d[4]=0;
    if (serptr) serptr->Write((char *)d,5);
  };

  void TimerEnd() {
    // send heartbeat
    if (timer_msec > lastheartbeat+300 || timer_msec < lastheartbeat || lastheartbeat < 0) {
      SendHeartbeat();
      lastheartbeat=timer_msec;
    }
  };

  void SetChannelCount(int numchannels) {
    num_channels=numchannels;
  };

  void ResetTimer() {
    lastheartbeat=-1;
  };

  // maxintensity is usually 100 (LOR) or 255 (Vixen)
  void SetMaxIntensity(int maxintensity) {
    int temp;
    max_intensity=maxintensity;
    for (int i=0; i<=maxintensity; i++) {
      temp=(int)(100.0*(double)i/(double)maxintensity+0.5);
      switch (temp) {
        case 0:   IntensityMap[i]=0xF0; break;
        case 100: IntensityMap[i]=0x01; break;
        default:  IntensityMap[i]=228-temp*2; break;
      }
    }
  };

  void ramp (int chindex, int duration, int startintensity, int endintensity) {
    wxByte d[9];
    d[3]=IntensityMap[startintensity];
    d[4]=IntensityMap[endintensity];
    if (d[3] == d[4]) {
      SetMappedIntensity(chindex, d[3]);
    } else {
      d[0]=0;
      d[1]=chindex >> 4;
      if (d[1] < 0xF0) d[1]++;
      d[2]=4;  // ramp command
      int deltaInt=abs((int)d[3] - (int)d[4]);
      int ramp=(int)((double)deltaInt/239.0*510.0*1000.0/(double)duration+0.5);
      d[5]=ramp >> 8;
      d[6]=ramp & 0xFF;
      if (d[6] == 0) {
        d[6]=1;
        d[5] |= 0x40;
      } else if (d[5] == 0) {
        d[5] |= 0x80;
      }
      d[7]=0x80 | (chindex % 16);
      d[8]=0;
      //printf("LOR ramp 1=%02X 2=%02X 3=%02X 4=%02X 5=%02X 6=%02X 7=%02X\n",d[1],d[2],d[3],d[4],d[5],d[6],d[7]);
      if (serptr) serptr->Write((char *)d,9);
    }
  };

  void twinkle (int chindex, int period, int intensity) {
    shimtwink(6, chindex, period, intensity);
  };

  virtual void twinklefade (int chindex, int period, int duration, int startintensity, int endintensity) {
    shimtwinkfade(6, chindex, period, duration, startintensity, endintensity);
  };

  void shimmer (int chindex, int period, int intensity) {
    shimtwink(7, chindex, period, intensity);
  };

  virtual void shimmerfade (int chindex, int period, int duration, int startintensity, int endintensity) {
    shimtwinkfade(7, chindex, period, duration, startintensity, endintensity);
  };

  void off (int chindex) {
    SetIntensity(chindex, 0);
  };

  void alloff () {
    for (int i=0; i<16; i++)
      off(0xFF * 16 + i);
  };
};


// Same as LOR except shimmer and twinkle
class xNetwork_DLight: public xNetwork_LOR {

  // shimmer or twinkle at constant intensity
  void shimtwink (wxByte cmd, int chindex, int period, int intensity) {
    wxByte d[8];
    d[0]=0;
    d[1]=chindex >> 4;
    if (d[1] < 0xF0) d[1]++;
    d[2]=cmd;
    d[3]=0x80 | (chindex % 16);
    if (intensity == max_intensity) {
      d[4]=0;
      if (serptr) serptr->Write((char *)d,5);
    } else {
      d[4]=IntensityMap[intensity];
      d[5]=0;
      if (serptr) serptr->Write((char *)d,6);
    }
  };

  // shimmer or twinkle while ramping intensity up or down
  virtual void shimtwinkfade (wxByte cmd, int chindex, int period, int duration, int startintensity, int endintensity) {
    wxByte d[10];
    d[3]=IntensityMap[startintensity];
    d[4]=IntensityMap[endintensity];
    if (d[3] == d[4]) {
      shimtwink(cmd, chindex, period, startintensity);
    } else {
      d[0]=0;
      d[1]=chindex >> 4;
      if (d[1] < 0xF0) d[1]++;
      d[2]=4;  // ramp command
      int deltaInt=abs((int)d[3] - (int)d[4]);
      int ramp=(int)((double)deltaInt/239.0*510.0*1000.0/(double)duration+0.5);
      d[5]=ramp >> 8;
      d[6]=ramp & 0xFF;
      if (d[6] == 0) {
        d[6]=1;
        d[5] |= 0x40;
      } else if (d[5] == 0) {
        d[5] |= 0x80;
      }
      d[7]=0x80 | (chindex % 16);
      d[8]=8-cmd; // 1=shimmer, 2=twinkle
      d[9]=0;
      //printf("D-Light shimtwinkfade 1=%02X 2=%02X 3=%02X 4=%02X 5=%02X 6=%02X 7=%02X\n",d[1],d[2],d[3],d[4],d[5],d[6],d[7]);
      if (serptr) serptr->Write((char *)d,10);
    }
  };

};


// xOutput should be a singleton
// It contains references to all of the networks
class xOutput {
protected:
  WX_DEFINE_ARRAY_PTR(xNetwork*, xNetworkArray);
  xNetworkArray networks;

public:
  xOutput() {
    srand((unsigned)time(NULL));
  };

  ~xOutput() {
    WX_CLEAR_ARRAY(networks);
  };
  
  size_t NetworkCount() {
    return networks.GetCount();
  };

  // returns the network index
  size_t addnetwork (const wxString& NetworkType, int chcount, const wxString& portname, int baudrate) {
    xNetwork* netobj;
    wxString nettype3 = NetworkType.Upper().Left(3);
    if (nettype3 == wxT("LOR")) {
        netobj = new xNetwork_LOR();
    } else if (nettype3 == wxT("D-L")) {
        netobj = new xNetwork_DLight();
    } else if (nettype3 == wxT("REN")) {
        netobj = new xNetwork_Renard();
    } else if (nettype3 == wxT("DMX")) {
        netobj = new xNetwork_DMXpro();
    } else if (nettype3 == wxT("OPE")) {
        netobj = new xNetwork_DMXopen();
    } else if (nettype3 == wxT("PIX")) {
        netobj = new xNetwork_Pixelnet();
    } else if (nettype3 == wxT("E13")) {
        netobj = new xNetwork_E131();
    } else {
        throw "unknown network type";
    }
    size_t netnum = networks.GetCount();
    networks.Add(netobj);
    netobj->SetChannelCount(chcount);
    wxString description = NetworkType + _(" on ") + portname;
    netobj->SetNetworkDesc(description);
    if (nettype3 == wxT("E13")) {
      netobj->InitNetwork(portname, baudrate, (wxUint16) netnum);  // portname is ip address and baudrate is universe number
    } else {
      netobj->InitSerialPort(portname, baudrate);
    }
    return netnum;
  };

  int GetChannelCount(size_t netnum) {
    if (netnum >= networks.GetCount()) return 0;
    return networks[netnum]->GetChannelCount();
  };

  wxString GetNetworkDesc(size_t netnum) {
    if (netnum >= networks.GetCount()) return wxT("");
    return networks[netnum]->GetNetworkDesc();
  };

  void SetMaxIntensity(int maxintensity) {
    for (size_t i=0; i<networks.GetCount(); i++) {
      networks[i]->SetMaxIntensity(maxintensity);
    }
  };

  // chindex starts at 0
  // duration is in milliseconds
  // intensity values are relative to the last SetMaxIntensity call
  void ramp (size_t netnum, int chindex, int duration, int startintensity, int endintensity) {
    if (netnum >= networks.GetCount()) return;
    if (chindex <= networks[netnum]->GetChannelCount())
      networks[netnum]->ramp(chindex, duration, startintensity, endintensity);
  };

  // chindex starts at 0
  // intensity is relative to the last SetMaxIntensity call
  void SetIntensity (size_t netnum, int chindex, int intensity) {
    if (netnum >= networks.GetCount()) return;
    if (chindex <= networks[netnum]->GetChannelCount())
      networks[netnum]->SetIntensity(chindex, intensity);
  };

  // chindex starts at 0
  // intensity is relative to the last SetMaxIntensity call
  void twinkle (size_t netnum, int chindex, int period, int intensity) {
    if (netnum >= networks.GetCount()) return;
    if (chindex <= networks[netnum]->GetChannelCount())
      networks[netnum]->twinkle(chindex, period, intensity);
  };

  void twinklefade (size_t netnum, int chindex, int period, int duration, int startintensity, int endintensity) {
    if (netnum >= networks.GetCount()) return;
    if (chindex <= networks[netnum]->GetChannelCount())
      networks[netnum]->twinklefade(chindex, period, duration, startintensity, endintensity);
  };

  void shimmer (size_t netnum, int chindex, int period, int intensity) {
    if (netnum >= networks.GetCount()) return;
    if (chindex <= networks[netnum]->GetChannelCount())
      networks[netnum]->shimmer(chindex, period, intensity);
  };

  void shimmerfade (size_t netnum, int chindex, int period, int duration, int startintensity, int endintensity) {
    if (netnum >= networks.GetCount()) return;
    if (chindex <= networks[netnum]->GetChannelCount())
      networks[netnum]->shimmerfade(chindex, period, duration, startintensity, endintensity);
  };

  void off (size_t netnum, int chindex) {
    if (netnum >= networks.GetCount()) return;
    if (chindex <= networks[netnum]->GetChannelCount())
      networks[netnum]->off(chindex);
  };

  void alloff () {
    for(size_t i=0; i < networks.GetCount(); ++i) {
      networks[i]->alloff();
    }
  };

  void ResetTimer() {
    for(size_t i=0; i < networks.GetCount(); ++i) {
      networks[i]->ResetTimer();
    }
  };

  void TimerStart(long msec) {
    for(size_t i=0; i < networks.GetCount(); ++i) {
      networks[i]->TimerStart(msec);
    }
  };

  void TimerEnd() {
    for(size_t i=0; i < networks.GetCount(); ++i) {
      networks[i]->TimerEnd();
    }
  };

  void ClosePorts() {
    for(size_t i=0; i < networks.GetCount(); ++i) {
      networks[i]->CloseSerialPort();
    }
  };
  
  bool TxEmpty() {
    for(size_t i=0; i < networks.GetCount(); ++i) {
      if (!networks[i]->TxEmpty()) return false;
    }
    return true;
  };
};
