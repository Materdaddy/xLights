#ifndef E131DIALOG_H
#define E131DIALOG_H

//(*Headers(E131Dialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/dialog.h>
//*)

class E131Dialog: public wxDialog
{
	public:

		E131Dialog(wxWindow* parent,const wxString& title);
		virtual ~E131Dialog();

		//(*Declarations(E131Dialog)
		wxTextCtrl* TextCtrlIpAddr;
		wxStaticText* StaticText2;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxTextCtrl* TextCtrlLastChannel;
		wxStaticText* StaticText4;
		wxTextCtrl* TextCtrlUniverse;
		//*)

	protected:

		//(*Identifiers(E131Dialog)
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL_IP_ADDR;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL_UNIVERSE;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL_LAST_CHANNEL;
		//*)

	private:

		//(*Handlers(E131Dialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
