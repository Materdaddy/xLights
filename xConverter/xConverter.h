#ifndef XCONVERTER_H
#define XCONVERTER_H

//(*Headers(xConverter)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/filedlg.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/frame.h>
//*)

#include <wx/xml/xml.h>
#include <wx/filename.h>
#include <vector>
#include "../include/globals.h"

class xConverter: public wxFrame
{
	public:

		xConverter(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~xConverter();

		//(*Declarations(xConverter)
		wxTextCtrl* TextCtrlFilename;
		wxTextCtrl* TextCtrlStatus;
		wxStaticText* StaticText2;
		wxChoice* ChoiceOutputFormat;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxFileDialog* FileDialog1;
		wxStaticText* StaticText3;
		wxButton* ButtonStart;
		wxButton* ButtonChooseFile;
		//*)

	protected:

		//(*Identifiers(xConverter)
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL_FILENAME;
		static const long ID_BUTTON_CHOOSE_FILE;
		static const long ID_STATICTEXT3;
		static const long ID_CHOICE_OUTPUT_FORMAT;
		static const long ID_BUTTON_START;
		static const long ID_TEXTCTRL_STATUS;
		static const long ID_PANEL1;
		//*)

	private:

		//(*Handlers(xConverter)
		void OnButtonChooseFileClick(wxCommandEvent& event);
		void OnButtonStartClick(wxCommandEvent& event);
		//*)

        void LoadNetworkFile();
        wxFileName networkFile;
        bool LoadVixenProfile(const wxString& ProfileName);
        void ReadVixFile(const char* filename);
        void ReadLorFile(const char* filename);
        int GetLorTrack1Length(const char* filename);
        void WriteVixenFile(const wxString& filename);
        void WriteXLightsFile(const wxString& filename);
        void WriteConductorFile(const wxString& filename);
        void DoConversion();
        void ConversionError(const wxString& msg);
        wxString base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
        std::string base64_decode(const wxString& encoded_string);
        double rand01();

        wxString CurrentDir;
        wxString mediaFilename;
        long LorMapping;
        wxUint8 * SeqData;
        long SeqDataLen;
        long SeqNumPeriods;
        int SeqNumChannels;
        int TotChannels;
        wxArrayString ChannelNames;
        wxArrayInt ChannelColors;
        std::vector<int> VixChannels;
        std::vector<int> NetMaxChannel;

		DECLARE_EVENT_TABLE()
};

#endif
