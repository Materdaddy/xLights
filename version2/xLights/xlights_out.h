/***************************************************************
 * Name:      xlights_out.h
 * Purpose:
    Defines a common API for LOR, D-Light, DMX, Renard, Pixelnet, and E1.31 networks
    All calls should be made to xOutput class
 *
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-05-07
 * Copyright: 2010-2012 by Matt Brown
 * License:
     This file is part of xLights.

    xLights is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    xLights is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with xLights.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************************/
#ifndef XLIGHTSOUT_H
#define XLIGHTSOUT_H


#include <wx/string.h>
#include <wx/dynarray.h>
#include <vector>


typedef std::pair<int, int> ChannelPair; // first is network #, second is channel #
typedef std::vector<ChannelPair> ChannelVector;


class xNetwork {
protected:
  long timer_msec;
  size_t num_channels;
  wxString netdesc;
  int datalen;

public:
  xNetwork();
  virtual ~xNetwork();
  void CloseSerialPort();
  virtual bool TxEmpty() = 0;
  void SetNetworkDesc(wxString& NetworkDesc);
  wxString GetNetworkDesc();
  size_t GetChannelCount();
  virtual void SetChannelCount(size_t numchannels) = 0;
  void InitSerialPort(const wxString& portname, int baudrate);
  virtual void InitNetwork(const wxString& ipaddr, wxUint16 UniverseNumber, wxUint16 NetNum);
  void TimerStart(long msec);
  long GetTimer();
  virtual void TimerEnd() = 0;
  virtual void ResetTimer();
  virtual void SetIntensity (size_t chindex, wxByte intensity) = 0;
};


// xOutput should be a singleton
// It contains references to all of the networks
class xOutput {
protected:
  WX_DEFINE_ARRAY_PTR(xNetwork*, xNetworkArray);
  xNetworkArray networks;
  ChannelVector channels;

public:
  xOutput();
  ~xOutput();
  size_t NetworkCount();
  size_t addnetwork (const wxString& NetworkType, int chcount, const wxString& portname, int baudrate);
  int GetChannelCount(size_t netnum);
  wxString GetNetworkDesc(size_t netnum);
  void SetIntensity (size_t absChNum, wxByte intensity);
  void off (size_t absChNum);
  void alloff ();
  size_t TotalChannelCount();
  size_t AbsChannel2NetNum(size_t absChNum);
  size_t AbsChannel2NetCh(size_t absChNum);
  ChannelPair AbsChannelPair(size_t absChNum);
  void ResetTimer();
  void TimerStart(long msec);
  void TimerEnd();
  void ClosePorts();
  bool TxEmpty();
};

#endif // XLIGHTSOUT_H
