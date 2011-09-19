/***************************************************************
 * Name:      xTesterRGBApp.cpp
 * Purpose:   Code for Application Class
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

#include "xTesterRGBApp.h"
#include <wx/msgdlg.h>

//(*AppHeaders
#include "xTesterRGBMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(xTesterRGBApp);

bool xTesterRGBApp::OnInit()
{
    wxString name = GetAppName() + wxT("-SingleInstanceCheck");
    m_checker = new wxSingleInstanceChecker(name);
    if ( m_checker->IsAnotherRunning() )
    {
        wxMessageBox(_("Another program instance is already running"), _("Error"));
        return false;
    }

    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	xTesterRGBFrame* Frame = new xTesterRGBFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}

int xTesterRGBApp::OnExit()
{
    delete m_checker;
    return 0;
}
