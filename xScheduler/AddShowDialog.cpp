#include "AddShowDialog.h"

//(*InternalHeaders(AddShowDialog)
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(AddShowDialog)
const long AddShowDialog::ID_STATICTEXT1 = wxNewId();
const long AddShowDialog::ID_CHOICE_PLAYLIST = wxNewId();
const long AddShowDialog::ID_STATICTEXT5 = wxNewId();
const long AddShowDialog::ID_CHOICE_STARTTIME = wxNewId();
const long AddShowDialog::ID_STATICTEXT6 = wxNewId();
const long AddShowDialog::ID_CHOICE_ENDTIME = wxNewId();
const long AddShowDialog::ID_STATICTEXT2 = wxNewId();
const long AddShowDialog::ID_CHECKBOX_REPEAT = wxNewId();
const long AddShowDialog::ID_STATICTEXT3 = wxNewId();
const long AddShowDialog::ID_CHECKBOX_FIRST_ITEM = wxNewId();
const long AddShowDialog::ID_STATICTEXT4 = wxNewId();
const long AddShowDialog::ID_CHECKBOX_LAST_ITEM = wxNewId();
const long AddShowDialog::ID_STATICTEXT7 = wxNewId();
const long AddShowDialog::ID_CHECKBOX_RANDOM = wxNewId();
const long AddShowDialog::ID_CHECKBOX4 = wxNewId();
const long AddShowDialog::ID_CHECKBOX5 = wxNewId();
const long AddShowDialog::ID_CHECKBOX6 = wxNewId();
const long AddShowDialog::ID_CHECKBOX7 = wxNewId();
const long AddShowDialog::ID_CHECKBOX_TH = wxNewId();
const long AddShowDialog::ID_CHECKBOX_FR = wxNewId();
const long AddShowDialog::ID_CHECKBOX_SA = wxNewId();
//*)

BEGIN_EVENT_TABLE(AddShowDialog,wxDialog)
	//(*EventTable(AddShowDialog)
	//*)
END_EVENT_TABLE()

AddShowDialog::AddShowDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(AddShowDialog)
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer5;
	wxBoxSizer* BoxSizer2;
	wxFlexGridSizer* FlexGridSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;
	
	Create(parent, wxID_ANY, _("Schedule Playlist"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer5 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Playlist"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer4->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ChoicePlayList = new wxChoice(this, ID_CHOICE_PLAYLIST, wxDefaultPosition, wxSize(113,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_PLAYLIST"));
	FlexGridSizer4->Add(ChoicePlayList, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Start Time"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer4->Add(StaticText5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ChoiceStartTime = new wxChoice(this, ID_CHOICE_STARTTIME, wxDefaultPosition, wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_STARTTIME"));
	FlexGridSizer4->Add(ChoiceStartTime, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("End Time"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer4->Add(StaticText6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ChoiceEndTime = new wxChoice(this, ID_CHOICE_ENDTIME, wxDefaultPosition, wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_ENDTIME"));
	FlexGridSizer4->Add(ChoiceEndTime, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Repeat"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer4->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxRepeat = new wxCheckBox(this, ID_CHECKBOX_REPEAT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_REPEAT"));
	CheckBoxRepeat->SetValue(false);
	FlexGridSizer4->Add(CheckBoxRepeat, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Play first\nitem once"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer4->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxFirstItem = new wxCheckBox(this, ID_CHECKBOX_FIRST_ITEM, _("  (if repeating)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_FIRST_ITEM"));
	CheckBoxFirstItem->SetValue(false);
	FlexGridSizer4->Add(CheckBoxFirstItem, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Play last\nitem once"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer4->Add(StaticText4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxLastItem = new wxCheckBox(this, ID_CHECKBOX_LAST_ITEM, _("  (if repeating)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_LAST_ITEM"));
	CheckBoxLastItem->SetValue(false);
	FlexGridSizer4->Add(CheckBoxLastItem, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Random\norder"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer4->Add(StaticText7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxRandom = new wxCheckBox(this, ID_CHECKBOX_RANDOM, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RANDOM"));
	CheckBoxRandom->SetValue(false);
	FlexGridSizer4->Add(CheckBoxRandom, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(FlexGridSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	CheckBoxSu = new wxCheckBox(this, ID_CHECKBOX4, _("Su"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	CheckBoxSu->SetValue(false);
	BoxSizer2->Add(CheckBoxSu, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	CheckBoxMo = new wxCheckBox(this, ID_CHECKBOX5, _("Mo"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	CheckBoxMo->SetValue(false);
	BoxSizer2->Add(CheckBoxMo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	CheckBoxTu = new wxCheckBox(this, ID_CHECKBOX6, _("Tu"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	CheckBoxTu->SetValue(false);
	BoxSizer2->Add(CheckBoxTu, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	CheckBoxWe = new wxCheckBox(this, ID_CHECKBOX7, _("We"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	CheckBoxWe->SetValue(false);
	BoxSizer2->Add(CheckBoxWe, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	CheckBoxTh = new wxCheckBox(this, ID_CHECKBOX_TH, _("Th"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_TH"));
	CheckBoxTh->SetValue(false);
	BoxSizer2->Add(CheckBoxTh, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	CheckBoxFr = new wxCheckBox(this, ID_CHECKBOX_FR, _("Fr"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_FR"));
	CheckBoxFr->SetValue(false);
	BoxSizer2->Add(CheckBoxFr, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	CheckBoxSa = new wxCheckBox(this, ID_CHECKBOX_SA, _("Sa"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_SA"));
	CheckBoxSa->SetValue(false);
	BoxSizer2->Add(CheckBoxSa, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	FlexGridSizer5->Add(BoxSizer2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	FlexGridSizer5->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	//*)
}

AddShowDialog::~AddShowDialog()
{
	//(*Destroy(AddShowDialog)
	//*)
}

