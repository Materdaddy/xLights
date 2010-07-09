/***************************************************************
 * Name:      MainMenuMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-02-27
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

#include "wx_pch.h"
#include "MainMenuMain.h"
#include <wx/msgdlg.h>
#include <wx/filename.h>
#include <wx/config.h>
#include <wx/utils.h>

#include "../include/xlights.xpm"


//(*InternalHeaders(MainMenuFrame)
#include <wx/font.h>
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

//(*IdInit(MainMenuFrame)
const long MainMenuFrame::ID_STATICTEXT1 = wxNewId();
const long MainMenuFrame::ID_STATICTEXT2 = wxNewId();
const long MainMenuFrame::ID_BUTTON5 = wxNewId();
const long MainMenuFrame::ID_BUTTON_NETWORK_SETUP = wxNewId();
const long MainMenuFrame::ID_BUTTON_SEQUENCE = wxNewId();
const long MainMenuFrame::ID_BUTTON_SCHEDULE = wxNewId();
const long MainMenuFrame::ID_BUTTON_TEST = wxNewId();
const long MainMenuFrame::ID_PANEL1 = wxNewId();
const long MainMenuFrame::idMenuOpen = wxNewId();
const long MainMenuFrame::idMenuQuit = wxNewId();
const long MainMenuFrame::idMenuAbout = wxNewId();
const long MainMenuFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(MainMenuFrame,wxFrame)
    //(*EventTable(MainMenuFrame)
    //*)
END_EVENT_TABLE()

MainMenuFrame::MainMenuFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(MainMenuFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("xLights"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(204,368));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE, _T("ID_PANEL1"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(1);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("xLights"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText1->SetForegroundColour(wxColour(255,0,0));
    wxFont StaticText1Font(18,wxDEFAULT,wxFONTSTYLE_ITALIC,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    FlexGridSizer1->Add(StaticText1, 0, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, Panel1, _("Show Directory"));
    StaticTextDirName = new wxStaticText(Panel1, ID_STATICTEXT2, _("<No directory selected>"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticTextDirName->SetMinSize(wxSize(300,0));
    StaticBoxSizer1->Add(StaticTextDirName, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonChangeDir = new wxButton(Panel1, ID_BUTTON5, _("Change"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    StaticBoxSizer1->Add(ButtonChangeDir, 1, wxALL|wxFIXED_MINSIZE|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    ButtonNetworkSetup = new wxButton(Panel1, ID_BUTTON_NETWORK_SETUP, _("Network Setup"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_NETWORK_SETUP"));
    ButtonNetworkSetup->Disable();
    BoxSizer3->Add(ButtonNetworkSetup, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonSequence = new wxButton(Panel1, ID_BUTTON_SEQUENCE, _("Sequence"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SEQUENCE"));
    ButtonSequence->Disable();
    BoxSizer3->Add(ButtonSequence, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonSchedule = new wxButton(Panel1, ID_BUTTON_SCHEDULE, _("Schedule"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SCHEDULE"));
    ButtonSchedule->Disable();
    BoxSizer3->Add(ButtonSchedule, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonTest = new wxButton(Panel1, ID_BUTTON_TEST, _("Lighting Test"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_TEST"));
    ButtonTest->Disable();
    BoxSizer3->Add(ButtonTest, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(BoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(Panel1);
    FlexGridSizer1->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, idMenuOpen, _("Open Folder"), _("Open show folder"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
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
    DirDialog1 = new wxDirDialog(this, _("Select Show Directory"), wxEmptyString, wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxDirDialog"));
    BoxSizer1->SetSizeHints(this);

    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainMenuFrame::OnMenuOpenFolderSelected);
    Connect(ID_BUTTON_NETWORK_SETUP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainMenuFrame::OnButtonNetworkSetupClick);
    Connect(ID_BUTTON_SEQUENCE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainMenuFrame::OnButtonSequenceClick);
    Connect(ID_BUTTON_SCHEDULE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainMenuFrame::OnButtonScheduleClick);
    Connect(ID_BUTTON_TEST,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainMenuFrame::OnButtonTestClick);
    Connect(idMenuOpen,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainMenuFrame::OnMenuOpenFolderSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainMenuFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainMenuFrame::OnAbout);
    //*)

    wxIcon FrameIcon(xlights_xpm);
    SetIcon(FrameIcon);
    wxStandardPathsBase& stdp = wxStandardPaths::Get();
    ThisExe = stdp.GetExecutablePath();
    wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));
    wxString lastdir;
    if ( config->Read(_("LastDir"), &lastdir) ) {
        SetDir(lastdir);
    }
    delete config;
}

MainMenuFrame::~MainMenuFrame()
{
    //(*Destroy(MainMenuFrame)
    //*)
}

void MainMenuFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void MainMenuFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _(XLIGHTS_LICENSE);
    wxString hdg = wxString::Format(_("About xLights %s"),_(XLIGHTS_VERSION));
    wxMessageBox(msg, hdg);
}

void MainMenuFrame::SetDir(const wxString& dirname)
{
    CurrentDir=dirname;
    StaticTextDirName->SetLabel(CurrentDir);
    ButtonNetworkSetup->Enable();
    SetButtonEnable();
}

void MainMenuFrame::SetButtonEnable() {
    bool FileExists;
    wxFileName netFile;

    netFile.AssignDir( CurrentDir );
    netFile.SetFullName(_(XLIGHTS_NETWORK_FILE));
    FileExists = netFile.FileExists();
    //ButtonSequence->Enable(FileExists);
    ButtonSchedule->Enable(FileExists);
    ButtonTest->Enable(FileExists);
}

void MainMenuFrame::OnMenuOpenFolderSelected(wxCommandEvent& event)
{
    wxString newdir;
    if (DirDialog1->ShowModal() == wxID_OK) {
        newdir=DirDialog1->GetPath();
        SetDir(newdir);
        wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));
        config->Write(_("LastDir"), newdir);
        delete config;
    }
}

void MainMenuFrame::Exec(wxString program)
{
    wxString NewExe=ThisExe;
    NewExe.Replace(_("xMenu"), program);
    long pid=wxExecute(NewExe);

    if (pid==0) {
        wxMessageBox(_("Unable to start program"), _("Error"));
    }
}

void MainMenuFrame::OnButtonNetworkSetupClick(wxCommandEvent& event)
{
	NetworkDialog NetDlg(this);
    if (NetDlg.ShowModal() > 0) {
        // save was pressed
        StatusBar1->SetStatusText(_("Network settings saved"));
    } else {
        StatusBar1->SetStatusText(_(""));
    }
    SetButtonEnable();
}

void MainMenuFrame::OnButtonSequenceClick(wxCommandEvent& event)
{
    Exec(_("xSequence"));
}

void MainMenuFrame::OnButtonScheduleClick(wxCommandEvent& event)
{
    Exec(_("xSchedule"));
}

void MainMenuFrame::OnButtonTestClick(wxCommandEvent& event)
{
    Exec(_("xTester"));
}

