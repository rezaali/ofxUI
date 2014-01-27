/**********************************************************************************
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#include "ofxUISpacer.h"
#include "ofxUI.h"

ofxUISpacer::ofxUISpacer(float x, float y, float w, float h) : ofxUIWidget()
{
    init(x, y, w, h);
}

ofxUISpacer::ofxUISpacer(float x, float y, float w, float h, string _name) : ofxUIWidget()
{
    init(x, y, w, h);
    name = string(_name);
}

ofxUISpacer::ofxUISpacer(float w, float h) : ofxUIWidget()
{
    init(0, 0, w, h);
}

ofxUISpacer::ofxUISpacer(float w, float h, string _name) : ofxUIWidget()
{
    init(0, 0, w, h);
    name = string(_name);
}

void ofxUISpacer::init(float x, float y, float w, float h)
{
    initRect(x,y,w,h);
    name = string("OFX_UI_SPACER");
    kind = OFX_UI_WIDGET_SPACER;
    
    draw_fill = true;
    draw_back = false;
}

void ofxUISpacer::toggleColor()
{
    draw_fill = !draw_fill;
    draw_back = !draw_back;
}

void ofxUISpacer::setToggleColor(bool _value)
{
    if(_value)
    {
        draw_fill = true;
        draw_back = false;
    }
    else
    {
        draw_fill = false;
        draw_back = true;
    }
}