#ifndef STOPDIALOG_H
#define STOPDIALOG_H

//(*Headers(StopDialog)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/radiobut.h>
#include <wx/stattext.h>
//*)

class StopDialog: public wxDialog
{
	public:

		StopDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~StopDialog();
        bool StopImmediately();

		//(*Declarations(StopDialog)
		wxRadioButton* RadioButtonImmediate;
		wxStaticText* StaticText1;
		wxRadioButton* RadioButtonWait;
		wxStaticText* StaticText2;
		//*)

	protected:

		//(*Identifiers(StopDialog)
		static const long ID_STATICTEXT1;
		static const long ID_RADIOBUTTON_IMMEDIATE;
		static const long ID_RADIOBUTTON_WAIT;
		static const long ID_STATICTEXT2;
		//*)

	private:

		//(*Handlers(StopDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
