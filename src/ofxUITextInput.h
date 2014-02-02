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

class ofxUITextInput : public ofxUIWidgetWithLabel
{
public:
    ofxUITextInput(string _name, string _textstring, float w, float h = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    void init(string _name, string _textstring, float w, float h = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    virtual void drawFill();
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);
    void unClick();
    void stateChange();
	bool isClicked();
	string getTextString();
    void setInputTriggerType(int _triggerType);
    int getInputTriggerType();
	void setTextString(string s);
	void setParent(ofxUIWidget *_parent);
	void setAutoClear(bool _autoclear);
    void setAutoUnfocus(bool _autoUnfocus);
    bool isFocused();
    void setFocus(bool _focus); 
    void setTriggerOnClick(bool _triggerOnClick);
    void recalculateDisplayString();
    bool hasState(){ return true; };
#ifndef OFX_UI_NO_XML
    virtual void saveState(ofxXmlSettings *XML);
    virtual void loadState(ofxXmlSettings *XML);
#endif    

protected:
	string textstring; 
	string defaultstring; 
    string displaystring; 
	bool clicked;
    bool autoUnfocus; 
	float theta; 
	float cursorWidth; 
	float spaceOffset;		
	bool autoclear; 
	float defaultY, defaultX; 	
	int inputTriggerType;
    int maxsize;
    bool triggerOnClick;
    
    unsigned int cursorPosition;
    unsigned int firstVisibleCharacterIndex;
}; 