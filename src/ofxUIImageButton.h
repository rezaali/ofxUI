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

#ifndef OFXUI_IMAGE_BUTTON
#define OFXUI_IMAGE_BUTTON

#include "ofxUIWidget.h"

class ofxUIImageButton : public ofxUIButton
{
public:
    ofxUIImageButton() {}
    
    ofxUIImageButton(float x, float y, float w, float h, bool _value, string _pathURL, string _name)
    {
        useReference = false; 
        rect = new ofxUIRectangle(x,y,w,h);
        init(w, h, &_value, _pathURL, _name);         
    }

    ofxUIImageButton(float w, float h, bool _value, string _pathURL, string _name)
    {
        useReference = false;         
        rect = new ofxUIRectangle(0,0,w,h);
        init(w, h, &_value, _pathURL, _name);         
    }
        
    ofxUIImageButton(float x, float y, float w, float h, bool *_value, string _pathURL, string _name)
    {
        useReference = true;         
        rect = new ofxUIRectangle(x,y,w,h);
        init(w, h, _value, _pathURL, _name);         
    }
    
    ofxUIImageButton(float w, float h, bool *_value, string _pathURL, string _name)
    {
        useReference = true;                 
        rect = new ofxUIRectangle(0,0,w,h);
        init(w, h, _value, _pathURL, _name);         
    }    
    
    void init(float w, float h, bool *_value, string _pathURL, string _name)
    {
        name = _name; 		
		kind = OFX_UI_WIDGET_IMAGEBUTTON; 		
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding*2.0);
		paddedRect->setParent(rect); 
        
        if(useReference)
        {
            value = _value; 
        }
        else
        {
            value = new bool(); 
            *value = *_value; 
        }
        
        setValue(*_value); 
        
        img = new ofImage(); 
        img->loadImage(_pathURL);         
    }
	
    virtual bool hasLabel()
    {
        return false;
    }

    virtual void setDrawPadding(bool _draw_padded_rect)
	{
		draw_padded_rect = _draw_padded_rect; 
	}
    
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline)
	{
		draw_padded_rect_outline = _draw_padded_rect_outline; 
	}  
    
    virtual ~ofxUIImageButton()
    {
        delete img; 
    }
	

    virtual void drawBack()
    {
                    
        if(draw_back)
        {
            ofFill(); 
            ofSetColor(color_back); 
            img->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight()); 
        }
    }
    
    virtual void drawFill()
    {
        if(draw_fill)
        {
            ofFill(); 
            ofSetColor(color_fill); 
            img->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight()); 
        }
    }
    
    virtual void drawFillHighlight()
    {
        if(draw_fill_highlight)
        {
            ofFill(); 
            ofSetColor(color_fill_highlight); 
            img->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());             
        }
    }   
    
    virtual void drawOutlineHighlight()
    {
        if(draw_outline_highlight)
        {
            ofNoFill();
            ofSetColor(color_outline_highlight); 
            img->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight()); 
        }
    }   
    
    void stateChange()
    {        
        switch (state) {
            case OFX_UI_STATE_NORMAL:
            {            
                draw_fill_highlight = false;             
                draw_outline_highlight = false;  
            }
                break;
            case OFX_UI_STATE_OVER:
            {
                draw_fill_highlight = false;            
                draw_outline_highlight = true;  
            }
                break;
            case OFX_UI_STATE_DOWN:
            {
                draw_fill_highlight = true;            
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
	
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
	}	

    virtual void setValue(bool _value)
	{
		*value = _value;         
        draw_fill = *value; 
	}	
    
    virtual void setVisible(bool _visible)
    {
        visible = _visible; 
    }

    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    ofImage *img; 
}; 

#endif
