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

#ifndef OFXUI_SUPER_CANVAS
#define OFXUI_SUPER_CANVAS

#include "ofxUICanvas.h"

class ofxUISuperCanvas : public ofxUICanvas
{
public:    
    ofxUISuperCanvas(string _label, ofxUIRectangle r, int _size = OFX_UI_FONT_MEDIUM) : ofxUICanvas(r)
    {
        superInit(_label, _size);
    }
    
    ofxUISuperCanvas(string _label, float x, float y, float w, float h, int _size = OFX_UI_FONT_MEDIUM) : ofxUICanvas(x, y, w, h)
    {
        superInit(_label, _size);        
    }
    
    ofxUISuperCanvas(string _label, float x, float y, float w, float h, ofxUICanvas *sharedResources, int _size = OFX_UI_FONT_MEDIUM) : ofxUICanvas(x, y, w, h, sharedResources)
    {
        superInit(_label, _size);
    }
    
    ofxUISuperCanvas(string _label, int _size = OFX_UI_FONT_MEDIUM) : ofxUICanvas()
    {
        superInit(_label, _size);
    }
    
    ofxUISuperCanvas(string _label, ofxUICanvas *sharedResources, int _size = OFX_UI_FONT_MEDIUM) : ofxUICanvas(sharedResources)
    {
        superInit(_label, _size);
    }

    void superInit(string _label, int _size)
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
    
    void setDeltaTime(float _deltaTime)
    {
        deltaTime = _deltaTime; 
    }
    
    void setMinified(bool _bIsMinified)
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
    
    bool isMinified()
    {
        return bIsMinified; 
    }
    
    void toggleMinified()
    {
        setMinified(!bIsMinified);
    }
    
    ofxUILabel *getCanvasTitle()
    {
        return canvasTitle;
    }
    
#ifdef TARGET_OPENGLES
	
    virtual void touchDown(float x, float y, int id)
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
    
    virtual void touchMoved(float x, float y, int id)
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
    
    virtual void touchUp(float x, float y, int id)
    {
        if(touchId == id)
        {
            touchId = -1;
            bTitleLabelHit = false;
        }
        canvasTouchUp(x, y, id);
    }
    
    virtual void touchDoubleTap(float x, float y, int id)
    {
        if(rect->inside(x, y) && canvasTitle->isHit(x, y))
        {
            toggleMinified();
            return;
        }
        canvasTouchDoubleTap(x, y, id);
    }
    
    virtual void touchCancelled(float x, float y, int id)
    {
        if(touchId == id)
        {
            touchId = -1;
            bTitleLabelHit = false;
        }
        canvasTouchCancelled(x, y, id);
    }

#else
    
    virtual void onMouseReleased(ofMouseEventArgs& data)
    {
        bTitleLabelHit = false; 
        mouseReleased(data.x, data.y, data.button);
    }
    
    virtual void onMousePressed(ofMouseEventArgs& data)
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
        
    virtual void onMouseDragged(ofMouseEventArgs& data)
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
    
#ifndef OFX_UI_NO_XML
    
    virtual void saveSettings(string fileName)
    {
        ofxXmlSettings *XML = new ofxXmlSettings();
        XML->addTag("Canvas");
        XML->pushTag("Canvas", 0);
        XML->setValue("Kind", getKind(), 0);
        XML->setValue("Name", getName(), 0);
        XML->setValue("IsMinified", (bIsMinified ? 1 : 0), 0);
        XML->setValue("XPosition", rect->getX(), 0);
        XML->setValue("YPosition", rect->getY(), 0);
        XML->popTag();        
        for(int i = 0; i < widgetsWithState.size(); i++)
        {
            int index = XML->addTag("Widget");
            if(XML->pushTag("Widget", index))
            {
                XML->setValue("Kind", widgetsWithState[i]->getKind(), 0);
                XML->setValue("Name", widgetsWithState[i]->getName(), 0);
                writeSpecificWidgetData(widgetsWithState[i], XML);
            }
            XML->popTag();
        }
        XML->saveFile(fileName);
        delete XML;
    }
    
    virtual void loadSettings(string fileName)
    {
        ofxXmlSettings *XML = new ofxXmlSettings();
        XML->loadFile(fileName);                
        int widgetTags = XML->getNumTags("Widget");
        for(int i = 0; i < widgetTags; i++)
        {
            XML->pushTag("Widget", i);
            string name = XML->getValue("Name", "NULL", 0);
            ofxUIWidget *widget = getWidget(name);
            if(widget != NULL)
            {
                loadSpecificWidgetData(widget, XML);
                if(bTriggerWidgetsUponLoad)
                {
                    triggerEvent(widget);
                }
            }
            XML->popTag();
        }
        XML->pushTag("Canvas", 0);
        int value = XML->getValue("IsMinified", (bIsMinified ? 1 : 0), 0);
        setMinified((value ? 1 : 0));
        rect->setX(XML->getValue("XPosition", rect->getX(), 0));
        rect->setY(XML->getValue("YPosition", rect->getY(), 0));
        XML->popTag();        
        hasKeyBoard = false;
        delete XML;
    }
    
#endif

    //These header widgets are meant to stay visible when minified...
    void addWidgetToHeader(ofxUIWidget *widget)
    {
//        widget->setEmbedded(true); 
        headerWidgets.push_back(widget);
    }
    
    void removeWidgets()
    {     
        ofxUICanvas::removeWidgets();
        headerWidgets.clear();
        
        canvasTitle = new ofxUILabel(rect->getWidth()-widgetSpacing*2, title, size);
        canvasTitle->setEmbedded(true);
        headerWidgets.push_back(canvasTitle);
        addWidgetPosition(canvasTitle, widgetPosition, widgetAlign);
    }
    
protected:
    void minify()
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
    
    void maximize()
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
    
    int size; 
    string title; 
    ofxUILabel *canvasTitle;
    vector<ofxUIWidget *> headerWidgets;
    
    ofxUIVec2f hitPoint;
    float deltaTime;
    float lastHitTime;
    bool bIsMinified;
    bool bTitleLabelHit;
};



#endif
