/***************************************************************
 * Name:      MainMenuApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-02-27
 * Copyright: Matt Brown (dowdybrown.com)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "MainMenuApp.h"

//(*AppHeaders
#include "MainMenuMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(MainMenuApp);

bool MainMenuApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	MainMenuFrame* Frame = new MainMenuFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
