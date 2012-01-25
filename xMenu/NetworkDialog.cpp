#include "NetworkDialog.h"

//(*InternalHeaders(NetworkDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/msgdlg.h>
#include "SerialPortWithRate.h"
#include "E131Dialog.h"


//(*IdInit(NetworkDialog)
const long NetworkDialog::ID_BUTTON_LOR_MAP = wxNewId();
const long NetworkDialog::ID_BUTTON_ADD_LOR = wxNewId();
const long NetworkDialog::ID_BUTTON_ADD_DLIGHT = wxNewId();
const long NetworkDialog::ID_BUTTON_ADD_RENARD = wxNewId();
const long NetworkDialog::ID_BUTTON_ADD_DMX = wxNewId();
const long NetworkDialog::ID_BUTTON_ADD_OPEN_DMX = wxNewId();
const long NetworkDialog::ID_BUTTON_ADD_PIXELNET = wxNewId();
const long NetworkDialog::ID_BUTTON_ADD_E131 = wxNewId();
const long NetworkDialog::ID_STATICTEXT1 = wxNewId();
const long NetworkDialog::ID_BUTTON_EDIT_ROW = wxNewId();
const long NetworkDialog::ID_BUTTON_DELROW = wxNewId();
const long NetworkDialog::ID_BUTTON_MOVE_UP = wxNewId();
const long NetworkDialog::ID_BUTTON_MOVE_DOWN = wxNewId();
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
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, wxID_ANY, _("Define Lighting Networks"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer2 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableRow(1);
	FlexGridSizer6 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer6->AddGrowableCol(0);
	FlexGridSizer6->AddGrowableRow(0);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(Panel1, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(Panel1, wxID_SAVE, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	FlexGridSizer6->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ButtonLorMap = new wxButton(Panel1, ID_BUTTON_LOR_MAP, _("LOR Sequence Channel Mapping"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LOR_MAP"));
	FlexGridSizer6->Add(ButtonLorMap, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(FlexGridSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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
	ButtonAddPixelnet = new wxButton(Panel1, ID_BUTTON_ADD_PIXELNET, _("Pixelnet Dongle"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ADD_PIXELNET"));
	StaticBoxSizer2->Add(ButtonAddPixelnet, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonAddE131 = new wxButton(Panel1, ID_BUTTON_ADD_E131, _("E1.31"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ADD_E131"));
	StaticBoxSizer2->Add(ButtonAddE131, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(1, 2, 0, 0);
	FlexGridSizer3->AddGrowableCol(1);
	FlexGridSizer3->AddGrowableRow(0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Row Commands"));
	FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Select a row by\nclicking on the\nrow number"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer4->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonEditRow = new wxButton(Panel1, ID_BUTTON_EDIT_ROW, _("Change"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_EDIT_ROW"));
	FlexGridSizer4->Add(ButtonEditRow, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonDelRow = new wxButton(Panel1, ID_BUTTON_DELROW, _("Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_DELROW"));
	FlexGridSizer4->Add(ButtonDelRow, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonMoveUp = new wxButton(Panel1, ID_BUTTON_MOVE_UP, _("Move Up"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_MOVE_UP"));
	FlexGridSizer4->Add(ButtonMoveUp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonMoveDown = new wxButton(Panel1, ID_BUTTON_MOVE_DOWN, _("Move Down"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_MOVE_DOWN"));
	FlexGridSizer4->Add(ButtonMoveDown, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer3->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridNetwork = new wxGrid(Panel1, ID_GRID_NETWORK, wxDefaultPosition, wxSize(592,203), 0, _T("ID_GRID_NETWORK"));
	GridNetwork->CreateGrid(0,4);
	GridNetwork->EnableEditing(false);
	GridNetwork->EnableGridLines(true);
	GridNetwork->SetRowLabelSize(50);
	GridNetwork->SetDefaultColSize(135, true);
	GridNetwork->SetColLabelValue(0, _("Network Type"));
	GridNetwork->SetColLabelValue(1, _("Port"));
	GridNetwork->SetColLabelValue(2, _("Baud Rate"));
	GridNetwork->SetColLabelValue(3, _("Last Channel"));
	GridNetwork->SetDefaultCellFont( GridNetwork->GetFont() );
	GridNetwork->SetDefaultCellTextColour( GridNetwork->GetForegroundColour() );
	FlexGridSizer3->Add(GridNetwork, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(FlexGridSizer3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(FlexGridSizer2);
	FlexGridSizer2->Fit(Panel1);
	FlexGridSizer2->SetSizeHints(Panel1);
	FlexGridSizer1->Add(Panel1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON_LOR_MAP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonLorMapClick);
	Connect(ID_BUTTON_ADD_LOR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonAddLORClick);
	Connect(ID_BUTTON_ADD_DLIGHT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonAddDLightClick);
	Connect(ID_BUTTON_ADD_RENARD,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonAddRenardClick);
	Connect(ID_BUTTON_ADD_DMX,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonAddDMXClick);
	Connect(ID_BUTTON_ADD_OPEN_DMX,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonAddOpenDMXClick);
	Connect(ID_BUTTON_ADD_PIXELNET,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonAddPixelnetClick);
	Connect(ID_BUTTON_ADD_E131,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonAddE131Click);
	Connect(ID_BUTTON_EDIT_ROW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonEditRowClick);
	Connect(ID_BUTTON_DELROW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonDelRowClick);
	Connect(ID_BUTTON_MOVE_UP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonMoveUpClick);
	Connect(ID_BUTTON_MOVE_DOWN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonMoveDownClick);
	//*)

    SetAffirmativeId(wxID_SAVE);
    GridNetwork->SetSelectionMode(wxGrid::wxGridSelectRows);
	GridNetwork->SetColLabelValue(2, _("Baud Rate or\nE1.31 Univ"));
    LorMapping = XLIGHTS_LORMAP_MULTI;

#ifdef __WXOSX__
    ButtonAddOpenDMX->Enable(false);
#endif

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
        wxXmlNode* e=doc.GetRoot();
        wxString LorMappingStr=e->GetPropVal(wxT("LorMapping"), wxT("2"));
        LorMappingStr.ToLong(&LorMapping);
        for( e=e->GetChildren(); e!=NULL; e=e->GetNext() ) {
            if (e->GetName() == wxT("network")) {
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
    wxString LorMappingStr;
    LorMappingStr.Printf(wxT("%d"),(int)LorMapping);
    wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("Networks") );
    root->AddProperty( wxT("computer"), wxGetHostName());
    root->AddProperty( wxT("LorMapping"), LorMappingStr);
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
    return (NetName!=wxT("DMX") && NetName!=wxT("OpenDMX") && NetName!=wxT("Pixelnet"));
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
	if (NetName == _("LOR")) {
	    SerialDlg.SetLabel(_("LOR controllers attached\nto any LOR dongle"));
	} else if (NetName == _("OpenDMX")) {
	    SerialDlg.SetLabel(_("DMX controllers (or LOR or D-Light controllers in DMX mode) attached\nto an LOR dongle, D-Light dongle,\nHolidayCoro programming cable,\nor Entec Open DMX dongle"));
	} else if (NetName == _("DMX")) {
	    SerialDlg.SetLabel(_("DMX controllers (or LOR or D-Light controllers in DMX mode) attached to an\nEntec DMX USB Pro, Lynx DMX dongle,\nDIYC RPM, or DMXking.com dongle"));
	} else if (NetName == _("Pixelnet")) {
	    SerialDlg.SetLabel(_("Pixelnet hub attached to a\nLynx Pixelnet dongle"));
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
    AddSerial(wxT("Pixelnet"));
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

void NetworkDialog::OnButtonLorMapClick(wxCommandEvent& event)
{
    long PreviousMapValue = LorMapping;
    LorMapDialog MapDlg(this);
    MapDlg.RadioButtonSingleNetwork->SetValue(LorMapping == XLIGHTS_LORMAP_SINGLE);
    MapDlg.RadioButtonMultiNetwork->SetValue(LorMapping == XLIGHTS_LORMAP_MULTI);
    MapDlg.RadioButtonStrictMap->SetValue(LorMapping == XLIGHTS_LORMAP_STRICT);
    if (MapDlg.ShowModal() > 0) {
        // ok was pressed
        if (MapDlg.RadioButtonSingleNetwork->GetValue()) LorMapping=XLIGHTS_LORMAP_SINGLE;
        if (MapDlg.RadioButtonMultiNetwork->GetValue()) LorMapping=XLIGHTS_LORMAP_MULTI;
        if (MapDlg.RadioButtonStrictMap->GetValue()) LorMapping=XLIGHTS_LORMAP_STRICT;
        if (LorMapping != PreviousMapValue) UnsavedChanges=true;
    }
}
