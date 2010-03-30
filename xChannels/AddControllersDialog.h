#ifndef ADDCONTROLLERSDIALOG_H
#define ADDCONTROLLERSDIALOG_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(AddControllersDialog)
	#include <wx/sizer.h>
	#include <wx/stattext.h>
	#include <wx/button.h>
	#include <wx/dialog.h>
	//*)
#endif
//(*Headers(AddControllersDialog)
#include <wx/spinctrl.h>
//*)

class AddControllersDialog: public wxDialog
{
	public:

		AddControllersDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~AddControllersDialog();

		//(*Declarations(AddControllersDialog)
		wxStaticText* StaticText2;
		wxButton* ButtonOK;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxButton* ButtonCancel;
		wxSpinCtrl* SpinFirstController;
		wxSpinCtrl* SpinChannelsPerController;
		wxSpinCtrl* SpinNumControllers;
		//*)

	protected:

		//(*Identifiers(AddControllersDialog)
		static const long ID_STATICTEXT1;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_SPINCTRL2;
		static const long ID_STATICTEXT3;
		static const long ID_SPINCTRL3;
		//*)

	private:

		//(*Handlers(AddControllersDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
