#ifndef NETWORKDIALOG_H
#define NETWORKDIALOG_H

//(*Headers(NetworkDialog)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/stattext.h>
//*)

#include <wx/config.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/xml/xml.h>
#include "LorMapDialog.h"
#include "../include/globals.h"


class NetworkDialog: public wxDialog
{
	public:

		NetworkDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~NetworkDialog();
        bool UnsavedChanges;
        void SaveFile();

		//(*Declarations(NetworkDialog)
		wxButton* ButtonAddPixelnet;
		wxPanel* Panel1;
		wxButton* ButtonAddE131;
		wxButton* ButtonAddRenard;
		wxButton* ButtonMoveDown;
		wxButton* ButtonAddLOR;
		wxButton* ButtonLorMap;
		wxStaticText* StaticText1;
		wxButton* ButtonAddDLight;
		wxButton* ButtonEditRow;
		wxButton* ButtonDelRow;
		wxListCtrl* GridNetwork;
		wxButton* ButtonAddOpenDMX;
		wxButton* ButtonMoveUp;
		wxButton* ButtonAddDMX;
		//*)

	protected:

		//(*Identifiers(NetworkDialog)
		static const long ID_BUTTON_LOR_MAP;
		static const long ID_BUTTON_ADD_LOR;
		static const long ID_BUTTON_ADD_DLIGHT;
		static const long ID_BUTTON_ADD_RENARD;
		static const long ID_BUTTON_ADD_DMX;
		static const long ID_BUTTON_ADD_OPEN_DMX;
		static const long ID_BUTTON_ADD_PIXELNET;
		static const long ID_BUTTON_ADD_E131;
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON_EDIT_ROW;
		static const long ID_BUTTON_DELROW;
		static const long ID_BUTTON_MOVE_UP;
		static const long ID_BUTTON_MOVE_DOWN;
		static const long ID_LISTCTRL_NETWORKS;
		static const long ID_PANEL1;
		//*)

	private:

		//(*Handlers(NetworkDialog)
		void OnButtonSaveClick(wxCommandEvent& event);
		void OnButtonAddRowClick(wxCommandEvent& event);
		void OnButtonDelRowClick(wxCommandEvent& event);
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
		void OnButtonAddOpenDMXClick(wxCommandEvent& event);
		void OnButtonLorMapClick(wxCommandEvent& event);
		void OnGridNetworkBeginDrag(wxListEvent& event);
		//*)

        wxFileName networkFile;
        long LorMapping;
        long DragRowIdx;

        void LoadFile();
        void MoveRowData(int fromRow, int toRow);
        void AddSerial(wxString NetName, int r=-1);
        bool EnableRate(const wxString& NetName);
        void AddE131(int r=-1);
        long GetSelectedItem();
        void OnDragQuit(wxMouseEvent& event);
        void OnDragEnd(wxMouseEvent& event);

		DECLARE_EVENT_TABLE()
};

#endif
