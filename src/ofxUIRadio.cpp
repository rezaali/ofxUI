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

#include "ofxUIRadio.h"

ofxUIRadio::ofxUIRadio(string _name, vector<string> names, int _orientation, float w, float h, float x, float y, int _size) : ofxUIWidget()
{
    init(_name, names, _orientation, w, h, x, y, _size);
}

void ofxUIRadio::init(string _name, vector<string> names, int _orientation, float w, float h, float x, float y, int _size)
{
    initRect(x,y,w,h);
    name = string(_name);
    kind = OFX_UI_WIDGET_RADIO;
    
    draw_back = false;
    orientation = _orientation;
    
    value = -1;
    
    if(names.size() == 0)
    {
        setEmbedded(true);
    }
    else
    {
        for(unsigned int i = 0; i < names.size(); i++)
        {
            string tname = names[i];
            ofxUIToggle *toggle = new ofxUIToggle(tname, false, w, h, 0, 0, _size);
            addEmbeddedWidget(toggle);
            toggles.push_back(toggle);            
        }
    }
    
    active = NULL;
}

void ofxUIRadio::setVisible(bool _visible)
{
    visible = _visible;
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ofxUIToggle *t = toggles[i];
        t->setVisible(visible);
    }
}
void ofxUIRadio::activateToggle(string _name)
{
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ofxUIToggle *t = toggles[i];
        if(!(t->getName().compare(_name.c_str())))
        {
            t->setValue(true);
            active = t;
            value = i;
        }
        else
        {
            t->setValue(false);
        }
    }
}

void ofxUIRadio::triggerSelf()
{
    if(parent != NULL)
    {
        parent->triggerEvent(this);
        parent->triggerEvent(active);
    }
}

void ofxUIRadio::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    
    float tWidth = 0;
    float tHeight = 0;
    
    float xt = 0;
    float yt = 0;
    
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ofxUIToggle *t = toggles[i];
        t->setParent(this);
        t->setRectParent(this->getRect());
        if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
        {
            t->getRect()->x = xt;
            t->getRect()->y = 0;
            xt+=t->getPaddingRect()->width;
            tHeight = t->getPaddingRect()->height;
        }
        else
        {
            t->getRect()->x = 0;
            t->getRect()->y = yt;
            if(t->getPaddingRect()->width > tWidth)
            {
                tWidth = t->getPaddingRect()->width;
            }
            tHeight+=t->getPaddingRect()->getHeight();
            yt +=t->getPaddingRect()->getHeight();
        }
    }
    
    if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
    {
        if(xt > tWidth)
        {
            tWidth = xt;
        }
    }
    rect->setWidth(tWidth - padding);
    rect->setHeight(tHeight - padding*2.0);
    calculatePaddingRect();
}

vector<ofxUIToggle *> ofxUIRadio::getToggles()
{
    return toggles;
}

ofxUIToggle* ofxUIRadio::getActive()
{
    return active;
}

void ofxUIRadio::triggerEvent(ofxUIWidget *child)
{
    activateToggle(child->getName().c_str());
    triggerSelf();
}

void ofxUIRadio::addToggle(ofxUIToggle *toggle)
{
    toggle->setParent(this);
    toggles.push_back(toggle);
    if(toggle->getValue())
    {
        activateToggle(toggle->getName());
    }
}

int ofxUIRadio::getValue()
{
    return value;
}

string ofxUIRadio::getActiveName()
{
    if(active != NULL)
    {
        return active->getName();
    }
    return ""; 
}