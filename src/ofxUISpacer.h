#ifndef OFXUI_LINE_SPACER
#define OFXUI_LINE_SPACER

#include "ofxUIWidget.h"

class ofxUISpacer : public ofxUIWidget
{
public:
    ofxUISpacer(float x, float y, float w, float h)
    {
        rect = new ofxUIRectangle(x,y,w,h); 
        init(w, h); 
    }
    
    ofxUISpacer(float w, float h)
    {
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w, h); 
    }    
    
    void init(float w, float h)
    {
        name = "OFX_UI_SPACER"; 				
        kind = OFX_UI_WIDGET_SPACER; 
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding*2.0);
		paddedRect->setParent(rect);     
        
        draw_fill = true; 
        draw_back = false; 
    }
    
    
    void draw()
    {
        ofPushStyle(); 
        
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
    }
    
		
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
	}	
    
    void toggleColor()
    {
        draw_fill = !draw_fill; 
        draw_back = !draw_back; 
    }
protected: 
}; 

#endif
