#ifndef LORMAPDIALOG_H
#define LORMAPDIALOG_H

//(*Headers(LorMapDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobut.h>
#include <wx/dialog.h>
//*)

class LorMapDialog: public wxDialog
{
	public:

		LorMapDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~LorMapDialog();

		//(*Declarations(LorMapDialog)
		wxRadioButton* RadioButtonMultiNetwork;
		wxRadioButton* RadioButtonStrictMap;
		wxStaticText* StaticText2;
		wxRadioButton* RadioButtonSingleNetwork;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
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
