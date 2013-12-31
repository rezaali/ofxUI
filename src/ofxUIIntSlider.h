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

class ofxUIIntSlider : public ofxUIWidgetWithLabel
{
public:
    ofxUIIntSlider();
    ofxUIIntSlider(string _name, int _min, int _max, int _value, float w, float h, float x = 0, float y = 0);
    ofxUIIntSlider(string _name, int _min, int _max, int *_value, float w, float h, float x = 0, float y = 0);
    ~ofxUIIntSlider();
    
    virtual void init(string _name, int _min, int _max, int *_value, float w, float h, float x, float y);
    virtual void update();
    
    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    virtual void drawBack();
    virtual void drawOutline();
    virtual void drawOutlineHighlight();
    virtual void drawFill();
    virtual void drawFillHighlight();
    
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);
    
    bool getSetClampValue();
    void setClampValue(bool _bClampValue);
    
    int getIncrement();
    void setIncrement(int _increment);
	virtual void input(float x, float y);
    void updateValueRef();
	virtual void updateLabel();
    virtual void stateChange();
	void setValue(int _value);
	int getValue();
	float getPercentValue();
	ofxUILabel *getLabel();
    void setLabelVisible(bool _labelVisible);
    void setVisible(bool _visible);
	virtual void setParent(ofxUIWidget *_parent);
    void setMax(int _max, bool bKeepValueTheSame = false);
    int getMax();
    void setMin(int _min, bool bKeepValueTheSame = false);
    int getMin();
    ofxUIVec2f getMaxAndMin();
    void setMaxAndMin(int _max, int _min, bool bKeepValueTheSame = false);
    bool isDraggable();
    
protected:
    bool bClampValue;
    int value, increment;
    int *valueRef;
    bool useReference;
	int max, min;
}; 