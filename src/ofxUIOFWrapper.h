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

#include "ofMain.h"
#include "ofPoint.h"

#ifndef OFX_UI_FONT_RENDERER
#define OFX_UI_FONT_RENDERER ofTrueTypeFont
#endif

typedef ofVec3f ofxUIVec3f;
typedef ofVec2f ofxUIVec2f;
typedef OFX_UI_FONT_RENDERER ofxUIFont;
typedef ofColor ofxUIColor;

#if defined( TARGET_OF_IPHONE ) || defined( TARGET_OF_IOS ) || defined( TARGET_ANDROID )
    #define OFX_UI_TARGET_TOUCH
#endif

#define OFX_UI_RECTMODE_CORNER OF_RECTMODE_CORNER
#define OFX_UI_RECTMODE_CENTER OF_RECTMODE_CENTER

class ofxUIAppCBGlue
{
public:        
    ofBaseApp *app;
    
    void EnableCallbacks()
	{
        enableAppDrawCallback();
        enableAppUpdateCallback();
        enableAppExitCallback();
#ifdef OFX_UI_TARGET_TOUCH
        enableTouchEventCallbacks();
#else
        enableMouseEventCallbacks();
        enableWindowEventCallbacks();
#endif
        enableKeyEventCallbacks();
	}
	
	void DisableCallbacks()
	{
        disableAppDrawCallback();
        disableAppUpdateCallback();
        disableAppExitCallback();
#ifdef OFX_UI_TARGET_TOUCH
        disableTouchEventCallbacks();
#else
        disableMouseEventCallbacks();
        disableWindowEventCallbacks();
#endif
        disableKeyEventCallbacks();
    }
    
   	//App Callbacks
    void enableAppEventCallbacks()
    {
        ofAddListener(ofEvents().update, this, &ofxUIAppCBGlue::onUpdate);
        ofAddListener(ofEvents().draw, this, &ofxUIAppCBGlue::onDraw);
        ofAddListener(ofEvents().exit, this, &ofxUIAppCBGlue::onExit);
    }
	
	//App Callbacks
    void disableAppEventCallbacks()
    {
        ofRemoveListener(ofEvents().update, this, &ofxUIAppCBGlue::onUpdate);
        ofRemoveListener(ofEvents().draw, this, &ofxUIAppCBGlue::onDraw);
        ofRemoveListener(ofEvents().exit, this, &ofxUIAppCBGlue::onExit);
    }
	
    void enableAppDrawCallback()
    {
        ofAddListener(ofEvents().draw, this, &ofxUIAppCBGlue::onDraw);
    }
    
    void enableAppUpdateCallback()
    {
        ofAddListener(ofEvents().update, this, &ofxUIAppCBGlue::onUpdate);
    }
    
    void enableAppExitCallback()
    {
        ofAddListener(ofEvents().exit, this, &ofxUIAppCBGlue::onExit);
    }
    
    void disableAppDrawCallback()
    {
        ofRemoveListener(ofEvents().draw, this, &ofxUIAppCBGlue::onDraw);
    }
    
    void disableAppUpdateCallback()
    {
        ofRemoveListener(ofEvents().update, this, &ofxUIAppCBGlue::onUpdate);
    }
    
    void disableAppExitCallback()
    {
        ofRemoveListener(ofEvents().exit, this, &ofxUIAppCBGlue::onExit);
    }
    
#ifdef OFX_UI_TARGET_TOUCH
	
	//Touch Callbacks
    void enableTouchEventCallbacks()
    {
        
        ofAddListener(ofEvents().touchUp, this, &ofxUIAppCBGlue::onTouchUp);
        ofAddListener(ofEvents().touchDown, this, &ofxUIAppCBGlue::onTouchDown);
        ofAddListener(ofEvents().touchMoved, this, &ofxUIAppCBGlue::onTouchMoved);
        ofAddListener(ofEvents().touchCancelled, this, &ofxUIAppCBGlue::onTouchCancelled);
        ofAddListener(ofEvents().touchDoubleTap, this, &ofxUIAppCBGlue::onTouchDoubleTap);
    }
    
	void disableTouchEventCallbacks()
    {
        ofRemoveListener(ofEvents().touchUp, this, &ofxUIAppCBGlue::onTouchUp);
        ofRemoveListener(ofEvents().touchDown, this, &ofxUIAppCBGlue::onTouchDown);
        ofRemoveListener(ofEvents().touchMoved, this, &ofxUIAppCBGlue::onTouchMoved);
        ofRemoveListener(ofEvents().touchCancelled, this, &ofxUIAppCBGlue::onTouchCancelled);
        ofRemoveListener(ofEvents().touchDoubleTap, this, &ofxUIAppCBGlue::onTouchDoubleTap);
    }
	
#else
	
	//Mouse Callbacks
    void enableMouseEventCallbacks()
    {
        ofAddListener(ofEvents().mouseReleased, this, &ofxUIAppCBGlue::onMouseReleased);
        ofAddListener(ofEvents().mousePressed, this, &ofxUIAppCBGlue::onMousePressed);
        ofAddListener(ofEvents().mouseMoved, this, &ofxUIAppCBGlue::onMouseMoved);
        ofAddListener(ofEvents().mouseDragged, this, &ofxUIAppCBGlue::onMouseDragged);
    }
    
	//Mouse Callbacks
    void disableMouseEventCallbacks()
    {
        ofRemoveListener(ofEvents().mouseReleased, this, &ofxUIAppCBGlue::onMouseReleased);
        ofRemoveListener(ofEvents().mousePressed, this, &ofxUIAppCBGlue::onMousePressed);
        ofRemoveListener(ofEvents().mouseMoved, this, &ofxUIAppCBGlue::onMouseMoved);
        ofRemoveListener(ofEvents().mouseDragged, this, &ofxUIAppCBGlue::onMouseDragged);
    }
    
    //Window Resize Callback
    void enableWindowEventCallbacks()
    {
        ofAddListener(ofEvents().windowResized, this, &ofxUIAppCBGlue::onWindowResized);
    }
    
	//Window Resize Callback
    void disableWindowEventCallbacks()
    {
        ofRemoveListener(ofEvents().windowResized, this, &ofxUIAppCBGlue::onWindowResized);
    }
	
#endif
    
    //KeyBoard Callbacks
	void enableKeyEventCallbacks()
	{
		ofAddListener(ofEvents().keyPressed, this, &ofxUIAppCBGlue::onKeyPressed);
		ofAddListener(ofEvents().keyReleased, this, &ofxUIAppCBGlue::onKeyReleased);
	}
    
	//KeyBoard Callbacks
	void disableKeyEventCallbacks()
	{
		ofRemoveListener(ofEvents().keyPressed, this, &ofxUIAppCBGlue::onKeyPressed);
		ofRemoveListener(ofEvents().keyReleased, this, &ofxUIAppCBGlue::onKeyReleased);
	}
    
    void onUpdate(ofEventArgs &data)
    {
        update();
    }
        
    void onDraw(ofEventArgs &data)
    {
        draw();
    }
        
    void onExit(ofEventArgs &data)
    {
        exit();
    }
    
    void onKeyPressed(ofKeyEventArgs& data)
    {
		keyPressed(data.key);
    }
    
    void onKeyReleased(ofKeyEventArgs& data)
    {
		keyReleased(data.key);
    }
    
    virtual void onMousePressed(ofMouseEventArgs& data)
    {
        mousePressed(data.x, data.y, data.button);
    }

    virtual void onMouseDragged(ofMouseEventArgs& data)
    {
        mouseDragged(data.x, data.y, data.button);
    }

    virtual void onMouseReleased(ofMouseEventArgs& data)
    {
        mouseReleased(data.x, data.y, data.button);
    }
        
    virtual void onMouseMoved(ofMouseEventArgs& data)
    {
        mouseMoved(data.x, data.y);
    }

    void onWindowResized(ofResizeEventArgs& data)
    {
		windowResized(data.width, data.height);
    }
    
    virtual void update()
    {
        
    }
    
    virtual void draw()
    {
        
    }
    
    virtual void exit()
    {
        
    }
    
    virtual void keyPressed(int key)
    {
        
    }
    
    virtual void keyReleased(int key)
    {
        
    }
    
    virtual void mousePressed(int x, int y, int button)
    {
        
    }

    virtual void mouseDragged(int x, int y, int button)
    {
        
    }

    virtual void mouseReleased(int x, int y, int button)
    {
        
    }
    
    virtual void mouseMoved(int x, int y)
    {
        
    }

    virtual void windowResized(int w, int h)
    {

    }
    
#ifdef OFX_UI_TARGET_TOUCH
	
    virtual void onTouchDown(ofTouchEventArgs &data)
    {
		touchDown(data.x, data.y, data.id);
    }
    
    virtual void onTouchMoved(ofTouchEventArgs &data)
    {
		touchMoved(data.x, data.y, data.id);
    }

    virtual void onTouchUp(ofTouchEventArgs &data)
    {
		touchUp(data.x, data.y, data.id);
    }

    virtual void onTouchDoubleTap(ofTouchEventArgs &data)
    {
		touchDoubleTap(data.x, data.y, data.id);
    }
    
	virtual void onTouchCancelled(ofTouchEventArgs &data)
    {
		touchCancelled(data.x, data.y, data.id);
    }
    
    virtual void touchDown(float x, float y, int id)
    {
        
    }
    
    virtual void touchMoved(float x, float y, int id)
    {
        
    }
    
    virtual void touchUp(float x, float y, int id)
    {
        
    }
    
    virtual void touchDoubleTap(float x, float y, int id)
    {
        
    }

    virtual void touchCancelled(float x, float y, int id)
    {
        
    }

#endif
};

static void ofxUISetColor(ofxUIColor color, float alpha)
{
    ofSetColor(color, alpha);
}

static void ofxUISetColor(ofxUIColor color)
{
    ofSetColor(color);
}

static void ofxUIFill()
{
    ofFill();
}

static void ofxUINoFill()
{
    ofNoFill();
}

static void ofxUIPushStyle()
{
    ofPushStyle();
#ifndef TARGET_OPENGLES
    glPushAttrib(GL_ALL_ATTRIB_BITS);
#endif
}

static void ofxUIPopStyle()
{
#ifndef TARGET_OPENGLES    
    glPopAttrib();
#endif
    ofPopStyle();
}

static void ofxUISetLineWidth(float lineWidth)
{
    ofSetLineWidth(lineWidth);
}

static float ofxUIGetFrameRate()
{
    return ofGetFrameRate();
}

static void ofxUISetRectMode(ofRectMode rectMode)
{
    ofSetRectMode(rectMode);
}

static void ofxUICircle(float x, float y, float radius)
{
    ofCircle(x, y, radius);
}

static void ofxUIDrawRect(float x, float y, float w, float h)
{
    ofRect(x,y,w,h);
}

static void ofxUIDrawLine(float x1, float y1, float x2, float y2)
{
    ofLine(x1, y1, x2, y2); 
}

static int ofxUIGetHeight()
{
    return ofGetHeight(); 
}

static int ofxUIGetWidth()
{
    return ofGetWidth();
}