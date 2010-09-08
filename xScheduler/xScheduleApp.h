/***************************************************************
 * Name:      xScheduleApp.h
 * Purpose:   Defines Application Class
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2010-05-15
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

#ifndef XSCHEDULEAPP_H
#define XSCHEDULEAPP_H

#include <wx/app.h>
#include <wx/snglinst.h>

class xScheduleApp : public wxApp
{
    public:
        virtual bool OnInit();
        virtual int OnExit();

    private:
        wxSingleInstanceChecker* m_checker;
};

#endif // XSCHEDULEAPP_H
