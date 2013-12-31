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

#include "ofxUIBaseDraws.h"
#include "ofxUI.h"

ofxUIBaseDraws::ofxUIBaseDraws(float x, float y, float w, float h, ofBaseDraws* _image, string _name) : ofxUIWidgetWithLabel()
{
    rect = new ofxUIRectangle(x,y,w,h);
    init(w, h, _image, _name);
}

ofxUIBaseDraws::ofxUIBaseDraws(float x, float y, float w, float h, ofBaseDraws* _image, string _name, bool _showLabel) : ofxUIWidgetWithLabel()
{
    rect = new ofxUIRectangle(x,y,w,h);
    init(w, h, _image, _name);
    showLabel = _showLabel;
}

ofxUIBaseDraws::ofxUIBaseDraws(float w, float h, ofBaseDraws* _image, string _name) : ofxUIWidgetWithLabel()
{
    rect = new ofxUIRectangle(0,0,w,h);
    init(w, h, _image, _name);
}

ofxUIBaseDraws::ofxUIBaseDraws(float w, float h, ofBaseDraws* _image, string _name, bool _showLabel) : ofxUIWidgetWithLabel()
{
    rect = new ofxUIRectangle(0,0,w,h);
    init(w, h, _image, _name);
    showLabel = _showLabel;
}

void ofxUIBaseDraws::init(float w, float h, ofBaseDraws* _image, string _name)
{
    name = _name;
    kind = OFX_UI_WIDGET_BASE_DRAWS;
    showLabel = true;
    paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding);
    paddedRect->setParent(rect);
    
    draw_back = false;
    draw_fill = true;
    
    image = _image;
    
    label = new ofxUILabel(0,h+padding,(name+" LABEL"),name, OFX_UI_FONT_SMALL);
    label->setParent(label);
    label->setRectParent(rect);
    label->setEmbedded(true);
}

void ofxUIBaseDraws::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

void ofxUIBaseDraws::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

void ofxUIBaseDraws::drawFill()
{
    if(draw_fill)
    {
        if(image != NULL)
        {
            ofFill();
            ofSetColor(255);
            image->draw(rect->getX(), rect->getY(), rect->width, rect->height);
        }
    }
}

void ofxUIBaseDraws::setVisible(bool _visible)
{
    visible = _visible;
    label->setVisible(showLabel);
}

ofxUILabel *ofxUIBaseDraws::getLabel()
{
    return label;
}

void ofxUIBaseDraws::set(ofBaseDraws *_image)
{
    image = _image;
}

void ofxUIBaseDraws::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    if(showLabel)
    {
        paddedRect->height += label->getPaddingRect()->height;
    }
    else
    {
        paddedRect->height += padding;
    }
    label->setVisible(showLabel);
}

bool ofxUIBaseDraws::isDraggable()
{
    return false;
}