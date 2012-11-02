/***************************************************************
 * Name:      xRGBMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2012-10-09
 * Copyright: 2012 by Matt Brown
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

#include "xRGBMain.h"
#include <wx/msgdlg.h>
#include <wx/textdlg.h>

#include "../include/xlights.xpm"


//(*InternalHeaders(xRGBFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(xRGBFrame)
const long xRGBFrame::ID_SCROLLEDWINDOW1 = wxNewId();
const long xRGBFrame::ID_BUTTON7 = wxNewId();
const long xRGBFrame::ID_CHECKBOX1 = wxNewId();
const long xRGBFrame::ID_STATICTEXT1 = wxNewId();
const long xRGBFrame::ID_STATICTEXT5 = wxNewId();
const long xRGBFrame::ID_BUTTON5 = wxNewId();
const long xRGBFrame::ID_BUTTON1 = wxNewId();
const long xRGBFrame::ID_BUTTON3 = wxNewId();
const long xRGBFrame::ID_BUTTON11 = wxNewId();
const long xRGBFrame::ID_BUTTON6 = wxNewId();
const long xRGBFrame::ID_BUTTON2 = wxNewId();
const long xRGBFrame::ID_BUTTON4 = wxNewId();
const long xRGBFrame::ID_BUTTON12 = wxNewId();
const long xRGBFrame::ID_GRID1 = wxNewId();
const long xRGBFrame::ID_BUTTON58 = wxNewId();
const long xRGBFrame::ID_CHOICE7 = wxNewId();
const long xRGBFrame::ID_BUTTON13 = wxNewId();
const long xRGBFrame::ID_BUTTON59 = wxNewId();
const long xRGBFrame::ID_CHOICE2 = wxNewId();
const long xRGBFrame::ID_BUTTON9 = wxNewId();
const long xRGBFrame::ID_BUTTON8 = wxNewId();
const long xRGBFrame::ID_BUTTON10 = wxNewId();
const long xRGBFrame::ID_STATICTEXT2 = wxNewId();
const long xRGBFrame::ID_CHOICE_LayerMethod = wxNewId();
const long xRGBFrame::ID_BUTTON56 = wxNewId();
const long xRGBFrame::ID_STATICTEXT3 = wxNewId();
const long xRGBFrame::ID_SLIDER_SparkleDensity = wxNewId();
const long xRGBFrame::ID_STATICTEXT6 = wxNewId();
const long xRGBFrame::ID_SLIDER_SparkleFrequency = wxNewId();
const long xRGBFrame::ID_PANEL2 = wxNewId();
const long xRGBFrame::ID_STATICTEXT17 = wxNewId();
const long xRGBFrame::ID_SLIDER_Bars1_BarCount = wxNewId();
const long xRGBFrame::ID_STATICTEXT21 = wxNewId();
const long xRGBFrame::ID_CHOICE_Bars1_Direction = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Bars1_Highlight = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Bars1_3D = wxNewId();
const long xRGBFrame::ID_PANEL8 = wxNewId();
const long xRGBFrame::ID_STATICTEXT19 = wxNewId();
const long xRGBFrame::ID_CHOICE1 = wxNewId();
const long xRGBFrame::ID_STATICTEXT23 = wxNewId();
const long xRGBFrame::ID_SLIDER_Butterfly1_Style = wxNewId();
const long xRGBFrame::ID_STATICTEXT25 = wxNewId();
const long xRGBFrame::ID_SLIDER_Butterfly1_Chunks = wxNewId();
const long xRGBFrame::ID_STATICTEXT26 = wxNewId();
const long xRGBFrame::ID_SLIDER_Butterfly1_Skip = wxNewId();
const long xRGBFrame::ID_PANEL10 = wxNewId();
const long xRGBFrame::ID_STATICTEXT7 = wxNewId();
const long xRGBFrame::ID_CHECKBOX_ColorWash1_HFade = wxNewId();
const long xRGBFrame::ID_STATICTEXT8 = wxNewId();
const long xRGBFrame::ID_CHECKBOX_ColorWash1_VFade = wxNewId();
const long xRGBFrame::ID_PANEL5 = wxNewId();
const long xRGBFrame::ID_PANEL12 = wxNewId();
const long xRGBFrame::ID_STATICTEXT31 = wxNewId();
const long xRGBFrame::ID_SLIDER_Garlands1_Type = wxNewId();
const long xRGBFrame::ID_STATICTEXT32 = wxNewId();
const long xRGBFrame::ID_SLIDER_Garlands1_Spacing = wxNewId();
const long xRGBFrame::ID_PANEL14 = wxNewId();
const long xRGBFrame::ID_STATICTEXT35 = wxNewId();
const long xRGBFrame::ID_SLIDER_Life1_Count = wxNewId();
const long xRGBFrame::ID_STATICTEXT37 = wxNewId();
const long xRGBFrame::ID_SLIDER_Life1_Seed = wxNewId();
const long xRGBFrame::ID_PANEL16 = wxNewId();
const long xRGBFrame::ID_STATICTEXT39 = wxNewId();
const long xRGBFrame::ID_CHOICE_Meteors1_Type = wxNewId();
const long xRGBFrame::ID_STATICTEXT41 = wxNewId();
const long xRGBFrame::ID_SLIDER_Meteors1_Count = wxNewId();
const long xRGBFrame::ID_STATICTEXT43 = wxNewId();
const long xRGBFrame::ID_SLIDER_Meteors1_Length = wxNewId();
const long xRGBFrame::ID_PANEL18 = wxNewId();
const long xRGBFrame::ID_BUTTON42 = wxNewId();
const long xRGBFrame::ID_TEXTCTRL_Pictures1_Filename = wxNewId();
const long xRGBFrame::ID_STATICTEXT46 = wxNewId();
const long xRGBFrame::ID_CHOICE_Pictures1_Direction = wxNewId();
const long xRGBFrame::ID_PANEL20 = wxNewId();
const long xRGBFrame::ID_PANEL22 = wxNewId();
const long xRGBFrame::ID_STATICTEXT45 = wxNewId();
const long xRGBFrame::ID_SLIDER_Snowstorm1_Count = wxNewId();
const long xRGBFrame::ID_STATICTEXT51 = wxNewId();
const long xRGBFrame::ID_SLIDER_Snowstorm1_Length = wxNewId();
const long xRGBFrame::ID_PANEL24 = wxNewId();
const long xRGBFrame::ID_STATICTEXT9 = wxNewId();
const long xRGBFrame::ID_SLIDER_Spirals1_Count = wxNewId();
const long xRGBFrame::ID_STATICTEXT10 = wxNewId();
const long xRGBFrame::ID_SLIDER_Spirals1_Rotation = wxNewId();
const long xRGBFrame::ID_STATICTEXT11 = wxNewId();
const long xRGBFrame::ID_SLIDER_Spirals1_Thickness = wxNewId();
const long xRGBFrame::ID_STATICTEXT24 = wxNewId();
const long xRGBFrame::ID_SLIDER_Spirals1_Direction = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Spirals1_Blend = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Spirals1_3D = wxNewId();
const long xRGBFrame::ID_PANEL26 = wxNewId();
const long xRGBFrame::ID_STATICTEXT53 = wxNewId();
const long xRGBFrame::ID_TEXTCTRL_Text1_Line1 = wxNewId();
const long xRGBFrame::ID_STATICTEXT54 = wxNewId();
const long xRGBFrame::ID_TEXTCTRL_Text1_Line2 = wxNewId();
const long xRGBFrame::ID_STATICTEXT57 = wxNewId();
const long xRGBFrame::ID_SLIDER_Text1_Top = wxNewId();
const long xRGBFrame::ID_PANEL7 = wxNewId();
const long xRGBFrame::ID_CHOICEBOOK1 = wxNewId();
const long xRGBFrame::ID_BUTTON_Palette1 = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Palette1_1 = wxNewId();
const long xRGBFrame::ID_BUTTON_Palette1_1 = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Palette1_2 = wxNewId();
const long xRGBFrame::ID_BUTTON_Palette1_2 = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Palette1_3 = wxNewId();
const long xRGBFrame::ID_BUTTON_Palette1_3 = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Palette1_4 = wxNewId();
const long xRGBFrame::ID_BUTTON_Palette1_4 = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Palette1_5 = wxNewId();
const long xRGBFrame::ID_BUTTON_Palette1_5 = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Palette1_6 = wxNewId();
const long xRGBFrame::ID_BUTTON_Palette1_6 = wxNewId();
const long xRGBFrame::ID_STATICTEXT61 = wxNewId();
const long xRGBFrame::ID_SLIDER_Speed1 = wxNewId();
const long xRGBFrame::ID_PANEL3 = wxNewId();
const long xRGBFrame::ID_STATICTEXT18 = wxNewId();
const long xRGBFrame::ID_SLIDER_Bars2_BarCount = wxNewId();
const long xRGBFrame::ID_STATICTEXT22 = wxNewId();
const long xRGBFrame::ID_CHOICE_Bars2_Direction = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Bars2_Highlight = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Bars2_3D = wxNewId();
const long xRGBFrame::ID_PANEL9 = wxNewId();
const long xRGBFrame::ID_STATICTEXT20 = wxNewId();
const long xRGBFrame::ID_CHOICE3 = wxNewId();
const long xRGBFrame::ID_STATICTEXT27 = wxNewId();
const long xRGBFrame::ID_SLIDER_Butterfly2_Style = wxNewId();
const long xRGBFrame::ID_STATICTEXT29 = wxNewId();
const long xRGBFrame::ID_SLIDER_Butterfly2_Chunks = wxNewId();
const long xRGBFrame::ID_STATICTEXT30 = wxNewId();
const long xRGBFrame::ID_SLIDER_Butterfly2_Skip = wxNewId();
const long xRGBFrame::ID_PANEL11 = wxNewId();
const long xRGBFrame::ID_STATICTEXT12 = wxNewId();
const long xRGBFrame::ID_CHECKBOX_ColorWash2_HFade = wxNewId();
const long xRGBFrame::ID_STATICTEXT16 = wxNewId();
const long xRGBFrame::ID_CHECKBOX_ColorWash2_VFade = wxNewId();
const long xRGBFrame::ID_PANEL6 = wxNewId();
const long xRGBFrame::ID_PANEL13 = wxNewId();
const long xRGBFrame::ID_STATICTEXT33 = wxNewId();
const long xRGBFrame::ID_SLIDER_Garlands2_Type = wxNewId();
const long xRGBFrame::ID_STATICTEXT34 = wxNewId();
const long xRGBFrame::ID_SLIDER_Garlands2_Spacing = wxNewId();
const long xRGBFrame::ID_PANEL15 = wxNewId();
const long xRGBFrame::ID_STATICTEXT36 = wxNewId();
const long xRGBFrame::ID_SLIDER_Life2_Count = wxNewId();
const long xRGBFrame::ID_STATICTEXT38 = wxNewId();
const long xRGBFrame::ID_SLIDER_Life2_Seed = wxNewId();
const long xRGBFrame::ID_PANEL17 = wxNewId();
const long xRGBFrame::ID_STATICTEXT40 = wxNewId();
const long xRGBFrame::ID_CHOICE_Meteors2_Type = wxNewId();
const long xRGBFrame::ID_STATICTEXT42 = wxNewId();
const long xRGBFrame::ID_SLIDER_Meteors2_Count = wxNewId();
const long xRGBFrame::ID_STATICTEXT44 = wxNewId();
const long xRGBFrame::ID_SLIDER_Meteors2_Length = wxNewId();
const long xRGBFrame::ID_PANEL19 = wxNewId();
const long xRGBFrame::ID_BUTTON47 = wxNewId();
const long xRGBFrame::ID_TEXTCTRL_Pictures2_Filename = wxNewId();
const long xRGBFrame::ID_STATICTEXT47 = wxNewId();
const long xRGBFrame::ID_CHOICE_Pictures2_Direction = wxNewId();
const long xRGBFrame::ID_PANEL21 = wxNewId();
const long xRGBFrame::ID_PANEL23 = wxNewId();
const long xRGBFrame::ID_STATICTEXT50 = wxNewId();
const long xRGBFrame::ID_SLIDER_Snowstorm2_Count = wxNewId();
const long xRGBFrame::ID_STATICTEXT52 = wxNewId();
const long xRGBFrame::ID_SLIDER_Snowstorm2_Length = wxNewId();
const long xRGBFrame::ID_PANEL25 = wxNewId();
const long xRGBFrame::ID_STATICTEXT13 = wxNewId();
const long xRGBFrame::ID_SLIDER_Spirals2_Count = wxNewId();
const long xRGBFrame::ID_STATICTEXT14 = wxNewId();
const long xRGBFrame::ID_SLIDER_Spirals2_Rotation = wxNewId();
const long xRGBFrame::ID_STATICTEXT15 = wxNewId();
const long xRGBFrame::ID_SLIDER_Spirals2_Thickness = wxNewId();
const long xRGBFrame::ID_STATICTEXT28 = wxNewId();
const long xRGBFrame::ID_SLIDER_Spirals2_Direction = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Spirals2_Blend = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Spirals2_3D = wxNewId();
const long xRGBFrame::ID_PANEL4 = wxNewId();
const long xRGBFrame::ID_STATICTEXT55 = wxNewId();
const long xRGBFrame::ID_TEXTCTRL_Text2_Line1 = wxNewId();
const long xRGBFrame::ID_STATICTEXT56 = wxNewId();
const long xRGBFrame::ID_TEXTCTRL_Text2_Line2 = wxNewId();
const long xRGBFrame::ID_STATICTEXT58 = wxNewId();
const long xRGBFrame::ID_SLIDER_Text2_Top = wxNewId();
const long xRGBFrame::ID_PANEL27 = wxNewId();
const long xRGBFrame::ID_CHOICEBOOK2 = wxNewId();
const long xRGBFrame::ID_BUTTON_Palette2 = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Palette2_1 = wxNewId();
const long xRGBFrame::ID_BUTTON_Palette2_1 = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Palette2_2 = wxNewId();
const long xRGBFrame::ID_BUTTON_Palette2_2 = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Palette2_3 = wxNewId();
const long xRGBFrame::ID_BUTTON_Palette2_3 = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Palette2_4 = wxNewId();
const long xRGBFrame::ID_BUTTON_Palette2_4 = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Palette2_5 = wxNewId();
const long xRGBFrame::ID_BUTTON_Palette2_5 = wxNewId();
const long xRGBFrame::ID_CHECKBOX_Palette2_6 = wxNewId();
const long xRGBFrame::ID_BUTTON_Palette2_6 = wxNewId();
const long xRGBFrame::ID_STATICTEXT4 = wxNewId();
const long xRGBFrame::ID_SLIDER_Speed2 = wxNewId();
const long xRGBFrame::ID_PANEL1 = wxNewId();
const long xRGBFrame::idMenuQuit = wxNewId();
const long xRGBFrame::idMenuAbout = wxNewId();
const long xRGBFrame::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(xRGBFrame,wxFrame)
    //(*EventTable(xRGBFrame)
    //*)
END_EVENT_TABLE()

xRGBFrame::xRGBFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(xRGBFrame)
    wxStaticBoxSizer* StaticBoxSizer2;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer16;
    wxFlexGridSizer* FlexGridSizer24;
    wxFlexGridSizer* FlexGridSizer19;
    wxFlexGridSizer* FlexGridSizer23;
    wxMenuItem* MenuItem2;
    wxFlexGridSizer* FlexGridSizer10;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer27;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer25;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer22;
    wxFlexGridSizer* FlexGridSizer9;
    wxFlexGridSizer* FlexGridSizer2;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxFlexGridSizer* FlexGridSizer7;
    wxFlexGridSizer* FlexGridSizer29;
    wxFlexGridSizer* FlexGridSizer34;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxGridSizer* GridSizer1;
    wxFlexGridSizer* FlexGridSizer15;
    wxFlexGridSizer* FlexGridSizer18;
    wxFlexGridSizer* FlexGridSizer8;
    wxFlexGridSizer* FlexGridSizer21;
    wxFlexGridSizer* FlexGridSizer14;
    wxFlexGridSizer* FlexGridSizer20;
    wxBoxSizer* BoxSizer1;
    wxFlexGridSizer* FlexGridSizer13;
    wxFlexGridSizer* FlexGridSizer35;
    wxFlexGridSizer* FlexGridSizer12;
    wxFlexGridSizer* FlexGridSizer36;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer6;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer11;
    wxBoxSizer* BoxSizer3;
    wxFlexGridSizer* FlexGridSizer17;
    wxMenu* Menu2;
    wxFlexGridSizer* FlexGridSizer32;
    wxFlexGridSizer* FlexGridSizer31;
    wxFlexGridSizer* FlexGridSizer28;
    wxFlexGridSizer* FlexGridSizer26;
    wxFlexGridSizer* FlexGridSizer30;

    Create(parent, wxID_ANY, _("xLights RGB Sequencer"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetBackgroundColour(wxColour(160,160,160));
    FlexGridSizer1 = new wxFlexGridSizer(2, 2, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    FlexGridSizer9 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer9->AddGrowableCol(0);
    FlexGridSizer9->AddGrowableRow(0);
    ScrolledWindow1 = new wxScrolledWindow(Panel1, ID_SCROLLEDWINDOW1, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL|wxSIMPLE_BORDER, _T("ID_SCROLLEDWINDOW1"));
    ScrolledWindow1->SetBackgroundColour(wxColour(0,0,0));
    FlexGridSizer9->Add(ScrolledWindow1, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
    FlexGridSizer11 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer11->AddGrowableCol(2);
    FlexGridSizer11->AddGrowableRow(0);
    Button_Stop = new wxButton(Panel1, ID_BUTTON7, _("Stop"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    Button_Stop->Disable();
    Button_Stop->SetBackgroundColour(wxColour(255,0,0));
    FlexGridSizer11->Add(Button_Stop, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_SendOutput = new wxCheckBox(Panel1, ID_CHECKBOX1, _("Send to lights"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox_SendOutput->SetValue(false);
    FlexGridSizer11->Add(CheckBox_SendOutput, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    StaticText_PlaybackMode = new wxStaticText(Panel1, ID_STATICTEXT1, _("Playback mode"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText_PlaybackMode->SetForegroundColour(wxColour(240,240,240));
    BoxSizer3->Add(StaticText_PlaybackMode, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    StaticText_MediaFile = new wxStaticText(Panel1, ID_STATICTEXT5, _("Media File: none"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StaticText_MediaFile->SetForegroundColour(wxColour(240,240,240));
    BoxSizer3->Add(StaticText_MediaFile, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer11->Add(BoxSizer3, 1, wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer9->Add(FlexGridSizer11, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer1->Add(FlexGridSizer9, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5 = new wxFlexGridSizer(0, 1, 0, 0);
    GridSizer1 = new wxGridSizer(2, 4, 0, 0);
    Button_PlaySelection = new wxButton(Panel1, ID_BUTTON5, _("Play Selection"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    Button_PlaySelection->SetBackgroundColour(wxColour(0,255,0));
    GridSizer1->Add(Button_PlaySelection, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    Button_DisplayElements = new wxButton(Panel1, ID_BUTTON1, _("Display Elements"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button_DisplayElements->SetBackgroundColour(wxColour(224,224,224));
    GridSizer1->Add(Button_DisplayElements, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    Button_MediaFile = new wxButton(Panel1, ID_BUTTON3, _("Media File"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Button_MediaFile->SetBackgroundColour(wxColour(224,224,224));
    GridSizer1->Add(Button_MediaFile, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    Button_Open = new wxButton(Panel1, ID_BUTTON11, _("Open Sequence"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
    Button_Open->SetBackgroundColour(wxColour(224,224,224));
    GridSizer1->Add(Button_Open, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    Button_PlayAll = new wxButton(Panel1, ID_BUTTON6, _("Play All"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    Button_PlayAll->SetBackgroundColour(wxColour(0,255,0));
    GridSizer1->Add(Button_PlayAll, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    Button_TimeSlots = new wxButton(Panel1, ID_BUTTON2, _("Time Slots"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Button_TimeSlots->SetBackgroundColour(wxColour(224,224,224));
    GridSizer1->Add(Button_TimeSlots, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    Button_Export = new wxButton(Panel1, ID_BUTTON4, _("Import/Export"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    Button_Export->SetBackgroundColour(wxColour(224,224,224));
    GridSizer1->Add(Button_Export, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    Button_Save = new wxButton(Panel1, ID_BUTTON12, _("Save Sequence"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON12"));
    Button_Save->SetBackgroundColour(wxColour(224,224,224));
    GridSizer1->Add(Button_Save, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    FlexGridSizer5->Add(GridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Grid1 = new wxGrid(Panel1, ID_GRID1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID1"));
    Grid1->CreateGrid(10,3);
    Grid1->EnableEditing(true);
    Grid1->EnableGridLines(true);
    Grid1->SetRowLabelSize(35);
    Grid1->SetColLabelValue(0, _("Start Time"));
    Grid1->SetColLabelValue(1, _("End Time"));
    Grid1->SetColLabelValue(2, _("Label"));
    Grid1->SetDefaultCellFont( Grid1->GetFont() );
    Grid1->SetDefaultCellTextColour( Grid1->GetForegroundColour() );
    FlexGridSizer5->Add(Grid1, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer1->Add(FlexGridSizer5, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Combined Effect"));
    FlexGridSizer6 = new wxFlexGridSizer(0, 3, 0, 0);
    Button_Models = new wxButton(Panel1, ID_BUTTON58, _("Models"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON58"));
    Button_Models->SetBackgroundColour(wxColour(224,224,224));
    FlexGridSizer6->Add(Button_Models, 1, wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Choice_Models = new wxChoice(Panel1, ID_CHOICE7, wxDefaultPosition, wxDefaultSize, 0, 0, wxCB_SORT, wxDefaultValidator, _T("ID_CHOICE7"));
    FlexGridSizer6->Add(Choice_Models, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Button_PlayEffect = new wxButton(Panel1, ID_BUTTON13, _("Play Effect"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON13"));
    Button_PlayEffect->Disable();
    Button_PlayEffect->SetBackgroundColour(wxColour(0,255,0));
    FlexGridSizer6->Add(Button_PlayEffect, 1, wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_Presets = new wxButton(Panel1, ID_BUTTON59, _("Effect Presets"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON59"));
    Button_Presets->SetBackgroundColour(wxColour(224,224,224));
    FlexGridSizer6->Add(Button_Presets, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Choice_Presets = new wxChoice(Panel1, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, wxCB_SORT, wxDefaultValidator, _T("ID_CHOICE2"));
    FlexGridSizer6->Add(Choice_Presets, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6->Add(-1,-1,1, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_PresetAdd = new wxButton(Panel1, ID_BUTTON9, _("Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
    Button_PresetAdd->SetBackgroundColour(wxColour(224,224,224));
    FlexGridSizer6->Add(Button_PresetAdd, 1, wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Button_PresetUpdate = new wxButton(Panel1, ID_BUTTON8, _("Update"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
    Button_PresetUpdate->SetBackgroundColour(wxColour(224,224,224));
    FlexGridSizer6->Add(Button_PresetUpdate, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Button_UpdateGrid = new wxButton(Panel1, ID_BUTTON10, _("Update Grid"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
    Button_UpdateGrid->SetBackgroundColour(wxColour(224,224,224));
    FlexGridSizer6->Add(Button_UpdateGrid, 1, wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Layer Method"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer6->Add(StaticText2, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Choice_LayerMethod = new wxChoice(Panel1, ID_CHOICE_LayerMethod, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_LayerMethod"));
    Choice_LayerMethod->SetSelection( Choice_LayerMethod->Append(_("Effect 1")) );
    Choice_LayerMethod->Append(_("Effect 2"));
    Choice_LayerMethod->Append(_("1 is Mask"));
    Choice_LayerMethod->Append(_("2 is Mask"));
    Choice_LayerMethod->Append(_("Layered"));
    Choice_LayerMethod->Append(_("Average"));
    FlexGridSizer6->Add(Choice_LayerMethod, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Button_SaveEffects = new wxButton(Panel1, ID_BUTTON56, _("Save File"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON56"));
    Button_SaveEffects->SetBackgroundColour(wxColour(224,224,224));
    FlexGridSizer6->Add(Button_SaveEffects, 1, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("Sparkle Density"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer6->Add(StaticText3, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Slider_SparkleDensity = new wxSlider(Panel1, ID_SLIDER_SparkleDensity, 0, 0, 50, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_SparkleDensity"));
    FlexGridSizer6->Add(Slider_SparkleDensity, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6->Add(-1,-1,1, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(Panel1, ID_STATICTEXT6, _("Sparkle Frequency"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    FlexGridSizer6->Add(StaticText6, 1, wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Slider_SparkleFrequency = new wxSlider(Panel1, ID_SLIDER_SparkleFrequency, 200, 10, 200, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER_SparkleFrequency"));
    FlexGridSizer6->Add(Slider_SparkleFrequency, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6->Add(-1,-1,1, wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3->Add(FlexGridSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(StaticBoxSizer3, 2, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, Panel1, _("Effect 1"));
    FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 0);
    Choicebook1 = new wxChoicebook(Panel1, ID_CHOICEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_CHOICEBOOK1"));
    Panel1_None = new wxPanel(Choicebook1, ID_PANEL2, wxPoint(0,6), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Panel1_Bars = new wxPanel(Choicebook1, ID_PANEL8, wxPoint(30,18), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL8"));
    FlexGridSizer12 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText17 = new wxStaticText(Panel1_Bars, ID_STATICTEXT17, _("# of Bars"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    FlexGridSizer12->Add(StaticText17, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Bars1_BarCount = new wxSlider(Panel1_Bars, ID_SLIDER_Bars1_BarCount, 1, 1, 10, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Bars1_BarCount"));
    FlexGridSizer12->Add(Slider_Bars1_BarCount, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText21 = new wxStaticText(Panel1_Bars, ID_STATICTEXT21, _("Direction"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    FlexGridSizer12->Add(StaticText21, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Choice_Bars1_Direction = new wxChoice(Panel1_Bars, ID_CHOICE_Bars1_Direction, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_Bars1_Direction"));
    Choice_Bars1_Direction->SetSelection( Choice_Bars1_Direction->Append(_("up")) );
    Choice_Bars1_Direction->Append(_("down"));
    Choice_Bars1_Direction->Append(_("expand"));
    Choice_Bars1_Direction->Append(_("compress"));
    FlexGridSizer12->Add(Choice_Bars1_Direction, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    CheckBox_Bars1_Highlight = new wxCheckBox(Panel1_Bars, ID_CHECKBOX_Bars1_Highlight, _("Highlight"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Bars1_Highlight"));
    CheckBox_Bars1_Highlight->SetValue(false);
    FlexGridSizer12->Add(CheckBox_Bars1_Highlight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    CheckBox_Bars1_3D = new wxCheckBox(Panel1_Bars, ID_CHECKBOX_Bars1_3D, _("3D"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Bars1_3D"));
    CheckBox_Bars1_3D->SetValue(false);
    FlexGridSizer12->Add(CheckBox_Bars1_3D, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel1_Bars->SetSizer(FlexGridSizer12);
    FlexGridSizer12->Fit(Panel1_Bars);
    FlexGridSizer12->SetSizeHints(Panel1_Bars);
    Panel1_Butterfly = new wxPanel(Choicebook1, ID_PANEL10, wxPoint(41,11), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL10"));
    FlexGridSizer14 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText12 = new wxStaticText(Panel1_Butterfly, ID_STATICTEXT19, _("Colors"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    FlexGridSizer14->Add(StaticText12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Choice_Butterfly1_Colors = new wxChoice(Panel1_Butterfly, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice_Butterfly1_Colors->SetSelection( Choice_Butterfly1_Colors->Append(_("Rainbow")) );
    Choice_Butterfly1_Colors->Append(_("Palette"));
    FlexGridSizer14->Add(Choice_Butterfly1_Colors, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText23 = new wxStaticText(Panel1_Butterfly, ID_STATICTEXT23, _("Style"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
    FlexGridSizer14->Add(StaticText23, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Butterfly1_Style = new wxSlider(Panel1_Butterfly, ID_SLIDER_Butterfly1_Style, 1, 1, 3, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Butterfly1_Style"));
    FlexGridSizer14->Add(Slider_Butterfly1_Style, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText25 = new wxStaticText(Panel1_Butterfly, ID_STATICTEXT25, _("Bkgrd Chunks"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
    FlexGridSizer14->Add(StaticText25, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Butterfly1_Chunks = new wxSlider(Panel1_Butterfly, ID_SLIDER_Butterfly1_Chunks, 1, 1, 10, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Butterfly1_Chunks"));
    FlexGridSizer14->Add(Slider_Butterfly1_Chunks, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText26 = new wxStaticText(Panel1_Butterfly, ID_STATICTEXT26, _("Bkgrd Skip"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
    FlexGridSizer14->Add(StaticText26, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Butterfly1_Skip = new wxSlider(Panel1_Butterfly, ID_SLIDER_Butterfly1_Skip, 2, 2, 10, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Butterfly1_Skip"));
    FlexGridSizer14->Add(Slider_Butterfly1_Skip, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel1_Butterfly->SetSizer(FlexGridSizer14);
    FlexGridSizer14->Fit(Panel1_Butterfly);
    FlexGridSizer14->SetSizeHints(Panel1_Butterfly);
    Panel1_ColorWash = new wxPanel(Choicebook1, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText4 = new wxStaticText(Panel1_ColorWash, ID_STATICTEXT7, _("Horizontal"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    FlexGridSizer2->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_ColorWash1_HFade = new wxCheckBox(Panel1_ColorWash, ID_CHECKBOX_ColorWash1_HFade, _("Fade"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_ColorWash1_HFade"));
    CheckBox_ColorWash1_HFade->SetValue(false);
    FlexGridSizer2->Add(CheckBox_ColorWash1_HFade, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(Panel1_ColorWash, ID_STATICTEXT8, _("Vertical"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    FlexGridSizer2->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_ColorWash1_VFade = new wxCheckBox(Panel1_ColorWash, ID_CHECKBOX_ColorWash1_VFade, _("Fade"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_ColorWash1_VFade"));
    CheckBox_ColorWash1_VFade->SetValue(false);
    FlexGridSizer2->Add(CheckBox_ColorWash1_VFade, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1_ColorWash->SetSizer(FlexGridSizer2);
    FlexGridSizer2->Fit(Panel1_ColorWash);
    FlexGridSizer2->SetSizeHints(Panel1_ColorWash);
    Panel1_Fire = new wxPanel(Choicebook1, ID_PANEL12, wxPoint(11,13), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL12"));
    FlexGridSizer16 = new wxFlexGridSizer(0, 2, 0, 0);
    Panel1_Fire->SetSizer(FlexGridSizer16);
    FlexGridSizer16->Fit(Panel1_Fire);
    FlexGridSizer16->SetSizeHints(Panel1_Fire);
    Panel1_Garlands = new wxPanel(Choicebook1, ID_PANEL14, wxPoint(16,15), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL14"));
    FlexGridSizer18 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText31 = new wxStaticText(Panel1_Garlands, ID_STATICTEXT31, _("Garland Type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT31"));
    FlexGridSizer18->Add(StaticText31, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Garlands1_Type = new wxSlider(Panel1_Garlands, ID_SLIDER_Garlands1_Type, 0, 0, 4, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Garlands1_Type"));
    FlexGridSizer18->Add(Slider_Garlands1_Type, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText32 = new wxStaticText(Panel1_Garlands, ID_STATICTEXT32, _("Spacing"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT32"));
    FlexGridSizer18->Add(StaticText32, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Garlands1_Spacing = new wxSlider(Panel1_Garlands, ID_SLIDER_Garlands1_Spacing, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Garlands1_Spacing"));
    FlexGridSizer18->Add(Slider_Garlands1_Spacing, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel1_Garlands->SetSizer(FlexGridSizer18);
    FlexGridSizer18->Fit(Panel1_Garlands);
    FlexGridSizer18->SetSizeHints(Panel1_Garlands);
    Panel1_Life = new wxPanel(Choicebook1, ID_PANEL16, wxPoint(30,13), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL16"));
    FlexGridSizer20 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText35 = new wxStaticText(Panel1_Life, ID_STATICTEXT35, _("Cells to start"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT35"));
    FlexGridSizer20->Add(StaticText35, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Life1_Count = new wxSlider(Panel1_Life, ID_SLIDER_Life1_Count, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Life1_Count"));
    FlexGridSizer20->Add(Slider_Life1_Count, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText37 = new wxStaticText(Panel1_Life, ID_STATICTEXT37, _("Seed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT37"));
    FlexGridSizer20->Add(StaticText37, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Life1_Seed = new wxSlider(Panel1_Life, ID_SLIDER_Life1_Seed, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Life1_Seed"));
    FlexGridSizer20->Add(Slider_Life1_Seed, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel1_Life->SetSizer(FlexGridSizer20);
    FlexGridSizer20->Fit(Panel1_Life);
    FlexGridSizer20->SetSizeHints(Panel1_Life);
    Panel1_Meteors = new wxPanel(Choicebook1, ID_PANEL18, wxPoint(29,14), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL18"));
    FlexGridSizer22 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText39 = new wxStaticText(Panel1_Meteors, ID_STATICTEXT39, _("Type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT39"));
    FlexGridSizer22->Add(StaticText39, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Choice_Meteors1_Type = new wxChoice(Panel1_Meteors, ID_CHOICE_Meteors1_Type, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_Meteors1_Type"));
    Choice_Meteors1_Type->Append(_("Rainbow"));
    Choice_Meteors1_Type->Append(_("Range"));
    Choice_Meteors1_Type->SetSelection( Choice_Meteors1_Type->Append(_("Palette")) );
    FlexGridSizer22->Add(Choice_Meteors1_Type, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText41 = new wxStaticText(Panel1_Meteors, ID_STATICTEXT41, _("Count"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT41"));
    FlexGridSizer22->Add(StaticText41, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Meteors1_Count = new wxSlider(Panel1_Meteors, ID_SLIDER_Meteors1_Count, 10, 1, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Meteors1_Count"));
    FlexGridSizer22->Add(Slider_Meteors1_Count, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText43 = new wxStaticText(Panel1_Meteors, ID_STATICTEXT43, _("Trail Length"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT43"));
    FlexGridSizer22->Add(StaticText43, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Meteors1_Length = new wxSlider(Panel1_Meteors, ID_SLIDER_Meteors1_Length, 25, 1, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Meteors1_Length"));
    FlexGridSizer22->Add(Slider_Meteors1_Length, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel1_Meteors->SetSizer(FlexGridSizer22);
    FlexGridSizer22->Fit(Panel1_Meteors);
    FlexGridSizer22->SetSizeHints(Panel1_Meteors);
    Panel1_Pictures = new wxPanel(Choicebook1, ID_PANEL20, wxPoint(18,7), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL20"));
    FlexGridSizer24 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer24->AddGrowableCol(1);
    Button_Pictures1_Filename = new wxButton(Panel1_Pictures, ID_BUTTON42, _("File name"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON42"));
    Button_Pictures1_Filename->SetBackgroundColour(wxColour(224,224,224));
    FlexGridSizer24->Add(Button_Pictures1_Filename, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    TextCtrl_Pictures1_Filename = new wxTextCtrl(Panel1_Pictures, ID_TEXTCTRL_Pictures1_Filename, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_Pictures1_Filename"));
    FlexGridSizer24->Add(TextCtrl_Pictures1_Filename, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText46 = new wxStaticText(Panel1_Pictures, ID_STATICTEXT46, _("Direction"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT46"));
    FlexGridSizer24->Add(StaticText46, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Choice_Pictures1_Direction = new wxChoice(Panel1_Pictures, ID_CHOICE_Pictures1_Direction, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_Pictures1_Direction"));
    Choice_Pictures1_Direction->SetSelection( Choice_Pictures1_Direction->Append(_("left")) );
    Choice_Pictures1_Direction->Append(_("right"));
    Choice_Pictures1_Direction->Append(_("up"));
    Choice_Pictures1_Direction->Append(_("down"));
    Choice_Pictures1_Direction->Append(_("none"));
    FlexGridSizer24->Add(Choice_Pictures1_Direction, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel1_Pictures->SetSizer(FlexGridSizer24);
    FlexGridSizer24->Fit(Panel1_Pictures);
    FlexGridSizer24->SetSizeHints(Panel1_Pictures);
    Panel1_Snowflakes = new wxPanel(Choicebook1, ID_PANEL22, wxPoint(17,17), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL22"));
    FlexGridSizer26 = new wxFlexGridSizer(0, 2, 0, 0);
    Panel1_Snowflakes->SetSizer(FlexGridSizer26);
    FlexGridSizer26->Fit(Panel1_Snowflakes);
    FlexGridSizer26->SetSizeHints(Panel1_Snowflakes);
    Panel1_Snowstorm = new wxPanel(Choicebook1, ID_PANEL24, wxPoint(10,13), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL24"));
    FlexGridSizer28 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText45 = new wxStaticText(Panel1_Snowstorm, ID_STATICTEXT45, _("Max Snowflakes"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT45"));
    FlexGridSizer28->Add(StaticText45, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Snowstorm1_Count = new wxSlider(Panel1_Snowstorm, ID_SLIDER_Snowstorm1_Count, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Snowstorm1_Count"));
    FlexGridSizer28->Add(Slider_Snowstorm1_Count, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText51 = new wxStaticText(Panel1_Snowstorm, ID_STATICTEXT51, _("Trail Length"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT51"));
    FlexGridSizer28->Add(StaticText51, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Snowstorm1_Length = new wxSlider(Panel1_Snowstorm, ID_SLIDER_Snowstorm1_Length, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Snowstorm1_Length"));
    FlexGridSizer28->Add(Slider_Snowstorm1_Length, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel1_Snowstorm->SetSizer(FlexGridSizer28);
    FlexGridSizer28->Fit(Panel1_Snowstorm);
    FlexGridSizer28->SetSizeHints(Panel1_Snowstorm);
    Panel1_Spirals = new wxPanel(Choicebook1, ID_PANEL26, wxPoint(16,13), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL26"));
    FlexGridSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText9 = new wxStaticText(Panel1_Spirals, ID_STATICTEXT9, _("# of Spirals"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    FlexGridSizer4->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Slider_Spirals1_Count = new wxSlider(Panel1_Spirals, ID_SLIDER_Spirals1_Count, 2, 1, 9, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Spirals1_Count"));
    FlexGridSizer4->Add(Slider_Spirals1_Count, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText10 = new wxStaticText(Panel1_Spirals, ID_STATICTEXT10, _("Rotations"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    FlexGridSizer4->Add(StaticText10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Slider_Spirals1_Rotation = new wxSlider(Panel1_Spirals, ID_SLIDER_Spirals1_Rotation, 20, -50, 50, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Spirals1_Rotation"));
    FlexGridSizer4->Add(Slider_Spirals1_Rotation, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText11 = new wxStaticText(Panel1_Spirals, ID_STATICTEXT11, _("Thickness"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    FlexGridSizer4->Add(StaticText11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Slider_Spirals1_Thickness = new wxSlider(Panel1_Spirals, ID_SLIDER_Spirals1_Thickness, 50, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Spirals1_Thickness"));
    FlexGridSizer4->Add(Slider_Spirals1_Thickness, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText19 = new wxStaticText(Panel1_Spirals, ID_STATICTEXT24, _("Direction"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
    FlexGridSizer4->Add(StaticText19, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Slider_Spirals1_Direction = new wxSlider(Panel1_Spirals, ID_SLIDER_Spirals1_Direction, 1, -1, 1, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Spirals1_Direction"));
    FlexGridSizer4->Add(Slider_Spirals1_Direction, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_Spirals1_Blend = new wxCheckBox(Panel1_Spirals, ID_CHECKBOX_Spirals1_Blend, _("Blend"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Spirals1_Blend"));
    CheckBox_Spirals1_Blend->SetValue(false);
    FlexGridSizer4->Add(CheckBox_Spirals1_Blend, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    CheckBox_Spirals1_3D = new wxCheckBox(Panel1_Spirals, ID_CHECKBOX_Spirals1_3D, _("3D"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Spirals1_3D"));
    CheckBox_Spirals1_3D->SetValue(false);
    FlexGridSizer4->Add(CheckBox_Spirals1_3D, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel1_Spirals->SetSizer(FlexGridSizer4);
    FlexGridSizer4->Fit(Panel1_Spirals);
    FlexGridSizer4->SetSizeHints(Panel1_Spirals);
    Panel1_Text = new wxPanel(Choicebook1, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
    FlexGridSizer30 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer30->AddGrowableCol(1);
    StaticText53 = new wxStaticText(Panel1_Text, ID_STATICTEXT53, _("Line 1"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT53"));
    FlexGridSizer30->Add(StaticText53, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    TextCtrl_Text1_Line1 = new wxTextCtrl(Panel1_Text, ID_TEXTCTRL_Text1_Line1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_Text1_Line1"));
    TextCtrl_Text1_Line1->SetMaxLength(32);
    FlexGridSizer30->Add(TextCtrl_Text1_Line1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText54 = new wxStaticText(Panel1_Text, ID_STATICTEXT54, _("Line 2"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT54"));
    FlexGridSizer30->Add(StaticText54, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    TextCtrl_Text1_Line2 = new wxTextCtrl(Panel1_Text, ID_TEXTCTRL_Text1_Line2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_Text1_Line2"));
    TextCtrl_Text1_Line2->SetMaxLength(32);
    FlexGridSizer30->Add(TextCtrl_Text1_Line2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText57 = new wxStaticText(Panel1_Text, ID_STATICTEXT57, _("Top of Text"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT57"));
    FlexGridSizer30->Add(StaticText57, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Text1_Top = new wxSlider(Panel1_Text, ID_SLIDER_Text1_Top, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Text1_Top"));
    FlexGridSizer30->Add(Slider_Text1_Top, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel1_Text->SetSizer(FlexGridSizer30);
    FlexGridSizer30->Fit(Panel1_Text);
    FlexGridSizer30->SetSizeHints(Panel1_Text);
    Choicebook1->AddPage(Panel1_None, _("None"), false);
    Choicebook1->AddPage(Panel1_Bars, _("Bars"), false);
    Choicebook1->AddPage(Panel1_Butterfly, _("Butterfly"), false);
    Choicebook1->AddPage(Panel1_ColorWash, _("Color Wash"), false);
    Choicebook1->AddPage(Panel1_Fire, _("Fire"), false);
    Choicebook1->AddPage(Panel1_Garlands, _("Garlands"), false);
    Choicebook1->AddPage(Panel1_Life, _("Life"), false);
    Choicebook1->AddPage(Panel1_Meteors, _("Meteors"), false);
    Choicebook1->AddPage(Panel1_Pictures, _("Pictures"), false);
    Choicebook1->AddPage(Panel1_Snowflakes, _("Snowflakes"), false);
    Choicebook1->AddPage(Panel1_Snowstorm, _("Snowstorm"), false);
    Choicebook1->AddPage(Panel1_Spirals, _("Spirals"), false);
    Choicebook1->AddPage(Panel1_Text, _("Text"), false);
    FlexGridSizer7->Add(Choicebook1, 1, wxTOP|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer32 = new wxFlexGridSizer(0, 1, 0, 0);
    Button_Palette1 = new wxButton(Panel1, ID_BUTTON_Palette1, _("Palette"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_Palette1"));
    Button_Palette1->SetBackgroundColour(wxColour(224,224,224));
    FlexGridSizer32->Add(Button_Palette1, 1, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer_Palette1 = new wxFlexGridSizer(0, 2, 0, 0);
    CheckBox_Palette1_1 = new wxCheckBox(Panel1, ID_CHECKBOX_Palette1_1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Palette1_1"));
    CheckBox_Palette1_1->SetValue(true);
    FlexGridSizer_Palette1->Add(CheckBox_Palette1_1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_Palette1_1 = new wxButton(Panel1, ID_BUTTON_Palette1_1, _("1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_Palette1_1"));
    Button_Palette1_1->SetMinSize(wxSize(30,20));
    Button_Palette1_1->SetBackgroundColour(wxColour(255,0,0));
    FlexGridSizer_Palette1->Add(Button_Palette1_1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    CheckBox_Palette1_2 = new wxCheckBox(Panel1, ID_CHECKBOX_Palette1_2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Palette1_2"));
    CheckBox_Palette1_2->SetValue(true);
    FlexGridSizer_Palette1->Add(CheckBox_Palette1_2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_Palette1_2 = new wxButton(Panel1, ID_BUTTON_Palette1_2, _("2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_Palette1_2"));
    Button_Palette1_2->SetMinSize(wxSize(30,20));
    Button_Palette1_2->SetBackgroundColour(wxColour(0,255,0));
    FlexGridSizer_Palette1->Add(Button_Palette1_2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    CheckBox_Palette1_3 = new wxCheckBox(Panel1, ID_CHECKBOX_Palette1_3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Palette1_3"));
    CheckBox_Palette1_3->SetValue(false);
    FlexGridSizer_Palette1->Add(CheckBox_Palette1_3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_Palette1_3 = new wxButton(Panel1, ID_BUTTON_Palette1_3, _("3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_Palette1_3"));
    Button_Palette1_3->SetMinSize(wxSize(30,20));
    Button_Palette1_3->SetBackgroundColour(wxColour(0,0,255));
    FlexGridSizer_Palette1->Add(Button_Palette1_3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    CheckBox_Palette1_4 = new wxCheckBox(Panel1, ID_CHECKBOX_Palette1_4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Palette1_4"));
    CheckBox_Palette1_4->SetValue(false);
    FlexGridSizer_Palette1->Add(CheckBox_Palette1_4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_Palette1_4 = new wxButton(Panel1, ID_BUTTON_Palette1_4, _("4"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_Palette1_4"));
    Button_Palette1_4->SetMinSize(wxSize(30,20));
    Button_Palette1_4->SetBackgroundColour(wxColour(255,255,0));
    FlexGridSizer_Palette1->Add(Button_Palette1_4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    CheckBox_Palette1_5 = new wxCheckBox(Panel1, ID_CHECKBOX_Palette1_5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Palette1_5"));
    CheckBox_Palette1_5->SetValue(false);
    FlexGridSizer_Palette1->Add(CheckBox_Palette1_5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_Palette1_5 = new wxButton(Panel1, ID_BUTTON_Palette1_5, _("5"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_Palette1_5"));
    Button_Palette1_5->SetMinSize(wxSize(30,20));
    Button_Palette1_5->SetBackgroundColour(wxColour(255,255,255));
    FlexGridSizer_Palette1->Add(Button_Palette1_5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    CheckBox_Palette1_6 = new wxCheckBox(Panel1, ID_CHECKBOX_Palette1_6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Palette1_6"));
    CheckBox_Palette1_6->SetValue(false);
    FlexGridSizer_Palette1->Add(CheckBox_Palette1_6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_Palette1_6 = new wxButton(Panel1, ID_BUTTON_Palette1_6, _("6"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_Palette1_6"));
    Button_Palette1_6->SetMinSize(wxSize(30,20));
    Button_Palette1_6->SetBackgroundColour(wxColour(0,0,0));
    FlexGridSizer_Palette1->Add(Button_Palette1_6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    FlexGridSizer32->Add(FlexGridSizer_Palette1, 1, wxTOP|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer7->Add(FlexGridSizer32, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer34 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticText59 = new wxStaticText(Panel1, ID_STATICTEXT61, _("Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT61"));
    FlexGridSizer34->Add(StaticText59, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Slider_Speed1 = new wxSlider(Panel1, ID_SLIDER_Speed1, 10, 1, 20, wxDefaultPosition, wxSize(30,150), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER_Speed1"));
    FlexGridSizer34->Add(Slider_Speed1, 1, wxTOP|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer7->Add(FlexGridSizer34, 1, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    StaticBoxSizer1->Add(FlexGridSizer7, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(StaticBoxSizer1, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, Panel1, _("Effect 2"));
    FlexGridSizer8 = new wxFlexGridSizer(0, 3, 0, 0);
    Choicebook2 = new wxChoicebook(Panel1, ID_CHOICEBOOK2, wxDefaultPosition, wxDefaultSize, 0, _T("ID_CHOICEBOOK2"));
    Panel2_None = new wxPanel(Choicebook2, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    Panel2_Bars = new wxPanel(Choicebook2, ID_PANEL9, wxPoint(1,9), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL9"));
    FlexGridSizer13 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText18 = new wxStaticText(Panel2_Bars, ID_STATICTEXT18, _("# of Bars"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    FlexGridSizer13->Add(StaticText18, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Bars2_BarCount = new wxSlider(Panel2_Bars, ID_SLIDER_Bars2_BarCount, 1, 1, 10, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Bars2_BarCount"));
    FlexGridSizer13->Add(Slider_Bars2_BarCount, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText22 = new wxStaticText(Panel2_Bars, ID_STATICTEXT22, _("Direction"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
    FlexGridSizer13->Add(StaticText22, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Choice_Bars2_Direction = new wxChoice(Panel2_Bars, ID_CHOICE_Bars2_Direction, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_Bars2_Direction"));
    Choice_Bars2_Direction->SetSelection( Choice_Bars2_Direction->Append(_("up")) );
    Choice_Bars2_Direction->Append(_("down"));
    Choice_Bars2_Direction->Append(_("expand"));
    Choice_Bars2_Direction->Append(_("compress"));
    FlexGridSizer13->Add(Choice_Bars2_Direction, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    CheckBox_Bars2_Highlight = new wxCheckBox(Panel2_Bars, ID_CHECKBOX_Bars2_Highlight, _("Highlight"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Bars2_Highlight"));
    CheckBox_Bars2_Highlight->SetValue(false);
    FlexGridSizer13->Add(CheckBox_Bars2_Highlight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    CheckBox_Bars2_3D = new wxCheckBox(Panel2_Bars, ID_CHECKBOX_Bars2_3D, _("3D"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Bars2_3D"));
    CheckBox_Bars2_3D->SetValue(false);
    FlexGridSizer13->Add(CheckBox_Bars2_3D, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel2_Bars->SetSizer(FlexGridSizer13);
    FlexGridSizer13->Fit(Panel2_Bars);
    FlexGridSizer13->SetSizeHints(Panel2_Bars);
    Panel2_Butterfly = new wxPanel(Choicebook2, ID_PANEL11, wxPoint(71,18), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL11"));
    FlexGridSizer15 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText16 = new wxStaticText(Panel2_Butterfly, ID_STATICTEXT20, _("Colors"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
    FlexGridSizer15->Add(StaticText16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Choice_Butterfly2_Colors = new wxChoice(Panel2_Butterfly, ID_CHOICE3, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    Choice_Butterfly2_Colors->SetSelection( Choice_Butterfly2_Colors->Append(_("Rainbow")) );
    Choice_Butterfly2_Colors->Append(_("Palette"));
    FlexGridSizer15->Add(Choice_Butterfly2_Colors, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText27 = new wxStaticText(Panel2_Butterfly, ID_STATICTEXT27, _("Style"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
    FlexGridSizer15->Add(StaticText27, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Butterfly2_Style = new wxSlider(Panel2_Butterfly, ID_SLIDER_Butterfly2_Style, 1, 1, 3, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Butterfly2_Style"));
    FlexGridSizer15->Add(Slider_Butterfly2_Style, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText29 = new wxStaticText(Panel2_Butterfly, ID_STATICTEXT29, _("Bkgrd Chunks"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
    FlexGridSizer15->Add(StaticText29, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Butterfly2_Chunks = new wxSlider(Panel2_Butterfly, ID_SLIDER_Butterfly2_Chunks, 1, 1, 10, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Butterfly2_Chunks"));
    FlexGridSizer15->Add(Slider_Butterfly2_Chunks, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText30 = new wxStaticText(Panel2_Butterfly, ID_STATICTEXT30, _("Bkgrd Skip"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT30"));
    FlexGridSizer15->Add(StaticText30, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Butterfly2_Skip = new wxSlider(Panel2_Butterfly, ID_SLIDER_Butterfly2_Skip, 2, 2, 10, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Butterfly2_Skip"));
    FlexGridSizer15->Add(Slider_Butterfly2_Skip, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel2_Butterfly->SetSizer(FlexGridSizer15);
    FlexGridSizer15->Fit(Panel2_Butterfly);
    FlexGridSizer15->SetSizeHints(Panel2_Butterfly);
    Panel2_ColorWash = new wxPanel(Choicebook2, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
    FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText7 = new wxStaticText(Panel2_ColorWash, ID_STATICTEXT12, _("Horizontal"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    FlexGridSizer3->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_ColorWash2_HFade = new wxCheckBox(Panel2_ColorWash, ID_CHECKBOX_ColorWash2_HFade, _("Fade"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_ColorWash2_HFade"));
    CheckBox_ColorWash2_HFade->SetValue(false);
    FlexGridSizer3->Add(CheckBox_ColorWash2_HFade, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText8 = new wxStaticText(Panel2_ColorWash, ID_STATICTEXT16, _("Vertical"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    FlexGridSizer3->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_ColorWash2_VFade = new wxCheckBox(Panel2_ColorWash, ID_CHECKBOX_ColorWash2_VFade, _("Fade"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_ColorWash2_VFade"));
    CheckBox_ColorWash2_VFade->SetValue(false);
    FlexGridSizer3->Add(CheckBox_ColorWash2_VFade, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel2_ColorWash->SetSizer(FlexGridSizer3);
    FlexGridSizer3->Fit(Panel2_ColorWash);
    FlexGridSizer3->SetSizeHints(Panel2_ColorWash);
    Panel2_Fire = new wxPanel(Choicebook2, ID_PANEL13, wxPoint(13,7), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL13"));
    FlexGridSizer17 = new wxFlexGridSizer(0, 2, 0, 0);
    Panel2_Fire->SetSizer(FlexGridSizer17);
    FlexGridSizer17->Fit(Panel2_Fire);
    FlexGridSizer17->SetSizeHints(Panel2_Fire);
    Panel2_Garlands = new wxPanel(Choicebook2, ID_PANEL15, wxPoint(6,16), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL15"));
    FlexGridSizer19 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText33 = new wxStaticText(Panel2_Garlands, ID_STATICTEXT33, _("Garland Type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT33"));
    FlexGridSizer19->Add(StaticText33, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Garlands2_Type = new wxSlider(Panel2_Garlands, ID_SLIDER_Garlands2_Type, 0, 0, 4, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Garlands2_Type"));
    FlexGridSizer19->Add(Slider_Garlands2_Type, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText34 = new wxStaticText(Panel2_Garlands, ID_STATICTEXT34, _("Spacing"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT34"));
    FlexGridSizer19->Add(StaticText34, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Garlands2_Spacing = new wxSlider(Panel2_Garlands, ID_SLIDER_Garlands2_Spacing, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Garlands2_Spacing"));
    FlexGridSizer19->Add(Slider_Garlands2_Spacing, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel2_Garlands->SetSizer(FlexGridSizer19);
    FlexGridSizer19->Fit(Panel2_Garlands);
    FlexGridSizer19->SetSizeHints(Panel2_Garlands);
    Panel2_Life = new wxPanel(Choicebook2, ID_PANEL17, wxPoint(21,11), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL17"));
    FlexGridSizer21 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText36 = new wxStaticText(Panel2_Life, ID_STATICTEXT36, _("Cells to start"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT36"));
    FlexGridSizer21->Add(StaticText36, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Life2_Count = new wxSlider(Panel2_Life, ID_SLIDER_Life2_Count, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Life2_Count"));
    FlexGridSizer21->Add(Slider_Life2_Count, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText38 = new wxStaticText(Panel2_Life, ID_STATICTEXT38, _("Seed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT38"));
    FlexGridSizer21->Add(StaticText38, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Life2_Seed = new wxSlider(Panel2_Life, ID_SLIDER_Life2_Seed, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Life2_Seed"));
    FlexGridSizer21->Add(Slider_Life2_Seed, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel2_Life->SetSizer(FlexGridSizer21);
    FlexGridSizer21->Fit(Panel2_Life);
    FlexGridSizer21->SetSizeHints(Panel2_Life);
    Panel2_Meteors = new wxPanel(Choicebook2, ID_PANEL19, wxPoint(3,14), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL19"));
    FlexGridSizer23 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText40 = new wxStaticText(Panel2_Meteors, ID_STATICTEXT40, _("Type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT40"));
    FlexGridSizer23->Add(StaticText40, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Choice_Meteors2_Type = new wxChoice(Panel2_Meteors, ID_CHOICE_Meteors2_Type, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_Meteors2_Type"));
    Choice_Meteors2_Type->Append(_("Rainbow"));
    Choice_Meteors2_Type->Append(_("Range"));
    Choice_Meteors2_Type->SetSelection( Choice_Meteors2_Type->Append(_("Palette")) );
    FlexGridSizer23->Add(Choice_Meteors2_Type, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText42 = new wxStaticText(Panel2_Meteors, ID_STATICTEXT42, _("Count"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT42"));
    FlexGridSizer23->Add(StaticText42, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Meteors2_Count = new wxSlider(Panel2_Meteors, ID_SLIDER_Meteors2_Count, 10, 1, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Meteors2_Count"));
    FlexGridSizer23->Add(Slider_Meteors2_Count, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText44 = new wxStaticText(Panel2_Meteors, ID_STATICTEXT44, _("Trail Length"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT44"));
    FlexGridSizer23->Add(StaticText44, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Meteors2_Length = new wxSlider(Panel2_Meteors, ID_SLIDER_Meteors2_Length, 25, 1, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Meteors2_Length"));
    FlexGridSizer23->Add(Slider_Meteors2_Length, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel2_Meteors->SetSizer(FlexGridSizer23);
    FlexGridSizer23->Fit(Panel2_Meteors);
    FlexGridSizer23->SetSizeHints(Panel2_Meteors);
    Panel2_Pictures = new wxPanel(Choicebook2, ID_PANEL21, wxPoint(3,25), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL21"));
    FlexGridSizer25 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer25->AddGrowableCol(1);
    Button_Pictures2_Filename = new wxButton(Panel2_Pictures, ID_BUTTON47, _("File name"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON47"));
    Button_Pictures2_Filename->SetBackgroundColour(wxColour(224,224,224));
    FlexGridSizer25->Add(Button_Pictures2_Filename, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    TextCtrl_Pictures2_Filename = new wxTextCtrl(Panel2_Pictures, ID_TEXTCTRL_Pictures2_Filename, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_Pictures2_Filename"));
    FlexGridSizer25->Add(TextCtrl_Pictures2_Filename, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText47 = new wxStaticText(Panel2_Pictures, ID_STATICTEXT47, _("Direction"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT47"));
    FlexGridSizer25->Add(StaticText47, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Choice_Pictures2_Direction = new wxChoice(Panel2_Pictures, ID_CHOICE_Pictures2_Direction, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_Pictures2_Direction"));
    Choice_Pictures2_Direction->SetSelection( Choice_Pictures2_Direction->Append(_("left")) );
    Choice_Pictures2_Direction->Append(_("right"));
    Choice_Pictures2_Direction->Append(_("up"));
    Choice_Pictures2_Direction->Append(_("down"));
    Choice_Pictures2_Direction->Append(_("none"));
    FlexGridSizer25->Add(Choice_Pictures2_Direction, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel2_Pictures->SetSizer(FlexGridSizer25);
    FlexGridSizer25->Fit(Panel2_Pictures);
    FlexGridSizer25->SetSizeHints(Panel2_Pictures);
    Panel2_Snowflakes = new wxPanel(Choicebook2, ID_PANEL23, wxPoint(10,21), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL23"));
    FlexGridSizer27 = new wxFlexGridSizer(0, 2, 0, 0);
    Panel2_Snowflakes->SetSizer(FlexGridSizer27);
    FlexGridSizer27->Fit(Panel2_Snowflakes);
    FlexGridSizer27->SetSizeHints(Panel2_Snowflakes);
    Panel2_Snowstorm = new wxPanel(Choicebook2, ID_PANEL25, wxPoint(21,15), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL25"));
    FlexGridSizer29 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText50 = new wxStaticText(Panel2_Snowstorm, ID_STATICTEXT50, _("Max Snowflakes"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT50"));
    FlexGridSizer29->Add(StaticText50, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Snowstorm2_Count = new wxSlider(Panel2_Snowstorm, ID_SLIDER_Snowstorm2_Count, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Snowstorm2_Count"));
    FlexGridSizer29->Add(Slider_Snowstorm2_Count, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText52 = new wxStaticText(Panel2_Snowstorm, ID_STATICTEXT52, _("Trail Length"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT52"));
    FlexGridSizer29->Add(StaticText52, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Snowstorm2_Length = new wxSlider(Panel2_Snowstorm, ID_SLIDER_Snowstorm2_Length, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Snowstorm2_Length"));
    FlexGridSizer29->Add(Slider_Snowstorm2_Length, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel2_Snowstorm->SetSizer(FlexGridSizer29);
    FlexGridSizer29->Fit(Panel2_Snowstorm);
    FlexGridSizer29->SetSizeHints(Panel2_Snowstorm);
    Panel2_Spirals = new wxPanel(Choicebook2, ID_PANEL4, wxPoint(6,18), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    FlexGridSizer10 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText13 = new wxStaticText(Panel2_Spirals, ID_STATICTEXT13, _("# of Spirals"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    FlexGridSizer10->Add(StaticText13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Spirals2_Count = new wxSlider(Panel2_Spirals, ID_SLIDER_Spirals2_Count, 2, 1, 9, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Spirals2_Count"));
    FlexGridSizer10->Add(Slider_Spirals2_Count, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText14 = new wxStaticText(Panel2_Spirals, ID_STATICTEXT14, _("Rotations"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    FlexGridSizer10->Add(StaticText14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Spirals2_Rotation = new wxSlider(Panel2_Spirals, ID_SLIDER_Spirals2_Rotation, 20, -50, 50, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Spirals2_Rotation"));
    FlexGridSizer10->Add(Slider_Spirals2_Rotation, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText15 = new wxStaticText(Panel2_Spirals, ID_STATICTEXT15, _("Thickness"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    FlexGridSizer10->Add(StaticText15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Spirals2_Thickness = new wxSlider(Panel2_Spirals, ID_SLIDER_Spirals2_Thickness, 50, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Spirals2_Thickness"));
    FlexGridSizer10->Add(Slider_Spirals2_Thickness, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText20 = new wxStaticText(Panel2_Spirals, ID_STATICTEXT28, _("Direction"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
    FlexGridSizer10->Add(StaticText20, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Slider_Spirals2_Direction = new wxSlider(Panel2_Spirals, ID_SLIDER_Spirals2_Direction, 1, -1, 1, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Spirals2_Direction"));
    FlexGridSizer10->Add(Slider_Spirals2_Direction, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox_Spirals2_Blend = new wxCheckBox(Panel2_Spirals, ID_CHECKBOX_Spirals2_Blend, _("Blend"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Spirals2_Blend"));
    CheckBox_Spirals2_Blend->SetValue(false);
    FlexGridSizer10->Add(CheckBox_Spirals2_Blend, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    CheckBox_Spirals2_3D = new wxCheckBox(Panel2_Spirals, ID_CHECKBOX_Spirals2_3D, _("3D"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Spirals2_3D"));
    CheckBox_Spirals2_3D->SetValue(false);
    FlexGridSizer10->Add(CheckBox_Spirals2_3D, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel2_Spirals->SetSizer(FlexGridSizer10);
    FlexGridSizer10->Fit(Panel2_Spirals);
    FlexGridSizer10->SetSizeHints(Panel2_Spirals);
    Panel2_Text = new wxPanel(Choicebook2, ID_PANEL27, wxPoint(31,4), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL27"));
    FlexGridSizer31 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer31->AddGrowableCol(1);
    StaticText55 = new wxStaticText(Panel2_Text, ID_STATICTEXT55, _("Line 1"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT55"));
    FlexGridSizer31->Add(StaticText55, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    TextCtrl_Text2_Line1 = new wxTextCtrl(Panel2_Text, ID_TEXTCTRL_Text2_Line1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_Text2_Line1"));
    TextCtrl_Text2_Line1->SetMaxLength(32);
    FlexGridSizer31->Add(TextCtrl_Text2_Line1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText56 = new wxStaticText(Panel2_Text, ID_STATICTEXT56, _("Line 2"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT56"));
    FlexGridSizer31->Add(StaticText56, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    TextCtrl_Text2_Line2 = new wxTextCtrl(Panel2_Text, ID_TEXTCTRL_Text2_Line2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_Text2_Line2"));
    TextCtrl_Text2_Line2->SetMaxLength(32);
    FlexGridSizer31->Add(TextCtrl_Text2_Line2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText58 = new wxStaticText(Panel2_Text, ID_STATICTEXT58, _("Top of Text"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT58"));
    FlexGridSizer31->Add(StaticText58, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Slider_Text2_Top = new wxSlider(Panel2_Text, ID_SLIDER_Text2_Top, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER_Text2_Top"));
    FlexGridSizer31->Add(Slider_Text2_Top, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel2_Text->SetSizer(FlexGridSizer31);
    FlexGridSizer31->Fit(Panel2_Text);
    FlexGridSizer31->SetSizeHints(Panel2_Text);
    Choicebook2->AddPage(Panel2_None, _("None"), false);
    Choicebook2->AddPage(Panel2_Bars, _("Bars"), false);
    Choicebook2->AddPage(Panel2_Butterfly, _("Butterfly"), false);
    Choicebook2->AddPage(Panel2_ColorWash, _("Color Wash"), false);
    Choicebook2->AddPage(Panel2_Fire, _("Fire"), false);
    Choicebook2->AddPage(Panel2_Garlands, _("Garlands"), false);
    Choicebook2->AddPage(Panel2_Life, _("Life"), false);
    Choicebook2->AddPage(Panel2_Meteors, _("Meteors"), false);
    Choicebook2->AddPage(Panel2_Pictures, _("Pictures"), false);
    Choicebook2->AddPage(Panel2_Snowflakes, _("Snowflakes"), false);
    Choicebook2->AddPage(Panel2_Snowstorm, _("Snowstorm"), false);
    Choicebook2->AddPage(Panel2_Spirals, _("Spirals"), false);
    Choicebook2->AddPage(Panel2_Text, _("Text"), false);
    FlexGridSizer8->Add(Choicebook2, 1, wxTOP|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer35 = new wxFlexGridSizer(0, 1, 0, 0);
    Button_Palette2 = new wxButton(Panel1, ID_BUTTON_Palette2, _("Palette"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_Palette2"));
    Button_Palette2->SetBackgroundColour(wxColour(224,224,224));
    FlexGridSizer35->Add(Button_Palette2, 1, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer_Palette2 = new wxFlexGridSizer(0, 2, 0, 0);
    CheckBox_Palette2_1 = new wxCheckBox(Panel1, ID_CHECKBOX_Palette2_1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Palette2_1"));
    CheckBox_Palette2_1->SetValue(true);
    FlexGridSizer_Palette2->Add(CheckBox_Palette2_1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_Palette2_1 = new wxButton(Panel1, ID_BUTTON_Palette2_1, _("1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_Palette2_1"));
    Button_Palette2_1->SetMinSize(wxSize(30,20));
    Button_Palette2_1->SetBackgroundColour(wxColour(255,0,0));
    FlexGridSizer_Palette2->Add(Button_Palette2_1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    CheckBox_Palette2_2 = new wxCheckBox(Panel1, ID_CHECKBOX_Palette2_2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Palette2_2"));
    CheckBox_Palette2_2->SetValue(true);
    FlexGridSizer_Palette2->Add(CheckBox_Palette2_2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_Palette2_2 = new wxButton(Panel1, ID_BUTTON_Palette2_2, _("2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_Palette2_2"));
    Button_Palette2_2->SetMinSize(wxSize(30,20));
    Button_Palette2_2->SetBackgroundColour(wxColour(0,255,0));
    FlexGridSizer_Palette2->Add(Button_Palette2_2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    CheckBox_Palette2_3 = new wxCheckBox(Panel1, ID_CHECKBOX_Palette2_3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Palette2_3"));
    CheckBox_Palette2_3->SetValue(false);
    FlexGridSizer_Palette2->Add(CheckBox_Palette2_3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_Palette2_3 = new wxButton(Panel1, ID_BUTTON_Palette2_3, _("3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_Palette2_3"));
    Button_Palette2_3->SetMinSize(wxSize(30,20));
    Button_Palette2_3->SetBackgroundColour(wxColour(0,0,255));
    FlexGridSizer_Palette2->Add(Button_Palette2_3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    CheckBox_Palette2_4 = new wxCheckBox(Panel1, ID_CHECKBOX_Palette2_4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Palette2_4"));
    CheckBox_Palette2_4->SetValue(false);
    FlexGridSizer_Palette2->Add(CheckBox_Palette2_4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_Palette2_4 = new wxButton(Panel1, ID_BUTTON_Palette2_4, _("4"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_Palette2_4"));
    Button_Palette2_4->SetMinSize(wxSize(30,20));
    Button_Palette2_4->SetBackgroundColour(wxColour(255,255,0));
    FlexGridSizer_Palette2->Add(Button_Palette2_4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    CheckBox_Palette2_5 = new wxCheckBox(Panel1, ID_CHECKBOX_Palette2_5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Palette2_5"));
    CheckBox_Palette2_5->SetValue(false);
    FlexGridSizer_Palette2->Add(CheckBox_Palette2_5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_Palette2_5 = new wxButton(Panel1, ID_BUTTON_Palette2_5, _("5"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_Palette2_5"));
    Button_Palette2_5->SetMinSize(wxSize(30,20));
    Button_Palette2_5->SetBackgroundColour(wxColour(255,255,255));
    FlexGridSizer_Palette2->Add(Button_Palette2_5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    CheckBox_Palette2_6 = new wxCheckBox(Panel1, ID_CHECKBOX_Palette2_6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_Palette2_6"));
    CheckBox_Palette2_6->SetValue(false);
    FlexGridSizer_Palette2->Add(CheckBox_Palette2_6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_Palette2_6 = new wxButton(Panel1, ID_BUTTON_Palette2_6, _("6"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_Palette2_6"));
    Button_Palette2_6->SetMinSize(wxSize(30,20));
    Button_Palette2_6->SetBackgroundColour(wxColour(0,0,0));
    FlexGridSizer_Palette2->Add(Button_Palette2_6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    FlexGridSizer35->Add(FlexGridSizer_Palette2, 1, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer8->Add(FlexGridSizer35, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer36 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT4, _("Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer36->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Slider_Speed2 = new wxSlider(Panel1, ID_SLIDER_Speed2, 10, 1, 20, wxDefaultPosition, wxSize(30,150), wxSL_VERTICAL|wxSL_INVERSE, wxDefaultValidator, _T("ID_SLIDER_Speed2"));
    FlexGridSizer36->Add(Slider_Speed2, 1, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer8->Add(FlexGridSizer36, 1, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    StaticBoxSizer2->Add(FlexGridSizer8, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(StaticBoxSizer2, 1, wxLEFT|wxRIGHT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(Panel1);
    FlexGridSizer1->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    ColourDialog1 = new wxColourDialog(this);
    Timer1.SetOwner(this, ID_TIMER1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_StopClick);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnCheckBox_SendOutputClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_PlaySelectionClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_PlayAllClick);
    Connect(ID_BUTTON58,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_ModelsClick);
    Connect(ID_BUTTON13,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_PlayEffectClick);
    Connect(ID_BUTTON59,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_PresetsClick);
    Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&xRGBFrame::OnChoice_PresetsSelect);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_PresetAddClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_PresetUpdateClick);
    Connect(ID_CHOICE_LayerMethod,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&xRGBFrame::OnChoice_LayerMethodSelect);
    Connect(ID_BUTTON56,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_SaveEffectsClick);
    Connect(ID_CHECKBOX_Palette1_1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnCheckBox_PaletteClick);
    Connect(ID_BUTTON_Palette1_1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_ColorClick);
    Connect(ID_CHECKBOX_Palette1_2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnCheckBox_PaletteClick);
    Connect(ID_BUTTON_Palette1_2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_ColorClick);
    Connect(ID_CHECKBOX_Palette1_3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnCheckBox_PaletteClick);
    Connect(ID_BUTTON_Palette1_3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_ColorClick);
    Connect(ID_CHECKBOX_Palette1_4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnCheckBox_PaletteClick);
    Connect(ID_BUTTON_Palette1_4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_ColorClick);
    Connect(ID_CHECKBOX_Palette1_5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnCheckBox_PaletteClick);
    Connect(ID_BUTTON_Palette1_5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_ColorClick);
    Connect(ID_CHECKBOX_Palette1_6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnCheckBox_PaletteClick);
    Connect(ID_BUTTON_Palette1_6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_ColorClick);
    Connect(ID_CHECKBOX_Palette2_1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnCheckBox_PaletteClick);
    Connect(ID_BUTTON_Palette2_1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_ColorClick);
    Connect(ID_CHECKBOX_Palette2_2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnCheckBox_PaletteClick);
    Connect(ID_BUTTON_Palette2_2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_ColorClick);
    Connect(ID_CHECKBOX_Palette2_3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnCheckBox_PaletteClick);
    Connect(ID_BUTTON_Palette2_3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_ColorClick);
    Connect(ID_CHECKBOX_Palette2_4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnCheckBox_PaletteClick);
    Connect(ID_BUTTON_Palette2_4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_ColorClick);
    Connect(ID_CHECKBOX_Palette2_5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnCheckBox_PaletteClick);
    Connect(ID_BUTTON_Palette2_5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_ColorClick);
    Connect(ID_CHECKBOX_Palette2_6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnCheckBox_PaletteClick);
    Connect(ID_BUTTON_Palette2_6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xRGBFrame::OnButton_ColorClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xRGBFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xRGBFrame::OnAbout);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&xRGBFrame::OnTimer1Trigger);
    //*)


    SetIcon(wxIcon(xlights_xpm));
    UnsavedChanges=false;
    PaletteChanged=true;
    MixTypeChanged=true;
    /*
    ResetTimer(NO_EFFECT);
    if (PortsOK) {
    }
    */

    // Get CurrentDir
    wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));
    if ( !config->Read(_("LastDir"), &CurrentDir) ) {
        wxMessageBox(_("No directory specified"), _("Error"));
        Close();
    }
    HtmlEasyPrint=new wxHtmlEasyPrinting(wxT("xLights Printing"), this);
    LoadEffectsFile();
    PresetsSelect();
    SetPlayMode(play_off);
    buffer.SetWindow(ScrolledWindow1);
    Timer1.Start(XTIMER_INTERVAL, wxTIMER_CONTINUOUS);
}

xRGBFrame::~xRGBFrame()
{
    //(*Destroy(xRGBFrame)
    //*)
}

void xRGBFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void xRGBFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _(XLIGHTS_LICENSE);
    wxString hdg = wxString::Format(_("About xLights %s"),_(XLIGHTS_VERSION));
    wxMessageBox(msg, hdg);
}

void xRGBFrame::OnTimer1Trigger(wxTimerEvent& event)
{
    if (xout) {
        wxTimeSpan ts = wxDateTime::UNow() - starttime;
        long curtime = ts.GetMilliseconds().ToLong();
        xout->TimerStart(curtime);
    }
    switch (play_mode) {
        case play_off:
            break;
        case play_effect:
            TimerEffect();
            break;
        case play_seqpartial:
            TimerSeqPartial();
            break;
        case play_seqall:
            TimerSeqAll();
            break;
    }
    if (xout) {
        xout->TimerEnd();
    }
}

void xRGBFrame::UpdateBufferPalette()
{
    wxColourVector newcolors;

    // effect 1
    if (CheckBox_Palette1_1->IsChecked()) newcolors.push_back(Button_Palette1_1->GetBackgroundColour());
    if (CheckBox_Palette1_2->IsChecked()) newcolors.push_back(Button_Palette1_2->GetBackgroundColour());
    if (CheckBox_Palette1_3->IsChecked()) newcolors.push_back(Button_Palette1_3->GetBackgroundColour());
    if (CheckBox_Palette1_4->IsChecked()) newcolors.push_back(Button_Palette1_4->GetBackgroundColour());
    if (CheckBox_Palette1_5->IsChecked()) newcolors.push_back(Button_Palette1_5->GetBackgroundColour());
    if (CheckBox_Palette1_6->IsChecked()) newcolors.push_back(Button_Palette1_6->GetBackgroundColour());
    buffer.SetPalette(0,newcolors);

    // effect 2
    newcolors.clear();
    if (CheckBox_Palette2_1->IsChecked()) newcolors.push_back(Button_Palette2_1->GetBackgroundColour());
    if (CheckBox_Palette2_2->IsChecked()) newcolors.push_back(Button_Palette2_2->GetBackgroundColour());
    if (CheckBox_Palette2_3->IsChecked()) newcolors.push_back(Button_Palette2_3->GetBackgroundColour());
    if (CheckBox_Palette2_4->IsChecked()) newcolors.push_back(Button_Palette2_4->GetBackgroundColour());
    if (CheckBox_Palette2_5->IsChecked()) newcolors.push_back(Button_Palette2_5->GetBackgroundColour());
    if (CheckBox_Palette2_6->IsChecked()) newcolors.push_back(Button_Palette2_6->GetBackgroundColour());
    buffer.SetPalette(1,newcolors);
}

void xRGBFrame::TimerEffect()
{
    wxString line1,line2,s;
    buffer.Clear();

    // update SparkleFrequency or SparkleDensity if necessary
    int SparkleFrequency=Slider_SparkleFrequency->GetValue();
    int SparkleDensity=Slider_SparkleDensity->GetValue();
    if (SparkleFrequency != LastSparkleFrequency || SparkleDensity != LastSparkleDensity) {
        buffer.SetSparkle(SparkleFrequency,SparkleDensity);
        LastSparkleFrequency=SparkleFrequency;
        LastSparkleDensity=SparkleDensity;
    }

    if (PaletteChanged) {
        UpdateBufferPalette();
        PaletteChanged=false;
    }
    if (MixTypeChanged) {
        s=Choice_LayerMethod->GetStringSelection();
        buffer.SetMixType(s);
        MixTypeChanged=false;
    }


    // render effect 1
    buffer.SetSpeed(Slider_Speed1->GetValue());
    switch (Choicebook1->GetSelection())
    {
        case 0: break;   // none
        case 1:
            buffer.RenderBars(0, Slider_Bars1_BarCount->GetValue(),
                              Choice_Bars1_Direction->GetSelection(),
                              CheckBox_Bars1_Highlight->GetValue(),
                              CheckBox_Bars1_3D->GetValue());
            break;
        case 2:
            buffer.RenderButterfly(0, Choice_Butterfly1_Colors->GetSelection(),
                                   Slider_Butterfly1_Style->GetValue(),
                                   Slider_Butterfly1_Chunks->GetValue(),
                                   Slider_Butterfly1_Skip->GetValue());
            break;
        case 3:
            buffer.RenderColorWash(0,CheckBox_ColorWash1_HFade->GetValue(),
                                   CheckBox_ColorWash1_VFade->GetValue());
            break;
        case 4:
            buffer.RenderFire(0);
            break;
        case 5:
            buffer.RenderGarlands(0,Slider_Garlands1_Type->GetValue(),
                                  Slider_Garlands1_Spacing->GetValue());
            break;
        case 6:
            buffer.RenderLife(0,Slider_Life1_Count->GetValue(),
                              Slider_Life1_Seed->GetValue());
            break;
        case 7:
            buffer.RenderMeteors(0,Choice_Meteors1_Type->GetSelection(),
                                 Slider_Meteors1_Count->GetValue(),
                                 Slider_Meteors1_Length->GetValue());
            break;
        case 8:
            buffer.RenderPictures(0);
            break;
        case 9:
            buffer.RenderSnowflakes(0);
            break;
        case 10:
            buffer.RenderSnowstorm(0,Slider_Snowstorm1_Count->GetValue(),
                                   Slider_Snowstorm1_Length->GetValue());
            break;
        case 11:
            buffer.RenderSpirals(0,Slider_Spirals1_Count->GetValue(),
                                 Slider_Spirals1_Direction->GetValue(),
                                 Slider_Spirals1_Rotation->GetValue(),
                                 Slider_Spirals1_Thickness->GetValue(),
                                 CheckBox_Spirals1_Blend->GetValue(),
                                 CheckBox_Spirals1_3D->GetValue());
            break;
        case 12:
            line1=TextCtrl_Text1_Line1->GetValue();
            line2=TextCtrl_Text1_Line2->GetValue();
            buffer.RenderText(0,Slider_Text1_Top->GetValue(),line1,line2);
            break;
    }

    // render effect 2
    buffer.SetSpeed(Slider_Speed2->GetValue());
    switch (Choicebook2->GetSelection())
    {
        case 0: break;   // none
        case 1:
            buffer.RenderBars(1, Slider_Bars2_BarCount->GetValue(),
                              Choice_Bars2_Direction->GetSelection(),
                              CheckBox_Bars2_Highlight->GetValue(),
                              CheckBox_Bars2_3D->GetValue());
            break;
        case 2:
            buffer.RenderButterfly(1, Choice_Butterfly2_Colors->GetSelection(),
                                   Slider_Butterfly2_Style->GetValue(),
                                   Slider_Butterfly2_Chunks->GetValue(),
                                   Slider_Butterfly2_Skip->GetValue());
            break;
        case 3:
            buffer.RenderColorWash(1,CheckBox_ColorWash2_HFade->GetValue(),
                                   CheckBox_ColorWash2_VFade->GetValue());
            break;
        case 4:
            buffer.RenderFire(1);
            break;
        case 5:
            buffer.RenderGarlands(1,Slider_Garlands2_Type->GetValue(),
                                  Slider_Garlands2_Spacing->GetValue());
            break;
        case 6:
            buffer.RenderLife(1,Slider_Life2_Count->GetValue(),
                              Slider_Life2_Seed->GetValue());
            break;
        case 7:
            buffer.RenderMeteors(1,Choice_Meteors2_Type->GetSelection(),
                                 Slider_Meteors2_Count->GetValue(),
                                 Slider_Meteors2_Length->GetValue());
            break;
        case 8:
            buffer.RenderPictures(1);
            break;
        case 9:
            buffer.RenderSnowflakes(1);
            break;
        case 10:
            buffer.RenderSnowstorm(1,Slider_Snowstorm2_Count->GetValue(),
                                   Slider_Snowstorm2_Length->GetValue());
            break;
        case 11:
            buffer.RenderSpirals(1,Slider_Spirals2_Count->GetValue(),
                                 Slider_Spirals2_Direction->GetValue(),
                                 Slider_Spirals2_Rotation->GetValue(),
                                 Slider_Spirals2_Thickness->GetValue(),
                                 CheckBox_Spirals2_Blend->GetValue(),
                                 CheckBox_Spirals2_3D->GetValue());
            break;
        case 12:
            line1=TextCtrl_Text2_Line1->GetValue();
            line2=TextCtrl_Text2_Line2->GetValue();
            buffer.RenderText(1,Slider_Text2_Top->GetValue(),line1,line2);
            break;
    }
    buffer.DisplayOutput();
    if (CheckBox_SendOutput->IsChecked() && xout) {
        size_t ChannelNum=buffer.StartChannel-1;
        size_t NodeCnt=buffer.GetNodeCount();
        for(size_t i=0; i<NodeCnt; i++) {
            xout->SetIntensity(ChannelNum,buffer.Nodes[i].GetChannel(0));
            ChannelNum++;
            xout->SetIntensity(ChannelNum,buffer.Nodes[i].GetChannel(1));
            ChannelNum++;
            xout->SetIntensity(ChannelNum,buffer.Nodes[i].GetChannel(2));
            ChannelNum++;
        }
    }
}

void xRGBFrame::TimerSeqPartial()
{
}

void xRGBFrame::TimerSeqAll()
{
}

void xRGBFrame::OnCheckBox_SendOutputClick(wxCommandEvent& event)
{
    if (CheckBox_SendOutput->IsChecked() && xout==0) {
        xout = new xOutput();

        if (LoadNetworkFile()) {
            xout->SetMaxIntensity(255);
        } else {
            CheckBox_SendOutput->SetValue(false);
            CheckBox_SendOutput->Enable(false);
        }
    }
}

void xRGBFrame::UpdateEffectsList()
{
    wxString name;
    wxString SelectedStr=Choice_Presets->GetStringSelection();
    Choice_Presets->Clear();
    for(wxXmlNode* e=EffectsNode->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() == wxT("effect")) {
            name=e->GetAttribute(wxT("name"));
            if (!name.IsEmpty()) {
                Choice_Presets->Append(name,e);
            }
        }
    }

    // select a preset if one exists
    if (Choice_Presets->GetCount() > 0) {
        if (SelectedStr.IsEmpty() || !Choice_Presets->SetStringSelection(SelectedStr)) {
            Choice_Presets->SetSelection(0);
        }
    }
}

void xRGBFrame::UpdateModelsList()
{
    wxString name;
    wxString SelectedStr=Choice_Models->GetStringSelection();
    Choice_Models->Clear();
    for(wxXmlNode* e=ModelsNode->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() == wxT("model")) {
            name=e->GetAttribute(wxT("name"));
            if (!name.IsEmpty()) {
                Choice_Models->Append(name,e);
            }
        }
    }

    // select a model if one exists
    if (Choice_Models->GetCount() > 0) {
        if (SelectedStr.IsEmpty() || !Choice_Models->SetStringSelection(SelectedStr)) {
            Choice_Models->SetSelection(0);
        }
    }
}

void xRGBFrame::CreateDefaultEffectsXml()
{
    wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("xrgb") );
    EffectsXml.SetRoot( root );
}

// returns true on success
void xRGBFrame::LoadEffectsFile()
{
    //wxMessageBox(Slider_Meteors1_Type->GetName());
    wxFileName effectsFile;
    effectsFile.AssignDir( CurrentDir );
    effectsFile.SetFullName(_(XLIGHTS_RGBEFFECTS_FILE));
    if (!effectsFile.FileExists()) {
        // file does not exist, so create an empty xml doc
        CreateDefaultEffectsXml();
    } else if (!EffectsXml.Load( effectsFile.GetFullPath() )) {
        wxMessageBox(_("Unable to load RGB effects file"), _("Error"));
        CreateDefaultEffectsXml();
    }
    wxXmlNode* root=EffectsXml.GetRoot();
    if (root->GetName() != wxT("xrgb")) {
        wxMessageBox(_("Invalid RGB effects file. Press Save File button to start a new file."), _("Error"));
        CreateDefaultEffectsXml();
    }
    for(wxXmlNode* e=root->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() == wxT("models")) ModelsNode=e;
        if (e->GetName() == wxT("effects")) EffectsNode=e;
    }
    if (ModelsNode == 0) {
        ModelsNode = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("models") );
        root->AddChild( ModelsNode );
    }
    if (EffectsNode == 0) {
        EffectsNode = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("effects") );
        root->AddChild( EffectsNode );
    }
    UpdateModelsList();
    UpdateEffectsList();
}

// returns true on success
bool xRGBFrame::SaveEffectsFile()
{
    wxFileName effectsFile;
    effectsFile.AssignDir( CurrentDir );
    effectsFile.SetFullName(_(XLIGHTS_RGBEFFECTS_FILE));
    if (!EffectsXml.Save( effectsFile.GetFullPath() )) {
        wxMessageBox(_("Unable to save RGB effects file"), _("Error"));
        return false;
    }
    UnsavedChanges=false;
    return true;
}

bool xRGBFrame::LoadNetworkFile()
{
    long MaxChan;
    bool ok = true;
    wxString tempstr;
    wxXmlDocument doc;
    wxFileName networkFile;
    networkFile.AssignDir( CurrentDir );
    networkFile.SetFullName(_(XLIGHTS_NETWORK_FILE));
    if (!networkFile.FileExists()) {
        wxMessageBox(_("Lighting networks must be defined first"), _("Error"));
        return false;
    }
    if (doc.Load( networkFile.GetFullPath() )) {
        wxXmlNode* e=doc.GetRoot();
        //tempstr=e->GetAttribute(wxT("LorMapping"), wxT("2"));
        //tempstr.ToLong(&LorMapping);
        for( e=doc.GetRoot()->GetChildren(); e!=NULL && ok; e=e->GetNext() ) {
            wxString tagname=e->GetName();
            if (tagname == wxT("network")) {
                wxString tempstr=e->GetAttribute(wxT("MaxChannels"), wxT("0"));
                tempstr.ToLong(&MaxChan);
                wxString NetworkType=e->GetAttribute(wxT("NetworkType"), wxT(""));
                wxString ComPort=e->GetAttribute(wxT("ComPort"), wxT(""));
                wxString BaudRate=e->GetAttribute(wxT("BaudRate"), wxT(""));
                ok = AddNetwork(NetworkType,ComPort,BaudRate,MaxChan);
            }
        }
    } else {
        wxMessageBox(_("Unable to load network definition file"), _("Error"));
        ok = false;
    }
    return ok;
}

bool xRGBFrame::AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels)
{
    int netnum=-1;
    int baud = (BaudRate == _("n/a")) ? 115200 : atoi(BaudRate.mb_str(wxConvUTF8));
    wxString msg = _("Error occurred while connecting to ") + NetworkType+ _(" network on ") + ComPort +
        _("\n\nThings to check:\n1. Are all required cables plugged in?") +
        _("\n2. Is there another program running that is accessing the port (like the LOR Control Panel)? If so, then you must close the other program and then restart xLights.") +
        _("\n3. If this is a USB dongle, are the FTDI Virtual COM Port drivers loaded?\n\n");
    try {
        netnum=xout->addnetwork(NetworkType,MaxChannels,ComPort,baud);
        //TextCtrlLog->AppendText(_("Successfully initialized ") + NetworkType + _(" network on ") + ComPort + _("\n"));
    }
    catch (const char *str) {
        wxString errmsg(str,wxConvUTF8);
        wxMessageBox(msg + errmsg, _("Communication Error"));
        return false;
    }
    catch (char *str) {
        wxString errmsg(str,wxConvUTF8);
        wxMessageBox(msg + errmsg, _("Communication Error"));
        return false;
    }
    return true;
}


void xRGBFrame::OnButton_SaveEffectsClick(wxCommandEvent& event)
{
    SaveEffectsFile();
}

void xRGBFrame::OnButton_PresetAddClick(wxCommandEvent& event)
{
    wxTextEntryDialog dialog(this,_("Enter preset name"),_("Add New Preset"));
    int DlgResult;
    bool ok;
    wxString name;
    do {
        ok=true;
        DlgResult=dialog.ShowModal();
        if (DlgResult == wxID_OK) {
            // validate inputs
            name=dialog.GetValue();
            name.Trim();
            if (name.IsEmpty()) {
                ok=false;
                wxMessageBox(_("A preset name cannot be empty"), _("ERROR"));
            } else if (Choice_Presets->FindString(name) != wxNOT_FOUND) {
                ok=false;
                wxMessageBox(_("That name is already in use"), _("ERROR"));
            }
        }
    } while (DlgResult == wxID_OK && !ok);
    if (DlgResult != wxID_OK) return;

    // update Choice_Presets
    EffectsNode->AddChild(CreateEffectNode(name));
    UpdateEffectsList();
    Choice_Presets->SetStringSelection(name);
}

void xRGBFrame::OnButton_PresetUpdateClick(wxCommandEvent& event)
{
    int NameIdx=Choice_Presets->GetSelection();
    if (NameIdx == wxNOT_FOUND) {
        wxMessageBox(_("No preset name is selected"), _("ERROR"));
    } else {
        // delete old xml entry
        wxXmlNode* OldXml=(wxXmlNode*)Choice_Presets->GetClientData(NameIdx);
        EffectsNode->RemoveChild(OldXml);
        delete OldXml;

        wxString name=Choice_Presets->GetString(NameIdx);
        EffectsNode->AddChild(CreateEffectNode(name));
        UpdateEffectsList();
        Choice_Presets->SetStringSelection(name);
    }
}

wxXmlNode* xRGBFrame::CreateEffectNode(wxString& name)
{
    int PageIdx1=Choicebook1->GetSelection();
    int PageIdx2=Choicebook2->GetSelection();
    wxXmlNode* NewXml=new wxXmlNode(wxXML_ELEMENT_NODE, wxT("effect"));
    NewXml->AddAttribute(wxT("name"), name);
    NewXml->AddAttribute(wxT("ID_CHOICEBOOK1"), Choicebook1->GetPageText(PageIdx1));
    NewXml->AddAttribute(wxT("ID_CHOICEBOOK2"), Choicebook2->GetPageText(PageIdx2));
    NewXml->AddAttribute(wxT("ID_CHOICE_LayerMethod"), Choice_LayerMethod->GetStringSelection());
    NewXml->AddAttribute(wxT("ID_SLIDER_SparkleDensity"), wxString::Format(wxT("%d"),Slider_SparkleDensity->GetValue()));
    NewXml->AddAttribute(wxT("ID_SLIDER_SparkleFrequency"), wxString::Format(wxT("%d"),Slider_SparkleFrequency->GetValue()));
    NewXml->AddAttribute(wxT("ID_SLIDER_Speed1"), wxString::Format(wxT("%d"),Slider_Speed1->GetValue()));
    NewXml->AddAttribute(wxT("ID_SLIDER_Speed2"), wxString::Format(wxT("%d"),Slider_Speed2->GetValue()));
    LoadPageControlsToAttr(Choicebook1->GetPage(PageIdx1),NewXml);
    LoadSizerControlsToAttr(FlexGridSizer_Palette1, NewXml);
    LoadPageControlsToAttr(Choicebook2->GetPage(PageIdx2),NewXml);
    LoadSizerControlsToAttr(FlexGridSizer_Palette2, NewXml);
    return NewXml;
}

void xRGBFrame::LoadPageControlsToAttr(wxWindow* page,wxXmlNode* x)
{
    wxWindowList &ChildList = page->GetChildren();
    //wxString msg=_("Children of ")+page->GetName();
    for ( wxWindowList::Node *node = ChildList.GetFirst(); node; node = node->GetNext() )
    {
        wxWindow *ChildWin = (wxWindow *)node->GetData();
        wxString ChildName=ChildWin->GetName();
        if (ChildName.StartsWith(wxT("ID_SLIDER"))) {
            wxSlider* ctrl=(wxSlider*)ChildWin;
            x->AddAttribute(ChildName, wxString::Format(wxT("%d"),ctrl->GetValue()));
        } else if (ChildName.StartsWith(wxT("ID_TEXTCTRL"))) {
            wxTextCtrl* ctrl=(wxTextCtrl*)ChildWin;
            x->AddAttribute(ChildName, ctrl->GetValue());
        } else if (ChildName.StartsWith(wxT("ID_CHOICE"))) {
            wxChoice* ctrl=(wxChoice*)ChildWin;
            x->AddAttribute(ChildName, ctrl->GetStringSelection());
        } else if (ChildName.StartsWith(wxT("ID_CHECKBOX"))) {
            wxCheckBox* ctrl=(wxCheckBox*)ChildWin;
            wxString v=(ctrl->IsChecked()) ? wxT("1") : wxT("0");
            x->AddAttribute(ChildName, v);
        }
        //msg+=wxT("\n")+ChildName;
    }
    //wxMessageBox(msg);
}

// used to save palette
void xRGBFrame::LoadSizerControlsToAttr(wxSizer* sizer,wxXmlNode* x)
{
    wxSizerItemList &ChildList = sizer->GetChildren();
    for ( wxSizerItemList::iterator it = ChildList.begin(); it != ChildList.end(); ++it )
    {
        if (!(*it)->IsWindow()) continue;
        wxWindow *ChildWin = (*it)->GetWindow();
        wxString ChildName=ChildWin->GetName();
        if (ChildName.StartsWith(wxT("ID_BUTTON"))) {
            wxColour color=ChildWin->GetBackgroundColour();
            x->AddAttribute(ChildName, color.GetAsString(wxC2S_HTML_SYNTAX));
        } else if (ChildName.StartsWith(wxT("ID_CHECKBOX"))) {
            wxCheckBox* ctrl=(wxCheckBox*)ChildWin;
            wxString v=(ctrl->IsChecked()) ? wxT("1") : wxT("0");
            x->AddAttribute(ChildName, v);
        }
    }
}

void xRGBFrame::OnButton_ModelsClick(wxCommandEvent& event)
{
    ModelListDialog dialog(this);
    wxString name;
    wxXmlNode* e;
    for(e=ModelsNode->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() == wxT("model")) {
            name=e->GetAttribute(wxT("name"));
            if (!name.IsEmpty()) {
                dialog.ListBox1->Append(name,e);
            }
        }
    }
    dialog.HtmlEasyPrint=HtmlEasyPrint;
    dialog.ShowModal();

    // append any new models to the main xml structure
    for(size_t i=0; i<dialog.ListBox1->GetCount(); i++) {
        e=(wxXmlNode*)dialog.ListBox1->GetClientData(i);
        if (!e->GetParent()) {
            ModelsNode->AddChild(e);
        }
    }
    UpdateModelsList();
}

void xRGBFrame::OnButton_PresetsClick(wxCommandEvent& event)
{
    EffectListDialog dialog(this);
    wxString name;
    for(wxXmlNode* e=EffectsNode->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() == wxT("effect")) {
            name=e->GetAttribute(wxT("name"));
            if (!name.IsEmpty()) {
                dialog.ListBox1->Append(name,e);
            }
        }
    }
    dialog.ShowModal();
    UpdateEffectsList();
    PresetsSelect();
}

// displays color chooser and updates the button's background color with the return value
void xRGBFrame::OnButton_ColorClick(wxCommandEvent& event)
{
    wxWindow* w=(wxWindow*)event.GetEventObject();
    if (ColourDialog1->ShowModal() == wxID_OK) {
        wxColourData retData = ColourDialog1->GetColourData();
        wxColour color = retData.GetColour();
        w->SetBackgroundColour(color);
        PaletteChanged=true;
    }
}

/*
// old version
void xRGBFrame::OnButton_ColorClick(wxCommandEvent& event)
{
    wxWindow* w=(wxWindow*)event.GetEventObject();
    wxString ButtonName=w->GetName();
    wxString TextCtrlName=ButtonName;
    TextCtrlName.Replace(wxT("ID_BUTTON_"), wxT("ID_TEXTCTRL_"));
    wxTextCtrl* t=(wxTextCtrl*)wxWindow::FindWindowByName(TextCtrlName, w->GetParent());
    if (t) {
        if (ColourDialog1->ShowModal() == wxID_OK) {
            wxColourData retData = ColourDialog1->GetColourData();
            wxColour color = retData.GetColour();
            t->SetValue(color.GetAsString(wxC2S_HTML_SYNTAX));
        }
    } else {
        wxMessageBox(_("Cannot find window ")+TextCtrlName, _("Internal Error"));
    }
}
*/

void xRGBFrame::SetChoicebook(wxChoicebook* cb, wxString& PageName)
{
    for(size_t i=0; i<cb->GetPageCount(); i++) {
        if (cb->GetPageText(i) == PageName) {
            cb->SetSelection(i);
            return;
        }
    }
}

void xRGBFrame::SetControls(wxXmlNode* x)
{
    long TempLong;
    wxColour color;
    for (wxXmlAttribute *a=x->GetAttributes(); a!=NULL; a=a->GetNext()) {
        wxString name=a->GetName();
        wxString value=a->GetValue();
        if (!name.StartsWith(wxT("ID_"))) continue;
        wxWindow *CtrlWin=wxWindow::FindWindowByName(name);
        if (CtrlWin==NULL) continue;
        if (name.StartsWith(wxT("ID_SLIDER"))) {
            wxSlider* ctrl=(wxSlider*)CtrlWin;
            if (value.ToLong(&TempLong)) ctrl->SetValue(TempLong);
        } else if (name.StartsWith(wxT("ID_TEXTCTRL"))) {
            wxTextCtrl* ctrl=(wxTextCtrl*)CtrlWin;
            ctrl->SetValue(value);
        } else if (name.StartsWith(wxT("ID_CHOICEBOOK"))) {
            SetChoicebook((wxChoicebook*)CtrlWin,value);
        } else if (name.StartsWith(wxT("ID_CHOICE"))) {
            wxChoice* ctrl=(wxChoice*)CtrlWin;
            ctrl->SetStringSelection(value);
        } else if (name.StartsWith(wxT("ID_BUTTON"))) {
            color.Set(value);
            CtrlWin->SetBackgroundColour(color);
        } else if (name.StartsWith(wxT("ID_CHECKBOX"))) {
            wxCheckBox* ctrl=(wxCheckBox*)CtrlWin;
            if (value.ToLong(&TempLong)) ctrl->SetValue(TempLong!=0);
        }
    }
    PaletteChanged=true;
    MixTypeChanged=true;
}

void xRGBFrame::PresetsSelect()
{
    int NameIdx=Choice_Presets->GetSelection();
    if (NameIdx != wxNOT_FOUND) {
        wxXmlNode* x=(wxXmlNode*)Choice_Presets->GetClientData(NameIdx);
        SetControls(x);
    }
}

void xRGBFrame::OnChoice_PresetsSelect(wxCommandEvent& event)
{
    PresetsSelect();
}

void xRGBFrame::SetPlayMode(play_modes newmode)
{
    int sel;
    wxString s;
    wxXmlNode* ModelXml;
    switch (newmode) {
        case play_off:
            StaticText_PlaybackMode->SetLabelText(_("Playback: off"));
            break;
        case play_effect:
            sel=Choice_Models->GetSelection();
            if (sel == wxNOT_FOUND) {
                wxMessageBox(_("No model is selected"), _("ERROR"));
                return;
            }
            ModelXml=(wxXmlNode*)Choice_Models->GetClientData(sel);
            buffer.InitBuffer(ModelXml);
            s=Choice_LayerMethod->GetStringSelection();
            buffer.SetMixType(s);
            LastSparkleFrequency=-1;
            LastSparkleDensity=-1;
            StaticText_PlaybackMode->SetLabelText(_("Playback: effect"));
            break;
        case play_seqpartial:
            StaticText_PlaybackMode->SetLabelText(_("Playback: sequence selection"));
            break;
        case play_seqall:
            StaticText_PlaybackMode->SetLabelText(_("Playback: complete sequence"));
            break;
    }
    play_mode=newmode;
    Button_Stop->Enable(newmode != play_off);
    Button_PlayEffect->Enable(newmode == play_off && Choice_Models->GetCount() > 0);
    Button_PlaySelection->Enable(newmode == play_off);
    Button_PlayAll->Enable(newmode == play_off);
    Button_Models->Enable(newmode == play_off);
    Button_Presets->Enable(newmode == play_off);
    Choice_Models->Enable(newmode == play_off);
    Button_Pictures1_Filename->Enable(newmode == play_off);
    TextCtrl_Pictures1_Filename->Enable(newmode == play_off);
    Button_Pictures2_Filename->Enable(newmode == play_off);
    TextCtrl_Pictures2_Filename->Enable(newmode == play_off);
    starttime = wxDateTime::UNow();
}

void xRGBFrame::OnButton_PlayEffectClick(wxCommandEvent& event)
{
    SetPlayMode(play_effect);
}

void xRGBFrame::OnButton_PlaySelectionClick(wxCommandEvent& event)
{
    SetPlayMode(play_seqpartial);
}

void xRGBFrame::OnButton_PlayAllClick(wxCommandEvent& event)
{
    SetPlayMode(play_seqall);
}

void xRGBFrame::OnButton_StopClick(wxCommandEvent& event)
{
    SetPlayMode(play_off);
}

void xRGBFrame::OnChoice_LayerMethodSelect(wxCommandEvent& event)
{
    MixTypeChanged=true;
}

void xRGBFrame::OnCheckBox_PaletteClick(wxCommandEvent& event)
{
    PaletteChanged=true;
}
