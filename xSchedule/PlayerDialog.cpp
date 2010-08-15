#include "PlayerDialog.h"

//(*InternalHeaders(PlayerDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "wx/sizer.h"       //for positioning controls/wxBoxSizer
#include <wx/msgdlg.h>


//(*IdInit(PlayerDialog)
//*)

const long PlayerDialog::wxID_MEDIACTRL = wxNewId();


BEGIN_EVENT_TABLE(PlayerDialog,wxDialog)
	//(*EventTable(PlayerDialog)
	//*)
END_EVENT_TABLE()

PlayerDialog::PlayerDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(PlayerDialog)
	Create(parent, id, _("xPlayer"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);

	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&PlayerDialog::OnClose);
	//*)

    //
    //  Create and attach the sizer
    //
    wxFlexGridSizer* sizer = new wxFlexGridSizer(2, 1, 0, 0);
    this->SetSizer(sizer);
    this->SetAutoLayout(true);
    sizer->AddGrowableRow(0);
    sizer->AddGrowableCol(0);


    //
    //  Create our media control
    //
    MediaCtrl = new wxMediaCtrl();

    //  Make sure creation was successful
    bool bOK = MediaCtrl->Create(this, wxID_MEDIACTRL, wxEmptyString,
                                    wxDefaultPosition, wxDefaultSize, 0);

    wxASSERT_MSG(bOK, wxT("Could not create media control!"));
    wxUnusedVar(bOK);

    sizer->Add(MediaCtrl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

    //
    // Media Control events
    //
    /*
    this->Connect(wxID_MEDIACTRL, wxEVT_MEDIA_PLAY,
                  wxMediaEventHandler(PlayerDialog::OnMediaPlay));
    this->Connect(wxID_MEDIACTRL, wxEVT_MEDIA_PAUSE,
                  wxMediaEventHandler(PlayerDialog::OnMediaPause));
                  */
    this->Connect(wxID_MEDIACTRL, wxEVT_MEDIA_STOP,
                  wxMediaEventHandler(PlayerDialog::OnMediaStop));
    this->Connect(wxID_MEDIACTRL, wxEVT_MEDIA_FINISHED,
                  wxMediaEventHandler(PlayerDialog::OnMediaFinished));
    this->Connect(wxID_MEDIACTRL, wxEVT_MEDIA_LOADED,
                  wxMediaEventHandler(PlayerDialog::OnMediaLoaded));

    //m_timer = new wxMediaPlayerTimer();
    //m_timer->Start(500);

    SetExtraStyle(GetExtraStyle()&~wxWS_EX_BLOCK_EVENTS);
}

PlayerDialog::~PlayerDialog()
{
	//(*Destroy(PlayerDialog)
	//*)
}

// ----------------------------------------------------------------------------
// PlayerDialog::OnMediaLoaded
//
// Called when the media is ready to be played
// ----------------------------------------------------------------------------
void PlayerDialog::OnMediaLoaded(wxMediaEvent& WXUNUSED(evt))
{
    if( !MediaCtrl->Play() )
    {
        wxMessageBox(wxT("Unable to play file!"));
    }
}

void PlayerDialog::OnMediaPlay(wxMediaEvent& WXUNUSED(evt))
{
}

void PlayerDialog::OnMediaPause(wxMediaEvent& WXUNUSED(evt))
{
}

void PlayerDialog::OnMediaStop(wxMediaEvent& event)
{
    //wxMessageBox(_("OnMediaStop"), _("Info"));
    event.SetId(this->GetId());
    event.ResumePropagation(1);
    GetEventHandler()->ProcessEvent( event );
}

void PlayerDialog::OnMediaFinished(wxMediaEvent& event)
{
    //wxMessageBox(_("OnMediaFinished"), _("Info"));
    event.SetId(this->GetId());
    event.ResumePropagation(1);
    GetEventHandler()->ProcessEvent( event );
}

void PlayerDialog::OnClose(wxCloseEvent& event)
{
    MediaCtrl->Stop();
    if (this->IsModal()) {
        this->EndModal(0);
    } else {
        this->Show(false);
    }
}
