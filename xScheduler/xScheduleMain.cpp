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
#include <wx/choicdlg.h>
#include <wx/bmpbuttn.h>
#include <wx/treectrl.h>
#include <wx/textdlg.h>
#include <wx/grid.h>

//(*InternalHeaders(xScheduleFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

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
#include "../include/play24.xpm"



/* ****************************************************
 * Define the number of fixed notebook pages
 * 2 = 1 for calendar and 1 for log
 */

#define FixedPages 2

/* ****************************************************
 * Define the output interval in milliseconds
 */

#define XTIMER_INTERVAL 50


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
    if (id == _("xlights_play"))
        return wxBitmap(play24_xpm);
    return wxNullBitmap;
};


/* ****************************************************
 * Extend the MiniBasic script class
 * with customized commands for xLights
 */

class xlbasic: public MiniBasicClass {

protected:

    xScheduleFrame* xsched;
    wxGrid* playlist;
    std::vector<ctb::SerialPort> SerialPorts;
    bool haltflag;
    int runstate;
    int playbackend_goto;

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
        return EXEC_PAUSE;
    }

    // LET handle=SERIALOPEN("COM1",9600,"8N1")
    // returns a handle to the port
    double do_serialopen(void) {
        match(OPAREN);
        char *pPortName = stringexpr();
        if(!pPortName) return 0;
        wxString portname(pPortName,wxConvFile);
        if(!portname) return 0;
        match(COMMA);
        int baudrate = integer( expr() );
        match(COMMA);
        char *pSerialConfig = stringexpr();
        if(!pSerialConfig) return 0;
        match(CPAREN);

        ctb::SerialPort port;
        SerialPorts.push_back(port);
        int handle=SerialPorts.size()-1;
        int errcode=SerialPorts[handle].Open(portname, baudrate, pSerialConfig);
        free(pPortName);
        free(pSerialConfig);
        if (errcode < 0) {
            seterror(ERR_IO);
        }
        return (double)handle;
    }

    // write to a serial port
    int do_serialwrite(void) {
        int handle = integer( expr() );
        match(COMMA);
        char *datastr = stringexpr();
        if(!datastr) return 0;
        if (handle >= 0 && handle < SerialPorts.size()) {
            SerialPorts[handle].Write(datastr,strlen(datastr));
        } else {
            seterror(ERR_ILLEGALOFFSET);
        }
        free(datastr);
        return EXEC_NEXTLINE;
    }

    // reads data from a serial port
    char* do_serialread(void) {
        char *answer = 0;
        char buf[100];
        match(OPAREN);
        int handle = integer( expr() );
        match(CPAREN);
        if (handle >= 0 && handle < SerialPorts.size()) {
            int cnt = SerialPorts[handle].Read(buf,sizeof(buf)-1);
            buf[cnt]=0;
            answer = mystrdup(buf);
            if(!answer) seterror(ERR_OUTOFMEMORY);
        } else {
            seterror(ERR_ILLEGALOFFSET);
        }
        return answer;
    }

    // returns the length of the playlist
    double do_playlistsize(void) {
        return playlist->GetNumberRows();
    }

    // returns number of seconds remaining in scheduled play time
    double do_secondsremaining(void) {
        return xsched->SecondsRemaining;
    }

    int do_setplaylist(void) {
        char *pName = stringexpr();
        if(!pName) return 0;
        wxString name(pName,wxConvUTF8);
        int nbidx=xsched->FindNotebookPage(name);
        if (nbidx < FixedPages) return 0;
        playlist = (wxGrid*)xsched->FindNotebookControl(nbidx,xsched->PLAYLIST_LISTBOX);
        return EXEC_NEXTLINE;
    }

    char* do_itemname(void) {
        char *answer = 0;
        match(OPAREN);
        int idx = floor(expr());
        match(CPAREN);
        if(1 <= idx && idx <= playlist->GetNumberRows()) {
            wxString n = playlist->GetCellValue(idx-1,0);
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
        if(1 <= idx && idx <= playlist->GetNumberRows()) {
            wxString n = playlist->GetCellValue(idx-1,0);
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

    // all lights off
    int do_lightsoff(void)
    {
        xsched->xout->alloff();
        return EXEC_NEXTLINE;
    };

    // play item in playlist
    int do_PlayItem(void)
    {
        int idx = integer( expr() );
        if(1 <= idx && idx <= playlist->GetNumberRows()) {
            wxString filename = playlist->GetCellValue(idx-1,0);
            wxString delay = playlist->GetCellValue(idx-1,1);
            long idelay;
            delay.ToLong(&idelay);
            xsched->Play(filename,idelay);
        } else {
            seterror(ERR_ILLEGALOFFSET);
        }
        return EXEC_NEXTLINE;
    };

    int do_StopPlayback(void)
    {
        xsched->StopPlayback();
        return EXEC_NEXTLINE;
    }

    int do_OnPlaybackEnd(void)
    {
        playbackend_goto = integer( expr() );
        return EXEC_NEXTLINE;
    }

    int do_OnSerialRx(void)
    {
        int handle = integer( expr() );
        match(COMMA);
        int rxgoto = integer( expr() );
        SerialPorts[handle].SetCallback(rxgoto);
        return EXEC_NEXTLINE;
    }

    /*
      Interpret a BASIC script
      Returns: true on success, false on error condition.
    */
    virtual bool runFromLineIdx(int curline = 0) {
      int nextline = -1;
      bool answer = true;
      char msgbuf[100];

      //nfors = 0;
      runstate=1;
      haltflag=false;
      while(curline != -1) {
        // uncomment to trace
        //sprintf(msgbuf, " at line %d\n", lines[curline].no);
        //outfunc(msgbuf);
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

        if(nextline == EXEC_NEXTLINE) {
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

      runstate=-1;  // suspended
      if (nextline != EXEC_PAUSE || answer == false) {
          halt();
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
        AddStringFunction("SERIALREAD$", static_cast<StringFuncPtr>(&xlbasic::do_serialread));
        AddNumericFunction("SERIALOPEN", static_cast<NumericFuncPtr>(&xlbasic::do_serialopen));
        AddCommand("SETPLAYLIST", static_cast<CommandPtr>(&xlbasic::do_setplaylist));
        AddCommand("LIGHTSOFF", static_cast<CommandPtr>(&xlbasic::do_lightsoff));
        AddCommand("SERIALWRITE", static_cast<CommandPtr>(&xlbasic::do_serialwrite));
        AddCommand("PLAYITEM", static_cast<CommandPtr>(&xlbasic::do_PlayItem));
        AddCommand("STOPPLAYBACK", static_cast<CommandPtr>(&xlbasic::do_StopPlayback));
        AddCommand("ONPLAYBACKEND", static_cast<CommandPtr>(&xlbasic::do_OnPlaybackEnd));
        AddCommand("ONSERIALRX", static_cast<CommandPtr>(&xlbasic::do_OnSerialRx));
        AddCommand("WAIT", static_cast<CommandPtr>(&xlbasic::do_wait));
    };

    void setFrame(xScheduleFrame* fr) {
        xsched=fr;
    };

    void halt() {
        if (runstate == 1) {
            haltflag=true;
        } else if (runstate != 0) {
            runstate=0;
            SerialPorts.clear();
            xsched->EndScript(scriptname);
        }
    }

    void PlaybackEndCallback()
    {
        if (runstate==-1 && playbackend_goto > 0) {
            if (!runat(playbackend_goto)) halt();
        }
    }

    void SerialCallback()
    {
        //char msgbuf[100];
        if (runstate!=-1) return;
        for (int i=0; i < SerialPorts.size(); i++) {
            int rxgoto = SerialPorts[i].GetCallback();
            if (rxgoto > 0 && SerialPorts[i].AvailableToRead() > 0) {
                //sprintf(msgbuf, "SerialCallback to line %d\n", rxgoto);
                //outfunc(msgbuf);
                if (!runat(rxgoto)) halt();
                return;
            }
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
        playbackend_goto=-1;
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
const long xScheduleFrame::ID_AUITOOLBARITEM_PLAY = wxNewId();
const long xScheduleFrame::ID_AUITOOLBAR1 = wxNewId();
const long xScheduleFrame::ID_PANEL2 = wxNewId();
const long xScheduleFrame::ID_LISTBOX_SCHED = wxNewId();
const long xScheduleFrame::ID_BITMAPBUTTON_SCHED_INFO = wxNewId();
const long xScheduleFrame::ID_CHECKBOX_RUN_SCHEDULE = wxNewId();
const long xScheduleFrame::ID_BUTTON_ADD_SHOW = wxNewId();
const long xScheduleFrame::ID_BUTTON2 = wxNewId();
const long xScheduleFrame::ID_BUTTON_DELETE_SHOW = wxNewId();
const long xScheduleFrame::ID_BUTTON_DESELECT = wxNewId();
const long xScheduleFrame::ID_PANEL_CAL = wxNewId();
const long xScheduleFrame::ID_BUTTON_CLEARLOG = wxNewId();
const long xScheduleFrame::ID_BUTTON_SAVELOG = wxNewId();
const long xScheduleFrame::ID_STATICTEXT1 = wxNewId();
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
const long xScheduleFrame::idCustomScript = wxNewId();
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
END_EVENT_TABLE()

xScheduleFrame::xScheduleFrame(wxWindow* parent,wxWindowID id)
 : timer(this, ID_TIMER), schedtimer(this, ID_SCHED_TIMER)
{
    wxArtProvider::Push(new MyArtProvider);

    //(*Initialize(xScheduleFrame)
    wxMenu* MenuHelp;
    wxFlexGridSizer* FlexGridSizer4;
    wxMenuItem* MenuItemCustomScript;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItemAddList;
    wxFlexGridSizer* FlexGridSizer3;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem4;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer2;
    wxMenuItem* MenuItemDelList;
    wxMenuItem* MenuItem3;
    wxFlexGridSizer* FlexGridSizer8;
    wxMenu* MenuFile;
    wxMenuItem* MenuItemRenameList;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer1;
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
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM_PLAY, _("Start Playlist"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlights_play")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Start Playlist"), wxEmptyString, NULL);
    AuiToolBar1->SetToolDropDown(ID_AUITOOLBARITEM_PLAY, true);
    AuiToolBar1->EnableTool(ID_AUITOOLBARITEM_PLAY, false);
    AuiToolBar1->Realize();
    AuiManager1->AddPane(AuiToolBar1, wxAuiPaneInfo().Name(_T("PaneName")).ToolbarPane().Caption(_("Pane caption")).Layer(10).Top().Gripper());
    AuiManager1->Update();
    FlexGridSizer2->Add(Panel2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Notebook1 = new wxNotebook(Panel1, ID_NOTEBOOK1, wxDefaultPosition, wxSize(799,312), 0, _T("ID_NOTEBOOK1"));
    PanelCal = new wxPanel(Notebook1, ID_PANEL_CAL, wxPoint(49,10), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_CAL"));
    FlexGridSizer8 = new wxFlexGridSizer(1, 2, 0, 0);
    FlexGridSizer8->AddGrowableCol(0);
    FlexGridSizer8->AddGrowableRow(0);
    ListBoxSched = new wxListBox(PanelCal, ID_LISTBOX_SCHED, wxDefaultPosition, wxDefaultSize, 0, 0, wxLB_MULTIPLE, wxDefaultValidator, _T("ID_LISTBOX_SCHED"));
    FlexGridSizer8->Add(ListBoxSched, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    BitmapButtonSchedInfo = new wxBitmapButton(PanelCal, ID_BITMAPBUTTON_SCHED_INFO, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_INFORMATION")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxRAISED_BORDER, wxDefaultValidator, _T("ID_BITMAPBUTTON_SCHED_INFO"));
    BitmapButtonSchedInfo->SetToolTip(_("Tips for using scheduler"));
    BoxSizer3->Add(BitmapButtonSchedInfo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxRunSchedule = new wxCheckBox(PanelCal, ID_CHECKBOX_RUN_SCHEDULE, _("Run Schedule"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RUN_SCHEDULE"));
    CheckBoxRunSchedule->SetValue(false);
    wxFont CheckBoxRunScheduleFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    CheckBoxRunSchedule->SetFont(CheckBoxRunScheduleFont);
    BoxSizer3->Add(CheckBoxRunSchedule, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ButtonAddShow = new wxButton(PanelCal, ID_BUTTON_ADD_SHOW, _("Schedule Playlist"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ADD_SHOW"));
    BoxSizer3->Add(ButtonAddShow, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ButtonUpdateShow = new wxButton(PanelCal, ID_BUTTON2, _("Update Selected Item"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer3->Add(ButtonUpdateShow, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ButtonDeleteShow = new wxButton(PanelCal, ID_BUTTON_DELETE_SHOW, _("Delete Selected Items"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_DELETE_SHOW"));
    BoxSizer3->Add(ButtonDeleteShow, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ButtonDeselect = new wxButton(PanelCal, ID_BUTTON_DESELECT, _("Deselect All"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_DESELECT"));
    BoxSizer3->Add(ButtonDeselect, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(BoxSizer3, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer8->Add(FlexGridSizer4, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    PanelCal->SetSizer(FlexGridSizer8);
    FlexGridSizer8->Fit(PanelCal);
    FlexGridSizer8->SetSizeHints(PanelCal);
    PanelLog = new wxPanel(Notebook1, ID_PANEL_LOG, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_LOG"));
    FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer3->AddGrowableCol(0);
    FlexGridSizer3->AddGrowableRow(1);
    FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
    ButtonClearLog = new wxButton(PanelLog, ID_BUTTON_CLEARLOG, _("Clear"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CLEARLOG"));
    FlexGridSizer5->Add(ButtonClearLog, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonSaveLog = new wxButton(PanelLog, ID_BUTTON_SAVELOG, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SAVELOG"));
    FlexGridSizer5->Add(ButtonSaveLog, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText1 = new wxStaticText(PanelLog, ID_STATICTEXT1, _("While the scheduler is running, each item that is played is logged here"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer5->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(FlexGridSizer5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlLog = new wxTextCtrl(PanelLog, ID_TEXTCTRL_LOG, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_LOG"));
    FlexGridSizer3->Add(TextCtrlLog, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PanelLog->SetSizer(FlexGridSizer3);
    FlexGridSizer3->Fit(PanelLog);
    FlexGridSizer3->SetSizeHints(PanelLog);
    Notebook1->AddPage(PanelCal, _("Schedule"), false);
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
    MenuItemCustomScript = new wxMenuItem(MenuPlaylist, idCustomScript, _("Custom Script"), wxEmptyString, wxITEM_NORMAL);
    MenuPlaylist->Append(MenuItemCustomScript);
    MenuBar1->Append(MenuPlaylist, _("&Playlist"));
    MenuHelp = new wxMenu();
    MenuItem4 = new wxMenuItem(MenuHelp, idMenuHelpContent, _("Content\tF1"), wxEmptyString, wxITEM_NORMAL);
    MenuHelp->Append(MenuItem4);
    MenuItem2 = new wxMenuItem(MenuHelp, idMenuAbout, _("About"), _("Show info about this application"), wxITEM_NORMAL);
    MenuHelp->Append(MenuItem2);
    MenuBar1->Append(MenuHelp, _("&Help"));
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
    Connect(ID_AUITOOLBARITEM_PLAY,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemPlayClick);
    Connect(ID_BITMAPBUTTON_SCHED_INFO,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnBitmapButtonSchedInfoClick);
    Connect(ID_CHECKBOX_RUN_SCHEDULE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnCheckBoxRunScheduleClick);
    Connect(ID_BUTTON_ADD_SHOW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonAddShowClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonUpdateShowClick);
    Connect(ID_BUTTON_DELETE_SHOW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonDeleteShowClick);
    Connect(ID_BUTTON_DESELECT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonDeselectClick);
    Connect(ID_BUTTON_CLEARLOG,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonClearLogClick);
    Connect(ID_BUTTON_SAVELOG,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonSaveLogClick);
    Connect(ID_NOTEBOOK1,wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&xScheduleFrame::OnNotebook1PageChanged);
    Connect(idMenuSave,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemSaveClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnQuit);
    Connect(idMenuAddList,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemAddClick);
    Connect(idMenuRenameList,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnMenuItemRenameListSelected);
    Connect(idMenuDelList,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemDelClick);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnMenuItemRefreshSelected);
    Connect(idCustomScript,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnMenuItemCustomScriptSelected);
    Connect(idMenuHelpContent,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemHelpClick);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xScheduleFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&xScheduleFrame::OnClose);
    //*)

    SetIcon(wxIcon(xlights_xpm));
    PlayerDlg = new PlayerFrame(this, ID_PLAYER_DIALOG);
    PlayMode=NO_PLAY;
    xout = new xOutput();
    ResetTimer(NO_SEQ);

    // set time format

    if (wxDateTime::GetCountry() == wxDateTime::USA) {
        datefmt=_("%b %d");
        timefmt=_("%I:%M %p");
    } else {
        datefmt=_("%d %b");
        timefmt=_("%X");
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
        AuiToolBar1->EnableTool(ID_AUITOOLBARITEM_PLAY, true);
        AuiToolBar1->Realize();
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
    DisplaySchedule();
    Notebook1->ChangeSelection(0);
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
    AuiToolBar1->EnableTool(ID_AUITOOLBARITEM_PLAY, false);
    AuiToolBar1->Realize();
    wxString wxname(scriptname, wxConvUTF8);
    StatusBar1->SetStatusText(_("Playing playlist: ")+wxname);
}

void xScheduleFrame::EndScript(const char *scriptname) {
    AuiToolBar1->EnableTool(ID_AUITOOLBARITEM_STOP, false);
    AuiToolBar1->EnableTool(ID_AUITOOLBARITEM_PLAY, true);
    AuiToolBar1->Realize();
    PlayerDlg->MediaCtrl->Stop();
    ResetTimer(NO_SEQ);
    PlayerDlg->Show(false);
    xout->alloff();
    wxString wxname(scriptname, wxConvUTF8);
    SendToLogAndStatusBar(_("Ended playlist: ")+wxname);
}

void xScheduleFrame::AddPlaylist(const wxString& name) {
    int id, baseid=1000*Notebook1->GetPageCount();
    wxPanel* PanelPlayList = new wxPanel(Notebook1);

    wxFlexGridSizer* FlexGridSizer4 = new wxFlexGridSizer(0, 4, 0, 0);
    FlexGridSizer4->AddGrowableCol(3);
    FlexGridSizer4->AddGrowableRow(2);
    wxStaticText* StaticText1 = new wxStaticText(PanelPlayList, -1, _("Available Files"));
    wxFont StaticText1Font(10,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    FlexGridSizer4->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxStaticText* StaticText2 = new wxStaticText(PanelPlayList, -1, _("Playlist"));
    wxFont StaticText2Font(10,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    FlexGridSizer4->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxBoxSizer* BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* StaticText3 = new wxStaticText(PanelPlayList, -1, _("Files:"));
    BoxSizer4->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

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
    FlexGridSizer4->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxFlexGridSizer* FlexGridSizer5 = new wxFlexGridSizer(0, 6, 0, 0);

    id=baseid+CHKBOX_MOVIEMODE;
    wxCheckBox* CheckBoxMovieMode = new wxCheckBox(PanelPlayList, id, _("Movie Mode"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_MOVIEMODE"));
    CheckBoxMovieMode->SetValue(false);
    FlexGridSizer5->Add(CheckBoxMovieMode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+UP_BUTTON;
    wxBitmapButton* BitmapButtonUp = new wxBitmapButton(PanelPlayList, id, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_UP")),wxART_BUTTON));
    BitmapButtonUp->SetDefault();
    BitmapButtonUp->SetToolTip(_("Move Item Up"));
    FlexGridSizer5->Add(BitmapButtonUp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonUpClick);

    id=baseid+DOWN_BUTTON;
    wxBitmapButton* BitmapButtonDown = new wxBitmapButton(PanelPlayList, id, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_DOWN")),wxART_BUTTON));
    BitmapButtonDown->SetDefault();
    BitmapButtonDown->SetToolTip(_("Move Item Down"));
    FlexGridSizer5->Add(BitmapButtonDown, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonDownClick);

    id=baseid+INFO_BUTTON;
    wxBitmapButton* BitmapButtonInfo = new wxBitmapButton(PanelPlayList, id, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_INFORMATION")),wxART_BUTTON));
    BitmapButtonInfo->SetDefault();
    BitmapButtonInfo->SetToolTip(_("Sequence Information"));
    FlexGridSizer5->Add(BitmapButtonInfo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonInfoClick);

    id=baseid+PLAY_BUTTON;
    wxButton* ButtonPlay = new wxButton(PanelPlayList, id, _("Play Item"));
    ButtonPlay->SetToolTip(_("Play Selected Item"));
    ButtonPlay->SetHelpText(_("Plays the currently selected item in the play list"));
    FlexGridSizer5->Add(ButtonPlay, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonPlayItemClick);

    FlexGridSizer4->Add(FlexGridSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    //FlexGridSizer4->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+REMOVE_SCRIPT_BUTTON;
    wxButton* ButtonRemoveScript = new wxButton(PanelPlayList, id, _("Remove Script"));
    FlexGridSizer4->Add(ButtonRemoveScript, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonRemoveScriptClick);
    ButtonRemoveScript->Hide();

    id=baseid+PLAYLIST_FILES;
    wxTreeCtrl* TreeCtrl = new wxTreeCtrl(PanelPlayList, id);
    FlexGridSizer4->Add(TreeCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxBoxSizer* BoxSizer5 = new wxBoxSizer(wxVERTICAL);

    id=baseid+PLAYLIST_ADD;
    wxButton* Button2 = new wxButton(PanelPlayList, id, _(">"));
    Button2->SetMinSize(wxSize(30,20));
    Button2->SetToolTip(_("Add selected file"));
    BoxSizer5->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonPlaylistAddClick);

    id=baseid+PLAYLIST_ADD_ALL;
    wxButton* Button3 = new wxButton(PanelPlayList, id, _(">>"));
    Button3->SetMinSize(wxSize(30,20));
    Button3->SetToolTip(_("Add all files"));
    BoxSizer5->Add(Button3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonPlaylistAddAllClick);

    id=baseid+PLAYLIST_DELETE;
    wxButton* Button4 = new wxButton(PanelPlayList, id, _("<"));
    Button4->SetMinSize(wxSize(30,20));
    Button4->SetToolTip(_("Delete selected item"));
    BoxSizer5->Add(Button4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonPlaylistDeleteClick);

    id=baseid+PLAYLIST_DELETE_ALL;
    wxButton* Button5 = new wxButton(PanelPlayList, id, _("<<"));
    Button5->SetMinSize(wxSize(30,20));
    Button5->SetToolTip(_("Delete all items"));
    BoxSizer5->Add(Button5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonPlaylistDeleteAllClick);

    FlexGridSizer4->Add(BoxSizer5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+PLAYLIST_LISTBOX;
    //wxListBox* ListBox1 = new wxListBox(PanelPlayList, id);
    //FlexGridSizer4->Add(ListBox1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxGrid* GridPlaylist = new wxGrid(PanelPlayList, id);
	GridPlaylist->CreateGrid(0,2);
	//GridPlaylist->EnableEditing(false);
	GridPlaylist->EnableGridLines(true);
	GridPlaylist->SetRowLabelSize(40);
	//GridPlaylist->SetDefaultColSize(120, true);
	GridPlaylist->SetDefaultCellAlignment(wxALIGN_LEFT,wxALIGN_CENTRE);
	GridPlaylist->SetDefaultEditor(new wxGridCellNumberEditor(0,3600));
	GridPlaylist->SetDefaultCellFont( GridPlaylist->GetFont() );
	GridPlaylist->SetDefaultCellTextColour( GridPlaylist->GetForegroundColour() );
	GridPlaylist->SetDefaultRowSize(25);
	GridPlaylist->DisableDragGridSize();
	GridPlaylist->DisableDragColSize();
	GridPlaylist->DisableDragRowSize();
    GridPlaylist->SetSelectionMode(wxGrid::wxGridSelectRows);
	GridPlaylist->SetColLabelValue(0, _("Filename"));
	GridPlaylist->SetColLabelValue(1, _("Delay After\nPlay (sec)"));
	GridPlaylist->SetColSize(0,150);
	GridPlaylist->SetColSize(1,90);
	GridPlaylist->SetColFormatNumber(1);
	wxGridCellAttr* attrCol0=new wxGridCellAttr();
	attrCol0->SetReadOnly();
	GridPlaylist->SetColAttr(0,attrCol0);
    FlexGridSizer4->Add(GridPlaylist, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);


    id=baseid+PLAYLIST_LOGIC;
    wxTextCtrl* TextCtrlLogic = new wxTextCtrl(PanelPlayList, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_LOGIC"));
    FlexGridSizer4->Add(TextCtrlLogic, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlLogic->Hide();

    PanelPlayList->SetSizer(FlexGridSizer4);
    FlexGridSizer4->Fit(PanelPlayList);
    FlexGridSizer4->SetSizeHints(PanelPlayList);
    Notebook1->AddPage(PanelPlayList, name, true);
}

void xScheduleFrame::OnButtonPlaylistAddClick() {
    int nbidx=Notebook1->GetSelection();
    int baseid=1000*nbidx;
    wxGrid* ListBoxPlay=(wxGrid*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxTreeCtrl* TreeCtrlFiles=(wxTreeCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_FILES,Notebook1);
    wxTreeItemId root=TreeCtrlFiles->GetRootItem();
    wxTreeItemId selid=TreeCtrlFiles->GetSelection();
    if (!selid.IsOk()) return;
    wxString selstr = TreeCtrlFiles->GetItemText(selid);
    ListBoxPlay->AppendRows(1);
    int r=ListBoxPlay->GetNumberRows()-1;
    ListBoxPlay->SetCellValue(r,0,selstr);
    ListBoxPlay->SetCellValue(r,1,wxT("0"));
    UnsavedChanges=true;
    ScanForFiles();
}

void xScheduleFrame::OnButtonPlaylistAddAllClick() {
    int nbidx=Notebook1->GetSelection();
    int baseid=1000*nbidx;
    int r;
    wxGrid* ListBoxPlay=(wxGrid*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxTreeCtrl* TreeCtrlFiles=(wxTreeCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_FILES,Notebook1);
    wxTreeItemId root=TreeCtrlFiles->GetRootItem();
    wxTreeItemId item=TreeCtrlFiles->GetFirstVisibleItem();
    while (item.IsOk()) {
        if (item != root) {
            ListBoxPlay->AppendRows(1);
            r=ListBoxPlay->GetNumberRows()-1;
            ListBoxPlay->SetCellValue(r,0,TreeCtrlFiles->GetItemText(item));
            ListBoxPlay->SetCellValue(r,1,wxT("0"));
            UnsavedChanges=true;
        }
        item=TreeCtrlFiles->GetNextVisible(item);
    }
    ScanForFiles();
}

void xScheduleFrame::OnButtonPlaylistDeleteClick() {
    int nbidx=Notebook1->GetSelection();
    int baseid=1000*nbidx;
    wxGrid* ListBoxPlay=(wxGrid*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);

    wxArrayInt selectedRows = ListBoxPlay->GetSelectedRows();
    int cnt = selectedRows.GetCount();
    if (cnt == 0) {
        wxMessageBox(_("You must select a row by clicking on the row number first!"), _("WARNING"));
    } else {
        for(size_t i = 0; i < cnt; i++)
        {
            ListBoxPlay->DeleteRows(selectedRows[i]);
        }
    }

    UnsavedChanges=true;
    ScanForFiles();
}

void xScheduleFrame::OnButtonPlaylistDeleteAllClick() {
    int nbidx=Notebook1->GetSelection();
    int baseid=1000*nbidx;
    wxGrid* ListBoxPlay=(wxGrid*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    ListBoxPlay->DeleteRows(0,ListBoxPlay->GetNumberRows());
    UnsavedChanges=true;
    ScanForFiles();
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

void xScheduleFrame::TimerNoPlay() {
    wxTimeSpan ts = wxDateTime::UNow() - starttime;
    long msec = ts.GetMilliseconds().ToLong();
    xout->TimerStart(msec);
    xout->TimerEnd();
    //wxString msg = wxString::Format(_("TimerNoPlay %d"),msec);
    //StatusBar1->SetStatusText(msg);
}

void xScheduleFrame::ResetTimer(SeqPlayerStates newstate) {
    SeqPlayerState = newstate;
    xout->ResetTimer();
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

void xScheduleFrame::ForceScheduleCheck() {
    LastWkDay = wxDateTime::Inv_WeekDay;
}

void xScheduleFrame::OnSchedTimer(wxTimerEvent& event)
{
    wxString WkDayStr,StartTime, EndTime;
    int SchedDay,i,cnt;
    bool CheckSchedule = false;

    static wxString RepeatOptions, Playlist, strStartTime, strEndTime;
    static wxDateTime LastTime = wxDateTime::Now();  // last time this method was called
    static long StartTimeSec,EndTimeSec;
    static bool MoreShowsToday = true;

    if (!CheckBoxRunSchedule->IsChecked()) return;
    wxDateTime n=wxDateTime::Now();
    long SecPastMidnight=n.GetHour()*60*60 + n.GetMinute()*60 + n.GetSecond();
    //StatusBar1->SetStatusText(_("OnSchedTimer: ") + n.FormatISOTime());

    if (basic.IsRunning()) {

        // playlist is running - check for the schedule end

        SecondsRemaining=EndTimeSec - SecPastMidnight;
        int minutes=(SecondsRemaining + 59) / 60;  // round up
        if (minutes > 60) {
            StatusBar1->SetStatusText(_("Show will end at: ") + strEndTime, 1);
        } else if (minutes > 0) {
            StatusBar1->SetStatusText(wxString::Format(_("Show will end in %d minutes"),minutes), 1);
        } else {
            StatusBar1->SetStatusText(_("Finishing playlist: ") + Playlist, 1);
        }

    } else {

        // no playlist running - wait for next event

        // should we check ShowEvents[]?
        wxDateTime::WeekDay CurrentWkDay = n.GetWeekDay();
        if (LastWkDay != CurrentWkDay) {
            // either the Run Schedule button was just pressed, or we just passed midnight
            CheckSchedule = true;
            LastWkDay = CurrentWkDay;
        } else {
            // has computer has been sleeping?
            wxTimeSpan TimeDiff=n.Subtract(LastTime);
            if (TimeDiff.GetSeconds().ToLong() > 10) CheckSchedule = true;
        }
        LastTime=n;
        SecondsRemaining=24*60*60 - SecPastMidnight;

        if (CheckSchedule) {
            // find first event for the day
            MoreShowsToday = false;
            cnt=ShowEvents.Count();
            WkDayStr.Printf(wxT("%d"),CurrentWkDay);
            for (i=0; i < cnt; i++) {
                if (ShowEvents[i].StartsWith(WkDayStr)) break;
            }
            if (i >= cnt) {
                StatusBar1->SetStatusText(_("No show scheduled for today"), 1);
                return;
            }
            do {
                UnpackSchedCode(ShowEvents[i], &SchedDay, StartTime, EndTime, RepeatOptions, Playlist);
                StartTimeSec=Time2Seconds(StartTime);
                EndTimeSec=Time2Seconds(EndTime);
                if (SecPastMidnight < EndTimeSec) {
                    MoreShowsToday = true;
                    strStartTime = StartTime.Left(2) + wxT(":") + StartTime.Right(2);
                    strEndTime = EndTime.Left(2) + wxT(":") + EndTime.Right(2);
                    break;
                }
                i++;
            } while (i < cnt && ShowEvents[i].StartsWith(WkDayStr));
            if (!MoreShowsToday) {
                StatusBar1->SetStatusText(_("No more shows scheduled for today"), 1);
                return;
            }
        } // CheckSchedule

        if (MoreShowsToday) {
            if (SecPastMidnight < StartTimeSec) {
                // have not reached show start time
                SecondsRemaining=StartTimeSec - SecPastMidnight;
                int minutes= (SecondsRemaining + 59) / 60;  // round up
                if (minutes > 60) {
                    StatusBar1->SetStatusText(_("Next show will start at: ") + strStartTime, 1);
                } else if (minutes > 1) {
                    StatusBar1->SetStatusText(wxString::Format(_("Next show will start in %d minutes"),minutes), 1);
                } else {
                    StatusBar1->SetStatusText(wxString::Format(_("Next show will start in %ld seconds"),SecondsRemaining), 1);
                }
            } else if (SecPastMidnight < EndTimeSec) {
                // start show
                int nbidx=FindNotebookPage(Playlist);
                if (!PortsOK) {
                    StatusBar1->SetStatusText(_("ERROR: serial ports did not initialize at program startup, cannot start playlist ") + Playlist, 1);
                } else if (nbidx > 0) {
                    PlayMode=SCHEDULE;
                    RunPlaylist(nbidx,RepeatOptions[0]=='R',RepeatOptions[1]=='F',RepeatOptions[2]=='L',false);
                } else {
                    StatusBar1->SetStatusText(_("ERROR: cannot find playlist ") + Playlist, 1);
                }
            } else {
                // check the next show
                ForceScheduleCheck();
            }
        }
    }
}


int xScheduleFrame::FindNotebookPage(wxString& pagename)
{
    for (int i=FixedPages; i < Notebook1->GetPageCount(); i++) {
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
        case DELAY_AFTER_PLAY:
            ts = wxDateTime::UNow() - starttime;
            msec = ts.GetMilliseconds().ToLong();
            if (msec > DelayAfterPlayMSEC) {
                ResetTimer(NO_SEQ);
                // reached end of song/sequence, so execute callback (if defined)
                basic.PlaybackEndCallback();
                return;
            } else {
                TimerNoPlay();
            }
            break;
        case STARTING_MEDIA:
            TimerNoPlay();
            if(PlayerDlg->MediaCtrl->GetState() == wxMEDIASTATE_PLAYING){
                SeqPlayerState = PLAYING_MEDIA;
            } else {
                PlayerDlg->MediaCtrl->Play();
            }
            break;
        case PLAYING_MEDIA:
            if (PlayerDlg->MediaCtrl->GetState() != wxMEDIASTATE_PLAYING) {
                ResetTimer(basic.IsRunning() ? DELAY_AFTER_PLAY : NO_SEQ);
            } else {
                TimerNoPlay();
            }
            break;
        case STARTING_LOR_ANIM:
            LorIter=LorEvents.begin();
            ResetTimer(PLAYING_LOR_ANIM);
            break;
        case STARTING_VIX_ANIM:
            if (VixLastChannel > VixNetwork.size()) VixLastChannel=VixNetwork.size();
            LastIntensity.resize(VixLastChannel,1);
            ResetTimer(PLAYING_VIX_ANIM);
            break;
        case PLAYING_LOR_ANIM:
            if (LorIter == LorEvents.end()) {
                ResetTimer(basic.IsRunning() ? DELAY_AFTER_PLAY : NO_SEQ);
                return;
            }
            ts = wxDateTime::UNow() - starttime;
            msec = ts.GetMilliseconds().ToLong();
            xout->TimerStart(msec);
            while (LorIter != LorEvents.end()) {

                startmsec=LorIter->first * 10;
                if (startmsec > msec) break;
                endmsec=LorIter->second->EndCentiSec * 10;
                netnum=LorIter->second->netnum;
                chindex=LorIter->second->chindex;
                //TextCtrlLog->AppendText(wxString::Format(_(" LOR ms=%ld, ch=%d, st=%d, en=%d\n"),msec,chindex,startmsec,endmsec));
                if (LorIter->second->EndIntesity == -1) {
                    switch (LorIter->second->action) {
                        case LOR_INTENSITY:
                            xout->SetIntensity(netnum,chindex,LorIter->second->StartIntensity);
                            break;
                        case LOR_TWINKLE:
                            xout->twinkle(netnum,chindex,400,LorIter->second->StartIntensity);
                            break;
                        case LOR_SHIMMER:
                            xout->shimmer(netnum,chindex,100,LorIter->second->StartIntensity);
                            break;
                    }
                } else {
                    duration = endmsec - startmsec;
                    switch (LorIter->second->action) {
                        case LOR_INTENSITY:
                            xout->ramp(netnum,chindex,duration,LorIter->second->StartIntensity,LorIter->second->EndIntesity);
                            break;
                        case LOR_TWINKLE:
                            xout->twinklefade(netnum,chindex,400,duration,LorIter->second->StartIntensity,LorIter->second->EndIntesity);
                            break;
                        case LOR_SHIMMER:
                            xout->shimmerfade(netnum,chindex,100,duration,LorIter->second->StartIntensity,LorIter->second->EndIntesity);
                            break;
                    }
                }

                LorIter++;
            }
            xout->TimerEnd();
            break;
        case PLAYING_VIX_ANIM:
            ts = wxDateTime::UNow() - starttime;
            msec = ts.GetMilliseconds().ToLong();
            period = msec / VixEventPeriod;
            if (period < VixNumPeriods) {
                xout->TimerStart(msec);
                for (chindex=0; chindex<VixLastChannel; chindex++) {
                    vixintensity=VixEventData[chindex*VixNumPeriods+period];
                    if (vixintensity != LastIntensity[chindex]) {
                        xout->SetIntensity(VixNetwork[chindex].first, VixNetwork[chindex].second, vixintensity);
                        LastIntensity[chindex]=vixintensity;
                    }
                }
                xout->TimerEnd();
            } else {
                ResetTimer(basic.IsRunning() ? DELAY_AFTER_PLAY : NO_SEQ);
            }
            break;
        case STARTING_LOR:
            if(PlayerDlg->MediaCtrl->GetState() == wxMEDIASTATE_PLAYING){
                LorIter=LorEvents.begin();
                ResetTimer(PLAYING_LOR);
            } else {
                PlayerDlg->MediaCtrl->Play();
            }
            break;
        case STARTING_VIX:
            if(PlayerDlg->MediaCtrl->GetState() == wxMEDIASTATE_PLAYING){
                if (VixLastChannel > VixNetwork.size()) VixLastChannel=VixNetwork.size();
                LastIntensity.resize(VixLastChannel,1);
                ResetTimer(PLAYING_VIX);
            } else {
                PlayerDlg->MediaCtrl->Play();
            }
            break;
        case PLAYING_LOR:
            if (PlayerDlg->MediaCtrl->GetState() != wxMEDIASTATE_PLAYING) {
                ResetTimer(basic.IsRunning() ? DELAY_AFTER_PLAY : PAUSE_LOR);
                return;
            }
            msec = PlayerDlg->MediaCtrl->Tell();
            xout->TimerStart(msec);
            while (LorIter != LorEvents.end()) {

                startmsec=LorIter->first * 10;
                if (startmsec > msec) break;
                endmsec=LorIter->second->EndCentiSec * 10;
                netnum=LorIter->second->netnum;
                chindex=LorIter->second->chindex;
                //TextCtrlLog->AppendText(wxString::Format(_(" LOR ms=%ld, ch=%d, st=%d, en=%d\n"),msec,chindex,startmsec,endmsec));
                if (LorIter->second->EndIntesity == -1) {
                    switch (LorIter->second->action) {
                        case LOR_INTENSITY:
                            xout->SetIntensity(netnum,chindex,LorIter->second->StartIntensity);
                            break;
                        case LOR_TWINKLE:
                            xout->twinkle(netnum,chindex,400,LorIter->second->StartIntensity);
                            break;
                        case LOR_SHIMMER:
                            xout->shimmer(netnum,chindex,100,LorIter->second->StartIntensity);
                            break;
                    }
                } else {
                    duration = endmsec - startmsec;
                    switch (LorIter->second->action) {
                        case LOR_INTENSITY:
                            xout->ramp(netnum,chindex,duration,LorIter->second->StartIntensity,LorIter->second->EndIntesity);
                            break;
                        case LOR_TWINKLE:
                            xout->twinklefade(netnum,chindex,400,duration,LorIter->second->StartIntensity,LorIter->second->EndIntesity);
                            break;
                        case LOR_SHIMMER:
                            xout->shimmerfade(netnum,chindex,100,duration,LorIter->second->StartIntensity,LorIter->second->EndIntesity);
                            break;
                    }
                }

                LorIter++;
            }
            xout->TimerEnd();
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
                ResetTimer(basic.IsRunning() ? DELAY_AFTER_PLAY : PAUSE_VIX);
                return;
            }
            msec = PlayerDlg->MediaCtrl->Tell();
            period = msec / VixEventPeriod;
            xout->TimerStart(msec);
            if (period < VixNumPeriods) {
                for (chindex=0; chindex<VixLastChannel; chindex++) {
                    vixintensity=VixEventData[chindex*VixNumPeriods+period];
                    if (vixintensity != LastIntensity[chindex]) {
                        xout->SetIntensity(VixNetwork[chindex].first, VixNetwork[chindex].second, vixintensity);
                        LastIntensity[chindex]=vixintensity;
                    }
                }
            }
            xout->TimerEnd();
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
    basic.SerialCallback();
}

void xScheduleFrame::LoadNetworkFile()
{
    long MaxChan;
    wxString tempstr;
    wxXmlDocument doc;
    if (doc.Load( networkFile.GetFullPath() )) {
        wxXmlNode* e=doc.GetRoot();
        tempstr=e->GetPropVal(wxT("LorMapping"), wxT("2"));
        tempstr.ToLong(&LorMapping);
        for( e=doc.GetRoot()->GetChildren(); e!=NULL; e=e->GetNext() ) {
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

void xScheduleFrame::AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels)
{
    int netnum=-1;
    int baud = (BaudRate == _("n/a")) ? 115200 : atoi(BaudRate.mb_str(wxConvUTF8));
    wxString msg = _("Error occurred while connecting to ") + NetworkType+ _(" network on ") + ComPort + _("\n\n");
    try {
        netnum=xout->addnetwork(NetworkType,MaxChannels,ComPort,baud);
    }
    catch (const char *str) {
        wxString errmsg(str,wxConvUTF8);
        wxMessageBox(msg + errmsg, _("Communication Error"));
        PortsOK=false;
    }
    catch (char *str) {
        wxString errmsg(str,wxConvUTF8);
        wxMessageBox(msg + errmsg, _("Communication Error"));
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
    wxArrayString filenames;
    bool ok;
    int i;

    int nbidx=Notebook1->GetSelection();
    int baseid=1000*nbidx;
    wxString PageName=Notebook1->GetPageText(nbidx);
    wxTreeCtrl* TreeCtrlFiles=(wxTreeCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_FILES,Notebook1);
    if (TreeCtrlFiles == 0) {
        wxMessageBox(_("Must be on a playlist tab"));
        return;
    }
    wxGrid* ListBoxPlay=(wxGrid*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxCheckBox* CheckBoxAudio=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_AUDIO,Notebook1);
    wxCheckBox* CheckBoxVideo=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_VIDEO,Notebook1);
    wxCheckBox* CheckBoxLOR=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_LOR,Notebook1);
    wxCheckBox* CheckBoxVixen=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_VIXEN,Notebook1);

    wxFileName* oName=new wxFileName();
    oName->AssignDir( CurrentDir );

    // if file was deleted, remove matching entry
    int cnt=ListBoxPlay->GetNumberRows();
    for (i=0; i<cnt; i++) {
        filenames.Add(ListBoxPlay->GetCellValue(i,0));
    }
    for (i=filenames.GetCount()-1; i >= 0; i--) {
        oName->SetFullName(filenames[i]);
        if (!oName->FileExists()) {
            ListBoxPlay->DeleteRows(i);
            UnsavedChanges=true;
            wxMessageBox(_("File ") + filenames[i] + _(" was deleted from the show directory\n\nRemoving it from playlist ") + PageName, _("Playlist Updated"));
        }
    }

    // scan directory for matches
    TreeCtrlFiles->DeleteAllItems();
    wxTreeItemId root=TreeCtrlFiles->AddRoot(_("Show Directory"));
    wxDir* d=new wxDir(CurrentDir);
    if (d->GetFirst(&filename)) {
        do {
            if (filenames.Index(filename) != wxNOT_FOUND) continue;
            oName->SetFullName(filename);
            ok=false;
            switch (ExtType(oName->GetExt())) {
                case 'a': ok=CheckBoxAudio->IsChecked(); break;
                case 'v': ok=CheckBoxVideo->IsChecked(); break;
                case 'L': ok=CheckBoxLOR->IsChecked(); break;
                case 'V': ok=CheckBoxVixen->IsChecked(); break;
            }
            if (ok) {
                TreeCtrlFiles->AppendItem(root,filename);
            }
        } while (d->GetNext(&filename));
    }
    delete d;
    delete oName;
    TreeCtrlFiles->ExpandAll();
}

// returns V for vixen, L for LOR, a for audio, v for video
char xScheduleFrame::ExtType(const wxString& ext) {
    if (ext == _("vix")) {
        return 'V';
    } else if (ext == _("lms") || ext == _("las")) {
        return 'L';
    } else if (ext == _("wav") || ext == _("mp3") ||
               ext == _("wma") || ext == _("aac") ||
               ext == _("mid")) {
        return 'a';
    } else if (ext == _("avi") || ext == _("mp4") ||
               ext == _("wmv") || ext == _("mov") ||
               ext == _("mpg")) {
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
    wxGrid* ListBoxPlay=(wxGrid*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxArrayInt selectedRows = ListBoxPlay->GetSelectedRows();
    if (selectedRows.GetCount() != 1) {
        wxMessageBox(_("Please select a single row by clicking on the row number!"), _("Error"));
    } else {
        PlayMode=SINGLE;
        wxString filename = ListBoxPlay->GetCellValue(selectedRows[0],0);
        // ignore delay value
        Play(filename,0);
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


void xScheduleFrame::StopPlayback()
{
    ResetTimer(NO_SEQ);
}


void xScheduleFrame::Play(wxString& filename, long delay) {
    DelayAfterPlayMSEC=delay*1000;  // convert seconds to milliseconds
    wxFileName oName(CurrentDir, filename);
    wxString fullpath=oName.GetFullPath();
    switch (ExtType(oName.GetExt())) {
        case 'a':
        case 'v':
            if (wxFile::Exists(fullpath) && PlayerDlg->MediaCtrl->Load(fullpath)) {
                ResetTimer(STARTING_MEDIA);
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
    if (!LoadLorFile(FileName)) return;
    xout->SetMaxIntensity(100);
    if (mediaFilename.IsEmpty()) {
        ResetTimer(STARTING_LOR_ANIM);
    } else if (!wxFile::Exists(mediaFilename)) {
        PlayerError(_("Cannot locate media file:\n") + mediaFilename + _("\n\nMake sure your media files are in the same directory as your sequences."));
    } else if (PlayerDlg->MediaCtrl->Load(mediaFilename)) {
        ShowPlayerSingle();
        ResetTimer(STARTING_LOR);
    } else {
        PlayerError(_("Unable to play file:\n")+mediaFilename);
    }
}

bool xScheduleFrame::LoadLorFile(wxString& FileName)
{
    LorEvents.clear();
    for (int i=0; i<MAXNETWORKS; i++) {
        LorLastUnit[i]=-1;
    }
    mediaFilename.clear();
    wxXmlDocument doc;
    if (doc.Load( FileName )) {
        wxXmlNode* root=doc.GetRoot();
        mediaFilename=root->GetPropVal(wxT("musicFilename"), wxT(""));
        for( wxXmlNode* e=root->GetChildren(); e!=NULL; e=e->GetNext() ) {
            if (e->GetName() == _("channels")) {
                LoadLorChannels(e);
            }
        }
        if (!mediaFilename.IsEmpty()) {
            wxPathFormat PathFmt = mediaFilename.Contains(_("\\")) ? wxPATH_DOS : wxPATH_NATIVE;
            wxFileName fn1(mediaFilename, PathFmt);
            if (!fn1.FileExists()) {
                wxFileName fn2(CurrentDir,fn1.GetFullName());
                mediaFilename=fn2.GetFullPath();
            }
        }
        return true;
    } else {
        PlayerError(_("Unable to load sequence:\n")+FileName);
    }
    return false;
}

void xScheduleFrame::LoadLorChannels(wxXmlNode* n)
{
    long netnum, unit, circuit;
    int chindex;
    wxString tempstr;
    for( wxXmlNode* e=n->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() != _("channel")) continue;
        if (e->HasProp(_("unit")) && e->HasProp(_("circuit"))) {
            tempstr=e->GetPropVal(wxT("unit"), wxT("1"));
            tempstr.ToLong(&unit);
            tempstr=e->GetPropVal(wxT("circuit"), wxT("0"));
            tempstr.ToLong(&circuit);
            tempstr=e->GetPropVal(wxT("network"), wxT("0"));
            tempstr.ToLong(&netnum);
            if (netnum < MAXNETWORKS) {
                chindex=(unit-1)*16+circuit-1;
                switch (LorMapping) {
                    case XLIGHTS_LORMAP_SINGLE:
                        if (chindex < VixNetwork.size()) {
                            LoadLorChannel(e, VixNetwork[chindex].first, VixNetwork[chindex].second);
                        }
                        break;
                    case XLIGHTS_LORMAP_MULTI:
                        if (chindex < xout->GetChannelCount(netnum)) {
                            LoadLorChannel(e,netnum,chindex);
                        }
                        break;
                    case XLIGHTS_LORMAP_STRICT:
                        LoadLorChannel(e,netnum,chindex);
                        break;
                }
                if (unit > LorLastUnit[netnum]) LorLastUnit[netnum]=unit;
            }
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
    if (!CheckPorts()) return;
    if (!LoadVixenFile(FileName)) return;
    if (VixEventPeriod < 0) {
        PlayerError(_("EventPeriodInMilliseconds is undefined"));
    } else if (VixLastChannel <= 0) {
        PlayerError(_("Unable to determine number of channels"));
    } else if (mediaFilename.IsEmpty()) {
        ResetTimer(STARTING_VIX_ANIM);
    } else if (!wxFile::Exists(mediaFilename)) {
        PlayerError(_("Cannot locate media file:\n") + mediaFilename + _("\n\nMake sure your media files are in the same directory as your sequences."));
    } else if (!PlayerDlg->MediaCtrl->Load(mediaFilename)) {
        PlayerError(_("Unable to play file:\n")+mediaFilename);
    } else {
        ResetTimer(STARTING_VIX);
        ShowPlayerSingle();
    }
}

bool xScheduleFrame::LoadVixenFile(wxString& FileName)
{
    long MaxIntensity = 255;
    long toValue;
    wxString tag,tempstr;
    wxFileName fn;
    fn.AssignDir(CurrentDir);
    mediaFilename.clear();
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
                mediaFilename = fn.GetFullPath();
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
        xout->SetMaxIntensity(MaxIntensity);
        VixNumPeriods = VixEventData.size() / VixLastChannel;
        return true;
    } else {
        PlayerError(_("Unable to load sequence:\n")+FileName);
    }
    return false;
}

void xScheduleFrame::OnButtonUpClick()
{
    int baseid=1000*Notebook1->GetSelection();
    wxGrid* ListBoxPlay=(wxGrid*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxArrayInt selectedRows = ListBoxPlay->GetSelectedRows();
    if (selectedRows.GetCount() != 1) {
        wxMessageBox(_("Please select a single row by clicking on the row number!"), _("Error"));
        return;
    }

    int idx = selectedRows[0];
    if (idx == 0) return;
    wxString filename = ListBoxPlay->GetCellValue(idx,0);
    wxString delay = ListBoxPlay->GetCellValue(idx,1);
    ListBoxPlay->DeleteRows(idx);
    idx--;
    ListBoxPlay->InsertRows(idx);
    ListBoxPlay->SetCellValue(idx,0,filename);
    ListBoxPlay->SetCellValue(idx,1,delay);
    ListBoxPlay->SelectRow(idx);
    UnsavedChanges=true;
}

void xScheduleFrame::OnButtonDownClick()
{
    int baseid=1000*Notebook1->GetSelection();
    wxGrid* ListBoxPlay=(wxGrid*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxArrayInt selectedRows = ListBoxPlay->GetSelectedRows();
    if (selectedRows.GetCount() != 1) {
        wxMessageBox(_("Please select a single row by clicking on the row number!"), _("Error"));
        return;
    }

    int idx = selectedRows[0];
    if (idx == ListBoxPlay->GetNumberRows()-1) return;
    wxString filename = ListBoxPlay->GetCellValue(idx,0);
    wxString delay = ListBoxPlay->GetCellValue(idx,1);
    ListBoxPlay->DeleteRows(idx);
    idx++;
    ListBoxPlay->InsertRows(idx);
    ListBoxPlay->SetCellValue(idx,0,filename);
    ListBoxPlay->SetCellValue(idx,1,delay);
    ListBoxPlay->SelectRow(idx);
    UnsavedChanges=true;
}

wxString xScheduleFrame::LorNetDesc(int netnum)
{
    wxString result;

    if (netnum==0) {
        result = _("default network");
    } else {
        char c = netnum - 1 + 'A';
        result = wxString::Format(_("Aux %c network"),c);
    }
    return result;
}

void xScheduleFrame::OnButtonInfoClick()
{
    int baseid=1000*Notebook1->GetSelection();
    wxGrid* ListBoxPlay=(wxGrid*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxArrayInt selectedRows = ListBoxPlay->GetSelectedRows();
    if (selectedRows.GetCount() != 1) {
        wxMessageBox(_("Please select a single row by clicking on the row number!"), _("Error"));
        return;
    }

    wxString filename = ListBoxPlay->GetCellValue(selectedRows[0],0);
    wxString msg = _("Information for ") + filename + _("\n\n");

    wxFileName oName(CurrentDir, filename);
    wxString fullpath=oName.GetFullPath();
    switch (ExtType(oName.GetExt())) {
        case 'L':
            if (LoadLorFile(fullpath)) {
                msg+=_("LOR channel mapping mode: ");
                switch (LorMapping) {
                    case XLIGHTS_LORMAP_SINGLE:
                        msg+=_("single network");
                        break;
                    case XLIGHTS_LORMAP_MULTI:
                        msg+=_("multi network");
                        break;
                    case XLIGHTS_LORMAP_STRICT:
                        msg+=_("strict");
                        break;
                }
                msg+=_("\n");
                if (mediaFilename.IsEmpty()) {
                    msg+=_("Media file: none");
                } else if (!wxFile::Exists(mediaFilename)) {
                    msg+=_("Cannot locate media file:\n") + mediaFilename + _("\n\nMake sure your media files are in the same directory as your sequences.");
                } else {
                    msg+=_("Media file:\n") + mediaFilename;
                }
                msg += _("\n\nChannel Map:");
                for (int netidx=0; netidx<MAXNETWORKS; netidx++) {
                    if (LorLastUnit[netidx] > 0) {
                        int lastch = LorLastUnit[netidx]*16;
                        int xch = xout->GetChannelCount(netidx);
                        if (xch < lastch) lastch = xch;
                        msg += wxString::Format(_("\nLOR sequence, ")+LorNetDesc(netidx)+_(", units 1-%d map to ")+xout->GetNetworkDesc(netidx)+_(" channels 1-%d"),LorLastUnit[netidx],lastch);
                    }
                }
            } else {
                msg+=_("Unable to load sequence file:\n") + fullpath;
            }
            break;
        case 'V':
            if (LoadVixenFile(fullpath)) {
                if (mediaFilename.IsEmpty()) {
                    msg+=_("Media file: none");
                } else if (!wxFile::Exists(mediaFilename)) {
                    msg+=_("Cannot locate media file:\n") + mediaFilename + _("\n\nMake sure your media files are in the same directory as your sequences.");
                } else {
                    msg+=_("Media file: ") + mediaFilename;
                }
                float seqlen = (float)VixNumPeriods*VixEventPeriod/1000.0;
                msg += wxString::Format(_("\nSequence Length: %3.1f sec\nEvent Period: %d msec\nChannel Count: %d"),seqlen,VixEventPeriod,VixLastChannel);
                if (VixLastChannel > 0) {
                    msg += _("\n\nChannel Map:");
                    int mapcnt = 0;
                    int LeftToMap = VixLastChannel;
                    int netidx = 0;
                    while (mapcnt < VixLastChannel && netidx < MAXNETWORKS) {
                        int chcnt = xout->GetChannelCount(netidx);
                        if (chcnt > 0) {
                            int mapcnt1 = chcnt < LeftToMap ? chcnt : LeftToMap;
                            msg += wxString::Format(_("\nVixen channels %d-%d map to %s channels %d-%d"),mapcnt+1,mapcnt+mapcnt1,xout->GetNetworkDesc(netidx).c_str(),1,mapcnt1);
                            mapcnt += mapcnt1;
                            LeftToMap -= mapcnt1;
                        }
                        netidx++;
                    }
                    if (LeftToMap > 0) {
                        msg += wxString::Format(_("\nVixen channels %d-%d are unmapped"),mapcnt+1,VixLastChannel);
                    }
                }
            } else {
                msg+=_("Unable to load sequence file:\n") + fullpath;
            }
            break;
        default:
            msg+=_("Please select a Vixen or LOR sequence when using this command.");
            break;
    }

    wxMessageBox(msg, _("Sequence Info"));
}

void xScheduleFrame::OnAuiToolBarItemAddClick(wxCommandEvent& event)
{
    wxTextEntryDialog dialog(this, _("Enter name for new playlist"), _("New Playlist"));
    if (dialog.ShowModal() != wxID_OK) return;
    wxString name=dialog.GetValue();
    if (name.IsEmpty()) return;
    if (FindNotebookPage(name) >= 0) {
        wxMessageBox(_("That name is already in use!"), _("Error"));
        return;
    }
    AddPlaylist(name);
    UnsavedChanges=true;
}

void xScheduleFrame::OnAuiToolBarItemDelClick(wxCommandEvent& event)
{
    DelListDialog dialog(this);
    int idx=Notebook1->GetSelection();
    if (idx  < FixedPages) {
        wxMessageBox(_("Can't delete this page!"), _("Error"));
        return;
    }
    dialog.StaticTextDelName->SetLabel(Notebook1->GetPageText(idx));
    if (dialog.ShowModal() != wxID_OK) return;
    Notebook1->DeletePage(idx);
    UnsavedChanges=true;
}

void xScheduleFrame::OnMenuItemRenameListSelected(wxCommandEvent& event)
{
    int nbidx=Notebook1->GetSelection();
    if (nbidx < FixedPages) {
        wxMessageBox(_("Can't rename this page"), _("Error"));
        return;
    }
    wxString PlaylistName=Notebook1->GetPageText(nbidx);
    wxTextEntryDialog dialog(this, _("Enter a new name"), _("Rename Playlist"), PlaylistName);
    if (dialog.ShowModal() != wxID_OK) return;
    wxString NewName=dialog.GetValue();
    if (NewName.IsEmpty() || NewName == PlaylistName) return;
    if (FindNotebookPage(NewName) >= 0) {
        wxMessageBox(_("That name is already in use!"), _("Error"));
        return;
    }
    Notebook1->SetPageText(nbidx,NewName);
    UnsavedChanges=true;
}

void xScheduleFrame::OnAuiToolBarItemHelpClick(wxCommandEvent& event)
{
    if (!wxLaunchDefaultBrowser(_(XLIGHTS_HELP_URL)))
    {
        wxMessageBox(_("Help requires Internet access. Unable to access help."), _("Error"));
    }
}

void xScheduleFrame::OnScriptHelpClick(wxCommandEvent& event)
{
    if (!wxLaunchDefaultBrowser(_(XLIGHTS_SCRIPT_HELP_URL)))
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
    wxString v;
    wxCheckBox* chkbox;
    wxTextCtrl* TextCtrlLogic;
    wxXmlDocument doc;
    wxXmlNode *item, *plist, *scriptnode, *scripttext;
    wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("xSchedule") );
    root->AddProperty( wxT("computer"), wxGetHostName());
    doc.SetRoot( root );

    // save schedule
    wxXmlNode* sched = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("schedule") );
    root->AddChild(sched);
    int cnt=ShowEvents.GetCount();
    for (int i=0; i<cnt; i++) {
        item = new wxXmlNode( wxXML_ELEMENT_NODE, _("event") );
        item->AddProperty( wxT("schedcode"), ShowEvents[i] );
        sched->AddChild( item );
    }

    // save playlists
    wxXmlNode* lists = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("playlists") );
    root->AddChild(lists);

    cnt=Notebook1->GetPageCount();
    for (int pagenum=FixedPages; pagenum < cnt; pagenum++) {
        plist = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("playlist") );
        plist->AddProperty( wxT("name"), Notebook1->GetPageText(pagenum) );
        baseid=1000*pagenum;
        wxGrid* ListBoxPlay=(wxGrid*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
        for (int i=CHKBOX_AUDIO; i<=CHKBOX_MOVIEMODE; i++) {
            chkbox=(wxCheckBox*)wxWindow::FindWindowById(baseid+i,Notebook1);
            v = chkbox->GetValue() ? _("1") : _("0");
            wxString label = chkbox->GetLabelText();
            label.Replace(_(" "), _(""));
            plist->AddProperty( label, v );
        }
        lists->AddChild( plist );

        RowCount=ListBoxPlay->GetNumberRows();
        for (unsigned int r=0; r < RowCount; r++ ) {
            item = new wxXmlNode( wxXML_ELEMENT_NODE, _("listitem") );
            item->AddProperty( wxT("name"), ListBoxPlay->GetCellValue(r,0) );
            item->AddProperty( wxT("delay"), ListBoxPlay->GetCellValue(r,1) );
            //v = ListBoxPlay->IsChecked(r) ? _("1") : _("0");
            //item->AddProperty( wxT("enabled"), v );
            plist->AddChild( item );
        }

        TextCtrlLogic = (wxTextCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LOGIC,Notebook1);
        if (TextCtrlLogic && TextCtrlLogic->IsShown()) {
            scriptnode = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("script") );
            scripttext = new wxXmlNode( wxXML_TEXT_NODE, wxT("scripttext") );
            scripttext->SetContent( TextCtrlLogic->GetValue() );
            plist->AddChild( scriptnode );
            scriptnode->AddChild( scripttext );
        }
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
    for( wxXmlNode* e=n->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() == _("event")) {
            wxString schedcode = e->GetPropVal( wxT("schedcode"), wxT(""));
            if (schedcode.Len() > 10) ShowEvents.Add(schedcode);
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
    wxGrid* ListBoxPlay = (wxGrid*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxTextCtrl* TextCtrlLogic = (wxTextCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LOGIC,Notebook1);
    wxButton* ButtonRemoveScript=(wxButton*)wxWindow::FindWindowById(baseid+REMOVE_SCRIPT_BUTTON,Notebook1);
    int cnt=0;
    for( wxXmlNode* e=n->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() == _("listitem")) {
            //wxString itemname = e->GetPropVal( wxT("name"), wxT(""));
            //ListBoxPlay->AppendString(itemname);
            //chkval = e->GetPropVal( wxT("enabled"), wxT("0"));
            //ListBoxPlay->Check(cnt, chkval == _("1"));
            ListBoxPlay->AppendRows(1);
            ListBoxPlay->SetCellValue(cnt,0,e->GetPropVal(wxT("name"), wxT("")));
            ListBoxPlay->SetCellValue(cnt,1,e->GetPropVal(wxT("delay"), wxT("0")));
            cnt++;
        } else if (e->GetName() == _("script")) {
            ButtonRemoveScript->Show();
            TextCtrlLogic->Show();
            TextCtrlLogic->ChangeValue( e->GetNodeContent() );
        }
    }
    ScanForFiles();
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

wxWindow* xScheduleFrame::FindNotebookControl(int nbidx, PlayListIds id) {
    return wxWindow::FindWindowById(1000*nbidx+id, Notebook1);
}

void xScheduleFrame::RunPlaylist(int nbidx, bool Repeat, bool FirstItemOnce, bool LastItemOnce, bool LightsOff)
{
    wxString userscript;
    wxString PageName=Notebook1->GetPageText(nbidx);
    TextCtrlLog->AppendText(_("At: ") + wxDateTime::Now().FormatTime() + _("\n"));
    TextCtrlLog->AppendText(_("Starting playlist ") + PageName + _("\n"));
    if (basic.IsRunning()) {
        SendToLogAndStatusBar(_("WARNING: another playlist is already running!"));
        return;
    }
    wxCheckBox* MovieMode=(wxCheckBox*)FindNotebookControl(nbidx,CHKBOX_MOVIEMODE);
    wxTextCtrl* LogicCtl=(wxTextCtrl*)FindNotebookControl(nbidx,PLAYLIST_LOGIC);
    if (LogicCtl && LogicCtl->IsShown()) {
        // run custom script
        userscript=LogicCtl->GetValue();
    } else {
        // this is a playlist page, run generic script
        userscript=CreateScript(PageName,Repeat,FirstItemOnce,LastItemOnce,LightsOff);
    }
    if (userscript.IsEmpty()) {
        SendToLogAndStatusBar(_("ERROR: no script to run!"));
        return;
    }
    if (!userscript.EndsWith(_("\n"))) userscript += _("\n"); // ensure script ends with a newline
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
/*
void xScheduleFrame::OnButtonWizardClick()
{
    WizardDialog dialog(this);
    int nbidx=Notebook1->GetSelection();
    dialog.StaticTextListName->SetLabel(Notebook1->GetPageText(nbidx));
    if (dialog.ShowModal() != wxID_OK) return;

    bool FirstItemOnce = dialog.CheckBoxFirstItem->GetValue();
    bool LastItemOnce = dialog.CheckBoxLastItem->GetValue();
    bool LightsOff = dialog.CheckBoxLightsOff->GetValue();
    wxTextCtrl* LogicCtl=(wxTextCtrl*)FindNotebookControl(nbidx,PLAYLIST_LOGIC);
    wxStaticText* PriNameCtl=(wxStaticText*)FindNotebookControl(nbidx,PRIMARY_NAME);
    wxString PlaylistName = PriNameCtl->GetLabel();
    LogicCtl->SetValue( CreateScript(PlaylistName,FirstItemOnce,LastItemOnce,LightsOff) );
    UnsavedChanges=true;
}
*/
wxString xScheduleFrame::CreateScript(wxString ListName, bool Repeat, bool FirstItemOnce, bool LastItemOnce, bool LightsOff)
{
    wxString script;
    wxString loopstart = Repeat && FirstItemOnce ? _("2") : _("1");
    wxString loopend = Repeat && LastItemOnce ? _("PLAYLISTSIZE-1") : _("PLAYLISTSIZE");

    script.Append(_("100 REM *\n"));
    script.Append(_("120 REM * Created: ") + wxDateTime::Now().Format() + _("\n"));
    script.Append(_("130 REM *\n"));
    script.Append(_("140 LET ListName$=\"") + ListName + _("\"\n"));
    script.Append(_("150 SETPLAYLIST ListName$\n"));
    script.Append(_("160 ONPLAYBACKEND 300\n"));
    script.Append(_("170 LET NextItem=1\n"));
    script.Append(_("200 REM *\n"));
    script.Append(_("201 REM * Play item NextItem\n"));
    script.Append(_("202 REM *\n"));
    script.Append(_("210 LET LastItemPlayed=NextItem\n"));
    script.Append(_("215 PRINT \"At:\", FORMATDATETIME$(NOW,5)\n"));
    script.Append(_("220 PRINT \"Playing:\",ITEMNAME$(NextItem)\n"));
    script.Append(_("230 PLAYITEM NextItem\n"));
    script.Append(_("240 WAIT\n"));
    script.Append(_("300 REM *\n"));
    script.Append(_("301 REM * Jump here at end of song or sequence\n"));
    script.Append(_("302 REM *\n"));
    if (LightsOff) script.Append(_("305 LIGHTSOFF\n"));
    //script.Append(_("303 PRINT \"SECONDSREMAINING:\",SECONDSREMAINING\n"));
    script.Append(_("310 IF SECONDSREMAINING <= 0 THEN 400\n"));
    script.Append(_("320 LET NextItem=LastItemPlayed+1\n"));
    script.Append(_("330 IF NextItem <= ") + loopend + _(" THEN 200\n"));
    if (Repeat) {
        script.Append(_("340 LET NextItem=") + loopstart + _("\n"));
        script.Append(_("350 GOTO 200\n"));
    }
    script.Append(_("400 REM Reached scheduled end time\n"));
    if (LastItemOnce) {
        script.Append(_("410 ONPLAYBACKEND 490\n"));
        script.Append(_("415 PRINT \"At:\", FORMATDATETIME$(NOW,5)\n"));
        script.Append(_("420 PRINT \"Playing:\",ITEMNAME$(PLAYLISTSIZE)\n"));
        script.Append(_("430 PLAYITEM PLAYLISTSIZE\n"));
        script.Append(_("440 WAIT\n"));
    }
    script.Append(_("490 LIGHTSOFF\n"));
    //wxMessageBox(script);
    return script;
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

void xScheduleFrame::OnAuiToolBarItemPlayClick(wxCommandEvent& event)
{
    if (!CheckPorts()) return;
    int selidx = Notebook1->GetSelection();
    int cnt = Notebook1->GetPageCount();
    if (cnt < FixedPages) {
        wxMessageBox(_("Nothing to play. Create a playlist first."), _("Error"));
        return;
    }
    // get playback options
    WizardDialog dialog(this);
    for (int i=FixedPages; i < cnt; i++) {
        dialog.ChoicePlayList->Append(Notebook1->GetPageText(i));
    }
    dialog.ChoicePlayList->SetSelection(selidx >= FixedPages ? selidx-FixedPages : 0);
    if (dialog.ShowModal() != wxID_OK) return;
    //wxMessageBox(_("OnAuiToolBarItemPlayClick: GetSelection"));
    selidx = dialog.ChoicePlayList->GetSelection() + FixedPages;
    PlayMode=PLAYLIST;
    SecondsRemaining=1;
    //wxMessageBox(_("OnAuiToolBarItemPlayClick: RunPlaylist"));
    RunPlaylist(selidx,dialog.CheckBoxRepeat->IsChecked(),dialog.CheckBoxFirstItem->IsChecked(),dialog.CheckBoxLastItem->IsChecked(),dialog.CheckBoxLightsOff->IsChecked());
}

// convert ChoiceBox index to hhmm
int xScheduleFrame::TimeIdx2Time(int TimeIdx) {
    return (TimeIdx / 4) * 100 + (TimeIdx % 4) * 15;
}


// convert hhmm string to seconds past midnight
int xScheduleFrame::Time2Seconds(const wxString& hhmm) {
    long t;
    if (hhmm.ToLong(&t)) {
        int hh=t / 100;
        int mm=t % 100;
        return hh*60*60+mm*60;
    } else {
        return 0;
    }
}


// convert hhmm string to ChoiceBox index
int xScheduleFrame::Time2TimeIdx(const wxString& hhmm) {
    long t;
    if (hhmm.ToLong(&t)) {
        int hh=t / 100;
        int mm=t % 100;
        return (hh * 4) + (mm / 15);
    } else {
        return 0;
    }
}


void xScheduleFrame::PopulateShowDialog(AddShowDialog& dialog) {

    // populate playlist selection

    int cnt = Notebook1->GetPageCount();
    for (int i=FixedPages; i < cnt; i++) {
        dialog.ChoicePlayList->AppendString(Notebook1->GetPageText(i));
    }

    // populate start & end times

    wxDateTime t;
    t.Set(0,15,0,0); // 15 minutes after midnight
    for (int i=0; i<95; i++) {
        if (i < 94) dialog.ChoiceStartTime->AppendString(t.Format(timefmt));
        if (i > 0) dialog.ChoiceEndTime->AppendString(t.Format(timefmt));
        t+=wxTimeSpan::Minutes(15);
    }
}

void xScheduleFrame::OnButtonAddShowClick(wxCommandEvent& event)
{
    int StartTimeIdx, EndTimeIdx;
    wxString Playlist, PartialCode;
    int cnt = Notebook1->GetPageCount();
    if (cnt < FixedPages) {
        wxMessageBox(_("You must create at least one playlist before scheduling your show."), _("Error"));
        return;
    }
    AddShowDialog dialog(this);
    PopulateShowDialog(dialog);

    while (dialog.ShowModal() == wxID_OK) {
        Playlist = dialog.ChoicePlayList->GetStringSelection();
        if (Playlist.IsEmpty()) {
            wxMessageBox(_("Select a playlist."), _("Error"));
            continue;
        }
        StartTimeIdx=dialog.ChoiceStartTime->GetSelection();
        if (StartTimeIdx == wxNOT_FOUND) {
            wxMessageBox(_("Select a start time."), _("Error"));
            continue;
        }
        EndTimeIdx=dialog.ChoiceEndTime->GetSelection();
        if (EndTimeIdx == wxNOT_FOUND) {
            wxMessageBox(_("Select an end time."), _("Error"));
            continue;
        }
        if (StartTimeIdx > EndTimeIdx) {
            wxMessageBox(_("Start time must be before end time."), _("Error"));
            continue;
        }
        PartialCode.Printf(wxT("%04d-%04d %c%c%c "),TimeIdx2Time(StartTimeIdx+1),TimeIdx2Time(EndTimeIdx+2),
                         dialog.CheckBoxRepeat->IsChecked() ? 'R' : '-',
                         dialog.CheckBoxFirstItem->IsChecked() ? 'F' : '-',
                         dialog.CheckBoxLastItem->IsChecked() ? 'L' : '-');
        //wxMessageBox(PartialCode, _("SchedCode"));
        if (dialog.CheckBoxSu->IsChecked()) AddShow(wxDateTime::Sun,PartialCode,Playlist);
        if (dialog.CheckBoxMo->IsChecked()) AddShow(wxDateTime::Mon,PartialCode,Playlist);
        if (dialog.CheckBoxTu->IsChecked()) AddShow(wxDateTime::Tue,PartialCode,Playlist);
        if (dialog.CheckBoxWe->IsChecked()) AddShow(wxDateTime::Wed,PartialCode,Playlist);
        if (dialog.CheckBoxTh->IsChecked()) AddShow(wxDateTime::Thu,PartialCode,Playlist);
        if (dialog.CheckBoxFr->IsChecked()) AddShow(wxDateTime::Fri,PartialCode,Playlist);
        if (dialog.CheckBoxSa->IsChecked()) AddShow(wxDateTime::Sat,PartialCode,Playlist);
        DisplaySchedule();
        return;
    }
}

void xScheduleFrame::UnpackSchedCode(const wxString& SchedCode, int* WkDay, wxString& StartTime, wxString& EndTime, wxString& RepeatOptions, wxString& Playlist) {
    wxChar WkDayChar=SchedCode[0];
    *WkDay=WkDayChar - '0';
    StartTime=SchedCode(1,4);
    EndTime=SchedCode(6,4);
    RepeatOptions=SchedCode(11,3);
    Playlist=SchedCode.Mid(15);
}

// populates ListBoxSched for single day
int xScheduleFrame::DisplayScheduleOneDay(wxDateTime::WeekDay wkday) {
    wxString WkDayStr, EventDesc, RepeatDesc, StartTime, EndTime, RepeatOptions, Playlist;
    int SchedDay;
    int cnt=0;
    WkDayStr.Printf(wxT("%d"),wkday);
    wxString WkDayHeading = wxT("--------- ") + wxDateTime::GetWeekDayName(wkday) + wxT(" ---------");
    ListBoxSched->Append(WkDayHeading);
    for (int i=0; i < ShowEvents.Count(); i++) {
        if (ShowEvents[i].StartsWith(WkDayStr)) {
            UnpackSchedCode(ShowEvents[i], &SchedDay, StartTime, EndTime, RepeatOptions, Playlist);
            if (RepeatOptions[0]=='R') {
                RepeatDesc=_("  (repeat");
                if (RepeatOptions[1]=='F') RepeatDesc+=_(", first once");
                if (RepeatOptions[2]=='L') RepeatDesc+=_(", last once");
                RepeatDesc+=_(")");
            } else {
                RepeatDesc.clear();
            }
            EventDesc=wxT("   ") + StartTime.Left(2) + wxT(":") + StartTime.Mid(2) + wxT(" to ") + EndTime.Left(2) + wxT(":") + EndTime.Mid(2) + wxT("  ") + Playlist + RepeatDesc;
            ListBoxSched->Append(EventDesc, new wxStringClientData(ShowEvents[i]));
            cnt++;
        }
    }
    if (cnt == 0) ListBoxSched->Append(wxT("   <no show scheduled>"));
    ListBoxSched->Append(wxT(""));
    return cnt;
}

// populates ListBoxSched based on contents of ShowEvents[]
void xScheduleFrame::DisplaySchedule() {
    ListBoxSched->Clear();
    ShowEvents.Sort();
    DisplayScheduleOneDay(wxDateTime::Sun);
    DisplayScheduleOneDay(wxDateTime::Mon);
    DisplayScheduleOneDay(wxDateTime::Tue);
    DisplayScheduleOneDay(wxDateTime::Wed);
    DisplayScheduleOneDay(wxDateTime::Thu);
    DisplayScheduleOneDay(wxDateTime::Fri);
    DisplayScheduleOneDay(wxDateTime::Sat);
    bool hasevents=!ShowEvents.IsEmpty();
    CheckBoxRunSchedule->Enable(hasevents && PortsOK);
    ButtonUpdateShow->Enable(hasevents);
    ButtonDeleteShow->Enable(hasevents);
    //ButtonDeselect->Enable(hasevents);
}

void xScheduleFrame::AddShow(wxDateTime::WeekDay wkday, const wxString& StartStop, const wxString& Playlist) {
    wxString WkDayStr;
    WkDayStr.Printf(wxT("%d"),wkday);
    wxString SchedCode = WkDayStr + StartStop + Playlist;
    ShowEvents.Add(SchedCode);
    UnsavedChanges=true;
}


void xScheduleFrame::OnButtonUpdateShowClick(wxCommandEvent& event)
{
    int StartTimeIdx, EndTimeIdx;
    wxString SchedCode, StartTime, EndTime, RepeatOptions, Playlist, PartialCode;
    int WkDay;
    wxArrayInt selections;
    wxStringClientData *SchedPtr;
    int cnt=ListBoxSched->GetSelections(selections);
    int updcnt=0;
    for (int i=cnt-1; i>=0; i--) {
        SchedPtr = (wxStringClientData*)ListBoxSched->GetClientObject(selections[i]);
        if (SchedPtr) {
            updcnt++;
            SchedCode=SchedPtr->GetData();
        }
    }
    if (updcnt != 1) {
        wxMessageBox(_("You must select a single item to edit."));
        return;
    }

    AddShowDialog dialog(this);
    PopulateShowDialog(dialog);

    // allow all fields to be updated
    UnpackSchedCode(SchedCode, &WkDay, StartTime, EndTime, RepeatOptions, Playlist);
    dialog.ChoicePlayList->SetStringSelection(Playlist);
    dialog.ChoiceStartTime->SetSelection(Time2TimeIdx(StartTime)-1);
    dialog.ChoiceEndTime->SetSelection(Time2TimeIdx(EndTime)-2);
    dialog.CheckBoxRepeat->SetValue(RepeatOptions[0]=='R');
    dialog.CheckBoxFirstItem->SetValue(RepeatOptions[1]=='F');
    dialog.CheckBoxLastItem->SetValue(RepeatOptions[2]=='L');
    dialog.CheckBoxSu->SetValue(wxDateTime::Sun==WkDay);
    dialog.CheckBoxMo->SetValue(wxDateTime::Mon==WkDay);
    dialog.CheckBoxTu->SetValue(wxDateTime::Tue==WkDay);
    dialog.CheckBoxWe->SetValue(wxDateTime::Wed==WkDay);
    dialog.CheckBoxTh->SetValue(wxDateTime::Thu==WkDay);
    dialog.CheckBoxFr->SetValue(wxDateTime::Fri==WkDay);
    dialog.CheckBoxSa->SetValue(wxDateTime::Sat==WkDay);

    while (dialog.ShowModal() == wxID_OK) {
        Playlist = dialog.ChoicePlayList->GetStringSelection();
        if (updcnt == 1) {
            if (Playlist.IsEmpty()) {
                wxMessageBox(_("Select a playlist."), _("Error"));
                continue;
            }
            StartTimeIdx=dialog.ChoiceStartTime->GetSelection();
            if (StartTimeIdx == wxNOT_FOUND) {
                wxMessageBox(_("Select a start time."), _("Error"));
                continue;
            }
            EndTimeIdx=dialog.ChoiceEndTime->GetSelection();
            if (EndTimeIdx == wxNOT_FOUND) {
                wxMessageBox(_("Select an end time."), _("Error"));
                continue;
            }
        }
        if (StartTimeIdx != wxNOT_FOUND && EndTimeIdx != wxNOT_FOUND && StartTimeIdx > EndTimeIdx) {
            wxMessageBox(_("Start time must be before end time."), _("Error"));
            continue;
        }

        ShowEvents.Remove(SchedCode);
        PartialCode.Printf(wxT("%04d-%04d %c%c%c "),TimeIdx2Time(StartTimeIdx+1),TimeIdx2Time(EndTimeIdx+2),
                         dialog.CheckBoxRepeat->IsChecked() ? 'R' : '-',
                         dialog.CheckBoxFirstItem->IsChecked() ? 'F' : '-',
                         dialog.CheckBoxLastItem->IsChecked() ? 'L' : '-');
        //wxMessageBox(PartialCode, _("SchedCode"));
        if (dialog.CheckBoxSu->IsChecked()) AddShow(wxDateTime::Sun,PartialCode,Playlist);
        if (dialog.CheckBoxMo->IsChecked()) AddShow(wxDateTime::Mon,PartialCode,Playlist);
        if (dialog.CheckBoxTu->IsChecked()) AddShow(wxDateTime::Tue,PartialCode,Playlist);
        if (dialog.CheckBoxWe->IsChecked()) AddShow(wxDateTime::Wed,PartialCode,Playlist);
        if (dialog.CheckBoxTh->IsChecked()) AddShow(wxDateTime::Thu,PartialCode,Playlist);
        if (dialog.CheckBoxFr->IsChecked()) AddShow(wxDateTime::Fri,PartialCode,Playlist);
        if (dialog.CheckBoxSa->IsChecked()) AddShow(wxDateTime::Sat,PartialCode,Playlist);
        DisplaySchedule();
        UnsavedChanges=true;

        return;
    }
}

void xScheduleFrame::OnButtonDeleteShowClick(wxCommandEvent& event)
{
    wxArrayInt selections;
    wxStringClientData *SchedCode;
    int delcnt=0;
    int cnt=ListBoxSched->GetSelections(selections);
    for (int i=cnt-1; i>=0; i--) {
        SchedCode = (wxStringClientData*)ListBoxSched->GetClientObject(selections[i]);
        if (SchedCode) {
            ShowEvents.Remove(SchedCode->GetData());
            delcnt++;
        }
    }
    if (delcnt==0) {
        wxMessageBox(_("You must select one or more scheduled items first!"));
    } else {
        DisplaySchedule();
        UnsavedChanges=true;
    }
}

void xScheduleFrame::OnButtonDeselectClick(wxCommandEvent& event)
{
    ListBoxSched->DeselectAll();
}

void xScheduleFrame::OnCheckBoxRunScheduleClick(wxCommandEvent& event)
{
    basic.halt();
    bool notrunning=!CheckBoxRunSchedule->IsChecked();
    bool hasevents=!ShowEvents.IsEmpty();
    ButtonAddShow->Enable(notrunning);
    ButtonUpdateShow->Enable(notrunning && hasevents);
    ButtonDeleteShow->Enable(notrunning && hasevents);
    ButtonDeselect->Enable(notrunning && hasevents);
    AuiToolBar1->EnableTool(ID_AUITOOLBARITEM_PLAY, notrunning);
    if (CheckBoxRunSchedule->IsChecked()) {
        ForceScheduleCheck();
        StatusBar1->SetStatusText(_("Starting scheduler"), 1);
    } else {
        StatusBar1->SetStatusText(_("Scheduler not running"), 1);
    }
}


void xScheduleFrame::OnBitmapButtonSchedInfoClick(wxCommandEvent& event)
{
    wxMessageBox(_("1) To select multiple items, just click on each\nof the desired items. No ctrl-click or shift-click.\n\n2) The schedule is NOT SAVED until you click the save icon.\n\n3)  The schedule WILL NOT RUN unless the Run\nSchedule checkbox is checked."),_("Schedule Tab"));
}

void xScheduleFrame::OnMenuItemCustomScriptSelected(wxCommandEvent& event)
{
    int nbIdx=Notebook1->GetSelection();
    wxTextCtrl* TextCtrlLogic=(wxTextCtrl*)FindNotebookControl(nbIdx,PLAYLIST_LOGIC);
    if (TextCtrlLogic == 0) {
        wxMessageBox(_("Must be on a playlist tab"));
        return;
    }
    // get playback options
    WizardDialog dialog(this);
    wxString nbName=Notebook1->GetPageText(nbIdx);
    dialog.ChoicePlayList->Append(nbName);
    dialog.ChoicePlayList->SetSelection(0);
    if (dialog.ShowModal() != wxID_OK) return;
    TextCtrlLogic->ChangeValue(CreateScript(nbName,dialog.CheckBoxRepeat->IsChecked(),dialog.CheckBoxFirstItem->IsChecked(),dialog.CheckBoxLastItem->IsChecked(),dialog.CheckBoxLightsOff->IsChecked()));
    TextCtrlLogic->Show();
    wxButton* ButtonRemoveScript=(wxButton*)FindNotebookControl(nbIdx,REMOVE_SCRIPT_BUTTON);
    ButtonRemoveScript->Show();
    UnsavedChanges=true;
}

void xScheduleFrame::OnButtonRemoveScriptClick(wxCommandEvent& event)
{
    int nbIdx=Notebook1->GetSelection();
    wxTextCtrl* TextCtrlLogic=(wxTextCtrl*)FindNotebookControl(nbIdx,PLAYLIST_LOGIC);
    wxButton* ButtonRemoveScript=(wxButton*)FindNotebookControl(nbIdx,REMOVE_SCRIPT_BUTTON);
    wxMessageDialog confirm(this, _("Are you sure you want to remove the script?\n\nScripts are useful for interactive displays, or when\nyou want your playlist to play back out of order.\nOtherwise, scripts are not necessary."), _("Confirm"), wxYES|wxNO);
    if (confirm.ShowModal() == wxID_YES) {
        TextCtrlLogic->Hide();
        ButtonRemoveScript->Hide();
        UnsavedChanges=true;
    }
}

void xScheduleFrame::OnClose(wxCloseEvent& event)
{
    if (UnsavedChanges) {
        wxMessageDialog confirm(this, _("Save changes?"), _("Confirm"), wxYES|wxNO);
        if (confirm.ShowModal() == wxID_YES) {
            SaveFile();
        }
    }
    StatusBar1->SetStatusText(_("Turning lights off"));
    xout->alloff();
    wxMilliSleep(XTIMER_INTERVAL * 2);
    StatusBar1->SetStatusText(_("Stopping schedtimer"));
    if (schedtimer.IsRunning()) schedtimer.Stop();
    StatusBar1->SetStatusText(_("Stopping main timer"));
    if (timer.IsRunning()) timer.Stop();
    StatusBar1->SetStatusText(_("Closing ports"));
    xout->ClosePorts();
    if (PlayerDlg) PlayerDlg->Destroy();
    if (xout) delete xout;
    this->Destroy();
}
