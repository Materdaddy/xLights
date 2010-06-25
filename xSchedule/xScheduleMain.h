/***************************************************************
 * Name:      xScheduleMain.h
 * Purpose:   Defines Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-05-15
 * Copyright: Matt Brown (dowdybrown.com)
 * License:
 **************************************************************/

#ifndef XSCHEDULEMAIN_H
#define XSCHEDULEMAIN_H

//(*Headers(xScheduleFrame)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
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

#include <set>

#include "PlayerDialog.h"
#include "NewListDialog.h"
#include "DelListDialog.h"
#include "RenListDialog.h"
#include "../include/globals.h"
#include "../include/tinyxml.h"

typedef std::set<std::pair<int, int> > GridSelection;

class xScheduleFrame: public wxFrame
{
    public:

        xScheduleFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~xScheduleFrame();

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
        //*)

        //(*Identifiers(xScheduleFrame)
        static const long ID_AUITOOLBARITEM_ADD;
        static const long ID_AUITOOLBARITEM_DEL;
        static const long ID_AUITOOLBARITEM_HELP;
        static const long ID_AUITOOLBARITEM_SAVE;
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
        static const long ID_NOTEBOOK1;
        static const long ID_PANEL1;
        static const long idMenuSave;
        static const long idMenuQuit;
        static const long idMenuAddList;
        static const long idMenuRenameList;
        static const long idMenuDelList;
        static const long idMenuHelpContent;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(xScheduleFrame)
        wxAuiManager* AuiManager1;
        wxAuiToolBar* AuiToolBar1;
        wxNotebook* Notebook1;
        wxStaticText* StaticText6;
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

        wxString CurrentDir;
        wxFileName networkFile;
        wxFileName scheduleFile;
        wxDateTime CalStart;
        PlayerDialog* PlayerDlg;
        bool UnsavedChanges;

        wxString GetAttribute(TiXmlElement* e, const char *attr);
        void SetGridCell(const int& row, const int& col, wxString& playlist, wxString& timestart, wxString& timeend);
        void AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels);
        void LoadNetworkFile();
        void LoadScheduleFile();
        void LoadSchedule(TiXmlElement* n);
        void LoadPlaylists(TiXmlElement* n);
        void LoadPlaylist(TiXmlElement* n);
        void SaveFile();
        void ScanForFiles();
        char ExtType(const wxString& ext);
        void AddPlaylist(const wxString& name);
        void OnButtonPlayClick();
        void OnButtonUpClick();
        void OnButtonDownClick();
        GridSelection getGridSelection(wxGrid & grid);

        // these are added to 1000*pagenum to get the control id
        enum PlayListIds {
            CHKBOX_AUDIO,
            CHKBOX_VIDEO,
            CHKBOX_LOR,
            CHKBOX_VIXEN,
            UP_BUTTON,
            DOWN_BUTTON,
            PLAY_BUTTON,
            PLAYLIST
        };

        DECLARE_EVENT_TABLE()
};

#endif // XSCHEDULEMAIN_H
