/////////////////////////////////////////////////////////////////////////////
// Name:        ser_posix.cpp
// Purpose:
// Author:      Joachim Buermann (adapted for xLights by Matt Brown)
// Id:          $Id: serport.cpp,v 1.1.1.1 2004/11/24 10:30:11 jb Exp $
// Copyright:   (c) 2001 Joachim Buermann
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>


namespace ctb {

/*!
  \class SerialPort

  \brief the linux and OS/X version
*/
class SerialPort : public SerialPort_x
{
  protected:
     /*!
    \brief under Linux, the serial ports are normal file descriptor
     */
     int fd;
     /*!
    \brief Linux defines this struct termios for controling asynchronous
    communication.
     */
     struct termios t;

     /*!
    \brief adaptor member function, to convert the plattform independent
    type wxBaud into a linux conform value.
    \param baud the baudrate as wxBaud type
    \return speed_t linux specific data type, defined in termios.h
     */
    speed_t AdaptBaudrate( int baud )
    {
       switch(baud) {
       case 150: return B150;
       case 300: return B300;
       case 600: return B600;
       case 1200: return B1200;
       case 2400: return B2400;
       case 4800: return B4800;
       case 9600: return B9600;
       case 19200: return B19200;
       case 57600: return B57600;
       case 115200: return B115200;
       case 230400: return B230400;
       default: return B38400;
       }
    };

    int CloseDevice()
    {
       int err = 0;
       // only close an open file handle
       if(fd < 0) return EBADF;
       // With some systems, it is recommended to flush the serial port's
       // Output before closing it, in order to avoid a possible hang of
       // the process...
       tcflush(fd, TCOFLUSH);

       // Don't recover the orgin settings while the device is open. This
       // implicate a mismatched data output!
       // Just close device
       err = close( fd );

       fd = -1;

       return err;
    };

    int OpenDevice(const wxString& devname, int baudrate, const char* protocol)
    {
       if (strlen(protocol) != 3) return -1;

#ifdef __WXWINDOWS__
       fd = open(devname.fn_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
#else
       // for unit test (not a wxWidgets app)
       fd = open(devname.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
#endif
       if(fd < 0) return fd;

        // exclusive use
        if ( ioctl( fd, TIOCEXCL ) == -1 ) return -1;

        tcgetattr(fd,&t);

        // save the device name
        m_devname = devname;

        // Fill the internal termios struct.
        cfsetspeed(&t, AdaptBaudrate( baudrate ) );

        // parity settings
        switch( protocol[1] ) {
          case 'N':
            t.c_cflag &= ~PARENB; break;
          case 'O':
            t.c_cflag |= PARENB;
            t.c_cflag |= PARODD;
            break;
          case 'E':
            t.c_cflag |= PARENB;
            t.c_cflag &= ~PARODD;
            break;
        }

        // stopbits
        if(protocol[2] == '2')
          t.c_cflag |= CSTOPB;
        else
          t.c_cflag &= ~CSTOPB;

        // wordlen
        t.c_cflag &= ~CSIZE;
        switch( protocol[0] ) {
          case '5': t.c_cflag |= CS5; break;
          case '6': t.c_cflag |= CS6; break;
          case '7': t.c_cflag |= CS7; break;
          default:  t.c_cflag |= CS8; break;
        }

        // this may overwrite the number of bits to 8
        cfmakeraw(&t);

        // look out!
        // MIN = 1 means, in TIME (1/10 secs) defined timeout
        // will be started AFTER receiving the first byte
        // so we must set MIN = 0. (timeout starts immediately, abort
        // also without readed byte)
        t.c_cc[VMIN] = 0;
        // timeout in 1/10 secs
        // no timeout for non blocked transfer
        t.c_cc[VTIME] = 0;
        // write the settings
        if (tcsetattr(fd,TCSANOW,&t) == -1) return -1;

       return fd;
    };

  public:

    SerialPort()
    {
       fd = -1;
    };

    ~SerialPort()
    {
       Close();
    };

    int IsOpen()
    {
       return (fd != -1);
    };

    int Read(char* buf,size_t len)
    {
       if(m_fifo->items() > 0) {
        return m_fifo->read(buf,len);
       }
       // Read() (using read() ) will return an 'error' EAGAIN as it is
       // set to non-blocking. This is not a true error within the
       // functionality of Read, and thus should be handled by the caller.
       int n = read(fd,buf,len);
       if((n < 0) && (errno == EAGAIN)) return 0;
       return n;
    };

    int Write(char* buf,size_t len)
    {
       // Write() (using write() ) will return an 'error' EAGAIN as it is
       // set to non-blocking. This is not a true error within the
       // functionality of Write, and thus should be handled by the caller.
       int n = write(fd,buf,len);
       if((n < 0) && (errno == EAGAIN)) return 0;
       return n;
    };

  }; // class SerialPort

} // namespace ctb

