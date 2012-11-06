#include "../../include/xlights_out.cpp"
#include <winbase.h>
#include <iostream>

#define MAXINTENSITY 100
#define RATE 10
#define DURATION 9

xOutput xout;

void runtest() {
  int interval=1000/RATE;
  for (int i=0; i<RATE*DURATION; i++) {
    printf("%d\n",i);
    xout.TimerStart(i*interval);
    //if (i==RATE) xout.setintensity(0,0,MAXINTENSITY);
    //if (i==RATE) xout.twinkle(0,0,5000,1000);
    if (i==RATE) xout.ramp(0,0,2000,0,MAXINTENSITY);
    if (i==RATE*3) xout.shimmer(0,0,3000,50);
    if (i==RATE*6) xout.ramp(0,0,2000,MAXINTENSITY,0);
    if (i==RATE*DURATION-2) xout.alloff();
    xout.TimerEnd();
    Sleep(interval);
  }
}

int main(int argc, char* argv[])
{
  try {
    //xout.addnetwork(new xNetwork_LOR(),0,16,MAXINTENSITY,"COM5",57600);
    xout.addnetwork(new xNetwork_DMXentec(),0,16,MAXINTENSITY,"COM4",57600);
    runtest();
  }
  catch (const char *str) {
    std::cout << "Exception raised: " << str << '\n';
  }
  catch (char *str) {
    std::cout << "Exception raised: " << str << '\n';
  }
  return 0;
}
