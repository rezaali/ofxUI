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

#include "ofxUIRotarySlider.h"
#include "ofxUI.h"

ofxUIRotarySlider::ofxUIRotarySlider(float x, float y, float w, float _min, float _max, float _value, string _name, int _size) : ofxUIWidgetWithLabel()
{
    useReference = false;
    init(x, y, w, _min, _max, &_value, _name, _size);
}

ofxUIRotarySlider::ofxUIRotarySlider(float w, float _min, float _max, float _value, string _name, int _size) : ofxUIWidgetWithLabel()
{
    useReference = false;
    init(0, 0, w, _min, _max, &_value, _name, _size);
}

ofxUIRotarySlider::ofxUIRotarySlider(float x, float y, float w, float _min, float _max, float *_value, string _name, int _size) : ofxUIWidgetWithLabel()
{
    useReference = true;
    init(x, y, w, _min, _max, _value, _name, _size);
}

ofxUIRotarySlider::ofxUIRotarySlider(float w, float _min, float _max, float *_value, string _name, int _size) : ofxUIWidgetWithLabel()
{
    useReference = true;
    init(0, 0, w, _min, _max, _value, _name, _size);
}

ofxUIRotarySlider::~ofxUIRotarySlider()
{
    if(!useReference)
    {
        delete valueRef;
    }
}

void ofxUIRotarySlider::init(float x, float y, float w, float _min, float _max, float *_value, string _name, int _size)
{
    initRect(x,y,w,w);
    name = string(_name);
    kind = OFX_UI_WIDGET_ROTARYSLIDER;
    
    draw_fill = true;
    
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
    
    if(value > max)
    {
        value = max;
    }
    if(value < min)
    {
        value = min;
    }
    
    outerRadius = rect->getWidth()*.5;
    innerRadius = rect->getWidth()*.25;
    
    value = ofxUIMap(value, min, max, 0.0, 1.0, true);
    valueString = ofxUIToString(getValue(),2);
    label = new ofxUILabel(0,w+padding,(name+" LABEL"), (name + ": " + valueString), _size);
    addEmbeddedWidget(label);
    increment = fabs(max - min) / 10.0;
}

void ofxUIRotarySlider::update()
{
    if(useReference)
    {
        value = ofxUIMap(*valueRef, min, max, 0.0, 1.0, true);
        updateLabel();
    }
}

void ofxUIRotarySlider::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

void ofxUIRotarySlider::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

void ofxUIRotarySlider::drawBack()
{
    if(draw_back)
    {
        ofxUIFill();
        ofxUISetColor(color_back);
        drawArcStrip(1.0);
    }
}

void ofxUIRotarySlider::drawFill()
{
    if(draw_fill)
    {
        ofxUIFill();
        ofxUISetColor(color_fill);
        drawArcStrip(value);
    }
}

void ofxUIRotarySlider::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ofxUIFill();
        ofxUISetColor(color_fill_highlight);
        drawArcStrip(value);
    }
}

void ofxUIRotarySlider::drawOutline()
{
    if(draw_outline)
    {
        ofNoFill();
        ofxUISetColor(color_outline);
        ofSetLineWidth(2.0);
        drawArcStrip(1.0);
        ofSetLineWidth(1.0);
    }
}
void ofxUIRotarySlider::drawOutlineHighlight()
{
    if(draw_outline_highlight)
    {
        ofNoFill();
        ofxUISetColor(color_outline_highlight);
        ofSetLineWidth(2.0);
        drawArcStrip(1.0);
        ofSetLineWidth(1.0);
    }
}

void ofxUIRotarySlider::mouseMoved(int x, int y )
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

void ofxUIRotarySlider::mouseDragged(int x, int y, int button)
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

void ofxUIRotarySlider::mousePressed(int x, int y, int button)
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

void ofxUIRotarySlider::mouseReleased(int x, int y, int button)
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

void ofxUIRotarySlider::keyPressed(int key)
{
    if(state == OFX_UI_STATE_OVER)
    {
        switch (key)
        {
            case OF_KEY_RIGHT:
                setValue(getScaledValue()+increment);
                triggerEvent(this);
                break;
                
            case OF_KEY_UP:
                setValue(getScaledValue()+increment);
                triggerEvent(this);
                break;
                
            case OF_KEY_LEFT:
                setValue(getScaledValue()-increment);
                triggerEvent(this);
                break;
                
            case OF_KEY_DOWN:
                setValue(getScaledValue()-increment);
                triggerEvent(this);
                break;
                
            default:
                break;
        }
    }
}

void ofxUIRotarySlider::drawArcStrip(float percent)
{
    float theta = ofxUIMap(percent, 0, 1, 0, 360.0, true);
    
    ofPushMatrix();
    ofTranslate(rect->getX(),rect->getY());
    
    ofBeginShape();
    
    {
        float x = sin(-ofDegToRad(0));
        float y = cos(-ofDegToRad(0));
        ofVertex(center.x+outerRadius*x,center.y+outerRadius*y);
    }
    
    for(int i = 0; i <= theta; i+=10)
    {
        float x = sin(-ofDegToRad(i));
        float y = cos(-ofDegToRad(i));
        
        ofVertex(center.x+outerRadius*x,center.y+outerRadius*y);
    }
    
    {
        float x = sin(-ofDegToRad(theta));
        float y = cos(-ofDegToRad(theta));
        ofVertex(center.x+outerRadius*x,center.y+outerRadius*y);
        ofVertex(center.x+innerRadius*x,center.y+innerRadius*y);
    }
    
    for(int i = theta; i >= 0; i-=10)
    {
        float x = sin(-ofDegToRad(i));
        float y = cos(-ofDegToRad(i));
        
        ofVertex(center.x+innerRadius*x,center.y+innerRadius*y);
    }
    
    {
        float x = sin(-ofDegToRad(0));
        float y = cos(-ofDegToRad(0));
        ofVertex(center.x+innerRadius*x,center.y+innerRadius*y);
    }
    
    ofEndShape();
    ofPopMatrix();
}

void ofxUIRotarySlider::setIncrement(float _increment)
{
    increment = _increment;
}

void ofxUIRotarySlider::input(float x, float y)
{
    hitPoint = ofxUIVec2f(x,y);
    ofVec2f mappedHitPoint = hitPoint;
    mappedHitPoint -= ofVec2f(rect->getX()+center.x, rect->getY()+center.y);
    
    ofVec2f cVector = center-homePoint;
    value = ofxUIMap(cVector.angle(mappedHitPoint), -180, 180, 0, 1.0, true);
    
    value = MIN(1.0, MAX(0.0, value));
    updateValueRef();
    updateLabel();
}

void ofxUIRotarySlider::updateValueRef()
{
    (*valueRef) = getScaledValue();
}

void ofxUIRotarySlider::updateLabel()
{
    valueString = ofxUIToString(getValue(),2);
    label->setLabel(name + ": " + valueString);
}

void ofxUIRotarySlider::stateChange()
{
    if(value > 0)
    {
        draw_fill = true;
    }
    else
    {
        draw_fill = false;
    }
    
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

void ofxUIRotarySlider::setValue(float _value)
{
    value = ofxUIMap(_value, min, max, 0.0, 1.0, true);
    updateValueRef();
    updateLabel();
}

float ofxUIRotarySlider::getValue()
{
    return (*valueRef); 
}

float ofxUIRotarySlider::getNormalizedValue()
{
    return value;
}

float ofxUIRotarySlider::getScaledValue()
{
    return ofxUIMap(value, 0.0, 1.0, min, max, true);
}

void ofxUIRotarySlider::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    calculatePaddingRect();
    center = ofxUIVec2f(rect->getWidth()*.5, rect->getHeight()*.5);
    homePoint = ofxUIVec2f(rect->getWidth()*.5, rect->getHeight());
}

bool ofxUIRotarySlider::isDraggable()
{
    return true;
}

void ofxUIRotarySlider::setMax(float _max)
{
    setMaxAndMin(_max, min);
}

float ofxUIRotarySlider::getMax()
{
    return max;
}

void ofxUIRotarySlider::setMin(float _min)
{
    setMaxAndMin(max, _min);
}

float ofxUIRotarySlider::getMin()
{
    return min;
}

ofVec2f ofxUIRotarySlider::getMaxAndMind()
{
    return ofVec2f(max, min);
}

void ofxUIRotarySlider::setMaxAndMin(float _max, float _min)
{
    max = _max;
    min = _min;
    
    value = ofxUIMap(value, 0, 1.0, min, max, true);
    value = ofxUIMap(value, min, max, 0.0, 1.0, true);
    updateValueRef();
    updateLabel();
}


bool ofxUIRotarySlider::isHit(float x, float y)
{
    float d = ofDist(x, y, rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight());
    if(visible &&  d < outerRadius && d > innerRadius)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#ifndef OFX_UI_NO_XML

void ofxUIRotarySlider::saveState(ofxXmlSettings *XML)
{
    XML->setValue("Value", getScaledValue(), 0);   
}

void ofxUIRotarySlider::loadState(ofxXmlSettings *XML)
{
    setValue(XML->getValue("Value", getScaledValue(), 0));
}

#endif