/***************************************************************
 * Name:      xTesterMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-04-03
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

#include "xTesterMain.h"
#include <wx/msgdlg.h>
#include <wx/config.h>
#include <wx/icon.h>

// For wxWidgets 2.9/3.0
//#include <wx/kbdstate.h>

#include "../include/xlights.xpm"


//(*InternalHeaders(xTesterFrame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "../include/xlights_out.cpp"


#define MAXINTENSITY 255
#define XTIMER_INTERVAL 50

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

//(*IdInit(xTesterFrame)
const long xTesterFrame::ID_STATICTEXT1 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON_1 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON_16 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON_ALL = wxNewId();
const long xTesterFrame::ID_STATICTEXT3 = wxNewId();
const long xTesterFrame::ID_BUTTON1 = wxNewId();
const long xTesterFrame::ID_NOTEBOOK2 = wxNewId();
const long xTesterFrame::ID_STATICTEXT2 = wxNewId();
const long xTesterFrame::ID_SLIDER1 = wxNewId();
const long xTesterFrame::ID_STATICTEXT6 = wxNewId();
const long xTesterFrame::ID_STATICTEXT11 = wxNewId();
const long xTesterFrame::ID_PANEL1 = wxNewId();
const long xTesterFrame::ID_CHECKBOX_RUNSEQ = wxNewId();
const long xTesterFrame::ID_STATICTEXT4 = wxNewId();
const long xTesterFrame::ID_SLIDER2 = wxNewId();
const long xTesterFrame::ID_STATICTEXT5 = wxNewId();
const long xTesterFrame::ID_STATICTEXT10 = wxNewId();
const long xTesterFrame::ID_PANEL2 = wxNewId();
const long xTesterFrame::ID_CHECKBOX_RUNALT = wxNewId();
const long xTesterFrame::ID_STATICTEXT7 = wxNewId();
const long xTesterFrame::ID_SLIDER3 = wxNewId();
const long xTesterFrame::ID_STATICTEXT8 = wxNewId();
const long xTesterFrame::ID_STATICTEXT9 = wxNewId();
const long xTesterFrame::ID_PANEL3 = wxNewId();
const long xTesterFrame::ID_CHECKBOX_RUNTW = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON_TWNOFADE = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON_TWFADE = wxNewId();
const long xTesterFrame::ID_STATICTEXT12 = wxNewId();
const long xTesterFrame::ID_STATICTEXT15 = wxNewId();
const long xTesterFrame::ID_SLIDER_TWRATE = wxNewId();
const long xTesterFrame::ID_STATICTEXT13 = wxNewId();
const long xTesterFrame::ID_STATICTEXT14 = wxNewId();
const long xTesterFrame::ID_PANEL5 = wxNewId();
const long xTesterFrame::ID_CHECKBOX_RUNSH = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON_SHNOFADE = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON_SHFADE = wxNewId();
const long xTesterFrame::ID_STATICTEXT16 = wxNewId();
const long xTesterFrame::ID_STATICTEXT17 = wxNewId();
const long xTesterFrame::ID_SLIDER4 = wxNewId();
const long xTesterFrame::ID_STATICTEXT18 = wxNewId();
const long xTesterFrame::ID_STATICTEXT19 = wxNewId();
const long xTesterFrame::ID_PANEL6 = wxNewId();
const long xTesterFrame::ID_NOTEBOOK1 = wxNewId();
const long xTesterFrame::ID_PANEL4 = wxNewId();
const long xTesterFrame::idMenuQuit = wxNewId();
const long xTesterFrame::idMenuHelpContent = wxNewId();
const long xTesterFrame::idMenuAbout = wxNewId();
const long xTesterFrame::ID_STATUSBAR1 = wxNewId();
//*)
const long xTesterFrame::ID_TIMER = wxNewId();

BEGIN_EVENT_TABLE(xTesterFrame,wxFrame)
    //(*EventTable(xTesterFrame)
    //*)
    EVT_TIMER(ID_TIMER, xTesterFrame::OnTimer)
END_EVENT_TABLE()

xTesterFrame::xTesterFrame(wxWindow* parent,wxWindowID id) : timer(this, ID_TIMER)
{
    //(*Initialize(xTesterFrame)
    wxBoxSizer* BoxSizer4;
    wxFlexGridSizer* FlexGridSizer4;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer7;
    wxMenuItem* MenuItem2;
    wxFlexGridSizer* FlexGridSizer3;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer2;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer11;
    wxMenu* Menu1;
    wxFlexGridSizer* FlexGridSizer7;
    wxMenuItem* MenuItemHelpContent;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer9;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer6;
    wxFlexGridSizer* FlexGridSizer1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("xTester"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(476,263));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel3 = new wxPanel(this, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE, _T("ID_PANEL4"));
    FlexGridSizer2 = new wxFlexGridSizer(2, 2, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    FlexGridSizer2->AddGrowableCol(1);
    FlexGridSizer2->AddGrowableRow(1);
    FlexGridSizer7 = new wxFlexGridSizer(0, 4, 0, 0);
    FlexGridSizer7->AddGrowableCol(0);
    FlexGridSizer7->AddGrowableRow(0);
    StaticText1 = new wxStaticText(Panel3, ID_STATICTEXT1, _("Select channels"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(wxDEFAULT,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    FlexGridSizer7->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButton1 = new wxRadioButton(Panel3, ID_RADIOBUTTON_1, _("1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON_1"));
    RadioButton1->SetValue(true);
    FlexGridSizer7->Add(RadioButton1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButton16 = new wxRadioButton(Panel3, ID_RADIOBUTTON_16, _("16"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON_16"));
    FlexGridSizer7->Add(RadioButton16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonAll = new wxRadioButton(Panel3, ID_RADIOBUTTON_ALL, _("All"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON_ALL"));
    FlexGridSizer7->Add(RadioButtonAll, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(FlexGridSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    StaticText3 = new wxStaticText(Panel3, ID_STATICTEXT3, _("Select test"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    wxFont StaticText3Font(wxDEFAULT,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText3->SetFont(StaticText3Font);
    BoxSizer2->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button1 = new wxButton(Panel3, ID_BUTTON1, _("All Lights Off"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(Button1, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
    FlexGridSizer2->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Notebook2 = new wxNotebook(Panel3, ID_NOTEBOOK2, wxDefaultPosition, wxSize(191,220), 0, _T("ID_NOTEBOOK2"));
    FlexGridSizer2->Add(Notebook2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Notebook1 = new wxNotebook(Panel3, ID_NOTEBOOK1, wxDefaultPosition, wxSize(281,220), 0, _T("ID_NOTEBOOK1"));
    Panel_Dim = new wxPanel(Notebook1, ID_PANEL1, wxPoint(29,39), wxSize(211,136), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    StaticText2 = new wxStaticText(Panel_Dim, ID_STATICTEXT2, _("Dim selected channels"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer1->Add(StaticText2, 0, wxTOP|wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 10);
    SliderMasterDimmer = new wxSlider(Panel_Dim, ID_SLIDER1, 0, 0, 255, wxDefaultPosition, wxSize(184,48), wxSL_HORIZONTAL|wxSL_AUTOTICKS|wxSL_LABELS|wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER1"));
    FlexGridSizer1->Add(SliderMasterDimmer, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    StaticText6 = new wxStaticText(Panel_Dim, ID_STATICTEXT6, _("Off"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    BoxSizer4->Add(StaticText6, 1, wxALL|wxSHAPED|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText11 = new wxStaticText(Panel_Dim, ID_STATICTEXT11, _("On"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    BoxSizer4->Add(StaticText11, 1, wxALL|wxSHAPED|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(BoxSizer4, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    Panel_Dim->SetSizer(FlexGridSizer1);
    FlexGridSizer1->SetSizeHints(Panel_Dim);
    Panel_Seq = new wxPanel(Notebook1, ID_PANEL2, wxPoint(71,15), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer3->AddGrowableCol(0);
    CheckBoxRunSeq = new wxCheckBox(Panel_Seq, ID_CHECKBOX_RUNSEQ, _("Run selected lights in sequence"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RUNSEQ"));
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
    FlexGridSizer3->Fit(Panel_Seq);
    FlexGridSizer3->SetSizeHints(Panel_Seq);
    Panel_Alt = new wxPanel(Notebook1, ID_PANEL3, wxPoint(114,11), wxSize(188,117), wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    CheckBoxRunAlt = new wxCheckBox(Panel_Alt, ID_CHECKBOX_RUNALT, _("Alternate selected lights (even/odd)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RUNALT"));
    CheckBoxRunAlt->SetValue(false);
    FlexGridSizer4->Add(CheckBoxRunAlt, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 10);
    StaticText7 = new wxStaticText(Panel_Alt, ID_STATICTEXT7, _("Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    wxFont StaticText7Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText7->SetFont(StaticText7Font);
    FlexGridSizer4->Add(StaticText7, 0, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 10);
    Slider3 = new wxSlider(Panel_Alt, ID_SLIDER3, 50, 0, 100, wxDefaultPosition, wxSize(184,24), wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER3"));
    FlexGridSizer4->Add(Slider3, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 10);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    StaticText8 = new wxStaticText(Panel_Alt, ID_STATICTEXT8, _("Slow"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    BoxSizer5->Add(StaticText8, 1, wxALL|wxSHAPED|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(Panel_Alt, ID_STATICTEXT9, _("Fast"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    BoxSizer5->Add(StaticText9, 1, wxALL|wxSHAPED|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(BoxSizer5, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    Panel_Alt->SetSizer(FlexGridSizer4);
    FlexGridSizer4->SetSizeHints(Panel_Alt);
    Panel1 = new wxPanel(Notebook1, ID_PANEL5, wxPoint(119,15), wxSize(271,194), wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    FlexGridSizer5 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer5->AddGrowableCol(0);
    CheckBoxRunTw = new wxCheckBox(Panel1, ID_CHECKBOX_RUNTW, _("Twinkle selected lights"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RUNTW"));
    CheckBoxRunTw->SetValue(false);
    FlexGridSizer5->Add(CheckBoxRunTw, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    RadioButtonTwNoFade = new wxRadioButton(Panel1, ID_RADIOBUTTON_TWNOFADE, _("No Fade"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON_TWNOFADE"));
    RadioButtonTwNoFade->SetValue(true);
    BoxSizer9->Add(RadioButtonTwNoFade, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonTwFade = new wxRadioButton(Panel1, ID_RADIOBUTTON_TWFADE, _("Fade In"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON_TWFADE"));
    BoxSizer9->Add(RadioButtonTwFade, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(BoxSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText12 = new wxStaticText(Panel1, ID_STATICTEXT12, _("Twinkle Rate"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    wxFont StaticText12Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText12->SetFont(StaticText12Font);
    FlexGridSizer5->Add(StaticText12, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText15 = new wxStaticText(Panel1, ID_STATICTEXT15, _("Not supported on LOR or D-Light networks"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    FlexGridSizer5->Add(StaticText15, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderTwRate = new wxSlider(Panel1, ID_SLIDER_TWRATE, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER_TWRATE"));
    FlexGridSizer5->Add(SliderTwRate, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    StaticText13 = new wxStaticText(Panel1, ID_STATICTEXT13, _("Slow"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    BoxSizer7->Add(StaticText13, 1, wxALL|wxSHAPED|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText14 = new wxStaticText(Panel1, ID_STATICTEXT14, _("Fast"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    BoxSizer7->Add(StaticText14, 1, wxALL|wxSHAPED|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(BoxSizer7, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    Panel1->SetSizer(FlexGridSizer5);
    FlexGridSizer5->SetSizeHints(Panel1);
    Panel2 = new wxPanel(Notebook1, ID_PANEL6, wxPoint(91,12), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
    FlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer6->AddGrowableCol(0);
    CheckBoxRunSh = new wxCheckBox(Panel2, ID_CHECKBOX_RUNSH, _("Shimmer selected lights"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RUNSH"));
    CheckBoxRunSh->SetValue(false);
    FlexGridSizer6->Add(CheckBoxRunSh, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    RadioButtonShNoFade = new wxRadioButton(Panel2, ID_RADIOBUTTON_SHNOFADE, _("No Fade"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON_SHNOFADE"));
    RadioButtonShNoFade->SetValue(true);
    BoxSizer10->Add(RadioButtonShNoFade, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonShFade = new wxRadioButton(Panel2, ID_RADIOBUTTON_SHFADE, _("Fade In"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON_SHFADE"));
    BoxSizer10->Add(RadioButtonShFade, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6->Add(BoxSizer10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText16 = new wxStaticText(Panel2, ID_STATICTEXT16, _("Shimmer Rate"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    wxFont StaticText16Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText16->SetFont(StaticText16Font);
    FlexGridSizer6->Add(StaticText16, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText17 = new wxStaticText(Panel2, ID_STATICTEXT17, _("Not supported on LOR or D-Light networks"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    FlexGridSizer6->Add(StaticText17, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderShRate = new wxSlider(Panel2, ID_SLIDER4, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER4"));
    FlexGridSizer6->Add(SliderShRate, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    StaticText18 = new wxStaticText(Panel2, ID_STATICTEXT18, _("Slow"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    BoxSizer11->Add(StaticText18, 1, wxALL|wxSHAPED|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText19 = new wxStaticText(Panel2, ID_STATICTEXT19, _("Fast"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    BoxSizer11->Add(StaticText19, 1, wxALL|wxSHAPED|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6->Add(BoxSizer11, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    Panel2->SetSizer(FlexGridSizer6);
    FlexGridSizer6->Fit(Panel2);
    FlexGridSizer6->SetSizeHints(Panel2);
    Notebook1->AddPage(Panel_Dim, _("Dim"), false);
    Notebook1->AddPage(Panel_Seq, _("Sequence"), false);
    Notebook1->AddPage(Panel_Alt, _("Alternate"), false);
    Notebook1->AddPage(Panel1, _("Twinkle"), false);
    Notebook1->AddPage(Panel2, _("Shimmer"), false);
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

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xTesterFrame::OnButton1Click);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnQuit);
    Connect(idMenuHelpContent,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnMenuItemHelpContentSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnAbout);
    //*)

    SetIcon(wxIcon(xlights_xpm));

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

xTesterFrame::~xTesterFrame()
{
    if (timer.IsRunning()) timer.Stop();
    //(*Destroy(xTesterFrame)
    //*)
}

void xTesterFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void xTesterFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _(XLIGHTS_LICENSE);
    wxString hdg = wxString::Format(_("About xLights %s"),_(XLIGHTS_VERSION));
    wxMessageBox(msg, hdg);
}

void xTesterFrame::OnTimer(wxTimerEvent& event) {
    static int LastNotebookSelection = -1;
    static int LastMasterDimValue;
    static int LastSequenceSpeed;
    static long NextSequenceStart = -1;
    static wxArrayInt chArray;
    static int interval;
    static unsigned int seqidx=9999,alt=0;
    int v,n,ch;
    unsigned int i;
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
    }
    switch (NotebookSelection) {
        case 0:
            // dimmer
            v=SliderMasterDimmer->GetValue();
            if (v != LastMasterDimValue) {
                for (ch=0,n=0; ch < maxch; ch++) {
                    if (lb->IsChecked(ch)) {
                        xout.SetIntensity(netidx, ch, v);
                        n++;
                    }
                }
                LastMasterDimValue = v;
                StatusBar1->SetStatusText(wxString::Format(_("Dimming %d channels to %d"),n,v));
            }
            break;
        case 1:
            // turn on in sequence
            if (CheckBoxRunSeq->IsChecked()) {
                if (LastSequenceSpeed == -1) {
                    // get list of checked channels
                    chArray.Clear();
                    for (ch=0; ch < maxch; ch++) {
                        if (lb->IsChecked(ch)) {
                            chArray.Add(ch);
                        }
                    }
                }
                v=Slider1->GetValue();  // 0-100
                if (v != LastSequenceSpeed) {
                    interval = 1600 - v*15;
                    if (seqidx < chArray.Count()) {
                        NextSequenceStart = curtime + interval;
                    }
                    LastSequenceSpeed = v;
                    StatusBar1->SetStatusText(wxString::Format(_("Turning on %d channels in sequence, speed=%d"),chArray.Count(),interval));
                }
                if (curtime >= NextSequenceStart && chArray.Count() > 0) {
                    if (seqidx < chArray.Count()) xout.off(netidx, chArray[seqidx]);
                    NextSequenceStart = curtime + interval;
                    seqidx++;
                    if (seqidx >= chArray.Count()) seqidx=0;
                    xout.SetIntensity(netidx, chArray[seqidx], MAXINTENSITY);
                }
            } else {
                LastSequenceSpeed=-1;
            }
            break;
        case 2:
            // alternate odd/even
            if (CheckBoxRunAlt->IsChecked()) {
                if (LastSequenceSpeed == -1) {
                    // get list of checked channels
                    chArray.Clear();
                    for (ch=0; ch < maxch; ch++) {
                        if (lb->IsChecked(ch)) {
                            chArray.Add(ch);
                        }
                    }
                }
                v=Slider3->GetValue();  // 0-100
                if (v != LastSequenceSpeed) {
                    interval = 1600 - v*15;
                    NextSequenceStart = curtime + interval;
                    LastSequenceSpeed = v;
                    StatusBar1->SetStatusText(wxString::Format(_("Alternating %d channels, speed=%d"),chArray.Count(),interval));
                }
                if (curtime >= NextSequenceStart) {
                    for (i=0; i < chArray.Count(); i++) {
                        v=(i % 2) ^ alt;
                        xout.SetIntensity(netidx, chArray[i], v * MAXINTENSITY);
                    }
                    NextSequenceStart = curtime + interval;
                    alt=1-alt;
                }
            } else {
                LastSequenceSpeed=-1;
            }
            break;
        case 3:
            // twinkle
            if (CheckBoxRunTw->IsChecked()) {
                if (LastSequenceSpeed == -1) {
                    // get list of checked channels
                    chArray.Clear();
                    for (ch=0; ch < maxch; ch++) {
                        if (lb->IsChecked(ch)) {
                            chArray.Add(ch);
                        }
                    }
                }
                v=SliderTwRate->GetValue();  // 0-100
                if (v != LastSequenceSpeed) {
                    interval = 2000 - v*15;
                    LastSequenceSpeed = v;
                    if (RadioButtonTwNoFade->GetValue()) {
                        for (i=0; i < chArray.Count(); i++) {
                            xout.twinkle(netidx, chArray[i], interval, MAXINTENSITY);
                        }
                    } else {
                        for (i=0; i < chArray.Count(); i++) {
                            xout.twinklefade(netidx, chArray[i], interval, 8000, 0, MAXINTENSITY);
                        }
                    }
                    StatusBar1->SetStatusText(wxString::Format(_("Twinkling %d channels, speed=%d"),chArray.Count(),interval));
                }
            } else {
                if (LastSequenceSpeed != -1) {
                    for (i=0; i < chArray.Count(); i++) {
                        xout.off(netidx, chArray[i]);
                    }
                    chArray.Clear();
                }
                LastSequenceSpeed=-1;
            }
            break;
        case 4:
            // shimmer
            if (CheckBoxRunSh->IsChecked()) {
                if (LastSequenceSpeed == -1) {
                    // get list of checked channels
                    chArray.Clear();
                    for (ch=0; ch < maxch; ch++) {
                        if (lb->IsChecked(ch)) {
                            chArray.Add(ch);
                        }
                    }
                }
                v=SliderShRate->GetValue();  // 0-100
                if (v != LastSequenceSpeed) {
                    interval = 450 - v*4;
                    LastSequenceSpeed = v;
                    if (RadioButtonShNoFade->GetValue()) {
                        for (i=0; i < chArray.Count(); i++) {
                            xout.shimmer(netidx, chArray[i], interval, MAXINTENSITY);
                        }
                    } else {
                        for (i=0; i < chArray.Count(); i++) {
                            xout.shimmerfade(netidx, chArray[i], interval, 8000, 0, MAXINTENSITY);
                        }
                    }
                    StatusBar1->SetStatusText(wxString::Format(_("Shimmering %d channels, speed=%d"),chArray.Count(),interval));
                }
            } else {
                if (LastSequenceSpeed != -1) {
                    for (i=0; i < chArray.Count(); i++) {
                        xout.off(netidx, chArray[i]);
                    }
                    chArray.Clear();
                }
                LastSequenceSpeed=-1;
            }
            break;
    }
    xout.TimerEnd();
    //StatusBar1->SetStatusText(ts.Format(_("%S.%l")));
}

void xTesterFrame::LoadFile()
{
    long MaxChan;
    wxXmlDocument doc;
    if (doc.Load( networkFile.GetFullPath() )) {
        wxXmlNode* e=doc.GetRoot();
        for( e=e->GetChildren(); e!=NULL; e=e->GetNext() ) {
            wxString tagname=e->GetName();
            if (tagname == wxT("network")) {
                wxString tempstr=e->GetPropVal(wxT("MaxChannels"), wxT("0"));
                tempstr.ToLong(&MaxChan);
                wxString NetworkType=e->GetPropVal(wxT("NetworkType"), wxT(""));
                wxString ComPort=e->GetPropVal(wxT("ComPort"), wxT(""));
                wxString BaudRate=e->GetPropVal(wxT("BaudRate"), wxT(""));
                AddNetwork(NetworkType,ComPort,BaudRate,MaxChan);
            }
        }
    } else {
        wxMessageBox(_("Unable to load network definition file"), _("Error"));
    }
}

NetworkInfo* xTesterFrame::AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels)
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
    int baud = atoi(BaudRate.mb_str(wxConvUTF8));
    try {
        if (net3 == _("LOR")) {
            xout.setnetwork(new xNetwork_LOR(),cnt,MaxChannels,ComPort,baud);
        } else if (net3 == _("Ren")) {
            xout.setnetwork(new xNetwork_Renard(),cnt,MaxChannels,ComPort,baud);
        } else if (net3 == _("DMX")) {
            xout.setnetwork(new xNetwork_DMXentec(),cnt,MaxChannels,ComPort,baud);
        }
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
    if (net3 == _("LOR")) {
        for (int i=0; i < MaxChannels; i++) {
            chNames.Add( wxString::Format(_T("Unit %d.%02d"), (i >> 4)+1, (i & 0x0F)+1 ));
        }
    } else {
        for (int i=1; i <= MaxChannels; i++) {
            chNames.Add( wxString::Format(_T("Channel %d"), i) );
        }
    }
    ListBox->Set(chNames);
    ListBox->Connect(wxEVT_COMMAND_CHECKLISTBOX_TOGGLED,(wxObjectEventFunction)&xTesterFrame::OnCheckboxToggle, NULL, this);

    return NetInfo;
}


void xTesterFrame::OnCheckboxToggle(wxCommandEvent& event)
{
    int netidx = Notebook2->GetSelection(); // which network
    wxCheckListBox* lb = Networks[netidx]->ListBox;
    int ChCount = lb->GetCount();
    int row=event.GetInt();
    bool newval=lb->IsChecked(row);
    if (RadioButton16->GetValue()) {
        for (int i=row+1; i <= row+15; i++) {
            if (i >= ChCount) break;
            lb->Check(i,newval);
        }
    } else if (RadioButtonAll->GetValue()) {
        for (int i=0; i < ChCount; i++) {
            lb->Check(i,newval);
        }
    }
    //StatusBar1->SetStatusText(newval ? _("true") : _("false"));
    //static int lastrow=0;

    // In wxWidgets 2.9/3.0:
    // test state of shift key using wxKeyboardState class
    // so that shift-click will select a range of checkboxes
}


void xTesterFrame::alloff()
{
    SliderMasterDimmer->SetValue(0);
    CheckBoxRunSeq->SetValue(false);
    CheckBoxRunAlt->SetValue(false);
    CheckBoxRunTw->SetValue(false);
    CheckBoxRunSh->SetValue(false);
    xout.alloff();
}


void xTesterFrame::OnButton1Click(wxCommandEvent& event)
{
    alloff();
    StatusBar1->SetStatusText(_("All lights off"));
}

void xTesterFrame::OnMenuItemHelpContentSelected(wxCommandEvent& event)
{
    if (!wxLaunchDefaultBrowser(_(XLIGHTS_HELP_URL)))
    {
        wxMessageBox(_("Help requires Internet access. Unable to access help."), _("Error"));
    }
}
