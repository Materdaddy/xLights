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
#include <cmath>

PixelBufferClass::PixelBufferClass()
{
}

PixelBufferClass::~PixelBufferClass()
{
}

void PixelBufferClass::SetWindow(wxScrolledWindow* ScrolledWindow)
{
    DrawWindow = ScrolledWindow;
}

void PixelBufferClass::InitBuffer(wxXmlNode* ModelNode)
{
    size_t i;
    wxClientDC dc(DrawWindow);
    dc.Clear();
    SetFromXml(ModelNode);
    pixels.resize(BufferHt * BufferWi);
    size_t NodeCount=GetNodeCount();
    uint8_t offset_r=RGBorder.find(wxT("R"));
    uint8_t offset_g=RGBorder.find(wxT("G"));
    uint8_t offset_b=RGBorder.find(wxT("B"));
    for(i=0; i<NodeCount; i++) {
        Nodes[i].SetOffset(offset_r, offset_g, offset_b);
        Nodes[i].sparkle = rand() % 10000;
    }
    for(i=0; i<2; i++) {
        BarState[i]=0;
        ButterflyState[i]=0;
        ColorWashState[i]=0;
        GarlandsState[i]=0;
        MeteorState[i]=0;
        SpiralState[i]=0;
    }
}

// return a random number between 0 and 1 inclusive
double PixelBufferClass::rand01()
{
    return (double)rand()/(double)RAND_MAX;
}

// generates a random number between num1 and num2 inclusive
double PixelBufferClass::RandomRange(double num1, double num2)
{
    double hi,lo;
    if (num1 < num2) {
        lo = num1;
        hi = num2;
    } else {
        lo = num2;
        hi = num1;
    }
    return rand01()*(hi-lo)+ lo;
}

// sets newcolor to a random color between hsv1 and hsv2
void PixelBufferClass::SetRangeColor(const wxImage::HSVValue& hsv1, const wxImage::HSVValue& hsv2, wxImage::HSVValue& newhsv)
{
    newhsv.hue=RandomRange(hsv1.hue,hsv2.hue);
    newhsv.saturation=RandomRange(hsv1.saturation,hsv2.saturation);
    newhsv.value=1.0;
}

void PixelBufferClass::Color2HSV(const wxColour& color, wxImage::HSVValue& hsv)
{
    wxImage::RGBValue rgb(color.Red(),color.Green(),color.Blue());
    hsv=wxImage::RGBtoHSV(rgb);
}

// 0,0 is lower left
void PixelBufferClass::SetPixel(int layer, int x, int y, wxColour &color)
{
    if (x >= 0 && x < BufferWi && y >= 0 && y < BufferHt) {
        pixels[y*BufferWi+x].SetColor(layer,color);
    }
}

void PixelBufferClass::SetPixel(int layer, int x, int y, wxImage::HSVValue& hsv)
{
    wxImage::RGBValue rgb = wxImage::HSVtoRGB(hsv);
    wxColour color(rgb.red,rgb.green,rgb.blue);
    SetPixel(layer,x,y,color);
}

void PixelBufferClass::Clear()
{
    for(size_t i=0; i<pixels.size(); i++) {
        pixels[i].Clear();
    }
}

// convert MixName to MixType enum
void PixelBufferClass::SetMixType(wxString& MixName)
{
    if (MixName == wxT("Effect 1")) {
        MixType=Mix_Effect1;
    } else if (MixName == wxT("Effect 2")) {
        MixType=Mix_Effect2;
    } else if (MixName == wxT("1 is Mask")) {
        MixType=Mix_Mask1;
    } else if (MixName == wxT("2 is Mask")) {
        MixType=Mix_Mask2;
    } else if (MixName == wxT("Layered")) {
        MixType=Mix_Layered;
    } else if (MixName == wxT("Average")) {
        MixType=Mix_Average;
    }
}

void PixelBufferClass::SetPalette(int layer, wxColourVector& newcolors)
{
    palette[layer].Set(newcolors);
}

size_t PixelBufferClass::GetColorCount(int layer)
{
    size_t colorcnt=palette[layer].Size();
    if (colorcnt < 1) colorcnt=1;
    return colorcnt;
}

// return a value between c1 and c2
wxByte PixelBufferClass::ChannelBlend(wxByte c1, wxByte c2, double ratio)
{
    return c1 + floor(ratio*(c2-c1)+0.5);
}

void PixelBufferClass::Get2ColorBlend(int layer, int coloridx1, int coloridx2, double ratio, wxColour &color)
{
    wxColour c1,c2;
    palette[layer].GetColor(coloridx1,c1);
    palette[layer].GetColor(coloridx2,c2);
    color.Set(ChannelBlend(c1.Red(),c2.Red(),ratio), ChannelBlend(c1.Green(),c2.Green(),ratio), ChannelBlend(c1.Blue(),c2.Blue(),ratio));
}

// 0 <= n < 1
void PixelBufferClass::GetMultiColorBlend(int layer, double n, bool circular, wxColour &color)
{
    /*
    // debug
    wxClientDC dc(DrawWindow);
    wxString msg=wxString::Format(wxT("%6.4f"),n);
    wxColour txtcolor(255,255,255);
    dc.Clear();
    dc.SetTextForeground(txtcolor);
    dc.DrawText(msg,0,0);
    */
    size_t colorcnt=GetColorCount(layer);
    if (colorcnt <= 1) {
        palette[layer].GetColor(0,color);
        return;
    }
    if (n >= 1.0) n=0.99999;
    if (n < 0.0) n=0.0;
    double realidx=circular ? n*colorcnt : n*(colorcnt-1);
    int coloridx1=floor(realidx);
    int coloridx2=(coloridx1+1) % colorcnt;
    double ratio=realidx-double(coloridx1);
    Get2ColorBlend(layer,coloridx1,coloridx2,ratio,color);
}

// 10-200 or so, or 0 for no sparkle
void PixelBufferClass::SetSparkle(int freq)
{
    sparkle_count=freq;
}

void PixelBufferClass::SetSpeed(int newspeed)
{
    Speed=newspeed;
}

void PixelBufferClass::RenderBars(int layer, int BarCount, int Direction, bool Highlight, bool Show3D)
{
    int x,y,n,pixel_ratio,ColorIdx;
    bool IsMovingDown,IsHighlightRow;
    wxImage::HSVValue hsv;
    size_t colorcnt=GetColorCount(layer);
    int BarWidth = BufferHt/BarCount+1;
    int HalfHt = BufferHt/2;
    BarState[layer]+=Speed;
    int f_offset = BarState[layer]/4 % BufferHt;
    for (x=0; x<BufferWi; x++) {
        for (y=0; y<BufferHt; y++) {
            ColorIdx=(y/BarWidth) % colorcnt;
            palette[layer].GetHSV(ColorIdx, hsv);
            switch (Direction) {
                case 1: IsMovingDown=true; break;
                case 2: IsMovingDown=(y <= HalfHt); break;
                case 3: IsMovingDown=(y > HalfHt); break;
                default: IsMovingDown=false; break;
            }
            if (IsMovingDown) {
                n=y-f_offset;
                pixel_ratio = BarWidth - y%BarWidth;
                IsHighlightRow=y % BarWidth == 0;
            } else {
                n=y+f_offset;
                pixel_ratio = y%BarWidth;
                IsHighlightRow=(y % BarWidth == BarWidth-1) || (y == BufferHt-1);
            }
            if (Highlight && IsHighlightRow) hsv.saturation=0.0;
            if (Show3D) hsv.value *= double(pixel_ratio) / BarWidth;
            n=n % BufferHt;
            if (n < 0) n+=BufferHt;
            SetPixel(layer,x,n,hsv);
        }
    }
}

void PixelBufferClass::RenderButterfly(int layer, int ColorScheme, int Style, int Chunks, int Skip)
{
    int x,y,d;
    double n,x1,y1,f;
    double h=0.0;
    static const double pi2=6.283185307;
    wxColour color;
    wxImage::HSVValue hsv;
    int maxframe=BufferHt*2;
    ButterflyState[layer]+=Speed;
    int frame=(BufferHt * ButterflyState[layer] / 200)%maxframe;
    double offset=double(ButterflyState[layer])/100.0;

    for (x=0; x<BufferWi; x++) {
        for (y=0; y<BufferHt; y++) {
            switch (Style) {
                case 1:
                    n = abs((x*x - y*y) * sin (offset + ((x+y)*pi2 / (BufferHt+BufferWi))));
                    d = x*x + y*y+1;
                    h=n/d;
                    break;
                case 2:
                    f=(frame < maxframe/2) ? frame+1 : maxframe - frame;
                    x1=(double(x)-BufferWi/2.0)/f;
                    y1=(double(y)-BufferHt/2.0)/f;
                    h=sqrt(x1*x1+y1*y1);
                    break;
                case 3:
                    f=(frame < maxframe/2) ? frame+1 : maxframe - frame;
                    f=f*0.1+double(BufferHt)/60.0;
                    x1 = (x-BufferWi/2.0)/f;
                    y1 = (y-BufferHt/2.0)/f;
                    h=sin(x1) * cos(y1);
                    break;
            }
            hsv.saturation=1.0;
            hsv.value=1.0;
            if (Chunks <= 1 || int(h*Chunks) % Skip != 0) {
                if (ColorScheme == 0) {
                    hsv.hue=h;
                    SetPixel(layer,x,y,hsv);
                } else {
                    GetMultiColorBlend(layer,h,false,color);
                    SetPixel(layer,x,y,color);
                }
            }
        }
    }
}

void PixelBufferClass::RenderColorWash(int layer, bool HorizFade, bool VertFade)
{
    int x,y;
    wxColour color;
    wxImage::HSVValue hsv,hsv2;
    size_t colorcnt=GetColorCount(layer);
    int CycleLen=colorcnt*100;
    ColorWashState[layer]+=Speed;
    double ratio= double(ColorWashState[layer]/4 % CycleLen) / double(CycleLen);
    GetMultiColorBlend(layer, ratio, true, color);
    Color2HSV(color,hsv);
    double HalfHt=double(BufferHt-1)/2.0;
    double HalfWi=double(BufferWi-1)/2.0;
    for (x=0; x<BufferWi; x++) {
        for (y=0; y<BufferHt; y++) {
            hsv2=hsv;
            if (HorizFade) hsv2.value*=1.0-abs(HalfWi-x)/HalfWi;
            if (VertFade) hsv2.value*=1.0-abs(HalfHt-y)/HalfHt;
            SetPixel(layer,x,y,hsv2);
        }
    }
}

void PixelBufferClass::RenderFire(int layer)
{

}

void PixelBufferClass::RenderGarlands(int layer, int GarlandType, int Spacing)
{
    int x,y,yadj,ylimit,ring;
    double ratio;
    wxColour color;
    int PixelSpacing=Spacing*BufferHt/100+3;
    int limit=BufferHt*PixelSpacing*4;
    GarlandsState[layer]=(GarlandsState[layer] + Speed) % limit;
    // ring=0 is the top ring
    for (ring=0; ring<BufferHt; ring++) {
        ratio=double(ring)/double(BufferHt);
        GetMultiColorBlend(layer, ratio, false, color);
        y=(limit - GarlandsState[layer])/4 - ring*PixelSpacing;
        ylimit=BufferHt-ring-1;
        for (x=0; x<BufferWi; x++) {
            yadj=y;
            switch (GarlandType) {
                case 1:
                    switch (x%5) {
                        case 2: yadj-=2; break;
                        case 1:
                        case 3: yadj-=1; break;
                    }
                    break;
                case 2:
                    switch (x%5) {
                        case 2: yadj-=4; break;
                        case 1:
                        case 3: yadj-=2; break;
                    }
                    break;
                case 3:
                    switch (x%6) {
                        case 3: yadj-=6; break;
                        case 2:
                        case 4: yadj-=4; break;
                        case 1:
                        case 5: yadj-=2; break;
                    }
                    break;
                case 4:
                    switch (x%5) {
                        case 1:
                        case 3: yadj-=2; break;
                    }
                    break;
            }
            if (yadj < ylimit) yadj=ylimit;
            if (yadj < BufferHt) SetPixel(layer,x,yadj,color);
        }
    }
}

void PixelBufferClass::RenderLife(int layer, int Count, int Seed)
{

}

void PixelBufferClass::RenderMeteors(int layer, int MeteorType, int Count, int Length)
{
    MeteorState[layer]+=Speed;
    int mspeed=MeteorState[layer]/4;
    MeteorState[layer]-=mspeed*4;

    // create new meteors
    MeteorClass m;
    wxImage::HSVValue hsv,hsv0,hsv1;
    palette[layer].GetHSV(0,hsv0);
    palette[layer].GetHSV(1,hsv1);
    size_t colorcnt=GetColorCount(layer);
    Count=BufferWi * Count / 100;
    int TailLength=(BufferHt < 10) ? Length / 10 : BufferHt * Length / 100;
    if (TailLength < 1) TailLength=1;
    int TailStart=BufferHt - TailLength;
    if (TailStart < 1) TailStart=1;
    for(int i=0; i<Count; i++) {
        m.x=rand() % BufferWi;
        m.y=BufferHt - 1 - rand() % TailStart;
        switch (MeteorType) {
            case 1:
                SetRangeColor(hsv0,hsv1,m.hsv);
                break;
            case 2:
                palette[layer].GetHSV(rand()%colorcnt, m.hsv);
                break;
        }
        meteors[layer].push_back(m);
    }

    // render meteors
    for (MeteorList::iterator it=meteors[layer].begin(); it!=meteors[layer].end(); ++it) {
        for(int ph=0; ph<TailLength; ph++) {
            switch (MeteorType) {
                case 0:
                    hsv.hue=double(rand() % 1000) / 1000.0;
                    hsv.saturation=1.0;
                    hsv.value=1.0;
                    break;
                default:
                    hsv=it->hsv;
                    break;
            }
            hsv.value*=1.0 - double(ph)/TailLength;
            SetPixel(layer,it->x,it->y+ph,hsv);
        }
        it->y -= mspeed;
    }

    // delete old meteors
    meteors[layer].remove_if(MeteorHasExpired(TailLength));
}

void PixelBufferClass::RenderPictures(int layer, int dir, const wxString& NewPictureName)
{
    const int speedfactor=4;
    if (NewPictureName != PictureName[layer]) {
        if (!image[layer].LoadFile(NewPictureName)) {
            //wxMessageBox("Error loading image file: "+NewPictureName);
            image[layer].Clear();
        }
        PictureName[layer]=NewPictureName;
    }
    if (!image[layer].IsOk()) return;
    int imgwidth=image[layer].GetWidth();
    int imght=image[layer].GetHeight();
    int yoffset=(BufferHt+imght)/2;
    int xoffset=(imgwidth-BufferWi)/2;
    int limit=(dir < 2) ? imgwidth+BufferWi : imght+BufferHt;
    PictureState[layer]=(PictureState[layer]+Speed) % (limit*speedfactor);
    int movement=PictureState[layer]/speedfactor;

    // copy image to buffer
    wxColour c;
    for(int x=0; x<imgwidth; x++) {
        for(int y=0; y<imght; y++) {
            if (!image[layer].IsTransparent(x,y)) {
                c.Set(image[layer].GetRed(x,y),image[layer].GetGreen(x,y),image[layer].GetBlue(x,y));
                switch (dir) {
                    case 0:
                        // left
                        SetPixel(layer,x+BufferWi-movement,yoffset-y,c);
                        break;
                    case 1:
                        // right
                        SetPixel(layer,x+movement-imgwidth,yoffset-y,c);
                        break;
                    case 2:
                        // up
                        SetPixel(layer,x-xoffset,movement-y,c);
                        break;
                    case 3:
                        // down
                        SetPixel(layer,x-xoffset,BufferHt+imght-y-movement,c);
                        break;
                    default:
                        // no movement - centered
                        SetPixel(layer,x-xoffset,yoffset-y,c);
                        break;
                }
            }
        }
    }
}

void PixelBufferClass::RenderSnowflakes(int layer)
{

}

void PixelBufferClass::RenderSnowstorm(int layer, int Count, int Length)
{

}

void PixelBufferClass::RenderSpirals(int layer, int Count, int Direction, int Rotation, int Thickness, bool Blend, bool Show3D)
{
    int strand_base,strand,thick,x,y,ColorIdx;
    int deltaStrands=BufferWi / Count;
    int SpiralThickness=(deltaStrands * Thickness / 100) + 1;
    size_t colorcnt=GetColorCount(layer);
    SpiralState[layer]+=Speed*Direction;
    wxImage::HSVValue hsv;
    wxColour color;
    for(int ns=0; ns < Count; ns++) {
        strand_base=ns * deltaStrands;
        ColorIdx=ns % colorcnt;
        palette[layer].GetColor(ColorIdx,color);
        for(thick=0; thick < SpiralThickness; thick++) {
            strand = (strand_base + thick) % BufferWi;
            for(y=0; y < BufferHt; y++) {
                x=(strand + SpiralState[layer]/10 + y*Rotation/BufferHt) % BufferWi;
                if (x < 0) x += BufferWi;
                if (Blend) {
                    GetMultiColorBlend(layer, double(BufferHt-y-1)/double(BufferHt), false, color);
                }
                if (Show3D) {
                    Color2HSV(color,hsv);
                    if (Rotation < 0)  {
                        hsv.value*=double(thick+1)/SpiralThickness;
                    } else {
                        hsv.value*=double(SpiralThickness-thick)/SpiralThickness;
                    }
                    SetPixel(layer,x,y,hsv);
                } else {
                    SetPixel(layer,x,y,color);
                }
            }
        }
    }
}

void PixelBufferClass::RenderText(int layer, int Top, const wxString& Line1, const wxString& Line2, const wxString& FontString)
{
    wxColour c;
    wxBitmap bitmap(BufferWi,BufferHt);
    wxMemoryDC dc(bitmap);
    wxFont font;
    font.SetNativeFontInfoUserDesc(FontString);
    dc.SetFont(font);
    palette[layer].GetColor(0,c);
    dc.SetTextForeground(c);
    wxString msg = Line1;
    if (!Line2.IsEmpty()) msg+=wxT("\n")+Line2;
    wxSize sz1 = dc.GetTextExtent(Line1);
    wxSize sz2 = dc.GetTextExtent(Line2);
    int maxwidth=sz1.GetWidth() > sz2.GetWidth() ? sz1.GetWidth() : sz2.GetWidth();
    int dctop=Top * BufferHt / 50 - BufferHt/2;
    int limit=(BufferWi+maxwidth)*8 + 1;
    TextState[layer]=(TextState[layer] + Speed) % limit;
    dc.DrawText(msg,BufferWi-TextState[layer]/8,dctop);

    // copy dc to buffer
    for(wxCoord x=0; x<BufferWi; x++) {
        for(wxCoord y=0; y<BufferHt; y++) {
            dc.GetPixel(x,BufferHt-y-1,&c);
            SetPixel(layer,x,y,c);
        }
    }
}

void PixelBufferClass::DisplayOutput()
{
    wxPen pen;
    wxClientDC dc(DrawWindow);
    wxColour color;
    wxCoord w, h;
    static wxCoord lastw, lasth;
    dc.GetSize(&w, &h);
    if (w!=lastw || h!=lasth) {
        // window was resized
        dc.Clear();
        lastw=w;
        lasth=h;
    }
    dc.SetAxisOrientation(true,true);
    if (RenderHt==1) {
        dc.SetDeviceOrigin(w/2,h/2); // set origin at center
    } else {
        dc.SetDeviceOrigin(w/2,h-1); // set origin at bottom center
    }
    double scaleX = double(w) / RenderWi;
    double scaleY = double(h) / RenderHt;
    double scale=scaleY < scaleX ? scaleY : scaleX;
    //scale=0.25;
    dc.SetUserScale(scale,scale);

/*
        // check that origin is in the right place
        dc.SetUserScale(4,4);
        color.Set(0,0,255);
        pen.SetColour(color);
        dc.SetPen(pen);
        dc.DrawPoint(0,0);
        dc.DrawPoint(1,1);
        dc.DrawPoint(2,2);
        return;
*/
    // layer calculation and map to output
    size_t NodeCount=Nodes.size();
    for(size_t i=0; i<NodeCount; i++) {
        if (Nodes[i].bufX < 0) {
            // unmapped pixel - set to black
            Nodes[i].SetColor(0,0,0);
        } else {
            // get blend of two effects
            pixels[Nodes[i].bufY*BufferWi+Nodes[i].bufX].MixColors(MixType,color);
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
            // draw node on screen
            pen.SetColour(color);
            dc.SetPen(pen);
            //dc.DrawCircle(Nodes[i].screenX, Nodes[i].screenY,1);
            dc.DrawPoint(Nodes[i].screenX, Nodes[i].screenY);
        }
    }
}
