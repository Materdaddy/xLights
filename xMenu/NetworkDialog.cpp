#include "NetworkDialog.h"

//(*InternalHeaders(NetworkDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/msgdlg.h>
#include "SerialPortWithRate.h"
#include "E131Dialog.h"


//(*IdInit(NetworkDialog)
const long NetworkDialog::ID_BUTTON_SAVE = wxNewId();
const long NetworkDialog::ID_BUTTON_NETCLOSE = wxNewId();
const long NetworkDialog::ID_BUTTON_EDIT_ROW = wxNewId();
const long NetworkDialog::ID_BUTTON_DELROW = wxNewId();
const long NetworkDialog::ID_BUTTON_MOVE_UP = wxNewId();
const long NetworkDialog::ID_BUTTON_MOVE_DOWN = wxNewId();
const long NetworkDialog::ID_BUTTON_ADD_LOR = wxNewId();
const long NetworkDialog::ID_BUTTON_ADD_DLIGHT = wxNewId();
const long NetworkDialog::ID_BUTTON_ADD_RENARD = wxNewId();
const long NetworkDialog::ID_BUTTON_ADD_DMX = wxNewId();
const long NetworkDialog::ID_BUTTON_ADD_OPEN_DMX = wxNewId();
const long NetworkDialog::ID_BUTTON_ADD_PIXELNET = wxNewId();
const long NetworkDialog::ID_BUTTON_ADD_E131 = wxNewId();
const long NetworkDialog::ID_GRID_NETWORK = wxNewId();
const long NetworkDialog::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(NetworkDialog,wxDialog)
	//(*EventTable(NetworkDialog)
	//*)
END_EVENT_TABLE()

NetworkDialog::NetworkDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(NetworkDialog)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer2;
	wxBoxSizer* BoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, _("Define Lighting Networks"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer2 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableRow(1);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	ButtonSave = new wxButton(Panel1, ID_BUTTON_SAVE, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SAVE"));
	BoxSizer1->Add(ButtonSave, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonNetClose = new wxButton(Panel1, ID_BUTTON_NETCLOSE, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_NETCLOSE"));
	BoxSizer1->Add(ButtonNetClose, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(BoxSizer1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Select a row by clicking on the row number"));
	ButtonEditRow = new wxButton(Panel1, ID_BUTTON_EDIT_ROW, _("Change"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_EDIT_ROW"));
	StaticBoxSizer1->Add(ButtonEditRow, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonDelRow = new wxButton(Panel1, ID_BUTTON_DELROW, _("Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_DELROW"));
	StaticBoxSizer1->Add(ButtonDelRow, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonMoveUp = new wxButton(Panel1, ID_BUTTON_MOVE_UP, _("Move Up"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_MOVE_UP"));
	StaticBoxSizer1->Add(ButtonMoveUp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonMoveDown = new wxButton(Panel1, ID_BUTTON_MOVE_DOWN, _("Move Down"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_MOVE_DOWN"));
	StaticBoxSizer1->Add(ButtonMoveDown, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Add a new lighting network"));
	ButtonAddLOR = new wxButton(Panel1, ID_BUTTON_ADD_LOR, _("LOR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ADD_LOR"));
	StaticBoxSizer2->Add(ButtonAddLOR, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonAddDLight = new wxButton(Panel1, ID_BUTTON_ADD_DLIGHT, _("D-Light"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ADD_DLIGHT"));
	StaticBoxSizer2->Add(ButtonAddDLight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonAddRenard = new wxButton(Panel1, ID_BUTTON_ADD_RENARD, _("Renard"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ADD_RENARD"));
	StaticBoxSizer2->Add(ButtonAddRenard, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonAddDMX = new wxButton(Panel1, ID_BUTTON_ADD_DMX, _("DMX Pro/Lynx"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ADD_DMX"));
	StaticBoxSizer2->Add(ButtonAddDMX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonAddOpenDMX = new wxButton(Panel1, ID_BUTTON_ADD_OPEN_DMX, _("Open DMX"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ADD_OPEN_DMX"));
	StaticBoxSizer2->Add(ButtonAddOpenDMX, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonAddPixelnet = new wxButton(Panel1, ID_BUTTON_ADD_PIXELNET, _("PixelNet Dongle"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ADD_PIXELNET"));
	StaticBoxSizer2->Add(ButtonAddPixelnet, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonAddE131 = new wxButton(Panel1, ID_BUTTON_ADD_E131, _("E1.31"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ADD_E131"));
	StaticBoxSizer2->Add(ButtonAddE131, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	GridNetwork = new wxGrid(Panel1, ID_GRID_NETWORK, wxDefaultPosition, wxSize(530,139), 0, _T("ID_GRID_NETWORK"));
	GridNetwork->CreateGrid(0,4);
	GridNetwork->EnableEditing(false);
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
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON_SAVE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonSaveClick);
	Connect(ID_BUTTON_NETCLOSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonNetCloseClick);
	Connect(ID_BUTTON_EDIT_ROW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonEditRowClick);
	Connect(ID_BUTTON_DELROW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonDelRowClick);
	Connect(ID_BUTTON_MOVE_UP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonMoveUpClick);
	Connect(ID_BUTTON_MOVE_DOWN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonMoveDownClick);
	Connect(ID_BUTTON_ADD_LOR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonAddLORClick);
	Connect(ID_BUTTON_ADD_DLIGHT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonAddDLightClick);
	Connect(ID_BUTTON_ADD_RENARD,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonAddRenardClick);
	Connect(ID_BUTTON_ADD_DMX,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonAddDMXClick);
	Connect(ID_BUTTON_ADD_OPEN_DMX,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonAddOpenDMXClick);
	Connect(ID_BUTTON_ADD_PIXELNET,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonAddPixelnetClick);
	Connect(ID_BUTTON_ADD_E131,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonAddE131Click);
	//*)

    GridNetwork->SetSelectionMode(wxGrid::wxGridSelectRows);
	GridNetwork->SetColLabelValue(2, _("Baud Rate or\nE1.31 Univ"));


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
}

NetworkDialog::~NetworkDialog()
{
    if (UnsavedChanges) {
        wxMessageDialog confirm(this, _("Save changes?"), _("Confirm"), wxYES|wxNO);
        if (confirm.ShowModal() == wxID_YES) {
            SaveFile();
        }
    }
	//(*Destroy(NetworkDialog)
	//*)
}

void NetworkDialog::LoadFile()
{
    wxXmlDocument doc;
    if (doc.Load( networkFile.GetFullPath() )) {
        int r=0;
        for( wxXmlNode* e=doc.GetRoot()->GetChildren(); e!=NULL; e=e->GetNext() ) {
            if (e->GetName() == _("network")) {
                GridNetwork->AppendRows(1);
                GridNetwork->SetCellValue(r,0,e->GetPropVal(wxT("NetworkType"), wxT("")));
                GridNetwork->SetCellValue(r,1,e->GetPropVal(wxT("ComPort"), wxT("")));
                GridNetwork->SetCellValue(r,2,e->GetPropVal(wxT("BaudRate"), wxT("")));
                GridNetwork->SetCellValue(r,3,e->GetPropVal(wxT("MaxChannels"), wxT("0")));
                r++;
            }
        }
        //if (r > 0) GridNetwork->AutoSizeColumns();
    } else {
        wxMessageBox(_("Unable to load network definition file"), _("Error"));
    }
}

void NetworkDialog::SaveFile()
{
    int RowCount;
    wxXmlNode* net;
    wxXmlDocument doc;
    wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("Networks") );
    root->AddProperty( wxT("computer"), wxGetHostName());
    doc.SetRoot( root );

    RowCount=GridNetwork->GetNumberRows();
    for (int r=0; r < RowCount; r++ ) {
        net = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("network") );
        net->AddProperty( wxT("NetworkType"), GridNetwork->GetCellValue(r,0));
        net->AddProperty( wxT("ComPort"), GridNetwork->GetCellValue(r,1));
        net->AddProperty( wxT("BaudRate"), GridNetwork->GetCellValue(r,2));
        net->AddProperty( wxT("MaxChannels"), GridNetwork->GetCellValue(r,3));
        root->AddChild( net );
    }
    wxString FileName=networkFile.GetFullPath();
    if (doc.Save( FileName )) {
        UnsavedChanges=false;
    } else {
        wxMessageBox(_("Unable to save network definition file"), _("Error"));
    }
}

void NetworkDialog::OnButtonSaveClick(wxCommandEvent& event)
{
    SaveFile();
    EndModal(1);
}

void NetworkDialog::OnButtonAddRowClick(wxCommandEvent& event)
{
    GridNetwork->AppendRows(1);
}

void NetworkDialog::OnButtonDelRowClick(wxCommandEvent& event)
{
    wxArrayInt selectedRows = GridNetwork->GetSelectedRows();
    int cnt = selectedRows.GetCount();
    if (cnt == 0) {
        wxMessageBox(_("You must select a row by clicking on the row number first!"), _("WARNING"));
    } else {
        for(int i = 0; i < cnt; i++)
        {
            GridNetwork->DeleteRows(selectedRows[i]);
        }
    }
}

void NetworkDialog::OnButtonNetCloseClick(wxCommandEvent& event)
{
    EndModal(0);
}

void NetworkDialog::MoveRowData(int fromRow, int toRow)
{
    int colcnt=GridNetwork->GetCols();
    for (int c=0; c < colcnt; c++)
    {
        GridNetwork->SetCellValue(toRow,c,GridNetwork->GetCellValue(fromRow,c));
    }
    GridNetwork->DeleteRows(fromRow);
}

void NetworkDialog::OnButtonMoveUpClick(wxCommandEvent& event)
{
    wxArrayInt selectedRows = GridNetwork->GetSelectedRows();
    int cnt = selectedRows.GetCount();
    if (cnt == 1) {
        int r=selectedRows[0];
        if (r > 0)
        {
            GridNetwork->InsertRows(r-1);
            MoveRowData(r+1,r-1);
            GridNetwork->SelectRow(r-1);
        }
    } else {
        wxMessageBox(_("You must select a row by clicking on the row number first!"), _("WARNING"));
    }
}

void NetworkDialog::OnButtonMoveDownClick(wxCommandEvent& event)
{
    wxArrayInt selectedRows = GridNetwork->GetSelectedRows();
    int cnt = selectedRows.GetCount();
    if (cnt == 1) {
        int r=selectedRows[0];
        int lastrow = GridNetwork->GetRows()-1;
        if (r < lastrow)
        {
            GridNetwork->InsertRows(r+2);
            MoveRowData(r,r+2);
            GridNetwork->SelectRow(r+1);
        }
    } else {
        wxMessageBox(_("You must select a row by clicking on the row number first!"), _("WARNING"));
    }
}

void NetworkDialog::OnButtonEditRowClick(wxCommandEvent& event)
{
    wxArrayInt selectedRows = GridNetwork->GetSelectedRows();
    int cnt = selectedRows.GetCount();
    if (cnt == 1) {
        int r=selectedRows[0];
        if (GridNetwork->GetCellValue(r,0) == wxT("E131")) {
            AddE131(r);
        } else {
            AddSerial(wxT(""), r);
        }
    } else {
        wxMessageBox(_("You must select a row by clicking on the row number first!"), _("WARNING"));
    }
}

bool NetworkDialog::EnableRate(const wxString& NetName)
{
    return (NetName!=wxT("DMX") && NetName!=wxT("OpenDMX") && NetName!=wxT("PixelNet"));
}

void NetworkDialog::AddSerial(wxString NetName, int r)
{
	int DlgResult;
	bool ok=true;
	wxString Port,BaudRate,LastChannel;
	wxString action=_("Add ");

	if (r >= 0)
	{
	    action=_("Change ");
        NetName=GridNetwork->GetCellValue(r,0);
        Port=GridNetwork->GetCellValue(r,1);
        BaudRate=GridNetwork->GetCellValue(r,2);
        LastChannel=GridNetwork->GetCellValue(r,3);
	}

	bool RateEnabled = EnableRate(NetName);
	wxString title = action + NetName + _(" Network");
	SerialPortWithRate SerialDlg(this,title);
	SerialDlg.ChoiceBaudRate->Enable(RateEnabled);
	if (r >= 0)
	{
        SerialDlg.ChoicePort->SetStringSelection(Port);
        if (RateEnabled) SerialDlg.ChoiceBaudRate->SetStringSelection(BaudRate);
        SerialDlg.TextCtrlLastChannel->SetValue(LastChannel);
	}
	do {
	    DlgResult=SerialDlg.ShowModal();
	    if (DlgResult == wxID_OK) {
            Port=SerialDlg.ChoicePort->GetStringSelection();
            BaudRate=SerialDlg.ChoiceBaudRate->GetStringSelection();
            LastChannel=SerialDlg.TextCtrlLastChannel->GetValue();
            ok=!Port.IsEmpty() && (!RateEnabled || !BaudRate.IsEmpty()) && !LastChannel.IsEmpty();
            if (ok) {
                if (r < 0)
                {
                    GridNetwork->AppendRows(1);
                    r=GridNetwork->GetRows()-1;
                }
                GridNetwork->SetCellValue(r,0,NetName);
                GridNetwork->SetCellValue(r,1,Port);
                if (NetName==wxT("OpenDMX"))
                    GridNetwork->SetCellValue(r,2,wxT("250000"));
                else if (RateEnabled)
                    GridNetwork->SetCellValue(r,2,BaudRate);
                else
                    GridNetwork->SetCellValue(r,2,_("n/a"));
                GridNetwork->SetCellValue(r,3,LastChannel);
                UnsavedChanges=true;
            } else {
                wxMessageBox(_("All fields must be filled in!"), _("ERROR"));
            }
	    }
	} while (DlgResult == wxID_OK && !ok);
}

void NetworkDialog::OnButtonAddLORClick(wxCommandEvent& event)
{
    AddSerial(wxT("LOR"));
}

void NetworkDialog::OnButtonAddDLightClick(wxCommandEvent& event)
{
    AddSerial(wxT("D-Light"));
}

void NetworkDialog::OnButtonAddRenardClick(wxCommandEvent& event)
{
    AddSerial(wxT("Renard"));
}

void NetworkDialog::OnButtonAddDMXClick(wxCommandEvent& event)
{
    AddSerial(wxT("DMX"));
}

void NetworkDialog::OnButtonAddPixelnetClick(wxCommandEvent& event)
{
    AddSerial(wxT("PixelNet"));
}

void NetworkDialog::AddE131(int r)
{
	int DlgResult;
	bool ok=true;
	wxString IpAddr,Universe,LastChannel;
	wxString action=_("Add ");
	wxString NetName=wxT("E131");

	if (r >= 0)
	{
	    action=_("Change ");
        //NetName=GridNetwork->GetCellValue(r,0);
        IpAddr=GridNetwork->GetCellValue(r,1);
        Universe=GridNetwork->GetCellValue(r,2);
        LastChannel=GridNetwork->GetCellValue(r,3);
	}

	wxString title = action + NetName + _(" Network");
	E131Dialog E131Dlg(this,title);
	if (r >= 0)
	{
        E131Dlg.TextCtrlIpAddr->SetValue(IpAddr);
        E131Dlg.TextCtrlUniverse->SetValue(Universe);
        E131Dlg.TextCtrlLastChannel->SetValue(LastChannel);
	}
	do {
	    DlgResult=E131Dlg.ShowModal();
	    if (DlgResult == wxID_OK) {
            IpAddr=E131Dlg.TextCtrlIpAddr->GetValue();
            Universe=E131Dlg.TextCtrlUniverse->GetValue();
            LastChannel=E131Dlg.TextCtrlLastChannel->GetValue();
            ok=!IpAddr.IsEmpty() && !Universe.IsEmpty() && !LastChannel.IsEmpty();
            if (ok) {
                if (r < 0)
                {
                    GridNetwork->AppendRows(1);
                    r=GridNetwork->GetRows()-1;
                }
                GridNetwork->SetCellValue(r,0,NetName);
                GridNetwork->SetCellValue(r,1,IpAddr);
                GridNetwork->SetCellValue(r,2,Universe);
                GridNetwork->SetCellValue(r,3,LastChannel);
                UnsavedChanges=true;
            } else {
                wxMessageBox(_("All fields must be filled in!"), _("ERROR"));
            }
	    }
	} while (DlgResult == wxID_OK && !ok);
}

void NetworkDialog::OnButtonAddE131Click(wxCommandEvent& event)
{
    AddE131();
}

void NetworkDialog::OnButtonAddOpenDMXClick(wxCommandEvent& event)
{
    AddSerial(wxT("OpenDMX"));
}
