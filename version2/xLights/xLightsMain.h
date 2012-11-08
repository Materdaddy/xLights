/***************************************************************
 * Name:      xLightsMain.h
 * Purpose:   Defines Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2012-11-03
 * Copyright: Matt Brown ()
 * License:
 **************************************************************/

#ifndef XLIGHTSMAIN_H
#define XLIGHTSMAIN_H

enum play_modes {
    play_off,
    play_effect,
    play_seqpartial,
    play_seqall,
    play_test
};

enum TestFunctions {
    OFF,
    CHASE,
    CHASE2,
    CHASE3,
    CHASE4,
    DIM,
    TWINKLE,
    SHIMMER
};


//(*Headers(xLightsFrame)
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/checklst.h>
#include <wx/checkbox.h>
#include <wx/radiobut.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/filedlg.h>
#include <wx/choice.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/dirdlg.h>
#include <wx/frame.h>
#include <wx/timer.h>
#include <wx/statusbr.h>
//*)

#include <wx/config.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/xml/xml.h>

#include "../include/globals.h"
#include "../include/xlights_out.cpp"

#define MRU_LENGTH 4

class xLightsFrame: public wxFrame
{
    public:

        xLightsFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~xLightsFrame();

    private:

        //(*Handlers(xLightsFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnMenuOpenFolderSelected(wxCommandEvent& event);
        void OnTimer1Trigger(wxTimerEvent& event);
        void OnCheckBoxRunScheduleClick(wxCommandEvent& event);
        void OnButtonAddShowClick(wxCommandEvent& event);
        void OnButtonUpdateShowClick(wxCommandEvent& event);
        void OnButtonDeleteShowClick(wxCommandEvent& event);
        void OnButtonDeselectClick(wxCommandEvent& event);
        void OnButtonShowDatesChangeClick(wxCommandEvent& event);
        void OnNotebook1PageChanged(wxNotebookEvent& event);
        void OnButtonClearLogClick(wxCommandEvent& event);
        void OnButtonSaveLogClick(wxCommandEvent& event);
        void OnMenuItemRenameListSelected(wxCommandEvent& event);
        void OnMenuItemRefreshSelected(wxCommandEvent& event);
        void OnMenuItemCustomScriptSelected(wxCommandEvent& event);
        void OnButtonNetworkChangeClick(wxCommandEvent& event);
        void OnButtonNetworkDeleteClick(wxCommandEvent& event);
        void OnButtonNetworkMoveUpClick(wxCommandEvent& event);
        void OnButtonNetworkMoveDownClick(wxCommandEvent& event);
        void OnGridNetworkBeginDrag(wxListEvent& event);
        void OnButtonAddE131Click(wxCommandEvent& event);
        void OnButtonAddDongleClick(wxCommandEvent& event);
        void OnRadioButtonLorMapClick(wxCommandEvent& event);
        void OnButtonTestSelectAllClick(wxCommandEvent& event);
        void OnButtonTestClearClick(wxCommandEvent& event);
        void OnButtonTestLoadClick(wxCommandEvent& event);
        void OnButtonTestSaveClick(wxCommandEvent& event);
        void OnRadioButtonOffSelect(wxCommandEvent& event);
        void OnRadioButtonChaseSelect(wxCommandEvent& event);
        void OnRadioButtonChase3Select(wxCommandEvent& event);
        void OnRadioButtonChase4Select(wxCommandEvent& event);
        void OnRadioButtonChase5Select(wxCommandEvent& event);
        void OnRadioButtonAltSelect(wxCommandEvent& event);
        void OnRadioButtonTwinkle05Select(wxCommandEvent& event);
        void OnRadioButtonTwinkle10Select(wxCommandEvent& event);
        void OnRadioButtonTwinkle25Select(wxCommandEvent& event);
        void OnRadioButtonTwinkle50Select(wxCommandEvent& event);
        void OnRadioButtonShimmerSelect(wxCommandEvent& event);
        void OnRadioButtonDimSelect(wxCommandEvent& event);
        void OnCheckListBoxTestChannelsToggled(wxCommandEvent& event);
        void OnButtonSaveSetupClick(wxCommandEvent& event);
        void OnBitmapButtonTabInfoClick(wxCommandEvent& event);
        void OnMenuItemDelListSelected(wxCommandEvent& event);
        void OnMenuItemAddListSelected(wxCommandEvent& event);
        void OnButtonLightsOffClick(wxCommandEvent& event);
        void OnCheckBoxLightOutputClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(xLightsFrame)
        static const long ID_BITMAPBUTTON_TAB_INFO;
        static const long ID_BUTTON_STOP_NOW;
        static const long ID_BUTTON_GRACEFUL_STOP;
        static const long ID_BUTTON_LIGHTS_OFF;
        static const long ID_CHECKBOX_LIGHT_OUTPUT;
        static const long ID_CHECKBOX_RUN_SCHEDULE;
        static const long ID_STATICTEXT_SETUP1;
        static const long ID_STATICTEXT_DIRNAME;
        static const long ID_BUTTON_CHANGEDIR;
        static const long ID_BUTTON_ADD_DONGLE;
        static const long ID_BUTTON_ADD_E131;
        static const long ID_BUTTON_NETWORK_CHANGE;
        static const long ID_BUTTON_NETWORK_DELETE;
        static const long ID_BUTTON_NETWORK_MOVEUP;
        static const long ID_BUTTON_NETWORK_MOVEDOWN;
        static const long ID_BUTTON_SAVE_SETUP;
        static const long ID_STATICTEXT4;
        static const long ID_RADIOBUTTON1;
        static const long ID_RADIOBUTTON2;
        static const long ID_LISTCTRL_NETWORKS;
        static const long ID_PANEL_SETUP;
        static const long ID_BUTTON_SELECT_ALL;
        static const long ID_BUTTON_CLEAR_ALL;
        static const long ID_BUTTON_LOAD;
        static const long ID_BUTTON_SAVE;
        static const long ID_STATICTEXT6;
        static const long ID_CHECKLISTBOX_TEST_CHANNELS;
        static const long ID_STATICTEXT8;
        static const long ID_RADIOBUTTON14;
        static const long ID_RADIOBUTTON15;
        static const long ID_RADIOBUTTON16;
        static const long ID_RADIOBUTTON17;
        static const long ID_RADIOBUTTON19;
        static const long ID_RADIOBUTTON18;
        static const long ID_RADIOBUTTON7;
        static const long ID_RADIOBUTTON31;
        static const long ID_RADIOBUTTON30;
        static const long ID_RADIOBUTTON29;
        static const long ID_RADIOBUTTON8;
        static const long ID_RADIOBUTTON6;
        static const long ID_STATICTEXT9;
        static const long ID_SLIDER4;
        static const long ID_STATICTEXT10;
        static const long ID_SLIDER5;
        static const long ID_STATICTEXT11;
        static const long ID_SLIDER6;
        static const long ID_PANEL_TEST_STANDARD;
        static const long ID_STATICTEXT29;
        static const long ID_RADIOBUTTON3;
        static const long ID_RADIOBUTTON4;
        static const long ID_RADIOBUTTON5;
        static const long ID_RADIOBUTTON9;
        static const long ID_RADIOBUTTON25;
        static const long ID_RADIOBUTTON10;
        static const long ID_RADIOBUTTON12;
        static const long ID_RADIOBUTTON28;
        static const long ID_RADIOBUTTON11;
        static const long ID_RADIOBUTTON13;
        static const long ID_RADIOBUTTON20;
        static const long ID_RADIOBUTTON21;
        static const long ID_SLIDER12;
        static const long ID_SLIDER11;
        static const long ID_SLIDER1;
        static const long ID_SLIDER14;
        static const long ID_SLIDER13;
        static const long ID_SLIDER9;
        static const long ID_STATICTEXT7;
        static const long ID_SLIDER2;
        static const long ID_PANEL_TEST_RGB;
        static const long ID_STATICTEXT12;
        static const long ID_RADIOBUTTON22;
        static const long ID_RADIOBUTTON23;
        static const long ID_RADIOBUTTON24;
        static const long ID_RADIOBUTTON26;
        static const long ID_RADIOBUTTON27;
        static const long ID_STATICTEXT13;
        static const long ID_SLIDER7;
        static const long ID_PANEL_RGB_CYCLE;
        static const long ID_NOTEBOOK_TEST;
        static const long ID_PANEL_TEST;
        static const long ID_STATICTEXT14;
        static const long ID_STATICTEXT15;
        static const long ID_TEXTCTRL_FILENAME;
        static const long ID_BUTTON_CHOOSE_FILE;
        static const long ID_STATICTEXT16;
        static const long ID_CHOICE_OUTPUT_FORMAT;
        static const long ID_STATICTEXT17;
        static const long ID_CHECKBOX_OFF_AT_END;
        static const long ID_BUTTON_START;
        static const long ID_STATICTEXT18;
        static const long ID_TEXTCTRL_STATUS;
        static const long ID_PANEL_CONVERT;
        static const long ID_PANEL_SEQUENCE;
        static const long ID_TREECTRL1;
        static const long ID_BUTTON_ADD_SHOW;
        static const long ID_BUTTON_UPDATE_SHOW;
        static const long ID_BUTTON_DELETE_SHOW;
        static const long ID_BUTTON_DESELECT;
        static const long ID_STATICTEXT2;
        static const long ID_BUTTON_SHOW_DATES_CHANGE;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT_SHOWSTART;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT_SHOWEND;
        static const long ID_PANEL_CAL;
        static const long ID_BUTTON_CLEARLOG;
        static const long ID_BUTTON_SAVELOG;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL_LOG;
        static const long ID_PANEL_LOG;
        static const long ID_NOTEBOOK1;
        static const long ID_PANEL1;
        static const long ID_MENUITEM2;
        static const long idMenuQuit;
        static const long idMenuAddList;
        static const long idMenuRenameList;
        static const long idMenuDelList;
        static const long ID_MENUITEM1;
        static const long idCustomScript;
        static const long idMenuHelpContent;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(xLightsFrame)
        wxStaticText* StaticText10;
        wxRadioButton* RadioButtonChase5;
        wxStaticText* StaticText9;
        wxRadioButton* RadioButtonRgbCycle4;
        wxTextCtrl* TextCtrlFilename;
        wxRadioButton* RadioButtonRgbChaseOff;
        wxTextCtrl* TextCtrlStatus;
        wxRadioButton* RadioButtonRgbCycleOff;
        wxRadioButton* RadioButtonLorMapSingle;
        wxRadioButton* RadioButtonLorMapMulti;
        wxRadioButton* RadioButtonRgbChase;
        wxButton* ButtonAddE131;
        wxRadioButton* RadioButtonRgbChase5;
        wxRadioButton* RadioButtonRgbChase3;
        wxStaticText* StaticText29;
        wxRadioButton* RadioButtonShimmer;
        wxCheckBox* CheckBoxRunSchedule;
        wxNotebook* Notebook1;
        wxButton* ButtonClearLog;
        wxPanel* PanelLog;
        wxStaticText* StaticText13;
        wxStaticText* StaticText2;
        wxSlider* SliderFgColorC;
        wxFileDialog* FileDialogConvert;
        wxSlider* SliderRgbChaseSpeed;
        wxStaticText* StaticText14;
        wxButton* ButtonLightsOff;
        wxButton* ButtonTestLoad;
        wxStaticText* StaticTextShowEnd;
        wxButton* ButtonGracefulStop;
        wxRadioButton* RadioButtonRgbCycle3;
        wxChoice* ChoiceOutputFormat;
        wxTextCtrl* TextCtrlLog;
        wxStaticText* StaticText6;
        wxMenuItem* MenuItemRefresh;
        wxRadioButton* RadioButtonDim;
        wxRadioButton* RadioButtonChase4;
        wxRadioButton* RadioButtonRgbTwinkle10;
        wxRadioButton* RadioButtonChase3;
        wxButton* ButtonNetworkMoveDown;
        wxSlider* SliderChaseSpeed;
        wxStaticText* StaticText8;
        wxStaticText* StaticText11;
        wxStaticText* StaticText18;
        wxSlider* SliderFgColorA;
        wxStaticText* StaticTextShowStart;
        wxPanel* PanelTestRgb;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxPanel* PanelRgbCycle;
        wxRadioButton* RadioButtonRgbAlt;
        wxButton* ButtonSaveLog;
        wxButton* ButtonDeselect;
        wxButton* ButtonChangeDir;
        wxStaticText* StaticTextDirName;
        wxNotebook* NotebookTest;
        wxSlider* SliderRgbCycleSpeed;
        wxButton* ButtonAddDongle;
        wxRadioButton* RadioButtonTwinkle50;
        wxButton* ButtonNetworkMoveUp;
        wxRadioButton* RadioButtonRgbCycleMixed;
        wxButton* ButtonNetworkChange;
        wxSlider* SliderBgColorA;
        wxRadioButton* RadioButtonRgbTwinkle50;
        wxStaticText* StaticTextSetup1;
        wxSlider* SliderBgColorC;
        wxRadioButton* RadioButtonRgbTwinkle05;
        wxButton* ButtonNetworkDelete;
        wxStaticText* StaticText5;
        wxTreeCtrl* ListBoxSched;
        wxStaticText* StaticText7;
        wxPanel* PanelTest;
        wxListCtrl* GridNetwork;
        wxPanel* PanelCal;
        wxStatusBar* StatusBar1;
        wxMenu* MenuFile;
        wxDirDialog* DirDialog1;
        wxButton* ButtonTestClear;
        wxBitmapButton* BitmapButtonTabInfo;
        wxButton* ButtonDeleteShow;
        wxButton* ButtonShowDatesChange;
        wxRadioButton* RadioButtonRgbTwinkle25;
        wxRadioButton* RadioButtonRgbShimmer;
        wxCheckBox* CheckBoxLightOutput;
        wxStaticText* StaticText15;
        wxStaticText* StaticText12;
        wxCheckListBox* CheckListBoxTestChannels;
        wxPanel* PanelConvert;
        wxRadioButton* RadioButtonTwinkle10;
        wxPanel* PanelSetup;
        wxSlider* SliderBgColorB;
        wxButton* ButtonSaveSetup;
        wxButton* ButtonStart;
        wxRadioButton* RadioButtonRgbDim;
        wxRadioButton* RadioButtonTwinkle25;
        wxPanel* PanelSequence;
        wxRadioButton* RadioButtonChase;
        wxButton* ButtonUpdateShow;
        wxPanel* PanelTestStandard;
        wxSlider* SliderBgIntensity;
        wxRadioButton* RadioButtonTwinkle05;
        wxButton* ButtonChooseFile;
        wxRadioButton* RadioButtonOff;
        wxStaticText* StaticText4;
        wxStaticText* StaticText17;
        wxRadioButton* RadioButtonRgbCycle5;
        wxRadioButton* RadioButtonRgbChase4;
        wxButton* ButtonTestSelectAll;
        wxButton* ButtonAddShow;
        wxButton* ButtonTestSave;
        wxSlider* SliderFgIntensity;
        wxStaticText* StaticText16;
        wxSlider* SliderFgColorB;
        wxTimer Timer1;
        wxCheckBox* CheckBoxOffAtEnd;
        wxRadioButton* RadioButtonAlt;
        wxButton* ButtonStopNow;
        //*)

        wxString CurrentDir;
        wxFileName networkFile;
        wxArrayString mru;  // most recently used directories
        wxMenuItem* mru_MenuItem[MRU_LENGTH];
        wxXmlDocument NetworkXML;
        long DragRowIdx;
        bool UnsavedChanges;
        wxDateTime starttime;
        xOutput* xout;
        play_modes play_mode;
        void SetPlayMode(play_modes newmode);
        bool AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels);
        double rand01();

        // setup
        void OnMenuMRU(wxCommandEvent& event);
        void SetDir(const wxString& dirname);
        void UpdateNetworkList();
        void UpdateLorMapping();
        long GetNetworkSelection();
        void MoveNetworkRow(int fromRow, int toRow);
        void OnGridNetworkDragQuit(wxMouseEvent& event);
        void OnGridNetworkDragEnd(wxMouseEvent& event);
        void SetupDongle(wxXmlNode* e);
        void SetupE131(wxXmlNode* e);

        // test
        void SetTestCheckboxes(bool NewValue);
        void GetCheckedItems(wxArrayInt& chArray);
        void TestButtonsOff();
        bool CheckChannelList;
        int ChaseGrouping;
        int TwinkleRatio;
        TestFunctions TestFunc;
        void OnTimerTest();


        DECLARE_EVENT_TABLE()
};

#endif // XLIGHTSMAIN_H
