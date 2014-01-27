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

#include "ofxUIImage.h"
#include "ofxUI.h"

ofxUIImage::ofxUIImage(float x, float y, float w, float h, ofImage *_image, string _name) : ofxUIWidgetWithLabel()
{
    rect = new ofxUIRectangle(x,y,w,h);
    init(w, h, _image, _name);
}

ofxUIImage::ofxUIImage(float x, float y, float w, float h, ofImage *_image, string _name, bool _showLabel) : ofxUIWidgetWithLabel()
{
    rect = new ofxUIRectangle(x,y,w,h);
    init(w, h, _image, _name);
    showLabel = _showLabel;
}

ofxUIImage::ofxUIImage(float w, float h, ofImage *_image, string _name) : ofxUIWidgetWithLabel()
{
    rect = new ofxUIRectangle(0,0,w,h);
    init(w, h, _image, _name);
}

ofxUIImage::ofxUIImage(float w, float h, ofImage *_image, string _name, bool _showLabel) : ofxUIWidgetWithLabel()
{
    rect = new ofxUIRectangle(0,0,w,h);
    init(w, h, _image, _name);
    showLabel = _showLabel;
}

void ofxUIImage::init(float w, float h, ofImage *_image, string _name)
{
    name = string(_name);
    kind = OFX_UI_WIDGET_IMAGE;
    showLabel = true;
    paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding);
    paddedRect->setParent(rect);
    
    draw_back = false;
    draw_fill = true;
    
    image = _image;
    
    label = new ofxUILabel(0,h+padding*2.0,(name+" LABEL"),name, OFX_UI_FONT_SMALL);
    addEmbeddedWidget(label);
    cropImageToFitRect = false;
}

void ofxUIImage::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

void ofxUIImage::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

void ofxUIImage::drawFill()
{
    if(draw_fill)
    {
        if(image != NULL)
        {
            ofxUIFill();
            ofxUISetColor(255);
            if(cropImageToFitRect)
            {
                image->drawSubsection(rect->getX(), rect->getY(), rect->width, rect->height, 0, 0, rect->width, rect->height);
            }
            else
            {
                image->draw(rect->getX(), rect->getY(), rect->width, rect->height);
            }
        }
    }
}

void ofxUIImage::setVisible(bool _visible)
{
    visible = _visible;
    label->setVisible(showLabel && _visible);
    calculatePaddingRect(); 
}

void ofxUIImage::setCropImageToFitRect(bool _cropImageToFitRect)
{
    cropImageToFitRect = _cropImageToFitRect;
}

ofxUILabel *ofxUIImage::getLabel()
{
    return label;
}

void ofxUIImage::setImage(ofImage *_image)
{
    image = _image;
}

void ofxUIImage::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    label->setVisible(showLabel);
    calculatePaddingRect();
}

bool ofxUIImage::isDraggable()
{
    return false;
}