#include "SerialPortWithRate.h"

//(*InternalHeaders(SerialPortWithRate)
#include <wx/button.h>
#include <wx/string.h>
#include <wx/intl.h>
//*)
#include <wx/valtext.h>
#include <wx/msgdlg.h>

//(*IdInit(SerialPortWithRate)
const long SerialPortWithRate::ID_STATICTEXT_PORT = wxNewId();
const long SerialPortWithRate::ID_CHOICE_PORT = wxNewId();
const long SerialPortWithRate::ID_STATICTEXT_RATE = wxNewId();
const long SerialPortWithRate::ID_CHOICE_BAUD_RATE = wxNewId();
const long SerialPortWithRate::ID_STATICTEXT3 = wxNewId();
const long SerialPortWithRate::ID_TEXTCTRL_LAST_CHANNEL = wxNewId();
//*)

BEGIN_EVENT_TABLE(SerialPortWithRate,wxDialog)
	//(*EventTable(SerialPortWithRate)
	//*)
END_EVENT_TABLE()

SerialPortWithRate::SerialPortWithRate(wxWindow* parent,const wxString& title)
{
	//(*Initialize(SerialPortWithRate)
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticTextPort = new wxStaticText(this, ID_STATICTEXT_PORT, _("Port"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_PORT"));
	FlexGridSizer2->Add(StaticTextPort, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ChoicePort = new wxChoice(this, ID_CHOICE_PORT, wxDefaultPosition, wxSize(127,29), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_PORT"));
	FlexGridSizer2->Add(ChoicePort, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticTextRate = new wxStaticText(this, ID_STATICTEXT_RATE, _("Baud Rate"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_RATE"));
	FlexGridSizer2->Add(StaticTextRate, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ChoiceBaudRate = new wxChoice(this, ID_CHOICE_BAUD_RATE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_BAUD_RATE"));
	ChoiceBaudRate->Append(_("9600"));
	ChoiceBaudRate->Append(_("19200"));
	ChoiceBaudRate->Append(_("38400"));
	ChoiceBaudRate->Append(_("57600"));
	ChoiceBaudRate->Append(_("115200"));
	FlexGridSizer2->Add(ChoiceBaudRate, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Last Channel"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer2->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlLastChannel = new wxTextCtrl(this, ID_TEXTCTRL_LAST_CHANNEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_LAST_CHANNEL"));
	TextCtrlLastChannel->SetMaxLength(5);
	FlexGridSizer2->Add(TextCtrlLastChannel, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	FlexGridSizer1->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	//*)

    wxArrayString ports;
    PopulatePortChooser(&ports);
    ChoicePort->Append(ports);
}

SerialPortWithRate::~SerialPortWithRate()
{
	//(*Destroy(SerialPortWithRate)
	//*)
}

void SerialPortWithRate::PopulatePortChooser(wxArrayString *chooser)
{
#ifdef __WXMSW__
  // Windows
  chooser->Add(wxT("COM1"));
  chooser->Add(wxT("COM2"));
  chooser->Add(wxT("COM3"));
  chooser->Add(wxT("COM4"));
  chooser->Add(wxT("COM5"));
  chooser->Add(wxT("COM6"));
  chooser->Add(wxT("COM7"));
  chooser->Add(wxT("COM8"));
  chooser->Add(wxT("COM9"));
  chooser->Add(wxT("\\\\.\\COM10"));
  chooser->Add(wxT("\\\\.\\COM11"));
  chooser->Add(wxT("\\\\.\\COM12"));
  chooser->Add(wxT("\\\\.\\COM13"));
  chooser->Add(wxT("\\\\.\\COM14"));
  chooser->Add(wxT("\\\\.\\COM15"));
  chooser->Add(wxT("\\\\.\\COM16"));
  chooser->Add(wxT("\\\\.\\COM17"));
  chooser->Add(wxT("\\\\.\\COM18"));
  chooser->Add(wxT("\\\\.\\COM19"));
  chooser->Add(wxT("\\\\.\\COM20"));
#elif __WXMAC__
  // no standard device names for USB-serial converters on OS/X
  // scan /dev directory for candidates
  wxArrayString output,errors;
  wxExecute(wxT("ls -1 /dev"), output, errors, wxEXEC_SYNC);
  if (!errors.IsEmpty()) {
    wxMessageBox(errors.Last(), _("Error"));
  } else if (output.IsEmpty()) {
    wxMessageBox(_("no devices found"), _("Error"));
  } else {
    for (int i=0; i<output.Count(); i++) {
      if (output[i].StartsWith(wxT("cu."))) {
         chooser->Add(wxT("/dev/") + output[i]);
      }
    }
  }
#else
  // Linux
  chooser->Add(wxT("/dev/ttyS0"));
  chooser->Add(wxT("/dev/ttyS1"));
  chooser->Add(wxT("/dev/ttyS2"));
  chooser->Add(wxT("/dev/ttyS3"));
  chooser->Add(wxT("/dev/ttyUSB0"));
  chooser->Add(wxT("/dev/ttyUSB1"));
  chooser->Add(wxT("/dev/ttyUSB2"));
  chooser->Add(wxT("/dev/ttyUSB3"));
  chooser->Add(wxT("/dev/ttyUSB4"));
  chooser->Add(wxT("/dev/ttyUSB5"));
#endif
}

