#ifndef PLAYERDIALOG_H
#define PLAYERDIALOG_H

//(*Headers(PlayerDialog)
#include <wx/dialog.h>
//*)

#include "wx/timer.h"       //timer for updating status bar
#include "wx/mediactrl.h"   //for wxMediaCtrl

class PlayerDialog: public wxDialog
{
	public:

		PlayerDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~PlayerDialog();
        wxMediaCtrl* MediaCtrl;

        // Media event handlers
        void OnMediaPlay(wxMediaEvent& event);
        void OnMediaPause(wxMediaEvent& event);
        void OnMediaStop(wxMediaEvent& event);
        void OnMediaFinished(wxMediaEvent& event);
        void OnMediaLoaded(wxMediaEvent& event);

		//(*Declarations(PlayerDialog)
		//*)

	protected:

		//(*Identifiers(PlayerDialog)
		//*)

	private:

		//(*Handlers(PlayerDialog)
		void OnClose(wxCloseEvent& event);
		void OnInit(wxInitDialogEvent& event);
		//*)

		static const long wxID_MEDIACTRL;

		DECLARE_EVENT_TABLE()
};

#endif
