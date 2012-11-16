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
#include <wx/splitter.h>
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
#include <wx/choicdlg.h>
#include <wx/xml/xml.h>

#include "../include/globals.h"
#include "../include/xlights_out.cpp"
#include "PlayerFrame.h"
#include "AddShowDialog.h"
#include "ShowDatesDialog.h"
#include "PlaybackOptionsDialog.h"

// max number of most recently used show directories on the File menu
#define MRU_LENGTH 4

// notebook pages
#define SETUPTAB 0
#define TESTTAB 1
#define CONVERTTAB 2
#define SEQUENCETAB 3
#define SCHEDULETAB 4

#define FixedPages 5

enum play_modes {
    play_off,
    play_effect,
    play_seqpartial,
    play_seqall,
    play_test,
    play_single,
    play_list,
    play_sched
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

enum SeqPlayerStates {
    NO_SEQ,
    STARTING_MEDIA,
    STARTING_SEQ,
    PLAYING_MEDIA,
    PLAYING_SEQ,
    STARTING_SEQ_ANIM,
    PLAYING_SEQ_ANIM,
    PAUSE_SEQ,
    DELAY_AFTER_PLAY
};

class SchedTreeData : public wxTreeItemData
{
protected:
    wxString eventString;

public:
    SchedTreeData(const wxString& EventData = wxT("")) { eventString = EventData; };
    wxString GetString() { return eventString; };
};



class xLightsFrame: public wxFrame
{
    public:

        xLightsFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~xLightsFrame();

        // these are added to 1000*pagenum to get the control id
        enum PlayListIds {
            CHKBOX_AUDIO,
            CHKBOX_VIDEO,
            CHKBOX_XLIGHTS,
            CHKBOX_MOVIEMODE,
            UP_BUTTON,
            DOWN_BUTTON,
            INFO_BUTTON,
            PLAY_BUTTON,
            PLAY_ALL_BUTTON,
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

        long SecondsRemaining, EndTimeSec;
        int TxOverflowCnt;
        xOutput* xout;
        void BasicPrompt(char* prompt, char* buff, int size);
        void BasicOutput(char *msg);
        void BasicError(const char *msg);
        char ExtType(const wxString& ext);
        bool Play(wxString& filename, long delay);
        void StopPlayback();
        void StartScript(const char *scriptname);
        void EndScript(const char *scriptname);
        int  FindNotebookPage(wxString& pagename);
        wxWindow* FindNotebookControl(int nbidx, PlayListIds id);

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
        void OnButtonStartConversionClick(wxCommandEvent& event);
        void OnButtonChooseFileClick(wxCommandEvent& event);
        void OnButtonStopNowClick(wxCommandEvent& event);
        void OnButtonGracefulStopClick(wxCommandEvent& event);
        void OnButtonSaveScheduleClick(wxCommandEvent& event);
        void OnMenuItemSavePlaylistsSelected(wxCommandEvent& event);
        void OnButtonNetworkDeleteAllClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(xLightsFrame)
        static const long ID_BITMAPBUTTON_TAB_INFO;
        static const long ID_BUTTON_STOP_NOW;
        static const long ID_BUTTON_GRACEFUL_STOP;
        static const long ID_BUTTON_LIGHTS_OFF;
        static const long ID_CHECKBOX_LIGHT_OUTPUT;
        static const long ID_STATICTEXT_SETUP1;
        static const long ID_STATICTEXT_DIRNAME;
        static const long ID_BUTTON_CHANGEDIR;
        static const long ID_BUTTON_SAVE_SETUP;
        static const long ID_BUTTON_ADD_DONGLE;
        static const long ID_BUTTON_ADD_E131;
        static const long ID_BUTTON_NETWORK_CHANGE;
        static const long ID_BUTTON_NETWORK_DELETE;
        static const long ID_BUTTON_NETWORK_DELETE_ALL;
        static const long ID_STATICTEXT4;
        static const long ID_RADIOBUTTON1;
        static const long ID_RADIOBUTTON2;
        static const long ID_BITMAPBUTTON1;
        static const long ID_BITMAPBUTTON2;
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
        static const long ID_STATICTEXT19;
        static const long ID_STATICTEXT15;
        static const long ID_BUTTON_CHOOSE_FILE;
        static const long ID_TEXTCTRL_FILENAME;
        static const long ID_STATICTEXT16;
        static const long ID_CHOICE_OUTPUT_FORMAT;
        static const long ID_STATICTEXT20;
        static const long ID_CHECKBOX_SAVE_CHANNEL_NAMES;
        static const long ID_STATICTEXT17;
        static const long ID_CHECKBOX_OFF_AT_END;
        static const long ID_BUTTON_START_CONVERSION;
        static const long ID_STATICTEXT18;
        static const long ID_TEXTCTRL_CONVERSION_STATUS;
        static const long ID_PANEL_CONVERT;
        static const long ID_PANEL_SEQUENCE;
        static const long ID_TREECTRL1;
        static const long ID_CHECKBOX_RUN_SCHEDULE;
        static const long ID_BUTTON_SAVE_SCHEDULE;
        static const long ID_BUTTON_ADD_SHOW;
        static const long ID_BUTTON_UPDATE_SHOW;
        static const long ID_BUTTON_DELETE_SHOW;
        static const long ID_STATICTEXT2;
        static const long ID_BUTTON_SHOW_DATES_CHANGE;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT_SHOWSTART;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT_SHOWEND;
        static const long ID_PANEL3;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL_LOG;
        static const long ID_BUTTON_CLEARLOG;
        static const long ID_BUTTON_SAVELOG;
        static const long ID_PANEL2;
        static const long ID_SPLITTERWINDOW1;
        static const long ID_PANEL_CAL;
        static const long ID_NOTEBOOK1;
        static const long ID_PANEL1;
        static const long ID_MENUITEM2;
        static const long idMenuQuit;
        static const long idMenuSaveSched;
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

        static const long ID_PLAYER_DIALOG;

        //(*Declarations(xLightsFrame)
        wxStaticText* StaticText10;
        wxRadioButton* RadioButtonChase5;
        wxStaticText* StaticText9;
        wxRadioButton* RadioButtonRgbCycle4;
        wxTextCtrl* TextCtrlFilename;
        wxRadioButton* RadioButtonRgbChaseOff;
        wxStaticText* StaticText20;
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
        wxBitmapButton* BitmapButtonMoveNetworkDown;
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
        wxStaticText* StaticText19;
        wxSlider* SliderChaseSpeed;
        wxStaticText* StaticText8;
        wxButton* ButtonNetworkDeleteAll;
        wxButton* ButtonStartConversion;
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
        wxButton* ButtonChangeDir;
        wxStaticText* StaticTextDirName;
        wxNotebook* NotebookTest;
        wxPanel* Panel3;
        wxSlider* SliderRgbCycleSpeed;
        wxButton* ButtonAddDongle;
        wxRadioButton* RadioButtonTwinkle50;
        wxBitmapButton* BitmapButtonMoveNetworkUp;
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
        wxRadioButton* RadioButtonRgbDim;
        wxRadioButton* RadioButtonTwinkle25;
        wxPanel* Panel2;
        wxPanel* PanelSequence;
        wxMenuItem* MenuItemSavePlaylists;
        wxRadioButton* RadioButtonChase;
        wxButton* ButtonUpdateShow;
        wxPanel* PanelTestStandard;
        wxSlider* SliderBgIntensity;
        wxTextCtrl* TextCtrlConversionStatus;
        wxRadioButton* RadioButtonTwinkle05;
        wxSplitterWindow* SplitterWindow1;
        wxButton* ButtonChooseFile;
        wxRadioButton* RadioButtonOff;
        wxCheckBox* CheckBoxSaveChannelNames;
        wxStaticText* StaticText4;
        wxStaticText* StaticText17;
        wxRadioButton* RadioButtonRgbCycle5;
        wxRadioButton* RadioButtonRgbChase4;
        wxButton* ButtonTestSelectAll;
        wxButton* ButtonSaveSchedule;
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
        wxFileName scheduleFile;
        PlayerFrame* PlayerDlg;
        wxArrayString mru;  // most recently used directories
        wxMenuItem* mru_MenuItem[MRU_LENGTH];
        wxXmlDocument NetworkXML;
        long DragRowIdx;
        wxListCtrl* DragListBox;
        bool UnsavedChanges;
        wxDateTime starttime;
        play_modes play_mode;

        void SetPlayMode(play_modes newmode);
        double rand01();
        bool EnableOutputs();
        void EnableNetworkChanges();

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
        void GetTestPresetNames(wxArrayString& PresetNames);
        void TestButtonsOff();
        bool CheckChannelList;
        int ChaseGrouping;
        int TwinkleRatio;
        TestFunctions TestFunc;
        void OnTimerTest();

        // convert
        bool LoadVixenProfile(const wxString& ProfileName, wxArrayInt& VixChannels);
        void ReadVixFile(const char* filename);
        void ReadLorFile(const char* filename);
        void ReadXlightsFile(const wxString& FileName);
        void ReadConductorFile(const wxString& FileName);
        void SetMediaFilename(const wxString& filename);
        int GetLorTrack1Length(const char* filename);
        void WriteVixenFile(const wxString& filename);
        void WriteXLightsFile(const wxString& filename);
        void WriteConductorFile(const wxString& filename);
        void ClearLastPeriod();
        void ConversionInit();
        void DoConversion(const wxString& FileName, const wxString& OutputFormat);
        void ConversionError(const wxString& msg);
        wxString base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
        std::string base64_decode(const wxString& encoded_string);

        wxString mediaFilename;
        wxUint8 * SeqData;
        long SeqDataLen;
        long SeqNumPeriods;
        long SeqNumChannels;
        size_t TotChannels;
        wxArrayString FileNames;
        wxArrayString ChannelNames;
        wxArrayInt ChannelColors;
        std::vector<size_t> NetMaxChannel;

        // schedule
        wxDateTime ShowStartDate,ShowEndDate;
        wxArrayString ShowEvents;
        SeqPlayerStates SeqPlayerState;
        wxString LastMoDay;
        long DelayAfterPlayMSEC;

        void AddShow(const wxDateTime& d, const wxString& StartStop, const wxString& Playlist);
        void DisplaySchedule();
        int DisplayScheduleOneDay(const wxDateTime& d, const wxTreeItemId& root);
        void PopulateShowDialog(AddShowDialog& dialog, wxSortedArrayString& SelectedDates);
        void UnpackSchedCode(const wxString& SchedCode, wxString& StartTime, wxString& EndTime, wxString& RepeatOptions, wxString& Playlist);
        void ForceScheduleCheck();
        void CheckRunSchedule();
        long GetSelectedItem(wxListCtrl* ListBoxPlay);
        void UpdateShowDates(const wxDateTime& NewStart, const wxDateTime NewEnd);
        bool DisplayAddShowDialog(AddShowDialog& dialog);
        int DeleteSelectedShows();
        void CheckSchedule();
        void LoadScheduleFile();
        void LoadSchedule(wxXmlNode* n);
        void LoadPlaylists(wxXmlNode* n);
        void LoadPlaylist(wxXmlNode* n);
        void AddPlaylist(const wxString& name);
        wxString OnOffString(bool b);
        wxString CreateScript(wxString ListName, bool Repeat, bool FirstItemOnce, bool LastItemOnce, bool LightsOff, bool Random);
        void RunPlaylist(int nbidx, wxString& script);
        void PlayerError(const wxString& msg);
        void SendToLogAndStatusBar(const wxString& msg);
        void ScanForFiles();
        long DiffSeconds(wxString& strTime, wxTimeSpan& tsCurrent);
        int Time2Seconds(const wxString& hhmm);
        void ResetTimer(SeqPlayerStates newstate);
        void SaveScheduleFile();
        void OnButtonPlaylistAddClick(wxCommandEvent& event);
        void OnButtonPlaylistAddAllClick(wxCommandEvent& event);
        void OnButtonPlaylistDeleteClick(wxCommandEvent& event);
        void OnButtonPlaylistDeleteAllClick(wxCommandEvent& event);
        void OnButtonRemoveScriptClick(wxCommandEvent& event);
        void OnButtonRunPlaylistClick(wxCommandEvent& event);
        void OnButtonPlayItemClick(wxCommandEvent& event);
        void OnButtonUpClick(wxCommandEvent& event);
        void OnButtonDownClick(wxCommandEvent& event);
        void OnButtonSetDelayClick(wxCommandEvent& event);
        void OnFileTypeButtonClicked(wxCommandEvent& event);
        void OnPlayListBeginDrag(wxListEvent& event);
        void OnPlayListDragEnd(wxMouseEvent& event);
        void OnPlayListDragQuit(wxMouseEvent& event);
        void OnTimerPlaylist(long msec);

        DECLARE_EVENT_TABLE()
};

#endif // XLIGHTSMAIN_H
