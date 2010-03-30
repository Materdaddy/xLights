/////////////////////////////////////////////////////////////////////////////
// Name:        linux/serport.cpp
// Purpose:
// Author:      Joachim Buermann
// Id:          $Id: serport.cpp,v 1.1.1.1 2004/11/24 10:30:11 jb Exp $
// Copyright:   (c) 2001 Joachim Buermann
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include "serport.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#define CMSPAR	  010000000000		/* mark or space (stick) parity */

namespace ctb {

    SerialPort::SerialPort() :
	   SerialPort_x()
    {
	   fd = -1;
    };

    SerialPort::~SerialPort()
    {
	   Close();
    };

    speed_t SerialPort::AdaptBaudrate( int baud )
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
	   case 460800: return B460800;
	   case 921600: return B921600;

		  // NOTE! The speed of 38400 is required, if you want to set
		  //       an non-standard baudrate. See below!
	   default: return B38400;
	   }
    };

    int SerialPort::CloseDevice()
    {
	   int err = 0;
	   // only close an open file handle
	   if(fd < 0) return EBADF;
	   // With some systems, it is recommended to flush the serial port's 
	   // Output before closing it, in order to avoid a possible hang of
	   // the process...
	   // Thanks to Germain (I couldn't answer you, because your email
	   // address was invalid)
	   tcflush(fd, TCOFLUSH);

	   // Don't recover the orgin settings while the device is open. This
	   // implicate a mismatched data output!
	   // Just close device
	   err = close( fd );

	   fd = -1;

	   return err;
    };

//
// included from /usr/include/linux/serial.h
//
//  struct serial_icounter_struct {
//  	int cts, dsr, rng, dcd;
//  	int rx, tx;
//  	int frame, overrun, parity, brk;
//  	int buf_overrun;
//  	int reserved[9];
//  };
//
    int SerialPort::Ioctl(int cmd, void* args)
    {
	   int count = 0;
	   int err = 0;
	   struct serial_icounter_struct info;
	   SerialPort_EINFO einfo;

	   switch(cmd) {
	   case CTB_RESET:
		  return SendBreak(0);
	   case CTB_SER_GETEINFO:
		  err = ioctl(fd,TIOCGICOUNT,&info);
		  if(err) return err;
		  einfo.brk = info.brk - save_info.brk;
		  einfo.frame = info.frame - save_info.frame;
		  einfo.overrun = info.overrun - save_info.overrun;
		  einfo.parity = info.parity - save_info.parity;
		  *(SerialPort_EINFO*)args = einfo;
		  break;
	   case CTB_SER_GETBRK:
		  err = ioctl(fd,TIOCGICOUNT,&info);
		  if(err) return err;
		  if(last_info.brk != info.brk) count = 1;
		  break;
	   case CTB_SER_GETFRM:
		  err = ioctl(fd,TIOCGICOUNT,&info);
		  if(err) return err;
		  if(last_info.frame != info.frame) count = 1;
		  break;
	   case CTB_SER_GETOVR:
		  err = ioctl(fd,TIOCGICOUNT,&info);
		  if(err) return err;
		  if(last_info.overrun != info.overrun) count = 1;
		  break;
	   case CTB_SER_GETPAR:
		  err = ioctl(fd,TIOCGICOUNT,&info);
		  if(err) return err;
		  if(last_info.parity != info.parity) count = 1;
		  break;
	   case CTB_SER_GETINQUE:
		  err = ioctl(fd,TIOCINQ,&count);
		  if(err) return err;
		  *(int*)args = count;
		  return 0;
	   default:
		  return -1;
	   }
	   last_info = info;
	   return 0;
    };

    int SerialPort::IsOpen()
    {
	   return (fd != -1);
    };

    int SerialPort::OpenDevice(const char* devname, void* dcs)
    {
	   // if dcs isn't NULL, type cast
	   if(dcs) m_dcs = *(SerialPort_DCS*)dcs;
	   // open serial comport device for reading and writing,
	   // don't wait (O_NONBLOCK)
	   fd = open(devname, O_RDWR | O_NOCTTY | O_NONBLOCK);
	   if(fd >= 0) {

		  // exclusive use
		  int dummy;

		  ioctl( fd, TIOCEXCL, &dummy );

		  tcgetattr(fd,&t);
		  save_t = t;

		  // save the device name
		  strncpy(m_devname,(char*)devname,sizeof(m_devname));
		  // we write an eos to avoid a buffer overflow
		  m_devname[sizeof(m_devname)-1] = '\0';

		  // Fill the internal terios struct.
		  // If the given baudrate is an non-standard one, the AdaptBaudrate
		  // call returns the linux specific value B38400 which is a
		  // condition for the later switch to an unusual baudrate!
		  cfsetspeed(&t, AdaptBaudrate( m_dcs.baud ) );

		  // parity settings
		  switch( m_dcs.parity ) {

		  case ParityNone:
			 t.c_cflag &= ~PARENB; break;

		  case ParityOdd:
			 t.c_cflag |= PARENB;
			 t.c_cflag |= PARODD;
			 break;

		  case ParityEven:
			 t.c_cflag |= PARENB;
			 t.c_cflag &= ~PARODD;
			 break;

		  case ParityMark:
			 t.c_cflag |= PARENB | CMSPAR | PARODD;
			 break;

		  case ParitySpace:
			 t.c_cflag |= PARENB | CMSPAR;
			 t.c_cflag &= ~PARODD;
			 break;
		  }
		  
		  // stopbits
		  if(m_dcs.stopbits == 2)
			 t.c_cflag |= CSTOPB;
		  else
			 t.c_cflag &= ~CSTOPB;
		  // wordlen
		  t.c_cflag &= ~CSIZE;
		  if(m_dcs.wordlen == 7) t.c_cflag |= CS7;
		  else if(m_dcs.wordlen == 6) t.c_cflag |= CS6;
		  else if(m_dcs.wordlen == 5) t.c_cflag |= CS5;
		  // this is the default
		  else t.c_cflag |= CS8;
		  // rts/cts
		  if(m_dcs.rtscts == false)
			 t.c_cflag &= ~CRTSCTS;
		  else
			 t.c_cflag |= CRTSCTS;

		  t.c_lflag &= ~(ICANON | ECHO | ISIG | IEXTEN);
		  t.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON | IXOFF | IXANY);
		  t.c_iflag |= IGNPAR;
		  t.c_oflag &= ~OPOST;

		  if(m_dcs.xonxoff == true) {
			 t.c_iflag |= (IXON | IXOFF);
		  }

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
		  tcsetattr(fd,TCSANOW,&t);
		  // it's careless, but in the moment we don't test
		  // the return of tcsetattr (normally there is no error)
	
		  // request the actual numbers of breaks, framing, overrun
		  // and parity errors (because Linux summing all of them during
		  // system lifetime, not only while serial port is open.
		  ioctl(fd,TIOCGICOUNT,&save_info);
		  // it's also careless, but we assume, that there was no error
		  last_info = save_info;

		  SetBaudrate( m_dcs.baud );

	   }
	   return fd;
    };

    int SerialPort::Read(char* buf,size_t len)
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

    int SerialPort::SendBreak(int duration)
    {
	   // the parameter is equal with linux
	   return tcsendbreak(fd,duration);
    };

    int SerialPort::SetBaudrate( int baudrate )
    {
	   speed_t baud = AdaptBaudrate( baudrate );
	   // setting the input baudrate
	   if(cfsetspeed(&t,baud) < 0) {
		  return -1;
	   }
	   // take over
	   m_dcs.baud = baudrate;

	   tcsetattr(fd,TCSANOW,&t);

	   return tcgetattr( fd, &t );
    }

    int SerialPort::Write(char* buf,size_t len)
    {
	   // Write() (using write() ) will return an 'error' EAGAIN as it is 
	   // set to non-blocking. This is not a true error within the 
	   // functionality of Write, and thus should be handled by the caller.
	   int n = write(fd,buf,len);
	   if((n < 0) && (errno == EAGAIN)) return 0;
	   return n;
    };

} // namespace ctb

