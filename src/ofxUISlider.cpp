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

#include "ofxUISlider.h"
#include "ofxUI.h"

template<typename T>
ofxUISlider_<T>::ofxUISlider_() : ofxUIWidgetWithLabel()
{
    
}

template<typename T>
ofxUISlider_<T>::ofxUISlider_(string _name, T _min, T _max, T _value, float w, float h, float x, float y) : ofxUIWidgetWithLabel()
{
    useReference = false;
    init(_name, _min, _max, &_value, w, h, x, y);
}

template<typename T>
ofxUISlider_<T>::ofxUISlider_(string _name, T _min, T _max, T *_value, float w, float h, float x, float y) : ofxUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _min, _max, _value, w, h, x, y);
}

template<typename T>
ofxUISlider_<T>::~ofxUISlider_()
{
    if(!useReference)
    {
        delete valueRef;
    }
}

template<typename T>
void ofxUISlider_<T>::init(string _name, T _min, T _max, T *_value, float w, float h, float x, float y)
{
    initRect(x,y,w,h);
    name = string(_name);
    setOrientation(w, h);
    setKind();
    
    draw_fill = true;
    
    value = *_value;                                               //the widget's value
    if(useReference)
    {
        valueRef = _value;
    }
    else
    {
        valueRef = new T();
        *valueRef = value;
    }
    
    max = _max;
    min = _min;
    labelPrecision = 2;
    
    if(value > max)
    {
        value = max;
    }
    if(value < min)
    {
        value = min;
    }
    
    value = ofxUIMap(value, min, max, 0.0, 1.0, true);    
    valueString = ofxUIToString(getScaledValue(),labelPrecision);
    
    if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
    {
        label = new ofxUILabel(0,h+padding,string(name+" LABEL"), string(name + ": " + ofxUIToString(max,labelPrecision)), OFX_UI_FONT_SMALL);
    }
    else
    {
        label = new ofxUILabel(0,h+padding,string(name+" LABEL"), string(name), OFX_UI_FONT_SMALL);
    }
    addEmbeddedWidget(label);
    label->setVisible(drawLabel);
    
    increment = ABS(max - min) / 100.0;
    bRoundedToNearestInt = false;
    bClampValue = true;
}

template<typename T>
void ofxUISlider_<T>::setOrientation(float w, float h)
{
    if(w > h)
    {
        orientation = OFX_UI_ORIENTATION_HORIZONTAL;
    }
    else
    {
        orientation = OFX_UI_ORIENTATION_VERTICAL;
    }
}

template<>
void ofxUISlider_<float>::setKind()
{
    if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
    {
        kind = OFX_UI_WIDGET_SLIDER_H;
    }
    else
    {
        kind = OFX_UI_WIDGET_SLIDER_V;
    }
}

template<>
void ofxUISlider_<int>::setKind()
{
    if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
    {
        kind = OFX_UI_WIDGET_INTSLIDER_H;
    }
    else
    {
        kind = OFX_UI_WIDGET_INTSLIDER_V;
    }
}


template<>
void ofxUISlider_<double>::setKind()
{
    if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
    {
        kind = OFX_UI_WIDGET_DOUBLESLIDER_H;
    }
    else
    {
        kind = OFX_UI_WIDGET_DOUBLESLIDER_V;
    }
}

template<typename T>
bool ofxUISlider_<T>::getSetClampValue()
{
    return bClampValue;
}

template<typename T>
void ofxUISlider_<T>::setClampValue(bool _bClampValue)
{
    bClampValue = _bClampValue;
}

template<typename T>
void ofxUISlider_<T>::update()
{
    if(useReference)
    {
        value = ofxUIMap(*valueRef, min, max, 0.0, 1.0, bClampValue);
        updateLabel();
    }
}

template<typename T>
void ofxUISlider_<T>::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

template<typename T>
void ofxUISlider_<T>::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

template<typename T>
void ofxUISlider_<T>::drawBack()
{
    if(draw_back)
    {
        ofxUIFill();
        ofxUISetColor(color_back);
        rect->draw();
    }
}

template<typename T>
void ofxUISlider_<T>::drawOutline()
{
    if(draw_outline)
    {
        ofNoFill();
        ofxUISetColor(color_outline);
        rect->draw();
    }
}

template<typename T>
void ofxUISlider_<T>::drawOutlineHighlight()
{
    if(draw_outline_highlight)
    {
        ofNoFill();
        ofxUISetColor(color_outline_highlight);
        rect->draw();
    }
}

template<typename T>
void ofxUISlider_<T>::drawFill()
{
    if(draw_fill && value > 0.0)
    {
        ofxUIFill();
        ofxUISetColor(color_fill);
        if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
        {
            ofxUIDrawRect(rect->getX(), rect->getY(), rect->getWidth()*MIN(MAX(value, 0.0), 1.0), rect->getHeight());
        }
        else
        {
            ofxUIDrawRect(rect->getX(), rect->getY()+rect->getHeight(), rect->getWidth(), -rect->getHeight()*MIN(MAX(value, 0.0), 1.0));
        }
    }
}

template<typename T>
void ofxUISlider_<T>::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ofxUIFill();
        ofxUISetColor(color_fill_highlight);
        if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
        {
            ofxUIDrawRect(rect->getX(), rect->getY(), rect->getWidth()*MIN(MAX(value, 0.0), 1.0), rect->getHeight());
        }
        else
        {
            ofxUIDrawRect(rect->getX(), rect->getY()+rect->getHeight(), rect->getWidth(), -rect->getHeight()*MIN(MAX(value, 0.0), 1.0));
        }
        if(kind == OFX_UI_WIDGET_SLIDER_V)
        {
            label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*MIN(MAX(value, 0.0), 1.0), valueString);
        }
    }
}

template<typename T>
void ofxUISlider_<T>::mouseMoved(int x, int y )
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

template<typename T>
void ofxUISlider_<T>::mouseDragged(int x, int y, int button)
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

template<typename T>
void ofxUISlider_<T>::mousePressed(int x, int y, int button)
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

template<typename T>
void ofxUISlider_<T>::mouseReleased(int x, int y, int button)
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

template<typename T>
void ofxUISlider_<T>::keyPressed(int key)
{
    if(state == OFX_UI_STATE_OVER || state == OFX_UI_STATE_DOWN)
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
                
            case OF_KEY_SHIFT:
#if OF_VERSION_MINOR > 7
            case OF_KEY_LEFT_SHIFT:
            case OF_KEY_RIGHT_SHIFT:
#endif
                bRoundedToNearestInt = true;
                break;
            default:
                break;
        }
    }
}

template<typename T>
void ofxUISlider_<T>::keyReleased(int key)
{
    bRoundedToNearestInt = false;
}

template<typename T>
void ofxUISlider_<T>::windowResized(int w, int h)
{
    
}

template<typename T>
T ofxUISlider_<T>::getIncrement()
{
    return increment;
}

template<typename T>
void ofxUISlider_<T>::setIncrement(T _increment)
{
    increment = _increment;
}

template<typename T>
void ofxUISlider_<T>::input(float x, float y)
{
    if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
    {
        value = rect->percentInside(x, y).x;
    }
    else
    {
        value = 1.0-rect->percentInside(x, y).y;
    }
    
    value = MIN(1.0, MAX(0.0, value));
    updateValueRef();
    updateLabel();
}

template<typename T>
void ofxUISlider_<T>::updateValueRef()
{
    (*valueRef) = bRoundedToNearestInt ? ceil(getScaledValue()) : getScaledValue();
}

template<typename T>
void ofxUISlider_<T>::updateLabel()
{
    valueString = ofxUIToString(getValue(),labelPrecision);
    if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
    {
        label->setLabel(name + ": " + valueString);
    }
}

template<typename T>
void ofxUISlider_<T>::stateChange()
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

template<typename T>
void ofxUISlider_<T>::setValue(T _value)
{
    value = ofxUIMap(_value, min, max, 0.0, 1.0, bClampValue);
    updateValueRef();
    updateLabel();
}

template<typename T>
T ofxUISlider_<T>::getValue()
{
    return (*valueRef);
}

template<typename T>
T ofxUISlider_<T>::getNormalizedValue()
{
    return value;
}

template<typename T>
float ofxUISlider_<T>::getPercentValue()
{
    return value;
}

template<typename T>
T ofxUISlider_<T>::getScaledValue()
{
    return ofxUIMap(value, 0.0, 1.0, min, max, bClampValue);
}

template<typename T>
void ofxUISlider_<T>::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    label->getRect()->setY(rect->getHeight()+padding);
    calculatePaddingRect();
    updateValueRef();
    updateLabel();
}

template<typename T>
void ofxUISlider_<T>::setLabelPrecision(int _precision)
{
    labelPrecision = _precision;
    updateValueRef();
    updateLabel();
}

template<typename T>
void ofxUISlider_<T>::setMax(T _max, bool bKeepValueTheSame)
{
    setMaxAndMin(_max, min, bKeepValueTheSame);
}

template<typename T>
T ofxUISlider_<T>::getMax()
{
    return max;
}

template<typename T>
void ofxUISlider_<T>::setMin(T _min, bool bKeepValueTheSame)
{
    setMaxAndMin(max, _min, bKeepValueTheSame);
}

template<typename T>
T ofxUISlider_<T>::getMin()
{
    return min;
}

template<typename T>
ofxUIVec2f ofxUISlider_<T>::getMaxAndMin()
{
    return ofxUIVec2f(max, min);
}

template<typename T>
void ofxUISlider_<T>::setMaxAndMin(T _max, T _min, bool bKeepValueTheSame)
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

template<typename T>
bool ofxUISlider_<T>::isDraggable()
{
    return true;
}

#ifndef OFX_UI_NO_XML

template<typename T>
void ofxUISlider_<T>::saveState(ofxXmlSettings *XML)
{
    XML->setValue("Value", getValue(), 0);
}

template<typename T>
void ofxUISlider_<T>::loadState(ofxXmlSettings *XML)
{
    T value = XML->getValue("Value", getValue(), 0);
    setValue(value);
}

#endif

template class ofxUISlider_<int>;
template class ofxUISlider_<float>;
template class ofxUISlider_<double>;