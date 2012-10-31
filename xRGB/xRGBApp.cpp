/***************************************************************
 * Name:      xRGBApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2012-10-09
 * Copyright: Matt Brown ()
 * License:
 **************************************************************/

#include "xRGBApp.h"

//(*AppHeaders
#include "xRGBMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(xRGBApp);

bool xRGBApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	xRGBFrame* Frame = new xRGBFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
