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

#include "ofxUILabelButton.h"
#include "ofxUI.h"

ofxUILabelButton::ofxUILabelButton(string _name, bool _value, float w, float h, float x, float y, int _size, bool _justifyLeft) : ofxUIButton()
{
    useReference = false;
    init(_name, &_value, w, h, x, y, _size, _justifyLeft);
}

ofxUILabelButton::ofxUILabelButton(string _name, bool *_value, float w, float h, float x, float y, int _size, bool _justifyLeft) : ofxUIButton()
{
    useReference = true;
    init(_name, _value, w, h, x, y, _size, _justifyLeft);
}

void ofxUILabelButton::init(string _name, bool *_value, float w, float h, float x, float y, int _size, bool _justifyLeft)
{
    initRect(x, y, w, h);
    justifyLeft = _justifyLeft;
    autoSize = w == 0 ? true : false;
    name = string(_name);
    
    label = new ofxUILabel(0,0,(name+" LABEL"), name, _size);
    addEmbeddedWidget(label);
    
    kind = OFX_UI_WIDGET_LABELBUTTON;
    
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

void ofxUILabelButton::setLabelText(string labeltext)
{
    label->setLabel(labeltext);
    if(!autoSize)
    {
        ofxUIRectangle *labelrect = label->getRect();
        float h = labelrect->getHeight();
        float ph = rect->getHeight();
        float w = labelrect->getWidth();
        float pw = rect->getWidth();
        labelrect->y = (int)(ph*.5 - h*.5);
        labelrect->x = (int)(pw*.5 - w*.5-padding*.5);
    }
}

void ofxUILabelButton::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    float compareHeight = label->getPaddingRect()->getHeight()+padding*2.0;
    if(rect->getHeight() == 0 || rect->getHeight() < compareHeight)
    {
        rect->setHeight(compareHeight);
    }

    ofxUIRectangle *labelrect = label->getRect();
    labelrect->setParent(rect);
    
    if(autoSize)
    {
        rect->setWidth(label->getPaddingRect()->getWidth()+padding*2.0);
    }
    else
    {
        while(labelrect->getWidth() > rect->width)
        {
            string labelstring = label->getLabel();
            string::iterator it;
            it=labelstring.end();
            it--;
            labelstring.erase (it);
            label->setLabel(labelstring);
        }
    }
    
    float h = labelrect->getHeight();
    float ph = rect->getHeight();
    
    labelrect->setY((int)(ph*.5 - h*.5));
    if(justifyLeft)
    {
        labelrect->setX(padding);
    }
    else
    {
        float w = labelrect->getWidth();
        float pw = rect->getWidth();
        labelrect->setX((int)(pw*.5 - w*.5-padding*.5));
    }
    calculatePaddingRect();
}

void ofxUILabelButton::setValue(bool _value)
{
    *value = _value;
    draw_fill = *value;
    label->setDrawBack((*value));
}