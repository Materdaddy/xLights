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
#include <wx/checklst.h>
#include <wx/checkbox.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include <wx/filename.h>

#include "../include/globals.h"
#include "../include/tinyxml.h"

class xTesterFrame: public wxFrame
{
    public:

        xTesterFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~xTesterFrame();

    private:

        //(*Handlers(xTesterFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnCheckBoxRunClick(wxCommandEvent& event);
        void OnSliderMasterDimmerCmdScroll(wxScrollEvent& event);
        //*)

        void LoadFile();
        wxString GetAttribute(TiXmlElement* e, const char *attr);

        //(*Identifiers(xTesterFrame)
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT3;
        static const long ID_CHECKLISTBOX1;
        static const long ID_SLIDER1;
        static const long ID_STATICTEXT2;
        static const long ID_BUTTON1;
        static const long ID_PANEL1;
        static const long ID_CHECKBOX1;
        static const long ID_SLIDER2;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_PANEL2;
        static const long ID_CHECKBOX2;
        static const long ID_SLIDER3;
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT8;
        static const long ID_STATICTEXT9;
        static const long ID_PANEL3;
        static const long ID_NOTEBOOK1;
        static const long ID_PANEL4;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(xTesterFrame)
        wxSlider* Slider1;
        wxPanel* Panel_Dim;
        wxStaticText* StaticText9;
        wxNotebook* Notebook1;
        wxStaticText* StaticText2;
        wxButton* Button1;
        wxStaticText* StaticText6;
        wxSlider* Slider3;
        wxStaticText* StaticText8;
        wxCheckBox* CheckBox2;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxPanel* Panel3;
        wxCheckBox* CheckBox1;
        wxStaticText* StaticText5;
        wxStaticText* StaticText7;
        wxStatusBar* StatusBar1;
        wxCheckListBox* CheckListBox_Channels;
        wxPanel* Panel_Seq;
        wxSlider* SliderMasterDimmer;
        wxStaticText* StaticText4;
        wxPanel* Panel_Alt;
        //*)

        wxFileName channelFile;

        DECLARE_EVENT_TABLE()
};

#endif // XTESTERMAIN_H
