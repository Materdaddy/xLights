#ifndef LORMAPDIALOG_H
#define LORMAPDIALOG_H

//(*Headers(LorMapDialog)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/radiobut.h>
#include <wx/stattext.h>
//*)

class LorMapDialog: public wxDialog
{
	public:

		LorMapDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~LorMapDialog();

		//(*Declarations(LorMapDialog)
		wxRadioButton* RadioButtonStrictMap;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxStaticText* StaticText2;
		wxRadioButton* RadioButtonSingleNetwork;
		wxRadioButton* RadioButtonMultiNetwork;
		//*)

	protected:

		//(*Identifiers(LorMapDialog)
		static const long ID_RADIOBUTTON_SINGLENET;
		static const long ID_STATICTEXT1;
		static const long ID_RADIOBUTTON2;
		static const long ID_STATICTEXT2;
		static const long ID_RADIOBUTTON_STRICT_MAP;
		static const long ID_STATICTEXT3;
		//*)

	private:

		//(*Handlers(LorMapDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
