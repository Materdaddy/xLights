#ifndef DELETECONTROLLERDIALOG_H
#define DELETECONTROLLERDIALOG_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(DeleteControllerDialog)
	#include <wx/sizer.h>
	#include <wx/stattext.h>
	#include <wx/choice.h>
	#include <wx/button.h>
	#include <wx/dialog.h>
	//*)
#endif
//(*Headers(DeleteControllerDialog)
//*)

class DeleteControllerDialog: public wxDialog
{
	public:

		DeleteControllerDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~DeleteControllerDialog();

		//(*Declarations(DeleteControllerDialog)
		wxButton* ButtonOK;
		wxStaticText* StaticText1;
		wxChoice* ChoiceController;
		wxButton* ButtonCancel;
		//*)

	protected:

		//(*Identifiers(DeleteControllerDialog)
		static const long ID_STATICTEXT1;
		static const long ID_CHOICE_CONTROLLER;
		//*)

	private:

		//(*Handlers(DeleteControllerDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
