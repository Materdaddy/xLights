/***************************************************************
 * Name:      xChannelsMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-03-01
 * Copyright: Matt Brown (dowdybrown.com)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "xChannelsMain.h"
#include <wx/msgdlg.h>
#include <wx/config.h>

#include "../include/tinyxml.cpp"
#include "../include/tinyxmlerror.cpp"
#include "../include/tinyxmlparser.cpp"

//(*InternalHeaders(xChannelsFrame)
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

//(*IdInit(xChannelsFrame)
const long xChannelsFrame::ID_NOTEBOOK1 = wxNewId();
const long xChannelsFrame::idMenuImport = wxNewId();
const long xChannelsFrame::idMenuExport = wxNewId();
const long xChannelsFrame::idMenuSave = wxNewId();
const long xChannelsFrame::idMenuQuit = wxNewId();
const long xChannelsFrame::ID_MENUITEM_ADDNETWORK = wxNewId();
const long xChannelsFrame::ID_MENUITEM_SETLASTCHANNEL = wxNewId();
const long xChannelsFrame::ID_MENUITEM_ADDCONTROLLERS = wxNewId();
const long xChannelsFrame::idMenuDelete = wxNewId();
const long xChannelsFrame::idMenuAbout = wxNewId();
const long xChannelsFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(xChannelsFrame,wxFrame)
    //(*EventTable(xChannelsFrame)
    //*)
END_EVENT_TABLE()

xChannelsFrame::xChannelsFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(xChannelsFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;
    
    Create(parent, wxID_ANY, _("xChannels"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxSize(750,400), 0, _T("ID_NOTEBOOK1"));
    BoxSizer1->Add(Notebook1, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuImport = new wxMenuItem(Menu1, idMenuImport, _("Import"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuImport);
    MenuExport = new wxMenuItem(Menu1, idMenuExport, _("Export"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuExport);
    MenuItemSave = new wxMenuItem(Menu1, idMenuSave, _("Save"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItemSave);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuAddNetwork = new wxMenuItem(Menu3, ID_MENUITEM_ADDNETWORK, _("Add Network"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuAddNetwork);
    MenuSetLastChannel = new wxMenuItem(Menu3, ID_MENUITEM_SETLASTCHANNEL, _("Set Last Channel"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuSetLastChannel);
    MenuAddControllers = new wxMenuItem(Menu3, ID_MENUITEM_ADDCONTROLLERS, _("Add Controllers"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuAddControllers);
    MenuDeleteController = new wxMenuItem(Menu3, idMenuDelete, _("Delete Controller"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuDeleteController);
    MenuBar1->Append(Menu3, _("&Channels"));
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
    
    Connect(idMenuImport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xChannelsFrame::OnMenuImportSelected);
    Connect(idMenuExport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xChannelsFrame::OnMenuExportSelected);
    Connect(idMenuSave,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xChannelsFrame::OnMenuItemSaveSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xChannelsFrame::OnQuit);
    Connect(ID_MENUITEM_ADDNETWORK,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xChannelsFrame::OnMenuAddNetworkSelected);
    Connect(ID_MENUITEM_SETLASTCHANNEL,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xChannelsFrame::OnMenuSetLastChannelSelected);
    Connect(ID_MENUITEM_ADDCONTROLLERS,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xChannelsFrame::OnMenuAddControllersSelected);
    Connect(idMenuDelete,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xChannelsFrame::OnMenuDeleteControllerSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&xChannelsFrame::OnAbout);
    //*)

    // TO DO:
    // CurrentDir should be passed via ARGV
    Connect(wxEVT_GRID_EDITOR_SHOWN,(wxObjectEventFunction)&xChannelsFrame::GridEdit);
    wxConfig* config = new wxConfig(_(XLIGHTS_CONFIG_ID));
    wxString CurrentDir;
    if ( !config->Read(_("LastDir"), &CurrentDir) ) {
        wxMessageBox(_("No directory specified"), _("ERROR"));
        Close();
    }
    channelFile.AssignDir( CurrentDir );
    channelFile.SetFullName(_(XLIGHTS_CHANNEL_FILE));

    UnsavedChanges=false;
    if (channelFile.FileExists()) {
        LoadFile();
    } else {
        AddNetworkWithPrompt();
    }

}

xChannelsFrame::~xChannelsFrame()
{
    if (UnsavedChanges) {
        wxMessageDialog confirm(this, _("Save changes?"), _("Confirm"), wxYES|wxNO);
        if (confirm.ShowModal() == wxID_YES) {
            SaveFile();
        }
    }
    //(*Destroy(xChannelsFrame)
    //*)
}

void xChannelsFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void xChannelsFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _(XLIGHTS_LICENSE);
    wxString hdg = wxString::Format(_("About xLights %s"),_(XLIGHTS_VERSION));
    wxMessageBox(msg, hdg);
}

void xChannelsFrame::GridEdit(wxGridEvent& event)
{
    UnsavedChanges=true;
}

void xChannelsFrame::LoadFile()
{
	wxString FileName=channelFile.GetFullPath();
    TiXmlDocument doc( FileName.mb_str() );
    if (doc.LoadFile()) {
        TiXmlElement* root=doc.RootElement();
        for( TiXmlElement* e=root->FirstChildElement(); e!=NULL; e=e->NextSiblingElement() ) {
            if (e->ValueStr() == "network") {
                LoadNetwork(e);
            }
        }
    } else {
        wxString msg(doc.ErrorDesc(), wxConvUTF8);
        wxMessageBox(msg, _("Error Loading File"));
    }
}

void xChannelsFrame::LoadNetwork(TiXmlElement* n)
{
    wxString NetworkType(n->Attribute("NetworkType"), wxConvUTF8);
    wxString ComPort(n->Attribute("ComPort"), wxConvUTF8);
    int pagenum=AddNetwork(NetworkType, ComPort);
    wxGrid *grid;
    grid=Grids[pagenum];
    int r=0;
    for( TiXmlElement* e=n->FirstChildElement(); e!=NULL; e=e->NextSiblingElement() ) {
        if (e->ValueStr() == "channel") {
            grid->AppendRows(1);
            grid->SetCellValue(r,0,GetAttribute(e,"cont"));
            grid->SetCellValue(r,1,GetAttribute(e,"chan"));
            grid->SetCellValue(r,2,GetAttribute(e,"id"));
            grid->SetCellValue(r,3,GetAttribute(e,"desc"));
            grid->SetCellValue(r,4,GetAttribute(e,"func"));
            grid->SetCellValue(r,5,GetAttribute(e,"color"));
            r++;
        }
    }
}

wxString xChannelsFrame::GetAttribute(TiXmlElement* e, const char *attr)
{
    wxString s(e->Attribute(attr), wxConvUTF8);
    return s;
}

void xChannelsFrame::AddNetworkWithPrompt()
{
    int cnt=Notebook1->GetPageCount();
    if (cnt == XLIGHTS_MAX_NETWORKS) {
        wxMessageBox(_("Sorry, xLights is limited to XLIGHTS_MAX_NETWORKS networks"),_("Error"));
        return;
    }

    wxString NetworkType, ComPort;
    NewNetworkDialog NetDialog(this);
    if (NetDialog.ShowModal() == wxID_OK) {
        UnsavedChanges=true;
        NetworkType=NetDialog.ChoiceNetwork->GetStringSelection();
        ComPort=NetDialog.ChoicePort->GetStringSelection();
        AddNetwork(NetworkType, ComPort);
    }
}

int xChannelsFrame::AddNetwork(wxString NetworkType, wxString ComPort)
{
    wxBoxSizer* BoxSizer;
    wxFlexGridSizer* FlexSizer;

    int cnt=Notebook1->GetPageCount();
    wxString sid = wxString::Format(_T("%d"), cnt+1);
    wxString gridID = _("Grid ")+sid;
    Panels[cnt] = new wxPanel(Notebook1, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL")+sid);
    FlexSizer = new wxFlexGridSizer(0, 1, 0, 0);
    FlexSizer->AddGrowableRow(1);
    BoxSizer = new wxBoxSizer(wxHORIZONTAL);
    NetworkTypes[cnt] = new wxStaticText(Panels[cnt], -1, NetworkType);
    BoxSizer->Add(NetworkTypes[cnt], 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ComPorts[cnt] = new wxStaticText(Panels[cnt], -1, ComPort);
    BoxSizer->Add(ComPorts[cnt], 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexSizer->Add(BoxSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Grids[cnt] = new wxGrid(Panels[cnt], -1, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL, _T("ID_GRID"+sid));
    Grids[cnt]->CreateGrid(0,6);
    SetGridHeadings(Grids[cnt]);
    FlexSizer->Add(Grids[cnt], 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panels[cnt]->SetSizer(FlexSizer);
    FlexSizer->Fit(Panels[cnt]);
    FlexSizer->SetSizeHints(Panels[cnt]);
    Notebook1->AddPage(Panels[cnt], _("Network ")+sid, true);
    return cnt;
}

void xChannelsFrame::SetGridHeadings(wxGrid *grid)
{
    wxGridCellAttr* col01=new wxGridCellAttr();
    col01->SetAlignment(wxALIGN_CENTRE,wxALIGN_CENTRE);
    col01->SetReadOnly(true);
    grid->SetColLabelValue(0,_("Controller"));
    grid->SetColAttr(0,col01);
    grid->SetColLabelValue(1,_("Channel"));
    grid->SetColAttr(1,col01);
    grid->SetColLabelValue(2,_("Name"));
    grid->SetColLabelValue(3,_("Description"));
    grid->SetColSize(3,200);

    wxGridCellAttr* col4=new wxGridCellAttr();
    wxArrayString functions;
    functions.Add(_("dimmer"));
    functions.Add(_("dimmer-RGB"));
    functions.Add(_("on-off"));
    functions.Add(_("disabled"));
    col4->SetEditor(new wxGridCellChoiceEditor(functions));
    grid->SetColLabelValue(4,_("Function"));
    grid->SetColAttr(4,col4);

    wxGridCellAttr* col5=new wxGridCellAttr();
    wxArrayString colors;
    colors.Add(_("white"));
    colors.Add(_("blue"));
    colors.Add(_("purple"));
    colors.Add(_("red"));
    colors.Add(_("orange"));
    colors.Add(_("yellow"));
    colors.Add(_("green"));
    colors.Add(_("multi"));
    col5->SetEditor(new wxGridCellChoiceEditor(colors));
    grid->SetColLabelValue(5,_("Color"));
    grid->SetColAttr(5,col5);
}

void xChannelsFrame::OnMenuAddNetworkSelected(wxCommandEvent& event)
{
    AddNetworkWithPrompt();
}

void xChannelsFrame::OnMenuSetLastChannelSelected(wxCommandEvent& event)
{
    int pagenum=Notebook1->GetSelection();
    if (pagenum == wxNOT_FOUND) {
        wxMessageBox(_("You must add a network first"),_("Error"));
        return;
    }
    wxString net = NetworkTypes[pagenum]->GetLabelText();

    if (net != _("DMX")) {
        wxMessageBox(_("You can only set the last channel on DMX networks"),_("Error"));
        return;
    }

    wxGrid *grid;
    grid=Grids[pagenum];
    int OldRowCount=grid->GetNumberRows();
    ChannelCountDialog dialog(this);
    if (dialog.ShowModal() == wxID_OK)
    {
        int NewRowCount = dialog.SpinNumberChannels->GetValue();
        int diff=NewRowCount - OldRowCount;
        if (diff > 0) {
            UnsavedChanges=true;
            grid->AppendRows(diff);
            for (int r=OldRowCount; r<NewRowCount; r++) {
                wxString rStr = wxString::Format(_T("%d"), r+1);
                grid->SetCellValue(r,0,_("0"));
                grid->SetCellValue(r,1,rStr);
                grid->SetCellValue(r,4,_("dimmer"));
            }
        } else if (diff < 0) {
            diff=-diff;
            wxString sdiff = wxString::Format(_T("%d"), diff);
            wxString msg = _("Warning: the last ") + sdiff + _(" rows will be deleted!");
            wxMessageDialog confirm(this, msg, _("Confirm"), wxOK|wxCANCEL);
            if (confirm.ShowModal() == wxID_OK) {
                grid->DeleteRows(OldRowCount-diff,diff);
                UnsavedChanges=true;
            }
        }
    }
}

void xChannelsFrame::OnMenuAddControllersSelected(wxCommandEvent& event)
{
    int pagenum=Notebook1->GetSelection();
    if (pagenum == wxNOT_FOUND) {
        wxMessageBox(_("You must add a network first"),_("Error"));
        return;
    }

    wxString net = NetworkTypes[pagenum]->GetLabelText();
    wxGrid *grid;
    grid=Grids[pagenum];
    int r=grid->GetNumberRows();
    AddControllersDialog dialog(this);
    if (net == _("Renard")) {
        dialog.SpinChannelsPerController->SetValue(8);
    } else {
        dialog.SpinChannelsPerController->SetValue(16);
    }
    int fc=MaxController(grid)+1;
    if (net.Left(3) == _("LOR") && fc==0) fc=1;
    dialog.SpinFirstController->SetValue(fc);

    if (dialog.ShowModal() == wxID_OK)
    {
        int FirstController=dialog.SpinFirstController->GetValue();
        int ChannelsPerController=dialog.SpinChannelsPerController->GetValue();
        int NumControllers=dialog.SpinNumControllers->GetValue();
        grid->AppendRows(ChannelsPerController*NumControllers);
        int cont,ch;
        for (cont=0; cont < NumControllers; cont++) {
            wxString scont = wxString::Format(_T("%d"), cont+FirstController);
            for (ch=1; ch <= ChannelsPerController; ch++) {
                wxString sch = wxString::Format(_T("%d"), net==_("DMX") ? r+1 : ch);
                grid->SetCellValue(r,0,scont);
                grid->SetCellValue(r,1,sch);
                grid->SetCellValue(r,4,_("dimmer"));
                r++;
            }
        }
        UnsavedChanges=true;
    }
}

int xChannelsFrame::MaxController(wxGrid *grid)
{
    int result=-1;
    int r=grid->GetNumberRows();
    int GridValue;
    while (r > 0) {
        r--;
        GridValue = wxAtoi(grid->GetCellValue(r,0));
        if (GridValue > result) result=GridValue;
    }
    return result;
}

void xChannelsFrame::SaveFile()
{
    wxGrid *grid;
    int RowCount;
	TiXmlElement* net;
	TiXmlElement* ch;
	wxString FileName=channelFile.GetFullPath();
    TiXmlDocument doc( FileName.mb_str() );
 	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild( decl );
	TiXmlElement* root = new TiXmlElement( "Networks" );
    root->SetAttribute("computer", wxGetHostName().mb_str());
	doc.LinkEndChild( root );

    int cnt=Notebook1->GetPageCount();
    for (int pagenum=0; pagenum < cnt; pagenum++) {
        grid=Grids[pagenum];
        net = new TiXmlElement( "network" );
        net->SetAttribute("NetworkType", NetworkTypes[pagenum]->GetLabelText().mb_str());
        net->SetAttribute("ComPort", ComPorts[pagenum]->GetLabelText().mb_str());
        root->LinkEndChild( net );
        RowCount=grid->GetNumberRows();
        for (int r=0; r < RowCount; r++ ) {
            ch = new TiXmlElement( "channel" );
            SetAttribute(ch,"cont",grid->GetCellValue(r,0));
            SetAttribute(ch,"chan",grid->GetCellValue(r,1));
            SetAttribute(ch,"id",grid->GetCellValue(r,2));
            SetAttribute(ch,"desc",grid->GetCellValue(r,3));
            SetAttribute(ch,"func",grid->GetCellValue(r,4));
            SetAttribute(ch,"color",grid->GetCellValue(r,5));
            net->LinkEndChild( ch );
        }
    }
    if (doc.SaveFile()) {
        UnsavedChanges=false;
    } else {
        wxString msg(doc.ErrorDesc(), wxConvUTF8);
        wxMessageBox(msg, _("Error Saving File"));
    }
}

void xChannelsFrame::SetAttribute(TiXmlElement* e, std::string name, wxString value)
{
    std::string svalue(value.mb_str());
    e->SetAttribute(name, svalue);
}

void xChannelsFrame::OnMenuItemSaveSelected(wxCommandEvent& event)
{
    if (Notebook1->GetPageCount() == 0) {
        wxMessageBox(_("You must add a network first"),_("Error"));
    } else {
        SaveFile();
    }
}

void xChannelsFrame::OnMenuImportSelected(wxCommandEvent& event)
{
    wxMessageBox(_("Not implemented yet"),_("Error"));
}

void xChannelsFrame::OnMenuExportSelected(wxCommandEvent& event)
{
    wxMessageBox(_("Not implemented yet"),_("Error"));
}

void xChannelsFrame::OnMenuDeleteControllerSelected(wxCommandEvent& event)
{
    int pagenum=Notebook1->GetSelection();
    if (pagenum == wxNOT_FOUND) {
        wxMessageBox(_("You must add a network first"),_("Error"));
        return;
    }
    wxGrid *grid;
    grid=Grids[pagenum];
    int RowCount=grid->GetNumberRows();
    if (RowCount == 0) {
        wxMessageBox(_("Nothing to delete"),_("Error"));
        return;
    }
    wxString net = NetworkTypes[pagenum]->GetLabelText();
    if (net == _("DMX")) {
        wxMessageBox(_("For DMX networks, use 'Set Last Channel' to reduce the number of channels, or for unused channels set channel function to disabled"),_("Error"));
        return;
    }

    DeleteControllerDialog dialog(this);

    dialog.ChoiceController->Clear();
    wxString item,lastitem;
    int r;
    for (r=0; r < RowCount; r++) {
        item=grid->GetCellValue(r,0);
        if (item != lastitem) {
            dialog.ChoiceController->Append(item);
            lastitem=item;
        }
    }
    dialog.ChoiceController->SetSelection(0);

    if (dialog.ShowModal() == wxID_OK)
    {
        item=dialog.ChoiceController->GetStringSelection();
        r=RowCount;
        while (r > 0) {
            r--;
            if (item == grid->GetCellValue(r,0)) {
                grid->DeleteRows(r);
            }
        }
        UnsavedChanges=true;
    }
}
