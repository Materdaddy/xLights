/////////////////////////////////////////////////////////////////////////////
// Name:        fifo.cpp
// Purpose:
// Author:      Joachim Buermann, Michael Hungershausen (adapted for xLights by Matt Brown)
// Id:          $Id$
// Copyright:   (c) 2006,2007 Joachim Buermann
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include <sys/types.h>

namespace ctb {

/*!
  \class Fifo
  A simple thread safe fifo to realize a put back mechanism for the
  wxIOBase and it's derivated classes.
*/
    class Fifo
    {
    protected:
	   /*! the size of the fifo */
	   size_t m_size;
	   /*! the start of the internal fifo buffer */
	   char* m_begin;
	   /*!
		the end of the internal fifo buffer (m_end marks the first
		invalid byte AFTER the internal buffer)
	   */
	   char* m_end;
	   /*! the current read position */
	   char* m_rdptr;
	   /*! the current write position */
	   char* m_wrptr;

    public:
	   /*!
		\brief the constructor initialize a fifo with the given size.
		\param size size of the fifo
	   */
	   Fifo(size_t size)
		{
		   m_begin = new char[size];
		   m_end = m_begin + m_size;
		   m_rdptr = m_wrptr = m_begin;
		};

	   /*!
		\brief the destructor destroys all internal memory.
	   */
	   virtual ~Fifo()
		{
		   delete m_begin;
		};

	   /*!
		\brief clear all internal memory and set the read and write
		pointers to the start of the internal memory.
		\Note This function is not thread safe! Don't use it, if another
		thread takes access to the fifo instance. Use a looping get() or
		read() call instead of this.
	   */
	   virtual void clear()
		{
		   m_rdptr = m_wrptr = m_begin;
		};

	   /*!
		\brief fetch the next available byte from the fifo.
		\param ch points to a charater to store the result
		\return 1 if successful, 0 otherwise
	   */
	   virtual int get(char* ch)
		{
		   if(m_rdptr != m_wrptr) {
			  *ch = *m_rdptr++;
			  if(m_rdptr >= m_end) {
				 m_rdptr = m_begin;
			  }
			  return 1;
		   }
		   return 0;
		};

	   /*!
		\brief query the fifo for it's available bytes.
		\return count of readable bytes, storing in the fifo
	   */
	   size_t items()
		{
		   char* tmp_wrptr = m_wrptr;
		   // the rdptr will only changed by the reader. If we suppose, that
		   // the caller of the items() method is identical with the reader,
		   // this should be thread save.
		   char* tmp_rdptr = m_rdptr;

		   // if the write pointer is identical with the read, there are no
		   // more data in the Fifo
		   if(tmp_wrptr == tmp_rdptr) {
			  return 0;
		   }
		   // the write pointer is greater as the read pointer, so we just
		   // can calculate the difference for the remaining data
		   if(tmp_wrptr > tmp_rdptr) {
			  return (tmp_wrptr - tmp_rdptr);
		   }
		   // the write pointer has circulate and stands against the read
		   // pointer
		   else {
			  return (m_size - (tmp_rdptr - tmp_wrptr));
		   }
		};

	   /*!
		\brief put a character into the fifo.
		\param ch the character to put in
		\return 1 if successful, 0 otherwise
	   */
	   virtual int put(char ch)
		{
		   // for a thread safe operation, the write of a data byte must be
		   // atomic. So we first assign the current position of the write
		   // pointer to a temporary pointer.
		   // Increment it for the comparison with the end of the internal
		   // buffer and the read pointer
		   char* tmp_wrptr = m_wrptr + 1;
		   if(tmp_wrptr >= m_end) {
			  tmp_wrptr = m_begin;
		   }
		   if(tmp_wrptr == m_rdptr) {
			  return 0;
		   }
		   // this don't changes the write pointer!
		   *m_wrptr = ch;
		   // that's the trick! The following assignment is atomic and cannot
		   // interrupted within a read access by the read thread
		   m_wrptr = tmp_wrptr;
		   return 1;
		};

	   /*!
		\brief read a given count of bytes out of the fifo.
		\param data memory to store the readed data
		\param n number of bytes to read
		\return On success, the number of bytes read are returned,
		0 otherwise
	   */
	   virtual int read(char* data, int n)
		{
		   int nresult = 0;
		   while(n--) {
			  // the same as get()
			  if(m_rdptr != m_wrptr) {
				 *data = *m_rdptr++;
				 if(m_rdptr >= m_end) {
					m_rdptr = m_begin;
				 }
			  }
			  else {
				 break;
			  }
			  nresult++;
			  data++;
		   }
		   return nresult;
		};

	   /*!
		\brief write a given count of bytes into the fifo.
		\param data start of the data to write
		\param n number of bytes to write
		\return On success, the number of bytes written are returned,
		0 otherwise
	   */
	   virtual int write(char* data, int n)
		{
		   int nresult = 0;
		   while(n--) {
			  // the same as put()
			  char* tmp_wrptr = m_wrptr + 1;
			  if(tmp_wrptr >= m_end) {
				 tmp_wrptr = m_begin;
			  }
			  if(tmp_wrptr == m_rdptr) {
				 break;
			  }
			  *m_wrptr = *data++;
			  m_wrptr = tmp_wrptr;
			  nresult++;
		   }
		   return nresult;
		};

    };


} // namespace ctb
