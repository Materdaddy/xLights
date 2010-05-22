#ifndef PLAYERDIALOG_H
#define PLAYERDIALOG_H

//(*Headers(PlayerDialog)
#include <wx/dialog.h>
//*)

#include "wx/timer.h"       //timer for updating status bar
#include "wx/mediactrl.h"   //for wxMediaCtrl

// ----------------------------------------------------------------------------
// wxMediaPlayerTimer
// ----------------------------------------------------------------------------

class wxMediaPlayerTimer : public wxTimer
{
public:
    //Ctor
    //wxMediaPlayerTimer(wxMediaPlayerFrame* frame) {m_frame = frame;}

    //Called each time the timer's timeout expires
    void Notify();

    //wxMediaPlayerFrame* m_frame;       //The wxMediaPlayerFrame
};



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
		//*)

		static const long wxID_MEDIACTRL;
		wxMediaPlayerTimer* m_timer;

		DECLARE_EVENT_TABLE()
};

#endif
