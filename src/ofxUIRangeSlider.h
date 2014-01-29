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

class ofxUIRangeSlider : public ofxUIWidgetWithLabel
{
public:
    ofxUIRangeSlider(string _name, float _min, float _max, float _valuelow, float _valuehigh, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    ofxUIRangeSlider(string _name, float _min, float _max, float *_valuelow, float *_valuehigh, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    ofxUIRangeSlider(float x, float y, float w, float h, float _min, float _max, float _valuelow, float _valuehigh, string _name, int _size = OFX_UI_FONT_SMALL);
    ofxUIRangeSlider(float w, float h, float _min, float _max, float _valuelow, float _valuehigh, string _name, int _size = OFX_UI_FONT_SMALL);
    ofxUIRangeSlider(float x, float y, float w, float h, float _min, float _max, float *_valuelow, float *_valuehigh, string _name, int _size = OFX_UI_FONT_SMALL);
    ofxUIRangeSlider(float w, float h, float _min, float _max, float *_valuelow, float *_valuehigh, string _name, int _size = OFX_UI_FONT_SMALL);
    ~ofxUIRangeSlider();
    void init(string _name, float _min, float _max, float *_valuelow, float *_valuehigh, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    virtual void update();
    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    virtual void drawFill();
    virtual void drawFillHighlight();
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);
    void keyReleased(int key);
    void windowResized(int w, int h);
    void setIncrement(float _increment);
	void input(float x, float y);
    void updateValueRef();
	void updateLabel();
    void stateChange();
	void setValueLow(float _value);
	void setValueHigh(float _value);
    float getValueLow();
    float getValueHigh();
    float getNormalizedValueLow();
    float getNormalizedValueHigh();
    float getPercentValueLow();
	float getPercentValueHigh();
	float getScaledValueLow();
	float getScaledValueHigh();
    void setLabelPrecision(int _precision);
	void setParent(ofxUIWidget *_parent);
    void setMax(float _max);
    void setMin(float _min);
    void setMaxAndMin(float _max, float _min);
    bool isDraggable();
    bool hasState(){ return true; };
#ifndef OFX_UI_NO_XML
    virtual void saveState(ofxXmlSettings *XML);
    virtual void loadState(ofxXmlSettings *XML);
#endif
    
protected:    
	float valuelow, valuehigh, increment; 
    float *valuelowRef; 
    float *valuehighRef;    
    bool useReference;         
    float hitValueLow, hitValueHigh; 
	bool hitHigh, hitLow, hitCenter; 
	float hitPoint; 
	float max, min; 
    int labelPrecision;
    string valuelowString;
    string valuehighString; 
}; 