/////////////////////////////////////////////////////////////////////////////
// Name:        ser_win32.cpp
// Purpose:
// Author:      Joachim Buermann (adapted for xLights by Matt Brown)
// Id:          $Id: serport.cpp,v 1.1.1.1 2004/11/24 10:30:11 jb Exp $
// Copyright:   (c) 2001 Joachim Buermann
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <windows.h>

#define SERIALPORT_BUFSIZE 4096

namespace ctb {

    enum SerialLineState
    {
      /*! Data Carrier Detect (read only) */
      LinestateDcd = 0x040,
      /*! Clear To Send (read only) */
      LinestateCts = 0x020,
      /*! Data Set Ready (read only) */
      LinestateDsr = 0x100,
      /*! Data Terminal Ready (write only) */
      LinestateDtr = 0x002,
      /*! Ring Detect (read only) */
      LinestateRing = 0x080,
      /*! Request To Send (write only) */
      LinestateRts = 0x004,
      /*! no active line state, use this for clear */
      LinestateNull = 0x000
    };


    /*!
   \class SerialPort

   \brief the Windows version
    */
    class SerialPort : public SerialPort_x
    {
    protected:
     /*!
    \brief the win32 api equivalent for the Linux
    file descriptor
     */
     HANDLE fd;
     /*!
    \brief a special struct in the win32 api for controling
    an asynchronous serial communication through the com ports.
     */
     OVERLAPPED m_ov;

     /*!
    \brief The win32 API doesn't have any function to detect the
    current state of the output lines RST and DTR (if someone knows
    some function, please contact me).
    So we save the state always after changing one or both lines
    (for example, on Open, SetLineState and ChangeLineState)
     */
     int m_rtsdtr_state;

    int CloseDevice()
    {
      if (fd != INVALID_HANDLE_VALUE) {
        CloseHandle(m_ov.hEvent);
        CloseHandle(fd);
        fd = INVALID_HANDLE_VALUE;
      }
      return 0;
    };

    int OpenDevice(const wxString& devname, int baudrate, const char* protocol)
    {
      if (strlen(protocol) != 3) return -1;

      fd = CreateFile(devname.c_str(),  // device name
        GENERIC_READ | GENERIC_WRITE,   // O_RDWR
        0,                              // not shared
        NULL,                           // default value for object security ?!?
        OPEN_EXISTING,                  // file (device) exists
        FILE_FLAG_OVERLAPPED,           // asynchron handling
        NULL);                          // no more handle flags

      if(fd == INVALID_HANDLE_VALUE) {
        return -1;
      }
      // save the device name
      m_devname = devname;

      // device control block
      DCB dcb;
      memset(&dcb,0,sizeof(dcb));
      dcb.DCBlength = sizeof(dcb);
      dcb.BaudRate = baudrate;
      dcb.fBinary = 1;

      m_rtsdtr_state = LinestateNull;

      // Specifies whether the CTS (clear-to-send) signal is monitored
      // for output flow control. If this member is TRUE and CTS is turned
      // off, output is suspended until CTS is sent again.
      dcb.fOutxCtsFlow = false;

      // Specifies the DTR (data-terminal-ready) flow control.
      // This member can be one of the following values:
      // DTR_CONTROL_DISABLE   Disables the DTR line when the device is
      //                       opened and leaves it disabled.
      // DTR_CONTROL_ENABLE    Enables the DTR line when the device is
      //                       opened and leaves it on.
      // DTR_CONTROL_HANDSHAKE Enables DTR handshaking. If handshaking is
      //                       enabled, it is an error for the application
      //                       to adjust the line by using the
      //                       EscapeCommFunction function.
      dcb.fDtrControl = DTR_CONTROL_DISABLE;
      m_rtsdtr_state |= LinestateDtr;
      dcb.fRtsControl = RTS_CONTROL_DISABLE;
      m_rtsdtr_state |= LinestateRts;

      // Specifies the XON/XOFF flow control.
      // If fOutX is true (the default is false), transmission stops when the
      // XOFF character is received and starts again, when the XON character
      // is received.
      dcb.fOutX = false;
      // If fInX is true (default is false), the XOFF character is sent when
      // the input buffer comes within XoffLim bytes of being full, and the
      // XON character is sent, when the input buffer comes within XonLim
      // bytes of being empty.
      dcb.fInX = false;
      // default character for XOFF is 0x13 (hex 13)
      dcb.XoffChar = 0x13;
      // default character for XON is 0x11 (hex 11)
      dcb.XonChar = 0x11;
      // set the minimum number of bytes allowed in the input buffer before
      // the XON character is sent (3/4 of full size)
      dcb.XonLim = (SERIALPORT_BUFSIZE >> 2) * 3;
      // set the maximum number of free bytes in the input buffer, before the
      // XOFF character is sent (3/4 of full size)
      dcb.XoffLim = (SERIALPORT_BUFSIZE >> 2) * 3;

      // parity settings
      switch( protocol[1] ) {
        case 'O': dcb.Parity = ODDPARITY; break;
        case 'E': dcb.Parity = EVENPARITY; break;
        default:  dcb.Parity = NOPARITY; break;
      }

      // stopbits
      if(protocol[2] == '2')
        dcb.StopBits = TWOSTOPBITS;
      else
        dcb.StopBits = ONESTOPBIT;
      // stopbits

      // wordlen, valid values are 5,6,7,8
      dcb.ByteSize = protocol[0] - '0';

      if (!SetCommState(fd,&dcb)) return -2;

      // create event for overlapped I/O
      // we need a event object, which inform us about the
      // end of an operation (here reading device)
      m_ov.hEvent = CreateEvent(NULL, // LPSECURITY_ATTRIBUTES lpsa
          TRUE,  // BOOL fManualReset
          TRUE,  // BOOL fInitialState
          NULL); // LPTSTR lpszEventName
      if(m_ov.hEvent == INVALID_HANDLE_VALUE) {
        return -3;
      }

      /* THIS IS OBSOLETE!!!
      // event should be triggered, if there are some received data
      if(!SetCommMask(fd,EV_RXCHAR))
      return -4;
      */

      COMMTIMEOUTS cto = {MAXDWORD,0,0,0,0};
      if(!SetCommTimeouts(fd,&cto)) return -5;

      // for a better performance with win95/98 I increased the internal
      // buffer to SERIALPORT_BUFSIZE (normal size is 1024, but this can
      // be a little bit to small, if you use a higher baudrate like 115200)
      if(!SetupComm(fd,SERIALPORT_BUFSIZE,SERIALPORT_BUFSIZE)) return -6;

      return 0;
    };

  public:

    SerialPort()
    {
      memset( &m_ov, 0, sizeof( OVERLAPPED ) );
      fd = INVALID_HANDLE_VALUE;
      m_rtsdtr_state = LinestateNull;
    };

    ~SerialPort()
    {
      Close();
    };

    int IsOpen()
    {
      return (fd != INVALID_HANDLE_VALUE);
    };


    int AvailableToRead()
    {
      COMSTAT comStat;
      DWORD   dwErrors;
      // Get and clear current errors on the port.
      if (!ClearCommError(fd, &dwErrors, &comStat))
          // Report error in ClearCommError.
          return 0;
      return comStat.cbInQue;
    };

    int WaitingToWrite()
    {
      COMSTAT comStat;
      DWORD   dwErrors;
      // Get and clear current errors on the port.
      if (!ClearCommError(fd, &dwErrors, &comStat))
          // Report error in ClearCommError.
          return 0;
      return comStat.cbOutQue;
    };

    int Read(char* buf,size_t len)
    {
      DWORD read;
      if(!ReadFile(fd,buf,len,&read,&m_ov)) {
        // if we use a asynchrone reading, ReadFile always gives FALSE
        // ERROR_IO_PENDING means ok, other values show an error
        if(GetLastError() != ERROR_IO_PENDING) {
          // oops..., error in communication
          return -1;
        }
      }
      else {
        // ok, we have read all wanted bytes
        return (int)read;
      }
      return 0;
    };

    int Write(char* buf,size_t len)
    {
     DWORD write;
     if(!WriteFile(fd,buf,len,&write,&m_ov)) {
      if(GetLastError() != ERROR_IO_PENDING) {
       return -1;
      }
      else {
       // VERY IMPORTANT to flush the data out of the internal
       // buffer
       FlushFileBuffers(fd);
       // first you must call GetOverlappedResult, then you
       // get the REALLY transmitted count of bytes
       if(!GetOverlappedResult(fd,&m_ov,&write,TRUE)) {
      // ooops... something is going wrong
      return (int)write;
       }
      }
     }
     return write;
    };

  }; // class SerialPort

} // namespace ctb
