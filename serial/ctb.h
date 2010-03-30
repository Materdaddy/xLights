#ifndef LIBCTB_CTB_H_INCLUDED_
#define LIBCTB_CTB_H_INCLUDED_

#include "fifo.h"
#include "serport.h"
#include "serportx.h"

/*!
  \mainpage ctb overview

  The ctb (communication toolbox) library was realized, to simplify the
  communication with other instruments throughout the serial com ports
  (at first). To make my life easier, it should works with Linux and
  all win32 plattforms (excepted windows 3.1, which is a only 16bit OS)
  because I develope my applications for both plattforms).\n
  The main goal of the library was a non-blocked communication to avoid
  frozen GUIs waiting for data which in some conditions never arrives.
  
    ctb is composed of 2 parts:

  - ctb::SerialPort class
  - ctb::Fifo class

  \section SerialPort SerialPort class

  The class for the serial ports is named as
  ctb::SerialPort. SerialPort is a wrapper for non blocked reading and
  writing. This is easy under linux, but with windows a lot more
  tricky. SerialPort is as simple as possible. It doesn't create any
  gui events or signals, so it works also standalone. It's also not a
  device driver, means, you must call the read method, if you look for
  receiving data.

  You can write any desired data with any length (length type is
  size_t, I think, on win32 and linux this is a 32Bit integer) and
  SerialPort returns the really writen data length, also you can read
  a lot of data and SerialPort returns the really received data count.

  Both, read and write returns immediatelly. Using these, the program
  never blocks.

  \section Fifo Fifo cass
  Provides a simple thread safe fifo to realize a fast and simple
  communication pipe between two threads (and was used also as a put
  back mechanism for the wxIOBase and it's derivated classes).\n
  ctb::Fifo tackles the concurrently access from different threads with an
  internal temporary pointer asignment which was atomic. From there no
  mutex or semaphore is involved and lead to a fast access.

  Please note:\n
  The thread safeness is limited to the put/get write/read methods but
  which should be sufficent for a fifo.


  \latexonly \newpage \endlatexonly

 */

#endif
