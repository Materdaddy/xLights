/***************************************************************
 * Name:      xChannelsMain.h
 * Purpose:   Defines Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-03-01
 * Copyright: Matt Brown (dowdybrown.com)
 * License:
 **************************************************************/

#ifndef XCHANNELSMAIN_H
#define XCHANNELSMAIN_H

//(*Headers(xChannelsFrame)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)
#include <wx/grid.h>
#include <wx/panel.h>
#include <wx/filename.h>

#include "AddControllersDialog.h"
#include "ChannelCountDialog.h"
#include "NewNetworkDialog.h"
#include "DeleteControllerDialog.h"
#include "../include/globals.h"
#include "../include/tinyxml.h"

class NetworkInfo
{
    public:

    wxPanel* Panel;
    wxGrid* Grid;
    wxStaticText* DescField;
    wxString NetworkType;
    wxString ComPort;
    wxString BaudRate;

    void SetDescField() {
        if (NetworkType.IsEmpty()) {
            DescField->SetLabel(_(""));
        } else {
            DescField->SetLabel(NetworkType+_(" on ")+ComPort+_(" at ")+BaudRate+_(" baud"));
        }
    }

    bool IsDMX() {
        return NetworkType.Left(3)==_("DMX");
    }
};

class xChannelsFrame: public wxFrame
{
    public:

        xChannelsFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~xChannelsFrame();

    private:

        //(*Handlers(xChannelsFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnMenuAddNetworkSelected(wxCommandEvent& event);
        void OnMenuSetLastChannelSelected(wxCommandEvent& event);
        void OnMenuAddControllersSelected(wxCommandEvent& event);
        void OnMenuItemSaveSelected(wxCommandEvent& event);
        void OnMenuImportSelected(wxCommandEvent& event);
        void OnMenuExportSelected(wxCommandEvent& event);
        void OnMenuDeleteControllerSelected(wxCommandEvent& event);
        void OnMenuChangeNetwork(wxCommandEvent& event);
        void OnMenuDeleteNetwork(wxCommandEvent& event);
        //*)

        //(*Identifiers(xChannelsFrame)
        static const long ID_NOTEBOOK1;
        static const long idMenuImport;
        static const long idMenuExport;
        static const long idMenuSave;
        static const long idMenuQuit;
        static const long ID_MENUITEM_ADDNETWORK;
        static const long ID_MENUITEM1;
        static const long ID_MENUITEM2;
        static const long ID_MENUITEM_SETLASTCHANNEL;
        static const long ID_MENUITEM_ADDCONTROLLERS;
        static const long idMenuDelete;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(xChannelsFrame)
        wxMenuItem* MenuItemSave;
        wxMenuItem* MenuDeleteController;
        wxNotebook* Notebook1;
        wxMenuItem* MenuImport;
        wxMenu* Menu3;
        wxMenuItem* MenuExport;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuSetLastChannel;
        wxStatusBar* StatusBar1;
        wxMenuItem* MenuAddControllers;
        //*)

    wxFileName channelFile;
    WX_DEFINE_ARRAY(NetworkInfo*, NetworkArray);
    NetworkArray Networks;
    bool UnsavedChanges;

    void SetGridHeadings(wxGrid *grid);
    void AddNetworkWithPrompt();
    NetworkInfo* AddNetwork(wxString NetworkType, wxString ComPort, wxString BaudRate);
    int MaxController(wxGrid *grid);
    void GridEdit(wxGridEvent& event);

    void SaveFile();
    void LoadFile();
    void LoadNetwork(TiXmlElement* n);
    wxString GetAttribute(TiXmlElement* e, const char *attr);
    void SetAttribute(TiXmlElement* e, std::string name, wxString v);

        DECLARE_EVENT_TABLE()
};

#endif // XCHANNELSMAIN_H
