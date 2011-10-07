#ifndef WIZARDDIALOG_H
#define WIZARDDIALOG_H

//(*Headers(WizardDialog)
#include <wx/sizer.h>
#include <wx/checkbox.h>
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
		wxCheckBox* CheckBoxLastItem;
		wxCheckBox* CheckBoxRandom;
		//*)

	protected:

		//(*Identifiers(WizardDialog)
		static const long ID_CHECKBOX_REPEAT;
		static const long ID_CHECKBOX_FIRSTITEM;
		static const long ID_CHECKBOX_LASTITEM;
		static const long ID_CHECKBOX_RANDOM;
		//*)

	private:

		//(*Handlers(WizardDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
