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

#ifndef OFXUI_CANVAS
#define OFXUI_CANVAS

#include "ofxUIWidget.h"
#include <vector>
#include <map>

class ofxUICanvas : public ofxUIWidget
{    
public:	
    ~ofxUICanvas() 
    {
		delete GUIevent; 
        if(!hasSharedResources)
        {
            delete font_large; 
            delete font_medium;
            delete font_small;		
        }
		for(int i = 0; i < widgets.size(); i++)
		{
			ofxUIWidget *w = widgets[i]; 
			delete w; 
		}
		widgets.clear();             
    }
    
    ofxUICanvas(float x, float y, float w, float h) 
    {
        rect = new ofxUIRectangle(x,y,w,h);        
        init(w,h);
    }

    ofxUICanvas(float x, float y, float w, float h, ofxUICanvas *sharedResources) 
    {
        rect = new ofxUIRectangle(x,y,w,h);        
        init(w,h, sharedResources);
    }
    
    ofxUICanvas() 
    {
        float w = ofGetWidth(); 
        float h = ofGetHeight(); 
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w,h);
        setDrawBack(false); 
    }

    ofxUICanvas(ofxUICanvas *sharedResources) 
    {
        float w = ofGetWidth(); 
        float h = ofGetHeight(); 
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w,h, sharedResources);
        setDrawBack(false); 
    }
    
    void init(int w, int h)
    {
        name = "OFX_UI_WIDGET_CANVAS"; 
		kind = OFX_UI_WIDGET_CANVAS; 

		enabled = false; 
		enable(); 
		
		enable_highlight_outline = false; 
		enable_highlight_fill = false; 
        
		GUIevent = new ofxUIEventArgs(this); 
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding*2.0);
		paddedRect->setParent(rect);
        
        font_large = new ofTrueTypeFont();
        font_medium = new ofTrueTypeFont();
        font_small = new ofTrueTypeFont();
        
        fontName = OFX_UI_FONT_NAME;
        setFont(fontName,true, true, false, 0.0, OFX_UI_FONT_RESOLUTION);
                
		font = font_medium; 
		lastAdded = NULL; 
        uniqueIDs = 0;         
        widgetSpacing = OFX_UI_GLOBAL_WIDGET_SPACING; 
        hasKeyBoard = false; 
    }
    
    void init(int w, int h, ofxUICanvas *sharedResources)
    {
        name = "OFX_UI_WIDGET_CANVAS"; 
		kind = OFX_UI_WIDGET_CANVAS; 

		enabled = false; 		
		enable(); 
		
		enable_highlight_outline = false; 
		enable_highlight_fill = false; 
        
		GUIevent = new ofxUIEventArgs(this); 
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding*2.0);
		paddedRect->setParent(rect);

        hasSharedResources = true; 
        font_large = sharedResources->getFontLarge();
        font_medium = sharedResources->getFontMedium();
        font_small = sharedResources->getFontSmall();
        
        fontName = OFX_UI_FONT_NAME;
//        setFont(fontName,true, true, false, 0.0, OFX_UI_FONT_RESOLUTION);
        
		font = font_medium; 
		lastAdded = NULL; 
        uniqueIDs = 0;         
        widgetSpacing = OFX_UI_GLOBAL_WIDGET_SPACING; 
        hasKeyBoard = false; 
    }    

    void saveSettings(string fileName)
    {
        ofxXmlSettings *XML = new ofxXmlSettings(); 
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
    
    void writeSpecificWidgetData(ofxUIWidget *widget, ofxXmlSettings *XML)
    {
        int kind = widget->getKind();        
        switch (kind) {
            case OFX_UI_WIDGET_IMAGETOGGLE:    
            case OFX_UI_WIDGET_MULTIIMAGETOGGLE: 
            case OFX_UI_WIDGET_LABELTOGGLE:                
            case OFX_UI_WIDGET_TOGGLE:
            {
                ofxUIToggle *toggle = (ofxUIToggle *) widget; 
                XML->setValue("Value", (toggle->getValue() ? 1 : 0), 0);                
            }
                break;
                
            case OFX_UI_WIDGET_MULTIIMAGESLIDER_H:
            case OFX_UI_WIDGET_MULTIIMAGESLIDER_V:                                 
            case OFX_UI_WIDGET_IMAGESLIDER_H:
            case OFX_UI_WIDGET_IMAGESLIDER_V:
            case OFX_UI_WIDGET_BILABELSLIDER:
            case OFX_UI_WIDGET_CIRCLESLIDER:
            case OFX_UI_WIDGET_MINIMALSLIDER:                
            case OFX_UI_WIDGET_SLIDER_H:
            case OFX_UI_WIDGET_SLIDER_V:
            {
                ofxUISlider *slider = (ofxUISlider *) widget; 
                XML->setValue("Value", slider->getScaledValue(), 0); 
            }
                break;

            case OFX_UI_WIDGET_RSLIDER_H:
            case OFX_UI_WIDGET_RSLIDER_V:
            {
                ofxUIRangeSlider *rslider = (ofxUIRangeSlider *) widget; 
                XML->setValue("HighValue", rslider->getScaledValueHigh(), 0); 
                XML->setValue("LowValue", rslider->getScaledValueLow(), 0);                 
            }
                break;

            case OFX_UI_WIDGET_NUMBERDIALER:
            {
                ofxUINumberDialer *numdialer = (ofxUINumberDialer *) widget; 
                XML->setValue("Value", numdialer->getValue(), 0); 
            }
                break;

            case OFX_UI_WIDGET_2DPAD:
            {
                ofxUI2DPad *pad = (ofxUI2DPad *) widget; 
                XML->setValue("XValue", pad->getScaledValue().x, 0); 
                XML->setValue("YValue", pad->getScaledValue().y, 0);                 
            }
                break;

            case OFX_UI_WIDGET_TEXTINPUT:
            {
                ofxUITextInput *textInput = (ofxUITextInput *) widget; 
                XML->setValue("Value", textInput->getTextString(), 0);                 
            }
                break;
                                
            case OFX_UI_WIDGET_ROTARYSLIDER:
            {
                ofxUIRotarySlider *rotslider = (ofxUIRotarySlider *) widget;
                XML->setValue("Value", rotslider->getScaledValue(), 0); 
            }
                break;
                
            case OFX_UI_WIDGET_IMAGESAMPLER:
            {
                ofxUIImageSampler *imageSampler = (ofxUIImageSampler *) widget;                 
                XML->setValue("XValue", imageSampler->getValue().x, 0); 
                XML->setValue("YValue", imageSampler->getValue().y, 0);                 
                XML->setValue("RColor", imageSampler->getColor().r, 0);                                 
                XML->setValue("GColor", imageSampler->getColor().g, 0);                                 
                XML->setValue("BColor", imageSampler->getColor().b, 0);                                                 
                XML->setValue("AColor", imageSampler->getColor().a, 0);                                 
            }
                break;

            default:
                break;
        }
    }
    
    void loadSettings(string fileName)
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
                triggerEvent(widget); 
            }
            XML->popTag(); 
        }
        hasKeyBoard = false;                
        delete XML; 
    }
    
    void loadSpecificWidgetData(ofxUIWidget *widget, ofxXmlSettings *XML)
    {
        int kind = widget->getKind();        
        switch (kind) 
        {
            case OFX_UI_WIDGET_IMAGETOGGLE:    
            case OFX_UI_WIDGET_MULTIIMAGETOGGLE: 
            case OFX_UI_WIDGET_LABELTOGGLE:                
            case OFX_UI_WIDGET_TOGGLE:
            {
                ofxUIToggle *toggle = (ofxUIToggle *) widget; 
                int value = XML->getValue("Value", (toggle->getValue() ? 1 : 0), 0);                             
                toggle->setValue((value ? 1 : 0)); 
            }
                break;

            case OFX_UI_WIDGET_MULTIIMAGESLIDER_H:
            case OFX_UI_WIDGET_MULTIIMAGESLIDER_V:                 
            case OFX_UI_WIDGET_IMAGESLIDER_H:
            case OFX_UI_WIDGET_IMAGESLIDER_V:                
            case OFX_UI_WIDGET_BILABELSLIDER:    
            case OFX_UI_WIDGET_CIRCLESLIDER:               
            case OFX_UI_WIDGET_MINIMALSLIDER:
            case OFX_UI_WIDGET_SLIDER_H:
            case OFX_UI_WIDGET_SLIDER_V:
            {
                ofxUISlider *slider = (ofxUISlider *) widget; 
                float value = XML->getValue("Value", slider->getScaledValue(), 0);            
                slider->setValue(value); 
            }
                break;
                
            case OFX_UI_WIDGET_RSLIDER_H:
            case OFX_UI_WIDGET_RSLIDER_V:
            {
                ofxUIRangeSlider *rslider = (ofxUIRangeSlider *) widget; 
                float valueHigh = XML->getValue("HighValue", rslider->getScaledValueHigh(), 0); 
                float valueLow = XML->getValue("LowValue", rslider->getScaledValueLow(), 0); 
                rslider->setValueHigh(valueHigh);
                rslider->setValueLow(valueLow);
            }
                break;
                
            case OFX_UI_WIDGET_NUMBERDIALER:
            {
                ofxUINumberDialer *numdialer = (ofxUINumberDialer *) widget; 
                float value = XML->getValue("Value", numdialer->getValue(), 0);             
                numdialer->setValue(value);                 
            }
                break;
                
            case OFX_UI_WIDGET_2DPAD:
            {
                ofxUI2DPad *pad = (ofxUI2DPad *) widget; 
                float valueX = XML->getValue("XValue", pad->getScaledValue().x, 0); 
                float valueY = XML->getValue("YValue", pad->getScaledValue().y, 0); 
                pad->setValue(ofPoint(valueX, valueY)); 
            }
                break;
                
            case OFX_UI_WIDGET_TEXTINPUT:
            {
                ofxUITextInput *textInput = (ofxUITextInput *) widget; 
                string value = XML->getValue("Value", textInput->getTextString(), 0);             
                textInput->setTextString(value); 
            }
                break;                
                
            case OFX_UI_WIDGET_ROTARYSLIDER:
            {
                ofxUIRotarySlider *rotslider = (ofxUIRotarySlider *) widget;
                float value = XML->getValue("Value", rotslider->getScaledValue(), 0);            
                rotslider->setValue(value); 
            }
                break;
                
            case OFX_UI_WIDGET_IMAGESAMPLER:
            {
                ofxUIImageSampler *imageSampler = (ofxUIImageSampler *) widget; 
                float valueX = XML->getValue("XValue", imageSampler->getValue().x, 0);   
                float valueY = XML->getValue("YValue", imageSampler->getValue().y, 0);                   
                
                int r = XML->getValue("RColor", imageSampler->getColor().r, 0);                                 
                int g = XML->getValue("GColor", imageSampler->getColor().g, 0);                                 
                int b = XML->getValue("BColor", imageSampler->getColor().b, 0);                                                 
                int a = XML->getValue("AColor", imageSampler->getColor().a, 0);                                 
                
                imageSampler->setValue(ofPoint(valueX, valueY));
                imageSampler->setColor(ofColor(r,g,b,a));
            }
                break;
                
            default:
                break;
        }        
    }
     
    ofTrueTypeFont *getFontLarge()
    {
        return font_large;
    }    
    
    ofTrueTypeFont *getFontMedium()
    {
        return font_medium;
    }

    ofTrueTypeFont *getFontSmall()
    {
        return font_small;
    }

    //Easy Font setting contributed from Colin Duffy (colin@tomorrowevening.com)
    bool setFont(string filename, bool _bAntiAliased=true, bool _bFullCharacterSet=true, bool makeContours=false, float simplifyAmt=0.0, int dpi=OFX_UI_FONT_RESOLUTION) 
    {
        bool large = updateFont(OFX_UI_FONT_LARGE, filename, OFX_UI_FONT_LARGE_SIZE, _bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt, dpi);
        bool medium = updateFont(OFX_UI_FONT_MEDIUM, filename, OFX_UI_FONT_MEDIUM_SIZE, _bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt, dpi);
        bool small = updateFont(OFX_UI_FONT_SMALL, filename, OFX_UI_FONT_SMALL_SIZE, _bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt, dpi);
        bool successful = large && medium && small;
        if( successful ) fontName = filename;
        return successful;
    }
    
    void setFontSize(ofxWidgetFontType _kind, int _size, int _resolution = OFX_UI_FONT_RESOLUTION)
    {
        switch(_kind)
        {
            case OFX_UI_FONT_LARGE:
                if(font_large != NULL)
                {
                    delete font_large;          
                }
                font_large = new ofTrueTypeFont(); 
                font_large->loadFont(fontName,_size,true, true, false, 0.0,_resolution); 				            
                break; 

            case OFX_UI_FONT_MEDIUM:
                if(font_medium != NULL)
                {
                    delete font_medium;          
                }
                font_medium = new ofTrueTypeFont(); 
                font_medium->loadFont(fontName,_size,true, true, false, 0.0,_resolution); 				                            
                break; 

            case OFX_UI_FONT_SMALL:
                if(font_small != NULL)
                {
                    delete font_small;          
                }
                font_small = new ofTrueTypeFont(); 
                font_small->loadFont(fontName,_size,true, true, false, 0.0,_resolution); 				                            
                break; 
        }
    }
    
    void setWidgetSpacing(float _widgetSpacing)
    {
        widgetSpacing = _widgetSpacing; 
    }
    
    float getWidgetSpacing()
    {
        return widgetSpacing;
    }
   
    bool isEnabled()
	{
		return enabled; 
	}
	
    void setVisible(bool _visible)
    {
        visible = _visible; 
        if(visible)
        {
            enable();
        }
        else
        {
            disable();
        }
    }
    
    
	void toggleVisible()
	{
		if(isEnabled())
		{
			disable(); 
		}
		else {
			enable(); 
		}
	}

    bool hasKeyboardFocus()
    {
        return hasKeyBoard; 
    }
	
	void enable()
	{
        if(!isEnabled())
        {            
            enabled = true; 
            enableAppEventCallbacks();        
    #ifdef TARGET_OPENGLES
            enableTouchEventCallbacks();
    #else
            enableMouseEventCallbacks();
            enableWindowEventCallbacks(); 
    #endif
            enableKeyEventCallbacks();
        }
	}
	
	void disable()
	{
        if(isEnabled())
        {                    
            enabled = false; 
            disableAppEventCallbacks();        
    #ifdef TARGET_OPENGLES
            disableTouchEventCallbacks();
    #else
            disableMouseEventCallbacks();
            disableWindowEventCallbacks();
    #endif
            disableKeyEventCallbacks();
        }
    }
	
	//App Callbacks
    void enableAppEventCallbacks()
    {
#if OF_VERSION >= 7 && OF_VERSION_MINOR > 0
        ofAddListener(ofEvents().update, this, &ofxUICanvas::onUpdate);
        ofAddListener(ofEvents().draw, this, &ofxUICanvas::onDraw);
        ofAddListener(ofEvents().exit, this, &ofxUICanvas::onExit);
#else
        ofAddListener(ofEvents.update, this, &ofxUICanvas::onUpdate);
        ofAddListener(ofEvents.draw, this, &ofxUICanvas::onDraw);
        ofAddListener(ofEvents.exit, this, &ofxUICanvas::onExit);
#endif
    }
	
	//App Callbacks
    void disableAppEventCallbacks()
    {
#if OF_VERSION >= 7 && OF_VERSION_MINOR > 0
        ofRemoveListener(ofEvents().update, this, &ofxUICanvas::onUpdate);
        ofRemoveListener(ofEvents().draw, this, &ofxUICanvas::onDraw);
        ofRemoveListener(ofEvents().exit, this, &ofxUICanvas::onExit);
#else
        ofRemoveListener(ofEvents.update, this, &ofxUICanvas::onUpdate);
        ofRemoveListener(ofEvents.draw, this, &ofxUICanvas::onDraw);
        ofRemoveListener(ofEvents.exit, this, &ofxUICanvas::onExit);
#endif
    }
	
#ifdef TARGET_OPENGLES
	
	//Touch Callbacks
    void enableTouchEventCallbacks()
    {
#if OF_VERSION >= 7 && OF_VERSION_MINOR > 0
        ofAddListener(ofEvents().touchUp, this, &ofxUICanvas::onTouchUp);
        ofAddListener(ofEvents().touchDown, this, &ofxUICanvas::onTouchDown);
        ofAddListener(ofEvents().touchMoved, this, &ofxUICanvas::onTouchMoved);
        ofAddListener(ofEvents().touchCancelled, this, &ofxUICanvas::onTouchCancelled);
        ofAddListener(ofEvents().touchDoubleTap, this, &ofxUICanvas::onTouchDoubleTap);
#else
        ofAddListener(ofEvents.touchUp, this, &ofxUICanvas::onTouchUp);
        ofAddListener(ofEvents.touchDown, this, &ofxUICanvas::onTouchDown);
        ofAddListener(ofEvents.touchMoved, this, &ofxUICanvas::onTouchMoved);
        ofAddListener(ofEvents.touchCancelled, this, &ofxUICanvas::onTouchCancelled);
        ofAddListener(ofEvents.touchDoubleTap, this, &ofxUICanvas::onTouchDoubleTap);
#endif
    }	

	void disableTouchEventCallbacks()
    {
#if OF_VERSION >= 7 && OF_VERSION_MINOR > 0
        ofRemoveListener(ofEvents().touchUp, this, &ofxUICanvas::onTouchUp);
        ofRemoveListener(ofEvents().touchDown, this, &ofxUICanvas::onTouchDown);
        ofRemoveListener(ofEvents().touchMoved, this, &ofxUICanvas::onTouchMoved);
        ofRemoveListener(ofEvents().touchCancelled, this, &ofxUICanvas::onTouchCancelled);
        ofRemoveListener(ofEvents().touchDoubleTap, this, &ofxUICanvas::onTouchDoubleTap);
#else
        ofRemoveListener(ofEvents.touchUp, this, &ofxUICanvas::onTouchUp);
        ofRemoveListener(ofEvents.touchDown, this, &ofxUICanvas::onTouchDown);
        ofRemoveListener(ofEvents.touchMoved, this, &ofxUICanvas::onTouchMoved);
        ofRemoveListener(ofEvents.touchCancelled, this, &ofxUICanvas::onTouchCancelled);
        ofRemoveListener(ofEvents.touchDoubleTap, this, &ofxUICanvas::onTouchDoubleTap);
#endif
    }	
	
#else
	
	//Mouse Callbacks
    void enableMouseEventCallbacks()
    {
#if OF_VERSION >= 7 && OF_VERSION_MINOR > 0
        ofAddListener(ofEvents().mouseReleased, this, &ofxUICanvas::onMouseReleased);
        ofAddListener(ofEvents().mousePressed, this, &ofxUICanvas::onMousePressed);
        ofAddListener(ofEvents().mouseMoved, this, &ofxUICanvas::onMouseMoved);
        ofAddListener(ofEvents().mouseDragged, this, &ofxUICanvas::onMouseDragged);
#else
        ofAddListener(ofEvents.mouseReleased, this, &ofxUICanvas::onMouseReleased);
        ofAddListener(ofEvents.mousePressed, this, &ofxUICanvas::onMousePressed);
        ofAddListener(ofEvents.mouseMoved, this, &ofxUICanvas::onMouseMoved);
        ofAddListener(ofEvents.mouseDragged, this, &ofxUICanvas::onMouseDragged);
#endif
    }

	//Mouse Callbacks
    void disableMouseEventCallbacks()
    {
#if OF_VERSION >= 7 && OF_VERSION_MINOR > 0
        ofRemoveListener(ofEvents().mouseReleased, this, &ofxUICanvas::onMouseReleased);
        ofRemoveListener(ofEvents().mousePressed, this, &ofxUICanvas::onMousePressed);
        ofRemoveListener(ofEvents().mouseMoved, this, &ofxUICanvas::onMouseMoved);
        ofRemoveListener(ofEvents().mouseDragged, this, &ofxUICanvas::onMouseDragged);
#else
        ofRemoveListener(ofEvents.mouseReleased, this, &ofxUICanvas::onMouseReleased);
        ofRemoveListener(ofEvents.mousePressed, this, &ofxUICanvas::onMousePressed);
        ofRemoveListener(ofEvents.mouseMoved, this, &ofxUICanvas::onMouseMoved);
        ofRemoveListener(ofEvents.mouseDragged, this, &ofxUICanvas::onMouseDragged);
#endif
    }

    //Window Resize Callback
    void enableWindowEventCallbacks()
    {
#if OF_VERSION >= 7 && OF_VERSION_MINOR > 0
        ofAddListener(ofEvents().windowResized, this, &ofxUICanvas::onWindowResized);        
#else
        ofAddListener(ofEvents.windowResized, this, &ofxUICanvas::onWindowResized);        
#endif
    }

	//Window Resize Callback
    void disableWindowEventCallbacks()
    {
#if OF_VERSION >= 7 && OF_VERSION_MINOR > 0
        ofRemoveListener(ofEvents().windowResized, this, &ofxUICanvas::onWindowResized);        
#else
        ofRemoveListener(ofEvents.windowResized, this, &ofxUICanvas::onWindowResized);        
#endif
    }
	
	
#endif	

    //KeyBoard Callbacks
	void enableKeyEventCallbacks()
	{
#if OF_VERSION >= 7 && OF_VERSION_MINOR > 0
		ofAddListener(ofEvents().keyPressed, this, &ofxUICanvas::onKeyPressed);
		ofAddListener(ofEvents().keyReleased, this, &ofxUICanvas::onKeyReleased);
#else
		ofAddListener(ofEvents.keyPressed, this, &ofxUICanvas::onKeyPressed);
		ofAddListener(ofEvents.keyReleased, this, &ofxUICanvas::onKeyReleased);
#endif
	}

	//KeyBoard Callbacks
	void disableKeyEventCallbacks()
	{
#if OF_VERSION >= 7 && OF_VERSION_MINOR > 0
		ofRemoveListener(ofEvents().keyPressed, this, &ofxUICanvas::onKeyPressed);
		ofRemoveListener(ofEvents().keyReleased, this, &ofxUICanvas::onKeyReleased);
#else
		ofRemoveListener(ofEvents.keyPressed, this, &ofxUICanvas::onKeyPressed);
		ofRemoveListener(ofEvents.keyReleased, this, &ofxUICanvas::onKeyReleased);
#endif
	}

    void onUpdate(ofEventArgs &data) { update(); }
    void onDraw(ofEventArgs &data) { draw(); } 
    void onExit(ofEventArgs &data) { exit(); } 

    
    virtual void update()
    {		
		for(int i = 0; i < widgets.size(); i++)
		{
			widgets[i]->update(); 	
		}		
    }
     
    void draw()
    {
        ofPushStyle(); 
		glDisable(GL_DEPTH_TEST);       
        glDisable(GL_LIGHTING);
        ofEnableBlendMode(OF_BLENDMODE_ALPHA); 
        ofSetRectMode(OF_RECTMODE_CORNER);         
        ofSetLineWidth(1.0);         
        
        drawPadded();
        
        drawPaddedOutline(); 
        
        drawBack(); 
        
        drawFill(); 
        
        drawFillHighlight(); 
        
        drawOutline(); 
        
        drawOutlineHighlight();

		for(int i = widgets.size()-1; i >= 0; i--)
		{
            if(widgets[i]->isVisible())
            {
                widgets[i]->draw(); 	
            }
		}
		
		glDisable(GL_DEPTH_TEST); 
        ofPopStyle();         
    }
    
    void exit()
    {

    }	
        
#ifdef TARGET_OPENGLES
	
    void onTouchDown(ofTouchEventArgs &data)
    {
		touchDown(data); 
    }
    
    void onTouchMoved(ofTouchEventArgs &data) 
    {
		touchMoved(data); 
    }

    void onTouchUp(ofTouchEventArgs &data) 
    {
		touchUp(data); 
    }
	
    void onTouchDoubleTap(ofTouchEventArgs &data)
    {
		touchDoubleTap(data); 
    }
	
	void onTouchCancelled(ofTouchEventArgs &data)
    {
		touchCancelled(data); 
    }
	
	virtual void touchDown(ofTouchEventArgs& touch) 
	{		
        if(rect->inside(touch.x, touch.y))
        {
			for(int i = 0; i < widgets.size(); i++)
			{
				if(widgets[i]->isVisible())	widgets[i]->touchDown(touch); 
			}
		}
	}
    
	virtual void touchMoved(ofTouchEventArgs& touch) 
	{
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible())	widgets[i]->touchMoved(touch);
        }
	}
    
	virtual void touchUp(ofTouchEventArgs& touch) 
	{
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible())	widgets[i]->touchUp(touch); 
        }
	}
    
	virtual void touchDoubleTap(ofTouchEventArgs& touch) 
	{
        if(rect->inside(touch.x, touch.y))
        {
			for(int i = 0; i < widgets.size(); i++)
			{
				if(widgets[i]->isVisible())	widgets[i]->touchDoubleTap(touch); 
			}
		}		
	}
    
	virtual void touchCancelled(ofTouchEventArgs& touch) 
	{		
        if(rect->inside(touch.x, touch.y))
        {
        	for(int i = 0; i < widgets.size(); i++)
			{
				if(widgets[i]->isVisible())	widgets[i]->touchCancelled(touch); 
			}
		}	
	}
	
#else	
    
    void onMouseReleased(ofMouseEventArgs& data) 
    { 
        mouseReleased(data.x, data.y, data.button); 
    }
    
    void onMousePressed(ofMouseEventArgs& data) 
    { 
        mousePressed(data.x, data.y, data.button); 
    }
    
    void onMouseMoved(ofMouseEventArgs& data) 
    { 
        mouseMoved(data.x, data.y); 
    }
    
    void onMouseDragged(ofMouseEventArgs& data) 
    { 
        mouseDragged(data.x, data.y, data.button); 
    }
	
	virtual void mouseMoved(int x, int y ) 
    {
        if(rect->inside(x, y))
        {
			for(int i = 0; i < widgets.size(); i++)
			{                
				if(widgets[i]->isVisible()) widgets[i]->mouseMoved(x, y); 
			}
		}	
    }
    
    virtual void mouseDragged(int x, int y, int button) 
    {		
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible())	widgets[i]->mouseDragged(x, y, button); 
        }                
    }
    
    virtual void mousePressed(int x, int y, int button) 
    {
        if(rect->inside(x, y))
        {
			for(int i = 0; i < widgets.size(); i++)
			{
				if(widgets[i]->isVisible()) widgets[i]->mousePressed(x, y, button); 
			}
		}		
    }
    
    virtual void mouseReleased(int x, int y, int button) 
    {		        
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible()) widgets[i]->mouseReleased(x, y, button); 
        }    
    }
	
    void onWindowResized(ofResizeEventArgs& data) 
    { 
		windowResized(data.width, data.height); 
    } 	
    
    virtual void windowResized(int w, int h) 
    {
		for(int i = 0; i < widgets.size(); i++)
		{
			widgets[i]->windowResized(w, h); 
		}
    }
    
#endif	

	void onKeyPressed(ofKeyEventArgs& data)
    {
		keyPressed(data.key);
    }

    void onKeyReleased(ofKeyEventArgs& data)
    {
		keyReleased(data.key);
    }

    virtual void keyPressed(int key)
    {
        for(int i = 0; i < widgets.size(); i++)
		{
			widgets[i]->keyPressed(key);
		}
    }

    virtual void keyReleased(int key)
    {
		for(int i = 0; i < widgets.size(); i++)
		{
			widgets[i]->keyReleased(key);
		}
    }
	
    bool isHit(int x, int y)
    {
        if(isEnabled())
        {
            return rect->inside(x, y);
        }
        else
        {
            return false; 
        }
    }
    
    ofxUIWidget *getWidgetHit(float x, float y)
    {
        if(isEnabled() && rect->inside(x, y))
        {
            for(int i = 0; i < widgets.size(); i++)
            {
                if(widgets[i]->isHit(x, y))
                {
                    return widgets[i]; 
                }
            }
            return NULL;
        }
        else
        {
            return NULL; 
        }        
    }
    

    void stateChange()
    {        
        switch (state) 
		{
            case OFX_UI_STATE_NORMAL:
            {            
                draw_fill_highlight = false;             
                draw_outline_highlight = false;             
            }
                break;
            case OFX_UI_STATE_OVER:
            {
                draw_fill_highlight = false;        
				if(enable_highlight_outline)
				{
					draw_outline_highlight = true;                         
				}
            }
                break;
            case OFX_UI_STATE_DOWN:
            {
				if(enable_highlight_fill)
				{
					draw_fill_highlight = true;     				
				}
                draw_outline_highlight = false;             
            }
                break;
            case OFX_UI_STATE_SUSTAINED:
            {
                draw_fill_highlight = false;            
                draw_outline_highlight = false;                         
            }
                break;            
                
            default:
                break;
        }        
    }
    
    void autoSizeToFitWidgets()
    {        
        float maxWidth = 0;
        float maxHeight = 0;

        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible())
            {
                ofxUIRectangle* wr = widgets[i]->getRect(); 
                float widgetwidth = wr->x+wr->getWidth();

                float widgetheight = wr->y+wr->getHeight();
                
                if(widgetwidth > maxWidth)
                {
                    maxWidth = wr->x+widgets[i]->getPaddingRect()->getWidth();
                }                        
                if(widgetheight > maxHeight)
                {
                    maxHeight = wr->y+widgets[i]->getPaddingRect()->getHeight();                                                                        
                }        
            }
        }
        
        rect->setWidth(maxWidth);
        rect->setHeight(maxHeight);
        paddedRect->width = rect->width+padding*2.0;
        paddedRect->height = rect->height+padding*2.0;        
    }
    
    void centerWidgetsOnCanvas(bool centerHorizontally=true, bool centerVertically=true)
    {            
        float xMin = 0; 
        float yMin = 0;
        
        float xMax = 0; 
        float yMax = 0;
        
        float w = 0; 
        float h = 0; 
        
        for(int i = 0; i < widgets.size(); i++)
        {
//            if(widgets[i]->isVisible())
//            {
                ofxUIRectangle* wr = widgets[i]->getRect(); 
                if(wr->x < xMin)
                {
                    xMin = wr->x; 
                }
                if((wr->x + wr->getWidth()) > xMax)
                {
                    xMax = (wr->x + wr->getWidth()); 
                }
                
                if(wr->y < yMin)
                {
                    yMin = wr->y; 
                }
                if((wr->y + wr->getHeight()) > yMax)
                {
                    yMax = (wr->y + wr->getHeight()); 
                }                                                                    
//            }
        }     
        
        w = xMax - xMin;
        h = yMax - yMin;            
        
        float moveDeltaX = rect->getHalfWidth() - w*.5; 
        float moveDeltaY = rect->getHalfHeight() - h*.5;
                
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible() && !(widgets[i]->isEmbedded()))
            {
                ofxUIRectangle* wr = widgets[i]->getRect(); 
                if(centerHorizontally) wr->x += moveDeltaX-padding;             
                if(centerVertically) wr->y += moveDeltaY-padding;                             
            }
        }           
//        addWidget(new ofxUISpacer(xMin+moveDeltaX, yMin+moveDeltaY, w, h));
    }    
    
    void centerWidgetsHorizontallyOnCanvas()
    {
        centerWidgetsOnCanvas(true, false);
    }

    void centerWidgetsVerticallyOnCanvas()
    {
        centerWidgetsOnCanvas(false, true);
    }
    
    void centerWidgets()
    {
        centerWidgetsOnCanvas(); 
    }
    
    void removeWidget(ofxUIWidget *widget)
    {
//        cout << endl; 
//        cout << "Widget to find: " << widget->getName() << endl; 
//        cout << endl; 
        
        //for the map
        map<string, ofxUIWidget*>::iterator it;        
        it=widgets_map.find(widget->getName());
        if(it != widgets_map.end())
        {
//            cout << "FOUND IT IN MAP, DELETING" << endl;
            widgets_map.erase(it);     
        }
        
        //for the widgets with state         
        for(int i = 0; i < widgetsWithState.size(); i++)
        {
            ofxUIWidget *other = widgetsWithState[i]; 
            if(widget->getName() == other->getName())
            {
//                cout << "FOUND IT IN WIDGETS WITH STATE, DELETING" << endl;
                widgetsWithState.erase(widgetsWithState.begin()+i);                
                break; 
            }
        }
        vector<ofxUIWidget *>::iterator wit;
        //for all the widgets 
        for(wit=widgets.begin(); wit != widgets.end(); wit++)
        {
            ofxUIWidget *other = *wit;
//            cout << other->getName() << endl;                     
            if(widget->getName() == other->getName())
            {
//                cout << "FOUND IT\t" << other->getName() << " " << widget->getName() << endl; 
                widgets.erase(wit);                             
                break; 
            }
        }
        
        if(widget->hasLabel())
        {
//            cout << "HAS LABEL" << endl;
            ofxUIWidgetWithLabel *wwl = (ofxUIWidgetWithLabel *) widget; 
            ofxUILabel *label = wwl->getLabelWidget();
            removeWidget(label);
        }        

        delete widget;
    }    

    void addWidget(ofxUIWidget *widget)
	{
//        if(widget->hasLabel())
//        {
//            ofxUIWidgetWithLabel *widgetWithLabel = (ofxUIWidgetWithLabel *) widget; 
//            ofxUILabel *label = widgetWithLabel->getLabelWidget();
//            setLabelFont(label);
//        }
//		else 
        if(widget->getKind() == OFX_UI_WIDGET_LABEL)
		{
			ofxUILabel *label = (ofxUILabel *) widget;
			setLabelFont(label); 
		}
		else if(widget->getKind() == OFX_UI_WIDGET_SLIDER_H || widget->getKind() == OFX_UI_WIDGET_SLIDER_V || widget->getKind() == OFX_UI_WIDGET_BILABELSLIDER || widget->getKind() == OFX_UI_WIDGET_MINIMALSLIDER || widget->getKind() == OFX_UI_WIDGET_CIRCLESLIDER || widget->getKind() == OFX_UI_WIDGET_IMAGESLIDER_H || widget->getKind() == OFX_UI_WIDGET_IMAGESLIDER_V || widget->getKind() == OFX_UI_WIDGET_MULTIIMAGESLIDER_H || widget->getKind() == OFX_UI_WIDGET_MULTIIMAGESLIDER_V)           
		{
			ofxUISlider *slider = (ofxUISlider *) widget;
			ofxUILabel *label = (ofxUILabel *) slider->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 				

            if(widget->getKind() == OFX_UI_WIDGET_BILABELSLIDER)
            {
                ofxUIBiLabelSlider *biSlider = (ofxUIBiLabelSlider *) widget;
                ofxUILabel *rlabel = (ofxUILabel *) biSlider->getRightLabel();
                setLabelFont(rlabel); 			
                pushbackWidget(rlabel); 				                
            }
            
            widgetsWithState.push_back(widget);                         
		}
		else if(widget->getKind() == OFX_UI_WIDGET_2DPAD)		
		{
			ofxUI2DPad *pad = (ofxUI2DPad *) widget;
			ofxUILabel *label = (ofxUILabel *) pad->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 				

            widgetsWithState.push_back(widget);             
		}		
		else if(widget->getKind() == OFX_UI_WIDGET_IMAGE)		
		{
			ofxUIImage *image = (ofxUIImage *) widget;
			ofxUILabel *label = (ofxUILabel *) image->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 				
		}	
		else if(widget->getKind() == OFX_UI_WIDGET_IMAGESAMPLER)		
		{
			ofxUIImage *image = (ofxUIImage *) widget;
			ofxUILabel *label = (ofxUILabel *) image->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 				
            
            widgetsWithState.push_back(widget);                                     
		}	        
		else if(widget->getKind() == OFX_UI_WIDGET_RSLIDER_H || widget->getKind() == OFX_UI_WIDGET_RSLIDER_V)
		{
			ofxUIRangeSlider *rslider = (ofxUIRangeSlider *) widget;
			ofxUILabel *label = (ofxUILabel *) rslider->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 			
            
            widgetsWithState.push_back(widget);                         
		}		
		else if(widget->getKind() == OFX_UI_WIDGET_ROTARYSLIDER)
		{
			ofxUIRotarySlider *rslider = (ofxUIRotarySlider *) widget;
			ofxUILabel *label = (ofxUILabel *) rslider->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 				
            
            widgetsWithState.push_back(widget);                         
		}		
		else if(widget->getKind() == OFX_UI_WIDGET_BUTTON || widget->getKind() ==  OFX_UI_WIDGET_LABELBUTTON || widget->getKind() == OFX_UI_WIDGET_LABELTOGGLE || widget->getKind() == OFX_UI_WIDGET_MULTIIMAGEBUTTON || widget->getKind() == OFX_UI_WIDGET_MULTIIMAGETOGGLE || widget->getKind() == OFX_UI_WIDGET_CUSTOMIMAGEBUTTON)
		{
			ofxUIButton *button = (ofxUIButton *) widget;
			ofxUILabel *label = (ofxUILabel *) button->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 		
            if(widget->getKind() != OFX_UI_WIDGET_BUTTON && widget->getKind() != OFX_UI_WIDGET_LABELBUTTON && widget->getKind() != OFX_UI_WIDGET_MULTIIMAGEBUTTON && widget->getKind() != OFX_UI_WIDGET_CUSTOMIMAGEBUTTON)
            {
                widgetsWithState.push_back(widget);                         
            }
		}
        else if(widget->getKind() == OFX_UI_WIDGET_DROPDOWNLIST)            
        { 
			ofxUIDropDownList *list = (ofxUIDropDownList *) widget;
			ofxUILabel *label = (ofxUILabel *) list->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 		
            
            vector<ofxUILabelToggle *> toggles = list->getToggles(); 
			for(int i = 0; i < toggles.size(); i++)
			{
				ofxUILabelToggle *t = toggles[i]; 
				ofxUILabel *l2 = (ofxUILabel *) t->getLabel();
				setLabelFont(l2); 	
                pushbackWidget(l2); 					
                pushbackWidget(t); 

                widgetsWithState.push_back(t);             
			}            
        }
		else if(widget->getKind() == OFX_UI_WIDGET_TEXTINPUT)
		{
			ofxUITextInput *textinput = (ofxUITextInput *) widget;
			ofxUILabel *label = (ofxUILabel *) textinput->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 	
            
            widgetsWithState.push_back(widget);             
		}		
		else if(widget->getKind() == OFX_UI_WIDGET_NUMBERDIALER)
		{
			ofxUINumberDialer *numberDialer = (ofxUINumberDialer *) widget;
			ofxUILabel *label = (ofxUILabel *) numberDialer->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 			
            
            widgetsWithState.push_back(widget);                         
		}		        
		else if(widget->getKind() == OFX_UI_WIDGET_TOGGLE)
		{
			ofxUIToggle *toggle = (ofxUIToggle *) widget;
			ofxUILabel *label = (ofxUILabel *) toggle->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 			
            
            widgetsWithState.push_back(widget);                         
		}
		else if(widget->getKind() == OFX_UI_WIDGET_RADIO)
		{
			ofxUIRadio *radio = (ofxUIRadio *) widget;
			ofxUILabel *label = (ofxUILabel *) radio->getLabel();			
			setLabelFont(label); 
			pushbackWidget(label); 				
			
			vector<ofxUIToggle *> toggles = radio->getToggles(); 
			
			for(int i = 0; i < toggles.size(); i++)
			{
				ofxUIToggle *t = toggles[i]; 
				ofxUILabel *l2 = (ofxUILabel *) t->getLabel();
				setLabelFont(l2); 	
				pushbackWidget(t); 
				pushbackWidget(l2);
                
                widgetsWithState.push_back(t);                             
			}
		}
        else if(widget->getKind() == OFX_UI_WIDGET_TOGGLEMATRIX)
		{
			ofxUIToggleMatrix *matrix = (ofxUIToggleMatrix *) widget;
			ofxUILabel *label = (ofxUILabel *) matrix->getLabel();			
			setLabelFont(label); 
			pushbackWidget(label); 				
			
			vector<ofxUIToggle *> toggles = matrix->getToggles(); 
			
			for(int i = 0; i < toggles.size(); i++)
			{
				ofxUIToggle *t = toggles[i]; 
				ofxUILabel *l2 = (ofxUILabel *) t->getLabel();
				setLabelFont(l2); 	
				pushbackWidget(t); 
				pushbackWidget(l2); 			
                
                widgetsWithState.push_back(t);                             
			}
		}
		else if(widget->getKind() == OFX_UI_WIDGET_FPS)
		{
			ofxUILabel *fps = (ofxUILabel *) widget;
			setLabelFont(fps); 
		}
        else if(widget->getKind() == OFX_UI_WIDGET_IMAGETOGGLE)
        {
            widgetsWithState.push_back(widget);              
        }
	
		widget->setParent(this); 
		widget->setRectParent(this->rect); 		
		pushbackWidget(widget); 	
	}
    
	ofxUIWidget* addWidgetDown(ofxUIWidget *widget, ofxWidgetAlignment align = OFX_UI_ALIGN_LEFT, bool reAdd = false)
	{
        if(!reAdd) addWidget(widget); 
        ofxUIRectangle *widgetRect = widget->getRect();         
		if(lastAdded != NULL)
		{
			ofxUIRectangle *lastPaddedRect = lastAdded->getPaddingRect(); 
			widgetRect->y = lastPaddedRect->getY()+lastPaddedRect->getHeight()-rect->getY()+widgetSpacing; 
		}
		else 
		{
			widgetRect->y = widgetSpacing; 
		}
        switch(align)
        {
            case OFX_UI_ALIGN_LEFT: 
                widgetRect->x = widgetSpacing;             
                break;                    
            case OFX_UI_ALIGN_FREE: 
                
                break; 
            case OFX_UI_ALIGN_RIGHT: 
                widgetRect->x = rect->getWidth()-widgetRect->getWidth()-widgetSpacing; 
                break;                     
        }                           
		lastAdded = widget; 
		return widget;
	}
    
	ofxUIWidget* addWidgetUp(ofxUIWidget *widget, ofxWidgetAlignment align = OFX_UI_ALIGN_LEFT, bool reAdd = false)
	{
        if(!reAdd) addWidget(widget); 
        ofxUIRectangle *widgetRect = widget->getRect();                 
		if(lastAdded != NULL)
		{
			ofxUIRectangle *lastPaddedRect = lastAdded->getPaddingRect(); 
            ofxUIRectangle *widgetPaddedRect = widget->getPaddingRect();                                     
			widgetRect->y = lastPaddedRect->getY()-widgetPaddedRect->getHeight()-rect->getY();                                     
		}
		else 
		{
			widgetRect->y = widgetSpacing;             
		}
        switch(align)
        {
            case OFX_UI_ALIGN_LEFT: 
                widgetRect->x = widgetSpacing;             
                break;                    
            case OFX_UI_ALIGN_FREE: 
                
                break; 
            case OFX_UI_ALIGN_RIGHT: 
                widgetRect->x = rect->getWidth()-widgetRect->getWidth()-widgetSpacing; 
                break;                     
        }          
		lastAdded = widget; 
		return widget;
	}    
    
	ofxUIWidget* addWidgetRight(ofxUIWidget *widget, ofxWidgetAlignment align = OFX_UI_ALIGN_FREE, bool reAdd = false)
	{
        if(!reAdd) addWidget(widget); 
        ofxUIRectangle *widgetRect = widget->getRect();                         
		if(lastAdded != NULL)
		{
			ofxUIRectangle *lastRect = lastAdded->getRect(); 
			ofxUIRectangle *lastPaddedRect = lastAdded->getPaddingRect();                         
			
            widgetRect->x = lastPaddedRect->getX()+lastPaddedRect->getWidth()-rect->getX()+widgetSpacing; 
			widgetRect->y = lastRect->getY()-rect->getY(); 
		}
		else 
		{
			widgetRect->x = widgetSpacing; 
            widgetRect->y = widgetSpacing;                         
		}
        switch(align)
        {
            case OFX_UI_ALIGN_LEFT: 
                widgetRect->x = widgetSpacing;             
                break;                    
            case OFX_UI_ALIGN_FREE: 
                
                break; 
            case OFX_UI_ALIGN_RIGHT: 
                widgetRect->x = rect->getWidth()-widgetRect->getWidth()-widgetSpacing; 
                break;                     
            case OFX_UI_ALIGN_TOP: 
                widgetRect->y = widgetSpacing;                         
                break;                     
            case OFX_UI_ALIGN_BOTTOM: 
                widgetRect->y = rect->getHeight()-widgetRect->getHeight()-widgetSpacing; 
                break;                                     
        }                  
        lastAdded = widget; 
        return widget; 	
	}
    
    ofxUIWidget* addWidgetLeft(ofxUIWidget *widget, ofxWidgetAlignment align = OFX_UI_ALIGN_FREE, bool reAdd = false)
	{
        if(!reAdd) addWidget(widget);     
        ofxUIRectangle *widgetRect = widget->getRect(); 
		if(lastAdded != NULL)
		{
			ofxUIRectangle *lastRect = lastAdded->getRect(); 
			ofxUIRectangle *lastPaddedRect = lastAdded->getPaddingRect();                         
            ofxUIRectangle *widgetPaddedRect = widget->getPaddingRect();                         
			
            widgetRect->x = lastPaddedRect->getX()-widgetPaddedRect->getWidth()-rect->getX(); 
			widgetRect->y = lastRect->getY()-rect->getY(); 
		}
		else 
		{
			widgetRect->x = widgetSpacing; 
            widgetRect->y = widgetSpacing;                         
		}
        switch(align)
        {
            case OFX_UI_ALIGN_LEFT: 
                widgetRect->x = widgetSpacing;             
                break;                    
            case OFX_UI_ALIGN_FREE: 
                
                break; 
            case OFX_UI_ALIGN_RIGHT: 
                widgetRect->x = rect->getWidth()-widgetRect->getWidth()-widgetSpacing; 
                break;        
            case OFX_UI_ALIGN_TOP: 
                widgetRect->y = widgetSpacing;                         
                break;                     
            case OFX_UI_ALIGN_BOTTOM: 
                widgetRect->y = rect->getHeight()-widgetRect->getHeight()-widgetSpacing; 
                break;                                                     
        }                          
        lastAdded = widget;  	
        return widget;
	}    
    
    ofxUIWidget* addWidgetSouthOf(ofxUIWidget *widget, string referenceName, bool reAdd = false)
	{
        if(!reAdd) addWidget(widget); 
        ofxUIWidget *referenceWidget = getWidget(referenceName);
		if(referenceWidget != NULL)
		{
			ofxUIRectangle *referencePaddedRect = referenceWidget->getPaddingRect(); 
			ofxUIRectangle *referenceRect = referenceWidget->getRect();             
			ofxUIRectangle *widgetRect = widget->getRect(); 
            
			widgetRect->y = referencePaddedRect->getY()+referencePaddedRect->getHeight()-rect->getY()+widgetSpacing; 
            widgetRect->x = referenceRect->getX()-rect->getX();   
		}
		else 
		{
			ofxUIRectangle *widgetRect = widget->getRect(); 
			widgetRect->y = widgetSpacing; 
		}
        lastAdded = widget;  		
        return widget;
    }    
    
    ofxUIWidget* addWidgetNorthOf(ofxUIWidget *widget, string referenceName, bool reAdd = false)
	{
        if(!reAdd) addWidget(widget); 
        ofxUIWidget *referenceWidget = getWidget(referenceName);
		if(referenceWidget != NULL)
		{
			ofxUIRectangle *referencePaddedRect = referenceWidget->getPaddingRect(); 
			ofxUIRectangle *referenceRect = referenceWidget->getRect();             
			ofxUIRectangle *widgetRect = widget->getRect(); 
            ofxUIRectangle *widgetPaddedRect = widget->getPaddingRect();             
            
			widgetRect->y = referencePaddedRect->getY()-widgetPaddedRect->getHeight()-rect->getY();             
            widgetRect->x = referenceRect->getX()-rect->getX();   
		}
		else 
		{
			ofxUIRectangle *widgetRect = widget->getRect(); 
			widgetRect->y = widgetSpacing; 
		}
        lastAdded = widget;  	        
        return widget;
    }      
    
    ofxUIWidget* addWidgetWestOf(ofxUIWidget *widget, string referenceName, bool reAdd = false)
	{
        if(!reAdd) addWidget(widget);      
        ofxUIWidget *referenceWidget = getWidget(referenceName);
		if(referenceWidget != NULL)
		{
			ofxUIRectangle *referencePaddedRect = referenceWidget->getPaddingRect(); 
			ofxUIRectangle *referenceRect = referenceWidget->getRect();             			
            ofxUIRectangle *widgetRect = widget->getRect(); 
            ofxUIRectangle *widgetPaddedRect = widget->getPaddingRect();             
            
            widgetRect->y = referenceRect->getY()-rect->getY();                         
            widgetRect->x = referencePaddedRect->getX()-rect->getX()-widgetPaddedRect->getWidth();   
		}
		else 
		{			
            ofxUIRectangle *currentRect = widget->getRect(); 			
            currentRect->y = widgetSpacing; 
		}
        lastAdded = widget;  	
        return widget;
    }        
    
    ofxUIWidget* addWidgetEastOf(ofxUIWidget *widget, string referenceName, bool reAdd = false)
	{
        if(!reAdd) addWidget(widget);     
        ofxUIWidget *referenceWidget = getWidget(referenceName);
		if(referenceWidget != NULL)
		{
			ofxUIRectangle *referencePaddedRect = referenceWidget->getPaddingRect(); 
			ofxUIRectangle *referenceRect = referenceWidget->getRect();             			
            ofxUIRectangle *widgetRect = widget->getRect(); 	            
            widgetRect->y = referenceRect->getY()-rect->getY();                         
            widgetRect->x = referencePaddedRect->getX()-rect->getX()+referencePaddedRect->getWidth()+widgetSpacing;   
		}
		else 
		{			
            ofxUIRectangle *currentRect = widget->getRect(); 			
            currentRect->y = widgetSpacing; 
		}
        lastAdded = widget;  	
        return widget;
    }         
    
    void resetPlacer()
    {
        lastAdded = NULL; 
    }
    
    void setPlacer(ofxUIWidget *referenceWidget)
    {
        lastAdded = referenceWidget; 
    }
    
	void setLabelFont(ofxUILabel *label)
	{
		switch(label->getSize())
		{
			case OFX_UI_FONT_LARGE:
				label->setFont(font_large); 					
				break; 
			case OFX_UI_FONT_MEDIUM:
				label->setFont(font_medium); 					
				break; 
			case OFX_UI_FONT_SMALL:
				label->setFont(font_small); 					
				break; 					
		}		
	}
	
	void triggerEvent(ofxUIWidget *child)
	{        
        checkForKeyFocus(child); 
		GUIevent->widget = child; 		
		ofNotifyEvent(newGUIEvent,*GUIevent,this);		
	}
	    
	void setWidgetColor(int _target, ofColor _color)
	{
		switch (_target) 
		{
			case OFX_UI_WIDGET_COLOR_BACK:
				for(int i = 0; i < widgets.size(); i++)
				{
					widgets[i]->setColorBack(_color); 
				}				
				break;

			case OFX_UI_WIDGET_COLOR_OUTLINE:
				for(int i = 0; i < widgets.size(); i++)
				{
					widgets[i]->setColorOutline(_color); 
				}				
				break;
			
			case OFX_UI_WIDGET_COLOR_OUTLINE_HIGHLIGHT:
				for(int i = 0; i < widgets.size(); i++)
				{
					widgets[i]->setColorOutlineHighlight(_color); 
				}				
				break;
			
			case OFX_UI_WIDGET_COLOR_FILL:
				for(int i = 0; i < widgets.size(); i++)
				{
					widgets[i]->setColorFill(_color); 
				}				
				break;
			
			case OFX_UI_WIDGET_COLOR_FILL_HIGHLIGHT:
				for(int i = 0; i < widgets.size(); i++)
				{
					widgets[i]->setColorFillHighlight(_color); 
				}					
				break;
                
			case OFX_UI_WIDGET_COLOR_PADDED:
				for(int i = 0; i < widgets.size(); i++)
				{
					widgets[i]->setColorPadded(_color); 
				}					
				break;
                
			case OFX_UI_WIDGET_COLOR_PADDED_OUTLINE:
				for(int i = 0; i < widgets.size(); i++)
				{
					widgets[i]->setColorPaddedOutline(_color); 
				}					
				break;                
				
			default:
				break;
		}
	}
    
    ofxUIWidget *getWidget(string _name)
	{
		return widgets_map[_name]; 
	}
	
    void removeWidget(string _name)    
    {
        //To Implement
    }
    
	void setDrawPadding(bool _draw_padded_rect)
	{
		draw_padded_rect = _draw_padded_rect; 
	}

    void setDrawWidgetPadding(bool _draw_padded_rect)
    {
		for(int i = 0; i < widgets.size(); i++)
		{
			widgets[i]->setDrawPadding(_draw_padded_rect); 
		}		        
    }

	void setDrawPaddingOutline(bool _draw_padded_rect_outline)
	{
		draw_padded_rect_outline = _draw_padded_rect_outline; 
	}

    void setDrawWidgetPaddingOutline(bool _draw_padded_rect_outline)
	{
		for(int i = 0; i < widgets.size(); i++)
		{
			widgets[i]->setDrawPaddingOutline(_draw_padded_rect_outline); 
		}		
	}

    
    vector<ofxUIWidget*> getWidgets()
    {
        return widgets;
    }
    
    vector<ofxUIWidget*> getWidgetsOfType(ofxWidgetType type)
    {
        vector<ofxUIWidget*> widgetToReturn; 
        for(int i = 0; i < widgets.size(); i++)
		{
            if(widgets[i]->getKind() == type)
            {
                widgetToReturn.push_back(widgets[i]);
            }
		}	 
        return widgetToReturn;                                         
    }
	
	ofEvent<ofxUIEventArgs> newGUIEvent;
	
protected:    
    
    void pushbackWidget(ofxUIWidget *widget)
    {
        widget->setID(uniqueIDs); 
        uniqueIDs++;
        widgets.push_back(widget);    
		widgets_map[widget->getName()] = widget;                             
    }
    
	ofTrueTypeFont *font_large; 	
	ofTrueTypeFont *font_medium; 		
	ofTrueTypeFont *font_small;
 	
	ofxUIEventArgs *GUIevent; 
    int state; 
    bool hasSharedResources;
    
    map<string, ofxUIWidget*> widgets_map;     
	vector<ofxUIWidget*> widgets; 
	vector<ofxUIWidget*> widgetsWithState;     
	ofxUIWidget *lastAdded; 
	ofxUIWidget *activeFocusedWidget; 
	bool enable_highlight_outline; 
	bool enable_highlight_fill; 	
	bool enabled; 
    int uniqueIDs; 
    bool hasKeyBoard; 
    
    float widgetSpacing; 
    
    string fontName;

    //Easy Font setting contributed from Colin Duffy (colin@tomorrowevening.com)    
    bool updateFont(ofxWidgetFontType _kind, string filename, int fontsize, bool _bAntiAliased=true, bool _bFullCharacterSet=false, bool makeContours=false, float simplifyAmt=0.3, int dpi=0) {
        bool success = false;
        switch(_kind)
        {
            case OFX_UI_FONT_LARGE:
                if(font_large != NULL)
                {
                    delete font_large;
                }
                font_large = new ofTrueTypeFont();
                success = font_large->loadFont(filename,fontsize,_bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt,dpi);
                break;
                
            case OFX_UI_FONT_MEDIUM:
                if(font_medium != NULL)
                {
                    delete font_medium;
                }
                font_medium = new ofTrueTypeFont();
                success = font_medium->loadFont(filename,fontsize,_bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt,dpi);
                break;
                
            case OFX_UI_FONT_SMALL:
                if(font_small != NULL)
                {
                    delete font_small;
                }
                font_small = new ofTrueTypeFont();
                success = font_small->loadFont(filename,fontsize,_bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt,dpi);
                break;
        }
        return success;
    }
    
    void checkForKeyFocus(ofxUIWidget *child)
    {
        if(child->getKind() == OFX_UI_WIDGET_TEXTINPUT)
        {
            ofxUITextInput *textinput = (ofxUITextInput *) child;         
            switch(textinput->getTriggerType())
            {
                case OFX_UI_TEXTINPUT_ON_FOCUS:
                {
                    hasKeyBoard = true;         
                }
                    break; 
                    
                case OFX_UI_TEXTINPUT_ON_ENTER:
                {
                    hasKeyBoard = true; 
                }        
                    break; 
                    
                case OFX_UI_TEXTINPUT_ON_UNFOCUS:
                {
                    hasKeyBoard = false; 
                }        
                    break; 
                    
                default:
                {
                    hasKeyBoard = false; 
                }
                    break;                     
            }
        }        
    }
    
};

#endif

