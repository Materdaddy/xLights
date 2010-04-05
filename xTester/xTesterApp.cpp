/***************************************************************
 * Name:      xTesterApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-04-03
 * Copyright: Matt Brown (dowdybrown.com)
 * License:
 **************************************************************/

#include "xTesterApp.h"

//(*AppHeaders
#include "xTesterMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(xTesterApp);

bool xTesterApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	xTesterFrame* Frame = new xTesterFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
