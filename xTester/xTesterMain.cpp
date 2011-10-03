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
const long xTesterFrame::ID_STATICTEXT12 = wxNewId();
const long xTesterFrame::ID_SLIDER_TWRATE = wxNewId();
const long xTesterFrame::ID_STATICTEXT13 = wxNewId();
const long xTesterFrame::ID_STATICTEXT14 = wxNewId();
const long xTesterFrame::ID_PANEL_TWINKLE = wxNewId();
const long xTesterFrame::ID_CHECKBOX_RUNSH = wxNewId();
const long xTesterFrame::ID_STATICTEXT16 = wxNewId();
const long xTesterFrame::ID_SLIDER4 = wxNewId();
const long xTesterFrame::ID_STATICTEXT18 = wxNewId();
const long xTesterFrame::ID_STATICTEXT19 = wxNewId();
const long xTesterFrame::ID_PANEL_SHIMMER = wxNewId();
const long xTesterFrame::ID_CHECKBOX_AUTO = wxNewId();
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
    wxBoxSizer* BoxSizer4;
    wxFlexGridSizer* FlexGridSizer4;
    wxBoxSizer* BoxSizer5;
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
    wxFlexGridSizer* FlexGridSizer8;
    wxBoxSizer* BoxSizer1;
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
    StaticText1 = new wxStaticText(Panel3, ID_STATICTEXT1, _("Selection mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer7->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ChoiceNumSelect = new wxChoice(Panel3, ID_CHOICE_NUMSELECT, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_NUMSELECT"));
    ChoiceNumSelect->SetSelection( ChoiceNumSelect->Append(_("1")) );
    ChoiceNumSelect->Append(_("16"));
    ChoiceNumSelect->Append(_("32"));
    ChoiceNumSelect->Append(_("60"));
    ChoiceNumSelect->Append(_("64"));
    ChoiceNumSelect->Append(_("100"));
    ChoiceNumSelect->Append(_("150"));
    ChoiceNumSelect->Append(_("225"));
    ChoiceNumSelect->Append(_("300"));
    ChoiceNumSelect->Append(_("All"));
    FlexGridSizer7->Add(ChoiceNumSelect, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(FlexGridSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    StaticText3 = new wxStaticText(Panel3, ID_STATICTEXT3, _("Available Tests"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer2->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button1 = new wxButton(Panel3, ID_BUTTON1, _("All Lights Off"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(Button1, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
    FlexGridSizer2->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Notebook2 = new wxNotebook(Panel3, ID_NOTEBOOK2, wxDefaultPosition, wxSize(225,220), 0, _T("ID_NOTEBOOK2"));
    FlexGridSizer2->Add(Notebook2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Notebook1 = new wxNotebook(Panel3, ID_NOTEBOOK1, wxDefaultPosition, wxSize(400,220), 0, _T("ID_NOTEBOOK1"));
    Panel_Dim = new wxPanel(Notebook1, ID_PANEL1, wxPoint(29,39), wxSize(211,136), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    StaticText2 = new wxStaticText(Panel_Dim, ID_STATICTEXT2, _("Dim selected channels"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer1->Add(StaticText2, 0, wxTOP|wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 10);
    SliderMasterDimmer = new wxSlider(Panel_Dim, ID_SLIDER1, 0, 0, 255, wxDefaultPosition, wxSize(184,48), wxSL_HORIZONTAL|wxSL_LABELS|wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER1"));
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
    PanelTwinkle = new wxPanel(Notebook1, ID_PANEL_TWINKLE, wxPoint(119,15), wxSize(271,194), wxTAB_TRAVERSAL, _T("ID_PANEL_TWINKLE"));
    FlexGridSizer5 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer5->AddGrowableCol(0);
    CheckBoxRunTw = new wxCheckBox(PanelTwinkle, ID_CHECKBOX_RUNTW, _("Twinkle selected lights"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RUNTW"));
    CheckBoxRunTw->SetValue(false);
    FlexGridSizer5->Add(CheckBoxRunTw, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 10);
    StaticText12 = new wxStaticText(PanelTwinkle, ID_STATICTEXT12, _("Twinkle Dimmer"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    wxFont StaticText12Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText12->SetFont(StaticText12Font);
    FlexGridSizer5->Add(StaticText12, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderTwIntensity = new wxSlider(PanelTwinkle, ID_SLIDER_TWRATE, 255, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_LABELS|wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER_TWRATE"));
    FlexGridSizer5->Add(SliderTwIntensity, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    StaticText13 = new wxStaticText(PanelTwinkle, ID_STATICTEXT13, _("Off"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    BoxSizer7->Add(StaticText13, 1, wxALL|wxSHAPED|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText14 = new wxStaticText(PanelTwinkle, ID_STATICTEXT14, _("On"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    BoxSizer7->Add(StaticText14, 1, wxALL|wxSHAPED|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(BoxSizer7, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    PanelTwinkle->SetSizer(FlexGridSizer5);
    FlexGridSizer5->SetSizeHints(PanelTwinkle);
    PanelShimmer = new wxPanel(Notebook1, ID_PANEL_SHIMMER, wxPoint(91,12), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_SHIMMER"));
    FlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer6->AddGrowableCol(0);
    CheckBoxRunSh = new wxCheckBox(PanelShimmer, ID_CHECKBOX_RUNSH, _("Shimmer selected lights"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RUNSH"));
    CheckBoxRunSh->SetValue(false);
    FlexGridSizer6->Add(CheckBoxRunSh, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 10);
    StaticText16 = new wxStaticText(PanelShimmer, ID_STATICTEXT16, _("Shimmer Dimmer"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    wxFont StaticText16Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText16->SetFont(StaticText16Font);
    FlexGridSizer6->Add(StaticText16, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderShIntensity = new wxSlider(PanelShimmer, ID_SLIDER4, 255, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_LABELS|wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER4"));
    FlexGridSizer6->Add(SliderShIntensity, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    StaticText18 = new wxStaticText(PanelShimmer, ID_STATICTEXT18, _("Off"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    BoxSizer11->Add(StaticText18, 1, wxALL|wxSHAPED|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText19 = new wxStaticText(PanelShimmer, ID_STATICTEXT19, _("On"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    BoxSizer11->Add(StaticText19, 1, wxALL|wxSHAPED|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6->Add(BoxSizer11, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    PanelShimmer->SetSizer(FlexGridSizer6);
    FlexGridSizer6->Fit(PanelShimmer);
    FlexGridSizer6->SetSizeHints(PanelShimmer);
    PanelAutoTest = new wxPanel(Notebook1, ID_PANEL_AUTOTEST, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_AUTOTEST"));
    FlexGridSizer8 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer8->AddGrowableCol(0);
    FlexGridSizer8->AddGrowableRow(1);
    CheckBoxRunAuto = new wxCheckBox(PanelAutoTest, ID_CHECKBOX_AUTO, _("Run Automated Test"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_AUTO"));
    CheckBoxRunAuto->SetValue(false);
    FlexGridSizer8->Add(CheckBoxRunAuto, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 10);
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
    FlexGridSizer8->Add(ListBoxAutoTest, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 10);
    PanelAutoTest->SetSizer(FlexGridSizer8);
    FlexGridSizer8->Fit(PanelAutoTest);
    FlexGridSizer8->SetSizeHints(PanelAutoTest);
    Notebook1->AddPage(Panel_Dim, _("Dim"), false);
    Notebook1->AddPage(Panel_Seq, _("Sequence"), false);
    Notebook1->AddPage(Panel_Alt, _("Alternate"), false);
    Notebook1->AddPage(PanelTwinkle, _("Twinkle"), false);
    Notebook1->AddPage(PanelShimmer, _("Shimmer"), false);
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

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xTesterFrame::OnButton1Click);
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
    static int LastDimValue;
    static int LastSequenceSpeed;
    static int LastTest;
    static long NextSequenceStart = -1;
    static wxArrayInt chArray;
    static int interval;
    static unsigned int seqidx=9999,alt=0;
    int v,n,ch;
    unsigned int i;
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
        LastDimValue=-1;
        LastTest=-1;
    }
    switch (NotebookSelection) {
        case 0:
            // dimmer
            v=SliderMasterDimmer->GetValue();
            if (v != LastDimValue) {
                for (ch=0,n=0; ch < maxch; ch++) {
                    if (lb->IsChecked(ch)) {
                        xout.SetIntensity(netidx, ch, v);
                        n++;
                    }
                }
                LastDimValue = v;
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
                if (LastDimValue == -1) {
                    // get list of checked channels
                    chArray.Clear();
                    for (ch=0; ch < maxch; ch++) {
                        if (lb->IsChecked(ch)) {
                            chArray.Add(ch);
                        }
                    }
                }
                v=SliderTwIntensity->GetValue();  // 0-255
                if (v != LastDimValue) {
                    LastDimValue = v;
                    for (i=0; i < chArray.Count(); i++) {
                        xout.twinkle(netidx, chArray[i], TWINKLE_PERIOD, v);
                    }
                    StatusBar1->SetStatusText(wxString::Format(_("Twinkling %d channels, intentiy=%d"),chArray.Count(),v));
                }
            } else {
                if (LastDimValue != -1) {
                    for (i=0; i < chArray.Count(); i++) {
                        xout.off(netidx, chArray[i]);
                    }
                    chArray.Clear();
                }
                LastDimValue=-1;
            }
            break;
        case 4:
            // shimmer
            if (CheckBoxRunSh->IsChecked()) {
                if (LastDimValue == -1) {
                    // get list of checked channels
                    chArray.Clear();
                    for (ch=0; ch < maxch; ch++) {
                        if (lb->IsChecked(ch)) {
                            chArray.Add(ch);
                        }
                    }
                }
                v=SliderShIntensity->GetValue();  // 0-255
                if (v != LastDimValue) {
                    LastDimValue = v;
                    for (i=0; i < chArray.Count(); i++) {
                        xout.shimmer(netidx, chArray[i], SHIMMER_PERIOD, v);
                    }
                    StatusBar1->SetStatusText(wxString::Format(_("Shimmering %d channels, speed=%d"),chArray.Count(),interval));
                }
            } else {
                if (LastDimValue != -1) {
                    for (i=0; i < chArray.Count(); i++) {
                        xout.off(netidx, chArray[i]);
                    }
                    chArray.Clear();
                }
                LastDimValue=-1;
            }
            break;
        case 5:
            // automated test
            if (CheckBoxRunAuto->IsChecked()) {
                interval = 3000;  // 3 seconds per test
                if (LastTest == -1) {
                    // get list of checked channels
                    chArray.Clear();
                    for (ch=0; ch < maxch; ch++) {
                        if (lb->IsChecked(ch)) {
                            chArray.Add(ch);
                        }
                    }
                    seqidx=99;  // test #
                    NextSequenceStart = curtime;
                    ListBoxAutoTest->Enable(true);
                }
                if (curtime >= NextSequenceStart && chArray.Count() > 0) {
                    NextSequenceStart = curtime + interval + 1500; // allow time between tests
                    seqidx++;
                    if (seqidx >= ListBoxAutoTest->GetCount()) seqidx=0;
                    LastTest=seqidx;
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
                }
            } else if (LastTest != -1) {
                for (i=0; i < chArray.Count(); i++) {
                    xout.off(netidx, chArray[i]);
                }
                chArray.Clear();
                ListBoxAutoTest->Enable(false);
                LastTest=-1;
            }
            break;
    }
    xout.TimerEnd();
    wxLogTrace(wxT("xout"),wxT("Ending OnTimer"));
    //StatusBar1->SetStatusText(ts.Format(_("%S.%l")));
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
    wxLog::ClearTraceMasks();
}

void xTesterFrame::OnMenuItemHelpContentSelected(wxCommandEvent& event)
{
    if (!wxLaunchDefaultBrowser(_(XLIGHTS_HELP_URL)))
    {
        wxMessageBox(_("Help requires Internet access. Unable to access help."), _("Error"));
    }
}
