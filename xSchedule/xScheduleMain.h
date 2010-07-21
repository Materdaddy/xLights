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
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/aui/aui.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

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

#include <set>
#include <map>
#include <vector>

#include "PlayerDialog.h"
#include "NewListDialog.h"
#include "DelListDialog.h"
#include "RenListDialog.h"
#include "../include/globals.h"
#include "../include/tinyxml.h"

class LorEventClass
{
    public:

    LorEventClass(int net_num, int ch_index, int End_Centi, TiXmlElement* xml_data) {
        netnum=net_num;
        chindex=ch_index;
        EndCentiSec=End_Centi;
        xmldata=xml_data;
    }

    int netnum;
    int chindex;
    int EndCentiSec;
    TiXmlElement* xmldata;
};

typedef std::set<std::pair<int, int> > GridSelection;
typedef std::multimap<int, LorEventClass* > LorEventMap;
typedef std::pair<int, LorEventClass* > LorEventPair;
typedef std::vector<std::pair<int, int> > VixChannelVector; // first is network #, second is channel #

class xScheduleFrame: public wxFrame
{
    public:

        xScheduleFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~xScheduleFrame();

        void BasicPrompt(char* prompt, char* buff, int size);
        void BasicOutput(char *msg);
        void BasicError(const char *msg);
        char ExtType(const wxString& ext);
        bool Play(wxString& filename);

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
        //*)

        //(*Identifiers(xScheduleFrame)
        static const long ID_AUITOOLBARITEM_ADD;
        static const long ID_AUITOOLBARITEM_DEL;
        static const long ID_AUITOOLBARITEM_HELP;
        static const long ID_AUITOOLBARITEM_SAVE;
        static const long ID_AUITOOLBARITEM_STOP;
        static const long ID_AUITOOLBAR1;
        static const long ID_PANEL2;
        static const long ID_CHOICE_PLAYLIST;
        static const long ID_STATICTEXT5;
        static const long ID_CHOICE_STARTTIME;
        static const long ID_STATICTEXT6;
        static const long ID_CHOICE_ENDTIME;
        static const long ID_BUTTON_SET;
        static const long ID_BUTTON_CLEAR;
        static const long ID_GRID1;
        static const long ID_PANEL_CAL;
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
        static const long idMenuHelpContent;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)
        static const long ID_TIMER;

        //(*Declarations(xScheduleFrame)
        wxAuiManager* AuiManager1;
        wxAuiToolBar* AuiToolBar1;
        wxNotebook* Notebook1;
        wxPanel* PanelLog;
        wxTextCtrl* TextCtrlLog;
        wxStaticText* StaticText6;
        wxMenuItem* MenuItemRefresh;
        wxButton* ButtonSet;
        wxPanel* Panel1;
        wxButton* ButtonClear;
        wxGrid* Grid1;
        wxChoice* ChoiceStartTime;
        wxStaticText* StaticText5;
        wxPanel* PanelCal;
        wxStatusBar* StatusBar1;
        wxPanel* Panel2;
        wxChoice* ChoicePlayList;
        wxChoice* ChoiceEndTime;
        //*)

        // these are added to 1000*pagenum to get the control id
        enum PlayListIds {
            CHKBOX_AUDIO,
            CHKBOX_VIDEO,
            CHKBOX_LOR,
            CHKBOX_VIXEN,
            UP_BUTTON,
            DOWN_BUTTON,
            PLAY_BUTTON,
            RUN_BUTTON,
            PLAYLIST,
            PLAYLIST_LOGIC
        };

        enum SeqPlayerStates {
            NO_SEQ,
            PLAYING_LOR,
            PLAYING_VIX,
            PAUSE_LOR,
            PAUSE_VIX
        };

        wxString CurrentDir;
        wxFileName networkFile;
        wxFileName scheduleFile;
        wxDateTime CalStart,CalEnd;
        wxString datefmt, timefmt;
        PlayerDialog* PlayerDlg;
        bool UnsavedChanges;
        bool PortsOK;
        LorEventMap LorEvents;
        wxTimer timer;
        wxDateTime starttime;
        SeqPlayerStates SeqPlayerState;
        int VixEventPeriod;
        int VixNumPeriods;
        int VixLastChannel;
        std::string VixEventData;
        VixChannelVector VixNetwork;

        wxString GetAttribute(TiXmlElement* e, const char *attr);
        void SetGridCell(const int& row, const int& col, wxString& playlist, wxString& timestart, wxString& timeend);
        void ClearGridCell(const int& row, const int& col);
        void AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels);
        void LoadNetworkFile();
        void LoadScheduleFile();
        void LoadSchedule(TiXmlElement* n);
        void LoadPlaylists(TiXmlElement* n);
        void LoadPlaylist(TiXmlElement* n);
        void SaveFile();
        void ScanForFiles();
        void AddPlaylist(const wxString& name);
        void OnButtonRunPlaylistClick();
        void OnButtonPlayItemClick();
        void OnButtonUpClick();
        void OnButtonDownClick();
        GridSelection getGridSelection(wxGrid & grid);
        void PlayLorFile(wxString& FileName);
        void PlayVixenFile(wxString& FileName);
        void LoadLorChannels(TiXmlElement* n);
        void LoadLorChannel(TiXmlElement* n, int netnum, int chindex);
        void OnTimer(wxTimerEvent& event);
        void ResetTimer(SeqPlayerStates newstate);
        void TimerNoPlay();
        std::string base64_decode(std::string const& encoded_string);

        DECLARE_EVENT_TABLE()
};

#endif // XSCHEDULEMAIN_H
