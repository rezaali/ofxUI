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
    
    ofxUISpacer(float x, float y, float w, float h, string _name)
    {
        rect = new ofxUIRectangle(x,y,w,h); 
        init(w, h); 
        name = _name; 
    }
    
    ofxUISpacer(float w, float h)
    {
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w, h); 
    }    
    
    ofxUISpacer(float w, float h, string _name)
    {
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w, h); 
        name = _name; 
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
		
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
	}	
    
    void toggleColor()
    {
        draw_fill = !draw_fill; 
        draw_back = !draw_back; 
    }
    
    void setToggleColor(bool _value)
    {
        if(_value)
        {
            draw_fill = true; 
            draw_back = false; 
        }
        else
        {
            draw_fill = false; 
            draw_back = true;             
        }
    }
protected: 
}; 

#endif
