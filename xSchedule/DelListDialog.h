#ifndef DELLISTDIALOG_H
#define DELLISTDIALOG_H

//(*Headers(DelListDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/dialog.h>
//*)

class DelListDialog: public wxDialog
{
	public:

		DelListDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~DelListDialog();

		//(*Declarations(DelListDialog)
		wxStaticText* StaticTextDelName;
		wxStaticText* StaticText1;
		wxStaticLine* StaticLine1;
		//*)

	protected:

		//(*Identifiers(DelListDialog)
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT_DELNAME;
		static const long ID_STATICLINE1;
		//*)

	private:

		//(*Handlers(DelListDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
