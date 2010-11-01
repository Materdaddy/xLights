/////////////////////////////////////////////////////////////////////////////
// Name:        serport.cpp
// Purpose:
// Author:      Joachim Buermann (adapted for xLights by Matt Brown)
// Copyright:   (c) 2010 Joachim Buermann
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <sstream>

namespace ctb {

/*!
  \class SerialPort_x
  SerialPort_x is the basic class for serial communication via
  the serial comports. It is also an abstract class and defines
  all necessary methods, which the derivated plattform dependent
  classes must be invoke.
*/
class SerialPort_x
{
  protected:
     /*!
    Close the interface (internally the file descriptor, which was
    connected with the interface).
    \return zero on success, otherwise -1.
     */
     virtual int CloseDevice() = 0;
     virtual int OpenDevice( const wxString& portname, int baudrate, const char* protocol ) = 0;
     /*!
    \brief contains the internal (os specific) name of the serial
    device.
     */
    wxString m_devname;
    int callback;  // used in basic script

  public:

    SerialPort_x() {
      m_devname = wxT("");
      callback = -1;
    };

    virtual ~SerialPort_x() {
    };


    void SetCallback(int cb) {
        callback = cb;
    }

    int GetCallback() {
        return callback;
    }

    virtual int AvailableToRead() = 0;

     /*!
    Closed the interface. Internally it calls the CloseDevice()
    method, which must be defined in the derivated class.
    \return zero on success, or -1 if an error occurred.
     */
    int Close()
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
    int Open( const wxString& portname, int baudrate, const char* protocol = "8N1" )
    {
      return OpenDevice(portname, baudrate, protocol);
    };

  }; // class SerialPort_x
} // namespace ctb

#if defined (WIN32)
# include "ser_win32.cpp"
#else
# include "ser_posix.cpp"
#endif
