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

#include "ofxUIRectangle.h"

ofxUIRectangle::ofxUIRectangle()
{
    x = y = width = height = halfheight = halfwidth = 0.0f;
    setParent(NULL);
}

ofxUIRectangle::ofxUIRectangle(float _x, float _y, float _w, float _h)
{
    x = _x;
    y = _y;
    width = _w;
    halfwidth = width*.5;
    height = _h;
    halfheight = height*.5;
    setParent(NULL);
}

ofxUIRectangle::ofxUIRectangle(ofxUIRectangle const & r)
{
    x = r.x;
    y = r.y;
    width = r.width;
    halfwidth = width*.5;
    height = r.height;
    halfheight = height*.5;
    setParent(NULL);
}

void ofxUIRectangle::set(float px, float py, float w, float h)
{
    x		= px;
    y		= py;
    width	= w;
    height	= h;
    halfwidth = width*.5;
    halfheight = height*.5;
}

void ofxUIRectangle::setX(float px)
{
    x = px;
}

void ofxUIRectangle::setY(float py)
{
    y = py;
}

void ofxUIRectangle::setParent(ofxUIRectangle *_parent)
{
    parent = _parent;
}

void ofxUIRectangle::setHeight(float _height)
{
    height = _height;
    halfheight = height*.5;
}

void ofxUIRectangle::setWidth(float _width)
{
    width = _width;
    halfwidth = width*.5;
}

float ofxUIRectangle::getMinX() const
{
    return MIN(x, x + width);  // - width
}

float ofxUIRectangle::getMaxX() const
{
    return MAX(x, x + width);  // - width
}

float ofxUIRectangle::getMinY() const
{
    return MIN(y, y + height);  // - height
}

float ofxUIRectangle::getMaxY() const
{
    return MAX(y, y + height);  // - height
}

bool ofxUIRectangle::inside(ofPoint p)
{
    if(parent !=NULL)
    {
        return insideParent(p.x, p.y);
    }
    else
    {
        return insideChild(p.x, p.y);
    }
}

bool ofxUIRectangle::inside(float px, float py)
{
    if(parent != NULL)
    {
        return insideParent(px,py);
    }
    else
    {
        return insideChild(px,py);
    }
}

bool ofxUIRectangle::insideChild(float px, float py)
{
    if( px > x && py > y && px < x + width && py < y + height ){
        return true;
    }
    return false;
    
}

bool ofxUIRectangle::insideParent(float px, float py)
{
    if( px > (x+parent->getX()) && py > (y+parent->getY()) && px < (x+parent->getX()) + width && py < (y+parent->getY()) + height )
    {
        return true;
    }
    return false;
}

ofxUIVec2f ofxUIRectangle::percentInside(float px, float py)				//Assumes your already inside rect
{
    if(parent != NULL)
    {
        return percentInsideParent(px,py);
    }
    else
    {
        return percentInsideChild(px,py);
    }
}

ofxUIVec2f ofxUIRectangle::percentInsideChild(float px, float py)
{
    return ofxUIVec2f((px-x)/(width), (py-y)/(height));
}

ofxUIVec2f ofxUIRectangle::percentInsideParent(float px, float py)
{
    return ofxUIVec2f((px-(x+parent->getX()))/(width), (py-(y+parent->getY()))/(height));
}

void ofxUIRectangle::draw()
{
    if(parent != NULL)
    {
        ofxUIDrawRect(parent->getX()+x, parent->getY()+y, width, height);
    }
    else
    {
        ofxUIDrawRect(x,y,width,height);
    }
}

float ofxUIRectangle::getX(bool recursive)
{
    if(parent != NULL && recursive)
    {
        return (x+parent->getX());
    }
    else
    {
        return x;
    }
}

float ofxUIRectangle::getY(bool recursive)
{
    if(parent != NULL && recursive)
    {
        return (y+parent->getY());
    }
    else
    {
        return y;
    }
}

float ofxUIRectangle::getWidth()
{
    return width;
}

float ofxUIRectangle::getHeight()
{
    return height;
}

float ofxUIRectangle::getHalfWidth()
{
    return halfwidth;
}

float ofxUIRectangle::getHalfHeight()
{
    return halfheight;
}

float ofxUIRectangle::getRelativeMinX()
{
    return MIN(getX(), getX() + getWidth());    // - width
}

float ofxUIRectangle::getRelativeMinY()
{
    return MIN(getY(), getY() + getHeight());   // - height
}

float ofxUIRectangle::getRelativeMaxX()
{
    return MAX(getX(), getX() + getWidth());    // - width
}

float ofxUIRectangle::getRelativeMaxY()
{
    return MAX(getY(), getY() + getHeight());   // - height
}

bool ofxUIRectangle::rIntersects(const ofxUIRectangle& rect)
{
    return (getRelativeMinX() < rect.getMaxX() && getRelativeMaxX() > rect.getMinX() &&
            getRelativeMinY() < rect.getMaxY() && getRelativeMaxY() > rect.getMinY());
}

bool ofxUIRectangle::rInside(const ofxUIRectangle& rect)
{
    return (getRelativeMinX() > rect.getMinX() && getRelativeMaxX() < rect.getMaxX() &&
            getRelativeMinY() > rect.getMinY() && getRelativeMaxY() < rect.getMaxY());
}