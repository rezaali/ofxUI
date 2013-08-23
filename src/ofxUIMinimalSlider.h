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

#ifndef OFXUI_MINIMAL_SLIDER
#define OFXUI_MINIMAL_SLIDER

#include "ofxUISlider.h"

class ofxUIMinimalSlider : public ofxUISlider
{
public:
    
    ofxUIMinimalSlider(string _name, float _min, float _max, float _value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL) : ofxUISlider()
    {
        useReference = false;
        init(_name, _min, _max, &_value, w, h, x, y, _size);
    }
    
    ofxUIMinimalSlider(string _name, float _min, float _max, float *_value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL) : ofxUISlider()
    {
        useReference = true;
        init(_name, _min, _max, _value, w, h, x, y, _size);
    }
    
    ofxUIMinimalSlider(float x, float y, float w, float h, float _min, float _max, float _value, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUISlider()
    {
        useReference = false;                                         
        init(_name, _min, _max, &_value, w, h, x, y, _size);
//        ofLogWarning("OFXUIMINIMALSLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
    }
    
    ofxUIMinimalSlider(float w, float h, float _min, float _max, float _value, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUISlider()
    {
        useReference = false;                                          
        init(_name, _min, _max, &_value, w, h, 0, 0, _size);
//        ofLogWarning("OFXUIMINIMALSLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");        
    }
    
    ofxUIMinimalSlider(float w, float _min, float _max, float _value, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUISlider()
    {
        useReference = false;                                                 
        init(_name, _min, _max, &_value, w, 0, 0, 0, _size);
//        ofLogWarning("OFXUIMINIMALSLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");        
    }
    
    ofxUIMinimalSlider(float x, float y, float w, float h, float _min, float _max, float *_value, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUISlider()
    {
        useReference = true;
        init(_name, _min, _max, _value, w, h, x, y, _size);
//        ofLogWarning("OFXUIMINIMALSLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");        
    }
    
    ofxUIMinimalSlider(float w, float h, float _min, float _max, float *_value, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUISlider()
    {
        useReference = true;
        init(_name, _min, _max, _value, w, h, 0, 0, _size);
//        ofLogWarning("OFXUIMINIMALSLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");        
    }
    
    ofxUIMinimalSlider(float w, float _min, float _max, float *_value, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUISlider()
    {
        useReference = true;                                                 
        init(_name, _min, _max, _value, w, 0, 0, 0, _size);
//        ofLogWarning("OFXUIMINIMALSLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");        
    }
    

    void init(string _name, float _min, float _max, float *_value, float w, float h, float x, float y, int _size = OFX_UI_FONT_SMALL) 
    {
        if(h < .1)
        {
            autoSize = true;
        }
        else
        {
            autoSize = false; 
        }
        
        rect = new ofxUIRectangle(x,y,w,h);
        name = string(_name);  				
        kind = OFX_UI_WIDGET_MINIMALSLIDER;
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding);
		paddedRect->setParent(rect);     
        
        draw_fill = true; 
        showValue = true; 
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
		
		value = ofxUIMap(value, min, max, 0.0, 1.0, true); 
        
        label = new ofxUILabel(padding,h*.5,(name+" LABEL"), name, _size); 	
        label->setDrawBack(false);
		label->setParent(label); 
		label->setRectParent(rect); 	
        label->setEmbedded(true);        
        increment = fabs(max - min) / 10.0;
        bRoundedToNearestInt = false;
        bClampValue = false;
    }
    
    virtual void drawFill()
    {
        if(draw_fill)
        {			
            ofxUIFill(); 
            ofxUISetColor(color_fill); 
            ofxUIDrawRect(rect->getX(), rect->getY(), rect->getWidth()*MIN(MAX(value, 0.0), 1.0), rect->getHeight());
        }
    }
    
    virtual void drawFillHighlight()
    {
        if(draw_fill_highlight && showValue)
        {
            ofxUIFill(); 
            ofxUISetColor(color_fill_highlight); 
            ofxUIDrawRect(rect->getX(), rect->getY(), rect->getWidth()*MIN(MAX(value, 0.0), 1.0), rect->getHeight());
            ofxUISetColor(label->getColorFillHighlight());             
            label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*.5, ofxUIToString(getScaledValue(),labelPrecision)); 
        }        
    }
    
    virtual void drawOutlineHighlight()
    {
        if(draw_outline_highlight && showValue)
        {
            ofNoFill();
            ofxUISetColor(color_outline_highlight); 
            rect->draw();                      
            if(!draw_fill_highlight)
            {
                ofxUISetColor(label->getColorFill()); 
                label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*.5, ofxUIToString(getScaledValue(),labelPrecision)); 
            }
        }
    }
    
    void input(float x, float y)
	{
        value = rect->percentInside(x, y).x; 
        
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

    
    void updateLabel()
	{

	}
    
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent;         
		ofxUIRectangle *labelrect = label->getRect(); 
        while(labelrect->getWidth() > rect->getWidth())
        {
            string labelstring = label->getLabel();
            string::iterator it;
            it=labelstring.end();
            it--; 
            labelstring.erase (it); 
            label->setLabel(labelstring);
        }            
        if(autoSize || rect->getHeight() <= label->getPaddingRect()->getHeight())
        {
            rect->setHeight(label->getPaddingRect()->getHeight()+padding*2.0);             
        }
        
		float h = labelrect->getHeight(); 
		float ph = rect->getHeight(); 	
        
		labelrect->y = (int)(ph*.5 - h*.5);
        labelrect->x = padding*2.0;
		paddedRect->setHeight(rect->getHeight()+padding*2.0);  
        paddedRect->setWidth(rect->getWidth()+padding*2.0);
        updateValueRef();
        updateLabel(); 
	}	
    
    virtual void setShowValue(bool _showValue)
    {
        showValue = _showValue;
    }
    
    bool getShowValue()
    {
        return showValue;
    }
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    bool autoSize;
    bool showValue; 
}; 

#endif
