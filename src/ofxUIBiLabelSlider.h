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

#ifndef OFXUI_BILABEL_SLIDER
#define OFXUI_BILABEL_SLIDER

#include "ofxUISlider.h"

class ofxUIBiLabelSlider : public ofxUISlider
{
public:
    ofxUIBiLabelSlider(float x, float y, float w, float h, float _min, float _max, float _value, string _name, string _leftLabel, string _rightLabel, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = false;                 
        rect = new ofxUIRectangle(x,y,w,h); 
        autoSize = false; 
        init(w, h, _min, _max, &_value, _name, _leftLabel, _rightLabel, _size); 		
    }
    
    ofxUIBiLabelSlider(float w, float h, float _min, float _max, float _value, string _name, string _leftLabel, string _rightLabel, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = false;                 
        rect = new ofxUIRectangle(0,0,w,h); 
        autoSize = false; 
        init(w, h, _min, _max, &_value, _name, _leftLabel, _rightLabel, _size); 
    }    
    
    ofxUIBiLabelSlider(float x, float y, float w, float _min, float _max, float _value, string _name, string _leftLabel, string _rightLabel, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = false;                 
        rect = new ofxUIRectangle(x,y,w,0); 
        autoSize = true; 
        init(w, 0, _min, _max, &_value, _name, _leftLabel, _rightLabel, _size); 		
    }
    
    ofxUIBiLabelSlider(float w, float _min, float _max, float _value, string _name, string _leftLabel, string _rightLabel, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = false;                 
        rect = new ofxUIRectangle(0,0,w,0); 
        autoSize = true; 
        init(w, 0, _min, _max, &_value, _name, _leftLabel, _rightLabel, _size); 
    }    
    
    ofxUIBiLabelSlider(float x, float y, float w, float h, float _min, float _max, float *_value, string _name, string _leftLabel, string _rightLabel, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = true;                 
        rect = new ofxUIRectangle(x,y,w,h); 
        autoSize = false; 
        init(w, h, _min, _max, _value, _name, _leftLabel, _rightLabel, _size); 		
    }
    
    ofxUIBiLabelSlider(float w, float h, float _min, float _max, float *_value, string _name, string _leftLabel, string _rightLabel, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = true;                         
        rect = new ofxUIRectangle(0,0,w,h); 
        autoSize = false; 
        init(w, h, _min, _max, _value, _name, _leftLabel, _rightLabel, _size); 
    }    
    
    ofxUIBiLabelSlider(float x, float y, float w, float _min, float _max, float *_value, string _name, string _leftLabel, string _rightLabel, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = true;                         
        rect = new ofxUIRectangle(x,y,w,0); 
        autoSize = true; 
        init(w, 0, _min, _max, _value, _name, _leftLabel, _rightLabel, _size); 		
    }
    
    ofxUIBiLabelSlider(float w, float _min, float _max, float *_value, string _name, string _leftLabel, string _rightLabel, int _size = OFX_UI_FONT_SMALL)
    {
        useReference = true;                         
        rect = new ofxUIRectangle(0,0,w,0); 
        autoSize = true; 
        init(w, 0, _min, _max, _value, _name, _leftLabel, _rightLabel, _size); 
    }         
    
    void init(float w, float h, float _min, float _max, float *_value, string _name, string _leftLabel, string _rightLabel, int _size)
    {
        name = _name; 	
        leftLabel = _leftLabel; 
        rightLabel = _rightLabel; 
        kind = OFX_UI_WIDGET_BILABELSLIDER; 
        
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
        
        label = new ofxUILabel(padding,h*.5,(name+" LABEL"), name, _size); 	
        label->setDrawBack(true);        
		label->setParent(label); 
		label->setRectParent(rect); 	
        label->setEmbedded(true);        

        rlabel = new ofxUILabel(padding,h*.5,(name+" LABEL"), rightLabel, _size); 	
        rlabel->setDrawBack(true);        
		rlabel->setParent(rlabel); 
		rlabel->setRectParent(rect); 	

        increment = fabs(max - min) / 10.0;
    }
    
    virtual void setDrawPadding(bool _draw_padded_rect)
	{
		draw_padded_rect = _draw_padded_rect; 
        label->setDrawPadding(false);
        rlabel->setDrawPadding(false);
	}
    
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline)
	{
		draw_padded_rect_outline = _draw_padded_rect_outline; 
        label->setDrawPaddingOutline(false);
        rlabel->setDrawPaddingOutline(false);        
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
        label->setLabel(leftLabel);
		ofxUIRectangle *labelrect = label->getRect(); 
        ofxUIRectangle *rightlabelrect = rlabel->getRect(); 
        
        
        if(autoSize || rect->height < label->getPaddingRect()->height)
        {
            rect->height = label->getPaddingRect()->height;                 
        }
        
		float h = labelrect->getHeight(); 
		float ph = rect->getHeight(); 	
        
		labelrect->y = (int)(ph*.5 - h*.5); 

        rightlabelrect->y = labelrect->y;
        rightlabelrect->x = rect->getWidth()-rightlabelrect->getWidth()-padding*2.0; 
        labelrect->x = padding;


		paddedRect->height = rect->getHeight()+padding*2.0;  
        paddedRect->width = rect->width+padding*2.0;  
        updateValueRef();                   
        updateLabel(); 
	}	
    
    ofxUILabel * getRightLabel()
    {
        return rlabel; 
    }
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    bool autoSize;     
    string leftLabel, rightLabel; 
    ofxUILabel *rlabel; 
}; 

#endif
