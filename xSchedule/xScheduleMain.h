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
#include <wx/checklst.h>
#include <wx/checkbox.h>
#include <wx/tglbtn.h>
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

#include "PlayerDialog.h"
#include "../include/globals.h"
#include "../include/tinyxml.h"


class xScheduleFrame: public wxFrame
{
    public:

        xScheduleFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~xScheduleFrame();

    private:

        //(*Handlers(xScheduleFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButtonSaveClick(wxCommandEvent& event);
        void OnButtonPlayClick(wxCommandEvent& event);
        void OnCheckBoxAudioClick(wxCommandEvent& event);
        void OnCheckBoxVideoClick(wxCommandEvent& event);
        void OnCheckBoxLORClick(wxCommandEvent& event);
        void OnCheckBoxVixenClick(wxCommandEvent& event);
        void OnChoicePlayListSelect(wxCommandEvent& event);
        void OnButtonUpClick(wxCommandEvent& event);
        void OnButtonDownClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(xScheduleFrame)
        static const long ID_CHOICE_PLAYLIST;
        static const long ID_BUTTON_SAVE;
        static const long ID_STATICTEXT1;
        static const long ID_BUTTON_UP;
        static const long ID_BUTTON_DOWN;
        static const long ID_BUTTON_PLAY;
        static const long ID_STATICTEXT2;
        static const long ID_CHECKBOX_AUDIO;
        static const long ID_CHECKBOX_VIDEO;
        static const long ID_CHECKBOX_LOR;
        static const long ID_CHECKBOX_VIXEN;
        static const long ID_CHECKLISTBOX_PLAY;
        static const long ID_STATICTEXT3;
        static const long ID_CHOICE_LOGIC;
        static const long ID_TEXTCTRL_LOGIC;
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
        wxPanel* PanelPlayList;
        wxCheckBox* CheckBoxVideo;
        wxNotebook* Notebook1;
        wxStaticText* StaticText2;
        wxChoice* Choice3;
        wxStaticText* StaticText6;
        wxCheckListBox* CheckListBoxPlay;
        wxCheckBox* CheckBoxAudio;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxGrid* Grid1;
        wxToggleButton* ToggleButton6;
        wxToggleButton* ToggleButton5;
        wxButton* ButtonUp;
        wxStaticText* StaticText5;
        wxButton* ButtonSave;
        wxPanel* PanelCal;
        wxStatusBar* StatusBar1;
        wxButton* ButtonDown;
        wxCheckBox* CheckBoxLOR;
        wxChoice* ChoiceLogic;
        wxButton* ButtonPlay;
        wxChoice* ChoicePlayList;
        wxTextCtrl* TextCtrlLogic;
        wxChoice* Choice1;
        wxCheckBox* CheckBoxVixen;
        wxChoice* Choice2;
        //*)

        wxString CurrentDir;
        wxFileName scheduleFile;
        PlayerDialog* PlayerDlg;
        bool UnsavedChanges;

        void LoadFile();
        void ScanForFiles();
        char ExtType(wxString ext);

        DECLARE_EVENT_TABLE()
};

#endif // XSCHEDULEMAIN_H
