#include "serportx.h"

#include <sstream>

namespace ctb {

    int SerialPort_x::Open( const char* portname, int baudrate,
					   const char* protocol,
					   FlowControl flowControl )
    {
	   SerialPort_DCS dcs;

	   dcs.baud = baudrate;

	   // default wordlen is 8
	   if( ( protocol[ 0 ] >= '5' ) && ( protocol[ 0 ] <= '8' )) {
		  
		  dcs.wordlen = protocol[ 0 ] - '0';

	   }
	   else {

		  return -1;

	   }

	   // protocol is given as a string like "8N1", the first
	   // character specifies the data bits (5...8), the second
	   // the parity (None,Odd,Even,Mark,Space).
	   // The third character defines the stopbit (1...2).
	   switch( protocol[ 1 ] ) {
	   case 'N': case 'n': dcs.parity = ParityNone; break;
	   case 'O': case 'o': dcs.parity = ParityOdd; break;
	   case 'E': case 'e': dcs.parity = ParityEven; break;
	   case 'M': case 'm': dcs.parity = ParityMark; break;
	   case 'S': case 's': dcs.parity = ParitySpace; break;
		  // all other parameters cause an error!
	   default: return -1;
	   }
	   // default stopbits is 1
	   if( ( protocol[ 2 ] >= '1' ) && ( protocol[ 2 ] <= '2' )) {
		  
		  dcs.stopbits = protocol[ 2 ] - '0';

	   }
	   else {

		  return -1;

	   }
	   // default flow control is disabled
	   dcs.rtscts = ( flowControl == RtsCtsFlowControl );

	   dcs.xonxoff = ( flowControl == XonXoffFlowControl );

	   // save the settings in the internal dcs for later use
	   m_dcs = dcs;

	   return OpenDevice( portname, &m_dcs );

    }

} // namespace ctb

