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

#include "ofxUIRangeSlider.h"
#include "ofxUI.h"

ofxUIRangeSlider::ofxUIRangeSlider(string _name, float _min, float _max, float _valuelow, float _valuehigh, float w, float h,
                 float x, float y, int _size) : ofxUIWidgetWithLabel()
{
    useReference = false;
    init(_name, _min, _max, &_valuelow, &_valuehigh, w, h, x, y, _size);
}

ofxUIRangeSlider::ofxUIRangeSlider(string _name, float _min, float _max, float *_valuelow, float *_valuehigh, float w, float h,
                 float x, float y, int _size) : ofxUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _min, _max, _valuelow, _valuehigh, w, h, x, y, _size);
}

ofxUIRangeSlider::ofxUIRangeSlider(float x, float y, float w, float h, float _min, float _max, float _valuelow, float _valuehigh, string _name, int _size) : ofxUIWidgetWithLabel()
{
    useReference = false;
    init(_name, _min, _max, &_valuelow, &_valuehigh, w, h, x, y, _size);
    //        ofLogWarning("OFXUIRANGESLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUIRangeSlider::ofxUIRangeSlider(float w, float h, float _min, float _max, float _valuelow, float _valuehigh, string _name, int _size) : ofxUIWidgetWithLabel()
{
    useReference = false;
    init(_name, _min, _max, &_valuelow, &_valuehigh, w, h, 0, 0, _size);
    //        ofLogWarning("OFXUIRANGESLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUIRangeSlider::ofxUIRangeSlider(float x, float y, float w, float h, float _min, float _max, float *_valuelow, float *_valuehigh, string _name, int _size) : ofxUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _min, _max, _valuelow, _valuehigh, w, h, x, y, _size);
    //        ofLogWarning("OFXUIRANGESLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUIRangeSlider::ofxUIRangeSlider(float w, float h, float _min, float _max, float *_valuelow, float *_valuehigh, string _name, int _size) : ofxUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _min, _max, _valuelow, _valuehigh, w, h, 0, 0, _size);
    //        ofLogWarning("OFXUIRANGESLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUIRangeSlider::~ofxUIRangeSlider()
{
    if(!useReference)
    {
        delete valuelowRef;
        delete valuehighRef;
    }
}

void ofxUIRangeSlider::init(string _name, float _min, float _max, float *_valuelow, float *_valuehigh, float w, float h,
          float x, float y, int _size)
{
    initRect(x,y,w,h);
    name = string(_name);
    if(w > h)
    {
        kind = OFX_UI_WIDGET_RSLIDER_H;
    }
    else
    {
        kind = OFX_UI_WIDGET_RSLIDER_V;
    }
    
    draw_fill = true;
    
    valuelow = *_valuelow;                                                  //the widget's value
    valuehigh = *_valuehigh;                                                //the widget's value
    
    if(useReference)
    {
        valuelowRef = _valuelow;
        valuehighRef = _valuehigh;
    }
    else
    {
        valuelowRef = new float();
        valuehighRef = new float();
        *valuelowRef = valuelow;
        *valuehighRef = valuehigh;
    }
    
    max = _max;
    min = _min;
    hitHigh = false;
    hitLow = false;
    hitCenter = false;
    
    if(valuelow > max)
    {
        valuelow = max;
    }
    if(valuelow < min)
    {
        valuelow = min;
    }
    
    if(valuehigh > max)
    {
        valuehigh = max;
    }
    if(valuehigh < min)
    {
        valuehigh = min;
    }
    
    valuelow = ofxUIMap(valuelow, min, max, 0.0, 1.0, true);
    valuehigh = ofxUIMap(valuehigh, min, max, 0.0, 1.0, true);
    labelPrecision = 2;
    
    valuelowString = ofxUIToString(getScaledValueLow(),labelPrecision);
    valuehighString = ofxUIToString(getScaledValueHigh(),labelPrecision);
    
    if(kind == OFX_UI_WIDGET_RSLIDER_H)
    {
        label = new ofxUILabel(0,h+padding,(name+" LABEL"), (name + ": " + valuelowString + " " + valuehighString), _size);
    }
    else
    {
        label = new ofxUILabel(0,h+padding,(name+" LABEL"), name, _size);
    }
    addEmbeddedWidget(label);
    
    increment = fabs(max - min) / 10.0;
}

void ofxUIRangeSlider::update()
{
    if(useReference)
    {
        valuelow = ofxUIMap(*valuelowRef, min, max, 0.0, 1.0, true);
        valuehigh = ofxUIMap(*valuehighRef, min, max, 0.0, 1.0, true);
    }
}

void ofxUIRangeSlider::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

void ofxUIRangeSlider::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

void ofxUIRangeSlider::drawFill()
{
    if(draw_fill)
    {
        ofxUIFill();
        ofxUISetColor(color_fill);
        if(kind == OFX_UI_WIDGET_RSLIDER_H)
        {
            ofxUIDrawRect(rect->getX()+rect->getWidth()*valuelow, rect->getY(), rect->getWidth()*(valuehigh-valuelow), rect->getHeight());
        }
        else
        {
            ofxUIDrawRect(rect->getX(), rect->getY()+(1.0-valuehigh)*rect->getHeight(), rect->getWidth(), rect->getHeight()*(valuehigh-valuelow));
        }
    }
}

void ofxUIRangeSlider::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ofxUIFill();
        ofxUISetColor(color_fill_highlight);
        if(kind == OFX_UI_WIDGET_RSLIDER_H)
        {
            ofxUIDrawRect(rect->getX()+rect->getWidth()*valuelow, rect->getY(), rect->getWidth()*(valuehigh-valuelow), rect->getHeight());
        }
        else
        {
            ofxUIDrawRect(rect->getX(), rect->getY()+(1.0-valuehigh)*rect->getHeight(), rect->getWidth(), rect->getHeight()*(valuehigh-valuelow));
        }
        if(kind == OFX_UI_WIDGET_RSLIDER_V)
        {
            label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*valuehigh, valuehighString);
            label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*valuelow, valuelowString);
        }
    }
}

void ofxUIRangeSlider::mouseMoved(int x, int y )
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

void ofxUIRangeSlider::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        state = OFX_UI_STATE_DOWN;
        hitValueHigh = valuehigh;
        hitValueLow = valuelow;
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

void ofxUIRangeSlider::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        hit = true;
        state = OFX_UI_STATE_DOWN;
        hitValueHigh = valuehigh;
        hitValueLow = valuelow;
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

void ofxUIRangeSlider::mouseReleased(int x, int y, int button)
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
    hitHigh = false;
    hitLow = false;
    hitCenter = false;
}

void ofxUIRangeSlider::keyPressed(int key)
{
    if(state == OFX_UI_STATE_OVER)
    {
        switch (key)
        {
            case OF_KEY_RIGHT:
                setValueHigh(getScaledValueHigh()+increment);
                setValueLow(getScaledValueLow()+increment);
                triggerEvent(this);
                break;
                
            case OF_KEY_LEFT:
                setValueHigh(getScaledValueHigh()-increment);
                setValueLow(getScaledValueLow()-increment);
                triggerEvent(this);
                break;
                
                
            case OF_KEY_UP:
                setValueHigh(getScaledValueHigh()+increment);
                setValueLow(getScaledValueLow()-increment);
                triggerEvent(this);
                break;
                
                
            case OF_KEY_DOWN:
                setValueHigh(getScaledValueHigh()-increment);
                setValueLow(getScaledValueLow()+increment);
                triggerEvent(this);
                break;
                
            default:
                break;
        }
    }
}

void ofxUIRangeSlider::keyReleased(int key)
{
    
}

void ofxUIRangeSlider::windowResized(int w, int h)
{
    
}

void ofxUIRangeSlider::setIncrement(float _increment)
{
    increment = _increment;
}

void ofxUIRangeSlider::input(float x, float y)
{
    float v = 0;
    
    if(kind == OFX_UI_WIDGET_RSLIDER_H)
    {
        v = rect->percentInside(x, y).x;
    }
    else
    {
        v = 1.0-rect->percentInside(x, y).y;
    }
    
    if(hitHigh)
    {
        valuehigh = v;
    }
    else if(hitLow)
    {
        valuelow = v;
    }
    else if(hitCenter)
    {
        valuehigh +=(v-hitPoint);
        valuelow +=(v-hitPoint);
        hitPoint = v;
    }
    else
    {
        float dvh = fabs(valuehigh - v);
        float dvl = fabs(valuelow - v);
        if(dvh < .05 || v > valuehigh)
        {
            valuehigh = v;
            hitHigh = true;
        }
        else if(dvl < .05 || v < valuelow)
        {
            valuelow = v;
            hitLow = true;
        }
        else
        {
            hitCenter = true;
            hitPoint = v;
        }
    }
    
    if(valuehigh < valuelow && hitHigh)
    {
        valuehigh = hitValueLow;
        hitHigh = false;
        hitLow = true;
    }
    else if(valuelow > valuehigh && hitLow)
    {
        valuelow = hitValueHigh;
        hitHigh = true;
        hitLow = false;
    }
    
    valuehigh = MIN(1.0, MAX(0.0, valuehigh));
    valuelow = MIN(1.0, MAX(0.0, valuelow));
    updateValueRef();
    updateLabel();
}

void ofxUIRangeSlider::updateValueRef()
{
    (*valuelowRef) = getScaledValueLow();
    (*valuehighRef) = getScaledValueHigh();
}

void ofxUIRangeSlider::updateLabel()
{
    valuelowString = ofxUIToString(getValueLow(),labelPrecision);
    valuehighString = ofxUIToString(getValueHigh(),labelPrecision);
    
    if(kind == OFX_UI_WIDGET_RSLIDER_H)
    {
        label->setLabel(name + ": " + valuelowString + " " + valuehighString);
    }
}

void ofxUIRangeSlider::stateChange()
{
    if(valuehigh > 0)
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

void ofxUIRangeSlider::setValueLow(float _value)
{
    valuelow = ofxUIMap(_value, min, max, 0.0, 1.0, true);
    updateValueRef();
    updateLabel();
}

void ofxUIRangeSlider::setValueHigh(float _value)
{
    valuehigh = ofxUIMap(_value, min, max, 0.0, 1.0, true);
    updateValueRef();
    updateLabel();
}

float ofxUIRangeSlider::getValueLow()
{
    return (*valuelowRef);
}

float ofxUIRangeSlider::getValueHigh()
{
    return (*valuehighRef);
}

float ofxUIRangeSlider::getNormalizedValueLow()
{
    return valuelow;
}

float ofxUIRangeSlider::getNormalizedValueHigh()
{
    return valuehigh;
}

float ofxUIRangeSlider::getPercentValueLow()
{
    return valuelow;
}

float ofxUIRangeSlider::getPercentValueHigh()
{
    return valuehigh;
}

float ofxUIRangeSlider::getScaledValueLow()
{
    return ofxUIMap(valuelow, 0.0, 1.0, min, max, true);
}

float ofxUIRangeSlider::getScaledValueHigh()
{
    return ofxUIMap(valuehigh, 0.0, 1.0, min, max, true);
}

void ofxUIRangeSlider::setLabelPrecision(int _precision)
{
    labelPrecision = _precision;
    updateValueRef();
    updateLabel();
}

void ofxUIRangeSlider::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    calculatePaddingRect(); 
}

void ofxUIRangeSlider::setMax(float _max)
{
    setMaxAndMin(_max, min);
}

void ofxUIRangeSlider::setMin(float _min)
{
    setMaxAndMin(max, _min);
}

void ofxUIRangeSlider::setMaxAndMin(float _max, float _min)
{
    max = _max;
    min = _min;
    
    valuelow= ofxUIMap(valuelow, 0, 1.0, min, max, true);
    valuelow = ofxUIMap(valuelow, min, max, 0.0, 1.0, true);
    
    valuehigh = ofxUIMap(valuehigh, 0, 1.0, min, max, true);
    valuehigh = ofxUIMap(valuehigh, min, max, 0.0, 1.0, true);
    updateValueRef();
    updateLabel();
}

bool ofxUIRangeSlider::isDraggable()
{
    return true;
}

#ifndef OFX_UI_NO_XML

void ofxUIRangeSlider::saveState(ofxXmlSettings *XML)
{
    XML->setValue("HighValue", getValueHigh(), 0);
    XML->setValue("LowValue", getValueLow(), 0);

}

void ofxUIRangeSlider::loadState(ofxXmlSettings *XML)
{
    setValueHigh(XML->getValue("HighValue", getValueHigh(), 0));
    setValueLow(XML->getValue("LowValue", getValueLow(), 0));
}

#endif