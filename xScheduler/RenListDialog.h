#ifndef RENLISTDIALOG_H
#define RENLISTDIALOG_H

//(*Headers(RenListDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/dialog.h>
//*)

class RenListDialog: public wxDialog
{
	public:

		RenListDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~RenListDialog();

		//(*Declarations(RenListDialog)
		wxTextCtrl* TextCtrlRename;
		wxStaticText* StaticText1;
		wxStaticLine* StaticLine1;
		//*)

	protected:

		//(*Identifiers(RenListDialog)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL_RENAME;
		static const long ID_STATICLINE1;
		//*)

	private:

		//(*Handlers(RenListDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
