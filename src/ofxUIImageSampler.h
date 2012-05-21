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

#ifndef OFXUI_IMAGE_SAMPLER
#define OFXUI_IMAGE_SAMPLER

#include "ofxUIImage.h"

class ofxUIImageSampler : public ofxUIImage
{
public:
    ofxUIImageSampler(float x, float y, float w, float h, ofImage *_image, string _name) : ofxUIImage(x, y, w, h, _image, _name)
    {
        initSampler();
    }
    
    ofxUIImageSampler(float w, float h, ofImage *_image, string _name) : ofxUIImage(w, h, _image, _name)
    {
        initSampler();
    }    
    
    void initSampler()
    {
        label->setVisible(false);          
        value.x = .5; 
		value.y = .5; 
        input(value.x*rect->getWidth(),value.y*rect->getHeight());
        kind = OFX_UI_WIDGET_IMAGESAMPLER; 
        squareSize = OFX_UI_GLOBAL_WIDGET_SPACING;
    }
    
    void setSquareSize(float _squareSize)
    {
        squareSize = _squareSize; 
    }
    
    void drawFill()
    {
        if(draw_fill)
        {			            
			if(image != NULL)
			{			   
				ofFill(); 
				ofSetColor(255); 		
				image->draw(rect->getX(), rect->getY(), rect->width, rect->height); 
			}
            ofSetColor(color_fill);             
			ofLine(rect->getX()+value.x*rect->getWidth(),  rect->getY(), rect->getX()+value.x*rect->getWidth(),  rect->getY()+rect->getHeight()); 
			ofLine(rect->getX(),  rect->getY()+value.y*rect->getHeight(), rect->getX()+rect->getWidth(),  rect->getY()+value.y*rect->getHeight()); 			

            ofFill(); 
            ofSetColor(sampledColor); 		 
			ofSetRectMode(OF_RECTMODE_CENTER);            
			ofRect(rect->getX()+value.x*rect->getWidth(), rect->getY()+value.y*rect->getHeight(), squareSize, squareSize); 
			ofSetRectMode(OF_RECTMODE_CORNER);
            
        }
    }
    
    void drawFillHighlight()
    {
        if(draw_fill_highlight)
        {
            ofSetColor(color_fill_highlight);             
			ofLine(rect->getX()+value.x*rect->getWidth(),  rect->getY(), rect->getX()+value.x*rect->getWidth(),  rect->getY()+rect->getHeight()); 
			ofLine(rect->getX(),  rect->getY()+value.y*rect->getHeight(), rect->getX()+rect->getWidth(),  rect->getY()+value.y*rect->getHeight()); 			                        

            ofFill(); 
            ofSetColor(sampledColor); 
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofRect(rect->getX()+value.x*rect->getWidth(), rect->getY()+value.y*rect->getHeight(), squareSize, squareSize); 
			ofSetRectMode(OF_RECTMODE_CORNER);						
        }        
    }
        
    void setVisible(bool _visible)
    {
        visible = _visible; 
        label->setVisible(false); 
    }    
    	
    void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
        paddedRect->height += padding;
	}	        
    
    void mouseDragged(int x, int y, int button) 
    {
        if(hit)
        {
            state = OFX_UI_STATE_DOWN;     
			input(x, y); 
			triggerEvent(this); 			
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;        
        }
        stateChange();     
    }
    
    void mousePressed(int x, int y, int button) 
    {
        if(rect->inside(x, y))
        {
            hit = true; 
            state = OFX_UI_STATE_DOWN;     
			input(x, y); 
			triggerEvent(this); 
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;        
        }
        stateChange();         
    }
    
    void mouseReleased(int x, int y, int button) 
    {
        if(hit)
        {
#ifdef TARGET_OPENGLES
            state = OFX_UI_STATE_NORMAL;        
#else            
            state = OFX_UI_STATE_OVER; 
#endif 
			input(x, y); 
			triggerEvent(this); 			
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;         
        }
        stateChange();         
        hit = false; 
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
                draw_outline_highlight = true;             
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
    
    void input(int x, int y)
    {
		value.x = rect->percentInside(x, y).x; 			
		value.y = rect->percentInside(x, y).y; 	
        if(value.x > 1.0)
        {
            value.x = 1.0;             
        }
        else if(value.x < 0.0)
        {
            value.x = 0.0;             
        }
        
        if(value.y > 1.0)
        {
            value.y = 1.0;             
        }
        else if(value.y < 0.0)
        {
            value.y = 0.0; 
        }    
        sampledColor = image->getColor(value.x*(image->getWidth()-1), value.y*(image->getHeight()-1));          //why one? well because if we get to the end, we sample the beginning...
    }
    
    ofColor& getColor()
    {
        return sampledColor; 
    }
    
    void setColor(ofColor _sampledColor)
    {
        sampledColor = _sampledColor; 
    }
    
    ofPoint getValue()
    {
        return value;
    }
    
    void setValue(ofPoint _value)
    {
        value = _value; 
        if(value.x > 1.0)
        {
            value.x = 1.0;             
        }
        else if(value.x < 0.0)
        {
            value.x = 0.0;             
        }
        
        if(value.y > 1.0)
        {
            value.y = 1.0;             
        }
        else if(value.y < 0.0)
        {
            value.y = 0.0; 
        }    
        sampledColor = image->getColor(value.x*(image->getWidth()-1), value.y*(image->getHeight()-1));          //why one? well because if we get to the end, we sample the beginning...        
    }
    
    bool isDraggable()
    {
        return true; 
    }

protected: 
    ofColor sampledColor; 
	ofPoint value;     
    float squareSize; 
}; 

#endif
