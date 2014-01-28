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

class ofxUINumberDialer : public ofxUIWidgetWithLabel
{
public:
    ofxUINumberDialer(float x, float y, float _min, float _max, float _value, int _precision, string _name, int _size);
    ofxUINumberDialer(float _min, float _max, float _value, int _precision, string _name, int _size);
    ofxUINumberDialer(float x, float y, float _min, float _max, float *_value, int _precision, string _name, int _size);
    ofxUINumberDialer(float _min, float _max, float *_value, int _precision, string _name, int _size);
    ~ofxUINumberDialer();
    void init(float x, float y, float w, float h, float _min, float _max, float *_value, int _precision, string _name, int _size);
    virtual void update();
    virtual void drawFill();
    virtual void drawFillHighlight();
    void calculatePrecisionZone();
    float getMax();
    float getMin();
    float getValue();
    void setValue(float _value);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);
    void keyReleased(int key);
    void windowResized(int w, int h);
    void stateChange();
	string getTextString();
	void setTextString(string s);
	void setParent(ofxUIWidget *_parent);
    bool isDraggable();
    string numToString(float value, int precision, int width, char fill);
    bool hasState(){ return true; };
#ifndef OFX_UI_NO_XML
    virtual void saveState(ofxXmlSettings *XML);
    virtual void loadState(ofxXmlSettings *XML);
#endif    
    
protected:
	string textstring;
    string displaystring;
    int precision; 
	float zoneMultiplier; 
	float *value;  
    bool useReference;     
	float max, min; 
    ofPoint hitPoint; 
    int numOfPrecisionZones;
    int currentPrecisionZone;
    int hasPeriod; 
};