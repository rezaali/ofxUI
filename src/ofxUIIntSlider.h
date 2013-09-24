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

#ifndef OFXUI_INT_SLIDER
#define OFXUI_INT_SLIDER

#include "ofxUIWidgetWithLabel.h"

class ofxUIIntSlider : public ofxUIWidgetWithLabel
{
public:
    ofxUIIntSlider() : ofxUIWidgetWithLabel()
    {
        
    }
    
    ofxUIIntSlider(string _name, int _min, int _max, int _value, float w, float h, float x = 0, float y = 0) : ofxUIWidgetWithLabel()
    {
        useReference = false;
        init(_name, _min, _max, &_value, w, h, x, y);
    }
    
    ofxUIIntSlider(string _name, int _min, int _max, int *_value, float w, float h, float x = 0, float y = 0) : ofxUIWidgetWithLabel()
    {
        useReference = true;
        init(_name, _min, _max, _value, w, h, x, y);
    }
    
    ~ofxUIIntSlider()
    {
        if(!useReference)
        {
            delete valueRef;
        }
    }
    
    virtual void init(string _name, int _min, int _max, int *_value, float w, float h, float x, float y)
    {
        rect = new ofxUIRectangle(x,y,w,h);
        name = string(_name);
		if(w > h)
		{
			kind = OFX_UI_WIDGET_INTSLIDER_H;
		}
		else
		{
			kind = OFX_UI_WIDGET_INTSLIDER_V;
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
            valueRef = new int();
            *valueRef = value;
        }
        
		max = _max;
		min = _min;
        
		if(value > max)
		{
			value = max;
		}
		if(value < min)
		{
			value = min;
		}
		        
		if(kind == OFX_UI_WIDGET_INTSLIDER_H)
		{
			label = new ofxUILabel(0,h+padding,string(name+" LABEL"), string(name + ": " + ofxUIToString(max)), OFX_UI_FONT_SMALL);
		}
		else
		{
			label = new ofxUILabel(0,h+padding,string(name+" LABEL"), string(name), OFX_UI_FONT_SMALL);
		}
        
		label->setParent(label);
		label->setRectParent(rect);
        label->setEmbedded(true);
        increment = 1;
        bClampValue = true;
    }
    
    bool getSetClampValue()
    {
        return bClampValue;
    }
    
    void setClampValue(bool _bClampValue)
    {
        bClampValue = _bClampValue;
    }
    
    virtual void update()
    {
        if(useReference)
        {
            value = *valueRef;
            if (bClampValue) {
                value = MAX(MIN(max, value), min);
            }
            
            updateLabel();
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
            ofxUIFill();
            ofxUISetColor(color_back);
            rect->draw();
        }
    }
    
    virtual void drawOutline()
    {
        if(draw_outline)
        {
            ofNoFill();
            ofxUISetColor(color_outline);
            rect->draw();
        }
    }
    
    virtual void drawOutlineHighlight()
    {
        if(draw_outline_highlight)
        {
            ofNoFill();
            ofxUISetColor(color_outline_highlight);
            rect->draw();
        }
    }
    
    virtual void drawFill()
    {
        if(draw_fill && value > 0)
        {
            ofxUIFill();
            ofxUISetColor(color_fill);
			if(kind == OFX_UI_WIDGET_INTSLIDER_H)
			{
				ofxUIDrawRect(rect->getX(), rect->getY(), rect->getWidth()*ofxUIMap(value, min, max, 0.0, 1.0, true), rect->getHeight());
			}
			else
			{
				ofxUIDrawRect(rect->getX(), rect->getY()+rect->getHeight(), rect->getWidth(), -rect->getHeight()*ofxUIMap(value, min, max, 0.0, 1.0, true));
			}
        }
    }
    
    virtual void drawFillHighlight()
    {
        if(draw_fill_highlight)
        {
            ofxUIFill();
            ofxUISetColor(color_fill_highlight);
			if(kind == OFX_UI_WIDGET_INTSLIDER_H)
			{
				ofxUIDrawRect(rect->getX(), rect->getY(), rect->getWidth()*ofxUIMap(value, min, max, 0.0, 1.0, true), rect->getHeight());
			}
			else
			{
				ofxUIDrawRect(rect->getX(), rect->getY()+rect->getHeight(), rect->getWidth(), -rect->getHeight()*ofxUIMap(value, min, max, 0.0, 1.0, true));
			}
			if(kind == OFX_UI_WIDGET_INTSLIDER_V)
			{
				label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*ofxUIMap(value, min, max, 0.0, 1.0, true), ofxUIToString(getValue()));
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
		if(state == OFX_UI_STATE_OVER || state == OFX_UI_STATE_DOWN)
		{
			switch (key)
			{
				case OF_KEY_RIGHT:
					setValue(getValue()+increment);
					triggerEvent(this);
					break;
                    
				case OF_KEY_UP:
					setValue(getValue()+increment);
					triggerEvent(this);
					break;
					
				case OF_KEY_LEFT:
					setValue(getValue()-increment);
					triggerEvent(this);
					break;
                    
				case OF_KEY_DOWN:
					setValue(getValue()-increment);
					triggerEvent(this);
					break;
                    
				default:
					break;
			}
		}
    }
	
    void windowResized(int w, int h)
	{
		
    }
    
    int getIncrement()
    {
        return increment;
    }
    
    void setIncrement(int _increment)
	{
		increment = _increment;
	}
    
	virtual void input(float x, float y)
	{
		float valuePct;
        
        if(kind == OFX_UI_WIDGET_INTSLIDER_H)
		{
			valuePct = rect->percentInside(x, y).x;
		}
		else
		{
			valuePct = 1.0-rect->percentInside(x, y).y;
		}
        
        if(valuePct > 1.0)
        {
            valuePct = 1.0;
        }
        else if(valuePct < 0.0)
        {
            valuePct = 0.0;
        }
        
        value = ofxUIMap(valuePct, 0.0, 1.0, min, max, bClampValue);
        updateValueRef();
		updateLabel();
	}
    
    void updateValueRef()
    {
        (*valueRef) = getValue();
    }
    
	virtual void updateLabel()
	{
		if(kind == OFX_UI_WIDGET_INTSLIDER_H)
		{
			label->setLabel(name + ": " + ofxUIToString(getValue()));
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
	
	void setValue(int _value)
	{
		if (bClampValue)
            value = MAX(MIN(max, _value), min);
        else
            value = _value;
        
        updateValueRef();
		updateLabel();
	}
    
	int getValue()
	{
		return value;
	}
	
	float getPercentValue()
	{
		return ofxUIMap(value, min, max, 0.0, 1.0, bClampValue);
	}
    
	ofxUILabel *getLabel()
	{
		return label;
	}
    
    void setLabelVisible(bool _labelVisible)
    {
        label->setVisible(_labelVisible);
        paddedRect->height -= label->getPaddingRect()->height;
    }
    
    void setVisible(bool _visible)
    {
        visible = _visible;
        label->setVisible(visible);
    }
	
	virtual void setParent(ofxUIWidget *_parent)
	{
		parent = _parent;
        label->getRect()->setY(rect->getHeight()+padding);
        paddedRect->height = rect->getHeight() + label->getPaddingRect()->height + padding;
        paddedRect->x = -padding;
        paddedRect->y = -padding;
        if(label->getPaddingRect()->width > paddedRect->width)
        {
            paddedRect->width = label->getPaddingRect()->width;
        }
        updateValueRef();
        updateLabel();
	}
    
    void setMax(int _max, bool bKeepValueTheSame = false)
    {
        setMaxAndMin(_max, min, bKeepValueTheSame);
    }
    
    int getMax()
    {
        return max;
    }
    
    void setMin(int _min, bool bKeepValueTheSame = false)
    {
        setMaxAndMin(max, _min, bKeepValueTheSame);
    }
    
    int getMin()
    {
        return min;
    }
    
    ofxUIVec2f getMaxAndMin()
    {
        return ofxUIVec2f(max, min);
    }
    
    void setMaxAndMin(int _max, int _min, bool bKeepValueTheSame = false)
    {
        max = _max;
        min = _min;
        
        if(!bKeepValueTheSame)
        {
            value = ofxUIMap(value, 0, 1.0, min, max, bClampValue);
            value = ofxUIMap(value, min, max, 0.0, 1.0, bClampValue);
            updateValueRef();
            updateLabel();
        }
    }
    
    bool isDraggable()
    {
        return true;
    }
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent;
    bool bClampValue;
    int value, increment;
    int *valueRef;
    bool useReference;
	int max, min;
}; 

#endif
