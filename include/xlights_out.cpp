/*
 * xLights output classes
 *
 * Defines a common API for LOR, DMX, and Renard networks
 * All calls should be made to xOutput class
 *
 * Matt Brown
 * May 2010
 */

#include "../serial/ctb.h"
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
  int timer_msec;

public:
  xNetwork() {
    serptr=0;
    timer_msec=0;
  };

  virtual void SetMappedIntensity (int chindex, unsigned char intensity) =0;

  void SetIntensity (int chindex, unsigned char intensity) {
    SetMappedIntensity(chindex, IntensityMap[intensity]);
  };

  unsigned char MapIntensity(unsigned char intensity) {
    return IntensityMap[intensity];
  };

  virtual void Initialize(int numchannels, int maxintensity) = 0;

  virtual void InitSerialPort(const char* portname, int baudrate) {
    serptr=new ctb::SerialPort();
    int errcode=serptr->Open(portname, baudrate, "8N1");
    if (errcode) {
      char msg[100];
      sprintf(msg,"unable to open serial port, error code=%d",errcode);
      throw msg;
    }
  };

  virtual int TimerStart(int msec) {
    timer_msec=msec;
  };

  int GetTimer() {
    return timer_msec;
  };

  virtual void TimerEnd() =0;

  virtual void ramp (int chindex, int duration, int startintensity, int endintensity) =0;

  virtual void twinkle (int chindex, int duration, int period) =0;

  virtual void shimmer (int chindex, int duration, int period) =0;

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
  int myindex;
  char optype;
  int optimestart, optimeend, twinklestate, periodend, effectperiod;
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

  // duration - total duration of the effect (msec)
  // period - sets the upper bound on an individual twinkle (msec)
  void twinkle (int duration, int period) {
    optype='T';
    optimestart=mynet->GetTimer();
    optimeend=optimestart + duration;
    effectperiod=period;
    periodend=optimestart + NextTwinkleTime();
    twinklestate= rand01() < 0.5 ? 0 : 1;
    mynet->SetMappedIntensity(myindex,twinklestate*255);
  };

  // duration - total duration of the effect (msec)
  // period - sets the length of each shimmer, typically 50-100 (msec)
  void shimmer (int duration, int period) {
    optype='S';
    optimestart=mynet->GetTimer();
    optimeend=optimestart + duration;
    //printf("xChannel_Dimmer::shimmer duration=%d period=%d start=%d end=%d\n",duration,period,optimestart,optimeend);
    effectperiod=period;
    periodend=optimestart + effectperiod;
    twinklestate=1;
    mynet->SetMappedIntensity(myindex,255);
  };

  void off () {
    mynet->SetMappedIntensity(myindex,0);
  };

  // returns true if the current timed operation is finished, false otherwise
  int ChannelCallback(int curtime) {
    //printf("xChannel_Dimmer::ChannelCallback curtime=%d optype=%c\n",curtime,optype);
    switch (optype) {
      case 'R':
        if (curtime >= optimeend) {
          mynet->SetMappedIntensity(myindex, rampend);
          optype=' ';
        } else {
          mynet->SetMappedIntensity(myindex, (curtime - optimestart) / opduration * rampdiff + rampstart);
          return 0;
        }
        break;
      case 'T':
        if (curtime >= optimeend) {
          if (twinklestate) off();
          optype=' ';
        } else {
          if (curtime > periodend) {
            periodend+=NextTwinkleTime();
            twinklestate=1 - twinklestate;
            mynet->SetMappedIntensity(myindex,twinklestate*255);
          }
          return 0;
        }
        break;
      case 'S':
        if (curtime >= optimeend) {
          if (twinklestate) off();
          optype=' ';
        } else {
          if (curtime >= periodend) {
            periodend+=effectperiod;
            twinklestate=1 - twinklestate;
            mynet->SetMappedIntensity(myindex,twinklestate*255);
          }
          return 0;
        }
        break;
    }
    return 1;
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
    timerCallbackList.remove(channel);  // ensure no there are no lingering callbacks for this channel
    timerCallbackList.push_front(channel);
  };

public:
  xNetwork_Dimmer() {
  };

  ~xNetwork_Dimmer() {
    for(int i=0; i < channels.size(); ++i) {
      delete channels[i];
    }
    if (serptr) delete serptr;
  };

  // callbacks return true if they are finished, false if they will continue to run
  virtual int TimerStart(int msec) {
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
  };

  virtual void ramp (int chindex, int duration, int startintensity, int endintensity) {
    channels.at(chindex)->ramp(duration, startintensity, endintensity);
    AddChannelCallback(chindex);
  };

  virtual void twinkle (int chindex, int duration, int period) {
    channels.at(chindex)->twinkle(duration,period);
    AddChannelCallback(chindex);
  };

  virtual void shimmer (int chindex, int duration, int period) {
    channels.at(chindex)->shimmer(duration,period);
    AddChannelCallback(chindex);
  };

  void off (int chindex) {
    SetIntensity(chindex, 0);
  };

  virtual void alloff () {
    for(int i=0; i < channels.size(); ++i) {
      off(i);
    }
  };
};


// ******************************************************
// * This class represents a single DMX universe
// * Compatible with Entec Pro and Lynx DMX dongles
// * Methods should be called with: 0 <= chindex <= 511
// ******************************************************
class xNetwork_DMXentec: public xNetwork_Dimmer {
protected:
  unsigned char data[518];

public:
  void Initialize(int numchannels, int maxintensity) {
    if (numchannels > 512) throw "max channels on DMX is 512";
    int len=513;   // entec supports this, but lynx does not: len=numchannels < 24 ? 25 : numchannels+1;
    datalen=len+5;
    data[0]=0x7E;               // start of message
    data[1]=6;                  // dmx send
    data[2]=len & 0xFF;        // length LSB
    data[3]=(len >> 8) & 0xFF;  // length MSB
    data[4]=0;                  // DMX start
    data[datalen-1]=0xE7;       // end of message
    changed=0;
    CreateChannels(numchannels);
    for (int i=0; i<=maxintensity; i++) {
      IntensityMap[i]=(int)(255.0*(double)i/(double)maxintensity+0.5);
    }
    //printf("DMXentec::Initialize numchannels=%d len=%d datalen=%d\n",numchannels,len,datalen);
  };

  void SetMappedIntensity(int chindex, unsigned char mappedintensity) {
    data[chindex+5]=mappedintensity;
    //printf("DMXentec::SetMappedIntensity channel=%d mapped-value=%d\n",chindex,(int)mappedintensity);
    changed=1;
  };

  void TimerEnd() {
    if (changed && serptr) {
      //printf("DMXentec data sent: %02X %02X %02X %02X %02X %02X\n",data[0],data[1],data[2],data[3],data[4],data[5]);
      serptr->Write((char *)data,datalen);
      changed=0;
    }
  };
};



// Should be called with: 0 <= chindex <= 1015 (max channels=127*8)
class xNetwork_Renard: public xNetwork_Dimmer {
protected:
  unsigned char data[1024];

public:
  void Initialize(int numchannels, int maxintensity) {
    if (numchannels > 1016) throw "max channels on a Renard network is 1016";
    if (numchannels % 8 != 0) throw "Number of Renard channels must be a multiple of 8";
    datalen=numchannels+2;
    data[0]=0x7E;               // start of message
    data[1]=0x80;               // start address
    changed=0;
    CreateChannels(numchannels);
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

  void SetMappedIntensity (int chindex, unsigned char intensity) {
    data[chindex+2]=intensity;
    changed=1;
  };

  void InitSerialPort(const char* portname, int baudrate) {
    serptr=new ctb::SerialPort();
    // use 2 stop bits so padding chars are not required
    int errcode=serptr->Open(portname, baudrate, "8N2");
    if (errcode) {
      char msg[100];
      sprintf(msg,"unable to open serial port, error code=%d",errcode);
      throw msg;
    }
  };

  void TimerEnd() {
    if (changed && serptr) {
      //printf("Renard data sent: %02X %02X %02X %02X %02X %02X\n",data[0],data[1],data[2],data[3],data[4],data[5]);
      serptr->Write((char *)data,datalen);
      changed=0;
    }
  };
};



class xNetwork_LOR: public xNetwork {
protected:
  int lastheartbeat;

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

  // should be called with maxintensity of 100 or 255
  void Initialize(int numchannels, int maxintensity) {
    int temp;
    lastheartbeat=-1;
    for (int i=0; i<=maxintensity; i++) {
      temp=(int)(100.0*(double)i/(double)maxintensity+0.5);
      switch (temp) {
        case 0:   IntensityMap[i]=0xF0; break;
        case 100: IntensityMap[i]=0x01; break;
        default:  IntensityMap[i]=228-temp*2; break;
      }
    }
  };

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
      d[2]=4;
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

  void twinkle (int chindex, int duration, int period) {
    //printf("LOR twinkle %d\n",chindex);
    unsigned char d[5];
    d[0]=0;
    d[1]=chindex >> 4;
    if (d[1] < 0xF0) d[1]++;
    d[2]=6;
    d[3]=0x80 | (chindex % 16);
    d[4]=0;
    serptr->Write((char *)d,5);
  };

  void shimmer (int chindex, int duration, int period) {
    //printf("LOR shimmer %d\n",chindex);
    unsigned char d[5];
    d[0]=0;
    d[1]=chindex >> 4;
    if (d[1] < 0xF0) d[1]++;
    d[2]=7;
    d[3]=0x80 | (chindex % 16);
    d[4]=0;
    serptr->Write((char *)d,5);
  };

  void off (int chindex) {
    SetIntensity(chindex, 0);
  };

  void alloff () {
    for (int i=0; i<16; i++)
      off(0xFF * 16 + i);
  };
};


// xOutput should be a singleton
// It contains references to all of the networks
class xOutput {
protected:
  xNetwork* networks[MAXNETWORKS];

public:
  xOutput() {
    srand((unsigned)time(NULL));
    for (int i=0; i<MAXNETWORKS; i++)
      networks[i]=0;
  };

  ~xOutput() {
    for (int i=0; i<MAXNETWORKS; i++) {
      if (networks[i]) delete networks[i];
    }
  };

  void addnetwork (xNetwork* netobj, int netnum, int chcount, int maxintensity, const char* portname, int baudrate) {
    if (networks[netnum]) throw "duplicate network defined";
    networks[netnum] = netobj;
    netobj->Initialize(chcount, maxintensity);
    netobj->InitSerialPort(portname, baudrate);
  };

  void ramp (int netnum, int chindex, int duration, int startintensity, int endintensity) {
    networks[netnum]->ramp(chindex, duration, startintensity, endintensity);
  };

  void SetIntensity (int netnum, int chindex, int intensity) {
    networks[netnum]->SetIntensity(chindex, intensity);
  };

  void twinkle (int netnum, int chindex, int duration, int period) {
    networks[netnum]->twinkle(chindex, duration, period);
  };

  void shimmer (int netnum, int chindex, int duration, int period) {
    networks[netnum]->shimmer(chindex, duration, period);
  };

  void off (int netnum, int chindex) {
    networks[netnum]->off(chindex);
  };

  void alloff () {
    for(int i=0; i < MAXNETWORKS; ++i) {
      if (networks[i]) networks[i]->alloff();
    }
  };

  void TimerStart(int msec) {
    for(int i=0; i < MAXNETWORKS; ++i) {
      if (networks[i]) networks[i]->TimerStart(msec);
    }
  };

  void TimerEnd() {
    for(int i=0; i < MAXNETWORKS; ++i) {
      if (networks[i]) networks[i]->TimerEnd();
    }
  };
};
