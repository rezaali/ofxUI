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

#ifndef OFXUI_LABEL_TOGGLE
#define OFXUI_LABEL_TOGGLE

#include "ofxUIWidget.h"

class ofxUILabelToggle : public ofxUIToggle
{
public:
    ofxUILabelToggle(float x, float y, float w, bool _value, string _name, int _size)
    {
        rect = new ofxUIRectangle(x,y,w,0);                                                      //the widget's value        
        autoSize = false;         
        init(_value, _name, _size); 
    }

    ofxUILabelToggle(float x, float y, float w, float h, bool _value, string _name, int _size)
    {
        rect = new ofxUIRectangle(x,y,w,h);                                                      //the widget's value        
        autoSize = false;         
        init(_value, _name, _size); 
    }
    
    ofxUILabelToggle(float w, bool _value, string _name, int _size, float h = 0)
    {
        rect = new ofxUIRectangle(0,0,w,h);                                                      //the widget's value        
        autoSize = false;         
        init(_value, _name, _size); 
    }
    
    ofxUILabelToggle(float x, float y, bool _value, string _name, int _size)
    {				
        rect = new ofxUIRectangle(x,y,0,0);                 
        autoSize = true;         
        init(_value, _name, _size); 
    }

    ofxUILabelToggle(bool _value, string _name, int _size)
    {				
        rect = new ofxUIRectangle(0,0,0,0);                 
        autoSize = true;         
        init(_value, _name, _size); 
    }

    
    void init(bool _value, string _name, int _size)
    {        
		name = _name; 		        

        kind = OFX_UI_WIDGET_LABELTOGGLE; 		
        paddedRect = new ofxUIRectangle(-padding, -padding, padding*2.0, padding*2.0);
		paddedRect->setParent(rect); 
        
        label = new ofxUILabel((name+" LABEL"), name, _size); 
		label->setParent(label); 
		label->setRectParent(rect); 
        label->setEmbedded(true);        
        setValue(_value);
    }	
	
	void setParent(ofxUIWidget *_parent)
	{
		parent = _parent; 
        if(rect->height == 0)
        {
            rect->height = label->getPaddingRect()->height+padding*2.0; 
        }
		ofxUIRectangle *labelrect = label->getRect(); 
        
        if(autoSize)
        {
            rect->width = label->getPaddingRect()->width+padding*2.0;             
        }
        else
        {
            while(labelrect->width+padding*4.0 > rect->width)
            {
                string labelstring = label->getLabel();
                string::iterator it;
                it=labelstring.end();
                it--; 
                labelstring.erase (it); 
                label->setLabel(labelstring);
            }                        
        }

		float h = labelrect->getHeight(); 
		float ph = rect->getHeight(); 	
        
        float w = labelrect->getWidth(); 
        float pw = rect->getWidth(); 
        
		labelrect->y = (int)(ph*.5 - h*.5); 
        labelrect->x = (int)(pw*.5 - w*.5-padding*.5); 
		paddedRect->height = rect->height+padding*2.0;  
        paddedRect->width = rect->width+padding*2.0;  
	}	
    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    bool autoSize; 
}; 

#endif
