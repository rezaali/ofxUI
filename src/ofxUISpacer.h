#ifndef OFXUI_LINE_SPACER
#define OFXUI_LINE_SPACER

#include "ofxUIWidget.h"

class ofxUISpacer : public ofxUIWidget
{
public:
    ofxUISpacer() {}
    
    ofxUISpacer(float w, float h, float x = 0, float y = 0)
    {
        init(w, h, x, y);
    }
    
    ofxUISpacer* init(float w, float h, float x = 0, float y = 0)
    {
        rect = new ofxUIRectangle(x,y,w,h);
        name = "OFX_UI_SPACER"; 				
        kind = OFX_UI_WIDGET_SPACER; 
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding*2.0);
		paddedRect->setParent(rect);     
        
        draw_fill = true; 
        draw_back = false; 
        
        return this;
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
