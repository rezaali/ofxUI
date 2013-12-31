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

#include "ofxUISuperCanvas.h"
#include "ofxUI.h"

ofxUISuperCanvas::ofxUISuperCanvas(string _label, ofxUIRectangle r, int _size) : ofxUICanvas(r)
{
    superInit(_label, _size);
}

ofxUISuperCanvas::ofxUISuperCanvas(string _label, float x, float y, float w, float h, int _size) : ofxUICanvas(x, y, w, h)
{
    superInit(_label, _size);
}

ofxUISuperCanvas::ofxUISuperCanvas(string _label, float x, float y, float w, float h, ofxUICanvas *sharedResources, int _size) : ofxUICanvas(x, y, w, h, sharedResources)
{
    superInit(_label, _size);
}

ofxUISuperCanvas::ofxUISuperCanvas(string _label, int _size) : ofxUICanvas()
{
    superInit(_label, _size);
}

ofxUISuperCanvas::ofxUISuperCanvas(string _label, ofxUICanvas *sharedResources, int _size) : ofxUICanvas(sharedResources)
{
    superInit(_label, _size);
}

void ofxUISuperCanvas::superInit(string _label, int _size)
{
    size = _size;
    title = _label;
    kind = OFX_UI_WIDGET_SUPERCANVAS;
    canvasTitle = new ofxUILabel(rect->getWidth()-widgetSpacing*2, title, size);
    canvasTitle->setEmbedded(true);
    headerWidgets.push_back(canvasTitle);
    addWidgetPosition(canvasTitle, widgetPosition, widgetAlign);
    deltaTime = .35;
    lastHitTime = ofGetElapsedTimef();
    bIsMinified = false;
    lastHitTime = 0;
    bTitleLabelHit = false;
    hitPoint = ofxUIVec2f(0.0, 0.0);
}

void ofxUISuperCanvas::setDeltaTime(float _deltaTime)
{
    deltaTime = _deltaTime;
}

void ofxUISuperCanvas::setMinified(bool _bIsMinified)
{
    bIsMinified = _bIsMinified;
    if(bIsMinified)
    {
        minify();
    }
    else
    {
        maximize();
    }
}

bool ofxUISuperCanvas::isMinified()
{
    return bIsMinified;
}

void ofxUISuperCanvas::toggleMinified()
{
    setMinified(!bIsMinified);
}

ofxUILabel *ofxUISuperCanvas::getCanvasTitle()
{
    return canvasTitle;
}

#ifdef TARGET_OPENGLES

void ofxUISuperCanvas::touchDown(float x, float y, int id)
{
    if(touchId == -1)
    {
        if(rect->inside(x, y) && canvasTitle->isHit(x, y))
        {
            touchId = id;
            bTitleLabelHit = true;
            hitPoint.set(x - rect->getX(), y - rect->getY());
            return;
        }
    }
    canvasTouchDown(x, y, id);
}

void ofxUISuperCanvas::touchMoved(float x, float y, int id)
{
    if(touchId == id)
    {
        if(bTitleLabelHit)
        {
            rect->setX(x - hitPoint.x);
            rect->setY(y - hitPoint.y);
            return;
        }
    }
    canvasTouchMoved(x, y, id);
}

void ofxUISuperCanvas::touchUp(float x, float y, int id)
{
    if(touchId == id)
    {
        touchId = -1;
        bTitleLabelHit = false;
    }
    canvasTouchUp(x, y, id);
}

void ofxUISuperCanvas::touchDoubleTap(float x, float y, int id)
{
    if(rect->inside(x, y) && canvasTitle->isHit(x, y))
    {
        toggleMinified();
        return;
    }
    canvasTouchDoubleTap(x, y, id);
}

void ofxUISuperCanvas::touchCancelled(float x, float y, int id)
{
    if(touchId == id)
    {
        touchId = -1;
        bTitleLabelHit = false;
    }
    canvasTouchCancelled(x, y, id);
}

#else

void ofxUISuperCanvas::onMouseReleased(ofMouseEventArgs& data)
{
    bTitleLabelHit = false;
    mouseReleased(data.x, data.y, data.button);
}

void ofxUISuperCanvas::onMousePressed(ofMouseEventArgs& data)
{
    if(rect->inside(data.x, data.y) && canvasTitle->isHit(data.x, data.y))
    {
        bTitleLabelHit = true;
        hitPoint.set(data.x - rect->getX(), data.y - rect->getY());
        
        if((ofGetElapsedTimef() - lastHitTime) < deltaTime)
        {
            toggleMinified();
            return;
        }
        lastHitTime = ofGetElapsedTimef();
    }
    mousePressed(data.x, data.y, data.button);
}

void ofxUISuperCanvas::onMouseDragged(ofMouseEventArgs& data)
{
    if(bTitleLabelHit)
    {
        rect->setX(data.x - hitPoint.x);
        rect->setY(data.y - hitPoint.y);
        return;
    }
    mouseDragged(data.x, data.y, data.button);
}

#endif

void ofxUISuperCanvas::saveSettings(string fileName)
{
    ofXml *XML = new ofXml();
    XML->addChild("UI");
    XML->addChild("Canvas");
    XML->setTo("Canvas");
    XML->addValue("Kind", getKind());
    XML->addValue("Name", getName());
    XML->addValue("IsMinified", (bIsMinified ? 1 : 0));
    XML->addValue("XPosition", rect->getX());
    XML->addValue("YPosition", rect->getY());
    XML->reset();
    for(int i = 0; i < widgetsWithState.size(); i++) {
        XML->reset();
        XML->addChild("Widget");
        XML->setTo("//Widget["+ofToString(i)+"]");
        XML->addValue("Kind", widgetsWithState[i]->getKind());
        XML->addValue("Name", widgetsWithState[i]->getName());
        writeSpecificWidgetData(widgetsWithState[i], XML);
    }
    XML->save(fileName);
    delete XML;
}

void ofxUISuperCanvas::loadSettings(string fileName)
{
    ofXml *XML = new ofXml();
    if(XML->load(fileName))
    {
        int widgetTags = XML->getNumChildren("Widget");
        for(int i = 0; i < widgetTags; i++)
        {
            XML->setTo("//Widget["+ofToString(i)+"]");
            string name = XML->getValue("Name");
            ofxUIWidget *widget = getWidget(name);
            if(widget != NULL)
            {
                loadSpecificWidgetData(widget, XML);
                if(bTriggerWidgetsUponLoad)
                {
                    triggerEvent(widget);
                }
            }
        }
        XML->setTo("//Canvas");
        int value = XML->getIntValue("IsMinified");
        setMinified((value ? 1 : 0));
        rect->setX(XML->getFloatValue("XPosition"));
        rect->setY(XML->getFloatValue("YPosition"));
    }
    hasKeyBoard = false;
    delete XML;
}

void ofxUISuperCanvas::addWidgetToHeader(ofxUIWidget *widget)
{
    //        widget->setEmbedded(true);
    headerWidgets.push_back(widget);
}

void ofxUISuperCanvas::removeWidgets()
{
    ofxUICanvas::removeWidgets();
    headerWidgets.clear();
    
    canvasTitle = new ofxUILabel(rect->getWidth()-widgetSpacing*2, title, size);
    canvasTitle->setEmbedded(true);
    headerWidgets.push_back(canvasTitle);
    addWidgetPosition(canvasTitle, widgetPosition, widgetAlign);
}

void ofxUISuperCanvas::minify()
{
    for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        ofxUIWidget *w = (*it);
        if(w != NULL)
        {
            w->setVisible(false);
        }
    }
    for(vector<ofxUIWidget *>::iterator it = headerWidgets.begin(); it != headerWidgets.end(); ++it)
    {
        ofxUIWidget *w = (*it);
        if(w != NULL)
        {
            w->setVisible(true);
        }
    }
    autoSizeToFitWidgets();
}

void ofxUISuperCanvas::maximize()
{
    for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        ofxUIWidget *w = (*it);
        if(w != NULL)
        {
            w->setVisible(true);
        }
    }
    autoSizeToFitWidgets();
}
