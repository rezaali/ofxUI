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

#include "ofxUIWidgetWithLabel.h"
#include "ofxUIDefines.h"

class ofxUIButton : public ofxUIWidgetWithLabel
{
public:
    ofxUIButton();
    ofxUIButton(string _name, bool _value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    ofxUIButton(string _name, bool *_value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    ~ofxUIButton();
    virtual void init(string _name, bool *_value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    virtual void drawFill();
    virtual void mouseMoved(int x, int y);
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void stateChange();
	virtual void setParent(ofxUIWidget *_parent);
	bool getValue();
    virtual void setValue(bool _value);
    virtual void setValuePtr(bool *_value);
	void toggleValue();
    virtual bool isHit(float x, float y);
    void setLabelPosition(ofxUIWidgetPosition pos);
    virtual bool hasState(){ return false; };
protected:
    bool *value; 
    bool useReference; 
    bool bLabelRight; 
}; 