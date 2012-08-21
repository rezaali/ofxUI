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

#ifndef OFXUI_RANGE_SLIDER
#define OFXUI_RANGE_SLIDER

#include "ofxUIWidgetWithLabel.h"

class ofxUIRangeSlider : public ofxUIWidgetWithLabel
{
public:
    ofxUIRangeSlider(string _name, float _min, float _max, float _valuelow, float _valuehigh, float w, float h, 
                     float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = false;                                 
        init(_name, _min, _max, &_valuelow, &_valuehigh, w, h, x, y, _size);
    }

    ofxUIRangeSlider(string _name, float _min, float _max, float *_valuelow, float *_valuehigh, float w, float h, 
                     float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = true;                         
        init(_name, _min, _max, _valuelow, _valuehigh, w, h, x, y, _size);
    }

    // DON'T USE THE NEXT CONSTRUCTORS
    // This is maintained for backward compatibility and will be removed on future releases
    
    ofxUIRangeSlider(float x, float y, float w, float h, float _min, float _max, float _valuelow, float _valuehigh, string _name, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = false;                                 
        init(_name, _min, _max, &_valuelow, &_valuehigh, w, h, x, y, _size);
        ofLogWarning("OFXUIRANGESLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ofxUIRangeSlider(float w, float h, float _min, float _max, float _valuelow, float _valuehigh, string _name, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = false;                                 
        init(_name, _min, _max, &_valuelow, &_valuehigh, w, h, 0, 0, _size);
        ofLogWarning("OFXUIRANGESLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ofxUIRangeSlider(float x, float y, float w, float h, float _min, float _max, float *_valuelow, float *_valuehigh, string _name, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = true;                         
        init(_name, _min, _max, _valuelow, _valuehigh, w, h, x, y, _size);
        ofLogWarning("OFXUIRANGESLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ofxUIRangeSlider(float w, float h, float _min, float _max, float *_valuelow, float *_valuehigh, string _name, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = true;                                 
        init(_name, _min, _max, _valuelow, _valuehigh, w, h, 0, 0, _size);
        ofLogWarning("OFXUIRANGESLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ~ofxUIRangeSlider()    
    {
        if(!useReference)
        {
            delete valuelowRef; 
            delete valuehighRef;             
        }        
    }
    
    void init(string _name, float _min, float _max, float *_valuelow, float *_valuehigh, float w, float h, 
              float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL)
    {
        rect = new ofxUIRectangle(x,y,w,h);
        name = _name; 				
		if(w > h)
		{
			kind = OFX_UI_WIDGET_RSLIDER_H;  			
		}
		else 
		{
			kind = OFX_UI_WIDGET_RSLIDER_V;  			
		}
		
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding);
		paddedRect->setParent(rect); 
		
        draw_fill = true; 
        
        valuelow = *_valuelow;                                                  //the widget's value
        valuehigh = *_valuehigh;                                                //the widget's value		
        
        if(useReference)
        {
            valuelowRef = _valuelow;                                               
            valuehighRef = _valuehigh;                                                         
        }
        else
        {
            valuelowRef = new float(); 
            valuehighRef = new float();             
            *valuelowRef = valuelow;                                               
            *valuehighRef = valuehigh;                                                         
        }
		
		max = _max; 
		min = _min; 
		hitHigh = false; 
		hitLow = false;
		hitCenter = false; 
		
		if(valuelow > max)
		{
			valuelow = max; 
		}
		if(valuelow < min)
		{
			valuelow = min; 
		}
		
		if(valuehigh > max)
		{
			valuehigh = max; 
		}
		if(valuehigh < min)
		{
			valuehigh = min; 
		}
		
		valuelow = ofMap(valuelow, min, max, 0.0, 1.0, true); 
		valuehigh = ofMap(valuehigh, min, max, 0.0, 1.0, true); 
		labelPrecision = 2;
        
		if(kind == OFX_UI_WIDGET_RSLIDER_H)
		{
			label = new ofxUILabel(0,h+padding,(name+" LABEL"), (name + ": " + ofToString(getScaledValueLow(),labelPrecision) + " " + ofToString(getScaledValueHigh(),labelPrecision)), _size); 
		}
		else 
		{
			label = new ofxUILabel(0,h+padding,(name+" LABEL"), name, _size); 	
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
            valuelow = ofMap(*valuelowRef, min, max, 0.0, 1.0, true); 
            valuehigh = ofMap(*valuehighRef, min, max, 0.0, 1.0, true);         
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
    
    virtual void drawFill()
    {
        if(draw_fill)
        {			
            ofFill(); 
            ofSetColor(color_fill); 
			if(kind == OFX_UI_WIDGET_RSLIDER_H)
			{			   
				ofRect(rect->getX()+rect->getWidth()*valuelow, rect->getY(), rect->getWidth()*(valuehigh-valuelow), rect->getHeight()); 
			}
			else 
			{
				ofRect(rect->getX(), rect->getY()+(1.0-valuehigh)*rect->getHeight(), rect->getWidth(), rect->getHeight()*(valuehigh-valuelow)); 
			}
        }
    }
    
    virtual void drawFillHighlight()
    {
        if(draw_fill_highlight)
        {
            ofFill(); 
            ofSetColor(color_fill_highlight); 
			if(kind == OFX_UI_WIDGET_RSLIDER_H)
			{			   
				ofRect(rect->getX()+rect->getWidth()*valuelow, rect->getY(), rect->getWidth()*(valuehigh-valuelow), rect->getHeight()); 
			}
			else 
			{
				ofRect(rect->getX(), rect->getY()+(1.0-valuehigh)*rect->getHeight(), rect->getWidth(), rect->getHeight()*(valuehigh-valuelow)); 
			}	
			if(kind == OFX_UI_WIDGET_RSLIDER_V)
			{
				label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*valuehigh, ofToString(getScaledValueHigh(),labelPrecision)); 
				label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*valuelow, ofToString(getScaledValueLow(),labelPrecision)); 
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
            hitValueHigh = valuehigh; 
            hitValueLow = valuelow; 
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
            hitValueHigh = valuehigh; 
            hitValueLow = valuelow; 
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
        hitHigh = false;  
        hitLow = false; 
        hitCenter = false; 
    }
	
    void keyPressed(int key) 
    {		
		if(state == OFX_UI_STATE_OVER)
		{
			switch (key) 
			{
				case OF_KEY_RIGHT:
					setValueHigh(getScaledValueHigh()+increment); 					
					setValueLow(getScaledValueLow()+increment); 															
					triggerEvent(this); 
					break;
                    
				case OF_KEY_LEFT:
					setValueHigh(getScaledValueHigh()-increment); 					
					setValueLow(getScaledValueLow()-increment); 										
					triggerEvent(this); 					
					break;
					
					
				case OF_KEY_UP:
					setValueHigh(getScaledValueHigh()+increment); 
					setValueLow(getScaledValueLow()-increment); 					
					triggerEvent(this); 
					break;
					
					
				case OF_KEY_DOWN:
					setValueHigh(getScaledValueHigh()-increment); 
					setValueLow(getScaledValueLow()+increment); 					
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
    
    void setIncrement(float _increment)
	{
		increment = _increment; 
	}

	void input(float x, float y)
	{
        float v = 0; 
        
		if(kind == OFX_UI_WIDGET_RSLIDER_H)
		{	
            v = rect->percentInside(x, y).x; 						            			
		}
		else 
		{			
            v = 1.0-rect->percentInside(x, y).y; 						  				
		}
        
        if(hitHigh)
        {								
            valuehigh = v;	
        }			
        else if(hitLow)
        {
            valuelow = v; 
        }
        else if(hitCenter)
        {
            valuehigh +=(v-hitPoint); 
            valuelow +=(v-hitPoint);
            hitPoint = v; 
        }
        else 
        {
            float dvh = fabs(valuehigh - v); 
            float dvl = fabs(valuelow - v); 
            if(dvh < .05 || v > valuehigh)
            {
                valuehigh = v;
                hitHigh = true; 					
            }
            else if(dvl < .05 || v < valuelow)
            {
                valuelow = v; 
                hitLow = true; 
            }	
            else 
            {
                hitCenter = true; 
                hitPoint = v; 
            }
        }			
        
		if(valuehigh < valuelow && hitHigh)			
		{
            valuehigh = hitValueLow; 
			hitHigh = false; 
			hitLow = true; 
		}				
		else if(valuelow > valuehigh && hitLow)			
		{
            valuelow = hitValueHigh; 
			hitHigh = true; 
			hitLow = false; 
		}
        
        if(valuehigh > 1.0)
        {
            valuehigh = 1.0; 
        }
        else if(valuehigh < 0.0)
        {
            valuehigh = 0.0; 
        }
        
        if(valuelow < 0.0)
        {
            valuelow = 0.0; 
        }
        else if(valuelow > 1.0)
        {
            valuelow = 1.0; 
        }

        updateValueRef(); 
		updateLabel(); 
	}
	
    void updateValueRef()
    {
        (*valuelowRef) = getScaledValueLow();  
        (*valuehighRef) = getScaledValueHigh();          
    }

	void updateLabel()
	{
		if(kind == OFX_UI_WIDGET_RSLIDER_H)
		{
			label->setLabel(name + ": " + ofToString(getScaledValueLow(),labelPrecision) + " " + ofToString(getScaledValueHigh(),labelPrecision)); 		
		}		
	}
	
    void stateChange()
    {
        if(valuehigh > 0)
        {
            draw_fill = true; 
        }
        else 
        {
            draw_fill = false; 
        }
        
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
	
    void setVisible(bool _visible)
    {
        visible = _visible; 
        label->setVisible(visible); 
    }
    
	void setValueLow(float _value)
	{			
		valuelow = ofMap(_value, min, max, 0.0, 1.0, true); 
        updateValueRef(); 
		updateLabel(); 		
	}

	void setValueHigh(float _value)
	{
		valuehigh = ofMap(_value, min, max, 0.0, 1.0, true); 
        updateValueRef(); 
		updateLabel(); 		
	}
	
	float getPercentValueLow()
	{
		return valuelow; 
	}

	float getPercentValueHigh()
	{
		return valuehigh; 
	}
	
	float getScaledValueLow()
	{
		return ofMap(valuelow, 0.0, 1.0, min, max, true); 
	}

	float getScaledValueHigh()
	{
		return ofMap(valuehigh, 0.0, 1.0, min, max, true); 
	}
	
	ofxUILabel *getLabel()
	{
		return label; 
	}
    
    void setLabelVisible(bool _labelVisible)
    {
        label->setVisible(_labelVisible);
    }
	
    void setLabelPrecision(int _precision) 
    {
        labelPrecision = _precision;
        updateValueRef();
        updateLabel();
    }
    
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
		paddedRect->height += label->getPaddingRect()->height; 
		if(kind == OFX_UI_WIDGET_RSLIDER_V)
		{
			if(label->getPaddingRect()->width > paddedRect->width)
			{
				paddedRect->width = label->getPaddingRect()->width+padding;				
			}
		}
	}	
    
    void setMax(float _max)
    {
        setMaxAndMin(_max, min); 
    }
    
    void setMin(float _min)
    {
        setMaxAndMin(max, _min); 
    }
    
    void setMaxAndMin(float _max, float _min)
    {
        max = _max; 
        min = _min; 
		
		valuelow= ofMap(valuelow, 0, 1.0, min, max, true);         
		valuelow = ofMap(valuelow, min, max, 0.0, 1.0, true); 

		valuehigh = ofMap(valuehigh, 0, 1.0, min, max, true);         
		valuehigh = ofMap(valuehigh, min, max, 0.0, 1.0, true); 
        updateValueRef();        
        updateLabel(); 
    }

    bool isDraggable()
    {
        return true; 
    }

    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	float valuelow, valuehigh, increment; 
    float *valuelowRef; 
    float *valuehighRef;    
    bool useReference;         
    float hitValueLow, hitValueHigh; 
	bool hitHigh, hitLow, hitCenter; 
	float hitPoint; 
	float max, min; 
    int labelPrecision;        
}; 

#endif
