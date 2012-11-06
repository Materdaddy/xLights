//
// Just compile with g++, then run a.out or a.exe
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <string>

// compatibility with wxWidgets

#ifdef UNICODE
#define wxT(x) L ## x
#else
#define wxT(x) x
#endif

#ifdef WIN32
#define DEFAULTPORT "COM1"
#else
#define DEFAULTPORT "/dev/ttyUSB0"
#endif

typedef std::string wxString;


#include "../../include/serial/serport.cpp"
#include "./getopt.cpp"

using namespace std;

// ----------------- options -------------------------------
const char* options="b:d:h:p:t:";

const char* helpMessage =
{
    "A simple serial port test to send one set of data to a DMX dongle\n"
    "ctbtest [options]\n"
    "available options are:\n"
    "-b     : baudrate [any value], default is 115200\n"
    "-d     : connected device, default is " DEFAULTPORT "\n"
    "-h     : print this\n"
};

int main(int argc,char* argv[])
{
  string line;
  int baudrate = 115200;
  wxString devname = DEFAULTPORT;
  string protocol = "8N1";
  int quit = 0;
  int channel;
  int val;
  char data[518];

  while ( ( val=getopt( argc, argv, (char*)options ) ) != EOF ) {
    switch ( val ) {
      case 'b' : baudrate = strtol( optarg, NULL, 10 ); break;
      case 'd' : devname = optarg; break;
      case 'h' : cerr << helpMessage << endl; exit( 0 );
    }
  }

  ctb::SerialPort* serialPort = new ctb::SerialPort();

  if( serialPort->Open( devname, baudrate, protocol.c_str() ) < 0 ) {
     cout << "Cannot open " << devname.c_str() << endl;
     return -1;
  }

    cout << "Enter an invalid value to exit...\n";

    while( true ) {

      cout << endl << "Channel number (1-512) >";
      cin >> channel;
      if (channel < 1 || channel > 512) break;

      cout << endl << "Intensity (0-255) >";
      cin >> val;
      if (val < 0 || val > 255) break;

      data[0]=0x7E;   // start of message
      data[1]=6;      // dmx send
      data[2]=1;      // length LSB  (513 = 0x201)
      data[3]=2;      // length MSB
      data[channel+4]=(char)val;
      data[517]=0xE7; // end of message

      int cnt = serialPort->Write( data, 518 );
      if( cnt != 518 ) {
        printf("Incomplete data transmission: %d bytes sent",cnt);
      }

      cout << endl;

    } // while( true )

    serialPort->Close();
    delete serialPort;
    return 0;
}
