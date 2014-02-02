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

#include "ofxUI2DPad.h"
#include "ofxUI.h"

ofxUI2DPad::ofxUI2DPad(string _name, ofxUIVec3f _rangeX, ofxUIVec3f _rangeY, ofxUIVec3f _value, float w, float h, float x, float y) : ofxUIWidgetWithLabel()
{
    useReference = false;
    init(_name, _rangeX, _rangeY, &_value, w, h, x, y);
}

ofxUI2DPad::ofxUI2DPad(string _name, ofxUIVec3f _rangeX, ofxUIVec3f _rangeY, ofxUIVec3f *_value, float w, float h, float x, float y) : ofxUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _rangeX, _rangeY, _value, w, h, x, y);
}

ofxUI2DPad::~ofxUI2DPad()
{
    if(!useReference)
    {
        delete valueRef;
    }
}

void ofxUI2DPad::init(string _name, ofxUIVec3f _rangeX, ofxUIVec3f _rangeY, ofxUIVec3f *_value, float w, float h, float x, float y)
{
    initRect(x, y, w, h);
    name = string(_name);
    kind = OFX_UI_WIDGET_2DPAD;
    draw_fill = true;
    draw_outline = true;
    value = *_value;                                               //the widget's value
    if(useReference)
    {
        valueRef = _value;
    }
    else
    {
        valueRef = new ofxUIVec3f();
        *valueRef = value;
    }
    
    rangeX = _rangeX;
    rangeY = _rangeY;
    labelPrecision = 2;
    
    value.x = ofxUIMap(value.x, rangeX.x, rangeX.y, 0.0, 1.0, true);
    value.y = ofxUIMap(value.y, rangeY.x, rangeY.y, 0.0, 1.0, true);
    
    if(value.x > 1)
    {
        value.x = 1;
    }
    else if(value.x < 0)
    {
        value.x = 0;
    }
    
    if(value.y > 1)
    {
        value.y = 1;
    }
    else if(value.y < 0)
    {
        value.y = 0;
    }
    
    label = new ofxUILabel(0,h+padding*2.0,(name+" LABEL"), (name + ": " + ofxUIToString(getScaledValue().x,labelPrecision) + ", " + ofxUIToString(getScaledValue().y,labelPrecision)), OFX_UI_FONT_SMALL);
    addEmbeddedWidget(label);
    
    float horizontalRange = abs(rangeX.x - rangeX.y);
    float verticalRange = abs(rangeY.x - rangeY.y);
    increment = MIN(horizontalRange, verticalRange) / 10.0;
}

void ofxUI2DPad::update()
{
    if(useReference)
    {
        value.x = ofxUIMap(valueRef->x, rangeX.x, rangeX.y, 0.0, 1.0, true);
        value.y = ofxUIMap(valueRef->y, rangeY.x, rangeY.y, 0.0, 1.0, true);
    }
}

void ofxUI2DPad::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

void ofxUI2DPad::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

void ofxUI2DPad::drawFill()
{
    if(draw_fill)
    {
        ofxUIFill();
        ofxUISetColor(color_fill);
        ofxUISetRectMode(OFX_UI_RECTMODE_CENTER);
        ofxUIDrawRect(rect->getX()+value.x*rect->getWidth(), rect->getY()+value.y*rect->getHeight(), OFX_UI_GLOBAL_WIDGET_SPACING, OFX_UI_GLOBAL_WIDGET_SPACING);
        ofxUISetRectMode(OFX_UI_RECTMODE_CORNER);
        
        ofxUIDrawLine(rect->getX()+value.x*rect->getWidth(),  rect->getY(), rect->getX()+value.x*rect->getWidth(),  rect->getY()+rect->getHeight());
        ofxUIDrawLine(rect->getX(),  rect->getY()+value.y*rect->getHeight(), rect->getX()+rect->getWidth(),  rect->getY()+value.y*rect->getHeight());
    }
}

void ofxUI2DPad::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ofxUIFill();
        ofxUISetColor(color_fill_highlight);
        ofxUISetRectMode(OFX_UI_RECTMODE_CENTER);
        ofxUIDrawRect(rect->getX()+value.x*rect->getWidth(), rect->getY()+value.y*rect->getHeight(), OFX_UI_GLOBAL_WIDGET_SPACING, OFX_UI_GLOBAL_WIDGET_SPACING);
        ofxUISetRectMode(OFX_UI_RECTMODE_CORNER);
        
        ofxUIDrawLine(rect->getX()+value.x*rect->getWidth(),  rect->getY(), rect->getX()+value.x*rect->getWidth(),  rect->getY()+rect->getHeight());
        ofxUIDrawLine(rect->getX(),  rect->getY()+value.y*rect->getHeight(), rect->getX()+rect->getWidth(),  rect->getY()+value.y*rect->getHeight());
        
        label->drawString(rect->getX()+value.x*rect->getWidth()+OFX_UI_GLOBAL_WIDGET_SPACING, rect->getY()+value.y*rect->getHeight(), "(" +ofxUIToString(getScaledValue().x,labelPrecision) + ", " + ofxUIToString(getScaledValue().y,labelPrecision)+")");
    }
}

float ofxUI2DPad::getIncrement()
{
    return increment;
}

void ofxUI2DPad::setIncrement(float _increment)
{
    increment = _increment;
}

void ofxUI2DPad::mouseMoved(int x, int y )
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

void ofxUI2DPad::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        state = OFX_UI_STATE_DOWN;
        if(triggerType & OFX_UI_TRIGGER_CHANGE)
        {
            input(x, y);
            triggerEvent(this);
        }
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUI2DPad::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        hit = true;
        state = OFX_UI_STATE_DOWN;
        if(triggerType & OFX_UI_TRIGGER_BEGIN)
        {
            input(x, y);
            triggerEvent(this);
        }
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUI2DPad::mouseReleased(int x, int y, int button)
{
    if(hit)
    {
#ifdef OFX_UI_TARGET_TOUCH
        state = OFX_UI_STATE_NORMAL;
#else
        state = OFX_UI_STATE_OVER;
#endif
        if(triggerType & OFX_UI_TRIGGER_END)
        {
            input(x, y);
            triggerEvent(this);
        }
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
    hit = false;
}

void ofxUI2DPad::keyPressed(int key)
{
    if(state == OFX_UI_STATE_OVER)
    {
        switch (key)
        {
            case OF_KEY_RIGHT:
            {
                ofxUIVec3f p = getScaledValue();
                p.x+=increment;
                value.x = ofxUIMap(p.x, rangeX.x, rangeX.y, 0.0, 1.0, true);
                updateValueRef();
                updateLabel();
                triggerEvent(this);
            }
                break;
                
            case OF_KEY_UP:
            {
                ofxUIVec3f p = getScaledValue();
                p.y +=increment;
                value.y = ofxUIMap(p.y, rangeY.x, rangeY.y, 0.0, 1.0, true);
                updateValueRef();
                updateLabel();
                triggerEvent(this);
            }
                break;
                
            case OF_KEY_LEFT:
            {
                ofxUIVec3f p = getScaledValue();
                p.x-=increment;
                value.x = ofxUIMap(p.x, rangeX.x, rangeX.y, 0.0, 1.0, true);
                updateValueRef();
                updateLabel();
                triggerEvent(this);
            }
                break;
                
            case OF_KEY_DOWN:
            {
                ofxUIVec3f p = getScaledValue();
                p.y -=increment;
                value.y = ofxUIMap(p.y, rangeY.x, rangeY.y, 0.0, 1.0, true);
                updateValueRef();
                updateLabel();
                triggerEvent(this);
            }
                break;
                
            default:
                break;
        }
    }
}

void ofxUI2DPad::input(float x, float y)
{
    value.x = MIN(1.0, MAX(0.0, rect->percentInside(x, y).x));
    value.y = MIN(1.0, MAX(0.0, rect->percentInside(x, y).y));

    updateValueRef();
    updateLabel();
}

void ofxUI2DPad::updateValueRef()
{
    (*valueRef) = getScaledValue();
}

void ofxUI2DPad::updateLabel()
{
    label->setLabel(name + ": " + ofxUIToString(getScaledValue().x,labelPrecision) + ", " + ofxUIToString(getScaledValue().y,labelPrecision));
}

void ofxUI2DPad::stateChange()
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

void ofxUI2DPad::setValue(ofxUIVec3f _value)
{
    if(_value.x > rangeX.y)
    {
        _value.x = rangeX.y;
    }
    else if(_value.x < rangeX.x)
    {
        _value.x = rangeX.x;
    }
    
    if(_value.y > rangeY.y)
    {
        _value.y = rangeY.y;
    }
    else if(_value.y < rangeY.x)
    {
        _value.y = rangeY.x;
    }
    
    value.x = ofxUIMap(_value.x, rangeX.x, rangeX.y, 0.0, 1.0, true);
    value.y = ofxUIMap(_value.y, rangeY.x, rangeY.y, 0.0, 1.0, true);
    updateValueRef();
    updateLabel();
}

ofxUIVec3f ofxUI2DPad::getValue()
{
    return value;
}

ofxUIVec3f ofxUI2DPad::getPercentValue()
{
    return value;
}

ofxUIVec3f ofxUI2DPad::getScaledValue()
{
    ofxUIVec3f p = value;
    p.x = ofxUIMap(p.x, 0, 1, rangeX.x, rangeX.y, true);
    p.y = ofxUIMap(p.y, 0, 1, rangeY.x, rangeY.y, true);
    return p;
}

bool ofxUI2DPad::isDraggable()
{
    return true;
}

void ofxUI2DPad::setLabelPrecision(int _precision)
{
    labelPrecision = _precision;
    updateValueRef();
    updateLabel();
}

#ifndef OFX_UI_NO_XML

void ofxUI2DPad::saveState(ofxXmlSettings *XML)
{
    XML->setValue("XValue", getScaledValue().x, 0);
    XML->setValue("YValue", getScaledValue().y, 0);
}

void ofxUI2DPad::loadState(ofxXmlSettings *XML)
{
    setValue(ofxUIVec3f(XML->getValue("XValue", getScaledValue().x, 0), XML->getValue("YValue", getScaledValue().y, 0)));
}

#endif