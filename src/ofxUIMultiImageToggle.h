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

#ifndef OFXUI_MULTI_IMAGE_TOGGLE
#define OFXUI_MULTI_IMAGE_TOGGLE

#include "ofxUIToggle.h"

class ofxUIMultiImageToggle : public ofxUIToggle
{
public:        
    ofxUIMultiImageToggle(float x, float y, float w, float h, bool _value, string _pathURL, string _name,  int _size= OFX_UI_FONT_SMALL) : ofxUIToggle()
    {
        useReference = false; 
        rect = new ofxUIRectangle(x,y,w,h); 
        init(w, h, &_value, _pathURL, _name, _size);
    }
    
    ofxUIMultiImageToggle(float w, float h, bool _value, string _pathURL, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUIToggle()
    {
        useReference = false;         
        rect = new ofxUIRectangle(0,0,w,h);
        init(w, h, &_value, _pathURL, _name, _size);
    }    
    
    ofxUIMultiImageToggle(float x, float y, float w, float h, bool *_value, string _pathURL, string _name,  int _size= OFX_UI_FONT_SMALL) : ofxUIToggle()
    {
        useReference = true;
        rect = new ofxUIRectangle(x,y,w,h);
        init(w, h, _value, _pathURL, _name, _size);
    }
    
    ofxUIMultiImageToggle(float w, float h, bool *_value, string _pathURL, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUIToggle()
    {
        useReference = true;
        rect = new ofxUIRectangle(0,0,w,h);
        init(w, h, _value, _pathURL, _name, _size);
    }
    
    
    ~ofxUIMultiImageToggle()
    {
        delete down;
        delete back;
        delete over;
        delete on;
    }
    
    void init(float w, float h, bool *_value, string _pathURL, string _name, int _size = OFX_UI_FONT_SMALL)
    {
		name = string(_name);  		
		kind = OFX_UI_WIDGET_MULTIIMAGETOGGLE;
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding*2.0);
		paddedRect->setParent(rect); 
        
		label = new ofxUILabel(w+padding*2.0,0, (name+" LABEL"), name, _size); 
		label->setParent(label); 
		label->setRectParent(rect); 
        label->setEmbedded(true);		

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
        
        drawLabel = true;
        label->setVisible(drawLabel);      
        
        string coreURL = _pathURL;
        string extension = "";
        string period (".");
        size_t found;        
        
        found=_pathURL.find(period);
        if (found!=string::npos)        
        {
            coreURL = _pathURL.substr(0,found);
            extension = _pathURL.substr(found);
        }
        
        back = new ofImage();   back->loadImage(_pathURL);         
        down = new ofImage();   down->loadImage(coreURL+"down"+extension);         
        over = new ofImage();   over->loadImage(coreURL+"over"+extension);         
        on = new ofImage();     on->loadImage(coreURL+"on"+extension);         
    }       
    
    
    
    void drawBack()                     //NORMAL
    {
        if(draw_back && !draw_fill)
        {
            ofSetColor(255); 
            back->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());       
        }
    }
    
    void drawOutlineHighlight()         //OVER
    {
        if(draw_outline_highlight)
        {
            ofSetColor(255); 
            over->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());                      
        }
    }    
    
    void drawFill()                     
    {
        if(draw_fill)
        {
            ofSetColor(255); 
            on->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight()); 
        }        
    }
    
    void drawFillHighlight()            //DOWN/ON
    {
        if(draw_fill_highlight)
        {
            ofSetColor(255); 
            down->draw(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight()); 
        }        
    }
    
    
    virtual void stateChange()
    {                
        switch (state) {
            case OFX_UI_STATE_NORMAL:
            {            
                draw_back = true; 
                draw_fill_highlight = false;             
                draw_outline_highlight = false;  
				label->unfocus(); 								
            }
                break;
            case OFX_UI_STATE_OVER:
            {
                draw_back = false;                 
                draw_fill_highlight = false;            
                draw_outline_highlight = true;  
				label->focus(); 								
            }
                break;
            case OFX_UI_STATE_DOWN:
            {
                draw_back = false;                  
                draw_fill_highlight = true;            
                draw_outline_highlight = false;             
				label->focus(); 					
            }
                break;
            case OFX_UI_STATE_SUSTAINED:
            {
                draw_fill_highlight = false;            
                draw_outline_highlight = false;                         
				label->unfocus(); 								
            }
                break;            
                
            default:
                break;
        }        
    }    
    
    virtual void setValue(bool _value)
	{
		*value = _value;
        draw_fill = *value;
	}
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    ofImage *back; 
    ofImage *over; 
    ofImage *down;
    ofImage *on; 
}; 

#endif

