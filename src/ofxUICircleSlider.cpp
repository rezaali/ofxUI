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

#include "ofxUICircleSlider.h"
#include "ofxUI.h"

ofxUICircleSlider::ofxUICircleSlider(float x, float y, float w, float _min, float _max, float _value, string _name, int _size) : ofxUISlider()
{
    useReference = false;
    init(x, y, w, w, _min, _max, &_value, _name, _size);
}

ofxUICircleSlider::ofxUICircleSlider(float w, float _min, float _max, float _value, string _name, int _size) : ofxUISlider()
{
    useReference = false;
    init(0, 0, w, w, _min, _max, &_value, _name, _size);
}

ofxUICircleSlider::ofxUICircleSlider(float x, float y, float w, float _min, float _max, float *_value, string _name, int _size) : ofxUISlider()
{
    useReference = true;
    init(x, y, w, w, _min, _max, _value, _name, _size);
}

ofxUICircleSlider::ofxUICircleSlider(float w, float _min, float _max, float *_value, string _name, int _size) : ofxUISlider()
{
    useReference = true;
    init(0, 0, w, w, _min, _max, _value, _name, _size);
}

void ofxUICircleSlider::init(float x, float y, float w, float h, float _min, float _max, float *_value, string _name, int _size)
{
    initRect(x,y,w,h);
    name = string(_name);
    kind = OFX_UI_WIDGET_CIRCLESLIDER;
    
    draw_fill = true;
    draw_outline = true;
    
    value = *_value;                                               //the widget's value
    if(useReference)
    {
        valueRef = _value;
    }
    else
    {
        valueRef = new float();
        *valueRef = value;
    }
    
    max = _max;
    min = _min;
    labelPrecision = 2;
    increment = .0005;
    inputDirection = OFX_UI_DIRECTION_SOUTHNORTH;
    
    if(value > max)
    {
        value = max;
    }
    if(value < min)
    {
        value = min;
    }
    
    value = ofxUIMap(value, min, max, 0.0, 1.0, true);
    
    label = new ofxUILabel(0,w+padding,(name+" LABEL"), name, _size);
    addEmbeddedWidget(label);
}


void ofxUICircleSlider::drawBack()
{
    if(draw_back)
    {
        ofxUIFill();
        ofxUISetColor(color_back);
        ofxUICircle(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight(), rect->getHalfWidth());
    }
}

void ofxUICircleSlider::drawOutline()
{
    if(draw_outline)
    {
        ofNoFill();
        ofxUISetColor(color_outline);
        ofxUICircle(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight(), rect->getHalfWidth());
    }
}

void ofxUICircleSlider::drawFill()
{
    if(draw_fill)
    {
        ofxUIFill();
        ofxUISetColor(color_fill);
        ofxUICircle(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight(), value*rect->getHalfWidth());
    }
}

void ofxUICircleSlider::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ofxUIFill();
        ofxUISetColor(color_fill_highlight);
        ofxUICircle(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight(), value*rect->getHalfWidth());
        ofxUISetColor(label->getColorFillHighlight());
        label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*.5, ofxUIToString(getScaledValue(),labelPrecision));
    }
}

void ofxUICircleSlider::drawOutlineHighlight()
{
    if(draw_outline_highlight)
    {
        ofNoFill();
        ofxUISetColor(color_outline_highlight);
        ofxUICircle(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight(), rect->getHalfWidth());
        if(!draw_fill_highlight)
        {
            ofxUISetColor(label->getColorFill());
            label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*.5, ofxUIToString(getScaledValue(),labelPrecision));
        }
    }
}

void ofxUICircleSlider::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        if(triggerType & OFX_UI_TRIGGER_CHANGE)
        {
            switch(inputDirection)
            {
                case OFX_UI_DIRECTION_NORTHSOUTH:
                    value -= increment*(hitPoint.y-y);
                    valueClamp();
                    break;
                case OFX_UI_DIRECTION_SOUTHNORTH:
                    value += increment*(hitPoint.y-y);
                    valueClamp();
                    break;
                case OFX_UI_DIRECTION_EASTWEST:
                    value += increment*(hitPoint.x-x);
                    valueClamp();
                    break;
                case OFX_UI_DIRECTION_WESTEAST:
                    value -= increment*(hitPoint.x-x);
                    valueClamp();
                    break;
            }
            
            hitPoint = ofxUIVec2f(x,y);
            updateValueRef();
            triggerEvent(this);
        }
        state = OFX_UI_STATE_DOWN;
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUICircleSlider::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        hit = true;
        hitPoint = ofxUIVec2f(x,y);
        state = OFX_UI_STATE_DOWN;
        if(triggerType & OFX_UI_TRIGGER_BEGIN)
        {
            triggerEvent(this);
        }
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUICircleSlider::mouseReleased(int x, int y, int button)
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

void ofxUICircleSlider::valueClamp()
{
    value = MIN(1.0, MAX(0.0, value));
}

void ofxUICircleSlider::setInputDirection(ofxUIWidgetInputDirection _inputDirection)
{
    inputDirection = _inputDirection;
}

void ofxUICircleSlider::updateLabel()
{
    
}

void ofxUICircleSlider::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    ofxUIRectangle *labelrect = label->getRect();
    while(labelrect->getWidth() > rect->getWidth())
    {
        string labelstring = label->getLabel();
        string::iterator it;
        it=labelstring.end();
        it--;
        labelstring.erase (it);
        label->setLabel(labelstring);
    }
    
    float w = labelrect->getWidth();
    float pw = rect->getWidth();
    labelrect->setX((int)(pw*.5 - w*.5-padding*.5)); 
    calculatePaddingRect();
}

bool ofxUICircleSlider::isHit(float x, float y)
{
    if(visible && ofDist(x, y, rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight()) < rect->getHalfWidth())
    {
        return true;
    }
    else
    {
        return false;
    }
}