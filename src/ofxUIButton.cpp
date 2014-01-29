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

#include "ofxUIButton.h"
#include "ofxUI.h"

ofxUIButton::ofxUIButton() : ofxUIWidgetWithLabel()
{
    
}

ofxUIButton::ofxUIButton(string _name, bool _value, float w, float h, float x, float y, int _size) : ofxUIWidgetWithLabel()
{
    useReference = false;
    init(_name, &_value, w, h, x, y, _size);
}

ofxUIButton::ofxUIButton(string _name, bool *_value, float w, float h, float x, float y, int _size) : ofxUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _value, w, h, x, y, _size);
}

ofxUIButton::~ofxUIButton()
{
    if(!useReference)
    {
        delete value;
    }
}

void ofxUIButton::init(string _name, bool *_value, float w, float h, float x, float y, int _size)
{
    initRect(x,y,w,h);
    name = string(_name);
    kind = OFX_UI_WIDGET_BUTTON;
    label = new ofxUILabel((name+" LABEL"),name,_size);
    addEmbeddedWidget(label);
    
    bLabelRight = true;
    
    if(useReference)
    {
        value = _value;
    }
    else
    {
        value = new bool();
        *value = *_value;
    }
    
    setValue(*_value);
}

void ofxUIButton::drawFill()
{
    if(*value)
    {
        ofxUIFill();
        ofxUISetColor(color_fill);
        rect->draw();
    }
}

void ofxUIButton::mouseMoved(int x, int y)
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

void ofxUIButton::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        if(rect->inside(x, y) || (label->isVisible() && label->getPaddingRect()->inside(x, y)))
        {
            state = OFX_UI_STATE_DOWN;
        }
        else
        {
            hit = false;
            state = OFX_UI_STATE_NORMAL;
            toggleValue();
            triggerEvent(this);
        }
        stateChange();
    }
}

void ofxUIButton::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y) || (label->isVisible() && label->getPaddingRect()->inside(x, y)))
    {
        hit = true;
        state = OFX_UI_STATE_DOWN;
        toggleValue();
        triggerEvent(this);
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUIButton::mouseReleased(int x, int y, int button)
{
    if(hit)
    {
#ifdef OFX_UI_TARGET_TOUCH
        state = OFX_UI_STATE_NORMAL;
#else
        if(rect->inside(x, y) || (label->isVisible() && label->getPaddingRect()->inside(x, y)))
        {
            state = OFX_UI_STATE_OVER;
        }
        else
        {
            state = OFX_UI_STATE_NORMAL;
        }
#endif
        toggleValue();
        triggerEvent(this);
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
    hit = false;
}

void ofxUIButton::stateChange()
{
    switch (state) {
        case OFX_UI_STATE_NORMAL:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
        case OFX_UI_STATE_OVER:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = true;
            label->focus();
        }
            break;
        case OFX_UI_STATE_DOWN:
        {
            draw_fill_highlight = true;
            draw_outline_highlight = false;
            label->focus();
        }
            break;
        case OFX_UI_STATE_SUSTAINED:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
            
        default:
            break;
    }
}

void ofxUIButton::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    ofxUIRectangle *labelrect = label->getRect();
    float h = labelrect->getHeight();
    float ph = rect->getHeight();
    labelrect->setX(rect->getWidth()+padding);
    labelrect->setY(ph/2.0 - h/2.0);
    calculatePaddingRect();
}

bool ofxUIButton::getValue()
{
    return *value;
}
void ofxUIButton::setValue(bool _value)
{
    *value = _value;
    draw_fill = *value;
}

void ofxUIButton::setValuePtr(bool *_value)
{
    if(!useReference)
    {
        delete value;
        useReference = true;
    }
    value = _value;
    setValue(*value);
}

void ofxUIButton::toggleValue()
{
    setValue(!(*value));
}

bool ofxUIButton::isHit(float x, float y)
{
    if(visible)
    {
        return (rect->inside(x, y) || (label->isVisible() && label->getPaddingRect()->inside(x, y)));
    }
    else
    {
        return false;
    }
}

void ofxUIButton::setLabelPosition(ofxUIWidgetPosition pos)
{
    switch (pos)
    {
        case OFX_UI_WIDGET_POSITION_LEFT:
        {
            bLabelRight = false;
            label->getRect()->setX(-label->getRect()->getWidth() - padding*2);
            calculatePaddingRect();
        }
            break;
            
        case OFX_UI_WIDGET_POSITION_RIGHT:
        {
            bLabelRight = true;
            label->getRect()->setX(rect->getWidth() + padding*2.0);
            calculatePaddingRect();
        }
            break;
            
        default:
            break;
    }
}