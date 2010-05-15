#include "../../serial/ctb.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <string>

#include "./getopt.cpp"

using namespace std;

// ----------------- options -------------------------------
const char* options="b:d:h:p:t:";

const char* helpMessage =
{
    "A simple serial port test to send one set of data to a DMX dongle\n"
    "ctbtest [options]\n"
    "available options are:\n"
    "-b     : baudrate [any value], default is 38400\n"
    "-d     : connected device, default is COM1\n"
    "-h     : print this\n"
    "-p     : protocol like 8N1\n"
    "-t     : communication timeout in ms (default is 100ms)\n"
};

int main(int argc,char* argv[])
{
    string line;
    int baudrate = 115200;
    string devname = "/dev/ttyUSB0";
    string protocol = "8N1";
    int timeout = 100;
    int quit = 0;
	int channel = 1;
    int val;
	char data[518];
	istringstream intConv;

    while ( ( val=getopt( argc, argv, (char*)options ) ) != EOF ) {
	   switch ( val ) {
	   case 'b' : baudrate = strtol( optarg, NULL, 10 ); break;
	   case 'd' : devname = optarg; break;
	   case 'h' : cerr << helpMessage << endl; exit( 0 );
	   case 'p' : protocol = optarg; break;
	   case 't' : timeout = strtol( optarg, NULL, 10 ); break;
	   }
    }

	ctb::SerialPort* serialPort = new ctb::SerialPort();

	if( serialPort->Open( devname.c_str(), baudrate, protocol.c_str(), ctb::SerialPort::NoFlowControl ) < 0 ) {
	   cout << "Cannot open " << devname.c_str() << endl;
	   return -1;
	}

    cout << "Enter your command or just press Enter without any\n"
	   "input for exit!";

    while( true ) {

		cout << endl << "Your input >";

		// read the string to send
		getline( cin, line );
		intConv.clear();
		intConv.str(line);
		if (intConv>>val) {
			data[0]=0x7E;   // start of message
			data[1]=6;      // dmx send
			data[2]=1;      // length LSB  (513 = 0x201)
			data[3]=2;      // length MSB
			data[channel+4]=(char)val;
			data[517]=0xE7; // end of message
      
			if( serialPort->Write( data, 518 ) != 518 ) {
			  cerr << "Incomplete data transmission" << endl;
			}
		} else {
		  break;
		}

	   cout << endl;
	   
    } // while( true )

    serialPort->Close();
    delete serialPort;
    return 0;
}
