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

class ofxUICanvas : public ofxUIWidget
{    
public:	
    ~ofxUICanvas() 
    {
		delete GUIevent; 
		delete font_large; 
		delete font_medium;
		delete font_small;		
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

    ofxUICanvas() 
    {
        float w = ofGetWidth(); 
        float h = ofGetHeight(); 
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w,h);
    }

    void init(int w, int h)
    {
        name = "OFX_UI_WIDGET_CANVAS"; 
		kind = OFX_UI_WIDGET_CANVAS; 
		
		enable(); 
		
		enable_highlight_outline = false; 
		enable_highlight_fill = false; 
        
		GUIevent = new ofxUIEventArgs(this); 
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding*2.0);
		paddedRect->setParent(rect);
        
		font_large = new ofTrueTypeFont(); 
		font_medium = new ofTrueTypeFont(); 
		font_small = new ofTrueTypeFont(); 		
		
		font_large->loadFont(OFX_UI_FONT_NAME,OFX_UI_FONT_LARGE_SIZE,true, true, false, 0.0,OFX_UI_FONT_RESOLUTION); 				
		font_medium->loadFont(OFX_UI_FONT_NAME,OFX_UI_FONT_MEDIUM_SIZE,true, true, false, 0.0,OFX_UI_FONT_RESOLUTION); 				
		font_small->loadFont(OFX_UI_FONT_NAME,OFX_UI_FONT_SMALL_SIZE,true, true, false, 0.0,OFX_UI_FONT_RESOLUTION); 						
        
		font = font_medium; 
		lastAdded = NULL; 
        uniqueIDs = 0;         
        widgetSpacing = OFX_UI_GLOBAL_WIDGET_SPACING; 
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
                font_large->loadFont(OFX_UI_FONT_NAME,_size,true, true, false, 0.0,_resolution); 				            
                break; 

            case OFX_UI_FONT_MEDIUM:
                if(font_medium != NULL)
                {
                    delete font_medium;          
                }
                font_medium = new ofTrueTypeFont(); 
                font_medium->loadFont(OFX_UI_FONT_NAME,_size,true, true, false, 0.0,_resolution); 				                            
                break; 

            case OFX_UI_FONT_SMALL:
                if(font_small != NULL)
                {
                    delete font_small;          
                }
                font_small = new ofTrueTypeFont(); 
                font_small->loadFont(OFX_UI_FONT_NAME,_size,true, true, false, 0.0,_resolution); 				                            
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
	
	void enable()
	{
		enabled = true; 
        enableAppEventCallbacks();        
#ifdef TARGET_OPENGLES
        enableTouchEventCallbacks();
#else
        enableMouseEventCallbacks();
        enableKeyEventCallbacks();
        enableWindowEventCallbacks(); 
#endif                		
	}
	
	void disable()
	{
		enabled = false; 
        disableAppEventCallbacks();        
#ifdef TARGET_OPENGLES
        disableTouchEventCallbacks();
#else
        disableMouseEventCallbacks();
        disableKeyEventCallbacks();
        disableWindowEventCallbacks(); 
#endif                		
	}
	
	bool isEnabled()
	{
		return enabled; 
	}
	
	
	//App Callbacks
    void enableAppEventCallbacks()
    {
        ofAddListener(ofEvents.update, this, &ofxUICanvas::onUpdate);
        ofAddListener(ofEvents.draw, this, &ofxUICanvas::onDraw);
        ofAddListener(ofEvents.exit, this, &ofxUICanvas::onExit);
    }
	
	//App Callbacks
    void disableAppEventCallbacks()
    {
        ofRemoveListener(ofEvents.update, this, &ofxUICanvas::onUpdate);
        ofRemoveListener(ofEvents.draw, this, &ofxUICanvas::onDraw);
        ofRemoveListener(ofEvents.exit, this, &ofxUICanvas::onExit);
    }
	
#ifdef TARGET_OPENGLES
	
	//Touch Callbacks
    void enableTouchEventCallbacks()
    {
        ofAddListener(ofEvents.touchUp, this, &ofxUICanvas::onTouchUp);
        ofAddListener(ofEvents.touchDown, this, &ofxUICanvas::onTouchDown);
        ofAddListener(ofEvents.touchMoved, this, &ofxUICanvas::onTouchMoved);
        ofAddListener(ofEvents.touchCancelled, this, &ofxUICanvas::onTouchCancelled);
        ofAddListener(ofEvents.touchDoubleTap, this, &ofxUICanvas::onTouchDoubleTap);
    }	

	void disableTouchEventCallbacks()
    {
        ofRemoveListener(ofEvents.touchUp, this, &ofxUICanvas::onTouchUp);
        ofRemoveListener(ofEvents.touchDown, this, &ofxUICanvas::onTouchDown);
        ofRemoveListener(ofEvents.touchMoved, this, &ofxUICanvas::onTouchMoved);
        ofRemoveListener(ofEvents.touchCancelled, this, &ofxUICanvas::onTouchCancelled);
        ofRemoveListener(ofEvents.touchDoubleTap, this, &ofxUICanvas::onTouchDoubleTap);
    }	
	
#else
	
	//Mouse Callbacks
    void enableMouseEventCallbacks()
    {
        ofAddListener(ofEvents.mouseReleased, this, &ofxUICanvas::onMouseReleased);
        ofAddListener(ofEvents.mousePressed, this, &ofxUICanvas::onMousePressed);
        ofAddListener(ofEvents.mouseMoved, this, &ofxUICanvas::onMouseMoved);
        ofAddListener(ofEvents.mouseDragged, this, &ofxUICanvas::onMouseDragged);
    }

	//Mouse Callbacks
    void disableMouseEventCallbacks()
    {
        ofRemoveListener(ofEvents.mouseReleased, this, &ofxUICanvas::onMouseReleased);
        ofRemoveListener(ofEvents.mousePressed, this, &ofxUICanvas::onMousePressed);
        ofRemoveListener(ofEvents.mouseMoved, this, &ofxUICanvas::onMouseMoved);
        ofRemoveListener(ofEvents.mouseDragged, this, &ofxUICanvas::onMouseDragged);
    }
	
	//KeyBoard Callbacks
	void enableKeyEventCallbacks()
    {
        ofAddListener(ofEvents.keyPressed, this, &ofxUICanvas::onKeyPressed);
        ofAddListener(ofEvents.keyReleased, this, &ofxUICanvas::onKeyReleased);
    }

	//KeyBoard Callbacks
	void disableKeyEventCallbacks()
    {
        ofRemoveListener(ofEvents.keyPressed, this, &ofxUICanvas::onKeyPressed);
        ofRemoveListener(ofEvents.keyReleased, this, &ofxUICanvas::onKeyReleased);
    }
	
	
    //Window Resize Callback
    void enableWindowEventCallbacks()
    {
        ofAddListener(ofEvents.windowResized, this, &ofxUICanvas::onWindowResized);        
    }

	//Window Resize Callback
    void disableWindowEventCallbacks()
    {
        ofRemoveListener(ofEvents.windowResized, this, &ofxUICanvas::onWindowResized);        
    }
	
	
#endif	


    void onUpdate(ofEventArgs &data) { update(); }
    void onDraw(ofEventArgs &data) { draw(); } 
    void onExit(ofEventArgs &data) { exit(); } 

    
    void update()
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
        ofEnableBlendMode(OF_BLENDMODE_ALPHA); 
        if(draw_back)
        {
            ofFill(); 
            ofSetColor(color_back); 
            rect->draw(); 
        }
        
        if(draw_fill)
        {
            ofFill(); 
            ofSetColor(color_fill); 
            rect->draw(); 
        }
        
        if(draw_fill_highlight)
        {
            ofFill(); 
            ofSetColor(color_fill_highlight); 
            rect->draw(); 
        }
        
        if(draw_outline)
        {
            ofNoFill();
            ofSetColor(color_outline); 
            rect->draw(); 
        }
        
        if(draw_outline_highlight)
        {
            ofNoFill();
            ofSetColor(color_outline_highlight); 
            rect->draw();          
        }
		
		if(draw_padded_rect)
		{
            ofNoFill();
            ofSetColor(color_outline_highlight); 
			paddedRect->draw(); 
		}
        
        ofPopStyle();         
        
        ofSetLineWidth(1.0); 
		
		for(int i = widgets.size()-1; i >= 0; i--)
		{
            if(widgets[i]->isVisible())
            {
                widgets[i]->draw(); 	
            }
		}
		
		glDisable(GL_DEPTH_TEST); 

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
	
	void touchDown(ofTouchEventArgs& touch) 
	{		
        if(rect->inside(touch.x, touch.y))
        {
			for(int i = 0; i < widgets.size(); i++)
			{
				if(widgets[i]->isVisible())	widgets[i]->touchDown(touch); 
			}
		}
	}
    
	void touchMoved(ofTouchEventArgs& touch) 
	{
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible())	widgets[i]->touchMoved(touch);
        }
	}
    
	void touchUp(ofTouchEventArgs& touch) 
	{
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible())	widgets[i]->touchUp(touch); 
        }
	}
    
	void touchDoubleTap(ofTouchEventArgs& touch) 
	{
        if(rect->inside(touch.x, touch.y))
        {
			for(int i = 0; i < widgets.size(); i++)
			{
				if(widgets[i]->isVisible())	widgets[i]->touchDoubleTap(touch); 
			}
		}		
	}
    
	void touchCancelled(ofTouchEventArgs& touch) 
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
	
	void mouseMoved(int x, int y ) 
    {
        if(rect->inside(x, y))
        {
			for(int i = 0; i < widgets.size(); i++)
			{                
				if(widgets[i]->isVisible()) widgets[i]->mouseMoved(x, y); 
			}
		}	
    }
    
    void mouseDragged(int x, int y, int button) 
    {		
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible())	widgets[i]->mouseDragged(x, y, button); 
        }                
    }
    
    void mousePressed(int x, int y, int button) 
    {
        if(rect->inside(x, y))
        {
			for(int i = 0; i < widgets.size(); i++)
			{
				if(widgets[i]->isVisible()) widgets[i]->mousePressed(x, y, button); 
			}
		}		
    }
    
    void mouseReleased(int x, int y, int button) 
    {		        
        for(int i = 0; i < widgets.size(); i++)
        {
            if(widgets[i]->isVisible()) widgets[i]->mouseReleased(x, y, button); 
        }    
    }	
    
    bool isHit(int x, int y)
    {
        return rect->inside(x, y);
    }
    
	void onKeyPressed(ofKeyEventArgs& data)
    {
		keyPressed(data.key); 
    }
    
    void onKeyReleased(ofKeyEventArgs& data)
    {
		keyReleased(data.key); 
    }	

    void keyPressed(int key) 
    {
        for(int i = 0; i < widgets.size(); i++)
		{
			widgets[i]->keyPressed(key); 
		}		
    }
    
    void keyReleased(int key) 
    {
		for(int i = 0; i < widgets.size(); i++)
		{
			widgets[i]->keyReleased(key); 
		}	
    }
	
    void onWindowResized(ofResizeEventArgs& data) 
    { 
		windowResized(data.width, data.height); 
    } 	
    
    void windowResized(int w, int h) 
    {
		for(int i = 0; i < widgets.size(); i++)
		{
			widgets[i]->windowResized(w, h); 
		}
    }
    
#endif	
	
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
    
	void addWidget(ofxUIWidget *widget)
	{
		if(widget->getKind() == OFX_UI_WIDGET_LABEL)
		{
			ofxUILabel *label = (ofxUILabel *) widget;
			setLabelFont(label); 
		}
		else if(widget->getKind() == OFX_UI_WIDGET_SLIDER_H || widget->getKind() == OFX_UI_WIDGET_SLIDER_V)
		{
			ofxUISlider *slider = (ofxUISlider *) widget;
			ofxUILabel *label = (ofxUILabel *) slider->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 				
		}
		else if(widget->getKind() == OFX_UI_WIDGET_2DPAD)		
		{
			ofxUI2DPad *pad = (ofxUI2DPad *) widget;
			ofxUILabel *label = (ofxUILabel *) pad->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 				
		}		
		else if(widget->getKind() == OFX_UI_WIDGET_IMAGE)		
		{
			ofxUIImage *image = (ofxUIImage *) widget;
			ofxUILabel *label = (ofxUILabel *) image->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 				
		}				
		else if(widget->getKind() == OFX_UI_WIDGET_RSLIDER_H || widget->getKind() == OFX_UI_WIDGET_RSLIDER_V)
		{
			ofxUIRangeSlider *rslider = (ofxUIRangeSlider *) widget;
			ofxUILabel *label = (ofxUILabel *) rslider->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 				
		}		
		else if(widget->getKind() == OFX_UI_WIDGET_ROTARYSLIDER)
		{
			ofxUIRotarySlider *rslider = (ofxUIRotarySlider *) widget;
			ofxUILabel *label = (ofxUILabel *) rslider->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 				
		}		
		else if(widget->getKind() == OFX_UI_WIDGET_BUTTON || widget->getKind() ==  OFX_UI_WIDGET_LABELBUTTON || widget->getKind() == OFX_UI_WIDGET_LABELTOGGLE)
		{
			ofxUIButton *button = (ofxUIButton *) widget;
			ofxUILabel *label = (ofxUILabel *) button->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 					
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
			}            
        }
		else if(widget->getKind() == OFX_UI_WIDGET_TEXTINPUT)
		{
			ofxUITextInput *textinput = (ofxUITextInput *) widget;
			ofxUILabel *label = (ofxUILabel *) textinput->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 					
		}		
		else if(widget->getKind() == OFX_UI_WIDGET_NUMBERDIALER)
		{
			ofxUINumberDialer *numberDialer = (ofxUINumberDialer *) widget;
			ofxUILabel *label = (ofxUILabel *) numberDialer->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 					
		}		        
		else if(widget->getKind() == OFX_UI_WIDGET_TOGGLE)
		{
			ofxUIToggle *toggle = (ofxUIToggle *) widget;
			ofxUILabel *label = (ofxUILabel *) toggle->getLabel();
			setLabelFont(label); 			
			pushbackWidget(label); 					
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
			}
		}
		else if(widget->getKind() == OFX_UI_WIDGET_FPS)
		{
			ofxUILabel *fps = (ofxUILabel *) widget;
			setLabelFont(fps); 
		}
	
		widget->setParent(this); 
		widget->setRectParent(this->rect); 		
		pushbackWidget(widget); 	
	}
		
	void addWidgetDown(ofxUIWidget *widget, ofxWidgetAlignment align = OFX_UI_ALIGN_LEFT)
	{
		addWidget(widget); 
        ofxUIRectangle *widgetRect = widget->getRect();         
		if(lastAdded != NULL)
		{
			ofxUIRectangle *lastRect = lastAdded->getRect();                         
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
	}
    
	void addWidgetUp(ofxUIWidget *widget, ofxWidgetAlignment align = OFX_UI_ALIGN_LEFT)
	{
		addWidget(widget); 
        ofxUIRectangle *widgetRect = widget->getRect();                 
		if(lastAdded != NULL)
		{
			ofxUIRectangle *lastRect = lastAdded->getRect();             
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
	}    
    
	void addWidgetRight(ofxUIWidget *widget)
	{
		addWidget(widget); 	
		if(lastAdded != NULL)
		{
			ofxUIRectangle *lastRect = lastAdded->getRect(); 
			ofxUIRectangle *lastPaddedRect = lastAdded->getPaddingRect();                         
			ofxUIRectangle *widgetRect = widget->getRect(); 
			
            widgetRect->x = lastPaddedRect->getX()+lastPaddedRect->getWidth()-rect->getX()+widgetSpacing; 
			widgetRect->y = lastRect->getY(); 
		}
		else 
		{
			ofxUIRectangle *widgetRect = widget->getRect(); 
			widgetRect->x = widgetSpacing; 
            widgetRect->y = widgetSpacing;                         
		}
        lastAdded = widget;  	
	}
    
    void addWidgetLeft(ofxUIWidget *widget)
	{
		addWidget(widget); 	        
		if(lastAdded != NULL)
		{
			ofxUIRectangle *lastRect = lastAdded->getRect(); 
			ofxUIRectangle *lastPaddedRect = lastAdded->getPaddingRect();                         
			ofxUIRectangle *widgetRect = widget->getRect(); 
            ofxUIRectangle *widgetPaddedRect = widget->getPaddingRect();                         
			
            widgetRect->x = lastPaddedRect->getX()-widgetPaddedRect->getWidth()-rect->getX(); 
			widgetRect->y = lastRect->getY(); 
		}
		else 
		{
			ofxUIRectangle *widgetRect = widget->getRect(); 
			widgetRect->x = widgetSpacing; 
            widgetRect->y = widgetSpacing;                         
		}
        lastAdded = widget;  	
	}    
    
    void addWidgetSouthOf(ofxUIWidget *widget, string referenceName)
    {
        addWidget(widget); 	
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
    }    
    
    void addWidgetNorthOf(ofxUIWidget *widget, string referenceName)
    {
        addWidget(widget); 	
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
    }      
    
    void addWidgetWestOf(ofxUIWidget *widget, string referenceName)
    {
		addWidget(widget); 	        
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
    }        
    
    void addWidgetEastOf(ofxUIWidget *widget, string referenceName)
    {
		addWidget(widget); 	        
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
				
			default:
				break;
		}
	}
	
	ofxUIWidget *getWidget(string _name)
	{
		return widgets_map[_name]; 
	}
	
	void setDrawPadding(bool _draw_padded_rect)
	{
		draw_padded_rect = _draw_padded_rect; 
		for(int i = 0; i < widgets.size(); i++)
		{
			widgets[i]->setDrawPadding(_draw_padded_rect); 
		}		
	}
    
    vector<ofxUIWidget*> getWidgets()
    {
        return widgets;
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
    
    map<string, ofxUIWidget*> widgets_map;     
	vector<ofxUIWidget*> widgets; 
	ofxUIWidget *lastAdded; 
	ofxUIWidget *activeFocusedWidget; 
	bool enable_highlight_outline; 
	bool enable_highlight_fill; 	
	bool enabled; 
    int uniqueIDs; 
    
    float widgetSpacing; 
};

#endif
