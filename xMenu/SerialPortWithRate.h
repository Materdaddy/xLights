#ifndef SERIALPORTWITHRATE_H
#define SERIALPORTWITHRATE_H

//(*Headers(SerialPortWithRate)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/dialog.h>
//*)

class SerialPortWithRate: public wxDialog
{
	public:

		SerialPortWithRate(wxWindow* parent,const wxString& title);
		virtual ~SerialPortWithRate();

		//(*Declarations(SerialPortWithRate)
		wxStaticText* StaticTextRate;
		wxChoice* ChoicePort;
		wxStaticText* StaticText3;
		wxTextCtrl* TextCtrlLastChannel;
		wxChoice* ChoiceBaudRate;
		wxStaticText* StaticTextPort;
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
