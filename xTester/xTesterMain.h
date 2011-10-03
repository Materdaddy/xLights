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
#include <wx/checkbox.h>
#include <wx/listbox.h>
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
        //*)

        void LoadFile();

        //(*Identifiers(xTesterFrame)
        static const long ID_STATICTEXT1;
        static const long ID_CHOICE_NUMSELECT;
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
        static const long ID_STATICTEXT12;
        static const long ID_SLIDER_TWRATE;
        static const long ID_STATICTEXT13;
        static const long ID_STATICTEXT14;
        static const long ID_PANEL_TWINKLE;
        static const long ID_CHECKBOX_RUNSH;
        static const long ID_STATICTEXT16;
        static const long ID_SLIDER4;
        static const long ID_STATICTEXT18;
        static const long ID_STATICTEXT19;
        static const long ID_PANEL_SHIMMER;
        static const long ID_CHECKBOX_AUTO;
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
        wxStaticText* StaticText10;
        wxSlider* Slider1;
        wxPanel* Panel_Dim;
        wxStaticText* StaticText9;
        wxNotebook* Notebook1;
        wxPanel* PanelAutoTest;
        wxCheckBox* CheckBoxRunSh;
        wxStaticText* StaticText13;
        wxStaticText* StaticText2;
        wxStaticText* StaticText14;
        wxButton* Button1;
        wxPanel* PanelTwinkle;
        wxStaticText* StaticText6;
        wxSlider* SliderShIntensity;
        wxSlider* Slider3;
        wxStaticText* StaticText19;
        wxStaticText* StaticText8;
        wxStaticText* StaticText11;
        wxStaticText* StaticText18;
        wxCheckBox* CheckBoxRunTw;
        wxCheckBox* CheckBoxRunAuto;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxPanel* Panel3;
        wxMenuItem* MenuItemHelpContent;
        wxCheckBox* CheckBoxRunAlt;
        wxStaticText* StaticText5;
        wxStaticText* StaticText7;
        wxChoice* ChoiceNumSelect;
        wxStatusBar* StatusBar1;
        wxSlider* SliderTwIntensity;
        wxPanel* Panel_Seq;
        wxStaticText* StaticText12;
        wxListBox* ListBoxAutoTest;
        wxPanel* PanelShimmer;
        wxSlider* SliderMasterDimmer;
        wxNotebook* Notebook2;
        wxStaticText* StaticText4;
        wxStaticText* StaticText16;
        wxPanel* Panel_Alt;
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

#endif // XTESTERMAIN_H
