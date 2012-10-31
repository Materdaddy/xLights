/***************************************************************
 * Name:      xScheduleMain.h
 * Purpose:   Defines Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-05-15
 * Copyright: 2010 by Matt Brown
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

#ifndef XSCHEDULEMAIN_H
#define XSCHEDULEMAIN_H

//(*Headers(xScheduleFrame)
#include <wx/bmpbuttn.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/aui/aui.h>
#include <wx/textctrl.h>
#include <wx/treectrl.h>
//*)

#include <wx/msgdlg.h>
#include <wx/config.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/bmpbuttn.h>
#include <wx/artprov.h>
#include <wx/checkbox.h>
#include <wx/checklst.h>
#include <wx/datetime.h>
#include <wx/file.h>
#include <wx/timer.h>
#include <wx/xml/xml.h>
#include <wx/listctrl.h>

#include <set>
#include <map>
#include <vector>
#include <string>

#include "PlayerFrame.h"
#include "DelListDialog.h"
#include "WizardDialog.h"
#include "AddShowDialog.h"
#include "TestDialog.h"
#include "StopDialog.h"
#include "ShowDatesDialog.h"
#include "../include/globals.h"
#include "../include/xlights_out.cpp"

enum LOR_ACTIONS {
    LOR_INTENSITY,
    LOR_TWINKLE,
    LOR_SHIMMER,
    LOR_UNKNOWN
};

class LorEventClass
{
    public:

    LorEventClass(int net_num, int ch_index, int End_Centi, LOR_ACTIONS act, int Start_Intensity, int End_Intesity) {
        netnum=net_num;
        chindex=ch_index;
        EndCentiSec=End_Centi;
        action=act;
        StartIntensity=Start_Intensity;
        EndIntesity=End_Intesity;
    }

    int netnum;
    int chindex;
    int EndCentiSec;
    int StartIntensity;
    int EndIntesity;
    LOR_ACTIONS action;
};

class SchedTreeData : public wxTreeItemData
{
protected:
    wxString eventString;

public:
    SchedTreeData(const wxString& EventData = wxT("")) { eventString = EventData; };
    wxString GetString() { return eventString; };
};

typedef std::set<std::pair<int, int> > GridSelection;
typedef std::multimap<int, LorEventClass* > LorEventMap;
typedef std::pair<int, LorEventClass* > LorEventPair;

class xScheduleFrame: public wxFrame
{
    public:

        // these are added to 1000*pagenum to get the control id
        enum PlayListIds {
            CHKBOX_AUDIO,
            CHKBOX_VIDEO,
            CHKBOX_LOR,
            CHKBOX_VIXEN,
            CHKBOX_XLIGHTS,
            CHKBOX_MOVIEMODE,
            UP_BUTTON,
            DOWN_BUTTON,
            INFO_BUTTON,
            PLAY_BUTTON,
            DELAY_BUTTON,
            CREATE_SCRIPT,
            PLAYLIST_LISTBOX,
            PLAYLIST_FILES,
            PLAYLIST_ADD,
            PLAYLIST_ADD_ALL,
            PLAYLIST_DELETE,
            PLAYLIST_DELETE_ALL,
            SCRIPT_HELP,
            PLAYLIST_LOGIC,
            REMOVE_SCRIPT_BUTTON
        };

        xScheduleFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~xScheduleFrame();

        xOutput* xout;
        long SecondsRemaining, EndTimeSec;
        int TxOverflowCnt;
        void BasicPrompt(char* prompt, char* buff, int size);
        void BasicOutput(char *msg);
        void BasicError(const char *msg);
        char ExtType(const wxString& ext);
        void Play(wxString& filename, long delay);
        void StopPlayback();
        void StartScript(const char *scriptname);
        void EndScript(const char *scriptname);
        int  FindNotebookPage(wxString& pagename);
        wxWindow* FindNotebookControl(int nbidx, PlayListIds id);

    private:

        //(*Handlers(xScheduleFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnAuiToolBarItemAddClick(wxCommandEvent& event);
        void OnAuiToolBarItemDelClick(wxCommandEvent& event);
        void OnMenuItemAddListSelected(wxCommandEvent& event);
        void OnMenuItemRenameListSelected(wxCommandEvent& event);
        void OnMenuItemDelListSelected(wxCommandEvent& event);
        void OnAuiToolBarItemHelpClick(wxCommandEvent& event);
        void OnAuiToolBarItemSaveClick(wxCommandEvent& event);
        void OnButtonSetClick(wxCommandEvent& event);
        void OnButtonClearClick(wxCommandEvent& event);
        void OnMenuItemRefreshSelected(wxCommandEvent& event);
        void OnNotebook1PageChanged(wxNotebookEvent& event);
        void OnAuiToolBarItemStopClick(wxCommandEvent& event);
        void OnButtonSaveLogClick(wxCommandEvent& event);
        void OnButtonClearLogClick(wxCommandEvent& event);
        void OnAuiToolBarItemPlayClick(wxCommandEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnChoice1Select(wxCommandEvent& event);
        void OnButtonAddShowClick(wxCommandEvent& event);
        void OnButtonUpdateShowClick(wxCommandEvent& event);
        void OnButtonDeleteShowClick(wxCommandEvent& event);
        void OnButtonDeselectClick(wxCommandEvent& event);
        void OnCheckBoxRunScheduleClick(wxCommandEvent& event);
        void OnBitmapButtonSchedInfoClick(wxCommandEvent& event);
        void OnMenuItemCustomScriptSelected(wxCommandEvent& event);
        void OnMenuItemConvert2VixenSelected(wxCommandEvent& event);
        void OnMenuItemSave2ConductorSelected(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnAuiToolBarItemTestClick(wxCommandEvent& event);
        void OnButtonShowDatesChangeClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(xScheduleFrame)
        static const long ID_AUITOOLBARITEM_ADD;
        static const long ID_AUITOOLBARITEM_DEL;
        static const long ID_AUITOOLBARITEM_HELP;
        static const long ID_AUITOOLBARITEM_SAVE;
        static const long ID_AUITOOLBARITEM_STOP;
        static const long ID_AUITOOLBARITEM_PLAY;
        static const long ID_AUITOOLBARITEM_TEST;
        static const long ID_AUITOOLBAR1;
        static const long ID_PANEL2;
        static const long ID_TREECTRL1;
        static const long ID_CHECKBOX_RUN_SCHEDULE;
        static const long ID_BUTTON_ADD_SHOW;
        static const long ID_BITMAPBUTTON_SCHED_INFO;
        static const long ID_BUTTON2;
        static const long ID_BUTTON_DELETE_SHOW;
        static const long ID_BUTTON_DESELECT;
        static const long ID_STATICTEXT2;
        static const long ID_BUTTON_SHOW_DATES_CHANGE;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_PANEL_CAL;
        static const long ID_BUTTON_CLEARLOG;
        static const long ID_BUTTON_SAVELOG;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL_LOG;
        static const long ID_PANEL_LOG;
        static const long ID_NOTEBOOK1;
        static const long ID_PANEL1;
        static const long idMenuSave;
        static const long idMenuQuit;
        static const long idMenuAddList;
        static const long idMenuRenameList;
        static const long idMenuDelList;
        static const long ID_MENUITEM1;
        static const long idCustomScript;
        static const long idMenuHelpContent;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)
        static const long ID_TIMER;
        static const long ID_SCHED_TIMER;
        static const long ID_PLAYER_DIALOG;

        //(*Declarations(xScheduleFrame)
        wxAuiToolBar* AuiToolBar1;
        wxStaticText* StaticTextShowEnd;
        wxButton* ButtonDeleteShow;
        wxPanel* Panel1;
        wxButton* ButtonClearLog;
        wxPanel* PanelLog;
        wxStatusBar* StatusBar1;
        wxButton* ButtonUpdateShow;
        wxTreeCtrl* ListBoxSched;
        wxCheckBox* CheckBoxRunSchedule;
        wxBitmapButton* BitmapButtonSchedInfo;
        wxButton* ButtonSaveLog;
        wxStaticText* StaticText1;
        wxStaticText* StaticTextShowStart;
        wxPanel* Panel2;
        wxPanel* PanelCal;
        wxStaticText* StaticText3;
        wxTextCtrl* TextCtrlLog;
        wxButton* ButtonAddShow;
        wxButton* ButtonDeselect;
        wxButton* ButtonShowDatesChange;
        wxStaticText* StaticText4;
        wxStaticText* StaticText2;
        wxMenuItem* MenuItemRefresh;
        wxNotebook* Notebook1;
        wxAuiManager* AuiManager1;
        //*)

        enum SeqPlayerStates {
            NO_SEQ,
            STARTING_MEDIA,
            STARTING_LOR,
            STARTING_VIX,
            PLAYING_MEDIA,
            PLAYING_LOR,
            PLAYING_VIX,
            STARTING_LOR_ANIM,
            STARTING_VIX_ANIM,
            PLAYING_LOR_ANIM,
            PLAYING_VIX_ANIM,
            PAUSE_LOR,
            PAUSE_VIX,
            DELAY_AFTER_PLAY
        };

        enum PlayModes {
            NO_PLAY,
            SINGLE,
            PLAYLIST,
            SCHEDULE
        };

        wxString CurrentDir;
        wxFileName networkFile;
        wxFileName scheduleFile;
        PlayerFrame* PlayerDlg;
        bool UnsavedChanges;
        bool PortsOK;
        LorEventMap LorEvents;
        std::vector<int> LorLastUnit;
        long LorMapping;
        wxTimer timer;
        wxTimer schedtimer;
        wxDateTime starttime;
        wxString LastMoDay;
        PlayModes PlayMode;
        SeqPlayerStates SeqPlayerState;
        long VixEventPeriod;
        int VixNumPeriods;
        long VixNumChannels;
        long DelayAfterPlayMSEC;
        ChannelVector VixNetwork2; // accounts for channel re-ordering in Vixen
        wxString mediaFilename;
        wxArrayString ShowEvents;
        wxUint8* VixEventData;
        wxUint8 decoding_table[256];
        TestDialog* pTestDialog;
        wxDateTime ShowStartDate,ShowEndDate;
        long DragRowIdx;
        wxListCtrl* DragListBox;

        void AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels);
        wxString LorNetDesc(int netnum);
        wxString LorChDesc(int ch);
        void LoadNetworkFile();
        void LoadScheduleFile();
        void LoadSchedule(wxXmlNode* n);
        void LoadPlaylists(wxXmlNode* n);
        void LoadPlaylist(wxXmlNode* n);
        void SaveFile();
        void ScanForFiles();
        void AddPlaylist(const wxString& name);
        wxString OnOffString(bool b);
        wxString CreateScript(wxString ListName, bool Repeat, bool FirstItemOnce, bool LastItemOnce, bool LightsOff, bool Random);
        bool CheckPorts();
        wxString VixenInfo();
        bool LoadLorFile(wxString& FileName);
        bool LoadXlightsFile(wxString& FileName);
        bool LoadVixenFile(wxString& FileName);
        bool LoadVixenProfile(const wxString& ProfileName);
        void PlayLorFile(wxString& FileName);
        void PlayVixenFile(wxString& FileName);
        void PlayXlightsFile(wxString& FileName);
        void LoadLorChannels(wxXmlNode* n);
        void LoadLorChannel(wxXmlNode* n, int netnum, int chindex);
        void SetMediaFilename(const wxString& filename);
        long DiffSeconds(wxString& strTime, wxTimeSpan& tsCurrent);
        void ResetTimer(SeqPlayerStates newstate);
        void TimerNoPlay();
        void RunPlaylist(int nbidx, wxString& script);
        void ShowPlayerSingle();
        void PlayerError(const wxString& msg);
        void SendToLogAndStatusBar(const wxString& msg);
        //std::string base64_decode(const wxString& encoded_string);
        void build_decoding_table();
        wxUint8 *base64_decode(const wxString& data, long *output_length);
        int Time2Seconds(const wxString& hhmm);
        void AddShow(const wxDateTime& d, const wxString& StartStop, const wxString& Playlist);
        void DisplaySchedule();
        int DisplayScheduleOneDay(const wxDateTime& d, const wxTreeItemId& root);
        void PopulateShowDialog(AddShowDialog& dialog, wxSortedArrayString& SelectedDates);
        void UnpackSchedCode(const wxString& SchedCode, wxString& StartTime, wxString& EndTime, wxString& RepeatOptions, wxString& Playlist);
        void ForceScheduleCheck();
        void CheckRunSchedule();
        void PerformTesting();
        double rand01();
        long GetSelectedItem(wxListCtrl* ListBoxPlay);
        void UpdateShowDates(const wxDateTime& NewStart, const wxDateTime NewEnd);
        bool DisplayAddShowDialog(AddShowDialog& dialog);
        int DeleteSelectedShows();

        void OnTimer(wxTimerEvent& event);
        void OnSchedTimer(wxTimerEvent& event);
        void OnFileTypeButtonClicked();
        void OnButtonRunPlaylistClick();
        void OnButtonPlayItemClick();
        void OnScriptHelpClick(wxCommandEvent& event);
        void OnButtonUpClick();
        void OnButtonDownClick();
        void OnButtonInfoClick();
        void OnButtonSetDelayClick();
        void OnButtonPlaylistAddClick();
        void OnButtonPlaylistAddAllClick();
        void OnButtonPlaylistDeleteClick();
        void OnButtonPlaylistDeleteAllClick();
        void OnButtonRemoveScriptClick(wxCommandEvent& event);
        void OnMediaEnd( wxCommandEvent &event );
        void OnPlayListBeginDrag(wxListEvent& event);
        void OnDragEnd(wxMouseEvent& event);
        void OnDragQuit(wxMouseEvent& event);

        DECLARE_EVENT_TABLE()
};

#endif // XSCHEDULEMAIN_H
