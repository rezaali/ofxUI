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

#include "ofxUILabelToggle.h"
#include "ofxUI.h"

ofxUILabelToggle::ofxUILabelToggle(string _name, bool _value, float w, float h, float x, float y, int _size, bool _justifyLeft) : ofxUIToggle()
{
    useReference = false;
    init(_name, &_value, w, h, x, y, _size, _justifyLeft);
}

ofxUILabelToggle::ofxUILabelToggle(string _name, bool *_value, float w, float h, float x, float y, int _size, bool _justifyLeft) : ofxUIToggle()
{
    useReference = true;
    init(_name, _value, w, h, x, y, _size, _justifyLeft);
}

void ofxUILabelToggle::init(string _name, bool *_value, float w, float h, float x, float y, int _size, bool _justifyLeft)
{
    initRect(x,y,w,h);
    autoSize = (w == 0) ? true : false;
    justifyLeft = _justifyLeft;
    name = string(_name);
    kind = OFX_UI_WIDGET_LABELTOGGLE;
    
    label = new ofxUILabel((name+" LABEL"), name, _size);
    addEmbeddedWidget(label);
    
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

void ofxUILabelToggle::setLabelText(string labeltext)
{
    label->setLabel(labeltext);
    if(!autoSize)
    {
        ofxUIRectangle *labelrect = label->getRect();
        float h = labelrect->getHeight();
        float ph = rect->getHeight();
        float w = labelrect->getWidth();
        float pw = rect->getWidth();
        labelrect->setY((int)(ph*.5 - h*.5));
        labelrect->setX((int)(pw*.5 - w*.5-padding*.5));
    }
}

void ofxUILabelToggle::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    float compareHeight = label->getPaddingRect()->getHeight()+padding*2.0;
    if(rect->getHeight() == 0 || rect->getHeight() < compareHeight)
    {
        rect->setHeight(compareHeight);
    }
    ofxUIRectangle *labelrect = label->getRect();
    
    label->setParent(this);
    labelrect->setParent(rect);
    
    if(autoSize)
    {
        rect->setWidth(label->getPaddingRect()->getWidth()+padding*2.0);
    }
    else
    {
        while(labelrect->getWidth()+padding*4.0 > rect->getWidth() && label->getLabel().size() > 0)
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