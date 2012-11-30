/***************************************************************
 * Name:      TabSchedule.cpp
 * Purpose:   Code for xLights scheduling
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-05-15
 * Copyright: 2010-2012 by Matt Brown
 * License:
     This file is part of xLights.

    xLights is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    xLights is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with xLights.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************/



void xLightsFrame::BasicPrompt(char* prompt, char* buff, int size) {
  //fputs(prompt, stdout);
  //fgets(buff, size, stdin);
}

void xLightsFrame::BasicOutput(char *msg) {
    wxString wxmsg(msg, wxConvUTF8);
    TextCtrlLog->AppendText(wxmsg);
}

void xLightsFrame::BasicError(const char *msg) {
    wxString wxmsg(msg, wxConvUTF8);
    TextCtrlLog->AppendText(wxmsg);
}

void xLightsFrame::StartScript(const char *scriptname) {
    //AuiToolBar1->EnableTool(ID_AUITOOLBARITEM_STOP, true);
    wxString wxname(scriptname, wxConvUTF8);
    StatusBar1->SetStatusText(_("Playing playlist: ")+wxname);
}

void xLightsFrame::EndScript(const char *scriptname) {
    //AuiToolBar1->EnableTool(ID_AUITOOLBARITEM_STOP, false);
    PlayerDlg->MediaCtrl->Stop();
    ResetTimer(NO_SEQ);
    PlayerDlg->Show(false);
    if (xout) xout->alloff();
    wxString wxname(scriptname, wxConvUTF8);
    SendToLogAndStatusBar(_("Ended playlist: ")+wxname);
}

void xLightsFrame::AddPlaylist(const wxString& name) {
    int id, baseid=1000*Notebook1->GetPageCount();
    wxPanel* PanelPlayList = new wxPanel(Notebook1);

    wxFlexGridSizer* FlexGridSizer4 = new wxFlexGridSizer(0, 4, 0, 0);
    FlexGridSizer4->AddGrowableCol(3);
    FlexGridSizer4->AddGrowableRow(2);
    wxStaticText* StaticText1 = new wxStaticText(PanelPlayList, -1, _("Available Files"));
    wxFont StaticText1Font(10,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    FlexGridSizer4->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxStaticText* StaticText2 = new wxStaticText(PanelPlayList, -1, _("Playlist"));
    wxFont StaticText2Font(10,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    FlexGridSizer4->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    //wxBoxSizer* BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer* BoxSizer4 = new wxFlexGridSizer(0, 6, 0, 0);
    wxStaticText* StaticText3 = new wxStaticText(PanelPlayList, -1, _("Files:"));
    BoxSizer4->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+CHKBOX_AUDIO;
    wxCheckBox* CheckBoxAudio = new wxCheckBox(PanelPlayList, id, _("Audio"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_AUDIO"));
    CheckBoxAudio->SetValue(false);
    BoxSizer4->Add(CheckBoxAudio, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED, (wxObjectEventFunction)&xLightsFrame::OnFileTypeButtonClicked);

    id=baseid+CHKBOX_VIDEO;
    wxCheckBox* CheckBoxVideo = new wxCheckBox(PanelPlayList, id, _("Video"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_VIDEO"));
    CheckBoxVideo->SetValue(false);
    BoxSizer4->Add(CheckBoxVideo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED, (wxObjectEventFunction)&xLightsFrame::OnFileTypeButtonClicked);

    id=baseid+CHKBOX_XLIGHTS;
    wxCheckBox* CheckBoxXlights = new wxCheckBox(PanelPlayList, id, _("xLights"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_XLIGHTS"));
    CheckBoxXlights->SetValue(false);
    BoxSizer4->Add(CheckBoxXlights, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED, (wxObjectEventFunction)&xLightsFrame::OnFileTypeButtonClicked);

    FlexGridSizer4->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxFlexGridSizer* FlexGridSizer5 = new wxFlexGridSizer(0, 6, 0, 0);

    id=baseid+CHKBOX_MOVIEMODE;
    wxCheckBox* CheckBoxMovieMode = new wxCheckBox(PanelPlayList, id, _("Movie Mode"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_MOVIEMODE"));
    CheckBoxMovieMode->SetValue(false);
    CheckBoxMovieMode->SetToolTip(_("When a playlist is played in movie mode, a full screen player window is opened to display the associated video."));
    FlexGridSizer5->Add(CheckBoxMovieMode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+UP_BUTTON;
    wxBitmapButton* BitmapButtonUp = new wxBitmapButton(PanelPlayList, id, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_UP")),wxART_BUTTON));
    BitmapButtonUp->SetDefault();
    BitmapButtonUp->SetToolTip(_("Move Item Up"));
    FlexGridSizer5->Add(BitmapButtonUp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xLightsFrame::OnButtonUpClick);

    id=baseid+DOWN_BUTTON;
    wxBitmapButton* BitmapButtonDown = new wxBitmapButton(PanelPlayList, id, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_DOWN")),wxART_BUTTON));
    BitmapButtonDown->SetDefault();
    BitmapButtonDown->SetToolTip(_("Move Item Down"));
    FlexGridSizer5->Add(BitmapButtonDown, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xLightsFrame::OnButtonDownClick);
/*
    id=baseid+INFO_BUTTON;
    wxBitmapButton* BitmapButtonInfo = new wxBitmapButton(PanelPlayList, id, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_INFORMATION")),wxART_BUTTON));
    BitmapButtonInfo->SetDefault();
    BitmapButtonInfo->SetToolTip(_("Sequence Information"));
    FlexGridSizer5->Add(BitmapButtonInfo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xLightsFrame::OnButtonInfoClick);
*/
    id=baseid+DELAY_BUTTON;
    wxButton* ButtonDelay = new wxButton(PanelPlayList, id, _("Set delay"));
    ButtonDelay->SetToolTip(_("Sets the amount of delay after item is played"));
    FlexGridSizer5->Add(ButtonDelay, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xLightsFrame::OnButtonSetDelayClick);

    id=baseid+PLAY_BUTTON;
    wxButton* ButtonPlay = new wxButton(PanelPlayList, id, _("Play Item"));
    ButtonPlay->SetToolTip(_("Play Selected Item"));
    ButtonPlay->SetHelpText(_("Plays the currently selected item in the play list"));
    FlexGridSizer5->Add(ButtonPlay, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xLightsFrame::OnButtonPlayItemClick);

    id=baseid+PLAY_ALL_BUTTON;
    wxButton* ButtonPlayAll = new wxButton(PanelPlayList, id, _("Play All"));
    ButtonPlayAll->SetToolTip(_("Play entire list"));
    ButtonPlayAll->SetHelpText(_("Plays everything in the play list"));
    FlexGridSizer5->Add(ButtonPlayAll, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xLightsFrame::OnButtonRunPlaylistClick);

    FlexGridSizer4->Add(FlexGridSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    //FlexGridSizer4->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+REMOVE_SCRIPT_BUTTON;
    wxButton* ButtonRemoveScript = new wxButton(PanelPlayList, id, _("Remove Script"));
    FlexGridSizer4->Add(ButtonRemoveScript, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xLightsFrame::OnButtonRemoveScriptClick);
    ButtonRemoveScript->Hide();

    id=baseid+PLAYLIST_FILES;
    wxTreeCtrl* TreeCtrl = new wxTreeCtrl(PanelPlayList, id);
    FlexGridSizer4->Add(TreeCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxBoxSizer* BoxSizer5 = new wxBoxSizer(wxVERTICAL);

    id=baseid+PLAYLIST_ADD;
    wxButton* Button2 = new wxButton(PanelPlayList, id, _(">"));
    Button2->SetMinSize(wxSize(35,20));
    Button2->SetToolTip(_("Add selected file"));
    BoxSizer5->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xLightsFrame::OnButtonPlaylistAddClick);

    id=baseid+PLAYLIST_ADD_ALL;
    wxButton* Button3 = new wxButton(PanelPlayList, id, _(">>"));
    Button3->SetMinSize(wxSize(35,20));
    Button3->SetToolTip(_("Add all files"));
    BoxSizer5->Add(Button3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xLightsFrame::OnButtonPlaylistAddAllClick);

    id=baseid+PLAYLIST_DELETE;
    wxButton* Button4 = new wxButton(PanelPlayList, id, _("<"));
    Button4->SetMinSize(wxSize(35,20));
    Button4->SetToolTip(_("Delete selected item"));
    BoxSizer5->Add(Button4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xLightsFrame::OnButtonPlaylistDeleteClick);

    id=baseid+PLAYLIST_DELETE_ALL;
    wxButton* Button5 = new wxButton(PanelPlayList, id, _("<<"));
    Button5->SetMinSize(wxSize(35,20));
    Button5->SetToolTip(_("Delete all items"));
    BoxSizer5->Add(Button5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xLightsFrame::OnButtonPlaylistDeleteAllClick);

    FlexGridSizer4->Add(BoxSizer5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+PLAYLIST_LISTBOX;
    wxListCtrl* ListBox1 = new wxListCtrl(PanelPlayList, id, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);

#ifndef __WXOSX__
    ListBox1->SetToolTip(_("Drag an item to reorder the list"));
#endif
    Connect(id, wxEVT_COMMAND_LIST_BEGIN_DRAG, (wxObjectEventFunction)&xLightsFrame::OnPlayListBeginDrag);
    FlexGridSizer4->Add(ListBox1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+PLAYLIST_LOGIC;
    wxTextCtrl* TextCtrlLogic = new wxTextCtrl(PanelPlayList, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_LOGIC"));
    FlexGridSizer4->Add(TextCtrlLogic, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlLogic->Hide();

    PanelPlayList->SetSizer(FlexGridSizer4);
    FlexGridSizer4->Fit(PanelPlayList);
    FlexGridSizer4->SetSizeHints(PanelPlayList);
    Notebook1->AddPage(PanelPlayList, name, true);

    // set playlist columns
    wxListItem itemCol;
    itemCol.SetText(_T("Filename"));
    itemCol.SetImage(-1);
    ListBox1->InsertColumn(0, itemCol);
    itemCol.SetText(_T("Delay (s)"));
    itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
    ListBox1->InsertColumn(1, itemCol);
    ListBox1->SetColumnWidth(0,100);
    ListBox1->SetColumnWidth(1,100);
}

void xLightsFrame::OnButtonPlaylistAddClick(wxCommandEvent& event) {
    int nbidx=Notebook1->GetSelection();
    int baseid=1000*nbidx;
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxTreeCtrl* TreeCtrlFiles=(wxTreeCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_FILES,Notebook1);
    wxTreeItemId root=TreeCtrlFiles->GetRootItem();
    wxTreeItemId selid=TreeCtrlFiles->GetSelection();
    if (!selid.IsOk() || root==selid) return;
    wxString selstr = TreeCtrlFiles->GetItemText(selid);
    long newidx = ListBoxPlay->InsertItem(ListBoxPlay->GetItemCount(), selstr);
    ListBoxPlay->SetItem(newidx,1,wxT("0"));
    ListBoxPlay->SetColumnWidth(0,wxLIST_AUTOSIZE);
    UnsavedChanges=true;
    ScanForFiles();
}

void xLightsFrame::OnButtonPlaylistAddAllClick(wxCommandEvent& event) {
    int nbidx=Notebook1->GetSelection();
    int baseid=1000*nbidx;
    int cnt=0;
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxTreeCtrl* TreeCtrlFiles=(wxTreeCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_FILES,Notebook1);
    wxTreeItemId root=TreeCtrlFiles->GetRootItem();
    wxTreeItemId item=TreeCtrlFiles->GetFirstVisibleItem();
    while (item.IsOk()) {
        if (item != root) {
            long newidx = ListBoxPlay->InsertItem(ListBoxPlay->GetItemCount(), TreeCtrlFiles->GetItemText(item));
            ListBoxPlay->SetItem(newidx,1,wxT("0"));
            UnsavedChanges=true;
            cnt++;
        }
        item=TreeCtrlFiles->GetNextVisible(item);
    }
    if (cnt > 0) ListBoxPlay->SetColumnWidth(0,wxLIST_AUTOSIZE);
    ScanForFiles();
}

void xLightsFrame::OnButtonPlaylistDeleteClick(wxCommandEvent& event) {
    int nbidx=Notebook1->GetSelection();
    int baseid=1000*nbidx;
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    long SelectedItem = GetSelectedItem(ListBoxPlay);
    if (SelectedItem == -1) {
        wxMessageBox(_("Please select a single row in the playlist first"), _("Error"));
        return;
    }
    ListBoxPlay->DeleteItem(SelectedItem);
    ListBoxPlay->SetColumnWidth(0, ListBoxPlay->GetItemCount() > 0 ? wxLIST_AUTOSIZE : wxLIST_AUTOSIZE_USEHEADER);
    UnsavedChanges=true;
    ScanForFiles();
}

void xLightsFrame::OnButtonPlaylistDeleteAllClick(wxCommandEvent& event) {
    int nbidx=Notebook1->GetSelection();
    int baseid=1000*nbidx;
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    if (ListBoxPlay->GetItemCount() > 0) {
        ListBoxPlay->DeleteAllItems();
        ListBoxPlay->SetColumnWidth(0,wxLIST_AUTOSIZE_USEHEADER);
        UnsavedChanges=true;
    }
    ScanForFiles();
}

void xLightsFrame::ResetTimer(SeqPlayerStates newstate) {
    SeqPlayerState = newstate;
#ifndef NDEBUG
    TextCtrlLog->AppendText(wxString::Format(_("ResetTimer mode=%d state=%d\n"),play_mode,SeqPlayerState));
#endif
    //if (newstate == NO_SEQ) SetPlayMode(play_off);
    if (xout) xout->ResetTimer();
    starttime = wxDateTime::UNow();
}

long xLightsFrame::DiffSeconds(wxString& strTime, wxTimeSpan& tsCurrent)
{
    wxDateTime t;
    t.ParseTime(strTime);
    wxTimeSpan tsSched(t.GetHour(),t.GetMinute(),t.GetSecond(),t.GetMillisecond());
    tsSched -= tsCurrent;
    return tsSched.GetSeconds().ToLong();
}

void xLightsFrame::ForceScheduleCheck() {
    LastMoDay.Empty();
}

void xLightsFrame::CheckSchedule()
{
    wxString StartTime, EndTime, userscript;
    int i,cnt;
    bool CheckSchedule = false;
    wxTextCtrl* LogicCtl;

    static wxString RepeatOptions, Playlist, strStartTime, strEndTime, StartMoDay;
    static wxDateTime LastTime = wxDateTime::Now();  // last time this method was called
    static long StartTimeSec;
    static wxArrayString AlreadyPlayed;
    static bool MoreShowsToday = true;

    if (!CheckBoxRunSchedule->IsChecked()) return;
    if (play_mode!=play_sched && play_mode!=play_off) return;

    wxDateTime n=wxDateTime::Now();
    long SecPastMidnight=n.GetHour()*60*60 + n.GetMinute()*60 + n.GetSecond();
    wxString CurrentMoDay = n.Format(wxT("%m%d"));
    //StatusBar1->SetStatusText(_("OnSchedTimer: ") + n.FormatISOTime());

    if (basic.IsRunning()) {

        // playlist is running - check for the schedule end

        if (CurrentMoDay != StartMoDay) SecPastMidnight+=24*60*60;
        SecondsRemaining=EndTimeSec - SecPastMidnight;
        int minutes=(SecondsRemaining + 59) / 60;  // round up
        if (minutes > 60) {
            StatusBar1->SetStatusText(_("Show will end at: ") + strEndTime, 1);
        } else if (minutes > 1) {
            StatusBar1->SetStatusText(wxString::Format(_("Show will end in %d minutes"),minutes), 1);
        } else if (SecondsRemaining > 0) {
            StatusBar1->SetStatusText(wxString::Format(_("Show will end in about %ld seconds"),SecondsRemaining), 1);
        } else {
            StatusBar1->SetStatusText(_("Finishing playlist: ") + Playlist, 1);
        }

    } else {

        // no playlist running - wait for next event

        // should we check ShowEvents[]?
        if (LastMoDay != CurrentMoDay) {
            // either the Run Schedule button was just pressed, or we just passed midnight
            CheckSchedule = true;
            LastMoDay = CurrentMoDay;
        } else {
            // has computer has been sleeping?
            wxTimeSpan TimeDiff=n.Subtract(LastTime);
            if (TimeDiff.GetSeconds().ToLong() > 10) CheckSchedule = true;
        }
        LastTime=n;
        SecondsRemaining=24*60*60 - SecPastMidnight;

        if (CheckSchedule) {
            // find first event for the day
            MoreShowsToday = false;
            cnt=ShowEvents.Count();
            for (i=0; i < cnt; i++) {
                if (ShowEvents[i].StartsWith(CurrentMoDay)) break;
            }
            if (i >= cnt) {
                StatusBar1->SetStatusText(_("No show scheduled for today"), 1);
                return;
            }
            do {
                UnpackSchedCode(ShowEvents[i], StartTime, EndTime, RepeatOptions, Playlist);
                StartTimeSec=Time2Seconds(StartTime);
                EndTimeSec=Time2Seconds(EndTime);
                if (SecPastMidnight < EndTimeSec && AlreadyPlayed.Index(ShowEvents[i]) == wxNOT_FOUND) {
                    MoreShowsToday = true;
                    strStartTime = StartTime.Left(2) + wxT(":") + StartTime.Right(2);
                    strEndTime = EndTime.Left(2) + wxT(":") + EndTime.Right(2);
                    break;
                }
                i++;
            } while (i < cnt && ShowEvents[i].StartsWith(CurrentMoDay));
            if (!MoreShowsToday) {
                StatusBar1->SetStatusText(_("No more shows scheduled for today"), 1);
                SetPlayMode(play_off);
                return;
            }
        } // CheckSchedule

        if (MoreShowsToday) {
            if (SecPastMidnight < StartTimeSec) {
                // have not reached show start time
                SecondsRemaining=StartTimeSec - SecPastMidnight;
                int minutes= (SecondsRemaining + 59) / 60;  // round up
                if (minutes > 60) {
                    StatusBar1->SetStatusText(_("Next show will start at: ") + strStartTime, 1);
                } else if (minutes > 1) {
                    StatusBar1->SetStatusText(wxString::Format(_("Next show will start in %d minutes"),minutes), 1);
                } else {
                    StatusBar1->SetStatusText(wxString::Format(_("Next show will start in %ld seconds"),SecondsRemaining), 1);
                }
            } else if (SecPastMidnight < EndTimeSec) {
                // start show
                int nbidx=FindNotebookPage(Playlist);
                if (nbidx > 0) {
                    SetPlayMode(play_sched);
                    LogicCtl=(wxTextCtrl*)FindNotebookControl(nbidx,PLAYLIST_LOGIC);
                    if (LogicCtl && LogicCtl->IsShown()) {
                        // run custom script
                        userscript=LogicCtl->GetValue();
                    } else {
                        // this is a playlist page, run generic script
                        userscript=CreateScript(Notebook1->GetPageText(nbidx),RepeatOptions[0]=='R',RepeatOptions[1]=='F',RepeatOptions[2]=='L',false,RepeatOptions[3]=='X');
                    }
                    StartMoDay=CurrentMoDay;
                    AlreadyPlayed.Add(ShowEvents[i]);
                    RunPlaylist(nbidx,userscript);
                } else {
                    StatusBar1->SetStatusText(_("ERROR: cannot find playlist ") + Playlist, 1);
                }
            } else {
                // check the next show
                ForceScheduleCheck();
            }
        }
    }
}


int xLightsFrame::FindNotebookPage(wxString& pagename)
{
    for (size_t i=FixedPages; i < Notebook1->GetPageCount(); i++) {
        if (Notebook1->GetPageText(i) == pagename) {
            return i;
        }
    }
    return -1;
}

void xLightsFrame::OnTimerPlaylist(long msec)
{
    int period, chindex;
    static std::string LastIntensity;
    char intensity;
    switch (SeqPlayerState) {
        case DELAY_AFTER_PLAY:
            if (msec > DelayAfterPlayMSEC) {
                ResetTimer(NO_SEQ);
                // reached end of song/sequence, so execute callback (if defined)
                basic.PlaybackEndCallback();
                return;
            }
            break;
        case STARTING_MEDIA:
            if(PlayerDlg->MediaCtrl->GetState() == wxMEDIASTATE_PLAYING){
                ResetTimer(PLAYING_MEDIA);
            } else {
                PlayerDlg->MediaCtrl->Play();
            }
            break;
        case PLAYING_MEDIA:
            if (PlayerDlg->MediaCtrl->GetState() != wxMEDIASTATE_PLAYING) {
                ResetTimer(basic.IsRunning() ? DELAY_AFTER_PLAY : NO_SEQ);
            }
            break;
        case STARTING_SEQ_ANIM:
            LastIntensity.resize(SeqNumChannels,1);
            ResetTimer(PLAYING_SEQ_ANIM);
            break;
        case PLAYING_SEQ_ANIM:
            if (xout && !xout->TxEmpty()) {
                TxOverflowCnt++;
                break;
            }
            period = msec / XTIMER_INTERVAL;
            if (period < SeqNumPeriods) {
                if (CheckBoxLightOutput->IsChecked()) {
                    for (chindex=0; chindex<SeqNumChannels; chindex++) {
                        intensity=SeqData[chindex*SeqNumPeriods+period];
                        if (xout && intensity != LastIntensity[chindex]) {
                            xout->SetIntensity(chindex, intensity);
                            LastIntensity[chindex]=intensity;
                        }
                    }
                }
            } else {
                ResetTimer(basic.IsRunning() ? DELAY_AFTER_PLAY : NO_SEQ);
            }
            break;
        case STARTING_SEQ:
            if(PlayerDlg->MediaCtrl->GetState() == wxMEDIASTATE_PLAYING){
                LastIntensity.resize(SeqNumChannels,1);
                ResetTimer(PLAYING_SEQ);
            } else {
                PlayerDlg->MediaCtrl->Play();
            }
            break;
        case PLAYING_SEQ:
            if (PlayerDlg->MediaCtrl->GetState() != wxMEDIASTATE_PLAYING) {
                ResetTimer(basic.IsRunning() ? DELAY_AFTER_PLAY : PAUSE_SEQ);
                return;
            }
            if (xout && !xout->TxEmpty()) {
                TxOverflowCnt++;
                break;
            }
            msec = PlayerDlg->MediaCtrl->Tell();
            period = msec / XTIMER_INTERVAL;
            if (period < SeqNumPeriods) {
                if (CheckBoxLightOutput->IsChecked()) {
                    for (chindex=0; chindex<SeqNumChannels; chindex++) {
                        intensity=SeqData[chindex*SeqNumPeriods+period];
                        if (xout && intensity != LastIntensity[chindex]) {
                            xout->SetIntensity(chindex, intensity);
                            LastIntensity[chindex]=intensity;
                        }
                    }
                }
            }
            break;
        case PAUSE_SEQ:
            if (PlayerDlg->MediaCtrl->GetState() == wxMEDIASTATE_PLAYING) {
                LastIntensity.resize(SeqNumChannels,1);
                ResetTimer(PLAYING_SEQ);
            }
            break;
    }
    basic.SerialCallback();
}

void xLightsFrame::OnFileTypeButtonClicked(wxCommandEvent& event)
{
    UnsavedChanges=true;
    ScanForFiles();
}

void xLightsFrame::ScanForFiles()
{
    wxString filename;
    wxArrayString filenames;
    bool ok;
    int i;

    int nbidx=Notebook1->GetSelection();
    int baseid=1000*nbidx;
    wxString PageName=Notebook1->GetPageText(nbidx);
    wxTreeCtrl* TreeCtrlFiles=(wxTreeCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_FILES,Notebook1);
    if (TreeCtrlFiles == 0) {
        wxMessageBox(_("Must be on a playlist tab"));
        return;
    }
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxCheckBox* CheckBoxAudio=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_AUDIO,Notebook1);
    wxCheckBox* CheckBoxVideo=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_VIDEO,Notebook1);
    wxCheckBox* CheckBoxXlights=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_XLIGHTS,Notebook1);

    wxFileName oName;
    oName.AssignDir( CurrentDir );

    // if file was deleted, remove matching entry
    int cnt=ListBoxPlay->GetItemCount();
    for (i=0; i<cnt; i++) {
        filenames.Add(ListBoxPlay->GetItemText(i));
    }
    for (i=filenames.GetCount()-1; i >= 0; i--) {
        oName.SetFullName(filenames[i]);
        if (!oName.FileExists()) {
            ListBoxPlay->DeleteItem(i);
            UnsavedChanges=true;
            wxMessageBox(_("File ") + filenames[i] + _(" was deleted from the show directory\n\nRemoving it from playlist ") + PageName, _("Playlist Updated"));
        }
    }

    // scan directory for matches
    TreeCtrlFiles->DeleteAllItems();
    wxTreeItemId root=TreeCtrlFiles->AddRoot(_("Show Directory"));
    wxDir dir(CurrentDir);
    bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
    while ( cont ) {
        if (filenames.Index(filename) == wxNOT_FOUND) {
            oName.SetFullName(filename);
            ok=false;
            switch (ExtType(oName.GetExt())) {
                case 'a': ok=CheckBoxAudio->IsChecked(); break;
                case 'v': ok=CheckBoxVideo->IsChecked(); break;
                case 'X': ok=CheckBoxXlights->IsChecked(); break;
            }
            if (ok) TreeCtrlFiles->AppendItem(root,filename);
        }
        cont = dir.GetNext(&filename);
    }
    TreeCtrlFiles->ExpandAll();
}

// returns V for vixen, L for LOR, X for xLights, a for audio, v for video
char xLightsFrame::ExtType(const wxString& ext) {
    if (ext == _("vix")) {
        return 'V';
    } else if (ext == _(XLIGHTS_SEQUENCE_EXT)) {
        return 'X';
    } else if (ext == _("lms") || ext == _("las")) {
        return 'L';
    } else if (ext == _("wav") || ext == _("mp3") ||
               ext == _("wma") || ext == _("aac") ||
               ext == _("mid")) {
        return 'a';
    } else if (ext == _("avi") || ext == _("mp4") ||
               ext == _("wmv") || ext == _("mov") ||
               ext == _("mpg")) {
        return 'v';
    }
    return ' ';
}

// returns -1 if not found
long xLightsFrame::GetSelectedItem(wxListCtrl* ListBoxPlay)
{
    return ListBoxPlay->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
}

void xLightsFrame::OnButtonSetDelayClick(wxCommandEvent& event)
{
    int baseid=1000*Notebook1->GetSelection();
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    long SelectedItem = GetSelectedItem(ListBoxPlay);
    if (SelectedItem == -1) {
        wxMessageBox(_("Please select a single row in the playlist first"), _("Error"));
        return;
    }
    wxListItem column1;
    column1.SetId(SelectedItem);
    column1.SetColumn(1);
    column1.SetMask(wxLIST_MASK_TEXT);
    ListBoxPlay->GetItem(column1);
    wxString delay = column1.GetText();
    long CurrentValue;
    delay.ToLong(&CurrentValue);
    long NewValue = wxGetNumberFromUser(_("Amount of delay after the selected item has finished playing"),
                        _("Enter the number of seconds (0-3600)"), _("Set Delay"), CurrentValue, 0, 3600, this);
    if (NewValue >= 0) {
        delay = wxString::Format(wxT("%ld"),NewValue);
        ListBoxPlay->SetItem(SelectedItem, 1, delay);
        UnsavedChanges=true;
    }
}

void xLightsFrame::OnButtonPlayItemClick(wxCommandEvent& event)
{
    if (basic.IsRunning()) {
        StatusBar1->SetStatusText(_("A playlist is already running!"));
        return;
    }
    int baseid=1000*Notebook1->GetSelection();
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    long SelectedItem = GetSelectedItem(ListBoxPlay);
    if (SelectedItem == -1) {
        wxMessageBox(_("Please select a single row in the playlist first"), _("Error"));
        return;
    }

    SetPlayMode(play_single);
    wxString filename = ListBoxPlay->GetItemText(SelectedItem);
    // ignore delay value
    if (Play(filename,0)) {
        StatusBar1->SetStatusText(_("Playing: ") + filename);
        PlayerDlg->MediaCtrl->ShowPlayerControls(wxMEDIACTRLPLAYERCONTROLS_DEFAULT);
        PlayerDlg->ShowFullScreen(false, 0);
        PlayerDlg->Show();
    }
}

void xLightsFrame::PlayerError(const wxString& msg)
{
    if (play_mode == play_sched) {
        TextCtrlLog->AppendText(msg + _("\n"));
    } else {
        wxMessageBox(msg, _("Error"), wxOK | wxICON_EXCLAMATION);
    }
}

void xLightsFrame::StopPlayback()
{
    ResetTimer(NO_SEQ);
}

// returns true on success
bool xLightsFrame::PlayCurrentXlightsFile() {
    if (SeqNumChannels <= 0) {
        PlayerError(_("Unable to determine number of channels"));
    } else if (mediaFilename.IsEmpty()) {
        ResetTimer(STARTING_SEQ_ANIM);
    } else if (!wxFile::Exists(mediaFilename)) {
        PlayerError(_("Cannot locate media file:\n") + mediaFilename + _("\n\nMake sure your media files are in the same directory as your sequences."));
    } else if (!PlayerDlg->MediaCtrl->Load(mediaFilename)) {
        PlayerError(_("Unable to play media file:\n")+mediaFilename);
    } else {
        ResetTimer(STARTING_SEQ);
        return true;
    }
    return false;
}

// returns true on success
// also called from script
bool xLightsFrame::Play(wxString& filename, long delay) {
    DelayAfterPlayMSEC=delay*1000;  // convert seconds to milliseconds
    wxFileName oName(CurrentDir, filename);
    wxString fullpath=oName.GetFullPath();
    switch (ExtType(oName.GetExt())) {
        case 'a':
        case 'v':
            if (wxFile::Exists(fullpath) && PlayerDlg->MediaCtrl->Load(fullpath)) {
                ResetTimer(STARTING_MEDIA);
                return true;
            } else {
                PlayerError(_("Unable to play file:\n")+filename);
            }
            break;
        case 'X':
            ReadXlightsFile(fullpath);
            return PlayCurrentXlightsFile();
            break;
    }
    return false;
}

void xLightsFrame::OnButtonUpClick(wxCommandEvent& event)
{
    int baseid=1000*Notebook1->GetSelection();
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    long SelectedItem = GetSelectedItem(ListBoxPlay);
    if (SelectedItem == -1) {
        wxMessageBox(_("Please select a single row in the playlist first"), _("Error"));
        return;
    }

    if (SelectedItem == 0) return;
#ifdef __WXOSX__
    // cannot use regular code because of wxWidgets ticket #4492
	wxArrayString ColText[2];
    int rowcnt=ListBoxPlay->GetItemCount();
    wxListItem listcol;
	int r,c;
	// get text for all rows
	for (r=0; r < rowcnt; r++) {
		listcol.SetId(r);
		for (c=0; c < 2; c++)
		{
			listcol.SetColumn(c);
			listcol.SetMask(wxLIST_MASK_TEXT);
			ListBoxPlay->GetItem(listcol);
			ColText[c].Add(listcol.GetText());
		}
	}
	//wxMessageBox(wxString::Format(wxT("SelectedItem=%ld"),SelectedItem), wxT("DEBUG"));

	ListBoxPlay->DeleteAllItems();

	// update order
	wxString s;
	for (c=0; c < 2; c++) {
	    s=ColText[c][SelectedItem];
		ColText[c].Insert(s,SelectedItem-1);
	}
	for (c=0; c < 2; c++) {
	    ColText[c].RemoveAt(SelectedItem+1);
	}

	// add everything back in the new order
	for (r=0; r < rowcnt; r++) {
        ListBoxPlay->InsertItem(r,ColText[0][r]);
		for (c=1; c < 2; c++)
		{
			ListBoxPlay->SetItem(r,c,ColText[c][r]);
		}
	}
    SelectedItem--;
#else
    wxString filename = ListBoxPlay->GetItemText(SelectedItem);
    wxListItem column1;
    column1.SetId(SelectedItem);
    column1.SetColumn(1);
    column1.SetMask(wxLIST_MASK_TEXT);
    ListBoxPlay->GetItem(column1);
    wxString delay = column1.GetText();
    ListBoxPlay->DeleteItem(SelectedItem);
    SelectedItem--;
    ListBoxPlay->InsertItem(SelectedItem,filename);
    ListBoxPlay->SetItem(SelectedItem,1,delay);
#endif
    ListBoxPlay->SetItemState(SelectedItem,wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
    UnsavedChanges=true;
}

void xLightsFrame::OnButtonDownClick(wxCommandEvent& event)
{
    int baseid=1000*Notebook1->GetSelection();
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    long SelectedItem = GetSelectedItem(ListBoxPlay);
    if (SelectedItem == -1) {
        wxMessageBox(_("Please select a single row in the playlist first"), _("Error"));
        return;
    }

    if (SelectedItem == ListBoxPlay->GetItemCount()-1) return;
#ifdef __WXOSX__
    // cannot use regular code because of wxWidgets ticket #4492
	wxArrayString ColText[2];
    int rowcnt=ListBoxPlay->GetItemCount();
    wxListItem listcol;
	int r,c;
	// get text for all rows
	for (r=0; r < rowcnt; r++) {
		listcol.SetId(r);
		for (c=0; c < 2; c++)
		{
			listcol.SetColumn(c);
			listcol.SetMask(wxLIST_MASK_TEXT);
			ListBoxPlay->GetItem(listcol);
			ColText[c].Add(listcol.GetText());
		}
	}
	//wxMessageBox(wxString::Format(wxT("SelectedItem=%ld"),SelectedItem), wxT("DEBUG"));

	ListBoxPlay->DeleteAllItems();

	// update order
	wxString s;
	for (c=0; c < 2; c++) {
	    s=ColText[c][SelectedItem];
		ColText[c].Insert(s,SelectedItem+2);
	}
	for (c=0; c < 2; c++) {
	    ColText[c].RemoveAt(SelectedItem);
	}

	// add everything back in the new order
	for (r=0; r < rowcnt; r++) {
        ListBoxPlay->InsertItem(r,ColText[0][r]);
		for (c=1; c < 2; c++)
		{
			ListBoxPlay->SetItem(r,c,ColText[c][r]);
		}
	}
    SelectedItem++;
#else
    wxString filename = ListBoxPlay->GetItemText(SelectedItem);
    wxListItem column1;
    column1.SetId(SelectedItem);
    column1.SetColumn(1);
    column1.SetMask(wxLIST_MASK_TEXT);
    ListBoxPlay->GetItem(column1);
    wxString delay = column1.GetText();
    ListBoxPlay->DeleteItem(SelectedItem);
    SelectedItem++;
    ListBoxPlay->InsertItem(SelectedItem,filename);
    ListBoxPlay->SetItem(SelectedItem,1,delay);
#endif
    ListBoxPlay->SetItemState(SelectedItem,wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
    UnsavedChanges=true;
}

void xLightsFrame::OnMenuItemAddListSelected(wxCommandEvent& event)
{
    if (!scheduleFile.IsOk()) {
        wxMessageBox(_("Please select a valid show directory before adding a playlist."));
        return;
    }
    wxTextEntryDialog dialog(this, _("Enter name for new playlist"), _("New Playlist"));
    if (dialog.ShowModal() != wxID_OK) return;
    wxString name=dialog.GetValue();
    if (name.IsEmpty()) return;
    if (FindNotebookPage(name) >= 0) {
        wxMessageBox(_("That name is already in use!"), _("Error"));
        return;
    }
    AddPlaylist(name);
    UnsavedChanges=true;
}

void xLightsFrame::OnMenuItemDelListSelected(wxCommandEvent& event)
{
    int idx=Notebook1->GetSelection();
    if (idx  < FixedPages) {
        wxMessageBox(_("Can't delete this page!"), _("Error"));
        return;
    }
    int result = wxMessageBox(_("Are you sure you want to delete '") + Notebook1->GetPageText(idx) + _("'?"), _("Delete Playlist"), wxOK | wxCANCEL | wxCENTER);
    if (result != wxOK) return;
    Notebook1->DeletePage(idx);
    UnsavedChanges=true;
}

void xLightsFrame::OnMenuItemRenameListSelected(wxCommandEvent& event)
{
    int nbidx=Notebook1->GetSelection();
    if (nbidx < FixedPages) {
        wxMessageBox(_("Can't rename this page"), _("Error"));
        return;
    }
    wxString PlaylistName=Notebook1->GetPageText(nbidx);
    wxTextEntryDialog dialog(this, _("Enter a new name"), _("Rename Playlist"), PlaylistName);
    if (dialog.ShowModal() != wxID_OK) return;
    wxString NewName=dialog.GetValue();
    if (NewName.IsEmpty() || NewName == PlaylistName) return;
    if (FindNotebookPage(NewName) >= 0) {
        wxMessageBox(_("That name is already in use!"), _("Error"));
        return;
    }
    Notebook1->SetPageText(nbidx,NewName);
    UnsavedChanges=true;
}

void xLightsFrame::SaveScheduleFile()
{
    if (!scheduleFile.IsOk()) {
        wxMessageBox(_("Please select a valid show directory before saving your schedule."));
        return;
    }
    wxListItem column1;
    unsigned int RowCount,baseid;
    wxString v;
    wxCheckBox* chkbox;
    wxTextCtrl* TextCtrlLogic;
    wxXmlDocument doc;
    wxXmlNode *item, *plist, *scriptnode, *scripttext;
    wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("xSchedule") );
    root->AddAttribute( wxT("computer"), wxGetHostName());
    doc.SetRoot( root );

    // save schedule
    wxXmlNode* sched = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("schedule") );
    sched->AddAttribute( wxT("schedstart"), ShowStartDate.FormatISODate() );
    sched->AddAttribute( wxT("schedend"), ShowEndDate.FormatISODate() );
    root->AddChild(sched);
    int cnt=ShowEvents.GetCount();
    for (int i=0; i<cnt; i++) {
        item = new wxXmlNode( wxXML_ELEMENT_NODE, _("calevent") );
        item->AddAttribute( wxT("schedcode"), ShowEvents[i] );
        sched->AddChild( item );
    }

    // save playlists
    wxXmlNode* lists = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("playlists") );
    root->AddChild(lists);

    cnt=Notebook1->GetPageCount();
    for (int pagenum=FixedPages; pagenum < cnt; pagenum++) {
        plist = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("playlist") );
        plist->AddAttribute( wxT("name"), Notebook1->GetPageText(pagenum) );
        baseid=1000*pagenum;
        wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
        for (int i=CHKBOX_AUDIO; i<=CHKBOX_MOVIEMODE; i++) {
            chkbox=(wxCheckBox*)wxWindow::FindWindowById(baseid+i,Notebook1);
            v = chkbox->GetValue() ? _("1") : _("0");
            wxString label = chkbox->GetLabelText();
            label.Replace(_(" "), _(""));
            plist->AddAttribute( label, v );
        }
        lists->AddChild( plist );

        RowCount=ListBoxPlay->GetItemCount();
        for (unsigned int r=0; r < RowCount; r++ ) {
            item = new wxXmlNode( wxXML_ELEMENT_NODE, _("listitem") );
            item->AddAttribute( wxT("name"), ListBoxPlay->GetItemText(r) );
            column1.SetId(r);
            column1.SetColumn(1);
            column1.SetMask(wxLIST_MASK_TEXT);
            ListBoxPlay->GetItem(column1);
            item->AddAttribute( wxT("delay"), column1.GetText() );
            plist->AddChild( item );
        }

        TextCtrlLogic = (wxTextCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LOGIC,Notebook1);
        if (TextCtrlLogic && TextCtrlLogic->IsShown()) {
            scriptnode = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("script") );
            scripttext = new wxXmlNode( wxXML_TEXT_NODE, wxT("scripttext") );
            scripttext->SetContent( TextCtrlLogic->GetValue() );
            plist->AddChild( scriptnode );
            scriptnode->AddChild( scripttext );
        }
    }

    // commit to disk
    wxString FileName=scheduleFile.GetFullPath();
    if (doc.Save(FileName)) {
        UnsavedChanges=false;
        StatusBar1->SetStatusText(_("File saved successfully"));
    } else {
        wxMessageBox(_("Unable to save schedule file"), _("Error"));
    }
}

void xLightsFrame::LoadScheduleFile()
{
    if (!scheduleFile.IsOk()) {
        wxMessageBox(_("Unable to load schedule file."));
        return;
    }
    wxXmlDocument doc;
    wxString name;
    if (doc.Load( scheduleFile.GetFullPath() )) {
        wxXmlNode* root=doc.GetRoot();
        for( wxXmlNode* e=root->GetChildren(); e!=NULL; e=e->GetNext() ) {
            name=e->GetName();
            if (name == _("schedule")) {
                LoadSchedule(e);
            } else if (name == _("playlists")) {
                LoadPlaylists(e);
            }
        }
    } else {
        wxMessageBox(_("Unable to load schedule file"), _("Error"));
    }
}

void xLightsFrame::LoadSchedule(wxXmlNode* n)
{
    wxDateTime NewStart = wxDateTime::Now();
    wxDateTime NewEnd = wxDateTime::Now();
    if (n->HasAttribute(wxT("schedstart"))) {
        NewStart.ParseFormat(n->GetAttribute( wxT("schedstart"), wxT("")), wxT("%Y-%m-%d"));
    }
    if (n->HasAttribute(wxT("schedend"))) {
        NewEnd.ParseFormat(n->GetAttribute( wxT("schedend"), wxT("")), wxT("%Y-%m-%d"));
    }
    UpdateShowDates(NewStart,NewEnd);
    for( wxXmlNode* e=n->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() == _("calevent")) {
            wxString schedcode = e->GetAttribute( wxT("schedcode"), wxT(""));
            if (schedcode.Len() > 10) ShowEvents.Add(schedcode);
        }
    }
}

void xLightsFrame::LoadPlaylists(wxXmlNode* n)
{
    for( wxXmlNode* e=n->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() == _("playlist")) {
            LoadPlaylist(e);
        }
    }
}

void xLightsFrame::LoadPlaylist(wxXmlNode* n)
{
    wxCheckBox* chkbox;
    wxString chkval;
    wxString name = n->GetAttribute( wxT("name"), wxT(""));
    int baseid=1000*Notebook1->GetPageCount();
    AddPlaylist(name);
    for (int i=CHKBOX_AUDIO; i<=CHKBOX_MOVIEMODE; i++) {
        chkbox=(wxCheckBox*)wxWindow::FindWindowById(baseid+i,Notebook1);
        if (!chkbox) continue;
        wxString label = chkbox->GetLabelText();
        label.Replace(_(" "), _(""));
        chkval = n->GetAttribute(label, wxT("0"));
        chkbox->SetValue( chkval == _("1") );
    }
    wxListCtrl* ListBoxPlay = (wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxTextCtrl* TextCtrlLogic = (wxTextCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LOGIC,Notebook1);
    wxButton* ButtonRemoveScript=(wxButton*)wxWindow::FindWindowById(baseid+REMOVE_SCRIPT_BUTTON,Notebook1);
    int cnt=0;
    for( wxXmlNode* e=n->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() == _("listitem")) {
            ListBoxPlay->InsertItem(cnt,e->GetAttribute(wxT("name"), wxT("")));
            ListBoxPlay->SetItem(cnt,1,e->GetAttribute(wxT("delay"), wxT("0")));
            cnt++;
        } else if (e->GetName() == _("script")) {
            ButtonRemoveScript->Show();
            TextCtrlLogic->Show();
            TextCtrlLogic->ChangeValue( e->GetNodeContent() );
        }
    }
    ListBoxPlay->SetColumnWidth(0,wxLIST_AUTOSIZE);
    ScanForFiles();
}

void xLightsFrame::OnMenuItemRefreshSelected(wxCommandEvent& event)
{
    ScanForFiles();
}

wxWindow* xLightsFrame::FindNotebookControl(int nbidx, PlayListIds id) {
    return wxWindow::FindWindowById(1000*nbidx+id, Notebook1);
}

void xLightsFrame::RunPlaylist(int nbidx, wxString& script)
{
    wxString PageName=Notebook1->GetPageText(nbidx);
    TextCtrlLog->AppendText(_("At: ") + wxDateTime::Now().FormatTime() + _("\n"));
    TextCtrlLog->AppendText(_("Starting playlist ") + PageName + _("\n"));
    if (basic.IsRunning()) {
        SendToLogAndStatusBar(_("ERROR: unable to start - another playlist is already running!"));
        return;
    }
    wxCheckBox* MovieMode=(wxCheckBox*)FindNotebookControl(nbidx,CHKBOX_MOVIEMODE);
    if (script.IsEmpty()) {
        SendToLogAndStatusBar(_("ERROR: no script to run!"));
        return;
    }
    if (!script.EndsWith(_("\n"))) script += _("\n"); // ensure script ends with a newline
    if (basic.setScript(PageName.mb_str(wxConvUTF8), script.mb_str(wxConvUTF8))) {
        basic.run();
        if (MovieMode->GetValue()) {
            PlayerDlg->MediaCtrl->ShowPlayerControls(wxMEDIACTRLPLAYERCONTROLS_NONE);
            PlayerDlg->Show();
            PlayerDlg->ShowFullScreen(true, wxFULLSCREEN_ALL);
        }
    } else {
        SendToLogAndStatusBar(_("Error in playlist script"));
    }
}

void xLightsFrame::SendToLogAndStatusBar(const wxString& msg)
{
    TextCtrlLog->AppendText(msg + _("\n"));
    StatusBar1->SetStatusText(msg);
}

wxString xLightsFrame::OnOffString(bool b)
{
    return b ? wxT("on") : wxT("off");
}

wxString xLightsFrame::CreateScript(wxString ListName, bool Repeat, bool FirstItemOnce, bool LastItemOnce, bool LightsOff, bool Random)
{
    wxString script,loopsize;
    wxString endoflist = Repeat ? wxT("180") : wxT("400");
    wxString loopstart = FirstItemOnce ? wxT("2") : wxT("1");
    wxString loopend = LastItemOnce ? wxT("PLAYLISTSIZE-1") : wxT("PLAYLISTSIZE");
    if (FirstItemOnce && LastItemOnce) {
        loopsize=wxT("PLAYLISTSIZE-2");
    } else if (FirstItemOnce || LastItemOnce) {
        loopsize=wxT("PLAYLISTSIZE-1");
    } else {
        loopsize=wxT("PLAYLISTSIZE");
    }

    script.Append(_("100 REM *\n"));
    script.Append(_("101 REM * Created: ") + wxDateTime::Now().Format() + _("\n"));
    script.Append(_("102 REM * Random: ") + OnOffString(Random) + _("\n"));
    script.Append(_("103 REM * Repeat: ") + OnOffString(Repeat) + _("\n"));
    script.Append(_("104 REM * First Item Once: ") + OnOffString(FirstItemOnce) + _("\n"));
    script.Append(_("105 REM * Last Item Once: ") + OnOffString(LastItemOnce) + _("\n"));
    script.Append(_("106 REM *\n"));
    script.Append(_("110 LET ListName$=\"") + ListName + _("\"\n"));
    script.Append(_("120 SETPLAYLIST ListName$\n"));
    if (FirstItemOnce) {
        script.Append(_("130 ONPLAYBACKEND 140\n"));
        script.Append(_("131 PRINT \"At:\", FORMATDATETIME$(NOW,5)\n"));
        script.Append(_("132 PRINT \"Playing:\",ITEMNAME$(1)\n"));
        script.Append(_("133 PLAYITEM 1\n"));
        script.Append(_("134 WAIT\n"));
    }
    script.Append(_("140 ONPLAYBACKEND 300\n"));

    if (Random) {
        script.Append(_("170 IF ") + loopsize + _(">1 THEN 176\n"));
        script.Append(_("172 PRINT \"ERROR: not enough items in playlist to support random playback\"\n"));
        script.Append(_("174 GOTO 400\n"));
        script.Append(_("176 LET LastItemPlayed=-1\n"));
        script.Append(_("178 DIM PLAYED(PLAYLISTSIZE)\n"));
        script.Append(_("180 FOR I=1 TO PLAYLISTSIZE\n"));
        script.Append(_("182 LET PLAYED(I)=0\n"));
        script.Append(_("184 NEXT I\n"));
        script.Append(_("186 LET PlayCount=0\n"));
        script.Append(_("188 GOTO 300\n"));
        script.Append(_("200 REM *\n"));
        script.Append(_("201 REM * Play item NextItem\n"));
        script.Append(_("202 REM *\n"));
        script.Append(_("210 LET LastItemPlayed=NextItem\n"));
        script.Append(_("215 PRINT \"At:\", FORMATDATETIME$(NOW,5)\n"));
        script.Append(_("220 PRINT \"Playing:\",ITEMNAME$(NextItem)\n"));
        script.Append(_("230 PLAYITEM NextItem\n"));
        script.Append(_("240 WAIT\n"));
        script.Append(_("300 REM *\n"));
        script.Append(_("301 REM * Jump here at end of song or sequence\n"));
        script.Append(_("302 REM *\n"));
        if (LightsOff) script.Append(_("305 LIGHTSOFF\n"));
        script.Append(_("310 IF SECONDSREMAINING <= 0 THEN 400\n"));
        script.Append(_("320 IF PlayCount>=") + loopsize + _(" THEN ") + endoflist + _("\n"));
        script.Append(_("330 LET NextItem=RND(") + loopsize + _(")+") + loopstart + _("\n"));
        script.Append(_("340 IF PLAYED(NextItem)>0 THEN 330\n"));
        script.Append(_("345 IF LastItemPlayed=NextItem THEN 330\n"));
        script.Append(_("350 LET PLAYED(NextItem)=1\n"));
        script.Append(_("360 LET PlayCount=PlayCount+1\n"));
        script.Append(_("370 GOTO 200\n"));
    } else {
        script.Append(_("180 LET NextItem=") + loopstart + _("\n"));
        script.Append(_("200 REM *\n"));
        script.Append(_("201 REM * Play item NextItem\n"));
        script.Append(_("202 REM *\n"));
        script.Append(_("210 LET LastItemPlayed=NextItem\n"));
        script.Append(_("215 PRINT \"At:\", FORMATDATETIME$(NOW,5)\n"));
        script.Append(_("220 PRINT \"Playing:\",ITEMNAME$(NextItem)\n"));
        script.Append(_("230 PLAYITEM NextItem\n"));
        script.Append(_("240 WAIT\n"));
        script.Append(_("300 REM *\n"));
        script.Append(_("301 REM * Jump here at end of song or sequence\n"));
        script.Append(_("302 REM *\n"));
        if (LightsOff) script.Append(_("305 LIGHTSOFF\n"));
        script.Append(_("307 IF TXOVERFLOWCNT = 0 THEN 310\n"));
        script.Append(_("308 PRINT \"Serial transmit overflows:\",TXOVERFLOWCNT\n"));
        script.Append(_("310 IF SECONDSREMAINING <= 0 THEN 400\n"));
        script.Append(_("320 LET NextItem=LastItemPlayed+1\n"));
        script.Append(_("330 IF NextItem <= ") + loopend + _(" THEN 200\n"));
        if (Repeat) script.Append(_("340 GOTO 180\n"));
    }

    script.Append(_("400 REM *\n"));
    script.Append(_("401 REM Reached scheduled end time\n"));
    script.Append(_("402 REM *\n"));
    if (LastItemOnce) {
        script.Append(_("410 ONPLAYBACKEND 490\n"));
        script.Append(_("415 PRINT \"At:\", FORMATDATETIME$(NOW,5)\n"));
        script.Append(_("420 PRINT \"Playing:\",ITEMNAME$(PLAYLISTSIZE)\n"));
        script.Append(_("430 PLAYITEM PLAYLISTSIZE\n"));
        script.Append(_("440 WAIT\n"));
    }
    script.Append(_("490 LIGHTSOFF\n"));
    //wxMessageBox(script);
    return script;
}

void xLightsFrame::OnButtonSaveLogClick(wxCommandEvent& event)
{
    wxString filename = _("xSchedule-") + wxDateTime::Today().FormatISODate() + _(".log");
    wxFileDialog filedlg(this, _("Save log messages"), CurrentDir, filename, _("*.*"), wxFD_SAVE);
    if (filedlg.ShowModal() == wxID_OK) {
        if (TextCtrlLog->SaveFile( filedlg.GetPath() )) {
            StatusBar1->SetStatusText(_("Log saved successfully to: ")+filename);
        } else {
            StatusBar1->SetStatusText(_("An error occurred while saving: ")+filename);
        }
    }
}

void xLightsFrame::OnButtonClearLogClick(wxCommandEvent& event)
{
    TextCtrlLog->Clear();
}

void xLightsFrame::OnButtonRunPlaylistClick(wxCommandEvent& event)
{
    int selidx = Notebook1->GetSelection();
    int cnt = Notebook1->GetPageCount();
    if (cnt <= FixedPages) {
        wxMessageBox(_("Nothing to play. Create a playlist first."), _("Error"));
        return;
    }
    if (selidx < FixedPages) {
        wxMessageBox(_("Click on the desired playlist tab first."), _("Error"));
        return;
    }
    wxString userscript;
    wxTextCtrl* LogicCtl=(wxTextCtrl*)FindNotebookControl(selidx,PLAYLIST_LOGIC);
    if (LogicCtl && LogicCtl->IsShown()) {
        // run custom script
        userscript=LogicCtl->GetValue();
    } else {
        // get playback options, run generic script
        PlaybackOptionsDialog dialog(this);
        if (dialog.ShowModal() != wxID_OK) return;
        userscript=CreateScript(Notebook1->GetPageText(selidx),dialog.CheckBoxRepeat->IsChecked(),dialog.CheckBoxFirstItem->IsChecked(),dialog.CheckBoxLastItem->IsChecked(),false,dialog.CheckBoxRandom->IsChecked());
    }
    SetPlayMode(play_list);
    SecondsRemaining=1;
    RunPlaylist(selidx,userscript);
}

// convert hhmm string to seconds past midnight
// 23:59 is treated as 23:59:59
int xLightsFrame::Time2Seconds(const wxString& hhmm) {
    long t;
    if (hhmm == wxT("2359")) {
        return 24*60*60 - 1;
    } else if (hhmm.ToLong(&t)) {
        int hh=t / 100;
        int mm=t % 100;
        return hh*60*60+mm*60;
    } else {
        return 0;
    }
}


void xLightsFrame::PopulateShowDialog(AddShowDialog& dialog, wxSortedArrayString& SelectedDates) {

    // populate playlist selection
    int cnt = Notebook1->GetPageCount();
    for (int i=FixedPages; i < cnt; i++) {
        dialog.ChoicePlayList->AppendString(Notebook1->GetPageText(i));
    }

    // populate list of days
    int idx;
    wxString MonthDayStr;
    wxDateTime SchedDay =  ShowStartDate;
    while (SchedDay <= ShowEndDate) {
        MonthDayStr = SchedDay.Format(wxT("%m%d"));
        idx = dialog.ListBoxDates->Append(SchedDay.Format(wxT("%a, %b %d, %Y")));
        if (SelectedDates.Index(MonthDayStr) != wxNOT_FOUND) dialog.ListBoxDates->Select(idx);
        SchedDay += wxTimeSpan::Day();
    }
}


// returns false if user cancelled dialog
bool xLightsFrame::DisplayAddShowDialog(AddShowDialog& dialog)
{
    while (dialog.ShowModal() == wxID_OK) {
        if (!dialog.IsPlaylistSelected()) {
            wxMessageBox(_("Select a playlist."), _("Error"));
            continue;
        }

        if (!dialog.StartBeforeEnd()) {
            wxMessageBox(_("Start time must be before end time."), _("Error"));
            continue;
        }

        wxArrayInt selections;
        dialog.ListBoxDates->GetSelections(selections);
        if (selections.GetCount() == 0) {
            wxMessageBox(_("No dates selected."), _("Error"));
            continue;
        }

        return true;
    }
    return false;
}


void xLightsFrame::OnButtonAddShowClick(wxCommandEvent& event)
{
    size_t cnt = Notebook1->GetPageCount();
    if (cnt < FixedPages) {
        wxMessageBox(_("You must create at least one playlist before scheduling your show."), _("Error"));
        return;
    }
    AddShowDialog dialog(this);
    wxSortedArrayString SelectedDates; // leave empty - no dates pre-selected when adding
    PopulateShowDialog(dialog, SelectedDates);
    if (!DisplayAddShowDialog(dialog)) return;

    // user clicked ok, so add events
    wxDateTime SchedDay =  ShowStartDate;
    cnt = dialog.ListBoxDates->GetCount();
    wxString Playlist = dialog.ChoicePlayList->GetStringSelection();
    wxString PartialCode = dialog.PartialEventCode();
    for (size_t i=0; i < cnt; i++) {
        if (dialog.ListBoxDates->IsSelected(i)) AddShow(SchedDay,PartialCode,Playlist);
        SchedDay += wxTimeSpan::Day();
    }
    DisplaySchedule();
}

void xLightsFrame::UnpackSchedCode(const wxString& SchedCode, wxString& StartTime, wxString& EndTime, wxString& RepeatOptions, wxString& Playlist) {
    StartTime=SchedCode(4,4);
    EndTime=SchedCode(9,4);
    RepeatOptions=SchedCode(14,4);
    Playlist=SchedCode.Mid(18);
}

// populates ListBoxSched for single day
int xLightsFrame::DisplayScheduleOneDay(const wxDateTime& d, const wxTreeItemId& root) {
    wxString EventDesc, RepeatDesc, StartTime, EndTime, RepeatOptions, Playlist;
    int cnt=0;
    wxString MonthDayStr = d.Format(wxT("%m%d"));
    wxString MonthDayHeading =d.Format(wxT("%A, %B %d, %Y"));
    wxTreeItemId DayItemId = ListBoxSched->AppendItem(root, MonthDayHeading);
    ListBoxSched->SetItemBold(DayItemId);
    for (unsigned int i=0; i < ShowEvents.Count(); i++) {
        if (ShowEvents[i].StartsWith(MonthDayStr)) {
            UnpackSchedCode(ShowEvents[i], StartTime, EndTime, RepeatOptions, Playlist);
            if (RepeatOptions[0]=='R') {
                RepeatDesc=_("  (repeat");
                if (RepeatOptions[1]=='F') RepeatDesc+=_(", first once");
                if (RepeatOptions[2]=='L') RepeatDesc+=_(", last once");
                if (RepeatOptions[3]=='X') RepeatDesc+=_(", random");
                RepeatDesc+=_(")");
            } else if (RepeatOptions[3]=='X') {
                RepeatDesc=_("  (random)");
            } else {
                RepeatDesc.clear();
            }
            EventDesc=wxT("   ") + StartTime.Left(2) + wxT(":") + StartTime.Mid(2) + wxT(" to ") + EndTime.Left(2) + wxT(":") + EndTime.Mid(2) + wxT("  ") + Playlist + RepeatDesc;
            ListBoxSched->AppendItem(DayItemId, EventDesc, -1, -1, new SchedTreeData(ShowEvents[i]));
            cnt++;
        }
    }
    //if (cnt == 0) ListBoxSched->AppendItem(DayItemId, wxT("   <no show scheduled>"));
    return cnt;
}

// populates ListBoxSched based on contents of ShowEvents[]
void xLightsFrame::DisplaySchedule() {
    ListBoxSched->DeleteAllItems();
    ShowEvents.Sort();
    wxTreeItemId root = ListBoxSched->AddRoot(_("All Scheduled Events"));
    wxDateTime SchedDay =  ShowStartDate;
    while (SchedDay <= ShowEndDate) {
        DisplayScheduleOneDay(SchedDay, root);
        SchedDay += wxTimeSpan::Day();
    }
    ListBoxSched->ExpandAll();
    bool hasevents=!ShowEvents.IsEmpty();
    CheckBoxRunSchedule->Enable(hasevents);
    ButtonUpdateShow->Enable(hasevents);
    ButtonDeleteShow->Enable(hasevents);
    //ButtonDeselect->Enable(hasevents);
}


// adds the event to ShowEvents[]
void xLightsFrame::AddShow(const wxDateTime& d, const wxString& StartStop, const wxString& Playlist) {
    wxString MonthDayStr = d.Format(wxT("%m%d"));
    wxString SchedCode = MonthDayStr + StartStop + Playlist;
    ShowEvents.Add(SchedCode);
    UnsavedChanges=true;
}


void xLightsFrame::OnButtonUpdateShowClick(wxCommandEvent& event)
{
    wxString FirstSchedCode, SchedCode, StartTime, EndTime, RepeatOptions, Playlist, PartialCode;
    wxArrayTreeItemIds selections;
    SchedTreeData *SchedPtr;
    wxSortedArrayString SelectedDates;
    int cnt=ListBoxSched->GetSelections(selections);
    for (int i=0; i<cnt; i++) {
        SchedPtr = (SchedTreeData*)ListBoxSched->GetItemData(selections[i]);
        if (SchedPtr) {
            SchedCode=SchedPtr->GetString();
            SelectedDates.Add(SchedCode.Left(4));
            if (FirstSchedCode.IsEmpty()) FirstSchedCode = SchedCode;
        }
    }
    if (FirstSchedCode.length() == 0) {
        wxMessageBox(_("You must select at least one item to edit."));
        return;
    }

    AddShowDialog dialog(this);
    PopulateShowDialog(dialog, SelectedDates);

    // allow all fields to be updated
    UnpackSchedCode(FirstSchedCode, StartTime, EndTime, RepeatOptions, Playlist);
    dialog.ChoicePlayList->SetStringSelection(Playlist);

    dialog.SpinCtrlStartHour->SetValue(StartTime.Left(2));
    dialog.SpinCtrlStartMinute->SetValue(StartTime.Mid(2));
    dialog.SpinCtrlEndHour->SetValue(EndTime.Left(2));
    dialog.SpinCtrlEndMinute->SetValue(EndTime.Mid(2));

    dialog.CheckBoxRepeat->SetValue(RepeatOptions[0]=='R');
    dialog.CheckBoxFirstItem->SetValue(RepeatOptions[1]=='F');
    dialog.CheckBoxLastItem->SetValue(RepeatOptions[2]=='L');
    dialog.CheckBoxRandom->SetValue(RepeatOptions[3]=='X');

    if (!DisplayAddShowDialog(dialog)) return;

    // user clicked ok, so delete old events, then add new events
    DeleteSelectedShows();
    wxDateTime SchedDay =  ShowStartDate;
    cnt = dialog.ListBoxDates->GetCount();
    Playlist = dialog.ChoicePlayList->GetStringSelection();
    PartialCode = dialog.PartialEventCode();
    for (int i=0; i < cnt; i++) {
        if (dialog.ListBoxDates->IsSelected(i)) AddShow(SchedDay,PartialCode,Playlist);
        SchedDay += wxTimeSpan::Day();
    }
    DisplaySchedule();
}

// returns the number of shows that were deleted
int xLightsFrame::DeleteSelectedShows()
{
    wxArrayTreeItemIds selections;
    SchedTreeData *SchedCode;
    int delcnt=0;
    int cnt=ListBoxSched->GetSelections(selections);
    for (int i=cnt-1; i>=0; i--) {
        SchedCode = (SchedTreeData*)ListBoxSched->GetItemData(selections[i]);
        if (SchedCode) {
            ShowEvents.Remove(SchedCode->GetString());
            delcnt++;
        }
    }
    return delcnt;
}

void xLightsFrame::OnButtonDeleteShowClick(wxCommandEvent& event)
{
    int delcnt = DeleteSelectedShows();
    if (delcnt == 0) {
        wxMessageBox(_("You must select one or more scheduled items first!"));
    } else {
        DisplaySchedule();
        UnsavedChanges=true;
    }
}

void xLightsFrame::CheckRunSchedule()
{
    if (play_mode == play_sched) basic.halt();
    bool notrunning=!CheckBoxRunSchedule->IsChecked();
    bool hasevents=!ShowEvents.IsEmpty();
    ButtonAddShow->Enable(notrunning);
    ButtonUpdateShow->Enable(notrunning && hasevents);
    ButtonDeleteShow->Enable(notrunning && hasevents);
    if (CheckBoxRunSchedule->IsChecked()) {
        ForceScheduleCheck();
        StatusBar1->SetStatusText(_("Starting scheduler"), 1);
    } else {
        StatusBar1->SetStatusText(_("Scheduler not running"), 1);
    }
}

void xLightsFrame::OnCheckBoxRunScheduleClick(wxCommandEvent& event)
{
    if (CheckBoxRunSchedule->IsChecked() && !CheckBoxLightOutput->IsChecked()) {
        CheckBoxRunSchedule->SetValue(false);
        int result = wxMessageBox(_("Light output is not enabled! Do you really want to run the schedule?"),_("Warning"),wxCENTER | wxYES_NO);
        if (result != wxYES) return;
        CheckBoxRunSchedule->SetValue(true);
    }
    CheckRunSchedule();
    long RunFlag=CheckBoxRunSchedule->IsChecked() ? 1 : 0;
    // Get CurrentDir
    wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));
    config->Write(_("RunSchedule"), RunFlag);
}


void xLightsFrame::OnMenuItemCustomScriptSelected(wxCommandEvent& event)
{
    int nbIdx=Notebook1->GetSelection();
    wxTextCtrl* TextCtrlLogic=(wxTextCtrl*)FindNotebookControl(nbIdx,PLAYLIST_LOGIC);
    if (TextCtrlLogic == 0) {
        wxMessageBox(_("Must be on a playlist tab"));
        return;
    }
    // get playback options
    PlaybackOptionsDialog dialog(this);
    wxString nbName=Notebook1->GetPageText(nbIdx);
    if (dialog.ShowModal() != wxID_OK) return;
    TextCtrlLogic->ChangeValue(CreateScript(nbName,dialog.CheckBoxRepeat->IsChecked(),dialog.CheckBoxFirstItem->IsChecked(),dialog.CheckBoxLastItem->IsChecked(),false,dialog.CheckBoxRandom->IsChecked()));
    TextCtrlLogic->Show();
    wxButton* ButtonRemoveScript=(wxButton*)FindNotebookControl(nbIdx,REMOVE_SCRIPT_BUTTON);
    ButtonRemoveScript->Show();
    UnsavedChanges=true;
}

void xLightsFrame::OnButtonRemoveScriptClick(wxCommandEvent& event)
{
    int nbIdx=Notebook1->GetSelection();
    wxTextCtrl* TextCtrlLogic=(wxTextCtrl*)FindNotebookControl(nbIdx,PLAYLIST_LOGIC);
    wxButton* ButtonRemoveScript=(wxButton*)FindNotebookControl(nbIdx,REMOVE_SCRIPT_BUTTON);
    wxMessageDialog confirm(this, _("Are you sure you want to remove the script?\n\nScripts are useful for interactive displays, or when\nyou want your playlist to play back out of order.\nOtherwise, scripts are not necessary."), _("Confirm"), wxYES|wxNO);
    if (confirm.ShowModal() == wxID_YES) {
        TextCtrlLogic->Hide();
        ButtonRemoveScript->Hide();
        UnsavedChanges=true;
    }
}

void xLightsFrame::UpdateShowDates(const wxDateTime& NewStart, const wxDateTime NewEnd)
{
    ShowStartDate = NewStart.GetDateOnly();
    ShowEndDate = NewEnd.GetDateOnly();
    StaticTextShowStart->SetLabel(ShowStartDate.FormatDate());
    StaticTextShowEnd->SetLabel(ShowEndDate.FormatDate());
}

void xLightsFrame::OnButtonShowDatesChangeClick(wxCommandEvent& event)
{
    ShowDatesDialog dialog(this);
    dialog.CalendarCtrlStart->SetDate(ShowStartDate);
    dialog.CalendarCtrlEnd->SetDate(ShowEndDate);
    while (dialog.ShowModal() == wxID_OK) {
        wxDateTime NewStart = dialog.CalendarCtrlStart->GetDate();
        wxDateTime NewEnd = dialog.CalendarCtrlEnd->GetDate();
        wxTimeSpan diff = NewEnd - NewStart;
        int days = diff.GetDays();
        if (days < 0) {
            wxMessageBox(_("Show end date must be on or after the start date"),_("Error"));
        } else if (days > 100) {
            wxMessageBox(_("Show schedule must span 100 days or less"),_("Error"));
        } else {
            UpdateShowDates(NewStart,NewEnd);
            DisplaySchedule();
            UnsavedChanges=true;
            break;
        }
    }
}

// drop a list item (start row is in DragRowIdx)
void xLightsFrame::OnPlayListDragEnd(wxMouseEvent& event)
{
  wxListItem column1;
  wxPoint pos = event.GetPosition();  // must reference the event
  int flags = wxLIST_HITTEST_ONITEM;
  long index = DragListBox->HitTest(pos,flags,NULL); // got to use it at last
  if(index >= 0 && index != DragRowIdx){ // valid and not the same as start
    // move/copy the list control items
    column1.SetId(DragRowIdx);
    column1.SetColumn(1);
    column1.SetMask(wxLIST_MASK_TEXT);
    DragListBox->GetItem(column1);
    if (index > DragRowIdx) index++;
    long newidx = DragListBox->InsertItem(index,DragListBox->GetItemText(DragRowIdx));
    DragListBox->SetItem(newidx,1,column1.GetText());
    if (newidx < DragRowIdx) DragRowIdx++;
    DragListBox->DeleteItem(DragRowIdx);
    UnsavedChanges=true;
  }
  // restore cursor
  DragListBox->SetCursor(wxCursor(*wxSTANDARD_CURSOR));
  // disconnect both functions
  DragListBox->Disconnect(wxEVT_LEFT_UP,
    wxMouseEventHandler(xLightsFrame::OnPlayListDragEnd));
  DragListBox->Disconnect(wxEVT_LEAVE_WINDOW,
    wxMouseEventHandler(xLightsFrame::OnPlayListDragQuit));
}

// abort dragging a list item because user has left window
void xLightsFrame::OnPlayListDragQuit(wxMouseEvent& event)
{
  // restore cursor and disconnect unconditionally
  DragListBox->SetCursor(wxCursor(*wxSTANDARD_CURSOR));
  DragListBox->Disconnect(wxEVT_LEFT_UP,
    wxMouseEventHandler(xLightsFrame::OnPlayListDragEnd));
  DragListBox->Disconnect(wxEVT_LEAVE_WINDOW,
    wxMouseEventHandler(xLightsFrame::OnPlayListDragQuit));
}

void xLightsFrame::OnPlayListBeginDrag(wxListEvent& event)
{
  DragRowIdx = event.GetIndex();	// save the start index
  DragListBox = (wxListCtrl*) event.GetEventObject();
  // do some checks here to make sure valid start
  // ...
  // trigger when user releases left button (drop)
  DragListBox->Connect(wxEVT_LEFT_UP,
    wxMouseEventHandler(xLightsFrame::OnPlayListDragEnd), NULL,this);
  // trigger when user leaves window to abort drag
  DragListBox->Connect(wxEVT_LEAVE_WINDOW,
    wxMouseEventHandler(xLightsFrame::OnPlayListDragQuit), NULL,this);
  // give visual feedback that we are doing something
  DragListBox->SetCursor(wxCursor(wxCURSOR_HAND));
}
