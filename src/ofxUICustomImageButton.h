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

#include "ofxUIButton.h"

class ofxUICustomImageButton : public ofxUIButton
{
public:
    ofxUICustomImageButton(float w, float h, bool _value, string _pathURL, string _name, int _size, int _labelWidth, int _labelHeight);
    ofxUICustomImageButton(float w, float h, bool _value, string _pathURL, string _name, int _size, bool centerLabel = false);
    ofxUICustomImageButton(float w, float h, bool _value, ofImage *_img, string _name, int _size, int _labelWidth, int _labelHeight);
    ofxUICustomImageButton(float w, float h, bool _value, ofImage *_img, string _name, int _size, bool centerLabel = false);
    ~ofxUICustomImageButton();
    void init(bool *_value, string _pathURL, string _name, int _size, int _labelWidth, int _labelHeight);
    void init(bool *_value, ofImage *_img, string _name, int _size, int _labelWidth, int _labelHeight);
	void setParent(ofxUIWidget *_parent);
    virtual void drawBack();
    virtual void drawOutline();
    virtual void drawOutlineHighlight();
    virtual void drawFill();
    virtual void drawFillHighlight();
    void setImage(ofImage *_image);
    
protected:
    bool autoSize; 
    ofxUIRectangle *labelBackgroundRect; 
    ofImage *image; 
}; 