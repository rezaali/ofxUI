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

#include "ofxUI.h"
#include "ofxUIWidget.h"

ofxUIWidget::ofxUIWidget()
{
    parent = NULL;
    rect = NULL;
    paddedRect = NULL; 
    name = string("base");
    ID = -1;
    hit = false;
    visible = true;
#ifdef OFX_UI_TARGET_TOUCH
    touchId = -1;
#endif
    state = OFX_UI_STATE_NORMAL;
    draw_back = true;
    draw_outline = false;
    draw_fill = false;
    draw_fill_highlight = false;
    draw_outline_highlight = false;
    
    padding = OFX_UI_GLOBAL_PADDING;
    draw_padded_rect = OFX_UI_DRAW_PADDING;
    draw_padded_rect_outline = OFX_UI_DRAW_PADDING_OUTLINE;
    
    color_back = OFX_UI_COLOR_BACK;								//the rect's back color
    color_outline = OFX_UI_COLOR_OUTLINE;						//the rect's outline color
    color_outline_highlight = OFX_UI_COLOR_OUTLINE_HIGHLIGHT;   //the rect's onMouseOver outline highlight color
    color_fill = OFX_UI_COLOR_FILL;								//the rect's fill color
    color_fill_highlight = OFX_UI_COLOR_FILL_HIGHLIGHT;         //the rect's onMouseDown highlight color
    
    color_padded_rect = OFX_UI_COLOR_PADDED;
    color_padded_rect_outline = OFX_UI_COLOR_PADDED_OUTLINE;
    
    embedded = false;
    modal = false;
    setTriggerType(OFX_UI_TRIGGER_ALL);
}

ofxUIWidget::~ofxUIWidget()
{
    if(rect != NULL)
    {
        delete rect;
    }
    if(paddedRect != NULL)
    {
        delete paddedRect;
    }
}

// Mitchell Nordine - custom copy constructor for heap allocation handling.
ofxUIWidget::ofxUIWidget(const ofxUIWidget &other)
: name(other.name),
kind(other.kind),
visible(other.visible),
ID(other.ID),
hit(other.hit),
state(other.state),
embedded(other.embedded),
modal(other.modal),
draw_back(other.draw_back),
draw_outline(other.draw_outline),
draw_outline_highlight(other.draw_outline_highlight),
draw_fill(other.draw_fill),
draw_fill_highlight(other.draw_fill_highlight),
color_back(other.color_back),
color_outline(other.color_outline),
color_outline_highlight(other.color_outline_highlight),
color_fill(other.color_fill),
color_fill_highlight(other.color_fill_highlight),
padding(other.padding),
draw_padded_rect(other.draw_padded_rect),
draw_padded_rect_outline(other.draw_padded_rect_outline)
{
    parent = other.parent;
    if (other.rect) {
        rect = new ofxUIRectangle(*other.rect);
    }
    else {
        rect = NULL;
    }
    if (other.paddedRect) {
        paddedRect = new ofxUIRectangle(*other.paddedRect);
        paddedRect->setParent(rect);
        calculatePaddingRect();
    }
    else {
        paddedRect = NULL;
    }
}

// Mitchell Nordine - custom assignment operator for heap allocation handling.
ofxUIWidget& ofxUIWidget::operator=(const ofxUIWidget &other)
{
    name = other.name;
    kind = other.kind;
    visible = other.visible;
    ID = other.ID;
    hit = other.hit;
    state = other.state;
    embedded = other.embedded;
    modal = other.modal;
    draw_back = other.draw_back;
    draw_outline = other.draw_outline;
    draw_outline_highlight = other.draw_outline_highlight;
    draw_fill = other.draw_fill;
    draw_fill_highlight = other.draw_fill_highlight;
    color_back = other.color_back;
    color_outline = other.color_outline;
    color_outline_highlight = other.color_outline_highlight;
    color_fill = other.color_fill;
    color_fill_highlight = other.color_fill_highlight;
    padding = other.padding;
    draw_padded_rect = other.draw_padded_rect;
    draw_padded_rect_outline = other.draw_padded_rect_outline;
    parent = other.parent;
    if (other.rect) {
        rect = new ofxUIRectangle(*other.rect);
    }
    else {
        rect = NULL;
    }
    if (other.paddedRect) {
        paddedRect = new ofxUIRectangle(*other.paddedRect);
        paddedRect->setParent(rect);
        calculatePaddingRect();
    }
    else {
        paddedRect = NULL;
    }
    return *this;
}

void ofxUIWidget::initRect(float x, float y, float w, float h)
{
    if(rect != NULL)
    {
        delete rect;
    }
    rect = new ofxUIRectangle(x,y,w,h);
    initPaddingRect();
}

void ofxUIWidget::initPaddingRect()
{
    if(paddedRect != NULL)
    {
        delete paddedRect;
    }
    paddedRect = new ofxUIRectangle(-padding, -padding, rect->getWidth()+padding*2.0, rect->getHeight()+padding*2.0);
    paddedRect->setParent(rect);
    calculatePaddingRect();
}

void ofxUIWidget::calculatePaddingRect()
{
    float xMax = rect->getWidth();
    float yMax = rect->getHeight();
    
    for(vector<ofxUIWidget *>::iterator it = embeddedWidgets.begin(); it != embeddedWidgets.end(); ++it)
    {
        if((*it)->isVisible())
        {
            ofxUIRectangle *r = (*it)->getRect();
            r->getMaxX() > xMax ? (xMax = r->getMaxX()) : NULL;
            r->getMaxY() > yMax ? (yMax = r->getMaxY()) : NULL;
        }
    }
    paddedRect->set(-padding, -padding, xMax+padding*2.0, yMax+padding*2.0);
}

void ofxUIWidget::update()
{

}

void ofxUIWidget::draw()
{
    ofxUIPushStyle();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    drawPadded();
    drawPaddedOutline();
    
    drawBack();
    
    drawOutline();
    drawOutlineHighlight();
    
    drawFill();
    drawFillHighlight();
    
    ofxUIPopStyle();
}

void ofxUIWidget::drawBack()
{
    if(draw_back)
    {
        ofxUIFill();
        ofxUISetColor(color_back);
        rect->draw();
    }
}

void ofxUIWidget::drawOutline()
{
    if(draw_outline)
    {
        ofxUINoFill();
        ofxUISetColor(color_outline);
        rect->draw();
    }
}

void ofxUIWidget::drawOutlineHighlight()
{
    if(draw_outline_highlight)
    {
        ofxUINoFill();
        ofxUISetColor(color_outline_highlight);
        rect->draw();
    }
}

void ofxUIWidget::drawFill()
{
    if(draw_fill)
    {
        ofxUIFill();
        ofxUISetColor(color_fill);
        rect->draw();
    }
}

void ofxUIWidget::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ofxUIFill();
        ofxUISetColor(color_fill_highlight);
        rect->draw();
    }
}

void ofxUIWidget::drawPadded()
{
    if(draw_padded_rect && !embedded)
    {
        ofxUIFill();
        ofxUISetColor(color_padded_rect);
        paddedRect->draw();
    }
}

void ofxUIWidget::drawPaddedOutline()
{
    if(draw_padded_rect_outline && !embedded)
    {
        ofxUINoFill();
        ofxUISetColor(color_padded_rect_outline);
        paddedRect->draw();
    }
}

#ifdef OFX_UI_TARGET_TOUCH          //iOS Mode
void ofxUIWidget::touchDown(float x, float y, int id)
{
    if(touchId == -1)
    {
        this->mousePressed(x, y, 0);
        if(hit)
        {
            touchId = id;
        }
    }
}

void ofxUIWidget::touchMoved(float x, float y, int id)
{
    if(touchId == id)
    {
        this->mouseDragged(x, y, 0);
    }
}

void ofxUIWidget::touchUp(float x, float y, int id)
{
    if(touchId == id)
    {
        this->mouseReleased(x, y, 0);
        touchId = -1;
    }
}

void ofxUIWidget::touchCancelled(float x, float y, int id)
{
    if(touchId == id)
    {
        this->mouseReleased(x, y, 0);
        touchId = -1;
    }
}
#endif

void ofxUIWidget::setTriggerType(ofxUITriggerType _triggerType)
{
    triggerType = _triggerType;
}

ofxUITriggerType ofxUIWidget::getTriggerType()
{
    return triggerType;
}

void ofxUIWidget::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
}

void ofxUIWidget::setRectParent(ofxUIRectangle *_prect)
{
    rect->setParent(_prect);
}

ofxUIWidget *ofxUIWidget::getParent()
{
    return parent;
}

ofxUIRectangle* ofxUIWidget::getRect()
{
    return rect;
}

void ofxUIWidget::setName(string _name)
{
    name = string(_name);
}

void ofxUIWidget::setState(int _state)
{
    state = _state;
}
//--------------------------------------------------------------------------------
void ofxUIWidget::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
}

void ofxUIWidget::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
}

void ofxUIWidget::setDrawBack(bool _draw_back)
{
    draw_back = _draw_back;
}

void ofxUIWidget::setDrawOutline(bool _draw_outline)
{
    draw_outline = _draw_outline;
}

void ofxUIWidget::setDrawFill(bool _draw_fill)
{
    draw_fill = _draw_fill;
}

void ofxUIWidget::setDrawFillHighLight(bool _draw_fill_highlight)
{
    draw_fill_highlight = _draw_fill_highlight;
}

void ofxUIWidget::setDrawOutlineHighLight(bool _draw_outline_hightlight)
{
    draw_outline_highlight = _draw_outline_hightlight;
}
//--------------------------------------------------------------------------------
bool ofxUIWidget::getDrawPadding()
{
    return draw_padded_rect;
}

bool ofxUIWidget::getDrawPaddingOutline()
{
    return draw_padded_rect_outline;
}

bool ofxUIWidget::getDrawBack()
{
    return draw_back;
}

bool ofxUIWidget::getDrawOutline()
{
    return draw_outline;
}

bool ofxUIWidget::getDrawFill()
{
    return draw_fill;
}

bool ofxUIWidget::getDrawFillHighLight()
{
    return draw_fill_highlight;
}

bool ofxUIWidget::getDrawOutlineHighLight()
{
    return draw_outline_highlight;
}

void ofxUIWidget::setColorBack(ofxUIColor _color_back)
{
    color_back = _color_back;
}

void ofxUIWidget::setColorOutline(ofxUIColor _color_outline)
{
    color_outline = _color_outline;
}

void ofxUIWidget::setColorOutlineHighlight(ofxUIColor _color_outline_highlight)
{
    color_outline_highlight = _color_outline_highlight;
}

void ofxUIWidget::setColorFill(ofxUIColor _color_fill)
{
    color_fill = _color_fill;
}

void ofxUIWidget::setColorFillHighlight(ofxUIColor _color_fill_highlight)
{
    color_fill_highlight = _color_fill_highlight;
}

void ofxUIWidget::setColorPadded(ofxUIColor _color_padded_rect)
{
    color_padded_rect = _color_padded_rect;
}

void ofxUIWidget::setColorPaddedOutline(ofxUIColor _color_padded_rect_outline)
{
    color_padded_rect_outline = _color_padded_rect_outline;
}

ofxUIColor& ofxUIWidget::getColorPadded()
{
    return color_padded_rect;
}

ofxUIColor& ofxUIWidget::getColorPaddedOutline()
{
    return color_padded_rect_outline;
}

ofxUIColor& ofxUIWidget::getColorBack()
{
    return color_back;
}

ofxUIColor& ofxUIWidget::getColorOutline()
{
    return color_outline;
}

ofxUIColor& ofxUIWidget::getColorOutlineHighlight()
{
    return color_outline_highlight;
}

ofxUIColor& ofxUIWidget::getColorFill()
{
    return color_fill;
}

ofxUIColor& ofxUIWidget::getColorFillHighlight()
{
    return color_fill_highlight;
}

void ofxUIWidget::setKind(int _kind)
{
    kind = _kind;
}

int ofxUIWidget::getKind()
{
    return kind;
}

void ofxUIWidget::setFont(ofxUIFont *_font)
{
    font = _font;
}

void ofxUIWidget::setVisible(bool _visible)
{
    visible = _visible;
}

bool ofxUIWidget::isVisible()
{
    return visible;
}

void ofxUIWidget::toggleVisible()
{
    visible =! visible;
}

bool ofxUIWidget::isHit(float x, float y)
{
    if(visible)
    {
        return rect->inside(x, y);
    }
    else
    {
        return false;
    }
}

string& ofxUIWidget::getName()
{
    return name;
}

void ofxUIWidget::triggerEvent(ofxUIWidget *child)
{
    if(parent != NULL)
    {
        parent->triggerEvent(child);
    }
}

void ofxUIWidget::triggerSelf()
{
    if(parent != NULL)
    {
        parent->triggerEvent(this);
    }
}

void ofxUIWidget::setPadding(float _padding)
{
    padding = _padding;
    calculatePaddingRect();
}

float ofxUIWidget::getPadding()
{
    return padding;
}

ofxUIRectangle * ofxUIWidget::getPaddingRect()
{
    return paddedRect;
}

void ofxUIWidget::stateChange()
{
    
}

bool ofxUIWidget::isDraggable()
{
    return false;
}

bool ofxUIWidget::isEmbedded()
{
    return embedded;
}

void ofxUIWidget::setEmbedded(bool _embedded)
{
    embedded = _embedded;
}

void ofxUIWidget::setID(int _id)
{
    ID = _id;
}

int ofxUIWidget::getID()
{
    return ID;
}

//void ofxUIWidget::positionWidget(ofxUIWidget *widget)
//{
//    widget->getRect()->setX(0);
//    widget->getRect()->setY(0);
//    calculatePaddingRect();
//}
//
//void ofxUIWidget::positionWidgetDown(ofxUIWidget *widget)
//{
//    widget->getRect()->setX(0);
//    widget->getRect()->setY(rect->getHeight()+padding);
//    calculatePaddingRect();
//}
//
//void ofxUIWidget::positionWidgetUp(ofxUIWidget *widget)
//{
//    widget->getRect()->setX(0);
//    widget->getRect()->setY(-widget->getRect()->getHeight()-padding);
//    calculatePaddingRect();
//}
//
//void ofxUIWidget::positionWidgetLeft(ofxUIWidget *widget)
//{
//    widget->getRect()->setX(-widget->getRect()->getWidth()-padding);
//    widget->getRect()->setY(0);
//    calculatePaddingRect();
//}
//
//void ofxUIWidget::positionWidgetRight(ofxUIWidget *widget)
//{
//    widget->getRect()->setX(rect->getWidth()+padding);
//    widget->getRect()->setY(0);
//    calculatePaddingRect();
//}

void ofxUIWidget::addWidget(ofxUIWidget *widget)
{

}

void ofxUIWidget::removeWidget(ofxUIWidget *widget)
{
    
}

bool ofxUIWidget::hasLabel()
{
    return false;
}

bool ofxUIWidget::isModal()
{
    return modal;
}

void ofxUIWidget::setModal(bool _modal)      //allows for piping mouse/touch input to widgets that are outside of parent's rect/canvas
{
    modal = _modal;
    if(parent != NULL)
    {
        if(modal)
        {
            parent->addModalWidget(this);
        }
        else
        {
            parent->removeModalWidget(this);
        }
    }
}

void ofxUIWidget::addModalWidget(ofxUIWidget *widget)
{
    if(parent != NULL)
    {
        parent->addModalWidget(widget);
    }
}

void ofxUIWidget::removeModalWidget(ofxUIWidget *widget)
{
    if(parent != NULL)
    {
        parent->removeModalWidget(widget);
    }
}

void ofxUIWidget::addEmbeddedWidget(ofxUIWidget *widget)
{
    widget->setEmbedded(true);
    embeddedWidgets.push_back(widget);
}

int ofxUIWidget::getEmbeddedWidgetsSize()
{
    return embeddedWidgets.size();
}

ofxUIWidget *ofxUIWidget::getEmbeddedWidget(int index)
{
    return embeddedWidgets[index%embeddedWidgets.size()];
}

void ofxUIWidget::clearEmbeddedWidgets()
{
    embeddedWidgets.clear();        //does not deallocate widgets, just deletes the pointers and sets the size to zero
}

ofxUIWidget *ofxUIWidget::getCanvasParent()
{
    bool notFoundParentCanvas = true;
    ofxUIWidget *parent = this->getParent();
    
    while (notFoundParentCanvas)
    {
        int kind = parent->getKind();
        if( kind == OFX_UI_WIDGET_CANVAS || kind == OFX_UI_WIDGET_SCROLLABLECANVAS || kind == OFX_UI_WIDGET_SUPERCANVAS || OFX_UI_WIDGET_TABBAR)
        {
            notFoundParentCanvas = false;
            return parent;
        }
        else
        {
            parent = parent->getParent();
            if(parent == NULL)
            {
                return NULL; 
            }
        }
    }
    return NULL; 
}

bool ofxUIWidget::hasState()
{
    return false;
}

#ifndef OFX_UI_NO_XML

void ofxUIWidget::saveState(ofxXmlSettings *XML)
{
    
}

void ofxUIWidget::loadState(ofxXmlSettings *XML)
{
    
}

#endif