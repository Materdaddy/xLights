/***************************************************************
 * Name:      MainMenuMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-02-27
 * Copyright: 2010-2011 by Matt Brown
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
const long MainMenuFrame::ID_STATICTEXT3 = wxNewId();
const long MainMenuFrame::ID_STATICTEXT2 = wxNewId();
const long MainMenuFrame::ID_BUTTON5 = wxNewId();
const long MainMenuFrame::ID_BUTTON_NETWORK_SETUP = wxNewId();
const long MainMenuFrame::ID_BUTTON_SCHEDULE = wxNewId();
const long MainMenuFrame::ID_BUTTON_TEST = wxNewId();
const long MainMenuFrame::ID_BUTTON_TESTRGB = wxNewId();
const long MainMenuFrame::ID_BUTTON_SEQUENCE = wxNewId();
const long MainMenuFrame::ID_PANEL1 = wxNewId();
const long MainMenuFrame::idMenuOpen = wxNewId();
const long MainMenuFrame::idMenuQuit = wxNewId();
const long MainMenuFrame::idMenuHelpContent = wxNewId();
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
    wxMenuItem* MenuItemHelpContent;
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
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT3, _("All sequences and media files must be in this directory"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    wxFont StaticText2Font(10,wxDEFAULT,wxFONTSTYLE_ITALIC,wxNORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    StaticBoxSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextDirName = new wxStaticText(Panel1, ID_STATICTEXT2, _("<No directory selected>"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticTextDirName->SetMinSize(wxSize(300,0));
    StaticTextDirName->SetForegroundColour(wxColour(0,0,255));
    StaticBoxSizer1->Add(StaticTextDirName, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonChangeDir = new wxButton(Panel1, ID_BUTTON5, _("Change"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    StaticBoxSizer1->Add(ButtonChangeDir, 1, wxALL|wxFIXED_MINSIZE|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    ButtonNetworkSetup = new wxButton(Panel1, ID_BUTTON_NETWORK_SETUP, _("Network Setup"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_NETWORK_SETUP"));
    ButtonNetworkSetup->Disable();
    BoxSizer3->Add(ButtonNetworkSetup, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonSchedule = new wxButton(Panel1, ID_BUTTON_SCHEDULE, _("Scheduler"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SCHEDULE"));
    ButtonSchedule->Disable();
    BoxSizer3->Add(ButtonSchedule, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonTest = new wxButton(Panel1, ID_BUTTON_TEST, _("Lighting Test"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_TEST"));
    ButtonTest->Disable();
    BoxSizer3->Add(ButtonTest, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonTestRGB = new wxButton(Panel1, ID_BUTTON_TESTRGB, _("RGB Lighting Test"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_TESTRGB"));
    ButtonTestRGB->Disable();
    BoxSizer3->Add(ButtonTestRGB, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonSequence = new wxButton(Panel1, ID_BUTTON_SEQUENCE, _("Sequencer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SEQUENCE"));
    ButtonSequence->Disable();
    ButtonSequence->Hide();
    BoxSizer3->Add(ButtonSequence, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(BoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(Panel1);
    FlexGridSizer1->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, idMenuOpen, _("Select Show Folder"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
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
    DirDialog1 = new wxDirDialog(this, _("Select Show Directory"), wxEmptyString, wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxDirDialog"));
    BoxSizer1->SetSizeHints(this);

    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainMenuFrame::OnMenuOpenFolderSelected);
    Connect(ID_BUTTON_NETWORK_SETUP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainMenuFrame::OnButtonNetworkSetupClick);
    Connect(ID_BUTTON_SCHEDULE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainMenuFrame::OnButtonScheduleClick);
    Connect(ID_BUTTON_TEST,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainMenuFrame::OnButtonTestClick);
    Connect(ID_BUTTON_TESTRGB,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainMenuFrame::OnButtonTestRGBClick);
    Connect(ID_BUTTON_SEQUENCE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MainMenuFrame::OnButtonSequenceClick);
    Connect(idMenuOpen,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainMenuFrame::OnMenuOpenFolderSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainMenuFrame::OnQuit);
    Connect(idMenuHelpContent,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainMenuFrame::OnMenuItemHelpContentSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainMenuFrame::OnAbout);
    //*)

    SetIcon(wxIcon(xlights_xpm));
    wxStandardPathsBase& stdp = wxStandardPaths::Get();
    ThisExe = stdp.GetExecutablePath();
    wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));

    // get list of most recently used directories
    wxString dir,mru_name;
    mru_Menu = Menu1;
    mru_MenuLength = 0;
    int menuID, idx;
    for (int i=0; i<MRU_LENGTH; i++) {
        mru_name=wxString::Format(wxT("mru%d"),i);
        if ( config->Read(mru_name, &dir) ) {
            idx=mru.Index(dir);
            if (idx == wxNOT_FOUND && !dir.IsEmpty()) mru.Add(dir);
        }
        menuID = wxNewId();
        mru_MenuItem[i] = new wxMenuItem(mru_Menu, menuID);
        Connect(menuID,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MainMenuFrame::OnMenuMRU);
    }
    if ( config->Read(_("LastDir"), &dir) ) {
        idx=mru.Index(dir);
        if (idx != wxNOT_FOUND) mru.RemoveAt(idx);
        SetDir(dir);
    }
    delete config;
}

void MainMenuFrame::OnMenuMRU(wxCommandEvent& event)
{
    int id = event.GetId();
    wxString newdir = mru_Menu->GetLabel(id);
    UpdateMRU(newdir);
    SetDir(newdir);
}

void MainMenuFrame::UpdateMRU(const wxString& newdir)
{
    // update most recently used array
    int idx;
    idx=mru.Index(newdir);
    if (idx != wxNOT_FOUND) mru.RemoveAt(idx);
    idx=mru.Index(CurrentDir);
    if (idx != wxNOT_FOUND) mru.RemoveAt(idx);
    mru.Insert(CurrentDir,0);
    int cnt=mru.GetCount();
    if (cnt > MRU_LENGTH) {
        mru.RemoveAt(MRU_LENGTH, cnt - MRU_LENGTH);
        cnt = MRU_LENGTH;
    }

    /*
    wxString msg=wxT("UpdateMRU:\n");
    for (int i=0; i<mru.GetCount(); i++) msg+=wxT("\n") + mru[i];
    wxMessageBox(msg);
    */

    // save config
    wxString mru_name, value;
    wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));
    config->Write(_("LastDir"), newdir);
    for (int i=0; i<MRU_LENGTH; i++) {
        mru_name=wxString::Format(wxT("mru%d"),i);
        if (i < cnt) {
            value = mru[i];
        } else {
            value = wxEmptyString;
        }
        config->Write(mru_name, value);
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

    /*
    wxString msg=wxString::Format(wxT("SetDir %d:\n"),mru.GetCount());;
    for (int i=0; i<mru.GetCount(); i++) msg+=wxT("\n") + mru[i];
    wxMessageBox(msg);
    */

    // clear mru items from menu
    /*
    for (int i=0; i<MRU_LENGTH; i++) {
        mru_Menu->Remove(mru_MenuItem[i]);
    }
    */

    // append mru items to menu
    int cnt=mru.GetCount();
    for (int i=0; i<cnt; i++) {
        mru_MenuItem[i]->SetItemLabel(mru[i]);
        if (i >= mru_MenuLength) {
            mru_Menu->Append(mru_MenuItem[i]);
            mru_MenuLength++;
        }
    }
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
    ButtonTestRGB->Enable(FileExists);
}

void MainMenuFrame::OnMenuOpenFolderSelected(wxCommandEvent& event)
{
    wxString newdir;
    if (DirDialog1->ShowModal() == wxID_OK) {
        newdir=DirDialog1->GetPath();
        if (newdir == CurrentDir) return;
        UpdateMRU(newdir);
        SetDir(newdir);
    }
}

void MainMenuFrame::Exec(const wxString& program)
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
    if (NetDlg.ShowModal() == wxID_SAVE) {
        // save was pressed
        NetDlg.SaveFile();
        StatusBar1->SetStatusText(_("Network settings saved"));
    } else {
        StatusBar1->SetStatusText(_(""));
    }
    SetButtonEnable();
}

void MainMenuFrame::OnButtonSequenceClick(wxCommandEvent& event)
{
    Exec(_("xSequencer"));
}

void MainMenuFrame::OnButtonScheduleClick(wxCommandEvent& event)
{
    Exec(_("xScheduler"));
}

void MainMenuFrame::OnButtonTestClick(wxCommandEvent& event)
{
    Exec(_("xTester"));
}


void MainMenuFrame::OnMenuItemHelpContentSelected(wxCommandEvent& event)
{
    if (!wxLaunchDefaultBrowser(_(XLIGHTS_HELP_URL)))
    {
        wxMessageBox(_("Help requires Internet access. Unable to access help."), _("Error"));
    }
}

void MainMenuFrame::OnButtonTestRGBClick(wxCommandEvent& event)
{
    Exec(_("xTesterRGB"));
}

