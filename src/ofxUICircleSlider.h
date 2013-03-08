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

#ifndef OFXUI_CIRCLE_SLIDER
#define OFXUI_CIRCLE_SLIDER

#include "ofxUISlider.h"

class ofxUICircleSlider : public ofxUISlider
{
public:
    ofxUICircleSlider(float x, float y, float w, float _min, float _max, float _value, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUISlider()
    {
        useReference = false;         
        rect = new ofxUIRectangle(x,y,w,w); 
        init(w, w, _min, _max, &_value, _name, _size); 		
    }
    
    ofxUICircleSlider(float w, float _min, float _max, float _value, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUISlider()
    {
        useReference = false;                 
        rect = new ofxUIRectangle(0,0,w,w); 
        init(w, w, _min, _max, &_value, _name, _size); 
    }        
    
    ofxUICircleSlider(float x, float y, float w, float _min, float _max, float *_value, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUISlider()
    {
        useReference = true;                 
        rect = new ofxUIRectangle(x,y,w,w); 
        init(w, w, _min, _max, _value, _name, _size); 		
    }
    
    ofxUICircleSlider(float w, float _min, float _max, float *_value, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUISlider()
    {
        useReference = true;                 
        rect = new ofxUIRectangle(0,0,w,w); 
        init(w, w, _min, _max, _value, _name, _size); 
    }    
    
    void init(float w, float h, float _min, float _max, float *_value, string _name, int _size)
    {
        name = string(_name);  				
        kind = OFX_UI_WIDGET_CIRCLESLIDER;
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding);
		paddedRect->setParent(rect);     
        
        draw_fill = true; 
        draw_outline = true;
        
        value = *_value;                                               //the widget's value
        if(useReference)
        {
            valueRef = _value; 
        }
        else
        {
            valueRef = new float(); 
            *valueRef = value; 
        }
        
		max = _max; 
		min = _min; 
        labelPrecision = 2;
        
		if(value > max)
		{
			value = max; 
		}
		if(value < min)
		{
			value = min; 
		}
		
		value = ofMap(value, min, max, 0.0, 1.0, true); 
                
        label = new ofxUILabel(0,w+padding,(name+" LABEL"), name, _size); 	
        label->setDrawBack(false);
		label->setParent(label); 
		label->setRectParent(rect); 	
        label->setEmbedded(true);        
        increment = .0005;    
        inputDirection = OFX_UI_DIRECTION_SOUTHNORTH;
    }
    
    
    void drawBack() 
    {
        if(draw_back)
        {
            ofFill(); 
            ofSetColor(color_back); 
            ofCircle(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight(), rect->getHalfWidth());
        }
    }
    
    void drawOutline() 
    {
        if(draw_outline)
        {
            ofNoFill();
            ofSetColor(color_outline); 
            ofCircle(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight(), rect->getHalfWidth());
        } 
    }
    
    virtual void drawFill()
    {
        if(draw_fill)
        {			
            ofFill(); 
            ofSetColor(color_fill); 
            ofCircle(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight(), value*rect->getHalfWidth());
        }
    }
    
    virtual void drawFillHighlight()
    {
        if(draw_fill_highlight)
        {
            ofFill(); 
            ofSetColor(color_fill_highlight); 
            ofCircle(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight(), value*rect->getHalfWidth());
            ofSetColor(label->getColorFillHighlight());             
            label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*.5, ofToString(getScaledValue(),labelPrecision)); 
        }        
    }
    
    virtual void drawOutlineHighlight()
    {
        if(draw_outline_highlight)
        {
            ofNoFill();
            ofSetColor(color_outline_highlight); 
            ofCircle(rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight(), rect->getHalfWidth());
            if(!draw_fill_highlight)
            {
                ofSetColor(label->getColorFill()); 
                label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*.5, ofToString(getScaledValue(),labelPrecision)); 
            }
        }
    }
    
    void mouseDragged(int x, int y, int button) 
    {
        if(hit)
        {            
            switch(inputDirection)
            {
                case OFX_UI_DIRECTION_NORTHSOUTH:
                    value -= increment*(hitPoint.y-y); 
                    valueClamp();                 
                    break;
                case OFX_UI_DIRECTION_SOUTHNORTH:
                    value += increment*(hitPoint.y-y);
                    valueClamp(); 
                    break;                    
                case OFX_UI_DIRECTION_EASTWEST:
                    value += increment*(hitPoint.x-x);
                    valueClamp(); 
                    break;
                case OFX_UI_DIRECTION_WESTEAST:
                    value -= increment*(hitPoint.x-x); 
                    valueClamp();                     
                    break;
            }
            
            hitPoint = ofPoint(x,y);    
            updateValueRef();
			triggerEvent(this);             
            state = OFX_UI_STATE_DOWN;         
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
            hitPoint = ofPoint(x,y); 
            state = OFX_UI_STATE_DOWN;     
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
			triggerEvent(this); 
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;         
        }
        stateChange();   
        hit = false; 
    }
    
    void valueClamp()
    {
        if(value > 1.0)
        {
            value = 1.0;
        }
        else if(value < 0.0)
        {
            value = 0.0;
        }                        
    }
    
    void setInputDirection(ofxWidgetInputDirection _inputDirection)
    {
        inputDirection = _inputDirection; 
    }
    
    void updateLabel()
	{
        
	}
    
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
		paddedRect->height += label->getPaddingRect()->height; 

		ofxUIRectangle *labelrect = label->getRect(); 
        
        while(labelrect->width > rect->width)
        {
            string labelstring = label->getLabel();
            string::iterator it;
            it=labelstring.end();
            it--; 
            labelstring.erase (it); 
            label->setLabel(labelstring);
        }                    
        
        float w = labelrect->getWidth(); 
        float pw = rect->getWidth(); 
        
        labelrect->x = (int)(pw*.5 - w*.5-padding*.5); 
    }	
    
    virtual bool isHit(float x, float y)
    {
        if(visible && ofDist(x, y, rect->getX()+rect->getHalfWidth(), rect->getY()+rect->getHalfHeight()) < rect->getHalfWidth())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
protected:
    ofxWidgetInputDirection inputDirection; 
    ofPoint hitPoint;     
}; 

#endif
