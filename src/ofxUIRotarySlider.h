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

#pragma once

#include "ofxUIWidgetWithLabel.h"
#include "ofxUIDefines.h"

class ofxUIRotarySlider : public ofxUIWidgetWithLabel
{
public:    
    ofxUIRotarySlider(float x, float y, float w, float _min, float _max, float _value, string _name, int _size = OFX_UI_FONT_SMALL);
    ofxUIRotarySlider(float w, float _min, float _max, float _value, string _name, int _size = OFX_UI_FONT_SMALL);
    ofxUIRotarySlider(float x, float y, float w, float _min, float _max, float *_value, string _name, int _size = OFX_UI_FONT_SMALL);
    ofxUIRotarySlider(float w, float _min, float _max, float *_value, string _name, int _size = OFX_UI_FONT_SMALL);
    ~ofxUIRotarySlider();
    void init(float x, float y, float w, float _min, float _max, float *_value, string _name, int _size = OFX_UI_FONT_SMALL);
    virtual void update();
    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
	virtual void drawBack();
    virtual void drawFill();
    virtual void drawFillHighlight();
    virtual void drawOutline();
    virtual void drawOutlineHighlight();
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);
    void drawArcStrip(float percent);
    void setIncrement(float _increment);
	void input(float x, float y);
    void updateValueRef();
	void updateLabel();
    void stateChange();
	void setValue(float _value);
	float getValue();
    float getNormalizedValue();
	float getScaledValue();
	void setParent(ofxUIWidget *_parent);
    bool isDraggable();
    void setMax(float _max);
    float getMax();
    void setMin(float _min);
    float getMin();
    ofVec2f getMaxAndMind();
    void setMaxAndMin(float _max, float _min);
    virtual bool isHit(float x, float y);
    bool hasState(){ return true; };
#ifndef OFX_UI_NO_XML
    virtual void saveState(ofxXmlSettings *XML);
    virtual void loadState(ofxXmlSettings *XML);
#endif    
    
protected:    
	float value, increment; 
    float *valueRef; 
    bool useReference;         
	float max, min; 
    ofxUIVec2f center; 
    ofxUIVec2f hitPoint; 
    ofxUIVec2f homePoint; 
    float outerRadius, innerRadius;
    string valueString; 
    
    
}; 