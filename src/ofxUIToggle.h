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

#include "ofxUIButton.h"

class ofxUIToggle : public ofxUIButton
{
public:
    ofxUIToggle();
    ofxUIToggle(string _name, bool _value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    ofxUIToggle(string _name, bool *_value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
	virtual void setParent(ofxUIWidget *_parent);
    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    virtual void mouseMoved(int x, int y );
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void setValue(bool _value);
    bool hasState(){ return true; };
#ifndef OFX_UI_NO_XML
    virtual void saveState(ofxXmlSettings *XML);
    virtual void loadState(ofxXmlSettings *XML);
#endif
};