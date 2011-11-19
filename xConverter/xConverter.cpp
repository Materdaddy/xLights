#include "xConverter.h"
#include <wx/msgdlg.h>
#include <wx/config.h>
#include <wx/icon.h>
#include "../include/xlights.xpm"

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
	wxFlexGridSizer* FlexGridSizer2;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("xLights File Converter"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(1);
	StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("xLights File Converter"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(12,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Sequence file to convert:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(StaticText2, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlFilename = new wxTextCtrl(Panel1, ID_TEXTCTRL_FILENAME, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_FILENAME"));
	FlexGridSizer2->Add(TextCtrlFilename, 1, wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonChooseFile = new wxButton(Panel1, ID_BUTTON_CHOOSE_FILE, _("Choose File"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CHOOSE_FILE"));
	FlexGridSizer2->Add(ButtonChooseFile, 1, wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("Output Format:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer2->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ChoiceOutputFormat = new wxChoice(Panel1, ID_CHOICE_OUTPUT_FORMAT, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_OUTPUT_FORMAT"));
	ChoiceOutputFormat->Append(_("xLights Sequence"));
	ChoiceOutputFormat->Append(_("Lynx Conductor"));
	ChoiceOutputFormat->Append(_("Vixen"));
	FlexGridSizer2->Add(ChoiceOutputFormat, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ButtonStart = new wxButton(Panel1, ID_BUTTON_START, _("Start Conversion"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_START"));
	FlexGridSizer2->Add(ButtonStart, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	BoxSizer2->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Conversion Status"));
	TextCtrlStatus = new wxTextCtrl(Panel1, ID_TEXTCTRL_STATUS, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_STATUS"));
	TextCtrlStatus->SetBackgroundColour(wxColour(240,240,240));
	StaticBoxSizer1->Add(TextCtrlStatus, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(StaticBoxSizer1, 2, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	Panel1->SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(Panel1);
	FlexGridSizer1->SetSizeHints(Panel1);
	BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(BoxSizer1);
	FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, _("LOR Music Sequences (*.lms)|*.lms|LOR Animation Sequences (*.las)|*.las|Vixen Sequences (*.vix)|*.vix"), wxFD_OPEN|wxFD_FILE_MUST_EXIST, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
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
    wxString CurrentDir;
    if ( !config->Read(_("LastDir"), &CurrentDir) ) {
        wxMessageBox(_("No directory specified"), _("ERROR"));
        Close();
    }
    FileDialog1->SetDirectory(CurrentDir);
    networkFile.AssignDir( CurrentDir );
    networkFile.SetFullName(_(XLIGHTS_NETWORK_FILE));
    LoadFile();
}

xConverter::~xConverter()
{
	//(*Destroy(xConverter)
	//*)
}


void xConverter::LoadFile()
{
    long MaxChan;
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
                /*
                NetworkType=e->GetPropVal(wxT("NetworkType"), wxT(""));
                ComPort=e->GetPropVal(wxT("ComPort"), wxT(""));
                BaudRate=e->GetPropVal(wxT("BaudRate"), wxT(""));
                AddNetwork(NetworkType,ComPort,BaudRate,MaxChan);
                */
            }
        }
    } else {
        wxMessageBox(_("Unable to load network definition file"), _("Error"));
    }
}

void xConverter::OnButtonChooseFileClick(wxCommandEvent& event)
{
    if (FileDialog1->ShowModal() == wxID_OK) {
        TextCtrlFilename->ChangeValue( FileDialog1->GetPath() );
    }
}

void xConverter::OnButtonStartClick(wxCommandEvent& event)
{
    wxString Filename = TextCtrlFilename->GetValue();
    if (Filename.IsEmpty()) {
        wxMessageBox(_("Please select a file name"), _("Error"));
        return;
    }
    wxString OutputFormat = ChoiceOutputFormat->GetStringSelection();
    if (OutputFormat.IsEmpty()) {
        wxMessageBox(_("Please select an output format"), _("Error"));
        return;
    }
    TextCtrlStatus->Clear();
    TextCtrlStatus->AppendText(_("Starting conversion\n"));
}
