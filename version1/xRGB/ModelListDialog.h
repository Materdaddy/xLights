#ifndef MODELLISTDIALOG_H
#define MODELLISTDIALOG_H

//(*Headers(ModelListDialog)
#include <wx/sizer.h>
#include <wx/listbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#include <wx/html/htmprint.h>
#include "ModelClass.h"

class ModelListDialog: public wxDialog
{
	public:

		ModelListDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ModelListDialog();

        wxHtmlEasyPrinting* HtmlEasyPrint;

		//(*Declarations(ModelListDialog)
		wxButton* Button_Modify;
		wxButton* Button_Layout;
		wxButton* Button_Delete;
		wxButton* Button_New;
		wxButton* Button_Rename;
		wxListBox* ListBox1;
		//*)

	protected:

		//(*Identifiers(ModelListDialog)
		static const long ID_LISTBOX1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_BUTTON2;
		static const long ID_BUTTON_LAYOUT;
		//*)

	private:

		//(*Handlers(ModelListDialog)
		void OnButton_NewClick(wxCommandEvent& event);
		void OnButton_ModifyClick(wxCommandEvent& event);
		void OnButton_DeleteClick(wxCommandEvent& event);
		void OnButton_RenameClick(wxCommandEvent& event);
		void OnButton_LayoutClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
