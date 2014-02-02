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

#include "ofxUICanvas.h"
#include "ofxUIDefines.h"

class ofxUISuperCanvas : public ofxUICanvas
{
public:
    ofxUISuperCanvas(const ofxUISuperCanvas &other);
    ofxUISuperCanvas(string _label, ofxUIRectangle r, int _size = OFX_UI_FONT_MEDIUM);
    ofxUISuperCanvas(string _label, float x, float y, float w, float h, int _size = OFX_UI_FONT_MEDIUM);
    ofxUISuperCanvas(string _label, float x, float y, float w, float h, ofxUICanvas *sharedResources, int _size = OFX_UI_FONT_MEDIUM);
    ofxUISuperCanvas(string _label, int _size = OFX_UI_FONT_MEDIUM);
    ofxUISuperCanvas(string _label, ofxUICanvas *sharedResources, int _size = OFX_UI_FONT_MEDIUM);
    void superInit(string _label, int _size);
    void setDeltaTime(float _deltaTime);
    void setMinified(bool _bIsMinified);
    bool isMinified();
    void toggleMinified();
    ofxUILabel *getCanvasTitle();

#ifdef OFX_UI_TARGET_TOUCH
    virtual void touchDown(float x, float y, int id);
    virtual void touchMoved(float x, float y, int id);
    virtual void touchUp(float x, float y, int id);
    virtual void touchDoubleTap(float x, float y, int id);
    virtual void touchCancelled(float x, float y, int id);
#else
    virtual void onMouseReleased(ofMouseEventArgs& data);
    virtual void onMousePressed(ofMouseEventArgs& data);
    virtual void onMouseDragged(ofMouseEventArgs& data);
#endif
    
    virtual void saveSettings(string fileName);
    virtual void loadSettings(string fileName);
    void addWidgetToHeader(ofxUIWidget *widget);
    void removeWidgets();
    
protected:
    void minify();
    void maximize();
    
    int size; 
    string title; 
    ofxUILabel *canvasTitle;
    vector<ofxUIWidget *> headerWidgets;
    
    ofxUIVec2f hitPoint;
    float deltaTime;
    float lastHitTime;
    bool bIsMinified;
    bool bTitleLabelHit;
};