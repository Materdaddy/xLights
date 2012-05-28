#include "NetworkDialog.h"

//(*InternalHeaders(NetworkDialog)
#include <wx/string.h>
#include <wx/intl.h>
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
const long NetworkDialog::ID_LISTCTRL_NETWORKS = wxNewId();
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
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer6;
	wxFlexGridSizer* FlexGridSizer3;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;
	wxStaticBoxSizer* StaticBoxSizer1;

	Create(parent, wxID_ANY, _("Define Lighting Networks"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(1, 1, 0, 0);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer2 = new wxFlexGridSizer(3, 1, 0, 0);
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
	GridNetwork = new wxListCtrl(Panel1, ID_LISTCTRL_NETWORKS, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTCTRL_NETWORKS"));
	GridNetwork->SetToolTip(_("Drag an item to reorder the list"));
	FlexGridSizer3->Add(GridNetwork, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(FlexGridSizer3, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
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
	Connect(ID_LISTCTRL_NETWORKS,wxEVT_COMMAND_LIST_BEGIN_DRAG,(wxObjectEventFunction)&NetworkDialog::OnGridNetworkBeginDrag);
	//*)

    SetAffirmativeId(wxID_SAVE);
    LorMapping = XLIGHTS_LORMAP_MULTI;

    wxListItem itemCol;
    itemCol.SetText(_T("Network Type"));
    itemCol.SetImage(-1);
    GridNetwork->InsertColumn(0, itemCol);

    itemCol.SetText(_T("Port"));
    itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
    GridNetwork->InsertColumn(1, itemCol);

    itemCol.SetText(_T("Baud Rate or E1.31 Univ"));
    itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
    GridNetwork->InsertColumn(2, itemCol);

    itemCol.SetText(_T("Last Channel"));
    itemCol.SetAlign(wxLIST_FORMAT_CENTRE);
    GridNetwork->InsertColumn(3, itemCol);


#ifdef __WXOSX__
    ButtonAddOpenDMX->Enable(false);
	GridNetwork->SetToolTip(_(""));
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
        GridNetwork->SetColumnWidth(0,wxLIST_AUTOSIZE_USEHEADER);
        GridNetwork->SetColumnWidth(1,100);
        GridNetwork->SetColumnWidth(2,wxLIST_AUTOSIZE_USEHEADER);
        GridNetwork->SetColumnWidth(3,100);
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
    long newidx;
    wxXmlDocument doc;
    if (doc.Load( networkFile.GetFullPath() )) {
        int r=0;
        wxXmlNode* e=doc.GetRoot();
        wxString LorMappingStr=e->GetAttribute(wxT("LorMapping"), wxT("2"));
        LorMappingStr.ToLong(&LorMapping);
        for( e=e->GetChildren(); e!=NULL; e=e->GetNext() ) {
            if (e->GetName() == wxT("network")) {
                newidx = GridNetwork->InsertItem(GridNetwork->GetItemCount(), e->GetAttribute(wxT("NetworkType"), wxT("")));
                GridNetwork->SetItem(newidx,1,e->GetAttribute(wxT("ComPort"), wxT("")));
                GridNetwork->SetItem(newidx,2,e->GetAttribute(wxT("BaudRate"), wxT("")));
                GridNetwork->SetItem(newidx,3,e->GetAttribute(wxT("MaxChannels"), wxT("0")));
                GridNetwork->SetColumnWidth(0,wxLIST_AUTOSIZE);
                GridNetwork->SetColumnWidth(1,wxLIST_AUTOSIZE);
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
    wxString PropNames[4];
    wxXmlNode* net;
    wxXmlDocument doc;
    wxString LorMappingStr;
    LorMappingStr.Printf(wxT("%d"),(int)LorMapping);
    wxXmlNode* root = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("Networks") );
    root->AddAttribute( wxT("computer"), wxGetHostName());
    root->AddAttribute( wxT("LorMapping"), LorMappingStr);
    doc.SetRoot( root );
    PropNames[0]=wxT("NetworkType");
    PropNames[1]=wxT("ComPort");
    PropNames[2]=wxT("BaudRate");
    PropNames[3]=wxT("MaxChannels");

    RowCount=GridNetwork->GetItemCount();
    wxListItem listcol;
    for (int r=0; r < RowCount; r++ ) {
        net = new wxXmlNode( wxXML_ELEMENT_NODE, wxT("network") );
        net->AddAttribute( PropNames[0], GridNetwork->GetItemText(r));
        for (int c=1; c<4; c++) {
            listcol.SetId(r);
            listcol.SetColumn(c);
            listcol.SetMask(wxLIST_MASK_TEXT);
            GridNetwork->GetItem(listcol);
            net->AddAttribute( PropNames[c], listcol.GetText());
        }
        root->AddChild( net );
    }
    wxString FileName=networkFile.GetFullPath();
    if (doc.Save( FileName )) {
        UnsavedChanges=false;
    } else {
        wxMessageBox(_("Unable to save network definition file"), _("Error"));
    }
}

// returns -1 if not found
long NetworkDialog::GetSelectedItem()
{
    return GridNetwork->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
}

void NetworkDialog::OnButtonDelRowClick(wxCommandEvent& event)
{
    long SelectedItem = GetSelectedItem();
    if ( SelectedItem == -1 ) {
        wxMessageBox(_("You must select a row by clicking on the row number first!"), _("WARNING"));
    } else {
        GridNetwork->DeleteItem(SelectedItem);
        UnsavedChanges=true;
        int cnt=GridNetwork->GetItemCount();
        if (cnt > 0) {
            GridNetwork->SetItemState(cnt <= SelectedItem ? cnt-1 : SelectedItem, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
        }
    }
}

void NetworkDialog::MoveRowData(int fromRow, int toRow)
{
#define NETWORKDIALOG_COLS 4
#ifdef __WXOSX__
    // cannot use regular code because of wxWidgets ticket #4492
	wxArrayString ColText[NETWORKDIALOG_COLS];
    int rowcnt=GridNetwork->GetItemCount();
    wxListItem listcol;
	int r,c;
	// get text for all rows
	for (r=0; r < rowcnt; r++) {
		listcol.SetId(r);
		for (c=0; c < NETWORKDIALOG_COLS; c++)
		{
			listcol.SetColumn(c);
			listcol.SetMask(wxLIST_MASK_TEXT);
			GridNetwork->GetItem(listcol);
			ColText[c].Add(listcol.GetText());
		}
	}
	
	GridNetwork->DeleteAllItems();
	
	// update order
	for (c=0; c < NETWORKDIALOG_COLS; c++) {
	    ColText[c].Insert(ColText[c][fromRow],toRow);
	}
	for (c=0; c < NETWORKDIALOG_COLS; c++) {
	    ColText[c].RemoveAt(fromRow);
	}
	
	// add everything back in the new order
	for (r=0; r < rowcnt; r++) {
        GridNetwork->InsertItem(r,ColText[0][r]);
		for (c=1; c < NETWORKDIALOG_COLS; c++)
		{
			GridNetwork->SetItem(r,c,ColText[c][r]);
		}
	}
#else
    GridNetwork->InsertItem(toRow,wxT("new item"));
    wxListItem listcol;
    listcol.SetId(fromRow);
    for (int c=0; c < NETWORKDIALOG_COLS; c++)
    {
        listcol.SetColumn(c);
        listcol.SetMask(wxLIST_MASK_TEXT);
        GridNetwork->GetItem(listcol);
        GridNetwork->SetItem(toRow,c,listcol.GetText());
    }
    GridNetwork->DeleteItem(fromRow);
#endif
}

void NetworkDialog::OnButtonMoveUpClick(wxCommandEvent& event)
{
    long SelectedItem = GetSelectedItem();
    if (SelectedItem == -1) {
        wxMessageBox(_("Please select a single row first"), _("Error"));
        return;
    }
    if (SelectedItem == 0) return;
    MoveRowData(SelectedItem+1, SelectedItem-1);
    GridNetwork->SetItemState(SelectedItem-1,wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
}

void NetworkDialog::OnButtonMoveDownClick(wxCommandEvent& event)
{
    long SelectedItem = GetSelectedItem();
    if (SelectedItem == -1) {
        wxMessageBox(_("Please select a single row first"), _("Error"));
        return;
    }
    if (SelectedItem == GridNetwork->GetItemCount()-1) return;
    MoveRowData(SelectedItem, SelectedItem+2);
    GridNetwork->SetItemState(SelectedItem+1,wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
}

void NetworkDialog::OnButtonEditRowClick(wxCommandEvent& event)
{
    long SelectedItem = GetSelectedItem();
    if (SelectedItem == -1) {
        wxMessageBox(_("Please select a single row first"), _("Error"));
        return;
    }
    if (GridNetwork->GetItemText(SelectedItem) == wxT("E131")) {
        AddE131(SelectedItem);
    } else {
        AddSerial(wxT(""), SelectedItem);
    }
}

bool NetworkDialog::EnableRate(const wxString& NetName)
{
    return (NetName!=wxT("DMX") && NetName!=wxT("OpenDMX") && NetName!=wxT("Pixelnet"));
}

void NetworkDialog::AddSerial(wxString NetName, int r)
{
    wxListItem listcol;
	int DlgResult;
	bool ok=true;
	wxString Port,BaudRate,LastChannel;
	wxString action=_("Add ");

	if (r >= 0)
	{
	    action=_("Change ");
        listcol.SetId(r);
        listcol.SetMask(wxLIST_MASK_TEXT);
        NetName=GridNetwork->GetItemText(r);
        listcol.SetColumn(1);
        GridNetwork->GetItem(listcol);
        Port=listcol.GetText();
        listcol.SetColumn(2);
        GridNetwork->GetItem(listcol);
        BaudRate=listcol.GetText();
        listcol.SetColumn(3);
        GridNetwork->GetItem(listcol);
        LastChannel=listcol.GetText();
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
	} else if (NetName == _("D-Light")) {
	    SerialDlg.SetLabel(_("D-Light controllers attached\nto a D-Light dongle"));
	} else if (NetName == _("Renard")) {
	    SerialDlg.SetLabel(_("Renard controllers connected\nto a serial port or a USB dongle\nwith virtual comm port.\n2 stop bits are set automatically."));
	} else if (NetName == _("OpenDMX")) {
	    SerialDlg.SetLabel(_("DMX controllers (or LOR or D-Light controllers in DMX mode)\nattached to an LOR dongle, D-Light dongle, HolidayCoro\nprogramming cable, or Entec Open DMX dongle"));
	} else if (NetName == _("DMX")) {
	    SerialDlg.SetLabel(_("DMX controllers (or LOR or D-Light controllers in DMX mode)\nattached to an Entec DMX USB Pro, Lynx DMX dongle,\nDIYC RPM, DMXking.com, or DIY Blinky dongle.\n\nLast Channel should be 512 or less, unless you are using\na DIY Blinky dongle (in which case it can be up to 3036)."));
	} else if (NetName == _("Pixelnet")) {
	    SerialDlg.SetLabel(_("Pixelnet hub attached to a\nLynx Pixelnet dongle"));
	}
	do {
	    DlgResult=SerialDlg.ShowModal();
	    if (DlgResult == wxID_OK) {
            ok=false;
            Port=SerialDlg.ChoicePort->GetStringSelection();
            BaudRate=SerialDlg.ChoiceBaudRate->GetStringSelection();
            LastChannel=SerialDlg.TextCtrlLastChannel->GetValue();
            if (Port.IsEmpty() || (RateEnabled && BaudRate.IsEmpty()) || LastChannel.IsEmpty()) {
                wxMessageBox(_("All fields must be filled in!"), _("ERROR"));
            } else if (!LastChannel.IsNumber() || LastChannel[0]=='-') {
                wxMessageBox(_("Last Channel must be a positive number!"), _("ERROR"));
            } else {
                if (r < 0)
                {
                    r=GridNetwork->GetItemCount();
                    GridNetwork->InsertItem(r,wxT(""));
                }
                GridNetwork->SetItem(r,0,NetName);
                GridNetwork->SetItem(r,1,Port);
                if (NetName==wxT("OpenDMX"))
                    GridNetwork->SetItem(r,2,wxT("250000"));
                else if (RateEnabled)
                    GridNetwork->SetItem(r,2,BaudRate);
                else
                    GridNetwork->SetItem(r,2,_("n/a"));
                GridNetwork->SetItem(r,3,LastChannel);
                UnsavedChanges=true;
                ok=true;
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
    wxListItem listcol;
	int DlgResult,UnivNum;
	bool ok=true;
	int NumUniv;
	wxString IpAddr,StartUniverse,LastChannel;
	wxString action=_("Add ");
	wxString NetName=wxT("E131");

	if (r >= 0)
	{
	    action=_("Change ");
        listcol.SetId(r);
        listcol.SetMask(wxLIST_MASK_TEXT);
        listcol.SetColumn(1);
        GridNetwork->GetItem(listcol);
        IpAddr=listcol.GetText();
        listcol.SetColumn(2);
        GridNetwork->GetItem(listcol);
        StartUniverse=listcol.GetText();
        listcol.SetColumn(3);
        GridNetwork->GetItem(listcol);
        LastChannel=listcol.GetText();
        //LastChannel.ToLong(&NumUniv);
        //NumUniv=(NumUniv + 511) / 512; // round up
	}

	wxString title = action + NetName + _(" Network");
	E131Dialog E131Dlg(this,title);
	if (r >= 0)
	{
        E131Dlg.SpinCtrl_StartUniv->SetValue(StartUniverse);
        E131Dlg.SpinCtrl_NumUniv->SetValue(1);
        E131Dlg.SpinCtrl_NumUniv->Enable(false);

        if (IpAddr.StartsWith( wxT("239.255.") ) || IpAddr == wxT("MULTICAST")) {
            E131Dlg.TextCtrlIpAddr->SetValue(wxT("MULTICAST"));
            E131Dlg.TextCtrlIpAddr->Enable(false);
            E131Dlg.RadioButtonMulticast->SetValue(true);
        } else {
            E131Dlg.TextCtrlIpAddr->SetValue(IpAddr);
            E131Dlg.TextCtrlIpAddr->Enable(true);
            E131Dlg.RadioButtonUnicast->SetValue(true);
        }
	}
	do {
	    DlgResult=E131Dlg.ShowModal();
	    if (DlgResult == wxID_OK) {
            IpAddr=E131Dlg.TextCtrlIpAddr->GetValue();
            UnivNum = E131Dlg.SpinCtrl_StartUniv->GetValue();
            LastChannel = wxT("512");
            //LastChannel = wxString::Format(wxT("%d"), E131Dlg.SpinCtrl_NumUniv->GetValue() * 512);
            ok=!IpAddr.IsEmpty() && !LastChannel.IsEmpty();
            if (ok) {
                NumUniv = E131Dlg.SpinCtrl_NumUniv->GetValue();
                for (int u=0; u < NumUniv; u++) {
                    if (action == _("Add "))
                    {
                        r=GridNetwork->GetItemCount();
                        GridNetwork->InsertItem(r,wxT(""));
                    }
                    GridNetwork->SetItem(r,0,NetName);
                    GridNetwork->SetItem(r,1,IpAddr);
                    GridNetwork->SetItem(r,2,wxString::Format(wxT("%d"),UnivNum));
                    GridNetwork->SetItem(r,3,LastChannel);
                    UnivNum++;
                }
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


// drop a list item (start row is in DragRowIdx)
void NetworkDialog::OnDragEnd(wxMouseEvent& event)
{
  wxPoint pos = event.GetPosition();  // must reference the event
  int flags = wxLIST_HITTEST_ONITEM;
  long index = GridNetwork->HitTest(pos,flags,NULL); // got to use it at last
  if(index >= 0){
    if (index > DragRowIdx) {
        // moving down
        MoveRowData(DragRowIdx, index+1);
        UnsavedChanges=true;
    } else if (index < DragRowIdx) {
        // moving up
        MoveRowData(DragRowIdx+1, index);
        UnsavedChanges=true;
    }
  }
  // restore cursor
  GridNetwork->SetCursor(wxCursor(*wxSTANDARD_CURSOR));
  // disconnect both functions
  GridNetwork->Disconnect(wxEVT_LEFT_UP,
    wxMouseEventHandler(NetworkDialog::OnDragEnd));
  GridNetwork->Disconnect(wxEVT_LEAVE_WINDOW,
    wxMouseEventHandler(NetworkDialog::OnDragQuit));
}

// abort dragging a list item because user has left window
void NetworkDialog::OnDragQuit(wxMouseEvent& event)
{
  // restore cursor and disconnect unconditionally
  GridNetwork->SetCursor(wxCursor(*wxSTANDARD_CURSOR));
  GridNetwork->Disconnect(wxEVT_LEFT_UP,
    wxMouseEventHandler(NetworkDialog::OnDragEnd));
  GridNetwork->Disconnect(wxEVT_LEAVE_WINDOW,
    wxMouseEventHandler(NetworkDialog::OnDragQuit));
}

void NetworkDialog::OnGridNetworkBeginDrag(wxListEvent& event)
{
  DragRowIdx = event.GetIndex();	// save the start index
  // do some checks here to make sure valid start
  // ...
  // trigger when user releases left button (drop)
  GridNetwork->Connect(wxEVT_LEFT_UP,
    wxMouseEventHandler(NetworkDialog::OnDragEnd), NULL,this);
  // trigger when user leaves window to abort drag
  GridNetwork->Connect(wxEVT_LEAVE_WINDOW,
    wxMouseEventHandler(NetworkDialog::OnDragQuit), NULL,this);
  // give visual feedback that we are doing something
  GridNetwork->SetCursor(wxCursor(wxCURSOR_HAND));
}
