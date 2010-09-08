#ifndef NEWLISTDIALOG_H
#define NEWLISTDIALOG_H

//(*Headers(NewListDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/dialog.h>
//*)

class NewListDialog: public wxDialog
{
	public:

		NewListDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~NewListDialog();

		//(*Declarations(NewListDialog)
		wxTextCtrl* TextCtrlNewName;
		wxStaticText* StaticText1;
		wxStaticLine* StaticLine1;
		//*)

	protected:

		//(*Identifiers(NewListDialog)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL_NEWNAME;
		static const long ID_STATICLINE1;
		//*)

	private:

		//(*Handlers(NewListDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
