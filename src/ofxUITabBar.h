#ifndef OFXUI_TAB_BAR
#define OFXUI_TAB_BAR

#include "ofxUICanvas.h"
#include "ofxUIScrollableCanvas.h"

class ofxUITabBar : public ofxUICanvas
{
public:
    ~ofxUITabBar()
    {
        ofRemoveListener(newGUIEvent, this, &ofxUITabBar::mainUiEvent);
    }
    
    ofxUITabBar(float x, float y, float w, float h) : ofxUICanvas(x,y,w,h)
    {
        initTabBar();
    }
    
    
    ofxUITabBar() : ofxUICanvas()
    {
        initTabBar();
    }
    
    void initTabBar()
    {
        kind = OFX_UI_WIDGET_TABBAR;
        autoSizeToFitWidgets();
        ofAddListener(newGUIEvent, this, &ofxUITabBar::mainUiEvent);
        active = NULL; 
    }
    
    void addCanvas(ofxUICanvas *_canvas)
    {
        ofxUIToggle* newToggle = addToggle(_canvas->getName(), false);
        canvases.insert ( pair<ofxUIToggle*, ofxUICanvas*>( newToggle, _canvas) );
        _canvas->disable();
        autoSizeToFitWidgets();
    }

    void addCanvas(ofxUIScrollableCanvas *_canvas)
    {
        ofxUIToggle* newToggle = addToggle(_canvas->getName(), false);
        canvases.insert ( pair<ofxUIToggle*, ofxUICanvas*>( newToggle, _canvas) );
        _canvas->disable();
        autoSizeToFitWidgets();
    }
    
    void mainUiEvent(ofxUIEventArgs &event)
    {
        string name = event.widget->getName();
        
        for (map<ofxUIToggle*, ofxUICanvas*>::iterator it=canvases.begin(); it!=canvases.end(); ++it) {
            if(it->second->getName() == name) {
                active = it->second;
                it->first->setValue(true);
                it->second->enable();
            } else {
                it->first->setValue(false);
                it->second->disable();
            }
            
        }
    }
    
    void enable()
    {
        ofxUICanvas::enable();
        
        if (active != NULL) {
            active->enable();
        }
    }
    
    void disable()
    {
        ofxUICanvas::disable();

        if (active != NULL) {
            active->disable();
        }
    }
    
    void toggleVisible()
    {
        ofxUICanvas::toggleVisible();
        
        if (active != NULL) {
            active->toggleVisible();
        }
    }
    
    ofxUICanvas* getActiveCanvas()
    {
        return active;
    }
    
    bool isHit(int x, int y)
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

#ifndef OFX_UI_NO_XML
    
    void saveSettings(string pathToSaveTo, string fileNamePrefix)
    {                
        for (map<ofxUIToggle*, ofxUICanvas*>::iterator it=canvases.begin(); it!=canvases.end(); ++it) {
            it->second->saveSettings(pathToSaveTo + fileNamePrefix + it->second->getName() + ".xml");
        }
    }
    
    void loadSettings(string pathToLoadFrom, string fileNamePrefix)
    {        
        for (map<ofxUIToggle*, ofxUICanvas*>::iterator it=canvases.begin(); it!=canvases.end(); ++it) {
            it->second->loadSettings(pathToLoadFrom + fileNamePrefix + it->second->getName() + ".xml");
        }
    }

#endif
    
protected:
    map<ofxUIToggle*, ofxUICanvas*> canvases;
    ofxUICanvas *active;
    
};



#endif
