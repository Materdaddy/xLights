#include "TestDialog.h"
#include <wx/msgdlg.h>
#include <limits>

//(*InternalHeaders(TestDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(TestDialog)
const long TestDialog::ID_STATICTEXT1 = wxNewId();
const long TestDialog::ID_CHOICE_NUMSELECT = wxNewId();
const long TestDialog::ID_BUTTON_CLEAR = wxNewId();
const long TestDialog::ID_STATICTEXT3 = wxNewId();
const long TestDialog::ID_BUTTON_EXPORT = wxNewId();
const long TestDialog::ID_BUTTON_LIGHTS_OFF = wxNewId();
const long TestDialog::ID_BUTTON_CLOSE = wxNewId();
const long TestDialog::ID_NOTEBOOK2 = wxNewId();
const long TestDialog::ID_STATICTEXT8 = wxNewId();
const long TestDialog::ID_RADIOBUTTON14 = wxNewId();
const long TestDialog::ID_RADIOBUTTON15 = wxNewId();
const long TestDialog::ID_RADIOBUTTON16 = wxNewId();
const long TestDialog::ID_RADIOBUTTON17 = wxNewId();
const long TestDialog::ID_RADIOBUTTON19 = wxNewId();
const long TestDialog::ID_RADIOBUTTON18 = wxNewId();
const long TestDialog::ID_RADIOBUTTON7 = wxNewId();
const long TestDialog::ID_RADIOBUTTON31 = wxNewId();
const long TestDialog::ID_RADIOBUTTON30 = wxNewId();
const long TestDialog::ID_RADIOBUTTON29 = wxNewId();
const long TestDialog::ID_RADIOBUTTON8 = wxNewId();
const long TestDialog::ID_RADIOBUTTON6 = wxNewId();
const long TestDialog::ID_STATICTEXT9 = wxNewId();
const long TestDialog::ID_SLIDER4 = wxNewId();
const long TestDialog::ID_STATICTEXT10 = wxNewId();
const long TestDialog::ID_SLIDER5 = wxNewId();
const long TestDialog::ID_STATICTEXT11 = wxNewId();
const long TestDialog::ID_SLIDER6 = wxNewId();
const long TestDialog::ID_PANEL_STANDARD = wxNewId();
const long TestDialog::ID_STATICTEXT29 = wxNewId();
const long TestDialog::ID_RADIOBUTTON1 = wxNewId();
const long TestDialog::ID_RADIOBUTTON2 = wxNewId();
const long TestDialog::ID_RADIOBUTTON3 = wxNewId();
const long TestDialog::ID_RADIOBUTTON4 = wxNewId();
const long TestDialog::ID_RADIOBUTTON25 = wxNewId();
const long TestDialog::ID_RADIOBUTTON5 = wxNewId();
const long TestDialog::ID_RADIOBUTTON12 = wxNewId();
const long TestDialog::ID_RADIOBUTTON28 = wxNewId();
const long TestDialog::ID_RADIOBUTTON10 = wxNewId();
const long TestDialog::ID_RADIOBUTTON9 = wxNewId();
const long TestDialog::ID_RADIOBUTTON13 = wxNewId();
const long TestDialog::ID_RADIOBUTTON11 = wxNewId();
const long TestDialog::ID_SLIDER12 = wxNewId();
const long TestDialog::ID_SLIDER11 = wxNewId();
const long TestDialog::ID_SLIDER1 = wxNewId();
const long TestDialog::ID_SLIDER14 = wxNewId();
const long TestDialog::ID_SLIDER13 = wxNewId();
const long TestDialog::ID_SLIDER9 = wxNewId();
const long TestDialog::ID_STATICTEXT4 = wxNewId();
const long TestDialog::ID_SLIDER2 = wxNewId();
const long TestDialog::ID_PANEL_RGB = wxNewId();
const long TestDialog::ID_STATICTEXT2 = wxNewId();
const long TestDialog::ID_RADIOBUTTON20 = wxNewId();
const long TestDialog::ID_RADIOBUTTON22 = wxNewId();
const long TestDialog::ID_RADIOBUTTON23 = wxNewId();
const long TestDialog::ID_RADIOBUTTON24 = wxNewId();
const long TestDialog::ID_RADIOBUTTON21 = wxNewId();
const long TestDialog::ID_STATICTEXT13 = wxNewId();
const long TestDialog::ID_SLIDER7 = wxNewId();
const long TestDialog::ID_PANEL_RGB_CYCLE = wxNewId();
const long TestDialog::ID_NOTEBOOK1 = wxNewId();
const long TestDialog::ID_PANEL4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(TestDialog,wxDialog)
	//(*EventTable(TestDialog)
	//*)
END_EVENT_TABLE()

TestDialog::TestDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(TestDialog)
	wxFlexGridSizer* FlexGridSizer24;
	wxStaticBoxSizer* StaticBoxSizerHighlightColor;
	wxBoxSizer* BoxSizer10;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer22;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxBoxSizer* BoxSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxFlexGridSizer* FlexGridSizer15;
	wxFlexGridSizer* FlexGridSizer21;
	wxFlexGridSizer* FlexGridSizer14;
	wxFlexGridSizer* FlexGridSizer20;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;
	wxBoxSizer* BoxSizer3;
	wxFlexGridSizer* FlexGridSizer17;
	wxStaticBoxSizer* StaticBoxSizerBackgroundColor;
	
	Create(parent, id, _("xTester"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
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
	ButtonLightsOff = new wxButton(Panel3, ID_BUTTON_LIGHTS_OFF, _("All Lights Off"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LIGHTS_OFF"));
	FlexGridSizer17->Add(ButtonLightsOff, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
	ButtonClose = new wxButton(Panel3, ID_BUTTON_CLOSE, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CLOSE"));
	FlexGridSizer17->Add(ButtonClose, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(FlexGridSizer17, 1, wxALL|wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Notebook2 = new wxNotebook(Panel3, ID_NOTEBOOK2, wxDefaultPosition, wxSize(225,220), 0, _T("ID_NOTEBOOK2"));
	FlexGridSizer2->Add(Notebook2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Notebook1 = new wxNotebook(Panel3, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
	PanelStandard = new wxPanel(Notebook1, ID_PANEL_STANDARD, wxPoint(29,39), wxSize(211,136), wxTAB_TRAVERSAL, _T("ID_PANEL_STANDARD"));
	FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer9->AddGrowableRow(0);
	FlexGridSizer10 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText8 = new wxStaticText(PanelStandard, ID_STATICTEXT8, _("Select function:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	wxFont StaticText8Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText8->SetFont(StaticText8Font);
	FlexGridSizer10->Add(StaticText8, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonOff = new wxRadioButton(PanelStandard, ID_RADIOBUTTON14, _("Off"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON14"));
	FlexGridSizer10->Add(RadioButtonOff, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonChase = new wxRadioButton(PanelStandard, ID_RADIOBUTTON15, _("Chase"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON15"));
	FlexGridSizer10->Add(RadioButtonChase, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonChase3 = new wxRadioButton(PanelStandard, ID_RADIOBUTTON16, _("Chase 1/3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON16"));
	FlexGridSizer10->Add(RadioButtonChase3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonChase4 = new wxRadioButton(PanelStandard, ID_RADIOBUTTON17, _("Chase 1/4"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON17"));
	FlexGridSizer10->Add(RadioButtonChase4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonChase5 = new wxRadioButton(PanelStandard, ID_RADIOBUTTON19, _("Chase 1/5"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON19"));
	FlexGridSizer10->Add(RadioButtonChase5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonAlt = new wxRadioButton(PanelStandard, ID_RADIOBUTTON18, _("Alternate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON18"));
	FlexGridSizer10->Add(RadioButtonAlt, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonTwinkle05 = new wxRadioButton(PanelStandard, ID_RADIOBUTTON7, _("Twinkle 5%"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON7"));
	FlexGridSizer10->Add(RadioButtonTwinkle05, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonTwinkle10 = new wxRadioButton(PanelStandard, ID_RADIOBUTTON31, _("Twinkle 10%"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON31"));
	FlexGridSizer10->Add(RadioButtonTwinkle10, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonTwinkle25 = new wxRadioButton(PanelStandard, ID_RADIOBUTTON30, _("Twinkle 25%"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON30"));
	FlexGridSizer10->Add(RadioButtonTwinkle25, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonTwinkle50 = new wxRadioButton(PanelStandard, ID_RADIOBUTTON29, _("Twinkle 50%"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON29"));
	FlexGridSizer10->Add(RadioButtonTwinkle50, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonShimmer = new wxRadioButton(PanelStandard, ID_RADIOBUTTON8, _("Shimmer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON8"));
	FlexGridSizer10->Add(RadioButtonShimmer, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonDim = new wxRadioButton(PanelStandard, ID_RADIOBUTTON6, _("Background Only"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON6"));
	FlexGridSizer10->Add(RadioButtonDim, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9->Add(FlexGridSizer10, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer9->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	FlexGridSizer20 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer20->AddGrowableCol(0);
	FlexGridSizer20->AddGrowableRow(1);
	StaticText9 = new wxStaticText(PanelStandard, ID_STATICTEXT9, _("Background\nIntensity"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	wxFont StaticText9Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText9->SetFont(StaticText9Font);
	FlexGridSizer20->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SliderBgIntensity = new wxSlider(PanelStandard, ID_SLIDER4, 0, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER4"));
	FlexGridSizer20->Add(SliderBgIntensity, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	BoxSizer3->Add(FlexGridSizer20, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer21 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer21->AddGrowableCol(0);
	FlexGridSizer21->AddGrowableRow(1);
	StaticText10 = new wxStaticText(PanelStandard, ID_STATICTEXT10, _("Highlight\nIntensity"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	wxFont StaticText10Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText10->SetFont(StaticText10Font);
	FlexGridSizer21->Add(StaticText10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SliderFgIntensity = new wxSlider(PanelStandard, ID_SLIDER5, 255, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER5"));
	FlexGridSizer21->Add(SliderFgIntensity, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	BoxSizer3->Add(FlexGridSizer21, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer22 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer22->AddGrowableCol(0);
	FlexGridSizer22->AddGrowableRow(1);
	StaticText11 = new wxStaticText(PanelStandard, ID_STATICTEXT11, _("Speed\n"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	wxFont StaticText11Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText11->SetFont(StaticText11Font);
	FlexGridSizer22->Add(StaticText11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SliderChaseSpeed = new wxSlider(PanelStandard, ID_SLIDER6, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER6"));
	FlexGridSizer22->Add(SliderChaseSpeed, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	BoxSizer3->Add(FlexGridSizer22, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer9->Add(BoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	PanelStandard->SetSizer(FlexGridSizer9);
	FlexGridSizer9->SetSizeHints(PanelStandard);
	Panel_RGB = new wxPanel(Notebook1, ID_PANEL_RGB, wxPoint(29,39), wxSize(211,136), wxTAB_TRAVERSAL, _T("ID_PANEL_RGB"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 6, 0, 0);
	FlexGridSizer1->AddGrowableRow(0);
	FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText29 = new wxStaticText(Panel_RGB, ID_STATICTEXT29, _("Select function:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
	wxFont StaticText29Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText29->SetFont(StaticText29Font);
	FlexGridSizer3->Add(StaticText29, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbChaseOff = new wxRadioButton(Panel_RGB, ID_RADIOBUTTON1, _("Off"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	FlexGridSizer3->Add(RadioButtonRgbChaseOff, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbChase = new wxRadioButton(Panel_RGB, ID_RADIOBUTTON2, _("Chase"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	FlexGridSizer3->Add(RadioButtonRgbChase, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbChase3 = new wxRadioButton(Panel_RGB, ID_RADIOBUTTON3, _("Chase 1/3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON3"));
	FlexGridSizer3->Add(RadioButtonRgbChase3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbChase4 = new wxRadioButton(Panel_RGB, ID_RADIOBUTTON4, _("Chase 1/4"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON4"));
	FlexGridSizer3->Add(RadioButtonRgbChase4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbChase5 = new wxRadioButton(Panel_RGB, ID_RADIOBUTTON25, _("Chase 1/5"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON25"));
	FlexGridSizer3->Add(RadioButtonRgbChase5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbAlt = new wxRadioButton(Panel_RGB, ID_RADIOBUTTON5, _("Alternate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON5"));
	FlexGridSizer3->Add(RadioButtonRgbAlt, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbTwinkle05 = new wxRadioButton(Panel_RGB, ID_RADIOBUTTON12, _("Twinkle 5%"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON12"));
	FlexGridSizer3->Add(RadioButtonRgbTwinkle05, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbTwinkle10 = new wxRadioButton(Panel_RGB, ID_RADIOBUTTON28, _("Twinkle 10%"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON28"));
	FlexGridSizer3->Add(RadioButtonRgbTwinkle10, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbTwinkle25 = new wxRadioButton(Panel_RGB, ID_RADIOBUTTON10, _("Twinkle 25%"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON10"));
	FlexGridSizer3->Add(RadioButtonRgbTwinkle25, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbTwinkle50 = new wxRadioButton(Panel_RGB, ID_RADIOBUTTON9, _("Twinkle 50%"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON9"));
	FlexGridSizer3->Add(RadioButtonRgbTwinkle50, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbShimmer = new wxRadioButton(Panel_RGB, ID_RADIOBUTTON13, _("Shimmer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON13"));
	FlexGridSizer3->Add(RadioButtonRgbShimmer, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbDim = new wxRadioButton(Panel_RGB, ID_RADIOBUTTON11, _("Background Only"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON11"));
	FlexGridSizer3->Add(RadioButtonRgbDim, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer10 = new wxBoxSizer(wxVERTICAL);
	StaticBoxSizerBackgroundColor = new wxStaticBoxSizer(wxHORIZONTAL, Panel_RGB, _("Background Color"));
	SliderBgColorA = new wxSlider(Panel_RGB, ID_SLIDER12, 0, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER12"));
	StaticBoxSizerBackgroundColor->Add(SliderBgColorA, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	SliderBgColorB = new wxSlider(Panel_RGB, ID_SLIDER11, 0, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER11"));
	StaticBoxSizerBackgroundColor->Add(SliderBgColorB, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	SliderBgColorC = new wxSlider(Panel_RGB, ID_SLIDER1, 0, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER1"));
	StaticBoxSizerBackgroundColor->Add(SliderBgColorC, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	BoxSizer10->Add(StaticBoxSizerBackgroundColor, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	StaticBoxSizerHighlightColor = new wxStaticBoxSizer(wxHORIZONTAL, Panel_RGB, _("Highlight Color"));
	SliderFgColorA = new wxSlider(Panel_RGB, ID_SLIDER14, 255, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER14"));
	StaticBoxSizerHighlightColor->Add(SliderFgColorA, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	SliderFgColorB = new wxSlider(Panel_RGB, ID_SLIDER13, 255, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER13"));
	StaticBoxSizerHighlightColor->Add(SliderFgColorB, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	SliderFgColorC = new wxSlider(Panel_RGB, ID_SLIDER9, 255, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER9"));
	StaticBoxSizerHighlightColor->Add(SliderFgColorC, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	BoxSizer10->Add(StaticBoxSizerHighlightColor, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
	FlexGridSizer1->Add(BoxSizer10, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer14 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer14->AddGrowableCol(0);
	FlexGridSizer14->AddGrowableRow(1);
	StaticText4 = new wxStaticText(Panel_RGB, ID_STATICTEXT4, _("Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	wxFont StaticText4Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText4->SetFont(StaticText4Font);
	FlexGridSizer14->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SliderRgbChaseSpeed = new wxSlider(Panel_RGB, ID_SLIDER2, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER2"));
	FlexGridSizer14->Add(SliderRgbChaseSpeed, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer1->Add(FlexGridSizer14, 1, wxALL|wxEXPAND|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel_RGB->SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(Panel_RGB);
	Panel_RGB_Cycle = new wxPanel(Notebook1, ID_PANEL_RGB_CYCLE, wxPoint(71,15), wxSize(392,209), wxTAB_TRAVERSAL, _T("ID_PANEL_RGB_CYCLE"));
	FlexGridSizer11 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer11->AddGrowableRow(0);
	FlexGridSizer15 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText2 = new wxStaticText(Panel_RGB_Cycle, ID_STATICTEXT2, _("Select function:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	wxFont StaticText2Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText2->SetFont(StaticText2Font);
	FlexGridSizer15->Add(StaticText2, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbCycleOff = new wxRadioButton(Panel_RGB_Cycle, ID_RADIOBUTTON20, _("Off"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON20"));
	FlexGridSizer15->Add(RadioButtonRgbCycleOff, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbCycle3 = new wxRadioButton(Panel_RGB_Cycle, ID_RADIOBUTTON22, _("A-B-C"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON22"));
	FlexGridSizer15->Add(RadioButtonRgbCycle3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbCycle4 = new wxRadioButton(Panel_RGB_Cycle, ID_RADIOBUTTON23, _("A-B-C-All"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON23"));
	FlexGridSizer15->Add(RadioButtonRgbCycle4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbCycle5 = new wxRadioButton(Panel_RGB_Cycle, ID_RADIOBUTTON24, _("A-B-C-All-None"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON24"));
	FlexGridSizer15->Add(RadioButtonRgbCycle5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	RadioButtonRgbCycleMixed = new wxRadioButton(Panel_RGB_Cycle, ID_RADIOBUTTON21, _("Mixed Colors"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON21"));
	FlexGridSizer15->Add(RadioButtonRgbCycleMixed, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer11->Add(FlexGridSizer15, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer11->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer24 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer24->AddGrowableRow(1);
	StaticText13 = new wxStaticText(Panel_RGB_Cycle, ID_STATICTEXT13, _("Cycle Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	wxFont StaticText13Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText13->SetFont(StaticText13Font);
	FlexGridSizer24->Add(StaticText13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SliderRgbCycleSpeed = new wxSlider(Panel_RGB_Cycle, ID_SLIDER7, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS|wxSL_INVERSE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_SLIDER7"));
	FlexGridSizer24->Add(SliderRgbCycleSpeed, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
	FlexGridSizer11->Add(FlexGridSizer24, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel_RGB_Cycle->SetSizer(FlexGridSizer11);
	FlexGridSizer11->SetSizeHints(Panel_RGB_Cycle);
	Notebook1->AddPage(PanelStandard, _("Standard"), false);
	Notebook1->AddPage(Panel_RGB, _("RGB"), false);
	Notebook1->AddPage(Panel_RGB_Cycle, _("RGB Cycle"), false);
	FlexGridSizer2->Add(Notebook1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel3->SetSizer(FlexGridSizer2);
	FlexGridSizer2->Fit(Panel3);
	FlexGridSizer2->SetSizeHints(Panel3);
	BoxSizer1->Add(Panel3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	Center();
	
	Connect(ID_BUTTON_CLEAR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TestDialog::OnButtonClearClick);
	Connect(ID_BUTTON_EXPORT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TestDialog::OnButtonExportClick);
	Connect(ID_BUTTON_LIGHTS_OFF,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TestDialog::OnButtonLightsOffClick);
	Connect(ID_BUTTON_CLOSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&TestDialog::OnButtonCloseClick);
	Connect(ID_RADIOBUTTON14,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonOffSelect);
	Connect(ID_RADIOBUTTON15,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonChaseSelect);
	Connect(ID_RADIOBUTTON16,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonChase3Select);
	Connect(ID_RADIOBUTTON17,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonChase4Select);
	Connect(ID_RADIOBUTTON19,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonChase5Select);
	Connect(ID_RADIOBUTTON18,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonAltSelect);
	Connect(ID_RADIOBUTTON7,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonTwinkle05Select);
	Connect(ID_RADIOBUTTON31,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonTwinkle10Select);
	Connect(ID_RADIOBUTTON30,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonTwinkle25Select);
	Connect(ID_RADIOBUTTON29,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonTwinkle50Select);
	Connect(ID_RADIOBUTTON8,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonShimmerSelect);
	Connect(ID_RADIOBUTTON6,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonDimSelect);
	Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonOffSelect);
	Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonChaseSelect);
	Connect(ID_RADIOBUTTON3,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonChase3Select);
	Connect(ID_RADIOBUTTON4,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonChase4Select);
	Connect(ID_RADIOBUTTON25,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonChase5Select);
	Connect(ID_RADIOBUTTON5,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonAltSelect);
	Connect(ID_RADIOBUTTON12,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonTwinkle05Select);
	Connect(ID_RADIOBUTTON28,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonTwinkle10Select);
	Connect(ID_RADIOBUTTON10,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonTwinkle25Select);
	Connect(ID_RADIOBUTTON9,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonTwinkle50Select);
	Connect(ID_RADIOBUTTON13,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonShimmerSelect);
	Connect(ID_RADIOBUTTON11,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonDimSelect);
	Connect(ID_RADIOBUTTON20,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonOffSelect);
	Connect(ID_RADIOBUTTON22,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonChase3Select);
	Connect(ID_RADIOBUTTON23,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonChase4Select);
	Connect(ID_RADIOBUTTON24,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonChase5Select);
	Connect(ID_RADIOBUTTON21,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&TestDialog::OnRadioButtonDimSelect);
	//*)

    CheckChannelList = true;
}

TestDialog::~TestDialog()
{
	//(*Destroy(TestDialog)
	//*)
}


void TestDialog::OnButtonClearClick(wxCommandEvent& event)
{
    int netidx = Notebook2->GetSelection(); // which network
    wxCheckListBox* lb = Networks[netidx]->ListBox;
    int ChCount = lb->GetCount();
    for (int i=0; i < ChCount; i++) {
        lb->Check(i,false);
    }
    CheckChannelList = true;
}

void TestDialog::OnButtonExportClick(wxCommandEvent& event)
{
    wxMessageBox(_("Export not implemented yet"), _("Export"));
}

void TestDialog::OnButtonLightsOffClick(wxCommandEvent& event)
{
    RadioButtonsOff();
}

void TestDialog::OnRadioButtonOffSelect(wxCommandEvent& event)
{
    TestFunc=OFF;
}

void TestDialog::OnRadioButtonChaseSelect(wxCommandEvent& event)
{
    TestFunc=CHASE;
    ChaseGrouping=std::numeric_limits<int>::max();
}

void TestDialog::OnRadioButtonChase3Select(wxCommandEvent& event)
{
    TestFunc=CHASE;
    ChaseGrouping=3;
}

void TestDialog::OnRadioButtonChase4Select(wxCommandEvent& event)
{
    TestFunc=CHASE;
    ChaseGrouping=4;
}

void TestDialog::OnRadioButtonChase5Select(wxCommandEvent& event)
{
    TestFunc=CHASE;
    ChaseGrouping=5;
}

void TestDialog::OnRadioButtonAltSelect(wxCommandEvent& event)
{
    TestFunc=CHASE;
    ChaseGrouping=2;
}

void TestDialog::OnRadioButtonTwinkle05Select(wxCommandEvent& event)
{
    TestFunc=TWINKLE;
    TwinkleRatio=20;
}

void TestDialog::OnRadioButtonTwinkle10Select(wxCommandEvent& event)
{
    TestFunc=TWINKLE;
    TwinkleRatio=10;
}

void TestDialog::OnRadioButtonTwinkle25Select(wxCommandEvent& event)
{
    TestFunc=TWINKLE;
    TwinkleRatio=4;
}

void TestDialog::OnRadioButtonTwinkle50Select(wxCommandEvent& event)
{
    TestFunc=TWINKLE;
    TwinkleRatio=2;
}

void TestDialog::OnRadioButtonShimmerSelect(wxCommandEvent& event)
{
    TestFunc=SHIMMER;
}

void TestDialog::OnRadioButtonDimSelect(wxCommandEvent& event)
{
    TestFunc=DIM;
}

void TestDialog::AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels)
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
    wxArrayString chNames;
    if (net3 == wxT("LOR") || net3 == wxT("D-L")) {
        for (int i=0; i < MaxChannels; i++) {
            chNames.Add( wxString::Format(_T("Unit %02X.%d"), (i >> 4)+1, (i & 0x0F)+1 ));
        }
    } else {
        for (int i=1; i <= MaxChannels; i++) {
            chNames.Add( wxString::Format(_T("Channel %d"), i) );
        }
    }
    ListBox->Set(chNames);
    ListBox->Connect(wxEVT_COMMAND_CHECKLISTBOX_TOGGLED,(wxObjectEventFunction)&TestDialog::OnCheckboxToggle, NULL, this);
}


void TestDialog::OnCheckboxToggle(wxCommandEvent& event)
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


void TestDialog::RadioButtonsOff()
{
    RadioButtonOff->SetValue(true);
    RadioButtonChase->SetValue(false);
    RadioButtonChase3->SetValue(false);
    RadioButtonChase4->SetValue(false);
    RadioButtonChase5->SetValue(false);
    RadioButtonAlt->SetValue(false);
    RadioButtonTwinkle05->SetValue(false);
    RadioButtonTwinkle10->SetValue(false);
    RadioButtonTwinkle25->SetValue(false);
    RadioButtonTwinkle50->SetValue(false);
    RadioButtonShimmer->SetValue(false);
    RadioButtonDim->SetValue(false);

    RadioButtonRgbChaseOff->SetValue(true);
    RadioButtonRgbChase->SetValue(false);
    RadioButtonRgbChase3->SetValue(false);
    RadioButtonRgbChase4->SetValue(false);
    RadioButtonRgbChase5->SetValue(false);
    RadioButtonRgbAlt->SetValue(false);
    RadioButtonRgbTwinkle05->SetValue(false);
    RadioButtonRgbTwinkle10->SetValue(false);
    RadioButtonRgbTwinkle25->SetValue(false);
    RadioButtonRgbTwinkle50->SetValue(false);
    RadioButtonRgbShimmer->SetValue(false);
    RadioButtonRgbDim->SetValue(false);

    RadioButtonRgbCycleOff->SetValue(true);
    RadioButtonRgbCycle3->SetValue(false);
    RadioButtonRgbCycle4->SetValue(false);
    RadioButtonRgbCycle5->SetValue(false);
    RadioButtonRgbCycleMixed->SetValue(false);

    TestFunc=OFF;
}

int TestDialog::GetNetIdx()
{
    return Notebook2->GetSelection(); // which network
}

int TestDialog::GetTestIdx()
{
    return Notebook1->GetSelection(); // which network
}

void TestDialog::GetCheckedItems(int netidx, wxArrayInt& chArray)
{
    chArray.Clear();
    wxCheckListBox* lb = Networks[netidx]->ListBox;
    int maxch = lb->GetCount();
    for (int ch=0; ch < maxch; ch++) {
        if (lb->IsChecked(ch)) {
            chArray.Add(ch);
        }
    }
}

int TestDialog::ChaseSpeed()
{
    return SliderChaseSpeed->GetValue();  // 0-100
}

int TestDialog::BgIntensity()
{
    return SliderBgIntensity->GetValue();  // 0-255
}

int TestDialog::FgIntensity()
{
    return SliderFgIntensity->GetValue();  // 0-255
}

int TestDialog::RgbChaseSpeed()
{
    return SliderRgbChaseSpeed->GetValue();  // 0-100
}

int TestDialog::BgColorA()
{
    return SliderBgColorA->GetValue();  // 0-255
}

int TestDialog::BgColorB()
{
    return SliderBgColorB->GetValue();  // 0-255
}

int TestDialog::BgColorC()
{
    return SliderBgColorC->GetValue();  // 0-255
}

int TestDialog::FgColorA()
{
    return SliderFgColorA->GetValue();  // 0-255
}

int TestDialog::FgColorB()
{
    return SliderFgColorB->GetValue();  // 0-255
}

int TestDialog::FgColorC()
{
    return SliderFgColorC->GetValue();  // 0-255
}

int TestDialog::RgbCycleSpeed()
{
    return SliderRgbCycleSpeed->GetValue();  // 0-100
}


void TestDialog::OnButtonCloseClick(wxCommandEvent& event)
{
    RadioButtonsOff();
    wxMilliSleep(100);  // give some time for everything to shut off
    this->Close();
}
