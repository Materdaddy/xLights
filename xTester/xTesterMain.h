/***************************************************************
 * Name:      xTesterMain.h
 * Purpose:   Defines Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-04-03
 * Copyright: Matt Brown (dowdybrown.com)
 * License:
 **************************************************************/

#ifndef XTESTERMAIN_H
#define XTESTERMAIN_H

//(*Headers(xTesterFrame)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/checkbox.h>
#include <wx/radiobut.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include <wx/filename.h>
#include <wx/checklst.h>
#include <wx/timer.h>
#include <wx/datetime.h>

#include "../include/globals.h"
#include "../include/tinyxml.h"

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
        } else {
            return NetworkType+_("\n")+ComPort+_(" at ")+BaudRate+_(" baud");
        }
    }

    wxString net3() {
        return NetworkType.Left(3);
    }

    bool IsDMX() {
        return net3() ==_("DMX");
    }
};

class xTesterFrame: public wxFrame
{
    public:

        xTesterFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~xTesterFrame();
        void OnTimer(wxTimerEvent& event);

    private:

        //(*Handlers(xTesterFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButtonSh3Click(wxCommandEvent& event);
        void OnButtonSh10Click(wxCommandEvent& event);
        void OnButtonTw3Click(wxCommandEvent& event);
        void OnButtonTw10Click(wxCommandEvent& event);
        //*)

        void LoadFile();
        wxString GetAttribute(TiXmlElement* e, const char *attr);

        //(*Identifiers(xTesterFrame)
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT3;
        static const long ID_BUTTON1;
        static const long ID_NOTEBOOK2;
        static const long ID_STATICTEXT2;
        static const long ID_SLIDER1;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT11;
        static const long ID_PANEL1;
        static const long ID_CHECKBOX_RUNSEQ;
        static const long ID_STATICTEXT4;
        static const long ID_SLIDER2;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT10;
        static const long ID_PANEL2;
        static const long ID_CHECKBOX_RUNALT;
        static const long ID_STATICTEXT7;
        static const long ID_SLIDER3;
        static const long ID_STATICTEXT8;
        static const long ID_STATICTEXT9;
        static const long ID_PANEL3;
        static const long ID_CHECKBOX_RUNTW;
        static const long ID_RADIOBUTTON_TWNOFADE;
        static const long ID_RADIOBUTTON_TWFADE;
        static const long ID_STATICTEXT12;
        static const long ID_STATICTEXT15;
        static const long ID_SLIDER_TWRATE;
        static const long ID_STATICTEXT13;
        static const long ID_STATICTEXT14;
        static const long ID_PANEL5;
        static const long ID_CHECKBOX_RUNSH;
        static const long ID_RADIOBUTTON_SHNOFADE;
        static const long ID_RADIOBUTTON_SHFADE;
        static const long ID_STATICTEXT16;
        static const long ID_STATICTEXT17;
        static const long ID_SLIDER4;
        static const long ID_STATICTEXT18;
        static const long ID_STATICTEXT19;
        static const long ID_PANEL6;
        static const long ID_NOTEBOOK1;
        static const long ID_PANEL4;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)
        static const long ID_TIMER;

        //(*Declarations(xTesterFrame)
        wxStaticText* StaticText10;
        wxSlider* Slider1;
        wxPanel* Panel_Dim;
        wxStaticText* StaticText9;
        wxNotebook* Notebook1;
        wxCheckBox* CheckBoxRunSh;
        wxStaticText* StaticText13;
        wxStaticText* StaticText2;
        wxStaticText* StaticText14;
        wxRadioButton* RadioButtonTwNoFade;
        wxButton* Button1;
        wxStaticText* StaticText6;
        wxRadioButton* RadioButtonShNoFade;
        wxSlider* Slider3;
        wxStaticText* StaticText19;
        wxStaticText* StaticText8;
        wxStaticText* StaticText11;
        wxStaticText* StaticText18;
        wxCheckBox* CheckBoxRunTw;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxPanel* Panel3;
        wxCheckBox* CheckBoxRunAlt;
        wxRadioButton* RadioButtonShFade;
        wxStaticText* StaticText5;
        wxStaticText* StaticText7;
        wxStatusBar* StatusBar1;
        wxPanel* Panel_Seq;
        wxSlider* SliderTwRate;
        wxStaticText* StaticText15;
        wxStaticText* StaticText12;
        wxRadioButton* RadioButtonTwFade;
        wxPanel* Panel2;
        wxSlider* SliderMasterDimmer;
        wxNotebook* Notebook2;
        wxStaticText* StaticText17;
        wxStaticText* StaticText4;
        wxSlider* SliderShRate;
        wxStaticText* StaticText16;
        wxPanel* Panel_Alt;
        wxCheckBox* CheckBoxRunSeq;
        //*)

        wxFileName networkFile;
        WX_DEFINE_ARRAY(NetworkInfo*, NetworkArray);
        NetworkArray Networks;
        NetworkInfo* AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels);
        void alloff();
        wxTimer timer;
        wxDateTime starttime;

        DECLARE_EVENT_TABLE()
};

#endif // XTESTERMAIN_H
