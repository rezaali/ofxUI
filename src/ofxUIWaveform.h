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

#include "ofxUIWidget.h"

class ofxUIWaveform : public ofxUIWidget
{
public:    
    ofxUIWaveform(float x, float y, float w, float h, float *_buffer, int _bufferSize, float _min, float _max, string _name);
    ofxUIWaveform(float w, float h, float *_buffer, int _bufferSize, float _min, float _max, string _name);
    void init(float x, float y, float w, float h, float *_buffer, int _bufferSize, float _min, float _max, string _name);
    virtual void drawBack();
    virtual void drawFill();
	void setParent(ofxUIWidget *_parent);
    void setMax(float _max);
    float getMax();
    void setMin(float _min);
    float getMin();
    ofVec2f getMaxAndMind();
    void setMaxAndMin(float _max, float _min);
    
protected:
	float *buffer; 
	float max, min, scale, inc; 
	int bufferSize; 
}; 