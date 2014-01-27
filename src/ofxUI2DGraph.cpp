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

#include "ofxUI2DGraph.h"
#include "ofxUI.h"

ofxUI2DGraph::ofxUI2DGraph(string _name, ofPoint _rangeX, ofPoint _rangeY, int _bufferSize, float * _xValues, float * _yValues, float w, float h, float x, float y) : ofxUIWidget()
{
    init(_name, _rangeX, _rangeY, _bufferSize, _xValues, _yValues, w, h, x, y);
}

void ofxUI2DGraph::init(string _name, ofPoint _rangeX, ofPoint _rangeY, float _bufferSize, float * _xValues, float * _yValues, float w, float h, float x, float y)
{
    initRect(x, y, w, h);
    name = string(_name);
    kind = OFX_UI_WIDGET_2DGRAPH;
    draw_fill = true;
    
    bufferSize = _bufferSize;
    rangeX = _rangeX;
    rangeY = _rangeY;
    
    xValues = _xValues;
    yValues = _yValues;
    
    inc = MAX(rect->getHalfHeight(), rect->getHalfWidth())/6.0;
}

void ofxUI2DGraph::drawBack()
{
    if(draw_back)
    {
        ofFill();
        ofSetColor(color_back);
        rect->draw();
        
        ofPushMatrix();
        ofTranslate(rect->getX(), rect->getY(), 0);
        
        for(int x = 0; x <= rect->getWidth(); x+=inc)
        {
            ofLine(x, 0, x, rect->getHeight());   //y
        }
        
        for(int y = 0; y <= rect->getHeight(); y+=inc)
        {
            ofLine(0, y, rect->getWidth(), y);   //x
        }
        
        ofSetLineWidth(2);
        ofLine(rect->getHalfWidth(), 0, rect->getHalfWidth(), rect->getHeight());
        ofLine(0, rect->getHalfHeight(), rect->getWidth(), rect->getHalfHeight());
        ofPopMatrix();
        ofNoFill();
        rect->draw();
        
        ofSetLineWidth(1);
        ofFill();
    }
}


void ofxUI2DGraph::drawFill()
{
    if(draw_fill)
    {
        ofNoFill();
        if(draw_fill_highlight)
        {
            ofSetColor(color_fill_highlight);
        }
        else
        {
            ofSetColor(color_fill);
        }
        if(xValues != NULL && yValues != NULL)
        {
            ofPushMatrix();
            ofTranslate(rect->getX(), rect->getY(), 0);
            ofSetLineWidth(1.5);
            ofPolyline line;
            for(int i =0; i < bufferSize; i++)
            {
                line.addVertex(ofMap(xValues[i], rangeX.x, rangeX.y, 0.0, rect->getWidth(), true), ofMap(yValues[i], rangeY.x, rangeY.y, 0.0, rect->getHeight(), true));
            }
            line.draw();
            ofSetLineWidth(1);
            ofPopMatrix();
        }
    }
}