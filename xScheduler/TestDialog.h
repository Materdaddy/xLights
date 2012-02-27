#ifndef TESTDIALOG_H
#define TESTDIALOG_H

//(*Headers(TestDialog)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/radiobut.h>
#include <wx/panel.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/choice.h>
//*)

#include <wx/checklst.h>


class NetworkInfo
{
    public:

    wxPanel* Panel;
    wxCheckListBox* ListBox;
    wxStaticText* DescField;
    wxString NetworkType;
    wxString ComPort;
    wxString BaudRate;
    int MaxChannels;

    const wxString Description() {
        if (NetworkType.IsEmpty()) {
            return _("");
        } else if (NetworkType == wxT("E131")) {
            return NetworkType+_("\n")+ComPort+_("\nUniv #")+BaudRate;
        } else {
            return NetworkType+_("\n")+ComPort+_("\n")+BaudRate+_(" baud");
        }
    }

    wxString net3() {
        return NetworkType.Left(3);
    }

    bool IsDMX() {
        return net3() ==_("DMX");
    }
};

class TestDialog: public wxDialog
{
	public:

		TestDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~TestDialog();

        void AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels);
        int GetNetIdx();
        int GetTestIdx();
        void GetCheckedItems(int netidx, wxArrayInt& chArray);
        void RadioButtonsOff();
        int ChaseSpeed();
        int BgIntensity();
        int FgIntensity();
        int RgbChaseSpeed();
        int BgColorA();
        int BgColorB();
        int BgColorC();
        int FgColorA();
        int FgColorB();
        int FgColorC();
        int RgbCycleSpeed();

        bool CheckChannelList;
        int ChaseGrouping;
        int TwinkleRatio;
        enum TestFunctions {
            OFF,
            CHASE,
            CHASE2,
            CHASE3,
            CHASE4,
            DIM,
            TWINKLE,
            SHIMMER
        } TestFunc;

		//(*Declarations(TestDialog)
		wxRadioButton* RadioButtonTwinkle50;
		wxRadioButton* RadioButtonAlt;
		wxRadioButton* RadioButtonRgbChase;
		wxSlider* SliderBgColorC;
		wxRadioButton* RadioButtonRgbChaseOff;
		wxStaticText* StaticText13;
		wxRadioButton* RadioButtonRgbCycle3;
		wxButton* ButtonClose;
		wxSlider* SliderFgColorC;
		wxButton* ButtonClear;
		wxRadioButton* RadioButtonRgbTwinkle05;
		wxRadioButton* RadioButtonRgbCycleOff;
		wxRadioButton* RadioButtonRgbCycleMixed;
		wxRadioButton* RadioButtonRgbShimmer;
		wxRadioButton* RadioButtonRgbTwinkle10;
		wxRadioButton* RadioButtonRgbAlt;
		wxRadioButton* RadioButtonTwinkle10;
		wxSlider* SliderBgColorA;
		wxSlider* SliderFgIntensity;
		wxSlider* SliderFgColorA;
		wxRadioButton* RadioButtonRgbCycle4;
		wxRadioButton* RadioButtonRgbTwinkle50;
		wxRadioButton* RadioButtonOff;
		wxRadioButton* RadioButtonChase3;
		wxRadioButton* RadioButtonChase;
		wxPanel* Panel_RGB;
		wxStaticText* StaticText1;
		wxStaticText* StaticText10;
		wxRadioButton* RadioButtonRgbDim;
		wxStaticText* StaticText3;
		wxRadioButton* RadioButtonTwinkle05;
		wxSlider* SliderChaseSpeed;
		wxRadioButton* RadioButtonShimmer;
		wxRadioButton* RadioButtonTwinkle25;
		wxRadioButton* RadioButtonRgbChase3;
		wxRadioButton* RadioButtonChase5;
		wxStaticText* StaticText8;
		wxButton* ButtonExport;
		wxPanel* Panel3;
		wxRadioButton* RadioButtonChase4;
		wxButton* ButtonLightsOff;
		wxRadioButton* RadioButtonRgbChase5;
		wxNotebook* Notebook2;
		wxChoice* ChoiceNumSelect;
		wxStaticText* StaticText4;
		wxRadioButton* RadioButtonRgbTwinkle25;
		wxStaticText* StaticText2;
		wxSlider* SliderRgbCycleSpeed;
		wxNotebook* Notebook1;
		wxPanel* Panel_RGB_Cycle;
		wxPanel* PanelStandard;
		wxSlider* SliderBgColorB;
		wxSlider* SliderFgColorB;
		wxRadioButton* RadioButtonRgbCycle5;
		wxSlider* SliderBgIntensity;
		wxStaticText* StaticText29;
		wxStaticText* StaticText9;
		wxRadioButton* RadioButtonDim;
		wxRadioButton* RadioButtonRgbChase4;
		wxSlider* SliderRgbChaseSpeed;
		wxStaticText* StaticText11;
		//*)

	protected:

		//(*Identifiers(TestDialog)
		static const long ID_STATICTEXT1;
		static const long ID_CHOICE_NUMSELECT;
		static const long ID_BUTTON_CLEAR;
		static const long ID_STATICTEXT3;
		static const long ID_BUTTON_EXPORT;
		static const long ID_BUTTON_LIGHTS_OFF;
		static const long ID_BUTTON_CLOSE;
		static const long ID_NOTEBOOK2;
		static const long ID_STATICTEXT8;
		static const long ID_RADIOBUTTON14;
		static const long ID_RADIOBUTTON15;
		static const long ID_RADIOBUTTON16;
		static const long ID_RADIOBUTTON17;
		static const long ID_RADIOBUTTON19;
		static const long ID_RADIOBUTTON18;
		static const long ID_RADIOBUTTON7;
		static const long ID_RADIOBUTTON31;
		static const long ID_RADIOBUTTON30;
		static const long ID_RADIOBUTTON29;
		static const long ID_RADIOBUTTON8;
		static const long ID_RADIOBUTTON6;
		static const long ID_STATICTEXT9;
		static const long ID_SLIDER4;
		static const long ID_STATICTEXT10;
		static const long ID_SLIDER5;
		static const long ID_STATICTEXT11;
		static const long ID_SLIDER6;
		static const long ID_PANEL_STANDARD;
		static const long ID_STATICTEXT29;
		static const long ID_RADIOBUTTON1;
		static const long ID_RADIOBUTTON2;
		static const long ID_RADIOBUTTON3;
		static const long ID_RADIOBUTTON4;
		static const long ID_RADIOBUTTON25;
		static const long ID_RADIOBUTTON5;
		static const long ID_RADIOBUTTON12;
		static const long ID_RADIOBUTTON28;
		static const long ID_RADIOBUTTON10;
		static const long ID_RADIOBUTTON9;
		static const long ID_RADIOBUTTON13;
		static const long ID_RADIOBUTTON11;
		static const long ID_SLIDER12;
		static const long ID_SLIDER11;
		static const long ID_SLIDER1;
		static const long ID_SLIDER14;
		static const long ID_SLIDER13;
		static const long ID_SLIDER9;
		static const long ID_STATICTEXT4;
		static const long ID_SLIDER2;
		static const long ID_PANEL_RGB;
		static const long ID_STATICTEXT2;
		static const long ID_RADIOBUTTON20;
		static const long ID_RADIOBUTTON22;
		static const long ID_RADIOBUTTON23;
		static const long ID_RADIOBUTTON24;
		static const long ID_RADIOBUTTON21;
		static const long ID_STATICTEXT13;
		static const long ID_SLIDER7;
		static const long ID_PANEL_RGB_CYCLE;
		static const long ID_NOTEBOOK1;
		static const long ID_PANEL4;
		//*)

	private:

		//(*Handlers(TestDialog)
		void OnButtonClearClick(wxCommandEvent& event);
		void OnButtonExportClick(wxCommandEvent& event);
		void OnButtonLightsOffClick(wxCommandEvent& event);
		void OnRadioButtonOffSelect(wxCommandEvent& event);
		void OnRadioButtonChaseSelect(wxCommandEvent& event);
		void OnRadioButtonChase3Select(wxCommandEvent& event);
		void OnRadioButtonChase4Select(wxCommandEvent& event);
		void OnRadioButtonChase5Select(wxCommandEvent& event);
		void OnRadioButtonAltSelect(wxCommandEvent& event);
		void OnRadioButtonTwinkle05Select(wxCommandEvent& event);
		void OnRadioButtonTwinkle10Select(wxCommandEvent& event);
		void OnRadioButtonTwinkle25Select(wxCommandEvent& event);
		void OnRadioButtonTwinkle50Select(wxCommandEvent& event);
		void OnRadioButtonShimmerSelect(wxCommandEvent& event);
		void OnRadioButtonDimSelect(wxCommandEvent& event);
		void OnButtonCloseClick(wxCommandEvent& event);
		//*)

        void OnCheckboxToggle(wxCommandEvent& event);
        WX_DEFINE_ARRAY_PTR(NetworkInfo*, NetworkArray);
        NetworkArray Networks;

		DECLARE_EVENT_TABLE()
};

#endif
