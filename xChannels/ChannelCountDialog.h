#ifndef CHANNELCOUNTDIALOG_H
#define CHANNELCOUNTDIALOG_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(ChannelCountDialog)
	#include <wx/sizer.h>
	#include <wx/stattext.h>
	#include <wx/button.h>
	#include <wx/dialog.h>
	//*)
#endif
//(*Headers(ChannelCountDialog)
#include <wx/spinctrl.h>
//*)

class ChannelCountDialog: public wxDialog
{
	public:

		ChannelCountDialog(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~ChannelCountDialog();

		//(*Declarations(ChannelCountDialog)
		wxSpinCtrl* SpinNumberChannels;
		wxButton* ButtonOK;
		wxStaticText* StaticText1;
		wxButton* ButtonCancel;
		//*)

	protected:

		//(*Identifiers(ChannelCountDialog)
		static const long ID_STATICTEXT1;
		static const long ID_SPINCTRL1;
		//*)

	private:

		//(*Handlers(ChannelCountDialog)
		void OnButtonCancelClick(wxCommandEvent& event);
		void OnButtonOKClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
