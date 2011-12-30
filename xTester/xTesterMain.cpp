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

#include <limits>
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

//(*IdInit(xTesterFrame)
const long xTesterFrame::ID_STATICTEXT1 = wxNewId();
const long xTesterFrame::ID_CHOICE_NUMSELECT = wxNewId();
const long xTesterFrame::ID_BUTTON_CLEAR = wxNewId();
const long xTesterFrame::ID_STATICTEXT3 = wxNewId();
const long xTesterFrame::ID_BUTTON_EXPORT = wxNewId();
const long xTesterFrame::ID_BUTTON1 = wxNewId();
const long xTesterFrame::ID_NOTEBOOK2 = wxNewId();
const long xTesterFrame::ID_STATICTEXT8 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON14 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON15 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON16 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON17 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON19 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON18 = wxNewId();
const long xTesterFrame::ID_STATICTEXT9 = wxNewId();
const long xTesterFrame::ID_SLIDER4 = wxNewId();
const long xTesterFrame::ID_STATICTEXT10 = wxNewId();
const long xTesterFrame::ID_SLIDER5 = wxNewId();
const long xTesterFrame::ID_STATICTEXT11 = wxNewId();
const long xTesterFrame::ID_SLIDER6 = wxNewId();
const long xTesterFrame::ID_PANEL3 = wxNewId();
const long xTesterFrame::ID_STATICTEXT7 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON9 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON6 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON7 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON8 = wxNewId();
const long xTesterFrame::ID_STATICTEXT12 = wxNewId();
const long xTesterFrame::ID_SLIDER_TWRATE = wxNewId();
const long xTesterFrame::ID_PANEL_TWINKLE = wxNewId();
const long xTesterFrame::ID_STATICTEXT29 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON1 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON2 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON3 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON4 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON25 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON5 = wxNewId();
const long xTesterFrame::ID_SLIDER12 = wxNewId();
const long xTesterFrame::ID_SLIDER11 = wxNewId();
const long xTesterFrame::ID_SLIDER1 = wxNewId();
const long xTesterFrame::ID_SLIDER14 = wxNewId();
const long xTesterFrame::ID_SLIDER13 = wxNewId();
const long xTesterFrame::ID_SLIDER9 = wxNewId();
const long xTesterFrame::ID_STATICTEXT4 = wxNewId();
const long xTesterFrame::ID_SLIDER2 = wxNewId();
const long xTesterFrame::ID_PANEL1 = wxNewId();
const long xTesterFrame::ID_STATICTEXT5 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON10 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON11 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON12 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON13 = wxNewId();
const long xTesterFrame::ID_SLIDER3 = wxNewId();
const long xTesterFrame::ID_SLIDER8 = wxNewId();
const long xTesterFrame::ID_SLIDER10 = wxNewId();
const long xTesterFrame::ID_PANEL2 = wxNewId();
const long xTesterFrame::ID_STATICTEXT2 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON20 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON22 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON23 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON24 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON21 = wxNewId();
const long xTesterFrame::ID_STATICTEXT13 = wxNewId();
const long xTesterFrame::ID_SLIDER7 = wxNewId();
const long xTesterFrame::ID_PANEL5 = wxNewId();
const long xTesterFrame::ID_STATICTEXT6 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON26 = wxNewId();
const long xTesterFrame::ID_RADIOBUTTON27 = wxNewId();
const long xTesterFrame::ID_LISTBOX_AUTOTEST = wxNewId();
const long xTesterFrame::ID_PANEL_AUTOTEST = wxNewId();
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
    wxStaticBoxSizer* StaticBoxSizer2;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer24;
    wxBoxSizer* BoxSizer10;
    wxMenuItem* MenuItem2;
    wxFlexGridSizer* FlexGridSizer10;
    wxFlexGridSizer* FlexGridSizer3;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer22;
    wxFlexGridSizer* FlexGridSizer9;
    wxFlexGridSizer* FlexGridSizer2;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxFlexGridSizer* FlexGridSizer7;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxFlexGridSizer* FlexGridSizer15;
    wxFlexGridSizer* FlexGridSizer18;
    wxFlexGridSizer* FlexGridSizer8;
    wxFlexGridSizer* FlexGridSizer21;
    wxFlexGridSizer* FlexGridSizer14;
    wxFlexGridSizer* FlexGridSizer20;
    wxBoxSizer* BoxSizer1;
    wxFlexGridSizer* FlexGridSizer13;
    wxFlexGridSizer* FlexGridSizer12;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer6;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer11;
    wxBoxSizer* BoxSizer3;
    wxFlexGridSizer* FlexGridSizer17;
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
    StaticText1 = new wxStaticText(Panel3, ID_STATICTEXT1, _("Selection mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer7->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ChoiceNumSelect = new wxChoice(Panel3, ID_CHOICE_NUMSELECT, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_NUMSELECT"));
    ChoiceNumSelect->SetSelection( ChoiceNumSelect->Append(_("1")) );
    ChoiceNumSelect->Append(_("16"));
    ChoiceNumSelect->Append(_("32"));
    ChoiceNumSelect->Append(_("64"));
    ChoiceNumSelect->Append(_("128"));
    ChoiceNumSelect->Append(_("3"));
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
    ChoiceNumSelect->Append(_("600"));
    ChoiceNumSelect->Append(_("1200"));
    ChoiceNumSelect->Append(_("1800"));
    ChoiceNumSelect->Append(_("2400"));
    ChoiceNumSelect->Append(_("3000"));
    ChoiceNumSelect->Append(_("All"));
    FlexGridSizer7->Add(ChoiceNumSelect, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonClear = new wxButton(Panel3, ID_BUTTON_CLEAR, _("Clear"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CLEAR"));
    FlexGridSizer7->Add(ButtonClear, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(FlexGridSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    StaticText3 = new wxStaticText(Panel3, ID_STATICTEXT3, _("Available Tests"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer2->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer17 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer17->AddGrowableCol(0);
    ButtonExport = new wxButton(Panel3, ID_BUTTON_EXPORT, _("Export"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_EXPORT"));
    ButtonExport->Hide();
    FlexGridSizer17->Add(ButtonExport, 1, wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    Button1 = new wxButton(Panel3, ID_BUTTON1, _("All Lights Off"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer17->Add(Button1, 0, wxALIGN_RIGHT|wxALIGN_TOP, 0);
    BoxSizer2->Add(FlexGridSizer17, 1, wxALL|wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Notebook2 = new wxNotebook(Panel3, ID_NOTEBOOK2, wxDefaultPosition, wxSize(225,220), 0, _T("ID_NOTEBOOK2"));
    FlexGridSizer2->Add(Notebook2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Notebook1 = new wxNotebook(Panel3, ID_NOTEBOOK1, wxDefaultPosition, wxSize(495,329), 0, _T("ID_NOTEBOOK1"));
    Panel2 = new wxPanel(Notebook1, ID_PANEL3, wxPoint(29,39), wxSize(211,136), wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer9->AddGrowableRow(0);
    FlexGridSizer10 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticText8 = new wxStaticText(Panel2, ID_STATICTEXT8, _("Select function:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    wxFont StaticText8Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText8->SetFont(StaticText8Font);
    FlexGridSizer10->Add(StaticText8, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonChaseOff = new wxRadioButton(Panel2, ID_RADIOBUTTON14, _("Off"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON14"));
    FlexGridSizer10->Add(RadioButtonChaseOff, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonChase = new wxRadioButton(Panel2, ID_RADIOBUTTON15, _("Chase"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON15"));
    FlexGridSizer10->Add(RadioButtonChase, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonChase3 = new wxRadioButton(Panel2, ID_RADIOBUTTON16, _("Chase 1/3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON16"));
    FlexGridSizer10->Add(RadioButtonChase3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonChase4 = new wxRadioButton(Panel2, ID_RADIOBUTTON17, _("Chase 1/4"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON17"));
    FlexGridSizer10->Add(RadioButtonChase4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonChase5 = new wxRadioButton(Panel2, ID_RADIOBUTTON19, _("Chase 1/5"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON19"));
    FlexGridSizer10->Add(RadioButtonChase5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonAlt = new wxRadioButton(Panel2, ID_RADIOBUTTON18, _("Alternate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON18"));
    FlexGridSizer10->Add(RadioButtonAlt, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer9->Add(FlexGridSizer10, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer9->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    FlexGridSizer20 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer20->AddGrowableCol(0);
    FlexGridSizer20->AddGrowableRow(1);
    StaticText9 = new wxStaticText(Panel2, ID_STATICTEXT9, _("Background\nIntensity"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    wxFont StaticText9Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText9->SetFont(StaticText9Font);
    FlexGridSizer20->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderBgIntensity = new wxSlider(Panel2, ID_SLIDER4, 0, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER4"));
    FlexGridSizer20->Add(SliderBgIntensity, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer3->Add(FlexGridSizer20, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer21 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer21->AddGrowableCol(0);
    FlexGridSizer21->AddGrowableRow(1);
    StaticText10 = new wxStaticText(Panel2, ID_STATICTEXT10, _("Chase\nIntensity"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    wxFont StaticText10Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText10->SetFont(StaticText10Font);
    FlexGridSizer21->Add(StaticText10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderFgIntensity = new wxSlider(Panel2, ID_SLIDER5, 255, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER5"));
    FlexGridSizer21->Add(SliderFgIntensity, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer3->Add(FlexGridSizer21, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer22 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer22->AddGrowableCol(0);
    FlexGridSizer22->AddGrowableRow(1);
    StaticText11 = new wxStaticText(Panel2, ID_STATICTEXT11, _("Chase\nSpeed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    wxFont StaticText11Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText11->SetFont(StaticText11Font);
    FlexGridSizer22->Add(StaticText11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderChaseSpeed = new wxSlider(Panel2, ID_SLIDER6, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER6"));
    FlexGridSizer22->Add(SliderChaseSpeed, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer3->Add(FlexGridSizer22, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer9->Add(BoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    Panel2->SetSizer(FlexGridSizer9);
    FlexGridSizer9->SetSizeHints(Panel2);
    PanelTwinkle = new wxPanel(Notebook1, ID_PANEL_TWINKLE, wxPoint(119,15), wxSize(271,194), wxTAB_TRAVERSAL, _T("ID_PANEL_TWINKLE"));
    FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer5->AddGrowableRow(0);
    FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticText7 = new wxStaticText(PanelTwinkle, ID_STATICTEXT7, _("Select function:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    wxFont StaticText7Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText7->SetFont(StaticText7Font);
    FlexGridSizer4->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonDimOff = new wxRadioButton(PanelTwinkle, ID_RADIOBUTTON9, _("Off"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON9"));
    FlexGridSizer4->Add(RadioButtonDimOff, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonDim = new wxRadioButton(PanelTwinkle, ID_RADIOBUTTON6, _("Dim"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON6"));
    FlexGridSizer4->Add(RadioButtonDim, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonTwinkle = new wxRadioButton(PanelTwinkle, ID_RADIOBUTTON7, _("Twinkle"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON7"));
    FlexGridSizer4->Add(RadioButtonTwinkle, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonShimmer = new wxRadioButton(PanelTwinkle, ID_RADIOBUTTON8, _("Shimmer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON8"));
    FlexGridSizer4->Add(RadioButtonShimmer, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(FlexGridSizer4, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer6->AddGrowableRow(1);
    StaticText12 = new wxStaticText(PanelTwinkle, ID_STATICTEXT12, _("Intensity"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    wxFont StaticText12Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText12->SetFont(StaticText12Font);
    FlexGridSizer6->Add(StaticText12, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderDimIntensity = new wxSlider(PanelTwinkle, ID_SLIDER_TWRATE, 255, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER_TWRATE"));
    FlexGridSizer6->Add(SliderDimIntensity, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(FlexGridSizer6, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    PanelTwinkle->SetSizer(FlexGridSizer5);
    FlexGridSizer5->SetSizeHints(PanelTwinkle);
    Panel_Dim = new wxPanel(Notebook1, ID_PANEL1, wxPoint(29,39), wxSize(211,136), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 5, 0, 0);
    FlexGridSizer1->AddGrowableRow(1);
    FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticText29 = new wxStaticText(Panel_Dim, ID_STATICTEXT29, _("Select function:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
    wxFont StaticText29Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText29->SetFont(StaticText29Font);
    FlexGridSizer3->Add(StaticText29, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonRgbChaseOff = new wxRadioButton(Panel_Dim, ID_RADIOBUTTON1, _("Off"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
    FlexGridSizer3->Add(RadioButtonRgbChaseOff, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonRgbChase = new wxRadioButton(Panel_Dim, ID_RADIOBUTTON2, _("Chase"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
    FlexGridSizer3->Add(RadioButtonRgbChase, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonRgbChase3 = new wxRadioButton(Panel_Dim, ID_RADIOBUTTON3, _("Chase 1/3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON3"));
    FlexGridSizer3->Add(RadioButtonRgbChase3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonRgbChase4 = new wxRadioButton(Panel_Dim, ID_RADIOBUTTON4, _("Chase 1/4"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON4"));
    FlexGridSizer3->Add(RadioButtonRgbChase4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonRgbChase5 = new wxRadioButton(Panel_Dim, ID_RADIOBUTTON25, _("Chase 1/5"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON25"));
    FlexGridSizer3->Add(RadioButtonRgbChase5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonRgbAlt = new wxRadioButton(Panel_Dim, ID_RADIOBUTTON5, _("Alternate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON5"));
    FlexGridSizer3->Add(RadioButtonRgbAlt, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer10 = new wxBoxSizer(wxVERTICAL);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, Panel_Dim, _("Background Color"));
    SliderBgColorA = new wxSlider(Panel_Dim, ID_SLIDER12, 0, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER12"));
    StaticBoxSizer1->Add(SliderBgColorA, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    SliderBgColorB = new wxSlider(Panel_Dim, ID_SLIDER11, 0, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER11"));
    StaticBoxSizer1->Add(SliderBgColorB, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    SliderBgColorC = new wxSlider(Panel_Dim, ID_SLIDER1, 0, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER1"));
    StaticBoxSizer1->Add(SliderBgColorC, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer10->Add(StaticBoxSizer1, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, Panel_Dim, _("Chase Color"));
    SliderFgColorA = new wxSlider(Panel_Dim, ID_SLIDER14, 255, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER14"));
    StaticBoxSizer2->Add(SliderFgColorA, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    SliderFgColorB = new wxSlider(Panel_Dim, ID_SLIDER13, 255, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER13"));
    StaticBoxSizer2->Add(SliderFgColorB, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    SliderFgColorC = new wxSlider(Panel_Dim, ID_SLIDER9, 255, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER9"));
    StaticBoxSizer2->Add(SliderFgColorC, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer10->Add(StaticBoxSizer2, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    FlexGridSizer1->Add(BoxSizer10, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer14 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer14->AddGrowableCol(0);
    FlexGridSizer14->AddGrowableRow(1);
    StaticText4 = new wxStaticText(Panel_Dim, ID_STATICTEXT4, _("Chase\nSpeed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    wxFont StaticText4Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText4->SetFont(StaticText4Font);
    FlexGridSizer14->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderRgbChaseSpeed = new wxSlider(Panel_Dim, ID_SLIDER2, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER2"));
    FlexGridSizer14->Add(SliderRgbChaseSpeed, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer1->Add(FlexGridSizer14, 1, wxALL|wxEXPAND|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    Panel_Dim->SetSizer(FlexGridSizer1);
    FlexGridSizer1->SetSizeHints(Panel_Dim);
    Panel1 = new wxPanel(Notebook1, ID_PANEL2, wxPoint(119,15), wxSize(271,194), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    FlexGridSizer13 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer13->AddGrowableRow(0);
    FlexGridSizer18 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticText5 = new wxStaticText(Panel1, ID_STATICTEXT5, _("Select function:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    wxFont StaticText5Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText5->SetFont(StaticText5Font);
    FlexGridSizer18->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonRgbDimOff = new wxRadioButton(Panel1, ID_RADIOBUTTON10, _("Off"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON10"));
    FlexGridSizer18->Add(RadioButtonRgbDimOff, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonRgbDim = new wxRadioButton(Panel1, ID_RADIOBUTTON11, _("Dim"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON11"));
    FlexGridSizer18->Add(RadioButtonRgbDim, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonRgbTwinkle = new wxRadioButton(Panel1, ID_RADIOBUTTON12, _("Twinkle"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON12"));
    FlexGridSizer18->Add(RadioButtonRgbTwinkle, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonRgbShimmer = new wxRadioButton(Panel1, ID_RADIOBUTTON13, _("Shimmer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON13"));
    FlexGridSizer18->Add(RadioButtonRgbShimmer, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer13->Add(FlexGridSizer18, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer13->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Set Color"));
    SliderDimColorA = new wxSlider(Panel1, ID_SLIDER3, 255, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER3"));
    StaticBoxSizer3->Add(SliderDimColorA, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 10);
    SliderDimColorB = new wxSlider(Panel1, ID_SLIDER8, 255, 0, 255, wxDefaultPosition, wxSize(65,180), wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER8"));
    StaticBoxSizer3->Add(SliderDimColorB, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 10);
    SliderDimColorC = new wxSlider(Panel1, ID_SLIDER10, 255, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER10"));
    StaticBoxSizer3->Add(SliderDimColorC, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 10);
    FlexGridSizer13->Add(StaticBoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer13);
    FlexGridSizer13->SetSizeHints(Panel1);
    Panel_RGB_Seq = new wxPanel(Notebook1, ID_PANEL5, wxPoint(71,15), wxSize(392,209), wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    FlexGridSizer11 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer11->AddGrowableRow(0);
    FlexGridSizer15 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticText2 = new wxStaticText(Panel_RGB_Seq, ID_STATICTEXT2, _("Select function:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    wxFont StaticText2Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    FlexGridSizer15->Add(StaticText2, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonRgbCycleOff = new wxRadioButton(Panel_RGB_Seq, ID_RADIOBUTTON20, _("Off"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON20"));
    FlexGridSizer15->Add(RadioButtonRgbCycleOff, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonRgbCycle3 = new wxRadioButton(Panel_RGB_Seq, ID_RADIOBUTTON22, _("A-B-C"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON22"));
    FlexGridSizer15->Add(RadioButtonRgbCycle3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonRgbCycle4 = new wxRadioButton(Panel_RGB_Seq, ID_RADIOBUTTON23, _("A-B-C-All"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON23"));
    FlexGridSizer15->Add(RadioButtonRgbCycle4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonRgbCycle5 = new wxRadioButton(Panel_RGB_Seq, ID_RADIOBUTTON24, _("A-B-C-All-None"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON24"));
    FlexGridSizer15->Add(RadioButtonRgbCycle5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonRgbCycleMixed = new wxRadioButton(Panel_RGB_Seq, ID_RADIOBUTTON21, _("Mixed Colors"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON21"));
    FlexGridSizer15->Add(RadioButtonRgbCycleMixed, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer11->Add(FlexGridSizer15, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer11->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer24 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer24->AddGrowableRow(1);
    StaticText13 = new wxStaticText(Panel_RGB_Seq, ID_STATICTEXT13, _("Cycle Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    wxFont StaticText13Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText13->SetFont(StaticText13Font);
    FlexGridSizer24->Add(StaticText13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderRgbCycleSpeed = new wxSlider(Panel_RGB_Seq, ID_SLIDER7, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER7"));
    FlexGridSizer24->Add(SliderRgbCycleSpeed, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    FlexGridSizer11->Add(FlexGridSizer24, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel_RGB_Seq->SetSizer(FlexGridSizer11);
    FlexGridSizer11->SetSizeHints(Panel_RGB_Seq);
    PanelAutoTest = new wxPanel(Notebook1, ID_PANEL_AUTOTEST, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_AUTOTEST"));
    FlexGridSizer8 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer8->AddGrowableRow(1);
    FlexGridSizer12 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticText6 = new wxStaticText(PanelAutoTest, ID_STATICTEXT6, _("Select function:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    wxFont StaticText6Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText6->SetFont(StaticText6Font);
    FlexGridSizer12->Add(StaticText6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonAutoOff = new wxRadioButton(PanelAutoTest, ID_RADIOBUTTON26, _("Off"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON26"));
    FlexGridSizer12->Add(RadioButtonAutoOff, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadioButtonAutoOn = new wxRadioButton(PanelAutoTest, ID_RADIOBUTTON27, _("Run Automated Test"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON27"));
    FlexGridSizer12->Add(RadioButtonAutoOn, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer8->Add(FlexGridSizer12, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer8->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ListBoxAutoTest = new wxListBox(PanelAutoTest, ID_LISTBOX_AUTOTEST, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX_AUTOTEST"));
    ListBoxAutoTest->Append(_("Intensity 100%"));
    ListBoxAutoTest->Append(_("Intensity 50%"));
    ListBoxAutoTest->Append(_("Twinkle 100%"));
    ListBoxAutoTest->Append(_("Twinkle 50%"));
    ListBoxAutoTest->Append(_("Shimmer 100%"));
    ListBoxAutoTest->Append(_("Shimmer 50%"));
    ListBoxAutoTest->Append(_("Ramp 0% to 100%"));
    ListBoxAutoTest->Append(_("Ramp 100% to 0%"));
    ListBoxAutoTest->Append(_("Twinkle Ramp 0% to 100%"));
    ListBoxAutoTest->Append(_("Twinkle Ramp 100% to 0%"));
    ListBoxAutoTest->Append(_("Shimmer Ramp 0% to 100%"));
    ListBoxAutoTest->Append(_("Shimmer Ramp 100% to 0%"));
    ListBoxAutoTest->Disable();
    FlexGridSizer8->Add(ListBoxAutoTest, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 10);
    PanelAutoTest->SetSizer(FlexGridSizer8);
    FlexGridSizer8->Fit(PanelAutoTest);
    FlexGridSizer8->SetSizeHints(PanelAutoTest);
    Notebook1->AddPage(Panel2, _("Chase"), false);
    Notebook1->AddPage(PanelTwinkle, _("Dim/Tw/Sh"), false);
    Notebook1->AddPage(Panel_Dim, _("RGB Chase"), false);
    Notebook1->AddPage(Panel1, _("RGB Dim/Tw/Sh"), false);
    Notebook1->AddPage(Panel_RGB_Seq, _("RGB Cycle"), false);
    Notebook1->AddPage(PanelAutoTest, _("Automated"), false);
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

    Connect(ID_BUTTON_CLEAR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xTesterFrame::OnButtonClearClick);
    Connect(ID_BUTTON_EXPORT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xTesterFrame::OnButtonExportClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xTesterFrame::OnButton1Click);
    Connect(ID_RADIOBUTTON14,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonOffSelect);
    Connect(ID_RADIOBUTTON15,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonChaseSelect);
    Connect(ID_RADIOBUTTON16,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonChase3Select);
    Connect(ID_RADIOBUTTON17,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonChase4Select);
    Connect(ID_RADIOBUTTON19,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonChase5Select);
    Connect(ID_RADIOBUTTON18,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonAltSelect);
    Connect(ID_RADIOBUTTON9,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonOffSelect);
    Connect(ID_RADIOBUTTON6,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonDimSelect);
    Connect(ID_RADIOBUTTON7,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonTwinkleSelect);
    Connect(ID_RADIOBUTTON8,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonShimmerSelect);
    Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonOffSelect);
    Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonChaseSelect);
    Connect(ID_RADIOBUTTON3,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonChase3Select);
    Connect(ID_RADIOBUTTON4,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonChase4Select);
    Connect(ID_RADIOBUTTON25,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonChase5Select);
    Connect(ID_RADIOBUTTON5,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonAltSelect);
    Connect(ID_RADIOBUTTON10,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonOffSelect);
    Connect(ID_RADIOBUTTON11,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonDimSelect);
    Connect(ID_RADIOBUTTON12,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonTwinkleSelect);
    Connect(ID_RADIOBUTTON13,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonShimmerSelect);
    Connect(ID_RADIOBUTTON20,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonOffSelect);
    Connect(ID_RADIOBUTTON22,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonChase3Select);
    Connect(ID_RADIOBUTTON23,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonChase4Select);
    Connect(ID_RADIOBUTTON24,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonChase5Select);
    Connect(ID_RADIOBUTTON21,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonDimSelect);
    Connect(ID_RADIOBUTTON26,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonOffSelect);
    Connect(ID_RADIOBUTTON27,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnRadioButtonDimSelect);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnQuit);
    Connect(idMenuHelpContent,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnMenuItemHelpContentSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnAbout);
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

    CheckChannelList = true;
    if (Networks.Count() > 0) {
        timer.Start(XTIMER_INTERVAL, wxTIMER_CONTINUOUS);
    }
}

xTesterFrame::~xTesterFrame()
{
    if (timer.IsRunning()) timer.Stop();
    WX_CLEAR_ARRAY(Networks);
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
    static int LastBgIntensity,LastFgIntensity,LastBgColor[3],LastFgColor[3];
    static int LastSequenceSpeed;
    static int LastAutomatedTest;
    static long NextSequenceStart = -1;
    static TestFunctions LastFunc = OFF;
    static unsigned int interval, rgbCycle, seqidx;
    static wxArrayInt chArray,TwinkleState;
    static float frequency;
	static int twinkleperiod = 400;
    int v,ch,BgIntensity,FgIntensity,BgColor[3],FgColor[3];
    unsigned int i;
    bool ColorChange;
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
        CheckChannelList = true;
        seqidx=0;
        alloff();
    }
    if (TestFunc != LastFunc) {
        LastFunc = TestFunc;
        rgbCycle=0;
        CheckChannelList = true;
    }

    if (CheckChannelList) {
        // get list of checked channels
        xout.alloff();
        chArray.Clear();
        for (ch=0; ch < maxch; ch++) {
            if (lb->IsChecked(ch)) {
                chArray.Add(ch);
            }
        }
        LastSequenceSpeed=-1;
        LastBgIntensity=-1;
        LastFgIntensity=-1;
        LastAutomatedTest=-1;
        for (i=0; i < 3; i++) {
            LastBgColor[i] = -1;
            LastFgColor[i] = -1;
        }
        CheckChannelList = false;
    }

    if (TestFunc != OFF && chArray.Count() > 0) switch (NotebookSelection) {
        case 0:
            // chase
            v=SliderChaseSpeed->GetValue();  // 0-100
            BgIntensity = SliderBgIntensity->GetValue();
            FgIntensity = SliderFgIntensity->GetValue();

            if (v != LastSequenceSpeed) {
                interval = 1600 - v*15;
                NextSequenceStart = curtime + interval;
                LastSequenceSpeed = v;
                StatusBar1->SetStatusText(wxString::Format(_("Chasing %d channels, speed=%d"),chArray.Count(),interval));
            }
            if (curtime >= NextSequenceStart || BgIntensity != LastBgIntensity || FgIntensity != LastFgIntensity) {
                for (i=0; i < chArray.Count(); i++) {
                    v = (i % ChaseGrouping) == seqidx ? FgIntensity : BgIntensity;
                    xout.SetIntensity(netidx, chArray[i], v);
                }
                LastBgIntensity = BgIntensity;
                LastFgIntensity = FgIntensity;
                if (curtime >= NextSequenceStart) {
                    NextSequenceStart = curtime + interval;
                    seqidx = (seqidx + 1) % ChaseGrouping;
                    if (seqidx >= chArray.Count()) seqidx=0;
                }
            }
            break;

        case 1:
            // dim, twinkle, shimmer
            v=SliderDimIntensity->GetValue();
            if (v != LastBgIntensity) {
                switch (TestFunc) {
                    case DIM:
                        for (i=0; i < chArray.Count(); i++) {
                            xout.SetIntensity(netidx, chArray[i], v);
                        }
                        StatusBar1->SetStatusText(wxString::Format(_("Dimming %d channels to %d"),chArray.Count(),v));
                        break;
                    case TWINKLE:
                        for (i=0; i < chArray.Count(); i++) {
                            xout.twinkle(netidx, chArray[i], TWINKLE_PERIOD, v);
                        }
                        StatusBar1->SetStatusText(wxString::Format(_("Twinkling %d channels, intensity=%d"),chArray.Count(),v));
                        break;
                    case SHIMMER:
                        for (i=0; i < chArray.Count(); i++) {
                            xout.shimmer(netidx, chArray[i], SHIMMER_PERIOD, v);
                        }
                        StatusBar1->SetStatusText(wxString::Format(_("Shimmering %d channels, intensity=%d"),chArray.Count(),v));
                        break;
                    default: break;
                }
                LastBgIntensity = v;
            }
            break;

        case 2:
            // RGB chase
            v=SliderRgbChaseSpeed->GetValue();  // 0-100
            BgColor[0] = SliderBgColorA->GetValue();
            BgColor[1] = SliderBgColorB->GetValue();
            BgColor[2] = SliderBgColorC->GetValue();
            FgColor[0] = SliderFgColorA->GetValue();
            FgColor[1] = SliderFgColorB->GetValue();
            FgColor[2] = SliderFgColorC->GetValue();

            if (v != LastSequenceSpeed) {
                interval = 1600 - v*15;
                NextSequenceStart = curtime + interval;
                LastSequenceSpeed = v;
                StatusBar1->SetStatusText(wxString::Format(_("RGB Chasing %d channels, speed=%d"),chArray.Count(),interval));
            }
            for (ColorChange=false,i=0; i < 3; i++) {
                ColorChange |= (BgColor[i] != LastBgColor[i]);
                ColorChange |= (FgColor[i] != LastFgColor[i]);
            }
            if (curtime >= NextSequenceStart || ColorChange) {
                for (i=0; i < chArray.Count(); i++) {
                    v = (i / 3 % ChaseGrouping) == seqidx ? FgColor[i % 3] : BgColor[i % 3];
                    xout.SetIntensity(netidx, chArray[i], v);
                }
                for (i=0; i < 3; i++) {
                    LastBgColor[i] = BgColor[i];
                    LastFgColor[i] = FgColor[i];
                }
                if (curtime >= NextSequenceStart) {
                    NextSequenceStart = curtime + interval;
                    seqidx = (seqidx + 1) % ChaseGrouping;
                    if (seqidx >= (chArray.Count()+2) / 3) seqidx=0;
                }
            }
            break;

        case 3:
            // RGB dim, twinkle, shimmer
            BgColor[0]=SliderDimColorA->GetValue();
            BgColor[1]=SliderDimColorB->GetValue();
            BgColor[2]=SliderDimColorC->GetValue();
            switch (TestFunc) {
                case DIM:
                    for (ColorChange=false,i=0; i < 3; i++) {
                        ColorChange |= (BgColor[i] != LastBgColor[i]);
                    }
                    if (ColorChange) {
                        for (i=0; i < chArray.Count(); i++) {
                            xout.SetIntensity(netidx, chArray[i], BgColor[i % 3]);
                        }
                        StatusBar1->SetStatusText(wxString::Format(_("RGB Dimming %d channels"),chArray.Count()));
                        for (i=0; i < 3; i++) {
                            LastBgColor[i] = BgColor[i];
                        }
                    }
                    break;

                case TWINKLE:
                    if (LastSequenceSpeed < 0) {
                        StatusBar1->SetStatusText(wxString::Format(_("RGB Twinkling %d channels"),chArray.Count()));
                        LastSequenceSpeed=0;
                        TwinkleState.Clear();
                        for (i=0; i < chArray.Count(); i+=3) {
                            TwinkleState.Add(static_cast<int>(rand01()*2.0) * 2 - 1);  // +1 or -1
                        }
                    }
                    for (i=0; i < TwinkleState.Count(); i++) {
                        if (TwinkleState[i] < -1) {
                            // off
                            TwinkleState[i]++;
                        } else if (TwinkleState[i] > 1) {
                            // on
                            TwinkleState[i]--;
                        } else if (TwinkleState[i] == -1) {
                            // was off, now turn on for random period
                            TwinkleState[i]=static_cast<int>(rand01()*twinkleperiod+100) / XTIMER_INTERVAL;
                            seqidx = i * 3;
                            xout.SetIntensity(netidx, seqidx, BgColor[0]);
                            xout.SetIntensity(netidx, seqidx+1, BgColor[1]);
                            xout.SetIntensity(netidx, seqidx+2, BgColor[2]);
                        } else {
                            // was on, now turn off for random period
                            TwinkleState[i]=-static_cast<int>(rand01()*twinkleperiod+100) / XTIMER_INTERVAL;
                            seqidx = i * 3;
                            xout.SetIntensity(netidx, seqidx, 0);
                            xout.SetIntensity(netidx, seqidx+1, 0);
                            xout.SetIntensity(netidx, seqidx+2, 0);
                        }
                    }
                    break;
                case SHIMMER:
                    if (LastSequenceSpeed < 0) {
                        StatusBar1->SetStatusText(wxString::Format(_("RGB Shimmering %d channels"),chArray.Count()));
                        LastSequenceSpeed=0;
                    }
                    seqidx = seqidx == 0 ? 1 : 0;
                    for (i=0; i < chArray.Count(); i++) {
                        xout.SetIntensity(netidx, chArray[i], BgColor[i % 3] * seqidx);
                    }
                    break;
                default: break;
            }
            break;

        case 4:
            // RGB Cycle
            v=SliderRgbCycleSpeed->GetValue();  // 0-100
            if (TestFunc == DIM) {
                // color mixing
                if (v != LastSequenceSpeed) {
                    frequency=v/1000.0 + 0.05;
                    StatusBar1->SetStatusText(wxString::Format(_("Color Cycle, speed=%d"),v));
                    LastSequenceSpeed = v;
                }
                BgColor[0] = sin(frequency*seqidx + 0.0) * 127 + 128;
                BgColor[1] = sin(frequency*seqidx + 2.0) * 127 + 128;
                BgColor[2] = sin(frequency*seqidx + 4.0) * 127 + 128;
                seqidx++;
                for (i=0; i < chArray.Count(); i++) {
                    xout.SetIntensity(netidx, chArray[i], BgColor[i % 3]);
                }
            } else {
                // RGB cycle
                if (v != LastSequenceSpeed) {
                    interval = 1600 - v*15;
                    NextSequenceStart = curtime + interval;
                    LastSequenceSpeed = v;
                    StatusBar1->SetStatusText(wxString::Format(_("Turning on channels in RGB sequence, speed=%d"),interval));
                }
                if (curtime >= NextSequenceStart) {
                    for (i=0; i < chArray.Count(); i++) {
                        switch (rgbCycle) {
                            case 3: v=MAXINTENSITY; break;
                            default: v = (i % 3) == rgbCycle ? MAXINTENSITY : 0; break;
                        }
                        xout.SetIntensity(netidx, chArray[i], v);
                    }
                    rgbCycle=(rgbCycle + 1) % ChaseGrouping;
                    NextSequenceStart += interval;
                }
            }
            break;

        case 5:
            // automated test
            interval = 3000;  // 3 seconds per test
            if (LastAutomatedTest == -1) {
                seqidx=99;  // test #
                NextSequenceStart = curtime;
                ListBoxAutoTest->Enable(true);
            }
            if (curtime < NextSequenceStart) break;
            NextSequenceStart = curtime + interval + 1500; // allow time between tests
            seqidx++;
            if (seqidx >= ListBoxAutoTest->GetCount()) seqidx=0;
            LastAutomatedTest=seqidx;
            ListBoxAutoTest->Select(seqidx);
            switch (seqidx) {
                case 0:
                    // intensity 100%
                    for (i=0; i < chArray.Count(); i++) {
                        xout.SetIntensity(netidx, chArray[i], MAXINTENSITY);
                    }
                    break;
                case 1:
                    // intensity 50%
                    for (i=0; i < chArray.Count(); i++) {
                        xout.SetIntensity(netidx, chArray[i], MAXINTENSITY/2);
                    }
                    break;
                case 2:
                    // twinkle 100%
                    for (i=0; i < chArray.Count(); i++) {
                        xout.twinkle(netidx, chArray[i], TWINKLE_PERIOD, MAXINTENSITY);
                    }
                    break;
                case 3:
                    // twinkle 50%
                    for (i=0; i < chArray.Count(); i++) {
                        xout.twinkle(netidx, chArray[i], TWINKLE_PERIOD, MAXINTENSITY/2);
                    }
                    break;
                case 4:
                    // shimmer 100%
                    for (i=0; i < chArray.Count(); i++) {
                        xout.shimmer(netidx, chArray[i], SHIMMER_PERIOD, MAXINTENSITY);
                    }
                    break;
                case 5:
                    // shimmer 50%
                    for (i=0; i < chArray.Count(); i++) {
                        xout.shimmer(netidx, chArray[i], SHIMMER_PERIOD, MAXINTENSITY/2);
                    }
                    break;
                case 6:
                    // ramp 0% to 100%
                    for (i=0; i < chArray.Count(); i++) {
                        xout.ramp(netidx, chArray[i], interval, 0, MAXINTENSITY);
                    }
                    break;
                case 7:
                    // ramp 100% to 0%
                    for (i=0; i < chArray.Count(); i++) {
                        xout.ramp(netidx, chArray[i], interval, MAXINTENSITY, 0);
                    }
                    break;
                case 8:
                    // twinkle ramp 0% to 100%
                    for (i=0; i < chArray.Count(); i++) {
                        xout.twinklefade(netidx, chArray[i], TWINKLE_PERIOD, interval, 0, MAXINTENSITY);
                    }
                    break;
                case 9:
                    // twinkle ramp 100% to 0%
                    for (i=0; i < chArray.Count(); i++) {
                        xout.twinklefade(netidx, chArray[i], TWINKLE_PERIOD, interval, MAXINTENSITY, 0);
                    }
                    break;
                case 10:
                    // shimmer ramp 0% to 100%
                    for (i=0; i < chArray.Count(); i++) {
                        xout.shimmerfade(netidx, chArray[i], SHIMMER_PERIOD, interval, 0, MAXINTENSITY);
                    }
                    break;
                case 11:
                    // shimmer ramp 100% to 0%
                    for (i=0; i < chArray.Count(); i++) {
                        xout.shimmerfade(netidx, chArray[i], SHIMMER_PERIOD, interval, MAXINTENSITY, 0);
                    }
                    break;
            }
            break;
    }
    xout.TimerEnd();
    wxLogTrace(wxT("xout"),wxT("Ending OnTimer"));
    //StatusBar1->SetStatusText(ts.Format(_("%S.%l")));
}

// return a random number between 0 and 1 inclusive
double xTesterFrame::rand01()
{
    return (double)rand()/(double)RAND_MAX;
}

void xTesterFrame::LoadFile()
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
    int baud = (BaudRate == _("n/a")) ? 230400 : atoi(BaudRate.mb_str(wxConvUTF8));
    try {
        xout.addnetwork(net3,MaxChannels,ComPort,baud);
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
    CheckChannelList = true;
    //StatusBar1->SetStatusText(newval ? _("true") : _("false"));
    //static int lastrow=0;

    // In wxWidgets 2.9/3.0:
    // test state of shift key using wxKeyboardState class
    // so that shift-click will select a range of checkboxes
}


void xTesterFrame::alloff()
{
    RadioButtonChaseOff->SetValue(true);
    RadioButtonChase->SetValue(false);
    RadioButtonChase3->SetValue(false);
    RadioButtonChase4->SetValue(false);
    RadioButtonChase5->SetValue(false);
    RadioButtonAlt->SetValue(false);

    RadioButtonDimOff->SetValue(true);
    RadioButtonDim->SetValue(false);
    RadioButtonTwinkle->SetValue(false);
    RadioButtonShimmer->SetValue(false);

    RadioButtonRgbChaseOff->SetValue(true);
    RadioButtonRgbChase->SetValue(false);
    RadioButtonRgbChase3->SetValue(false);
    RadioButtonRgbChase4->SetValue(false);
    RadioButtonRgbChase5->SetValue(false);
    RadioButtonRgbAlt->SetValue(false);

    RadioButtonRgbDimOff->SetValue(true);
    RadioButtonRgbDim->SetValue(false);
    RadioButtonRgbTwinkle->SetValue(false);
    RadioButtonRgbShimmer->SetValue(false);

    RadioButtonRgbCycleOff->SetValue(true);
    RadioButtonRgbCycle3->SetValue(false);
    RadioButtonRgbCycle4->SetValue(false);
    RadioButtonRgbCycle5->SetValue(false);
    RadioButtonRgbCycleMixed->SetValue(false);

    RadioButtonAutoOff->SetValue(true);
    RadioButtonAutoOn->SetValue(false);

    xout.alloff();
    TestFunc=OFF;
    StatusBar1->SetStatusText(_("All lights off"));
}


void xTesterFrame::OnButton1Click(wxCommandEvent& event)
{
    alloff();
    //wxLog::ClearTraceMasks();
}

void xTesterFrame::OnMenuItemHelpContentSelected(wxCommandEvent& event)
{
    if (!wxLaunchDefaultBrowser(_(XLIGHTS_HELP_URL)))
    {
        wxMessageBox(_("Help requires Internet access. Unable to access help."), _("Error"));
    }
}

void xTesterFrame::OnButtonExportClick(wxCommandEvent& event)
{
    wxMessageBox(_("Export not implemented yet"), _("Export"));
}

void xTesterFrame::OnButtonClearClick(wxCommandEvent& event)
{
    int netidx = Notebook2->GetSelection(); // which network
    wxCheckListBox* lb = Networks[netidx]->ListBox;
    int ChCount = lb->GetCount();
    for (int i=0; i < ChCount; i++) {
        lb->Check(i,false);
    }
    CheckChannelList = true;
}

void xTesterFrame::OnRadioButtonOffSelect(wxCommandEvent& event)
{
    TestFunc=OFF;
}

void xTesterFrame::OnRadioButtonChaseSelect(wxCommandEvent& event)
{
    TestFunc=CHASE;
    ChaseGrouping=std::numeric_limits<int>::max();
}

void xTesterFrame::OnRadioButtonAltSelect(wxCommandEvent& event)
{
    TestFunc=CHASE;
    ChaseGrouping=2;
}

void xTesterFrame::OnRadioButtonChase3Select(wxCommandEvent& event)
{
    TestFunc=CHASE;
    ChaseGrouping=3;
}

void xTesterFrame::OnRadioButtonChase4Select(wxCommandEvent& event)
{
    TestFunc=CHASE;
    ChaseGrouping=4;
}

void xTesterFrame::OnRadioButtonChase5Select(wxCommandEvent& event)
{
    TestFunc=CHASE;
    ChaseGrouping=5;
}

void xTesterFrame::OnRadioButtonDimSelect(wxCommandEvent& event)
{
    TestFunc=DIM;
}

void xTesterFrame::OnRadioButtonTwinkleSelect(wxCommandEvent& event)
{
    TestFunc=TWINKLE;
}

void xTesterFrame::OnRadioButtonShimmerSelect(wxCommandEvent& event)
{
    TestFunc=SHIMMER;
}

