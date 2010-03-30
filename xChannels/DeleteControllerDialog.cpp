#include "wx_pch.h"
#include "DeleteControllerDialog.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(DeleteControllerDialog)
	#include <wx/intl.h>
	#include <wx/string.h>
	//*)
#endif
//(*InternalHeaders(DeleteControllerDialog)
//*)

//(*IdInit(DeleteControllerDialog)
const long DeleteControllerDialog::ID_STATICTEXT1 = wxNewId();
const long DeleteControllerDialog::ID_CHOICE_CONTROLLER = wxNewId();
//*)

BEGIN_EVENT_TABLE(DeleteControllerDialog,wxDialog)
	//(*EventTable(DeleteControllerDialog)
	//*)
END_EVENT_TABLE()

DeleteControllerDialog::DeleteControllerDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(DeleteControllerDialog)
	wxFlexGridSizer* FlexGridSizer1;
	
	Create(parent, id, _("Delete a Controller"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Select controller to delete"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ChoiceController = new wxChoice(this, ID_CHOICE_CONTROLLER, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_CONTROLLER"));
	FlexGridSizer1->Add(ChoiceController, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonOK = new wxButton(this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	FlexGridSizer1->Add(ButtonOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonCancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	FlexGridSizer1->Add(ButtonCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	//*)
}

DeleteControllerDialog::~DeleteControllerDialog()
{
	//(*Destroy(DeleteControllerDialog)
	//*)
}

