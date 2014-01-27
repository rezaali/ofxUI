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

class ofxUILabel : public ofxUIWidget
{
public:
    ofxUILabel();
    ofxUILabel(float x, float y, string _name, string _label, int _size);
    ofxUILabel(float x, float y, string _name, int _size);
    ofxUILabel(string _name, string _label, int _size);
    ofxUILabel(string _name, int _size);
    ofxUILabel(float x, float y, float w, string _name, string _label, int _size);
    ofxUILabel(float x, float y, float w, string _name, int _size);
    ofxUILabel(float w, string _name, string _label, int _size);
    ofxUILabel(float w, string _name, int _size);
    ofxUILabel(float w, string _name, int _size, float h);
    
    void init(float x, float y, float w, float h, string _name, string _label, int _size);
    
    void drawBack();
    void drawFill();
    
    void drawFillHighlight();
    void drawBackLabel();
	
    void drawString(float x, float y, string _string);
    void drawStringShadow(float x, float y, string _string);
	
    float getStringWidth(string s);
	float getStringHeight(string s);

    float getLineHeight();
    virtual ofxUILabel* getLabelWidget();

    void setLabel(string _label);
    string& getLabel();
    
    bool getAutoSize();
    void setAutoSize(bool _autoSize);
	
    void setFont(ofxUIFont *_font);
	int getSize();
	
    void focus();
	void unfocus();
    
    void setVisible(bool _visible);
    bool isVisible();
    void toggleVisible();
    
protected:    
	int size;
	string label; 
    bool autoSize;
    int xOffset, yOffset; 
}; 