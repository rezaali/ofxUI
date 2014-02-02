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

#include "ofxUIToggle.h"
#include "ofxUILabelToggle.h"

class ofxUIDropDownList : public ofxUIToggle
{
public:    
    ofxUIDropDownList(string _name, vector<string> items, float w = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_MEDIUM);
    ofxUIDropDownList(float x, float y, float w, string _name, vector<string> items, int _size);
    ofxUIDropDownList(float w, string _name, vector<string> items, int _size);
    ofxUIDropDownList(float x, float y, string _name, vector<string> items, int _size);
    void init(string _name, vector<string> items, float w = 0, float x = 0, float y = 0, int _size = OFX_UI_FONT_MEDIUM);
    virtual void draw();
    void clearToggles();
    void clearSelected();
    void addToggle(string toggleName);
    void addToggles(vector<string>& toggleNames);
    void removeToggle(string toggleName);
    bool* getShowCurrentSelectedPtr();
    bool getShowCurrentSelected();
    void setShowCurrentSelected(bool _bShowCurrentSelected);
    void checkAndSetTitleLabel();
    vector<ofxUIWidget *> & getSelected();
    vector<int> & getSelectedIndeces();
    vector<string> getSelectedNames(); 
    void setLabelText(string labeltext);
    void setParent(ofxUIWidget *_parent);
    void mouseReleased(int x, int y, int button);
    void setAutoClose(bool _autoClose);
    void open();
    void close();
    void setVisible(bool _visible);
    void setToggleVisibility(bool _value);
    vector<ofxUILabelToggle *> &getToggles();
    void triggerSelf();
    void triggerEvent(ofxUIWidget *child);
	void activateToggle(string _name);
    void setAllowMultiple(bool _allowMultiple);
    virtual void setValue(bool _value);
    virtual void setModal(bool _modal);      
    bool isOpen();
    
protected:
    bool autoSize; 
    bool autoClose;
    bool bShowCurrentSelected; 
    vector<ofxUILabelToggle *> toggles;
    ofxUILabelToggle *singleSelected;
    vector<ofxUIWidget *> selected;
    vector<int> selectedIndeces;
    bool allowMultiple;
    int size;     
}; 