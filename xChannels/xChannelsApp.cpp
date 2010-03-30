/***************************************************************
 * Name:      xChannelsApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-03-01
 * Copyright: Matt Brown (dowdybrown.com)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "xChannelsApp.h"

//(*AppHeaders
#include "xChannelsMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(xChannelsApp);

bool xChannelsApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	xChannelsFrame* Frame = new xChannelsFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
