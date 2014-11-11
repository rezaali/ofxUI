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

#include "ofxUIEventArgs.h"
#include "ofxUIWidget.h"

ofxUIEventArgs::ofxUIEventArgs()
{
    widget = NULL;
}

ofxUIEventArgs::ofxUIEventArgs(ofxUIWidget *_widget)
{
    widget = _widget;
}

ofxUIButton *ofxUIEventArgs::getButton()
{
    return (ofxUIButton *) widget;
}

ofxUIToggle *ofxUIEventArgs::getToggle()
{
    return (ofxUIToggle *) widget;
}

ofxUISlider *ofxUIEventArgs::getSlider()
{
    return (ofxUISlider *) widget;
}

ofxUICanvas *ofxUIEventArgs::getCanvasParent()
{
    return (ofxUICanvas *) widget->getCanvasParent();
}

ofxUIWidget *ofxUIEventArgs::getParent()
{
    return widget->getParent();
}

bool ofxUIEventArgs::isName(string _name)
{
    return (getName() == _name) ? true : false; 
}

bool ofxUIEventArgs::getBool()
{
    return getButton()->getValue();
}

float ofxUIEventArgs::getFloat()
{
    return getSlider()->getValue();
}

double ofxUIEventArgs::getDouble()
{
    return getSlider()->getValue();
}

int ofxUIEventArgs::getInt()
{
    return getSlider()->getValue();
}

string ofxUIEventArgs::getName()
{
    return widget->getName();
}

string ofxUIEventArgs::getParentName()
{
    ofxUIWidget *parent = widget->getParent();
    if(parent != NULL)
    {
        return parent->getName();
    }
    else
    {
        return "";
    }
}

string ofxUIEventArgs::getCanvasParentName()
{
    ofxUIWidget *parent = widget->getCanvasParent();
    if(parent != NULL)
    {
        return parent->getName();
    }
    else
    {
        return "";
    }
}

int ofxUIEventArgs::getKind()
{
    return widget->getKind();
}