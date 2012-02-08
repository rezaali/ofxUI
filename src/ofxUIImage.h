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

#ifndef OFXUI_IMAGE
#define OFXUI_IMAGE

#include "ofxUIWidget.h"

class ofxUIImage : public ofxUIWidget
{
public:
    ofxUIImage(float x, float y, float w, float h, ofImage *_image, string _name)
    {
        rect = new ofxUIRectangle(x,y,w,h); 
        init(w, h, _image, _name); 
    }
    
    ofxUIImage(float w, float h, ofImage *_image, string _name)
    {
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w, h, _image, _name); 
    }    
    
    void init(float w, float h, ofImage *_image, string _name)
    {
		name = _name; 				
		kind = OFX_UI_WIDGET_IMAGE; 
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding);
		paddedRect->setParent(rect); 
        
        draw_back = false; 
        draw_fill = true; 
        
		image = _image; 
        
		label = new ofxUILabel(0,h+padding,(name+" LABEL"),name, OFX_UI_FONT_SMALL); 		
		label->setParent(label); 
		label->setRectParent(rect);         
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
			if(image != NULL)
			{			   
				ofFill(); 
				ofSetColor(255); 		
				image->draw(rect->getX(), rect->getY(), rect->width, rect->height); 
			}
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
				
	ofxUILabel *getLabel()
	{
		return label; 
	}
	
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
		paddedRect->height += label->getPaddingRect()->height; 		
	}	
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	ofImage *image; 
	ofxUILabel *label; 	
}; 

#endif
