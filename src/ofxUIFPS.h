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

#include "ofxUIWidgetWithLabel.h"

class ofxUIFPS : public ofxUIWidgetWithLabel
{
public:    
    ofxUIFPS(float x, float y, int _size) : ofxUIWidgetWithLabel()
    {
        init(x, y, "FPS", "FPS: 000", _size);
    }
    
    ofxUIFPS(int _size) : ofxUIWidgetWithLabel()
    {
        init(0, 0, "FPS", "FPS: 000", _size);
    }
    
    void init(float x, float y, string _name, string _label, int _size)
    {
        rect = new ofxUIRectangle(x,y,0,0);
		name = string(_name);
		kind = OFX_UI_WIDGET_FPS; 
        paddedRect = new ofxUIRectangle(-padding, -padding, padding*2.0, padding*2.0);
		paddedRect->setParent(rect);

        label = new ofxUILabel(0,0,(name+" LABEL"), _label, _size);
		label->setRectParent(rect);
        label->setEmbedded(true);
        
        labelPrecision = 0;
        draw_back = OFX_UI_LABEL_DRAW_BACK;
        draw_fill = false;
        draw_back = false;
    }
    
	void update()
	{
		label->setLabel(name + ": " + ofxUIToString(ofxUIGetFrameRate(), labelPrecision));
	}	    
    
    void setLabelPrecision(int _precision) {
        labelPrecision = _precision;
    }

    void setParent(ofxUIWidget *_parent)
	{
		parent = _parent;
        ofxUIRectangle *labelrect = label->getRect();
        
        rect->setHeight(label->getRect()->getHeight());
        rect->setWidth(label->getRect()->getWidth());         
        
		labelrect->y = 0;
        labelrect->x = 0;
		paddedRect->setHeight(rect->getHeight()+padding*2.0);
        paddedRect->setWidth(rect->getWidth()+padding*2.0);
	}

    
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    int labelPrecision;    
}; 

#endif