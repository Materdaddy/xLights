#include "SeqParmsDialog.h"

//(*InternalHeaders(SeqParmsDialog)
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(SeqParmsDialog)
const long SeqParmsDialog::ID_STATICTEXT_FILENAME = wxNewId();
const long SeqParmsDialog::ID_CHECKLISTBOX1 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT1 = wxNewId();
const long SeqParmsDialog::ID_SPINCTRL_BASE_CHANNEL = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT5 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH0 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT2 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH1 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT4 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH2 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT6 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH3 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT21 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH4 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT8 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH5 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT10 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH6 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT12 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH7 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT15 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH8 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT17 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH9 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT19 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH10 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT20 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH11 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT25 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH12 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT27 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH13 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT29 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH14 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT31 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH15 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT33 = wxNewId();
const long SeqParmsDialog::ID_STATICTEXT_CH16 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SeqParmsDialog,wxDialog)
	//(*EventTable(SeqParmsDialog)
	//*)
END_EVENT_TABLE()

SeqParmsDialog::SeqParmsDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(SeqParmsDialog)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, id, _("RGB Sequence Information"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	FlexGridSizer1->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_Filename = new wxStaticText(this, ID_STATICTEXT_FILENAME, _("Filename"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_FILENAME"));
	FlexGridSizer1->Add(StaticText_Filename, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 10);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Models to Include"));
	CheckListBox1 = new wxCheckListBox(this, ID_CHECKLISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, wxLB_SORT, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
	StaticBoxSizer1->Add(CheckListBox1, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Control Channels"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Base channel"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer3->Add(StaticText1, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SpinCtrlBaseChannel = new wxSpinCtrl(this, ID_SPINCTRL_BASE_CHANNEL, _T("1"), wxDefaultPosition, wxDefaultSize, 0, 1, 99999, 1, _T("ID_SPINCTRL_BASE_CHANNEL"));
	SpinCtrlBaseChannel->SetValue(_T("1"));
	FlexGridSizer3->Add(SpinCtrlBaseChannel, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Timing Channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer3->Add(StaticText5, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH0 = new wxStaticText(this, ID_STATICTEXT_CH0, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH0"));
	FlexGridSizer3->Add(StaticText_CH0, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Intensity Channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer3->Add(StaticText2, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH1 = new wxStaticText(this, ID_STATICTEXT_CH1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH1"));
	FlexGridSizer3->Add(StaticText_CH1, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Speed Channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer3->Add(StaticText4, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH2 = new wxStaticText(this, ID_STATICTEXT_CH2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH2"));
	FlexGridSizer3->Add(StaticText_CH2, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Sparkle Channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer3->Add(StaticText6, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH3 = new wxStaticText(this, ID_STATICTEXT_CH3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH3"));
	FlexGridSizer3->Add(StaticText_CH3, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText21 = new wxStaticText(this, ID_STATICTEXT21, _("Meteor Trigger:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
	FlexGridSizer3->Add(StaticText21, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH4 = new wxStaticText(this, ID_STATICTEXT_CH4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH4"));
	FlexGridSizer3->Add(StaticText_CH4, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Eff 1-Color 1:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer3->Add(StaticText8, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH5 = new wxStaticText(this, ID_STATICTEXT_CH5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH5"));
	FlexGridSizer3->Add(StaticText_CH5, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Eff 1-Color 2:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer3->Add(StaticText10, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH6 = new wxStaticText(this, ID_STATICTEXT_CH6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH6"));
	FlexGridSizer3->Add(StaticText_CH6, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Eff 1-Color 3:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer3->Add(StaticText12, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH7 = new wxStaticText(this, ID_STATICTEXT_CH7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH7"));
	FlexGridSizer3->Add(StaticText_CH7, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _("Eff 1-Color 4:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer3->Add(StaticText15, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH8 = new wxStaticText(this, ID_STATICTEXT_CH8, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH8"));
	FlexGridSizer3->Add(StaticText_CH8, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT17, _("Eff 1-Color 5:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	FlexGridSizer3->Add(StaticText17, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH9 = new wxStaticText(this, ID_STATICTEXT_CH9, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH9"));
	FlexGridSizer3->Add(StaticText_CH9, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText19 = new wxStaticText(this, ID_STATICTEXT19, _("Eff 1-Color 6:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	FlexGridSizer3->Add(StaticText19, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH10 = new wxStaticText(this, ID_STATICTEXT_CH10, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH10"));
	FlexGridSizer3->Add(StaticText_CH10, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText20 = new wxStaticText(this, ID_STATICTEXT20, _("Eff 2-Color 1:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	FlexGridSizer3->Add(StaticText20, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH11 = new wxStaticText(this, ID_STATICTEXT_CH11, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH11"));
	FlexGridSizer3->Add(StaticText_CH11, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText25 = new wxStaticText(this, ID_STATICTEXT25, _("Eff 2-Color 2:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
	FlexGridSizer3->Add(StaticText25, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH12 = new wxStaticText(this, ID_STATICTEXT_CH12, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH12"));
	FlexGridSizer3->Add(StaticText_CH12, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText27 = new wxStaticText(this, ID_STATICTEXT27, _("Eff 2-Color 3:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
	FlexGridSizer3->Add(StaticText27, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH13 = new wxStaticText(this, ID_STATICTEXT_CH13, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH13"));
	FlexGridSizer3->Add(StaticText_CH13, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText29 = new wxStaticText(this, ID_STATICTEXT29, _("Eff 2-Color 4:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
	FlexGridSizer3->Add(StaticText29, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH14 = new wxStaticText(this, ID_STATICTEXT_CH14, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH14"));
	FlexGridSizer3->Add(StaticText_CH14, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText31 = new wxStaticText(this, ID_STATICTEXT31, _("Eff 2-Color 5:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT31"));
	FlexGridSizer3->Add(StaticText31, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH15 = new wxStaticText(this, ID_STATICTEXT_CH15, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH15"));
	FlexGridSizer3->Add(StaticText_CH15, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText33 = new wxStaticText(this, ID_STATICTEXT33, _("Eff 2-Color 6:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT33"));
	FlexGridSizer3->Add(StaticText33, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText_CH16 = new wxStaticText(this, ID_STATICTEXT_CH16, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_CH16"));
	FlexGridSizer3->Add(StaticText_CH16, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer3, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_SPINCTRL_BASE_CHANNEL,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&SeqParmsDialog::OnSpinCtrlBaseChannelChange);
	//*)
    NetInfo=0;
}

SeqParmsDialog::~SeqParmsDialog()
{
	//(*Destroy(SeqParmsDialog)
	//*)
}


void SeqParmsDialog::SetChannelNames()
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

void SeqParmsDialog::SetNetInfo(NetInfoClass* NetInfoPtr)
{
    NetInfo=NetInfoPtr;
	SetChannelNames();
}

void SeqParmsDialog::OnSpinCtrlBaseChannelChange(wxSpinEvent& event)
{
    SetChannelNames();
}
