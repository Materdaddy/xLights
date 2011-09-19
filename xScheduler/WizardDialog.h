#ifndef WIZARDDIALOG_H
#define WIZARDDIALOG_H

//(*Headers(WizardDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/dialog.h>
//*)

class WizardDialog: public wxDialog
{
	public:

		WizardDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~WizardDialog();

		//(*Declarations(WizardDialog)
		wxCheckBox* CheckBoxFirstItem;
		wxCheckBox* CheckBoxRepeat;
		wxStaticText* StaticText1;
		wxCheckBox* CheckBoxLastItem;
		wxCheckBox* CheckBoxLightsOff;
		wxChoice* ChoicePlayList;
		//*)

	protected:

		//(*Identifiers(WizardDialog)
		static const long ID_STATICTEXT1;
		static const long ID_CHOICE_PLAYLIST;
		static const long ID_CHECKBOX_REPEAT;
		static const long ID_CHECKBOX_FIRSTITEM;
		static const long ID_CHECKBOX_LASTITEM;
		static const long ID_CHECKBOX_LIGHTSOFF;
		//*)

	private:

		//(*Handlers(WizardDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
