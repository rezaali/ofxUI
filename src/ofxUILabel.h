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

#ifndef OFXUI_LABEL
#define OFXUI_LABEL

#include "ofxUIWidget.h"

class ofxUILabel : public ofxUIWidget
{
public:    
    ofxUILabel()
    {
        
    }
    
    ofxUILabel(float x, float y, string _name, string _label, int _size)
    {
        rect = new ofxUIRectangle(x,y,0,0); 
        init(_name, _label, _size); 		
    }

    ofxUILabel(float x, float y, string _name, int _size)
    {
        rect = new ofxUIRectangle(x,y,0,0); 
        init(_name, _name, _size); 		
    }

    
    ofxUILabel(string _name, string _label, int _size)
    {
        rect = new ofxUIRectangle(0,0,0,0); 
        init(_name, _label, _size); 		
    }
	

    ofxUILabel(string _name, int _size)
    {
        rect = new ofxUIRectangle(0,0,0,0); 
        init(_name, _name, _size); 		
    }    

    void init(string _name, string _label, int _size)
    {
		name = _name;
		kind = OFX_UI_WIDGET_LABEL; 
		label = _label; 		 				
		size = _size;		

		font = NULL;                 
        draw_back = OFX_UI_LABEL_DRAW_BACK; 
        draw_fill = true; 
		
		paddedRect = new ofxUIRectangle(-padding, -padding, padding*2.0, padding*2.0);
		paddedRect->setParent(rect); 
    }
    
    void draw()
    {
        ofPushStyle(); 
        
        ofEnableBlendMode(OF_BLENDMODE_ALPHA); 

        if(draw_back)
        {
            drawBackLabel(); 
        }
        
        if(draw_fill)
        {
            ofFill(); 
            ofSetColor(color_fill); 
			font->drawString(label, rect->getX(), rect->getY()+rect->getHeight()); 
        }
		
		if(draw_fill_highlight)
        {
            ofFill(); 
            ofSetColor(color_fill_highlight); 
			font->drawString(label, rect->getX(), rect->getY()+rect->getHeight()); 
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
    
    void drawBackLabel()
    {
        ofFill(); 
        ofSetColor(color_back); 
        font->drawString(label, rect->getX()+1, rect->getY()+rect->getHeight()+1);         
    }
    
	void drawString(float x, float y, string _string)
	{
		font->drawString(_string, x, y); 
	}
	
	float getStringWidth(string s)
	{
		return font->stringWidth(s); 
	}

	float getStringHeight(string s)
	{
		return font->stringHeight(s); 
	}
    
    void setLabel(string _label)
	{
		label = _label; 		
		float w = font->stringWidth(label); 
		float h = font->stringHeight(label); 		
		rect->width = w; 
		rect->height = h; 		 
		paddedRect->width = w+padding*3.0; 
		paddedRect->height = h+padding*2.0; 
	}
    
    string getLabel()
    {
        return label; 
    }
	
	void setFont(ofTrueTypeFont *_font)
	{
		font = _font; 
		setLabel(label); 
	}
	
	int getSize()
	{
		return size; 
	}
	
	void focus()
	{
		draw_fill_highlight = true; 
		draw_fill = false; 
	}
	
	void unfocus()
	{
		draw_fill_highlight	= false; 		
		draw_fill = true; 
	}
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	int size; 
	string label; 
}; 

#endif