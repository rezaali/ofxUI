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

#pragma once

#include "ofxUIToggle.h"
#include "ofxUIDefines.h"

class ofxUIMultiImageToggle : public ofxUIToggle
{
public:        
    ofxUIMultiImageToggle(float x, float y, float w, float h, bool _value, string _pathURL, string _name,  int _size = OFX_UI_FONT_SMALL);
    ofxUIMultiImageToggle(float w, float h, bool _value, string _pathURL, string _name, int _size = OFX_UI_FONT_SMALL);
    ofxUIMultiImageToggle(float x, float y, float w, float h, bool *_value, string _pathURL, string _name,  int _size = OFX_UI_FONT_SMALL);
    ofxUIMultiImageToggle(float w, float h, bool *_value, string _pathURL, string _name, int _size = OFX_UI_FONT_SMALL);
    ~ofxUIMultiImageToggle();
    void init(float x, float y, float w, float h, bool *_value, string _pathURL, string _name, int _size = OFX_UI_FONT_SMALL);
    void drawBack();
    void drawOutlineHighlight();
    void drawFill();
    void drawFillHighlight();
    virtual void stateChange();
    virtual void setValue(bool _value);
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    ofImage *back; 
    ofImage *over; 
    ofImage *down;
    ofImage *on; 
}; 