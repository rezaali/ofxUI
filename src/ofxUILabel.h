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

#include "ofxUIWidgetWithLabel.h"

class ofxUILabel : public ofxUIWidget
{
public:
    ofxUILabel() : ofxUIWidget()
    {
        
    }
    
    ofxUILabel(float x, float y, string _name, string _label, int _size) : ofxUIWidget()
    {
        rect = new ofxUIRectangle(x,y,0,0); 
        init(_name, _label, _size); 		
        autoSize = true;
    }

    ofxUILabel(float x, float y, string _name, int _size) : ofxUIWidget()
    {
        rect = new ofxUIRectangle(x,y,0,0); 
        init(_name, _name, _size); 		
        autoSize = true;
    }

    ofxUILabel(string _name, string _label, int _size) : ofxUIWidget()
    {
        rect = new ofxUIRectangle(0,0,0,0); 
        init(_name, _label, _size); 		
        autoSize = true;        
    }	

    ofxUILabel(string _name, int _size) : ofxUIWidget()
    {
        rect = new ofxUIRectangle(0,0,0,0); 
        init(_name, _name, _size); 		
        autoSize = true;
    }   
    
    ofxUILabel(float x, float y, float w, string _name, string _label, int _size) : ofxUIWidget()
    {
        rect = new ofxUIRectangle(x,y,w,0); 
        init(_name, _label, _size); 		
        autoSize = false;
    }
    
    ofxUILabel(float x, float y, float w, string _name, int _size) : ofxUIWidget()
    {
        rect = new ofxUIRectangle(x,y,w,0); 
        init(_name, _name, _size); 		
        autoSize = false;
    }
    
    ofxUILabel(float w, string _name, string _label, int _size) : ofxUIWidget()
    {
        rect = new ofxUIRectangle(0,0,w,0); 
        init(_name, _label, _size); 		
        autoSize = false;        
    }	
    
    ofxUILabel(float w, string _name, int _size) : ofxUIWidget()
    {
        rect = new ofxUIRectangle(0,0,w,0); 
        init(_name, _name, _size); 		
        autoSize = false;
    }   

    ofxUILabel(float w, string _name, int _size, float h) : ofxUIWidget()
    {
        rect = new ofxUIRectangle(0,0,w,h); 
        init(_name, _name, _size); 		
        autoSize = false;
    }   
    
    void init(string _name, string _label, int _size) 
    {
		name = string(_name);
		kind = OFX_UI_WIDGET_LABEL; 
		label = string(_label);
		size = _size;		

		font = NULL;                 
        draw_back = OFX_UI_LABEL_DRAW_BACK; 
        draw_fill = true; 
		paddedRect = new ofxUIRectangle(-padding, -padding, padding*2.0, padding*2.0);
		paddedRect->setParent(rect); 
    }
    
    void drawBack()
    {
        if(draw_back)
        {
            drawBackLabel(); 
        }
    }
    
    void drawFill()
    {
        if(draw_fill)
        {
            ofxUIFill();
            ofxUISetColor(color_fill);
			font->drawString(label, floor(rect->getX())+xOffset, floor(rect->getY()+rect->getHeight())+yOffset); 
        }
	}
	
    void drawFillHighlight()
    {
		if(draw_fill_highlight)
        {
            ofxUIFill(); 
            ofxUISetColor(color_fill_highlight); 
			font->drawString(label, floor(rect->getX())+xOffset, floor(rect->getY()+rect->getHeight())+yOffset); 
        }        
	}	
            
    void drawBackLabel()
    {      
        ofxUIFill(); 
        ofxUISetColor(color_back);     
        font->drawString(label, floor(rect->getX())+1+xOffset, floor(rect->getY()+rect->getHeight())+1+yOffset);
    }
    
	void drawString(float x, float y, string _string)
	{
        font->drawString(_string, floor(x), floor(y));
	}
    
    void drawStringShadow(float x, float y, string _string)
	{
        ofxUIFill();
        ofxUISetColor(color_back);     
        font->drawString(_string, floor(x)+1, floor(y)+1);
	}
    
	float getStringWidth(string s)
	{
		return font->stringWidth(s); 
	}

	float getStringHeight(string s)
	{
		return font->stringHeight(s); 
	}
    
    float getLineHeight()
	{
		return font->getLineHeight();
	}
    
    virtual ofxUILabel* getLabelWidget()
    {
        return this;
    }
    
    void setLabel(string _label)
	{
		label = string(_label);
        if(autoSize)
        {
            float w = font->stringWidth(label); 
            float h = font->stringHeight("1");          //otherwise we get some funky non-uniform spacing :(
            rect->setWidth(w);
            rect->setHeight(h); 		 
            paddedRect->setWidth(w+padding*2.0);
            paddedRect->setHeight(h+padding*2.0);
            xOffset = 0;
            yOffset = 0;
        }
        else
        {                    
            while(getStringWidth(label) > rect->width-padding*4.0 && label.size())
            {
                label = label.substr(0, label.size()-1);
            }                        
//            float w = (int)font->stringWidth(label); 
            float h = (int)font->stringHeight("1");     //otherwise we get some funky non-uniform spacing :(
            if(rect->getHeight() > 0)
            {
                yOffset = 0; 
            }
            else
            {
                rect->setHeight(h);
                yOffset = 0; 
            }
            paddedRect->height = rect->getHeight()+padding*2.0;
            paddedRect->width = rect->getWidth()+padding*2.0;
//            xOffset = (int) (rect->width*.5 - w*.5);
            xOffset = 0;
        }
	}
    
    bool getAutoSize()
    {
        return autoSize;
    }
    
    void setAutoSize(bool _autoSize)
    {
        autoSize = _autoSize;
    }
    
    string& getLabel()
    {
        return label; 
    }
	
	void setFont(ofxUIFont *_font)
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
    bool autoSize;
    int xOffset, yOffset; 
}; 

#endif