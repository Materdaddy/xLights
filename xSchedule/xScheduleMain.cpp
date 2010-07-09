/***************************************************************
 * Name:      xScheduleMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-05-15
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

#include "xScheduleMain.h"
#include <wx/msgdlg.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/artprov.h>

//(*InternalHeaders(xScheduleFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

#include "../include/tinyxml.cpp"
#include "../include/tinyxmlerror.cpp"
#include "../include/tinyxmlparser.cpp"
#include "../include/xlights_out.cpp"

#include "../include/xlights.xpm"
#include "../include/add.xpm"
#include "../include/remove.xpm"
#include "../include/floppy_disc.xpm"
#include "../include/help.xpm"
#include "../include/up.xpm"
#include "../include/down.xpm"
#include "../include/play.xpm"

#define XTIMER_INTERVAL 100

class MyArtProvider : public wxArtProvider
{
protected:
    virtual wxBitmap CreateBitmap(const wxArtID& id, const wxArtClient& client,
                                  const wxSize& size);
};

wxBitmap MyArtProvider::CreateBitmap(const wxArtID& id,
                                     const wxArtClient& client,
                                     const wxSize& WXUNUSED(size))
{
    if (client != wxART_TOOLBAR)
        return wxNullBitmap;
    if (id == _("xlights_add"))
        return wxBitmap(add_xpm);
    if (id == _("xlights_remove"))
        return wxBitmap(remove_xpm);
    if (id == _("xlights_floppy_disc"))
        return wxBitmap(floppy_disc_xpm);
    if (id == _("xlights_help"))
        return wxBitmap(help_xpm);
    return wxNullBitmap;
};

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

//(*IdInit(xScheduleFrame)
const long xScheduleFrame::ID_AUITOOLBARITEM_ADD = wxNewId();
const long xScheduleFrame::ID_AUITOOLBARITEM_DEL = wxNewId();
const long xScheduleFrame::ID_AUITOOLBARITEM_HELP = wxNewId();
const long xScheduleFrame::ID_AUITOOLBARITEM_SAVE = wxNewId();
const long xScheduleFrame::ID_AUITOOLBAR1 = wxNewId();
const long xScheduleFrame::ID_PANEL2 = wxNewId();
const long xScheduleFrame::ID_CHOICE_PLAYLIST = wxNewId();
const long xScheduleFrame::ID_STATICTEXT5 = wxNewId();
const long xScheduleFrame::ID_CHOICE_STARTTIME = wxNewId();
const long xScheduleFrame::ID_STATICTEXT6 = wxNewId();
const long xScheduleFrame::ID_CHOICE_ENDTIME = wxNewId();
const long xScheduleFrame::ID_BUTTON_SET = wxNewId();
const long xScheduleFrame::ID_BUTTON_CLEAR = wxNewId();
const long xScheduleFrame::ID_GRID1 = wxNewId();
const long xScheduleFrame::ID_PANEL_CAL = wxNewId();
const long xScheduleFrame::ID_NOTEBOOK1 = wxNewId();
const long xScheduleFrame::ID_PANEL1 = wxNewId();
const long xScheduleFrame::idMenuSave = wxNewId();
const long xScheduleFrame::idMenuQuit = wxNewId();
const long xScheduleFrame::idMenuAddList = wxNewId();
const long xScheduleFrame::idMenuRenameList = wxNewId();
const long xScheduleFrame::idMenuDelList = wxNewId();
const long xScheduleFrame::ID_MENUITEM1 = wxNewId();
const long xScheduleFrame::idMenuHelpContent = wxNewId();
const long xScheduleFrame::idMenuAbout = wxNewId();
const long xScheduleFrame::ID_STATUSBAR1 = wxNewId();
//*)
const long xScheduleFrame::ID_TIMER = wxNewId();


BEGIN_EVENT_TABLE(xScheduleFrame,wxFrame)
    //(*EventTable(xScheduleFrame)
    //*)
    EVT_TIMER(ID_TIMER, xScheduleFrame::OnTimer)
END_EVENT_TABLE()


xScheduleFrame::xScheduleFrame(wxWindow* parent,wxWindowID id) : timer(this, ID_TIMER)
{
    wxArtProvider::Push(new MyArtProvider);

    //(*Initialize(xScheduleFrame)
    wxMenu* MenuHelp;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItemAddList;
    wxFlexGridSizer* FlexGridSizer10;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem4;
    wxFlexGridSizer* FlexGridSizer9;
    wxFlexGridSizer* FlexGridSizer2;
    wxBoxSizer* BoxSizer2;
    wxMenuItem* MenuItemDelList;
    wxMenuItem* MenuItem3;
    wxFlexGridSizer* FlexGridSizer8;
    wxMenu* MenuFile;
    wxMenuItem* MenuItemRenameList;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer11;
    wxBoxSizer* BoxSizer3;
    wxMenu* MenuPlaylist;

    Create(parent, wxID_ANY, _("xSchedule"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(635,311));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("..\\include\\xlights.ico"))));
    	SetIcon(FrameIcon);
    }
    FlexGridSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxNO_BORDER, _T("ID_PANEL1"));
    FlexGridSizer2 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    FlexGridSizer2->AddGrowableRow(1);
    Panel2 = new wxPanel(Panel1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER, _T("ID_PANEL2"));
    AuiManager1 = new wxAuiManager(Panel2, wxAUI_MGR_DEFAULT);
    AuiToolBar1 = new wxAuiToolBar(Panel2, ID_AUITOOLBAR1, wxPoint(6,10), wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM_ADD, _("Add playlist"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlights_add")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Add playlist"), wxEmptyString, NULL);
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM_DEL, _("Delete playlist"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlights_remove")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Delete playlist"), wxEmptyString, NULL);
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM_HELP, _("Help"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlights_help")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Help"), wxEmptyString, NULL);
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM_SAVE, _("Save"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlights_floppy_disc")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Save schedule"), wxEmptyString, NULL);
    AuiToolBar1->Realize();
    AuiManager1->AddPane(AuiToolBar1, wxAuiPaneInfo().Name(_T("PaneName")).ToolbarPane().Caption(_("Pane caption")).Layer(10).Top().Gripper());
    AuiManager1->Update();
    FlexGridSizer2->Add(Panel2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Notebook1 = new wxNotebook(Panel1, ID_NOTEBOOK1, wxDefaultPosition, wxSize(799,275), 0, _T("ID_NOTEBOOK1"));
    PanelCal = new wxPanel(Notebook1, ID_PANEL_CAL, wxPoint(49,10), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_CAL"));
    FlexGridSizer8 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer8->AddGrowableCol(0);
    FlexGridSizer8->AddGrowableRow(1);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    ChoicePlayList = new wxChoice(PanelCal, ID_CHOICE_PLAYLIST, wxDefaultPosition, wxSize(113,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_PLAYLIST"));
    BoxSizer2->Add(ChoicePlayList, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticText5 = new wxStaticText(PanelCal, ID_STATICTEXT5, _("Start"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer9->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ChoiceStartTime = new wxChoice(PanelCal, ID_CHOICE_STARTTIME, wxDefaultPosition, wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_STARTTIME"));
    FlexGridSizer9->Add(ChoiceStartTime, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(FlexGridSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer10 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticText6 = new wxStaticText(PanelCal, ID_STATICTEXT6, _("End"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    FlexGridSizer10->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ChoiceEndTime = new wxChoice(PanelCal, ID_CHOICE_ENDTIME, wxDefaultPosition, wxSize(80,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_ENDTIME"));
    FlexGridSizer10->Add(ChoiceEndTime, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(FlexGridSizer10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer11 = new wxFlexGridSizer(0, 3, 0, 0);
    ButtonSet = new wxButton(PanelCal, ID_BUTTON_SET, _("Set"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SET"));
    FlexGridSizer11->Add(ButtonSet, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonClear = new wxButton(PanelCal, ID_BUTTON_CLEAR, _("Clear"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CLEAR"));
    FlexGridSizer11->Add(ButtonClear, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(FlexGridSizer11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer8->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    Grid1 = new wxGrid(PanelCal, ID_GRID1, wxDefaultPosition, wxSize(696,176), 0, _T("ID_GRID1"));
    Grid1->CreateGrid(26,7);
    Grid1->EnableEditing(false);
    Grid1->EnableGridLines(true);
    Grid1->SetRowLabelSize(25);
    Grid1->SetDefaultRowSize(45, true);
    Grid1->SetDefaultColSize(102, true);
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
    Notebook1->AddPage(PanelCal, _("Calendar"), false);
    FlexGridSizer2->Add(Notebook1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer2);
    FlexGridSizer2->Fit(Panel1);
    FlexGridSizer2->SetSizeHints(Panel1);
    FlexGridSizer1->Add(Panel1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    MenuBar1 = new wxMenuBar();
    MenuFile = new wxMenu();
    MenuItem3 = new wxMenuItem(MenuFile, idMenuSave, _("Save\tCtrl-S"), wxEmptyString, wxITEM_NORMAL);
    MenuFile->Append(MenuItem3);
    MenuItem1 = new wxMenuItem(MenuFile, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    MenuFile->Append(MenuItem1);
    MenuBar1->Append(MenuFile, _("&File"));
    MenuPlaylist = new wxMenu();
    MenuItemAddList = new wxMenuItem(MenuPlaylist, idMenuAddList, _("Add"), wxEmptyString, wxITEM_NORMAL);
    MenuPlaylist->Append(MenuItemAddList);
    MenuItemRenameList = new wxMenuItem(MenuPlaylist, idMenuRenameList, _("Rename"), wxEmptyString, wxITEM_NORMAL);
    MenuPlaylist->Append(MenuItemRenameList);
    MenuItemDelList = new wxMenuItem(MenuPlaylist, idMenuDelList, _("Delete"), wxEmptyString, wxITEM_NORMAL);
    MenuPlaylist->Append(MenuItemDelList);
    MenuItemRefresh = new wxMenuItem(MenuPlaylist, ID_MENUITEM1, _("Refresh"), wxEmptyString, wxITEM_NORMAL);
    MenuPlaylist->Append(MenuItemRefresh);
    MenuBar1->Append(MenuPlaylist, _("Playlist"));
    MenuHelp = new wxMenu();
    MenuItem4 = new wxMenuItem(MenuHelp, idMenuHelpContent, _("Content"), wxEmptyString, wxITEM_NORMAL);
    MenuHelp->Append(MenuItem4);
    MenuItem2 = new wxMenuItem(MenuHelp, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    MenuHelp->Append(MenuItem2);
    MenuBar1->Append(MenuHelp, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_AUITOOLBARITEM_ADD,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemAddClick);
    Connect(ID_AUITOOLBARITEM_DEL,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemDelClick);
    Connect(ID_AUITOOLBARITEM_HELP,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemHelpClick);
    Connect(ID_AUITOOLBARITEM_SAVE,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemSaveClick);
    Connect(ID_BUTTON_SET,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonSetClick);
    Connect(ID_BUTTON_CLEAR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonClearClick);
    Connect(idMenuSave,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemSaveClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnQuit);
    Connect(idMenuAddList,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemAddClick);
    Connect(idMenuRenameList,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnMenuItemRenameListSelected);
    Connect(idMenuDelList,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemDelClick);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnMenuItemRefreshSelected);
    Connect(idMenuHelpContent,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemHelpClick);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAbout);
    //*)

   	wxIcon FrameIcon(xlights_xpm);
   	SetIcon(FrameIcon);
    PlayerDlg = new PlayerDialog(this);
    ResetTimer(NO_SEQ);

    // populate dates on calendar

    int country=wxDateTime::GetCountry();
    CalStart=wxDateTime::Today();

    if (country == wxDateTime::USA) {
        CalStart.SetToWeekDayInSameWeek(wxDateTime::Sun,wxDateTime::Sunday_First);
        datefmt=_("%b %d");
        timefmt=_("%I:%M %p");
    } else {
        Grid1->SetColLabelValue(0, wxDateTime::GetWeekDayName(wxDateTime::Mon, wxDateTime::Name_Full));
        Grid1->SetColLabelValue(1, wxDateTime::GetWeekDayName(wxDateTime::Tue, wxDateTime::Name_Full));
        Grid1->SetColLabelValue(2, wxDateTime::GetWeekDayName(wxDateTime::Wed, wxDateTime::Name_Full));
        Grid1->SetColLabelValue(3, wxDateTime::GetWeekDayName(wxDateTime::Thu, wxDateTime::Name_Full));
        Grid1->SetColLabelValue(4, wxDateTime::GetWeekDayName(wxDateTime::Fri, wxDateTime::Name_Full));
        Grid1->SetColLabelValue(5, wxDateTime::GetWeekDayName(wxDateTime::Sat, wxDateTime::Name_Full));
        Grid1->SetColLabelValue(6, wxDateTime::GetWeekDayName(wxDateTime::Sun, wxDateTime::Name_Full));
        CalStart.SetToWeekDayInSameWeek(wxDateTime::Mon,wxDateTime::Monday_First);
        datefmt=_("%d %b");
        timefmt=_("%X");
    }

    int nrows=Grid1->GetNumberRows();
    CalEnd=CalStart;
    for (int r=0; r<nrows; r++) {
        for (int c=0; c<7; c++) {
            Grid1->SetCellValue(r,c,CalEnd.Format(datefmt));
            CalEnd+=wxDateSpan::Day();
        }
    }

    // populate start & end times

    wxDateTime t;
    t.Set(0,15,0,0); // 15 minutes after midnight
    for (int i=0; i<95; i++) {
        ChoiceStartTime->AppendString(t.Format(timefmt));
        ChoiceEndTime->AppendString(t.Format(timefmt));
        t+=wxTimeSpan::Minutes(15);
    }

    // Get CurrentDir
    wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));
    if ( !config->Read(_("LastDir"), &CurrentDir) ) {
        wxMessageBox(_("No directory specified"), _("Error"));
        Close();
    }

    // Load files
    PortsOK=true;
    networkFile.AssignDir( CurrentDir );
    networkFile.SetFullName(_(XLIGHTS_NETWORK_FILE));
    if (networkFile.FileExists()) {
        LoadNetworkFile();
    }
    if (PortsOK) {
        timer.Start(XTIMER_INTERVAL, wxTIMER_CONTINUOUS);
    }
    scheduleFile.AssignDir( CurrentDir );
    scheduleFile.SetFullName(_(XLIGHTS_SCHEDULE_FILE));
    UnsavedChanges=false;
    if (scheduleFile.FileExists()) {
        LoadScheduleFile();
    }
}

void xScheduleFrame::AddPlaylist(const wxString& name) {
    int id, baseid=1000*Notebook1->GetPageCount();
    //wxPanel* PanelPlayList = new wxPanel(Notebook1, ID_PANEL_PLAYLIST, wxPoint(89,157), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_PLAYLIST"));
    wxPanel* PanelPlayList = new wxPanel(Notebook1);
    wxGridSizer* GridSizer1 = new wxGridSizer(2, 2, 0, 0);
    wxFlexGridSizer* FlexGridSizer4 = new wxFlexGridSizer(3, 1, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    FlexGridSizer4->AddGrowableRow(2);
    wxFlexGridSizer* FlexGridSizer5 = new wxFlexGridSizer(0, 4, 0, 0);
    FlexGridSizer5->AddGrowableCol(0);
    wxStaticText* StaticText1 = new wxStaticText(PanelPlayList, -1, _("Play List"));
    wxFont StaticText1Font(10,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    FlexGridSizer5->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+UP_BUTTON;
    wxBitmapButton* BitmapButtonUp = new wxBitmapButton(PanelPlayList, id, wxBitmap(up_xpm));
    BitmapButtonUp->SetDefault();
    BitmapButtonUp->SetToolTip(_("Move Up"));
    FlexGridSizer5->Add(BitmapButtonUp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonUpClick);

    id=baseid+DOWN_BUTTON;
    wxBitmapButton* BitmapButtonDown = new wxBitmapButton(PanelPlayList, id, wxBitmap(down_xpm));
    BitmapButtonDown->SetDefault();
    BitmapButtonDown->SetToolTip(_("Move Down"));
    FlexGridSizer5->Add(BitmapButtonDown, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonDownClick);

    id=baseid+PLAY_BUTTON;
    wxBitmapButton* ButtonPlay = new wxBitmapButton(PanelPlayList, id, wxBitmap(play_xpm));
    ButtonPlay->SetToolTip(_("Play"));
    ButtonPlay->SetHelpText(_("Plays the currently selected item in the play list"));
    FlexGridSizer5->Add(ButtonPlay, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonPlayClick);

    FlexGridSizer4->Add(FlexGridSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxBoxSizer* BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* StaticText2 = new wxStaticText(PanelPlayList, -1, _("Files:"));
    BoxSizer4->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+CHKBOX_AUDIO;
    wxCheckBox* CheckBoxAudio = new wxCheckBox(PanelPlayList, id, _("Audio"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_AUDIO"));
    CheckBoxAudio->SetValue(false);
    BoxSizer4->Add(CheckBoxAudio, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED, (wxObjectEventFunction)&xScheduleFrame::ScanForFiles);

    id=baseid+CHKBOX_VIDEO;
    wxCheckBox* CheckBoxVideo = new wxCheckBox(PanelPlayList, id, _("Video"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_VIDEO"));
    CheckBoxVideo->SetValue(false);
    BoxSizer4->Add(CheckBoxVideo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED, (wxObjectEventFunction)&xScheduleFrame::ScanForFiles);

    id=baseid+CHKBOX_LOR;
    wxCheckBox* CheckBoxLOR = new wxCheckBox(PanelPlayList, id, _("LOR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_LOR"));
    CheckBoxLOR->SetValue(false);
    BoxSizer4->Add(CheckBoxLOR, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED, (wxObjectEventFunction)&xScheduleFrame::ScanForFiles);

    id=baseid+CHKBOX_VIXEN;
    wxCheckBox* CheckBoxVixen = new wxCheckBox(PanelPlayList, id, _("Vixen"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_VIXEN"));
    CheckBoxVixen->SetValue(false);
    BoxSizer4->Add(CheckBoxVixen, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED, (wxObjectEventFunction)&xScheduleFrame::ScanForFiles);

    FlexGridSizer4->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+PLAYLIST;
    wxCheckListBox* CheckListBoxPlay = new wxCheckListBox(PanelPlayList, id, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX_PLAY"));
    FlexGridSizer4->Add(CheckListBoxPlay, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(FlexGridSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxFlexGridSizer* FlexGridSizer6 = new wxFlexGridSizer(3, 1, 0, 0);
    FlexGridSizer6->AddGrowableCol(0);
    FlexGridSizer6->AddGrowableRow(1);
    wxFlexGridSizer* FlexGridSizer7 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer7->AddGrowableCol(1);
    wxStaticText* StaticText3 = new wxStaticText(PanelPlayList, -1, _("Player Logic"));
    wxFont StaticText3Font(10,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText3->SetFont(StaticText3Font);
    FlexGridSizer7->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    wxChoice* ChoiceLogic = new wxChoice(PanelPlayList, -1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_LOGIC"));
    FlexGridSizer7->Add(ChoiceLogic, 1, wxALL|wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6->Add(FlexGridSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxTextCtrl* TextCtrlLogic = new wxTextCtrl(PanelPlayList, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL_LOGIC"));
    FlexGridSizer6->Add(TextCtrlLogic, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(FlexGridSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelPlayList->SetSizer(GridSizer1);
    GridSizer1->Fit(PanelPlayList);
    GridSizer1->SetSizeHints(PanelPlayList);
    Notebook1->AddPage(PanelPlayList, name, true);
    ChoicePlayList->AppendString(name);
}

xScheduleFrame::~xScheduleFrame()
{
    if (UnsavedChanges) {
        wxMessageDialog confirm(this, _("Save changes?"), _("Confirm"), wxYES|wxNO);
        if (confirm.ShowModal() == wxID_YES) {
            SaveFile();
        }
    }
    if (timer.IsRunning()) timer.Stop();
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

void xScheduleFrame::TimerNoPlay() {
    wxTimeSpan ts = wxDateTime::UNow() - starttime;
    long msec = ts.GetMilliseconds().ToLong();
    xout.TimerStart(msec);
    xout.TimerEnd();
    //wxString msg = wxString::Format(_("TimerNoPlay %d"),msec);
    //StatusBar1->SetStatusText(msg);
}

void xScheduleFrame::ResetTimer(SeqPlayerStates newstate) {
    SeqPlayerState = newstate;
    xout.ResetTimer();
    starttime = wxDateTime::UNow();
}

void xScheduleFrame::OnTimer(wxTimerEvent& event)
{
    long msec=0;
    int startmsec, endmsec, duration, lorintensity, startint, endint, period;
    int netnum, chindex;
    static long lastmsec;
    static LorEventMap::iterator LorIter;
    static std::string LastIntensity;
    char vixintensity;
    TiXmlElement* e;
    wxString action;
    wxTimeSpan ts;
    switch (SeqPlayerState) {
        case PLAYING_LOR:
            if (PlayerDlg->MediaCtrl->GetState() != wxMEDIASTATE_PLAYING) {
                ResetTimer(PAUSE_LOR);
                return;
            }
            msec = PlayerDlg->MediaCtrl->Tell();
            xout.TimerStart(msec);
            while (LorIter != LorEvents.end()) {

                startmsec=LorIter->first * 10;
                if (startmsec > msec) break;
                endmsec=LorIter->second->EndCentiSec * 10;
                netnum=LorIter->second->netnum;
                chindex=LorIter->second->chindex;
                e=LorIter->second->xmldata;
                if (e) {
                    action=GetAttribute(e,"type");
                    if (e->QueryIntAttribute("intensity",&lorintensity) == TIXML_SUCCESS) {
                        if (action == _("intensity")) {
                            xout.SetIntensity(netnum,chindex,lorintensity);
                        } else if (action == _("twinkle")) {
                            xout.twinkle(netnum,chindex,400,lorintensity);
                        } else if (action == _("shimmer")) {
                            xout.shimmer(netnum,chindex,100,lorintensity);
                        }
                    } else if (e->QueryIntAttribute("startIntensity",&startint) == TIXML_SUCCESS) {
                        if (e->QueryIntAttribute("endIntensity",&endint) == TIXML_SUCCESS) {
                            duration = endmsec - startmsec;
                            if (action == _("intensity")) {
                                xout.ramp(netnum,chindex,duration,startint,endint);
                            } else if (action == _("twinkle")) {
                                xout.twinklefade(netnum,chindex,400,duration,startint,endint);
                            } else if (action == _("shimmer")) {
                                xout.shimmerfade(netnum,100,chindex,duration,startint,endint);
                            }
                        }
                    }
                } else {
                    xout.off(netnum,chindex);
                }

                LorIter++;
            }
            xout.TimerEnd();
            break;
        case PAUSE_LOR:
            if (PlayerDlg->MediaCtrl->GetState() == wxMEDIASTATE_PLAYING) {
                ResetTimer(PLAYING_LOR);
                msec = PlayerDlg->MediaCtrl->Tell();
                LorIter=msec < 500 ? LorEvents.begin() : LorEvents.lower_bound(msec / 10);
            } else {
                TimerNoPlay();
            }
            break;
        case PLAYING_VIX:
            if (PlayerDlg->MediaCtrl->GetState() != wxMEDIASTATE_PLAYING) {
                ResetTimer(PAUSE_VIX);
                return;
            }
            msec = PlayerDlg->MediaCtrl->Tell();
            period = msec / VixEventPeriod;
            xout.TimerStart(msec);
            if (period < VixNumPeriods) {
                for (chindex=0; chindex<VixLastChannel; chindex++) {
                    vixintensity=VixEventData[chindex*VixNumPeriods+period];
                    if (vixintensity != LastIntensity[chindex]) {
                        xout.SetIntensity(VixNetwork[chindex], chindex, vixintensity);
                        LastIntensity[chindex]=vixintensity;
                    }
                }
            }
            xout.TimerEnd();
            break;
        case PAUSE_VIX:
            if (PlayerDlg->MediaCtrl->GetState() == wxMEDIASTATE_PLAYING) {
                if (VixLastChannel > VixNetwork.size()) VixLastChannel=VixNetwork.size();
                LastIntensity.resize(VixLastChannel,1);
                ResetTimer(PLAYING_VIX);
            } else {
                TimerNoPlay();
            }
            break;
        default:
            TimerNoPlay();
            break;
    }
    lastmsec=msec;
}

wxString xScheduleFrame::GetAttribute(TiXmlElement* e, const char *attr)
{
    wxString s(e->Attribute(attr), wxConvUTF8);
    return s;
}

void xScheduleFrame::LoadNetworkFile()
{
    wxString FileName=networkFile.GetFullPath();
    TiXmlDocument doc( FileName.mb_str() );
    if (doc.LoadFile()) {
        int r=0;
        for( TiXmlElement* e=doc.RootElement()->FirstChildElement(); e!=NULL; e=e->NextSiblingElement() ) {
            if (e->ValueStr() == "network") {
                AddNetwork(GetAttribute(e,"NetworkType"),
                           GetAttribute(e,"ComPort"),
                           GetAttribute(e,"BaudRate"),
                           atoi(GetAttribute(e,"MaxChannels").mb_str(wxConvUTF8)));
                r++;
            }
        }
    } else {
        wxString msg(doc.ErrorDesc(), wxConvUTF8);
        wxMessageBox(msg, _("Error Loading Network File"));
    }
}

void xScheduleFrame::AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels)
{
    int netnum=-1;
    wxString net3 = NetworkType.Left(3);
    int baud = atoi(BaudRate.mb_str(wxConvUTF8));
    char port[20];
    strcpy( port, (const char*)ComPort.mb_str(wxConvUTF8) );
    try {
        if (net3 == _("LOR")) {
            netnum=xout.addnetwork(new xNetwork_LOR(),MaxChannels,port,baud);
        } else if (net3 == _("Ren")) {
            netnum=xout.addnetwork(new xNetwork_Renard(),MaxChannels,port,baud);
        } else if (net3 == _("DMX")) {
            netnum=xout.addnetwork(new xNetwork_DMXentec(),MaxChannels,port,baud);
        }
    }
    catch (const char *str) {
        wxString errmsg(str,wxConvUTF8);
        wxString msg = wxString::Format(_("Error occurred while connecting to %s network on %s\n\n"),NetworkType.c_str(),ComPort.c_str());
        wxMessageBox(msg+errmsg, _("Communication Error"));
        PortsOK=false;
    }
    catch (char *str) {
        wxString errmsg(str,wxConvUTF8);
        wxString msg = wxString::Format(_("Error occurred while connecting to %s network on %s\n\n"),NetworkType.c_str(),ComPort.c_str());
        wxMessageBox(msg+errmsg, _("Communication Error"));
        PortsOK=false;
    }
    for (int i=0; i<MaxChannels; i++)
        VixNetwork.push_back(netnum);
}

void xScheduleFrame::ScanForFiles()
{
    wxString filename;
    bool ok;
    int i;

    int baseid=1000*Notebook1->GetSelection();
    wxCheckListBox* CheckListBoxPlay=(wxCheckListBox*)wxWindow::FindWindowById(baseid+PLAYLIST,Notebook1);
    wxCheckBox* CheckBoxAudio=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_AUDIO,Notebook1);
    wxCheckBox* CheckBoxVideo=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_VIDEO,Notebook1);
    wxCheckBox* CheckBoxLOR=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_LOR,Notebook1);
    wxCheckBox* CheckBoxVixen=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_VIXEN,Notebook1);

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
        if (!ok || !oName->FileExists()) {
            CheckListBoxPlay->Delete(i);
            UnsavedChanges=true;
        }
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
                UnsavedChanges=true;
            }
        } while (d->GetNext(&filename));
    }
    delete d;
    delete oName;
}

// returns V for vixen, L for LOR, a for audio, v for video
char xScheduleFrame::ExtType(const wxString& ext) {
    if (ext == _("vix")) {
        return 'V';
    } else if (ext == _("lms")) {
        return 'L';
    } else if (ext == _("wav") || ext == _("mp3") ||
               ext == _("wma") || ext == _("aac")) {
        return 'a';
    } else if (ext == _("avi") || ext == _("mp4") ||
               ext == _("wmv") || ext == _("mov")) {
        return 'v';
    }
    return ' ';
}

void xScheduleFrame::OnButtonPlayClick()
{
    int baseid=1000*Notebook1->GetSelection();
    wxCheckListBox* CheckListBoxPlay=(wxCheckListBox*)wxWindow::FindWindowById(baseid+PLAYLIST,Notebook1);
    wxString filename = CheckListBoxPlay->GetStringSelection();
    if (filename.IsEmpty()) {
        wxMessageBox(_("Nothing selected!"), _("Error"));
    } else {
        wxFileName oName(CurrentDir, filename);
        wxString fullpath=oName.GetFullPath();
        PlayerDlg->MediaCtrl->ShowPlayerControls(wxMEDIACTRLPLAYERCONTROLS_DEFAULT);
        switch (ExtType(oName.GetExt())) {
            case 'a':
            case 'v':
                if (wxFile::Exists(fullpath) && PlayerDlg->MediaCtrl->Load(fullpath)) {
                    PlayerDlg->Show();
                } else {
                    wxMessageBox(_("Unable to play file:\n")+fullpath, _("Error"));
                }
                break;
            case 'L':
                PlayLorFile(fullpath);
                break;
            case 'V':
                PlayVixenFile(fullpath);
                break;
        }
    }
}

void xScheduleFrame::PlayLorFile(wxString& FileName)
{
    if (!PortsOK) {
        wxMessageBox(_("Serial ports did not initialize at program startup.\nPlug in your dongles/adapters and restart the program."), _("Error"));
        return;
    }
    LorEvents.clear();
    TiXmlDocument doc( FileName.mb_str() );
    if (doc.LoadFile()) {
        TiXmlElement* root=doc.RootElement();
        wxString musicFilename(root->Attribute("musicFilename"), wxConvUTF8);
        for( TiXmlElement* e=root->FirstChildElement(); e!=NULL; e=e->NextSiblingElement() ) {
            if (e->ValueStr() == "channels") {
                LoadLorChannels(e);
            }
        }
        xout.SetMaxIntensity(100);

        wxFileName fn1(musicFilename);
        if (!fn1.FileExists()) {
            wxFileName fn2(CurrentDir,fn1.GetFullName());
            musicFilename=fn2.GetFullPath();
        }
        if (wxFile::Exists(musicFilename) && PlayerDlg->MediaCtrl->Load(musicFilename)) {
            ResetTimer(PAUSE_LOR);
            PlayerDlg->ShowModal();
            ResetTimer(NO_SEQ);
        } else {
            wxMessageBox(_("Unable to play file:\n")+musicFilename, _("Error"));
        }
    } else {
        wxString msg(doc.ErrorDesc(), wxConvUTF8);
        wxMessageBox(msg, _("Error Loading File"));
    }
}

void xScheduleFrame::LoadLorChannels(TiXmlElement* n)
{
    int netnum, unit, circuit;
    for( TiXmlElement* e=n->FirstChildElement(); e!=NULL; e=e->NextSiblingElement() ) {
        if (e->ValueStr() == "channel") {
            if (e->QueryIntAttribute("unit",&unit) == TIXML_SUCCESS &&
                e->QueryIntAttribute("circuit",&circuit) == TIXML_SUCCESS) {
                if (e->QueryIntAttribute("network",&netnum) != TIXML_SUCCESS) {
                    netnum=0;
                }
                LoadLorChannel(e,netnum,(unit-1)*16+circuit-1);
            }
        }
    }
}

void xScheduleFrame::LoadLorChannel(TiXmlElement* n, int netnum, int chindex)
{
    int start,end,lastend=0;
    if (!PortsOK) {
        wxMessageBox(_("Serial ports did not initialize at program startup.\nPlug in your dongles/adapters and restart the program."), _("Error"));
        return;
    }
    for( TiXmlElement* e=n->FirstChildElement(); e!=NULL; e=e->NextSiblingElement() ) {
        if (e->ValueStr() == "effect") {
            if (e->QueryIntAttribute("startCentisecond",&start) == TIXML_SUCCESS &&
                e->QueryIntAttribute("endCentisecond",&end) == TIXML_SUCCESS) {
                if (start != lastend && lastend > 0) {
                    LorEvents.insert(LorEventPair(lastend, new LorEventClass(netnum,chindex,start,0)));
                }
                LorEvents.insert(LorEventPair(start, new LorEventClass(netnum,chindex,end,e)));
                lastend=end;
            }
        }
    }
    LorEvents.insert(LorEventPair(lastend, new LorEventClass(netnum,chindex,lastend,0)));
}

void xScheduleFrame::PlayVixenFile(wxString& FileName)
{
    int MaxIntensity = 255;
    int toValue;
    std::string tag;
    wxFileName fn;
    const TiXmlNode* xmlNode;
    const TiXmlElement* pluginNode;
    const TiXmlText* textNode;
    fn.AssignDir(CurrentDir);
    if (!PortsOK) {
        wxMessageBox(_("Serial ports did not initialize at program startup.\nPlug in your dongles/adapters and restart the program."), _("Error"));
        return;
    }
    VixLastChannel = -1;
    VixEventPeriod=-1;
    TiXmlDocument doc( FileName.mb_str() );
    if (doc.LoadFile()) {
        TiXmlElement* root=doc.RootElement();
        for( TiXmlElement* e=root->FirstChildElement(); e!=NULL; e=e->NextSiblingElement() ) {
            tag = e->ValueStr();
            if (tag == "EventPeriodInMilliseconds") {
                VixEventPeriod = atoi(e->GetText());
            } else if (tag == "MaximumLevel") {
                MaxIntensity = atoi(e->GetText());
            } else if (tag == "Audio" || tag == "Song") {
                wxString filename(e->Attribute("filename"), wxConvUTF8);
                fn.SetFullName(filename);
            } else if (tag == "EventValues") {
                xmlNode = e->FirstChild();
                if (xmlNode && xmlNode->Type() == TiXmlNode::TEXT) {
                    textNode=xmlNode->ToText();
                    VixEventData = base64_decode(textNode->ValueStr());
                }
            } else if (tag == "PlugInData") {
                xmlNode = e->FirstChild("PlugIn");
                if (xmlNode) {
                    pluginNode=xmlNode->ToElement();
                    if (pluginNode->QueryIntAttribute("to",&toValue) == TIXML_SUCCESS) {
                        if (toValue > VixLastChannel) VixLastChannel=toValue;
                    }
                }
            }
        }
        xout.SetMaxIntensity(MaxIntensity);

        if (VixEventPeriod < 0) {
            wxMessageBox(_("EventPeriodInMilliseconds is undefined"), _("Vixen Error"));
        } else if (VixLastChannel < 0) {
            wxMessageBox(_("Unable to determine number of channels"), _("Vixen Error"));
        } else if (!fn.FileExists()) {
            wxMessageBox(_("No such file:\n")+fn.GetFullPath(), _("Vixen Error"));
        } else if (!PlayerDlg->MediaCtrl->Load(fn.GetFullPath())) {
            wxMessageBox(_("Unable to play file:\n")+fn.GetFullPath(), _("Vixen Error"));
        } else {
            VixNumPeriods = VixEventData.size() / VixLastChannel;
            wxString msg = wxString::Format(_("Data size=%d, Channel Count=%d, NumPeriods=%d, Period Len=%d, Media File=%s"),VixEventData.size(),VixLastChannel,VixNumPeriods,VixEventPeriod,fn.GetFullPath().c_str());
            StatusBar1->SetStatusText(msg);
            ResetTimer(PAUSE_VIX);
            PlayerDlg->ShowModal();
            ResetTimer(NO_SEQ);
        }
    } else {
        wxString msg(doc.ErrorDesc(), wxConvUTF8);
        wxMessageBox(msg, _("Error Loading File"));
    }
}

void xScheduleFrame::OnButtonUpClick()
{
    int baseid=1000*Notebook1->GetSelection();
    wxCheckListBox* CheckListBoxPlay=(wxCheckListBox*)wxWindow::FindWindowById(baseid+PLAYLIST,Notebook1);
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
    UnsavedChanges=true;
}

void xScheduleFrame::OnButtonDownClick()
{
    int baseid=1000*Notebook1->GetSelection();
    wxCheckListBox* CheckListBoxPlay=(wxCheckListBox*)wxWindow::FindWindowById(baseid+PLAYLIST,Notebook1);
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
    UnsavedChanges=true;
}

void xScheduleFrame::OnAuiToolBarItemAddClick(wxCommandEvent& event)
{
    NewListDialog dialog(this);
    if (dialog.ShowModal() != wxID_OK) return;
    wxString name=dialog.TextCtrlNewName->GetValue();
    if (name.IsEmpty()) return;
    int cnt=Notebook1->GetPageCount();
    for (int i=0; i<cnt; i++) {
        if (Notebook1->GetPageText(i) == name) {
            wxMessageBox(_("That name is already in use!"), _("Error"));
            return;
        }
    }
    AddPlaylist(name);
    UnsavedChanges=true;
}

void xScheduleFrame::OnAuiToolBarItemDelClick(wxCommandEvent& event)
{
    DelListDialog dialog(this);
    int idx=Notebook1->GetSelection();
    if (idx == 0) {
        wxMessageBox(_("Can't delete the calendar!"), _("Error"));
        return;
    }
    dialog.StaticTextDelName->SetLabel(Notebook1->GetPageText(idx));
    if (dialog.ShowModal() != wxID_OK) return;
    Notebook1->DeletePage(idx);
    ChoicePlayList->Delete(idx-1);
    UnsavedChanges=true;
}

void xScheduleFrame::OnMenuItemRenameListSelected(wxCommandEvent& event)
{
    RenListDialog dialog(this);
    int idx=Notebook1->GetSelection();
    if (idx == 0) {
        wxMessageBox(_("Can't rename the calendar!"), _("Error"));
        return;
    }
    if (dialog.ShowModal() != wxID_OK) return;
    wxString name=dialog.TextCtrlRename->GetValue();
    if (name.IsEmpty()) return;
    int cnt=Notebook1->GetPageCount();
    for (int i=0; i<cnt; i++) {
        if (Notebook1->GetPageText(i) == name && i != idx) {
            wxMessageBox(_("That name is already in use!"), _("Error"));
            return;
        }
    }
    Notebook1->SetPageText(idx,name);
    ChoicePlayList->SetString(idx-1,name);
    UnsavedChanges=true;
}

void xScheduleFrame::OnAuiToolBarItemHelpClick(wxCommandEvent& event)
{
}

void xScheduleFrame::OnAuiToolBarItemSaveClick(wxCommandEvent& event)
{
    SaveFile();
}

void xScheduleFrame::SaveFile()
{
    unsigned int RowCount,baseid;
    TiXmlElement* plist;
    TiXmlElement* item;
    wxCheckBox* chkbox;
    wxString FileName=scheduleFile.GetFullPath();
    TiXmlDocument doc( FileName.mb_str() );
    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
    doc.LinkEndChild( decl );
    TiXmlElement* root = new TiXmlElement( "xSchedule" );
    root->SetAttribute("computer", wxGetHostName().mb_str());
    doc.LinkEndChild( root );

    // save calendar
    TiXmlElement* sched = new TiXmlElement( "schedule" );
    root->LinkEndChild( sched );
    int nrows=Grid1->GetNumberRows();
    wxDateTime t1,t2,d=CalStart;
    wxString v,v1,playlist,timerange;
    for (int r=0; r<nrows; r++) {
        for (int c=0; c<7; c++) {
            v=Grid1->GetCellValue(r,c);
            v1=v.AfterFirst('\n');
            if (!v1.IsEmpty()) {
                playlist=v1.BeforeFirst('\n');
                timerange=v1.AfterFirst('\n');
                t1.ParseTime(timerange.BeforeFirst('-'));
                t2.ParseTime(timerange.AfterFirst('-'));
                item = new TiXmlElement( "playdate" );
                item->SetAttribute("playlist", playlist.mb_str());
                item->SetAttribute("date", d.FormatISODate().mb_str());
                item->SetAttribute("timestart", t1.FormatISOTime().mb_str());
                item->SetAttribute("timeend", t2.FormatISOTime().mb_str());
                sched->LinkEndChild( item );
            }
            d+=wxDateSpan::Day();
        }
    }

    // save playlists
    TiXmlElement* lists = new TiXmlElement( "playlists" );
    root->LinkEndChild( lists );

    int cnt=Notebook1->GetPageCount();
    for (int pagenum=1; pagenum < cnt; pagenum++) {
        plist = new TiXmlElement( "playlist" );
        plist->SetAttribute("name", Notebook1->GetPageText(pagenum).mb_str());
        baseid=1000*pagenum;
        wxCheckListBox* CheckListBoxPlay=(wxCheckListBox*)wxWindow::FindWindowById(baseid+PLAYLIST,Notebook1);
        for (int i=CHKBOX_AUDIO; i<=CHKBOX_VIXEN; i++) {
            chkbox=(wxCheckBox*)wxWindow::FindWindowById(baseid+i,Notebook1);
            plist->SetAttribute(chkbox->GetLabelText().mb_str(), chkbox->GetValue() ? "1" : "0");
        }
        lists->LinkEndChild( plist );
        RowCount=CheckListBoxPlay->GetCount();
        for (unsigned int r=0; r < RowCount; r++ ) {
            item = new TiXmlElement( "listitem" );
            item->SetAttribute("name",CheckListBoxPlay->GetString(r).mb_str());
            item->SetAttribute("enabled",CheckListBoxPlay->IsChecked(r) ? "1" : "0");
            plist->LinkEndChild( item );
        }
    }

    // commit to disk
    if (doc.SaveFile()) {
        UnsavedChanges=false;
        StatusBar1->SetStatusText(_("File saved successfully"));
    } else {
        wxString msg(doc.ErrorDesc(), wxConvUTF8);
        wxMessageBox(msg, _("Error Saving File"));
    }
}

void xScheduleFrame::LoadScheduleFile()
{
    wxString FileName=scheduleFile.GetFullPath();
    TiXmlDocument doc( FileName.mb_str() );
    if (doc.LoadFile()) {
        TiXmlElement* root=doc.RootElement();
        for( TiXmlElement* e=root->FirstChildElement(); e!=NULL; e=e->NextSiblingElement() ) {
            if (e->ValueStr() == "schedule") {
                LoadSchedule(e);
            } else if (e->ValueStr() == "playlists") {
                LoadPlaylists(e);
            }
        }
    } else {
        wxString msg(doc.ErrorDesc(), wxConvUTF8);
        wxMessageBox(msg, _("Error Loading File"));
    }
}

void xScheduleFrame::LoadSchedule(TiXmlElement* n)
{
    wxDateTime d,t1,t2;
    int days,r,c;
    for( TiXmlElement* e=n->FirstChildElement(); e!=NULL; e=e->NextSiblingElement() ) {
        if (e->ValueStr() == "playdate") {
            wxString playlist(e->Attribute("playlist"), wxConvUTF8);
            wxString playdate(e->Attribute("date"), wxConvUTF8);
            wxString time1(e->Attribute("timestart"), wxConvUTF8);
            wxString time2(e->Attribute("timeend"), wxConvUTF8);
            if (d.ParseFormat(playdate,_("%Y-%m-%d")) == NULL) {
                wxMessageBox(_("Invalid date in schedule file!"));
                return;
            } else if (d.IsBetween(CalStart,CalEnd)) {
                wxTimeSpan ts=d.Subtract(CalStart);
                days=ts.GetDays();
                r=days / 7;
                c=days % 7;
                t1.ParseFormat(time1,_("%H:%M:%S"));
                t2.ParseFormat(time2,_("%H:%M:%S"));
                time1=t1.Format(timefmt);
                time2=t2.Format(timefmt);
                SetGridCell(r,c,playlist,time1,time2);
            }
        }
    }
}

void xScheduleFrame::LoadPlaylists(TiXmlElement* n)
{
    for( TiXmlElement* e=n->FirstChildElement(); e!=NULL; e=e->NextSiblingElement() ) {
        if (e->ValueStr() == "playlist") {
            LoadPlaylist(e);
        }
    }
}

void xScheduleFrame::LoadPlaylist(TiXmlElement* n)
{
    wxCheckBox* chkbox;
    wxString name(n->Attribute("name"), wxConvUTF8);
    int baseid=1000*Notebook1->GetPageCount();
    AddPlaylist(name);
    for (int i=CHKBOX_AUDIO; i<=CHKBOX_VIXEN; i++) {
        chkbox=(wxCheckBox*)wxWindow::FindWindowById(baseid+i,Notebook1);
        chkbox->SetValue( strncmp(n->Attribute(chkbox->GetLabelText().mb_str()), "0", 1) );
    }
    wxCheckListBox* CheckListBoxPlay=(wxCheckListBox*)wxWindow::FindWindowById(baseid+PLAYLIST,Notebook1);
    int cnt=0;
    for( TiXmlElement* e=n->FirstChildElement(); e!=NULL; e=e->NextSiblingElement() ) {
        if (e->ValueStr() == "listitem") {
            wxString itemname(e->Attribute("name"), wxConvUTF8);
            bool itemchecked=(strncmp(e->Attribute("enabled"),"1",1) == 0);
            CheckListBoxPlay->AppendString(itemname);
            CheckListBoxPlay->Check(cnt,itemchecked);
            cnt++;
        }
    }
    ScanForFiles();
}

void xScheduleFrame::OnButtonSetClick(wxCommandEvent& event)
{
    wxString plist = ChoicePlayList->GetStringSelection();
    if (plist.IsEmpty()) {
        wxMessageBox(_("Select a play list first!"));
        return;
    }
    int StartIdx = ChoiceStartTime->GetSelection();
    if (StartIdx == wxNOT_FOUND) {
        wxMessageBox(_("Select a start time!"));
        return;
    }
    int EndIdx = ChoiceEndTime->GetSelection();
    if (EndIdx == wxNOT_FOUND) {
        wxMessageBox(_("Select a end time!"));
        return;
    }
    if (StartIdx >= EndIdx) {
        wxMessageBox(_("Start time must be before the end time!"));
        return;
    }
    wxString StartStr = ChoiceStartTime->GetStringSelection();
    wxString EndStr = ChoiceEndTime->GetStringSelection();
    GridSelection selCells = this->getGridSelection(*Grid1);
    GridSelection::iterator it;
    for (it = selCells.begin(); it != selCells.end(); it++) {
        this->SetGridCell(it->first,it->second,plist,StartStr,EndStr);
    }
}

void xScheduleFrame::SetGridCell(const int& row, const int& col,
                                 wxString& playlist,
                                 wxString& timestart,
                                 wxString& timeend)
{
    wxString s = Grid1->GetCellValue(row,col);
    s = s.BeforeFirst('\n');
    s.Append(_("\n")+playlist+_("\n")+timestart+_("-")+timeend);
    Grid1->SetCellValue(row,col,s);
}

void xScheduleFrame::ClearGridCell(const int& row, const int& col)
{
    wxString s = Grid1->GetCellValue(row,col);
    s = s.BeforeFirst('\n');
    Grid1->SetCellValue(row,col,s);
}

void xScheduleFrame::OnButtonClearClick(wxCommandEvent& event)
{
    GridSelection selCells = this->getGridSelection(*Grid1);
    GridSelection::iterator it;
    for (it = selCells.begin(); it != selCells.end(); it++) {
        this->ClearGridCell(it->first,it->second);
    }
}

// from http://aubedesheros.blogspot.com/2009/10/cellules-selectionnees-dune-wxgrid.html
GridSelection xScheduleFrame::getGridSelection(wxGrid & grid)
{
  GridSelection selection;

  wxGridCellCoordsArray topLeft = grid.GetSelectionBlockTopLeft();
  wxGridCellCoordsArray bottomRight = grid.GetSelectionBlockBottomRight();
  for(size_t i = 0; i < std::min(topLeft.GetCount(), bottomRight.GetCount()); i++)
  {
    for(int row = topLeft.Item(i).GetRow(); row <= bottomRight.Item(i).GetRow(); row++)
    {
      for(int col = topLeft.Item(i).GetCol(); col <= bottomRight.Item(i).GetCol(); col++)
      {
        selection.insert(std::make_pair(row, col));
      }
    }
  }

  wxGridCellCoordsArray cellSelection = grid.GetSelectedCells();
  for(size_t i = 0; i < cellSelection.GetCount(); i++)
  {
    selection.insert(std::make_pair(cellSelection.Item(i).GetRow(), cellSelection.Item(i).GetCol()));
  }

  wxArrayInt selectedRows = grid.GetSelectedRows();
  for(size_t i = 0; i < selectedRows.GetCount(); i++)
  {
    for(int col = 0; col < grid.GetNumberCols(); col++)
    {
      selection.insert(std::make_pair(selectedRows.Item(i), col));
    }
  }

  wxArrayInt selectedCols = grid.GetSelectedCols();
  for(size_t i = 0; i < selectedCols.GetCount(); i++)
  {
    for(int row = 0; row < grid.GetNumberRows(); row++)
    {
      selection.insert(std::make_pair(row, selectedCols.Item(i)));
    }
  }

  return selection;
}


// from: http://www.adp-gmbh.ch/cpp/common/base64.html
// Copyright (C) 2004-2008 René Nyffenegger
static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string xScheduleFrame::base64_decode(std::string const& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}


void xScheduleFrame::OnMenuItemRefreshSelected(wxCommandEvent& event)
{
    ScanForFiles();
}
