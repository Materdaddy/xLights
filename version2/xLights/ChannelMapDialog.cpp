#include "ChannelMapDialog.h"

//(*InternalHeaders(ChannelMapDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(ChannelMapDialog)
const long ChannelMapDialog::ID_STATICTEXT1 = wxNewId();
const long ChannelMapDialog::ID_SPINCTRL_BASE_CHANNEL = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT5 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH0 = wxNewId();
const long ChannelMapDialog::ID_BUTTON1 = wxNewId();
const long ChannelMapDialog::ID_CHECKBOX_ENABLE_BASIC = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT2 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH1 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT4 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH2 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT6 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH3 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT21 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH4 = wxNewId();
const long ChannelMapDialog::ID_CHECKBOX_ENABLE_COLOR = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT8 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH5 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT10 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH6 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT12 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH7 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT15 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH8 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT17 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH9 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT19 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH10 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT20 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH11 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT25 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH12 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT27 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH13 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT29 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH14 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT31 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH15 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT33 = wxNewId();
const long ChannelMapDialog::ID_STATICTEXT_CH16 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ChannelMapDialog,wxDialog)
	//(*EventTable(ChannelMapDialog)
	//*)
END_EVENT_TABLE()

ChannelMapDialog::ChannelMapDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(ChannelMapDialog)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxBoxSizer* BoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, id, _("RGB Sequence Channel Map"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	FlexGridSizer1->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Base channel"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SpinCtrlBaseChannel = new wxSpinCtrl(this, ID_SPINCTRL_BASE_CHANNEL, _T("1"), wxDefaultPosition, wxDefaultSize, 0, 1, 99999, 1, _T("ID_SPINCTRL_BASE_CHANNEL"));
	SpinCtrlBaseChannel->SetValue(_T("1"));
	FlexGridSizer2->Add(SpinCtrlBaseChannel, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Timing Channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	StaticText5->SetToolTip(_("During timing import, off-to-on transitions will causing timing rows to be generated in the sequence grid"));
	FlexGridSizer4->Add(StaticText5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH0 = new wxStaticText(this, ID_STATICTEXT_CH0, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH0"));
	StaticText_CH0->SetMinSize(wxSize(120,-1));
	FlexGridSizer4->Add(StaticText_CH0, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonImportTiming = new wxButton(this, ID_BUTTON1, _("Import Timing"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer4->Add(ButtonImportTiming, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Basic Control"));
	FlexGridSizer5 = new wxFlexGridSizer(0, 2, 0, 0);
	CheckBox_EnableBasic = new wxCheckBox(this, ID_CHECKBOX_ENABLE_BASIC, _("Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_ENABLE_BASIC"));
	CheckBox_EnableBasic->SetValue(false);
	FlexGridSizer5->Add(CheckBox_EnableBasic, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Intensity Channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticText2->SetToolTip(_("255 or 100% keeps original intensity, 50% lowers original intensity by half"));
	FlexGridSizer5->Add(StaticText2, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH1 = new wxStaticText(this, ID_STATICTEXT_CH1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH1"));
	StaticText_CH1->SetMinSize(wxSize(120,-1));
	FlexGridSizer5->Add(StaticText_CH1, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Speed Channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	StaticText4->SetToolTip(_("Throttles original speed setting of effect. 100% keeps the original speed, 50% lowers it by half."));
	FlexGridSizer5->Add(StaticText4, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH2 = new wxStaticText(this, ID_STATICTEXT_CH2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH2"));
	StaticText_CH2->SetMinSize(wxSize(120,-1));
	FlexGridSizer5->Add(StaticText_CH2, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Sparkle Channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	StaticText6->SetToolTip(_("Overrides the original sparkle setting"));
	FlexGridSizer5->Add(StaticText6, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH3 = new wxStaticText(this, ID_STATICTEXT_CH3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH3"));
	StaticText_CH3->SetMinSize(wxSize(120,-1));
	FlexGridSizer5->Add(StaticText_CH3, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText21 = new wxStaticText(this, ID_STATICTEXT21, _("Meteor Trigger:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
	StaticText21->SetToolTip(_("For meteor effect, this will cause meteors to be created only when this channel is on."));
	FlexGridSizer5->Add(StaticText21, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH4 = new wxStaticText(this, ID_STATICTEXT_CH4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH4"));
	StaticText_CH4->SetMinSize(wxSize(120,-1));
	FlexGridSizer5->Add(StaticText_CH4, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer5, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	BoxSizer1->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Color Control"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
	CheckBox_EnableColor = new wxCheckBox(this, ID_CHECKBOX_ENABLE_COLOR, _("Enable"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_ENABLE_COLOR"));
	CheckBox_EnableColor->SetValue(false);
	FlexGridSizer3->Add(CheckBox_EnableColor, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Eff 1-Color 1:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	StaticText8->SetToolTip(_("Overrides the checkbox for effect 1, color 1"));
	FlexGridSizer3->Add(StaticText8, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH5 = new wxStaticText(this, ID_STATICTEXT_CH5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH5"));
	StaticText_CH5->SetMinSize(wxSize(120,-1));
	FlexGridSizer3->Add(StaticText_CH5, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Eff 1-Color 2:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	StaticText10->SetToolTip(_("Overrides the checkbox for effect 1, color 2"));
	FlexGridSizer3->Add(StaticText10, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH6 = new wxStaticText(this, ID_STATICTEXT_CH6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH6"));
	StaticText_CH6->SetMinSize(wxSize(120,-1));
	FlexGridSizer3->Add(StaticText_CH6, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Eff 1-Color 3:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	StaticText12->SetToolTip(_("Overrides the checkbox for effect 1, color 3"));
	FlexGridSizer3->Add(StaticText12, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH7 = new wxStaticText(this, ID_STATICTEXT_CH7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH7"));
	StaticText_CH7->SetMinSize(wxSize(120,-1));
	FlexGridSizer3->Add(StaticText_CH7, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("Eff 1-Color 4:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	StaticText15->SetToolTip(_("Overrides the checkbox for effect 1, color 4"));
	FlexGridSizer3->Add(StaticText15, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH8 = new wxStaticText(this, ID_STATICTEXT_CH8, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH8"));
	StaticText_CH8->SetMinSize(wxSize(120,-1));
	FlexGridSizer3->Add(StaticText_CH8, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("Eff 1-Color 5:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	StaticText17->SetToolTip(_("Overrides the checkbox for effect 1, color 5"));
	FlexGridSizer3->Add(StaticText17, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH9 = new wxStaticText(this, ID_STATICTEXT_CH9, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH9"));
	StaticText_CH9->SetMinSize(wxSize(120,-1));
	FlexGridSizer3->Add(StaticText_CH9, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText19 = new wxStaticText(this, ID_STATICTEXT19, _("Eff 1-Color 6:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	StaticText19->SetToolTip(_("Overrides the checkbox for effect 1, color 6"));
	FlexGridSizer3->Add(StaticText19, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH10 = new wxStaticText(this, ID_STATICTEXT_CH10, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH10"));
	StaticText_CH10->SetMinSize(wxSize(120,-1));
	FlexGridSizer3->Add(StaticText_CH10, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText20 = new wxStaticText(this, ID_STATICTEXT20, _("Eff 2-Color 1:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	StaticText20->SetToolTip(_("Overrides the checkbox for effect 2, color 1"));
	FlexGridSizer3->Add(StaticText20, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH11 = new wxStaticText(this, ID_STATICTEXT_CH11, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH11"));
	StaticText_CH11->SetMinSize(wxSize(120,-1));
	FlexGridSizer3->Add(StaticText_CH11, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText25 = new wxStaticText(this, ID_STATICTEXT25, _("Eff 2-Color 2:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
	StaticText25->SetToolTip(_("Overrides the checkbox for effect 2, color 2"));
	FlexGridSizer3->Add(StaticText25, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH12 = new wxStaticText(this, ID_STATICTEXT_CH12, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH12"));
	StaticText_CH12->SetMinSize(wxSize(120,-1));
	FlexGridSizer3->Add(StaticText_CH12, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText27 = new wxStaticText(this, ID_STATICTEXT27, _("Eff 2-Color 3:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
	StaticText27->SetToolTip(_("Overrides the checkbox for effect 2, color 3"));
	FlexGridSizer3->Add(StaticText27, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH13 = new wxStaticText(this, ID_STATICTEXT_CH13, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH13"));
	StaticText_CH13->SetMinSize(wxSize(120,-1));
	FlexGridSizer3->Add(StaticText_CH13, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText29 = new wxStaticText(this, ID_STATICTEXT29, _("Eff 2-Color 4:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
	StaticText29->SetToolTip(_("Overrides the checkbox for effect 2, color 4"));
	FlexGridSizer3->Add(StaticText29, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH14 = new wxStaticText(this, ID_STATICTEXT_CH14, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH14"));
	StaticText_CH14->SetMinSize(wxSize(120,-1));
	FlexGridSizer3->Add(StaticText_CH14, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText31 = new wxStaticText(this, ID_STATICTEXT31, _("Eff 2-Color 5:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT31"));
	StaticText31->SetToolTip(_("Overrides the checkbox for effect 2, color 5"));
	FlexGridSizer3->Add(StaticText31, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH15 = new wxStaticText(this, ID_STATICTEXT_CH15, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH15"));
	StaticText_CH15->SetMinSize(wxSize(120,-1));
	FlexGridSizer3->Add(StaticText_CH15, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText33 = new wxStaticText(this, ID_STATICTEXT33, _("Eff 2-Color 6:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT33"));
	StaticText33->SetToolTip(_("Overrides the checkbox for effect 2, color 6"));
	FlexGridSizer3->Add(StaticText33, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH16 = new wxStaticText(this, ID_STATICTEXT_CH16, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH16"));
	StaticText_CH16->SetMinSize(wxSize(120,-1));
	FlexGridSizer3->Add(StaticText_CH16, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer3, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	BoxSizer1->Add(StaticBoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_SPINCTRL_BASE_CHANNEL,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&ChannelMapDialog::OnSpinCtrlBaseChannelChange);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ChannelMapDialog::OnButtonImportTimingClick);
	//*)
    NetInfo=0;
}

ChannelMapDialog::~ChannelMapDialog()
{
	//(*Destroy(ChannelMapDialog)
	//*)
}

void ChannelMapDialog::SetChannelNames()
{
    wxASSERT(NetInfo);
    wxString name;
    int BaseChannel=SpinCtrlBaseChannel->GetValue();
    for(int i=0; i<=16; i++) {
        wxStaticText* TextWin=(wxStaticText*)wxWindow::FindWindowByName(wxString::Format(wxT("ID_STATICTEXT_CH%d"),i));
        name=NetInfo->GetChannelName(BaseChannel-1+i);
        if (TextWin) TextWin->SetLabel(name);
    }
}

void ChannelMapDialog::SetNetInfo(NetInfoClass* NetInfoPtr)
{
    NetInfo=NetInfoPtr;
	SetChannelNames();
}

void ChannelMapDialog::OnSpinCtrlBaseChannelChange(wxSpinEvent& event)
{
    SetChannelNames();
}

void ChannelMapDialog::OnButtonImportTimingClick(wxCommandEvent& event)
{
}
