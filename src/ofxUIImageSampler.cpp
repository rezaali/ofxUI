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

#include "ofxUIImageSampler.h"
#include "ofxUI.h"

ofxUIImageSampler::ofxUIImageSampler(float x, float y, float w, float h, ofImage *_image, string _name) : ofxUIImage(x, y, w, h, _image, _name)
{
    initSampler();
}

ofxUIImageSampler::ofxUIImageSampler(float w, float h, ofImage *_image, string _name) : ofxUIImage(w, h, _image, _name)
{
    initSampler();
}

void ofxUIImageSampler::initSampler()
{
    setLabelVisible(false);
    value.x = .5;
    value.y = .5;
    input(value.x*rect->getWidth(),value.y*rect->getHeight());
    kind = OFX_UI_WIDGET_IMAGESAMPLER;
    squareSize = OFX_UI_GLOBAL_WIDGET_SPACING;
}

void ofxUIImageSampler::setSquareSize(float _squareSize)
{
    squareSize = _squareSize;
}

void ofxUIImageSampler::drawFill()
{
    if(draw_fill)
    {
        if(image != NULL)
        {
            ofxUIFill();
            ofxUISetColor(255);
            image->draw(rect->getX(), rect->getY(), rect->width, rect->height);
        }
        ofxUISetColor(color_fill);
        ofxUIDrawLine(rect->getX()+value.x*rect->getWidth(),  rect->getY(), rect->getX()+value.x*rect->getWidth(),  rect->getY()+rect->getHeight());
        ofxUIDrawLine(rect->getX(),  rect->getY()+value.y*rect->getHeight(), rect->getX()+rect->getWidth(),  rect->getY()+value.y*rect->getHeight());
        
        ofxUIFill();
        ofxUISetColor(sampledColor);
        ofxUISetRectMode(OFX_UI_RECTMODE_CENTER);
        ofxUIDrawRect(rect->getX()+value.x*rect->getWidth(), rect->getY()+value.y*rect->getHeight(), squareSize, squareSize);
        ofxUISetRectMode(OFX_UI_RECTMODE_CORNER);
        
    }
}

void ofxUIImageSampler::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ofxUISetColor(color_fill_highlight);
        ofxUIDrawLine(rect->getX()+value.x*rect->getWidth(),  rect->getY(), rect->getX()+value.x*rect->getWidth(),  rect->getY()+rect->getHeight());
        ofxUIDrawLine(rect->getX(),  rect->getY()+value.y*rect->getHeight(), rect->getX()+rect->getWidth(),  rect->getY()+value.y*rect->getHeight());
        
        ofxUIFill();
        ofxUISetColor(sampledColor);
        ofxUISetRectMode(OFX_UI_RECTMODE_CENTER);
        ofxUIDrawRect(rect->getX()+value.x*rect->getWidth(), rect->getY()+value.y*rect->getHeight(), squareSize, squareSize);
        ofxUISetRectMode(OFX_UI_RECTMODE_CORNER);
    }
}

void ofxUIImageSampler::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        state = OFX_UI_STATE_DOWN;
        if(triggerType & OFX_UI_TRIGGER_CHANGE)
        {
            input(x, y);
            triggerEvent(this);
        }
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUIImageSampler::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        hit = true;
        state = OFX_UI_STATE_DOWN;
        if(triggerType & OFX_UI_TRIGGER_BEGIN)
        {
            input(x, y);
            triggerEvent(this);
        }
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUIImageSampler::mouseReleased(int x, int y, int button)
{
    if(hit)
    {
#ifdef OFX_UI_TARGET_TOUCH
        state = OFX_UI_STATE_NORMAL;
#else
        state = OFX_UI_STATE_OVER;
#endif
        if(triggerType & OFX_UI_TRIGGER_END)
        {
            input(x, y);
            triggerEvent(this);
        }
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
    hit = false;
}

void ofxUIImageSampler::stateChange()
{
    switch (state) {
        case OFX_UI_STATE_NORMAL:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
        }
            break;
        case OFX_UI_STATE_OVER:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = true;
        }
            break;
        case OFX_UI_STATE_DOWN:
        {
            draw_fill_highlight = true;
            draw_outline_highlight = true;
        }
            break;
        case OFX_UI_STATE_SUSTAINED:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
        }
            break;
            
        default:
            break;
    }
}

void ofxUIImageSampler::input(int x, int y)
{
    ofxUIVec2f _v = rect->percentInside(x, y);
    setValue(_v);
}

ofColor& ofxUIImageSampler::getColor()
{
    return sampledColor;
}

void ofxUIImageSampler::setColor(ofColor _sampledColor)
{
    sampledColor = _sampledColor;
}

ofPoint ofxUIImageSampler::getValue()
{
    return value;
}

void ofxUIImageSampler::setValue(ofPoint _value)
{
    value.x = MIN(1.0, MAX(0.0, _value.x));
    value.y = MIN(1.0, MAX(0.0, _value.y));
    sampledColor = image->getColor(value.x*(image->getWidth()-1), value.y*(image->getHeight()-1));
}

bool ofxUIImageSampler::isDraggable()
{
    return true;
}

#ifndef OFX_UI_NO_XML

void ofxUIImageSampler::saveState(ofxXmlSettings *XML)
{
    XML->setValue("XValue", getValue().x, 0);
    XML->setValue("YValue", getValue().y, 0);
    XML->setValue("RColor", getColor().r, 0);
    XML->setValue("GColor", getColor().g, 0);
    XML->setValue("BColor", getColor().b, 0);
    XML->setValue("AColor", getColor().a, 0);
}

void ofxUIImageSampler::loadState(ofxXmlSettings *XML)
{
    setValue(ofxUIVec2f(XML->getValue("XValue", getValue().x, 0), XML->getValue("YValue", getValue().y, 0)));
    setColor(ofxUIColor(XML->getValue("RColor", getColor().r, 0),
                        XML->getValue("GColor", getColor().g, 0),
                        XML->getValue("BColor", getColor().b, 0),
                        XML->getValue("AColor", getColor().a, 0)));
}

#endif