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

#include "ofxUIIntSlider.h"
#include "ofxUI.h"

ofxUIIntSlider::ofxUIIntSlider() : ofxUIWidgetWithLabel()
{
    
}

ofxUIIntSlider::ofxUIIntSlider(string _name, int _min, int _max, int _value, float w, float h, float x, float y) : ofxUIWidgetWithLabel()
{
    useReference = false;
    init(_name, _min, _max, &_value, w, h, x, y);
}

ofxUIIntSlider::ofxUIIntSlider(string _name, int _min, int _max, int *_value, float w, float h, float x, float y) : ofxUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _min, _max, _value, w, h, x, y);
}

ofxUIIntSlider::~ofxUIIntSlider()
{
    if(!useReference)
    {
        delete valueRef;
    }
}

void ofxUIIntSlider::init(string _name, int _min, int _max, int *_value, float w, float h, float x, float y)
{
    rect = new ofxUIRectangle(x,y,w,h);
    name = string(_name);
    if(w > h)
    {
        kind = OFX_UI_WIDGET_INTSLIDER_H;
    }
    else
    {
        kind = OFX_UI_WIDGET_INTSLIDER_V;
    }
    
    paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding);
    paddedRect->setParent(rect);
    
    draw_fill = true;
    
    value = *_value;                                               //the widget's value
    if(useReference)
    {
        valueRef = _value;
    }
    else
    {
        valueRef = new int();
        *valueRef = value;
    }
    
    max = _max;
    min = _min;
    
    if(value > max)
    {
        value = max;
    }
    if(value < min)
    {
        value = min;
    }
    
    if(kind == OFX_UI_WIDGET_INTSLIDER_H)
    {
        label = new ofxUILabel(0,h+padding,string(name+" LABEL"), string(name + ": " + ofxUIToString(max)), OFX_UI_FONT_SMALL);
    }
    else
    {
        label = new ofxUILabel(0,h+padding,string(name+" LABEL"), string(name), OFX_UI_FONT_SMALL);
    }
    
    label->setParent(label);
    label->setRectParent(rect);
    label->setEmbedded(true);
    increment = 1;
    bClampValue = true;
}

bool ofxUIIntSlider::getSetClampValue()
{
    return bClampValue;
}

void ofxUIIntSlider::setClampValue(bool _bClampValue)
{
    bClampValue = _bClampValue;
}

void ofxUIIntSlider::update()
{
    if(useReference)
    {
        value = *valueRef;
        if (bClampValue) {
            value = MAX(MIN(max, value), min);
        }
        
        updateLabel();
    }
}

void ofxUIIntSlider::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

void ofxUIIntSlider::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

void ofxUIIntSlider::drawBack()
{
    if(draw_back)
    {
        ofxUIFill();
        ofxUISetColor(color_back);
        rect->draw();
    }
}

void ofxUIIntSlider::drawOutline()
{
    if(draw_outline)
    {
        ofNoFill();
        ofxUISetColor(color_outline);
        rect->draw();
    }
}

void ofxUIIntSlider::drawOutlineHighlight()
{
    if(draw_outline_highlight)
    {
        ofNoFill();
        ofxUISetColor(color_outline_highlight);
        rect->draw();
    }
}

void ofxUIIntSlider::drawFill()
{
    if(draw_fill && value > 0)
    {
        ofxUIFill();
        ofxUISetColor(color_fill);
        if(kind == OFX_UI_WIDGET_INTSLIDER_H)
        {
            ofxUIDrawRect(rect->getX(), rect->getY(), rect->getWidth()*ofxUIMap(value, min, max, 0.0, 1.0, true), rect->getHeight());
        }
        else
        {
            ofxUIDrawRect(rect->getX(), rect->getY()+rect->getHeight(), rect->getWidth(), -rect->getHeight()*ofxUIMap(value, min, max, 0.0, 1.0, true));
        }
    }
}

void ofxUIIntSlider::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ofxUIFill();
        ofxUISetColor(color_fill_highlight);
        if(kind == OFX_UI_WIDGET_INTSLIDER_H)
        {
            ofxUIDrawRect(rect->getX(), rect->getY(), rect->getWidth()*ofxUIMap(value, min, max, 0.0, 1.0, true), rect->getHeight());
        }
        else
        {
            ofxUIDrawRect(rect->getX(), rect->getY()+rect->getHeight(), rect->getWidth(), -rect->getHeight()*ofxUIMap(value, min, max, 0.0, 1.0, true));
        }
        if(kind == OFX_UI_WIDGET_INTSLIDER_V)
        {
            label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*ofxUIMap(value, min, max, 0.0, 1.0, true), ofxUIToString(getValue()));
        }
    }
}

void ofxUIIntSlider::mouseMoved(int x, int y )
{
    if(rect->inside(x, y))
    {
        state = OFX_UI_STATE_OVER;
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUIIntSlider::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        state = OFX_UI_STATE_DOWN;
        input(x, y);
        triggerEvent(this);
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUIIntSlider::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        hit = true;
        state = OFX_UI_STATE_DOWN;
        input(x, y);
        triggerEvent(this);
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUIIntSlider::mouseReleased(int x, int y, int button)
{
    if(hit)
    {
#ifdef TARGET_OPENGLES
        state = OFX_UI_STATE_NORMAL;
#else
        state = OFX_UI_STATE_OVER;
#endif
        input(x, y);
        triggerEvent(this);
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
    hit = false;
}

void ofxUIIntSlider::keyPressed(int key)
{
    if(state == OFX_UI_STATE_OVER || state == OFX_UI_STATE_DOWN)
    {
        switch (key)
        {
            case OF_KEY_RIGHT:
                setValue(getValue()+increment);
                triggerEvent(this);
                break;
                
            case OF_KEY_UP:
                setValue(getValue()+increment);
                triggerEvent(this);
                break;
                
            case OF_KEY_LEFT:
                setValue(getValue()-increment);
                triggerEvent(this);
                break;
                
            case OF_KEY_DOWN:
                setValue(getValue()-increment);
                triggerEvent(this);
                break;
                
            default:
                break;
        }
    }
}

int ofxUIIntSlider::getIncrement()
{
    return increment;
}

void ofxUIIntSlider::setIncrement(int _increment)
{
    increment = _increment;
}

void ofxUIIntSlider::input(float x, float y)
{
    float valuePct;
    
    if(kind == OFX_UI_WIDGET_INTSLIDER_H)
    {
        valuePct = rect->percentInside(x, y).x;
    }
    else
    {
        valuePct = 1.0-rect->percentInside(x, y).y;
    }
    
    if(valuePct > 1.0)
    {
        valuePct = 1.0;
    }
    else if(valuePct < 0.0)
    {
        valuePct = 0.0;
    }
    
    value = ofxUIMap(valuePct, 0.0, 1.0, min, max, bClampValue);
    updateValueRef();
    updateLabel();
}

void ofxUIIntSlider::updateValueRef()
{
    (*valueRef) = getValue();
}

void ofxUIIntSlider::updateLabel()
{
    if(kind == OFX_UI_WIDGET_INTSLIDER_H)
    {
        label->setLabel(name + ": " + ofxUIToString(getValue()));
    }
}

void ofxUIIntSlider::stateChange()
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
            label->unfocus();
        }
            break;
        case OFX_UI_STATE_DOWN:
        {
            draw_fill_highlight = true;
            draw_outline_highlight = true;
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

void ofxUIIntSlider::setValue(int _value)
{
    if (bClampValue)
        value = MAX(MIN(max, _value), min);
    else
        value = _value;
    
    updateValueRef();
    updateLabel();
}

int ofxUIIntSlider::getValue()
{
    return value;
}

float ofxUIIntSlider::getPercentValue()
{
    return ofxUIMap(value, min, max, 0.0, 1.0, bClampValue);
}

ofxUILabel *ofxUIIntSlider::getLabel()
{
    return label;
}

void ofxUIIntSlider::setLabelVisible(bool _labelVisible)
{
    label->setVisible(_labelVisible);
    paddedRect->height -= label->getPaddingRect()->height;
}

void ofxUIIntSlider::setVisible(bool _visible)
{
    visible = _visible;
    label->setVisible(visible);
}

void ofxUIIntSlider::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    label->getRect()->setY(rect->getHeight()+padding);
    paddedRect->height = rect->getHeight() + label->getPaddingRect()->height + padding;
    paddedRect->x = -padding;
    paddedRect->y = -padding;
    if(label->getPaddingRect()->width > paddedRect->width)
    {
        paddedRect->width = label->getPaddingRect()->width;
    }
    updateValueRef();
    updateLabel();
}

void ofxUIIntSlider::setMax(int _max, bool bKeepValueTheSame)
{
    setMaxAndMin(_max, min, bKeepValueTheSame);
}

int ofxUIIntSlider::getMax()
{
    return max;
}

void ofxUIIntSlider::setMin(int _min, bool bKeepValueTheSame)
{
    setMaxAndMin(max, _min, bKeepValueTheSame);
}

int ofxUIIntSlider::getMin()
{
    return min;
}

ofxUIVec2f ofxUIIntSlider::getMaxAndMin()
{
    return ofxUIVec2f(max, min);
}

void ofxUIIntSlider::setMaxAndMin(int _max, int _min, bool bKeepValueTheSame)
{
    max = _max;
    min = _min;
    
    if(!bKeepValueTheSame)
    {
        value = ofxUIMap(value, 0, 1.0, min, max, bClampValue);
        value = ofxUIMap(value, min, max, 0.0, 1.0, bClampValue);
        updateValueRef();
        updateLabel();
    }
}

bool ofxUIIntSlider::isDraggable()
{
    return true;
}