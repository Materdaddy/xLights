/* ****************************************************
 * Extend the MiniBasic script class
 * with customized commands for xLights
 */

#include "../include/minibasic.cpp"


class xlbasic: public MiniBasicClass {

protected:

    xLightsFrame* HostFrame;
    wxListCtrl* playlist;
    std::vector<ctb::SerialPort> SerialPorts;
    bool haltflag;
    int runstate;
    int playbackend_goto;

    void infunc(char* prompt, char* buff, int size) {
    }

    void outfunc(char *msg) {
        HostFrame->BasicOutput(msg);
    }

    void errfunc(const char *msg) {
        HostFrame->BasicError(msg);
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
        return HostFrame->SecondsRemaining;
    }

    // returns number of serial transmit overflows since count was last reset
    double do_txoverflowcnt(void) {
        return HostFrame->TxOverflowCnt;
    }

    int do_setplaylist(void) {
        char *pName = stringexpr();
        if(!pName) return 0;
        wxString name(pName,wxConvUTF8);
        int nbidx=HostFrame->FindNotebookPage(name);
        if (nbidx < FixedPages) return 0;
        playlist = (wxListCtrl*)HostFrame->FindNotebookControl(nbidx,HostFrame->PLAYLIST_LISTBOX);
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
            buf[0] = HostFrame->ExtType(ext);
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
        if (HostFrame->xout) HostFrame->xout->alloff();
        return EXEC_NEXTLINE;
    };

    // play item in playlist
    int do_PlayItem(void)
    {
        int idx = integer( expr() );
        if(1 <= idx && idx <= playlist->GetItemCount()) {
            HostFrame->TxOverflowCnt = 0;
            wxString filename = playlist->GetItemText(idx-1);
            wxString delay = _("0"); //playlist->GetCellValue(idx-1,1);
            long idelay;
            delay.ToLong(&idelay);
            HostFrame->Play(filename,idelay);
        } else {
            seterror(ERR_ILLEGALOFFSET);
        }
        return EXEC_NEXTLINE;
    };

    int do_StopPlayback(void)
    {
        HostFrame->StopPlayback();
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

    void setFrame(xLightsFrame* fr) {
        HostFrame=fr;
    };

    void halt() {
        if (runstate == 1) {
            haltflag=true;
        } else if (runstate != 0) {
            runstate=0;
            SerialPorts.clear();
            HostFrame->EndScript(scriptname);
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
        HostFrame->StartScript(scriptname);
        return runFromLineIdx(0);
    }

};

xlbasic basic;
