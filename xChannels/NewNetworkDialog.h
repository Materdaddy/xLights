#ifndef NEWNETWORKDIALOG_H
#define NEWNETWORKDIALOG_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(NewNetworkDialog)
	#include <wx/sizer.h>
	#include <wx/choice.h>
	#include <wx/button.h>
	#include <wx/dialog.h>
	//*)
#endif
//(*Headers(NewNetworkDialog)
//*)

class NewNetworkDialog: public wxDialog
{
	public:

		NewNetworkDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~NewNetworkDialog();

		//(*Declarations(NewNetworkDialog)
		wxButton* ButtonOK;
		wxChoice* ChoicePort;
		wxButton* ButtonCancel;
		wxChoice* ChoiceNetwork;
		wxChoice* ChoiceBaudRate;
		//*)

	protected:

		//(*Identifiers(NewNetworkDialog)
		static const long ID_CHOICE_NETWORK;
		static const long ID_CHOICE_PORT;
		static const long ID_CHOICE_BAUDRATE;
		//*)

	private:

		//(*Handlers(NewNetworkDialog)
		void OnButtonOKClick(wxCommandEvent& event);
		void OnChoiceBaudRateSelect(wxCommandEvent& event);
		//*)

		void PopulatePortChooser(wxChoice *chooser);

		DECLARE_EVENT_TABLE()
};

#endif
