#include "wx_pch.h"
#include "AddControllersDialog.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(AddControllersDialog)
	#include <wx/intl.h>
	#include <wx/string.h>
	//*)
#endif
//(*InternalHeaders(AddControllersDialog)
//*)

//(*IdInit(AddControllersDialog)
const long AddControllersDialog::ID_STATICTEXT1 = wxNewId();
const long AddControllersDialog::ID_SPINCTRL1 = wxNewId();
const long AddControllersDialog::ID_STATICTEXT2 = wxNewId();
const long AddControllersDialog::ID_SPINCTRL2 = wxNewId();
const long AddControllersDialog::ID_STATICTEXT3 = wxNewId();
const long AddControllersDialog::ID_SPINCTRL3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(AddControllersDialog,wxDialog)
	//(*EventTable(AddControllersDialog)
	//*)
END_EVENT_TABLE()

AddControllersDialog::AddControllersDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(AddControllersDialog)
	wxGridSizer* GridSizer1;
	
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	GridSizer1 = new wxGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("First Controller Number:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	GridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SpinFirstController = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL1"));
	SpinFirstController->SetValue(_T("0"));
	GridSizer1->Add(SpinFirstController, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Number of Controllers:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	GridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SpinNumControllers = new wxSpinCtrl(this, ID_SPINCTRL2, _T("1"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 1, _T("ID_SPINCTRL2"));
	SpinNumControllers->SetValue(_T("1"));
	GridSizer1->Add(SpinNumControllers, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Channels per controller:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	GridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SpinChannelsPerController = new wxSpinCtrl(this, ID_SPINCTRL3, _T("16"), wxDefaultPosition, wxDefaultSize, 0, 1, 128, 16, _T("ID_SPINCTRL3"));
	SpinChannelsPerController->SetValue(_T("16"));
	GridSizer1->Add(SpinChannelsPerController, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonOK = new wxButton(this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	GridSizer1->Add(ButtonOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonCancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	GridSizer1->Add(ButtonCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(GridSizer1);
	GridSizer1->Fit(this);
	GridSizer1->SetSizeHints(this);
	//*)
}

AddControllersDialog::~AddControllersDialog()
{
	//(*Destroy(AddControllersDialog)
	//*)
}

