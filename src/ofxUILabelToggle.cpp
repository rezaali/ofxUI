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

// DON'T USE THE NEXT CONSTRUCTORS
// This is maintained for backward compatibility and will be removed on future releases

ofxUILabelToggle::ofxUILabelToggle(float x, float y, float w, bool _value, string _name, int _size) : ofxUIToggle()
{
    useReference = false;
    init(_name, &_value, w, 0, x, y, _size);
    //        ofLogWarning("OFXUILABELTOGGLE: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUILabelToggle::ofxUILabelToggle(float x, float y, float w, float h, bool _value, string _name, int _size) : ofxUIToggle()
{
    useReference = false;
    init(_name, &_value, w, h, x, y, _size);
    //        ofLogWarning("OFXUILABELTOGGLE: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUILabelToggle::ofxUILabelToggle(float w, bool _value, string _name, int _size, float h) : ofxUIToggle()
{
    useReference = false;
    init(_name, &_value, w, h, 0, 0, _size);
    //        ofLogWarning("OFXUILABELTOGGLE: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUILabelToggle::ofxUILabelToggle(float x, float y, bool _value, string _name, int _size) : ofxUIToggle()
{
    useReference = false;
    init(_name, &_value, 0, 0, x, y, _size);
    //        ofLogWarning("OFXUILABELTOGGLE: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUILabelToggle::ofxUILabelToggle(bool _value, string _name, int _size) : ofxUIToggle()
{
    useReference = false;
    init(_name, &_value, 0, 0, 0, 0, _size);
    //        ofLogWarning("OFXUILABELTOGGLE: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUILabelToggle::ofxUILabelToggle(float x, float y, float w, bool *_value, string _name, int _size) : ofxUIToggle()
{
    useReference = true;
    init(_name, _value, w, 0, x, y, _size);
    //        ofLogWarning("OFXUILABELTOGGLE: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUILabelToggle::ofxUILabelToggle(float x, float y, float w, float h, bool *_value, string _name, int _size) : ofxUIToggle()
{
    useReference = true;
    init(_name, _value, w, h, x, y, _size);
    //        ofLogWarning("OFXUILABELTOGGLE: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUILabelToggle::ofxUILabelToggle(float w, bool *_value, string _name, int _size, float h) : ofxUIToggle()
{
    useReference = true;
    init(_name, _value, w, h, 0, 0, _size);
    //        ofLogWarning("OFXUILABELTOGGLE: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUILabelToggle::ofxUILabelToggle(float x, float y, bool *_value, string _name, int _size) : ofxUIToggle()
{
    useReference = true;
    init(_name, _value, 0, 0, x, y, _size);
    //        ofLogWarning("OFXUILABELTOGGLE: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUILabelToggle::ofxUILabelToggle(bool *_value, string _name, int _size) : ofxUIToggle()
{
    useReference = true;
    init(_name, _value, 0, 0, 0, 0, _size);
    //        ofLogWarning("OFXUILABELTOGGLE: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

void ofxUILabelToggle::init(string _name, bool *_value, float w, float h, float x, float y, int _size, bool _justifyLeft)
{
    rect = new ofxUIRectangle(x,y,w,h);
    autoSize = w == 0 ? true : false;
    justifyLeft = _justifyLeft;
    name = string(_name);
    kind = OFX_UI_WIDGET_LABELTOGGLE;
    paddedRect = new ofxUIRectangle(-padding, -padding, padding*2.0, padding*2.0);
    paddedRect->setParent(rect);
    
    label = new ofxUILabel((name+" LABEL"), name, _size);
    label->setParent(label);
    label->setRectParent(rect);
    label->setEmbedded(true);
    
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
        labelrect->y = (int)(ph*.5 - h*.5);
        labelrect->x = (int)(pw*.5 - w*.5-padding*.5);
    }
}

void ofxUILabelToggle::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    float compareHeight = label->getPaddingRect()->height+padding*2.0;
    if(rect->height == 0 || rect->height < compareHeight)
    {
        rect->height = compareHeight;
    }
    ofxUIRectangle *labelrect = label->getRect();
    
    label->setParent(this);
    labelrect->setParent(rect);
    
    if(autoSize)
    {
        rect->width = label->getPaddingRect()->width+padding*2.0;
    }
    else
    {
        while(labelrect->width+padding*4.0 > rect->width && label->getLabel().size() > 0)
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
    
    
    labelrect->y = (int)(ph*.5 - h*.5);
    
    
    if(justifyLeft)
    {
        labelrect->x = padding;
    }
    else
    {
        float w = labelrect->getWidth();
        float pw = rect->getWidth();
        labelrect->x = (int)(pw*.5 - w*.5-padding*.5);
    }
    
    paddedRect->height = rect->height+padding*2.0;
    paddedRect->width = rect->width+padding*2.0;
}

void ofxUILabelToggle::setLabelVisible(bool _visible)
{
    drawLabel = _visible;
    label->setVisible(drawLabel);
}

void ofxUILabelToggle::setVisible(bool _visible)
{
    visible = _visible;
    label->setVisible((visible && drawLabel));
}