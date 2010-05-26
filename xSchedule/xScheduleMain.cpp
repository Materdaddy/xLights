/***************************************************************
 * Name:      xScheduleMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-05-15
 * Copyright: Matt Brown (dowdybrown.com)
 * License:
 **************************************************************/

#include "xScheduleMain.h"
#include <wx/msgdlg.h>
#include <wx/dir.h>
#include <wx/filename.h>

//(*InternalHeaders(xScheduleFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

#include "../include/tinyxml.cpp"
#include "../include/tinyxmlerror.cpp"
#include "../include/tinyxmlparser.cpp"


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

//(*IdInit(xScheduleFrame)
const long xScheduleFrame::ID_CHOICE_PLAYLIST = wxNewId();
const long xScheduleFrame::ID_BUTTON_SAVE = wxNewId();
const long xScheduleFrame::ID_STATICTEXT1 = wxNewId();
const long xScheduleFrame::ID_BITMAPBUTTON_UP = wxNewId();
const long xScheduleFrame::ID_BITMAPBUTTON_DOWN = wxNewId();
const long xScheduleFrame::ID_BUTTON_PLAY = wxNewId();
const long xScheduleFrame::ID_STATICTEXT2 = wxNewId();
const long xScheduleFrame::ID_CHECKBOX_AUDIO = wxNewId();
const long xScheduleFrame::ID_CHECKBOX_VIDEO = wxNewId();
const long xScheduleFrame::ID_CHECKBOX_LOR = wxNewId();
const long xScheduleFrame::ID_CHECKBOX_VIXEN = wxNewId();
const long xScheduleFrame::ID_CHECKLISTBOX_PLAY = wxNewId();
const long xScheduleFrame::ID_STATICTEXT3 = wxNewId();
const long xScheduleFrame::ID_CHOICE_LOGIC = wxNewId();
const long xScheduleFrame::ID_TEXTCTRL_LOGIC = wxNewId();
const long xScheduleFrame::ID_PANEL_PLAYLIST = wxNewId();
const long xScheduleFrame::ID_CHOICE1 = wxNewId();
const long xScheduleFrame::ID_STATICTEXT5 = wxNewId();
const long xScheduleFrame::ID_CHOICE2 = wxNewId();
const long xScheduleFrame::ID_STATICTEXT6 = wxNewId();
const long xScheduleFrame::ID_CHOICE3 = wxNewId();
const long xScheduleFrame::ID_TOGGLEBUTTON5 = wxNewId();
const long xScheduleFrame::ID_TOGGLEBUTTON6 = wxNewId();
const long xScheduleFrame::ID_GRID1 = wxNewId();
const long xScheduleFrame::ID_PANEL_CAL = wxNewId();
const long xScheduleFrame::ID_NOTEBOOK1 = wxNewId();
const long xScheduleFrame::ID_PANEL1 = wxNewId();
const long xScheduleFrame::idMenuQuit = wxNewId();
const long xScheduleFrame::idMenuAbout = wxNewId();
const long xScheduleFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(xScheduleFrame,wxFrame)
    //(*EventTable(xScheduleFrame)
    //*)
END_EVENT_TABLE()

xScheduleFrame::xScheduleFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(xScheduleFrame)
    wxBoxSizer* BoxSizer4;
    wxFlexGridSizer* FlexGridSizer4;
    wxMenuItem* MenuItem2;
    wxFlexGridSizer* FlexGridSizer10;
    wxFlexGridSizer* FlexGridSizer3;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer9;
    wxFlexGridSizer* FlexGridSizer2;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxFlexGridSizer* FlexGridSizer7;
    wxGridSizer* GridSizer1;
    wxFlexGridSizer* FlexGridSizer8;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer6;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer11;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;

    Create(parent, id, _("xSchedule"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(612,327));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("..\\include\\xlights.ico"))));
    	SetIcon(FrameIcon);
    }
    FlexGridSizer1 = new wxFlexGridSizer(1, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxNO_BORDER, _T("ID_PANEL1"));
    FlexGridSizer2 = new wxFlexGridSizer(1, 1, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    FlexGridSizer2->AddGrowableRow(0);
    Notebook1 = new wxNotebook(Panel1, ID_NOTEBOOK1, wxDefaultPosition, wxSize(602,275), 0, _T("ID_NOTEBOOK1"));
    PanelPlayList = new wxPanel(Notebook1, ID_PANEL_PLAYLIST, wxPoint(89,157), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_PLAYLIST"));
    FlexGridSizer3 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer3->AddGrowableCol(0);
    FlexGridSizer3->AddGrowableRow(1);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    ChoicePlayList = new wxChoice(PanelPlayList, ID_CHOICE_PLAYLIST, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_PLAYLIST"));
    ChoicePlayList->SetSelection( ChoicePlayList->Append(_("Select play list...")) );
    ChoicePlayList->Append(_("<new>"));
    BoxSizer1->Add(ChoicePlayList, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonSave = new wxButton(PanelPlayList, ID_BUTTON_SAVE, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SAVE"));
    BoxSizer1->Add(ButtonSave, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1 = new wxGridSizer(2, 2, 0, 0);
    FlexGridSizer4 = new wxFlexGridSizer(3, 1, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    FlexGridSizer4->AddGrowableRow(2);
    FlexGridSizer5 = new wxFlexGridSizer(0, 4, 0, 0);
    FlexGridSizer5->AddGrowableCol(0);
    StaticText1 = new wxStaticText(PanelPlayList, ID_STATICTEXT1, _("Play List"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(10,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    FlexGridSizer5->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButtonUp = new wxBitmapButton(PanelPlayList, ID_BITMAPBUTTON_UP, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_UP")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_UP"));
    BitmapButtonUp->SetDefault();
    BitmapButtonUp->SetToolTip(_("Move Up"));
    FlexGridSizer5->Add(BitmapButtonUp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButtonDown = new wxBitmapButton(PanelPlayList, ID_BITMAPBUTTON_DOWN, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_DOWN")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON_DOWN"));
    BitmapButtonDown->SetDefault();
    BitmapButtonDown->SetToolTip(_("Move Down"));
    FlexGridSizer5->Add(BitmapButtonDown, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonPlay = new wxButton(PanelPlayList, ID_BUTTON_PLAY, _(">"), wxDefaultPosition, wxSize(29,23), 0, wxDefaultValidator, _T("ID_BUTTON_PLAY"));
    ButtonPlay->SetToolTip(_("Play"));
    ButtonPlay->SetHelpText(_("Plays the currently selected item in the play list"));
    FlexGridSizer5->Add(ButtonPlay, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(FlexGridSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    StaticText2 = new wxStaticText(PanelPlayList, ID_STATICTEXT2, _("Files:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer4->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxAudio = new wxCheckBox(PanelPlayList, ID_CHECKBOX_AUDIO, _("Audio"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_AUDIO"));
    CheckBoxAudio->SetValue(false);
    BoxSizer4->Add(CheckBoxAudio, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxVideo = new wxCheckBox(PanelPlayList, ID_CHECKBOX_VIDEO, _("Video"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_VIDEO"));
    CheckBoxVideo->SetValue(false);
    BoxSizer4->Add(CheckBoxVideo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxLOR = new wxCheckBox(PanelPlayList, ID_CHECKBOX_LOR, _("LOR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_LOR"));
    CheckBoxLOR->SetValue(false);
    BoxSizer4->Add(CheckBoxLOR, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxVixen = new wxCheckBox(PanelPlayList, ID_CHECKBOX_VIXEN, _("Vixen"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_VIXEN"));
    CheckBoxVixen->SetValue(false);
    BoxSizer4->Add(CheckBoxVixen, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckListBoxPlay = new wxCheckListBox(PanelPlayList, ID_CHECKLISTBOX_PLAY, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX_PLAY"));
    FlexGridSizer4->Add(CheckListBoxPlay, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(FlexGridSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6 = new wxFlexGridSizer(3, 1, 0, 0);
    FlexGridSizer6->AddGrowableCol(0);
    FlexGridSizer6->AddGrowableRow(1);
    FlexGridSizer7 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer7->AddGrowableCol(1);
    StaticText3 = new wxStaticText(PanelPlayList, ID_STATICTEXT3, _("Player Logic"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    wxFont StaticText3Font(10,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText3->SetFont(StaticText3Font);
    FlexGridSizer7->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ChoiceLogic = new wxChoice(PanelPlayList, ID_CHOICE_LOGIC, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_LOGIC"));
    FlexGridSizer7->Add(ChoiceLogic, 1, wxALL|wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6->Add(FlexGridSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlLogic = new wxTextCtrl(PanelPlayList, ID_TEXTCTRL_LOGIC, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_LOGIC"));
    FlexGridSizer6->Add(TextCtrlLogic, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(FlexGridSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(GridSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelPlayList->SetSizer(FlexGridSizer3);
    FlexGridSizer3->Fit(PanelPlayList);
    FlexGridSizer3->SetSizeHints(PanelPlayList);
    PanelCal = new wxPanel(Notebook1, ID_PANEL_CAL, wxPoint(49,10), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_CAL"));
    FlexGridSizer8 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer8->AddGrowableCol(0);
    FlexGridSizer8->AddGrowableRow(1);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    Choice1 = new wxChoice(PanelCal, ID_CHOICE1, wxDefaultPosition, wxSize(113,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    BoxSizer2->Add(Choice1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticText5 = new wxStaticText(PanelCal, ID_STATICTEXT5, _("Start"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer9->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Choice2 = new wxChoice(PanelCal, ID_CHOICE2, wxDefaultPosition, wxSize(64,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    FlexGridSizer9->Add(Choice2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(FlexGridSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer10 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticText6 = new wxStaticText(PanelCal, ID_STATICTEXT6, _("End"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    FlexGridSizer10->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Choice3 = new wxChoice(PanelCal, ID_CHOICE3, wxDefaultPosition, wxSize(59,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    FlexGridSizer10->Add(Choice3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(FlexGridSizer10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer11 = new wxFlexGridSizer(0, 3, 0, 0);
    ToggleButton5 = new wxToggleButton(PanelCal, ID_TOGGLEBUTTON5, _("Set"), wxDefaultPosition, wxSize(53,23), 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON5"));
    FlexGridSizer11->Add(ToggleButton5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ToggleButton6 = new wxToggleButton(PanelCal, ID_TOGGLEBUTTON6, _("Delete"), wxDefaultPosition, wxSize(59,23), 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON6"));
    FlexGridSizer11->Add(ToggleButton6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(FlexGridSizer11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer8->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    Grid1 = new wxGrid(PanelCal, ID_GRID1, wxDefaultPosition, wxSize(374,178), 0, _T("ID_GRID1"));
    Grid1->CreateGrid(26,7);
    Grid1->EnableEditing(true);
    Grid1->EnableGridLines(true);
    Grid1->SetDefaultRowSize(40, true);
    Grid1->SetColLabelValue(0, _("Sun"));
    Grid1->SetColLabelValue(1, _("Mon"));
    Grid1->SetColLabelValue(2, _("Tue"));
    Grid1->SetColLabelValue(3, _("Wed"));
    Grid1->SetColLabelValue(4, _("Thu"));
    Grid1->SetColLabelValue(5, _("Fri"));
    Grid1->SetColLabelValue(6, _("Sat"));
    Grid1->SetDefaultCellFont( Grid1->GetFont() );
    Grid1->SetDefaultCellTextColour( Grid1->GetForegroundColour() );
    BoxSizer3->Add(Grid1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer8->Add(BoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelCal->SetSizer(FlexGridSizer8);
    FlexGridSizer8->Fit(PanelCal);
    FlexGridSizer8->SetSizeHints(PanelCal);
    Notebook1->AddPage(PanelPlayList, _("Play List"), false);
    Notebook1->AddPage(PanelCal, _("Calendar"), false);
    FlexGridSizer2->Add(Notebook1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer2);
    FlexGridSizer2->Fit(Panel1);
    FlexGridSizer2->SetSizeHints(Panel1);
    FlexGridSizer1->Add(Panel1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
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
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_CHOICE_PLAYLIST,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnChoicePlayListSelect);
    Connect(ID_BUTTON_SAVE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonSaveClick);
    Connect(ID_BITMAPBUTTON_UP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonUpClick);
    Connect(ID_BITMAPBUTTON_DOWN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonDownClick);
    Connect(ID_BUTTON_PLAY,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonPlayClick);
    Connect(ID_CHECKBOX_AUDIO,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnCheckBoxAudioClick);
    Connect(ID_CHECKBOX_VIDEO,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnCheckBoxVideoClick);
    Connect(ID_CHECKBOX_LOR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnCheckBoxLORClick);
    Connect(ID_CHECKBOX_VIXEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnCheckBoxVixenClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAbout);
    //*)

    PlayerDlg=new PlayerDialog(this);

    // Get CurrentDir
    wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));
    if ( !config->Read(_("LastDir"), &CurrentDir) ) {
        wxMessageBox(_("No directory specified"), _("ERROR"));
        Close();
    }
    scheduleFile.AssignDir( CurrentDir );
    scheduleFile.SetFullName(_(XLIGHTS_NETWORK_FILE));
    UnsavedChanges=false;
    if (scheduleFile.FileExists()) {
        LoadFile();
    }
}

xScheduleFrame::~xScheduleFrame()
{
    //(*Destroy(xScheduleFrame)
    //*)
}

void xScheduleFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void xScheduleFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _(XLIGHTS_LICENSE);
    wxString hdg = wxString::Format(_("About xLights %s"),_(XLIGHTS_VERSION));
    wxMessageBox(msg, hdg);
}

void xScheduleFrame::LoadFile()
{

}

void xScheduleFrame::ScanForFiles()
{
    wxString filename;
    bool ok;
    int i;
    wxFileName* oName=new wxFileName();
    oName->AssignDir( CurrentDir );

    // if user unchecked a box, remove matching entries
    wxArrayString s=CheckListBoxPlay->GetStrings();
    for (i=s.GetCount()-1; i >= 0; i--) {
        oName->SetFullName(s[i]);
        ok=false;
        switch (ExtType(oName->GetExt())) {
            case 'a': ok=CheckBoxAudio->IsChecked(); break;
            case 'v': ok=CheckBoxVideo->IsChecked(); break;
            case 'L': ok=CheckBoxLOR->IsChecked(); break;
            case 'V': ok=CheckBoxVixen->IsChecked(); break;
        }
        if (!ok) CheckListBoxPlay->Delete(i);
    }

    // scan directory for matches
    wxDir* d=new wxDir(CurrentDir);
    if (d->GetFirst(&filename)) {
        do {
            if (CheckListBoxPlay->FindString(filename) != wxNOT_FOUND) continue;
            oName->SetFullName(filename);
            ok=false;
            switch (ExtType(oName->GetExt())) {
                case 'a': ok=CheckBoxAudio->IsChecked(); break;
                case 'v': ok=CheckBoxVideo->IsChecked(); break;
                case 'L': ok=CheckBoxLOR->IsChecked(); break;
                case 'V': ok=CheckBoxVixen->IsChecked(); break;
            }
            if (ok) {
                i=CheckListBoxPlay->Append(filename);
                CheckListBoxPlay->Check(i);
            }
        } while (d->GetNext(&filename));
    }
    delete oName;
    delete d;
}

// returns V for vixen, L for LOR, a for audio, v for video
char xScheduleFrame::ExtType(wxString ext) {
    if (ext == _("vix")) {
        return 'V';
    } else if (ext == _("lms")) {
        return 'L';
    } else if (CheckBoxAudio->IsChecked() &&
               (ext == _("wav") || ext == _("mp3") ||
                ext == _("wma") || ext == _("aac"))) {
        return 'a';
    } else if (CheckBoxAudio->IsChecked() &&
               (ext == _("avi") || ext == _("mp4") ||
                ext == _("wmv") || ext == _("mov"))) {
        return 'v';
    }
    return ' ';
}

void xScheduleFrame::OnButtonSaveClick(wxCommandEvent& event)
{
}

void xScheduleFrame::OnButtonPlayClick(wxCommandEvent& event)
{
    wxString filename = CheckListBoxPlay->GetStringSelection();
    if (filename.IsEmpty()) {
        wxMessageBox(_("Nothing selected!"), _("ERROR"));
    } else {
        wxFileName* oName=new wxFileName(CurrentDir, filename);
        PlayerDlg->MediaCtrl->ShowPlayerControls(wxMEDIACTRLPLAYERCONTROLS_DEFAULT);
        if (PlayerDlg->MediaCtrl->Load(oName->GetFullPath())) {
            PlayerDlg->Show();
        } else {
            wxMessageBox(_("Unable to play file!"), _("ERROR"));
        }
    }
}

void xScheduleFrame::OnCheckBoxAudioClick(wxCommandEvent& event)
{
    ScanForFiles();
}

void xScheduleFrame::OnCheckBoxVideoClick(wxCommandEvent& event)
{
    ScanForFiles();
}

void xScheduleFrame::OnCheckBoxLORClick(wxCommandEvent& event)
{
    ScanForFiles();
}

void xScheduleFrame::OnCheckBoxVixenClick(wxCommandEvent& event)
{
    ScanForFiles();
}

void xScheduleFrame::OnChoicePlayListSelect(wxCommandEvent& event)
{
}

void xScheduleFrame::OnButtonUpClick(wxCommandEvent& event)
{
    int idx = CheckListBoxPlay->GetSelection();
    if (idx == wxNOT_FOUND) return;
    if (idx == 0) return;
    wxString s = CheckListBoxPlay->GetString((unsigned int)idx);
    bool c = CheckListBoxPlay->IsChecked((unsigned int)idx);
    CheckListBoxPlay->Delete((unsigned int)idx);
    idx--;
    CheckListBoxPlay->Insert(s, (unsigned int)idx);
    CheckListBoxPlay->Check((unsigned int)idx, c);
    CheckListBoxPlay->Select(idx);
}

void xScheduleFrame::OnButtonDownClick(wxCommandEvent& event)
{
    int idx = CheckListBoxPlay->GetSelection();
    if (idx == wxNOT_FOUND) return;
    if (idx == CheckListBoxPlay->GetCount()-1) return;
    wxString s = CheckListBoxPlay->GetString((unsigned int)idx);
    bool c = CheckListBoxPlay->IsChecked((unsigned int)idx);
    CheckListBoxPlay->Delete((unsigned int)idx);
    idx++;
    CheckListBoxPlay->Insert(s, (unsigned int)idx);
    CheckListBoxPlay->Check((unsigned int)idx, c);
    CheckListBoxPlay->Select(idx);
}
