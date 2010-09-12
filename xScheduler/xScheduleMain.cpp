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
#include <wx/filedlg.h>

//(*InternalHeaders(xScheduleFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

#include "../include/xlights_out.cpp"
#include "../include/minibasic.cpp"

// image files
#include "../include/xlights.xpm"
#include "../include/add.xpm"
#include "../include/remove.xpm"
#include "../include/floppy_disc.xpm"
#include "../include/stop_sign.xpm"
#include "../include/help.xpm"
#include "../include/up.xpm"
#include "../include/down.xpm"
#include "../include/play.xpm"


/* ****************************************************
 * Define xlights output object
 * All of the light control commands flow through here
 */

#define XTIMER_INTERVAL 50

xOutput xout;



/* ****************************************************
 * Helper class to provide access to the bitmaps on the toolbar
 */

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
    if (id == _("xlights_stop_sign"))
        return wxBitmap(stop_sign_xpm);
    if (id == _("xlights_help"))
        return wxBitmap(help_xpm);
    return wxNullBitmap;
};



/* ****************************************************
 * Extend the MiniBasic script class
 * with customized commands for xLights
 */

class xlbasic: public MiniBasicClass {

protected:

    xScheduleFrame* xsched;
    wxCheckListBox* playlist;
    bool haltflag;
    int runstate;

    void infunc(char* prompt, char* buff, int size) {
    }

    void outfunc(char *msg) {
        xsched->BasicOutput(msg);
    }

    void errfunc(const char *msg) {
        xsched->BasicError(msg);
    }

    // suspend script execution
    int do_wait(void) {
        return -2;
    }

    // returns the length of the playlist
    double do_playlistsize(void) {
        return playlist->GetCount();
    }

    // returns the length of the playlist
    double do_secondsremaining(void) {
        return xsched->SecondsRemaining;
    }

    // returns 1 if item is checked, 0 otherwise
    double do_itemchecked(void) {
        double answer=0;
        match(OPAREN);
        int idx = floor(expr());
        match(CPAREN);
        if(1 <= idx && idx <= playlist->GetCount())
            answer = playlist->IsChecked(idx-1) ? 1.0 : 0.0;
        else
            seterror(ERR_ILLEGALOFFSET);
        return answer;
    }

    char* do_itemname(void) {
        char *answer = 0;
        match(OPAREN);
        int idx = floor(expr());
        match(CPAREN);
        if(1 <= idx && idx <= playlist->GetCount()) {
            wxString n = playlist->GetString(idx-1);
            answer = mystrdup(n.mb_str());
            if(!answer) seterror(ERR_OUTOFMEMORY);
        } else {
            seterror(ERR_ILLEGALOFFSET);
        }
        return answer;
    };

    char* do_itemtype(void) {
        char *answer = 0;
        char buf[2];
        match(OPAREN);
        int idx = floor(expr());
        match(CPAREN);
        if(1 <= idx && idx <= playlist->GetCount()) {
            wxString n = playlist->GetString(idx-1);
            wxString ext = n.AfterLast('.');
            buf[0] = xsched->ExtType(ext);
            buf[1] = 0;
            answer = mystrdup(buf);
            if(!answer) seterror(ERR_OUTOFMEMORY);
        } else {
            seterror(ERR_ILLEGALOFFSET);
        }
        return answer;
    };

    // play item in playlist
    int do_PlayItem(void)
    {
        int idx = integer( expr() );
        if(1 <= idx && idx <= playlist->GetCount()) {
            wxString filename = playlist->GetString(idx-1);
            xsched->Play(filename);
        } else {
            seterror(ERR_ILLEGALOFFSET);
        }
        return 0;
    }

    /*
      Interpret a BASIC script
      Returns: true on success, false on error condition.
    */
    virtual bool runFromLineIdx(int curline = 0) {
      int nextline = -1;
      bool answer = true;
      char msgbuf[100];

      runstate=1;
      haltflag=false;
      while(curline != -1) {
        string = lines[curline].str;
        token = gettoken(string);
        errorflag = 0;

        nextline = line();
        if(errorflag) {
          reporterror(lines[curline].no);
          answer = false;
          break;
        }

        if(nextline < 0)
          break;

        wxYield(); // allow the UI to process events while script is running

        if(nextline == 0) {
          curline++;
          if(curline == nlines) break;
        } else if (haltflag) {
          sprintf(msgbuf, "Execution halted at line %d\n", lines[curline].no);
          sendErrorMsg(msgbuf);
          answer = false;
          break;
        } else {
          curline = findline(nextline);
          if(curline == -1) {
            sprintf(msgbuf, "line %d not found\n", nextline);
            sendErrorMsg(msgbuf);
            answer = false;
            break;
          }
        }
      }

      if (nextline == -2 && answer) {
          runstate=-1;  // suspended
      } else {
          runstate=0;
          xsched->EndScript(scriptname);
      }
      return answer;
    }

public:

    xlbasic() {
        runstate=0;
        AddNumericFunction("SECONDSREMAINING", static_cast<NumericFuncPtr>(&xlbasic::do_secondsremaining));
        AddNumericFunction("PLAYLISTSIZE", static_cast<NumericFuncPtr>(&xlbasic::do_playlistsize));
        AddStringFunction("ITEMNAME$", static_cast<StringFuncPtr>(&xlbasic::do_itemname));
        AddStringFunction("ITEMTYPE$", static_cast<StringFuncPtr>(&xlbasic::do_itemtype));
        AddNumericFunction("ITEMCHECKED", static_cast<NumericFuncPtr>(&xlbasic::do_itemchecked));
        AddCommand("PLAYITEM", static_cast<CommandPtr>(&xlbasic::do_PlayItem));
        AddCommand("WAIT", static_cast<CommandPtr>(&xlbasic::do_wait));
    };

    void setFrame(xScheduleFrame* fr) {
        xsched=fr;
    };

    void setPlaylist(wxCheckListBox* chklist) {
        playlist=chklist;
    };


    void halt() {
        if (runstate == 1) {
            haltflag=true;
        } else if (runstate != 0) {
            runstate=0;
            xsched->EndScript(scriptname);
        }
    }

    bool IsRunning() {
        return runstate!=0;
    }

    /*
      Interpret BASIC script starting at first line
      Returns: true on success, false on error condition.
    */
    virtual bool run() {
        xsched->StartScript(scriptname);
        return runFromLineIdx(0);
    }

};

xlbasic basic;


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
const long xScheduleFrame::ID_AUITOOLBARITEM_STOP = wxNewId();
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
const long xScheduleFrame::ID_BUTTON_CLEARLOG = wxNewId();
const long xScheduleFrame::ID_BUTTON_SAVELOG = wxNewId();
const long xScheduleFrame::ID_TEXTCTRL_LOG = wxNewId();
const long xScheduleFrame::ID_PANEL_LOG = wxNewId();
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
const long xScheduleFrame::ID_SCHED_TIMER = wxNewId();
const long xScheduleFrame::ID_PLAYER_DIALOG = wxNewId();


BEGIN_EVENT_TABLE(xScheduleFrame,wxFrame)
    //(*EventTable(xScheduleFrame)
    //*)
    EVT_TIMER(ID_TIMER, xScheduleFrame::OnTimer)
    EVT_TIMER(ID_SCHED_TIMER, xScheduleFrame::OnSchedTimer)
    EVT_COMMAND(ID_PLAYER_DIALOG, wxEVT_MEDIA_FINISHED, xScheduleFrame::OnMediaEnd)
END_EVENT_TABLE()

xScheduleFrame::xScheduleFrame(wxWindow* parent,wxWindowID id)
 : timer(this, ID_TIMER), schedtimer(this, ID_SCHED_TIMER)
{
    wxArtProvider::Push(new MyArtProvider);

    //(*Initialize(xScheduleFrame)
    wxMenu* MenuHelp;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItemAddList;
    wxFlexGridSizer* FlexGridSizer10;
    wxFlexGridSizer* FlexGridSizer3;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem4;
    wxFlexGridSizer* FlexGridSizer9;
    wxFlexGridSizer* FlexGridSizer2;
    wxBoxSizer* BoxSizer2;
    wxMenuItem* MenuItemDelList;
    wxMenuItem* MenuItem3;
    wxFlexGridSizer* FlexGridSizer8;
    wxMenu* MenuFile;
    wxBoxSizer* BoxSizer1;
    wxMenuItem* MenuItemRenameList;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer11;
    wxBoxSizer* BoxSizer3;
    wxMenu* MenuPlaylist;

    Create(parent, wxID_ANY, _("xScheduler"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(635,311));
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
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM_STOP, _("Stop Playlist"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlights_stop_sign")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Stop Playlist"), wxEmptyString, NULL);
    AuiToolBar1->EnableTool(ID_AUITOOLBARITEM_STOP, false);
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
    PanelLog = new wxPanel(Notebook1, ID_PANEL_LOG, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_LOG"));
    FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer3->AddGrowableCol(0);
    FlexGridSizer3->AddGrowableRow(1);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    ButtonClearLog = new wxButton(PanelLog, ID_BUTTON_CLEARLOG, _("Clear"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CLEARLOG"));
    BoxSizer1->Add(ButtonClearLog, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonSaveLog = new wxButton(PanelLog, ID_BUTTON_SAVELOG, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SAVELOG"));
    BoxSizer1->Add(ButtonSaveLog, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(BoxSizer1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlLog = new wxTextCtrl(PanelLog, ID_TEXTCTRL_LOG, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_LOG"));
    FlexGridSizer3->Add(TextCtrlLog, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelLog->SetSizer(FlexGridSizer3);
    FlexGridSizer3->Fit(PanelLog);
    FlexGridSizer3->SetSizeHints(PanelLog);
    Notebook1->AddPage(PanelCal, _("Calendar"), false);
    Notebook1->AddPage(PanelLog, _("Log"), false);
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
    MenuItem4 = new wxMenuItem(MenuHelp, idMenuHelpContent, _("Content\tF1"), wxEmptyString, wxITEM_NORMAL);
    MenuHelp->Append(MenuItem4);
    MenuItem2 = new wxMenuItem(MenuHelp, idMenuAbout, _("About"), _("Show info about this application"), wxITEM_NORMAL);
    MenuHelp->Append(MenuItem2);
    MenuBar1->Append(MenuHelp, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[2] = { -1, -1 };
    int __wxStatusBarStyles_1[2] = { wxSB_NORMAL, wxSB_NORMAL };
    StatusBar1->SetFieldsCount(2,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(2,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_AUITOOLBARITEM_ADD,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemAddClick);
    Connect(ID_AUITOOLBARITEM_DEL,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemDelClick);
    Connect(ID_AUITOOLBARITEM_HELP,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemHelpClick);
    Connect(ID_AUITOOLBARITEM_SAVE,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemSaveClick);
    Connect(ID_AUITOOLBARITEM_STOP,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemStopClick);
    Connect(ID_BUTTON_SET,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonSetClick);
    Connect(ID_BUTTON_CLEAR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonClearClick);
    Connect(ID_BUTTON_CLEARLOG,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonClearLogClick);
    Connect(ID_BUTTON_SAVELOG,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonSaveLogClick);
    Connect(ID_NOTEBOOK1,wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&xScheduleFrame::OnNotebook1PageChanged);
    Connect(idMenuSave,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemSaveClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnQuit);
    Connect(idMenuAddList,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemAddClick);
    Connect(idMenuRenameList,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnMenuItemRenameListSelected);
    Connect(idMenuDelList,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemDelClick);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnMenuItemRefreshSelected);
    Connect(idMenuHelpContent,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemHelpClick);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAbout);
    //*)

    SetIcon(wxIcon(xlights_xpm));
    PlayerDlg = new PlayerFrame(this, ID_PLAYER_DIALOG);
    PlayMode=NO_PLAY;
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
        if (i < 94) ChoiceStartTime->AppendString(t.Format(timefmt));
        if (i > 0) ChoiceEndTime->AppendString(t.Format(timefmt));
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
        schedtimer.Start(1000, wxTIMER_CONTINUOUS);
    } else {
        schedtimer.Start(1000, wxTIMER_CONTINUOUS);
    }
    scheduleFile.AssignDir( CurrentDir );
    scheduleFile.SetFullName(_(XLIGHTS_SCHEDULE_FILE));
    UnsavedChanges=false;
    if (scheduleFile.FileExists()) {
        LoadScheduleFile();
    }

    basic.setFrame(this);
}

void xScheduleFrame::BasicPrompt(char* prompt, char* buff, int size) {
  //fputs(prompt, stdout);
  //fgets(buff, size, stdin);
}

void xScheduleFrame::BasicOutput(char *msg) {
    wxString wxmsg(msg, wxConvUTF8);
    TextCtrlLog->AppendText(wxmsg);
}

void xScheduleFrame::BasicError(const char *msg) {
    wxString wxmsg(msg, wxConvUTF8);
    TextCtrlLog->AppendText(wxmsg);
}

void xScheduleFrame::StartScript(const char *scriptname) {
    AuiToolBar1->EnableTool(ID_AUITOOLBARITEM_STOP, true);
    AuiToolBar1->Realize();
    wxString wxname(scriptname, wxConvUTF8);
    StatusBar1->SetStatusText(_("Playing playlist: ")+wxname);
}

void xScheduleFrame::EndScript(const char *scriptname) {
    AuiToolBar1->EnableTool(ID_AUITOOLBARITEM_STOP, false);
    AuiToolBar1->Realize();
    PlayerDlg->MediaCtrl->Stop();
    ResetTimer(NO_SEQ);
    PlayerDlg->Show(false);
    xout.alloff();
    wxString wxname(scriptname, wxConvUTF8);
    SendToLogAndStatusBar(_("Ended playlist: ")+wxname);
}

void xScheduleFrame::AddPlaylist(const wxString& name) {
    int id, baseid=1000*Notebook1->GetPageCount();
    //wxPanel* PanelPlayList = new wxPanel(Notebook1, ID_PANEL_PLAYLIST, wxPoint(89,157), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_PLAYLIST"));
    wxPanel* PanelPlayList = new wxPanel(Notebook1);
    wxGridSizer* GridSizer1 = new wxGridSizer(2, 2, 0, 0);
    wxFlexGridSizer* FlexGridSizer4 = new wxFlexGridSizer(3, 1, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    FlexGridSizer4->AddGrowableRow(2);
    wxFlexGridSizer* FlexGridSizer5 = new wxFlexGridSizer(0, 5, 0, 0);
    FlexGridSizer5->AddGrowableCol(0);
    wxStaticText* StaticText1 = new wxStaticText(PanelPlayList, -1, _("Play List"));
    wxFont StaticText1Font(10,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    FlexGridSizer5->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+CHKBOX_MOVIEMODE;
    wxCheckBox* CheckBoxMovieMode = new wxCheckBox(PanelPlayList, id, _("Movie Mode"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_MOVIEMODE"));
    CheckBoxMovieMode->SetValue(false);
    FlexGridSizer5->Add(CheckBoxMovieMode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+UP_BUTTON;
    wxBitmapButton* BitmapButtonUp = new wxBitmapButton(PanelPlayList, id, wxBitmap(up_xpm));
    BitmapButtonUp->SetDefault();
    BitmapButtonUp->SetToolTip(_("Move Item Up"));
    FlexGridSizer5->Add(BitmapButtonUp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonUpClick);

    id=baseid+DOWN_BUTTON;
    wxBitmapButton* BitmapButtonDown = new wxBitmapButton(PanelPlayList, id, wxBitmap(down_xpm));
    BitmapButtonDown->SetDefault();
    BitmapButtonDown->SetToolTip(_("Move Item Down"));
    FlexGridSizer5->Add(BitmapButtonDown, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonDownClick);

    id=baseid+PLAY_BUTTON;
    wxBitmapButton* ButtonPlay = new wxBitmapButton(PanelPlayList, id, wxBitmap(play_xpm));
    ButtonPlay->SetToolTip(_("Play Selected Item"));
    ButtonPlay->SetHelpText(_("Plays the currently selected item in the play list"));
    FlexGridSizer5->Add(ButtonPlay, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonPlayItemClick);

    FlexGridSizer4->Add(FlexGridSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxBoxSizer* BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* StaticText2 = new wxStaticText(PanelPlayList, -1, _("Files:"));
    BoxSizer4->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+CHKBOX_AUDIO;
    wxCheckBox* CheckBoxAudio = new wxCheckBox(PanelPlayList, id, _("Audio"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_AUDIO"));
    CheckBoxAudio->SetValue(false);
    BoxSizer4->Add(CheckBoxAudio, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnFileTypeButtonClicked);

    id=baseid+CHKBOX_VIDEO;
    wxCheckBox* CheckBoxVideo = new wxCheckBox(PanelPlayList, id, _("Video"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_VIDEO"));
    CheckBoxVideo->SetValue(false);
    BoxSizer4->Add(CheckBoxVideo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnFileTypeButtonClicked);

    id=baseid+CHKBOX_LOR;
    wxCheckBox* CheckBoxLOR = new wxCheckBox(PanelPlayList, id, _("LOR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_LOR"));
    CheckBoxLOR->SetValue(false);
    BoxSizer4->Add(CheckBoxLOR, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnFileTypeButtonClicked);

    id=baseid+CHKBOX_VIXEN;
    wxCheckBox* CheckBoxVixen = new wxCheckBox(PanelPlayList, id, _("Vixen"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_VIXEN"));
    CheckBoxVixen->SetValue(false);
    BoxSizer4->Add(CheckBoxVixen, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnFileTypeButtonClicked);

    FlexGridSizer4->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+PLAYLIST_LISTBOX;
    wxCheckListBox* CheckListBoxPlay = new wxCheckListBox(PanelPlayList, id, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX_PLAY"));
    FlexGridSizer4->Add(CheckListBoxPlay, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(FlexGridSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxFlexGridSizer* FlexGridSizer6 = new wxFlexGridSizer(3, 1, 0, 0);
    FlexGridSizer6->AddGrowableCol(0);
    FlexGridSizer6->AddGrowableRow(1);
    Connect(id, wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, (wxObjectEventFunction)&xScheduleFrame::OnPlaylistToggle);

    // Player script
    wxFlexGridSizer* FlexGridSizer7 = new wxFlexGridSizer(3);
    FlexGridSizer7->AddGrowableCol(1);
    wxStaticText* StaticText3 = new wxStaticText(PanelPlayList, -1, _("Player script"));
    wxFont StaticText3Font(10,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText3->SetFont(StaticText3Font);
    FlexGridSizer7->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+WIZARD_BUTTON;
    wxButton* ButtonWizard = new wxButton(PanelPlayList, id, _("Script Wizard..."));
    ButtonWizard->SetToolTip(_("Run script wizard to create script"));
    ButtonWizard->SetHelpText(_("Run script wizard to create script"));
    FlexGridSizer7->Add(ButtonWizard, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonWizardClick);

    id=baseid+RUN_BUTTON;
    wxBitmapButton* ButtonRun = new wxBitmapButton(PanelPlayList, id, wxBitmap(play_xpm));
    ButtonRun->SetToolTip(_("Run Player Script"));
    ButtonRun->SetHelpText(_("Plays the play list"));
    FlexGridSizer7->Add(ButtonRun, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonRunPlaylistClick);

    id=baseid+PLAYLIST_LOGIC;
    FlexGridSizer6->Add(FlexGridSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxTextCtrl* TextCtrlLogic = new wxTextCtrl(PanelPlayList, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_LOGIC"));
    FlexGridSizer6->Add(TextCtrlLogic, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(FlexGridSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelPlayList->SetSizer(GridSizer1);
    GridSizer1->Fit(PanelPlayList);
    GridSizer1->SetSizeHints(PanelPlayList);
    Notebook1->AddPage(PanelPlayList, name, true);
    ChoicePlayList->AppendString(name);
    TextCtrlLogic->SetValue( _("10 REM Run script wizard to create a script that will play the playlist\n") );
}

xScheduleFrame::~xScheduleFrame()
{
    if (schedtimer.IsRunning()) schedtimer.Stop();
    if (timer.IsRunning()) timer.Stop();
    delete PlayerDlg;
    if (UnsavedChanges) {
        wxMessageDialog confirm(this, _("Save changes?"), _("Confirm"), wxYES|wxNO);
        if (confirm.ShowModal() == wxID_YES) {
            SaveFile();
        }
    }
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

long xScheduleFrame::DiffSeconds(wxString& strTime, wxTimeSpan& tsCurrent)
{
    wxDateTime t;
    t.ParseTime(strTime);
    wxTimeSpan tsSched(t.GetHour(),t.GetMinute(),t.GetSecond(),t.GetMillisecond());
    tsSched -= tsCurrent;
    return tsSched.GetSeconds().ToLong();
}

void xScheduleFrame::OnSchedTimer(wxTimerEvent& event)
{
    //StatusBar1->SetStatusText(_("OnSchedTimer: ") + wxDateTime::Now().FormatISOTime());
    int FldNum=1;
    wxString strTime;
    wxDateTime n=wxDateTime::Now();
    wxTimeSpan tsCurrent=n.Subtract(CalStart);
    int days=tsCurrent.GetDays();
    int r=days / 7;
    int c=days % 7;
    tsCurrent.Subtract(wxTimeSpan::Days(days)); // timespan from midnight to the current time
    long SecondsRem = 24*60*60 - tsCurrent.GetSeconds().ToLong(); // seconds until midnight
    wxString v=Grid1->GetCellValue(r,c);
    wxString v1=v.AfterFirst('\n');
    if (v1.IsEmpty()) {
        StatusBar1->SetStatusText(_("No show scheduled for today"), FldNum);
    } else {
        wxString playlist=v1.BeforeFirst('\n');
        wxString timerange=v1.AfterFirst('\n');
        if (basic.IsRunning()) {
            // check for the schedule end
            strTime=timerange.AfterFirst('-');
            SecondsRem = DiffSeconds(strTime, tsCurrent);
            int minutes=(SecondsRem + 59) / 60;  // round up
            if (minutes > 60) {
                StatusBar1->SetStatusText(_("Show will end at: ") + strTime, FldNum);
            } else if (minutes > 0) {
                StatusBar1->SetStatusText(wxString::Format(_("Show will end in %d minutes"),minutes), FldNum);
            } else {
                StatusBar1->SetStatusText(_("Finishing playlist: ") + playlist, FldNum);
            }
        } else {
            // check for next scheduled start
            strTime=timerange.BeforeFirst('-');
            long seconds=DiffSeconds(strTime, tsCurrent);
            int minutes= (seconds + 59) / 60;  // round up
            if (minutes > 60) {
                StatusBar1->SetStatusText(_("Next show will start at: ") + strTime, FldNum);
            } else if (minutes > 1) {
                StatusBar1->SetStatusText(wxString::Format(_("Next show will start in %d minutes"),minutes), FldNum);
            } else if (minutes == 1) {
                StatusBar1->SetStatusText(wxString::Format(_("Next show will start in %ld seconds"),seconds), FldNum);
            } else if (minutes == 0 && v != LastSchedStart) {
                int nbidx=FindNotebookPage(playlist);
                if (!PortsOK) {
                    StatusBar1->SetStatusText(_("ERROR: serial ports did not initialize at program startup, cannot start playlist ") + playlist, FldNum);
                } else if (nbidx > 0) {
                    PlayMode=SCHEDULE;
                    RunPlaylist(nbidx);
                    LastSchedStart=v;
                } else {
                    StatusBar1->SetStatusText(_("ERROR: cannot find playlist ") + playlist, FldNum);
                }
            } else if (PlayMode == SCHEDULE && PlayerDlg->IsShown()) {
                PlayerDlg->Show(false);
                PlayMode=NO_PLAY;
            } else {
                StatusBar1->SetStatusText(_("Show has ended for today"), FldNum);
            }
        }
    }
    SecondsRemaining=SecondsRem;
}

int xScheduleFrame::FindNotebookPage(wxString& pagename)
{
    for (int i=2; i < Notebook1->GetPageCount(); i++) {
        if (Notebook1->GetPageText(i) == pagename) {
            return i;
        }
    }
    return -1;
}

void xScheduleFrame::OnTimer(wxTimerEvent& event)
{
    long msec=0;
    int startmsec, endmsec, duration, period;
    int netnum, chindex;
    static long lastmsec;
    static LorEventMap::iterator LorIter;
    static std::string LastIntensity;
    char vixintensity;
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
                TextCtrlLog->AppendText(wxString::Format(_(" LOR ms=%ld, ch=%d, st=%d, en=%d\n"),msec,chindex,startmsec,endmsec));
                if (LorIter->second->EndIntesity == -1) {
                    switch (LorIter->second->action) {
                        case LOR_INTENSITY:
                            xout.SetIntensity(netnum,chindex,LorIter->second->StartIntensity);
                            break;
                        case LOR_TWINKLE:
                            xout.twinkle(netnum,chindex,400,LorIter->second->StartIntensity);
                            break;
                        case LOR_SHIMMER:
                            xout.shimmer(netnum,chindex,100,LorIter->second->StartIntensity);
                            break;
                    }
                } else {
                    duration = endmsec - startmsec;
                    switch (LorIter->second->action) {
                        case LOR_INTENSITY:
                            xout.ramp(netnum,chindex,duration,LorIter->second->StartIntensity,LorIter->second->EndIntesity);
                            break;
                        case LOR_TWINKLE:
                            xout.twinklefade(netnum,chindex,400,duration,LorIter->second->StartIntensity,LorIter->second->EndIntesity);
                            break;
                        case LOR_SHIMMER:
                            xout.shimmerfade(netnum,chindex,100,duration,LorIter->second->StartIntensity,LorIter->second->EndIntesity);
                            break;
                    }
                }

                LorIter++;
            }
            xout.TimerEnd();
            break;
        case PAUSE_LOR:
            if (PlayerDlg->MediaCtrl->GetState() == wxMEDIASTATE_PLAYING) {
                msec = PlayerDlg->MediaCtrl->Tell();
                LorIter=msec < 500 ? LorEvents.begin() : LorEvents.lower_bound(msec / 10);
                ResetTimer(PLAYING_LOR);
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
                        xout.SetIntensity(VixNetwork[chindex].first, VixNetwork[chindex].second, vixintensity);
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

void xScheduleFrame::LoadNetworkFile()
{
    long MaxChan;
    wxString tempstr;
    wxXmlDocument doc;
    if (doc.Load( networkFile.GetFullPath() )) {
        for( wxXmlNode* e=doc.GetRoot()->GetChildren(); e!=NULL; e=e->GetNext() ) {
            tempstr=e->GetPropVal(wxT("MaxChannels"), wxT("0"));
            tempstr.ToLong(&MaxChan);
            if (e->GetName() == _("network")) {
                AddNetwork(e->GetPropVal(wxT("NetworkType"), wxT("")),
                           e->GetPropVal(wxT("ComPort"), wxT("")),
                           e->GetPropVal(wxT("BaudRate"), wxT("")),
                           MaxChan);
            }
        }
    } else {
        wxMessageBox(_("Unable to load network definition file"), _("Error"));
    }
}

void xScheduleFrame::AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels)
{
    int netnum=-1;
    wxString net3 = NetworkType.Left(3);
    int baud = atoi(BaudRate.mb_str(wxConvUTF8));
    try {
        if (net3 == _("LOR")) {
            netnum=xout.addnetwork(new xNetwork_LOR(),MaxChannels,ComPort,baud);
        } else if (net3 == _("Ren")) {
            netnum=xout.addnetwork(new xNetwork_Renard(),MaxChannels,ComPort,baud);
        } else if (net3 == _("DMX")) {
            netnum=xout.addnetwork(new xNetwork_DMXentec(),MaxChannels,ComPort,baud);
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
    for (int ch=0; ch<MaxChannels; ch++)
        VixNetwork.push_back(std::make_pair(netnum, ch));
}

void xScheduleFrame::OnFileTypeButtonClicked()
{
    UnsavedChanges=true;
    ScanForFiles();
}

void xScheduleFrame::ScanForFiles()
{
    wxString filename;
    bool ok;
    int i;

    int baseid=1000*Notebook1->GetSelection();
    wxCheckListBox* CheckListBoxPlay=(wxCheckListBox*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
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

void xScheduleFrame::OnPlaylistToggle()
{
    UnsavedChanges=true;
}

void xScheduleFrame::OnButtonPlayItemClick()
{
    if (basic.IsRunning()) {
        StatusBar1->SetStatusText(_("A playlist is already running!"));
        return;
    }
    int baseid=1000*Notebook1->GetSelection();
    wxCheckListBox* CheckListBoxPlay=(wxCheckListBox*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxString filename = CheckListBoxPlay->GetStringSelection();
    if (filename.IsEmpty()) {
        wxMessageBox(_("Nothing selected!"), _("Error"));
    } else {
        PlayMode=SINGLE;
        Play(filename);
    }
}

void xScheduleFrame::PlayerError(const wxString& msg)
{
    if (PlayMode == SCHEDULE) {
        TextCtrlLog->AppendText(msg + _("\n"));
    } else {
        wxMessageBox(msg, _("Error"));
    }
}

void xScheduleFrame::ShowPlayerSingle()
{
    if (PlayMode != SINGLE) return;
    PlayerDlg->MediaCtrl->ShowPlayerControls(wxMEDIACTRLPLAYERCONTROLS_DEFAULT);
    PlayerDlg->ShowFullScreen(false, 0);
    PlayerDlg->Show();
}


void xScheduleFrame::Play(wxString& filename) {
    wxFileName oName(CurrentDir, filename);
    wxString fullpath=oName.GetFullPath();
    switch (ExtType(oName.GetExt())) {
        case 'a':
        case 'v':
            if (wxFile::Exists(fullpath) && PlayerDlg->MediaCtrl->Load(fullpath)) {
                ResetTimer(NO_SEQ);
                ShowPlayerSingle();
            } else {
                PlayerError(_("Unable to play file:\n")+filename);
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

// returns true if serial ports are ok, displays an error and returns false otherwise
bool xScheduleFrame::CheckPorts()
{
    if (!PortsOK) {
        PlayerError(_("Serial ports did not initialize at program startup.\nPlug in your dongles/adapters and restart the program."));
    }
    return PortsOK;
}

void xScheduleFrame::PlayLorFile(wxString& FileName)
{
    if (!CheckPorts()) return;
    LorEvents.clear();
    wxXmlDocument doc;
    if (doc.Load( FileName )) {
        wxXmlNode* root=doc.GetRoot();
        wxString musicFilename=root->GetPropVal(wxT("musicFilename"), wxT(""));
        for( wxXmlNode* e=root->GetChildren(); e!=NULL; e=e->GetNext() ) {
            if (e->GetName() == _("channels")) {
                LoadLorChannels(e);
            }
        }
        xout.SetMaxIntensity(100);

        wxPathFormat PathFmt = musicFilename.Contains(_("\\")) ? wxPATH_DOS : wxPATH_NATIVE;
        wxFileName fn1(musicFilename, PathFmt);
        if (!fn1.FileExists()) {
            wxFileName fn2(CurrentDir,fn1.GetFullName());
            musicFilename=fn2.GetFullPath();
        }
        if (wxFile::Exists(musicFilename) && PlayerDlg->MediaCtrl->Load(musicFilename)) {
            ShowPlayerSingle();
            ResetTimer(PAUSE_LOR);
        } else {
            PlayerError(_("Unable to play file:\n")+musicFilename);
        }
    } else {
        PlayerError(_("Unable to load sequence:\n")+FileName);
    }
}

void xScheduleFrame::LoadLorChannels(wxXmlNode* n)
{
    long netnum, unit, circuit;
    wxString tempstr;
    for( wxXmlNode* e=n->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() != _("channel")) continue;
        if (e->HasProp(_("unit")) && e->HasProp(_("circuit"))) {
            tempstr=e->GetPropVal(wxT("unit"), wxT("0"));
            tempstr.ToLong(&unit);
            tempstr=e->GetPropVal(wxT("circuit"), wxT("0"));
            tempstr.ToLong(&circuit);
            tempstr=e->GetPropVal(wxT("network"), wxT("0"));
            tempstr.ToLong(&netnum);
            LoadLorChannel(e,netnum,(unit-1)*16+circuit-1);
        }
    }
}

void xScheduleFrame::LoadLorChannel(wxXmlNode* n, int netnum, int chindex)
{
    long start,end,lastend=0;
    long startint,endint;
    LOR_ACTIONS action;
    wxString tempstr;
    for( wxXmlNode* e=n->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() != _("effect")) continue;
        if (!e->HasProp(_("startCentisecond"))) continue;
        if (!e->HasProp(_("endCentisecond"))) continue;
        if (!e->HasProp(_("type"))) continue;

        tempstr=e->GetPropVal(wxT("type"), wxT(""));
        if (tempstr == _("intensity")) {
            action=LOR_INTENSITY;
        } else if (tempstr == _("twinkle")) {
            action=LOR_TWINKLE;
        } else if (tempstr == _("shimmer")) {
            action=LOR_SHIMMER;
        } else {
            continue;
        }
        tempstr=e->GetPropVal(wxT("startCentisecond"), wxT("0"));
        tempstr.ToLong(&start);
        tempstr=e->GetPropVal(wxT("endCentisecond"), wxT("0"));
        tempstr.ToLong(&end);
        if (e->HasProp(wxT("intensity"))) {
            tempstr=e->GetPropVal(wxT("intensity"), wxT("0"));
            tempstr.ToLong(&startint);
            endint=-1;
        } else if (e->HasProp(wxT("startIntensity")) && e->HasProp(wxT("endIntensity"))) {
            tempstr=e->GetPropVal(wxT("startIntensity"), wxT("0"));
            tempstr.ToLong(&startint);
            tempstr=e->GetPropVal(wxT("endIntensity"), wxT("100"));
            tempstr.ToLong(&endint);
        }
        if (start != lastend && lastend > 0) {
            LorEvents.insert(LorEventPair(lastend, new LorEventClass(netnum,chindex,start,LOR_INTENSITY,0,-1)));
        }
        LorEvents.insert(LorEventPair(start, new LorEventClass(netnum,chindex,end,action,startint,endint)));
        lastend=end;
    }
    LorEvents.insert(LorEventPair(lastend, new LorEventClass(netnum,chindex,lastend,LOR_INTENSITY,0,-1)));
}

void xScheduleFrame::PlayVixenFile(wxString& FileName)
{
    long MaxIntensity = 255;
    long toValue;
    wxString tag,tempstr;
    wxFileName fn;
    fn.AssignDir(CurrentDir);
    if (!CheckPorts()) return;
    VixLastChannel = -1;
    VixEventPeriod=-1;
    wxXmlDocument doc( FileName );
    if (doc.IsOk()) {
        wxXmlNode* root=doc.GetRoot();
        for( wxXmlNode* e=root->GetChildren(); e!=NULL; e=e->GetNext() ) {
            tag = e->GetName();
            if (tag == _("EventPeriodInMilliseconds")) {
                tempstr=e->GetNodeContent();
                tempstr.ToLong(&VixEventPeriod);
            } else if (tag == _("MaximumLevel")) {
                tempstr=e->GetNodeContent();
                tempstr.ToLong(&MaxIntensity);
            } else if (tag == _("Audio") || tag == _("Song")) {
                wxString filename=e->GetPropVal(wxT("filename"), wxT(""));
                fn.SetFullName(filename);
            } else if (tag == _("EventValues")) {
                VixEventData = base64_decode(e->GetNodeContent());
            } else if (tag == _("PlugInData")) {
                for( wxXmlNode* p=e->GetChildren(); p!=NULL; p=p->GetNext() ) {
                    if (p->GetName() == _("PlugIn")) {
                        if (p->HasProp(wxT("to"))) {
                            tempstr=p->GetPropVal(wxT("to"), wxT("0"));
                            tempstr.ToLong(&toValue);
                            if (toValue > VixLastChannel) VixLastChannel=toValue;
                        }
                    }
                    break;
                }
            }
        }
        xout.SetMaxIntensity(MaxIntensity);

        if (VixEventPeriod < 0) {
            PlayerError(_("EventPeriodInMilliseconds is undefined"));
        } else if (VixLastChannel <= 0) {
            PlayerError(_("Unable to determine number of channels"));
        } else if (!fn.FileExists()) {
            PlayerError(_("No such file:\n")+fn.GetFullPath());
        } else if (!PlayerDlg->MediaCtrl->Load(fn.GetFullPath())) {
            PlayerError(_("Unable to play file:\n")+fn.GetFullPath());
        } else {
            VixNumPeriods = VixEventData.size() / VixLastChannel;
            //wxString msg = wxString::Format(_("Data size=%d, Channel Count=%d, NumPeriods=%d, Period Len=%d, Media File=%s"),VixEventData.size(),VixLastChannel,VixNumPeriods,VixEventPeriod,fn.GetFullPath().c_str());
            //StatusBar1->SetStatusText(msg);
            ResetTimer(PAUSE_VIX);
            ShowPlayerSingle();
        }
    } else {
        PlayerError(_("Unable to load sequence:\n")+FileName);
    }
}

void xScheduleFrame::OnButtonUpClick()
{
    int baseid=1000*Notebook1->GetSelection();
    wxCheckListBox* CheckListBoxPlay=(wxCheckListBox*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
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
    wxCheckListBox* CheckListBoxPlay=(wxCheckListBox*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
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
    if (idx  < 2) {
        wxMessageBox(_("Can't delete this page!"), _("Error"));
        return;
    }
    dialog.StaticTextDelName->SetLabel(Notebook1->GetPageText(idx));
    if (dialog.ShowModal() != wxID_OK) return;
    Notebook1->DeletePage(idx);
    ChoicePlayList->Delete(idx-2);
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
    ChoicePlayList->SetString(idx-2,name);
    UnsavedChanges=true;
}

void xScheduleFrame::OnAuiToolBarItemHelpClick(wxCommandEvent& event)
{
    if (!wxLaunchDefaultBrowser(_(XLIGHTS_HELP_URL)))
    {
        wxMessageBox(_("Help requires Internet access. Unable to access help."), _("Error"));
    }
}

void xScheduleFrame::OnAuiToolBarItemSaveClick(wxCommandEvent& event)
{
    SaveFile();
}

void xScheduleFrame::SaveFile()
{
    unsigned int RowCount,baseid;
    wxCheckBox* chkbox;
    wxTextCtrl* TextCtrlLogic;
    wxXmlDocument doc;
    wxXmlNode *item, *plist, *scriptnode, *scripttext;
    wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("xSchedule") );
    root->AddProperty( wxT("computer"), wxGetHostName());
    doc.SetRoot( root );

    // save calendar
    wxXmlNode* sched = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("schedule") );
    root->AddChild(sched);
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
                item = new wxXmlNode( wxXML_ELEMENT_NODE, _("playdate") );
                item->AddProperty( wxT("playlist"), playlist );
                item->AddProperty( wxT("date"), d.FormatISODate() );
                item->AddProperty( wxT("timestart"), t1.FormatISOTime() );
                item->AddProperty( wxT("timeend"), t2.FormatISOTime() );
                sched->AddChild( item );
            }
            d+=wxDateSpan::Day();
        }
    }

    // save playlists
    wxXmlNode* lists = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("playlists") );
    root->AddChild(lists);

    int cnt=Notebook1->GetPageCount();
    for (int pagenum=2; pagenum < cnt; pagenum++) {
        plist = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("playlist") );
        plist->AddProperty( wxT("name"), Notebook1->GetPageText(pagenum) );
        baseid=1000*pagenum;
        wxCheckListBox* CheckListBoxPlay=(wxCheckListBox*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
        for (int i=CHKBOX_AUDIO; i<=CHKBOX_MOVIEMODE; i++) {
            chkbox=(wxCheckBox*)wxWindow::FindWindowById(baseid+i,Notebook1);
            v = chkbox->GetValue() ? _("1") : _("0");
            wxString label = chkbox->GetLabelText();
            label.Replace(_(" "), _(""));
            plist->AddProperty( label, v );
        }
        lists->AddChild( plist );

        RowCount=CheckListBoxPlay->GetCount();
        for (unsigned int r=0; r < RowCount; r++ ) {
            item = new wxXmlNode( wxXML_ELEMENT_NODE, _("listitem") );
            v = CheckListBoxPlay->IsChecked(r) ? _("1") : _("0");
            item->AddProperty( wxT("name"), CheckListBoxPlay->GetString(r) );
            item->AddProperty( wxT("enabled"), v );
            plist->AddChild( item );
        }
        scriptnode = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("script") );
        scripttext = new wxXmlNode( wxXML_TEXT_NODE, wxT("scripttext") );
        TextCtrlLogic = (wxTextCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LOGIC,Notebook1);
        scripttext->SetContent( TextCtrlLogic->GetValue() );
        plist->AddChild( scriptnode );
        scriptnode->AddChild( scripttext );
    }

    // commit to disk
    wxString FileName=scheduleFile.GetFullPath();
    if (doc.Save(FileName)) {
        UnsavedChanges=false;
        StatusBar1->SetStatusText(_("File saved successfully"));
    } else {
        wxMessageBox(_("Unable to save schedule file"), _("Error"));
    }
}

void xScheduleFrame::LoadScheduleFile()
{
    wxXmlDocument doc;
    wxString name;
    if (doc.Load( scheduleFile.GetFullPath() )) {
        wxXmlNode* root=doc.GetRoot();
        for( wxXmlNode* e=root->GetChildren(); e!=NULL; e=e->GetNext() ) {
            name=e->GetName();
            if (name == _("schedule")) {
                LoadSchedule(e);
            } else if (name == _("playlists")) {
                LoadPlaylists(e);
            }
        }
    } else {
        wxMessageBox(_("Unable to load schedule file"), _("Error"));
    }
}

void xScheduleFrame::LoadSchedule(wxXmlNode* n)
{
    wxDateTime d,t1,t2;
    int days,r,c;
    for( wxXmlNode* e=n->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() == _("playdate")) {
            wxString playlist = e->GetPropVal( wxT("playlist"), wxT(""));
            wxString playdate = e->GetPropVal( wxT("date"), wxT(""));
            wxString time1 = e->GetPropVal( wxT("timestart"), wxT(""));
            wxString time2 = e->GetPropVal( wxT("timeend"), wxT(""));
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

void xScheduleFrame::LoadPlaylists(wxXmlNode* n)
{
    for( wxXmlNode* e=n->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() == _("playlist")) {
            LoadPlaylist(e);
        }
    }
}

void xScheduleFrame::LoadPlaylist(wxXmlNode* n)
{
    wxCheckBox* chkbox;
    wxString chkval;
    wxString name = n->GetPropVal( wxT("name"), wxT(""));
    int baseid=1000*Notebook1->GetPageCount();
    AddPlaylist(name);
    for (int i=CHKBOX_AUDIO; i<=CHKBOX_MOVIEMODE; i++) {
        chkbox=(wxCheckBox*)wxWindow::FindWindowById(baseid+i,Notebook1);
        if (!chkbox) continue;
        wxString label = chkbox->GetLabelText();
        label.Replace(_(" "), _(""));
        chkval = n->GetPropVal(label, wxT("0"));
        chkbox->SetValue( chkval == _("1") );
    }
    wxCheckListBox* CheckListBoxPlay = (wxCheckListBox*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxTextCtrl* TextCtrlLogic = (wxTextCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LOGIC,Notebook1);
    int cnt=0;
    for( wxXmlNode* e=n->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() == _("listitem")) {
            wxString itemname = e->GetPropVal( wxT("name"), wxT(""));
            chkval = e->GetPropVal( wxT("enabled"), wxT("0"));
            CheckListBoxPlay->AppendString(itemname);
            CheckListBoxPlay->Check(cnt, chkval == _("1"));
            cnt++;
        } else if (e->GetName() == _("script")) {
            TextCtrlLogic->SetValue( e->GetNodeContent() );
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
    if (StartIdx > EndIdx) {
        wxMessageBox(_("Start time must be before the end time!"));
        return;
    }
    wxString StartStr = ChoiceStartTime->GetStringSelection();
    wxString EndStr = ChoiceEndTime->GetStringSelection();
    GridSelection selCells = this->getGridSelection(*Grid1);
    GridSelection::iterator it;
    for (it = selCells.begin(); it != selCells.end(); it++) {
        this->SetGridCell(it->first,it->second,plist,StartStr,EndStr);
        UnsavedChanges=true;
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
        UnsavedChanges=true;
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

std::string xScheduleFrame::base64_decode(const wxString& encoded_string) {
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

void xScheduleFrame::OnNotebook1PageChanged(wxNotebookEvent& event)
{
    int nbidx=event.GetSelection();
    bool enabled=nbidx > 1;
    AuiToolBar1->EnableTool(ID_AUITOOLBARITEM_DEL, enabled);
    AuiToolBar1->Realize();
}

void xScheduleFrame::RunPlaylist(int nbidx)
{
    wxString PageName=Notebook1->GetPageText(nbidx);
    TextCtrlLog->AppendText(_("At: ") + wxDateTime::Now().FormatTime() + _("\n"));
    TextCtrlLog->AppendText(_("Starting playlist ") + PageName + _("\n"));
    if (basic.IsRunning()) {
        SendToLogAndStatusBar(_("ERROR: a playlist is already running!"));
        return;
    }
    int baseid=1000*nbidx;
    wxTextCtrl* LogicCtl=(wxTextCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LOGIC,Notebook1);
    wxCheckListBox* Playlist=(wxCheckListBox*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxCheckBox* MovieMode=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_MOVIEMODE,Notebook1);
    wxString userscript=LogicCtl->GetValue();
    if (userscript.IsEmpty()) {
        SendToLogAndStatusBar(_("ERROR: no script to run!"));
        return;
    }
    if (!userscript.EndsWith(_("\n"))) userscript += _("\n"); // ensure script ends with a newline
    basic.setPlaylist(Playlist);
    if (basic.setScript(PageName.mb_str(wxConvUTF8), userscript.mb_str(wxConvUTF8))) {
        basic.run();
        if (MovieMode->GetValue()) {
            PlayerDlg->MediaCtrl->ShowPlayerControls(wxMEDIACTRLPLAYERCONTROLS_NONE);
            PlayerDlg->Show();
            PlayerDlg->ShowFullScreen(true, wxFULLSCREEN_ALL);
        }
    } else {
        SendToLogAndStatusBar(_("Error in playlist script"));
    }
}

void xScheduleFrame::SendToLogAndStatusBar(const wxString& msg)
{
    TextCtrlLog->AppendText(msg + _("\n"));
    StatusBar1->SetStatusText(msg);
}

void xScheduleFrame::OnButtonRunPlaylistClick()
{
    if (!CheckPorts()) return;
    PlayMode=PLAYLIST;
    RunPlaylist(Notebook1->GetSelection());
}

void xScheduleFrame::OnButtonWizardClick()
{
    WizardDialog dialog(this);
    int nbidx=Notebook1->GetSelection();
    dialog.StaticTextListName->SetLabel(Notebook1->GetPageText(nbidx));
    if (dialog.ShowModal() != wxID_OK) return;

    bool FirstItemOnce = dialog.CheckBoxFirstItem->GetValue();
    bool LastItemOnce = dialog.CheckBoxLastItem->GetValue();
    int baseid=1000*nbidx;
    wxTextCtrl* LogicCtl=(wxTextCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LOGIC,Notebook1);
    wxString script;
    wxString loopstart = FirstItemOnce ? _("2") : _("1");
    wxString loopend = LastItemOnce ? _("-1") : _("");

    script.Append(_("10 REM *\n"));
    script.Append(_("20 REM * Created: ") + wxDateTime::Now().Format() + _("\n"));
    script.Append(_("30 REM *\n"));
    if (FirstItemOnce) {
        script.Append(_("50 LET NextItem=1\n"));
        script.Append(_("60 GOTO 1100\n"));
    } else {
        script.Append(_("50 LET LastItemPlayed=999\n"));
    }
    script.Append(_("1000 REM *\n"));
    script.Append(_("1001 REM * Jump here at end of song or sequence\n"));
    script.Append(_("1002 REM *\n"));
    script.Append(_("1005 IF SECONDSREMAINING <= 0 THEN 9000\n"));
    script.Append(_("1010 REM Find next checked item in playlist\n"));
    script.Append(_("1020 FOR NextItem=LastItemPlayed+1 TO PLAYLISTSIZE") + loopend + _("\n"));
    script.Append(_("1030 IF ITEMCHECKED(NextItem)=1 THEN 1100\n"));
    script.Append(_("1040 NEXT NextItem\n"));
    script.Append(_("1050 REM Start over at beginning of list\n"));
    script.Append(_("1060 FOR NextItem=") + loopstart + _(" TO PLAYLISTSIZE") + loopend + _("\n"));
    script.Append(_("1070 IF ITEMCHECKED(NextItem)=1 THEN 1100\n"));
    script.Append(_("1080 NEXT NextItem\n"));
    script.Append(_("1090 GOTO 9000\n"));
    script.Append(_("1100 REM *\n"));
    script.Append(_("1101 REM * Play item NextItem\n"));
    script.Append(_("1102 REM *\n"));
    script.Append(_("1110 LET LastItemPlayed=NextItem\n"));
    script.Append(_("1115 PRINT \"At:\", FORMATDATETIME$(NOW,5)\n"));
    script.Append(_("1120 PRINT \"Playing:\",ITEMNAME$(NextItem)\n"));
    script.Append(_("1130 PLAYITEM NextItem\n"));
    script.Append(_("1140 WAIT\n"));
    script.Append(_("9000 REM DONE\n"));
    if (LastItemOnce) {
        script.Append(_("9010 IF LastItemPlayed = PLAYLISTSIZE THEN 9100\n"));
        script.Append(_("9020 LET NextItem=PLAYLISTSIZE\n"));
        script.Append(_("9030 GOTO 1100\n"));
        script.Append(_("9100 REM DONE\n"));
    }

    LogicCtl->SetValue( script );
    UnsavedChanges=true;
}

void xScheduleFrame::OnAuiToolBarItemStopClick(wxCommandEvent& event)
{
    basic.halt();
}

void xScheduleFrame::OnButtonSaveLogClick(wxCommandEvent& event)
{
    wxString filename = _("xSchedule-") + wxDateTime::Today().FormatISODate() + _(".log");
    wxFileDialog filedlg(this, _("Save log messages"), CurrentDir, filename, _("*.*"), wxFD_SAVE);
    if (filedlg.ShowModal() == wxID_OK) {
        if (TextCtrlLog->SaveFile( filedlg.GetPath() )) {
            StatusBar1->SetStatusText(_("Log saved successfully to: ")+filename);
        } else {
            StatusBar1->SetStatusText(_("An error occurred while saving: ")+filename);
        }
    }
}

void xScheduleFrame::OnButtonClearLogClick(wxCommandEvent& event)
{
    TextCtrlLog->Clear();
}

void xScheduleFrame::OnMediaEnd( wxCommandEvent &event )
{
    if (basic.IsRunning()) {
        // reached end of song/sequence, so start script at line 1000
        basic.runat(1000);
    }
}
