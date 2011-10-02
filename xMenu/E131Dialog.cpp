#include "E131Dialog.h"

//(*InternalHeaders(E131Dialog)
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(E131Dialog)
const long E131Dialog::ID_STATICTEXT4 = wxNewId();
const long E131Dialog::ID_STATICTEXT1 = wxNewId();
const long E131Dialog::ID_TEXTCTRL_IP_ADDR = wxNewId();
const long E131Dialog::ID_STATICTEXT2 = wxNewId();
const long E131Dialog::ID_TEXTCTRL_UNIVERSE = wxNewId();
const long E131Dialog::ID_STATICTEXT3 = wxNewId();
const long E131Dialog::ID_TEXTCTRL_LAST_CHANNEL = wxNewId();
//*)

BEGIN_EVENT_TABLE(E131Dialog,wxDialog)
	//(*EventTable(E131Dialog)
	//*)
END_EVENT_TABLE()

E131Dialog::E131Dialog(wxWindow* parent,const wxString& title)
{
	//(*Initialize(E131Dialog)
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Sets up an E1.31 connection over ethernet.\n\nSupported devices include those made\nby j1sys, the Lynx EtherDongle, and \nE1.31 projects on DIYC.\n\nEither enter your device\'s IP address\nhere for direct (unicast) communication,\nor use 239.255.x.y for multicast\n(where x is the high byte of the\nuniverse #, and y is the low byte\nof the universe #).\n\nThe Universe # should match one of\nthe universe numbers you have set up\non your E1.31 device."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer1->Add(StaticText4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("IP Address"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlIpAddr = new wxTextCtrl(this, ID_TEXTCTRL_IP_ADDR, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_IP_ADDR"));
	FlexGridSizer2->Add(TextCtrlIpAddr, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Universe #"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlUniverse = new wxTextCtrl(this, ID_TEXTCTRL_UNIVERSE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_UNIVERSE"));
	FlexGridSizer2->Add(TextCtrlUniverse, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Last Channel"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer2->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlLastChannel = new wxTextCtrl(this, ID_TEXTCTRL_LAST_CHANNEL, _("512"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_LAST_CHANNEL"));
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
}

E131Dialog::~E131Dialog()
{
	//(*Destroy(E131Dialog)
	//*)
}

