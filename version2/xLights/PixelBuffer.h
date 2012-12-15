/***************************************************************
 * Name:      PixelBuffer.h
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

#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include <stdint.h>
#include <list>
#include <vector>
#include <wx/colour.h>
#include <wx/scrolwin.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/pen.h>
#include <wx/xml/xml.h>

#include "ModelClass.h"

enum MixTypes {
    Mix_Effect1,
    Mix_Effect2,
    Mix_Mask1,
    Mix_Mask2,
    Mix_Unmask1,
    Mix_Unmask2,
    Mix_Layered,
    Mix_Average,
};


// for meteor effect
class MeteorClass
{
public:

    int x,y;
    wxImage::HSVValue hsv;
};


class MeteorHasExpired
{
    int TailLength;
public:
    MeteorHasExpired(int t)
    : TailLength(t)
    {}

    // operator() is what's called when you do MeteorHasExpired()
    bool operator()(const MeteorClass& obj)
    {
        return obj.y + TailLength < 0;
    }
};

typedef std::vector<wxColour> wxColourVector;
typedef std::vector<wxImage::HSVValue> hsvVector;

class PaletteClass
{
private:
    wxColourVector color;
    hsvVector hsv;
public:

    void Set(wxColourVector& newcolors)
    {
        color=newcolors;
        hsv.clear();
        wxImage::RGBValue newrgb;
        wxImage::HSVValue newhsv;
        for(size_t i=0; i<newcolors.size(); i++) {
            newrgb.red=newcolors[i].Red();
            newrgb.green=newcolors[i].Green();
            newrgb.blue=newcolors[i].Blue();
            newhsv=wxImage::RGBtoHSV(newrgb);
            hsv.push_back(newhsv);
        }
    }

    size_t Size()
    {
        return color.size();
    }

    void GetColor(size_t idx, wxColour& c)
    {
        if (idx >= color.size()) {
            c.Set(255,255,255);
        } else {
            c=color[idx];
        }
    }

    void GetHSV(size_t idx, wxImage::HSVValue& c)
    {
        if (idx >= hsv.size()) {
            // white
            c.hue=0.0;
            c.saturation=0.0;
            c.value=1.0;
        } else {
            c=hsv[idx];
        }
    }
};


// for pixels in the pixel buffer
class PixelClass
{
    wxColour color[2];
    //int sparklecnt;

public:

    void SetColor(int Layer,wxColour& c)
    {
        color[Layer & 1]=c;
    }

    void Clear()
    {
        color[0].SetRGB(0);
        color[1].SetRGB(0);
    }

    void MixColors(MixTypes MixType, wxColour& c)
    {
        switch (MixType)
        {
            case Mix_Effect1:
                c=color[0];
                break;
            case Mix_Effect2:
                c=color[1];
                break;
            case Mix_Mask1:
                // first masks second
                if (color[0].GetRGB() == 0) {
                    c=color[1];
                } else {
                    c.Set(0);
                }
                break;
            case Mix_Mask2:
                // second masks first
                if (color[1].GetRGB() == 0) {
                    c=color[0];
                } else {
                    c.Set(0);
                }
                break;
            case Mix_Unmask1:
                // first unmasks second
                if (color[0].GetRGB() != 0) {
                    c=color[1];
                } else {
                    c.Set(0);
                }
                break;
            case Mix_Unmask2:
                // second unmasks first
                if (color[1].GetRGB() != 0) {
                    c=color[0];
                } else {
                    c.Set(0);
                }
                break;
            case Mix_Layered:
                if (color[1].GetRGB() == 0) {
                    c=color[0];
                } else {
                    c=color[1];
                }
                break;
                break;
            case Mix_Average:
                // only average when both colors are non-black
                if (color[0].GetRGB() == 0) {
                    c=color[1];
                } else if (color[1].GetRGB() == 0) {
                    c=color[0];
                } else {
                    c.Set( (color[0].Red()+color[1].Red())/2, (color[0].Green()+color[1].Green())/2, (color[0].Blue()+color[1].Blue())/2 );
                }
                break;
        }
    }
};


typedef std::vector<PixelClass> PixelVector;
typedef std::list<MeteorClass> MeteorList;


class PixelBufferClass : public ModelClass
{
private:
    PixelVector pixels; // this is the calculation buffer

    int sparkle_count;
    int CurrentLayer;  // 0 or 1
    MixTypes MixType;
    MeteorList meteors[2];
    PaletteClass palette[2];
    wxImage image[2];
    wxString PictureName[2];
    long state[2];

    void SetPixel(int x, int y, wxColour &color);
    void SetPixel(int x, int y, wxImage::HSVValue& hsv);
    void SetRangeColor(const wxImage::HSVValue& hsv1, const wxImage::HSVValue& hsv2, wxImage::HSVValue& newhsv);
    double RandomRange(double num1, double num2);
    void Color2HSV(const wxColour& color, wxImage::HSVValue& hsv);
    double rand01();
    wxByte ChannelBlend(wxByte c1, wxByte c2, double ratio);
    void Get2ColorBlend(int coloridx1, int coloridx2, double ratio, wxColour &color);
    void GetMultiColorBlend(double n, bool circular, wxColour &color);

public:
    PixelBufferClass();
    ~PixelBufferClass();
    void InitBuffer(wxXmlNode* ModelNode);
    void Clear();
    size_t GetColorCount(int layer);
    void SetMixType(const wxString& MixName);
    void SetPalette(int layer, wxColourVector& newcolors);
    void SetLayer(int newlayer, int period, int speed, bool ResetState);
    void SetSparkle(int freq);
    void RenderBars(int PaletteRepeat, int Direction, bool Highlight, bool Show3D);
    void RenderButterfly(int ColorScheme, int Style, int Chunks, int Skip);
    void RenderColorWash(bool HorizFade, bool VertFade, int RepeatCount);
    void RenderFire();
    void RenderGarlands(int GarlandType, int Spacing);
    void RenderLife(int Count, int Seed);
    void RenderMeteors(int MeteorType, int Count, int Length);
    void RenderPictures(int dir, const wxString& NewPictureName);
    void RenderSnowflakes();
    void RenderSnowstorm(int Count, int Length);
    void RenderSpirals(int PaletteRepeat, int Direction, int Rotation, int Thickness, bool Blend, bool Show3D);
    void RenderText(int Top, const wxString& Line1, const wxString& Line2, const wxString& FontString, int dir);
    void CalcOutput();
};

#endif // PIXELBUFFER_H
