/***************************************************************
 * Name:      xNetworksMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-05-16
 * Copyright: Matt Brown (dowdybrown.com)
 * License:
 **************************************************************/

#include "xNetworksMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(xNetworksFrame)
#include <wx/bitmap.h>
#include <wx/icon.h>
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

//(*IdInit(xNetworksFrame)
const long xNetworksFrame::ID_BUTTON_SAVE = wxNewId();
const long xNetworksFrame::ID_BUTTON_ADDROW = wxNewId();
const long xNetworksFrame::ID_BUTTON_DELROW = wxNewId();
const long xNetworksFrame::ID_GRID_NETWORK = wxNewId();
const long xNetworksFrame::ID_PANEL1 = wxNewId();
const long xNetworksFrame::idMenuQuit = wxNewId();
const long xNetworksFrame::idMenuAbout = wxNewId();
const long xNetworksFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(xNetworksFrame,wxFrame)
    //(*EventTable(xNetworksFrame)
    //*)
END_EVENT_TABLE()

xNetworksFrame::xNetworksFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(xNetworksFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer2;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer1;
    wxMenu* Menu2;

    Create(parent, id, _("xNetworks"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(247,174));
    {
      wxIcon FrameIcon;
      FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("C:\\xlights\\include\\xlights.ico"))));
      SetIcon(FrameIcon);
    }
    FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer2 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    FlexGridSizer2->AddGrowableRow(1);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    ButtonSave = new wxButton(Panel1, ID_BUTTON_SAVE, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SAVE"));
    BoxSizer1->Add(ButtonSave, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonAddRow = new wxButton(Panel1, ID_BUTTON_ADDROW, _("Add Row"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ADDROW"));
    BoxSizer1->Add(ButtonAddRow, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonDelRow = new wxButton(Panel1, ID_BUTTON_DELROW, _("Delete Row"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_DELROW"));
    BoxSizer1->Add(ButtonDelRow, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridNetwork = new wxGrid(Panel1, ID_GRID_NETWORK, wxDefaultPosition, wxSize(530,139), 0, _T("ID_GRID_NETWORK"));
    GridNetwork->CreateGrid(0,4);
    GridNetwork->EnableEditing(true);
    GridNetwork->EnableGridLines(true);
    GridNetwork->SetRowLabelSize(50);
    GridNetwork->SetDefaultColSize(120, true);
    GridNetwork->SetColLabelValue(0, _("Network Type"));
    GridNetwork->SetColLabelValue(1, _("Port"));
    GridNetwork->SetColLabelValue(2, _("Baud Rate"));
    GridNetwork->SetColLabelValue(3, _("Last Channel"));
    GridNetwork->SetDefaultCellFont( GridNetwork->GetFont() );
    GridNetwork->SetDefaultCellTextColour( GridNetwork->GetForegroundColour() );
    FlexGridSizer2->Add(GridNetwork, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer2);
    FlexGridSizer2->Fit(Panel1);
    FlexGridSizer2->SetSizeHints(Panel1);
    FlexGridSizer1->Add(Panel1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
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
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_BUTTON_SAVE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xNetworksFrame::OnButtonSaveClick);
    Connect(ID_BUTTON_ADDROW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xNetworksFrame::OnButtonAddRowClick);
    Connect(ID_BUTTON_DELROW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&xNetworksFrame::OnButtonDelRowClick);
    Connect(ID_GRID_NETWORK,wxEVT_GRID_EDITOR_SHOWN,(wxObjectEventFunction)&xNetworksFrame::OnGridNetworkEditorShown);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xNetworksFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xNetworksFrame::OnAbout);
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
    UnsavedChanges=false;
    if (networkFile.FileExists()) {
        LoadFile();
    }

    wxArrayString types;
    types.Add(_("DMX-Entec Pro/Lynx"));
    types.Add(_("LOR/d-Light"));
    types.Add(_("Renard"));
    wxGridCellAttr* col0=new wxGridCellAttr();
    col0->SetEditor(new wxGridCellChoiceEditor(types));
    GridNetwork->SetColAttr(0,col0);

    wxArrayString ports;
    PopulatePortChooser(&ports);
    wxGridCellAttr* col1=new wxGridCellAttr();
    col1->SetEditor(new wxGridCellChoiceEditor(ports));
    GridNetwork->SetColAttr(1,col1);

    wxArrayString rates;
    rates.Add(_("115200"));
    rates.Add(_("57600"));
    rates.Add(_("38400"));
    rates.Add(_("19200"));
    rates.Add(_("9600"));
    wxGridCellAttr* col2=new wxGridCellAttr();
    col2->SetEditor(new wxGridCellChoiceEditor(rates));
    GridNetwork->SetColAttr(2,col2);
}

xNetworksFrame::~xNetworksFrame()
{
    if (UnsavedChanges) {
        wxMessageDialog confirm(this, _("Save changes?"), _("Confirm"), wxYES|wxNO);
        if (confirm.ShowModal() == wxID_YES) {
            SaveFile();
        }
    }
    //(*Destroy(xNetworksFrame)
    //*)
}

void xNetworksFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void xNetworksFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _(XLIGHTS_LICENSE);
    wxString hdg = wxString::Format(_("About xLights %s"),_(XLIGHTS_VERSION));
    wxMessageBox(msg, hdg);
}

void xNetworksFrame::OnGridNetworkEditorShown(wxGridEvent& event)
{
    UnsavedChanges=true;
}

void xNetworksFrame::LoadFile()
{
    wxString FileName=networkFile.GetFullPath();
    TiXmlDocument doc( FileName.mb_str() );
    if (doc.LoadFile()) {
        int r=0;
        for( TiXmlElement* e=doc.RootElement()->FirstChildElement(); e!=NULL; e=e->NextSiblingElement() ) {
            if (e->ValueStr() == "network") {
                GridNetwork->AppendRows(1);
                GridNetwork->SetCellValue(r,0,GetAttribute(e,"NetworkType"));
                GridNetwork->SetCellValue(r,1,GetAttribute(e,"ComPort"));
                GridNetwork->SetCellValue(r,2,GetAttribute(e,"BaudRate"));
                GridNetwork->SetCellValue(r,3,GetAttribute(e,"MaxChannels"));
                r++;
            }
        }
    } else {
        wxString msg(doc.ErrorDesc(), wxConvUTF8);
        wxMessageBox(msg, _("Error Loading Network File"));
    }
}

wxString xNetworksFrame::GetAttribute(TiXmlElement* e, const char *attr)
{
    wxString s(e->Attribute(attr), wxConvUTF8);
    return s;
}

void xNetworksFrame::SaveFile()
{
    int RowCount;
  TiXmlElement* net;
  wxString FileName=networkFile.GetFullPath();
    TiXmlDocument doc( FileName.mb_str() );
   TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
  doc.LinkEndChild( decl );
  TiXmlElement* root = new TiXmlElement( "Networks" );
    root->SetAttribute("computer", wxGetHostName().mb_str());
  doc.LinkEndChild( root );

    RowCount=GridNetwork->GetNumberRows();
    for (int r=0; r < RowCount; r++ ) {
        net = new TiXmlElement( "network" );
        SetAttribute(net,"NetworkType",GridNetwork->GetCellValue(r,0));
        SetAttribute(net,"ComPort",GridNetwork->GetCellValue(r,1));
        SetAttribute(net,"BaudRate",GridNetwork->GetCellValue(r,2));
        SetAttribute(net,"MaxChannels",GridNetwork->GetCellValue(r,3));
        root->LinkEndChild( net );
    }
    if (doc.SaveFile()) {
        UnsavedChanges=false;
    } else {
        wxString msg(doc.ErrorDesc(), wxConvUTF8);
        wxMessageBox(msg, _("Error Network Saving File"));
    }
}

void xNetworksFrame::SetAttribute(TiXmlElement* e, std::string name, wxString value)
{
    std::string svalue(value.mb_str());
    e->SetAttribute(name, svalue);
}


void xNetworksFrame::OnButtonSaveClick(wxCommandEvent& event)
{
    SaveFile();
}

void xNetworksFrame::OnButtonAddRowClick(wxCommandEvent& event)
{
    GridNetwork->AppendRows(1);
}

void xNetworksFrame::OnButtonDelRowClick(wxCommandEvent& event)
{
}

void xNetworksFrame::PopulatePortChooser(wxArrayString *chooser)
{
#ifdef WIN32
   chooser->Add(_("COM1"));
   chooser->Add(_("COM2"));
   chooser->Add(_("COM3"));
   chooser->Add(_("COM4"));
   chooser->Add(_("COM5"));
   chooser->Add(_("COM6"));
   chooser->Add(_("COM7"));
   chooser->Add(_("COM8"));
   chooser->Add(_("COM9"));
#else
   chooser->Add(_("/dev/ttyS0"));
   chooser->Add(_("/dev/ttyS1"));
   chooser->Add(_("/dev/ttyS2"));
   chooser->Add(_("/dev/ttyS3"));
   chooser->Add(_("/dev/ttyUSB0"));
   chooser->Add(_("/dev/ttyUSB1"));
   chooser->Add(_("/dev/ttyUSB2"));
   chooser->Add(_("/dev/ttyUSB3"));
#endif
}
