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

class ofxUIScrollableCanvas : public ofxUICanvas
{    
public:    
    ~ofxUIScrollableCanvas();
    ofxUIScrollableCanvas(float x, float y, float w, float h);
    ofxUIScrollableCanvas(float x, float y, float w, float h, ofxUICanvas *sharedResources);
    ofxUIScrollableCanvas();
    ofxUIScrollableCanvas(ofxUICanvas *sharedResources);
    void initScrollable();
    void setDamping(float _damping);
    void setSnapping(bool _snapping);
    void setScrollArea(float x, float y, float w, float h);
    void setScrollAreaToScreen();
    void setScrollAreaToScreenWidth();
    void setScrollAreaToScreenHeight();
    void setScrollAreaHeight(float _height);
    void setScrollAreaWidth(float _width);
    void setScrollableDirections(bool _scrollX, bool _scrollY);
    void setStickDistance(float _stickyDistance);
    void dampenX();
    void dampenY();
    void update();
    virtual void drawBack();
    virtual void drawOutline();
    virtual void drawOutlineHighlight();
    virtual void drawFill();
    virtual void drawFillHighlight();
    virtual void drawPadded();
    virtual void drawPaddedOutline();
    virtual void draw();
    virtual void setPosition(int x, int y);
    virtual void setDimensions(float _width, float _height);
    void drawScrollableRect();

#ifdef OFX_UI_TARGET_TOUCH
    void touchDown(float x, float y, int id);
    void touchMoved(float x, float y, int id);
    void touchUp(float x, float y, int id);
    void touchCancelled(float x, float y, int id);
#endif
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    ofxUIRectangle *getSRect();
    virtual bool isHit(int x, int y);

protected:
    ofxUIRectangle *sRect;
    bool isScrolling;
    bool snapping; 
    bool scrollX, scrollY; 
    bool nearTop, nearBot, nearRight, nearLeft;
    bool hitWidget; 
    ofPoint pos; 
    ofPoint ppos; 
    ofPoint vel; 
    ofPoint acc; 
    float damping;
    float stickyDistance;     
};