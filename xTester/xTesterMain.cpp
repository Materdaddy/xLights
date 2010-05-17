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
const long xTesterFrame::ID_CHECKLISTBOX1 = wxNewId();
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

BEGIN_EVENT_TABLE(xTesterFrame,wxFrame)
    //(*EventTable(xTesterFrame)
    //*)
END_EVENT_TABLE()

xTesterFrame::xTesterFrame(wxWindow* parent,wxWindowID id)
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
    CheckListBox_Channels = new wxCheckListBox(Panel3, ID_CHECKLISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
    FlexGridSizer2->Add(CheckListBox_Channels, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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

    Connect(ID_SLIDER1,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&xTesterFrame::OnSliderMasterDimmerCmdScroll);
    Connect(ID_SLIDER1,wxEVT_COMMAND_SLIDER_UPDATED,(wxObjectEventFunction)&xTesterFrame::OnSliderMasterDimmerCmdScroll);
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
}

xTesterFrame::~xTesterFrame()
{
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

void xTesterFrame::OnCheckBoxRunClick(wxCommandEvent& event)
{
}

void xTesterFrame::OnSliderMasterDimmerCmdScroll(wxScrollEvent& event)
{
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
                /*
                GridNetwork->AppendRows(1);
                GridNetwork->SetCellValue(r,0,GetAttribute(e,"NetworkType"));
                GridNetwork->SetCellValue(r,1,GetAttribute(e,"ComPort"));
                GridNetwork->SetCellValue(r,2,GetAttribute(e,"BaudRate"));
                GridNetwork->SetCellValue(r,3,GetAttribute(e,"MaxChannels"));
                */
                r++;
            }
        }
    } else {
        wxString msg(doc.ErrorDesc(), wxConvUTF8);
        wxMessageBox(msg, _("Error Loading Network File"));
    }
}

/*
void xTesterFrame::LoadFile()
{
	wxArrayString chNames;
	wxString chDesc, chFunc;
	wxString FileName=channelFile.GetFullPath();
    TiXmlDocument doc( FileName.mb_str() );
    if (!doc.LoadFile()) {
        wxString msg(doc.ErrorDesc(), wxConvUTF8);
        wxMessageBox(msg, _("Error Loading File"));
        return;
    }

    TiXmlElement* root=doc.RootElement();
    for( TiXmlElement* n=root->FirstChildElement(); n!=NULL; n=n->NextSiblingElement() ) {
        if (n->ValueStr() == "network") {
            //wxString NetworkType(n->Attribute("NetworkType"), wxConvUTF8);
            //wxString ComPort(n->Attribute("ComPort"), wxConvUTF8);
            int r=0;
            for( TiXmlElement* e=n->FirstChildElement(); e!=NULL; e=e->NextSiblingElement() ) {
                if (e->ValueStr() == "channel") {
                    chDesc=GetAttribute(e,"desc");
                    chFunc=GetAttribute(e,"func");
                    if (!chDesc.IsEmpty() && chFunc!=_("disabled")) {
                        chNames.Add(chDesc);
                    }
                    //grid->SetCellValue(r,0,GetAttribute(e,"cont"));
                    //grid->SetCellValue(r,1,GetAttribute(e,"chan"));
                    //grid->SetCellValue(r,2,GetAttribute(e,"id"));
                    //grid->SetCellValue(r,4,GetAttribute(e,"func"));
                    //grid->SetCellValue(r,5,GetAttribute(e,"color"));
                    r++;
                }
            }
        }
    }
    CheckListBox_Channels->Set(chNames);
}
*/
