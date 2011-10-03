/***************************************************************
 * Name:      xTesterRGBMain.h
 * Purpose:   Defines Application Frame
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2011-09-18
 * Copyright: 2011 by Matt Brown
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

#ifndef XTESTERRGBMAIN_H
#define XTESTERRGBMAIN_H

//(*Headers(xTesterRGBFrame)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/checkbox.h>
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

class xTesterRGBFrame: public wxFrame
{
    public:

        xTesterRGBFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~xTesterRGBFrame();
        void OnTimer(wxTimerEvent& event);

    private:

        //(*Handlers(xTesterRGBFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButtonSh3Click(wxCommandEvent& event);
        void OnButtonSh10Click(wxCommandEvent& event);
        void OnButtonTw3Click(wxCommandEvent& event);
        void OnButtonTw10Click(wxCommandEvent& event);
        void OnMenuItemHelpContentSelected(wxCommandEvent& event);
        //*)

        void LoadFile();

        //(*Identifiers(xTesterRGBFrame)
        static const long ID_STATICTEXT1;
        static const long ID_CHOICE_NUM_SELECT;
        static const long ID_STATICTEXT3;
        static const long ID_BUTTON1;
        static const long ID_NOTEBOOK2;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT13;
        static const long ID_SLIDER5;
        static const long ID_STATICTEXT14;
        static const long ID_SLIDER6;
        static const long ID_STATICTEXT12;
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
        static const long ID_CHECKBOX_RUNFADE;
        static const long ID_STATICTEXT7;
        static const long ID_SLIDER3;
        static const long ID_STATICTEXT8;
        static const long ID_STATICTEXT9;
        static const long ID_PANEL3;
        static const long ID_CHECKBOX_RUNSH;
        static const long ID_STATICTEXT15;
        static const long ID_SLIDER4;
        static const long ID_STATICTEXT16;
        static const long ID_SLIDER7;
        static const long ID_STATICTEXT17;
        static const long ID_SLIDER8;
        static const long ID_STATICTEXT18;
        static const long ID_STATICTEXT19;
        static const long ID_PANEL_SHIMMER;
        static const long ID_NOTEBOOK1;
        static const long ID_PANEL4;
        static const long idMenuQuit;
        static const long idMenuHelpContent;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)
        static const long ID_TIMER;

        //(*Declarations(xTesterRGBFrame)
        wxStaticText* StaticText10;
        wxSlider* Slider1;
        wxPanel* Panel_Dim;
        wxStaticText* StaticText9;
        wxNotebook* Notebook1;
        wxSlider* SliderSetColorA;
        wxCheckBox* CheckBoxRunSh;
        wxStaticText* StaticText13;
        wxStaticText* StaticText2;
        wxSlider* SliderSetColorC;
        wxStaticText* StaticText14;
        wxButton* Button1;
        wxCheckBox* CheckBoxRunFade;
        wxStaticText* StaticText6;
        wxSlider* Slider3;
        wxStaticText* StaticText19;
        wxStaticText* StaticText8;
        wxStaticText* StaticText11;
        wxStaticText* StaticText18;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxPanel* Panel3;
        wxSlider* SliderShimmerB;
        wxMenuItem* MenuItemHelpContent;
        wxPanel* Panel_Fade;
        wxSlider* SliderSetColorB;
        wxStaticText* StaticText5;
        wxStaticText* StaticText7;
        wxChoice* ChoiceNumSelect;
        wxStatusBar* StatusBar1;
        wxPanel* Panel_Seq;
        wxStaticText* StaticText15;
        wxStaticText* StaticText12;
        wxPanel* PanelShimmer;
        wxNotebook* Notebook2;
        wxStaticText* StaticText17;
        wxStaticText* StaticText4;
        wxSlider* SliderShimmerA;
        wxSlider* SliderShimmerC;
        wxStaticText* StaticText16;
        wxCheckBox* CheckBoxRunSeq;
        //*)

        wxFileName networkFile;
        long LorMapping;
        WX_DEFINE_ARRAY(NetworkInfo*, NetworkArray);
        NetworkArray Networks;
        NetworkInfo* AddNetwork(const wxString& NetworkType, const wxString& ComPort, const wxString& BaudRate, int MaxChannels);
        void alloff();
        void OnCheckboxToggle(wxCommandEvent& event);
        wxTimer timer;
        wxDateTime starttime;
        wxLog *logger;

        DECLARE_EVENT_TABLE()
};

#endif // XTESTERRGBMAIN_H
