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

class ofxUICanvas : public ofxUIWidget, public ofxUIAppCBGlue
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

    ofxUICanvas(ofxUIRectangle r) : ofxUIWidget()
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
        rect = new ofxUIRectangle(0, 0, 316, ofxUIGetHeight());        
        init(46, ofxUIGetHeight());
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
        bTriggerWidgetsUponLoad = true;
        
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
            font_large = new ofxUIFont();
            font_medium = new ofxUIFont();
            font_small = new ofxUIFont();            
        
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
    
    void setTriggerWidgetsUponLoad(bool _bTriggerWidgetsUponLoad)
    {
        bTriggerWidgetsUponLoad = _bTriggerWidgetsUponLoad;
    }
    
    bool getTriggerWidgetsUponLoad()
    {
        return bTriggerWidgetsUponLoad;
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
                if(bTriggerWidgetsUponLoad){
                    triggerEvent(widget);   
                }
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
                pad->setValue(ofxUIVec3f(valueX, valueY));
            }
                break;
                
            case OFX_UI_WIDGET_TEXTINPUT:
            {
                ofxUITextInput *textInput = (ofxUITextInput *) widget; 
                string value = XML->getValue("Value", textInput->getTextString(), 0);             
                textInput->setTextString(value);
                textInput->setTriggerType(OFX_UI_TEXTINPUT_ON_LOAD); 
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
                
                imageSampler->setValue(ofxUIVec2f(valueX, valueY));
                imageSampler->setColor(ofxUIColor(r,g,b,a));
            }
                break;
                
            default:
                break;
        }        
    }

#endif
	 
    ofxUIFont *getFontLarge()
    {
        return font_large;
    }    
    
    ofxUIFont *getFontMedium()
    {
        return font_medium;
    }

    ofxUIFont *getFontSmall()
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
    
    void setFontSize(ofxUIWidgetFontType _kind, int _size, int _resolution = OFX_UI_FONT_RESOLUTION)
    {
        switch(_kind)
        {
            case OFX_UI_FONT_LARGE:
                if(font_large != NULL)
                {
                    delete font_large;          
                }
                font_large = new ofxUIFont(); 
                font_large->loadFont(fontName,_size,true, true, false, 0.0,_resolution); 				            
                break; 

            case OFX_UI_FONT_MEDIUM:
                if(font_medium != NULL)
                {
                    delete font_medium;          
                }
                font_medium = new ofxUIFont(); 
                font_medium->loadFont(fontName,_size,true, true, false, 0.0,_resolution); 				                            
                break; 

            case OFX_UI_FONT_SMALL:
                if(font_small != NULL)
                {
                    delete font_small;          
                }
                font_small = new ofxUIFont(); 
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
            EnableCallbacks();
        }
	}
	
	void disable()
	{
        if(isEnabled())
        {                    
            enabled = false;
            visible = false;
            DisableCallbacks();
        }
    }
	    
    virtual void update()
    {    
		for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
		{
			(*it)->update(); 	
		}		
    }
     
    virtual void draw()
    {		
        ofxUIPushStyle();
		
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);

        glEnable(GL_BLEND);
#ifndef OFX_UI_TARGET_TOUCH
        glBlendEquation(GL_FUNC_ADD);
#endif
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        ofxUISetRectMode(OFX_UI_RECTMODE_CORNER);
        ofxUISetLineWidth(1.0);
        
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
        ofxUIPopStyle();
    }
    
    void exit()
    {

    }	
        
#ifdef OFX_UI_TARGET_TOUCH 
	
    virtual void canvasTouchDown(float x, float y, int id)
    {
        if(rect->inside(x, y))
        {
			for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
			{
				if((*it)->isVisible())	(*it)->touchDown(x, y, id);
			}
		}
        else
        {
            for (map<string, ofxUIWidget*>::iterator it=widgetsAreModal.begin() ; it != widgetsAreModal.end(); it++ )
            {
                if((*it).second->isVisible()) (*it).second->touchDown(x, y, id);
            }
        }
    }
    
    virtual void canvasTouchMoved(float x, float y, int id)
    {
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible())	(*it)->touchMoved(x, y, id);
        }
    }
    
    virtual void canvasTouchUp(float x, float y, int id)
	{
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible())	(*it)->touchUp(x, y, id);
        }
    }
    
    virtual void canvasTouchDoubleTap(float x, float y, int id)
    {
        if(rect->inside(x, y))
        {
			for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
			{
				if((*it)->isVisible())	(*it)->touchDoubleTap(x, y, id);
            }
		}
        else
        {
            for (map<string, ofxUIWidget*>::iterator it=widgetsAreModal.begin() ; it != widgetsAreModal.end(); it++ )
            {
                if((*it).second->isVisible()) (*it).second->touchDoubleTap(x, y, id);
            }
        }
    }
    
    virtual void canvasTouchCancelled(float x, float y, int id)
    {
        if(rect->inside(x, y))
        {
        	for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
			{
				if((*it)->isVisible())	(*it)->touchCancelled(x, y, id);
			}
		}
        else
        {
            for (map<string, ofxUIWidget*>::iterator it=widgetsAreModal.begin() ; it != widgetsAreModal.end(); it++ )
            {
                if((*it).second->isVisible()) (*it).second->touchCancelled(x, y, id);
            }
        }
    }
    
    virtual void touchDown(float x, float y, int id)
	{
        canvasTouchDown(x, y, id);
	}
    
	virtual void touchMoved(float x, float y, int id)
	{
        canvasTouchMoved(x, y, id);
	}
    
	virtual void touchUp(float x, float y, int id)
	{
        canvasTouchUp(x, y, id);
	}
    
	virtual void touchDoubleTap(float x, float y, int id)
	{
        canvasTouchDoubleTap(x, y, id);
	}
        
	virtual void touchCancelled(float x, float y, int id)
	{		
        canvasTouchCancelled(x, y, id);
	}
	   
#else	
    
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
    
    virtual void windowResized(int w, int h) 
    {
		for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
		{
			(*it)->windowResized(w, h); 
		}
    }
    
#endif	

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
        lastAdded = NULL; 
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
        multimap<string, ofxUIWidget*>::iterator it;
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
                                   ofxUIWidgetPosition position = OFX_UI_WIDGET_POSITION_DOWN,
                                   ofxUIWidgetAlignment align = OFX_UI_ALIGN_LEFT,
                                   bool reAdd = false)
    {
        if(!reAdd) addWidget(widget);
        ofxUIRectangle *widgetRect = widget->getRect();
        ofxUIRectangle *widgetPaddingRect = widget->getPaddingRect();        
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
    
	ofxUIWidget* addWidgetDown(ofxUIWidget *widget, ofxUIWidgetAlignment align = OFX_UI_ALIGN_LEFT, bool reAdd = false)
	{
        return addWidgetPosition(widget, OFX_UI_WIDGET_POSITION_DOWN, align, reAdd);
	}
    
	ofxUIWidget* addWidgetUp(ofxUIWidget *widget, ofxUIWidgetAlignment align = OFX_UI_ALIGN_LEFT, bool reAdd = false)
	{
        return addWidgetPosition(widget, OFX_UI_WIDGET_POSITION_UP, align, reAdd);
	}    
    
	ofxUIWidget* addWidgetRight(ofxUIWidget *widget, ofxUIWidgetAlignment align = OFX_UI_ALIGN_FREE, bool reAdd = false)
	{
        return addWidgetPosition(widget, OFX_UI_WIDGET_POSITION_RIGHT, align, reAdd);
	}
    
    ofxUIWidget* addWidgetLeft(ofxUIWidget *widget, ofxUIWidgetAlignment align = OFX_UI_ALIGN_FREE, bool reAdd = false)
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

    ofxUI2DPad* add2DPad(string _name, ofxUIVec3f _rangeX, ofxUIVec3f _rangeY, ofxUIVec3f _value)
    {
        float dim = rect->getWidth()-widgetSpacing*2; 
        ofxUI2DPad* widget = new ofxUI2DPad(_name, _rangeX, _rangeY, _value, dim, dim, 0, 0);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    
    ofxUI2DPad* add2DPad(string _name, ofxUIVec3f _rangeX, ofxUIVec3f _rangeY, ofxUIVec3f _value, float w, float h, float x = 0, float y = 0)
    {
        ofxUI2DPad* widget = new ofxUI2DPad(_name, _rangeX, _rangeY, _value, w, h, x, y);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUI2DPad* add2DPad(string _name, ofxUIVec3f _rangeX, ofxUIVec3f _rangeY, ofxUIVec3f *_value)
    {
        float dim = rect->getWidth()-widgetSpacing*2; 
        ofxUI2DPad* widget = new ofxUI2DPad(_name, _rangeX, _rangeY, _value, dim, dim, 0, 0);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUI2DPad* add2DPad(string _name, ofxUIVec3f _rangeX, ofxUIVec3f _rangeY, ofxUIVec3f *_value, float w, float h, float x = 0, float y = 0)
    {
        ofxUI2DPad* widget = new ofxUI2DPad(_name, _rangeX, _rangeY, _value, w, h, x, y);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUITextInput* addTextInput(string _name, string _textstring, int _size = OFX_UI_FONT_SMALL)
    {
        ofxUITextInput* widget = new ofxUITextInput(_name, _textstring, rect->getWidth()-widgetSpacing*2, _size);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUITextInput* addTextInput(string _name, string _textstring, float w, float h = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
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

    ofxUIBaseDraws *addBaseDraws(string _name, ofBaseDraws *_base, float _w, float _h, bool _showLabel = false)
    {
        ofxUIBaseDraws* widget = new ofxUIBaseDraws(_w, _h, _base, _name, _showLabel);
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }
    
    ofxUIBaseDraws *addBaseDraws(string _name, ofBaseDraws *_base, bool _showLabel = false)
    {
        float _w = rect->getWidth()-widgetSpacing*2;
        float _h = _w*(float)_base->getHeight()/(float)_base->getWidth();
        ofxUIBaseDraws* widget = new ofxUIBaseDraws(_w, _h, _base, _name, _showLabel);
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
    
    
    ofxUI2DGraph *add2DGraph(string _name, ofxUIVec2f _rangeX, ofxUIVec2f _rangeY, int _bufferSize, float * _xValues, float * _yValues)
    {
        ofxUI2DGraph* widget = new ofxUI2DGraph(_name, _rangeX, _rangeY, _bufferSize, _xValues, _yValues, rect->getWidth()-widgetSpacing*2, rect->getWidth()-widgetSpacing*2); 
        addWidgetPosition(widget, widgetPosition, widgetAlign);
        return widget;
    }

    ofxUI2DGraph *add2DGraph(string _name, ofxUIVec2f _rangeX, ofxUIVec2f _rangeY, int _bufferSize, float * _xValues, float * _yValues, float _w, float _h, float _x = 0, float _y = 0)
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
		
	void setWidgetPosition(ofxUIWidgetPosition _position, int _align = -1)
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
            widgetAlign = (ofxUIWidgetAlignment)_align;
        }
	}
	
    void setWidgetFontSize(ofxUIWidgetFontType _widgetFontSize)
    {
        widgetFontSize = _widgetFontSize;
    }
    
    ofxUIWidgetPosition getWidgetPosition()
    {
        return widgetPosition;
    }
    
    ofxUIWidgetFontType getWidgetFontSize()
    {
        return widgetFontSize; 
    }
    
	void triggerEvent(ofxUIWidget *child)
	{
        checkForKeyFocus(child);
        GUIevent->widget = child; 		
        ofNotifyEvent(newGUIEvent,*GUIevent,this);
	}
	    
    void setUIColors(ofxUIColor &cb, ofxUIColor &co, ofxUIColor &coh, ofxUIColor &cf, ofxUIColor &cfh, ofxUIColor &cp, ofxUIColor &cpo)
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
                ofxUIColor cb = OFX_UI_COLOR_BACK; 
                ofxUIColor co = OFX_UI_COLOR_OUTLINE; 
                ofxUIColor coh = OFX_UI_COLOR_OUTLINE_HIGHLIGHT;
                ofxUIColor cf = OFX_UI_COLOR_FILL; 
                ofxUIColor cfh = OFX_UI_COLOR_FILL_HIGHLIGHT;
                ofxUIColor cp = OFX_UI_COLOR_PADDED;
                ofxUIColor cpo = OFX_UI_COLOR_PADDED_OUTLINE;
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_HACKER:
            {
                ofxUIColor cb = ofxUIColor( 0.294118*255.0, 0*255.0, 0.0588235*255.0, 0.196078*255.0 );
                ofxUIColor co = ofxUIColor( 0.254902*255.0, 0.239216*255.0, 0.239216*255.0, 0.392157*255.0 );
                ofxUIColor coh = ofxUIColor( 0.294118*255.0, 0*255.0, 0.0588235*255.0, 0.784314*255.0 );
                ofxUIColor cf = ofxUIColor( 0.784314*255.0, 1*255.0, 0*255.0, 0.784314*255.0 );
                ofxUIColor cfh = ofxUIColor( 0.980392*255.0, 0.00784314*255.0, 0.235294*255.0, 1*255.0 );
                ofxUIColor cp = ofxUIColor( 0.0156863*255.0, 0*255.0, 0.0156863*255.0, 0.392157*255.0 );
                ofxUIColor cpo = ofxUIColor( 0.254902*255.0, 0.239216*255.0, 0.239216*255.0, 0.784314*255.0 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
                
            case OFX_UI_THEME_HIPSTER:
            {
                ofxUIColor cb = ofxUIColor( 0.607843*255.0, 0.6*255.0, 0.509804*255.0, 0.196078*255.0 );
                ofxUIColor co = ofxUIColor( 0.231373*255.0, 0.392157*255.0, 0.501961*255.0, 0.392157*255.0 );
                ofxUIColor coh = ofxUIColor( 0.607843*255.0, 0.6*255.0, 0.509804*255.0, 0.784314*255.0 );
                ofxUIColor cf = ofxUIColor( 1*255.0, 0.52549*255.0, 0.0666667*255.0, 0.784314*255.0 );
                ofxUIColor cfh = ofxUIColor( 0.0313725*255.0, 0.101961*255.0, 0.188235*255.0, 1*255.0 );
                ofxUIColor cp = ofxUIColor( 0.196078*255.0, 0.25098*255.0, 0.352941*255.0, 0.392157*255.0 );
                ofxUIColor cpo = ofxUIColor( 0.231373*255.0, 0.392157*255.0, 0.501961*255.0, 0.784314*255.0 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_DIETER:
            {
                ofxUIColor cb = ofxUIColor( 0.803922*255.0, 0.741176*255.0, 0.682353*255.0, 0.196078*255.0 );
                ofxUIColor co = ofxUIColor( 0.478431*255.0, 0.356863*255.0, 0.243137*255.0, 0.392157*255.0 );
                ofxUIColor coh = ofxUIColor( 0.803922*255.0, 0.741176*255.0, 0.682353*255.0, 0.784314*255.0 );
                ofxUIColor cf = ofxUIColor( 0.980392*255.0, 0.294118*255.0, 0*255.0, 0.784314*255.0 );
                ofxUIColor cfh = ofxUIColor( 0.980392*255.0, 0.980392*255.0, 0.980392*255.0, 1*255.0 );
                ofxUIColor cp = ofxUIColor( 0.121569*255.0, 0.121569*255.0, 0.121569*255.0, 0.392157*255.0 );
                ofxUIColor cpo = ofxUIColor( 0.478431*255.0, 0.356863*255.0, 0.243137*255.0, 0.784314*255.0 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_BARBIE:
            {
                ofxUIColor cb = ofxUIColor( 0.92549*255.0, 0*255.0, 0.54902*255.0, 0.196078*255.0 );
                ofxUIColor co = ofxUIColor( 0*255.0, 0*255.0, 0*255.0, 0.392157*255.0 );
                ofxUIColor coh = ofxUIColor( 0*255.0, 0.678431*255.0, 0.937255*255.0, 0.784314*255.0 );
                ofxUIColor cf = ofxUIColor( 0.92549*255.0, 0*255.0, 0.54902*255.0, 0.784314*255.0 );
                ofxUIColor cfh = ofxUIColor( 1*255.0, 0.94902*255.0, 0*255.0, 1*255.0 );
                ofxUIColor cp = ofxUIColor( 0*255.0, 0*255.0, 0*255.0, 0.392157*255.0 );
                ofxUIColor cpo = ofxUIColor( 0*255.0, 0.678431*255.0, 0.937255*255.0, 0.784314*255.0 ); 
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_WINDOWS:
            {
                ofxUIColor cb = ofxUIColor( 0.0470588*255.0, 0.0588235*255.0, 0.4*255.0, 0.196078*255.0 );
                ofxUIColor co = ofxUIColor( 0.0431373*255.0, 0.0627451*255.0, 0.54902*255.0, 0.392157*255.0 );
                ofxUIColor coh = ofxUIColor( 0.0470588*255.0, 0.0588235*255.0, 0.4*255.0, 0.784314*255.0 );
                ofxUIColor cf = ofxUIColor( 0.054902*255.0, 0.305882*255.0, 0.678431*255.0, 0.784314*255.0 );
                ofxUIColor cfh = ofxUIColor( 0.0627451*255.0, 0.498039*255.0, 0.788235*255.0, 1*255.0 );
                ofxUIColor cp = ofxUIColor( 0.027451*255.0, 0.0352941*255.0, 0.239216*255.0, 0.392157*255.0 );
                ofxUIColor cpo = ofxUIColor( 0.0431373*255.0, 0.0627451*255.0, 0.54902*255.0, 0.784314*255.0 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MACOSX:
            {
                ofxUIColor cb = ofxUIColor( 0*255.0, 0.678431*255.0, 0.937255*255.0, 0.196078*255.0 );
                ofxUIColor co = ofxUIColor( 1*255.0, 0.94902*255.0, 0*255.0, 0.392157*255.0 );
                ofxUIColor coh = ofxUIColor( 0*255.0, 0*255.0, 0*255.0, 0.784314*255.0 );
                ofxUIColor cf = ofxUIColor( 0*255.0, 0.678431*255.0, 0.937255*255.0, 0.784314*255.0 );
                ofxUIColor cfh = ofxUIColor( 0.92549*255.0, 0*255.0, 0.54902*255.0, 1*255.0 );
                ofxUIColor cp = ofxUIColor( 1*255.0, 0.94902*255.0, 0*255.0, 0.392157*255.0 );
                ofxUIColor cpo = ofxUIColor( 0*255.0, 0*255.0, 0*255.0, 0.784314*255.0 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_ZOOLANDER:
            {
                ofxUIColor cb = ofxUIColor( 0.160784*255.0, 0.133333*255.0, 0.121569*255.0, 0.196078*255.0 );
                ofxUIColor co = ofxUIColor( 0.0745098*255.0, 0.454902*255.0, 0.490196*255.0, 0.392157*255.0 );
                ofxUIColor coh = ofxUIColor( 0.160784*255.0, 0.133333*255.0, 0.121569*255.0, 0.784314*255.0 );
                ofxUIColor cf = ofxUIColor( 0.988235*255.0, 0.207843*255.0, 0.298039*255.0, 0.784314*255.0 );
                ofxUIColor cfh = ofxUIColor( 0.988235*255.0, 0.968627*255.0, 0.772549*255.0, 1*255.0 );
                ofxUIColor cp = ofxUIColor( 0.0392157*255.0, 0.74902*255.0, 0.737255*255.0, 0.392157*255.0 );
                ofxUIColor cpo = ofxUIColor( 0.0745098*255.0, 0.454902*255.0, 0.490196*255.0, 0.784314*255.0 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_VEGAN2:
            {
                ofxUIColor cb = ofxUIColor( 0.745098*255.0, 0.94902*255.0, 0.00784314*255.0, 0.196078*255.0 );
                ofxUIColor co = ofxUIColor( 0.533333*255.0, 0.768627*255.0, 0.145098*255.0, 0.392157*255.0 );
                ofxUIColor coh = ofxUIColor( 0.745098*255.0, 0.94902*255.0, 0.00784314*255.0, 0.784314*255.0 );
                ofxUIColor cf = ofxUIColor( 0.917647*255.0, 0.992157*255.0, 0.901961*255.0, 0.784314*255.0 );
                ofxUIColor cfh = ofxUIColor( 0.105882*255.0, 0.403922*255.0, 0.419608*255.0, 1*255.0 );
                ofxUIColor cp = ofxUIColor( 0.317647*255.0, 0.584314*255.0, 0.282353*255.0, 0.392157*255.0 );
                ofxUIColor cpo = ofxUIColor( 0.533333*255.0, 0.768627*255.0, 0.145098*255.0, 0.784314*255.0 );                                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_BERLIN:
            {
                ofxUIColor cb = ofxUIColor( 0.6*255.0, 0.894118*255.0, 1*255.0, 0.196078*255.0 );
                ofxUIColor co = ofxUIColor( 0.294118*255.0, 0.34902*255.0, 0.419608*255.0, 0.392157*255.0 );
                ofxUIColor coh = ofxUIColor( 0.6*255.0, 0.894118*255.0, 1*255.0, 0.784314*255.0 );
                ofxUIColor cf = ofxUIColor( 0.968627*255.0, 0.309804*255.0, 0.309804*255.0, 0.784314*255.0 );
                ofxUIColor cfh = ofxUIColor( 1*255.0, 0.231373*255.0, 0.231373*255.0, 1*255.0 );
                ofxUIColor cp = ofxUIColor( 0.105882*255.0, 0.12549*255.0, 0.14902*255.0, 0.392157*255.0 );
                ofxUIColor cpo = ofxUIColor( 0.294118*255.0, 0.34902*255.0, 0.419608*255.0, 0.784314*255.0 ); 
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_METALGEAR:
            {
                ofxUIColor cb = ofxUIColor( 51, 44, 44, 75 );
                ofxUIColor co = ofxUIColor( 25, 26, 36, 100 );
                ofxUIColor coh = ofxUIColor( 51, 44, 44, 200 );
                ofxUIColor cf = ofxUIColor( 250, 101, 87, 200 );
                ofxUIColor cfh = ofxUIColor( 255, 255, 255, 255 );
                ofxUIColor cp = ofxUIColor( 0, 0, 0, 100 );
                ofxUIColor cpo = ofxUIColor( 25, 26, 36, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_TEALLIME:
            {
                ofxUIColor cb = ofxUIColor( 27, 103, 107, 75 );
                ofxUIColor co = ofxUIColor( 234, 253, 230, 100 );
                ofxUIColor coh = ofxUIColor( 27, 103, 107, 200 );
                ofxUIColor cf = ofxUIColor( 81, 149, 72, 200 );
                ofxUIColor cfh = ofxUIColor( 136, 196, 37, 255 );
                ofxUIColor cp = ofxUIColor( 190, 242, 2, 100 );
                ofxUIColor cpo = ofxUIColor( 234, 253, 230, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_VEGAN:
            {
                ofxUIColor cb = ofxUIColor( 81, 149, 72, 75 );
                ofxUIColor co = ofxUIColor( 27, 103, 107, 100 );
                ofxUIColor coh = ofxUIColor( 81, 149, 72, 200 );
                ofxUIColor cf = ofxUIColor( 136, 196, 37, 200 );
                ofxUIColor cfh = ofxUIColor( 190, 242, 2, 255 );
                ofxUIColor cp = ofxUIColor( 234, 253, 230, 100 );
                ofxUIColor cpo = ofxUIColor( 27, 103, 107, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_RUSTIC:
            {
                ofxUIColor cb = ofxUIColor( 196, 182, 109, 75 );
                ofxUIColor co = ofxUIColor( 247, 109, 60, 100 );
                ofxUIColor coh = ofxUIColor( 196, 182, 109, 200 );
                ofxUIColor cf = ofxUIColor( 213, 39, 5, 200 );
                ofxUIColor cfh = ofxUIColor( 240, 211, 119, 255 );
                ofxUIColor cp = ofxUIColor( 243, 232, 228, 100 );
                ofxUIColor cpo = ofxUIColor( 247, 109, 60, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MIDNIGHT:
            {
                ofxUIColor cb = ofxUIColor( 11, 72, 107, 75 );
                ofxUIColor co = ofxUIColor( 207, 240, 158, 100 );
                ofxUIColor coh = ofxUIColor( 11, 72, 107, 200 );
                ofxUIColor cf = ofxUIColor( 59, 134, 134, 200 );
                ofxUIColor cfh = ofxUIColor( 121, 189, 154, 255 );
                ofxUIColor cp = ofxUIColor( 168, 219, 168, 100 );
                ofxUIColor cpo = ofxUIColor( 207, 240, 158, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MINBLUE:
            {
                ofxUIColor cb = ofxUIColor( 254, 249, 240, 75 );
                ofxUIColor co = ofxUIColor( 176, 248, 255, 100 );
                ofxUIColor coh = ofxUIColor( 254, 249, 240, 200 );
                ofxUIColor cf = ofxUIColor( 0, 188, 209, 200 );
                ofxUIColor cfh = ofxUIColor( 118, 211, 222, 255 );
                ofxUIColor cp = ofxUIColor( 174, 232, 251, 100 );
                ofxUIColor cpo = ofxUIColor( 176, 248, 255, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_LIMESTONE:
            {
                ofxUIColor cb = ofxUIColor( 108, 144, 134, 75 );
                ofxUIColor co = ofxUIColor( 252, 84, 99, 100 );
                ofxUIColor coh = ofxUIColor( 108, 144, 134, 200 );
                ofxUIColor cf = ofxUIColor( 169, 204, 24, 200 );
                ofxUIColor cfh = ofxUIColor( 207, 73, 108, 255 );
                ofxUIColor cp = ofxUIColor( 235, 234, 188, 100 );
                ofxUIColor cpo = ofxUIColor( 252, 84, 99, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;                  
                
            case OFX_UI_THEME_SPEARMINT:
            {
                ofxUIColor cb = ofxUIColor( 25, 140, 9, 75 );
                ofxUIColor co = ofxUIColor( 255, 197, 95, 100 );
                ofxUIColor coh = ofxUIColor( 25, 140, 9, 200 );
                ofxUIColor cf = ofxUIColor( 220, 250, 250, 200 );
                ofxUIColor cfh = ofxUIColor( 239, 88, 141, 255 );
                ofxUIColor cp = ofxUIColor( 254, 169, 18, 100 );
                ofxUIColor cpo = ofxUIColor( 255, 197, 95, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;                  
                
            case OFX_UI_THEME_MINPINK:
            {
                ofxUIColor cb = ofxUIColor( 220, 250, 250, 75 );
                ofxUIColor co = ofxUIColor( 25, 140, 9, 100 );
                ofxUIColor coh = ofxUIColor( 220, 250, 250, 200 );
                ofxUIColor cf = ofxUIColor( 239, 88, 141, 200 );
                ofxUIColor cfh = ofxUIColor( 254, 169, 18, 255 );
                ofxUIColor cp = ofxUIColor( 255, 197, 95, 100 );
                ofxUIColor cpo = ofxUIColor( 25, 140, 9, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_PEPTOBISMOL:
            {
                ofxUIColor cb = ofxUIColor( 223, 21, 26, 75 );
                ofxUIColor co = ofxUIColor( 0, 218, 60, 100 );
                ofxUIColor coh = ofxUIColor( 223, 21, 26, 200 );
                ofxUIColor cf = ofxUIColor( 244, 243, 40, 200 );
                ofxUIColor cfh = ofxUIColor( 253, 134, 3, 255 );
                ofxUIColor cp = ofxUIColor( 0, 203, 231, 100 );
                ofxUIColor cpo = ofxUIColor( 0, 218, 60, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_BILEBLUE:
            {
                ofxUIColor cb = ofxUIColor( 253, 134, 3, 75 );
                ofxUIColor co = ofxUIColor( 244, 243, 40, 100 );
                ofxUIColor coh = ofxUIColor( 253, 134, 3, 200 );
                ofxUIColor cf = ofxUIColor( 0, 203, 231, 200 );
                ofxUIColor cfh = ofxUIColor( 0, 218, 60, 255 );
                ofxUIColor cp = ofxUIColor( 223, 21, 26, 100 );
                ofxUIColor cpo = ofxUIColor( 244, 243, 40, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_COOLCLAY:
            {
                ofxUIColor cb = ofxUIColor( 153, 228, 255, 75 );
                ofxUIColor co = ofxUIColor( 75, 89, 107, 100 );
                ofxUIColor coh = ofxUIColor( 153, 228, 255, 200 );
                ofxUIColor cf = ofxUIColor( 247, 79, 79, 200 );
                ofxUIColor cfh = ofxUIColor( 255, 59, 59, 255 );
                ofxUIColor cp = ofxUIColor( 27, 32, 38, 100 );
                ofxUIColor cpo = ofxUIColor( 75, 89, 107, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_BLUEBLUE:
            {
                ofxUIColor cb = ofxUIColor( 0, 173, 239, 75 );
                ofxUIColor co = ofxUIColor( 255, 242, 0, 100 );
                ofxUIColor coh = ofxUIColor( 0, 0, 0, 200 );
                ofxUIColor cf = ofxUIColor( 0, 173, 239, 200 );
                ofxUIColor cfh = ofxUIColor( 236, 0, 140, 255 );
                ofxUIColor cp = ofxUIColor( 255, 242, 0, 100 );
                ofxUIColor cpo = ofxUIColor( 0, 0, 0, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_PINKPANTHER:
            {
                ofxUIColor cb = ofxUIColor( 236, 0, 140, 75 );
                ofxUIColor co = ofxUIColor( 0, 0, 0, 100 );
                ofxUIColor coh = ofxUIColor( 0, 173, 239, 200 );
                ofxUIColor cf = ofxUIColor( 236, 0, 140, 200 );
                ofxUIColor cfh = ofxUIColor( 255, 242, 0, 255 );
                ofxUIColor cp = ofxUIColor( 0, 0, 0, 100 );
                ofxUIColor cpo = ofxUIColor( 0, 173, 239, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MAROON:
            {
                ofxUIColor cb = ofxUIColor( 101, 150, 158, 75 );
                ofxUIColor co = ofxUIColor( 219, 217, 210, 100 );
                ofxUIColor coh = ofxUIColor( 101, 150, 158, 200 );
                ofxUIColor cf = ofxUIColor( 171, 20, 44, 200 );
                ofxUIColor cfh = ofxUIColor( 189, 219, 222, 255 );
                ofxUIColor cp = ofxUIColor( 205, 212, 108, 100 );
                ofxUIColor cpo = ofxUIColor( 219, 217, 210, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_PINKLATTE:
            {
                ofxUIColor cb = ofxUIColor( 218, 216, 167, 75 );
                ofxUIColor co = ofxUIColor( 127, 199, 175, 100 );
                ofxUIColor coh = ofxUIColor( 218, 216, 167, 200 );
                ofxUIColor cf = ofxUIColor( 255, 61, 127, 200 );
                ofxUIColor cfh = ofxUIColor( 255, 158, 157, 255 );
                ofxUIColor cp = ofxUIColor( 63, 184, 175, 100 );
                ofxUIColor cpo = ofxUIColor( 127, 199, 175, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MINGREEN:
            {
                ofxUIColor cb = ofxUIColor( 255, 255, 255, 75 );
                ofxUIColor co = ofxUIColor( 242, 230, 194, 100 );
                ofxUIColor coh = ofxUIColor( 255, 255, 255, 200 );
                ofxUIColor cf = ofxUIColor( 111, 191, 162, 200 );
                ofxUIColor cfh = ofxUIColor( 191, 184, 174, 255 );
                ofxUIColor cp = ofxUIColor( 242, 199, 119, 100 );
                ofxUIColor cpo = ofxUIColor( 242, 230, 194, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_HELLOYELLOW:
            {
                ofxUIColor cb = ofxUIColor( 255, 211, 0, 75 );
                ofxUIColor co = ofxUIColor( 74, 186, 176, 100 );
                ofxUIColor coh = ofxUIColor( 152, 33, 0, 200 );
                ofxUIColor cf = ofxUIColor( 255, 211, 0, 200 );
                ofxUIColor cfh = ofxUIColor( 255, 245, 158, 255 );
                ofxUIColor cp = ofxUIColor( 74, 186, 176, 100 );
                ofxUIColor cpo = ofxUIColor( 152, 33, 0, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_TEALTEAL:
            {
                ofxUIColor cb = ofxUIColor( 74, 186, 176, 75 );
                ofxUIColor co = ofxUIColor( 255, 211, 0, 100 );
                ofxUIColor coh = ofxUIColor( 255, 245, 158, 200 );
                ofxUIColor cf = ofxUIColor( 74, 186, 176, 200 );
                ofxUIColor cfh = ofxUIColor( 152, 33, 0, 255 );
                ofxUIColor cp = ofxUIColor( 255, 211, 0, 100 );
                ofxUIColor cpo = ofxUIColor( 255, 245, 158, 200 );            
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_RUSTICORANGE:
            {
                ofxUIColor cb = ofxUIColor( 107, 85, 48, 75 );
                ofxUIColor co = ofxUIColor( 49, 48, 66, 100 );
                ofxUIColor coh = ofxUIColor( 107, 85, 48, 200 );
                ofxUIColor cf = ofxUIColor( 255, 109, 36, 200 );
                ofxUIColor cfh = ofxUIColor( 255, 235, 107, 255 );
                ofxUIColor cp = ofxUIColor( 42, 135, 50, 100 );
                ofxUIColor cpo = ofxUIColor( 49, 48, 66, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_TEALSALMON:
            {
                ofxUIColor cb = ofxUIColor( 78, 133, 136, 75 );
                ofxUIColor co = ofxUIColor( 56, 69, 59, 100 );
                ofxUIColor coh = ofxUIColor( 78, 133, 136, 200 );
                ofxUIColor cf = ofxUIColor( 255, 70, 84, 200 );
                ofxUIColor cfh = ofxUIColor( 255, 213, 106, 255 );
                ofxUIColor cp = ofxUIColor( 255, 254, 211, 100 );
                ofxUIColor cpo = ofxUIColor( 56, 69, 59, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_CITRUSBLUE:
            {
                ofxUIColor cb = ofxUIColor( 57, 142, 182, 75 );
                ofxUIColor co = ofxUIColor( 34, 104, 136, 100 );
                ofxUIColor coh = ofxUIColor( 57, 142, 182, 200 );
                ofxUIColor cf = ofxUIColor( 255, 162, 0, 200 );
                ofxUIColor cfh = ofxUIColor( 255, 214, 0, 255 );
                ofxUIColor cp = ofxUIColor( 255, 245, 0, 100 );
                ofxUIColor cpo = ofxUIColor( 34, 104, 136, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_LIMEPURPLE:
            {
                ofxUIColor cb = ofxUIColor( 87, 54, 255, 75 );
                ofxUIColor co = ofxUIColor( 38, 38, 38, 100 );
                ofxUIColor coh = ofxUIColor( 87, 54, 255, 200 );
                ofxUIColor cf = ofxUIColor( 231, 255, 54, 200 );
                ofxUIColor cfh = ofxUIColor( 255, 54, 111, 255 );
                ofxUIColor cp = ofxUIColor( 35, 116, 222, 100 );
                ofxUIColor cpo = ofxUIColor( 38, 38, 38, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_LIMESTONE2:
            {
                ofxUIColor cb = ofxUIColor( 101, 98, 115, 75 );
                ofxUIColor co = ofxUIColor( 89, 186, 169, 100 );
                ofxUIColor coh = ofxUIColor( 101, 98, 115, 200 );
                ofxUIColor cf = ofxUIColor( 216, 241, 113, 200 );
                ofxUIColor cfh = ofxUIColor( 252, 255, 217, 255 );
                ofxUIColor cp = ofxUIColor( 64, 18, 44, 100 );
                ofxUIColor cpo = ofxUIColor( 89, 186, 169, 200 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_COOLPURPLE:
            {
                ofxUIColor cb = ofxUIColor( 38, 137, 233, 75 );
                ofxUIColor co = ofxUIColor( 11, 246, 147, 100 );
                ofxUIColor coh = ofxUIColor( 38, 137, 233, 200 );
                ofxUIColor cf = ofxUIColor( 233, 26, 157, 200 );
                ofxUIColor cfh = ofxUIColor( 246, 182, 11, 255 );
                ofxUIColor cp = ofxUIColor( 246, 242, 11, 100 );
                ofxUIColor cpo = ofxUIColor( 11, 246, 147, 200 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_GRAYRED:
            {
                ofxUIColor cb = ofxUIColor( 41, 34, 31, 75 );
                ofxUIColor co = ofxUIColor( 19, 116, 125, 100 );
                ofxUIColor coh = ofxUIColor( 41, 34, 31, 200 );
                ofxUIColor cf = ofxUIColor( 252, 53, 76, 200 );
                ofxUIColor cfh = ofxUIColor( 252, 247, 197, 255 );
                ofxUIColor cp = ofxUIColor( 10, 191, 188, 100 );
                ofxUIColor cpo = ofxUIColor( 19, 116, 125, 200 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_METALGEAR2:
            {
                ofxUIColor cb = ofxUIColor( 205, 189, 174, 75 );
                ofxUIColor co = ofxUIColor( 122, 91, 62, 100 );
                ofxUIColor coh = ofxUIColor( 205, 189, 174, 200 );
                ofxUIColor cf = ofxUIColor( 250, 75, 0, 200 );
                ofxUIColor cfh = ofxUIColor( 250, 250, 250, 255 );
                ofxUIColor cp = ofxUIColor( 31, 31, 31, 100 );
                ofxUIColor cpo = ofxUIColor( 122, 91, 62, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_LIGHTPINK:
            {
                ofxUIColor cb = ofxUIColor( 158, 30, 76, 75 );
                ofxUIColor co = ofxUIColor( 143, 143, 143, 100 );
                ofxUIColor coh = ofxUIColor( 158, 30, 76, 200 );
                ofxUIColor cf = ofxUIColor( 236, 236, 236, 200 );
                ofxUIColor cfh = ofxUIColor( 255, 17, 104, 255 );
                ofxUIColor cp = ofxUIColor( 37, 2, 15, 100 );
                ofxUIColor cpo = ofxUIColor( 143, 143, 143, 200 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MINPINK2:
            {
                ofxUIColor cb = ofxUIColor( 236, 236, 236, 75 );
                ofxUIColor co = ofxUIColor( 158, 30, 76, 100 );
                ofxUIColor coh = ofxUIColor( 236, 236, 236, 200 );
                ofxUIColor cf = ofxUIColor( 255, 17, 104, 200 );
                ofxUIColor cfh = ofxUIColor( 37, 2, 15, 255 );
                ofxUIColor cp = ofxUIColor( 143, 143, 143, 100 );
                ofxUIColor cpo = ofxUIColor( 158, 30, 76, 200 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MAXPINK:
            {
                ofxUIColor cb = ofxUIColor( 255, 20, 87, 75 );
                ofxUIColor co = ofxUIColor( 10, 10, 10, 100 );
                ofxUIColor coh = ofxUIColor( 227, 246, 255, 200 );
                ofxUIColor cf = ofxUIColor( 255, 20, 87, 200 );
                ofxUIColor cfh = ofxUIColor( 255, 216, 125, 255 );
                ofxUIColor cp = ofxUIColor( 10, 10, 10, 100 );
                ofxUIColor cpo = ofxUIColor( 227, 246, 255, 200 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MINYELLOW:
            {
                ofxUIColor cb = ofxUIColor( 229, 228, 218, 75 );
                ofxUIColor co = ofxUIColor( 216, 210, 153, 100 );
                ofxUIColor coh = ofxUIColor( 229, 228, 218, 200 );
                ofxUIColor cf = ofxUIColor( 245, 224, 56, 200 );
                ofxUIColor cfh = ofxUIColor( 23, 22, 92, 255 );
                ofxUIColor cp = ofxUIColor( 190, 191, 158, 100 );
                ofxUIColor cpo = ofxUIColor( 216, 210, 153, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MINLIME:
            {
                ofxUIColor cb = ofxUIColor( 245, 225, 226, 75 );
                ofxUIColor co = ofxUIColor( 225, 183, 237, 100 );
                ofxUIColor coh = ofxUIColor( 245, 225, 226, 200 );
                ofxUIColor cf = ofxUIColor( 185, 222, 81, 200 );
                ofxUIColor cfh = ofxUIColor( 209, 227, 137, 255 );
                ofxUIColor cp = ofxUIColor( 224, 72, 145, 100 );
                ofxUIColor cpo = ofxUIColor( 225, 183, 237, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MINORANGE:
            {
                ofxUIColor cb = ofxUIColor( 204, 204, 204, 75 );
                ofxUIColor co = ofxUIColor( 111, 111, 111, 100 );
                ofxUIColor coh = ofxUIColor( 204, 204, 204, 200 );
                ofxUIColor cf = ofxUIColor( 255, 100, 0, 200 );
                ofxUIColor cfh = ofxUIColor( 255, 255, 255, 255 );
                ofxUIColor cp = ofxUIColor( 51, 51, 51, 100 );
                ofxUIColor cpo = ofxUIColor( 111, 111, 111, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_GRAYDAY:
            {
                ofxUIColor cb = ofxUIColor( 177, 198, 204, 75 );
                ofxUIColor co = ofxUIColor( 255, 255, 255, 100 );
                ofxUIColor coh = ofxUIColor( 20, 20, 20, 200 );
                ofxUIColor cf = ofxUIColor( 177, 198, 204, 200 );
                ofxUIColor cfh = ofxUIColor( 255, 239, 94, 255 );
                ofxUIColor cp = ofxUIColor( 255, 255, 255, 100 );
                ofxUIColor cpo = ofxUIColor( 20, 20, 20, 200 );
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            case OFX_UI_THEME_MINBLACK:
            {
                ofxUIColor cb = ofxUIColor( 255, 255, 255, 75 );
                ofxUIColor co = ofxUIColor( 209, 231, 81, 100 );
                ofxUIColor coh = ofxUIColor( 255, 255, 255, 200 );
                ofxUIColor cf = ofxUIColor( 0, 0, 0, 200 );
                ofxUIColor cfh = ofxUIColor( 38, 173, 228, 255 );
                ofxUIColor cp = ofxUIColor( 77, 188, 233, 100 );
                ofxUIColor cpo = ofxUIColor( 209, 231, 81, 200 );                
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break;  
                
            default:
            {
                ofxUIColor cb = OFX_UI_COLOR_BACK; 
                ofxUIColor co = OFX_UI_COLOR_OUTLINE; 
                ofxUIColor coh = OFX_UI_COLOR_OUTLINE_HIGHLIGHT;
                ofxUIColor cf = OFX_UI_COLOR_FILL; 
                ofxUIColor cfh = OFX_UI_COLOR_FILL_HIGHLIGHT;
                ofxUIColor cp = OFX_UI_COLOR_PADDED;
                ofxUIColor cpo = OFX_UI_COLOR_PADDED_OUTLINE;
                setUIColors( cb, co, coh, cf, cfh, cp, cpo );                                 
            }
                break; 
        }
    }
    
    ofxUIColor& getWidgetColorPadded()
	{
        return widget_color_padded_rect;
	}
    
	ofxUIColor& getWidgetColorPaddedOutline()
	{
        return widget_color_padded_rect_outline;
	}
    
	ofxUIColor& getWidgetColorBack()
	{
		return widget_color_back;
	}
	
	ofxUIColor& getWidgetColorOutline()
	{
		return widget_color_outline;
	}
	
	ofxUIColor& getWidgetColorOutlineHighlight()
	{
		return widget_color_outline_highlight;
	}
	
	ofxUIColor& getWidgetColorFill()
	{
		return widget_color_fill;
	}
	
	ofxUIColor& getWidgetColorFillHighlight()
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
    
	void setWidgetColor(int _target, ofxUIColor _color)
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
    
    ofxUIWidget *getWidget(string _name, int widgetID = -1)
	{
        if(widgetID == -1)
        {
            multimap<string, ofxUIWidget *>::iterator wit = widgets_map.find(_name);
            if(wit != widgets_map.end())
            {
                return wit->second;
            }
        }
        else
        {
            for(multimap<string, ofxUIWidget*>::iterator wit = widgets_map.equal_range(_name).first; wit != widgets_map.equal_range(_name).second; ++wit)
            {
                if(wit->second->getID() == widgetID)
                {
                    return wit->second;
                }
            }
            multimap<string, ofxUIWidget *>::iterator wit = widgets_map.find(_name);
            if(wit != widgets_map.end())
            {
                return wit->second;
            }                    
        }
        return NULL;
	}
	
    void removeWidget(string _name)
    {
        ofxUIWidget *w = getWidget(_name);
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
    
    vector<ofxUIWidget*> getWidgetsOfType(ofxUIWidgetType type)
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
    
	ofxUIFont *font_large; 	
	ofxUIFont *font_medium; 		
	ofxUIFont *font_small;
 	
	ofxUIEventArgs *GUIevent; 
    int state;
    bool hasSharedResources;
    bool autoDraw;
    bool autoUpdate;
    
    multimap<string, ofxUIWidget*> widgets_map;
	vector<ofxUIWidget*> widgets;
    map<string, ofxUIWidget*> widgetsAreModal;
	vector<ofxUIWidget*> widgetsWithState;
	ofxUIWidget *lastAdded; 
	ofxUIWidget *activeFocusedWidget; 
	bool enable_highlight_outline; 
	bool enable_highlight_fill;
	bool enabled;
    bool bTriggerWidgetsUponLoad;
    int uniqueIDs; 
    bool hasKeyBoard; 
    
    float widgetSpacing;
    float globalCanvasWidth;
    float globalSliderHeight;
    float globalGraphHeight;
    float globalButtonDimension;
    float globalSpacerHeight;
    
    string fontName;

    ofxUIWidgetPosition widgetPosition;
    ofxUIWidgetAlignment widgetAlign;
    ofxUIWidgetFontType widgetFontSize;
    
	ofxUIColor widget_color_back;
	ofxUIColor widget_color_outline;
	ofxUIColor widget_color_outline_highlight;
	ofxUIColor widget_color_fill;
	ofxUIColor widget_color_fill_highlight;
    ofxUIColor widget_color_padded_rect;
	ofxUIColor widget_color_padded_rect_outline;
    
    bool bDrawWidgetPadding;
    bool bDrawWidgetPaddingOutline;
    
    //Easy Font setting contributed from Colin Duffy (colin@tomorrowevening.com)
    bool updateFont(ofxUIWidgetFontType _kind, string filename, int fontsize, bool _bAntiAliased=true, bool _bFullCharacterSet=false, bool makeContours=false, float simplifyAmt=0.3, int dpi=0) {
        bool success = false;
        switch(_kind)
        {
            case OFX_UI_FONT_LARGE:
                if(font_large != NULL)
                {
                    delete font_large;
                }
                font_large = new ofxUIFont();
                success = font_large->loadFont(filename,fontsize,_bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt,dpi);
                break;
                
            case OFX_UI_FONT_MEDIUM:
                if(font_medium != NULL)
                {
                    delete font_medium;
                }
                font_medium = new ofxUIFont();
                success = font_medium->loadFont(filename,fontsize,_bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt,dpi);
                break;
                
            case OFX_UI_FONT_SMALL:
                if(font_small != NULL)
                {
                    delete font_small;
                }
                font_small = new ofxUIFont();
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
                    return;
                }
                    break; 
                    
                case OFX_UI_TEXTINPUT_ON_ENTER:
                {
                    hasKeyBoard = false;
                    return;
                }
                    break; 
                    
                case OFX_UI_TEXTINPUT_ON_UNFOCUS:
                {
                    hasKeyBoard = false; 
                    return;
                }
                    break; 
                    
                default:
                {
                    hasKeyBoard = false; 
                    return; 
                }
                    break;                     
            }
        }        
        hasKeyBoard = false;
    }
};

#endif
