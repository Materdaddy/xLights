#include "xConverter.h"
#include <wx/msgdlg.h>
#include <wx/config.h>
#include <wx/icon.h>
#include <wx/file.h>

#include "../include/xlights.xpm"
#include "../include/xml-irr-1.2/irrXML.h"
#include "../include/xml-irr-1.2/irrXML.cpp"
using namespace irr;
using namespace io;


//(*InternalHeaders(xConverter)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(xConverter)
const long xConverter::ID_STATICTEXT1 = wxNewId();
const long xConverter::ID_STATICTEXT2 = wxNewId();
const long xConverter::ID_TEXTCTRL_FILENAME = wxNewId();
const long xConverter::ID_BUTTON_CHOOSE_FILE = wxNewId();
const long xConverter::ID_STATICTEXT3 = wxNewId();
const long xConverter::ID_CHOICE_OUTPUT_FORMAT = wxNewId();
const long xConverter::ID_STATICTEXT4 = wxNewId();
const long xConverter::ID_CHECKBOX_OFF_AT_END = wxNewId();
const long xConverter::ID_BUTTON_START = wxNewId();
const long xConverter::ID_TEXTCTRL_STATUS = wxNewId();
const long xConverter::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(xConverter,wxFrame)
	//(*EventTable(xConverter)
	//*)
END_EVENT_TABLE()

xConverter::xConverter(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(xConverter)
	wxFlexGridSizer* FlexGridSizer3;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("xLights File Converter"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(3);
	StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("xLights File Converter"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Sequence files to convert:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer3->Add(StaticText2, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlFilename = new wxTextCtrl(Panel1, ID_TEXTCTRL_FILENAME, wxEmptyString, wxDefaultPosition, wxSize(217,65), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_FILENAME"));
	TextCtrlFilename->SetBackgroundColour(wxColour(224,224,224));
	FlexGridSizer3->Add(TextCtrlFilename, 1, wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonChooseFile = new wxButton(Panel1, ID_BUTTON_CHOOSE_FILE, _("Choose Files"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CHOOSE_FILE"));
	FlexGridSizer3->Add(ButtonChooseFile, 1, wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("Output Format:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer3->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ChoiceOutputFormat = new wxChoice(Panel1, ID_CHOICE_OUTPUT_FORMAT, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_OUTPUT_FORMAT"));
	ChoiceOutputFormat->SetSelection( ChoiceOutputFormat->Append(_("xLights Sequence")) );
	ChoiceOutputFormat->Append(_("Lynx Conductor"));
	ChoiceOutputFormat->Append(_("Vixen 2.1"));
	FlexGridSizer3->Add(ChoiceOutputFormat, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(Panel1, ID_STATICTEXT4, _("All channels off at end:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer3->Add(StaticText4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxOffAtEnd = new wxCheckBox(Panel1, ID_CHECKBOX_OFF_AT_END, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_OFF_AT_END"));
	CheckBoxOffAtEnd->SetValue(false);
	FlexGridSizer3->Add(CheckBoxOffAtEnd, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonStart = new wxButton(Panel1, ID_BUTTON_START, _("Start Conversion"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_START"));
	FlexGridSizer1->Add(ButtonStart, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	TextCtrlStatus = new wxTextCtrl(Panel1, ID_TEXTCTRL_STATUS, wxEmptyString, wxDefaultPosition, wxSize(341,72), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_STATUS"));
	TextCtrlStatus->SetBackgroundColour(wxColour(240,240,240));
	FlexGridSizer1->Add(TextCtrlStatus, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(Panel1);
	FlexGridSizer1->SetSizeHints(Panel1);
	BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(BoxSizer1);
	FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, _("LOR Music Sequences (*.lms)|*.lms|LOR Animation Sequences (*.las)|*.las|Vixen Sequences (*.vix)|*.vix"), wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON_CHOOSE_FILE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xConverter::OnButtonChooseFileClick);
	Connect(ID_BUTTON_START,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xConverter::OnButtonStartClick);
	//*)

    SetIcon(wxIcon(xlights_xpm));

    /*
    wxLog *logger=new wxLogTextCtrl(TextCtrlLog);
    wxLog::SetActiveTarget(logger);
    Notebook1->AddPage(PanelLog, _("Log"), false);
    */

    // Get CurrentDir
    wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));
    if ( !config->Read(_("LastDir"), &CurrentDir) ) {
        wxMessageBox(_("No directory specified"), _("ERROR"));
        Close();
    }
    wxString ConvertDir;
    if (!config->Read(_("ConvertDir"), &ConvertDir)) {
        ConvertDir=CurrentDir;
    }
    FileDialog1->SetDirectory(ConvertDir);
    networkFile.AssignDir( CurrentDir );
    networkFile.SetFullName(_(XLIGHTS_NETWORK_FILE));
    LoadNetworkFile();
}

xConverter::~xConverter()
{
	//(*Destroy(xConverter)
	//*)
}


void xConverter::ConversionError(const wxString& msg)
{
    wxMessageBox(msg, _("Error"), wxOK | wxICON_EXCLAMATION);
}

void xConverter::LoadNetworkFile()
{
    long MaxChan;
    TotChannels=0;
    wxString tempstr,tagname,NetworkType,ComPort,BaudRate;
    wxXmlDocument doc;
    if (doc.Load( networkFile.GetFullPath() )) {
        wxXmlNode* e=doc.GetRoot();
        tempstr=e->GetPropVal(wxT("LorMapping"), wxT("2"));
        tempstr.ToLong(&LorMapping);
        for( e=e->GetChildren(); e!=NULL; e=e->GetNext() ) {
            tagname=e->GetName();
            if (tagname == wxT("network")) {
                tempstr=e->GetPropVal(wxT("MaxChannels"), wxT("0"));
                tempstr.ToLong(&MaxChan);
                TotChannels+=MaxChan;
                NetMaxChannel.push_back(MaxChan);
                /*
                NetworkType=e->GetPropVal(wxT("NetworkType"), wxT(""));
                ComPort=e->GetPropVal(wxT("ComPort"), wxT(""));
                BaudRate=e->GetPropVal(wxT("BaudRate"), wxT(""));
                AddNetwork(NetworkType,ComPort,BaudRate,MaxChan);
                */
            }
        }
    } else {
        ConversionError(_("Unable to load network definition file"));
    }
}

/*
   base64.cpp and base64.h

   Copyright (C) 2004-2008 René Nyffenegger

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

   René Nyffenegger rene.nyffenegger@adp-gmbh.ch

*/

static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

wxString xConverter::base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
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


std::string xConverter::base64_decode(const wxString& encoded_string) {
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


void xConverter::OnButtonChooseFileClick(wxCommandEvent& event)
{
    wxArrayString ShortNames;
    wxString AllNames;
    if (FileDialog1->ShowModal() == wxID_OK) {
        FileDialog1->GetPaths(FileNames);
        FileDialog1->GetFilenames(ShortNames);
        for (size_t i=0; i < ShortNames.GetCount(); i++) {
            AllNames.Append(ShortNames[i]);
            AllNames.Append(wxT("\n"));
        }
        TextCtrlFilename->ChangeValue( AllNames );
        wxString ConvertDir = FileDialog1->GetDirectory();
        wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));
        config->Write(_("ConvertDir"), ConvertDir);
    }
}

void xConverter::WriteVixenFile(const wxString& filename)
{
    wxString ChannelName;
    int32_t ChannelColor;
    long TotalTime=SeqNumPeriods * 50;
    TextCtrlStatus->AppendText(_("Writing Vixen sequence\n"));
    wxXmlNode *node,*chparent,*textnode;
    wxXmlDocument doc;
    wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("Program") );
    doc.SetRoot( root );

    // add nodes to root in reverse order

    node = new wxXmlNode( root, wxXML_ELEMENT_NODE, wxT("EventValues") );
    textnode = new wxXmlNode( node, wxXML_TEXT_NODE, wxEmptyString, base64_encode(SeqData, SeqDataLen) );

    node = new wxXmlNode( root, wxXML_ELEMENT_NODE, wxT("Audio") );
    node->AddProperty( wxT("filename"), mediaFilename);
    node->AddProperty( wxT("duration"), wxString::Format(wxT("%ld"),TotalTime));
    textnode = new wxXmlNode( node, wxXML_TEXT_NODE, wxEmptyString, wxT("Music") );

    chparent = new wxXmlNode( root, wxXML_ELEMENT_NODE, wxT("Channels") );
    for (size_t ch=0; ch < SeqNumChannels; ch++ ) {
        node = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("Channel") );
        node->AddProperty( wxT("output"), wxString::Format(wxT("%d"),ch));
        node->AddProperty( wxT("id"), wxT("0"));
        node->AddProperty( wxT("enabled"), wxT("True"));
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
        node->AddProperty( wxT("color"), wxString::Format(wxT("%d"),ChannelColor));
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
        TextCtrlStatus->AppendText(_("Finished writing new file: ")+filename+_("\n"));
    } else {
        ConversionError(_("Unable to save Vixen file"));
    }
}

void xConverter::WriteXLightsFile(const wxString& filename)
{
    TextCtrlStatus->AppendText(_("Writing xLights sequence\n"));
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
    sprintf(hdr,"xLights %2d %8d %8ld",1,SeqNumChannels,SeqNumPeriods);
    for (size_t i=0; i < mediaFilename.size(); i++) {
        hdr[i+32]=mediaFilename[i] & 0x7f;
    }
    f.Write(hdr,512);
    f.Write(SeqData,SeqDataLen);
    f.Close();
    TextCtrlStatus->AppendText(_("Finished writing new file: ")+filename+_("\n"));
}

void xConverter::WriteConductorFile(const wxString& filename)
{
    TextCtrlStatus->AppendText(_("Writing Lynx Conductor sequence\n"));
    wxFile f;
    wxUint8 buf[4];
    size_t ch,i,j;
    if (!f.Create(filename,true)) {
        ConversionError(_("Unable to create file: ")+filename);
        return;
    }
    for (long period=0; period < SeqNumPeriods; period++) {
        if (period % 500 == 499) TextCtrlStatus->AppendText(wxString::Format(wxT("Writing time period %d\n"),period+1));
        wxYield();
        for (i=0; i < 4096; i++) {
            for (j=0; j < 4; j++) {
                ch=j * 4096 + i;
                buf[j] = ch < SeqNumChannels ? SeqData[ch * SeqNumPeriods + period] : 0;
            }
            f.Write(buf,4);
        }
    }

    // pad the end of the file with 512 bytes of 0's
    memset(buf,0,4);
    for (i=0; i < 128; i++) {
        f.Write(buf,4);
    }
    f.Close();
    TextCtrlStatus->AppendText(_("Finished writing new file: ")+filename+_("\n"));
}

// return true on success
bool xConverter::LoadVixenProfile(const wxString& ProfileName)
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
        VixChannels.clear();
        wxXmlNode* root=doc.GetRoot();
        for( wxXmlNode* e=root->GetChildren(); e!=NULL; e=e->GetNext() ) {
            tag = e->GetName();
            if (tag == _("ChannelObjects")) {
                for( wxXmlNode* p=e->GetChildren(); p!=NULL; p=p->GetNext() ) {
                    if (p->GetName() == _("Channel")) {
                        if (p->HasProp(wxT("output"))) {
                            tempstr=p->GetPropVal(wxT("output"), wxT("0"));
                            tempstr.ToLong(&OutputChannel);
                            VixChannels.push_back(OutputChannel);
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

void xConverter::ReadVixFile(const char* filename)
{
	wxString NodeName,NodeValue,msg;
	std::string VixSeqData;
	size_t cnt = 0;
	wxArrayString context;
    long VixEventPeriod=-1;
	long MaxIntensity = 255;
	int OutputChannel;

    mediaFilename.clear();
    VixChannels.clear();
    delete SeqData;
    SeqData = 0;
    TextCtrlStatus->AppendText(_("Reading Vixen sequence\n"));
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
                if (context[1] == _("Profile")) LoadVixenProfile(NodeValue);
			}
			break;
		case EXN_ELEMENT:
            NodeName = wxString::FromAscii( xml->getNodeName() );
            context.Add(NodeName);
            cnt++;
            //msg=_("Element: ") + NodeName + wxString::Format(_(" (%d)\n"),cnt);
            //TextCtrlStatus->AppendText(msg);
            if (cnt == 2 && (NodeName == _("Audio") || NodeName == _("Song"))) {
                mediaFilename = wxString::FromAscii( xml->getAttributeValueSafe("filename") );
            }
            if (cnt > 1 && context[1] == _("Channels") && NodeName == _("Channel")) {
                OutputChannel = xml->getAttributeValueAsInt("output");
                VixChannels.push_back(OutputChannel);
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
	SeqNumChannels = VixChannels.size();
    TextCtrlStatus->AppendText(wxString::Format(_("Max Intensity=%ld\n"),MaxIntensity));
    TextCtrlStatus->AppendText(wxString::Format(_("# of Channels=%d\n"),SeqNumChannels));
    TextCtrlStatus->AppendText(wxString::Format(_("Vix Event Period=%ld\n"),VixEventPeriod));
    TextCtrlStatus->AppendText(wxString::Format(_("Vix data len=%d\n"),VixDataLen));
    if (SeqNumChannels == 0) return;
    long VixNumPeriods = VixDataLen / SeqNumChannels;
    TextCtrlStatus->AppendText(wxString::Format(_("Vix # of time periods=%ld\n"),VixNumPeriods));
    TextCtrlStatus->AppendText(_("Media file=")+mediaFilename+_("\n"));
    SeqNumPeriods = VixNumPeriods * VixEventPeriod / XTIMER_INTERVAL;
    SeqDataLen = SeqNumPeriods * SeqNumChannels;
    TextCtrlStatus->AppendText(wxString::Format(_("New # of time periods=%ld\n"),SeqNumPeriods));
    TextCtrlStatus->AppendText(wxString::Format(_("New data len=%d\n"),SeqDataLen));
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

// return a random number between 0 and 1 inclusive
double xConverter::rand01()
{
    return (double)rand()/(double)RAND_MAX;
}

// returns length of first track in centiseconds
int xConverter::GetLorTrack1Length(const char* filename)
{
	int centisec = -1;
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
            if (NodeName == _("track")) {
                centisec = xml->getAttributeValueAsInt("totalCentiseconds");
            }
			break;
        default: break;
		}
	}
	delete xml;
    TextCtrlStatus->AppendText(wxString::Format(_("Track 1 length = %d centiseconds\n"),centisec));
    return centisec;
}

void xConverter::ReadLorFile(const char* filename)
{
	wxString NodeName,msg,EffectType,ChannelName;
	wxArrayString context;
	int unit,circuit,startcsec,endcsec,intensity,startIntensity,endIntensity,rampdiff,ChannelColor;
	int i,startper,endper,perdiff,twinklestate,nexttwinkle;
	int twinkleperiod = 400;
	int curchannel = -1;
	int MappedChannelCnt = 0;
	int MaxIntensity = 100;
	int EffectCnt = 0;
	size_t network,chindex;
	size_t cnt = 0;

    TextCtrlStatus->AppendText(_("Reading LOR sequence\n"));
    mediaFilename.clear();
    ChannelNames.Clear();
    ChannelNames.Add(wxEmptyString, TotChannels);
    ChannelColors.Clear();
    ChannelColors.Add(0, TotChannels);
    SeqNumChannels=TotChannels;
    delete SeqData;
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
            //msg=_("Element: ") + NodeName + wxString::Format(_(" (%d)\n"),cnt);
            //TextCtrlStatus->AppendText(msg);
            if (NodeName == _("sequence")) {
                mediaFilename = wxString::FromAscii( xml->getAttributeValueSafe("musicFilename") );
            }
            if (cnt > 1 && context[1] == _("channels") && NodeName == _("channel") && !xml->isEmptyElement()) {
                network = xml->getAttributeValueAsInt("network");
                unit = xml->getAttributeValueAsInt("unit");
                if (unit < 0) unit+=256;
                circuit = xml->getAttributeValueAsInt("circuit");
                if (unit > 0 && circuit > 0 && network < NetMaxChannel.size()) {
                    chindex=(unit-1)*16+circuit-1;
                    switch (LorMapping) {
                        case XLIGHTS_LORMAP_SINGLE:
                            if (network==0 && chindex < TotChannels) {
                                MappedChannelCnt++;
                                curchannel = chindex;
                            } else {
                                curchannel = -1;
                            }
                            break;
                        case XLIGHTS_LORMAP_MULTI:
                            if (chindex < NetMaxChannel[network]) {
                                MappedChannelCnt++;
                                curchannel = chindex;
                                for (i=0; i < network; i++) {
                                    curchannel += NetMaxChannel[i];
                                }
                            } else {
                                curchannel = -1;
                            }
                            break;
                    }
                    //TextCtrlStatus->AppendText(wxString::Format(_("curchannel %d\n"),curchannel));
                    ChannelName = wxString::FromAscii( xml->getAttributeValueSafe("name") );
                    if (curchannel < 0) {
                        TextCtrlStatus->AppendText(_("WARNING: channel '")+ChannelName+_("' is unmapped\n"));
                    } else if (curchannel < TotChannels) {
                        if (!ChannelNames[curchannel].IsEmpty()) {
                            TextCtrlStatus->AppendText(_("WARNING: ")+ChannelNames[curchannel]+_(" and ")+ChannelName+_(" map to the same channel\n"));
                        }
                        ChannelNames[curchannel] = ChannelName;
                        ChannelColor = xml->getAttributeValueAsInt("color");
                        ChannelColors[curchannel] = ChannelColor;
                    }
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
    TextCtrlStatus->AppendText(wxString::Format(_("# of mapped channels with effects=%d\n"),MappedChannelCnt));
    TextCtrlStatus->AppendText(wxString::Format(_("# of effects=%d\n"),EffectCnt));
    TextCtrlStatus->AppendText(_("Media file=")+mediaFilename+_("\n"));
    TextCtrlStatus->AppendText(wxString::Format(_("New # of time periods=%ld\n"),SeqNumPeriods));
    TextCtrlStatus->AppendText(wxString::Format(_("New data len=%d\n"),SeqDataLen));
}

void xConverter::ClearLastPeriod()
{
    long LastPer = SeqNumPeriods-1;
    for (size_t ch=0; ch < SeqNumChannels; ch++) {
        SeqData[ch*SeqNumPeriods+LastPer] = 0;
    }
}

void xConverter::DoConversion(const wxString& Filename, const wxString& OutputFormat)
{
    // read sequence file
    wxFileName oName(Filename);
    wxString ext = oName.GetExt();
    if (ext == _("vix")) {
        if (OutputFormat[0] == 'V') {
            ConversionError(_("Cannot convert from Vixen to Vixen!"));
            return;
        }
        ReadVixFile(Filename.char_str());
    } else if (ext == _("lms") || ext == _("las")) {
        ReadLorFile(Filename.char_str());
    } else {
        ConversionError(_("Invalid sequence file extension"));
        return;
    }

    // check for errors
    if (SeqNumChannels == 0) {
        TextCtrlStatus->AppendText(_("ERROR: no channels defined\n"));
        return;
    }
    if (!SeqData || SeqDataLen == 0) {
        TextCtrlStatus->AppendText(_("ERROR: sequence length is 0\n"));
        return;
    }

    if (CheckBoxOffAtEnd->IsChecked()) {
        ClearLastPeriod();
    }

    // write converted file
    switch (OutputFormat[0])
    {
        case 'x':
            oName.SetExt(_(XLIGHTS_SEQUENCE_EXT));
            WriteXLightsFile(oName.GetFullPath());
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
            TextCtrlStatus->AppendText(_("Nothing to write - invalid output format\n"));
            break;
    }
}

void xConverter::OnButtonStartClick(wxCommandEvent& event)
{
    ButtonStart->Enable(false);
    wxString OutputFormat = ChoiceOutputFormat->GetStringSelection();
    TextCtrlStatus->Clear();

    // check user inputs
    if (FileNames.IsEmpty()) {
        wxMessageBox(_("Please select one or more sequence files"), _("Error"));
    } else if (OutputFormat.IsEmpty()) {
        wxMessageBox(_("Please select an output format"), _("Error"));
    } else {
        for (size_t i=0; i < FileNames.GetCount(); i++) {
            DoConversion(FileNames[i], OutputFormat);
        }
        TextCtrlStatus->AppendText(_("Finished converting all files\n"));
    }

    ButtonStart->Enable(true);
}
