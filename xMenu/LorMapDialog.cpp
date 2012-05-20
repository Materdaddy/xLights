#include "LorMapDialog.h"

//(*InternalHeaders(LorMapDialog)
#include <wx/button.h>
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(LorMapDialog)
const long LorMapDialog::ID_RADIOBUTTON_SINGLENET = wxNewId();
const long LorMapDialog::ID_STATICTEXT1 = wxNewId();
const long LorMapDialog::ID_RADIOBUTTON2 = wxNewId();
const long LorMapDialog::ID_STATICTEXT2 = wxNewId();
const long LorMapDialog::ID_RADIOBUTTON_STRICT_MAP = wxNewId();
const long LorMapDialog::ID_STATICTEXT3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(LorMapDialog,wxDialog)
	//(*EventTable(LorMapDialog)
	//*)
END_EVENT_TABLE()

LorMapDialog::LorMapDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(LorMapDialog)
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;
	
	Create(parent, id, _("LOR Sequence Channel Mapping"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	RadioButtonSingleNetwork = new wxRadioButton(this, ID_RADIOBUTTON_SINGLENET, _("Single Network"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP, wxDefaultValidator, _T("ID_RADIOBUTTON_SINGLENET"));
	FlexGridSizer2->Add(RadioButtonSingleNetwork, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("All LOR channels are assumed to be on the \"regular\" (default) network.\nIf the first network defined in xLights has 32 channels and the second\nnetwork has 64 channels, then the first 32 channels in the sequence \nwould be mapped to the first xLights network and the next 64 channels \nwould be mapped to the second network. \n\nxLights channel # = ((LOR-Unit-Number - 1) * 16) + LOR-Circuit-Number\n\nBasically, xLights assumes each controller in the LOR sequence has 16 channels. \nHowever, you can use circuits 1-32 on unit x if you don\'t define unit x+1 in your \nsequence. If you have a CCR, which uses circuits 1-150, on unit 10 (0A hex), the \nnext unit number you could use is 20 (14 hex) - 10 units/160 channels are then \nreserved for the CCR.\n"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonMultiNetwork = new wxRadioButton(this, ID_RADIOBUTTON2, _("Multi-Network"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	FlexGridSizer2->Add(RadioButtonMultiNetwork, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("The \"regular\" (default) network in the LOR sequence is mapped to the \nfirst network defined in xLights. The \"Aux A\" network in LOR is mapped \nto the second network in xLights, etc.\n\nChannel numbering is the same as Single Network mode.\n"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	RadioButtonStrictMap = new wxRadioButton(this, ID_RADIOBUTTON_STRICT_MAP, _("Strict Mapping"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON_STRICT_MAP"));
	RadioButtonStrictMap->Disable();
	RadioButtonStrictMap->Hide();
	FlexGridSizer2->Add(RadioButtonStrictMap, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("NOT IMPLEMENTED YET\n\nThe \"regular\" (default) network in the LOR sequence is mapped to the \nfirst network defined in xLights. The \"Aux A\" network in LOR is mapped \nto the second network in xLights, etc.\n\nWhen the xLights network is an LOR network, then unit and circuit \nnumbers are preserved. For other types of networks, channel\nnumbering is the same as Single Network mode.\n\nVixen playback is not supported in this mode.\n"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	StaticText3->Hide();
	FlexGridSizer2->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
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

LorMapDialog::~LorMapDialog()
{
	//(*Destroy(LorMapDialog)
	//*)
}

