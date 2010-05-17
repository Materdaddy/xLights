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
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/intl.h>
#include <wx/image.h>
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

//(*IdInit(xScheduleFrame)
const long xScheduleFrame::ID_TOGGLEBUTTON1 = wxNewId();
const long xScheduleFrame::ID_TOGGLEBUTTON2 = wxNewId();
const long xScheduleFrame::ID_TOGGLEBUTTON3 = wxNewId();
const long xScheduleFrame::ID_TOGGLEBUTTON4 = wxNewId();
const long xScheduleFrame::ID_STATICTEXT1 = wxNewId();
const long xScheduleFrame::ID_LISTBOX_PLAY = wxNewId();
const long xScheduleFrame::ID_STATICTEXT2 = wxNewId();
const long xScheduleFrame::ID_LISTBOX_SEQ = wxNewId();
const long xScheduleFrame::ID_STATICTEXT3 = wxNewId();
const long xScheduleFrame::ID_TEXTCTRL_LOGIC = wxNewId();
const long xScheduleFrame::ID_STATICTEXT4 = wxNewId();
const long xScheduleFrame::ID_LISTBOX_AV = wxNewId();
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
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("C:\\xlights\\include\\xlights.ico"))));
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
    ToggleButton1 = new wxToggleButton(PanelPlayList, ID_TOGGLEBUTTON1, _("Save List"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON1"));
    BoxSizer1->Add(ToggleButton1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ToggleButton2 = new wxToggleButton(PanelPlayList, ID_TOGGLEBUTTON2, _("Play Item"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON2"));
    BoxSizer1->Add(ToggleButton2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ToggleButton3 = new wxToggleButton(PanelPlayList, ID_TOGGLEBUTTON3, _("Delete Item"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON3"));
    BoxSizer1->Add(ToggleButton3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ToggleButton4 = new wxToggleButton(PanelPlayList, ID_TOGGLEBUTTON4, _("Add Item"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON4"));
    BoxSizer1->Add(ToggleButton4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1 = new wxGridSizer(2, 2, 0, 0);
    FlexGridSizer4 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    FlexGridSizer4->AddGrowableRow(1);
    StaticText1 = new wxStaticText(PanelPlayList, ID_STATICTEXT1, _("Play List"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer4->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ListBoxPlay = new wxListBox(PanelPlayList, ID_LISTBOX_PLAY, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX_PLAY"));
    FlexGridSizer4->Add(ListBoxPlay, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(FlexGridSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer5->AddGrowableCol(0);
    FlexGridSizer5->AddGrowableRow(1);
    StaticText2 = new wxStaticText(PanelPlayList, ID_STATICTEXT2, _("Sequences"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer5->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ListBoxSeq = new wxListBox(PanelPlayList, ID_LISTBOX_SEQ, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX_SEQ"));
    FlexGridSizer5->Add(ListBoxSeq, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(FlexGridSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer6->AddGrowableCol(0);
    FlexGridSizer6->AddGrowableRow(1);
    StaticText3 = new wxStaticText(PanelPlayList, ID_STATICTEXT3, _("Player Logic"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer6->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlLogic = new wxTextCtrl(PanelPlayList, ID_TEXTCTRL_LOGIC, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_LOGIC"));
    FlexGridSizer6->Add(TextCtrlLogic, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(FlexGridSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer7 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer7->AddGrowableCol(0);
    FlexGridSizer7->AddGrowableRow(1);
    StaticText4 = new wxStaticText(PanelPlayList, ID_STATICTEXT4, _("Audio/Video Files"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer7->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ListBoxAV = new wxListBox(PanelPlayList, ID_LISTBOX_AV, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX_AV"));
    FlexGridSizer7->Add(ListBoxAV, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(FlexGridSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAbout);
    //*)

    // Get CurrentDir
    wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));
    if ( !config->Read(_("LastDir"), &CurrentDir) ) {
        wxMessageBox(_("No directory specified"), _("ERROR"));
        Close();
    }
    LoadFilesToLists();
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

void xScheduleFrame::LoadFilesToLists()
{
    wxString filename,ext;
    wxFileName* oName=new wxFileName();
    wxDir* d=new wxDir(CurrentDir);
    oName->AssignDir( CurrentDir );
    if (d->GetFirst(&filename)) {
        do {
            oName->SetFullName(filename);
            ext=oName->GetExt();
            if (ext == _("vix") || ext == _("lms")) {
                ListBoxSeq->AppendString(filename);
            } else if (ext == _("wav") || ext == _("mp3") || ext == _("mp4") ||
                       ext == _("mov") || ext == _("wma") || ext == _("wmv") ||
                       ext == _("aac")) {
                ListBoxAV->AppendString(filename);
            }
        } while (d->GetNext(&filename));
    }
    delete oName;
    delete d;
}
