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

#include "ofxUIWidgetWithLabel.h"

class ofxUI2DPad : public ofxUIWidgetWithLabel
{
public:
    ofxUI2DPad(string _name, ofPoint _rangeX, ofPoint _rangeY, ofPoint _value, float w, float h, float x = 0, float y = 0) : ofxUIWidgetWithLabel()
    {
        useReference = false;                  
        init(_name, _rangeX, _rangeY, &_value, w, h, x, y);
    }	

    ofxUI2DPad(string _name, ofPoint _rangeX, ofPoint _rangeY, ofPoint *_value, float w, float h, float x = 0, float y = 0) : ofxUIWidgetWithLabel()
    {
        useReference = true; 
        init(_name, _rangeX, _rangeY, _value, w, h, x, y);
    }	

    // DON'T USE THE NEXT CONSTRUCTORS
    // This is maintained for backward compatibility and will be removed on future releases
    
    ofxUI2DPad(float x, float y, float w, float h, ofPoint _value, string _name) : ofxUIWidgetWithLabel()
    {
        useReference = false;                         
        init(_name, ofPoint(0,w), ofPoint(0,h), &_value, w, h, x, y);
//        ofLogWarning("OFXUI2DPAD: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }

    ofxUI2DPad(float x, float y, float w, float h, ofPoint _rangeX, ofPoint _rangeY, ofPoint _value, string _name) : ofxUIWidgetWithLabel()
    {
        useReference = false;                  
        init(_name, _rangeX, _rangeY, &_value, w, h, x, y);
//        ofLogWarning("OFXUI2DPAD: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ofxUI2DPad(float w, float h, ofPoint _value, string _name) : ofxUIWidgetWithLabel()
    {
        useReference = false;                         
        init(_name, ofPoint(0,w), ofPoint(0,h), &_value, w, h, 0, 0);
//        ofLogWarning("OFXUI2DPAD: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
	
    ofxUI2DPad(float w, float h, ofPoint _rangeX, ofPoint _rangeY, ofPoint _value, string _name) : ofxUIWidgetWithLabel()
    {
        useReference = false;                         
        init(_name, _rangeX, _rangeY, &_value, w, h, 0, 0);
//        ofLogWarning("OFXUI2DPAD: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ofxUI2DPad(float x, float y, float w, float h, ofPoint *_value, string _name) : ofxUIWidgetWithLabel()
    {
        useReference = true; 
        init(_name, ofPoint(0,w), ofPoint(0,h), _value, w, h, x, y);
//        ofLogWarning("OFXUI2DPAD: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ofxUI2DPad(float x, float y, float w, float h, ofPoint _rangeX, ofPoint _rangeY, ofPoint *_value, string _name) : ofxUIWidgetWithLabel()
    {
        useReference = true; 
        init(_name, _rangeX, _rangeY, _value, w, h, x, y);
//        ofLogWarning("OFXUI2DPAD: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ofxUI2DPad(float w, float h, ofPoint *_value, string _name) : ofxUIWidgetWithLabel()
    {
        useReference = true;         
        init(_name, ofPoint(0,w), ofPoint(0,h), _value, w, h, 0, 0);
//        ofLogWarning("OFXUI2DPAD: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
	
    ofxUI2DPad(float w, float h, ofPoint _rangeX, ofPoint _rangeY, ofPoint *_value, string _name) : ofxUIWidgetWithLabel()
    {
        useReference = true;         
        init(_name, _rangeX, _rangeY, _value, w, h, 0, 0);
//        ofLogWarning("OFXUI2DPAD: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ~ofxUI2DPad()
    {
        if(!useReference)
        {
            delete valueRef; 
        }        
    }
    
    void init(string _name, ofPoint _rangeX, ofPoint _rangeY, ofPoint *_value, float w, float h, float x = 0, float y = 0)
    {
        rect = new ofxUIRectangle(x,y,w,h);
		name = string(_name);
		kind = OFX_UI_WIDGET_2DPAD; 		
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
            valueRef = new ofPoint(); 
            *valueRef = value; 
        }

        rangeX = _rangeX; 
        rangeY = _rangeY; 
		labelPrecision = 2;
        
		value.x = ofMap(value.x, rangeX.x, rangeX.y, 0.0, 1.0);
		value.y = ofMap(value.y, rangeY.x, rangeY.y, 0.0, 1.0);
		
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
			value.y = 1;
		}
		else if(value.y < 0)
		{
			value.y = 0;
		}
		
		label = new ofxUILabel(0,h+padding,(name+" LABEL"), (name + ": " + ofToString(getScaledValue().x,labelPrecision) + ", " + ofToString(getScaledValue().y,labelPrecision)), OFX_UI_FONT_SMALL); 		
		label->setParent(label); 
		label->setRectParent(rect);         
        label->setEmbedded(true);
        
        float horizontalRange = abs(rangeX.x - rangeX.y);
        float verticalRange = abs(rangeY.x - rangeY.y);
        increment = MIN(horizontalRange, verticalRange) / 10.0;
    }
    
    virtual void update()
    {
        if(useReference)
        {
            value.x = ofMap(valueRef->x, rangeX.x, rangeX.y, 0.0, 1.0, true);
            value.y = ofMap(valueRef->y, rangeY.x, rangeY.y, 0.0, 1.0, true);
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
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofRect(rect->getX()+value.x*rect->getWidth(), rect->getY()+value.y*rect->getHeight(), OFX_UI_GLOBAL_WIDGET_SPACING, OFX_UI_GLOBAL_WIDGET_SPACING); 
			ofSetRectMode(OF_RECTMODE_CORNER);			
			
			ofLine(rect->getX()+value.x*rect->getWidth(),  rect->getY(), rect->getX()+value.x*rect->getWidth(),  rect->getY()+rect->getHeight()); 
			ofLine(rect->getX(),  rect->getY()+value.y*rect->getHeight(), rect->getX()+rect->getWidth(),  rect->getY()+value.y*rect->getHeight()); 			
        }
    }
    
    virtual void drawFillHighlight()
    {
        if(draw_fill_highlight)
        {
            ofFill(); 
            ofSetColor(color_fill_highlight); 
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofRect(rect->getX()+value.x*rect->getWidth(), rect->getY()+value.y*rect->getHeight(), OFX_UI_GLOBAL_WIDGET_SPACING, OFX_UI_GLOBAL_WIDGET_SPACING); 
			ofSetRectMode(OF_RECTMODE_CORNER);			
			
			ofLine(rect->getX()+value.x*rect->getWidth(),  rect->getY(), rect->getX()+value.x*rect->getWidth(),  rect->getY()+rect->getHeight()); 
			ofLine(rect->getX(),  rect->getY()+value.y*rect->getHeight(), rect->getX()+rect->getWidth(),  rect->getY()+value.y*rect->getHeight()); 			
			
			label->drawString(rect->getX()+value.x*rect->getWidth()+OFX_UI_GLOBAL_WIDGET_SPACING, rect->getY()+value.y*rect->getHeight(), "(" +ofToString(getScaledValue().x,labelPrecision) + ", " + ofToString(getScaledValue().y,labelPrecision)+")"); 

        }        
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
                    p.x+=increment; 
                    value.x = ofMap(p.x, rangeX.x, rangeX.y, 0.0, 1.0);                    
                    updateValueRef();                                            
                    updateLabel();                     
                    triggerEvent(this);			
                }
					break;
					
				case OF_KEY_UP:
                {
                    ofPoint p = getScaledValue();         
                    p.y +=increment; 
                    value.y = ofMap(p.y, rangeY.x, rangeY.y, 0.0, 1.0);                    
                    updateValueRef();                                            
                    updateLabel();                     
                    triggerEvent(this);	
                }
					break;
					
				case OF_KEY_LEFT:
                {
                    ofPoint p = getScaledValue();         
                    p.x-=increment; 
                    value.x = ofMap(p.x, rangeX.x, rangeX.y, 0.0, 1.0);                    
                    updateValueRef();                                            
                    updateLabel();                     
                    triggerEvent(this);		
                }
					break;
					
				case OF_KEY_DOWN:
                {
                    ofPoint p = getScaledValue();         
                    p.y -=increment; 
                    value.y = ofMap(p.y, rangeY.x, rangeY.y, 0.0, 1.0);                    
                    updateValueRef();                        
                    updateLabel();                     
                    triggerEvent(this);	
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
        updateValueRef();          							                
		updateLabel(); 
	}
	
    void updateValueRef()
    {
        (*valueRef) = getScaledValue();
    }
    
	void updateLabel()
	{
		label->setLabel(name + ": " + ofToString(getScaledValue().x,labelPrecision) + ", " + ofToString(getScaledValue().y,labelPrecision)); 		
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
	
    void setVisible(bool _visible)
    {
        visible = _visible; 
        label->setVisible(visible); 
    }
    
	void setValue(ofPoint _value)
	{
		if(_value.x > rangeX.y)
		{
			_value.x = rangeX.y;
		}
		else if(_value.x < rangeX.x)
		{
			_value.x = rangeX.x; 
		}
		
		if(_value.y > rangeY.y)
		{
			_value.y = rangeY.y;
		}
		else if(_value.y < rangeY.x)
		{
			_value.y = rangeY.x;
		}

		                        
        value.x = ofMap(_value.x, rangeX.x, rangeX.y, 0.0, 1.0);
		value.y = ofMap(_value.y, rangeY.x, rangeY.y, 0.0, 1.0);
        updateValueRef();        
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
		p.x = ofMap(p.x, 0, 1, rangeX.x, rangeX.y); 
		p.y = ofMap(p.y, 0, 1, rangeY.x, rangeY.y); 
		return p; 
	}
    
	ofxUILabel *getLabel()
	{
		return label; 
	}
	
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
        label->getRect()->setY(rect->getHeight()+padding);
        paddedRect->height += label->getPaddingRect()->height+padding;
	}	
    
    bool isDraggable()
    {
        return true; 
    }
    
    void setLabelPrecision(int _precision)
    {
        labelPrecision = _precision;
        updateValueRef();
        updateLabel();
    }

    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	ofPoint value; 
	ofPoint *valueRef;     
    float increment;
    int labelPrecision;     
    bool useReference; 
    ofPoint rangeX, rangeY; 
}; 

#endif
