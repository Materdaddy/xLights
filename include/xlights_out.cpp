/***************************************************************
 * Name:      xlights_out.cpp
 * Purpose:
    Defines a common API for LOR, DMX, and Renard networks
    All calls should be made to xOutput class
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-05-07
 * Copyright: 2010 by Matt Brown
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

#include "serial/serport.cpp"
#include <vector>
#include <list>
#include <time.h>

#define MAXNETWORKS 10


// *************************************************
// * Base class to define a collection of channels
// *************************************************
class xNetwork {
protected:
  ctb::SerialPort* serptr;
  unsigned char IntensityMap[256];
  char SerialConfig[4];
  long timer_msec;
  int max_intensity;
  int num_channels;
  friend class xChannel_Dimmer;

  virtual void SetMappedIntensity (int chindex, unsigned char intensity) =0;

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

  unsigned char MapIntensity(unsigned char intensity) {
    return IntensityMap[intensity];
  };

  int GetChannelCount() {
    return num_channels;
  };

  virtual void SetChannelCount(int numchannels) = 0;

  virtual void SetMaxIntensity(int maxintensity) = 0;

  void InitSerialPort(const wxString& portname, int baudrate) {
    static char errmsg[100];
    serptr=new ctb::SerialPort();
    int errcode=serptr->Open(portname, baudrate, SerialConfig);
    if (errcode < 0) {
      sprintf(errmsg,"unable to open serial port, error code=%d",errcode);
      throw errmsg;
    }
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

  virtual void SetIntensity (int chindex, unsigned char intensity) {
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
  unsigned char rampstart,rampend;
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

  void ramp (int duration, unsigned char startintensity, unsigned char endintensity) {
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
  void twinkle (int period, unsigned char intensity) {
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
  void twinklefade (int period, int duration, unsigned char startintensity, unsigned char endintensity) {
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
  void shimmer (int period, unsigned char intensity) {
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
  void shimmerfade (int period, int duration, unsigned char startintensity, unsigned char endintensity) {
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

  void ResetTimer() {
    timerCallbackList.clear();
  };

  // callbacks return true if they are finished, false if they will continue to run
  virtual void TimerStart(long msec) {
    timer_msec=msec;
    // process list of channels needing callbacks
    std::list<int>::iterator temp,it = timerCallbackList.begin();
    while (it != timerCallbackList.end()) {
      if (channels[*it]->ChannelCallback(msec)) {
        temp=it;
        ++it; // move past the one we are about to erase
        timerCallbackList.erase(temp);
      } else {
        ++it;
      }
    }
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

  virtual void SetIntensity (int chindex, unsigned char intensity) {
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
class xNetwork_DMXentec: public xNetwork_Dimmer {
protected:
  unsigned char data[518];

  void SetMappedIntensity(int chindex, unsigned char mappedintensity) {
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

  void SetMaxIntensity(int maxintensity) {
    max_intensity=maxintensity;
    for (int i=0; i<=maxintensity; i++) {
      IntensityMap[i]=(int)(255.0*(double)i/(double)maxintensity+0.5);
    }
  };

  void TimerEnd() {
    if (changed && serptr) {
      serptr->Write((char *)data,datalen);
      changed=0;
    }
  };
};



// Should be called with: 0 <= chindex <= 1015 (max channels=127*8)
class xNetwork_Renard: public xNetwork_Dimmer {
protected:
  unsigned char data[1024];

  void SetMappedIntensity (int chindex, unsigned char mappedintensity) {
    data[chindex+2]=mappedintensity;
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

  void SetMaxIntensity(int maxintensity) {
    max_intensity=maxintensity;
    for (int temp,i=0; i<=maxintensity; i++) {
      temp=(int)(255.0*(double)i/(double)maxintensity+0.5);
      switch (temp) {
        case 0x7D:
        case 0x7E: temp=0x7C; break;
        case 0x7F: temp=0x80; break;
      }
      IntensityMap[i]=temp;
    }
  };

  void TimerEnd() {
    if (changed && serptr) {
      serptr->Write((char *)data,datalen);
      changed=0;
    }
  };
};



// Should be called with: 0 <= chindex <= 3839 (max channels=240*16)
class xNetwork_LOR: public xNetwork {
protected:
  long lastheartbeat;

  // set intensity to a value that has already been mapped
  void SetMappedIntensity (int chindex, unsigned char intensity) {
    unsigned char d[6];
    d[0]=0;
    d[1]=chindex >> 4;
    if (d[1] < 0xF0) d[1]++;
    d[2]=3;
    d[3]=intensity;
    d[4]=0x80 | (chindex % 16);
    d[5]=0;
    //printf("LOR SetMappedIntensity 1=%02X 2=%02X 3=%02X 4=%02X\n",d[1],d[2],d[3],d[4]);
    serptr->Write((char *)d,6);
  };

  // shimmer or twinkle at constant intensity
  void shimtwink (unsigned char cmd, int chindex, int period, int intensity) {
    unsigned char d[8];
    d[0]=0;
    d[1]=chindex >> 4;
    if (d[1] < 0xF0) d[1]++;
    d[2]=cmd;
    d[3]=0x80 | (chindex % 16);
    if (intensity == max_intensity) {
      d[4]=0;
      serptr->Write((char *)d,5);
    } else {
      d[4]=0x81;
      d[5]=3;  // intensity command
      d[6]=IntensityMap[intensity];
      d[7]=0;
      serptr->Write((char *)d,8);
    }
  };

  // shimmer or twinkle while ramping intensity up or down
  virtual void shimtwinkfade (unsigned char cmd, int chindex, int period, int duration, int startintensity, int endintensity) {
    unsigned char d[11];
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
      serptr->Write((char *)d,8);
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
      serptr->Write((char *)d,11);
    }
  };

public:
  void SendHeartbeat () {
    unsigned char d[5];
    d[0]=0;
    d[1]=0xFF;
    d[2]=0x81;
    d[3]=0x56;
    d[4]=0;
    serptr->Write((char *)d,5);
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
    unsigned char d[9];
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
      serptr->Write((char *)d,9);
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
  void shimtwink (unsigned char cmd, int chindex, int period, int intensity) {
    unsigned char d[8];
    d[0]=0;
    d[1]=chindex >> 4;
    if (d[1] < 0xF0) d[1]++;
    d[2]=cmd;
    d[3]=0x80 | (chindex % 16);
    if (intensity == max_intensity) {
      d[4]=0;
      serptr->Write((char *)d,5);
    } else {
      d[4]=IntensityMap[intensity];
      d[5]=0;
      serptr->Write((char *)d,6);
    }
  };

  // shimmer or twinkle while ramping intensity up or down
  virtual void shimtwinkfade (unsigned char cmd, int chindex, int period, int duration, int startintensity, int endintensity) {
    unsigned char d[10];
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
      serptr->Write((char *)d,10);
    }
  };

};


// xOutput should be a singleton
// It contains references to all of the networks
class xOutput {
protected:
  xNetwork* networks[MAXNETWORKS];
  int lastnetnum;

public:
  xOutput() {
    srand((unsigned)time(NULL));
    lastnetnum = -1;
    for (int i=0; i<MAXNETWORKS; i++)
      networks[i]=0;
  };

  ~xOutput() {
    for (int i=0; i<MAXNETWORKS; i++) {
      if (networks[i]) delete networks[i];
    }
  };

  void setnetwork (const wxString& nettype3, int netnum, int chcount, const wxString& portname, int baudrate) {
    xNetwork* netobj;
    if (networks[netnum]) throw "duplicate network defined";
    if (nettype3 == wxT("LOR")) {
        netobj = new xNetwork_LOR();
    } else if (nettype3 == wxT("D-L")) {
        netobj = new xNetwork_DLight();
    } else if (nettype3 == wxT("Ren")) {
        netobj = new xNetwork_Renard();
    } else if (nettype3 == wxT("DMX")) {
        netobj = new xNetwork_DMXentec();
    } else {
        throw "unknown network type";
    }
    networks[netnum] = netobj;
    netobj->SetChannelCount(chcount);
    netobj->InitSerialPort(portname, baudrate);
    if (netnum > lastnetnum) lastnetnum = netnum;
  };

  int addnetwork (const wxString& nettype3, int chcount, const wxString& portname, int baudrate) {
    for (int i=0; i<MAXNETWORKS; i++) {
      if (networks[i] == 0) {
        setnetwork(nettype3, i, chcount, portname, baudrate);
        return i;
      }
    }
    return -1;
  };

  void SetMaxIntensity(int maxintensity) {
    for (int i=0; i<MAXNETWORKS; i++) {
      if (networks[i]) networks[i]->SetMaxIntensity(maxintensity);
    }
  };

  // chindex starts at 0
  // duration is in milliseconds
  // intensity values are relative to the last SetMaxIntensity call
  void ramp (int netnum, int chindex, int duration, int startintensity, int endintensity) {
    if (netnum < 0 || netnum >= MAXNETWORKS || !networks[netnum]) return;
    if (chindex <= networks[netnum]->GetChannelCount())
      networks[netnum]->ramp(chindex, duration, startintensity, endintensity);
  };

  // chindex starts at 0
  // intensity is relative to the last SetMaxIntensity call
  void SetIntensity (int netnum, int chindex, int intensity) {
    if (netnum < 0 || netnum >= MAXNETWORKS || !networks[netnum]) return;
    if (chindex <= networks[netnum]->GetChannelCount())
      networks[netnum]->SetIntensity(chindex, intensity);
  };

  // chindex starts at 0
  // intensity is relative to the last SetMaxIntensity call
  void twinkle (int netnum, int chindex, int period, int intensity) {
    if (netnum < 0 || netnum >= MAXNETWORKS || !networks[netnum]) return;
    if (chindex <= networks[netnum]->GetChannelCount())
      networks[netnum]->twinkle(chindex, period, intensity);
  };

  void twinklefade (int netnum, int chindex, int period, int duration, int startintensity, int endintensity) {
    if (netnum < 0 || netnum >= MAXNETWORKS || !networks[netnum]) return;
    if (chindex <= networks[netnum]->GetChannelCount())
      networks[netnum]->twinklefade(chindex, period, duration, startintensity, endintensity);
  };

  void shimmer (int netnum, int chindex, int period, int intensity) {
    if (netnum < 0 || netnum >= MAXNETWORKS || !networks[netnum]) return;
    if (chindex <= networks[netnum]->GetChannelCount())
      networks[netnum]->shimmer(chindex, period, intensity);
  };

  void shimmerfade (int netnum, int chindex, int period, int duration, int startintensity, int endintensity) {
    if (netnum < 0 || netnum >= MAXNETWORKS || !networks[netnum]) return;
    if (chindex <= networks[netnum]->GetChannelCount())
      networks[netnum]->shimmerfade(chindex, period, duration, startintensity, endintensity);
  };

  void off (int netnum, int chindex) {
    if (netnum < 0 || netnum >= MAXNETWORKS || !networks[netnum]) return;
    if (chindex <= networks[netnum]->GetChannelCount())
      networks[netnum]->off(chindex);
  };

  void alloff () {
    for(int i=0; i <= lastnetnum; ++i) {
      if (networks[i]) networks[i]->alloff();
    }
  };

  void ResetTimer() {
    for(int i=0; i <= lastnetnum; ++i) {
      if (networks[i]) networks[i]->ResetTimer();
    }
  };

  void TimerStart(long msec) {
    for(int i=0; i <= lastnetnum; ++i) {
      if (networks[i]) networks[i]->TimerStart(msec);
    }
  };

  void TimerEnd() {
    for(int i=0; i <= lastnetnum; ++i) {
      if (networks[i]) networks[i]->TimerEnd();
    }
  };
};
