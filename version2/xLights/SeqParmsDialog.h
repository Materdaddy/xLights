#ifndef SEQPARMSDIALOG_H
#define SEQPARMSDIALOG_H

//(*Headers(SeqParmsDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checklst.h>
#include <wx/spinctrl.h>
#include <wx/dialog.h>
//*)

#include "NetInfo.h"


class SeqParmsDialog: public wxDialog
{
	public:

		SeqParmsDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~SeqParmsDialog();
		void SetNetInfo(NetInfoClass* NetInfoPtr);

		//(*Declarations(SeqParmsDialog)
		wxStaticText* StaticText10;
		wxSpinCtrl* SpinCtrlBaseChannel;
		wxStaticText* StaticText_CH10;
		wxStaticText* StaticText20;
		wxStaticText* StaticText29;
		wxStaticText* StaticText33;
		wxStaticText* StaticText2;
		wxStaticText* StaticText_CH15;
		wxStaticText* StaticText_CH5;
		wxStaticText* StaticText_CH8;
		wxStaticText* StaticText6;
		wxStaticText* StaticText19;
		wxStaticText* StaticText_CH6;
		wxStaticText* StaticText8;
		wxStaticText* StaticText_CH2;
		wxStaticText* StaticText_CH4;
		wxCheckListBox* CheckListBox1;
		wxStaticText* StaticText31;
		wxStaticText* StaticText1;
		wxStaticText* StaticText27;
		wxStaticText* StaticText_CH1;
		wxStaticText* StaticText_CH9;
		wxStaticText* StaticText_CH16;
		wxStaticText* StaticText21;
		wxStaticText* StaticText_CH14;
		wxStaticText* StaticText_CH0;
		wxStaticText* StaticText5;
		wxStaticText* StaticText_CH12;
		wxStaticText* StaticText_Filename;
		wxStaticText* StaticText15;
		wxStaticText* StaticText_CH13;
		wxStaticText* StaticText12;
		wxStaticText* StaticText_CH11;
		wxStaticText* StaticText25;
		wxStaticText* StaticText17;
		wxStaticText* StaticText4;
		wxStaticText* StaticText_CH7;
		wxStaticText* StaticText_CH3;
		//*)

	protected:

		//(*Identifiers(SeqParmsDialog)
		static const long ID_STATICTEXT_FILENAME;
		static const long ID_CHECKLISTBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_SPINCTRL_BASE_CHANNEL;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT_CH0;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT_CH1;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT_CH2;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT_CH3;
		static const long ID_STATICTEXT21;
		static const long ID_STATICTEXT_CH4;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT_CH5;
		static const long ID_STATICTEXT10;
		static const long ID_STATICTEXT_CH6;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT_CH7;
		static const long ID_STATICTEXT15;
		static const long ID_STATICTEXT_CH8;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT_CH9;
		static const long ID_STATICTEXT19;
		static const long ID_STATICTEXT_CH10;
		static const long ID_STATICTEXT20;
		static const long ID_STATICTEXT_CH11;
		static const long ID_STATICTEXT25;
		static const long ID_STATICTEXT_CH12;
		static const long ID_STATICTEXT27;
		static const long ID_STATICTEXT_CH13;
		static const long ID_STATICTEXT29;
		static const long ID_STATICTEXT_CH14;
		static const long ID_STATICTEXT31;
		static const long ID_STATICTEXT_CH15;
		static const long ID_STATICTEXT33;
		static const long ID_STATICTEXT_CH16;
		//*)

	private:

		//(*Handlers(SeqParmsDialog)
		void OnSpinCtrlBaseChannelChange(wxSpinEvent& event);
		//*)

        void SetChannelNames();
        NetInfoClass* NetInfo;

		DECLARE_EVENT_TABLE()
};

#endif
