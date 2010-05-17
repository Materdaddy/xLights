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
#include <wx/textctrl.h>
#include <wx/listbox.h>
#include <wx/tglbtn.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/choice.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include <wx/config.h>
#include <wx/stdpaths.h>
#include "../include/globals.h"


class xScheduleFrame: public wxFrame
{
    public:

        xScheduleFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~xScheduleFrame();

    private:

        //(*Handlers(xScheduleFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(xScheduleFrame)
        static const long ID_TOGGLEBUTTON1;
        static const long ID_TOGGLEBUTTON2;
        static const long ID_TOGGLEBUTTON3;
        static const long ID_TOGGLEBUTTON4;
        static const long ID_STATICTEXT1;
        static const long ID_LISTBOX_PLAY;
        static const long ID_STATICTEXT2;
        static const long ID_LISTBOX_SEQ;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL_LOGIC;
        static const long ID_STATICTEXT4;
        static const long ID_LISTBOX_AV;
        static const long ID_PANEL_PLAYLIST;
        static const long ID_CHOICE1;
        static const long ID_STATICTEXT5;
        static const long ID_CHOICE2;
        static const long ID_STATICTEXT6;
        static const long ID_CHOICE3;
        static const long ID_TOGGLEBUTTON5;
        static const long ID_TOGGLEBUTTON6;
        static const long ID_GRID1;
        static const long ID_PANEL_CAL;
        static const long ID_NOTEBOOK1;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(xScheduleFrame)
        wxToggleButton* ToggleButton2;
        wxPanel* PanelPlayList;
        wxNotebook* Notebook1;
        wxStaticText* StaticText2;
        wxListBox* ListBoxPlay;
        wxChoice* Choice3;
        wxStaticText* StaticText6;
        wxToggleButton* ToggleButton3;
        wxToggleButton* ToggleButton1;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxGrid* Grid1;
        wxToggleButton* ToggleButton6;
        wxListBox* ListBoxSeq;
        wxListBox* ListBoxAV;
        wxToggleButton* ToggleButton5;
        wxStaticText* StaticText5;
        wxPanel* PanelCal;
        wxStatusBar* StatusBar1;
        wxToggleButton* ToggleButton4;
        wxStaticText* StaticText4;
        wxTextCtrl* TextCtrlLogic;
        wxChoice* Choice1;
        wxChoice* Choice2;
        //*)

        wxString CurrentDir;
        void LoadFilesToLists();

        DECLARE_EVENT_TABLE()
};

#endif // XSCHEDULEMAIN_H
