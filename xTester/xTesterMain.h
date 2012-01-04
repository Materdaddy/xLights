/***************************************************************
 * Name:      xTesterMain.h
 * Purpose:   Defines Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-04-03
 * Copyright: 2010 by Matt Brown
 * License:
     This file is part of xLights.

    xLights is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    xLights is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with xLights.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************************/

#ifndef XTESTERMAIN_H
#define XTESTERMAIN_H

//(*Headers(xTesterFrame)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/listbox.h>
#include <wx/radiobut.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include <wx/filename.h>
#include <wx/checklst.h>
#include <wx/timer.h>
#include <wx/datetime.h>
#include <wx/xml/xml.h>
#include <wx/log.h>

#include "../include/globals.h"


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
        void OnMenuItemHelpContentSelected(wxCommandEvent& event);
        void OnButtonExportClick(wxCommandEvent& event);
        void OnButtonClearClick(wxCommandEvent& event);
        void OnRadioButtonOffSelect(wxCommandEvent& event);
        void OnRadioButtonChaseSelect(wxCommandEvent& event);
        void OnRadioButtonChase3Select(wxCommandEvent& event);
        void OnRadioButtonChase4Select(wxCommandEvent& event);
        void OnRadioButtonAltSelect(wxCommandEvent& event);
        void OnRadioButtonDimSelect(wxCommandEvent& event);
        void OnRadioButtonShimmerSelect(wxCommandEvent& event);
        void OnRadioButtonChase5Select(wxCommandEvent& event);
        void OnRadioButtonTwinkle05Select(wxCommandEvent& event);
        void OnRadioButtonTwinkle10Select(wxCommandEvent& event);
        void OnRadioButtonTwinkle25Select(wxCommandEvent& event);
        void OnRadioButtonTwinkle50Select(wxCommandEvent& event);
        //*)

        //(*Identifiers(xTesterFrame)
        static const long ID_STATICTEXT1;
        static const long ID_CHOICE_NUMSELECT;
        static const long ID_BUTTON_CLEAR;
        static const long ID_STATICTEXT3;
        static const long ID_BUTTON_EXPORT;
        static const long ID_BUTTON1;
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
        static const long ID_STATICTEXT6;
        static const long ID_RADIOBUTTON26;
        static const long ID_RADIOBUTTON27;
        static const long ID_LISTBOX_AUTOTEST;
        static const long ID_PANEL_AUTOTEST;
        static const long ID_NOTEBOOK1;
        static const long ID_PANEL4;
        static const long idMenuQuit;
        static const long idMenuHelpContent;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)
        static const long ID_TIMER;

        //(*Declarations(xTesterFrame)
        wxRadioButton* RadioButtonAutoOff;
        wxStaticText* StaticText10;
        wxRadioButton* RadioButtonChase5;
        wxStaticText* StaticText9;
        wxRadioButton* RadioButtonRgbCycle4;
        wxRadioButton* RadioButtonRgbChaseOff;
        wxRadioButton* RadioButtonRgbCycleOff;
        wxRadioButton* RadioButtonAutoOn;
        wxButton* ButtonExport;
        wxRadioButton* RadioButtonRgbChase;
        wxRadioButton* RadioButtonRgbChase5;
        wxRadioButton* RadioButtonRgbChase3;
        wxStaticText* StaticText29;
        wxRadioButton* RadioButtonShimmer;
        wxNotebook* Notebook1;
        wxPanel* PanelAutoTest;
        wxStaticText* StaticText13;
        wxStaticText* StaticText2;
        wxSlider* SliderFgColorC;
        wxSlider* SliderRgbChaseSpeed;
        wxRadioButton* RadioButtonRgbCycle3;
        wxButton* Button1;
        wxStaticText* StaticText6;
        wxRadioButton* RadioButtonDim;
        wxRadioButton* RadioButtonChase4;
        wxPanel* Panel_RGB;
        wxRadioButton* RadioButtonRgbTwinkle10;
        wxRadioButton* RadioButtonChase3;
        wxSlider* SliderChaseSpeed;
        wxStaticText* StaticText8;
        wxStaticText* StaticText11;
        wxPanel* PanelStandard;
        wxSlider* SliderFgColorA;
        wxStaticText* StaticText1;
        wxButton* ButtonClear;
        wxStaticText* StaticText3;
        wxRadioButton* RadioButtonChaseOff;
        wxRadioButton* RadioButtonRgbAlt;
        wxPanel* Panel3;
        wxSlider* SliderRgbCycleSpeed;
        wxMenuItem* MenuItemHelpContent;
        wxRadioButton* RadioButtonTwinkle50;
        wxRadioButton* RadioButtonRgbCycleMixed;
        wxSlider* SliderBgColorA;
        wxRadioButton* RadioButtonRgbTwinkle50;
        wxSlider* SliderBgColorC;
        wxRadioButton* RadioButtonRgbTwinkle05;
        wxChoice* ChoiceNumSelect;
        wxStatusBar* StatusBar1;
        wxRadioButton* RadioButtonRgbTwinkle25;
        wxRadioButton* RadioButtonRgbShimmer;
        wxRadioButton* RadioButtonTwinkle10;
        wxSlider* SliderBgColorB;
        wxRadioButton* RadioButtonRgbDim;
        wxRadioButton* RadioButtonTwinkle25;
        wxListBox* ListBoxAutoTest;
        wxRadioButton* RadioButtonChase;
        wxSlider* SliderBgIntensity;
        wxRadioButton* RadioButtonTwinkle05;
        wxNotebook* Notebook2;
        wxStaticText* StaticText4;
        wxRadioButton* RadioButtonRgbCycle5;
        wxRadioButton* RadioButtonRgbChase4;
        wxPanel* Panel_RGB_Cycle;
        wxSlider* SliderFgIntensity;
        wxSlider* SliderFgColorB;
        wxRadioButton* RadioButtonAlt;
        //*)

        void LoadFile();
        double rand01();
        NetworkInfo* AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels);
        void alloff();
        void OnCheckboxToggle(wxCommandEvent& event);

        wxFileName networkFile;
        long LorMapping;
        WX_DEFINE_ARRAY_PTR(NetworkInfo*, NetworkArray);
        NetworkArray Networks;
        wxTimer timer;
        wxDateTime starttime;
        wxLog *logger;
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

        DECLARE_EVENT_TABLE()
};

#endif // XTESTERMAIN_H
