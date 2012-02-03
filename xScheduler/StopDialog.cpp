#include "StopDialog.h"

//(*InternalHeaders(StopDialog)
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(StopDialog)
const long StopDialog::ID_STATICTEXT1 = wxNewId();
const long StopDialog::ID_RADIOBUTTON_IMMEDIATE = wxNewId();
const long StopDialog::ID_RADIOBUTTON_WAIT = wxNewId();
const long StopDialog::ID_STATICTEXT2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(StopDialog,wxDialog)
	//(*EventTable(StopDialog)
	//*)
END_EVENT_TABLE()

StopDialog::StopDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(StopDialog)
	wxFlexGridSizer* FlexGridSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, id, _("Stop Playlist"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("How should the playlist be stopped\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonImmediate = new wxRadioButton(this, ID_RADIOBUTTON_IMMEDIATE, _("Immediately"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON_IMMEDIATE"));
	RadioButtonImmediate->SetValue(true);
	FlexGridSizer1->Add(RadioButtonImmediate, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonWait = new wxRadioButton(this, ID_RADIOBUTTON_WAIT, _("After the current item finishes playing"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON_WAIT"));
	FlexGridSizer1->Add(RadioButtonWait, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Note that clicking OK will also cause the scheduler to be stopped"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
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

StopDialog::~StopDialog()
{
	//(*Destroy(StopDialog)
	//*)
}

bool StopDialog::StopImmediately()
{
	return RadioButtonImmediate->GetValue();
}

