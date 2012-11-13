#ifndef ADDSHOWDIALOG_H
#define ADDSHOWDIALOG_H

//(*Headers(AddShowDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/listbox.h>
#include <wx/spinctrl.h>
#include <wx/choice.h>
#include <wx/dialog.h>
//*)

class AddShowDialog: public wxDialog
{
	public:

		AddShowDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~AddShowDialog();
		bool StartBeforeEnd();
        bool IsPlaylistSelected();
		wxString PartialEventCode();

		//(*Declarations(AddShowDialog)
		wxStaticText* StaticText10;
		wxStaticText* StaticText9;
		wxCheckBox* CheckBoxFirstItem;
		wxCheckBox* CheckBoxRepeat;
		wxStaticText* StaticText2;
		wxStaticText* StaticText6;
		wxStaticText* StaticText8;
		wxListBox* ListBoxDates;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxSpinCtrl* SpinCtrlEndMinute;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
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
		static const long ID_STATICTEXT10;
		static const long ID_LISTBOX1;
		//*)

	private:

		//(*Handlers(AddShowDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
