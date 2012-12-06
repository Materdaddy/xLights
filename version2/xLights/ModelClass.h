/***************************************************************
 * Name:      ModelClass.h
 * Purpose:   Represents Display Model
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2012-10-22
 * Copyright: 2012 by Matt Brown
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

#ifndef MODELCLASS_H
#define MODELCLASS_H

#include <vector>
#include <wx/xml/xml.h>
#include <wx/gdicmn.h>
#include <wx/colour.h>

class RgbNodeClass
{
    uint8_t c[3];      // color values in rgb order
    uint8_t offset[3]; // offsets to change the order in which the color values are sent to the physical device

public:

    wxCoord bufX, bufY, screenX, screenY;
    size_t bufIdx;
    int sparkle;

    void SetColor(wxColour& color)
    {
        c[0]=color.Red();
        c[1]=color.Green();
        c[2]=color.Blue();
    }

    void SetColor(uint8_t r,uint8_t g,uint8_t b)
    {
        c[0]=r;
        c[1]=g;
        c[2]=b;
    }

    // offsets should be 0-2
    // for rgb order, pass: 0,1,2
    // for grb order, pass: 1,0,2
    // for brg order, pass: 2,0,1
    void SetOffset(uint8_t offset_r,uint8_t offset_g,uint8_t offset_b)
    {
        offset[0]=offset_r;
        offset[1]=offset_g;
        offset[2]=offset_b;
    }

    // chnum should be 0-2
    uint8_t GetChannel(size_t chnum)
    {
        return c[offset[chnum]];
    }

    void GetColor(wxColour& color)
    {
        color.Set(c[0],c[1],c[2]);
    }
};

typedef std::vector<RgbNodeClass> RgbNodeVector;


class ModelClass
{
private:
    void InitVMatrix();
    void InitHMatrix();
    void InitLine();
    void InitFrame();
    void SetBufferSize(int NewHt, int NewWi);
    void SetRenderSize(int NewHt, int NewWi);
    void SetNodeCount(size_t NewCount);
    void CopyBufCoord2ScreenCoord();
    void SetTreeCoord(int degrees);
    void SetLineCoord();
    void SetArchCoord();
    static const double PI  =3.141592653589793238462;

public:
    wxString name;      // user-designated model name
    wxString DisplayAs; // Tree 360, Tree 270, Tree 180, Tree 90, Vert Matrix, Horiz Matrix, Single Line, Arches, Window Frame
    wxString RGBorder;  // RGB, RBG, GBR, GRB, BGR, BRG
    bool IsLtoR;        // true=left to right, false=right to left
    long parm1,parm2,parm3;
    long StartChannel;      // start channel for output (1 is first channel)
    int BufferHt,BufferWi;  // size of the buffer
    int RenderHt,RenderWi;  // size of the rendered output
    long Antialias;         // amount of anti-alias (0,1,2)
    int AliasFactor;        // factor to expand buffer (2 ^ Antialias)
    int TreeDegrees,FrameWidth;
    RgbNodeVector Nodes;
    bool MyDisplay;

    void SetFromXml(wxXmlNode* ModelNode);
    size_t GetNodeCount();
};

#endif // MODELCLASS_H
