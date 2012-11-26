#ifndef PALETTEMGMTDIALOG_H
#define PALETTEMGMTDIALOG_H

//(*Headers(PaletteMgmtDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/listbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#include <wx/xml/xml.h>
#include <wx/msgdlg.h>
#include <wx/textdlg.h>

class PaletteMgmtDialog: public wxDialog
{
	public:

		PaletteMgmtDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~PaletteMgmtDialog();
        void initialize(const wxString& id1, const wxString& id2, wxXmlNode* PalNode, wxSizer* PriSizer,wxSizer* SecSizer);


		//(*Declarations(PaletteMgmtDialog)
		wxButton* ButtonChangeOrder;
		wxStaticText* StaticText14;
		wxStaticText* StaticText1;
		wxButton* ButtonLoadPalette1;
		wxButton* ButtonLoadPaletteBoth;
		wxButton* ButtonSavePalette;
		wxButton* ButtonDelete;
		wxButton* ButtonCopy;
		wxListBox* ListBox1;
		//*)

	protected:

		//(*Identifiers(PaletteMgmtDialog)
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT1;
		static const long ID_LISTBOX1;
		static const long ID_BUTTON5;
		static const long ID_BUTTON4;
		static const long ID_BUTTON3;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON6;
		//*)

	private:

		//(*Handlers(PaletteMgmtDialog)
		void OnButtonSavePaletteClick(wxCommandEvent& event);
		void OnButtonLoadPalette1Click(wxCommandEvent& event);
		void OnButtonLoadPaletteBothClick(wxCommandEvent& event);
		void OnButtonCopyClick(wxCommandEvent& event);
		void OnButtonChangeOrderClick(wxCommandEvent& event);
		void OnButtonDeleteClick(wxCommandEvent& event);
		//*)

        void ReloadPaletteList();
        void LoadPalette(wxXmlNode* PaletteNode, wxSizer* Sizer);

		wxSizer* PrimarySizer;
		wxSizer* SecondarySizer;
		wxString PrimaryId;
		wxString SecondaryId;
		wxXmlNode* PalettesNode;

		DECLARE_EVENT_TABLE()
};

#endif
