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
    ofxUIMinimalSlider(float x, float y, float w, float h, float _min, float _max, float _value, string _name)
    {
        rect = new ofxUIRectangle(x,y,w,h); 
        autoSize = false; 
        init(w, h, _min, _max, _value, _name, OFX_UI_FONT_SMALL); 		
    }
    
    ofxUIMinimalSlider(float w, float h, float _min, float _max, float _value, string _name)
    {
        rect = new ofxUIRectangle(0,0,w,h); 
        autoSize = false; 
        init(w, h, _min, _max, _value, _name, OFX_UI_FONT_SMALL); 
    }    

    ofxUIMinimalSlider(float x, float y, float w, float _min, float _max, float _value, string _name, int _size)
    {
        rect = new ofxUIRectangle(x,y,w,0); 
        autoSize = true; 
        init(w, 0, _min, _max, _value, _name, _size); 		
    }
    
    ofxUIMinimalSlider(float w, float _min, float _max, float _value, string _name, int _size)
    {
        rect = new ofxUIRectangle(0,0,w,0); 
        autoSize = true; 
        init(w, 0, _min, _max, _value, _name, _size); 
    }    
    
    void init(float w, float h, float _min, float _max, float _value, string _name, int _size)
    {
        name = _name; 				
        kind = OFX_UI_WIDGET_MINIMALSLIDER;
        
		paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding);
		paddedRect->setParent(rect);     
        
        draw_fill = true; 
        
        value = _value;                                               //the widget's value
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
        
        label = new ofxUILabel(padding,h*.5,(name+" LABEL"), name, _size); 	
        label->setDrawBack(true);        
		label->setParent(label); 
		label->setRectParent(rect); 	
        label->setEmbedded(true);        
        increment = 1.0;         
    }
    
    virtual void drawFill()
    {
        if(draw_fill)
        {			
            ofFill(); 
            ofSetColor(color_fill); 
            ofRect(rect->getX(), rect->getY(), rect->getWidth()*value, rect->getHeight()); 
        }
    }
    
    virtual void drawFillHighlight()
    {
        if(draw_fill_highlight)
        {
            ofFill(); 
            ofSetColor(color_fill_highlight); 
            ofRect(rect->getX(), rect->getY(), rect->getWidth()*value, rect->getHeight()); 
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
            rect->draw();                      
            if(!draw_fill_highlight)
            {
                ofSetColor(label->getColorFill()); 
                label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*.5, ofToString(getScaledValue(),labelPrecision)); 
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
        
		updateLabel(); 
	}

    
    void updateLabel()
	{

	}
    
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent;         
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
        if(autoSize || rect->height < label->getPaddingRect()->height)
        {
            rect->height = label->getPaddingRect()->height;                 
        }
        
		float h = labelrect->getHeight(); 
		float ph = rect->getHeight(); 	
        
		labelrect->y = (int)(ph*.5 - h*.5); 
        labelrect->x = padding; 
		paddedRect->height = rect->height+padding*2.0;  
        paddedRect->width = rect->width+padding*2.0;  

        updateLabel(); 
	}	
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    bool autoSize;     
}; 

#endif
