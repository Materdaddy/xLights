#include "NetworkDialog.h"

//(*InternalHeaders(NetworkDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/msgdlg.h>


//(*IdInit(NetworkDialog)
const long NetworkDialog::ID_BUTTON_SAVE = wxNewId();
const long NetworkDialog::ID_BUTTON_ADDROW = wxNewId();
const long NetworkDialog::ID_BUTTON_DELROW = wxNewId();
const long NetworkDialog::ID_BUTTON_NETCLOSE = wxNewId();
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
	wxFlexGridSizer* FlexGridSizer2;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("Define Lighting Networks"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
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
	ButtonNetClose = new wxButton(Panel1, ID_BUTTON_NETCLOSE, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_NETCLOSE"));
	BoxSizer1->Add(ButtonNetClose, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON_SAVE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonSaveClick);
	Connect(ID_BUTTON_ADDROW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonAddRowClick);
	Connect(ID_BUTTON_DELROW,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonDelRowClick);
	Connect(ID_BUTTON_NETCLOSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NetworkDialog::OnButtonNetCloseClick);
	Connect(ID_GRID_NETWORK,wxEVT_GRID_EDITOR_SHOWN,(wxObjectEventFunction)&NetworkDialog::OnGridNetworkEditorShown);
	//*)

    wxArrayString types;
    types.Add(_("DMX-Entec Pro/Lynx"));
    types.Add(_("LOR/D-Light"));
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
    } else {
        GridNetwork->AppendRows(1);
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

void NetworkDialog::OnGridNetworkEditorShown(wxGridEvent& event)
{
    UnsavedChanges=true;
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
        if (r > 0) GridNetwork->AutoSizeColumns();
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
    for(size_t i = 0; i < selectedRows.GetCount(); i++)
    {
        GridNetwork->DeleteRows(selectedRows[i]);
    }
}

void NetworkDialog::PopulatePortChooser(wxArrayString *chooser)
{
#ifdef __WXMSW__
  // Windows
  chooser->Add(wxT("COM1"));
  chooser->Add(wxT("COM2"));
  chooser->Add(wxT("COM3"));
  chooser->Add(wxT("COM4"));
  chooser->Add(wxT("COM5"));
  chooser->Add(wxT("COM6"));
  chooser->Add(wxT("COM7"));
  chooser->Add(wxT("COM8"));
  chooser->Add(wxT("COM9"));
  chooser->Add(wxT("\\\\.\\COM10"));
  chooser->Add(wxT("\\\\.\\COM11"));
  chooser->Add(wxT("\\\\.\\COM12"));
  chooser->Add(wxT("\\\\.\\COM13"));
  chooser->Add(wxT("\\\\.\\COM14"));
  chooser->Add(wxT("\\\\.\\COM15"));
  chooser->Add(wxT("\\\\.\\COM16"));
  chooser->Add(wxT("\\\\.\\COM17"));
  chooser->Add(wxT("\\\\.\\COM18"));
  chooser->Add(wxT("\\\\.\\COM19"));
  chooser->Add(wxT("\\\\.\\COM20"));
#elif __WXMAC__
  // no standard device names for USB-serial converters on OS/X
  // scan /dev directory for candidates
  wxArrayString output,errors;
  wxExecute(wxT("ls -1 /dev"), output, errors, wxEXEC_SYNC);
  if (!errors.IsEmpty()) {
    wxMessageBox(errors.Last(), _("Error"));
  } else if (output.IsEmpty()) {
    wxMessageBox(_("no devices found"), _("Error"));
  } else {
    for (int i=0; i<output.Count(); i++) {
      if (output[i].StartsWith(wxT("cu."))) {
         chooser->Add(wxT("/dev/") + output[i]);
      }
    }
  }
#else
  // Linux
  chooser->Add(wxT("/dev/ttyS0"));
  chooser->Add(wxT("/dev/ttyS1"));
  chooser->Add(wxT("/dev/ttyS2"));
  chooser->Add(wxT("/dev/ttyS3"));
  chooser->Add(wxT("/dev/ttyUSB0"));
  chooser->Add(wxT("/dev/ttyUSB1"));
  chooser->Add(wxT("/dev/ttyUSB2"));
  chooser->Add(wxT("/dev/ttyUSB3"));
  chooser->Add(wxT("/dev/ttyUSB4"));
  chooser->Add(wxT("/dev/ttyUSB5"));
#endif
}

void NetworkDialog::OnButtonNetCloseClick(wxCommandEvent& event)
{
    EndModal(0);
}
