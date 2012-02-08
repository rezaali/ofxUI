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

#ifndef OFXUI_2D_PAD
#define OFXUI_2D_PAD

#include "ofxUIWidget.h"

class ofxUI2DPad : public ofxUIWidget
{
public:
    ofxUI2DPad(float x, float y, float w, float h, ofPoint _value, string _name)
    {
        rect = new ofxUIRectangle(x,y,w,h); 
        init(w, h, _value, _name);
    }	
    
    ofxUI2DPad(float w, float h, ofPoint _value, string _name)
    {
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w, h, _value, _name);
    }	
    
    void init(float w, float h, ofPoint _value, string _name)
    {
		name = _name; 				
		kind = OFX_UI_WIDGET_2DPAD; 		
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding);
		paddedRect->setParent(rect); 
		
        draw_fill = true;                 
        value = _value;                                               //the widget's value
		
		value.x /= rect->width; 
		value.y /= rect->height;
		
		if(value.x > 1)
		{
			value.x = 1; 
		}
		else if(value.x < 0)
		{
			value.x = 0; 
		}
		
		if(value.y > 1)
		{
			value = 1; 
		}
		else if(value.y < 0)
		{
			value = 0; 
		}
		
		label = new ofxUILabel(0,h+padding,(name+" LABEL"), (name + ": " + ofToString(getScaledValue().x,2) + ", " + ofToString(getScaledValue().y,2)), OFX_UI_FONT_SMALL); 		
		label->setParent(label); 
		label->setRectParent(rect);         
        increment = 1.0; 
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
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofRect(rect->getX()+value.x*rect->getWidth(), rect->getY()+value.y*rect->getHeight(), OFX_UI_GLOBAL_WIDGET_SPACING, OFX_UI_GLOBAL_WIDGET_SPACING); 
			ofSetRectMode(OF_RECTMODE_CORNER);			
			
			ofLine(rect->getX()+value.x*rect->getWidth(),  rect->getY(), rect->getX()+value.x*rect->getWidth(),  rect->getY()+rect->getHeight()); 
			ofLine(rect->getX(),  rect->getY()+value.y*rect->getHeight(), rect->getX()+rect->getWidth(),  rect->getY()+value.y*rect->getHeight()); 			
        }

        if(draw_fill_highlight)
        {
            ofFill(); 
            ofSetColor(color_fill_highlight); 
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofRect(rect->getX()+value.x*rect->getWidth(), rect->getY()+value.y*rect->getHeight(), OFX_UI_GLOBAL_WIDGET_SPACING, OFX_UI_GLOBAL_WIDGET_SPACING); 
			ofSetRectMode(OF_RECTMODE_CORNER);			
			
			ofLine(rect->getX()+value.x*rect->getWidth(),  rect->getY(), rect->getX()+value.x*rect->getWidth(),  rect->getY()+rect->getHeight()); 
			ofLine(rect->getX(),  rect->getY()+value.y*rect->getHeight(), rect->getX()+rect->getWidth(),  rect->getY()+value.y*rect->getHeight()); 			
			
			label->drawString(rect->getX()+value.x*rect->getWidth()+OFX_UI_GLOBAL_WIDGET_SPACING, rect->getY()+value.y*rect->getHeight(), "(" +ofToString(getScaledValue().x,2) + ", " + ofToString(getScaledValue().y,2)+")"); 

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
    
    float getIncrement()
    {
        return increment; 
    }
    
    void setIncrement(float _increment)
	{
		increment = _increment; 
	}

    void mouseMoved(int x, int y ) 
    {
        if(rect->inside(x, y))
        {
            state = OFX_UI_STATE_OVER;         
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;        
        }
        stateChange();         
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
	
    void keyPressed(int key) 
    {		
		if(state == OFX_UI_STATE_OVER)
		{
			switch (key) 
			{
				case OF_KEY_RIGHT:
                {
                    ofPoint p = getScaledValue(); 
                    p.x +=increment;                 
					setValue(p); 
                }
					break;
					
				case OF_KEY_UP:
                {
                    ofPoint p = getScaledValue(); 
                    p.y -=increment; 
					setValue(p); 
                }
					break;
					
				case OF_KEY_LEFT:
                {
                    ofPoint p = getScaledValue(); 
                    p.x -=increment; 
					setValue(p); 
                }
					break;
					
				case OF_KEY_DOWN:
                {
                    ofPoint p = getScaledValue(); 
                    p.y +=increment; 
					setValue(p); 
                }
					break;					
					
				default:
					break;
			}
		}
    }
    
    void keyReleased(int key) 
    {
		
    }

    void windowResized(int w, int h) 
    {
		
    }
    
	void input(float x, float y)
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
//		cout << "X: " << rect->percentInside(x, y).x << endl;		
//		cout << "Y: " << rect->percentInside(x, y).y << endl;
		updateLabel(); 
	}
	
	void updateLabel()
	{
		label->setLabel(name + ": " + ofToString(getScaledValue().x,2) + ", " + ofToString(getScaledValue().y,2)); 		
	}
	
    void stateChange()
    {
        switch (state) {
            case OFX_UI_STATE_NORMAL:
            {            
                draw_fill_highlight = false;             
                draw_outline_highlight = false;             
				label->unfocus(); 				
            }
                break;
            case OFX_UI_STATE_OVER:
            {
                draw_fill_highlight = false;            
                draw_outline_highlight = true;    
				label->unfocus(); 
            }
                break;
            case OFX_UI_STATE_DOWN:
            {
                draw_fill_highlight = true;            
                draw_outline_highlight = true;             
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
	
	void setValue(ofPoint _value)
	{
		if(_value.x > rect->width)
		{
			_value.x = rect->width; 
		}
		else if(_value.x < 0)
		{
			_value.x = 0; 
		}
		
		if(_value.y > rect->height)
		{
			_value = rect->height; 
		}
		else if(_value.y < 0)
		{
			_value = 0; 
		}
		
		ofPoint p = _value; 
		p.x = p.x/rect->width; 
		p.y = p.y/rect->height; 		
        
		value = p;  
		triggerEvent(this);										
		updateLabel(); 		
	}
	
	ofPoint getValue()
	{
		return value; 
	}
	
	ofPoint getPercentValue()
	{
		return value; 
	}
	
	ofPoint getScaledValue()
	{
		ofPoint p = value; 
		p.x = p.x*rect->width; 
		p.y = p.y*rect->height; 		
		return p; 
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
	ofPoint value; 
    float increment;
	ofxUILabel *label; 
}; 

#endif
