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

#include "ofxUIValuePlotter.h"
#include "ofxUI.h"

ofxUIValuePlotter::ofxUIValuePlotter(float x, float y, float w, float h, int _bufferSize, float _min, float _max, float *_value, string _name) : ofxUIWidget()
{
    init(x, y, w, h, _bufferSize, _min, _max, _value, _name);
}

ofxUIValuePlotter::ofxUIValuePlotter(float w, float h, int _bufferSize, float _min, float _max, float *_value, string _name) : ofxUIWidget()
{
    init(0, 0, w, h, _bufferSize, _min, _max, _value, _name);
}

void ofxUIValuePlotter::init(float x, float y, float w, float h, int _bufferSize, float _min, float _max, float *_value, string _name)
{
    initRect(x,y,w,h);
    name = string(_name);
    kind = OFX_UI_WIDGET_VALUEPLOTTER;
    
    value = _value;                                               //the widget's value
    
    draw_fill = true;
    
    bufferSize = _bufferSize;
    max = _max;
    min = _min;
    for(unsigned int i = 0; i < bufferSize; i++)
    {
        buffer.push_back(*value);
    }
    scale = rect->getHeight()*.5;
    inc = rect->getWidth()/((float)bufferSize-1.0);
}

void ofxUIValuePlotter::update()
{
    addPoint(*value);
}

void ofxUIValuePlotter::drawBack()
{
    if(draw_back)
    {
        ofxUIFill();
        ofxUISetColor(color_back);
        rect->draw();
        
        ofxUIDrawLine(rect->getX(), rect->getY()+rect->getHalfHeight(), rect->getX()+rect->getWidth(), rect->getY()+rect->getHalfHeight());
    }
}

void ofxUIValuePlotter::drawFill()
{
    if(draw_fill)
    {
        ofNoFill();
        if(draw_fill_highlight)
        {
            ofxUISetColor(color_fill_highlight);
        }
        else
        {
            ofxUISetColor(color_fill);
        }
        ofPushMatrix();
        ofTranslate(rect->getX(), rect->getY()+scale, 0);
        ofSetLineWidth(1.5);
        ofBeginShape();
        for (unsigned int i = 0; i < bufferSize; i++)
        {
            ofVertex(inc*(float)i, ofxUIMap(buffer[i], min, max, scale, -scale, true));
        }
        ofEndShape();
        ofSetLineWidth(1);
        ofPopMatrix();
        
    }
}

void ofxUIValuePlotter::addPoint(float _point)
{
    buffer.push_back(_point);
    
    if( buffer.size() >= bufferSize )
    {
        buffer.erase(buffer.begin(), buffer.begin()+1);
    }
}

vector<float> &ofxUIValuePlotter::getBuffer()
{
    return buffer;
}

void ofxUIValuePlotter::setBuffer(vector<float> _buffer)
{
    buffer = _buffer;
}