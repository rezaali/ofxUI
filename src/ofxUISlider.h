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

#ifndef OFXUI_SLIDER
#define OFXUI_SLIDER

#include "ofxUIWidgetWithLabel.h"

class ofxUISlider : public ofxUIWidgetWithLabel
{
public:
    ofxUISlider() {}
    
    ofxUISlider(string _name, float _min, float _max, float _value, float w, float h, float x = 0, float y = 0)
    {
        useReference = false;
        init(_name, _min, _max, &_value, w, h, x, y);
    }

    ofxUISlider(string _name, float _min, float _max, float *_value, float w, float h, float x = 0, float y = 0)
    {
        useReference = true;
        init(_name, _min, _max, _value, w, h, x, y);
    }
    
    // DON'T USE THE NEXT CONSTRUCTORS
    // This is maintained for backward compatibility and will be removed on future releases
    
    ofxUISlider(float x, float y, float w, float h, float _min, float _max, float _value, string _name)
    {
        useReference = false;         
        init(_name, _min, _max, &_value, w, h, x, y);
        ofLogWarning("OFXUISLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ofxUISlider(float w, float h, float _min, float _max, float _value, string _name)
    {
        useReference = false;         
        init(_name, _min, _max, &_value, w, h, 0, 0);
        ofLogWarning("OFXUISLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }    
    
    ofxUISlider(float x, float y, float w, float h, float _min, float _max, float *_value, string _name)
    {
        useReference = true; 
        init(_name, _min, _max, _value, w, h, x, y);
        ofLogWarning("OFXUISLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ofxUISlider(float w, float h, float _min, float _max, float *_value, string _name)
    {
        useReference = true; 
        init(_name, _min, _max, _value, w, h, 0, 0);
        ofLogWarning("OFXUISLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ~ofxUISlider()
    {
        if(!useReference)
        {
            delete valueRef; 
        }
    }   
    
    virtual void init(string _name, float _min, float _max, float *_value, float w, float h, float x, float y)
    {
        rect = new ofxUIRectangle(x,y,w,h);
        name = _name; 				
		if(w > h)
		{
			kind = OFX_UI_WIDGET_SLIDER_H;  			
		}
		else 
		{
			kind = OFX_UI_WIDGET_SLIDER_V;  			
		}
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding);
		paddedRect->setParent(rect);     
        
        draw_fill = true; 
        
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
        
		if(kind == OFX_UI_WIDGET_SLIDER_H)
		{
			label = new ofxUILabel(0,h+padding,(name+" LABEL"), (name + ": " + ofToString(max,labelPrecision)), OFX_UI_FONT_SMALL); 
		}
		else 
		{
			label = new ofxUILabel(0,h+padding,(name+" LABEL"), name, OFX_UI_FONT_SMALL); 	
		}
        
		label->setParent(label); 
		label->setRectParent(rect); 
        label->setEmbedded(true);
        increment = fabs(max - min) / 10.0;         
    }
    
    virtual void update()
    {
        if(useReference)
        {
            value = ofMap(*valueRef, min, max, 0.0, 1.0, true);
        }
    }

    virtual void setDrawPadding(bool _draw_padded_rect)
	{
		draw_padded_rect = _draw_padded_rect; 
        label->setDrawPadding(false);
	}
    
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline)
	{
		draw_padded_rect_outline = _draw_padded_rect_outline; 
        label->setDrawPaddingOutline(false);
	}  
    
    virtual void drawBack() 
    {
        if(draw_back)
        {
            ofFill(); 
            ofSetColor(color_back); 
            rect->draw(); 
        }
    }
    
    virtual void drawOutline() 
    {
        if(draw_outline)
        {
            ofNoFill();
            ofSetColor(color_outline); 
            rect->draw(); 
        }
    }
    
    virtual void drawOutlineHighlight() 
    {
        if(draw_outline_highlight)
        {
            ofNoFill();
            ofSetColor(color_outline_highlight); 
            rect->draw();          
        }
    }    
    
    virtual void drawFill() 
    {
        if(draw_fill)
        {			
            ofFill(); 
            ofSetColor(color_fill); 
			if(kind == OFX_UI_WIDGET_SLIDER_H)
			{			   
				ofRect(rect->getX(), rect->getY(), rect->getWidth()*value, rect->getHeight()); 
			}
			else 
			{
				ofRect(rect->getX(), rect->getY()+rect->getHeight(), rect->getWidth(), -rect->getHeight()*value); 
			}
        }
    }
    
    virtual void drawFillHighlight() 
    {
        if(draw_fill_highlight)
        {
            ofFill(); 
            ofSetColor(color_fill_highlight); 
			if(kind == OFX_UI_WIDGET_SLIDER_H)
			{			   
				ofRect(rect->getX(), rect->getY(), rect->getWidth()*value, rect->getHeight()); 
			}
			else 
			{
				ofRect(rect->getX(), rect->getY()+rect->getHeight(), rect->getWidth(), -rect->getHeight()*value); 
			}	
			if(kind == OFX_UI_WIDGET_SLIDER_V)
			{
				label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*value, ofToString(getScaledValue(),labelPrecision)); 
			}
        }        
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
					setValue(getScaledValue()+increment); 
					triggerEvent(this); 
					break;
                    
				case OF_KEY_UP:
					setValue(getScaledValue()+increment); 
					triggerEvent(this); 
					break;
					
				case OF_KEY_LEFT:
					setValue(getScaledValue()-increment); 					
					triggerEvent(this); 
					break;
                    
				case OF_KEY_DOWN:
					setValue(getScaledValue()-increment); 					
					triggerEvent(this); 
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
    
    float getIncrement()
    {
        return increment; 
    }
    
    void setIncrement(float _increment)
	{
		increment = _increment; 
	}
    
	virtual void input(float x, float y)
	{
		if(kind == OFX_UI_WIDGET_SLIDER_H)
		{
			value = rect->percentInside(x, y).x; 
		}
		else 
		{
			value = 1.0-rect->percentInside(x, y).y; 
		}	
        
        if(value > 1.0)
        {
            value = 1.0;
        }
        else if(value < 0.0)
        {
            value = 0.0;
        }        
        updateValueRef();        
		updateLabel(); 
	}
    
    void updateValueRef()
    {
        (*valueRef) = getScaledValue();  
    }    

	virtual void updateLabel()
	{
		if(kind == OFX_UI_WIDGET_SLIDER_H)
		{
			label->setLabel(name + ": " + ofToString(getScaledValue(),labelPrecision)); 		
		}		
	}
	
    virtual void stateChange()
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
	
	void setValue(float _value)
	{
		value = ofMap(_value, min, max, 0.0, 1.0, true);		
        updateValueRef();        
		updateLabel(); 		
	}
		
	float getValue()
	{
		return value; 
	}
	
	float getPercentValue()
	{
		return value; 
	}
	
	float getScaledValue()
	{
		return ofMap(value, 0.0, 1.0, min, max, true); 
	}
    
	ofxUILabel *getLabel()
	{
		return label; 
	}
    
    void setLabelVisible(bool _labelVisible)
    {
        label->setVisible(_labelVisible);
    }
    
    void setVisible(bool _visible)
    {
        visible = _visible; 
        label->setVisible(visible); 
    }
	
	virtual void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
		paddedRect->height += label->getPaddingRect()->height; 
        if(label->getPaddingRect()->width > paddedRect->width)
        {
            paddedRect->width = label->getPaddingRect()->width;				
        }
        updateValueRef();                
        updateLabel(); 
	}
	
    void setLabelPrecision(int _precision) {
        labelPrecision = _precision;
        updateValueRef();        
        updateLabel();
    }
    
    void setMax(float _max)
    {
        setMaxAndMin(_max, min); 
    }

    float getMax()
    {
        return max; 
    }
    
    void setMin(float _min)
    {
        setMaxAndMin(max, _min); 
    }
    
    float getMin()
    {
        return min; 
    }
    
    ofVec2f getMaxAndMind()
    {
        return ofVec2f(max, min); 
    }
    
    void setMaxAndMin(float _max, float _min)
    {
        max = _max; 
        min = _min; 
		
		value = ofMap(value, 0, 1.0, min, max, true);         
		value = ofMap(value, min, max, 0.0, 1.0, true); 
        updateValueRef();        
        updateLabel(); 
    }

    bool isDraggable()
    {
        return true; 
    }
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	float value, increment; 
    float *valueRef; 
    bool useReference;     
	float max, min;  
    int labelPrecision;
}; 

#endif
