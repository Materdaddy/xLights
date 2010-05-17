/***************************************************************
 * Name:      xScheduleApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-05-15
 * Copyright: Matt Brown (dowdybrown.com)
 * License:
 **************************************************************/

#include "xScheduleApp.h"

//(*AppHeaders
#include "xScheduleMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(xScheduleApp);

bool xScheduleApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	xScheduleFrame* Frame = new xScheduleFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
