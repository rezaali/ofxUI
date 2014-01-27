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

#include "ofxUIDragableLabelButton.h"

ofxUIDraggableLabelButton::ofxUIDraggableLabelButton(string _name, bool _value, float w, float h, float x, float y, int _size, bool _justifyLeft) : ofxUILabelButton(_name, _value, w, h, x, y, _size, _justifyLeft)
{
    useReference = false;
    init(_name, &_value, w, h, x, y, _size, _justifyLeft);
}

ofxUIDraggableLabelButton::ofxUIDraggableLabelButton(string _name, bool *_value, float w, float h, float x, float y, int _size, bool _justifyLeft) : ofxUILabelButton(_name, *_value, w, h, x, y, _size, _justifyLeft)
{
    useReference = true;
    init(_name, _value, w, h, x, y, _size, _justifyLeft);
}

void ofxUIDraggableLabelButton::init(string _name, bool *_value, float w, float h, float x, float y, int _size, bool _justifyLeft)
{
    saveX = posX = x;
    saveY = posY = y;
    onPressed = false;
    isDraggedOut = false;
    kind = OFX_UI_WIDGET_DRAGABLELABELBUTTON;
    id = "";
}

bool ofxUIDraggableLabelButton::isDraggable()
{
    return true;
}

void ofxUIDraggableLabelButton::setPos(int x , int y)// TODO easing
{
    int h = rect->getHeight();
    int w = rect->getWidth();
    ofxUIRectangle* parentRect = getParent()->getRect();
    int parentHeight = parentRect->getHeight();
    int parentWidth = parentRect->getWidth();
    
    int xClamped = ofClamp(x, padding, (parentWidth - padding - w));
    int yClamped = ofClamp(y, padding, (parentHeight - padding - h));
    
    posX = xClamped;
    posY = yClamped;
    
    rect->setY(yClamped);
    rect->setX(xClamped);
}

int ofxUIDraggableLabelButton::getMidY()//TODO this method mainly exists for the ofxSortableList class, not sure it belongs here
{
    return (posY + (int)(rect->getHeight()/2));
}

void ofxUIDraggableLabelButton::setSortID(string a_id)//TODO again, this is mainly for the ofxSortableList, maybe the ids should be modeled internally in ofxSortableList
{
    id = a_id;
}

std::string ofxUIDraggableLabelButton::getSortID()
{
    return id;
}

int ofxUIDraggableLabelButton::getY()
{
    return posY;
}

void ofxUIDraggableLabelButton::mouseDragged(int x, int y, int button)
{
    if(isHit(x, y)) // mouse dragged inside
    {
        if(!onPressed) return;
        posX = x - saveX;
        posY = y - saveY;
    }
    else //mouse dragged outside
    {
        if(!onPressed) return;
        isDraggedOut = true;
        posX = x - saveX;
        posY = y - saveY;
    }
    setPos(posX, posY);
}

void ofxUIDraggableLabelButton::mousePressed(int x, int y, int button)
{
    if(isHit(x,y))
    {
        isDraggedOut = false;
        saveX = x - posX;
        saveY = y - posY;
        onPressed = true;
    }
}

void ofxUIDraggableLabelButton::mouseReleased(int x, int y, int button)
{
    if(onPressed)
    {
        setPos(posX, posY);
    }
    onPressed = false;
    isDraggedOut = false;
}