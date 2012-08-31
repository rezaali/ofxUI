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

#ifndef OFXUI_IMAGE_TOGGLE
#define OFXUI_IMAGE_TOGGLE

#include "ofxUIWidget.h"

class ofxUIImageToggle : public ofxUIImageButton
{
public:
    ofxUIImageToggle(float x, float y, float w, float h, bool _value, string _pathURL, string _name)
    {
        useReference = false; 
        rect = new ofxUIRectangle(x,y,w,h); 
        init(w, h, &_value, _pathURL, _name);         
		kind = OFX_UI_WIDGET_IMAGETOGGLE; 		
    }

    ofxUIImageToggle(float w, float h, bool _value, string _pathURL, string _name)
    {
        useReference = false; 
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w, h, &_value, _pathURL, _name);         
		kind = OFX_UI_WIDGET_IMAGETOGGLE; 		
    }
    
    ofxUIImageToggle(float x, float y, float w, float h, bool *_value, string _pathURL, string _name)
    {
        useReference = true;         
        rect = new ofxUIRectangle(x,y,w,h); 
        init(w, h, _value, _pathURL, _name);         
		kind = OFX_UI_WIDGET_IMAGETOGGLE; 		
    }
    
    ofxUIImageToggle(float w, float h, bool *_value, string _pathURL, string _name)
    {
        useReference = true;                 
        rect = new ofxUIRectangle(0,0,w,h); 
        init(w, h, _value, _pathURL, _name);         
		kind = OFX_UI_WIDGET_IMAGETOGGLE; 		
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
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;        
        }
        stateChange();         
    }
    
    void mouseReleased(int x, int y, int button) 
    {
        if(rect->inside(x, y) && hit)
        {
            setValue(!(*value)); 
#ifdef TARGET_OPENGLES
            state = OFX_UI_STATE_NORMAL;        
#else            
            state = OFX_UI_STATE_OVER; 
#endif 
			triggerEvent(this); 
        }    
        else
        {
            state = OFX_UI_STATE_NORMAL;         
        }
        stateChange();     
        hit = false; 
    }        
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
}; 

#endif
