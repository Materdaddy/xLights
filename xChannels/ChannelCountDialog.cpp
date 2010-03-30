#include "wx_pch.h"
#include "ChannelCountDialog.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(ChannelCountDialog)
	#include <wx/intl.h>
	#include <wx/string.h>
	//*)
#endif
//(*InternalHeaders(ChannelCountDialog)
//*)

//(*IdInit(ChannelCountDialog)
const long ChannelCountDialog::ID_STATICTEXT1 = wxNewId();
const long ChannelCountDialog::ID_SPINCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ChannelCountDialog,wxDialog)
	//(*EventTable(ChannelCountDialog)
	//*)
END_EVENT_TABLE()

ChannelCountDialog::ChannelCountDialog(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(ChannelCountDialog)
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("Channel Count"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Number of channels:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SpinNumberChannels = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL1"));
	SpinNumberChannels->SetValue(_T("0"));
	FlexGridSizer1->Add(SpinNumberChannels, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonOK = new wxButton(this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	ButtonOK->SetDefault();
	FlexGridSizer1->Add(ButtonOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonCancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	FlexGridSizer1->Add(ButtonCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	//*)
}

ChannelCountDialog::~ChannelCountDialog()
{
	//(*Destroy(ChannelCountDialog)
	//*)
}


