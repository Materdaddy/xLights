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
#include <wx/numdlg.h>

//(*InternalHeaders(xScheduleFrame)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/artprov.h>
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
#include "../include/vslider.xpm"



/* ****************************************************
 * Define the number of fixed notebook pages
 * 2 = 1 for calendar and 1 for log
 */

#define FixedPages 2

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
    if (id == _("xlights_test"))
        return wxBitmap(vslider_xpm);
    return wxNullBitmap;
};


/* ****************************************************
 * Extend the MiniBasic script class
 * with customized commands for xLights
 */

class xlbasic: public MiniBasicClass {

protected:

    xScheduleFrame* xsched;
    wxListCtrl* playlist;
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

    int do_exec(void) {
        char *execstr = stringexpr();
        if(!execstr) return 0;
        wxString wxexecstr(execstr,wxConvUTF8);
        wxExecute(wxexecstr);
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
        return playlist->GetItemCount();
    }

    // returns number of seconds remaining in scheduled play time
    double do_secondsremaining(void) {
        return xsched->SecondsRemaining;
    }

    // returns number of serial transmit overflows since count was last reset
    double do_txoverflowcnt(void) {
        return xsched->TxOverflowCnt;
    }

    int do_setplaylist(void) {
        char *pName = stringexpr();
        if(!pName) return 0;
        wxString name(pName,wxConvUTF8);
        int nbidx=xsched->FindNotebookPage(name);
        if (nbidx < FixedPages) return 0;
        playlist = (wxListCtrl*)xsched->FindNotebookControl(nbidx,xsched->PLAYLIST_LISTBOX);
        return EXEC_NEXTLINE;
    }

    char* do_itemname(void) {
        char *answer = 0;
        match(OPAREN);
        int idx = floor(expr());
        match(CPAREN);
        if(1 <= idx && idx <= playlist->GetItemCount()) {
            wxString n = playlist->GetItemText(idx-1);
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
        if(1 <= idx && idx <= playlist->GetItemCount()) {
            wxString n = playlist->GetItemText(idx-1);
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
        if(1 <= idx && idx <= playlist->GetItemCount()) {
            xsched->TxOverflowCnt = 0;
            wxString filename = playlist->GetItemText(idx-1);
            wxString delay = _("0"); //playlist->GetCellValue(idx-1,1);
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
        AddNumericFunction("TXOVERFLOWCNT", static_cast<NumericFuncPtr>(&xlbasic::do_txoverflowcnt));
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
        AddCommand("EXEC", static_cast<CommandPtr>(&xlbasic::do_exec));
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
        for (unsigned int i=0; i < SerialPorts.size(); i++) {
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
const long xScheduleFrame::ID_AUITOOLBARITEM_TEST = wxNewId();
const long xScheduleFrame::ID_AUITOOLBAR1 = wxNewId();
const long xScheduleFrame::ID_PANEL2 = wxNewId();
const long xScheduleFrame::ID_TREECTRL1 = wxNewId();
const long xScheduleFrame::ID_CHECKBOX_RUN_SCHEDULE = wxNewId();
const long xScheduleFrame::ID_BUTTON_ADD_SHOW = wxNewId();
const long xScheduleFrame::ID_BITMAPBUTTON_SCHED_INFO = wxNewId();
const long xScheduleFrame::ID_BUTTON2 = wxNewId();
const long xScheduleFrame::ID_BUTTON_DELETE_SHOW = wxNewId();
const long xScheduleFrame::ID_BUTTON_DESELECT = wxNewId();
const long xScheduleFrame::ID_STATICTEXT2 = wxNewId();
const long xScheduleFrame::ID_BUTTON_SHOW_DATES_CHANGE = wxNewId();
const long xScheduleFrame::ID_STATICTEXT3 = wxNewId();
const long xScheduleFrame::ID_STATICTEXT4 = wxNewId();
const long xScheduleFrame::ID_STATICTEXT5 = wxNewId();
const long xScheduleFrame::ID_STATICTEXT6 = wxNewId();
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
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer8;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxMenuItem* MenuItemDelList;
    wxMenu* MenuFile;
    wxMenuItem* MenuItemAddList;
    wxFlexGridSizer* FlexGridSizer7;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer6;
    wxMenuItem* MenuItem3;
    wxFlexGridSizer* FlexGridSizer3;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem4;
    wxMenuItem* MenuItemCustomScript;
    wxMenu* MenuPlaylist;
    wxFlexGridSizer* FlexGridSizer5;
    wxMenu* MenuHelp;
    wxMenuItem* MenuItemRenameList;

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
    AuiToolBar1->EnableTool(ID_AUITOOLBARITEM_PLAY, false);
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM_TEST, _("Test Lights"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("xlights_test")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Test Lights"), wxEmptyString, NULL);
    AuiToolBar1->EnableTool(ID_AUITOOLBARITEM_TEST, false);
    AuiToolBar1->Realize();
    AuiManager1->AddPane(AuiToolBar1, wxAuiPaneInfo().Name(_T("PaneName")).ToolbarPane().Caption(_("Pane caption")).Layer(10).Top().Gripper());
    AuiManager1->Update();
    FlexGridSizer2->Add(Panel2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Notebook1 = new wxNotebook(Panel1, ID_NOTEBOOK1, wxDefaultPosition, wxSize(1057,350), 0, _T("ID_NOTEBOOK1"));
    PanelCal = new wxPanel(Notebook1, ID_PANEL_CAL, wxPoint(49,10), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_CAL"));
    FlexGridSizer8 = new wxFlexGridSizer(1, 2, 0, 0);
    FlexGridSizer8->AddGrowableCol(0);
    FlexGridSizer8->AddGrowableRow(0);
    ListBoxSched = new wxTreeCtrl(PanelCal, ID_TREECTRL1, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS|wxTR_NO_LINES|wxTR_HIDE_ROOT|wxTR_MULTIPLE|wxTR_EXTENDED|wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
    FlexGridSizer8->Add(ListBoxSched, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
    CheckBoxRunSchedule = new wxCheckBox(PanelCal, ID_CHECKBOX_RUN_SCHEDULE, _("Run Schedule"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RUN_SCHEDULE"));
    CheckBoxRunSchedule->SetValue(false);
    wxFont CheckBoxRunScheduleFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    CheckBoxRunSchedule->SetFont(CheckBoxRunScheduleFont);
    FlexGridSizer4->Add(CheckBoxRunSchedule, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6 = new wxFlexGridSizer(0, 3, 0, 0);
    ButtonAddShow = new wxButton(PanelCal, ID_BUTTON_ADD_SHOW, _("Schedule Playlist"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ADD_SHOW"));
    FlexGridSizer6->Add(ButtonAddShow, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButtonSchedInfo = new wxBitmapButton(PanelCal, ID_BITMAPBUTTON_SCHED_INFO, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_INFORMATION")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxRAISED_BORDER, wxDefaultValidator, _T("ID_BITMAPBUTTON_SCHED_INFO"));
    BitmapButtonSchedInfo->SetToolTip(_("Tips for using scheduler"));
    FlexGridSizer6->Add(BitmapButtonSchedInfo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(FlexGridSizer6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    ButtonUpdateShow = new wxButton(PanelCal, ID_BUTTON2, _("Update Selected Items"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer4->Add(ButtonUpdateShow, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ButtonDeleteShow = new wxButton(PanelCal, ID_BUTTON_DELETE_SHOW, _("Delete Selected Items"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_DELETE_SHOW"));
    FlexGridSizer4->Add(ButtonDeleteShow, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ButtonDeselect = new wxButton(PanelCal, ID_BUTTON_DESELECT, _("Deselect All"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_DESELECT"));
    FlexGridSizer4->Add(ButtonDeselect, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer7 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText2 = new wxStaticText(PanelCal, ID_STATICTEXT2, _("Show Dates"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    wxFont StaticText2Font(wxDEFAULT,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    FlexGridSizer7->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonShowDatesChange = new wxButton(PanelCal, ID_BUTTON_SHOW_DATES_CHANGE, _("Change"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SHOW_DATES_CHANGE"));
    FlexGridSizer7->Add(ButtonShowDatesChange, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(PanelCal, ID_STATICTEXT3, _("Start"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer7->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextShowStart = new wxStaticText(PanelCal, ID_STATICTEXT4, _("xx/xx/xxxx"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer7->Add(StaticTextShowStart, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(PanelCal, ID_STATICTEXT5, _("End"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer7->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextShowEnd = new wxStaticText(PanelCal, ID_STATICTEXT6, _("xx/xx/xxxx"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    FlexGridSizer7->Add(StaticTextShowEnd, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(FlexGridSizer7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
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
    Connect(ID_AUITOOLBARITEM_TEST,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnAuiToolBarItemTestClick);
    Connect(ID_CHECKBOX_RUN_SCHEDULE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnCheckBoxRunScheduleClick);
    Connect(ID_BUTTON_ADD_SHOW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonAddShowClick);
    Connect(ID_BITMAPBUTTON_SCHED_INFO,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnBitmapButtonSchedInfoClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonUpdateShowClick);
    Connect(ID_BUTTON_DELETE_SHOW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonDeleteShowClick);
    Connect(ID_BUTTON_DESELECT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonDeselectClick);
    Connect(ID_BUTTON_SHOW_DATES_CHANGE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xScheduleFrame::OnButtonShowDatesChangeClick);
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
    xout = new xOutput();
    UpdateShowDates(wxDateTime::Now(),wxDateTime::Now());

    // Get CurrentDir
    wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));
    if ( !config->Read(_("LastDir"), &CurrentDir) ) {
        wxMessageBox(_("No directory specified"), _("Error"));
        Close();
    }

    // Check if schedule should be running
    long RunFlag=0;
    config->Read(_("RunSchedule"), &RunFlag);

    // Load files
    pTestDialog = 0;
    PortsOK=true;
    networkFile.AssignDir( CurrentDir );
    networkFile.SetFullName(_(XLIGHTS_NETWORK_FILE));
    if (networkFile.FileExists()) {
        pTestDialog = new TestDialog(this);
        pTestDialog->SetCurrentDir( CurrentDir );
        LoadNetworkFile();
    }
    ResetTimer(NO_SEQ);
    if (PortsOK) {
        timer.Start(XTIMER_INTERVAL, wxTIMER_CONTINUOUS);
        schedtimer.Start(1000, wxTIMER_CONTINUOUS);
        AuiToolBar1->EnableTool(ID_AUITOOLBARITEM_TEST, true);
        AuiToolBar1->Realize();
    } else {
        //schedtimer.Start(1000, wxTIMER_CONTINUOUS);
    }
    scheduleFile.AssignDir( CurrentDir );
    scheduleFile.SetFullName(_(XLIGHTS_SCHEDULE_FILE));
    UnsavedChanges=false;
    if (scheduleFile.FileExists()) {
        LoadScheduleFile();
    }

    basic.setFrame(this);
    build_decoding_table();
    DisplaySchedule();
    Notebook1->ChangeSelection(0);
    if (RunFlag && PortsOK && !ShowEvents.IsEmpty()) {
        CheckBoxRunSchedule->SetValue(true);
        CheckRunSchedule();
    }
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
    //wxBoxSizer* BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer* BoxSizer4 = new wxFlexGridSizer(0, 6, 0, 0);
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

    id=baseid+CHKBOX_XLIGHTS;
    wxCheckBox* CheckBoxXlights = new wxCheckBox(PanelPlayList, id, _("xLights"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_XLIGHTS"));
    CheckBoxXlights->SetValue(false);
    BoxSizer4->Add(CheckBoxXlights, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnFileTypeButtonClicked);

    FlexGridSizer4->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(0,0,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    wxFlexGridSizer* FlexGridSizer5 = new wxFlexGridSizer(0, 6, 0, 0);

    id=baseid+CHKBOX_MOVIEMODE;
    wxCheckBox* CheckBoxMovieMode = new wxCheckBox(PanelPlayList, id, _("Movie Mode"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_MOVIEMODE"));
    CheckBoxMovieMode->SetValue(false);
    CheckBoxMovieMode->SetToolTip(_("When a playlist is played in movie mode, a full screen player window is opened to display the associated video."));
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

    id=baseid+DELAY_BUTTON;
    wxButton* ButtonDelay = new wxButton(PanelPlayList, id, _("Set delay"));
    ButtonDelay->SetToolTip(_("Sets the amount of delay after item is played"));
    FlexGridSizer5->Add(ButtonDelay, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonSetDelayClick);

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
    Button2->SetMinSize(wxSize(35,20));
    Button2->SetToolTip(_("Add selected file"));
    BoxSizer5->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonPlaylistAddClick);

    id=baseid+PLAYLIST_ADD_ALL;
    wxButton* Button3 = new wxButton(PanelPlayList, id, _(">>"));
    Button3->SetMinSize(wxSize(35,20));
    Button3->SetToolTip(_("Add all files"));
    BoxSizer5->Add(Button3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonPlaylistAddAllClick);

    id=baseid+PLAYLIST_DELETE;
    wxButton* Button4 = new wxButton(PanelPlayList, id, _("<"));
    Button4->SetMinSize(wxSize(35,20));
    Button4->SetToolTip(_("Delete selected item"));
    BoxSizer5->Add(Button4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonPlaylistDeleteClick);

    id=baseid+PLAYLIST_DELETE_ALL;
    wxButton* Button5 = new wxButton(PanelPlayList, id, _("<<"));
    Button5->SetMinSize(wxSize(35,20));
    Button5->SetToolTip(_("Delete all items"));
    BoxSizer5->Add(Button5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&xScheduleFrame::OnButtonPlaylistDeleteAllClick);

    FlexGridSizer4->Add(BoxSizer5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+PLAYLIST_LISTBOX;
    wxListCtrl* ListBox1 = new wxListCtrl(PanelPlayList, id, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);

    ListBox1->SetToolTip(_("Drag an item to reorder the list"));
    Connect(id, wxEVT_COMMAND_LIST_BEGIN_DRAG, (wxObjectEventFunction)&xScheduleFrame::OnPlayListBeginDrag);
    FlexGridSizer4->Add(ListBox1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    id=baseid+PLAYLIST_LOGIC;
    wxTextCtrl* TextCtrlLogic = new wxTextCtrl(PanelPlayList, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_LOGIC"));
    FlexGridSizer4->Add(TextCtrlLogic, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlLogic->Hide();

    PanelPlayList->SetSizer(FlexGridSizer4);
    FlexGridSizer4->Fit(PanelPlayList);
    FlexGridSizer4->SetSizeHints(PanelPlayList);
    Notebook1->AddPage(PanelPlayList, name, true);

    // set playlist columns
    wxListItem itemCol;
    itemCol.SetText(_T("Filename"));
    itemCol.SetImage(-1);
    ListBox1->InsertColumn(0, itemCol);
    itemCol.SetText(_T("Delay (s)"));
    itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
    ListBox1->InsertColumn(1, itemCol);
    ListBox1->SetColumnWidth(0,100);
    ListBox1->SetColumnWidth(1,100);
}

void xScheduleFrame::OnButtonPlaylistAddClick() {
    int nbidx=Notebook1->GetSelection();
    int baseid=1000*nbidx;
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxTreeCtrl* TreeCtrlFiles=(wxTreeCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_FILES,Notebook1);
    wxTreeItemId root=TreeCtrlFiles->GetRootItem();
    wxTreeItemId selid=TreeCtrlFiles->GetSelection();
    if (!selid.IsOk()) return;
    wxString selstr = TreeCtrlFiles->GetItemText(selid);
    long newidx = ListBoxPlay->InsertItem(ListBoxPlay->GetItemCount(), selstr);
    ListBoxPlay->SetItem(newidx,1,wxT("0"));
    ListBoxPlay->SetColumnWidth(0,wxLIST_AUTOSIZE);
    UnsavedChanges=true;
    ScanForFiles();
}

void xScheduleFrame::OnButtonPlaylistAddAllClick() {
    int nbidx=Notebook1->GetSelection();
    int baseid=1000*nbidx;
    int cnt=0;
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxTreeCtrl* TreeCtrlFiles=(wxTreeCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_FILES,Notebook1);
    wxTreeItemId root=TreeCtrlFiles->GetRootItem();
    wxTreeItemId item=TreeCtrlFiles->GetFirstVisibleItem();
    while (item.IsOk()) {
        if (item != root) {
            long newidx = ListBoxPlay->InsertItem(ListBoxPlay->GetItemCount(), TreeCtrlFiles->GetItemText(item));
            ListBoxPlay->SetItem(newidx,1,wxT("0"));
            UnsavedChanges=true;
            cnt++;
        }
        item=TreeCtrlFiles->GetNextVisible(item);
    }
    if (cnt > 0) ListBoxPlay->SetColumnWidth(0,wxLIST_AUTOSIZE);
    ScanForFiles();
}

void xScheduleFrame::OnButtonPlaylistDeleteClick() {
    int nbidx=Notebook1->GetSelection();
    int baseid=1000*nbidx;
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    long SelectedItem = GetSelectedItem(ListBoxPlay);
    if (SelectedItem == -1) {
        wxMessageBox(_("Please select a single row in the playlist first"), _("Error"));
        return;
    }
    ListBoxPlay->DeleteItem(SelectedItem);
    ListBoxPlay->SetColumnWidth(0, ListBoxPlay->GetItemCount() > 0 ? wxLIST_AUTOSIZE : wxLIST_AUTOSIZE_USEHEADER);
    UnsavedChanges=true;
    ScanForFiles();
}

void xScheduleFrame::OnButtonPlaylistDeleteAllClick() {
    int nbidx=Notebook1->GetSelection();
    int baseid=1000*nbidx;
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    if (ListBoxPlay->GetItemCount() > 0) {
        ListBoxPlay->DeleteAllItems();
        ListBoxPlay->SetColumnWidth(0,wxLIST_AUTOSIZE_USEHEADER);
        UnsavedChanges=true;
    }
    ScanForFiles();
}

xScheduleFrame::~xScheduleFrame()
{
    //(*Destroy(xScheduleFrame)
    //*)
    if (AuiManager1) AuiManager1->UnInit();
    if (pTestDialog) delete pTestDialog;
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
    if (newstate == NO_SEQ) PlayMode=NO_PLAY;
    AuiToolBar1->EnableTool(ID_AUITOOLBARITEM_PLAY, newstate == NO_SEQ && PortsOK);
    AuiToolBar1->Realize();
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
    LastMoDay.Empty();
}

void xScheduleFrame::OnSchedTimer(wxTimerEvent& event)
{
    wxString StartTime, EndTime, userscript;
    int i,cnt;
    bool CheckSchedule = false;
    wxTextCtrl* LogicCtl;

    static wxString RepeatOptions, Playlist, strStartTime, strEndTime, StartMoDay;
    static wxDateTime LastTime = wxDateTime::Now();  // last time this method was called
    static long StartTimeSec;
    static wxArrayString AlreadyPlayed;
    static bool MoreShowsToday = true;

    if (!CheckBoxRunSchedule->IsChecked() || PlayMode==PLAYLIST) return;
    wxDateTime n=wxDateTime::Now();
    long SecPastMidnight=n.GetHour()*60*60 + n.GetMinute()*60 + n.GetSecond();
    wxString CurrentMoDay = n.Format(wxT("%m%d"));
    //StatusBar1->SetStatusText(_("OnSchedTimer: ") + n.FormatISOTime());

    if (basic.IsRunning()) {

        // playlist is running - check for the schedule end

        if (CurrentMoDay != StartMoDay) SecPastMidnight+=24*60*60;
        SecondsRemaining=EndTimeSec - SecPastMidnight;
        int minutes=(SecondsRemaining + 59) / 60;  // round up
        if (minutes > 60) {
            StatusBar1->SetStatusText(_("Show will end at: ") + strEndTime, 1);
        } else if (minutes > 1) {
            StatusBar1->SetStatusText(wxString::Format(_("Show will end in %d minutes"),minutes), 1);
        } else if (SecondsRemaining > 0) {
            StatusBar1->SetStatusText(wxString::Format(_("Show will end in about %ld seconds"),SecondsRemaining), 1);
        } else {
            StatusBar1->SetStatusText(_("Finishing playlist: ") + Playlist, 1);
        }

    } else {

        // no playlist running - wait for next event

        // should we check ShowEvents[]?
        if (LastMoDay != CurrentMoDay) {
            // either the Run Schedule button was just pressed, or we just passed midnight
            CheckSchedule = true;
            LastMoDay = CurrentMoDay;
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
            for (i=0; i < cnt; i++) {
                if (ShowEvents[i].StartsWith(CurrentMoDay)) break;
            }
            if (i >= cnt) {
                StatusBar1->SetStatusText(_("No show scheduled for today"), 1);
                return;
            }
            do {
                UnpackSchedCode(ShowEvents[i], StartTime, EndTime, RepeatOptions, Playlist);
                StartTimeSec=Time2Seconds(StartTime);
                EndTimeSec=Time2Seconds(EndTime);
                if (SecPastMidnight < EndTimeSec && AlreadyPlayed.Index(ShowEvents[i]) == wxNOT_FOUND) {
                    MoreShowsToday = true;
                    strStartTime = StartTime.Left(2) + wxT(":") + StartTime.Right(2);
                    strEndTime = EndTime.Left(2) + wxT(":") + EndTime.Right(2);
                    break;
                }
                i++;
            } while (i < cnt && ShowEvents[i].StartsWith(CurrentMoDay));
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
                    LogicCtl=(wxTextCtrl*)FindNotebookControl(nbidx,PLAYLIST_LOGIC);
                    if (LogicCtl && LogicCtl->IsShown()) {
                        // run custom script
                        userscript=LogicCtl->GetValue();
                    } else {
                        // this is a playlist page, run generic script
                        userscript=CreateScript(Notebook1->GetPageText(nbidx),RepeatOptions[0]=='R',RepeatOptions[1]=='F',RepeatOptions[2]=='L',false,RepeatOptions[3]=='X');
                    }
                    StartMoDay=CurrentMoDay;
                    AlreadyPlayed.Add(ShowEvents[i]);
                    RunPlaylist(nbidx,userscript);
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
    for (size_t i=FixedPages; i < Notebook1->GetPageCount(); i++) {
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
    if (pTestDialog->IsShown()) {
        PerformTesting();
    } else {
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
                if (VixNumChannels > VixNetwork2.size()) VixNumChannels=VixNetwork2.size();
                LastIntensity.resize(VixNumChannels,1);
                ResetTimer(PLAYING_VIX_ANIM);
                break;
            case PLAYING_LOR_ANIM:
                if (LorIter == LorEvents.end()) {
                    ResetTimer(basic.IsRunning() ? DELAY_AFTER_PLAY : NO_SEQ);
                    return;
                }
                if (!xout->TxEmpty()) {
                    TxOverflowCnt++;
                    break;
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
                            default:
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
                            default:
                                break;
                        }
                    }

                    LorIter++;
                }
                xout->TimerEnd();
                break;
            case PLAYING_VIX_ANIM:
                if (!xout->TxEmpty()) {
                    TxOverflowCnt++;
                    break;
                }
                ts = wxDateTime::UNow() - starttime;
                msec = ts.GetMilliseconds().ToLong();
                period = msec / VixEventPeriod;
                if (period < VixNumPeriods) {
                    xout->TimerStart(msec);
                    for (chindex=0; chindex<VixNumChannels; chindex++) {
                        vixintensity=VixEventData[chindex*VixNumPeriods+period];
                        if (vixintensity != LastIntensity[chindex]) {
                            xout->SetIntensity(VixNetwork2[chindex].first, VixNetwork2[chindex].second, vixintensity);
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
                    if (VixNumChannels > VixNetwork2.size()) VixNumChannels=VixNetwork2.size();
                    LastIntensity.resize(VixNumChannels,1);
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
                if (!xout->TxEmpty()) {
                    TxOverflowCnt++;
                    break;
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
                            default:
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
                            default:
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
                if (!xout->TxEmpty()) {
                    TxOverflowCnt++;
                    break;
                }
                msec = PlayerDlg->MediaCtrl->Tell();
                period = msec / VixEventPeriod;
                xout->TimerStart(msec);
                if (period < VixNumPeriods) {
                    for (chindex=0; chindex<VixNumChannels; chindex++) {
                        vixintensity=VixEventData[chindex*VixNumPeriods+period];
                        if (vixintensity != LastIntensity[chindex]) {
                            xout->SetIntensity(VixNetwork2[chindex].first, VixNetwork2[chindex].second, vixintensity);
                            LastIntensity[chindex]=vixintensity;
                        }
                    }
                }
                xout->TimerEnd();
                break;
            case PAUSE_VIX:
                if (PlayerDlg->MediaCtrl->GetState() == wxMEDIASTATE_PLAYING) {
                    if (VixNumChannels > VixNetwork2.size()) VixNumChannels=VixNetwork2.size();
                    LastIntensity.resize(VixNumChannels,1);
                    ResetTimer(PLAYING_VIX);
                } else {
                    TimerNoPlay();
                }
                break;
            default:
                TimerNoPlay();
                break;
        }
    }
    lastmsec=msec;
    basic.SerialCallback();
}

// called on each Timer tick while Test dialog is open
void xScheduleFrame::PerformTesting()
{
    static int LastNotebookSelection = -1;
    static int LastBgIntensity,LastFgIntensity,LastBgColor[3],LastFgColor[3],*ShimColor,ShimIntensity;
    static int LastSequenceSpeed;
    static int LastAutomatedTest;
    static long NextSequenceStart = -1;
    static TestDialog::TestFunctions LastFunc = TestDialog::OFF;
    static unsigned int interval, rgbCycle, seqidx;
    static wxArrayInt chArray,TwinkleState;
    static float frequency;
    int v,BgIntensity,FgIntensity,BgColor[3],FgColor[3];
    unsigned int i;
    bool ColorChange;

    int netidx = pTestDialog->GetNetIdx();
    wxTimeSpan ts = wxDateTime::UNow() - starttime;
    long curtime = ts.GetMilliseconds().ToLong();
    xout->TimerStart(curtime);
    int NotebookSelection = pTestDialog->GetTestIdx();
    if (NotebookSelection != LastNotebookSelection) {
        LastNotebookSelection = NotebookSelection;
        pTestDialog->CheckChannelList = true;
        seqidx=0;
        pTestDialog->RadioButtonsOff();
    }
    if (pTestDialog->TestFunc != LastFunc) {
        LastFunc = pTestDialog->TestFunc;
        rgbCycle=0;
        pTestDialog->CheckChannelList = true;
    }

    if (pTestDialog->CheckChannelList) {
        // get list of checked channels
        xout->alloff();
        pTestDialog->GetCheckedItems(netidx, chArray);
        LastSequenceSpeed=-1;
        LastBgIntensity=-1;
        LastFgIntensity=-1;
        LastAutomatedTest=-1;
        for (i=0; i < 3; i++) {
            LastBgColor[i] = -1;
            LastFgColor[i] = -1;
        }
        if (pTestDialog->TestFunc == TestDialog::OFF) {
            StatusBar1->SetStatusText(_("All lights off"));
        } else {
            StatusBar1->SetStatusText(wxString::Format(_("Testing %ld channels"),static_cast<long>(chArray.Count())));
        }
        pTestDialog->CheckChannelList = false;
    }

    if (pTestDialog->TestFunc != TestDialog::OFF && chArray.Count() > 0) switch (NotebookSelection) {
        case 0:
            // standard tests
            v=pTestDialog->ChaseSpeed();  // 0-100
            BgIntensity = pTestDialog->BgIntensity();
            FgIntensity = pTestDialog->FgIntensity();
            ColorChange = BgIntensity != LastBgIntensity || FgIntensity != LastFgIntensity;
            LastBgIntensity = BgIntensity;
            LastFgIntensity = FgIntensity;
            interval = 1600 - v*15;

            switch (pTestDialog->TestFunc) {
                case TestDialog::DIM:
                    if (ColorChange) {
                        for (i=0; i < chArray.Count(); i++) {
                            xout->SetIntensity(netidx, chArray[i], BgIntensity);
                        }
                    }
                    break;

                case TestDialog::TWINKLE:
                    if (LastSequenceSpeed < 0) {
                        LastSequenceSpeed=0;
                        TwinkleState.Clear();
                        for (i=0; i < chArray.Count(); i++) {
                            seqidx = static_cast<int>(rand01()*pTestDialog->TwinkleRatio);
                            TwinkleState.Add(seqidx == 0 ? -1 : 1);
                        }
                    }
                    for (i=0; i < TwinkleState.Count(); i++) {
                        if (TwinkleState[i] < -1) {
                            // background
                            TwinkleState[i]++;
                        } else if (TwinkleState[i] > 1) {
                            // highlight
                            TwinkleState[i]--;
                        } else if (TwinkleState[i] == -1) {
                            // was background, now highlight for random period
                            TwinkleState[i]=static_cast<int>(rand01()*interval+100) / XTIMER_INTERVAL;
                            xout->SetIntensity(netidx, chArray[i], FgIntensity);
                        } else {
                            // was on, now go to bg color for random period
                            TwinkleState[i]=-static_cast<int>(rand01()*interval+100) / XTIMER_INTERVAL * (pTestDialog->TwinkleRatio - 1);
                            xout->SetIntensity(netidx, chArray[i], BgIntensity);
                        }
                    }
                    break;

                case TestDialog::SHIMMER:
                    if (ColorChange || curtime >= NextSequenceStart) {
                        ShimIntensity = (ShimIntensity == FgIntensity) ? BgIntensity : FgIntensity;
                        for (i=0; i < chArray.Count(); i++) {
                            xout->SetIntensity(netidx, chArray[i], ShimIntensity);
                        }
                    }
                    if (curtime >= NextSequenceStart) {
                        NextSequenceStart = curtime + interval/2;
                    }
                    break;

                case TestDialog::CHASE:
                    if (ColorChange || curtime >= NextSequenceStart) {
                        for (i=0; i < chArray.Count(); i++) {
                            v = (i % pTestDialog->ChaseGrouping) == seqidx ? FgIntensity : BgIntensity;
                            xout->SetIntensity(netidx, chArray[i], v);
                        }
                    }
                    if (curtime >= NextSequenceStart) {
                        NextSequenceStart = curtime + interval;
                        seqidx = (seqidx + 1) % pTestDialog->ChaseGrouping;
                        if (seqidx >= chArray.Count()) seqidx=0;
                    }
                    break;
                default: break;
            }
            break;

        case 1:
            // RGB tests
            v=pTestDialog->RgbChaseSpeed();  // 0-100
            BgColor[0] = pTestDialog->BgColorA();
            BgColor[1] = pTestDialog->BgColorB();
            BgColor[2] = pTestDialog->BgColorC();
            FgColor[0] = pTestDialog->FgColorA();
            FgColor[1] = pTestDialog->FgColorB();
            FgColor[2] = pTestDialog->FgColorC();

            interval = 1600 - v*15;
            for (ColorChange=false,i=0; i < 3; i++) {
                ColorChange |= (BgColor[i] != LastBgColor[i]);
                ColorChange |= (FgColor[i] != LastFgColor[i]);
                LastBgColor[i] = BgColor[i];
                LastFgColor[i] = FgColor[i];
            }
            switch (pTestDialog->TestFunc) {
                case TestDialog::DIM:
                    if (ColorChange) {
                        for (i=0; i < chArray.Count(); i++) {
                            xout->SetIntensity(netidx, chArray[i], BgColor[i % 3]);
                        }
                    }
                    break;

                case TestDialog::TWINKLE:
                    if (LastSequenceSpeed < 0) {
                        LastSequenceSpeed=0;
                        TwinkleState.Clear();
                        for (i=0; i < chArray.Count(); i+=3) {
                            seqidx = static_cast<int>(rand01()*pTestDialog->TwinkleRatio);
                            TwinkleState.Add(seqidx == 0 ? -1 : 1);
                        }
                    }
                    for (i=0; i < TwinkleState.Count(); i++) {
                        if (TwinkleState[i] < -1) {
                            // background
                            TwinkleState[i]++;
                        } else if (TwinkleState[i] > 1) {
                            // highlight
                            TwinkleState[i]--;
                        } else if (TwinkleState[i] == -1) {
                            // was background, now highlight for random period
                            TwinkleState[i]=static_cast<int>(rand01()*interval+100) / XTIMER_INTERVAL;
                            seqidx = i * 3;
                            xout->SetIntensity(netidx, chArray[seqidx], FgColor[0]);
                            xout->SetIntensity(netidx, chArray[seqidx+1], FgColor[1]);
                            xout->SetIntensity(netidx, chArray[seqidx+2], FgColor[2]);
                        } else {
                            // was on, now go to bg color for random period
                            TwinkleState[i]=-static_cast<int>(rand01()*interval+100) / XTIMER_INTERVAL * (pTestDialog->TwinkleRatio - 1);
                            seqidx = i * 3;
                            xout->SetIntensity(netidx, chArray[seqidx], BgColor[0]);
                            xout->SetIntensity(netidx, chArray[seqidx+1], BgColor[1]);
                            xout->SetIntensity(netidx, chArray[seqidx+2], BgColor[2]);
                        }
                    }
                    break;
                case TestDialog::SHIMMER:
                    if (ColorChange || curtime >= NextSequenceStart) {
                        ShimColor = (ShimColor == FgColor) ? BgColor : FgColor;
                        for (i=0; i < chArray.Count(); i++) {
                            xout->SetIntensity(netidx, chArray[i], ShimColor[i % 3]);
                        }
                    }
                    if (curtime >= NextSequenceStart) {
                        NextSequenceStart = curtime + interval/2;
                    }
                    break;
                case TestDialog::CHASE:
                    if (ColorChange || curtime >= NextSequenceStart) {
                        for (i=0; i < chArray.Count(); i++) {
                            v = (i / 3 % pTestDialog->ChaseGrouping) == seqidx ? FgColor[i % 3] : BgColor[i % 3];
                            xout->SetIntensity(netidx, chArray[i], v);
                        }
                    }
                    if (curtime >= NextSequenceStart) {
                        NextSequenceStart = curtime + interval;
                        seqidx = (seqidx + 1) % pTestDialog->ChaseGrouping;
                        if (seqidx >= (chArray.Count()+2) / 3) seqidx=0;
                    }
                    break;
                default: break;
            }
            break;

        case 2:
            // RGB Cycle
            v=pTestDialog->RgbCycleSpeed();  // 0-100
            if (pTestDialog->TestFunc == TestDialog::DIM) {
                // color mixing
                if (v != LastSequenceSpeed) {
                    frequency=v/1000.0 + 0.05;
                    LastSequenceSpeed = v;
                }
                BgColor[0] = sin(frequency*seqidx + 0.0) * 127 + 128;
                BgColor[1] = sin(frequency*seqidx + 2.0) * 127 + 128;
                BgColor[2] = sin(frequency*seqidx + 4.0) * 127 + 128;
                seqidx++;
                for (i=0; i < chArray.Count(); i++) {
                    xout->SetIntensity(netidx, chArray[i], BgColor[i % 3]);
                }
            } else {
                // RGB cycle
                if (v != LastSequenceSpeed) {
                    interval = (101-v)*50;
                    NextSequenceStart = curtime + interval;
                    LastSequenceSpeed = v;
                }
                if (curtime >= NextSequenceStart) {
                    for (i=0; i < chArray.Count(); i++) {
                        switch (rgbCycle) {
                            case 3: v=255; break;
                            default: v = (i % 3) == rgbCycle ? 255 : 0; break;
                        }
                        xout->SetIntensity(netidx, chArray[i], v);
                    }
                    rgbCycle=(rgbCycle + 1) % pTestDialog->ChaseGrouping;
                    NextSequenceStart += interval;
                }
            }
            break;

        case 3:
            // automated test
            /*
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
                        xout->SetIntensity(netidx, chArray[i], MAXINTENSITY);
                    }
                    break;
                case 1:
                    // intensity 50%
                    for (i=0; i < chArray.Count(); i++) {
                        xout->SetIntensity(netidx, chArray[i], MAXINTENSITY/2);
                    }
                    break;
                case 2:
                    // twinkle 100%
                    for (i=0; i < chArray.Count(); i++) {
                        xout->twinkle(netidx, chArray[i], TWINKLE_PERIOD, MAXINTENSITY);
                    }
                    break;
                case 3:
                    // twinkle 50%
                    for (i=0; i < chArray.Count(); i++) {
                        xout->twinkle(netidx, chArray[i], TWINKLE_PERIOD, MAXINTENSITY/2);
                    }
                    break;
                case 4:
                    // shimmer 100%
                    for (i=0; i < chArray.Count(); i++) {
                        xout->shimmer(netidx, chArray[i], SHIMMER_PERIOD, MAXINTENSITY);
                    }
                    break;
                case 5:
                    // shimmer 50%
                    for (i=0; i < chArray.Count(); i++) {
                        xout->shimmer(netidx, chArray[i], SHIMMER_PERIOD, MAXINTENSITY/2);
                    }
                    break;
                case 6:
                    // ramp 0% to 100%
                    for (i=0; i < chArray.Count(); i++) {
                        xout->ramp(netidx, chArray[i], interval, 0, MAXINTENSITY);
                    }
                    break;
                case 7:
                    // ramp 100% to 0%
                    for (i=0; i < chArray.Count(); i++) {
                        xout->ramp(netidx, chArray[i], interval, MAXINTENSITY, 0);
                    }
                    break;
                case 8:
                    // twinkle ramp 0% to 100%
                    for (i=0; i < chArray.Count(); i++) {
                        xout->twinklefade(netidx, chArray[i], TWINKLE_PERIOD, interval, 0, MAXINTENSITY);
                    }
                    break;
                case 9:
                    // twinkle ramp 100% to 0%
                    for (i=0; i < chArray.Count(); i++) {
                        xout->twinklefade(netidx, chArray[i], TWINKLE_PERIOD, interval, MAXINTENSITY, 0);
                    }
                    break;
                case 10:
                    // shimmer ramp 0% to 100%
                    for (i=0; i < chArray.Count(); i++) {
                        xout->shimmerfade(netidx, chArray[i], SHIMMER_PERIOD, interval, 0, MAXINTENSITY);
                    }
                    break;
                case 11:
                    // shimmer ramp 100% to 0%
                    for (i=0; i < chArray.Count(); i++) {
                        xout->shimmerfade(netidx, chArray[i], SHIMMER_PERIOD, interval, MAXINTENSITY, 0);
                    }
                    break;
            }
            */
            break;
    }
    xout->TimerEnd();
    //wxLogTrace(wxT("xout"),wxT("Ending OnTimer"));
    //StatusBar1->SetStatusText(ts.Format(_("%S.%l")));
}

// return a random number between 0 and 1 inclusive
double xScheduleFrame::rand01()
{
    return (double)rand()/(double)RAND_MAX;
}

void xScheduleFrame::LoadNetworkFile()
{
    long MaxChan;
    wxString tempstr;
    wxXmlDocument doc;
    if (doc.Load( networkFile.GetFullPath() )) {
        wxXmlNode* e=doc.GetRoot();
        tempstr=e->GetAttribute(wxT("LorMapping"), wxT("2"));
        tempstr.ToLong(&LorMapping);
        for( e=doc.GetRoot()->GetChildren(); e!=NULL; e=e->GetNext() ) {
            wxString tagname=e->GetName();
            if (tagname == wxT("network")) {
                wxString tempstr=e->GetAttribute(wxT("MaxChannels"), wxT("0"));
                tempstr.ToLong(&MaxChan);
                wxString NetworkType=e->GetAttribute(wxT("NetworkType"), wxT(""));
                wxString ComPort=e->GetAttribute(wxT("ComPort"), wxT(""));
                wxString BaudRate=e->GetAttribute(wxT("BaudRate"), wxT(""));
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

    if (pTestDialog) pTestDialog->AddNetwork(NetworkType,ComPort,BaudRate,PortsOK ? MaxChannels : 0);
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
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxCheckBox* CheckBoxAudio=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_AUDIO,Notebook1);
    wxCheckBox* CheckBoxVideo=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_VIDEO,Notebook1);
    wxCheckBox* CheckBoxLOR=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_LOR,Notebook1);
    wxCheckBox* CheckBoxVixen=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_VIXEN,Notebook1);
    wxCheckBox* CheckBoxXlights=(wxCheckBox*)wxWindow::FindWindowById(baseid+CHKBOX_XLIGHTS,Notebook1);

    wxFileName oName;
    oName.AssignDir( CurrentDir );

    // if file was deleted, remove matching entry
    int cnt=ListBoxPlay->GetItemCount();
    for (i=0; i<cnt; i++) {
        filenames.Add(ListBoxPlay->GetItemText(i));
    }
    for (i=filenames.GetCount()-1; i >= 0; i--) {
        oName.SetFullName(filenames[i]);
        if (!oName.FileExists()) {
            ListBoxPlay->DeleteItem(i);
            UnsavedChanges=true;
            wxMessageBox(_("File ") + filenames[i] + _(" was deleted from the show directory\n\nRemoving it from playlist ") + PageName, _("Playlist Updated"));
        }
    }

    // scan directory for matches
    TreeCtrlFiles->DeleteAllItems();
    wxTreeItemId root=TreeCtrlFiles->AddRoot(_("Show Directory"));
    wxDir dir(CurrentDir);
    bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
    while ( cont ) {
        if (filenames.Index(filename) == wxNOT_FOUND) {
            oName.SetFullName(filename);
            ok=false;
            switch (ExtType(oName.GetExt())) {
                case 'a': ok=CheckBoxAudio->IsChecked(); break;
                case 'v': ok=CheckBoxVideo->IsChecked(); break;
                case 'L': ok=CheckBoxLOR->IsChecked(); break;
                case 'V': ok=CheckBoxVixen->IsChecked(); break;
                case 'X': ok=CheckBoxXlights->IsChecked(); break;
            }
            if (ok) TreeCtrlFiles->AppendItem(root,filename);
        }
        cont = dir.GetNext(&filename);
    }
    TreeCtrlFiles->ExpandAll();
}

// returns V for vixen, L for LOR, X for xLights, a for audio, v for video
char xScheduleFrame::ExtType(const wxString& ext) {
    if (ext == _("vix")) {
        return 'V';
    } else if (ext == _(XLIGHTS_SEQUENCE_EXT)) {
        return 'X';
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

// returns -1 if not found
long xScheduleFrame::GetSelectedItem(wxListCtrl* ListBoxPlay)
{
    return ListBoxPlay->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
}

void xScheduleFrame::OnButtonSetDelayClick()
{
    int baseid=1000*Notebook1->GetSelection();
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    long SelectedItem = GetSelectedItem(ListBoxPlay);
    if (SelectedItem == -1) {
        wxMessageBox(_("Please select a single row in the playlist first"), _("Error"));
        return;
    }
    wxListItem column1;
    column1.SetId(SelectedItem);
    column1.SetColumn(1);
    column1.SetMask(wxLIST_MASK_TEXT);
    ListBoxPlay->GetItem(column1);
    wxString delay = column1.GetText();
    long CurrentValue;
    delay.ToLong(&CurrentValue);
    long NewValue = wxGetNumberFromUser(_("Amount of delay after the selected item has finished playing"),
                        _("Enter the number of seconds (0-3600)"), _("Set Delay"), CurrentValue, 0, 3600, this);
    if (NewValue >= 0) {
        delay = wxString::Format(wxT("%ld"),NewValue);
        ListBoxPlay->SetItem(SelectedItem, 1, delay);
        UnsavedChanges=true;
    }
}

void xScheduleFrame::OnButtonPlayItemClick()
{
    if (basic.IsRunning()) {
        StatusBar1->SetStatusText(_("A playlist is already running!"));
        return;
    }
    int baseid=1000*Notebook1->GetSelection();
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    long SelectedItem = GetSelectedItem(ListBoxPlay);
    if (SelectedItem == -1) {
        wxMessageBox(_("Please select a single row in the playlist first"), _("Error"));
        return;
    }

    PlayMode=SINGLE;
    wxString filename = ListBoxPlay->GetItemText(SelectedItem);
    // ignore delay value
    Play(filename,0);
}

void xScheduleFrame::PlayerError(const wxString& msg)
{
    if (PlayMode == SCHEDULE) {
        TextCtrlLog->AppendText(msg + _("\n"));
    } else {
        wxMessageBox(msg, _("Error"), wxOK | wxICON_EXCLAMATION);
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
        case 'X':
            PlayXlightsFile(fullpath);
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

void xScheduleFrame::SetMediaFilename(const wxString& filename)
{
    mediaFilename=filename;
    if (mediaFilename.IsEmpty()) return;
    wxPathFormat PathFmt = mediaFilename.Contains(_("\\")) ? wxPATH_DOS : wxPATH_NATIVE;
    wxFileName fn1(mediaFilename, PathFmt);
    if (!fn1.FileExists()) {
        wxFileName fn2(CurrentDir,fn1.GetFullName());
        mediaFilename=fn2.GetFullPath();
    }
}

bool xScheduleFrame::LoadLorFile(wxString& FileName)
{
    LorEvents.clear();
    mediaFilename.clear();
    wxXmlDocument doc;
    if (doc.Load( FileName )) {
        wxXmlNode* root=doc.GetRoot();
        SetMediaFilename(root->GetAttribute(wxT("musicFilename"), wxT("")));
        for( wxXmlNode* e=root->GetChildren(); e!=NULL; e=e->GetNext() ) {
            if (e->GetName() == _("channels")) {
                LoadLorChannels(e);
            }
        }
        return true;
    } else {
        PlayerError(_("Unable to load LOR sequence:\n")+FileName+_("\n\nNote that xLights is unable to play files generated by the LOR demo version."));
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
        if (e->HasAttribute(_("unit")) && e->HasAttribute(_("circuit"))) {
            tempstr=e->GetAttribute(wxT("unit"), wxT("1"));
            tempstr.ToLong(&unit);
            if (unit < 0) unit+=256;
            tempstr=e->GetAttribute(wxT("circuit"), wxT("0"));
            tempstr.ToLong(&circuit);
            tempstr=e->GetAttribute(wxT("network"), wxT("0"));
            tempstr.ToLong(&netnum);
            while (netnum >= LorLastUnit.size()) {
                LorLastUnit.push_back(-1);
            }
            chindex=(unit-1)*16+circuit-1;
            switch (LorMapping) {
                case XLIGHTS_LORMAP_SINGLE:
                    if (netnum==0 && chindex < VixNetwork.size()) {
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

void xScheduleFrame::LoadLorChannel(wxXmlNode* n, int netnum, int chindex)
{
    long start,end,lastend=0;
    long startint,endint;
    LOR_ACTIONS action;
    wxString tempstr;
    for( wxXmlNode* e=n->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() != _("effect")) continue;
        if (!e->HasAttribute(_("startCentisecond"))) continue;
        if (!e->HasAttribute(_("endCentisecond"))) continue;
        if (!e->HasAttribute(_("type"))) continue;

        tempstr=e->GetAttribute(wxT("type"), wxT(""));
        if (tempstr == _("intensity")) {
            action=LOR_INTENSITY;
        } else if (tempstr == _("twinkle")) {
            action=LOR_TWINKLE;
        } else if (tempstr == _("shimmer")) {
            action=LOR_SHIMMER;
        } else {
            continue;
        }
        tempstr=e->GetAttribute(wxT("startCentisecond"), wxT("0"));
        tempstr.ToLong(&start);
        tempstr=e->GetAttribute(wxT("endCentisecond"), wxT("0"));
        tempstr.ToLong(&end);
        if (e->HasAttribute(wxT("intensity"))) {
            tempstr=e->GetAttribute(wxT("intensity"), wxT("0"));
            tempstr.ToLong(&startint);
            endint=-1;
        } else if (e->HasAttribute(wxT("startIntensity")) && e->HasAttribute(wxT("endIntensity"))) {
            tempstr=e->GetAttribute(wxT("startIntensity"), wxT("0"));
            tempstr.ToLong(&startint);
            tempstr=e->GetAttribute(wxT("endIntensity"), wxT("100"));
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


void xScheduleFrame::PlayXlightsFile(wxString& FileName)
{
    if (!CheckPorts()) return;
    if (!LoadXlightsFile(FileName)) return;
    if (VixNumChannels <= 0) {
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


bool xScheduleFrame::LoadXlightsFile(wxString& FileName)
{
    wxFile f;
    wxFileName fn;
    fn.AssignDir(CurrentDir);
    char hdr[512],filetype[10];
    int fileversion,numch,numper,scancnt;
    size_t SeqDataLen, readcnt;
    mediaFilename.clear();
    if (VixEventData) delete VixEventData;
    VixEventPeriod=50;
    VixNumChannels=0;
    VixNumPeriods=0;
    VixNetwork2.clear();
    bool ok = false;
    if (f.Open(FileName.c_str())) {
        f.Read(hdr,512);
        scancnt=sscanf(hdr,"%8s %2d %8d %8d",filetype,&fileversion,&numch,&numper);
        if (scancnt != 4 || strncmp(filetype,"xLights",7) != 0 || numch <= 0 || numper <= 0) {
            PlayerError(_("Invalid file header:\n")+FileName);
        } else {
            VixNumPeriods=numper;
            VixNumChannels=numch;
            SeqDataLen=VixNumPeriods * VixNumChannels;
            wxString filename=wxString::FromAscii(hdr+32);
            SetMediaFilename(filename);
            VixEventData = new wxUint8[SeqDataLen];
            readcnt = f.Read(VixEventData,SeqDataLen);
            if (readcnt < SeqDataLen) {
                PlayerError(_("Unable to read all event data from:\n")+FileName);
            } else {
                xout->SetMaxIntensity(255);
                for (unsigned int i=0; i < VixNetwork.size(); i++) {
                    VixNetwork2.push_back(VixNetwork[i]);
                }
                ok=true;
            }
        }
        f.Close();
    } else {
        PlayerError(_("Unable to load sequence:\n")+FileName);
    }
    return ok;
}

void xScheduleFrame::PlayVixenFile(wxString& FileName)
{
    if (!CheckPorts()) return;
    if (!LoadVixenFile(FileName)) return;
    if (VixEventPeriod < 0) {
        PlayerError(_("EventPeriodInMilliseconds is undefined"));
    } else if (VixNumChannels <= 0) {
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
    long OutputChannel;
    long SeqDataLen;
    wxString tag,tempstr;
    wxFileName fn;
    fn.AssignDir(CurrentDir);
    mediaFilename.clear();
    if (VixEventData) delete VixEventData;
    VixNumChannels = 0;
    VixEventPeriod=-1;
    VixNetwork2.clear();
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
                wxString filename=e->GetAttribute(wxT("filename"), wxT(""));
                SetMediaFilename(filename);
            } else if (tag == _("Channels")) {
                for( wxXmlNode* p=e->GetChildren(); p!=NULL; p=p->GetNext() ) {
                    if (p->GetName() == _("Channel")) {
                        VixNumChannels++;
                        if (p->HasAttribute(wxT("output"))) {
                            tempstr=p->GetAttribute(wxT("output"), wxT("0"));
                            tempstr.ToLong(&OutputChannel);
                            VixNetwork2.push_back(VixNetwork[OutputChannel]);
                        }
                    }
                }
            } else if (tag == _("Profile")) {
                tempstr=e->GetNodeContent();
                if (!tempstr.IsEmpty()) {
                    if (!LoadVixenProfile(tempstr)) return false;
                }
            } else if (tag == _("EventValues")) {
                VixEventData = base64_decode(e->GetNodeContent(), &SeqDataLen);
            }
        }
        if (VixEventData && VixNumChannels > 0) {
            xout->SetMaxIntensity(MaxIntensity);
            VixNumPeriods = SeqDataLen / VixNumChannels;
            return true;
        } else {
            PlayerError(_("No channels in this sequence or its profile:\n")+FileName);
        }
    } else {
        PlayerError(_("Unable to load sequence:\n")+FileName);
    }
    return false;
}

// return true on success
bool xScheduleFrame::LoadVixenProfile(const wxString& ProfileName)
{
    wxString tag,tempstr;
    long OutputChannel;
    VixNumChannels = 0;
    VixNetwork2.clear();
    wxFileName fn;
    fn.AssignDir(CurrentDir);
    fn.SetFullName(ProfileName + wxT(".pro"));
    if (!fn.FileExists()) {
        PlayerError(_("Unable to find Vixen profile: ")+ProfileName+_("\n\nMake sure a copy is in your xLights directory"));
        return false;
    }
    wxXmlDocument doc( fn.GetFullPath() );
    if (doc.IsOk()) {
        wxXmlNode* root=doc.GetRoot();
        for( wxXmlNode* e=root->GetChildren(); e!=NULL; e=e->GetNext() ) {
            tag = e->GetName();
            if (tag == _("ChannelObjects")) {
                for( wxXmlNode* p=e->GetChildren(); p!=NULL; p=p->GetNext() ) {
                    if (p->GetName() == _("Channel")) {
                        VixNumChannels++;
                        if (p->HasAttribute(wxT("output"))) {
                            tempstr=p->GetAttribute(wxT("output"), wxT("0"));
                            tempstr.ToLong(&OutputChannel);
                            VixNetwork2.push_back(VixNetwork[OutputChannel]);
                        }
                    }
                }
            }
        }
        return true;
    } else {
        PlayerError(_("Unable to load Vixen profile: ")+ProfileName);
    }
    return false;
}
void xScheduleFrame::OnButtonUpClick()
{
    int baseid=1000*Notebook1->GetSelection();
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    long SelectedItem = GetSelectedItem(ListBoxPlay);
    if (SelectedItem == -1) {
        wxMessageBox(_("Please select a single row in the playlist first"), _("Error"));
        return;
    }

    if (SelectedItem == 0) return;
    wxString filename = ListBoxPlay->GetItemText(SelectedItem);
    wxListItem column1;
    column1.SetId(SelectedItem);
    column1.SetColumn(1);
    column1.SetMask(wxLIST_MASK_TEXT);
    ListBoxPlay->GetItem(column1);
    wxString delay = column1.GetText();
    ListBoxPlay->DeleteItem(SelectedItem);
    SelectedItem--;
    ListBoxPlay->InsertItem(SelectedItem,filename);
    ListBoxPlay->SetItem(SelectedItem,1,delay);
    ListBoxPlay->SetItemState(SelectedItem,wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
    UnsavedChanges=true;
}

void xScheduleFrame::OnButtonDownClick()
{
    int baseid=1000*Notebook1->GetSelection();
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    long SelectedItem = GetSelectedItem(ListBoxPlay);
    if (SelectedItem == -1) {
        wxMessageBox(_("Please select a single row in the playlist first"), _("Error"));
        return;
    }

    if (SelectedItem == ListBoxPlay->GetItemCount()-1) return;
    wxString filename = ListBoxPlay->GetItemText(SelectedItem);
    wxListItem column1;
    column1.SetId(SelectedItem);
    column1.SetColumn(1);
    column1.SetMask(wxLIST_MASK_TEXT);
    ListBoxPlay->GetItem(column1);
    wxString delay = column1.GetText();
    ListBoxPlay->DeleteItem(SelectedItem);
    SelectedItem++;
    ListBoxPlay->InsertItem(SelectedItem,filename);
    ListBoxPlay->SetItem(SelectedItem,1,delay);
    ListBoxPlay->SetItemState(SelectedItem,wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
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

wxString xScheduleFrame::LorChDesc(int ch)
{
    wxString result = wxString::Format(_("[unit %d/chan %d]"),ch / 16 + 1, ch % 16 + 1);
    return result;
}

wxString xScheduleFrame::VixenInfo()
{
    wxString msg;
    int netidx,chcnt,mapcnt,LeftToMap,mapcnt1;
    if (mediaFilename.IsEmpty()) {
        msg+=_("Media file: none");
    } else if (!wxFile::Exists(mediaFilename)) {
        msg+=_("Cannot locate media file:\n") + mediaFilename + _("\n\nMake sure your media files are in the same directory as your sequences.");
    } else {
        msg+=_("Media file: ") + mediaFilename;
    }
    float seqlen = (float)VixNumPeriods*VixEventPeriod/1000.0;
    msg += wxString::Format(_("\nSequence Length: %3.1f sec\nEvent Period: %ld msec\nChannel Count: %ld"),seqlen,VixEventPeriod,VixNumChannels);
    if (VixNumChannels > 0) {
        msg += _("\n\nChannel Map:");
        mapcnt = 0;
        LeftToMap = VixNumChannels;
        netidx = 0;
        while (mapcnt < VixNumChannels && netidx < xout->NetworkCount()) {
            chcnt = xout->GetChannelCount(netidx);
            if (chcnt > 0) {
                mapcnt1 = chcnt < LeftToMap ? chcnt : LeftToMap;
                msg += wxString::Format(_("\nSequence channels %d-%d map to %s channels %d-%d"),mapcnt+1,mapcnt+mapcnt1,xout->GetNetworkDesc(netidx).c_str(),1,mapcnt1);
                mapcnt += mapcnt1;
                LeftToMap -= mapcnt1;
            }
            netidx++;
        }
        if (LeftToMap > 0) {
            msg += wxString::Format(_("\nSequence channels %d-%ld are unmapped"),mapcnt+1,VixNumChannels);
        }
    }
    return msg;
}

void xScheduleFrame::OnButtonInfoClick()
{
    int baseid=1000*Notebook1->GetSelection();
    wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    long SelectedItem = GetSelectedItem(ListBoxPlay);
    if (SelectedItem == -1) {
        wxMessageBox(_("Please select a single row in the playlist first"), _("Error"));
        return;
    }

    wxString filename = ListBoxPlay->GetItemText(SelectedItem);
    wxString msg = _("Information for ") + filename + _("\n\n");
    wxFileName oName(CurrentDir, filename);
    wxString fullpath=oName.GetFullPath();
    int netidx,startch,endch,chcnt,lastch;
    switch (ExtType(oName.GetExt())) {
        case 'L':
            if (LoadLorFile(fullpath)) {
                if (mediaFilename.IsEmpty()) {
                    msg+=_("Media file: none");
                } else if (!wxFile::Exists(mediaFilename)) {
                    msg+=_("Cannot locate media file: ") + mediaFilename + _("\n\nMake sure your media files are in the same directory as your sequences.");
                } else {
                    msg+=_("Media file: ") + mediaFilename;
                }
                msg+=_("\n\nLOR channel mapping mode: ");
                switch (LorMapping) {
                    case XLIGHTS_LORMAP_SINGLE:
                        msg += _("single network\n\nChannel Map:");
                        startch = 0;
                        for (netidx=0; netidx<xout->NetworkCount(); netidx++) {
                            chcnt = xout->GetChannelCount(netidx);
                            if (chcnt > 0) {
                                endch = startch + chcnt - 1;
                                msg += wxString::Format(_("\nLOR sequence ")+LorNetDesc(0)+_(", ")+LorChDesc(startch)+_(" to ")+LorChDesc(endch)+_(" map to ")+xout->GetNetworkDesc(netidx)+_(" channels 1-%d"),chcnt);
                                startch = endch + 1;
                            }
                        }
                        for (netidx=1; netidx<xout->NetworkCount(); netidx++) {
                            if (LorLastUnit[netidx] > 0) {
                                msg += wxString::Format(_("\nLOR sequence ")+LorNetDesc(netidx)+_(", units 1-%d are unmapped"),LorLastUnit[netidx]);
                            }
                        }
                        break;
                    case XLIGHTS_LORMAP_MULTI:
                        msg += _("multi network\n\nChannel Map:");
                        for (netidx=0; netidx<xout->NetworkCount(); netidx++) {
                            if (LorLastUnit[netidx] > 0) {
                                lastch = LorLastUnit[netidx]*16;
                                chcnt = xout->GetChannelCount(netidx);
                                if (chcnt == 0) {
                                    msg += wxString::Format(_("\nLOR sequence ")+LorNetDesc(netidx)+_(", units 1-%d are unmapped"),LorLastUnit[netidx]);
                                } else {
                                    if (chcnt < lastch) lastch = chcnt;
                                    msg += wxString::Format(_("\nLOR sequence ")+LorNetDesc(netidx)+_(", units 1-%d map to ")+xout->GetNetworkDesc(netidx)+_(" channels 1-%d"),LorLastUnit[netidx],lastch);
                                }
                            }
                        }
                        break;
                    case XLIGHTS_LORMAP_STRICT:
                        msg += _("strict\n\nChannel Map:");
                        break;
                }
            } else {
                msg+=_("Unable to load sequence file:\n") + fullpath;
            }
            break;
        case 'X':
            if (LoadXlightsFile(fullpath)) {
                msg+=VixenInfo();
            } else {
                msg+=_("Unable to load sequence file:\n") + fullpath;
            }
            break;
        case 'V':
            if (LoadVixenFile(fullpath)) {
                msg+=VixenInfo();
            } else {
                msg+=_("Unable to load sequence file:\n") + fullpath;
            }
            break;
        default:
            msg+=_("Please select a Vixen, LOR, or xLights sequence when using this command.");
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
    wxListItem column1;
    unsigned int RowCount,baseid;
    wxString v;
    wxCheckBox* chkbox;
    wxTextCtrl* TextCtrlLogic;
    wxXmlDocument doc;
    wxXmlNode *item, *plist, *scriptnode, *scripttext;
    wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("xSchedule") );
    root->AddAttribute( wxT("computer"), wxGetHostName());
    doc.SetRoot( root );

    // save schedule
    wxXmlNode* sched = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("schedule") );
    sched->AddAttribute( wxT("schedstart"), ShowStartDate.FormatISODate() );
    sched->AddAttribute( wxT("schedend"), ShowEndDate.FormatISODate() );
    root->AddChild(sched);
    int cnt=ShowEvents.GetCount();
    for (int i=0; i<cnt; i++) {
        item = new wxXmlNode( wxXML_ELEMENT_NODE, _("calevent") );
        item->AddAttribute( wxT("schedcode"), ShowEvents[i] );
        sched->AddChild( item );
    }

    // save playlists
    wxXmlNode* lists = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("playlists") );
    root->AddChild(lists);

    cnt=Notebook1->GetPageCount();
    for (int pagenum=FixedPages; pagenum < cnt; pagenum++) {
        plist = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("playlist") );
        plist->AddAttribute( wxT("name"), Notebook1->GetPageText(pagenum) );
        baseid=1000*pagenum;
        wxListCtrl* ListBoxPlay=(wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
        for (int i=CHKBOX_AUDIO; i<=CHKBOX_MOVIEMODE; i++) {
            chkbox=(wxCheckBox*)wxWindow::FindWindowById(baseid+i,Notebook1);
            v = chkbox->GetValue() ? _("1") : _("0");
            wxString label = chkbox->GetLabelText();
            label.Replace(_(" "), _(""));
            plist->AddAttribute( label, v );
        }
        lists->AddChild( plist );

        RowCount=ListBoxPlay->GetItemCount();
        for (unsigned int r=0; r < RowCount; r++ ) {
            item = new wxXmlNode( wxXML_ELEMENT_NODE, _("listitem") );
            item->AddAttribute( wxT("name"), ListBoxPlay->GetItemText(r) );
            column1.SetId(r);
            column1.SetColumn(1);
            column1.SetMask(wxLIST_MASK_TEXT);
            ListBoxPlay->GetItem(column1);
            item->AddAttribute( wxT("delay"), column1.GetText() );
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
    wxDateTime NewStart = wxDateTime::Now();
    wxDateTime NewEnd = wxDateTime::Now();
    if (n->HasAttribute(wxT("schedstart"))) {
        NewStart.ParseFormat(n->GetAttribute( wxT("schedstart"), wxT("")), wxT("%Y-%m-%d"));
    }
    if (n->HasAttribute(wxT("schedend"))) {
        NewEnd.ParseFormat(n->GetAttribute( wxT("schedend"), wxT("")), wxT("%Y-%m-%d"));
    }
    UpdateShowDates(NewStart,NewEnd);
    for( wxXmlNode* e=n->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() == _("calevent")) {
            wxString schedcode = e->GetAttribute( wxT("schedcode"), wxT(""));
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
    wxString name = n->GetAttribute( wxT("name"), wxT(""));
    int baseid=1000*Notebook1->GetPageCount();
    AddPlaylist(name);
    for (int i=CHKBOX_AUDIO; i<=CHKBOX_MOVIEMODE; i++) {
        chkbox=(wxCheckBox*)wxWindow::FindWindowById(baseid+i,Notebook1);
        if (!chkbox) continue;
        wxString label = chkbox->GetLabelText();
        label.Replace(_(" "), _(""));
        chkval = n->GetAttribute(label, wxT("0"));
        chkbox->SetValue( chkval == _("1") );
    }
    wxListCtrl* ListBoxPlay = (wxListCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LISTBOX,Notebook1);
    wxTextCtrl* TextCtrlLogic = (wxTextCtrl*)wxWindow::FindWindowById(baseid+PLAYLIST_LOGIC,Notebook1);
    wxButton* ButtonRemoveScript=(wxButton*)wxWindow::FindWindowById(baseid+REMOVE_SCRIPT_BUTTON,Notebook1);
    int cnt=0;
    for( wxXmlNode* e=n->GetChildren(); e!=NULL; e=e->GetNext() ) {
        if (e->GetName() == _("listitem")) {
            ListBoxPlay->InsertItem(cnt,e->GetAttribute(wxT("name"), wxT("")));
            ListBoxPlay->SetItem(cnt,1,e->GetAttribute(wxT("delay"), wxT("0")));
            cnt++;
        } else if (e->GetName() == _("script")) {
            ButtonRemoveScript->Show();
            TextCtrlLogic->Show();
            TextCtrlLogic->ChangeValue( e->GetNodeContent() );
        }
    }
    ListBoxPlay->SetColumnWidth(0,wxLIST_AUTOSIZE);
    ScanForFiles();
}

// based on example given here: http://stackoverflow.com/questions/342409/how-do-i-base64-encode-decode-in-c
wxUint8 *xScheduleFrame::base64_decode(const wxString& data, long *output_length)
{
    long input_length = data.size();
    if (input_length % 4 != 0) return 0;

    *output_length = input_length / 4 * 3;
    if (data[input_length - 1] == '=') (*output_length)--;
    if (data[input_length - 2] == '=') (*output_length)--;

    wxUint8 *decoded_data = new wxUint8[*output_length];
    if (decoded_data == 0) return 0;

    for (int i = 0, j = 0; i < input_length;) {

        wxUint32 sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        wxUint32 sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        wxUint32 sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        wxUint32 sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

        wxUint32 triple = (sextet_a << 3 * 6)
                        + (sextet_b << 2 * 6)
                        + (sextet_c << 1 * 6)
                        + (sextet_d << 0 * 6);

        if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }

    return decoded_data;
}


void xScheduleFrame::build_decoding_table()
{
    static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                    'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                    '4', '5', '6', '7', '8', '9', '+', '/'};

    for (int i = 0; i < 0x40; i++)
        decoding_table[encoding_table[i]] = i;
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

void xScheduleFrame::RunPlaylist(int nbidx, wxString& script)
{
    wxString PageName=Notebook1->GetPageText(nbidx);
    TextCtrlLog->AppendText(_("At: ") + wxDateTime::Now().FormatTime() + _("\n"));
    TextCtrlLog->AppendText(_("Starting playlist ") + PageName + _("\n"));
    if (basic.IsRunning()) {
        SendToLogAndStatusBar(_("ERROR: unable to start - another playlist is already running!"));
        return;
    }
    wxCheckBox* MovieMode=(wxCheckBox*)FindNotebookControl(nbidx,CHKBOX_MOVIEMODE);
    if (script.IsEmpty()) {
        SendToLogAndStatusBar(_("ERROR: no script to run!"));
        return;
    }
    if (!script.EndsWith(_("\n"))) script += _("\n"); // ensure script ends with a newline
    if (basic.setScript(PageName.mb_str(wxConvUTF8), script.mb_str(wxConvUTF8))) {
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

wxString xScheduleFrame::OnOffString(bool b)
{
    return b ? wxT("on") : wxT("off");
}

wxString xScheduleFrame::CreateScript(wxString ListName, bool Repeat, bool FirstItemOnce, bool LastItemOnce, bool LightsOff, bool Random)
{
    wxString script,loopsize;
    wxString endoflist = Repeat ? wxT("180") : wxT("400");
    wxString loopstart = FirstItemOnce ? wxT("2") : wxT("1");
    wxString loopend = LastItemOnce ? wxT("PLAYLISTSIZE-1") : wxT("PLAYLISTSIZE");
    if (FirstItemOnce && LastItemOnce) {
        loopsize=wxT("PLAYLISTSIZE-2");
    } else if (FirstItemOnce || LastItemOnce) {
        loopsize=wxT("PLAYLISTSIZE-1");
    } else {
        loopsize=wxT("PLAYLISTSIZE");
    }

    script.Append(_("100 REM *\n"));
    script.Append(_("101 REM * Created: ") + wxDateTime::Now().Format() + _("\n"));
    script.Append(_("102 REM * Random: ") + OnOffString(Random) + _("\n"));
    script.Append(_("103 REM * Repeat: ") + OnOffString(Repeat) + _("\n"));
    script.Append(_("104 REM * First Item Once: ") + OnOffString(FirstItemOnce) + _("\n"));
    script.Append(_("105 REM * Last Item Once: ") + OnOffString(LastItemOnce) + _("\n"));
    script.Append(_("106 REM *\n"));
    script.Append(_("110 LET ListName$=\"") + ListName + _("\"\n"));
    script.Append(_("120 SETPLAYLIST ListName$\n"));
    if (FirstItemOnce) {
        script.Append(_("130 ONPLAYBACKEND 140\n"));
        script.Append(_("131 PRINT \"At:\", FORMATDATETIME$(NOW,5)\n"));
        script.Append(_("132 PRINT \"Playing:\",ITEMNAME$(1)\n"));
        script.Append(_("133 PLAYITEM 1\n"));
        script.Append(_("134 WAIT\n"));
    }
    script.Append(_("140 ONPLAYBACKEND 300\n"));

    if (Random) {
        script.Append(_("170 IF ") + loopsize + _(">1 THEN 176\n"));
        script.Append(_("172 PRINT \"ERROR: not enough items in playlist to support random playback\"\n"));
        script.Append(_("174 GOTO 400\n"));
        script.Append(_("176 LET LastItemPlayed=-1\n"));
        script.Append(_("178 DIM PLAYED(PLAYLISTSIZE)\n"));
        script.Append(_("180 FOR I=1 TO PLAYLISTSIZE\n"));
        script.Append(_("182 LET PLAYED(I)=0\n"));
        script.Append(_("184 NEXT I\n"));
        script.Append(_("186 LET PlayCount=0\n"));
        script.Append(_("188 GOTO 300\n"));
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
        script.Append(_("310 IF SECONDSREMAINING <= 0 THEN 400\n"));
        script.Append(_("320 IF PlayCount>=") + loopsize + _(" THEN ") + endoflist + _("\n"));
        script.Append(_("330 LET NextItem=RND(") + loopsize + _(")+") + loopstart + _("\n"));
        script.Append(_("340 IF PLAYED(NextItem)>0 THEN 330\n"));
        script.Append(_("345 IF LastItemPlayed=NextItem THEN 330\n"));
        script.Append(_("350 LET PLAYED(NextItem)=1\n"));
        script.Append(_("360 LET PlayCount=PlayCount+1\n"));
        script.Append(_("370 GOTO 200\n"));
    } else {
        script.Append(_("180 LET NextItem=") + loopstart + _("\n"));
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
        script.Append(_("307 IF TXOVERFLOWCNT = 0 THEN 310\n"));
        script.Append(_("308 PRINT \"Serial transmit overflows:\",TXOVERFLOWCNT\n"));
        script.Append(_("310 IF SECONDSREMAINING <= 0 THEN 400\n"));
        script.Append(_("320 LET NextItem=LastItemPlayed+1\n"));
        script.Append(_("330 IF NextItem <= ") + loopend + _(" THEN 200\n"));
        if (Repeat) script.Append(_("340 GOTO 180\n"));
    }

    script.Append(_("400 REM *\n"));
    script.Append(_("401 REM Reached scheduled end time\n"));
    script.Append(_("402 REM *\n"));
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
    StopDialog dialog(this);
    if (dialog.ShowModal() == wxID_OK) {
        if (dialog.StopImmediately()) {
            if (PlayMode == SCHEDULE) {
                CheckBoxRunSchedule->SetValue(false);
                CheckRunSchedule();
            } else {
                basic.halt();
            }
        } else {
            if (PlayMode == SCHEDULE) {
                EndTimeSec = 0;
            } else {
                SecondsRemaining = 0;
                StatusBar1->SetStatusText(_("Finishing playlist"));
            }
        }
    }
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
    if (cnt <= FixedPages) {
        wxMessageBox(_("Nothing to play. Create a playlist first."), _("Error"));
        return;
    }
    if (selidx < FixedPages) {
        wxMessageBox(_("Click on the desired playlist tab first."), _("Error"));
        return;
    }
    wxString userscript;
    wxTextCtrl* LogicCtl=(wxTextCtrl*)FindNotebookControl(selidx,PLAYLIST_LOGIC);
    if (LogicCtl && LogicCtl->IsShown()) {
        // run custom script
        userscript=LogicCtl->GetValue();
    } else {
        // get playback options, run generic script
        WizardDialog dialog(this);
        if (dialog.ShowModal() != wxID_OK) return;
        userscript=CreateScript(Notebook1->GetPageText(selidx),dialog.CheckBoxRepeat->IsChecked(),dialog.CheckBoxFirstItem->IsChecked(),dialog.CheckBoxLastItem->IsChecked(),false,dialog.CheckBoxRandom->IsChecked());
    }
    PlayMode=PLAYLIST;
    SecondsRemaining=1;
    //wxMessageBox(_("OnAuiToolBarItemPlayClick: RunPlaylist"));
    RunPlaylist(selidx,userscript);
}

// convert hhmm string to seconds past midnight
// 23:59 is treated as 23:59:59
int xScheduleFrame::Time2Seconds(const wxString& hhmm) {
    long t;
    if (hhmm == wxT("2359")) {
        return 24*60*60 - 1;
    } else if (hhmm.ToLong(&t)) {
        int hh=t / 100;
        int mm=t % 100;
        return hh*60*60+mm*60;
    } else {
        return 0;
    }
}


void xScheduleFrame::PopulateShowDialog(AddShowDialog& dialog, wxSortedArrayString& SelectedDates) {

    // populate playlist selection
    int cnt = Notebook1->GetPageCount();
    for (int i=FixedPages; i < cnt; i++) {
        dialog.ChoicePlayList->AppendString(Notebook1->GetPageText(i));
    }

    // populate list of days
    int idx;
    wxString MonthDayStr;
    wxDateTime SchedDay =  ShowStartDate;
    while (SchedDay <= ShowEndDate) {
        MonthDayStr = SchedDay.Format(wxT("%m%d"));
        idx = dialog.ListBoxDates->Append(SchedDay.Format(wxT("%a, %b %d, %Y")));
        if (SelectedDates.Index(MonthDayStr) != wxNOT_FOUND) dialog.ListBoxDates->Select(idx);
        SchedDay += wxTimeSpan::Day();
    }
}


// returns false if user cancelled dialog
bool xScheduleFrame::DisplayAddShowDialog(AddShowDialog& dialog)
{
    while (dialog.ShowModal() == wxID_OK) {
        if (!dialog.IsPlaylistSelected()) {
            wxMessageBox(_("Select a playlist."), _("Error"));
            continue;
        }

        if (!dialog.StartBeforeEnd()) {
            wxMessageBox(_("Start time must be before end time."), _("Error"));
            continue;
        }

        wxArrayInt selections;
        dialog.ListBoxDates->GetSelections(selections);
        if (selections.GetCount() == 0) {
            wxMessageBox(_("No dates selected."), _("Error"));
            continue;
        }

        return true;
    }
    return false;
}


void xScheduleFrame::OnButtonAddShowClick(wxCommandEvent& event)
{
    size_t cnt = Notebook1->GetPageCount();
    if (cnt < FixedPages) {
        wxMessageBox(_("You must create at least one playlist before scheduling your show."), _("Error"));
        return;
    }
    AddShowDialog dialog(this);
    wxSortedArrayString SelectedDates; // leave empty - no dates pre-selected when adding
    PopulateShowDialog(dialog, SelectedDates);
    if (!DisplayAddShowDialog(dialog)) return;

    // user clicked ok, so add events
    wxDateTime SchedDay =  ShowStartDate;
    cnt = dialog.ListBoxDates->GetCount();
    wxString Playlist = dialog.ChoicePlayList->GetStringSelection();
    wxString PartialCode = dialog.PartialEventCode();
    for (size_t i=0; i < cnt; i++) {
        if (dialog.ListBoxDates->IsSelected(i)) AddShow(SchedDay,PartialCode,Playlist);
        SchedDay += wxTimeSpan::Day();
    }
    DisplaySchedule();
}

void xScheduleFrame::UnpackSchedCode(const wxString& SchedCode, wxString& StartTime, wxString& EndTime, wxString& RepeatOptions, wxString& Playlist) {
    StartTime=SchedCode(4,4);
    EndTime=SchedCode(9,4);
    RepeatOptions=SchedCode(14,4);
    Playlist=SchedCode.Mid(18);
}

// populates ListBoxSched for single day
int xScheduleFrame::DisplayScheduleOneDay(const wxDateTime& d, const wxTreeItemId& root) {
    wxString EventDesc, RepeatDesc, StartTime, EndTime, RepeatOptions, Playlist;
    int cnt=0;
    wxString MonthDayStr = d.Format(wxT("%m%d"));
    wxString MonthDayHeading =d.Format(wxT("%A, %B %d, %Y"));
    wxTreeItemId DayItemId = ListBoxSched->AppendItem(root, MonthDayHeading);
    ListBoxSched->SetItemBold(DayItemId);
    for (unsigned int i=0; i < ShowEvents.Count(); i++) {
        if (ShowEvents[i].StartsWith(MonthDayStr)) {
            UnpackSchedCode(ShowEvents[i], StartTime, EndTime, RepeatOptions, Playlist);
            if (RepeatOptions[0]=='R') {
                RepeatDesc=_("  (repeat");
                if (RepeatOptions[1]=='F') RepeatDesc+=_(", first once");
                if (RepeatOptions[2]=='L') RepeatDesc+=_(", last once");
                if (RepeatOptions[3]=='X') RepeatDesc+=_(", random");
                RepeatDesc+=_(")");
            } else if (RepeatOptions[3]=='X') {
                RepeatDesc=_("  (random)");
            } else {
                RepeatDesc.clear();
            }
            EventDesc=wxT("   ") + StartTime.Left(2) + wxT(":") + StartTime.Mid(2) + wxT(" to ") + EndTime.Left(2) + wxT(":") + EndTime.Mid(2) + wxT("  ") + Playlist + RepeatDesc;
            ListBoxSched->AppendItem(DayItemId, EventDesc, -1, -1, new SchedTreeData(ShowEvents[i]));
            cnt++;
        }
    }
    //if (cnt == 0) ListBoxSched->AppendItem(DayItemId, wxT("   <no show scheduled>"));
    return cnt;
}

// populates ListBoxSched based on contents of ShowEvents[]
void xScheduleFrame::DisplaySchedule() {
    ListBoxSched->DeleteAllItems();
    ShowEvents.Sort();
    wxTreeItemId root = ListBoxSched->AddRoot(_("All Scheduled Events"));
    wxDateTime SchedDay =  ShowStartDate;
    while (SchedDay <= ShowEndDate) {
        DisplayScheduleOneDay(SchedDay, root);
        SchedDay += wxTimeSpan::Day();
    }
    ListBoxSched->ExpandAll();
    bool hasevents=!ShowEvents.IsEmpty();
    CheckBoxRunSchedule->Enable(hasevents && PortsOK);
    ButtonUpdateShow->Enable(hasevents);
    ButtonDeleteShow->Enable(hasevents);
    //ButtonDeselect->Enable(hasevents);
}


// adds the event to ShowEvents[]
void xScheduleFrame::AddShow(const wxDateTime& d, const wxString& StartStop, const wxString& Playlist) {
    wxString MonthDayStr = d.Format(wxT("%m%d"));
    wxString SchedCode = MonthDayStr + StartStop + Playlist;
    ShowEvents.Add(SchedCode);
    UnsavedChanges=true;
}


void xScheduleFrame::OnButtonUpdateShowClick(wxCommandEvent& event)
{
    wxString FirstSchedCode, SchedCode, StartTime, EndTime, RepeatOptions, Playlist, PartialCode;
    wxArrayTreeItemIds selections;
    SchedTreeData *SchedPtr;
    wxSortedArrayString SelectedDates;
    int cnt=ListBoxSched->GetSelections(selections);
    for (int i=0; i<cnt; i++) {
        SchedPtr = (SchedTreeData*)ListBoxSched->GetItemData(selections[i]);
        if (SchedPtr) {
            SchedCode=SchedPtr->GetString();
            SelectedDates.Add(SchedCode.Left(4));
            if (FirstSchedCode.IsEmpty()) FirstSchedCode = SchedCode;
        }
    }
    if (FirstSchedCode.length() == 0) {
        wxMessageBox(_("You must select at least one item to edit."));
        return;
    }

    AddShowDialog dialog(this);
    PopulateShowDialog(dialog, SelectedDates);

    // allow all fields to be updated
    UnpackSchedCode(FirstSchedCode, StartTime, EndTime, RepeatOptions, Playlist);
    dialog.ChoicePlayList->SetStringSelection(Playlist);

    dialog.SpinCtrlStartHour->SetValue(StartTime.Left(2));
    dialog.SpinCtrlStartMinute->SetValue(StartTime.Mid(2));
    dialog.SpinCtrlEndHour->SetValue(EndTime.Left(2));
    dialog.SpinCtrlEndMinute->SetValue(EndTime.Mid(2));

    dialog.CheckBoxRepeat->SetValue(RepeatOptions[0]=='R');
    dialog.CheckBoxFirstItem->SetValue(RepeatOptions[1]=='F');
    dialog.CheckBoxLastItem->SetValue(RepeatOptions[2]=='L');
    dialog.CheckBoxRandom->SetValue(RepeatOptions[3]=='X');

    if (!DisplayAddShowDialog(dialog)) return;

    // user clicked ok, so delete old events, then add new events
    DeleteSelectedShows();
    wxDateTime SchedDay =  ShowStartDate;
    cnt = dialog.ListBoxDates->GetCount();
    Playlist = dialog.ChoicePlayList->GetStringSelection();
    PartialCode = dialog.PartialEventCode();
    for (int i=0; i < cnt; i++) {
        if (dialog.ListBoxDates->IsSelected(i)) AddShow(SchedDay,PartialCode,Playlist);
        SchedDay += wxTimeSpan::Day();
    }
    DisplaySchedule();
}

// returns the number of shows that were deleted
int xScheduleFrame::DeleteSelectedShows()
{
    wxArrayTreeItemIds selections;
    SchedTreeData *SchedCode;
    int delcnt=0;
    int cnt=ListBoxSched->GetSelections(selections);
    for (int i=cnt-1; i>=0; i--) {
        SchedCode = (SchedTreeData*)ListBoxSched->GetItemData(selections[i]);
        if (SchedCode) {
            ShowEvents.Remove(SchedCode->GetString());
            delcnt++;
        }
    }
    return delcnt;
}

void xScheduleFrame::OnButtonDeleteShowClick(wxCommandEvent& event)
{
    int delcnt = DeleteSelectedShows();
    if (delcnt == 0) {
        wxMessageBox(_("You must select one or more scheduled items first!"));
    } else {
        DisplaySchedule();
        UnsavedChanges=true;
    }
}

void xScheduleFrame::OnButtonDeselectClick(wxCommandEvent& event)
{
    ListBoxSched->UnselectAll();
}

void xScheduleFrame::CheckRunSchedule()
{
    if (PlayMode == SCHEDULE) basic.halt();
    bool notrunning=!CheckBoxRunSchedule->IsChecked();
    bool hasevents=!ShowEvents.IsEmpty();
    ButtonAddShow->Enable(notrunning);
    ButtonUpdateShow->Enable(notrunning && hasevents);
    ButtonDeleteShow->Enable(notrunning && hasevents);
    ButtonDeselect->Enable(notrunning && hasevents);
    if (CheckBoxRunSchedule->IsChecked()) {
        ForceScheduleCheck();
        StatusBar1->SetStatusText(_("Starting scheduler"), 1);
    } else {
        StatusBar1->SetStatusText(_("Scheduler not running"), 1);
    }
}

void xScheduleFrame::OnCheckBoxRunScheduleClick(wxCommandEvent& event)
{
    CheckRunSchedule();
    long RunFlag=CheckBoxRunSchedule->IsChecked() ? 1 : 0;
    // Get CurrentDir
    wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));
    config->Write(_("RunSchedule"), RunFlag);
}


void xScheduleFrame::OnBitmapButtonSchedInfoClick(wxCommandEvent& event)
{
#ifdef __WXOSX__
    wxMessageBox(_("1) To select multiple items, use cmd-click. Don't worry if date headings get selected - they will be ignored.\n\n2) The schedule is NOT SAVED until you click the save icon.\n\n3)  The schedule WILL NOT RUN unless the Run\nSchedule checkbox is checked."),_("Schedule Tab"));
#else
    wxMessageBox(_("1) To select multiple items, use ctrl-click or shift-click. Don't worry if date headings get selected - they will be ignored.\n\n2) The schedule is NOT SAVED until you click the save icon.\n\n3)  The schedule WILL NOT RUN unless the Run\nSchedule checkbox is checked."),_("Schedule Tab"));
#endif
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
    if (dialog.ShowModal() != wxID_OK) return;
    TextCtrlLogic->ChangeValue(CreateScript(nbName,dialog.CheckBoxRepeat->IsChecked(),dialog.CheckBoxFirstItem->IsChecked(),dialog.CheckBoxLastItem->IsChecked(),false,dialog.CheckBoxRandom->IsChecked()));
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
    StatusBar1->SetStatusText(_("Ports closed, closing media player"));
    if (PlayerDlg) PlayerDlg->Destroy();
    StatusBar1->SetStatusText(_("Deleting xout object"));
    if (xout) delete xout;
    StatusBar1->SetStatusText(_("Closing window frame"));
    this->Destroy();
}

void xScheduleFrame::OnAuiToolBarItemTestClick(wxCommandEvent& event)
{
    xout->SetMaxIntensity(255);
    pTestDialog->Show();
}

void xScheduleFrame::UpdateShowDates(const wxDateTime& NewStart, const wxDateTime NewEnd)
{
    ShowStartDate = NewStart.GetDateOnly();
    ShowEndDate = NewEnd.GetDateOnly();
    StaticTextShowStart->SetLabel(ShowStartDate.FormatDate());
    StaticTextShowEnd->SetLabel(ShowEndDate.FormatDate());
}

void xScheduleFrame::OnButtonShowDatesChangeClick(wxCommandEvent& event)
{
    ShowDatesDialog dialog(this);
    dialog.CalendarCtrlStart->SetDate(ShowStartDate);
    dialog.CalendarCtrlEnd->SetDate(ShowEndDate);
    while (dialog.ShowModal() == wxID_OK) {
        wxDateTime NewStart = dialog.CalendarCtrlStart->GetDate();
        wxDateTime NewEnd = dialog.CalendarCtrlEnd->GetDate();
        wxTimeSpan diff = NewEnd - NewStart;
        int days = diff.GetDays();
        if (days < 0) {
            wxMessageBox(_("Show end date must be on or after the start date"),_("Error"));
        } else if (days > 100) {
            wxMessageBox(_("Show schedule must span 100 days or less"),_("Error"));
        } else {
            UpdateShowDates(NewStart,NewEnd);
            DisplaySchedule();
            UnsavedChanges=true;
            break;
        }
    }
}

// drop a list item (start row is in DragRowIdx)
void xScheduleFrame::OnDragEnd(wxMouseEvent& event)
{
  wxListItem column1;
  wxPoint pos = event.GetPosition();  // must reference the event
  int flags = wxLIST_HITTEST_ONITEM;
  long index = DragListBox->HitTest(pos,flags,NULL); // got to use it at last
  if(index >= 0 && index != DragRowIdx){ // valid and not the same as start
    // move/copy the list control items
    column1.SetId(DragRowIdx);
    column1.SetColumn(1);
    column1.SetMask(wxLIST_MASK_TEXT);
    DragListBox->GetItem(column1);
    if (index > DragRowIdx) index++;
    long newidx = DragListBox->InsertItem(index,DragListBox->GetItemText(DragRowIdx));
    DragListBox->SetItem(newidx,1,column1.GetText());
    if (newidx < DragRowIdx) DragRowIdx++;
    DragListBox->DeleteItem(DragRowIdx);
    UnsavedChanges=true;
  }
  // restore cursor
  DragListBox->SetCursor(wxCursor(*wxSTANDARD_CURSOR));
  // disconnect both functions
  DragListBox->Disconnect(wxEVT_LEFT_UP,
    wxMouseEventHandler(xScheduleFrame::OnDragEnd));
  DragListBox->Disconnect(wxEVT_LEAVE_WINDOW,
    wxMouseEventHandler(xScheduleFrame::OnDragQuit));
}

// abort dragging a list item because user has left window
void xScheduleFrame::OnDragQuit(wxMouseEvent& event)
{
  // restore cursor and disconnect unconditionally
  DragListBox->SetCursor(wxCursor(*wxSTANDARD_CURSOR));
  DragListBox->Disconnect(wxEVT_LEFT_UP,
    wxMouseEventHandler(xScheduleFrame::OnDragEnd));
  DragListBox->Disconnect(wxEVT_LEAVE_WINDOW,
    wxMouseEventHandler(xScheduleFrame::OnDragQuit));
}

void xScheduleFrame::OnPlayListBeginDrag(wxListEvent& event)
{
  DragRowIdx = event.GetIndex();	// save the start index
  DragListBox = (wxListCtrl*) event.GetEventObject();
  // do some checks here to make sure valid start
  // ...
  // trigger when user releases left button (drop)
  DragListBox->Connect(wxEVT_LEFT_UP,
    wxMouseEventHandler(xScheduleFrame::OnDragEnd), NULL,this);
  // trigger when user leaves window to abort drag
  DragListBox->Connect(wxEVT_LEAVE_WINDOW,
    wxMouseEventHandler(xScheduleFrame::OnDragQuit), NULL,this);
  // give visual feedback that we are doing something
  DragListBox->SetCursor(wxCursor(wxCURSOR_HAND));
}
