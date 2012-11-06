/***************************************************************
 * Name:      xRGBMain.h
 * Purpose:   Defines Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2012-10-09
 * Copyright: Matt Brown ()
 * License:
 **************************************************************/

#ifndef XRGBMAIN_H
#define XRGBMAIN_H

//(*Headers(xRGBFrame)
#include <wx/scrolwin.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/colordlg.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/timer.h>
#include <wx/choicebk.h>
//*)

#include <vector>

#include <wx/config.h>
#include <wx/filename.h>
#include <wx/xml/xml.h>
#include <wx/dcclient.h>
#include <wx/html/htmprint.h>

#include "ModelListDialog.h"
#include "EffectListDialog.h"
#include "../include/globals.h"
#include "../include/xlights_out.cpp"
#include "PixelBuffer.h"
#include "../xScheduler/PlayerFrame.h"


enum play_modes {
    play_off,
    play_effect,
    play_seqpartial,
    play_seqall
};


class xRGBFrame: public wxFrame
{
    public:

        xRGBFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~xRGBFrame();

    private:

        //(*Handlers(xRGBFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnTimer1Trigger(wxTimerEvent& event);
        void OnCheckBox_SendOutputClick(wxCommandEvent& event);
        void OnButton_SaveEffectsClick(wxCommandEvent& event);
        void OnButton_PresetAddClick(wxCommandEvent& event);
        void OnButton_ModelsClick(wxCommandEvent& event);
        void OnButton_PresetsClick(wxCommandEvent& event);
        void OnButton_ColorClick(wxCommandEvent& event);
        void OnChoice_PresetsSelect(wxCommandEvent& event);
        void OnButton_PresetUpdateClick(wxCommandEvent& event);
        void OnButton_PlayEffectClick(wxCommandEvent& event);
        void OnButton_PlaySelectionClick(wxCommandEvent& event);
        void OnButton_PlayAllClick(wxCommandEvent& event);
        void OnButton_StopClick(wxCommandEvent& event);
        void OnChoice_LayerMethodSelect(wxCommandEvent& event);
        void OnCheckBox_PaletteClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(xRGBFrame)
        static const long ID_SCROLLEDWINDOW1;
        static const long ID_BUTTON7;
        static const long ID_CHECKBOX1;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT5;
        static const long ID_BUTTON5;
        static const long ID_BUTTON1;
        static const long ID_BUTTON11;
        static const long ID_BUTTON6;
        static const long ID_BUTTON2;
        static const long ID_BUTTON12;
        static const long ID_GRID1;
        static const long ID_BUTTON58;
        static const long ID_CHOICE7;
        static const long ID_BUTTON13;
        static const long ID_BUTTON59;
        static const long ID_CHOICE2;
        static const long ID_BUTTON9;
        static const long ID_BUTTON8;
        static const long ID_BUTTON10;
        static const long ID_STATICTEXT2;
        static const long ID_CHOICE_LayerMethod;
        static const long ID_BUTTON56;
        static const long ID_STATICTEXT6;
        static const long ID_SLIDER_SparkleFrequency;
        static const long ID_PANEL2;
        static const long ID_STATICTEXT17;
        static const long ID_SLIDER_Bars1_BarCount;
        static const long ID_STATICTEXT21;
        static const long ID_CHOICE_Bars1_Direction;
        static const long ID_CHECKBOX_Bars1_Highlight;
        static const long ID_CHECKBOX_Bars1_3D;
        static const long ID_PANEL8;
        static const long ID_STATICTEXT19;
        static const long ID_CHOICE1;
        static const long ID_STATICTEXT23;
        static const long ID_SLIDER_Butterfly1_Style;
        static const long ID_STATICTEXT25;
        static const long ID_SLIDER_Butterfly1_Chunks;
        static const long ID_STATICTEXT26;
        static const long ID_SLIDER_Butterfly1_Skip;
        static const long ID_PANEL10;
        static const long ID_STATICTEXT7;
        static const long ID_CHECKBOX_ColorWash1_HFade;
        static const long ID_STATICTEXT8;
        static const long ID_CHECKBOX_ColorWash1_VFade;
        static const long ID_PANEL5;
        static const long ID_PANEL12;
        static const long ID_STATICTEXT31;
        static const long ID_SLIDER_Garlands1_Type;
        static const long ID_STATICTEXT32;
        static const long ID_SLIDER_Garlands1_Spacing;
        static const long ID_PANEL14;
        static const long ID_STATICTEXT35;
        static const long ID_SLIDER_Life1_Count;
        static const long ID_STATICTEXT37;
        static const long ID_SLIDER_Life1_Seed;
        static const long ID_PANEL16;
        static const long ID_STATICTEXT39;
        static const long ID_CHOICE_Meteors1_Type;
        static const long ID_STATICTEXT41;
        static const long ID_SLIDER_Meteors1_Count;
        static const long ID_STATICTEXT43;
        static const long ID_SLIDER_Meteors1_Length;
        static const long ID_PANEL18;
        static const long ID_BUTTON42;
        static const long ID_TEXTCTRL_Pictures1_Filename;
        static const long ID_STATICTEXT46;
        static const long ID_CHOICE_Pictures1_Direction;
        static const long ID_PANEL20;
        static const long ID_PANEL22;
        static const long ID_STATICTEXT45;
        static const long ID_SLIDER_Snowstorm1_Count;
        static const long ID_STATICTEXT51;
        static const long ID_SLIDER_Snowstorm1_Length;
        static const long ID_PANEL24;
        static const long ID_STATICTEXT9;
        static const long ID_SLIDER_Spirals1_Count;
        static const long ID_STATICTEXT10;
        static const long ID_SLIDER_Spirals1_Rotation;
        static const long ID_STATICTEXT11;
        static const long ID_SLIDER_Spirals1_Thickness;
        static const long ID_STATICTEXT24;
        static const long ID_SLIDER_Spirals1_Direction;
        static const long ID_CHECKBOX_Spirals1_Blend;
        static const long ID_CHECKBOX_Spirals1_3D;
        static const long ID_PANEL26;
        static const long ID_STATICTEXT53;
        static const long ID_TEXTCTRL_Text1_Line1;
        static const long ID_STATICTEXT54;
        static const long ID_TEXTCTRL_Text1_Line2;
        static const long ID_STATICTEXT57;
        static const long ID_SLIDER_Text1_Top;
        static const long ID_PANEL7;
        static const long ID_CHOICEBOOK1;
        static const long ID_BUTTON_Palette1;
        static const long ID_CHECKBOX_Palette1_1;
        static const long ID_BUTTON_Palette1_1;
        static const long ID_CHECKBOX_Palette1_2;
        static const long ID_BUTTON_Palette1_2;
        static const long ID_CHECKBOX_Palette1_3;
        static const long ID_BUTTON_Palette1_3;
        static const long ID_CHECKBOX_Palette1_4;
        static const long ID_BUTTON_Palette1_4;
        static const long ID_CHECKBOX_Palette1_5;
        static const long ID_BUTTON_Palette1_5;
        static const long ID_CHECKBOX_Palette1_6;
        static const long ID_BUTTON_Palette1_6;
        static const long ID_STATICTEXT61;
        static const long ID_SLIDER_Speed1;
        static const long ID_PANEL3;
        static const long ID_STATICTEXT18;
        static const long ID_SLIDER_Bars2_BarCount;
        static const long ID_STATICTEXT22;
        static const long ID_CHOICE_Bars2_Direction;
        static const long ID_CHECKBOX_Bars2_Highlight;
        static const long ID_CHECKBOX_Bars2_3D;
        static const long ID_PANEL9;
        static const long ID_STATICTEXT20;
        static const long ID_CHOICE3;
        static const long ID_STATICTEXT27;
        static const long ID_SLIDER_Butterfly2_Style;
        static const long ID_STATICTEXT29;
        static const long ID_SLIDER_Butterfly2_Chunks;
        static const long ID_STATICTEXT30;
        static const long ID_SLIDER_Butterfly2_Skip;
        static const long ID_PANEL11;
        static const long ID_STATICTEXT12;
        static const long ID_CHECKBOX_ColorWash2_HFade;
        static const long ID_STATICTEXT16;
        static const long ID_CHECKBOX_ColorWash2_VFade;
        static const long ID_PANEL6;
        static const long ID_PANEL13;
        static const long ID_STATICTEXT33;
        static const long ID_SLIDER_Garlands2_Type;
        static const long ID_STATICTEXT34;
        static const long ID_SLIDER_Garlands2_Spacing;
        static const long ID_PANEL15;
        static const long ID_STATICTEXT36;
        static const long ID_SLIDER_Life2_Count;
        static const long ID_STATICTEXT38;
        static const long ID_SLIDER_Life2_Seed;
        static const long ID_PANEL17;
        static const long ID_STATICTEXT40;
        static const long ID_CHOICE_Meteors2_Type;
        static const long ID_STATICTEXT42;
        static const long ID_SLIDER_Meteors2_Count;
        static const long ID_STATICTEXT44;
        static const long ID_SLIDER_Meteors2_Length;
        static const long ID_PANEL19;
        static const long ID_BUTTON47;
        static const long ID_TEXTCTRL_Pictures2_Filename;
        static const long ID_STATICTEXT47;
        static const long ID_CHOICE_Pictures2_Direction;
        static const long ID_PANEL21;
        static const long ID_PANEL23;
        static const long ID_STATICTEXT50;
        static const long ID_SLIDER_Snowstorm2_Count;
        static const long ID_STATICTEXT52;
        static const long ID_SLIDER_Snowstorm2_Length;
        static const long ID_PANEL25;
        static const long ID_STATICTEXT13;
        static const long ID_SLIDER_Spirals2_Count;
        static const long ID_STATICTEXT14;
        static const long ID_SLIDER_Spirals2_Rotation;
        static const long ID_STATICTEXT15;
        static const long ID_SLIDER_Spirals2_Thickness;
        static const long ID_STATICTEXT28;
        static const long ID_SLIDER_Spirals2_Direction;
        static const long ID_CHECKBOX_Spirals2_Blend;
        static const long ID_CHECKBOX_Spirals2_3D;
        static const long ID_PANEL4;
        static const long ID_STATICTEXT55;
        static const long ID_TEXTCTRL_Text2_Line1;
        static const long ID_STATICTEXT56;
        static const long ID_TEXTCTRL_Text2_Line2;
        static const long ID_STATICTEXT58;
        static const long ID_SLIDER_Text2_Top;
        static const long ID_PANEL27;
        static const long ID_CHOICEBOOK2;
        static const long ID_BUTTON_Palette2;
        static const long ID_CHECKBOX_Palette2_1;
        static const long ID_BUTTON_Palette2_1;
        static const long ID_CHECKBOX_Palette2_2;
        static const long ID_BUTTON_Palette2_2;
        static const long ID_CHECKBOX_Palette2_3;
        static const long ID_BUTTON_Palette2_3;
        static const long ID_CHECKBOX_Palette2_4;
        static const long ID_BUTTON_Palette2_4;
        static const long ID_CHECKBOX_Palette2_5;
        static const long ID_BUTTON_Palette2_5;
        static const long ID_CHECKBOX_Palette2_6;
        static const long ID_BUTTON_Palette2_6;
        static const long ID_STATICTEXT4;
        static const long ID_SLIDER_Speed2;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(xRGBFrame)
        wxPanel* Panel1_Life;
        wxSlider* Slider_Garlands2_Type;
        wxSlider* Slider_Butterfly1_Style;
        wxButton* Button_Presets;
        wxChoicebook* Choicebook2;
        wxChoice* Choice_Models;
        wxChoice* Choice_Butterfly1_Colors;
        wxButton* Button_Palette1_1;
        wxCheckBox* CheckBox_Palette2_6;
        wxButton* Button_DisplayElements;
        wxSlider* Slider_Snowstorm1_Length;
        wxCheckBox* CheckBox_Palette1_3;
        wxStaticText* StaticText32;
        wxCheckBox* CheckBox_Palette1_5;
        wxStaticText* StaticText36;
        wxChoice* Choice_Butterfly2_Colors;
        wxButton* Button_Palette2_4;
        wxStaticText* StaticText40;
        wxStaticText* StaticText27;
        wxTextCtrl* TextCtrl_Text1_Line1;
        wxPanel* Panel1_Garlands;
        wxSlider* Slider_Life1_Count;
        wxStaticText* StaticText_PlaybackMode;
        wxButton* Button_PlayAll;
        wxButton* Button_Stop;
        wxSlider* Slider_Butterfly2_Chunks;
        wxSlider* Slider_Snowstorm2_Count;
        wxStaticText* StaticText41;
        wxTimer Timer1;
        wxPanel* Panel1;
        wxButton* Button_Palette1;
        wxSlider* Slider_Snowstorm1_Count;
        wxStaticText* StaticText50;
        wxStaticText* StaticText46;
        wxButton* Button_PlaySelection;
        wxCheckBox* CheckBox_Palette2_1;
        wxSlider* Slider_Meteors2_Count;
        wxSlider* Slider_Garlands1_Type;
        wxButton* Button_Palette2_6;
        wxButton* Button_PlayEffect;
        wxStaticText* StaticText42;
        wxStaticText* StaticText5;
        wxSlider* Slider_Butterfly2_Style;
        wxSlider* Slider_Speed2;
        wxTextCtrl* TextCtrl_Text1_Line2;
        wxCheckBox* CheckBox_Palette2_3;
        wxStaticText* StaticText25;
        wxStaticText* StaticText6;
        wxPanel* Panel1_ColorWash;
        wxStaticText* StaticText52;
        wxCheckBox* CheckBox_Spirals2_Blend;
        wxSlider* Slider_Spirals1_Thickness;
        wxChoice* Choice_Bars1_Direction;
        wxSlider* Slider_Life1_Seed;
        wxStaticText* StaticText19;
        wxPanel* Panel2_Butterfly;
        wxChoice* Choice_Bars2_Direction;
        wxStaticText* StaticText39;
        wxSlider* Slider_Meteors1_Length;
        wxCheckBox* CheckBox_Bars1_Highlight;
        wxChoicebook* Choicebook1;
        wxButton* Button_Palette2_2;
        wxPanel* Panel2_Meteors;
        wxStaticText* StaticText10;
        wxButton* Button_Palette1_6;
        wxStaticText* StaticText35;
        wxFlexGridSizer* FlexGridSizer_Palette1;
        wxCheckBox* CheckBox_ColorWash2_VFade;
        wxPanel* Panel2_Life;
        wxStaticText* StaticText23;
        wxStaticText* StaticText33;
        wxStaticText* StaticText12;
        wxCheckBox* CheckBox_ColorWash2_HFade;
        wxCheckBox* CheckBox_Palette2_4;
        wxPanel* Panel1_Pictures;
        wxStaticText* StaticText22;
        wxButton* Button_Palette1_4;
        wxStaticText* StaticText56;
        wxButton* Button_Palette1_3;
        wxPanel* Panel1_Meteors;
        wxButton* Button_Pictures1_Filename;
        wxButton* Button_Palette1_2;
        wxTextCtrl* TextCtrl_Pictures1_Filename;
        wxStaticText* StaticText55;
        wxButton* Button_PresetAdd;
        wxScrolledWindow* ScrolledWindow1;
        wxButton* Button_UpdateGrid;
        wxCheckBox* CheckBox_Palette1_6;
        wxPanel* Panel2_Fire;
        wxSlider* Slider_Text2_Top;
        wxStaticText* StaticText7;
        wxPanel* Panel2_Garlands;
        wxSlider* Slider_Spirals2_Rotation;
        wxStaticText* StaticText16;
        wxSlider* Slider_SparkleFrequency;
        wxFlexGridSizer* FlexGridSizer_Palette2;
        wxGrid* Grid1;
        wxSlider* Slider_Speed1;
        wxCheckBox* CheckBox_Spirals1_Blend;
        wxStaticText* StaticText57;
        wxSlider* Slider_Spirals2_Direction;
        wxStaticText* StaticText47;
        wxPanel* Panel2_ColorWash;
        wxCheckBox* CheckBox_Palette2_5;
        wxStaticText* StaticText43;
        wxCheckBox* CheckBox_ColorWash1_VFade;
        wxButton* Button_Palette2_1;
        wxSlider* Slider_Spirals2_Count;
        wxSlider* Slider_Spirals1_Direction;
        wxStaticText* StaticText14;
        wxStaticText* StaticText34;
        wxSlider* Slider_Spirals1_Count;
        wxPanel* Panel2_Spirals;
        wxStaticText* StaticText18;
        wxCheckBox* CheckBox_SendOutput;
        wxStaticText* StaticText37;
        wxCheckBox* CheckBox_Bars2_Highlight;
        wxStaticText* StaticText13;
        wxSlider* Slider_Bars1_BarCount;
        wxStaticText* StaticText51;
        wxChoice* Choice_Pictures1_Direction;
        wxStaticText* StaticText53;
        wxButton* Button_Pictures2_Filename;
        wxStaticText* StaticText20;
        wxStaticText* StaticText54;
        wxPanel* Panel2_Snowstorm;
        wxPanel* Panel1_Snowflakes;
        wxTextCtrl* TextCtrl_Pictures2_Filename;
        wxButton* Button_PresetUpdate;
        wxButton* Button_Open;
        wxStaticText* StaticText31;
        wxSlider* Slider_Butterfly1_Skip;
        wxPanel* Panel1_Fire;
        wxButton* Button_Palette2_3;
        wxButton* Button_Palette1_5;
        wxStaticText* StaticText_MediaFile;
        wxButton* Button_TimeSlots;
        wxSlider* Slider_Text1_Top;
        wxPanel* Panel2_Snowflakes;
        wxCheckBox* CheckBox_Palette1_4;
        wxPanel* Panel2_Bars;
        wxChoice* Choice_Meteors1_Type;
        wxColourDialog* ColourDialog1;
        wxSlider* Slider_Life2_Seed;
        wxPanel* Panel1_None;
        wxChoice* Choice_Meteors2_Type;
        wxStaticText* StaticText45;
        wxSlider* Slider_Meteors2_Length;
        wxStaticText* StaticText21;
        wxStaticText* StaticText4;
        wxChoice* Choice_LayerMethod;
        wxTextCtrl* TextCtrl_Text2_Line1;
        wxSlider* Slider_Life2_Count;
        wxStaticText* StaticText59;
        wxChoice* Choice_Presets;
        wxButton* Button_Models;
        wxPanel* Panel2_Pictures;
        wxSlider* Slider_Bars2_BarCount;
        wxCheckBox* CheckBox_Spirals2_3D;
        wxStaticText* StaticText15;
        wxStaticText* StaticText26;
        wxButton* Button_Palette2_5;
        wxStaticText* StaticText8;
        wxSlider* Slider_Garlands1_Spacing;
        wxStaticText* StaticText30;
        wxStaticText* StaticText29;
        wxStaticText* StaticText58;
        wxSlider* Slider_Meteors1_Count;
        wxPanel* Panel1_Butterfly;
        wxPanel* Panel1_Spirals;
        wxPanel* Panel2_Text;
        wxCheckBox* CheckBox_Palette1_2;
        wxSlider* Slider_Spirals1_Rotation;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxCheckBox* CheckBox_ColorWash1_HFade;
        wxChoice* Choice_Pictures2_Direction;
        wxPanel* Panel1_Text;
        wxCheckBox* CheckBox_Palette1_1;
        wxStaticText* StaticText38;
        wxStaticText* StaticText17;
        wxCheckBox* CheckBox_Palette2_2;
        wxStaticText* StaticText11;
        wxButton* Button_SaveEffects;
        wxSlider* Slider_Spirals2_Thickness;
        wxSlider* Slider_Snowstorm2_Length;
        wxCheckBox* CheckBox_Bars1_3D;
        wxStaticText* StaticText9;
        wxButton* Button_Save;
        wxCheckBox* CheckBox_Spirals1_3D;
        wxSlider* Slider_Butterfly1_Chunks;
        wxButton* Button_Palette2;
        wxSlider* Slider_Garlands2_Spacing;
        wxTextCtrl* TextCtrl_Text2_Line2;
        wxCheckBox* CheckBox_Bars2_3D;
        wxPanel* Panel1_Bars;
        wxPanel* Panel1_Snowstorm;
        wxSlider* Slider_Butterfly2_Skip;
        wxStaticText* StaticText44;
        wxPanel* Panel2_None;
        //*)

        void ChooseColor(wxTextCtrl* TextCtrl);
        bool LoadNetworkFile();
        void LoadEffectsFile();
        bool SaveEffectsFile();
        void CreateDefaultEffectsXml();
        void UpdateEffectsList();
        void UpdateModelsList();
        void PresetsSelect();
        void SetPlayMode(play_modes newmode);
        void SetChoicebook(wxChoicebook* cb, wxString& PageName);
        void SetControls(wxXmlNode* x);
        wxXmlNode* CreateEffectNode(wxString& name);
        void LoadPageControlsToAttr(wxWindow* page,wxXmlNode* x);
        void LoadSizerControlsToAttr(wxSizer* sizer,wxXmlNode* x);
        bool AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels);
        void TimerEffect();
        void TimerSeqPartial();
        void TimerSeqAll();
        void UpdateBufferPalette();
        bool LoadXlightsFile(wxString& FileName);
        void SetMediaFilename(const wxString& filename);
        void DisplayError(const wxString& msg);

        wxString CurrentDir;
        wxDateTime starttime;
        xOutput* xout;
        wxXmlDocument EffectsXml;
        wxXmlNode* EffectsNode;
        wxXmlNode* ModelsNode;
        bool UnsavedChanges;
        bool PaletteChanged;
        bool MixTypeChanged;
        play_modes play_mode;
        PixelBufferClass buffer;
        wxHtmlEasyPrinting* HtmlEasyPrint;
        PlayerFrame* PlayerDlg;
        int VixNumPeriods;
        long VixNumChannels;
        wxUint8* VixEventData;
        wxString mediaFilename;

        DECLARE_EVENT_TABLE()
};

#endif // XRGBMAIN_H
