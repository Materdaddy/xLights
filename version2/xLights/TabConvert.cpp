/*
 * ********************************************
 * ********************************************
 * Process Convert Panel Events
 * ********************************************
 * ********************************************
 */


void xLightsFrame::ConversionError(const wxString& msg)
{
    wxMessageBox(msg, _("Error"), wxOK | wxICON_EXCLAMATION);
}

/*
   base64.cpp and base64.h

   Copyright (C) 2004-2008 Ren� Nyffenegger

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   Ren� Nyffenegger rene.nyffenegger@adp-gmbh.ch

*/

static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

wxString xLightsFrame::base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  wxString ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }
  return ret;
}


std::string xLightsFrame::base64_decode(const wxString& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }
  return ret;
}


void xLightsFrame::OnButtonChooseFileClick(wxCommandEvent& event)
{
    wxArrayString ShortNames;
    wxString AllNames;
    if (FileDialogConvert->ShowModal() == wxID_OK) {
        FileDialogConvert->GetPaths(FileNames);
        FileDialogConvert->GetFilenames(ShortNames);
        for (size_t i=0; i < ShortNames.GetCount(); i++) {
            AllNames.Append(ShortNames[i]);
            AllNames.Append(wxT("\n"));
        }
        TextCtrlFilename->ChangeValue( AllNames );
        wxString ConvertDir = FileDialogConvert->GetDirectory();
        wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));
        config->Write(_("ConvertDir"), ConvertDir);
        delete config;
    }
}

void xLightsFrame::WriteVixenFile(const wxString& filename)
{
    wxString ChannelName;
    int32_t ChannelColor;
    long TotalTime=SeqNumPeriods * 50;
    TextCtrlConversionStatus->AppendText(_("Writing Vixen sequence\n"));
    wxXmlNode *node,*chparent,*textnode;
    wxXmlDocument doc;
    wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("Program") );
    doc.SetRoot( root );

    // add nodes to root in reverse order

    node = new wxXmlNode( root, wxXML_ELEMENT_NODE, wxT("EventValues") );
    textnode = new wxXmlNode( node, wxXML_TEXT_NODE, wxEmptyString, base64_encode(SeqData, SeqDataLen) );

    node = new wxXmlNode( root, wxXML_ELEMENT_NODE, wxT("Audio") );
    node->AddAttribute( wxT("filename"), mediaFilename);
    node->AddAttribute( wxT("duration"), wxString::Format(wxT("%ld"),TotalTime));
    textnode = new wxXmlNode( node, wxXML_TEXT_NODE, wxEmptyString, wxT("Music") );

    chparent = new wxXmlNode( root, wxXML_ELEMENT_NODE, wxT("Channels") );
    for (int ch=0; ch < SeqNumChannels; ch++ ) {
        node = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("Channel") );
        node->AddAttribute( wxT("output"), wxString::Format(wxT("%d"),ch));
        node->AddAttribute( wxT("id"), wxT("0"));
        node->AddAttribute( wxT("enabled"), wxT("True"));
        chparent->AddChild( node );
        if (ch < ChannelNames.size() && !ChannelNames[ch].IsEmpty()) {
            ChannelName = ChannelNames[ch];
        } else {
            ChannelName = wxString::Format(wxT("Channel %d"),ch+1);
        }
        // LOR is BGR with high bits=0
        // Vix is RGB with high bits=1
        if (ch < ChannelColors.size() && ChannelColors[ch] > 0) {
            ChannelColor = 0xff000000 | (ChannelColors[ch] >> 16 & 0x0000ff) | (ChannelColors[ch] & 0x00ff00) | (ChannelColors[ch] << 16 & 0xff0000);
        } else {
            // default to white
            ChannelColor = -1;
        }
        node->AddAttribute( wxT("color"), wxString::Format(wxT("%d"),ChannelColor));
        textnode = new wxXmlNode( node, wxXML_TEXT_NODE, wxEmptyString, ChannelName );
    }

    node = new wxXmlNode( root, wxXML_ELEMENT_NODE, wxT("AudioDevice") );
    textnode = new wxXmlNode( node, wxXML_TEXT_NODE, wxEmptyString, wxT("-1") );

    node = new wxXmlNode( root, wxXML_ELEMENT_NODE, wxT("MaximumLevel") );
    textnode = new wxXmlNode( node, wxXML_TEXT_NODE, wxEmptyString, wxT("255") );

    node = new wxXmlNode( root, wxXML_ELEMENT_NODE, wxT("MinimumLevel") );
    textnode = new wxXmlNode( node, wxXML_TEXT_NODE, wxEmptyString, wxT("0") );

    node = new wxXmlNode( root, wxXML_ELEMENT_NODE, wxT("EventPeriodInMilliseconds") );
    textnode = new wxXmlNode( node, wxXML_TEXT_NODE, wxEmptyString, wxT("50") );

    node = new wxXmlNode( root, wxXML_ELEMENT_NODE, wxT("Time") );
    textnode = new wxXmlNode( node, wxXML_TEXT_NODE, wxEmptyString, wxString::Format(wxT("%ld"),TotalTime) );

    if (doc.Save( filename )) {
        TextCtrlConversionStatus->AppendText(_("Finished writing new file: ")+filename+_("\n"));
    } else {
        ConversionError(_("Unable to save Vixen file"));
    }
}

void xLightsFrame::WriteXLightsFile(const wxString& filename)
{
    wxFile f;
    char hdr[512];
    memset(hdr,0,512);
    if (!f.Create(filename,true)) {
        ConversionError(_("Unable to create file: ")+filename);
        return;
    }
    if (mediaFilename.size() > 470) {
        ConversionError(_("Media file name is too long"));
        return;
    }
    int xseq_format_version = 1;
    sprintf(hdr,"xLights %2d %8ld %8ld",xseq_format_version,SeqNumChannels,SeqNumPeriods);
    strncpy(&hdr[32],mediaFilename.c_str(),470);
    f.Write(hdr,512);
    f.Write(SeqData,SeqDataLen);
    f.Close();
}

void xLightsFrame::WriteConductorFile(const wxString& filename)
{
    TextCtrlConversionStatus->AppendText(_("Writing Lynx Conductor sequence\n"));
    wxFile f;
    wxUint8 buf[16384];
    size_t ch,i,j;
    if (!f.Create(filename,true)) {
        ConversionError(_("Unable to create file: ")+filename);
        return;
    }
    for (long period=0; period < SeqNumPeriods; period++) {
        //if (period % 500 == 499) TextCtrlConversionStatus->AppendText(wxString::Format(wxT("Writing time period %ld\n"),period+1));
        wxYield();
        for (i=0; i < 4096; i++) {
            for (j=0; j < 4; j++) {
                ch=j * 4096 + i;
                buf[i*4+j] = ch < SeqNumChannels ? SeqData[ch * SeqNumPeriods + period] : 0;
            }
        }
        f.Write(buf,16384);
    }

    // pad the end of the file with 512 bytes of 0's
    memset(buf,0,512);
    f.Write(buf,512);
    f.Close();
    TextCtrlConversionStatus->AppendText(_("Finished writing new file: ")+filename+_("\n"));
}

// return true on success
bool xLightsFrame::LoadVixenProfile(const wxString& ProfileName, wxArrayInt& VixChannels)
{
    wxString tag,tempstr;
    long OutputChannel;
    wxFileName fn;
    fn.AssignDir(CurrentDir);
    fn.SetFullName(ProfileName + wxT(".pro"));
    if (!fn.FileExists()) {
        ConversionError(_("Unable to find Vixen profile: ")+ProfileName+_("\n\nMake sure a copy is in your xLights directory"));
        return false;
    }
    wxXmlDocument doc( fn.GetFullPath() );
    if (doc.IsOk()) {
        VixChannels.Clear();
        wxXmlNode* root=doc.GetRoot();
        for( wxXmlNode* e=root->GetChildren(); e!=NULL; e=e->GetNext() ) {
            tag = e->GetName();
            if (tag == _("ChannelObjects")) {
                for( wxXmlNode* p=e->GetChildren(); p!=NULL; p=p->GetNext() ) {
                    if (p->GetName() == _("Channel")) {
                        if (p->HasAttribute(wxT("output"))) {
                            tempstr=p->GetAttribute(wxT("output"), wxT("0"));
                            tempstr.ToLong(&OutputChannel);
                            VixChannels.Add(OutputChannel);
                        }
                    }
                }
            }
        }
        return true;
    } else {
        ConversionError(_("Unable to load Vixen profile: ")+ProfileName);
    }
    return false;
}

void xLightsFrame::SetMediaFilename(const wxString& filename)
{
    mediaFilename=filename;
    if (mediaFilename.IsEmpty()) return;
    wxPathFormat PathFmt = mediaFilename.Contains(_("\\")) ? wxPATH_DOS : wxPATH_NATIVE;
    wxFileName fn1(mediaFilename, PathFmt);
    if (!fn1.FileExists()) {
        wxFileName fn2(CurrentDir,fn1.GetFullName());
        mediaFilename=fn2.GetFullPath();
    }
}

void xLightsFrame::ReadConductorFile(const wxString& FileName)
{
    wxFile f;
    int i,j,ch;
    char row[16384];
    int period=0;
    ConversionInit();
    wxFileDialog mediaDialog(this,_("Select associated media file, or cancel if this is an animation"));
    if (mediaDialog.ShowModal() == wxID_OK) {
        SetMediaFilename(mediaDialog.GetPath());
    }
    if (f.Open(FileName.c_str())) {
        SeqNumPeriods=f.Length()/16384;
        SeqDataLen=SeqNumPeriods * SeqNumChannels;
        SeqData = new wxUint8[SeqDataLen];
        while (f.Read(row,16384) == 16384) {
            wxYield();
            for (i=0; i < 4096; i++) {
                for (j=0; j < 4; j++) {
                    ch=j * 4096 + i;
                    if (ch < SeqNumChannels) {
                        SeqData[ch * SeqNumPeriods + period] = row[i*4+j];
                    }
                }
            }
            period++;
        }
        f.Close();
    } else {
        PlayerError(_("Unable to load sequence:\n")+FileName);
    }
}

void xLightsFrame::ReadXlightsFile(const wxString& FileName)
{
    wxFile f;
    char hdr[512],filetype[10];
    int fileversion,numch,numper,scancnt;
    size_t readcnt;
    xlightsFilename=FileName;
    ConversionInit();
    if (f.Open(FileName.c_str())) {
        f.Read(hdr,512);
        scancnt=sscanf(hdr,"%8s %2d %8d %8d",filetype,&fileversion,&numch,&numper);
        if (scancnt != 4 || strncmp(filetype,"xLights",7) != 0 || numch <= 0 || numper <= 0) {
            PlayerError(_("Invalid file header:\n")+FileName);
        } else {
            SeqNumPeriods=numper;
            SeqNumChannels=numch;
            SeqDataLen=SeqNumPeriods * SeqNumChannels;
            wxString filename=wxString::FromAscii(hdr+32);
            SetMediaFilename(filename);
            SeqData = new wxUint8[SeqDataLen];
            readcnt = f.Read(SeqData,SeqDataLen);
            if (readcnt < SeqDataLen) {
                PlayerError(_("Unable to read all event data from:\n")+FileName);
            }
#ifndef NDEBUG
            TextCtrlLog->AppendText(wxString::Format(_("ReadXlightsFile SeqNumPeriods=%ld SeqNumChannels=%ld\n"),SeqNumPeriods,SeqNumChannels));
#endif
        }
        f.Close();
    } else {
        PlayerError(_("Unable to load sequence:\n")+FileName);
    }
}

void xLightsFrame::ConversionInit()
{
    long TotChannels=NetInfo.GetTotChannels();
    mediaFilename.clear();
    ChannelNames.Clear();
    ChannelNames.Add(wxEmptyString, TotChannels);
    ChannelColors.Clear();
    ChannelColors.Add(0, TotChannels);
    delete SeqData;
    SeqData = 0;
    SeqNumChannels=TotChannels;
    SeqNumPeriods=0;
}

void xLightsFrame::ReadVixFile(const char* filename)
{
    wxString NodeName,NodeValue,msg;
    std::string VixSeqData;
    wxArrayInt VixChannels;
    long cnt = 0;
    wxArrayString context;
    long VixEventPeriod=-1;
    long MaxIntensity = 255;
    int OutputChannel;

    ConversionInit();
    TextCtrlConversionStatus->AppendText(_("Reading Vixen sequence\n"));
    IrrXMLReader* xml = createIrrXMLReader(filename);

  // parse the file until end reached
  while(xml && xml->read())
  {
    switch(xml->getNodeType())
    {
    case EXN_TEXT:
      // in this xml file, the only text which occurs is the messageText
      //messageText = xml->getNodeData();
      if (cnt == 2) {
                NodeValue = wxString::FromAscii( xml->getNodeData() );
                if (context[1] == _("MaximumLevel")) NodeValue.ToLong(&MaxIntensity);
                if (context[1] == _("EventPeriodInMilliseconds")) NodeValue.ToLong(&VixEventPeriod);
                if (context[1] == _("EventValues")) VixSeqData=base64_decode(NodeValue);
                if (context[1] == _("Profile")) LoadVixenProfile(NodeValue,VixChannels);
      }
      break;
    case EXN_ELEMENT:
      NodeName = wxString::FromAscii( xml->getNodeName() );
      context.Add(NodeName);
      cnt++;
      //msg=_("Element: ") + NodeName + wxString::Format(_(" (%ld)\n"),cnt);
      //TextCtrlConversionStatus->AppendText(msg);
      if (cnt == 2 && (NodeName == _("Audio") || NodeName == _("Song"))) {
          mediaFilename = wxString::FromAscii( xml->getAttributeValueSafe("filename") );
      }
      if (cnt > 1 && context[1] == _("Channels") && NodeName == _("Channel")) {
          OutputChannel = xml->getAttributeValueAsInt("output");
          VixChannels.Add(OutputChannel);
      }
      if (xml->isEmptyElement()) {
          context.RemoveAt(cnt-1);
          cnt--;
      }
      break;
    case EXN_ELEMENT_END:
      NodeName = wxString::FromAscii( xml->getNodeName() );
      if (cnt > 0) context.RemoveAt(cnt-1);
      cnt = context.GetCount();
      break;
    default: break;
    }
  }
  delete xml;
  long VixDataLen = VixSeqData.size();
  SeqNumChannels = VixChannels.GetCount();
    TextCtrlConversionStatus->AppendText(wxString::Format(_("Max Intensity=%ld\n"),MaxIntensity));
    TextCtrlConversionStatus->AppendText(wxString::Format(_("# of Channels=%ld\n"),SeqNumChannels));
    TextCtrlConversionStatus->AppendText(wxString::Format(_("Vix Event Period=%ld\n"),VixEventPeriod));
    TextCtrlConversionStatus->AppendText(wxString::Format(_("Vix data len=%ld\n"),VixDataLen));
    if (SeqNumChannels == 0) return;
    long VixNumPeriods = VixDataLen / SeqNumChannels;
    TextCtrlConversionStatus->AppendText(wxString::Format(_("Vix # of time periods=%ld\n"),VixNumPeriods));
    TextCtrlConversionStatus->AppendText(_("Media file=")+mediaFilename+_("\n"));
    SeqNumPeriods = VixNumPeriods * VixEventPeriod / XTIMER_INTERVAL;
    SeqDataLen = SeqNumPeriods * SeqNumChannels;
    TextCtrlConversionStatus->AppendText(wxString::Format(_("New # of time periods=%ld\n"),SeqNumPeriods));
    TextCtrlConversionStatus->AppendText(wxString::Format(_("New data len=%ld\n"),SeqDataLen));
    if (SeqDataLen == 0) return;
    SeqData = new wxUint8[SeqDataLen];

    // convert to 50ms timing, reorder channels according to output number, scale so that max intensity is 255
    int newper,vixper,intensity;
    size_t ch;
    for (ch=0; ch < SeqNumChannels; ch++) {
        OutputChannel = VixChannels[ch];
        for (newper=0; newper < SeqNumPeriods; newper++) {
            vixper=newper * VixNumPeriods / SeqNumPeriods;
            intensity=VixSeqData[ch*VixNumPeriods+vixper];
            if (MaxIntensity != 255) intensity=intensity * 255 / MaxIntensity;
            SeqData[OutputChannel*SeqNumPeriods+newper] = intensity;
        }
    }
}

// returns length of first track in centiseconds
int xLightsFrame::GetLorTrack1Length(const char* filename)
{
    int centisec = -1;
    int nodecnt=0;
    wxString NodeName;
    IrrXMLReader* xml = createIrrXMLReader(filename);

    // parse the file until end reached
    while(xml && xml->read() && centisec < 0)
    {
      switch(xml->getNodeType())
      {
          case EXN_TEXT:
              break;
          case EXN_ELEMENT:
              NodeName = wxString::FromAscii( xml->getNodeName() );
              nodecnt++;
              if (nodecnt > 1000) {
                nodecnt=0;
                wxYield();
              }
              if (NodeName == _("track")) {
                  centisec = xml->getAttributeValueAsInt("totalCentiseconds");
              }
              break;
          default: break;
      }
    }
    delete xml;
    TextCtrlConversionStatus->AppendText(wxString::Format(_("Track 1 length = %d centiseconds\n"),centisec));
    return centisec;
}

void xLightsFrame::ReadLorFile(const char* filename)
{
    wxString NodeName,msg,EffectType,ChannelName,deviceType;
    wxArrayString context;
    int unit,circuit,startcsec,endcsec,intensity,startIntensity,endIntensity,rampdiff,ChannelColor;
    int i,startper,endper,perdiff,twinklestate,nexttwinkle;
    int twinkleperiod = 400;
    int curchannel = -1;
    int MappedChannelCnt = 0;
    int MaxIntensity = 100;
    int EffectCnt = 0;
    size_t network,chindex;
    long cnt = 0;

    ConversionInit();
    TextCtrlConversionStatus->AppendText(_("Reading LOR sequence\n"));
    int centisec = GetLorTrack1Length(filename);
    if (centisec > 0) {
        SeqNumPeriods = centisec * 10 / XTIMER_INTERVAL;
        if (SeqNumPeriods == 0) SeqNumPeriods=1;
        SeqDataLen = SeqNumPeriods * SeqNumChannels;
        SeqData = new wxUint8[SeqDataLen];
        memset(SeqData,0,SeqDataLen);
    } else {
        ConversionError(_("Unable to determine the length of this LOR sequence (looked for length of track 1)"));
        return;
    }
    IrrXMLReader* xml = createIrrXMLReader(filename);

    // parse the file until end reached
    while(xml && xml->read())
    {
      switch(xml->getNodeType())
      {
          case EXN_TEXT:
            break;
          case EXN_ELEMENT:
            NodeName = wxString::FromAscii( xml->getNodeName() );
            context.Add(NodeName);
            cnt++;
            //msg=_("Element: ") + NodeName + wxString::Format(_(" (%ld)\n"),cnt);
            //TextCtrlConversionStatus->AppendText(msg);
            if (NodeName == _("sequence")) {
                mediaFilename = wxString::FromAscii( xml->getAttributeValueSafe("musicFilename") );
            }
            if (cnt > 1 && context[1] == _("channels") && NodeName == _("channel") && !xml->isEmptyElement()) {
                wxYield();
                deviceType = wxString::FromAscii( xml->getAttributeValueSafe("deviceType") );
                network = xml->getAttributeValueAsInt("network");
                unit = xml->getAttributeValueAsInt("unit");
                if (unit < 0) unit+=256;
                circuit = xml->getAttributeValueAsInt("circuit");
                if (deviceType.Left(3) == wxT("DMX")) {
                    chindex=circuit-1;
                    network--;
                } else {
                    chindex=(unit-1)*16+circuit-1;
                }
                ChannelName = wxString::FromAscii( xml->getAttributeValueSafe("name") );
                curchannel = NetInfo.CalcAbsChannel(network,chindex);
                if (curchannel >= 0) {
                    //TextCtrlConversionStatus->AppendText(wxString::Format(_("curchannel %d\n"),curchannel));
                    if (!ChannelNames[curchannel].IsEmpty()) {
                        TextCtrlConversionStatus->AppendText(_("WARNING: ")+ChannelNames[curchannel]+_(" and ")+ChannelName+_(" map to the same channel\n"));
                    }
                    MappedChannelCnt++;
                    ChannelNames[curchannel] = ChannelName;
                    ChannelColor = xml->getAttributeValueAsInt("color");
                    ChannelColors[curchannel] = ChannelColor;
                } else {
                    TextCtrlConversionStatus->AppendText(_("WARNING: channel '")+ChannelName+_("' is unmapped\n"));
                }
            }
            if (cnt > 1 && context[1] == _("channels") && NodeName == _("effect") && curchannel >= 0 && SeqData) {
                EffectCnt++;
                startcsec = xml->getAttributeValueAsInt("startCentisecond");
                endcsec = xml->getAttributeValueAsInt("endCentisecond");
                intensity = xml->getAttributeValueAsInt("intensity");
                startIntensity = xml->getAttributeValueAsInt("startIntensity");
                endIntensity = xml->getAttributeValueAsInt("endIntensity");
                startper = startcsec * 10 / XTIMER_INTERVAL;
                endper = endcsec * 10 / XTIMER_INTERVAL;
                perdiff=endper - startper;  // # of 50ms ticks
                if (perdiff > 0) {
                    intensity=intensity * 255 / MaxIntensity;
                    startIntensity=startIntensity * 255 / MaxIntensity;
                    endIntensity=endIntensity * 255 / MaxIntensity;
                    EffectType = wxString::FromAscii( xml->getAttributeValueSafe("type") );
                    if (EffectType == wxT("intensity")) {
                        if (intensity > 0) {
                            for (i=0; i < perdiff; i++) {
                                SeqData[curchannel*SeqNumPeriods+startper+i] = intensity;
                            }
                        } else if (startIntensity > 0 || endIntensity > 0) {
                            // ramp
                            rampdiff=endIntensity - startIntensity;
                            for (i=0; i < perdiff; i++) {
                                intensity=(int)((double)(i) / perdiff * rampdiff + startIntensity);
                                SeqData[curchannel*SeqNumPeriods+startper+i] = intensity;
                            }
                        }
                    } else if (EffectType == wxT("twinkle")) {
                        if (intensity == 0 && startIntensity == 0 && endIntensity == 0) intensity=MaxIntensity;
                        twinklestate=static_cast<int>(rand01()*2.0) & 0x01;
                        nexttwinkle=static_cast<int>(rand01()*twinkleperiod+100) / XTIMER_INTERVAL;
                        if (intensity > 0) {
                            for (i=0; i < perdiff; i++) {
                                SeqData[curchannel*SeqNumPeriods+startper+i] = intensity * twinklestate;
                                nexttwinkle--;
                                if (nexttwinkle <= 0) {
                                    twinklestate=1-twinklestate;
                                    nexttwinkle=static_cast<int>(rand01()*twinkleperiod+100) / XTIMER_INTERVAL;
                                }
                            }
                        } else if (startIntensity > 0 || endIntensity > 0) {
                            // ramp
                            rampdiff=endIntensity - startIntensity;
                            for (i=0; i < perdiff; i++) {
                                intensity=(int)((double)(i) / perdiff * rampdiff + startIntensity);
                                SeqData[curchannel*SeqNumPeriods+startper+i] = intensity * twinklestate;
                                nexttwinkle--;
                                if (nexttwinkle <= 0) {
                                    twinklestate=1-twinklestate;
                                    nexttwinkle=static_cast<int>(rand01()*twinkleperiod+100) / XTIMER_INTERVAL;
                                }
                            }
                        }
                    } else if (EffectType == wxT("shimmer")) {
                        if (intensity == 0 && startIntensity == 0 && endIntensity == 0) intensity=MaxIntensity;
                        if (intensity > 0) {
                            for (i=0; i < perdiff; i++) {
                                twinklestate=(startper + i) & 0x01;
                                SeqData[curchannel*SeqNumPeriods+startper+i] = intensity * twinklestate;
                            }
                        } else if (startIntensity > 0 || endIntensity > 0) {
                            // ramp
                            rampdiff=endIntensity - startIntensity;
                            for (i=0; i < perdiff; i++) {
                                twinklestate=(startper + i) & 0x01;
                                intensity=(int)((double)(i) / perdiff * rampdiff + startIntensity);
                                SeqData[curchannel*SeqNumPeriods+startper+i] = intensity * twinklestate;
                            }
                        }
                    }
                }
            }
            if (xml->isEmptyElement()) {
                context.RemoveAt(cnt-1);
                cnt--;
            }
      break;
    case EXN_ELEMENT_END:
            NodeName = wxString::FromAscii( xml->getNodeName() );
            if (NodeName == _("channel")) curchannel = -1;
            if (cnt > 0) context.RemoveAt(cnt-1);
            cnt = context.GetCount();
      break;
        default: break;
    }
  }
  delete xml;
    TextCtrlConversionStatus->AppendText(wxString::Format(_("# of mapped channels with effects=%d\n"),MappedChannelCnt));
    TextCtrlConversionStatus->AppendText(wxString::Format(_("# of effects=%d\n"),EffectCnt));
    TextCtrlConversionStatus->AppendText(_("Media file=")+mediaFilename+_("\n"));
    TextCtrlConversionStatus->AppendText(wxString::Format(_("New # of time periods=%ld\n"),SeqNumPeriods));
    TextCtrlConversionStatus->AppendText(wxString::Format(_("New data len=%ld\n"),SeqDataLen));
}

void xLightsFrame::ClearLastPeriod()
{
    long LastPer = SeqNumPeriods-1;
    for (size_t ch=0; ch < SeqNumChannels; ch++) {
        SeqData[ch*SeqNumPeriods+LastPer] = 0;
    }
}

void xLightsFrame::DoConversion(const wxString& Filename, const wxString& OutputFormat)
{
    char c;
    wxString fullpath;
#if wxCHECK_VERSION(2,9,1)
    OutputFormat[0].GetAsChar(&c);
#else
    c=OutputFormat[0];
#endif

    // read sequence file
    TextCtrlConversionStatus->AppendText(_("\nReading: ") + Filename + wxT("\n"));
    wxYield();
    wxFileName oName(Filename);
    wxString ext = oName.GetExt();
    if (ext == _("vix")) {
        if (c == 'V') {
            ConversionError(_("Cannot convert from Vixen to Vixen!"));
            return;
        }
        ReadVixFile(Filename.char_str());
    } else if (ext == _(XLIGHTS_SEQUENCE_EXT)) {
        if (c == 'x') {
            ConversionError(_("Cannot convert from xLights to xLights!"));
            return;
        }
        ReadXlightsFile(Filename);
    } else if (ext == _("seq")) {
        if (c == 'L') {
            ConversionError(_("Cannot convert from Conductor file to Conductor file!"));
            return;
        }
        ReadConductorFile(Filename);
    } else if (ext == _("lms") || ext == _("las")) {
        ReadLorFile(Filename.char_str());
    } else {
        ConversionError(_("Unknown sequence file extension"));
        return;
    }

    // check for errors
    if (SeqNumChannels == 0) {
        TextCtrlConversionStatus->AppendText(_("ERROR: no channels defined\n"));
        return;
    }
    if (!SeqData || SeqDataLen == 0) {
        TextCtrlConversionStatus->AppendText(_("ERROR: sequence length is 0\n"));
        return;
    }

    if (CheckBoxOffAtEnd->IsChecked()) {
        ClearLastPeriod();
    }
    wxYield();

    // write converted file to xLights directory
    oName.SetPath( CurrentDir );

    switch (c)
    {
        case 'x':
            oName.SetExt(_(XLIGHTS_SEQUENCE_EXT));
            fullpath=oName.GetFullPath();
            TextCtrlConversionStatus->AppendText(_("Writing xLights sequence\n"));
            WriteXLightsFile(fullpath);
            TextCtrlConversionStatus->AppendText(_("Finished writing new file: ")+fullpath+_("\n"));
            break;
        case 'L':
            oName.SetExt(_("seq"));
            WriteConductorFile(oName.GetFullPath());
            break;
        case 'V':
            oName.SetExt(_("vix"));
            WriteVixenFile(oName.GetFullPath());
            break;
        default:
            TextCtrlConversionStatus->AppendText(_("Nothing to write - invalid output format\n"));
            break;
    }
}


void xLightsFrame::OnButtonStartConversionClick(wxCommandEvent& event)
{
    ButtonStartConversion->Enable(false);
    wxString OutputFormat = ChoiceOutputFormat->GetStringSelection();
    TextCtrlConversionStatus->Clear();

    // check user inputs
    if (FileNames.IsEmpty()) {
        wxMessageBox(_("Please select one or more sequence files"), _("Error"));
    } else if (OutputFormat.IsEmpty()) {
        wxMessageBox(_("Please select an output format"), _("Error"));
    } else {
        for (size_t i=0; i < FileNames.GetCount(); i++) {
            DoConversion(FileNames[i], OutputFormat);
        }
        TextCtrlConversionStatus->AppendText(_("Finished converting all files\n"));
    }

    ButtonStartConversion->Enable(true);
}


