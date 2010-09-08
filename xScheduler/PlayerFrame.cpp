#include "PlayerFrame.h"
#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/icon.h>
#include "../include/xlights.xpm"


//(*InternalHeaders(PlayerFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(PlayerFrame)
//*)

const long PlayerFrame::wxID_MEDIACTRL = wxNewId();

BEGIN_EVENT_TABLE(PlayerFrame,wxFrame)
	//(*EventTable(PlayerFrame)
	//*)
END_EVENT_TABLE()

PlayerFrame::PlayerFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(PlayerFrame)
	Create(parent, id, _("xPlayer"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);

	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&PlayerFrame::OnClose);
	//*)

    SetIcon(wxIcon(xlights_xpm));

    //
    //  Create and attach the sizer
    //
    wxFlexGridSizer* sizer = new wxFlexGridSizer(1);
    this->SetSizer(sizer);
    this->SetAutoLayout(true);
    sizer->AddGrowableRow(0);
    sizer->AddGrowableCol(0);

    //
    //  Create and attach the media control
    //
    MediaCtrl = new wxMediaCtrl();

    //  Make sure creation was successful
    bool bOK = MediaCtrl->Create(this, wxID_MEDIACTRL, wxEmptyString,
                                    wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

    wxASSERT_MSG(bOK, wxT("Could not create media control!"));
    wxUnusedVar(bOK);

    sizer->Add(MediaCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 0);

    //
    // Media Control events
    //
    /*
    this->Connect(wxID_MEDIACTRL, wxEVT_MEDIA_PLAY,
                  wxMediaEventHandler(PlayerFrame::OnMediaPlay));
    this->Connect(wxID_MEDIACTRL, wxEVT_MEDIA_PAUSE,
                  wxMediaEventHandler(PlayerFrame::OnMediaPause));
    this->Connect(wxID_MEDIACTRL, wxEVT_MEDIA_STOP,
                  wxMediaEventHandler(PlayerFrame::OnMediaStop));
                  */
    this->Connect(wxID_MEDIACTRL, wxEVT_MEDIA_FINISHED,
                  wxMediaEventHandler(PlayerFrame::OnMediaFinished));
    this->Connect(wxID_MEDIACTRL, wxEVT_MEDIA_LOADED,
                  wxMediaEventHandler(PlayerFrame::OnMediaLoaded));
}

PlayerFrame::~PlayerFrame()
{
	//(*Destroy(PlayerFrame)
	//*)
}


void PlayerFrame::OnMediaLoaded(wxMediaEvent& WXUNUSED(evt))
{
    if( !MediaCtrl->Play() )
    {
        wxMessageBox(wxT("Unable to play file!"));
    }
}

void PlayerFrame::OnMediaFinished(wxMediaEvent& event)
{
    //wxMessageBox(_("OnMediaFinished"), _("Info"));
    event.SetId(this->GetId());
    event.ResumePropagation(1);
    GetEventHandler()->ProcessEvent( event );
}

void PlayerFrame::OnClose(wxCloseEvent& event)
{
    MediaCtrl->Stop();
    this->Show(false);
}
