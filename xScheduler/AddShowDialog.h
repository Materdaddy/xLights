#ifndef ADDSHOWDIALOG_H
#define ADDSHOWDIALOG_H

//(*Headers(AddShowDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/choice.h>
#include <wx/dialog.h>
//*)

class AddShowDialog: public wxDialog
{
	public:

		AddShowDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~AddShowDialog();

		//(*Declarations(AddShowDialog)
		wxStaticText* StaticText9;
		wxCheckBox* CheckBoxFirstItem;
		wxCheckBox* CheckBoxSu;
		wxCheckBox* CheckBoxRepeat;
		wxStaticText* StaticText2;
		wxStaticText* StaticText6;
		wxCheckBox* CheckBoxFr;
		wxStaticText* StaticText8;
		wxCheckBox* CheckBoxWe;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxSpinCtrl* SpinCtrlEndMinute;
		wxCheckBox* CheckBoxTu;
		wxCheckBox* CheckBoxMo;
		wxCheckBox* CheckBoxSa;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxCheckBox* CheckBoxTh;
		wxSpinCtrl* SpinCtrlStartMinute;
		wxCheckBox* CheckBoxLastItem;
		wxCheckBox* CheckBoxRandom;
		wxSpinCtrl* SpinCtrlStartHour;
		wxChoice* ChoicePlayList;
		wxSpinCtrl* SpinCtrlEndHour;
		wxStaticText* StaticText4;
		//*)

	protected:

		//(*Identifiers(AddShowDialog)
		static const long ID_STATICTEXT1;
		static const long ID_CHOICE_PLAYLIST;
		static const long ID_STATICTEXT5;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT8;
		static const long ID_SPINCTRL2;
		static const long ID_STATICTEXT6;
		static const long ID_SPINCTRL3;
		static const long ID_STATICTEXT9;
		static const long ID_SPINCTRL4;
		static const long ID_STATICTEXT2;
		static const long ID_CHECKBOX_REPEAT;
		static const long ID_STATICTEXT3;
		static const long ID_CHECKBOX_FIRST_ITEM;
		static const long ID_STATICTEXT4;
		static const long ID_CHECKBOX_LAST_ITEM;
		static const long ID_STATICTEXT7;
		static const long ID_CHECKBOX_RANDOM;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX7;
		static const long ID_CHECKBOX_TH;
		static const long ID_CHECKBOX_FR;
		static const long ID_CHECKBOX_SA;
		//*)

	private:

		//(*Handlers(AddShowDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
