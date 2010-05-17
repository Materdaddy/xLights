/***************************************************************
 * Name:      xNetworksApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-05-16
 * Copyright: Matt Brown (dowdybrown.com)
 * License:
 **************************************************************/

#include "xNetworksApp.h"

//(*AppHeaders
#include "xNetworksMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(xNetworksApp);

bool xNetworksApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	xNetworksFrame* Frame = new xNetworksFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
