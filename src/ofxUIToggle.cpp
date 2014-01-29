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

#include "ofxUIToggle.h"
#include "ofxUI.h"

ofxUIToggle::ofxUIToggle() : ofxUIButton()
{
    
}

ofxUIToggle::ofxUIToggle(string _name, bool _value, float w, float h, float x, float y, int _size)
: ofxUIButton( _name, _value, w, h, x, y, _size )
{
    kind = OFX_UI_WIDGET_TOGGLE;
}

ofxUIToggle::ofxUIToggle(string _name, bool *_value, float w, float h, float x, float y, int _size)
: ofxUIButton( _name, _value, w, h, x, y, _size )
{
    kind = OFX_UI_WIDGET_TOGGLE;
}

void ofxUIToggle::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

void ofxUIToggle::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

void ofxUIToggle::mouseMoved(int x, int y )
{
    if(rect->inside(x, y) || (label->isVisible() && label->getPaddingRect()->inside(x, y)))
    {
        state = OFX_UI_STATE_OVER;
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUIToggle::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        state = OFX_UI_STATE_DOWN;
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUIToggle::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y) || (label->isVisible() && label->getPaddingRect()->inside(x, y)))
    {
        hit = true;
        state = OFX_UI_STATE_DOWN;
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUIToggle::mouseReleased(int x, int y, int button)
{
    if((rect->inside(x, y) || (label->isVisible() && label->getPaddingRect()->inside(x, y))) && hit)
    {
        setValue(!(*value));
#ifdef OFX_UI_TARGET_TOUCH
        state = OFX_UI_STATE_NORMAL;
#else
        state = OFX_UI_STATE_OVER;
#endif
        triggerEvent(this);
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
    hit = false;
}

void ofxUIToggle::setParent(ofxUIWidget *_parent)
{
    ofxUIButton::setParent(_parent);
}

void ofxUIToggle::setValue(bool _value)
{
    *value = _value;
    draw_fill = *value;
}

#ifndef OFX_UI_NO_XML

void ofxUIToggle::saveState(ofxXmlSettings *XML)
{
    XML->setValue("Value", (getValue() ? 1 : 0), 0);
}

void ofxUIToggle::loadState(ofxXmlSettings *XML)
{
    int value = XML->getValue("Value", (getValue() ? 1 : 0), 0);
    setValue((value ? 1 : 0));
}

#endif