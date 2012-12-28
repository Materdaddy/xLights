/***************************************************************
 * Name:      PixelBuffer.cpp
 * Purpose:   Implements pixel buffer and effects
 * Author:    Matt Brown (dowdybrown@yahoo.com)
 * Created:   2012-10-21
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

#include "PixelBuffer.h"

PixelBufferClass::PixelBufferClass()
{
}

PixelBufferClass::~PixelBufferClass()
{
}

void PixelBufferClass::InitBuffer(wxXmlNode* ModelNode)
{
    size_t i;
    SetFromXml(ModelNode);
    size_t NodeCount=GetNodeCount();
    uint8_t offset_r=RGBorder.find(wxT("R"));
    uint8_t offset_g=RGBorder.find(wxT("G"));
    uint8_t offset_b=RGBorder.find(wxT("B"));
    for(i=0; i<NodeCount; i++) {
        Nodes[i].SetOffset(offset_r, offset_g, offset_b);
        Nodes[i].sparkle = rand() % 10000;
    }
    for(i=0; i<2; i++) {
        Effect[i].InitBuffer(BufferHt, BufferWi);
    }
}

void PixelBufferClass::Clear()
{
    wxColour bgColor=*wxBLACK;
    for(size_t i=0; i<2; i++) {
        Effect[i].Clear(bgColor);
    }
}

// convert MixName to MixType enum
void PixelBufferClass::SetMixType(const wxString& MixName)
{
    if (MixName == wxT("Effect 1")) {
        MixType=Mix_Effect1;
    } else if (MixName == wxT("Effect 2")) {
        MixType=Mix_Effect2;
    } else if (MixName == wxT("1 is Mask")) {
        MixType=Mix_Mask1;
    } else if (MixName == wxT("2 is Mask")) {
        MixType=Mix_Mask2;
    } else if (MixName == wxT("1 is Unmask")) {
        MixType=Mix_Unmask1;
    } else if (MixName == wxT("2 is Unmask")) {
        MixType=Mix_Unmask2;
    } else if (MixName == wxT("Layered")) {
        MixType=Mix_Layered;
    } else if (MixName == wxT("Average")) {
        MixType=Mix_Average;
    }
}

void PixelBufferClass::GetMixedColor(wxCoord x, wxCoord y, wxColour& c)
{
    wxColour c0,c1;
    Effect[0].GetPixel(x,y,c0);
    Effect[1].GetPixel(x,y,c1);
    switch (MixType)
    {
        case Mix_Effect1:
            c=c0;
            break;
        case Mix_Effect2:
            c=c1;
            break;
        case Mix_Mask1:
            // first masks second
            if (c0.GetRGB() == 0) {
                c=c1;
            } else {
                c.Set(0);
            }
            break;
        case Mix_Mask2:
            // second masks first
            if (c1.GetRGB() == 0) {
                c=c0;
            } else {
                c.Set(0);
            }
            break;
        case Mix_Unmask1:
            // first unmasks second
            if (c0.GetRGB() != 0) {
                c=c1;
            } else {
                c.Set(0);
            }
            break;
        case Mix_Unmask2:
            // second unmasks first
            if (c1.GetRGB() != 0) {
                c=c0;
            } else {
                c.Set(0);
            }
            break;
        case Mix_Layered:
            if (c1.GetRGB() == 0) {
                c=c0;
            } else {
                c=c1;
            }
            break;
        case Mix_Average:
            // only average when both colors are non-black
            if (c0.GetRGB() == 0) {
                c=c1;
            } else if (c1.GetRGB() == 0) {
                c=c0;
            } else {
                c.Set( (c0.Red()+c1.Red())/2, (c0.Green()+c1.Green())/2, (c0.Blue()+c1.Blue())/2 );
            }
            break;
    }
}

void PixelBufferClass::SetPalette(int layer, wxColourVector& newcolors)
{
    Effect[layer].SetPalette(newcolors);
}

size_t PixelBufferClass::GetColorCount(int layer)
{
    return Effect[layer].GetColorCount();
}

// 10-200 or so, or 0 for no sparkle
void PixelBufferClass::SetSparkle(int freq)
{
    sparkle_count=freq;
}

void PixelBufferClass::SetLayer(int newlayer, int period, int speed, bool ResetState)
{
    CurrentLayer=newlayer & 1;  // only 0 or 1 is allowed
    Effect[CurrentLayer].SetState(period,speed,ResetState);
}

void PixelBufferClass::CalcOutput()
{
    wxColour color;
    // layer calculation and map to output
    size_t NodeCount=Nodes.size();
    for(size_t i=0; i<NodeCount; i++) {
        if (Nodes[i].bufX < 0) {
            // unmapped pixel - set to black
            Nodes[i].SetColor(0,0,0);
        } else {
            // get blend of two effects
            GetMixedColor(Nodes[i].bufX, Nodes[i].bufY, color);
            // add sparkles
            if (sparkle_count > 0 && color.GetRGB()!=0) {
                switch (Nodes[i].sparkle%sparkle_count) {
                    case 1:
                    case 7:
                        // too dim
                        //color.Set(wxT("#444444"));
                        break;
                    case 2:
                    case 6:
                        color.Set(wxT("#888888"));
                        break;
                    case 3:
                    case 5:
                        color.Set(wxT("#BBBBBB"));
                        break;
                    case 4:
                        color.Set(wxT("#FFFFFF"));
                        break;
                }
                Nodes[i].sparkle++;
            }
            // set color for physical output
            Nodes[i].SetColor(color);
        }
    }
}

void PixelBufferClass::RenderBars(int PaletteRepeat, int Direction, bool Highlight, bool Show3D)
{
    Effect[CurrentLayer].RenderBars(PaletteRepeat,Direction,Highlight,Show3D);
}

void PixelBufferClass::RenderButterfly(int ColorScheme, int Style, int Chunks, int Skip)
{
    Effect[CurrentLayer].RenderButterfly(ColorScheme,Style,Chunks,Skip);
}

void PixelBufferClass::RenderColorWash(bool HorizFade, bool VertFade, int RepeatCount)
{
    Effect[CurrentLayer].RenderColorWash(HorizFade,VertFade,RepeatCount);
}

void PixelBufferClass::RenderFire(int HeightPct)
{
    Effect[CurrentLayer].RenderFire(HeightPct);
}

void PixelBufferClass::RenderGarlands(int GarlandType, int Spacing)
{
    Effect[CurrentLayer].RenderGarlands(GarlandType,Spacing);
}

void PixelBufferClass::RenderLife(int Count, int Seed)
{
    Effect[CurrentLayer].RenderLife(Count,Seed);
}

void PixelBufferClass::RenderMeteors(int MeteorType, int Count, int Length)
{
    Effect[CurrentLayer].RenderMeteors(MeteorType,Count,Length);
}

void PixelBufferClass::RenderPictures(int dir, const wxString& NewPictureName)
{
    Effect[CurrentLayer].RenderPictures(dir,NewPictureName);
}

void PixelBufferClass::RenderSnowflakes(int Count, int SnowflakeType)
{
    Effect[CurrentLayer].RenderSnowflakes(Count,SnowflakeType);
}

void PixelBufferClass::RenderSnowstorm(int Count, int Length)
{
    Effect[CurrentLayer].RenderSnowstorm(Count,Length);
}

void PixelBufferClass::RenderSpirals(int PaletteRepeat, int Direction, int Rotation, int Thickness, bool Blend, bool Show3D)
{
    Effect[CurrentLayer].RenderSpirals(PaletteRepeat,Direction,Rotation,Thickness,Blend,Show3D);
}

void PixelBufferClass::RenderText(int Top, const wxString& Line1, const wxString& Line2, const wxString& FontString, int dir)
{
    Effect[CurrentLayer].RenderText(Top,Line1,Line2,FontString,dir);
}

