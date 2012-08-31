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

#ifndef OFXUI_FPS
#define OFXUI_FPS

#include "ofxUILabel.h"

class ofxUIFPS : public ofxUILabel
{
public:    
    ofxUIFPS(float x, float y, int _size)
    {
        rect = new ofxUIRectangle(x,y,0,0); 
        init("FPS", "FPS: 60.000", _size); 
		kind = OFX_UI_WIDGET_FPS; 		
        labelPrecision = 3;
        autoSize = true; 
    }
    
    ofxUIFPS(int _size)
    {
        rect = new ofxUIRectangle(0,0,0,0); 
        init("FPS", "FPS: 60.000", _size); 
		kind = OFX_UI_WIDGET_FPS; 		
        labelPrecision = 3;
        autoSize = true; 
    }    
    
	void update()
	{
		setLabel("FPS: " + ofToString(ofGetFrameRate(), labelPrecision));
	}
	
    void setLabelPrecision(int _precision) {
        labelPrecision = _precision;
    }

    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    int labelPrecision;    
}; 

#endif