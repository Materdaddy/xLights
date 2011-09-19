#ifndef NETWORKDIALOG_H
#define NETWORKDIALOG_H

//(*Headers(NetworkDialog)
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#include <wx/config.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/xml/xml.h>
#include "../include/globals.h"


class NetworkDialog: public wxDialog
{
	public:

		NetworkDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~NetworkDialog();

		//(*Declarations(NetworkDialog)
		wxButton* ButtonMoveUp;
		wxButton* ButtonAddE131;
		wxButton* ButtonAddDLight;
		wxButton* ButtonNetClose;
		wxButton* ButtonAddRenard;
		wxButton* ButtonAddDMX;
		wxButton* ButtonMoveDown;
		wxPanel* Panel1;
		wxGrid* GridNetwork;
		wxButton* ButtonAddLOR;
		wxButton* ButtonSave;
		wxButton* ButtonAddPixelnet;
		wxButton* ButtonDelRow;
		wxButton* ButtonEditRow;
		//*)

	protected:

		//(*Identifiers(NetworkDialog)
		static const long ID_BUTTON_SAVE;
		static const long ID_BUTTON_NETCLOSE;
		static const long ID_BUTTON_EDIT_ROW;
		static const long ID_BUTTON_DELROW;
		static const long ID_BUTTON_MOVE_UP;
		static const long ID_BUTTON_MOVE_DOWN;
		static const long ID_BUTTON_ADD_LOR;
		static const long ID_BUTTON_ADD_DLIGHT;
		static const long ID_BUTTON_ADD_RENARD;
		static const long ID_BUTTON_ADD_DMX;
		static const long ID_BUTTON_ADD_PIXELNET;
		static const long ID_BUTTON_ADD_E131;
		static const long ID_GRID_NETWORK;
		static const long ID_PANEL1;
		//*)

	private:

		//(*Handlers(NetworkDialog)
		void OnButtonSaveClick(wxCommandEvent& event);
		void OnButtonAddRowClick(wxCommandEvent& event);
		void OnButtonDelRowClick(wxCommandEvent& event);
		void OnGridNetworkEditorShown(wxGridEvent& event);
		void OnGridNetworkCellLeftClick(wxGridEvent& event);
		void OnButtonNetCloseClick(wxCommandEvent& event);
		void OnButtonMoveUpClick(wxCommandEvent& event);
		void OnButtonMoveDownClick(wxCommandEvent& event);
		void OnButtonEditRowClick(wxCommandEvent& event);
		void OnButtonAddLORClick(wxCommandEvent& event);
		void OnButtonAddDLightClick(wxCommandEvent& event);
		void OnButtonAddRenardClick(wxCommandEvent& event);
		void OnButtonAddDMXClick(wxCommandEvent& event);
		void OnButtonAddPixelnetClick(wxCommandEvent& event);
		void OnButtonAddE131Click(wxCommandEvent& event);
		//*)

        wxFileName networkFile;
        bool UnsavedChanges;

        void SaveFile();
        void LoadFile();
        void MoveRowData(int fromRow, int toRow);
        void AddSerial(wxString NetName, int r=-1);
        bool EnableRate(const wxString& NetName);
        void AddE131(int r=-1);

		DECLARE_EVENT_TABLE()
};

#endif
