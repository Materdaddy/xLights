#ifndef PLAYERFRAME_H
#define PLAYERFRAME_H

//(*Headers(PlayerFrame)
#include <wx/frame.h>
//*)

#include <wx/mediactrl.h>   //for wxMediaCtrl

class PlayerFrame: public wxFrame
{
	public:

		PlayerFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~PlayerFrame();
        wxMediaCtrl* MediaCtrl;

        // Media event handlers
        //void OnMediaPlay(wxMediaEvent& event);
        //void OnMediaPause(wxMediaEvent& event);
        //void OnMediaStop(wxMediaEvent& event);
        void OnMediaFinished(wxMediaEvent& event);
        void OnMediaLoaded(wxMediaEvent& event);

		//(*Declarations(PlayerFrame)
		//*)

	protected:

		//(*Identifiers(PlayerFrame)
		//*)

	private:

		//(*Handlers(PlayerFrame)
		void OnClose(wxCloseEvent& event);
		//*)

		static const long wxID_MEDIACTRL;

		DECLARE_EVENT_TABLE()
};

#endif
