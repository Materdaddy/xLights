/***************************************************************
 * Name:      xTesterMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-04-03
 * Copyright: Matt Brown (dowdybrown.com)
 * License:
 **************************************************************/

#include "xTesterMain.h"
#include <wx/msgdlg.h>
#include <wx/config.h>

//(*InternalHeaders(xTesterFrame)
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
#include "../include/xlights_out.cpp"


#define MAXINTENSITY 255
#define XTIMER_INTERVAL 50

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

//(*IdInit(xTesterFrame)
const long xTesterFrame::ID_STATICTEXT1 = wxNewId();
const long xTesterFrame::ID_STATICTEXT3 = wxNewId();
const long xTesterFrame::ID_BUTTON1 = wxNewId();
const long xTesterFrame::ID_NOTEBOOK2 = wxNewId();
const long xTesterFrame::ID_STATICTEXT2 = wxNewId();
const long xTesterFrame::ID_SLIDER1 = wxNewId();
const long xTesterFrame::ID_STATICTEXT6 = wxNewId();
const long xTesterFrame::ID_STATICTEXT11 = wxNewId();
const long xTesterFrame::ID_PANEL1 = wxNewId();
const long xTesterFrame::ID_CHECKBOX_RUNSEQ = wxNewId();
const long xTesterFrame::ID_STATICTEXT4 = wxNewId();
const long xTesterFrame::ID_SLIDER2 = wxNewId();
const long xTesterFrame::ID_STATICTEXT5 = wxNewId();
const long xTesterFrame::ID_STATICTEXT10 = wxNewId();
const long xTesterFrame::ID_PANEL2 = wxNewId();
const long xTesterFrame::ID_CHECKBOX_RUNALT = wxNewId();
const long xTesterFrame::ID_STATICTEXT7 = wxNewId();
const long xTesterFrame::ID_SLIDER3 = wxNewId();
const long xTesterFrame::ID_STATICTEXT8 = wxNewId();
const long xTesterFrame::ID_STATICTEXT9 = wxNewId();
const long xTesterFrame::ID_PANEL3 = wxNewId();
const long xTesterFrame::ID_NOTEBOOK1 = wxNewId();
const long xTesterFrame::ID_PANEL4 = wxNewId();
const long xTesterFrame::idMenuQuit = wxNewId();
const long xTesterFrame::idMenuAbout = wxNewId();
const long xTesterFrame::ID_STATUSBAR1 = wxNewId();
//*)
const long xTesterFrame::ID_TIMER = wxNewId();

BEGIN_EVENT_TABLE(xTesterFrame,wxFrame)
    //(*EventTable(xTesterFrame)
    //*)
    EVT_TIMER(ID_TIMER, xTesterFrame::OnTimer)
END_EVENT_TABLE()

xTesterFrame::xTesterFrame(wxWindow* parent,wxWindowID id) : timer(this, ID_TIMER)
{
    //(*Initialize(xTesterFrame)
    wxBoxSizer* BoxSizer4;
    wxFlexGridSizer* FlexGridSizer4;
    wxBoxSizer* BoxSizer5;
    wxMenuItem* MenuItem2;
    wxFlexGridSizer* FlexGridSizer3;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer2;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("xTester"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("../include/xlights.ico"))));
    	SetIcon(FrameIcon);
    }
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel3 = new wxPanel(this, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE, _T("ID_PANEL4"));
    FlexGridSizer2 = new wxFlexGridSizer(2, 2, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    FlexGridSizer2->AddGrowableCol(1);
    FlexGridSizer2->AddGrowableRow(1);
    StaticText1 = new wxStaticText(Panel3, ID_STATICTEXT1, _("1. Select channels"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    StaticText3 = new wxStaticText(Panel3, ID_STATICTEXT3, _("2. Select test"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer2->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button1 = new wxButton(Panel3, ID_BUTTON1, _("All Lights Off"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(Button1, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
    FlexGridSizer2->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Notebook2 = new wxNotebook(Panel3, ID_NOTEBOOK2, wxDefaultPosition, wxSize(191,220), 0, _T("ID_NOTEBOOK2"));
    FlexGridSizer2->Add(Notebook2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Notebook1 = new wxNotebook(Panel3, ID_NOTEBOOK1, wxDefaultPosition, wxSize(219,161), 0, _T("ID_NOTEBOOK1"));
    Panel_Dim = new wxPanel(Notebook1, ID_PANEL1, wxPoint(29,39), wxSize(211,136), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    StaticText2 = new wxStaticText(Panel_Dim, ID_STATICTEXT2, _("Dim selected channels"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer1->Add(StaticText2, 0, wxTOP|wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 10);
    SliderMasterDimmer = new wxSlider(Panel_Dim, ID_SLIDER1, 0, 0, 255, wxDefaultPosition, wxSize(184,48), wxSL_HORIZONTAL|wxSL_AUTOTICKS|wxSL_LABELS|wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER1"));
    FlexGridSizer1->Add(SliderMasterDimmer, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    StaticText6 = new wxStaticText(Panel_Dim, ID_STATICTEXT6, _("Off"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    BoxSizer4->Add(StaticText6, 1, wxALL|wxSHAPED|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText11 = new wxStaticText(Panel_Dim, ID_STATICTEXT11, _("On"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    BoxSizer4->Add(StaticText11, 1, wxALL|wxSHAPED|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(BoxSizer4, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    Panel_Dim->SetSizer(FlexGridSizer1);
    FlexGridSizer1->SetSizeHints(Panel_Dim);
    Panel_Seq = new wxPanel(Notebook1, ID_PANEL2, wxPoint(71,15), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer3->AddGrowableCol(0);
    CheckBoxRunSeq = new wxCheckBox(Panel_Seq, ID_CHECKBOX_RUNSEQ, _("Run selected lights in sequence"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RUNSEQ"));
    CheckBoxRunSeq->SetValue(false);
    FlexGridSizer3->Add(CheckBoxRunSeq, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 10);
    StaticText4 = new wxStaticText(Panel_Seq, ID_STATICTEXT4, _("Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    wxFont StaticText4Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText4->SetFont(StaticText4Font);
    FlexGridSizer3->Add(StaticText4, 0, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 10);
    Slider1 = new wxSlider(Panel_Seq, ID_SLIDER2, 0, 0, 100, wxDefaultPosition, wxSize(184,24), wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER2"));
    FlexGridSizer3->Add(Slider1, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 10);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticText5 = new wxStaticText(Panel_Seq, ID_STATICTEXT5, _("Slow"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    BoxSizer3->Add(StaticText5, 1, wxALL|wxSHAPED|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText10 = new wxStaticText(Panel_Seq, ID_STATICTEXT10, _("Fast"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    BoxSizer3->Add(StaticText10, 1, wxALL|wxSHAPED|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(BoxSizer3, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    Panel_Seq->SetSizer(FlexGridSizer3);
    FlexGridSizer3->Fit(Panel_Seq);
    FlexGridSizer3->SetSizeHints(Panel_Seq);
    Panel_Alt = new wxPanel(Notebook1, ID_PANEL3, wxPoint(114,11), wxSize(188,117), wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    CheckBoxRunAlt = new wxCheckBox(Panel_Alt, ID_CHECKBOX_RUNALT, _("Alternate selected lights (even/odd)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RUNALT"));
    CheckBoxRunAlt->SetValue(false);
    FlexGridSizer4->Add(CheckBoxRunAlt, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 10);
    StaticText7 = new wxStaticText(Panel_Alt, ID_STATICTEXT7, _("Speed"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    wxFont StaticText7Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText7->SetFont(StaticText7Font);
    FlexGridSizer4->Add(StaticText7, 0, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 10);
    Slider3 = new wxSlider(Panel_Alt, ID_SLIDER3, 0, 0, 100, wxDefaultPosition, wxSize(184,24), wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER3"));
    FlexGridSizer4->Add(Slider3, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 10);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    StaticText8 = new wxStaticText(Panel_Alt, ID_STATICTEXT8, _("Slow"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    BoxSizer5->Add(StaticText8, 1, wxALL|wxSHAPED|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(Panel_Alt, ID_STATICTEXT9, _("Fast"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    BoxSizer5->Add(StaticText9, 1, wxALL|wxSHAPED|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(BoxSizer5, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    Panel_Alt->SetSizer(FlexGridSizer4);
    FlexGridSizer4->SetSizeHints(Panel_Alt);
    Notebook1->AddPage(Panel_Dim, _("Dim"), false);
    Notebook1->AddPage(Panel_Seq, _("Sequence"), false);
    Notebook1->AddPage(Panel_Alt, _("Alternate"), false);
    FlexGridSizer2->Add(Notebook1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel3->SetSizer(FlexGridSizer2);
    FlexGridSizer2->Fit(Panel3);
    FlexGridSizer2->SetSizeHints(Panel3);
    BoxSizer1->Add(Panel3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
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
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xTesterFrame::OnButton1Click);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xTesterFrame::OnAbout);
    //*)

    // Get CurrentDir
    wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));
    wxString CurrentDir;
    if ( !config->Read(_("LastDir"), &CurrentDir) ) {
        wxMessageBox(_("No directory specified"), _("ERROR"));
        Close();
    }
    networkFile.AssignDir( CurrentDir );
    networkFile.SetFullName(_(XLIGHTS_NETWORK_FILE));
    LoadFile();
    starttime = wxDateTime::UNow();

    if (Networks.Count() > 0) {
        timer.Start(XTIMER_INTERVAL, wxTIMER_CONTINUOUS);
    }
}

xTesterFrame::~xTesterFrame()
{
    if (timer.IsRunning()) timer.Stop();
    //(*Destroy(xTesterFrame)
    //*)
}

void xTesterFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void xTesterFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _(XLIGHTS_LICENSE);
    wxString hdg = wxString::Format(_("About xLights %s"),_(XLIGHTS_VERSION));
    wxMessageBox(msg, hdg);
}

void xTesterFrame::OnTimer(wxTimerEvent& event) {
    static int LastMasterDimValue;
    static int LastSequenceSpeed;
    static long NextSequenceStart = -1;
    static wxArrayInt chArray;
    static int interval;
    static unsigned int seqidx=9999,alt=0;
    int v,n,maxch,ch;
    unsigned int i;
    wxCheckListBox* lb;
    int netidx = Notebook2->GetSelection(); // which network
    lb = Networks[netidx]->ListBox;
    maxch = lb->GetCount();
    wxTimeSpan ts = wxDateTime::UNow() - starttime;
    long curtime = ts.GetMilliseconds().ToLong();
    xout.TimerStart(curtime);
    switch (Notebook1->GetSelection()) {
        case 0:
            // dimmer
            v=SliderMasterDimmer->GetValue();
            if (v != LastMasterDimValue) {
                for (ch=0,n=0; ch < maxch; ch++) {
                    if (lb->IsChecked(ch)) {
                        xout.SetIntensity(netidx, ch, v);
                        n++;
                    }
                }
                LastMasterDimValue = v;
                StatusBar1->SetStatusText(wxString::Format(_("Dimming %d channels to %d"),n,v));
            }
            break;
        case 1:
            // turn on in sequence
            if (CheckBoxRunSeq->IsChecked()) {
                if (LastSequenceSpeed == -1) {
                    // get list of checked channels
                    chArray.Clear();
                    for (ch=0; ch < maxch; ch++) {
                        if (lb->IsChecked(ch)) {
                            chArray.Add(ch);
                        }
                    }
                }
                v=Slider1->GetValue();  // 0-100
                if (v != LastSequenceSpeed) {
                    interval = 1600 - v*15;
                    if (seqidx < chArray.Count()) {
                        NextSequenceStart = curtime + interval;
                    }
                    LastSequenceSpeed = v;
                    StatusBar1->SetStatusText(wxString::Format(_("Turning on %d channels in sequence, speed=%d"),chArray.Count(),interval));
                }
                if (curtime >= NextSequenceStart && chArray.Count() > 0) {
                    if (seqidx < chArray.Count()) xout.off(netidx, chArray[seqidx]);
                    NextSequenceStart = curtime + interval;
                    seqidx++;
                    if (seqidx >= chArray.Count()) seqidx=0;
                    xout.SetIntensity(netidx, chArray[seqidx], MAXINTENSITY);
                }
            } else {
                LastSequenceSpeed=-1;
            }
            break;
        case 2:
            // alternate odd/even
            if (CheckBoxRunAlt->IsChecked()) {
                if (LastSequenceSpeed == -1) {
                    // get list of checked channels
                    chArray.Clear();
                    for (ch=0; ch < maxch; ch++) {
                        if (lb->IsChecked(ch)) {
                            chArray.Add(ch);
                        }
                    }
                }
                v=Slider3->GetValue();  // 0-100
                if (v != LastSequenceSpeed) {
                    interval = 1600 - v*15;
                    NextSequenceStart = curtime + interval;
                    LastSequenceSpeed = v;
                    StatusBar1->SetStatusText(wxString::Format(_("Alternating %d channels, speed=%d"),chArray.Count(),interval));
                }
                if (curtime >= NextSequenceStart) {
                    for (i=0; i < chArray.Count(); i++) {
                        v=(i % 2) ^ alt;
                        xout.SetIntensity(netidx, chArray[i], v * MAXINTENSITY);
                    }
                    NextSequenceStart = curtime + interval;
                    alt=1-alt;
                }
            } else {
                LastSequenceSpeed=-1;
            }
            break;
    }
    xout.TimerEnd();
    //StatusBar1->SetStatusText(ts.Format(_("%S.%l")));
}

wxString xTesterFrame::GetAttribute(TiXmlElement* e, const char *attr)
{
    wxString s(e->Attribute(attr), wxConvUTF8);
    return s;
}

void xTesterFrame::LoadFile()
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

NetworkInfo* xTesterFrame::AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels)
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
    int baud = atoi(BaudRate.mb_str(wxConvUTF8));
    char port[20];
    strcpy( port, (const char*)ComPort.mb_str(wxConvUTF8) );
    try {
        if (net3 == _("LOR")) {
            xout.setnetwork(new xNetwork_LOR(),cnt,MaxChannels,port,baud,MAXINTENSITY);
        } else if (net3 == _("Ren")) {
            xout.setnetwork(new xNetwork_Renard(),cnt,MaxChannels,port,baud,MAXINTENSITY);
        } else if (net3 == _("DMX")) {
            xout.setnetwork(new xNetwork_DMXentec(),cnt,MaxChannels,port,baud,MAXINTENSITY);
        }
    }
    catch (const char *str) {
        wxString errmsg(str,wxConvUTF8);
        wxString msg = wxString::Format(_("Error occurred while connecting to %s network on %s\n\n"),NetworkType.c_str(),ComPort.c_str());
        wxMessageBox(msg+errmsg, _("Communication Error"));
        return NetInfo;
    }
    catch (char *str) {
        wxString errmsg(str,wxConvUTF8);
        wxString msg = wxString::Format(_("Error occurred while connecting to %s network on %s\n\n"),NetworkType.c_str(),ComPort.c_str());
        wxMessageBox(msg+errmsg, _("Communication Error"));
        return NetInfo;
    }

    wxArrayString chNames;
    if (net3 == _("LOR")) {
        for (int i=0; i < MaxChannels; i++) {
            chNames.Add( wxString::Format(_T("Unit %d.%02d"), (i >> 4)+1, (i & 0x0F)+1 ));
        }
    } else {
        for (int i=1; i <= MaxChannels; i++) {
            chNames.Add( wxString::Format(_T("Channel %d"), i) );
        }
    }
    ListBox->Set(chNames);

    return NetInfo;
}


void xTesterFrame::OnButton1Click(wxCommandEvent& event)
{
    SliderMasterDimmer->SetValue(0);
    CheckBoxRunSeq->SetValue(false);
    CheckBoxRunAlt->SetValue(false);
    xout.alloff();
    StatusBar1->SetStatusText(_("All lights off"));
}
