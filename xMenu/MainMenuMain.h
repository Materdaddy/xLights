/***************************************************************
 * Name:      MainMenuMain.h
 * Purpose:   Defines Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-02-27
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

#ifndef MAINMENUMAIN_H
#define MAINMENUMAIN_H

//(*Headers(MainMenuFrame)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dirdlg.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include <wx/config.h>
#include <wx/stdpaths.h>
#include "NetworkDialog.h"
#include "../include/globals.h"

#define MRU_LENGTH 4

class MainMenuFrame: public wxFrame
{
    public:

        MainMenuFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~MainMenuFrame();

    private:

        //(*Handlers(MainMenuFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnMenuOpenFolderSelected(wxCommandEvent& event);
        void OnButtonChannelSetupClick(wxCommandEvent& event);
        void OnButtonSequenceClick(wxCommandEvent& event);
        void OnButtonScheduleClick(wxCommandEvent& event);
        void OnButtonTestClick(wxCommandEvent& event);
        void OnButtonImportClick(wxCommandEvent& event);
        void OnButtonExportClick(wxCommandEvent& event);
        void OnButtonAnimationClick(wxCommandEvent& event);
        void OnButtonNetworkSetupClick(wxCommandEvent& event);
        void OnMenuItemHelpContentSelected(wxCommandEvent& event);
        void OnButtonLorMapClick(wxCommandEvent& event);
        void OnButtonFileConversionClick(wxCommandEvent& event);
        //*)

        void SetDir(const wxString& dirname);

        //(*Identifiers(MainMenuFrame)
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT2;
        static const long ID_BUTTON5;
        static const long ID_BUTTON_NETWORK_SETUP;
        static const long ID_BUTTON_SCHEDULE;
        static const long ID_BUTTON_FILE_CONVERSION;
        static const long ID_PANEL1;
        static const long idMenuOpen;
        static const long idMenuQuit;
        static const long idMenuHelpContent;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(MainMenuFrame)
        wxButton* ButtonFileConversion;
        wxStaticText* StaticText2;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxButton* ButtonChangeDir;
        wxStaticText* StaticTextDirName;
        wxButton* ButtonNetworkSetup;
        wxMenuItem* MenuItem3;
        wxStatusBar* StatusBar1;
        wxDirDialog* DirDialog1;
        wxButton* ButtonSchedule;
        //*)

        wxString CurrentDir;
        wxString ThisExe;
        wxArrayString mru;  // most recently used directories
        wxMenuItem* mru_MenuItem[MRU_LENGTH];
        wxMenu* mru_Menu;
        int mru_MenuLength;
        void Exec(const wxString& program);
        void SetButtonEnable();
        void UpdateMRU(const wxString& newdir);
        void OnMenuMRU(wxCommandEvent& event);

        DECLARE_EVENT_TABLE()
};

#endif // MAINMENUMAIN_H
