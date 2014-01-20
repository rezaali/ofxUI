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

#include "ofxUITabBar.h"
#include "ofxUI.h"

ofxUITabBar::ofxUITabBar() : ofxUICanvas()
{
    initTabBar();
}

ofxUITabBar::~ofxUITabBar()
{
    ofRemoveListener(newGUIEvent, this, &ofxUITabBar::mainUiEvent);
}

ofxUITabBar::ofxUITabBar(float x, float y, float w, float h) : ofxUICanvas(x,y,w,h)
{
    initTabBar();
}

void ofxUITabBar::initTabBar()
{
    kind = OFX_UI_WIDGET_TABBAR;
    autoSizeToFitWidgets();
    ofAddListener(newGUIEvent, this, &ofxUITabBar::mainUiEvent);
    active = NULL;
}

void ofxUITabBar::addCanvas(ofxUICanvas *_canvas)
{
    ofxUIToggle* newToggle = addToggle(_canvas->getName(), false);
    canvases.insert ( pair<ofxUIToggle*, ofxUICanvas*>( newToggle, _canvas) );
    _canvas->disable();
    autoSizeToFitWidgets();
}

void ofxUITabBar::addCanvas(ofxUIScrollableCanvas *_canvas)
{
    ofxUIToggle* newToggle = addToggle(_canvas->getName(), false);
    canvases.insert ( pair<ofxUIToggle*, ofxUICanvas*>( newToggle, _canvas) );
    _canvas->disable();
    autoSizeToFitWidgets();
}

void ofxUITabBar::mainUiEvent(ofxUIEventArgs &event)
{
    string name = event.getName();
    for (map<ofxUIToggle*, ofxUICanvas*>::iterator it=canvases.begin(); it!=canvases.end(); ++it)
    {
        if(active != NULL && active->getName() == name)
        {
            it->first->setValue(false);
            it->second->disable();
            active = NULL;
        }
        else if(it->second->getName() == name && event.getToggle()->getValue())
        {
            active = it->second;
            it->first->setValue(true);
            it->second->enable();
            it->second->setPosition(rect->getX() + rect->getWidth() + padding*0.5, this->rect->getY());
        }
        else
        {
            it->first->setValue(false);
            it->second->disable();
        }        
    }
}

void ofxUITabBar::enable()
{
    ofxUICanvas::enable();
    
    if (active != NULL) {
        active->enable();
    }
}

void ofxUITabBar::disable()
{
    ofxUICanvas::disable();
    
    if (active != NULL) {
        active->disable();
    }
}

void ofxUITabBar::toggleVisible()
{
    ofxUICanvas::toggleVisible();
    
    if (active != NULL) {
        active->toggleVisible();
    }
}

ofxUICanvas* ofxUITabBar::getActiveCanvas()
{
    return active;
}

bool ofxUITabBar::isHit(int x, int y)
{
    if (ofxUICanvas::isHit(x, y)) {
        return true;
    } else {
        if (active != NULL) {
            return active->isHit(x, y);
        }
    }
    
    return false;
}

void ofxUITabBar::saveSettings(string pathToSaveTo, string fileNamePrefix)
{
    for (map<ofxUIToggle*, ofxUICanvas*>::iterator it=canvases.begin(); it!=canvases.end(); ++it) {
        it->second->saveSettings(pathToSaveTo + fileNamePrefix + it->second->getName() + ".xml");
    }
}

void ofxUITabBar::loadSettings(string pathToLoadFrom, string fileNamePrefix)
{
    for (map<ofxUIToggle*, ofxUICanvas*>::iterator it=canvases.begin(); it!=canvases.end(); ++it) {
        it->second->loadSettings(pathToLoadFrom + fileNamePrefix + it->second->getName() + ".xml");
    }
}