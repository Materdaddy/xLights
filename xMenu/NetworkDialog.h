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
#include "../include/globals.h"
#include "../include/tinyxml.h"


class NetworkDialog: public wxDialog
{
	public:

		NetworkDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~NetworkDialog();

		//(*Declarations(NetworkDialog)
		wxPanel* Panel1;
		wxGrid* GridNetwork;
		wxButton* ButtonSave;
		wxButton* ButtonAddRow;
		wxButton* ButtonDelRow;
		//*)

	protected:

		//(*Identifiers(NetworkDialog)
		static const long ID_BUTTON_SAVE;
		static const long ID_BUTTON_ADDROW;
		static const long ID_BUTTON_DELROW;
		static const long ID_GRID_NETWORK;
		static const long ID_PANEL1;
		//*)

	private:

		//(*Handlers(NetworkDialog)
		void OnButtonSaveClick(wxCommandEvent& event);
		void OnButtonAddRowClick(wxCommandEvent& event);
		void OnButtonDelRowClick(wxCommandEvent& event);
		void OnGridNetworkEditorShown(wxGridEvent& event);
		//*)

        wxFileName networkFile;
        bool UnsavedChanges;

        void SaveFile();
        void LoadFile();
        void LoadNetwork(TiXmlElement* n);
        wxString GetAttribute(TiXmlElement* e, const char *attr);
        void SetAttribute(TiXmlElement* e, std::string name, wxString v);
        void PopulatePortChooser(wxArrayString *chooser);

		DECLARE_EVENT_TABLE()
};

#endif
