// Name:        serial.h
// Author:      Matt Brown

#ifndef XLIGHTS_SERIAL_H
#define XLIGHTS_SERIAL_H

#include <wx/string.h>

class SerialPort
{
  protected:
    int CloseDevice();
    int OpenDevice( const wxString& portname, int baudrate, const char* protocol );
    wxString m_devname;
    int callback;  // used in basic script

  public:
    SerialPort();
    ~SerialPort();
    void SetCallback(int cb);
    int GetCallback();
    int AvailableToRead();
    int WaitingToWrite();
    int SendBreak();
    int Close();
    int Open( const wxString& portname, int baudrate, const char* protocol = "8N1" );
    bool IsOpen();
    int Read(char* buf,size_t len);
    int Write(char* buf,size_t len);
};

#endif // XLIGHTS_SERIAL_H
