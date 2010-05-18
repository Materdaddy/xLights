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
#define XTIMER_INTERVAL 100

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
const long xTesterFrame::ID_NOTEBOOK2 = wxNewId();
const long xTesterFrame::ID_SLIDER1 = wxNewId();
const long xTesterFrame::ID_STATICTEXT2 = wxNewId();
const long xTesterFrame::ID_BUTTON1 = wxNewId();
const long xTesterFrame::ID_PANEL1 = wxNewId();
const long xTesterFrame::ID_CHECKBOX1 = wxNewId();
const long xTesterFrame::ID_SLIDER2 = wxNewId();
const long xTesterFrame::ID_STATICTEXT4 = wxNewId();
const long xTesterFrame::ID_STATICTEXT5 = wxNewId();
const long xTesterFrame::ID_STATICTEXT6 = wxNewId();
const long xTesterFrame::ID_PANEL2 = wxNewId();
const long xTesterFrame::ID_CHECKBOX2 = wxNewId();
const long xTesterFrame::ID_SLIDER3 = wxNewId();
const long xTesterFrame::ID_STATICTEXT7 = wxNewId();
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
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer2;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("xTester"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("..\\include\\xlights.ico"))));
    	SetIcon(FrameIcon);
    }
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel3 = new wxPanel(this, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE, _T("ID_PANEL4"));
    FlexGridSizer2 = new wxFlexGridSizer(2, 2, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    FlexGridSizer2->AddGrowableRow(1);
    StaticText1 = new wxStaticText(Panel3, ID_STATICTEXT1, _("1. Select channels"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(Panel3, ID_STATICTEXT3, _("2. Select test"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer2->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Notebook2 = new wxNotebook(Panel3, ID_NOTEBOOK2, wxDefaultPosition, wxSize(191,181), 0, _T("ID_NOTEBOOK2"));
    FlexGridSizer2->Add(Notebook2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Notebook1 = new wxNotebook(Panel3, ID_NOTEBOOK1, wxDefaultPosition, wxSize(219,161), 0, _T("ID_NOTEBOOK1"));
    Panel_Dim = new wxPanel(Notebook1, ID_PANEL1, wxPoint(29,39), wxSize(211,136), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    SliderMasterDimmer = new wxSlider(Panel_Dim, ID_SLIDER1, 0, 0, 255, wxPoint(16,40), wxSize(184,48), wxSL_HORIZONTAL|wxSL_AUTOTICKS|wxSL_LABELS|wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER1"));
    StaticText2 = new wxStaticText(Panel_Dim, ID_STATICTEXT2, _("Dim selected channels"), wxPoint(16,16), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    Button1 = new wxButton(Panel_Dim, ID_BUTTON1, _("All Lights Off"), wxPoint(70,100), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Panel_Seq = new wxPanel(Notebook1, ID_PANEL2, wxPoint(71,15), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    CheckBox1 = new wxCheckBox(Panel_Seq, ID_CHECKBOX1, _("Run selected lights in sequence"), wxPoint(8,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox1->SetValue(false);
    Slider1 = new wxSlider(Panel_Seq, ID_SLIDER2, 0, 0, 100, wxPoint(16,72), wxSize(184,24), wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER2"));
    StaticText4 = new wxStaticText(Panel_Seq, ID_STATICTEXT4, _("Speed"), wxPoint(88,48), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    wxFont StaticText4Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText4->SetFont(StaticText4Font);
    StaticText5 = new wxStaticText(Panel_Seq, ID_STATICTEXT5, _("Slow"), wxPoint(16,96), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StaticText6 = new wxStaticText(Panel_Seq, ID_STATICTEXT6, _("Fast"), wxPoint(176,96), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    Panel_Alt = new wxPanel(Notebook1, ID_PANEL3, wxPoint(114,11), wxSize(188,117), wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    CheckBox2 = new wxCheckBox(Panel_Alt, ID_CHECKBOX2, _("Alternate selected lights (even/odd)"), wxPoint(8,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBox2->SetValue(false);
    Slider3 = new wxSlider(Panel_Alt, ID_SLIDER3, 0, 0, 100, wxPoint(16,72), wxSize(184,24), wxSTATIC_BORDER, wxDefaultValidator, _T("ID_SLIDER3"));
    StaticText7 = new wxStaticText(Panel_Alt, ID_STATICTEXT7, _("Speed"), wxPoint(88,48), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    wxFont StaticText7Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText7->SetFont(StaticText7Font);
    StaticText8 = new wxStaticText(Panel_Alt, ID_STATICTEXT8, _("Slow"), wxPoint(16,96), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    StaticText9 = new wxStaticText(Panel_Alt, ID_STATICTEXT9, _("Fast"), wxPoint(176,96), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
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
    int v,n,maxch,ch;
    wxCheckListBox* lb;
    int netidx = Notebook2->GetSelection(); // which network
    lb = Networks[netidx]->ListBox;
    maxch = Networks[netidx]->MaxChannels;
    wxTimeSpan ts = wxDateTime::UNow() - starttime;
    xout.TimerStart(ts.GetMilliseconds().ToLong());
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
                StatusBar1->SetStatusText(wxString::Format(_("# checked=%d Int=%d"),n,v));
            }
            break;
        case 1:
            // turn on in sequence
            break;
        case 2:
            // alternate odd/even
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

NetworkInfo* xTesterFrame::AddNetwork(wxString NetworkType, wxString ComPort, wxString BaudRate, int MaxChannels)
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
    wxArrayString chNames;
    if (net3 == _("LOR")) {
        for (int i=0; i < MaxChannels; i++) {
            chNames.Add( wxString::Format(_T("Unit %d.%02d"), (i >> 4)+1, (i % 4)+1 ));
        }
    } else {
        for (int i=1; i <= MaxChannels; i++) {
            chNames.Add( wxString::Format(_T("Channel %d"), i) );
        }
    }
    ListBox->Set(chNames);

    int baud = atoi(BaudRate.mb_str(wxConvUTF8));
    char port[20];
    strcpy( port, (const char*)ComPort.mb_str(wxConvUTF8) );
    try {
        if (net3 == _("LOR")) {
            xout.addnetwork(new xNetwork_LOR(),cnt,MaxChannels,MAXINTENSITY,port,baud);
        } else if (net3 == _("Ren")) {
            xout.addnetwork(new xNetwork_Renard(),cnt,MaxChannels,MAXINTENSITY,port,baud);
        } else if (net3 == _("DMX")) {
            xout.addnetwork(new xNetwork_DMXentec(),cnt,MaxChannels,MAXINTENSITY,port,baud);
        }
    }
    catch (const char *str) {
        wxString msg(str, wxConvUTF8);
        wxMessageBox(msg, _("Exception Raised"));
    }
    catch (char *str) {
        wxString msg(str, wxConvUTF8);
        wxMessageBox(msg, _("Exception Raised"));
    }

    return NetInfo;
}


void xTesterFrame::OnButton1Click(wxCommandEvent& event)
{
    SliderMasterDimmer->SetValue(0);
    xout.alloff();
}
