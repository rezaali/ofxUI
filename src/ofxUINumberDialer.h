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

#ifndef OFXUI_NUMBER_DIALER
#define OFXUI_NUMBER_DIALER

#include "ofxUIWidgetWithLabel.h"
#include <math.h>

class ofxUINumberDialer : public ofxUIWidgetWithLabel
{
public:
    ofxUINumberDialer(float x, float y, float _min, float _max, float _value, int _precision, string _name, int _size)
    {
        useReference = false;                                 
        rect = new ofxUIRectangle(x,y,0,0); 
        init(_min, _max, &_value, _precision, _name, _size); 
    }
    
    ofxUINumberDialer(float _min, float _max, float _value, int _precision, string _name, int _size)
    {
        useReference = false;                                 
        rect = new ofxUIRectangle(0,0,0,0); 
        init(_min, _max, &_value, _precision, _name, _size); 
    }    
    
    ofxUINumberDialer(float x, float y, float _min, float _max, float *_value, int _precision, string _name, int _size)
    {
        useReference = true;                                         
        rect = new ofxUIRectangle(x,y,0,0); 
        init(_min, _max, _value, _precision, _name, _size); 
    }
    
    ofxUINumberDialer(float _min, float _max, float *_value, int _precision, string _name, int _size)
    {
        useReference = true;                                  
        rect = new ofxUIRectangle(0,0,0,0); 
        init(_min, _max, _value, _precision, _name, _size); 
    }    
    
    ~ofxUINumberDialer()
    {
        if(!useReference)
        {
            delete value; 
        }        
    }
    
    void init(float _min, float _max, float *_value, int _precision, string _name, int _size)
    {
		name = _name; 		
		kind = OFX_UI_WIDGET_NUMBERDIALER;  		
        
        if(useReference)
        {
            value = _value; 
        }
        else
        {
            value = new float(); 
            *value = (*_value); 
        }
        
        max = _max; 
        min = _min; 
        if(*value > max)
        {
            *value = max;             
        }
        else if(*value < min)
        {
            *value = min; 
        }
        precision = _precision; 
        currentPrecisionZone = 1;
        
        
        string minString = ofToString(min, precision); 
        string maxString = ofToString(max, precision);         
        if(minString.length() > maxString.length())
        {
            textstring = minString; 
        }
        else
        {
            textstring = "+"+maxString;
        }

        string temp = "";
        if(precision > 0)
        {
            temp+="..";
            hasPeriod = 1;
        }
        else
        {
            temp += "+";            
            hasPeriod = 0;
        }
        
        numOfPrecisionZones = textstring.length()-1;             //1 for the "-/+" sign & 1 for the "."
        
		displaystring = textstring;
        
		paddedRect = new ofxUIRectangle(-padding, -padding, padding*2.0, padding*2.0);
		paddedRect->setParent(rect); 		
                
        for(int i = 0; i < numOfPrecisionZones; i++)
        {
            temp+="0";
        }
		
        label = new ofxUILabel(padding*2.0,0,(name+" LABEL"), temp, _size);
		label->setParent(label); 
		label->setRectParent(rect);
        label->setEmbedded(true);
        label->setVisible(false);
        draw_fill = true; 
    }
    
    virtual void update()
    {
        if(useReference)
        {
            setTextString(numToString(abs(*value), precision, numOfPrecisionZones, '0'));
        }
    }
    
    
    virtual void drawFill()
    {
        if(draw_fill)
        {
            ofFill();
            ofSetColor(color_fill);
            float x = label->getRect()->getX();
            float y = label->getRect()->getY()+label->getRect()->getHeight();
            float w = label->getStringWidth("_");

            for(int i = 0; i < displaystring.size(); i++)
            {
                float tw = label->getStringWidth(displaystring.substr(i,1));
                float delta = w/2.0 - tw/2.0;
                label->drawString(x+i*w+delta, y, displaystring.substr(i,1));
            }            
        }
    }
    
    virtual void drawFillHighlight()
    {
        if(draw_fill_highlight)
        {
            ofFill();
            ofSetColor(color_fill_highlight);
            float x = label->getRect()->getX();
            float y = label->getRect()->getY()+label->getRect()->getHeight();
            float w = label->getStringWidth("_");            
            ofRect(x+currentPrecisionZone*w,y+padding*.5,w, padding*.5);
            
            for(int i = 0; i < displaystring.size(); i++)
            {
                float tw = label->getStringWidth(displaystring.substr(i,1));
                float delta = w/2.0 - tw/2.0; 
                label->drawString(x+i*w+delta, y, displaystring.substr(i,1));
            }        
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
    
    void calculatePrecisionZone()
    {
        currentPrecisionZone = ceil(ofMap(hitPoint.x,rect->getX(),rect->getX()+rect->getWidth(),-1, displaystring.size()-1));
    }
	
    float getValue()
    {
        return *value; 
    }
    
    void setValue(float _value)
    {
        if(_value > max)
        {
            _value = max;             
        }
        else if(_value < min)
        {
            _value = min; 
        }            
        *value = _value; 
        setTextString(numToString(abs(*value), precision, numOfPrecisionZones, '0'));         
    }
    
    void mouseMoved(int x, int y ) 
    {
        if(rect->inside(x, y))
        {
            state = OFX_UI_STATE_OVER;
            hitPoint = ofPoint(x,y);
            calculatePrecisionZone();
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
            *value += zoneMultiplier*(hitPoint.y-y); 
            if(*value > max)
            {
                *value = max;             
            }
            else if(*value < min)
            {
                *value = min; 
            }                  
            hitPoint = ofPoint(x,y); 
            setTextString(numToString(abs(*value), precision, numOfPrecisionZones, '0'));     
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
            calculatePrecisionZone();

            if(currentPrecisionZone == 0)
            {
                zoneMultiplier = powf(10.0, numOfPrecisionZones-precision-hasPeriod);
            }
            else if(currentPrecisionZone <= numOfPrecisionZones-precision)
            {
                zoneMultiplier = powf(10.0, numOfPrecisionZones-precision-hasPeriod-currentPrecisionZone);
            }
            else
            {
                zoneMultiplier = powf(10.0, numOfPrecisionZones-currentPrecisionZone-precision);
            }            
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
	
    void keyPressed(int key) 
    {
        if(state == OFX_UI_STATE_OVER)
        {
            switch (key) 
            {
                case OF_KEY_RIGHT:
                    *value += zoneMultiplier; 
                    if(*value > max)
                    {
                        *value = max;             
                    }
                    else if(*value < min)
                    {
                        *value = min; 
                    }            
                    
                    setTextString(numToString(abs(*value), precision, numOfPrecisionZones, '0'));     
                    triggerEvent(this); 
                    break;
                    
                case OF_KEY_UP:
                    *value += zoneMultiplier; 
                    if(*value > max)
                    {
                        *value = max;             
                    }
                    else if(*value < min)
                    {
                        *value = min; 
                    }     
                    
                    setTextString(numToString(abs(*value), precision, numOfPrecisionZones, '0'));     
                    triggerEvent(this); 
                    break;
                    
                case OF_KEY_LEFT:
                    *value -= zoneMultiplier; 
                    if(*value > max)
                    {
                        *value = max;             
                    }
                    else if(*value < min)
                    {
                        *value = min; 
                    }     
                    
                    setTextString(numToString(abs(*value), precision, numOfPrecisionZones, '0'));     
                    triggerEvent(this); 
                    break;
                    
                case OF_KEY_DOWN:
                    *value -= zoneMultiplier; 
                    if(*value > max)
                    {
                        *value = max;             
                    }
                    else if(*value < min)
                    {
                        *value = min; 
                    }      
                    
                    setTextString(numToString(abs(*value), precision, numOfPrecisionZones, '0'));     
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
    
    void stateChange()
    {        
        switch (state) {
            case OFX_UI_STATE_NORMAL:
            {
                draw_fill = true;
                draw_fill_highlight = false;
                draw_outline_highlight = false;
				label->unfocus(); 								
            }
                break;
            case OFX_UI_STATE_OVER:
            {
                draw_fill = false;
                draw_fill_highlight = true;
                draw_outline_highlight = true;  
				label->focus(); 								
            }
                break;
            case OFX_UI_STATE_DOWN:
            {
                draw_fill = false;
                draw_fill_highlight = true;
                draw_outline_highlight = true;             
				label->focus(); 					
            }
                break;
            case OFX_UI_STATE_SUSTAINED:
            {
                draw_fill = true;                 
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
    
	ofxUILabel *getLabel()
	{
		return label; 
	}
	
	string getTextString()
	{
		return textstring; 
	}
	
	void setTextString(string s)
	{
        if(*value > 0)
        {
            s = "+" + s; 
        }
        else
        {
            s = "-" + s;
        }
        textstring = s;
        displaystring = s;
        label->setLabel(displaystring);
    }
	
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
        rect->height = label->getPaddingRect()->height+padding*2.0; 
        rect->width = label->getPaddingRect()->width+padding*2.0; 
		ofxUIRectangle *labelrect = label->getRect(); 
		float h = labelrect->getHeight(); 
		float ph = rect->getHeight(); 	
		
		labelrect->y = ph/2.0 - h/2.0; 
 		
		paddedRect->height = rect->height+padding*2.0; 
		paddedRect->width = rect->width+padding*2.0;         
        setTextString(numToString(abs(*value), precision, numOfPrecisionZones, '0'));
	}	
    
    bool isDraggable()
    {
        return true;
    }

    //Needed for people who aren't using the development version of of0071...will be removed in future versions.
    
    string numToString(float value, int precision, int width, char fill )
    {
        ostringstream out;
        out << fixed << setfill(fill) << setw(width) << setprecision(precision) << value;
        return out.str();
    }

    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	string textstring;  
    string displaystring;
    int precision; 
	float zoneMultiplier; 
	float *value;  
    bool useReference;     
	float max, min; 
    ofPoint hitPoint; 
    int numOfPrecisionZones;
    int currentPrecisionZone;
    int hasPeriod; 
};

#endif
