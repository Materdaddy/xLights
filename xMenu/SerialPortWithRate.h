#ifndef SERIALPORTWITHRATE_H
#define SERIALPORTWITHRATE_H

//(*Headers(SerialPortWithRate)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
//*)

class SerialPortWithRate: public wxDialog
{
	public:

		SerialPortWithRate(wxWindow* parent,const wxString& title);
		virtual ~SerialPortWithRate();

		//(*Declarations(SerialPortWithRate)
		wxStaticText* StaticTextPort;
		wxStaticText* StaticText3;
		wxTextCtrl* TextCtrlLastChannel;
		wxChoice* ChoicePort;
		wxStaticText* StaticTextRate;
		wxChoice* ChoiceBaudRate;
		//*)

	protected:

		//(*Identifiers(SerialPortWithRate)
		static const long ID_STATICTEXT_PORT;
		static const long ID_CHOICE_PORT;
		static const long ID_STATICTEXT_RATE;
		static const long ID_CHOICE_BAUD_RATE;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL_LAST_CHANNEL;
		//*)

	private:

		//(*Handlers(SerialPortWithRate)
		//*)

        void PopulatePortChooser(wxArrayString *chooser);

		DECLARE_EVENT_TABLE()
};

#endif
