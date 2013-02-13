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

#ifndef OFXUI_WAVEFORM
#define OFXUI_WAVEFORM

#include "ofxUIWidget.h"

class ofxUIWaveform : public ofxUIWidget
{
public:    
    ofxUIWaveform(float x, float y, float w, float h, float *_buffer, int _bufferSize, float _min, float _max, string _name) : ofxUIWidget()
    {
        rect = new ofxUIRectangle(x,y,w,h); 
        init(w, h, _buffer, _bufferSize, _min, _max, _name);
    }
    
    ofxUIWaveform(float w, float h, float *_buffer, int _bufferSize, float _min, float _max, string _name) : ofxUIWidget()
    {
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w, h, _buffer, _bufferSize, _min, _max, _name);
    }    
    
    void init(float w, float h, float *_buffer, int _bufferSize, float _min, float _max, string _name)
    {
        name = string(_name);  				
        kind = OFX_UI_WIDGET_WAVEFORM; 

        paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding*2.0);
        paddedRect->setParent(rect); 
		
        draw_fill = true; 
        
        if(_buffer != NULL)
        {
            buffer = _buffer;					//the widget's value
        }
        else
        {
            buffer = NULL; 
        }
        
        bufferSize = _bufferSize; 
        max = _max; 
        min = _min; 		
        scale = rect->getHeight()*.5;
        inc = rect->getWidth()/((float)bufferSize-1.0);
    }
    
    
    virtual void drawBack()
    {
        if(draw_back)
        {
            ofFill();
            ofSetColor(color_back);
            rect->draw();
            
            ofLine(rect->getX(), rect->getY()+rect->getHalfHeight(), rect->getX()+rect->getWidth(), rect->getY()+rect->getHalfHeight());
        }
    }
    
    
    virtual void drawFill()
    {
        if(draw_fill)
        {			
			ofNoFill(); 
			if(draw_fill_highlight)
			{
				ofSetColor(color_fill_highlight); 
			}        
			else 
			{
				ofSetColor(color_fill); 		 	
			}
            if(buffer != NULL)
            {
                ofPushMatrix(); 
                ofTranslate(rect->getX(), rect->getY()+scale, 0);
                ofSetLineWidth(1.5); 
                ofBeginShape();		
                for (int i = 0; i < bufferSize; i++)
                {				
                    ofVertex(inc*(float)i, ofMap(buffer[i], min, max, -scale, scale, true)); 
                }
                ofEndShape();
                ofSetLineWidth(1); 
                ofPopMatrix(); 
            }
        }
    }
		
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
	}
    
    void setMax(float _max)
    {
        max = _max;
    }
    
    float getMax()
    {
        return max;
    }
    
    void setMin(float _min)
    {
        min = _min;
    }
    
    float getMin()
    {
        return min;
    }
    
    ofVec2f getMaxAndMind()
    {
        return ofVec2f(max, min);
    }
    
    void setMaxAndMin(float _max, float _min)
    {
        max = _max;
        min = _min;
    }
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
	float *buffer; 
	float max, min, scale, inc; 
	int bufferSize; 
}; 



#endif
