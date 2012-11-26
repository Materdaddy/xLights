/////////////////////////////////////////////////////////////////////////////
// Name:        ser_port.cpp
// Purpose:
// Author:      Joachim Buermann (adapted for xLights by Matt Brown)
// Copyright:   (c) 2010 Joachim Buermann
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <sstream>
#include "serial.h"
#include <wx/utils.h>

void SerialPort::SetCallback(int cb) {
    callback = cb;
}

int SerialPort::GetCallback() {
    return callback;
}

 /*!
Closed the interface. Internally it calls the CloseDevice()
method, which must be defined in the derivated class.
\return zero on success, or -1 if an error occurred.
 */
int SerialPort::Close()
{
  return CloseDevice();
};

 /*!
\brief Opens a serial port
\param portname the name of the serial port
\param baudrate any baudrate, also an unusual one, if your
serial device support them
\param protocol a string with the number of databits (5...8),
the parity setting (N=None,O=Odd,E=Even), and the count of stopbits (1 or 2)
\return the new file descriptor, or -1 if an error occurred
  */
int SerialPort::Open( const wxString& portname, int baudrate, const char* protocol )
{
  return OpenDevice(portname, baudrate, protocol);
};


#ifdef __WXMSW__
# include "serial_win32.cpp"
#elif defined __WXOSX__
# include "serial_osx.cpp"
#else
# include "serial_posix.cpp"
#endif
