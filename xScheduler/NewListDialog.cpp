#include "NewListDialog.h"

//(*InternalHeaders(NewListDialog)
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(NewListDialog)
const long NewListDialog::ID_STATICTEXT1 = wxNewId();
const long NewListDialog::ID_TEXTCTRL_NEWNAME = wxNewId();
const long NewListDialog::ID_STATICLINE1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(NewListDialog,wxDialog)
	//(*EventTable(NewListDialog)
	//*)
END_EVENT_TABLE()

NewListDialog::NewListDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(NewListDialog)
	wxFlexGridSizer* FlexGridSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;
	
	Create(parent, id, _("New Playlist"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Enter name for new playlist"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlNewName = new wxTextCtrl(this, ID_TEXTCTRL_NEWNAME, wxEmptyString, wxDefaultPosition, wxSize(212,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL_NEWNAME"));
	TextCtrlNewName->SetMaxLength(60);
	FlexGridSizer1->Add(TextCtrlNewName, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	FlexGridSizer1->Add(StaticLine1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	FlexGridSizer1->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	//*)
}

NewListDialog::~NewListDialog()
{
	//(*Destroy(NewListDialog)
	//*)
}

