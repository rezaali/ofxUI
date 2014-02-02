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

#include "ofxUIToggleMatrix.h"
#include "ofxUI.h"

ofxUIToggleMatrix::ofxUIToggleMatrix(float x, float y, float w, float h, int _rows, int _cols, string _name, int _size) : ofxUIWidget()
{
    init(x, y, w, h, _rows, _cols, _name, _size);
}

ofxUIToggleMatrix::ofxUIToggleMatrix(float w, float h, int _rows, int _cols, string _name, int _size) : ofxUIWidget()
{
    init(0, 0, w, h, _rows, _cols, _name, _size);
}

void ofxUIToggleMatrix::init(float x, float y, float w, float h, int _rows, int _cols, string _name, int _size)
{
    initRect(x,y,w,h);
    name = string(_name);
    kind = OFX_UI_WIDGET_TOGGLEMATRIX;
    rows = _rows;
    cols = _cols;
    draw_back = false;
    
    toggleWidth = w;
    toggleHeight = h;
    
    for(int j = 0; j < rows; j++)
    {
        for(int i = 0; i < cols; i++)
        {
            ofxUIToggle *toggle = new ofxUIToggle((name+"("+ofxUIToString(i,0)+","+ofxUIToString(j,0)+")"), false, toggleWidth, toggleHeight, 0, 0, OFX_UI_FONT_SMALL);
            toggle->setLabelVisible(false);
            addEmbeddedWidget(toggle);
            toggles.push_back(toggle);
        }
    }
    allowMultiple = true;
}

void ofxUIToggleMatrix::setVisible(bool _visible)
{
    visible = _visible;
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ofxUIToggle *t = toggles[i];
        t->setVisible(visible);
        t->getLabelWidget()->setVisible(false);
    }
}

void ofxUIToggleMatrix::activateToggle(string _name)
{
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ofxUIToggle *t = toggles[i];
        if(!(t->getName().compare(_name.c_str())))
        {
            t->setValue(true);
        }
        else
        {
            t->setValue(false);
        }
    }
}

void ofxUIToggleMatrix::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    
    float tWidth = cols*(toggles[0]->getRect()->getWidth())+(cols-1)*padding;
    float tHeight = rows*(toggles[0]->getRect()->getHeight())+(rows-1)*padding;
    
    ofPoint pos = ofPoint(0,0);
    for(int j = 0; j < rows; j++)
    {
        for(int i = 0; i < cols; i++)
        {
            int index = i+j*cols;
            ofxUIToggle *t = toggles[index];
            t->getRect()->setX(pos.x);
            t->getRect()->setY(pos.y);
            t->setLabelVisible(false);
            t->setParent(this);            
            pos.x += toggleWidth+padding;
        }
        pos.y += toggleHeight+padding;
        pos.x = 0;
    }
    
    rect->setWidth(tWidth);
    rect->setHeight(tHeight);
    calculatePaddingRect();
}

void ofxUIToggleMatrix::setAllToggles(bool _value, bool _trigger)
{
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ofxUIToggle *t = toggles[i];
        t->setValue(_value);
        if(_trigger)
        {
            parent->triggerEvent(t);
        }
    }
    parent->triggerEvent(this);
}

void ofxUIToggleMatrix::setToggle(unsigned int row, unsigned int col, bool _value, bool _trigger)
{
    ofxUIToggle *t = getToggle(row, col);
    if(t != NULL)
    {
        t->setValue(_value);
        if(_trigger)
            parent->triggerEvent(t);
    }
    parent->triggerEvent(this);
}

ofxUIToggle * ofxUIToggleMatrix::getToggle(unsigned int row, unsigned int col)
{
    if(row*col < toggles.size())
    {
        return toggles[col+row*cols];
    }
    return NULL;
}

bool ofxUIToggleMatrix::getState(int row, int col)
{
    ofxUIToggle *t = getToggle(row, col);
    if(t != NULL)
    {
        return t->getValue();
    }
    return false;
}

int ofxUIToggleMatrix::getColumnCount()
{
    return cols;
}

int ofxUIToggleMatrix::getRowCount()
{
    return rows;
}

vector<ofxUIToggle *> ofxUIToggleMatrix::getToggles()
{
    return toggles;
}

vector<ofxUIToggle *> * ofxUIToggleMatrix::getTogglesPtr()
{
    return &toggles;
}

void ofxUIToggleMatrix::triggerEvent(ofxUIWidget *child)
{
    if(!allowMultiple)
    {
        activateToggle(child->getName().c_str());
    }
    if(parent != NULL)
    {
        parent->triggerEvent(child);
    }
}

void ofxUIToggleMatrix::setAllowMultiple(bool _allowMultiple)
{
    allowMultiple = _allowMultiple;
}

void ofxUIToggleMatrix::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        bool tv = false;
        if(ofGetKeyPressed())
        {
            tv = true;
        }
        
        for(vector<ofxUIToggle *>::iterator it = toggles.begin(); it != toggles.end(); ++it)
        {
            if((*it)->isHit(x, y))
            {
                (*it)->setValue(tv);
            }
        }
    }
}

void ofxUIToggleMatrix::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        hit = true;
        state = OFX_UI_STATE_DOWN;
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUIToggleMatrix::mouseReleased(int x, int y, int button)
{
    if(hit)
    {
        hit = false;
    }
}