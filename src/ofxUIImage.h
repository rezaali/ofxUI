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

class ofxUIImage : public ofxUIWidgetWithLabel
{
public:
    ofxUIImage(float x, float y, float w, float h, ofImage *_image, string _name);
    ofxUIImage(float x, float y, float w, float h, ofImage *_image, string _name, bool _showLabel);
    ofxUIImage(float w, float h, ofImage *_image, string _name);
    ofxUIImage(float w, float h, ofImage *_image, string _name, bool _showLabel);
    void init(float x, float y, float w, float h, ofImage *_image, string _name);
    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    virtual void drawFill();
    void setCropImageToFitRect(bool _cropImageToFitRect);
    void setImage(ofImage *_image);
    virtual bool isDraggable();
    
protected:  
	ofImage *image;
    bool cropImageToFitRect; 
}; 