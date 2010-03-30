#include "wx_pch.h"
#include "NewNetworkDialog.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(NewNetworkDialog)
	#include <wx/intl.h>
	#include <wx/string.h>
	//*)
#endif
//(*InternalHeaders(NewNetworkDialog)
//*)

//(*IdInit(NewNetworkDialog)
const long NewNetworkDialog::ID_CHOICE_NETWORK = wxNewId();
const long NewNetworkDialog::ID_CHOICE_PORT = wxNewId();
const long NewNetworkDialog::ID_CHOICE_BAUDRATE = wxNewId();
//*)

BEGIN_EVENT_TABLE(NewNetworkDialog,wxDialog)
	//(*EventTable(NewNetworkDialog)
	//*)
END_EVENT_TABLE()

NewNetworkDialog::NewNetworkDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(NewNetworkDialog)
	wxBoxSizer* BoxSizer2;
	wxGridSizer* GridSizer1;
	wxBoxSizer* BoxSizer1;

	Create(parent, id, _("Add Network"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	GridSizer1 = new wxGridSizer(2, 1, 0, 0);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	ChoiceNetwork = new wxChoice(this, ID_CHOICE_NETWORK, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_NETWORK"));
	ChoiceNetwork->SetSelection( ChoiceNetwork->Append(_("Network Type...")) );
	ChoiceNetwork->Append(_("DMX"));
	ChoiceNetwork->Append(_("Renard"));
	ChoiceNetwork->Append(_("LOR/d-Light"));
	BoxSizer1->Add(ChoiceNetwork, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ChoicePort = new wxChoice(this, ID_CHOICE_PORT, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_PORT"));
	ChoicePort->SetSelection( ChoicePort->Append(_("Port...")) );
	BoxSizer1->Add(ChoicePort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ChoiceBaudRate = new wxChoice(this, ID_CHOICE_BAUDRATE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_BAUDRATE"));
	ChoiceBaudRate->SetSelection( ChoiceBaudRate->Append(_("Baud Rate...")) );
	ChoiceBaudRate->Append(_("115200"));
	ChoiceBaudRate->Append(_("57600"));
	ChoiceBaudRate->Append(_("38400"));
	ChoiceBaudRate->Append(_("19200"));
	ChoiceBaudRate->Append(_("9600"));
	BoxSizer1->Add(ChoiceBaudRate, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	ButtonOK = new wxButton(this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	ButtonOK->SetDefault();
	BoxSizer2->Add(ButtonOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonCancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	BoxSizer2->Add(ButtonCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(GridSizer1);
	GridSizer1->Fit(this);
	GridSizer1->SetSizeHints(this);

	Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NewNetworkDialog::OnButtonOKClick);
	//*)

	PopulatePortChooser(ChoicePort);
}

NewNetworkDialog::~NewNetworkDialog()
{
	//(*Destroy(NewNetworkDialog)
	//*)
}


void NewNetworkDialog::OnButtonOKClick(wxCommandEvent& event)
{
    if (ChoiceNetwork->GetSelection() == 0) {
        wxMessageBox(_("Please select the type of lighting network (protocol)."),_("An entry is required"));
    } else if (ChoicePort->GetSelection() == 0) {
        wxMessageBox(_("Please select a serial port (you can always change it later)."),_("An entry is required"));
    } else {
        EndModal(wxID_OK);
    }
}

void NewNetworkDialog::PopulatePortChooser(wxChoice *chooser)
{
#ifdef WIN32
   chooser->Append(_("COM1"));
   chooser->Append(_("COM2"));
   chooser->Append(_("COM3"));
   chooser->Append(_("COM4"));
   chooser->Append(_("COM5"));
   chooser->Append(_("COM6"));
   chooser->Append(_("COM7"));
   chooser->Append(_("COM8"));
   chooser->Append(_("COM9"));
#else
   chooser->Append(_("/dev/ttyS0"));
   chooser->Append(_("/dev/ttyS1"));
   chooser->Append(_("/dev/ttyS2"));
   chooser->Append(_("/dev/ttyS3"));
   chooser->Append(_("/dev/ttyUSB0"));
   chooser->Append(_("/dev/ttyUSB1"));
   chooser->Append(_("/dev/ttyUSB2"));
   chooser->Append(_("/dev/ttyUSB3"));
#endif
}
