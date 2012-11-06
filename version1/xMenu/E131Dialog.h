#ifndef E131DIALOG_H
#define E131DIALOG_H

//(*Headers(E131Dialog)
#include <wx/spinctrl.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/radiobut.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class E131Dialog: public wxDialog
{
	public:

		E131Dialog(wxWindow* parent,const wxString& title);
		virtual ~E131Dialog();

		//(*Declarations(E131Dialog)
		wxTextCtrl* TextCtrlIpAddr;
		wxRadioButton* RadioButtonMulticast;
		wxSpinCtrl* SpinCtrl_NumUniv;
		wxRadioButton* RadioButtonUnicast;
		wxSpinCtrl* SpinCtrl_StartUniv;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		wxStaticText* StaticText5;
		wxStaticText* StaticText2;
		//*)

	protected:

		//(*Identifiers(E131Dialog)
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_RADIOBUTTON1;
		static const long ID_RADIOBUTTON2;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL_IP_ADDR;
		static const long ID_STATICTEXT2;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT3;
		static const long ID_SPINCTRL2;
		//*)

	private:

		//(*Handlers(E131Dialog)
		void OnRadioButtonUnicastSelect(wxCommandEvent& event);
		void OnRadioButtonMulticastSelect(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
