/***************************************************************
 * Name:      xTesterRGBMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2011-09-18
 * Copyright: 2011 by Matt Brown
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

#include "xTesterRGBMain.h"
#include <wx/msgdlg.h>
#include <wx/config.h>
#include <wx/icon.h>
// For wxWidgets 2.9/3.0
//#include <wx/kbdstate.h>

#include "../include/xlights.xpm"


//(*InternalHeaders(xTesterRGBFrame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "../include/xlights_out.cpp"


#define MAXINTENSITY 255
#define XTIMER_INTERVAL 50
#define TWINKLE_PERIOD 750
#define SHIMMER_PERIOD 50

xOutput xout;


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

//(*IdInit(xTesterRGBFrame)
const long xTesterRGBFrame::ID_STATICTEXT1 = wxNewId();
const long xTesterRGBFrame::ID_CHOICE_NUM_SELECT = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT3 = wxNewId();
const long xTesterRGBFrame::ID_BUTTON1 = wxNewId();
const long xTesterRGBFrame::ID_NOTEBOOK2 = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT2 = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT13 = wxNewId();
const long xTesterRGBFrame::ID_SLIDER5 = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT14 = wxNewId();
const long xTesterRGBFrame::ID_SLIDER6 = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT12 = wxNewId();
const long xTesterRGBFrame::ID_SLIDER1 = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT6 = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT11 = wxNewId();
const long xTesterRGBFrame::ID_PANEL1 = wxNewId();
const long xTesterRGBFrame::ID_CHECKBOX_RUNSEQ = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT4 = wxNewId();
const long xTesterRGBFrame::ID_SLIDER2 = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT5 = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT10 = wxNewId();
const long xTesterRGBFrame::ID_PANEL2 = wxNewId();
const long xTesterRGBFrame::ID_CHECKBOX_RUNFADE = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT7 = wxNewId();
const long xTesterRGBFrame::ID_SLIDER3 = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT8 = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT9 = wxNewId();
const long xTesterRGBFrame::ID_PANEL3 = wxNewId();
const long xTesterRGBFrame::ID_CHECKBOX_RUNSH = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT15 = wxNewId();
const long xTesterRGBFrame::ID_SLIDER4 = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT16 = wxNewId();
const long xTesterRGBFrame::ID_SLIDER7 = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT17 = wxNewId();
const long xTesterRGBFrame::ID_SLIDER8 = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT18 = wxNewId();
const long xTesterRGBFrame::ID_STATICTEXT19 = wxNewId();
const long xTesterRGBFrame::ID_PANEL_SHIMMER = wxNewId();
const long xTesterRGBFrame::ID_NOTEBOOK1 = wxNewId();
const long xTesterRGBFrame::ID_PANEL4 = wxNewId();
const long xTesterRGBFrame::idMenuQuit = wxNewId();
const long xTesterRGBFrame::idMenuHelpContent = wxNewId();
const long xTesterRGBFrame::idMenuAbout = wxNewId();
const long xTesterRGBFrame::ID_STATUSBAR1 = wxNewId();
//*)
const long xTesterRGBFrame::ID_TIMER = wxNewId();

BEGIN_EVENT_TABLE(xTesterRGBFrame,wxFrame)
    //(*EventTable(xTesterRGBFrame)
    //*)
    EVT_TIMER(ID_TIMER, xTesterRGBFrame::OnTimer)
END_EVENT_TABLE()

xTesterRGBFrame::xTesterRGBFrame(wxWindow* parent,wxWindowID id) : timer(this, ID_TIMER)
{
    //(*Initialize(xTesterRGBFrame)
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer6;
    wxFlexGridSizer* FlexGridSizer4;
    wxBoxSizer* BoxSizer5;
    wxMenuItem* MenuItem2;
    wxFlexGridSizer* FlexGridSizer3;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer2;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxFlexGridSizer* FlexGridSizer7;
    wxFlexGridSizer* FlexGridSizer8;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer6;
    wxFlexGridSizer* FlexGridSizer1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("xTesterRGB"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(645,325));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel3 = new wxPanel(this, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE, _T("ID_PANEL4"));
    FlexGridSizer2 = new wxFlexGridSizer(2, 2, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    FlexGridSizer2->AddGrowableCol(1);
    FlexGridSizer2->AddGrowableRow(1);
    FlexGridSizer7 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer7->AddGrowableCol(0);
    FlexGridSizer7->AddGrowableRow(0);
    StaticText1 = new wxStaticText(Panel3, ID_STATICTEXT1, _("Selection mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer7->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ChoiceNumSelect = new wxChoice(Panel3, ID_CHOICE_NUM_SELECT, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_NUM_SELECT"));
    ChoiceNumSelect->SetSelection( ChoiceNumSelect->Append(_("3")) );
    ChoiceNumSelect->Append(_("15"));
    ChoiceNumSelect->Append(_("30"));
    ChoiceNumSelect->Append(_("45"));
    ChoiceNumSelect->Append(_("60"));
    ChoiceNumSelect->Append(_("75"));
    ChoiceNumSelect->Append(_("90"));
    ChoiceNumSelect->Append(_("120"));
    ChoiceNumSelect->Append(_("150"));
    ChoiceNumSelect->Append(_("225"));
    ChoiceNumSelect->Append(_("300"));
    ChoiceNumSelect->Append(_("All"));
    FlexGridSizer7->Add(ChoiceNumSelect, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(FlexGridSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    StaticText3 = new wxStaticText(Panel3, ID_STATICTEXT3, _("Available Tests"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer2->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button1 = new wxButton(Panel3, ID_BUTTON1, _("All Lights Off"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(Button1, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
    FlexGridSizer2->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Notebook2 = new wxNotebook(Panel3, ID_NOTEBOOK2, wxDefaultPosition, wxSize(225,220), 0, _T("ID_NOTEBOOK2"));
    FlexGridSizer2->Add(Notebook2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Notebook1 = new wxNotebook(Panel3, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    Panel_Dim = new wxPanel(Notebook1, ID_PANEL1, wxPoint(29,39), wxSize(211,136), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    StaticText2 = new wxStaticText(Panel_Dim, ID_STATICTEXT2, _("Set RGB color on selected channels"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer1->Add(StaticText2, 0, wxTOP|wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 10);
    FlexGridSizer5 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer5->AddGrowableCol(1);
    StaticText13 = new wxStaticText(Panel_Dim, ID_STATICTEXT13, _("Channel A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    FlexGridSizer5->Add(StaticText13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderSetColorA = new wxSlider(Panel_Dim, ID_SLIDER5, 0, 0, 255, wxDefaultPosition, wxSize(184,48), wxSL_HORIZONTAL|wxSL_LABELS|wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER5"));
    FlexGridSizer5->Add(SliderSetColorA, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    StaticText14 = new wxStaticText(Panel_Dim, ID_STATICTEXT14, _("Channel B"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    FlexGridSizer5->Add(StaticText14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderSetColorB = new wxSlider(Panel_Dim, ID_SLIDER6, 0, 0, 255, wxDefaultPosition, wxSize(184,48), wxSL_HORIZONTAL|wxSL_LABELS|wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER6"));
    FlexGridSizer5->Add(SliderSetColorB, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    StaticText12 = new wxStaticText(Panel_Dim, ID_STATICTEXT12, _("Channel C"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    FlexGridSizer5->Add(StaticText12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderSetColorC = new wxSlider(Panel_Dim, ID_SLIDER1, 0, 0, 255, wxDefaultPosition, wxSize(184,48), wxSL_HORIZONTAL|wxSL_LABELS|wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER1"));
    FlexGridSizer5->Add(SliderSetColorC, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    FlexGridSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    StaticText6 = new wxStaticText(Panel_Dim, ID_STATICTEXT6, _("Off"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    BoxSizer4->Add(StaticText6, 1, wxALL|wxSHAPED|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText11 = new wxStaticText(Panel_Dim, ID_STATICTEXT11, _("On"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    BoxSizer4->Add(StaticText11, 1, wxALL|wxSHAPED|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(BoxSizer4, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    FlexGridSizer1->Add(FlexGridSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel_Dim->SetSizer(FlexGridSizer1);
    FlexGridSizer1->SetSizeHints(Panel_Dim);
    Panel_Seq = new wxPanel(Notebook1, ID_PANEL2, wxPoint(71,15), wxSize(392,209), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer3->AddGrowableCol(0);
    CheckBoxRunSeq = new wxCheckBox(Panel_Seq, ID_CHECKBOX_RUNSEQ, _("Run selected lights in RGB sequence"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RUNSEQ"));
    CheckBoxRunSeq->SetValue(false);
    FlexGridSizer3->Add(CheckBoxRunSeq, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 10);
    StaticText4 = new wxStaticText(Panel_Seq, ID_STATICTEXT4, _("Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    wxFont StaticText4Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText4->SetFont(StaticText4Font);
    FlexGridSizer3->Add(StaticText4, 0, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 10);
    Slider1 = new wxSlider(Panel_Seq, ID_SLIDER2, 50, 0, 100, wxDefaultPosition, wxSize(184,24), wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER2"));
    FlexGridSizer3->Add(Slider1, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 10);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticText5 = new wxStaticText(Panel_Seq, ID_STATICTEXT5, _("Slow"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    BoxSizer3->Add(StaticText5, 1, wxALL|wxSHAPED|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText10 = new wxStaticText(Panel_Seq, ID_STATICTEXT10, _("Fast"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    BoxSizer3->Add(StaticText10, 1, wxALL|wxSHAPED|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(BoxSizer3, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    Panel_Seq->SetSizer(FlexGridSizer3);
    FlexGridSizer3->SetSizeHints(Panel_Seq);
    Panel_Fade = new wxPanel(Notebook1, ID_PANEL3, wxPoint(114,11), wxSize(188,117), wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    CheckBoxRunFade = new wxCheckBox(Panel_Fade, ID_CHECKBOX_RUNFADE, _("Color cycle selected lights"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RUNFADE"));
    CheckBoxRunFade->SetValue(false);
    FlexGridSizer4->Add(CheckBoxRunFade, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 10);
    StaticText7 = new wxStaticText(Panel_Fade, ID_STATICTEXT7, _("Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    wxFont StaticText7Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText7->SetFont(StaticText7Font);
    FlexGridSizer4->Add(StaticText7, 0, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 10);
    Slider3 = new wxSlider(Panel_Fade, ID_SLIDER3, 50, 0, 100, wxDefaultPosition, wxSize(184,24), wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER3"));
    FlexGridSizer4->Add(Slider3, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 10);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    StaticText8 = new wxStaticText(Panel_Fade, ID_STATICTEXT8, _("Slow"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    BoxSizer5->Add(StaticText8, 1, wxALL|wxSHAPED|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(Panel_Fade, ID_STATICTEXT9, _("Fast"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    BoxSizer5->Add(StaticText9, 1, wxALL|wxSHAPED|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(BoxSizer5, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    Panel_Fade->SetSizer(FlexGridSizer4);
    FlexGridSizer4->SetSizeHints(Panel_Fade);
    PanelShimmer = new wxPanel(Notebook1, ID_PANEL_SHIMMER, wxPoint(91,12), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_SHIMMER"));
    FlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer6->AddGrowableCol(0);
    CheckBoxRunSh = new wxCheckBox(PanelShimmer, ID_CHECKBOX_RUNSH, _("Shimmer using selected color"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RUNSH"));
    CheckBoxRunSh->SetValue(false);
    FlexGridSizer6->Add(CheckBoxRunSh, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 10);
    FlexGridSizer8 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer8->AddGrowableCol(1);
    StaticText15 = new wxStaticText(PanelShimmer, ID_STATICTEXT15, _("Channel A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    FlexGridSizer8->Add(StaticText15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderShimmerA = new wxSlider(PanelShimmer, ID_SLIDER4, 0, 0, 255, wxDefaultPosition, wxSize(184,48), wxSL_HORIZONTAL|wxSL_LABELS|wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER4"));
    FlexGridSizer8->Add(SliderShimmerA, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    StaticText16 = new wxStaticText(PanelShimmer, ID_STATICTEXT16, _("Channel B"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    FlexGridSizer8->Add(StaticText16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderShimmerB = new wxSlider(PanelShimmer, ID_SLIDER7, 0, 0, 255, wxDefaultPosition, wxSize(184,48), wxSL_HORIZONTAL|wxSL_LABELS|wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER7"));
    FlexGridSizer8->Add(SliderShimmerB, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    StaticText17 = new wxStaticText(PanelShimmer, ID_STATICTEXT17, _("Channel C"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    FlexGridSizer8->Add(StaticText17, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderShimmerC = new wxSlider(PanelShimmer, ID_SLIDER8, 0, 0, 255, wxDefaultPosition, wxSize(184,48), wxSL_HORIZONTAL|wxSL_LABELS|wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER8"));
    FlexGridSizer8->Add(SliderShimmerC, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    FlexGridSizer8->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    StaticText18 = new wxStaticText(PanelShimmer, ID_STATICTEXT18, _("Off"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    BoxSizer6->Add(StaticText18, 1, wxALL|wxSHAPED|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText19 = new wxStaticText(PanelShimmer, ID_STATICTEXT19, _("On"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    BoxSizer6->Add(StaticText19, 1, wxALL|wxSHAPED|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer8->Add(BoxSizer6, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    FlexGridSizer6->Add(FlexGridSizer8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelShimmer->SetSizer(FlexGridSizer6);
    FlexGridSizer6->Fit(PanelShimmer);
    FlexGridSizer6->SetSizeHints(PanelShimmer);
    Notebook1->AddPage(Panel_Dim, _("Set Color"), false);
    Notebook1->AddPage(Panel_Seq, _("RGB Cycle"), false);
    Notebook1->AddPage(Panel_Fade, _("Color Cycle"), false);
    Notebook1->AddPage(PanelShimmer, _("Shimmer"), false);
    FlexGridSizer2->Add(Notebook1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel3->SetSizer(FlexGridSizer2);
    FlexGridSizer2->Fit(Panel3);
    FlexGridSizer2->SetSizeHints(Panel3);
    BoxSizer1->Add(Panel3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItemHelpContent = new wxMenuItem(Menu2, idMenuHelpContent, _("Content\tF1"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItemHelpContent);
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xTesterRGBFrame::OnButton1Click);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xTesterRGBFrame::OnQuit);
    Connect(idMenuHelpContent,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xTesterRGBFrame::OnMenuItemHelpContentSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xTesterRGBFrame::OnAbout);
    //*)

    SetIcon(wxIcon(xlights_xpm));

    /*
    wxLog *logger=new wxLogTextCtrl(TextCtrlLog);
    wxLog::SetActiveTarget(logger);
    Notebook1->AddPage(PanelLog, _("Log"), false);
    */

    // Get CurrentDir
    wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));
    wxString CurrentDir;
    if ( !config->Read(_("LastDir"), &CurrentDir) ) {
        wxMessageBox(_("No directory specified"), _("ERROR"));
        Close();
    }
    networkFile.AssignDir( CurrentDir );
    networkFile.SetFullName(_(XLIGHTS_NETWORK_FILE));
    LoadFile();
    starttime = wxDateTime::UNow();
    xout.SetMaxIntensity(MAXINTENSITY);

    if (Networks.Count() > 0) {
        timer.Start(XTIMER_INTERVAL, wxTIMER_CONTINUOUS);
    }
}

xTesterRGBFrame::~xTesterRGBFrame()
{
    if (timer.IsRunning()) timer.Stop();
    //(*Destroy(xTesterRGBFrame)
    //*)
}

void xTesterRGBFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void xTesterRGBFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _(XLIGHTS_LICENSE);
    wxString hdg = wxString::Format(_("About xLights %s"),_(XLIGHTS_VERSION));
    wxMessageBox(msg, hdg);
}

void xTesterRGBFrame::OnTimer(wxTimerEvent& event) {
    static int LastNotebookSelection = -1;
    static int LastDimValue[3];
    static int LastSequenceSpeed;
    static int LastTest;
    static long SeqNum=0, NextSequenceStart = -1;
    static int interval, rgbCycle=0, alt=0;
    static float frequency;
    int v,n,ch,rgbChannel,color[3];
    /*
    static bool loggingEnabled=false;
    if (CheckBoxRunSh->IsChecked() && !loggingEnabled) {
        wxLog::AddTraceMask(wxT("xout"));
        loggingEnabled=true;
    }
    wxLogTrace(wxT("xout"),wxT("Starting OnTimer"));
    */
    int netidx = Notebook2->GetSelection(); // which network
    wxCheckListBox* lb = Networks[netidx]->ListBox;
    int maxch = lb->GetCount();
    wxTimeSpan ts = wxDateTime::UNow() - starttime;
    long curtime = ts.GetMilliseconds().ToLong();
    xout.TimerStart(curtime);
    int NotebookSelection = Notebook1->GetSelection();
    if (NotebookSelection != LastNotebookSelection) {
        LastNotebookSelection = NotebookSelection;
        alloff();
        LastSequenceSpeed=-1;
        LastDimValue[0]=-1;
        LastDimValue[1]=-1;
        LastDimValue[2]=-1;
        LastTest=-1;
        StatusBar1->SetStatusText(wxEmptyString);
    }
    switch (NotebookSelection) {
        case 0:
            // RGB Color
            color[0]=SliderSetColorA->GetValue();
            color[1]=SliderSetColorB->GetValue();
            color[2]=SliderSetColorC->GetValue();
            if (color[0] != LastDimValue[0] || color[1] != LastDimValue[1] || color[2] != LastDimValue[2]) {
                for (ch=0,n=0,rgbChannel=0; ch < maxch; ch++) {
                    if (lb->IsChecked(ch)) {
                        xout.SetIntensity(netidx, ch, color[rgbChannel]);
                        n++;
                        rgbChannel=(rgbChannel + 1) % 3;
                    }
                }
                LastDimValue[0] = color[0];
                LastDimValue[1] = color[1];
                LastDimValue[2] = color[2];
                StatusBar1->SetStatusText(wxString::Format(_("Dimming %d channels to %d %d %d"),n,color[0],color[1],color[2]));
            }
            break;
        case 1:
            // RGB Cycle
            if (CheckBoxRunSeq->IsChecked()) {
                v=Slider1->GetValue();  // 0-100
                if (v != LastSequenceSpeed) {
                    interval = 1600 - v*15;
                    NextSequenceStart = curtime + interval;
                    LastSequenceSpeed = v;
                    StatusBar1->SetStatusText(wxString::Format(_("Turning on channels in RGB sequence, speed=%d"),interval));
                }
                if (curtime >= NextSequenceStart) {
                    for (ch=0,rgbChannel=0; ch < maxch; ch++) {
                        if (lb->IsChecked(ch)) {
                            v = rgbChannel == rgbCycle ? MAXINTENSITY : 0;
                            xout.SetIntensity(netidx, ch, v);
                            rgbChannel=(rgbChannel + 1) % 3;
                        }
                    }
                    rgbCycle=(rgbCycle + 1) % 3;
                    NextSequenceStart += interval;
                }
            } else {
                LastSequenceSpeed=-1;
                rgbCycle=0;
            }
            break;
        case 2:
            // Color Cycle
            if (CheckBoxRunFade->IsChecked()) {
                v=Slider3->GetValue();  // 0-100
                if (v != LastSequenceSpeed) {
                    frequency=v/1000.0 + 0.05;
                    StatusBar1->SetStatusText(wxString::Format(_("Color Cycle, speed=%d"),v));
                }
                color[0] = sin(frequency*SeqNum + 0.0) * 127 + 128;
                color[1] = sin(frequency*SeqNum + 2.0) * 127 + 128;
                color[2] = sin(frequency*SeqNum + 4.0) * 127 + 128;
                SeqNum++;
                for (ch=0,rgbChannel=0; ch < maxch; ch++) {
                    if (lb->IsChecked(ch)) {
                        xout.SetIntensity(netidx, ch, color[rgbChannel]);
                        rgbChannel=(rgbChannel + 1) % 3;
                    }
                }
            } else {
                LastSequenceSpeed=-1;
                SeqNum=0;
            }
            break;
        case 3:
            // shimmer
            if (CheckBoxRunSh->IsChecked()) {
                color[0]=SliderShimmerA->GetValue();
                color[1]=SliderShimmerB->GetValue();
                color[2]=SliderShimmerC->GetValue();
                if (color[0] != LastDimValue[0] || color[1] != LastDimValue[1] || color[2] != LastDimValue[2]) {
                    LastDimValue[0] = color[0];
                    LastDimValue[1] = color[1];
                    LastDimValue[2] = color[2];
                    StatusBar1->SetStatusText(wxString::Format(_("Shimmering values %d %d %d"),color[0],color[1],color[2]));
                }
                for (ch=0,rgbChannel=0; ch < maxch; ch++) {
                    if (lb->IsChecked(ch)) {
                        xout.SetIntensity(netidx, ch, color[rgbChannel]*alt);
                        rgbChannel=(rgbChannel + 1) % 3;
                    }
                }
                alt=1-alt;
            }
            break;
    }
    xout.TimerEnd();
    //wxLogTrace(wxT("xout"),wxT("Ending OnTimer"));
    //StatusBar1->SetStatusText(ts.Format(_("%S.%l")));
}

void xTesterRGBFrame::LoadFile()
{
    long MaxChan;
    wxString tempstr,tagname,NetworkType,ComPort,BaudRate;
    wxXmlDocument doc;
    if (doc.Load( networkFile.GetFullPath() )) {
        wxXmlNode* e=doc.GetRoot();
        tempstr=e->GetPropVal(wxT("LorMapping"), wxT("2"));
        tempstr.ToLong(&LorMapping);
        for( e=e->GetChildren(); e!=NULL; e=e->GetNext() ) {
            tagname=e->GetName();
            if (tagname == wxT("network")) {
                tempstr=e->GetPropVal(wxT("MaxChannels"), wxT("0"));
                tempstr.ToLong(&MaxChan);
                NetworkType=e->GetPropVal(wxT("NetworkType"), wxT(""));
                ComPort=e->GetPropVal(wxT("ComPort"), wxT(""));
                BaudRate=e->GetPropVal(wxT("BaudRate"), wxT(""));
                AddNetwork(NetworkType,ComPort,BaudRate,MaxChan);
            }
        }
    } else {
        wxMessageBox(_("Unable to load network definition file"), _("Error"));
    }
}

NetworkInfo* xTesterRGBFrame::AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels)
{
    NetworkInfo* NetInfo=new NetworkInfo();
    NetInfo->NetworkType=NetworkType;
    NetInfo->ComPort=ComPort;
    NetInfo->BaudRate=BaudRate;
    NetInfo->MaxChannels=MaxChannels;

    int cnt=Networks.Count();
    wxString sid = wxString::Format(_T("%d"), cnt+1);
    wxPanel* Panel = new wxPanel(Notebook2, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL")+sid);
    wxFlexGridSizer* FlexSizer = new wxFlexGridSizer(0, 1, 0, 0);
    FlexSizer->AddGrowableRow(1);
    FlexSizer->AddGrowableCol(0);
    wxStaticText* stNetDesc = new wxStaticText(Panel, -1, NetInfo->Description());
    FlexSizer->Add(stNetDesc, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    wxCheckListBox* ListBox = new wxCheckListBox(Panel, -1);
    FlexSizer->Add(ListBox, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel->SetSizer(FlexSizer);
    FlexSizer->Fit(Panel);
    FlexSizer->SetSizeHints(Panel);
    Notebook2->AddPage(Panel, _("Network ")+sid, true);

    NetInfo->Panel=Panel;
    NetInfo->ListBox=ListBox;
    NetInfo->DescField=stNetDesc;
    Networks.Add(NetInfo);

    wxString net3 = NetInfo->net3();
    int baud = (BaudRate == _("n/a")) ? 230400 : atoi(BaudRate.mb_str(wxConvUTF8));
    try {
        xout.setnetwork(net3,cnt,MaxChannels,ComPort,baud);
    }
    catch (const char *str) {
        wxString errmsg(str,wxConvUTF8);
        wxString msg = wxString::Format(_("Error occurred while connecting to %s network on %s\n\n"),NetworkType.c_str(),ComPort.c_str());
        wxMessageBox(msg+errmsg, _("Communication Error"));
        return NetInfo;
    }
    catch (char *str) {
        wxString errmsg(str,wxConvUTF8);
        wxString msg = wxString::Format(_("Error occurred while connecting to %s network on %s\n\n"),NetworkType.c_str(),ComPort.c_str());
        wxMessageBox(msg+errmsg, _("Communication Error"));
        return NetInfo;
    }

    wxArrayString chNames;
    if (net3 == wxT("LOR") || net3 == wxT("D-L")) {
        for (int i=0; i < MaxChannels; i++) {
            chNames.Add( wxString::Format(_T("Unit %d.%02d"), (i >> 4)+1, (i & 0x0F)+1 ));
        }
    } else {
        for (int i=1; i <= MaxChannels; i++) {
            chNames.Add( wxString::Format(_T("Channel %d"), i) );
        }
    }
    ListBox->Set(chNames);
    ListBox->Connect(wxEVT_COMMAND_CHECKLISTBOX_TOGGLED,(wxObjectEventFunction)&xTesterRGBFrame::OnCheckboxToggle, NULL, this);

    return NetInfo;
}


void xTesterRGBFrame::OnCheckboxToggle(wxCommandEvent& event)
{
    int netidx = Notebook2->GetSelection(); // which network
    wxCheckListBox* lb = Networks[netidx]->ListBox;
    int ChCount = lb->GetCount();
    int row=event.GetInt();
    bool newval=lb->IsChecked(row);
    long SelectCount;
    wxString SelectString = ChoiceNumSelect->GetStringSelection();
    if (SelectString == wxT("All")) {
        for (int i=0; i < ChCount; i++) {
            lb->Check(i,newval);
        }
    } else {
        SelectString.ToLong(&SelectCount);
        int lastrow = row+SelectCount;
        for (int i=row+1; i < lastrow; i++) {
            if (i >= ChCount) break;
            lb->Check(i,newval);
        }
    }
    //StatusBar1->SetStatusText(newval ? _("true") : _("false"));
    //static int lastrow=0;

    // In wxWidgets 2.9/3.0:
    // test state of shift key using wxKeyboardState class
    // so that shift-click will select a range of checkboxes
}


void xTesterRGBFrame::alloff()
{
    SliderSetColorA->SetValue(0);
    SliderSetColorB->SetValue(0);
    SliderSetColorC->SetValue(0);
    CheckBoxRunSeq->SetValue(false);
    CheckBoxRunFade->SetValue(false);
    CheckBoxRunSh->SetValue(false);
    xout.alloff();
}


void xTesterRGBFrame::OnButton1Click(wxCommandEvent& event)
{
    alloff();
    StatusBar1->SetStatusText(_("All lights off"));
    wxLog::ClearTraceMasks();
}

void xTesterRGBFrame::OnMenuItemHelpContentSelected(wxCommandEvent& event)
{
    if (!wxLaunchDefaultBrowser(_(XLIGHTS_HELP_URL)))
    {
        wxMessageBox(_("Help requires Internet access. Unable to access help."), _("Error"));
    }
}
