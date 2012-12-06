#include "ModelDialog.h"

//(*InternalHeaders(ModelDialog)
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(ModelDialog)
const long ModelDialog::ID_STATICTEXT1 = wxNewId();
const long ModelDialog::ID_TEXTCTRL1 = wxNewId();
const long ModelDialog::ID_STATICTEXT5 = wxNewId();
const long ModelDialog::ID_CHOICE1 = wxNewId();
const long ModelDialog::ID_STATICTEXT2 = wxNewId();
const long ModelDialog::ID_SPINCTRL1 = wxNewId();
const long ModelDialog::ID_STATICTEXT3 = wxNewId();
const long ModelDialog::ID_SPINCTRL2 = wxNewId();
const long ModelDialog::ID_STATICTEXT4 = wxNewId();
const long ModelDialog::ID_SPINCTRL3 = wxNewId();
const long ModelDialog::ID_STATICTEXT6 = wxNewId();
const long ModelDialog::ID_SPINCTRL4 = wxNewId();
const long ModelDialog::ID_STATICTEXT7 = wxNewId();
const long ModelDialog::ID_CHOICE2 = wxNewId();
const long ModelDialog::ID_STATICTEXT8 = wxNewId();
const long ModelDialog::ID_RADIOBUTTON1 = wxNewId();
const long ModelDialog::ID_RADIOBUTTON2 = wxNewId();
const long ModelDialog::ID_STATICTEXT9 = wxNewId();
const long ModelDialog::ID_CHOICE3 = wxNewId();
const long ModelDialog::ID_STATICTEXT10 = wxNewId();
const long ModelDialog::ID_CHECKBOX1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ModelDialog,wxDialog)
	//(*EventTable(ModelDialog)
	//*)
END_EVENT_TABLE()

ModelDialog::ModelDialog(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(ModelDialog)
	wxFlexGridSizer* FlexGridSizer2;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, id, _("Model"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Model Name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl_Name = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer2->Add(TextCtrl_Name, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Display As"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer2->Add(StaticText5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	Choice_DisplayAs = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	Choice_DisplayAs->SetSelection( Choice_DisplayAs->Append(_("Tree 360")) );
	Choice_DisplayAs->Append(_("Tree 270"));
	Choice_DisplayAs->Append(_("Tree 180"));
	Choice_DisplayAs->Append(_("Tree 90"));
	Choice_DisplayAs->Append(_("Vert Matrix"));
	Choice_DisplayAs->Append(_("Horiz Matrix"));
	Choice_DisplayAs->Append(_("Single Line"));
	Choice_DisplayAs->Append(_("Arches"));
	Choice_DisplayAs->Append(_("Window Frame"));
	FlexGridSizer2->Add(Choice_DisplayAs, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_Strings = new wxStaticText(this, ID_STATICTEXT2, _("Actual # of Strings"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(StaticText_Strings, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SpinCtrl_parm1 = new wxSpinCtrl(this, ID_SPINCTRL1, _T("1"), wxDefaultPosition, wxSize(60,21), 0, 1, 100, 1, _T("ID_SPINCTRL1"));
	SpinCtrl_parm1->SetValue(_T("1"));
	FlexGridSizer2->Add(SpinCtrl_parm1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_Nodes = new wxStaticText(this, ID_STATICTEXT3, _("# of RGB Nodes per String"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer2->Add(StaticText_Nodes, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SpinCtrl_parm2 = new wxSpinCtrl(this, ID_SPINCTRL2, _T("50"), wxDefaultPosition, wxSize(60,21), 0, 1, 300, 50, _T("ID_SPINCTRL2"));
	SpinCtrl_parm2->SetValue(_T("50"));
	FlexGridSizer2->Add(SpinCtrl_parm2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_Strands = new wxStaticText(this, ID_STATICTEXT4, _("# of Strands per String"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticText_Strands->SetHelpText(_("How many times is a string folded\?"));
	FlexGridSizer2->Add(StaticText_Strands, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SpinCtrl_parm3 = new wxSpinCtrl(this, ID_SPINCTRL3, _T("1"), wxDefaultPosition, wxSize(60,21), 0, 1, 100, 1, _T("ID_SPINCTRL3"));
	SpinCtrl_parm3->SetValue(_T("1"));
	FlexGridSizer2->Add(SpinCtrl_parm3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Start Channel"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer2->Add(StaticText6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SpinCtrl_StartChannel = new wxSpinCtrl(this, ID_SPINCTRL4, _T("1"), wxDefaultPosition, wxSize(90,21), 0, 1, 99999, 1, _T("ID_SPINCTRL4"));
	SpinCtrl_StartChannel->SetValue(_T("1"));
	FlexGridSizer2->Add(SpinCtrl_StartChannel, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT7, _("Channel Order"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer2->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	Choice_Order = new wxChoice(this, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	Choice_Order->SetSelection( Choice_Order->Append(_("RGB")) );
	Choice_Order->Append(_("RBG"));
	Choice_Order->Append(_("GBR"));
	Choice_Order->Append(_("GRB"));
	Choice_Order->Append(_("BRG"));
	Choice_Order->Append(_("BGR"));
	FlexGridSizer2->Add(Choice_Order, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT8, _("Direction"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer2->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	RadioButton_LtoR = new wxRadioButton(this, ID_RADIOBUTTON1, _("L to R"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	RadioButton_LtoR->SetValue(true);
	BoxSizer1->Add(RadioButton_LtoR, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	RadioButton_RtoL = new wxRadioButton(this, ID_RADIOBUTTON2, _("R to L"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	BoxSizer1->Add(RadioButton_RtoL, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(BoxSizer1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT9, _("Smooth Edges (antialias)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer2->Add(StaticText4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	Choice_Antialias = new wxChoice(this, ID_CHOICE3, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
	Choice_Antialias->SetSelection( Choice_Antialias->Append(_("None")) );
	Choice_Antialias->Append(_("2x"));
	FlexGridSizer2->Add(Choice_Antialias, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT10, _("Part of my display"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer2->Add(StaticText7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	CheckBox_MyDisplay = new wxCheckBox(this, ID_CHECKBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBox_MyDisplay->SetValue(true);
	FlexGridSizer2->Add(CheckBox_MyDisplay, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	FlexGridSizer1->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	Center();

	Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&ModelDialog::OnChoice_DisplayAsSelect);
	//*)
}

ModelDialog::~ModelDialog()
{
	//(*Destroy(ModelDialog)
	//*)
}


void ModelDialog::UpdateLabels()
{
    wxString choice;
    choice=Choice_DisplayAs->GetStringSelection();
    if (choice == wxT("Arches")) {
        StaticText_Strings->SetLabelText(_("# of Arches"));
        StaticText_Nodes->SetLabelText(_("# of RGB Nodes per Arch"));
        StaticText_Strands->SetLabelText(_("n/a"));
        SpinCtrl_parm3->SetValue(1);
        SpinCtrl_parm3->Enable(false);
    } else if (choice == wxT("Window Frame")) {
        StaticText_Strings->SetLabelText(_("# of RGB Nodes Top"));
        StaticText_Nodes->SetLabelText(_("# of RGB Nodes Left/Right"));
        StaticText_Strands->SetLabelText(_("# of RGB Nodes Bottom"));
        SpinCtrl_parm3->Enable(true);
    } else if (choice == wxT("Single Line")) {
        StaticText_Strings->SetLabelText(_("Actual # of Strings"));
        StaticText_Nodes->SetLabelText(_("# of RGB Nodes per String"));
        StaticText_Strands->SetLabelText(_("n/a"));
        SpinCtrl_parm3->SetValue(1);
        SpinCtrl_parm3->Enable(false);
    } else {
        // matrix or tree
        StaticText_Strings->SetLabelText(_("Actual # of Strings"));
        StaticText_Nodes->SetLabelText(_("# of RGB Nodes per String"));
        StaticText_Strands->SetLabelText(_("# of Strands per String"));
        SpinCtrl_parm3->Enable(true);
    }
}


void ModelDialog::OnChoice_DisplayAsSelect(wxCommandEvent& event)
{
    UpdateLabels();
}
