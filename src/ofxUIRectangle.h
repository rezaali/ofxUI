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

#include "ofxUIOFWrapper.h"

class ofxUIRectangle
{
public:
    ofxUIRectangle();
    ofxUIRectangle(float _x, float _y, float _w, float _h);
    ofxUIRectangle(ofxUIRectangle const & r);
    
    void setParent(ofxUIRectangle *_parent);
    
    void set(float px, float py, float w, float h);
    
    void setX(float px);
    float getX(bool recursive = true);

    void setY(float py);
    float getY(bool recursive = true);
    
	void setHeight(float _height);
    float getWidth();
    
	void setWidth(float _width);
	float getHeight();
    
    float getMinX() const;
    float getMaxX() const;
    
    float getMinY() const;
    float getMaxY() const;
    
    bool inside(ofPoint p);
    bool inside(float px, float py);
    bool insideChild(float px, float py);
    bool insideParent(float px, float py);
	
    ofxUIVec2f percentInside(float px, float py);
	ofxUIVec2f percentInsideChild(float px, float py);
    ofxUIVec2f percentInsideParent(float px, float py);
    
    void draw();
    
    float getHalfWidth();
	float getHalfHeight();
    
    float getRelativeMinX();
    float getRelativeMinY();
    
    float getRelativeMaxX();
    float getRelativeMaxY();
    
    bool rIntersects(const ofxUIRectangle& rect);
    bool rInside(const ofxUIRectangle& rect);

    float x;
    float y;
    float width;
    float height;

protected:
    float halfwidth;
    float halfheight;
    ofxUIRectangle *parent; 
};