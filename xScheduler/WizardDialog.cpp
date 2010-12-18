#include "WizardDialog.h"

//(*InternalHeaders(WizardDialog)
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(WizardDialog)
const long WizardDialog::ID_STATICTEXT1 = wxNewId();
const long WizardDialog::ID_STATICTEXT_LISTNAME = wxNewId();
const long WizardDialog::ID_CHECKBOX_FIRSTITEM = wxNewId();
const long WizardDialog::ID_CHECKBOX_LASTITEM = wxNewId();
const long WizardDialog::ID_CHECKBOX_LIGHTSOFF = wxNewId();
//*)

BEGIN_EVENT_TABLE(WizardDialog,wxDialog)
	//(*EventTable(WizardDialog)
	//*)
END_EVENT_TABLE()

WizardDialog::WizardDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(WizardDialog)
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;
	
	Create(parent, id, _("Script Wizard"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Playlist:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticTextListName = new wxStaticText(this, ID_STATICTEXT_LISTNAME, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_LISTNAME"));
	FlexGridSizer2->Add(StaticTextListName, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxFirstItem = new wxCheckBox(this, ID_CHECKBOX_FIRSTITEM, _("Play first item once at beginning"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_FIRSTITEM"));
	CheckBoxFirstItem->SetValue(false);
	FlexGridSizer1->Add(CheckBoxFirstItem, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxLastItem = new wxCheckBox(this, ID_CHECKBOX_LASTITEM, _("Play last item once at end"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_LASTITEM"));
	CheckBoxLastItem->SetValue(false);
	FlexGridSizer1->Add(CheckBoxLastItem, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxLightsOff = new wxCheckBox(this, ID_CHECKBOX_LIGHTSOFF, _("Turn lights off between each sequence"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_LIGHTSOFF"));
	CheckBoxLightsOff->SetValue(false);
	FlexGridSizer1->Add(CheckBoxLightsOff, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
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

WizardDialog::~WizardDialog()
{
	//(*Destroy(WizardDialog)
	//*)
}

