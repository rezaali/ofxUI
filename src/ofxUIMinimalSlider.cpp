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

#include "ofxUIMinimalSlider.h"
#include "ofxUI.h"

ofxUIMinimalSlider::ofxUIMinimalSlider(string _name, float _min, float _max, float _value, float w, float h, float x, float y, int _size) : ofxUISlider()
{
    useReference = false;
    init(_name, _min, _max, &_value, w, h, x, y, _size);
}

ofxUIMinimalSlider::ofxUIMinimalSlider(string _name, float _min, float _max, float *_value, float w, float h, float x, float y, int _size) : ofxUISlider()
{
    useReference = true;
    init(_name, _min, _max, _value, w, h, x, y, _size);
}

void ofxUIMinimalSlider::init(string _name, float _min, float _max, float *_value, float w, float h, float x, float y, int _size)
{
    if(h < .1)
    {
        autoSize = true;
    }
    else
    {
        autoSize = false;
    }
    
    initRect(x,y,w,h);
    name = string(_name);
    kind = OFX_UI_WIDGET_MINIMALSLIDER;
    
    draw_fill = true;
    showValue = true;
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
    
    if(value > max)
    {
        value = max;
    }
    if(value < min)
    {
        value = min;
    }
    
    value = ofxUIMap(value, min, max, 0.0, 1.0, true);
    
    label = new ofxUILabel(padding,h*.5,(name+" LABEL"), name, _size);
    label->setDrawBack(true); 
    addEmbeddedWidget(label);
    
    increment = fabs(max - min) / 10.0;
    bRoundedToNearestInt = false;
    bClampValue = false;
}

void ofxUIMinimalSlider::drawFill()
{
    if(draw_fill)
    {
        ofxUIFill();
        ofxUISetColor(color_fill);
        ofxUIDrawRect(rect->getX(), rect->getY(), rect->getWidth()*MIN(MAX(value, 0.0), 1.0), rect->getHeight());
    }
}

void ofxUIMinimalSlider::drawFillHighlight()
{
    if(draw_fill_highlight && showValue)
    {
        ofxUIFill();
        ofxUISetColor(color_fill_highlight);
        ofxUIDrawRect(rect->getX(), rect->getY(), rect->getWidth()*MIN(MAX(value, 0.0), 1.0), rect->getHeight());
        ofxUISetColor(label->getColorFillHighlight());
        label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*.5, ofxUIToString(getScaledValue(),labelPrecision));
    }
}

void ofxUIMinimalSlider::drawOutlineHighlight()
{
    if(draw_outline_highlight && showValue)
    {
        ofNoFill();
        ofxUISetColor(color_outline_highlight);
        rect->draw();
        if(!draw_fill_highlight)
        {
            ofxUISetColor(label->getColorFill());
            label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*.5, ofxUIToString(getScaledValue(),labelPrecision));
        }
    }
}

void ofxUIMinimalSlider::input(float x, float y)
{
    value = MIN(1.0, MAX(0.0, rect->percentInside(x, y).x));
    updateValueRef();
    updateLabel();
}


void ofxUIMinimalSlider::updateLabel()
{
    
}

void ofxUIMinimalSlider::setParent(ofxUIWidget *_parent)
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
    if(autoSize || rect->getHeight() <= label->getPaddingRect()->getHeight())
    {
        rect->setHeight(label->getPaddingRect()->getHeight()+padding*2.0);
    }
    
    float h = labelrect->getHeight();
    float ph = rect->getHeight();
    
    labelrect->setY((int)(ph*.5 - h*.5));
    labelrect->setX(padding*2.0);
    calculatePaddingRect(); 
    updateValueRef();
    updateLabel();
}

void ofxUIMinimalSlider::setShowValue(bool _showValue)
{
    showValue = _showValue;
}

bool ofxUIMinimalSlider::getShowValue()
{
    return showValue;
}