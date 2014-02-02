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
#include "ofxUIToggle.h"
#include "ofxUIDefines.h"

class ofxUIToggleMatrix : public ofxUIWidget
{
public:
    ofxUIToggleMatrix(float x, float y, float w, float h, int _rows, int _cols, string _name, int _size = OFX_UI_FONT_SMALL);
    ofxUIToggleMatrix(float w, float h, int _rows, int _cols, string _name, int _size = OFX_UI_FONT_SMALL);
    void init(float x, float y, float w, float h, int _rows, int _cols, string _name, int _size = OFX_UI_FONT_SMALL);
    void setVisible(bool _visible);
	void activateToggle(string _name);
	void setParent(ofxUIWidget *_parent);
    
    void setAllToggles(bool _value, bool _trigger = true);
    void setToggle(unsigned int row, unsigned int col, bool _value, bool _trigger = true);
    ofxUIToggle * getToggle(unsigned int row, unsigned int col);
    bool getState(int row, int col);
    
    int getColumnCount();
    int getRowCount();
    
	vector<ofxUIToggle *> getToggles();
	vector<ofxUIToggle *> *getTogglesPtr();
	void triggerEvent(ofxUIWidget *child);
    void setAllowMultiple(bool _allowMultiple);
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
protected:
	vector<ofxUIToggle *> toggles; 		   
    int rows, cols;
    float toggleWidth, toggleHeight; 
    bool allowMultiple;     
};