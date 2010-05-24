/***************************************************************
 * Name:      xNetworksMain.h
 * Purpose:   Defines Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-05-16
 * Copyright: Matt Brown (dowdybrown.com)
 * License:
 **************************************************************/

#ifndef XNETWORKSMAIN_H
#define XNETWORKSMAIN_H

//(*Headers(xNetworksFrame)
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include <wx/config.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "../include/globals.h"
#include "../include/tinyxml.h"

class xNetworksFrame: public wxFrame
{
    public:

        xNetworksFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~xNetworksFrame();

    private:

        //(*Handlers(xNetworksFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnToggleButtonSaveToggle(wxCommandEvent& event);
        void OnToggleButtonAddRowToggle(wxCommandEvent& event);
        void OnToggleButtonDelRowToggle(wxCommandEvent& event);
        void OnGridNetworkEditorShown(wxGridEvent& event);
        void OnButtonSaveClick(wxCommandEvent& event);
        void OnButtonAddRowClick(wxCommandEvent& event);
        void OnButtonDelRowClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(xNetworksFrame)
        static const long ID_BUTTON_SAVE;
        static const long ID_BUTTON_ADDROW;
        static const long ID_BUTTON_DELROW;
        static const long ID_GRID_NETWORK;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(xNetworksFrame)
        wxPanel* Panel1;
        wxGrid* GridNetwork;
        wxButton* ButtonSave;
        wxStatusBar* StatusBar1;
        wxButton* ButtonAddRow;
        wxButton* ButtonDelRow;
        //*)

        wxFileName networkFile;
        bool UnsavedChanges;

        void SaveFile();
        void LoadFile();
        void LoadNetwork(TiXmlElement* n);
        wxString GetAttribute(TiXmlElement* e, const char *attr);
        void SetAttribute(TiXmlElement* e, std::string name, wxString v);
        void PopulatePortChooser(wxArrayString *chooser);

        DECLARE_EVENT_TABLE()
};

#endif // XNETWORKSMAIN_H
