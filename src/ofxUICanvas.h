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
        disable();
		delete GUIevent; 
        if(!hasSharedResources)
        {
            delete font_large; 
            delete font_medium;
            delete font_small;		
        }
		for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
		{
			ofxUIWidget *w = (*it);
			delete w;
		}
		widgets.clear();             
    }

    ofxUICanvas(ofRectangle r) : ofxUIWidget()
    {
        rect = new ofxUIRectangle(r);
        init(r.width,r.height);
    }
    
    ofxUICanvas(float x, float y, float w, float h) : ofxUIWidget() 
    {
        rect = new ofxUIRectangle(x,y,w,h);        
        init(w,h);
    }

    ofxUICanvas(float x, float y, float w, float h, ofxUICanvas *sharedResources) : ofxUIWidget() 
    {
        rect = new ofxUIRectangle(x,y,w,h);        
        init(w,h, sharedResources);
    }
    
    ofxUICanvas(float defaultWidthSize = OFX_UI_GLOBAL_CANVAS_WIDTH, float defaultHeightSize = OFX_UI_GLOBAL_CANVAS_WIDTH) : ofxUIWidget()
    {        
        rect = new ofxUIRectangle(0,0,defaultWidthSize,defaultHeightSize);
        init(defaultWidthSize, defaultHeightSize);
        setGlobalCanvasWidth(defaultWidthSize);
    }
    
    ofxUICanvas(ofxUICanvas *sharedResources, float defaultWidthSize = OFX_UI_GLOBAL_CANVAS_WIDTH, float defaultHeightSize = OFX_UI_GLOBAL_CANVAS_WIDTH) : ofxUIWidget()
    {
        rect = new ofxUIRectangle(0,0,defaultWidthSize,defaultHeightSize);
        init(defaultWidthSize, defaultHeightSize, sharedResources);
        setGlobalCanvasWidth(defaultWidthSize);
    }
    
    ofxUICanvas(std::string title) : ofxUIWidget()
    {
        ofEnableSmoothing();
        rect = new ofxUIRectangle(0, 0, 316, ofGetHeight());        
        init(46, ofGetHeight());
        addWidgetDown(new ofxUILabel(title, OFX_UI_FONT_LARGE));
        addWidgetDown(new ofxUISpacer(0, 20));
        addWidgetDown(new ofxUIFPSSlider(300, 20, 0, 1000, ofGetFrameRate(), "FPS"));
    }
    
    void init(int w, int h, ofxUICanvas *sharedResources = NULL)
    {        
        name = string("OFX_UI_WIDGET_CANVAS");
		kind = OFX_UI_WIDGET_CANVAS; 
		
		enable_highlight_outline = false; 
		enable_highlight_fill = false;     
        
        bDrawWidgetPadding = false;
        bDrawWidgetPaddingOutline = false;
        
        autoDraw = true;
        autoUpdate = true;
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding*2.0);
		paddedRect->setParent(rect);
        
        if(sharedResources != NULL)
        {
            hasSharedResources = true;
            font_large = sharedResources->getFontLarge();
            font_medium = sharedResources->getFontMedium();
            font_small = sharedResources->getFontSmall();
        }
        else
        {
            hasSharedResources = false;
            font_large = new ofTrueTypeFont();
            font_medium = new ofTrueTypeFont();
            font_small = new ofTrueTypeFont();            
        
            fontName = string(OFX_UI_FONT_NAME);
            setFont(fontName,true, true, false, 0.0, OFX_UI_FONT_RESOLUTION);
        }
        
		font = font_medium; 
		lastAdded = NULL; 
        uniqueIDs = 0;         
        widgetSpacing = OFX_UI_GLOBAL_WIDGET_SPACING;
        globalCanvasWidth = OFX_UI_GLOBAL_CANVAS_WIDTH;
        globalSliderHeight = OFX_UI_GLOBAL_SLIDER_HEIGHT;
        globalGraphHeight = OFX_UI_GLOBAL_GRAPH_HEIGHT;
        globalButtonDimension = OFX_UI_GLOBAL_BUTTON_DIMENSION;
        globalSpacerHeight = OFX_UI_GLOBAL_SPACING_HEIGHT;
        
        hasKeyBoard = false; 
        
        widgetPosition = OFX_UI_WIDGET_POSITION_DOWN;
        widgetAlign = OFX_UI_ALIGN_LEFT;
        widgetFontSize = OFX_UI_FONT_MEDIUM;
        
		GUIevent = new ofxUIEventArgs(this);
		enabled = false;
		enable();        
    }
    
    void copyCanvasStyle(ofxUICanvas *styler)
    {
        setUIColors(styler->getWidgetColorBack(),
                    styler->getWidgetColorOutline(),
                    styler->getWidgetColorOutlineHighlight(),
                    styler->getWidgetColorFill(),
                    styler->getWidgetColorFillHighlight(),
                    styler->getWidgetColorPadded(),
                    styler->getWidgetColorPaddedOutline());
        
        setColorBack(styler->getColorBack());
        setColorOutline(styler->getColorOutline());
        setColorOutlineHighlight(styler->getColorOutlineHighlight());
        setColorFill(styler->getColorFill());
        setColorFillHighlight(styler->getColorFillHighlight());
        setColorPadded(styler->getColorPadded());
        setColorPaddedOutline(styler->getColorPaddedOutline());            

        setDrawBack(styler->getDrawBack());
        setDrawOutline(styler->getDrawOutline());
        setDrawOutlineHighLight(styler->getDrawOutlineHighLight());
        setDrawFill(styler->getDrawFill());
        setDrawFillHighLight(styler->getDrawFillHighLight());
        setDrawPadding(styler->getDrawPadding());
        setDrawPaddingOutline(styler->getDrawPaddingOutline());
        
        setDrawWidgetPadding(styler->getDrawWidgetPadding());
        setDrawWidgetPaddingOutline(styler->getDrawWidgetPaddingOutline());
    }
    
    void copyCanvasProperties(ofxUICanvas *styler)
    {
        setGlobalCanvasWidth(styler->getRect()->getWidth());
        setGlobalButtonDimension(styler->getGlobalButtonDimension());
        setGlobalSliderHeight(styler->getGlobalSliderHeight());
        setGlobalSpacerHeight(styler->getGlobalSpacerHeight());
        setGlobalGraphHeight(styler->getGlobalGraphHeight());

        setPadding(styler->getPadding());
        setWidgetSpacing(styler->getWidgetSpacing());
        
        setWidgetPosition(styler->getWidgetPosition());
        setWidgetFontSize(styler->getWidgetFontSize());        
    }
    
#ifndef OFX_UI_NO_XML

    virtual void saveSettings(string fileName)
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
    
    virtual void writeSpecificWidgetData(ofxUIWidget *widget, ofxXmlSettings *XML)
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
                triggerEvent(widget); 
            }
            XML->popTag(); 
        }
        hasKeyBoard = false;                
        delete XML; 
    }
    
    virtual void loadSpecificWidgetData(ofxUIWidget *widget, ofxXmlSettings *XML)
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

#endif
	 
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
            visible = true; 
            enableAppDrawCallback();
            enableAppUpdateCallback();
            enableAppExitCallback();
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
            visible = false;
            disableAppDrawCallback();
            disableAppUpdateCallback();
            disableAppExitCallback();     
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
        ofAddListener(ofEvents().update, this, &ofxUICanvas::onUpdate);
        ofAddListener(ofEvents().draw, this, &ofxUICanvas::onDraw);
        ofAddListener(ofEvents().exit, this, &ofxUICanvas::onExit);
    }
	
	//App Callbacks
    void disableAppEventCallbacks()
    {
        ofRemoveListener(ofEvents().update, this, &ofxUICanvas::onUpdate);
        ofRemoveListener(ofEvents().draw, this, &ofxUICanvas::onDraw);
        ofRemoveListener(ofEvents().exit, this, &ofxUICanvas::onExit);
    }
	
    void enableAppDrawCallback()
    {
        ofAddListener(ofEvents().draw, this, &ofxUICanvas::onDraw);
    }
    
    void enableAppUpdateCallback()
    {
        ofAddListener(ofEvents().update, this, &ofxUICanvas::onUpdate);
    }
    
    void enableAppExitCallback()
    {
        ofAddListener(ofEvents().exit, this, &ofxUICanvas::onExit);
    }

    void disableAppDrawCallback()
    {
        ofRemoveListener(ofEvents().draw, this, &ofxUICanvas::onDraw);
    }
    
    void disableAppUpdateCallback()
    {
        ofRemoveListener(ofEvents().update, this, &ofxUICanvas::onUpdate);
    }
    
    void disableAppExitCallback()
    {
        ofRemoveListener(ofEvents().exit, this, &ofxUICanvas::onExit);
    }

#ifdef TARGET_OPENGLES
	
	//Touch Callbacks
    void enableTouchEventCallbacks()
    {

        ofAddListener(ofEvents().touchUp, this, &ofxUICanvas::onTouchUp);
        ofAddListener(ofEvents().touchDown, this, &ofxUICanvas::onTouchDown);
        ofAddListener(ofEvents().touchMoved, this, &ofxUICanvas::onTouchMoved);
        ofAddListener(ofEvents().touchCancelled, this, &ofxUICanvas::onTouchCancelled);
        ofAddListener(ofEvents().touchDoubleTap, this, &ofxUICanvas::onTouchDoubleTap);
    }	

	void disableTouchEventCallbacks()
    {
        ofRemoveListener(ofEvents().touchUp, this, &ofxUICanvas::onTouchUp);
        ofRemoveListener(ofEvents().touchDown, this, &ofxUICanvas::onTouchDown);
        ofRemoveListener(ofEvents().touchMoved, this, &ofxUICanvas::onTouchMoved);
        ofRemoveListener(ofEvents().touchCancelled, this, &ofxUICanvas::onTouchCancelled);
        ofRemoveListener(ofEvents().touchDoubleTap, this, &ofxUICanvas::onTouchDoubleTap);
    }	
	
#else
	
	//Mouse Callbacks
    void enableMouseEventCallbacks()
    {
        ofAddListener(ofEvents().mouseReleased, this, &ofxUICanvas::onMouseReleased);
        ofAddListener(ofEvents().mousePressed, this, &ofxUICanvas::onMousePressed);
        ofAddListener(ofEvents().mouseMoved, this, &ofxUICanvas::onMouseMoved);
        ofAddListener(ofEvents().mouseDragged, this, &ofxUICanvas::onMouseDragged);
    }

	//Mouse Callbacks
    void disableMouseEventCallbacks()
    {
        ofRemoveListener(ofEvents().mouseReleased, this, &ofxUICanvas::onMouseReleased);
        ofRemoveListener(ofEvents().mousePressed, this, &ofxUICanvas::onMousePressed);
        ofRemoveListener(ofEvents().mouseMoved, this, &ofxUICanvas::onMouseMoved);
        ofRemoveListener(ofEvents().mouseDragged, this, &ofxUICanvas::onMouseDragged);
    }

    //Window Resize Callback
    void enableWindowEventCallbacks()
    {
        ofAddListener(ofEvents().windowResized, this, &ofxUICanvas::onWindowResized);        
    }

	//Window Resize Callback
    void disableWindowEventCallbacks()
    {
        ofRemoveListener(ofEvents().windowResized, this, &ofxUICanvas::onWindowResized);        
    }
	
	
#endif	

    //KeyBoard Callbacks
	void enableKeyEventCallbacks()
	{
		ofAddListener(ofEvents().keyPressed, this, &ofxUICanvas::onKeyPressed);
		ofAddListener(ofEvents().keyReleased, this, &ofxUICanvas::onKeyReleased);
	}

	//KeyBoard Callbacks
	void disableKeyEventCallbacks()
	{
		ofRemoveListener(ofEvents().keyPressed, this, &ofxUICanvas::onKeyPressed);
		ofRemoveListener(ofEvents().keyReleased, this, &ofxUICanvas::onKeyReleased);
	}

    void onUpdate(ofEventArgs &data) { if(autoUpdate) update(); }
    void onDraw(ofEventArgs &data) { if(autoDraw) draw(); }
    void onExit(ofEventArgs &data) { exit(); } 

    
    virtual void update()
    {    
		for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
		{
			(*it)->update(); 	
		}		
    }
     
    virtual void draw()
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

        for(vector<ofxUIWidget *>::reverse_iterator it = widgets.rbegin(); it != widgets.rend(); ++it)
        {
            if((*it)->isVisible() && ((*it)->getRect()->rInside(*rect) || (*it)->isModal()))
            {
                (*it)->draw(); 	
            }
		}    
        
        ofPopStyle();
    }
    
    void exit()
    {

    }	
        
#ifdef TARGET_OPENGLES
	
    virtual void onTouchDown(ofTouchEventArgs &data)
    {
		touchDown(data); 
    }
    
    virtual void onTouchMoved(ofTouchEventArgs &data) 
    {
		touchMoved(data); 
    }

    virtual void onTouchUp(ofTouchEventArgs &data) 
    {
		touchUp(data); 
    }
	
    virtual void onTouchDoubleTap(ofTouchEventArgs &data)
    {
		touchDoubleTap(data); 
    }
	
	virtual void onTouchCancelled(ofTouchEventArgs &data)
    {
		touchCancelled(data); 
    }
	
	virtual void touchDown(ofTouchEventArgs& touch) 
	{		
        if(rect->inside(touch.x, touch.y))
        {
			for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
			{
				if((*it)->isVisible())	(*it)->touchDown(touch); 
			}
		}
        else
        {
            for (map<string, ofxUIWidget*>::iterator it=widgetsAreModal.begin() ; it != widgetsAreModal.end(); it++ )
            {
                if((*it).second->isVisible()) (*it).second->touchDown(touch);
            }            
        }
	}
    
	virtual void touchMoved(ofTouchEventArgs& touch) 
	{
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible())	(*it)->touchMoved(touch);
        }
	}
    
	virtual void touchUp(ofTouchEventArgs& touch) 
	{
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible())	(*it)->touchUp(touch); 
        }
	}
    
	virtual void touchDoubleTap(ofTouchEventArgs& touch) 
	{
        if(rect->inside(touch.x, touch.y))
        {
			for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
			{
				if((*it)->isVisible())	(*it)->touchDoubleTap(touch); 
			}
		}
        else
        {
            for (map<string, ofxUIWidget*>::iterator it=widgetsAreModal.begin() ; it != widgetsAreModal.end(); it++ )
            {
                if((*it).second->isVisible()) (*it).second->touchDoubleTap(touch);
            }
        }        
	}
    
	virtual void touchCancelled(ofTouchEventArgs& touch) 
	{		
        if(rect->inside(touch.x, touch.y))
        {
        	for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
			{
				if((*it)->isVisible())	(*it)->touchCancelled(touch); 
			}
		}
        else
        {
            for (map<string, ofxUIWidget*>::iterator it=widgetsAreModal.begin() ; it != widgetsAreModal.end(); it++ )
            {
                if((*it).second->isVisible()) (*it).second->touchCancelled(touch);
            }
        }        
	}
	
#else	
    
    virtual void onMouseReleased(ofMouseEventArgs& data)
    { 
        mouseReleased(data.x, data.y, data.button); 
    }
    
    virtual void onMousePressed(ofMouseEventArgs& data)
    {
        mousePressed(data.x, data.y, data.button); 
    }
    
    virtual void onMouseMoved(ofMouseEventArgs& data) 
    { 
        mouseMoved(data.x, data.y); 
    }
    
    virtual void onMouseDragged(ofMouseEventArgs& data)
    { 
        mouseDragged(data.x, data.y, data.button); 
    }
	
	virtual void mouseMoved(int x, int y ) 
    {
        if(rect->inside(x, y))
        {
			for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
			{                
				if((*it)->isVisible()) (*it)->mouseMoved(x, y); 
			}
		}
        else
        {
            for (map<string, ofxUIWidget*>::iterator it=widgetsAreModal.begin() ; it != widgetsAreModal.end(); it++ )
            {
                if((*it).second->isVisible()) (*it).second->mouseMoved(x, y);
            }
        }    
    }
    
    virtual void mouseDragged(int x, int y, int button)
    {		
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible())	(*it)->mouseDragged(x, y, button); 
        }                
    }
    
    virtual void mousePressed(int x, int y, int button) 
    {
        if(rect->inside(x, y))
        {
			for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
			{
				if((*it)->isVisible()) (*it)->mousePressed(x, y, button); 
			}
		}
        else
        {
            for (map<string, ofxUIWidget*>::iterator it=widgetsAreModal.begin() ; it != widgetsAreModal.end(); it++ )
            {
                if((*it).second->isVisible()) (*it).second->mousePressed(x, y, button);
            }
        }
    }
    
    virtual void mouseReleased(int x, int y, int button) 
    {		        
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible()) (*it)->mouseReleased(x, y, button); 
        }    
    }
	
    void onWindowResized(ofResizeEventArgs& data) 
    { 
		windowResized(data.width, data.height); 
    } 	
    
    virtual void windowResized(int w, int h) 
    {
		for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
		{
			(*it)->windowResized(w, h); 
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
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
		{
			(*it)->keyPressed(key);
		}
    }

    virtual void keyReleased(int key)
    {
		for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
		{
			(*it)->keyReleased(key);
		}
    }
	
    virtual bool isHit(int x, int y)
    {
        if(isEnabled() && rect->inside(x, y))
        {
            return true;
        }
        else
        {
            for (map<string, ofxUIWidget*>::iterator it=widgetsAreModal.begin() ; it != widgetsAreModal.end(); it++ )
            {
                if((*it).second->isVisible() && (*it).second->isHit(x, y))
                {
                    return true;
                }
            }
        }
        return false;         
    }
    
    ofxUIWidget *getWidgetHit(float x, float y)
    {
        if(isEnabled() && rect->inside(x, y))
        {
            for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
            {
                if((*it)->isHit(x, y))
                {
                    return (*it); 
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
    
    virtual void autoSizeToFitWidgets()
    {        
        float maxWidth = 0;
        float maxHeight = 0; 

        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible())
            {
                ofxUIRectangle* wr = (*it)->getRect();
                ofxUIRectangle* wrp = (*it)->getPaddingRect();
                float widgetwidth = wr->getX()+wrp->getWidth() - rect->getX();
                float widgetheight = wr->getY()+wrp->getHeight() - rect->getY();

                float widgetpaddingwidth = wrp->getX()+wrp->getWidth() - rect->getX();
                float widgetpaddingheight = wrp->getY()+wrp->getHeight() - rect->getY();


                if(widgetwidth > maxWidth)
                {
                    maxWidth = widgetwidth;
                }
                else if(widgetpaddingwidth > maxWidth)
                {
                    maxWidth = widgetpaddingwidth; 
                }
                
                if(widgetheight > maxHeight)
                {
                    maxHeight = widgetheight;
                }
                else if(widgetpaddingheight > maxHeight)
                {
                    maxHeight = widgetpaddingheight;
                }
            }
        }
        setDimensions(maxWidth, maxHeight); 
    }
    
    virtual void centerWidgetsOnCanvas(bool centerHorizontally=true, bool centerVertically=true)
    {            
        float xMin = 0; 
        float yMin = 0;
        
        float xMax = 0; 
        float yMax = 0;
        
        float w = 0; 
        float h = 0; 
        
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
//            if((*it)->isVisible())
//            {
                ofxUIRectangle* wr = (*it)->getRect(); 
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
                
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible() && !((*it)->isEmbedded()))
            {
                ofxUIRectangle* wr = (*it)->getRect(); 
                if(centerHorizontally) wr->x += moveDeltaX-padding;             
                if(centerVertically) wr->y += moveDeltaY-padding;                             
            }
        }           
//        addWidget(new ofxUISpacer(xMin+moveDeltaX, yMin+moveDeltaY, w, h));
    }    
    
    virtual void centerWidgetsHorizontallyOnCanvas()
    {
        centerWidgetsOnCanvas(true, false);
    }

    virtual void centerWidgetsVerticallyOnCanvas()
    {
        centerWidgetsOnCanvas(false, true);
    }
    
    virtual void centerWidgets()
    {
        centerWidgetsOnCanvas(true, true);
    }

    virtual void addModalWidget(ofxUIWidget *widget)
    {
        widgetsAreModal[widget->getName()] = widget;
    }

    virtual void removeModalWidget(ofxUIWidget *widget)
    {
        map<string, ofxUIWidget*>::iterator it;
        it=widgetsAreModal.find(widget->getName());
        if(it != widgetsAreModal.end())
        {
            widgetsAreModal.erase(it);
        }
    }
    
    virtual void removeWidgets()
    {
		for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
		{
			ofxUIWidget *w = (*it);
			removeWidget(w);
		}
        widgets.clear(); 
    }
    
    void removeWidget(ofxUIWidget *widget)
    {
//        cout << endl; 
//        cout << "Widget to find: " << widget->getName() << endl; 
//        cout << endl; 
        
        if(widget->isModal())
        {
            map<string, ofxUIWidget*>::iterator it;
            it=widgetsAreModal.find(widget->getName());            

            if(it != widgetsAreModal.end())
            {
                widgetsAreModal.erase(it);
            }
        }
        
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
        
        for(int i = 0; i < widget->getEmbeddedWidgetsSize(); i++)
        {
            removeWidget(widget->getEmbeddedWidget(i));
        }
        widget->clearEmbeddedWidgets();

        delete widget;
    }    

    void addWidget(ofxUIWidget *widget)
	{
        widget->setPadding(padding);
        for(int i = 0; i < widget->getEmbeddedWidgetsSize(); i++)
        {
            ofxUIWidget *child = widget->getEmbeddedWidget(i);
            this->addWidget(child);
            child->setRectParent(widget->getRect());
        }            
        
        if(widget->hasLabel())
        {
            ofxUIWidgetWithLabel *wwl = (ofxUIWidgetWithLabel *) widget;
            ofxUILabel *label = wwl->getLabelWidget();
            setLabelFont(label);
            setWidgetColor(label);
            pushbackWidget(label);
        }
        else if(widget->getKind() == OFX_UI_WIDGET_LABEL)
        {
            ofxUILabel *label = (ofxUILabel *) widget; 
            setLabelFont(label);
            setWidgetColor(label);
        }
            
        if(widget->getKind() == OFX_UI_WIDGET_SLIDER_H || widget->getKind() == OFX_UI_WIDGET_SLIDER_V || widget->getKind() == OFX_UI_WIDGET_BILABELSLIDER || widget->getKind() == OFX_UI_WIDGET_MINIMALSLIDER || widget->getKind() == OFX_UI_WIDGET_CIRCLESLIDER || widget->getKind() == OFX_UI_WIDGET_IMAGESLIDER_H || widget->getKind() == OFX_UI_WIDGET_IMAGESLIDER_V || widget->getKind() == OFX_UI_WIDGET_MULTIIMAGESLIDER_H || widget->getKind() == OFX_UI_WIDGET_MULTIIMAGESLIDER_V)
		{
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
            widgetsWithState.push_back(widget);             
		}		
		else if(widget->getKind() == OFX_UI_WIDGET_IMAGE)		
		{
		}
		else if(widget->getKind() == OFX_UI_WIDGET_IMAGESAMPLER)		
		{
            widgetsWithState.push_back(widget);                                     
		}	        
		else if(widget->getKind() == OFX_UI_WIDGET_RSLIDER_H || widget->getKind() == OFX_UI_WIDGET_RSLIDER_V)
		{
            widgetsWithState.push_back(widget);
		}		
		else if(widget->getKind() == OFX_UI_WIDGET_ROTARYSLIDER)
		{
            widgetsWithState.push_back(widget);
		}		
		else if(widget->getKind() == OFX_UI_WIDGET_BUTTON || widget->getKind() ==  OFX_UI_WIDGET_LABELBUTTON || widget->getKind() == OFX_UI_WIDGET_LABELTOGGLE || widget->getKind() == OFX_UI_WIDGET_MULTIIMAGEBUTTON || widget->getKind() == OFX_UI_WIDGET_MULTIIMAGETOGGLE || widget->getKind() == OFX_UI_WIDGET_CUSTOMIMAGEBUTTON)
		{
            if(widget->getKind() != OFX_UI_WIDGET_BUTTON && widget->getKind() != OFX_UI_WIDGET_LABELBUTTON && widget->getKind() != OFX_UI_WIDGET_MULTIIMAGEBUTTON && widget->getKind() != OFX_UI_WIDGET_CUSTOMIMAGEBUTTON)
            {
                widgetsWithState.push_back(widget);                         
            }
		}
        else if(widget->getKind() == OFX_UI_WIDGET_DROPDOWNLIST)            
        {
			ofxUIDropDownList *list = (ofxUIDropDownList *) widget;            
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
            widgetsWithState.push_back(widget);             
		}		
		else if(widget->getKind() == OFX_UI_WIDGET_NUMBERDIALER)
		{
            widgetsWithState.push_back(widget);                         
		}		        
		else if(widget->getKind() == OFX_UI_WIDGET_TOGGLE)
		{
            widgetsWithState.push_back(widget);
		}
		else if(widget->getKind() == OFX_UI_WIDGET_RADIO)
		{
			ofxUIRadio *radio = (ofxUIRadio *) widget;
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
        else if(widget->getKind() == OFX_UI_WIDGET_IMAGETOGGLE)
        {
            widgetsWithState.push_back(widget);              
        }
        setWidgetDrawingProperties(widget);
        setWidgetColor(widget);
		widget->setParent(this); 
		widget->setRectParent(this->rect); 		
		pushbackWidget(widget);        
    }
	
    ofxUIWidget* addWidgetPosition(ofxUIWidget *widget, 
                                   ofxWidgetPosition position = OFX_UI_WIDGET_POSITION_DOWN,
                                   ofxWidgetAlignment align = OFX_UI_ALIGN_LEFT, 
                                   bool reAdd = false)
    {
        if(!reAdd) addWidget(widget);
        ofxUIRectangle *widgetRect = widget->getRect();         
		if(lastAdded != NULL)
		{
   			ofxUIRectangle *lastPaddedRect = lastAdded->getPaddingRect(); 
			switch(position)
			{
			    case OFX_UI_WIDGET_POSITION_DOWN:
			        widgetRect->y = lastPaddedRect->getY()+lastPaddedRect->getHeight()-rect->getY()+widgetSpacing; 
			        break;
                case OFX_UI_WIDGET_POSITION_UP:
                {
                    ofxUIRectangle *widgetPaddedRect = widget->getPaddingRect();                                     
			        widgetRect->y = lastPaddedRect->getY()-widgetPaddedRect->getHeight()-rect->getY();                                     
                    break;
                }
                case OFX_UI_WIDGET_POSITION_RIGHT:
                {
        			ofxUIRectangle *lastRect = lastAdded->getRect(); 
                    widgetRect->x = lastPaddedRect->getX()+lastPaddedRect->getWidth()-rect->getX()+widgetSpacing;
                    
                    widgetRect->y = lastRect->getY()-rect->getY();
                    break;
                }
                case OFX_UI_WIDGET_POSITION_LEFT:
                    ofxUIRectangle *lastRect = lastAdded->getRect(); 
                    ofxUIRectangle *widgetPaddedRect = widget->getPaddingRect();                         
                    widgetRect->x = lastPaddedRect->getX()-widgetPaddedRect->getWidth()-rect->getX(); 
                    widgetRect->y = lastRect->getY()-rect->getY(); 
                    break;
			}			
		}
		else 
		{
   			widgetRect->y = widgetSpacing;
   			if (position == OFX_UI_WIDGET_POSITION_LEFT ||
                position == OFX_UI_WIDGET_POSITION_RIGHT)
            {
                widgetRect->x = widgetSpacing; 
			}

		}
        switch(align)
        {
            case OFX_UI_ALIGN_LEFT: 
                widgetRect->x = widgetSpacing;             
                break;                    
            case OFX_UI_ALIGN_FREE: 
                
                break;
            case OFX_UI_ALIGN_CENTER:   //Experimental
                
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
        if(widget->getRect()->getHeight() != 0 || widget->getRect()->getWidth() != 0)
        {
            lastAdded = widget;
        }
		return widget;
    }
    
	ofxUIWidget* addWidgetDown(ofxUIWidget *widget, ofxWidgetAlignment align = OFX_UI_ALIGN_LEFT, bool reAdd = false)
	{
        return addWidgetPosition(widget, OFX_UI_WIDGET_POSITION_DOWN, align, reAdd);
	}
    
	ofxUIWidget* addWidgetUp(ofxUIWidget *widget, ofxWidgetAlignment align = OFX_UI_ALIGN_LEFT, bool reAdd = false)
	{
        return addWidgetPosition(widget, OFX_UI_WIDGET_POSITION_UP, align, reAdd);
	}    
    
	ofxUIWidget* addWidgetRight(ofxUIWidget *widget, ofxWidgetAlignment align = OFX_UI_ALIGN_FREE, bool reAdd = false)
	{
        return addWidgetPosition(widget, OFX_UI_WIDGET_POSITION_RIGHT, align, reAdd);
	}
    
    ofxUIWidget* addWidgetLeft(ofxUIWidget *widget, ofxWidgetAlignment align = OFX_UI_ALIGN_FREE, bool reAdd = false)
	{
        return addWidgetPosition(widget, OFX_UI_WIDGET_POSITION_LEFT, align, reAdd);
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
   
    ofxUISpacer* addSpacer(float h = OFX_UI_GLOBAL_SPACING_HEIGHT)
    {
        if(h != globalSpacerHeight)
        {
            h = globalSpacerHeight; 
        }
        ofxUISpacer* widget = new ofxUISpacer(rect->getWidth()-widgetSpacing*2, h);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUISpacer* addSpacer(string name, float h = OFX_UI_GLOBAL_SPACING_HEIGHT)
    {
        if(h != globalSpacerHeight)
        {
            h = globalSpacerHeight;
        }
        ofxUISpacer* widget = new ofxUISpacer(rect->getWidth()-widgetSpacing*2, h, name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUISpacer* addSpacer(float w, float h)
    {
        ofxUISpacer* widget = new ofxUISpacer(w, h);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUISpacer* addSpacer(float w, float h, string name)
    {
        ofxUISpacer* widget = new ofxUISpacer(w, h, name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUILabel *addLabel(string name, int size = OFX_UI_FONT_MEDIUM)
    {
        ofxUILabel* widget = new ofxUILabel(name, size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUILabel *addLabel(string name, string label, int size = OFX_UI_FONT_MEDIUM)
    {
        ofxUILabel* widget = new ofxUILabel(name, label, size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIFPS *addFPS(int size = OFX_UI_FONT_MEDIUM)
    {
        ofxUIFPS* widget = new ofxUIFPS(size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }    
    
    ofxUISlider* addSlider(string _name, float _min, float _max, float _value)
    {
        ofxUISlider* widget = new ofxUISlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUISlider* addSlider(string _name, float _min, float _max, float _value, float w, float h, float x = 0, float y = 0)
    {
        ofxUISlider* widget = new ofxUISlider(_name, _min, _max, _value, w, h, x, y);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUISlider* addSlider(string _name, float _min, float _max, float *_value)
    {
        ofxUISlider* widget = new ofxUISlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUISlider* addSlider(string _name, float _min, float _max, float *_value, float w, float h, float x = 0, float y = 0)
    {
        ofxUISlider* widget = new ofxUISlider(_name, _min, _max, _value, w, h, x, y);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIRotarySlider* addRotarySlider(string _name, float _min, float _max, float _value, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIRotarySlider* widget = new ofxUIRotarySlider(rect->getWidth()-widgetSpacing*2, _min, _max, _value, _name, _size); 
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIRotarySlider* addRotarySlider(string _name, float _min, float _max, float _value, float w, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIRotarySlider* widget = new ofxUIRotarySlider(x, y, rect->getWidth()-widgetSpacing*2, _min, _max, _value, _name, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIRotarySlider* addRotarySlider(string _name, float _min, float _max, float *_value, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIRotarySlider* widget = new ofxUIRotarySlider(rect->getWidth()-widgetSpacing*2, _min, _max, _value, _name, _size); 
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIRotarySlider* addRotarySlider(string _name, float _min, float _max, float *_value, float w, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIRotarySlider* widget = new ofxUIRotarySlider(x, y, w, _min, _max, _value, _name, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    //
    
    ofxUIImageSlider* addImageSlider(string _name, string _pathURL, float _min, float _max, float _value)
    {
        ofxUIImageSlider* widget = new ofxUIImageSlider(rect->getWidth()-widgetSpacing*2, globalSliderHeight, _min, _max, _value, _pathURL, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIImageSlider* addImageSlider(string _name, string _pathURL, float _min, float _max, float _value, float w, float h, float x = 0, float y = 0)
    {
        ofxUIImageSlider* widget = new ofxUIImageSlider(x, y, w, h, _min, _max, _value, _pathURL, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIImageSlider* addImageSlider(string _name, string _pathURL, float _min, float _max, float *_value)
    {
        ofxUIImageSlider* widget = new ofxUIImageSlider(rect->getWidth()-widgetSpacing*2, globalSliderHeight, _min, _max, _value, _pathURL, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIImageSlider* addImageSlider(string _name, string _pathURL, float _min, float _max, float *_value, float w, float h, float x = 0, float y = 0)
    {
        ofxUIImageSlider* widget = new ofxUIImageSlider(x, y, w, h, _min, _max, _value, _pathURL, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUINumberDialer *addNumberDialer(string _name, float _min, float _max, float _value, int _precision)
    {
        ofxUINumberDialer* widget = new ofxUINumberDialer(_min, _max, _value, _precision, _name, widgetFontSize);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;        
    }
    
    ofxUINumberDialer *addNumberDialer(string _name, float _min, float _max, float *_value, int _precision)
    {
        ofxUINumberDialer* widget = new ofxUINumberDialer(_min, _max, _value, _precision, _name, widgetFontSize);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIMinimalSlider* addMinimalSlider(string _name, float _min, float _max, float _value, int size = OFX_UI_FONT_SMALL)
    {
        ofxUIMinimalSlider* widget = new ofxUIMinimalSlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0, size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIMinimalSlider* addMinimalSlider(string _name, float _min, float _max, float _value, float w, float h, float x = 0, float y = 0, int size = OFX_UI_FONT_SMALL)
    {
        ofxUIMinimalSlider* widget = new ofxUIMinimalSlider(_name, _min, _max, _value, w, h, x, y, size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIMinimalSlider* addMinimalSlider(string _name, float _min, float _max, float *_value, int size = OFX_UI_FONT_SMALL)
    {
        ofxUIMinimalSlider* widget = new ofxUIMinimalSlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0, size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIMinimalSlider* addMinimalSlider(string _name, float _min, float _max, float *_value, float w, float h, float x = 0, float y = 0, int size = OFX_UI_FONT_SMALL)
    {
        ofxUIMinimalSlider* widget = new ofxUIMinimalSlider(_name, _min, _max, _value, w, h, x, y, size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIRangeSlider* addRangeSlider(string _name, float _min, float _max, float _valuelow, float _valuehigh)
    {
        ofxUIRangeSlider* widget = new ofxUIRangeSlider(_name, _min, _max, _valuelow, _valuehigh, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIRangeSlider* addRangeSlider(string _name, float _min, float _max, float _valuelow, float _valuehigh,
                                     float w, float h, float x = 0, float y = 0)
    {
        ofxUIRangeSlider* widget = new ofxUIRangeSlider(_name, _min, _max, _valuelow, _valuehigh, w, h, x, y);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIRangeSlider* addRangeSlider(string _name, float _min, float _max, float *_valuelow, float *_valuehigh)
    {
        ofxUIRangeSlider* widget = new ofxUIRangeSlider(_name, _min, _max, _valuelow, _valuehigh, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }    
    
    ofxUIRangeSlider* addRangeSlider(string _name, float _min, float _max, float *_valuelow, float *_valuehigh,
                                     float w, float h, float x = 0, float y = 0)
    {
        ofxUIRangeSlider* widget = new ofxUIRangeSlider(_name, _min, _max, _valuelow, _valuehigh, w, h, x, y);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIFPSSlider* addFPSSlider(string _name, float _max = 400)
    {
        ofxUIFPSSlider* widget = new ofxUIFPSSlider(_name, rect->getWidth()-widgetSpacing*2, globalSliderHeight, _max, 0, 0);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIFPSSlider* addFPSSlider(string _name, float w, float h, float _max = 400, float x = 0, float y = 0)
    {
        ofxUIFPSSlider* widget = new ofxUIFPSSlider(_name, w, h, _max, x, y);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIRadio* addRadio(string _name, vector<string> names, int _orientation = OFX_UI_ORIENTATION_VERTICAL, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIRadio* widget = new ofxUIRadio(_name, names, _orientation, globalButtonDimension, globalButtonDimension, 0, 0, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIRadio* addRadio(string _name, vector<string> names, int _orientation, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIRadio* widget = new ofxUIRadio(_name, names, _orientation, w, h, x, y, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIButton* addButton(string _name, bool _value)
    {
        ofxUIButton* widget = new ofxUIButton(_name, _value, globalButtonDimension, globalButtonDimension, 0, 0, widgetFontSize);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIButton* addButton(string _name, bool _value, float w, float h, float x = 0, float y = 0)
    {
        ofxUIButton* widget = new ofxUIButton(_name, _value, w, h, x, y, widgetFontSize);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIButton* addButton(string _name, bool *_value)
    {
        ofxUIButton* widget = new ofxUIButton(_name, _value, globalButtonDimension, globalButtonDimension, 0, 0, widgetFontSize);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIButton* addButton(string _name, bool *_value, float w, float h, float x = 0, float y = 0)
    {
        ofxUIButton* widget = new ofxUIButton(_name, _value, w, h, x, y, widgetFontSize);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIToggle* addToggle(string _name, bool _value)
    {
        ofxUIToggle* widget = new ofxUIToggle(_name, _value, globalButtonDimension, globalButtonDimension, 0, 0, widgetFontSize);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIToggle* addToggle(string _name, bool _value, float w, float h, float x = 0, float y = 0)
    {
        ofxUIToggle* widget = new ofxUIToggle(_name, _value, w, h, x, y, widgetFontSize);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIToggle* addToggle(string _name, bool *_value)
    {
        ofxUIToggle* widget = new ofxUIToggle(_name, _value, globalButtonDimension, globalButtonDimension, 0, 0, widgetFontSize);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIToggle* addToggle(string _name, bool *_value, float w, float h, float x = 0, float y = 0)
    {
        ofxUIToggle* widget = new ofxUIToggle(_name, _value, w, h, x, y, widgetFontSize);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIToggleMatrix* addToggleMatrix(string _name, int _rows, int _cols)
    {
        float dim = globalButtonDimension;        
        float width = rect->getWidth()-widgetSpacing*2; 
        if(_cols*dim+_cols*padding > width)
        {
            dim = (width-(_cols-1)*padding)/_cols;
        }
        ofxUIToggleMatrix* widget = new ofxUIToggleMatrix(dim, dim, _rows, _cols, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIToggleMatrix* addToggleMatrix(string _name, int _rows, int _cols, float w, float h)
    {
        ofxUIToggleMatrix* widget = new ofxUIToggleMatrix(w, h, _rows, _cols, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUI2DPad* add2DPad(string _name, ofPoint _rangeX, ofPoint _rangeY, ofPoint _value)
    {
        float dim = rect->getWidth()-widgetSpacing*2; 
        ofxUI2DPad* widget = new ofxUI2DPad(_name, _rangeX, _rangeY, _value, dim, dim, 0, 0);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    
    ofxUI2DPad* add2DPad(string _name, ofPoint _rangeX, ofPoint _rangeY, ofPoint _value, float w, float h, float x = 0, float y = 0)
    {
        ofxUI2DPad* widget = new ofxUI2DPad(_name, _rangeX, _rangeY, _value, w, h, x, y);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUI2DPad* add2DPad(string _name, ofPoint _rangeX, ofPoint _rangeY, ofPoint *_value)
    {
        float dim = rect->getWidth()-widgetSpacing*2; 
        ofxUI2DPad* widget = new ofxUI2DPad(_name, _rangeX, _rangeY, _value, dim, dim, 0, 0);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUI2DPad* add2DPad(string _name, ofPoint _rangeX, ofPoint _rangeY, ofPoint *_value, float w, float h, float x = 0, float y = 0)
    {
        ofxUI2DPad* widget = new ofxUI2DPad(_name, _rangeX, _rangeY, _value, w, h, x, y);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUITextInput* addTextInput(string _name, string _textstring, int _size = OFX_UI_FONT_MEDIUM)
    {
        ofxUITextInput* widget = new ofxUITextInput(_name, _textstring, rect->getWidth()-widgetSpacing*2, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUITextInput* addTextInput(string _name, string _textstring, float w, float h = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_MEDIUM)
    {
        ofxUITextInput* widget = new ofxUITextInput(_name, _textstring, w, h, x, y, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUILabelToggle* addLabelToggle(string _name, bool _value, bool _justifyLeft = false)
    {
        ofxUILabelToggle* widget = new ofxUILabelToggle(_name, _value, rect->getWidth()-widgetSpacing*2, globalButtonDimension, 0, 0, widgetFontSize, _justifyLeft);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUILabelToggle* addLabelToggle(string _name, bool _value, float w, float h = 0, float x = 0, float y = 0, bool _justifyLeft = false)
    {
        if(h == 0)
        {
            h = globalButtonDimension;
        }        
        ofxUILabelToggle* widget = new ofxUILabelToggle(_name, _value, w, h, x, y, widgetFontSize, _justifyLeft);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUILabelToggle* addLabelToggle(string _name, bool *_value, bool _justifyLeft = false)
    {
        ofxUILabelToggle* widget = new ofxUILabelToggle(_name, _value, rect->getWidth()-widgetSpacing*2, globalButtonDimension, 0, 0, widgetFontSize, _justifyLeft);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUILabelToggle* addLabelToggle(string _name, bool *_value, float w, float h = 0, float x = 0, float y = 0, bool _justifyLeft = false)
    {
        ofxUILabelToggle* widget = new ofxUILabelToggle(_name, _value, w, h, x, y, widgetFontSize, _justifyLeft);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    //
    ofxUILabelButton* addLabelButton(string _name, bool _value, bool _justifyLeft = false)
    {
        ofxUILabelButton* widget = new ofxUILabelButton(_name, _value, rect->getWidth()-widgetSpacing*2, globalButtonDimension, 0, 0, widgetFontSize, _justifyLeft);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUILabelButton* addLabelButton(string _name, bool _value, float w, float h = 0, float x = 0, float y = 0, bool _justifyLeft = false)
    {
        if(h == 0)
        {
            h = globalButtonDimension; 
        }
        ofxUILabelButton* widget = new ofxUILabelButton(_name, _value, w, h, x, y, widgetFontSize, _justifyLeft);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUILabelButton* addLabelButton(string _name, bool *_value, bool _justifyLeft = false)
    {
        ofxUILabelButton* widget = new ofxUILabelButton(_name, _value, rect->getWidth()-widgetSpacing*2, globalButtonDimension, 0, 0, widgetFontSize, _justifyLeft);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUILabelButton* addLabelButton(string _name, bool *_value, float w, float h = 0, float x = 0, float y = 0, bool _justifyLeft = false)
    {
        if(h == 0)
        {
            h = globalButtonDimension; 
        }
        ofxUILabelButton* widget = new ofxUILabelButton(_name, _value, w, h, x, y, widgetFontSize, _justifyLeft);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIDropDownList* addDropDownList(string _name, vector<string> items)
    {
        ofxUIDropDownList* widget = new ofxUIDropDownList(_name, items, rect->getWidth()-widgetSpacing*2, globalButtonDimension, 0, widgetFontSize);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIDropDownList* addDropDownList(string _name, vector<string> items, float w, float x = 0, float y = 0)
    {
        ofxUIDropDownList* widget = new ofxUIDropDownList(_name, items, w, x, y, widgetFontSize);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIWaveform* addWaveform(string _name, float *_buffer, int _bufferSize, float _min = -1.0, float _max = 1.0, float _h = OFX_UI_GLOBAL_GRAPH_HEIGHT)
    {
        if(_h != globalGraphHeight)
        {
            _h = globalGraphHeight;
        }
        ofxUIWaveform* widget = new ofxUIWaveform(rect->getWidth()-widgetSpacing*2, _h, _buffer, _bufferSize, _min, _max, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIWaveform* addWaveform(string _name, float *_buffer, int _bufferSize, float _min, float _max, float _w, float _h)
    {
        ofxUIWaveform* widget = new ofxUIWaveform(_w, _h, _buffer, _bufferSize, _min, _max, _name); 
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUISpectrum* addSpectrum(string _name, float *_buffer, int _bufferSize, float _min = 0.0, float _max = 1.0, float _h = OFX_UI_GLOBAL_GRAPH_HEIGHT)
    {
        if(_h != globalGraphHeight)
        {
            _h = globalGraphHeight;
        }
        ofxUISpectrum* widget = new ofxUISpectrum(rect->getWidth()-widgetSpacing*2, _h, _buffer, _bufferSize, _min, _max, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUISpectrum* addSpectrum(string _name, float *_buffer, int _bufferSize, float _min, float _max, float _w, float _h)
    {
        ofxUISpectrum* widget = new ofxUISpectrum(_w, _h, _buffer, _bufferSize, _min, _max, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIMovingGraph* addMovingGraph(string _name, vector<float> _buffer, int _bufferSize, float _min, float _max, float _h = OFX_UI_GLOBAL_GRAPH_HEIGHT)
    {
        if(_h != globalGraphHeight)
        {
            _h = globalGraphHeight;
        }        
        ofxUIMovingGraph* widget = new ofxUIMovingGraph(rect->getWidth()-widgetSpacing*2, _h, _buffer, _bufferSize, _min, _max, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIMovingGraph* addMovingGraph(string _name, vector<float> _buffer, int _bufferSize, float _min, float _max, float _w, float _h)
    {
        ofxUIMovingGraph* widget = new ofxUIMovingGraph(_w, _h, _buffer, _bufferSize, _min, _max, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIImage *addImage(string _name, ofImage *_image, float _w, float _h)
    {
        ofxUIImage* widget = new ofxUIImage(_w, _h, _image, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }    

    ofxUIImage *addImage(string _name, ofImage *_image)
    {
        float _w = rect->getWidth()-widgetSpacing*2;
        float _h = _w*(float)_image->getHeight()/(float)_image->getWidth();
        ofxUIImage* widget = new ofxUIImage(_w, _h, _image, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIImageSampler *addImageSampler(string _name, ofImage *_image, float _w, float _h)
    {
        ofxUIImageSampler* widget = new ofxUIImageSampler(_w, _h, _image, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIImageSampler *addImageSampler(string _name, ofImage *_image)
    {
        float _w = rect->getWidth()-widgetSpacing*2;
        float _h = _w*(float)_image->getHeight()/(float)_image->getWidth();
        ofxUIImageSampler* widget = new ofxUIImageSampler(_w, _h, _image, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIBiLabelSlider *addBiLabelSlider(string _name, string _leftLabel, string _rightLabel, float _min, float _max, float _value, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIBiLabelSlider* widget = new ofxUIBiLabelSlider(rect->getWidth()-widgetSpacing*2, globalSliderHeight, _min, _max, _value, _name, _leftLabel, _rightLabel, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIBiLabelSlider *addBiLabelSlider(string _name, string _leftLabel, string _rightLabel, float _min, float _max, float *_value, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIBiLabelSlider* widget = new ofxUIBiLabelSlider(rect->getWidth()-widgetSpacing*2, globalSliderHeight, _min, _max, _value, _name, _leftLabel, _rightLabel, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIBiLabelSlider *addBiLabelSlider(string _name, string _leftLabel, string _rightLabel, float _min, float _max, float _value, float _w, float _h, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIBiLabelSlider* widget = new ofxUIBiLabelSlider(_w, _h, _min, _max, _value, _name, _leftLabel, _rightLabel, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIBiLabelSlider *addBiLabelSlider(string _name, string _leftLabel, string _rightLabel, float _min, float _max, float *_value, float _w, float _h, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIBiLabelSlider* widget = new ofxUIBiLabelSlider(_w, _h, _min, _max, _value, _name, _leftLabel, _rightLabel, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUICircleSlider* addCircleSlider(string _name, float _min, float _max, float _value)
    {
        ofxUICircleSlider* widget = new ofxUICircleSlider(rect->getWidth()-widgetSpacing*2, _min, _max, _value, _name, widgetFontSize);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUICircleSlider* addCircleSlider(string _name, float _min, float _max, float _value, float w, float x = 0, float y = 0)
    {
        ofxUICircleSlider* widget = new ofxUICircleSlider(x, y, w, _min, _max, _value, _name, widgetFontSize);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUICircleSlider* addCircleSlider(string _name, float _min, float _max, float *_value)
    {
        ofxUICircleSlider* widget = new ofxUICircleSlider(0, 0, rect->getWidth()-widgetSpacing*2, _min, _max, _value, _name, widgetFontSize);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUICircleSlider* addCircleSlider(string _name, float _min, float _max, float *_value, float w, float x = 0, float y = 0)
    {
        ofxUICircleSlider* widget = new ofxUICircleSlider(x, y, w, _min, _max, _value, _name, widgetFontSize);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIValuePlotter* addValuePlotter(string _name, int _bufferSize, float _min, float _max, float *_value, float _h = OFX_UI_GLOBAL_GRAPH_HEIGHT)
    {
        if(_h != globalGraphHeight)
        {
            _h = globalGraphHeight;
        }
        ofxUIValuePlotter* widget = new ofxUIValuePlotter(rect->getWidth()-widgetSpacing*2, _h, _bufferSize, _min, _max, _value, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIValuePlotter* addValuePlotter(string _name, int _bufferSize, float _min, float _max, float *_value, float _w, float _h)
    {
        ofxUIValuePlotter* widget = new ofxUIValuePlotter(_w, _h, _bufferSize, _min, _max, _value, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    
    ofxUI2DGraph *add2DGraph(string _name, ofPoint _rangeX, ofPoint _rangeY, int _bufferSize, float * _xValues, float * _yValues)
    {
        ofxUI2DGraph* widget = new ofxUI2DGraph(_name, _rangeX, _rangeY, _bufferSize, _xValues, _yValues, rect->getWidth()-widgetSpacing*2, rect->getWidth()-widgetSpacing*2); 
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUI2DGraph *add2DGraph(string _name, ofPoint _rangeX, ofPoint _rangeY, int _bufferSize, float * _xValues, float * _yValues, float _w, float _h, float _x = 0, float _y = 0)
    {
        ofxUI2DGraph* widget = new ofxUI2DGraph(_name, _rangeX, _rangeY, _bufferSize, _xValues, _yValues, _w, _h, _x, _y);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIImageToggle *addImageToggle(string _name, string _path, bool *_value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIImageToggle *widget = new ofxUIImageToggle(x, y, w, h, _value, _path, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;        
    }

    ofxUIImageToggle *addImageToggle(string _name, string _path, bool _value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIImageToggle *widget = new ofxUIImageToggle(x, y, w, h, _value, _path, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUIImageToggle *addImageToggle(string _name, string _path, bool *_value, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIImageToggle *widget = new ofxUIImageToggle(globalButtonDimension, globalButtonDimension, _value, _path, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIImageToggle *addImageToggle(string _name, string _path, bool _value, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIImageToggle *widget = new ofxUIImageToggle(globalButtonDimension, globalButtonDimension, _value, _path, _name);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIImageButton *addImageButton(string _name, string _path, bool *_value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIImageButton *widget = new ofxUIImageButton(x, y, w, h, _value, _path, _name, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIImageButton *addImageButton(string _name, string _path, bool _value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIImageButton *widget = new ofxUIImageButton(x, y, w, h, _value, _path, _name, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIImageButton *addImageButton(string _name, string _path, bool *_value, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIImageButton *widget = new ofxUIImageButton(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIImageButton *addImageButton(string _name, string _path, bool _value, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIImageButton *widget = new ofxUIImageButton(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIMultiImageButton *addMultiImageButton(string _name, string _path, bool *_value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIMultiImageButton *widget = new ofxUIMultiImageButton(x, y, w, h, _value, _path, _name, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIMultiImageButton *addMultiImageButton(string _name, string _path, bool _value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIMultiImageButton *widget = new ofxUIMultiImageButton(x, y, w, h, _value, _path, _name, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIMultiImageButton *addMultiImageButton(string _name, string _path, bool *_value, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIMultiImageButton *widget = new ofxUIMultiImageButton(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIMultiImageButton *addMultiImageButton(string _name, string _path, bool _value, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIMultiImageButton *widget = new ofxUIMultiImageButton(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    //
    ofxUIMultiImageToggle *addMultiImageToggle(string _name, string _path, bool *_value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIMultiImageToggle *widget = new ofxUIMultiImageToggle(x, y, w, h, _value, _path, _name, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIMultiImageToggle *addMultiImageToggle(string _name, string _path, bool _value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIMultiImageToggle *widget = new ofxUIMultiImageToggle(x, y, w, h, _value, _path, _name, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIMultiImageToggle *addMultiImageToggle(string _name, string _path, bool *_value, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIMultiImageToggle *widget = new ofxUIMultiImageToggle(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIMultiImageToggle *addMultiImageToggle(string _name, string _path, bool _value, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUIMultiImageToggle *widget = new ofxUIMultiImageToggle(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    //
    
    ofxUITextArea* addTextArea(string _name, string _textstring, int _size = OFX_UI_FONT_MEDIUM)
    {
        ofxUITextArea *widget = new ofxUITextArea(_name, _textstring, rect->getWidth()-widgetSpacing*2, 0, 0, 0, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
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
    
    void setRetinaResolution()
    {
        setGlobalCanvasWidth(OFX_UI_GLOBAL_CANVAS_WIDTH*2);
        setPadding(OFX_UI_GLOBAL_PADDING*2);
        setWidgetSpacing(OFX_UI_GLOBAL_WIDGET_SPACING*2);        
        setFontSize(OFX_UI_FONT_LARGE, OFX_UI_FONT_LARGE_SIZE*2);
        setFontSize(OFX_UI_FONT_MEDIUM, OFX_UI_FONT_MEDIUM_SIZE*2);
        setFontSize(OFX_UI_FONT_SMALL, OFX_UI_FONT_SMALL_SIZE*2);
        setGlobalButtonDimension(OFX_UI_GLOBAL_BUTTON_DIMENSION*4);
        setGlobalSliderHeight(OFX_UI_GLOBAL_SLIDER_HEIGHT*4);
        setGlobalSpacerHeight(OFX_UI_GLOBAL_SPACING_HEIGHT*2);
        setGlobalGraphHeight(OFX_UI_GLOBAL_GRAPH_HEIGHT*2);
    }
    
    void setGlobalSliderHeight(float _globalSliderHeight)
    {
        globalSliderHeight = _globalSliderHeight;
    }
    
    void setGlobalGraphHeight(float _globalGraphHeight)
    {
        globalGraphHeight = _globalGraphHeight;
    }
    
    void setGlobalButtonDimension(float _globalButtonDimension)
    {
        globalButtonDimension = _globalButtonDimension;
    }
    
    void setGlobalSpacerHeight(float _globalSpacerHeight)
    {
        globalSpacerHeight = _globalSpacerHeight;
    }
    
    float getGlobalSliderHeight()
    {
        return globalSliderHeight;
    }
    
    float getGlobalGraphHeight()
    {
        return globalGraphHeight;
    }
    
    float getGlobalButtonDimension()
    {
        return globalButtonDimension;
    }
    
    float getGlobalSpacerHeight()
    {
        return globalSpacerHeight;
    }
    
    void setGlobalCanvasWidth(float _globalCanvasWidth)
    {
        globalCanvasWidth = _globalCanvasWidth;
        rect->setWidth(globalCanvasWidth);
        paddedRect->setWidth(globalCanvasWidth+padding*2);
    }
    
    float getGlobalCanvasWidth()
    {
        return globalCanvasWidth; 
    }
		
	void setWidgetPosition(ofxWidgetPosition _position, int _align = -1)
	{
	    widgetPosition = _position;
	    if (_align == -1) 
	    {
	        if (_position == OFX_UI_WIDGET_POSITION_DOWN ||
                _position == OFX_UI_WIDGET_POSITION_UP) 
            {
                widgetAlign = OFX_UI_ALIGN_LEFT;
            }
            else
            {
                widgetAlign = OFX_UI_ALIGN_FREE;
            }
	    }
        else
        {
            widgetAlign = (ofxWidgetAlignment)_align;
        }
	}
	
    void setWidgetFontSize(ofxWidgetFontType _widgetFontSize)
    {
        widgetFontSize = _widgetFontSize;
    }
    
    ofxWidgetPosition getWidgetPosition()
    {
        return widgetPosition;
    }
    
    ofxWidgetFontType getWidgetFontSize()
    {
        return widgetFontSize; 
    }
    
	void triggerEvent(ofxUIWidget *child)
	{
        checkForKeyFocus(child);
        GUIevent->widget = child; 		
        ofNotifyEvent(newGUIEvent,*GUIevent,this);
	}
	    
    void setUIColors(ofColor &cb, ofColor &co, ofColor &coh, ofColor &cf, ofColor &cfh, ofColor &cp, ofColor &cpo)
    {
        setWidgetColor(OFX_UI_WIDGET_COLOR_BACK, cb);
        setWidgetColor(OFX_UI_WIDGET_COLOR_OUTLINE, co);                
        setWidgetColor(OFX_UI_WIDGET_COLOR_OUTLINE_HIGHLIGHT, coh);
        setWidgetColor(OFX_UI_WIDGET_COLOR_FILL, cf);                
        setWidgetColor(OFX_UI_WIDGET_COLOR_FILL_HIGHLIGHT, cfh);
        setWidgetColor(OFX_UI_WIDGET_COLOR_PADDED, cp);
        setWidgetColor(OFX_UI_WIDGET_COLOR_PADDED_OUTLINE, cpo);
        
        setColorBack(cb);
        setColorOutline(co);
        setColorOutlineHighlight(coh);
        setColorFill(cf);
        setColorFillHighlight(cfh);
        setColorPadded(cp);
        setColorPaddedOutline(cpo);                
    }
    
    void setTheme(int theme)
    {
        switch(theme)
        {
            case OFX_UI_THEME_DEFAULT:
            {
                ofColor cb = OFX_UI_COLOR_BACK; 
                ofColor co = OFX_UI_COLOR_OUTLINE; 
                ofColor coh = OFX_UI_COLOR_OUTLINE_HIGHLIGHT;
                ofColor cf = OFX_UI_COLOR_FILL; 
                ofColor cfh = OFX_UI_COLOR_FILL_HIGHLIGHT;
                ofColor cp = OFX_UI_COLOR_PADDED;
                ofColor cpo = OFX_UI_COLOR_PADDED_OUTLINE;
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_HACKER:
            {
                ofColor cb = ofColor( 0.294118*255.0, 0*255.0, 0.0588235*255.0, 0.196078*255.0 );
                ofColor co = ofColor( 0.254902*255.0, 0.239216*255.0, 0.239216*255.0, 0.392157*255.0 );
                ofColor coh = ofColor( 0.294118*255.0, 0*255.0, 0.0588235*255.0, 0.784314*255.0 );
                ofColor cf = ofColor( 0.784314*255.0, 1*255.0, 0*255.0, 0.784314*255.0 );
                ofColor cfh = ofColor( 0.980392*255.0, 0.00784314*255.0, 0.235294*255.0, 1*255.0 );
                ofColor cp = ofColor( 0.0156863*255.0, 0*255.0, 0.0156863*255.0, 0.392157*255.0 );
                ofColor cpo = ofColor( 0.254902*255.0, 0.239216*255.0, 0.239216*255.0, 0.784314*255.0 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
                
            case OFX_UI_THEME_HIPSTER:
            {
                ofColor cb = ofColor( 0.607843*255.0, 0.6*255.0, 0.509804*255.0, 0.196078*255.0 );
                ofColor co = ofColor( 0.231373*255.0, 0.392157*255.0, 0.501961*255.0, 0.392157*255.0 );
                ofColor coh = ofColor( 0.607843*255.0, 0.6*255.0, 0.509804*255.0, 0.784314*255.0 );
                ofColor cf = ofColor( 1*255.0, 0.52549*255.0, 0.0666667*255.0, 0.784314*255.0 );
                ofColor cfh = ofColor( 0.0313725*255.0, 0.101961*255.0, 0.188235*255.0, 1*255.0 );
                ofColor cp = ofColor( 0.196078*255.0, 0.25098*255.0, 0.352941*255.0, 0.392157*255.0 );
                ofColor cpo = ofColor( 0.231373*255.0, 0.392157*255.0, 0.501961*255.0, 0.784314*255.0 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_DIETER:
            {
                ofColor cb = ofColor( 0.803922*255.0, 0.741176*255.0, 0.682353*255.0, 0.196078*255.0 );
                ofColor co = ofColor( 0.478431*255.0, 0.356863*255.0, 0.243137*255.0, 0.392157*255.0 );
                ofColor coh = ofColor( 0.803922*255.0, 0.741176*255.0, 0.682353*255.0, 0.784314*255.0 );
                ofColor cf = ofColor( 0.980392*255.0, 0.294118*255.0, 0*255.0, 0.784314*255.0 );
                ofColor cfh = ofColor( 0.980392*255.0, 0.980392*255.0, 0.980392*255.0, 1*255.0 );
                ofColor cp = ofColor( 0.121569*255.0, 0.121569*255.0, 0.121569*255.0, 0.392157*255.0 );
                ofColor cpo = ofColor( 0.478431*255.0, 0.356863*255.0, 0.243137*255.0, 0.784314*255.0 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_BARBIE:
            {
                ofColor cb = ofColor( 0.92549*255.0, 0*255.0, 0.54902*255.0, 0.196078*255.0 );
                ofColor co = ofColor( 0*255.0, 0*255.0, 0*255.0, 0.392157*255.0 );
                ofColor coh = ofColor( 0*255.0, 0.678431*255.0, 0.937255*255.0, 0.784314*255.0 );
                ofColor cf = ofColor( 0.92549*255.0, 0*255.0, 0.54902*255.0, 0.784314*255.0 );
                ofColor cfh = ofColor( 1*255.0, 0.94902*255.0, 0*255.0, 1*255.0 );
                ofColor cp = ofColor( 0*255.0, 0*255.0, 0*255.0, 0.392157*255.0 );
                ofColor cpo = ofColor( 0*255.0, 0.678431*255.0, 0.937255*255.0, 0.784314*255.0 ); 
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_WINDOWS:
            {
                ofColor cb = ofColor( 0.0470588*255.0, 0.0588235*255.0, 0.4*255.0, 0.196078*255.0 );
                ofColor co = ofColor( 0.0431373*255.0, 0.0627451*255.0, 0.54902*255.0, 0.392157*255.0 );
                ofColor coh = ofColor( 0.0470588*255.0, 0.0588235*255.0, 0.4*255.0, 0.784314*255.0 );
                ofColor cf = ofColor( 0.054902*255.0, 0.305882*255.0, 0.678431*255.0, 0.784314*255.0 );
                ofColor cfh = ofColor( 0.0627451*255.0, 0.498039*255.0, 0.788235*255.0, 1*255.0 );
                ofColor cp = ofColor( 0.027451*255.0, 0.0352941*255.0, 0.239216*255.0, 0.392157*255.0 );
                ofColor cpo = ofColor( 0.0431373*255.0, 0.0627451*255.0, 0.54902*255.0, 0.784314*255.0 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MACOSX:
            {
                ofColor cb = ofColor( 0*255.0, 0.678431*255.0, 0.937255*255.0, 0.196078*255.0 );
                ofColor co = ofColor( 1*255.0, 0.94902*255.0, 0*255.0, 0.392157*255.0 );
                ofColor coh = ofColor( 0*255.0, 0*255.0, 0*255.0, 0.784314*255.0 );
                ofColor cf = ofColor( 0*255.0, 0.678431*255.0, 0.937255*255.0, 0.784314*255.0 );
                ofColor cfh = ofColor( 0.92549*255.0, 0*255.0, 0.54902*255.0, 1*255.0 );
                ofColor cp = ofColor( 1*255.0, 0.94902*255.0, 0*255.0, 0.392157*255.0 );
                ofColor cpo = ofColor( 0*255.0, 0*255.0, 0*255.0, 0.784314*255.0 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_ZOOLANDER:
            {
                ofColor cb = ofColor( 0.160784*255.0, 0.133333*255.0, 0.121569*255.0, 0.196078*255.0 );
                ofColor co = ofColor( 0.0745098*255.0, 0.454902*255.0, 0.490196*255.0, 0.392157*255.0 );
                ofColor coh = ofColor( 0.160784*255.0, 0.133333*255.0, 0.121569*255.0, 0.784314*255.0 );
                ofColor cf = ofColor( 0.988235*255.0, 0.207843*255.0, 0.298039*255.0, 0.784314*255.0 );
                ofColor cfh = ofColor( 0.988235*255.0, 0.968627*255.0, 0.772549*255.0, 1*255.0 );
                ofColor cp = ofColor( 0.0392157*255.0, 0.74902*255.0, 0.737255*255.0, 0.392157*255.0 );
                ofColor cpo = ofColor( 0.0745098*255.0, 0.454902*255.0, 0.490196*255.0, 0.784314*255.0 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_VEGAN2:
            {
                ofColor cb = ofColor( 0.745098*255.0, 0.94902*255.0, 0.00784314*255.0, 0.196078*255.0 );
                ofColor co = ofColor( 0.533333*255.0, 0.768627*255.0, 0.145098*255.0, 0.392157*255.0 );
                ofColor coh = ofColor( 0.745098*255.0, 0.94902*255.0, 0.00784314*255.0, 0.784314*255.0 );
                ofColor cf = ofColor( 0.917647*255.0, 0.992157*255.0, 0.901961*255.0, 0.784314*255.0 );
                ofColor cfh = ofColor( 0.105882*255.0, 0.403922*255.0, 0.419608*255.0, 1*255.0 );
                ofColor cp = ofColor( 0.317647*255.0, 0.584314*255.0, 0.282353*255.0, 0.392157*255.0 );
                ofColor cpo = ofColor( 0.533333*255.0, 0.768627*255.0, 0.145098*255.0, 0.784314*255.0 );                                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_BERLIN:
            {
                ofColor cb = ofColor( 0.6*255.0, 0.894118*255.0, 1*255.0, 0.196078*255.0 );
                ofColor co = ofColor( 0.294118*255.0, 0.34902*255.0, 0.419608*255.0, 0.392157*255.0 );
                ofColor coh = ofColor( 0.6*255.0, 0.894118*255.0, 1*255.0, 0.784314*255.0 );
                ofColor cf = ofColor( 0.968627*255.0, 0.309804*255.0, 0.309804*255.0, 0.784314*255.0 );
                ofColor cfh = ofColor( 1*255.0, 0.231373*255.0, 0.231373*255.0, 1*255.0 );
                ofColor cp = ofColor( 0.105882*255.0, 0.12549*255.0, 0.14902*255.0, 0.392157*255.0 );
                ofColor cpo = ofColor( 0.294118*255.0, 0.34902*255.0, 0.419608*255.0, 0.784314*255.0 ); 
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_METALGEAR:
            {
                ofColor cb = ofColor( 51, 44, 44, 75 );
                ofColor co = ofColor( 25, 26, 36, 100 );
                ofColor coh = ofColor( 51, 44, 44, 200 );
                ofColor cf = ofColor( 250, 101, 87, 200 );
                ofColor cfh = ofColor( 255, 255, 255, 255 );
                ofColor cp = ofColor( 0, 0, 0, 100 );
                ofColor cpo = ofColor( 25, 26, 36, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_TEALLIME:
            {
                ofColor cb = ofColor( 27, 103, 107, 75 );
                ofColor co = ofColor( 234, 253, 230, 100 );
                ofColor coh = ofColor( 27, 103, 107, 200 );
                ofColor cf = ofColor( 81, 149, 72, 200 );
                ofColor cfh = ofColor( 136, 196, 37, 255 );
                ofColor cp = ofColor( 190, 242, 2, 100 );
                ofColor cpo = ofColor( 234, 253, 230, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_VEGAN:
            {
                ofColor cb = ofColor( 81, 149, 72, 75 );
                ofColor co = ofColor( 27, 103, 107, 100 );
                ofColor coh = ofColor( 81, 149, 72, 200 );
                ofColor cf = ofColor( 136, 196, 37, 200 );
                ofColor cfh = ofColor( 190, 242, 2, 255 );
                ofColor cp = ofColor( 234, 253, 230, 100 );
                ofColor cpo = ofColor( 27, 103, 107, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_RUSTIC:
            {
                ofColor cb = ofColor( 196, 182, 109, 75 );
                ofColor co = ofColor( 247, 109, 60, 100 );
                ofColor coh = ofColor( 196, 182, 109, 200 );
                ofColor cf = ofColor( 213, 39, 5, 200 );
                ofColor cfh = ofColor( 240, 211, 119, 255 );
                ofColor cp = ofColor( 243, 232, 228, 100 );
                ofColor cpo = ofColor( 247, 109, 60, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MIDNIGHT:
            {
                ofColor cb = ofColor( 11, 72, 107, 75 );
                ofColor co = ofColor( 207, 240, 158, 100 );
                ofColor coh = ofColor( 11, 72, 107, 200 );
                ofColor cf = ofColor( 59, 134, 134, 200 );
                ofColor cfh = ofColor( 121, 189, 154, 255 );
                ofColor cp = ofColor( 168, 219, 168, 100 );
                ofColor cpo = ofColor( 207, 240, 158, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MINBLUE:
            {
                ofColor cb = ofColor( 254, 249, 240, 75 );
                ofColor co = ofColor( 176, 248, 255, 100 );
                ofColor coh = ofColor( 254, 249, 240, 200 );
                ofColor cf = ofColor( 0, 188, 209, 200 );
                ofColor cfh = ofColor( 118, 211, 222, 255 );
                ofColor cp = ofColor( 174, 232, 251, 100 );
                ofColor cpo = ofColor( 176, 248, 255, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_LIMESTONE:
            {
                ofColor cb = ofColor( 108, 144, 134, 75 );
                ofColor co = ofColor( 252, 84, 99, 100 );
                ofColor coh = ofColor( 108, 144, 134, 200 );
                ofColor cf = ofColor( 169, 204, 24, 200 );
                ofColor cfh = ofColor( 207, 73, 108, 255 );
                ofColor cp = ofColor( 235, 234, 188, 100 );
                ofColor cpo = ofColor( 252, 84, 99, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;                  
                
            case OFX_UI_THEME_SPEARMINT:
            {
                ofColor cb = ofColor( 25, 140, 9, 75 );
                ofColor co = ofColor( 255, 197, 95, 100 );
                ofColor coh = ofColor( 25, 140, 9, 200 );
                ofColor cf = ofColor( 220, 250, 250, 200 );
                ofColor cfh = ofColor( 239, 88, 141, 255 );
                ofColor cp = ofColor( 254, 169, 18, 100 );
                ofColor cpo = ofColor( 255, 197, 95, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;                  
                
            case OFX_UI_THEME_MINPINK:
            {
                ofColor cb = ofColor( 220, 250, 250, 75 );
                ofColor co = ofColor( 25, 140, 9, 100 );
                ofColor coh = ofColor( 220, 250, 250, 200 );
                ofColor cf = ofColor( 239, 88, 141, 200 );
                ofColor cfh = ofColor( 254, 169, 18, 255 );
                ofColor cp = ofColor( 255, 197, 95, 100 );
                ofColor cpo = ofColor( 25, 140, 9, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_PEPTOBISMOL:
            {
                ofColor cb = ofColor( 223, 21, 26, 75 );
                ofColor co = ofColor( 0, 218, 60, 100 );
                ofColor coh = ofColor( 223, 21, 26, 200 );
                ofColor cf = ofColor( 244, 243, 40, 200 );
                ofColor cfh = ofColor( 253, 134, 3, 255 );
                ofColor cp = ofColor( 0, 203, 231, 100 );
                ofColor cpo = ofColor( 0, 218, 60, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_BILEBLUE:
            {
                ofColor cb = ofColor( 253, 134, 3, 75 );
                ofColor co = ofColor( 244, 243, 40, 100 );
                ofColor coh = ofColor( 253, 134, 3, 200 );
                ofColor cf = ofColor( 0, 203, 231, 200 );
                ofColor cfh = ofColor( 0, 218, 60, 255 );
                ofColor cp = ofColor( 223, 21, 26, 100 );
                ofColor cpo = ofColor( 244, 243, 40, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_COOLCLAY:
            {
                ofColor cb = ofColor( 153, 228, 255, 75 );
                ofColor co = ofColor( 75, 89, 107, 100 );
                ofColor coh = ofColor( 153, 228, 255, 200 );
                ofColor cf = ofColor( 247, 79, 79, 200 );
                ofColor cfh = ofColor( 255, 59, 59, 255 );
                ofColor cp = ofColor( 27, 32, 38, 100 );
                ofColor cpo = ofColor( 75, 89, 107, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_BLUEBLUE:
            {
                ofColor cb = ofColor( 0, 173, 239, 75 );
                ofColor co = ofColor( 255, 242, 0, 100 );
                ofColor coh = ofColor( 0, 0, 0, 200 );
                ofColor cf = ofColor( 0, 173, 239, 200 );
                ofColor cfh = ofColor( 236, 0, 140, 255 );
                ofColor cp = ofColor( 255, 242, 0, 100 );
                ofColor cpo = ofColor( 0, 0, 0, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_PINKPANTHER:
            {
                ofColor cb = ofColor( 236, 0, 140, 75 );
                ofColor co = ofColor( 0, 0, 0, 100 );
                ofColor coh = ofColor( 0, 173, 239, 200 );
                ofColor cf = ofColor( 236, 0, 140, 200 );
                ofColor cfh = ofColor( 255, 242, 0, 255 );
                ofColor cp = ofColor( 0, 0, 0, 100 );
                ofColor cpo = ofColor( 0, 173, 239, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MAROON:
            {
                ofColor cb = ofColor( 101, 150, 158, 75 );
                ofColor co = ofColor( 219, 217, 210, 100 );
                ofColor coh = ofColor( 101, 150, 158, 200 );
                ofColor cf = ofColor( 171, 20, 44, 200 );
                ofColor cfh = ofColor( 189, 219, 222, 255 );
                ofColor cp = ofColor( 205, 212, 108, 100 );
                ofColor cpo = ofColor( 219, 217, 210, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_PINKLATTE:
            {
                ofColor cb = ofColor( 218, 216, 167, 75 );
                ofColor co = ofColor( 127, 199, 175, 100 );
                ofColor coh = ofColor( 218, 216, 167, 200 );
                ofColor cf = ofColor( 255, 61, 127, 200 );
                ofColor cfh = ofColor( 255, 158, 157, 255 );
                ofColor cp = ofColor( 63, 184, 175, 100 );
                ofColor cpo = ofColor( 127, 199, 175, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MINGREEN:
            {
                ofColor cb = ofColor( 255, 255, 255, 75 );
                ofColor co = ofColor( 242, 230, 194, 100 );
                ofColor coh = ofColor( 255, 255, 255, 200 );
                ofColor cf = ofColor( 111, 191, 162, 200 );
                ofColor cfh = ofColor( 191, 184, 174, 255 );
                ofColor cp = ofColor( 242, 199, 119, 100 );
                ofColor cpo = ofColor( 242, 230, 194, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_HELLOYELLOW:
            {
                ofColor cb = ofColor( 255, 211, 0, 75 );
                ofColor co = ofColor( 74, 186, 176, 100 );
                ofColor coh = ofColor( 152, 33, 0, 200 );
                ofColor cf = ofColor( 255, 211, 0, 200 );
                ofColor cfh = ofColor( 255, 245, 158, 255 );
                ofColor cp = ofColor( 74, 186, 176, 100 );
                ofColor cpo = ofColor( 152, 33, 0, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_TEALTEAL:
            {
                ofColor cb = ofColor( 74, 186, 176, 75 );
                ofColor co = ofColor( 255, 211, 0, 100 );
                ofColor coh = ofColor( 255, 245, 158, 200 );
                ofColor cf = ofColor( 74, 186, 176, 200 );
                ofColor cfh = ofColor( 152, 33, 0, 255 );
                ofColor cp = ofColor( 255, 211, 0, 100 );
                ofColor cpo = ofColor( 255, 245, 158, 200 );            
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_RUSTICORANGE:
            {
                ofColor cb = ofColor( 107, 85, 48, 75 );
                ofColor co = ofColor( 49, 48, 66, 100 );
                ofColor coh = ofColor( 107, 85, 48, 200 );
                ofColor cf = ofColor( 255, 109, 36, 200 );
                ofColor cfh = ofColor( 255, 235, 107, 255 );
                ofColor cp = ofColor( 42, 135, 50, 100 );
                ofColor cpo = ofColor( 49, 48, 66, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_TEALSALMON:
            {
                ofColor cb = ofColor( 78, 133, 136, 75 );
                ofColor co = ofColor( 56, 69, 59, 100 );
                ofColor coh = ofColor( 78, 133, 136, 200 );
                ofColor cf = ofColor( 255, 70, 84, 200 );
                ofColor cfh = ofColor( 255, 213, 106, 255 );
                ofColor cp = ofColor( 255, 254, 211, 100 );
                ofColor cpo = ofColor( 56, 69, 59, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_CITRUSBLUE:
            {
                ofColor cb = ofColor( 57, 142, 182, 75 );
                ofColor co = ofColor( 34, 104, 136, 100 );
                ofColor coh = ofColor( 57, 142, 182, 200 );
                ofColor cf = ofColor( 255, 162, 0, 200 );
                ofColor cfh = ofColor( 255, 214, 0, 255 );
                ofColor cp = ofColor( 255, 245, 0, 100 );
                ofColor cpo = ofColor( 34, 104, 136, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_LIMEPURPLE:
            {
                ofColor cb = ofColor( 87, 54, 255, 75 );
                ofColor co = ofColor( 38, 38, 38, 100 );
                ofColor coh = ofColor( 87, 54, 255, 200 );
                ofColor cf = ofColor( 231, 255, 54, 200 );
                ofColor cfh = ofColor( 255, 54, 111, 255 );
                ofColor cp = ofColor( 35, 116, 222, 100 );
                ofColor cpo = ofColor( 38, 38, 38, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_LIMESTONE2:
            {
                ofColor cb = ofColor( 101, 98, 115, 75 );
                ofColor co = ofColor( 89, 186, 169, 100 );
                ofColor coh = ofColor( 101, 98, 115, 200 );
                ofColor cf = ofColor( 216, 241, 113, 200 );
                ofColor cfh = ofColor( 252, 255, 217, 255 );
                ofColor cp = ofColor( 64, 18, 44, 100 );
                ofColor cpo = ofColor( 89, 186, 169, 200 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_COOLPURPLE:
            {
                ofColor cb = ofColor( 38, 137, 233, 75 );
                ofColor co = ofColor( 11, 246, 147, 100 );
                ofColor coh = ofColor( 38, 137, 233, 200 );
                ofColor cf = ofColor( 233, 26, 157, 200 );
                ofColor cfh = ofColor( 246, 182, 11, 255 );
                ofColor cp = ofColor( 246, 242, 11, 100 );
                ofColor cpo = ofColor( 11, 246, 147, 200 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_GRAYRED:
            {
                ofColor cb = ofColor( 41, 34, 31, 75 );
                ofColor co = ofColor( 19, 116, 125, 100 );
                ofColor coh = ofColor( 41, 34, 31, 200 );
                ofColor cf = ofColor( 252, 53, 76, 200 );
                ofColor cfh = ofColor( 252, 247, 197, 255 );
                ofColor cp = ofColor( 10, 191, 188, 100 );
                ofColor cpo = ofColor( 19, 116, 125, 200 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_METALGEAR2:
            {
                ofColor cb = ofColor( 205, 189, 174, 75 );
                ofColor co = ofColor( 122, 91, 62, 100 );
                ofColor coh = ofColor( 205, 189, 174, 200 );
                ofColor cf = ofColor( 250, 75, 0, 200 );
                ofColor cfh = ofColor( 250, 250, 250, 255 );
                ofColor cp = ofColor( 31, 31, 31, 100 );
                ofColor cpo = ofColor( 122, 91, 62, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_LIGHTPINK:
            {
                ofColor cb = ofColor( 158, 30, 76, 75 );
                ofColor co = ofColor( 143, 143, 143, 100 );
                ofColor coh = ofColor( 158, 30, 76, 200 );
                ofColor cf = ofColor( 236, 236, 236, 200 );
                ofColor cfh = ofColor( 255, 17, 104, 255 );
                ofColor cp = ofColor( 37, 2, 15, 100 );
                ofColor cpo = ofColor( 143, 143, 143, 200 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MINPINK2:
            {
                ofColor cb = ofColor( 236, 236, 236, 75 );
                ofColor co = ofColor( 158, 30, 76, 100 );
                ofColor coh = ofColor( 236, 236, 236, 200 );
                ofColor cf = ofColor( 255, 17, 104, 200 );
                ofColor cfh = ofColor( 37, 2, 15, 255 );
                ofColor cp = ofColor( 143, 143, 143, 100 );
                ofColor cpo = ofColor( 158, 30, 76, 200 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MAXPINK:
            {
                ofColor cb = ofColor( 255, 20, 87, 75 );
                ofColor co = ofColor( 10, 10, 10, 100 );
                ofColor coh = ofColor( 227, 246, 255, 200 );
                ofColor cf = ofColor( 255, 20, 87, 200 );
                ofColor cfh = ofColor( 255, 216, 125, 255 );
                ofColor cp = ofColor( 10, 10, 10, 100 );
                ofColor cpo = ofColor( 227, 246, 255, 200 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MINYELLOW:
            {
                ofColor cb = ofColor( 229, 228, 218, 75 );
                ofColor co = ofColor( 216, 210, 153, 100 );
                ofColor coh = ofColor( 229, 228, 218, 200 );
                ofColor cf = ofColor( 245, 224, 56, 200 );
                ofColor cfh = ofColor( 23, 22, 92, 255 );
                ofColor cp = ofColor( 190, 191, 158, 100 );
                ofColor cpo = ofColor( 216, 210, 153, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MINLIME:
            {
                ofColor cb = ofColor( 245, 225, 226, 75 );
                ofColor co = ofColor( 225, 183, 237, 100 );
                ofColor coh = ofColor( 245, 225, 226, 200 );
                ofColor cf = ofColor( 185, 222, 81, 200 );
                ofColor cfh = ofColor( 209, 227, 137, 255 );
                ofColor cp = ofColor( 224, 72, 145, 100 );
                ofColor cpo = ofColor( 225, 183, 237, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MINORANGE:
            {
                ofColor cb = ofColor( 204, 204, 204, 75 );
                ofColor co = ofColor( 111, 111, 111, 100 );
                ofColor coh = ofColor( 204, 204, 204, 200 );
                ofColor cf = ofColor( 255, 100, 0, 200 );
                ofColor cfh = ofColor( 255, 255, 255, 255 );
                ofColor cp = ofColor( 51, 51, 51, 100 );
                ofColor cpo = ofColor( 111, 111, 111, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_GRAYDAY:
            {
                ofColor cb = ofColor( 177, 198, 204, 75 );
                ofColor co = ofColor( 255, 255, 255, 100 );
                ofColor coh = ofColor( 20, 20, 20, 200 );
                ofColor cf = ofColor( 177, 198, 204, 200 );
                ofColor cfh = ofColor( 255, 239, 94, 255 );
                ofColor cp = ofColor( 255, 255, 255, 100 );
                ofColor cpo = ofColor( 20, 20, 20, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MINBLACK:
            {
                ofColor cb = ofColor( 255, 255, 255, 75 );
                ofColor co = ofColor( 209, 231, 81, 100 );
                ofColor coh = ofColor( 255, 255, 255, 200 );
                ofColor cf = ofColor( 0, 0, 0, 200 );
                ofColor cfh = ofColor( 38, 173, 228, 255 );
                ofColor cp = ofColor( 77, 188, 233, 100 );
                ofColor cpo = ofColor( 209, 231, 81, 200 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            default:
            {
                ofColor cb = OFX_UI_COLOR_BACK; 
                ofColor co = OFX_UI_COLOR_OUTLINE; 
                ofColor coh = OFX_UI_COLOR_OUTLINE_HIGHLIGHT;
                ofColor cf = OFX_UI_COLOR_FILL; 
                ofColor cfh = OFX_UI_COLOR_FILL_HIGHLIGHT;
                ofColor cp = OFX_UI_COLOR_PADDED;
                ofColor cpo = OFX_UI_COLOR_PADDED_OUTLINE;
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break; 
        }
    }
    
    ofColor& getWidgetColorPadded()
	{
        return widget_color_padded_rect;
	}
    
	ofColor& getWidgetColorPaddedOutline()
	{
        return widget_color_padded_rect_outline;
	}
    
	ofColor& getWidgetColorBack()
	{
		return widget_color_back;
	}
	
	ofColor& getWidgetColorOutline()
	{
		return widget_color_outline;
	}
	
	ofColor& getWidgetColorOutlineHighlight()
	{
		return widget_color_outline_highlight;
	}
	
	ofColor& getWidgetColorFill()
	{
		return widget_color_fill;
	}
	
	ofColor& getWidgetColorFillHighlight()
	{
		return widget_color_fill_highlight;
	}
	
    void setWidgetDrawingProperties(ofxUIWidget *widget)
    {
        widget->setDrawPaddingOutline(bDrawWidgetPaddingOutline);
        widget->setDrawPadding(bDrawWidgetPadding);
    }
    
    void setWidgetColor(ofxUIWidget *widget)
    {
        widget->setColorBack(color_back);
        widget->setColorOutline(color_outline);
        widget->setColorOutlineHighlight(color_outline_highlight);
        widget->setColorFill(color_fill);
        widget->setColorFillHighlight(color_fill_highlight);
        widget->setColorPadded(color_padded_rect);
        widget->setColorPaddedOutline(color_padded_rect_outline);
    }
    
	void setWidgetColor(int _target, ofColor _color)
	{
		switch (_target) 
		{
			case OFX_UI_WIDGET_COLOR_BACK:
                widget_color_back = _color;
                for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
				{
					(*it)->setColorBack(_color);
				}				
				break;

			case OFX_UI_WIDGET_COLOR_OUTLINE:
                widget_color_outline = _color;
                for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
				{
					(*it)->setColorOutline(_color); 
				}				
				break;
			
			case OFX_UI_WIDGET_COLOR_OUTLINE_HIGHLIGHT:
                widget_color_outline_highlight = _color;
                for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
				{
					(*it)->setColorOutlineHighlight(_color); 
				}				
				break;
			
			case OFX_UI_WIDGET_COLOR_FILL:
                widget_color_fill = _color;
                for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
				{
					(*it)->setColorFill(_color);
				}				
				break;
			
			case OFX_UI_WIDGET_COLOR_FILL_HIGHLIGHT:
                widget_color_fill_highlight = _color;
                for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
				{
					(*it)->setColorFillHighlight(_color); 
				}					
				break;
                
			case OFX_UI_WIDGET_COLOR_PADDED:
                widget_color_padded_rect = _color;
                for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
				{
					(*it)->setColorPadded(_color); 
				}					
				break;
                
			case OFX_UI_WIDGET_COLOR_PADDED_OUTLINE:
                widget_color_padded_rect_outline = _color;
                for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
				{
					(*it)->setColorPaddedOutline(_color);
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
        ofxUIWidget *w = widgets_map[_name];
        if(w != NULL)
        {
            removeWidget(w);
        }
    }
    
    virtual void setAutoUpdate(bool _autoUpdate)
    {
        autoUpdate = _autoUpdate;
    }
    
    virtual void setAutoDraw(bool _autoDraw)
    {
        autoDraw = _autoDraw;
    }
    
    virtual void setPosition(int x, int y)
    {
        rect->x = x;
        rect->y = y;
    }
    
    virtual void setHeight(float _height)
    {
        setDimensions(rect->getWidth(), _height); 
    }
    
    virtual void setWidth(float _width)
    {
        setDimensions(_width, rect->getHeight()); 
    }
    
    virtual void setDimensions(float _width, float _height)
    {
        rect->setWidth(_width);
        rect->setHeight(_height);
        paddedRect->width = rect->width+padding*2;
        paddedRect->height = rect->height+padding*2;
    }

	void setDrawPadding(bool _draw_padded_rect)
	{
		draw_padded_rect = _draw_padded_rect; 
	}

    void setDrawWidgetPadding(bool _draw_padded_rect)
    {
		for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
		{
			(*it)->setDrawPadding(_draw_padded_rect); 
		}
        bDrawWidgetPadding = _draw_padded_rect; 
    }
    
    bool getDrawWidgetPadding()
    {
        return bDrawWidgetPadding;
    }
    
	void setDrawPaddingOutline(bool _draw_padded_rect_outline)
	{
		draw_padded_rect_outline = _draw_padded_rect_outline; 
	}
    
    void setDrawWidgetPaddingOutline(bool _draw_padded_rect_outline)
	{
		for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
		{
			(*it)->setDrawPaddingOutline(_draw_padded_rect_outline); 
		}
        bDrawWidgetPaddingOutline = _draw_padded_rect_outline;
	}

    bool getDrawWidgetPaddingOutline()
    {
        return bDrawWidgetPaddingOutline;
    }
    
    vector<ofxUIWidget*> getWidgets()
    {
        return widgets;
    }
    
    vector<ofxUIWidget*> getWidgetsOfType(ofxWidgetType type)
    {
        vector<ofxUIWidget*> widgetToReturn; 
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
		{
            if((*it)->getKind() == type)
            {
                widgetToReturn.push_back((*it));
            }
		}	 
        return widgetToReturn;                                         
    }
	
	ofEvent<ofxUIEventArgs> newGUIEvent;
	
protected:    
    
    void pushbackWidget(ofxUIWidget *widget, bool addWidgetToFront = false)
    {
        widget->setID(uniqueIDs); 
        uniqueIDs++;

        if(addWidgetToFront)
        {
            vector<ofxUIWidget*>::iterator it;
            it = widgets.begin();
            it = widgets.insert (it,widget);
        }
        else
        {
            widgets.push_back(widget);
        }
        
        widgets_map.insert ( pair<string,ofxUIWidget *>( widget->getName(), widget) );
    }
    
	ofTrueTypeFont *font_large; 	
	ofTrueTypeFont *font_medium; 		
	ofTrueTypeFont *font_small;
 	
	ofxUIEventArgs *GUIevent; 
    int state;
    bool hasSharedResources;
    bool autoDraw;
    bool autoUpdate;
    
    map<string, ofxUIWidget*> widgets_map;
	vector<ofxUIWidget*> widgets;
    map<string, ofxUIWidget*> widgetsAreModal;
	vector<ofxUIWidget*> widgetsWithState;
	ofxUIWidget *lastAdded; 
	ofxUIWidget *activeFocusedWidget; 
	bool enable_highlight_outline; 
	bool enable_highlight_fill;
	bool enabled; 
    int uniqueIDs; 
    bool hasKeyBoard; 
    
    float widgetSpacing;
    float globalCanvasWidth;
    float globalSliderHeight;
    float globalGraphHeight;
    float globalButtonDimension;
    float globalSpacerHeight;
    
    string fontName;

    ofxWidgetPosition widgetPosition;
    ofxWidgetAlignment widgetAlign;
    ofxWidgetFontType widgetFontSize;
    
	ofColor widget_color_back;
	ofColor widget_color_outline;
	ofColor widget_color_outline_highlight;
	ofColor widget_color_fill;
	ofColor widget_color_fill_highlight;
    ofColor widget_color_padded_rect;
	ofColor widget_color_padded_rect_outline;
    
    bool bDrawWidgetPadding;
    bool bDrawWidgetPaddingOutline;
    
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
