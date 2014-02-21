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

#include "ofxUICanvas.h"
#include "ofxUI.h"

ofxUICanvas::~ofxUICanvas()
{
    disable();
    if(GUIevent != NULL)
    {
        delete GUIevent;
    }
    if(!hasSharedResources)
    {
        if(font_large != NULL)
        {
            delete font_large;
        }
        if(font_medium != NULL)
        {
            delete font_medium;
        }
        if(font_small != NULL)
        {
            delete font_small;
        }
    }
    for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        ofxUIWidget *w = (*it);
        delete w;
    }
    widgets.clear();
}

// Copy constructor to handle heap allocation during a copy.
ofxUICanvas::ofxUICanvas(const ofxUICanvas &other)
: bInsideCanvas(other.bInsideCanvas),
state(other.state),
hasSharedResources(other.hasSharedResources),
autoDraw(other.autoDraw),
autoUpdate(other.autoUpdate),
widgets_map(other.widgets_map),
widgets(other.widgets),
widgetsAreModal(other.widgetsAreModal),
widgetsWithState(other.widgetsWithState),
lastAddeds(other.lastAddeds),
activeFocusedWidget(other.activeFocusedWidget),
enable_highlight_outline(other.enable_highlight_outline),
enable_highlight_fill(other.enable_highlight_fill),
enabled(other.enabled),
bTriggerWidgetsUponLoad(other.bTriggerWidgetsUponLoad),
uniqueIDs(other.uniqueIDs),
hasKeyBoard(other.hasKeyBoard),
widgetSpacing(other.widgetSpacing),
globalCanvasWidth(other.globalCanvasWidth),
globalSliderHeight(other.globalSliderHeight),
globalGraphHeight(other.globalGraphHeight),
globalButtonDimension(other.globalButtonDimension),
globalSpacerHeight(other.globalSpacerHeight),
fontName(other.fontName),
widgetPosition(other.widgetPosition),
widgetAlign(other.widgetAlign),
widgetFontSize(other.widgetFontSize),
widget_color_back(other.widget_color_back),
widget_color_outline(other.widget_color_outline),
widget_color_outline_highlight(other.widget_color_outline_highlight),
widget_color_fill(other.widget_color_fill),
widget_color_fill_highlight(other.widget_color_fill_highlight),
widget_color_padded_rect(other.widget_color_padded_rect),
widget_color_padded_rect_outline(other.widget_color_padded_rect_outline),
bDrawWidgetPadding(other.bDrawWidgetPadding),
bDrawWidgetPaddingOutline(other.bDrawWidgetPaddingOutline)
{
    if (other.font_large) {
        font_large = new ofxUIFont(*other.font_large);
    }
    else {
        font_large = NULL;
    }
    if (other.font_medium) {
        font_medium = new ofxUIFont(*other.font_medium);
    }
    else {
        font_medium = NULL;
    }
    if (other.font_small) {
        font_small = new ofxUIFont(*other.font_small);
    }
    else {
        font_small = NULL;
    }
    if (other.GUIevent) {
        GUIevent = new ofxUIEventArgs(*other.GUIevent);
    }
    else {
        GUIevent = NULL;
    }
}

// Assignment operator to handle heap allocation during assignment.
ofxUICanvas& ofxUICanvas::operator=(const ofxUICanvas &other)
{
    bInsideCanvas = other.bInsideCanvas;
    state = other.state;
    hasSharedResources = other.hasSharedResources;
    autoDraw = other.autoDraw;
    autoUpdate = other.autoUpdate;
    widgets_map = other.widgets_map;
    widgets = other.widgets;
    widgetsAreModal = other.widgetsAreModal;
    widgetsWithState = other.widgetsWithState;
    lastAddeds = other.lastAddeds;
    activeFocusedWidget = other.activeFocusedWidget;
    enable_highlight_outline = other.enable_highlight_outline;
    enable_highlight_fill = other.enable_highlight_fill;
    enabled = other.enabled;
    bTriggerWidgetsUponLoad = other.bTriggerWidgetsUponLoad;
    uniqueIDs = other.uniqueIDs;
    hasKeyBoard = other.hasKeyBoard;
    widgetSpacing = other.widgetSpacing;
    globalCanvasWidth = other.globalCanvasWidth;
    globalSliderHeight = other.globalSliderHeight;
    globalGraphHeight = other.globalGraphHeight;
    globalButtonDimension = other.globalButtonDimension;
    globalSpacerHeight = other.globalSpacerHeight;
    fontName = other.fontName;
    widgetPosition = other.widgetPosition;
    widgetAlign = other.widgetAlign;
    widgetFontSize = other.widgetFontSize;
    widget_color_back = other.widget_color_back;
    widget_color_outline = other.widget_color_outline;
    widget_color_outline_highlight = other.widget_color_outline_highlight;
    widget_color_fill = other.widget_color_fill;
    widget_color_fill_highlight = other.widget_color_fill_highlight;
    widget_color_padded_rect = other.widget_color_padded_rect;
    widget_color_padded_rect_outline = other.widget_color_padded_rect_outline;
    bDrawWidgetPadding = other.bDrawWidgetPadding;
    bDrawWidgetPaddingOutline = other.bDrawWidgetPaddingOutline;
    if (other.font_large) {
        font_large = new ofxUIFont(*other.font_large);
    }
    else {
        font_large = NULL;
    }
    if (other.font_medium) {
        font_medium = new ofxUIFont(*other.font_medium);
    }
    else {
        font_medium = NULL;
    }
    if (other.font_small) {
        font_small = new ofxUIFont(*other.font_small);
    }
    else {
        font_small = NULL;
    }
    if (other.GUIevent) {
        GUIevent = new ofxUIEventArgs(*other.GUIevent);
    }
    else {
        GUIevent = NULL;
    }
    return *this;
}

ofxUICanvas::ofxUICanvas(ofxUIRectangle r) : ofxUIWidget()
{
    init(r.getX(false), r.getY(false), r.width, r.height);
}

ofxUICanvas::ofxUICanvas(float x, float y, float w, float h) : ofxUIWidget()
{
    init(x, y, w, h);
}

ofxUICanvas::ofxUICanvas(float x, float y, float w, float h, ofxUICanvas *sharedResources) : ofxUIWidget()
{
    init(x, y, w, h,sharedResources);
}

ofxUICanvas::ofxUICanvas(float defaultWidthSize, float defaultHeightSize) : ofxUIWidget()
{
    init(0, 0, defaultWidthSize, defaultHeightSize);
    setGlobalCanvasWidth(defaultWidthSize);
}

ofxUICanvas::ofxUICanvas(ofxUICanvas *sharedResources, float defaultWidthSize, float defaultHeightSize) : ofxUIWidget()
{
    init(0, 0, defaultWidthSize, defaultHeightSize, sharedResources);
    setGlobalCanvasWidth(defaultWidthSize);
}

ofxUICanvas::ofxUICanvas(string title) : ofxUIWidget()
{
    init(0, 0, 46, ofxUIGetHeight());
    addWidgetDown(new ofxUILabel(title, OFX_UI_FONT_LARGE));
    addWidgetDown(new ofxUISpacer(0, 20));
    addWidgetDown(new ofxUIFPSSlider(300, 20, 0, 1000, ofGetFrameRate(), "FPS"));
}

void ofxUICanvas::init(int x, int y, int w, int h, ofxUICanvas *sharedResources)
{
    initRect(x, y, w, h);
    name = string("OFX_UI_WIDGET_CANVAS");
    kind = OFX_UI_WIDGET_CANVAS;
    
    enable_highlight_outline = false;
    enable_highlight_fill = false;
    
    bDrawWidgetPadding = false;
    bDrawWidgetPaddingOutline = false;
    
    autoDraw = true;
    autoUpdate = true;
    bTriggerWidgetsUponLoad = true;
    
    if(sharedResources != NULL)
    {
        hasSharedResources = true;
        font_large = sharedResources->getFontLarge();
        font_medium = sharedResources->getFontMedium();
        font_small = sharedResources->getFontSmall();
    }
    else
    {
        hasSharedResources = false;
        font_large = new ofxUIFont();
        font_medium = new ofxUIFont();
        font_small = new ofxUIFont();
        
        fontName = string(OFX_UI_FONT_NAME);
        setFont(fontName,true, true, false, 0.0, OFX_UI_FONT_RESOLUTION);
    }
    
    font = font_medium;
    uniqueIDs = 0;
    widgetSpacing = OFX_UI_GLOBAL_WIDGET_SPACING;
    globalCanvasWidth = OFX_UI_GLOBAL_CANVAS_WIDTH;
    globalSliderHeight = OFX_UI_GLOBAL_SLIDER_HEIGHT;
    globalGraphHeight = OFX_UI_GLOBAL_GRAPH_HEIGHT;
    globalButtonDimension = OFX_UI_GLOBAL_BUTTON_DIMENSION;
    globalSpacerHeight = OFX_UI_GLOBAL_SPACING_HEIGHT;
    
    hasKeyBoard = false;
    bInsideCanvas = false;
    
    widgetPosition = OFX_UI_WIDGET_POSITION_DOWN;
    widgetAlign = OFX_UI_ALIGN_LEFT;
    widgetFontSize = OFX_UI_FONT_SMALL;
    
    GUIevent = new ofxUIEventArgs(this);
    enabled = false;
    enable();
}

void ofxUICanvas::copyCanvasStyle(ofxUICanvas *styler)
{
    setUIColors(styler->getWidgetColorBack(),
                styler->getWidgetColorOutline(),
                styler->getWidgetColorOutlineHighlight(),
                styler->getWidgetColorFill(),
                styler->getWidgetColorFillHighlight(),
                styler->getWidgetColorPadded(),
                styler->getWidgetColorPaddedOutline());
    
    setColorBack(styler->getColorBack());
    setColorOutline(styler->getColorOutline());
    setColorOutlineHighlight(styler->getColorOutlineHighlight());
    setColorFill(styler->getColorFill());
    setColorFillHighlight(styler->getColorFillHighlight());
    setColorPadded(styler->getColorPadded());
    setColorPaddedOutline(styler->getColorPaddedOutline());
    
    setDrawBack(styler->getDrawBack());
    setDrawOutline(styler->getDrawOutline());
    setDrawOutlineHighLight(styler->getDrawOutlineHighLight());
    setDrawFill(styler->getDrawFill());
    setDrawFillHighLight(styler->getDrawFillHighLight());
    setDrawPadding(styler->getDrawPadding());
    setDrawPaddingOutline(styler->getDrawPaddingOutline());
    
    setDrawWidgetPadding(styler->getDrawWidgetPadding());
    setDrawWidgetPaddingOutline(styler->getDrawWidgetPaddingOutline());
}

void ofxUICanvas::copyCanvasProperties(ofxUICanvas *styler)
{
    setGlobalCanvasWidth(styler->getRect()->getWidth());
    setGlobalButtonDimension(styler->getGlobalButtonDimension());
    setGlobalSliderHeight(styler->getGlobalSliderHeight());
    setGlobalSpacerHeight(styler->getGlobalSpacerHeight());
    setGlobalGraphHeight(styler->getGlobalGraphHeight());
    
    setPadding(styler->getPadding());
    setWidgetSpacing(styler->getWidgetSpacing());
    
    setWidgetPosition(styler->getWidgetPosition());
    setWidgetFontSize(styler->getWidgetFontSize());
}

#ifndef OFX_UI_NO_XML

void ofxUICanvas::saveSettings(string fileName)
{
    ofxXmlSettings *XML = new ofxXmlSettings();
    for(int i = 0; i < widgetsWithState.size(); i++)
    {
        int index = XML->addTag("Widget");
        if(XML->pushTag("Widget", index))
        {
            XML->setValue("Kind", widgetsWithState[i]->getKind(), 0);
            XML->setValue("Name", widgetsWithState[i]->getName(), 0);
            widgetsWithState[i]->saveState(XML);
        }
        XML->popTag();
    }
    XML->saveFile(fileName);
    delete XML;
}

void ofxUICanvas::setTriggerWidgetsUponLoad(bool _bTriggerWidgetsUponLoad)
{
    bTriggerWidgetsUponLoad = _bTriggerWidgetsUponLoad;
}

bool ofxUICanvas::getTriggerWidgetsUponLoad()
{
    return bTriggerWidgetsUponLoad;
}

void ofxUICanvas::loadSettings(string fileName)
{
    ofxXmlSettings *XML = new ofxXmlSettings();
    XML->loadFile(fileName);
    int widgetTags = XML->getNumTags("Widget");
    for(int i = 0; i < widgetTags; i++)
    {
        XML->pushTag("Widget", i);
        string name = XML->getValue("Name", "NULL", 0);
        ofxUIWidget *widget = getWidget(name);
        if(widget != NULL && widget->hasState())
        {
            widget->loadState(XML);
            if(bTriggerWidgetsUponLoad){
                triggerEvent(widget);
            }
        }
        XML->popTag();
    }
    hasKeyBoard = false;
    delete XML;
}

#endif

ofxUIFont *ofxUICanvas::getFontLarge()
{
    return font_large;
}

ofxUIFont *ofxUICanvas::getFontMedium()
{
    return font_medium;
}

ofxUIFont *ofxUICanvas::getFontSmall()
{
    return font_small;
}

//Easy Font setting contributed from Colin Duffy (colin@tomorrowevening.com)
bool ofxUICanvas::setFont(string filename, bool _bAntiAliased, bool _bFullCharacterSet, bool makeContours, float simplifyAmt, int dpi)
{
    bool bLarge = updateFont(OFX_UI_FONT_LARGE, filename, OFX_UI_FONT_LARGE_SIZE, _bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt, dpi);
    bool bMedium = updateFont(OFX_UI_FONT_MEDIUM, filename, OFX_UI_FONT_MEDIUM_SIZE, _bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt, dpi);
    bool bSmall = updateFont(OFX_UI_FONT_SMALL, filename, OFX_UI_FONT_SMALL_SIZE, _bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt, dpi);
    bool successful = bLarge && bMedium && bSmall;
    if( successful ) fontName = filename;
    return successful;
}

void ofxUICanvas::setFontSize(ofxUIWidgetFontType _kind, int _size, int _resolution)
{
    switch(_kind)
    {
        case OFX_UI_FONT_LARGE:
            if(font_large != NULL)
            {
                delete font_large;
            }
            font_large = new ofxUIFont();
            font_large->loadFont(fontName,_size,true, true, false, 0.0,_resolution);
            break;
            
        case OFX_UI_FONT_MEDIUM:
            if(font_medium != NULL)
            {
                delete font_medium;
            }
            font_medium = new ofxUIFont();
            font_medium->loadFont(fontName,_size,true, true, false, 0.0,_resolution);
            break;
            
        case OFX_UI_FONT_SMALL:
            if(font_small != NULL)
            {
                delete font_small;
            }
            font_small = new ofxUIFont();
            font_small->loadFont(fontName,_size,true, true, false, 0.0,_resolution);
            break;
    }
}

void ofxUICanvas::setWidgetSpacing(float _widgetSpacing)
{
    widgetSpacing = _widgetSpacing;
}

float ofxUICanvas::getWidgetSpacing()
{
    return widgetSpacing;
}

bool ofxUICanvas::isEnabled()
{
    return enabled;
}

void ofxUICanvas::setVisible(bool _visible)
{
    visible = _visible;
    if(visible)
    {
        enable();
    }
    else
    {
        disable();
    }
}


void ofxUICanvas::toggleVisible()
{
    if(isEnabled())
    {
        disable();
    }
    else {
        enable();
    }
}

bool ofxUICanvas::hasKeyboardFocus()
{
    return hasKeyBoard;
}

void ofxUICanvas::enable()
{
    if(!isEnabled())
    {
        enabled = true;
        visible = true;
        EnableCallbacks();
    }
}

void ofxUICanvas::disable()
{
    if(isEnabled())
    {
        enabled = false;
        visible = false;
        DisableCallbacks();
    }
}

void ofxUICanvas::update()
{
    if (!isVisible()) { return; } // Custom to save framerate
    for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        (*it)->update();
    }
}

void ofxUICanvas::draw()
{
    ofxUIPushStyle();
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    
    glEnable(GL_BLEND);
#ifndef OFX_UI_TARGET_TOUCH
    glBlendEquation(GL_FUNC_ADD);
#endif
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    ofxUISetRectMode(OFX_UI_RECTMODE_CORNER);
    ofxUISetLineWidth(1.0);
    
    drawPadded();
    
    drawPaddedOutline();
    
    drawBack();
    
    drawFill();
    
    drawFillHighlight();
    
    drawOutline();
    
    drawOutlineHighlight();
    
    for(vector<ofxUIWidget *>::reverse_iterator it = widgets.rbegin(); it != widgets.rend(); ++it)
    {
        if((*it)->isVisible() && ((*it)->getRect()->rInside(*rect) || (*it)->isModal()))
        {
            (*it)->draw();
        }
    }
    ofxUIPopStyle();
}

void ofxUICanvas::exit()
{
    
}

#ifdef OFX_UI_TARGET_TOUCH

void ofxUICanvas::canvasTouchDown(float x, float y, int id)
{
    if(rect->inside(x, y))
    {
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible())	(*it)->touchDown(x, y, id);
        }
    }
    else
    {
        for (map<string, ofxUIWidget*>::iterator it=widgetsAreModal.begin() ; it != widgetsAreModal.end(); it++ )
        {
            if((*it).second->isVisible()) (*it).second->touchDown(x, y, id);
        }
    }
}

void ofxUICanvas::canvasTouchMoved(float x, float y, int id)
{
    for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        if((*it)->isVisible())	(*it)->touchMoved(x, y, id);
    }
}

void ofxUICanvas::canvasTouchUp(float x, float y, int id)
{
    for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        if((*it)->isVisible())	(*it)->touchUp(x, y, id);
    }
}

void ofxUICanvas::canvasTouchDoubleTap(float x, float y, int id)
{
    if(rect->inside(x, y))
    {
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible())	(*it)->touchDoubleTap(x, y, id);
        }
    }
    else
    {
        for (map<string, ofxUIWidget*>::iterator it=widgetsAreModal.begin() ; it != widgetsAreModal.end(); it++ )
        {
            if((*it).second->isVisible()) (*it).second->touchDoubleTap(x, y, id);
        }
    }
}

void ofxUICanvas::canvasTouchCancelled(float x, float y, int id)
{
    if(rect->inside(x, y))
    {
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible())	(*it)->touchCancelled(x, y, id);
        }
    }
    else
    {
        for (map<string, ofxUIWidget*>::iterator it=widgetsAreModal.begin() ; it != widgetsAreModal.end(); it++ )
        {
            if((*it).second->isVisible()) (*it).second->touchCancelled(x, y, id);
        }
    }
}

void ofxUICanvas::touchDown(float x, float y, int id)
{
    canvasTouchDown(x, y, id);
}

void ofxUICanvas::touchMoved(float x, float y, int id)
{
    canvasTouchMoved(x, y, id);
}

void ofxUICanvas::touchUp(float x, float y, int id)
{
    canvasTouchUp(x, y, id);
}

void ofxUICanvas::touchDoubleTap(float x, float y, int id)
{
    canvasTouchDoubleTap(x, y, id);
}

void ofxUICanvas::touchCancelled(float x, float y, int id)
{
    canvasTouchCancelled(x, y, id);
}

#else

void ofxUICanvas::mouseMoved(int x, int y )
{
    if(rect->inside(x, y))
    {
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible()) (*it)->mouseMoved(x, y);
        }
        bInsideCanvas = true;
    }
    else
    {
        bInsideCanvas = false;
        for (map<string, ofxUIWidget*>::iterator it=widgetsAreModal.begin() ; it != widgetsAreModal.end(); it++ )
        {
            if((*it).second->isVisible()) (*it).second->mouseMoved(x, y);
        }
    }
}

void ofxUICanvas::mouseDragged(int x, int y, int button)
{
    for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        if((*it)->isVisible())	(*it)->mouseDragged(x, y, button);
    }
}

void ofxUICanvas::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isVisible()) (*it)->mousePressed(x, y, button);
        }
    }
    else
    {
        for (map<string, ofxUIWidget*>::iterator it=widgetsAreModal.begin() ; it != widgetsAreModal.end(); it++ )
        {
            if((*it).second->isVisible()) (*it).second->mousePressed(x, y, button);
        }
    }
}

void ofxUICanvas::mouseReleased(int x, int y, int button)
{
    for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        if((*it)->isVisible()) (*it)->mouseReleased(x, y, button);
    }
}

void ofxUICanvas::windowResized(int w, int h)
{
    for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        (*it)->windowResized(w, h);
    }
}

#endif

void ofxUICanvas::keyPressed(int key)
{
    if(bInsideCanvas)
    {
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            (*it)->keyPressed(key);
        }
    }
}

void ofxUICanvas::keyReleased(int key)
{
    if(bInsideCanvas)
    {
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            (*it)->keyReleased(key);
        }
    }
}

bool ofxUICanvas::isHit(int x, int y)
{
    if(isEnabled() && rect->inside(x, y))
    {
        return true;
    }
    else
    {
        for (map<string, ofxUIWidget*>::iterator it=widgetsAreModal.begin() ; it != widgetsAreModal.end(); it++ )
        {
            if((*it).second->isVisible() && (*it).second->isHit(x, y))
            {
                return true;
            }
        }
    }
    return false;
}

ofxUIWidget *ofxUICanvas::getWidgetHit(float x, float y)
{
    if(isEnabled() && rect->inside(x, y))
    {
        for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
        {
            if((*it)->isHit(x, y))
            {
                return (*it);
            }
        }
        return NULL;
    }
    else
    {
        return NULL;
    }
}


void ofxUICanvas::stateChange()
{
    switch (state)
    {
        case OFX_UI_STATE_NORMAL:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
        }
            break;
        case OFX_UI_STATE_OVER:
        {
            draw_fill_highlight = false;
            if(enable_highlight_outline)
            {
                draw_outline_highlight = true;
            }
        }
            break;
        case OFX_UI_STATE_DOWN:
        {
            if(enable_highlight_fill)
            {
                draw_fill_highlight = true;
            }
            draw_outline_highlight = false;
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

void ofxUICanvas::autoSizeToFitWidgets()
{
    float maxWidth = 0;
    float maxHeight = 0;
    
    for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        if((*it)->isVisible())
        {
            ofxUIRectangle* wr = (*it)->getRect();
            ofxUIRectangle* wrp = (*it)->getPaddingRect();
            float widgetwidth = wr->getX()+wrp->getWidth() - rect->getX();
            float widgetheight = wr->getY()+wrp->getHeight() - rect->getY();
            
            float widgetpaddingwidth = wrp->getX()+wrp->getWidth() - rect->getX();
            float widgetpaddingheight = wrp->getY()+wrp->getHeight() - rect->getY();
            
            
            if(widgetwidth > maxWidth)
            {
                maxWidth = widgetwidth;
            }
            else if(widgetpaddingwidth > maxWidth)
            {
                maxWidth = widgetpaddingwidth;
            }
            
            if(widgetheight > maxHeight)
            {
                maxHeight = widgetheight;
            }
            else if(widgetpaddingheight > maxHeight)
            {
                maxHeight = widgetpaddingheight;
            }
        }
    }
    setDimensions(maxWidth, maxHeight);
}

void ofxUICanvas::centerWidgetsOnCanvas(bool centerHorizontally, bool centerVertically)
{
    float xMin = 0;
    float yMin = 0;
    
    float xMax = 0;
    float yMax = 0;
    
    float w = 0;
    float h = 0;
    
    for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        //            if((*it)->isVisible())
        //            {
        ofxUIRectangle* wr = (*it)->getRect();
        if(wr->x < xMin)
        {
            xMin = wr->x;
        }
        if((wr->x + wr->getWidth()) > xMax)
        {
            xMax = (wr->x + wr->getWidth());
        }
        
        if(wr->y < yMin)
        {
            yMin = wr->y;
        }
        if((wr->y + wr->getHeight()) > yMax)
        {
            yMax = (wr->y + wr->getHeight());
        }
        //            }
    }
    
    w = xMax - xMin;
    h = yMax - yMin;
    
    float moveDeltaX = rect->getHalfWidth() - w*.5;
    float moveDeltaY = rect->getHalfHeight() - h*.5;
    
    for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        if((*it)->isVisible() && !((*it)->isEmbedded()))
        {
            ofxUIRectangle* wr = (*it)->getRect();
            if(centerHorizontally) wr->x += moveDeltaX-padding;
            if(centerVertically) wr->y += moveDeltaY-padding;
        }
    }
}

void ofxUICanvas::centerWidgetsHorizontallyOnCanvas()
{
    centerWidgetsOnCanvas(true, false);
}

void ofxUICanvas::centerWidgetsVerticallyOnCanvas()
{
    centerWidgetsOnCanvas(false, true);
}

void ofxUICanvas::centerWidgets()
{
    centerWidgetsOnCanvas(true, true);
}

void ofxUICanvas::addModalWidget(ofxUIWidget *widget)
{
    widgetsAreModal[widget->getName()] = widget;
}

void ofxUICanvas::removeModalWidget(ofxUIWidget *widget)
{
    map<string, ofxUIWidget*>::iterator it;
    it=widgetsAreModal.find(widget->getName());
    if(it != widgetsAreModal.end())
    {
        widgetsAreModal.erase(it);
    }
}

void ofxUICanvas::removeWidgets()
{
    for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        ofxUIWidget *w = (*it);
        delete w;
    }
    clearWidgets();
    resetPlacer();
}

// To be called before destructor if "widgets" are pointing to stack-based widgets.
void ofxUICanvas::clearWidgets()
{
    widgets.clear();
    widgets_map.clear();
    widgetsAreModal.clear();
    widgetsWithState.clear();
    lastAddeds.clear();
    activeFocusedWidget = NULL;
}

void ofxUICanvas::removeWidget(ofxUIWidget *widget)
{
    //        cout << endl;
    //        cout << "Widget to find: " << widget->getName() << endl;
    //        cout << endl;
    
    if(widget->isModal())
    {
        map<string, ofxUIWidget*>::iterator it;
        it=widgetsAreModal.find(widget->getName());
        
        if(it != widgetsAreModal.end())
        {
            widgetsAreModal.erase(it);
        }
    }
    
    //for the map
    multimap<string, ofxUIWidget*>::iterator it;
    it=widgets_map.find(widget->getName());
    if(it != widgets_map.end())
    {
        //            cout << "FOUND IT IN MAP, DELETING" << endl;
        widgets_map.erase(it);
    }
    
    //for the widgets with state
    for(unsigned int i = 0; i < widgetsWithState.size(); i++)
    {
        ofxUIWidget *other = widgetsWithState[i];
        if(widget->getName() == other->getName())
        {
            //                cout << "FOUND IT IN WIDGETS WITH STATE, DELETING" << endl;
            widgetsWithState.erase(widgetsWithState.begin()+i);
            break;
        }
    }
    vector<ofxUIWidget *>::iterator wit;
    //for all the widgets
    for(wit=widgets.begin(); wit != widgets.end(); wit++)
    {
        ofxUIWidget *other = *wit;
        //            cout << other->getName() << endl;
        if(widget->getName() == other->getName())
        {
            //                cout << "FOUND IT\t" << other->getName() << " " << widget->getName() << endl;
            widgets.erase(wit);
            break;
        }
    }
    
    if(widget->hasLabel())
    {
        //            cout << "HAS LABEL" << endl;
        ofxUIWidgetWithLabel *wwl = (ofxUIWidgetWithLabel *) widget;
        ofxUILabel *label = wwl->getLabelWidget();
        removeWidget(label);
    }
    
    for(int i = 0; i < widget->getEmbeddedWidgetsSize(); i++)
    {
        removeWidget(widget->getEmbeddedWidget(i));
    }
    widget->clearEmbeddedWidgets();
    
    //	remove widget from lastAdded stack
    lastAddeds.erase( std::remove( lastAddeds.begin(), lastAddeds.end(), widget ), lastAddeds.end() );
    
    delete widget;
}

void ofxUICanvas::addWidget(ofxUIWidget *widget)
{
    if(widget->hasState())
    {
       widgetsWithState.push_back(widget);
    }
    widget->setPadding(padding);
    
    for(int i = 0; i < widget->getEmbeddedWidgetsSize(); i++)
    {
        ofxUIWidget *child = widget->getEmbeddedWidget(i);
        this->addWidget(child);
        child->setParent(widget);
        child->setRectParent(widget->getRect());
    }
    
    if(widget->getKind() == OFX_UI_WIDGET_LABEL)
    {
        ofxUILabel *label = (ofxUILabel *) widget;
        setLabelFont(label);
        setWidgetColor(label);
    }
    
    setWidgetDrawingProperties(widget);
    setWidgetColor(widget);
    widget->setParent(this);
    widget->setRectParent(this->rect);
    pushbackWidget(widget);
}

ofxUIWidget* ofxUICanvas::addWidgetPosition(ofxUIWidget *widget, ofxUIWidgetPosition position, ofxUIWidgetAlignment align, bool reAdd)
{
    if(!reAdd) addWidget(widget);
    ofxUIRectangle *widgetRect = widget->getRect();
    ofxUIWidget* lastAdded = lastAddeds.empty() ? NULL : lastAddeds.back();
    if(lastAdded != NULL)
    {
        ofxUIRectangle *lastPaddedRect = lastAdded->getPaddingRect();
        switch(position)
        {
            case OFX_UI_WIDGET_POSITION_DOWN:
                widgetRect->y = lastPaddedRect->getY()+lastPaddedRect->getHeight()-rect->getY()+widgetSpacing;
                break;
            case OFX_UI_WIDGET_POSITION_UP:
            {
                ofxUIRectangle *widgetPaddedRect = widget->getPaddingRect();
                widgetRect->y = lastPaddedRect->getY()-widgetPaddedRect->getHeight()-rect->getY();
                break;
            }
            case OFX_UI_WIDGET_POSITION_RIGHT:
            {
                ofxUIRectangle *lastRect = lastAdded->getRect();
                widgetRect->x = lastPaddedRect->getX()+lastPaddedRect->getWidth()-rect->getX()+widgetSpacing;
                
                widgetRect->y = lastRect->getY()-rect->getY();
                break;
            }
            case OFX_UI_WIDGET_POSITION_LEFT:
                ofxUIRectangle *lastRect = lastAdded->getRect();
                ofxUIRectangle *widgetPaddedRect = widget->getPaddingRect();
                widgetRect->x = lastPaddedRect->getX()-widgetPaddedRect->getWidth()-rect->getX();
                widgetRect->y = lastRect->getY()-rect->getY();
                break;
        }
    }
    else
    {
        widgetRect->y = widgetSpacing;
        if (position == OFX_UI_WIDGET_POSITION_LEFT ||
            position == OFX_UI_WIDGET_POSITION_RIGHT)
        {
            widgetRect->x = widgetSpacing;
        }
        
    }
    switch(align)
    {
        case OFX_UI_ALIGN_LEFT:
            widgetRect->x = widgetSpacing;
            break;
        case OFX_UI_ALIGN_FREE:
            
            break;
        case OFX_UI_ALIGN_CENTER:   //Experimental
            
            break;
        case OFX_UI_ALIGN_RIGHT:
            widgetRect->x = rect->getWidth()-widgetRect->getWidth()-widgetSpacing;
            break;
        case OFX_UI_ALIGN_TOP:
            widgetRect->y = widgetSpacing;
            break;
        case OFX_UI_ALIGN_BOTTOM:
            widgetRect->y = rect->getHeight()-widgetRect->getHeight()-widgetSpacing;
            break;
    }
    if(widget->getRect()->getHeight() != 0 || widget->getRect()->getWidth() != 0)
    {
        lastAddeds.push_back( widget );
    }
    return widget;
}

ofxUIWidget* ofxUICanvas::addWidgetDown(ofxUIWidget *widget, ofxUIWidgetAlignment align, bool reAdd)
{
    return addWidgetPosition(widget, OFX_UI_WIDGET_POSITION_DOWN, align, reAdd);
}

ofxUIWidget* ofxUICanvas::addWidgetUp(ofxUIWidget *widget, ofxUIWidgetAlignment align, bool reAdd)
{
    return addWidgetPosition(widget, OFX_UI_WIDGET_POSITION_UP, align, reAdd);
}

ofxUIWidget* ofxUICanvas::addWidgetRight(ofxUIWidget *widget, ofxUIWidgetAlignment align, bool reAdd)
{
    return addWidgetPosition(widget, OFX_UI_WIDGET_POSITION_RIGHT, align, reAdd);
}

ofxUIWidget* ofxUICanvas::addWidgetLeft(ofxUIWidget *widget, ofxUIWidgetAlignment align, bool reAdd)
{
    return addWidgetPosition(widget, OFX_UI_WIDGET_POSITION_LEFT, align, reAdd);
}

ofxUIWidget* ofxUICanvas::addWidgetSouthOf(ofxUIWidget *widget, string referenceName, bool reAdd)
{
    if(!reAdd) addWidget(widget);
    ofxUIWidget *referenceWidget = getWidget(referenceName);
    if(referenceWidget != NULL)
    {
        ofxUIRectangle *referencePaddedRect = referenceWidget->getPaddingRect();
        ofxUIRectangle *referenceRect = referenceWidget->getRect();
        ofxUIRectangle *widgetRect = widget->getRect();
        
        widgetRect->y = referencePaddedRect->getY()+referencePaddedRect->getHeight()-rect->getY()+widgetSpacing;
        widgetRect->x = referenceRect->getX()-rect->getX();
    }
    else
    {
        ofxUIRectangle *widgetRect = widget->getRect();
        widgetRect->y = widgetSpacing;
    }
    lastAddeds.push_back( widget );
    return widget;
}

ofxUIWidget* ofxUICanvas::addWidgetNorthOf(ofxUIWidget *widget, string referenceName, bool reAdd)
{
    if(!reAdd) addWidget(widget);
    ofxUIWidget *referenceWidget = getWidget(referenceName);
    if(referenceWidget != NULL)
    {
        ofxUIRectangle *referencePaddedRect = referenceWidget->getPaddingRect();
        ofxUIRectangle *referenceRect = referenceWidget->getRect();
        ofxUIRectangle *widgetRect = widget->getRect();
        ofxUIRectangle *widgetPaddedRect = widget->getPaddingRect();
        
        widgetRect->y = referencePaddedRect->getY()-widgetPaddedRect->getHeight()-rect->getY();
        widgetRect->x = referenceRect->getX()-rect->getX();
    }
    else
    {
        ofxUIRectangle *widgetRect = widget->getRect();
        widgetRect->y = widgetSpacing;
    }
    lastAddeds.push_back( widget );
    return widget;
}

ofxUIWidget* ofxUICanvas::addWidgetWestOf(ofxUIWidget *widget, string referenceName, bool reAdd)
{
    if(!reAdd) addWidget(widget);
    ofxUIWidget *referenceWidget = getWidget(referenceName);
    if(referenceWidget != NULL)
    {
        ofxUIRectangle *referencePaddedRect = referenceWidget->getPaddingRect();
        ofxUIRectangle *referenceRect = referenceWidget->getRect();
        ofxUIRectangle *widgetRect = widget->getRect();
        ofxUIRectangle *widgetPaddedRect = widget->getPaddingRect();
        
        widgetRect->y = referenceRect->getY()-rect->getY();
        widgetRect->x = referencePaddedRect->getX()-rect->getX()-widgetPaddedRect->getWidth();
    }
    else
    {
        ofxUIRectangle *currentRect = widget->getRect();
        currentRect->y = widgetSpacing;
    }
    lastAddeds.push_back( widget );
    return widget;
}

ofxUIWidget* ofxUICanvas::addWidgetEastOf(ofxUIWidget *widget, string referenceName, bool reAdd)
{
    if(!reAdd) addWidget(widget);
    ofxUIWidget *referenceWidget = getWidget(referenceName);
    if(referenceWidget != NULL)
    {
        ofxUIRectangle *referencePaddedRect = referenceWidget->getPaddingRect();
        ofxUIRectangle *referenceRect = referenceWidget->getRect();
        ofxUIRectangle *widgetRect = widget->getRect();
        widgetRect->y = referenceRect->getY()-rect->getY();
        widgetRect->x = referencePaddedRect->getX()-rect->getX()+referencePaddedRect->getWidth()+widgetSpacing;
    }
    else
    {
        ofxUIRectangle *currentRect = widget->getRect();
        currentRect->y = widgetSpacing;
    }
    lastAddeds.push_back( widget );
    return widget;
}

ofxUISpacer* ofxUICanvas::addSpacer(float h)
{
    if(h != globalSpacerHeight)
    {
        h = globalSpacerHeight;
    }
    ofxUISpacer* widget = new ofxUISpacer(rect->getWidth()-widgetSpacing*2, h);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUISpacer* ofxUICanvas::addSpacer(string name, float h)
{
    if(h != globalSpacerHeight)
    {
        h = globalSpacerHeight;
    }
    ofxUISpacer* widget = new ofxUISpacer(rect->getWidth()-widgetSpacing*2, h, name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUISpacer* ofxUICanvas::addSpacer(float w, float h)
{
    ofxUISpacer* widget = new ofxUISpacer(w, h);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUISpacer* ofxUICanvas::addSpacer(float w, float h, string name)
{
    ofxUISpacer* widget = new ofxUISpacer(w, h, name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUILabel* ofxUICanvas::addLabel(string name, int size)
{
    ofxUILabel* widget = new ofxUILabel(name, size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUILabel* ofxUICanvas::addLabel(string name, string label, int size)
{
    ofxUILabel* widget = new ofxUILabel(name, label, size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIFPS* ofxUICanvas::addFPS(int size)
{
    ofxUIFPS* widget = new ofxUIFPS(size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUISlider* ofxUICanvas::addSlider(string _name, float _min, float _max, float _value)
{
    ofxUISlider* widget = new ofxUISlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUISlider* ofxUICanvas::addSlider(string _name, float _min, float _max, float _value, float w, float h, float x, float y)
{
    ofxUISlider* widget = new ofxUISlider(_name, _min, _max, _value, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUISlider* ofxUICanvas::addSlider(string _name, float _min, float _max, float *_value)
{
    ofxUISlider* widget = new ofxUISlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUISlider* ofxUICanvas::addSlider(string _name, float _min, float _max, float *_value, float w, float h, float x, float y)
{
    ofxUISlider* widget = new ofxUISlider(_name, _min, _max, _value, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIIntSlider* ofxUICanvas::addIntSlider(string _name, int _min, int _max, int _value)
{
    ofxUIIntSlider* widget = new ofxUIIntSlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIIntSlider* ofxUICanvas::addIntSlider(string _name, int _min, int _max, int _value, float w, float h, float x, float y)
{
    ofxUIIntSlider* widget = new ofxUIIntSlider(_name, _min, _max, _value, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIIntSlider* ofxUICanvas::addIntSlider(string _name, int _min, int _max, int *_value)
{
    ofxUIIntSlider* widget = new ofxUIIntSlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIIntSlider* ofxUICanvas::addIntSlider(string _name, int _min, int _max, int *_value, float w, float h, float x, float y)
{
    ofxUIIntSlider* widget = new ofxUIIntSlider(_name, _min, _max, _value, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIDoubleSlider* ofxUICanvas::addDoubleSlider(string _name, double _min, double _max, double _value)
{
    ofxUIDoubleSlider* widget = new ofxUIDoubleSlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIDoubleSlider* ofxUICanvas::addDoubleSlider(string _name, double _min, double _max, double _value, float w, float h, float x, float y)
{
    ofxUIDoubleSlider* widget = new ofxUIDoubleSlider(_name, _min, _max, _value, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIDoubleSlider* ofxUICanvas::addDoubleSlider(string _name, double _min, double _max, double *_value)
{
    ofxUIDoubleSlider* widget = new ofxUIDoubleSlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIDoubleSlider* ofxUICanvas::addDoubleSlider(string _name, double _min, double _max, double *_value, float w, float h, float x, float y)
{
    ofxUIDoubleSlider* widget = new ofxUIDoubleSlider(_name, _min, _max, _value, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIRotarySlider* ofxUICanvas::addRotarySlider(string _name, float _min, float _max, float _value, int _size)
{
    ofxUIRotarySlider* widget = new ofxUIRotarySlider(rect->getWidth()-widgetSpacing*2, _min, _max, _value, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIRotarySlider* ofxUICanvas::addRotarySlider(string _name, float _min, float _max, float _value, float w, float x, float y, int _size)
{
    ofxUIRotarySlider* widget = new ofxUIRotarySlider(x, y, rect->getWidth()-widgetSpacing*2, _min, _max, _value, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIRotarySlider* ofxUICanvas::addRotarySlider(string _name, float _min, float _max, float *_value, int _size)
{
    ofxUIRotarySlider* widget = new ofxUIRotarySlider(rect->getWidth()-widgetSpacing*2, _min, _max, _value, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIRotarySlider* ofxUICanvas::addRotarySlider(string _name, float _min, float _max, float *_value, float w, float x, float y, int _size)
{
    ofxUIRotarySlider* widget = new ofxUIRotarySlider(x, y, w, _min, _max, _value, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIImageSlider* ofxUICanvas::addImageSlider(string _name, string _pathURL, float _min, float _max, float _value)
{
    ofxUIImageSlider* widget = new ofxUIImageSlider(rect->getWidth()-widgetSpacing*2, globalSliderHeight, _min, _max, _value, _pathURL, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIImageSlider* ofxUICanvas::addImageSlider(string _name, string _pathURL, float _min, float _max, float _value, float w, float h, float x, float y)
{
    ofxUIImageSlider* widget = new ofxUIImageSlider(x, y, w, h, _min, _max, _value, _pathURL, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIImageSlider* ofxUICanvas::addImageSlider(string _name, string _pathURL, float _min, float _max, float *_value)
{
    ofxUIImageSlider* widget = new ofxUIImageSlider(rect->getWidth()-widgetSpacing*2, globalSliderHeight, _min, _max, _value, _pathURL, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIImageSlider* ofxUICanvas::addImageSlider(string _name, string _pathURL, float _min, float _max, float *_value, float w, float h, float x, float y)
{
    ofxUIImageSlider* widget = new ofxUIImageSlider(x, y, w, h, _min, _max, _value, _pathURL, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUINumberDialer* ofxUICanvas::addNumberDialer(string _name, float _min, float _max, float _value, int _precision)
{
    ofxUINumberDialer* widget = new ofxUINumberDialer(_min, _max, _value, _precision, _name, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUINumberDialer* ofxUICanvas::addNumberDialer(string _name, float _min, float _max, float *_value, int _precision)
{
    ofxUINumberDialer* widget = new ofxUINumberDialer(_min, _max, _value, _precision, _name, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIMinimalSlider* ofxUICanvas::addMinimalSlider(string _name, float _min, float _max, float _value, int size)
{
    ofxUIMinimalSlider* widget = new ofxUIMinimalSlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0, size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIMinimalSlider* ofxUICanvas::addMinimalSlider(string _name, float _min, float _max, float _value, float w, float h, float x, float y, int size)
{
    ofxUIMinimalSlider* widget = new ofxUIMinimalSlider(_name, _min, _max, _value, w, h, x, y, size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIMinimalSlider* ofxUICanvas::addMinimalSlider(string _name, float _min, float _max, float *_value, int size)
{
    ofxUIMinimalSlider* widget = new ofxUIMinimalSlider(_name, _min, _max, _value, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0, size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIMinimalSlider* ofxUICanvas::addMinimalSlider(string _name, float _min, float _max, float *_value, float w, float h, float x, float y, int size)
{
    ofxUIMinimalSlider* widget = new ofxUIMinimalSlider(_name, _min, _max, _value, w, h, x, y, size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIRangeSlider* ofxUICanvas::addRangeSlider(string _name, float _min, float _max, float _valuelow, float _valuehigh)
{
    ofxUIRangeSlider* widget = new ofxUIRangeSlider(_name, _min, _max, _valuelow, _valuehigh, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIRangeSlider* ofxUICanvas::addRangeSlider(string _name, float _min, float _max, float _valuelow, float _valuehigh,
                                 float w, float h, float x, float y)
{
    ofxUIRangeSlider* widget = new ofxUIRangeSlider(_name, _min, _max, _valuelow, _valuehigh, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIRangeSlider* ofxUICanvas::addRangeSlider(string _name, float _min, float _max, float *_valuelow, float *_valuehigh)
{
    ofxUIRangeSlider* widget = new ofxUIRangeSlider(_name, _min, _max, _valuelow, _valuehigh, rect->getWidth()-widgetSpacing*2, globalSliderHeight, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIRangeSlider* ofxUICanvas::addRangeSlider(string _name, float _min, float _max, float *_valuelow, float *_valuehigh,
                                 float w, float h, float x, float y)
{
    ofxUIRangeSlider* widget = new ofxUIRangeSlider(_name, _min, _max, _valuelow, _valuehigh, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIFPSSlider* ofxUICanvas::addFPSSlider(string _name, float _max)
{
    ofxUIFPSSlider* widget = new ofxUIFPSSlider(_name, rect->getWidth()-widgetSpacing*2, globalSliderHeight, _max, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIFPSSlider* ofxUICanvas::addFPSSlider(string _name, float w, float h, float _max, float x, float y)
{
    ofxUIFPSSlider* widget = new ofxUIFPSSlider(_name, w, h, _max, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIRadio* ofxUICanvas::addRadio(string _name, vector<string> names, int _orientation, int _size)
{
    ofxUIRadio* widget = new ofxUIRadio(_name, names, _orientation, globalButtonDimension, globalButtonDimension, 0, 0, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIRadio* ofxUICanvas::addRadio(string _name, vector<string> names, int _orientation, float w, float h, float x, float y, int _size)
{
    ofxUIRadio* widget = new ofxUIRadio(_name, names, _orientation, w, h, x, y, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIButton* ofxUICanvas::addButton(string _name, bool _value)
{
    ofxUIButton* widget = new ofxUIButton(_name, _value, globalButtonDimension, globalButtonDimension, 0, 0, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIButton* ofxUICanvas::addButton(string _name, bool _value, float w, float h, float x, float y)
{
    ofxUIButton* widget = new ofxUIButton(_name, _value, w, h, x, y, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIButton* ofxUICanvas::addButton(string _name, bool *_value)
{
    ofxUIButton* widget = new ofxUIButton(_name, _value, globalButtonDimension, globalButtonDimension, 0, 0, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIButton* ofxUICanvas::addButton(string _name, bool *_value, float w, float h, float x, float y)
{
    ofxUIButton* widget = new ofxUIButton(_name, _value, w, h, x, y, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIToggle* ofxUICanvas::addToggle(string _name, bool _value)
{
    ofxUIToggle* widget = new ofxUIToggle(_name, _value, globalButtonDimension, globalButtonDimension, 0, 0, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIToggle* ofxUICanvas::addToggle(string _name, bool _value, float w, float h, float x, float y)
{
    ofxUIToggle* widget = new ofxUIToggle(_name, _value, w, h, x, y, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIToggle* ofxUICanvas::addToggle(string _name, bool *_value)
{
    ofxUIToggle* widget = new ofxUIToggle(_name, _value, globalButtonDimension, globalButtonDimension, 0, 0, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIToggle* ofxUICanvas::addToggle(string _name, bool *_value, float w, float h, float x, float y)
{
    ofxUIToggle* widget = new ofxUIToggle(_name, _value, w, h, x, y, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIToggleMatrix* ofxUICanvas::addToggleMatrix(string _name, int _rows, int _cols)
{
    float dim = globalButtonDimension;
    float width = rect->getWidth()-widgetSpacing*2;
    if(_cols*dim+_cols*padding > width)
    {
        dim = (width-(_cols-1)*padding)/_cols;
    }
    ofxUIToggleMatrix* widget = new ofxUIToggleMatrix(dim, dim, _rows, _cols, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIToggleMatrix* ofxUICanvas::addToggleMatrix(string _name, int _rows, int _cols, float w, float h)
{
    ofxUIToggleMatrix* widget = new ofxUIToggleMatrix(w, h, _rows, _cols, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUI2DPad* ofxUICanvas::add2DPad(string _name, ofxUIVec3f _rangeX, ofxUIVec3f _rangeY, ofxUIVec3f _value)
{
    float dim = rect->getWidth()-widgetSpacing*2;
    ofxUI2DPad* widget = new ofxUI2DPad(_name, _rangeX, _rangeY, _value, dim, dim, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}


ofxUI2DPad* ofxUICanvas::add2DPad(string _name, ofxUIVec3f _rangeX, ofxUIVec3f _rangeY, ofxUIVec3f _value, float w, float h, float x, float y)
{
    ofxUI2DPad* widget = new ofxUI2DPad(_name, _rangeX, _rangeY, _value, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUI2DPad* ofxUICanvas::add2DPad(string _name, ofxUIVec3f _rangeX, ofxUIVec3f _rangeY, ofxUIVec3f *_value)
{
    float dim = rect->getWidth()-widgetSpacing*2;
    ofxUI2DPad* widget = new ofxUI2DPad(_name, _rangeX, _rangeY, _value, dim, dim, 0, 0);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUI2DPad* ofxUICanvas::add2DPad(string _name, ofxUIVec3f _rangeX, ofxUIVec3f _rangeY, ofxUIVec3f *_value, float w, float h, float x, float y)
{
    ofxUI2DPad* widget = new ofxUI2DPad(_name, _rangeX, _rangeY, _value, w, h, x, y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUITextInput* ofxUICanvas::addTextInput(string _name, string _textstring, int _size)
{
    float h = 0;
    float x = 0;
    float y = 0;
    if(_size == -1)
    {
        _size = widgetFontSize;
    }
    ofxUITextInput* widget = new ofxUITextInput(_name, _textstring, rect->getWidth()-widgetSpacing*2, h, x, y, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUITextInput* ofxUICanvas::addTextInput(string _name, string _textstring, float w, float h, float x, float y, int _size)
{
    if(_size == -1)
    {
        _size = widgetFontSize;
    }
    ofxUITextInput* widget = new ofxUITextInput(_name, _textstring, w, h, x, y, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUILabelToggle* ofxUICanvas::addLabelToggle(string _name, bool _value, bool _justifyLeft)
{
    ofxUILabelToggle* widget = new ofxUILabelToggle(_name, _value, rect->getWidth()-widgetSpacing*2, globalButtonDimension, 0, 0, widgetFontSize, _justifyLeft);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUILabelToggle* ofxUICanvas::addLabelToggle(string _name, bool _value, float w, float h, float x, float y, bool _justifyLeft)
{
    if(h == 0)
    {
        h = globalButtonDimension;
    }
    ofxUILabelToggle* widget = new ofxUILabelToggle(_name, _value, w, h, x, y, widgetFontSize, _justifyLeft);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUILabelToggle* ofxUICanvas::addLabelToggle(string _name, bool *_value, bool _justifyLeft)
{
    ofxUILabelToggle* widget = new ofxUILabelToggle(_name, _value, rect->getWidth()-widgetSpacing*2, globalButtonDimension, 0, 0, widgetFontSize, _justifyLeft);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUILabelToggle* ofxUICanvas::addLabelToggle(string _name, bool *_value, float w, float h, float x, float y, bool _justifyLeft)
{
    ofxUILabelToggle* widget = new ofxUILabelToggle(_name, _value, w, h, x, y, widgetFontSize, _justifyLeft);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUILabelButton* ofxUICanvas::addLabelButton(string _name, bool _value, bool _justifyLeft)
{
    ofxUILabelButton* widget = new ofxUILabelButton(_name, _value, rect->getWidth()-widgetSpacing*2, globalButtonDimension, 0, 0, widgetFontSize, _justifyLeft);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUILabelButton* ofxUICanvas::addLabelButton(string _name, bool _value, float w, float h, float x, float y, bool _justifyLeft)
{
    if(h == 0)
    {
        h = globalButtonDimension;
    }
    ofxUILabelButton* widget = new ofxUILabelButton(_name, _value, w, h, x, y, widgetFontSize, _justifyLeft);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUILabelButton* ofxUICanvas::addLabelButton(string _name, bool *_value, bool _justifyLeft)
{
    ofxUILabelButton* widget = new ofxUILabelButton(_name, _value, rect->getWidth()-widgetSpacing*2, globalButtonDimension, 0, 0, widgetFontSize, _justifyLeft);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUILabelButton* ofxUICanvas::addLabelButton(string _name, bool *_value, float w, float h, float x, float y, bool _justifyLeft)
{
    if(h == 0)
    {
        h = globalButtonDimension;
    }
    ofxUILabelButton* widget = new ofxUILabelButton(_name, _value, w, h, x, y, widgetFontSize, _justifyLeft);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIDropDownList* ofxUICanvas::addDropDownList(string _name, vector<string> items)
{
    ofxUIDropDownList* widget = new ofxUIDropDownList(_name, items, rect->getWidth()-widgetSpacing*2, 0, 0, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIDropDownList* ofxUICanvas::addDropDownList(string _name, vector<string> items, float w, float x, float y)
{
    ofxUIDropDownList* widget = new ofxUIDropDownList(_name, items, w, x, y, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIWaveform* ofxUICanvas::addWaveform(string _name, float *_buffer, int _bufferSize, float _min, float _max, float _h)
{
    if(_h != globalGraphHeight)
    {
        _h = globalGraphHeight;
    }
    ofxUIWaveform* widget = new ofxUIWaveform(rect->getWidth()-widgetSpacing*2, _h, _buffer, _bufferSize, _min, _max, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIWaveform* ofxUICanvas::addWaveform(string _name, float *_buffer, int _bufferSize, float _min, float _max, float _w, float _h)
{
    ofxUIWaveform* widget = new ofxUIWaveform(_w, _h, _buffer, _bufferSize, _min, _max, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUISpectrum* ofxUICanvas::addSpectrum(string _name, float *_buffer, int _bufferSize, float _min, float _max, float _h)
{
    if(_h != globalGraphHeight)
    {
        _h = globalGraphHeight;
    }
    ofxUISpectrum* widget = new ofxUISpectrum(rect->getWidth()-widgetSpacing*2, _h, _buffer, _bufferSize, _min, _max, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUISpectrum* ofxUICanvas::addSpectrum(string _name, float *_buffer, int _bufferSize, float _min, float _max, float _w, float _h)
{
    ofxUISpectrum* widget = new ofxUISpectrum(_w, _h, _buffer, _bufferSize, _min, _max, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIMovingGraph* ofxUICanvas::addMovingGraph(string _name, vector<float> _buffer, int _bufferSize, float _min, float _max, float _h)
{
    if(_h != globalGraphHeight)
    {
        _h = globalGraphHeight;
    }
    ofxUIMovingGraph* widget = new ofxUIMovingGraph(rect->getWidth()-widgetSpacing*2, _h, _buffer, _bufferSize, _min, _max, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIMovingGraph* ofxUICanvas::addMovingGraph(string _name, vector<float> _buffer, int _bufferSize, float _min, float _max, float _w, float _h)
{
    ofxUIMovingGraph* widget = new ofxUIMovingGraph(_w, _h, _buffer, _bufferSize, _min, _max, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIImage* ofxUICanvas::addImage(string _name, ofImage *_image, float _w, float _h, bool _showLabel)
{
    ofxUIImage* widget = new ofxUIImage(_w, _h, _image, _name, _showLabel);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIImage* ofxUICanvas::addImage(string _name, ofImage *_image, bool _showLabel)
{
    float _w = rect->getWidth()-widgetSpacing*2;
    float _h = _w*(float)_image->getHeight()/(float)_image->getWidth();
    ofxUIImage* widget = new ofxUIImage(_w, _h, _image, _name, _showLabel);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIBaseDraws* ofxUICanvas::addBaseDraws(string _name, ofBaseDraws *_base, float _w, float _h, bool _showLabel)
{
    ofxUIBaseDraws* widget = new ofxUIBaseDraws(_w, _h, _base, _name, _showLabel);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIBaseDraws* ofxUICanvas::addBaseDraws(string _name, ofBaseDraws *_base, bool _showLabel)
{
    float _w = rect->getWidth()-widgetSpacing*2;
    float _h = _w*(float)_base->getHeight()/(float)_base->getWidth();
    ofxUIBaseDraws* widget = new ofxUIBaseDraws(_w, _h, _base, _name, _showLabel);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}
ofxUIImageSampler* ofxUICanvas::addImageSampler(string _name, ofImage *_image, float _w, float _h)
{
    ofxUIImageSampler* widget = new ofxUIImageSampler(_w, _h, _image, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIImageSampler* ofxUICanvas::addImageSampler(string _name, ofImage *_image)
{
    float _w = rect->getWidth()-widgetSpacing*2;
    float _h = _w*(float)_image->getHeight()/(float)_image->getWidth();
    ofxUIImageSampler* widget = new ofxUIImageSampler(_w, _h, _image, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIBiLabelSlider* ofxUICanvas::addBiLabelSlider(string _name, string _leftLabel, string _rightLabel, float _min, float _max, float _value, int _size)
{
    ofxUIBiLabelSlider* widget = new ofxUIBiLabelSlider(rect->getWidth()-widgetSpacing*2, globalSliderHeight, _min, _max, _value, _name, _leftLabel, _rightLabel, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIBiLabelSlider* ofxUICanvas::addBiLabelSlider(string _name, string _leftLabel, string _rightLabel, float _min, float _max, float *_value, int _size)
{
    ofxUIBiLabelSlider* widget = new ofxUIBiLabelSlider(rect->getWidth()-widgetSpacing*2, globalSliderHeight, _min, _max, _value, _name, _leftLabel, _rightLabel, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIBiLabelSlider* ofxUICanvas::addBiLabelSlider(string _name, string _leftLabel, string _rightLabel, float _min, float _max, float _value, float _w, float _h, int _size)
{
    ofxUIBiLabelSlider* widget = new ofxUIBiLabelSlider(_w, _h, _min, _max, _value, _name, _leftLabel, _rightLabel, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIBiLabelSlider* ofxUICanvas::addBiLabelSlider(string _name, string _leftLabel, string _rightLabel, float _min, float _max, float *_value, float _w, float _h, int _size)
{
    ofxUIBiLabelSlider* widget = new ofxUIBiLabelSlider(_w, _h, _min, _max, _value, _name, _leftLabel, _rightLabel, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUICircleSlider* ofxUICanvas::addCircleSlider(string _name, float _min, float _max, float _value)
{
    ofxUICircleSlider* widget = new ofxUICircleSlider(rect->getWidth()-widgetSpacing*2, _min, _max, _value, _name, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUICircleSlider* ofxUICanvas::addCircleSlider(string _name, float _min, float _max, float _value, float w, float x, float y)
{
    ofxUICircleSlider* widget = new ofxUICircleSlider(x, y, w, _min, _max, _value, _name, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUICircleSlider* ofxUICanvas::addCircleSlider(string _name, float _min, float _max, float *_value)
{
    ofxUICircleSlider* widget = new ofxUICircleSlider(0, 0, rect->getWidth()-widgetSpacing*2, _min, _max, _value, _name, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUICircleSlider* ofxUICanvas::addCircleSlider(string _name, float _min, float _max, float *_value, float w, float x, float y)
{
    ofxUICircleSlider* widget = new ofxUICircleSlider(x, y, w, _min, _max, _value, _name, widgetFontSize);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIValuePlotter* ofxUICanvas::addValuePlotter(string _name, int _bufferSize, float _min, float _max, float *_value, float _h)
{
    if(_h != globalGraphHeight)
    {
        _h = globalGraphHeight;
    }
    ofxUIValuePlotter* widget = new ofxUIValuePlotter(rect->getWidth()-widgetSpacing*2, _h, _bufferSize, _min, _max, _value, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIValuePlotter* ofxUICanvas::addValuePlotter(string _name, int _bufferSize, float _min, float _max, float *_value, float _w, float _h)
{
    ofxUIValuePlotter* widget = new ofxUIValuePlotter(_w, _h, _bufferSize, _min, _max, _value, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}


ofxUI2DGraph* ofxUICanvas::add2DGraph(string _name, ofxUIVec2f _rangeX, ofxUIVec2f _rangeY, int _bufferSize, float * _xValues, float * _yValues)
{
    ofxUI2DGraph* widget = new ofxUI2DGraph(_name, _rangeX, _rangeY, _bufferSize, _xValues, _yValues, rect->getWidth()-widgetSpacing*2, rect->getWidth()-widgetSpacing*2);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUI2DGraph* ofxUICanvas::add2DGraph(string _name, ofxUIVec2f _rangeX, ofxUIVec2f _rangeY, int _bufferSize, float * _xValues, float * _yValues, float _w, float _h, float _x, float _y)
{
    ofxUI2DGraph* widget = new ofxUI2DGraph(_name, _rangeX, _rangeY, _bufferSize, _xValues, _yValues, _w, _h, _x, _y);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIImageToggle* ofxUICanvas::addImageToggle(string _name, string _path, bool *_value, float w, float h, float x, float y, int _size)
{
    ofxUIImageToggle *widget = new ofxUIImageToggle(x, y, w, h, _value, _path, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIImageToggle* ofxUICanvas::addImageToggle(string _name, string _path, bool _value, float w, float h, float x, float y, int _size)
{
    ofxUIImageToggle *widget = new ofxUIImageToggle(x, y, w, h, _value, _path, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIImageToggle* ofxUICanvas::addImageToggle(string _name, string _path, bool *_value, int _size)
{
    ofxUIImageToggle *widget = new ofxUIImageToggle(globalButtonDimension, globalButtonDimension, _value, _path, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIImageToggle* ofxUICanvas::addImageToggle(string _name, string _path, bool _value, int _size)
{
    ofxUIImageToggle *widget = new ofxUIImageToggle(globalButtonDimension, globalButtonDimension, _value, _path, _name);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIImageButton* ofxUICanvas::addImageButton(string _name, string _path, bool *_value, float w, float h, float x, float y, int _size)
{
    ofxUIImageButton *widget = new ofxUIImageButton(x, y, w, h, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIImageButton* ofxUICanvas::addImageButton(string _name, string _path, bool _value, float w, float h, float x, float y, int _size)
{
    ofxUIImageButton *widget = new ofxUIImageButton(x, y, w, h, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIImageButton* ofxUICanvas::addImageButton(string _name, string _path, bool *_value, int _size)
{
    ofxUIImageButton *widget = new ofxUIImageButton(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIImageButton* ofxUICanvas::addImageButton(string _name, string _path, bool _value, int _size)
{
    ofxUIImageButton *widget = new ofxUIImageButton(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIMultiImageButton* ofxUICanvas::addMultiImageButton(string _name, string _path, bool *_value, float w, float h, float x, float y, int _size)
{
    ofxUIMultiImageButton *widget = new ofxUIMultiImageButton(x, y, w, h, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIMultiImageButton* ofxUICanvas::addMultiImageButton(string _name, string _path, bool _value, float w, float h, float x, float y, int _size)
{
    ofxUIMultiImageButton *widget = new ofxUIMultiImageButton(x, y, w, h, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIMultiImageButton* ofxUICanvas::addMultiImageButton(string _name, string _path, bool *_value, int _size)
{
    ofxUIMultiImageButton *widget = new ofxUIMultiImageButton(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIMultiImageButton* ofxUICanvas::addMultiImageButton(string _name, string _path, bool _value, int _size)
{
    ofxUIMultiImageButton *widget = new ofxUIMultiImageButton(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

//
ofxUIMultiImageToggle* ofxUICanvas::addMultiImageToggle(string _name, string _path, bool *_value, float w, float h, float x, float y, int _size)
{
    ofxUIMultiImageToggle *widget = new ofxUIMultiImageToggle(x, y, w, h, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIMultiImageToggle* ofxUICanvas::addMultiImageToggle(string _name, string _path, bool _value, float w, float h, float x, float y, int _size)
{
    ofxUIMultiImageToggle *widget = new ofxUIMultiImageToggle(x, y, w, h, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIMultiImageToggle* ofxUICanvas::addMultiImageToggle(string _name, string _path, bool *_value, int _size)
{
    ofxUIMultiImageToggle *widget = new ofxUIMultiImageToggle(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUIMultiImageToggle* ofxUICanvas::addMultiImageToggle(string _name, string _path, bool _value, int _size)
{
    ofxUIMultiImageToggle *widget = new ofxUIMultiImageToggle(globalButtonDimension, globalButtonDimension, _value, _path, _name, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}
//

ofxUITextArea* ofxUICanvas::addTextArea(string _name, string _textstring, int _size)
{
    ofxUITextArea *widget = new ofxUITextArea(_name, _textstring, rect->getWidth()-widgetSpacing*2, 0, 0, 0, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

ofxUISortableList* ofxUICanvas::addSortableList(string _name, vector<std::string> _items, int _size)
{
    if(_size == -1)
    {
        _size = widgetFontSize;
    }    
    ofxUISortableList *widget = new ofxUISortableList(_name, _items, rect->getWidth()-widgetSpacing*2, 0, 0, 0, _size);
    addWidgetPosition(widget, widgetPosition, widgetAlign);
    return widget;
}

void ofxUICanvas::resetPlacer()
{
    lastAddeds.clear();
}

void ofxUICanvas::setPlacer(ofxUIWidget *referenceWidget)
{
    if ( !referenceWidget )
        return;
    std::remove( lastAddeds.begin(), lastAddeds.end(), referenceWidget );
    lastAddeds.push_back( referenceWidget );
}

void ofxUICanvas::setLabelFont(ofxUILabel *label)
{
    switch(label->getSize())
    {
        case OFX_UI_FONT_LARGE:
            label->setFont(font_large);
            break;
        case OFX_UI_FONT_MEDIUM:
            label->setFont(font_medium);
            break;
        case OFX_UI_FONT_SMALL:
            label->setFont(font_small);
            break;
    }
}

void ofxUICanvas::setRetinaResolution()
{
    setGlobalCanvasWidth(OFX_UI_GLOBAL_CANVAS_WIDTH*2);
    setPadding(OFX_UI_GLOBAL_PADDING*2);
    setWidgetSpacing(OFX_UI_GLOBAL_WIDGET_SPACING*2);
    setFontSize(OFX_UI_FONT_LARGE, OFX_UI_FONT_LARGE_SIZE*2);
    setFontSize(OFX_UI_FONT_MEDIUM, OFX_UI_FONT_MEDIUM_SIZE*2);
    setFontSize(OFX_UI_FONT_SMALL, OFX_UI_FONT_SMALL_SIZE*2);
    setGlobalButtonDimension(OFX_UI_GLOBAL_BUTTON_DIMENSION*4);
    setGlobalSliderHeight(OFX_UI_GLOBAL_SLIDER_HEIGHT*4);
    setGlobalSpacerHeight(OFX_UI_GLOBAL_SPACING_HEIGHT*2);
    setGlobalGraphHeight(OFX_UI_GLOBAL_GRAPH_HEIGHT*2);
}

void ofxUICanvas::setGlobalSliderHeight(float _globalSliderHeight)
{
    globalSliderHeight = _globalSliderHeight;
}

void ofxUICanvas::setGlobalGraphHeight(float _globalGraphHeight)
{
    globalGraphHeight = _globalGraphHeight;
}

void ofxUICanvas::setGlobalButtonDimension(float _globalButtonDimension)
{
    globalButtonDimension = _globalButtonDimension;
}

void ofxUICanvas::setGlobalSpacerHeight(float _globalSpacerHeight)
{
    globalSpacerHeight = _globalSpacerHeight;
}

float ofxUICanvas::getGlobalSliderHeight()
{
    return globalSliderHeight;
}

float ofxUICanvas::getGlobalGraphHeight()
{
    return globalGraphHeight;
}

float ofxUICanvas::getGlobalButtonDimension()
{
    return globalButtonDimension;
}

float ofxUICanvas::getGlobalSpacerHeight()
{
    return globalSpacerHeight;
}

void ofxUICanvas::setGlobalCanvasWidth(float _globalCanvasWidth)
{
    globalCanvasWidth = _globalCanvasWidth;
    rect->setWidth(globalCanvasWidth);
    paddedRect->setWidth(globalCanvasWidth+padding*2);
}

float ofxUICanvas::getGlobalCanvasWidth()
{
    return globalCanvasWidth;
}

void ofxUICanvas::setWidgetPosition(ofxUIWidgetPosition _position, int _align)
{
    widgetPosition = _position;
    if (_align == -1)
    {
        if (_position == OFX_UI_WIDGET_POSITION_DOWN ||
            _position == OFX_UI_WIDGET_POSITION_UP)
        {
            widgetAlign = OFX_UI_ALIGN_LEFT;
        }
        else
        {
            widgetAlign = OFX_UI_ALIGN_FREE;
        }
    }
    else
    {
        widgetAlign = (ofxUIWidgetAlignment)_align;
    }
}

void ofxUICanvas::setWidgetFontSize(ofxUIWidgetFontType _widgetFontSize)
{
    widgetFontSize = _widgetFontSize;
}

ofxUIWidgetPosition ofxUICanvas::getWidgetPosition()
{
    return widgetPosition;
}

ofxUIWidgetFontType ofxUICanvas::getWidgetFontSize()
{
    return widgetFontSize;
}

void ofxUICanvas::triggerEvent(ofxUIWidget *child)
{
    checkForKeyFocus(child);
    GUIevent->widget = child;
    ofNotifyEvent(newGUIEvent,*GUIevent,this);
}

void ofxUICanvas::setUIColors(ofxUIColor &cb, ofxUIColor &co, ofxUIColor &coh, ofxUIColor &cf, ofxUIColor &cfh, ofxUIColor &cp, ofxUIColor &cpo)
{
    setWidgetColor(OFX_UI_WIDGET_COLOR_BACK, cb);
    setWidgetColor(OFX_UI_WIDGET_COLOR_OUTLINE, co);
    setWidgetColor(OFX_UI_WIDGET_COLOR_OUTLINE_HIGHLIGHT, coh);
    setWidgetColor(OFX_UI_WIDGET_COLOR_FILL, cf);
    setWidgetColor(OFX_UI_WIDGET_COLOR_FILL_HIGHLIGHT, cfh);
    setWidgetColor(OFX_UI_WIDGET_COLOR_PADDED, cp);
    setWidgetColor(OFX_UI_WIDGET_COLOR_PADDED_OUTLINE, cpo);
    
    setColorBack(cb);
    setColorOutline(co);
    setColorOutlineHighlight(coh);
    setColorFill(cf);
    setColorFillHighlight(cfh);
    setColorPadded(cp);
    setColorPaddedOutline(cpo);
}

void ofxUICanvas::setTheme(int theme)
{
    switch(theme)
    {
        case OFX_UI_THEME_DEFAULT:
        {
            ofxUIColor cb = OFX_UI_COLOR_BACK;
            ofxUIColor co = OFX_UI_COLOR_OUTLINE;
            ofxUIColor coh = OFX_UI_COLOR_OUTLINE_HIGHLIGHT;
            ofxUIColor cf = OFX_UI_COLOR_FILL;
            ofxUIColor cfh = OFX_UI_COLOR_FILL_HIGHLIGHT;
            ofxUIColor cp = OFX_UI_COLOR_PADDED;
            ofxUIColor cpo = OFX_UI_COLOR_PADDED_OUTLINE;
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_HACKER:
        {
            ofxUIColor cb = ofxUIColor( 0.294118*255.0, 0*255.0, 0.0588235*255.0, 0.196078*255.0 );
            ofxUIColor co = ofxUIColor( 0.254902*255.0, 0.239216*255.0, 0.239216*255.0, 0.392157*255.0 );
            ofxUIColor coh = ofxUIColor( 0.294118*255.0, 0*255.0, 0.0588235*255.0, 0.784314*255.0 );
            ofxUIColor cf = ofxUIColor( 0.784314*255.0, 1*255.0, 0*255.0, 0.784314*255.0 );
            ofxUIColor cfh = ofxUIColor( 0.980392*255.0, 0.00784314*255.0, 0.235294*255.0, 1*255.0 );
            ofxUIColor cp = ofxUIColor( 0.0156863*255.0, 0*255.0, 0.0156863*255.0, 0.392157*255.0 );
            ofxUIColor cpo = ofxUIColor( 0.254902*255.0, 0.239216*255.0, 0.239216*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
            
        case OFX_UI_THEME_HIPSTER:
        {
            ofxUIColor cb = ofxUIColor( 0.607843*255.0, 0.6*255.0, 0.509804*255.0, 0.196078*255.0 );
            ofxUIColor co = ofxUIColor( 0.231373*255.0, 0.392157*255.0, 0.501961*255.0, 0.392157*255.0 );
            ofxUIColor coh = ofxUIColor( 0.607843*255.0, 0.6*255.0, 0.509804*255.0, 0.784314*255.0 );
            ofxUIColor cf = ofxUIColor( 1*255.0, 0.52549*255.0, 0.0666667*255.0, 0.784314*255.0 );
            ofxUIColor cfh = ofxUIColor( 0.0313725*255.0, 0.101961*255.0, 0.188235*255.0, 1*255.0 );
            ofxUIColor cp = ofxUIColor( 0.196078*255.0, 0.25098*255.0, 0.352941*255.0, 0.392157*255.0 );
            ofxUIColor cpo = ofxUIColor( 0.231373*255.0, 0.392157*255.0, 0.501961*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_DIETER:
        {
            ofxUIColor cb = ofxUIColor( 0.803922*255.0, 0.741176*255.0, 0.682353*255.0, 0.196078*255.0 );
            ofxUIColor co = ofxUIColor( 0.478431*255.0, 0.356863*255.0, 0.243137*255.0, 0.392157*255.0 );
            ofxUIColor coh = ofxUIColor( 0.803922*255.0, 0.741176*255.0, 0.682353*255.0, 0.784314*255.0 );
            ofxUIColor cf = ofxUIColor( 0.980392*255.0, 0.294118*255.0, 0*255.0, 0.784314*255.0 );
            ofxUIColor cfh = ofxUIColor( 0.980392*255.0, 0.980392*255.0, 0.980392*255.0, 1*255.0 );
            ofxUIColor cp = ofxUIColor( 0.121569*255.0, 0.121569*255.0, 0.121569*255.0, 0.392157*255.0 );
            ofxUIColor cpo = ofxUIColor( 0.478431*255.0, 0.356863*255.0, 0.243137*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_BARBIE:
        {
            ofxUIColor cb = ofxUIColor( 0.92549*255.0, 0*255.0, 0.54902*255.0, 0.196078*255.0 );
            ofxUIColor co = ofxUIColor( 0*255.0, 0*255.0, 0*255.0, 0.392157*255.0 );
            ofxUIColor coh = ofxUIColor( 0*255.0, 0.678431*255.0, 0.937255*255.0, 0.784314*255.0 );
            ofxUIColor cf = ofxUIColor( 0.92549*255.0, 0*255.0, 0.54902*255.0, 0.784314*255.0 );
            ofxUIColor cfh = ofxUIColor( 1*255.0, 0.94902*255.0, 0*255.0, 1*255.0 );
            ofxUIColor cp = ofxUIColor( 0*255.0, 0*255.0, 0*255.0, 0.392157*255.0 );
            ofxUIColor cpo = ofxUIColor( 0*255.0, 0.678431*255.0, 0.937255*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_WINDOWS:
        {
            ofxUIColor cb = ofxUIColor( 0.0470588*255.0, 0.0588235*255.0, 0.4*255.0, 0.196078*255.0 );
            ofxUIColor co = ofxUIColor( 0.0431373*255.0, 0.0627451*255.0, 0.54902*255.0, 0.392157*255.0 );
            ofxUIColor coh = ofxUIColor( 0.0470588*255.0, 0.0588235*255.0, 0.4*255.0, 0.784314*255.0 );
            ofxUIColor cf = ofxUIColor( 0.054902*255.0, 0.305882*255.0, 0.678431*255.0, 0.784314*255.0 );
            ofxUIColor cfh = ofxUIColor( 0.0627451*255.0, 0.498039*255.0, 0.788235*255.0, 1*255.0 );
            ofxUIColor cp = ofxUIColor( 0.027451*255.0, 0.0352941*255.0, 0.239216*255.0, 0.392157*255.0 );
            ofxUIColor cpo = ofxUIColor( 0.0431373*255.0, 0.0627451*255.0, 0.54902*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_MACOSX:
        {
            ofxUIColor cb = ofxUIColor( 0*255.0, 0.678431*255.0, 0.937255*255.0, 0.196078*255.0 );
            ofxUIColor co = ofxUIColor( 1*255.0, 0.94902*255.0, 0*255.0, 0.392157*255.0 );
            ofxUIColor coh = ofxUIColor( 0*255.0, 0*255.0, 0*255.0, 0.784314*255.0 );
            ofxUIColor cf = ofxUIColor( 0*255.0, 0.678431*255.0, 0.937255*255.0, 0.784314*255.0 );
            ofxUIColor cfh = ofxUIColor( 0.92549*255.0, 0*255.0, 0.54902*255.0, 1*255.0 );
            ofxUIColor cp = ofxUIColor( 1*255.0, 0.94902*255.0, 0*255.0, 0.392157*255.0 );
            ofxUIColor cpo = ofxUIColor( 0*255.0, 0*255.0, 0*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_ZOOLANDER:
        {
            ofxUIColor cb = ofxUIColor( 0.160784*255.0, 0.133333*255.0, 0.121569*255.0, 0.196078*255.0 );
            ofxUIColor co = ofxUIColor( 0.0745098*255.0, 0.454902*255.0, 0.490196*255.0, 0.392157*255.0 );
            ofxUIColor coh = ofxUIColor( 0.160784*255.0, 0.133333*255.0, 0.121569*255.0, 0.784314*255.0 );
            ofxUIColor cf = ofxUIColor( 0.988235*255.0, 0.207843*255.0, 0.298039*255.0, 0.784314*255.0 );
            ofxUIColor cfh = ofxUIColor( 0.988235*255.0, 0.968627*255.0, 0.772549*255.0, 1*255.0 );
            ofxUIColor cp = ofxUIColor( 0.0392157*255.0, 0.74902*255.0, 0.737255*255.0, 0.392157*255.0 );
            ofxUIColor cpo = ofxUIColor( 0.0745098*255.0, 0.454902*255.0, 0.490196*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_VEGAN2:
        {
            ofxUIColor cb = ofxUIColor( 0.745098*255.0, 0.94902*255.0, 0.00784314*255.0, 0.196078*255.0 );
            ofxUIColor co = ofxUIColor( 0.533333*255.0, 0.768627*255.0, 0.145098*255.0, 0.392157*255.0 );
            ofxUIColor coh = ofxUIColor( 0.745098*255.0, 0.94902*255.0, 0.00784314*255.0, 0.784314*255.0 );
            ofxUIColor cf = ofxUIColor( 0.917647*255.0, 0.992157*255.0, 0.901961*255.0, 0.784314*255.0 );
            ofxUIColor cfh = ofxUIColor( 0.105882*255.0, 0.403922*255.0, 0.419608*255.0, 1*255.0 );
            ofxUIColor cp = ofxUIColor( 0.317647*255.0, 0.584314*255.0, 0.282353*255.0, 0.392157*255.0 );
            ofxUIColor cpo = ofxUIColor( 0.533333*255.0, 0.768627*255.0, 0.145098*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_BERLIN:
        {
            ofxUIColor cb = ofxUIColor( 0.6*255.0, 0.894118*255.0, 1*255.0, 0.196078*255.0 );
            ofxUIColor co = ofxUIColor( 0.294118*255.0, 0.34902*255.0, 0.419608*255.0, 0.392157*255.0 );
            ofxUIColor coh = ofxUIColor( 0.6*255.0, 0.894118*255.0, 1*255.0, 0.784314*255.0 );
            ofxUIColor cf = ofxUIColor( 0.968627*255.0, 0.309804*255.0, 0.309804*255.0, 0.784314*255.0 );
            ofxUIColor cfh = ofxUIColor( 1*255.0, 0.231373*255.0, 0.231373*255.0, 1*255.0 );
            ofxUIColor cp = ofxUIColor( 0.105882*255.0, 0.12549*255.0, 0.14902*255.0, 0.392157*255.0 );
            ofxUIColor cpo = ofxUIColor( 0.294118*255.0, 0.34902*255.0, 0.419608*255.0, 0.784314*255.0 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_METALGEAR:
        {
            ofxUIColor cb = ofxUIColor( 51, 44, 44, 75 );
            ofxUIColor co = ofxUIColor( 25, 26, 36, 100 );
            ofxUIColor coh = ofxUIColor( 51, 44, 44, 200 );
            ofxUIColor cf = ofxUIColor( 250, 101, 87, 200 );
            ofxUIColor cfh = ofxUIColor( 255, 255, 255, 255 );
            ofxUIColor cp = ofxUIColor( 0, 0, 0, 100 );
            ofxUIColor cpo = ofxUIColor( 25, 26, 36, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_TEALLIME:
        {
            ofxUIColor cb = ofxUIColor( 27, 103, 107, 75 );
            ofxUIColor co = ofxUIColor( 234, 253, 230, 100 );
            ofxUIColor coh = ofxUIColor( 27, 103, 107, 200 );
            ofxUIColor cf = ofxUIColor( 81, 149, 72, 200 );
            ofxUIColor cfh = ofxUIColor( 136, 196, 37, 255 );
            ofxUIColor cp = ofxUIColor( 190, 242, 2, 100 );
            ofxUIColor cpo = ofxUIColor( 234, 253, 230, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_VEGAN:
        {
            ofxUIColor cb = ofxUIColor( 81, 149, 72, 75 );
            ofxUIColor co = ofxUIColor( 27, 103, 107, 100 );
            ofxUIColor coh = ofxUIColor( 81, 149, 72, 200 );
            ofxUIColor cf = ofxUIColor( 136, 196, 37, 200 );
            ofxUIColor cfh = ofxUIColor( 190, 242, 2, 255 );
            ofxUIColor cp = ofxUIColor( 234, 253, 230, 100 );
            ofxUIColor cpo = ofxUIColor( 27, 103, 107, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_RUSTIC:
        {
            ofxUIColor cb = ofxUIColor( 196, 182, 109, 75 );
            ofxUIColor co = ofxUIColor( 247, 109, 60, 100 );
            ofxUIColor coh = ofxUIColor( 196, 182, 109, 200 );
            ofxUIColor cf = ofxUIColor( 213, 39, 5, 200 );
            ofxUIColor cfh = ofxUIColor( 240, 211, 119, 255 );
            ofxUIColor cp = ofxUIColor( 243, 232, 228, 100 );
            ofxUIColor cpo = ofxUIColor( 247, 109, 60, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_MIDNIGHT:
        {
            ofxUIColor cb = ofxUIColor( 11, 72, 107, 75 );
            ofxUIColor co = ofxUIColor( 207, 240, 158, 100 );
            ofxUIColor coh = ofxUIColor( 11, 72, 107, 200 );
            ofxUIColor cf = ofxUIColor( 59, 134, 134, 200 );
            ofxUIColor cfh = ofxUIColor( 121, 189, 154, 255 );
            ofxUIColor cp = ofxUIColor( 168, 219, 168, 100 );
            ofxUIColor cpo = ofxUIColor( 207, 240, 158, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_MINBLUE:
        {
            ofxUIColor cb = ofxUIColor( 254, 249, 240, 75 );
            ofxUIColor co = ofxUIColor( 176, 248, 255, 100 );
            ofxUIColor coh = ofxUIColor( 254, 249, 240, 200 );
            ofxUIColor cf = ofxUIColor( 0, 188, 209, 200 );
            ofxUIColor cfh = ofxUIColor( 118, 211, 222, 255 );
            ofxUIColor cp = ofxUIColor( 174, 232, 251, 100 );
            ofxUIColor cpo = ofxUIColor( 176, 248, 255, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_LIMESTONE:
        {
            ofxUIColor cb = ofxUIColor( 108, 144, 134, 75 );
            ofxUIColor co = ofxUIColor( 252, 84, 99, 100 );
            ofxUIColor coh = ofxUIColor( 108, 144, 134, 200 );
            ofxUIColor cf = ofxUIColor( 169, 204, 24, 200 );
            ofxUIColor cfh = ofxUIColor( 207, 73, 108, 255 );
            ofxUIColor cp = ofxUIColor( 235, 234, 188, 100 );
            ofxUIColor cpo = ofxUIColor( 252, 84, 99, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_SPEARMINT:
        {
            ofxUIColor cb = ofxUIColor( 25, 140, 9, 75 );
            ofxUIColor co = ofxUIColor( 255, 197, 95, 100 );
            ofxUIColor coh = ofxUIColor( 25, 140, 9, 200 );
            ofxUIColor cf = ofxUIColor( 220, 250, 250, 200 );
            ofxUIColor cfh = ofxUIColor( 239, 88, 141, 255 );
            ofxUIColor cp = ofxUIColor( 254, 169, 18, 100 );
            ofxUIColor cpo = ofxUIColor( 255, 197, 95, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_MINPINK:
        {
            ofxUIColor cb = ofxUIColor( 220, 250, 250, 75 );
            ofxUIColor co = ofxUIColor( 25, 140, 9, 100 );
            ofxUIColor coh = ofxUIColor( 220, 250, 250, 200 );
            ofxUIColor cf = ofxUIColor( 239, 88, 141, 200 );
            ofxUIColor cfh = ofxUIColor( 254, 169, 18, 255 );
            ofxUIColor cp = ofxUIColor( 255, 197, 95, 100 );
            ofxUIColor cpo = ofxUIColor( 25, 140, 9, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_PEPTOBISMOL:
        {
            ofxUIColor cb = ofxUIColor( 223, 21, 26, 75 );
            ofxUIColor co = ofxUIColor( 0, 218, 60, 100 );
            ofxUIColor coh = ofxUIColor( 223, 21, 26, 200 );
            ofxUIColor cf = ofxUIColor( 244, 243, 40, 200 );
            ofxUIColor cfh = ofxUIColor( 253, 134, 3, 255 );
            ofxUIColor cp = ofxUIColor( 0, 203, 231, 100 );
            ofxUIColor cpo = ofxUIColor( 0, 218, 60, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_BILEBLUE:
        {
            ofxUIColor cb = ofxUIColor( 253, 134, 3, 75 );
            ofxUIColor co = ofxUIColor( 244, 243, 40, 100 );
            ofxUIColor coh = ofxUIColor( 253, 134, 3, 200 );
            ofxUIColor cf = ofxUIColor( 0, 203, 231, 200 );
            ofxUIColor cfh = ofxUIColor( 0, 218, 60, 255 );
            ofxUIColor cp = ofxUIColor( 223, 21, 26, 100 );
            ofxUIColor cpo = ofxUIColor( 244, 243, 40, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_COOLCLAY:
        {
            ofxUIColor cb = ofxUIColor( 153, 228, 255, 75 );
            ofxUIColor co = ofxUIColor( 75, 89, 107, 100 );
            ofxUIColor coh = ofxUIColor( 153, 228, 255, 200 );
            ofxUIColor cf = ofxUIColor( 247, 79, 79, 200 );
            ofxUIColor cfh = ofxUIColor( 255, 59, 59, 255 );
            ofxUIColor cp = ofxUIColor( 27, 32, 38, 100 );
            ofxUIColor cpo = ofxUIColor( 75, 89, 107, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_BLUEBLUE:
        {
            ofxUIColor cb = ofxUIColor( 0, 173, 239, 75 );
            ofxUIColor co = ofxUIColor( 255, 242, 0, 100 );
            ofxUIColor coh = ofxUIColor( 0, 0, 0, 200 );
            ofxUIColor cf = ofxUIColor( 0, 173, 239, 200 );
            ofxUIColor cfh = ofxUIColor( 236, 0, 140, 255 );
            ofxUIColor cp = ofxUIColor( 255, 242, 0, 100 );
            ofxUIColor cpo = ofxUIColor( 0, 0, 0, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_PINKPANTHER:
        {
            ofxUIColor cb = ofxUIColor( 236, 0, 140, 75 );
            ofxUIColor co = ofxUIColor( 0, 0, 0, 100 );
            ofxUIColor coh = ofxUIColor( 0, 173, 239, 200 );
            ofxUIColor cf = ofxUIColor( 236, 0, 140, 200 );
            ofxUIColor cfh = ofxUIColor( 255, 242, 0, 255 );
            ofxUIColor cp = ofxUIColor( 0, 0, 0, 100 );
            ofxUIColor cpo = ofxUIColor( 0, 173, 239, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_MAROON:
        {
            ofxUIColor cb = ofxUIColor( 101, 150, 158, 75 );
            ofxUIColor co = ofxUIColor( 219, 217, 210, 100 );
            ofxUIColor coh = ofxUIColor( 101, 150, 158, 200 );
            ofxUIColor cf = ofxUIColor( 171, 20, 44, 200 );
            ofxUIColor cfh = ofxUIColor( 189, 219, 222, 255 );
            ofxUIColor cp = ofxUIColor( 205, 212, 108, 100 );
            ofxUIColor cpo = ofxUIColor( 219, 217, 210, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_PINKLATTE:
        {
            ofxUIColor cb = ofxUIColor( 218, 216, 167, 75 );
            ofxUIColor co = ofxUIColor( 127, 199, 175, 100 );
            ofxUIColor coh = ofxUIColor( 218, 216, 167, 200 );
            ofxUIColor cf = ofxUIColor( 255, 61, 127, 200 );
            ofxUIColor cfh = ofxUIColor( 255, 158, 157, 255 );
            ofxUIColor cp = ofxUIColor( 63, 184, 175, 100 );
            ofxUIColor cpo = ofxUIColor( 127, 199, 175, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_MINGREEN:
        {
            ofxUIColor cb = ofxUIColor( 255, 255, 255, 75 );
            ofxUIColor co = ofxUIColor( 242, 230, 194, 100 );
            ofxUIColor coh = ofxUIColor( 255, 255, 255, 200 );
            ofxUIColor cf = ofxUIColor( 111, 191, 162, 200 );
            ofxUIColor cfh = ofxUIColor( 191, 184, 174, 255 );
            ofxUIColor cp = ofxUIColor( 242, 199, 119, 100 );
            ofxUIColor cpo = ofxUIColor( 242, 230, 194, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_HELLOYELLOW:
        {
            ofxUIColor cb = ofxUIColor( 255, 211, 0, 75 );
            ofxUIColor co = ofxUIColor( 74, 186, 176, 100 );
            ofxUIColor coh = ofxUIColor( 152, 33, 0, 200 );
            ofxUIColor cf = ofxUIColor( 255, 211, 0, 200 );
            ofxUIColor cfh = ofxUIColor( 255, 245, 158, 255 );
            ofxUIColor cp = ofxUIColor( 74, 186, 176, 100 );
            ofxUIColor cpo = ofxUIColor( 152, 33, 0, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_TEALTEAL:
        {
            ofxUIColor cb = ofxUIColor( 74, 186, 176, 75 );
            ofxUIColor co = ofxUIColor( 255, 211, 0, 100 );
            ofxUIColor coh = ofxUIColor( 255, 245, 158, 200 );
            ofxUIColor cf = ofxUIColor( 74, 186, 176, 200 );
            ofxUIColor cfh = ofxUIColor( 152, 33, 0, 255 );
            ofxUIColor cp = ofxUIColor( 255, 211, 0, 100 );
            ofxUIColor cpo = ofxUIColor( 255, 245, 158, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_RUSTICORANGE:
        {
            ofxUIColor cb = ofxUIColor( 107, 85, 48, 75 );
            ofxUIColor co = ofxUIColor( 49, 48, 66, 100 );
            ofxUIColor coh = ofxUIColor( 107, 85, 48, 200 );
            ofxUIColor cf = ofxUIColor( 255, 109, 36, 200 );
            ofxUIColor cfh = ofxUIColor( 255, 235, 107, 255 );
            ofxUIColor cp = ofxUIColor( 42, 135, 50, 100 );
            ofxUIColor cpo = ofxUIColor( 49, 48, 66, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_TEALSALMON:
        {
            ofxUIColor cb = ofxUIColor( 78, 133, 136, 75 );
            ofxUIColor co = ofxUIColor( 56, 69, 59, 100 );
            ofxUIColor coh = ofxUIColor( 78, 133, 136, 200 );
            ofxUIColor cf = ofxUIColor( 255, 70, 84, 200 );
            ofxUIColor cfh = ofxUIColor( 255, 213, 106, 255 );
            ofxUIColor cp = ofxUIColor( 255, 254, 211, 100 );
            ofxUIColor cpo = ofxUIColor( 56, 69, 59, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_CITRUSBLUE:
        {
            ofxUIColor cb = ofxUIColor( 57, 142, 182, 75 );
            ofxUIColor co = ofxUIColor( 34, 104, 136, 100 );
            ofxUIColor coh = ofxUIColor( 57, 142, 182, 200 );
            ofxUIColor cf = ofxUIColor( 255, 162, 0, 200 );
            ofxUIColor cfh = ofxUIColor( 255, 214, 0, 255 );
            ofxUIColor cp = ofxUIColor( 255, 245, 0, 100 );
            ofxUIColor cpo = ofxUIColor( 34, 104, 136, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_LIMEPURPLE:
        {
            ofxUIColor cb = ofxUIColor( 87, 54, 255, 75 );
            ofxUIColor co = ofxUIColor( 38, 38, 38, 100 );
            ofxUIColor coh = ofxUIColor( 87, 54, 255, 200 );
            ofxUIColor cf = ofxUIColor( 231, 255, 54, 200 );
            ofxUIColor cfh = ofxUIColor( 255, 54, 111, 255 );
            ofxUIColor cp = ofxUIColor( 35, 116, 222, 100 );
            ofxUIColor cpo = ofxUIColor( 38, 38, 38, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_LIMESTONE2:
        {
            ofxUIColor cb = ofxUIColor( 101, 98, 115, 75 );
            ofxUIColor co = ofxUIColor( 89, 186, 169, 100 );
            ofxUIColor coh = ofxUIColor( 101, 98, 115, 200 );
            ofxUIColor cf = ofxUIColor( 216, 241, 113, 200 );
            ofxUIColor cfh = ofxUIColor( 252, 255, 217, 255 );
            ofxUIColor cp = ofxUIColor( 64, 18, 44, 100 );
            ofxUIColor cpo = ofxUIColor( 89, 186, 169, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_COOLPURPLE:
        {
            ofxUIColor cb = ofxUIColor( 38, 137, 233, 75 );
            ofxUIColor co = ofxUIColor( 11, 246, 147, 100 );
            ofxUIColor coh = ofxUIColor( 38, 137, 233, 200 );
            ofxUIColor cf = ofxUIColor( 233, 26, 157, 200 );
            ofxUIColor cfh = ofxUIColor( 246, 182, 11, 255 );
            ofxUIColor cp = ofxUIColor( 246, 242, 11, 100 );
            ofxUIColor cpo = ofxUIColor( 11, 246, 147, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_GRAYRED:
        {
            ofxUIColor cb = ofxUIColor( 41, 34, 31, 75 );
            ofxUIColor co = ofxUIColor( 19, 116, 125, 100 );
            ofxUIColor coh = ofxUIColor( 41, 34, 31, 200 );
            ofxUIColor cf = ofxUIColor( 252, 53, 76, 200 );
            ofxUIColor cfh = ofxUIColor( 252, 247, 197, 255 );
            ofxUIColor cp = ofxUIColor( 10, 191, 188, 100 );
            ofxUIColor cpo = ofxUIColor( 19, 116, 125, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_METALGEAR2:
        {
            ofxUIColor cb = ofxUIColor( 205, 189, 174, 75 );
            ofxUIColor co = ofxUIColor( 122, 91, 62, 100 );
            ofxUIColor coh = ofxUIColor( 205, 189, 174, 200 );
            ofxUIColor cf = ofxUIColor( 250, 75, 0, 200 );
            ofxUIColor cfh = ofxUIColor( 250, 250, 250, 255 );
            ofxUIColor cp = ofxUIColor( 31, 31, 31, 100 );
            ofxUIColor cpo = ofxUIColor( 122, 91, 62, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_LIGHTPINK:
        {
            ofxUIColor cb = ofxUIColor( 158, 30, 76, 75 );
            ofxUIColor co = ofxUIColor( 143, 143, 143, 100 );
            ofxUIColor coh = ofxUIColor( 158, 30, 76, 200 );
            ofxUIColor cf = ofxUIColor( 236, 236, 236, 200 );
            ofxUIColor cfh = ofxUIColor( 255, 17, 104, 255 );
            ofxUIColor cp = ofxUIColor( 37, 2, 15, 100 );
            ofxUIColor cpo = ofxUIColor( 143, 143, 143, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_MINPINK2:
        {
            ofxUIColor cb = ofxUIColor( 236, 236, 236, 75 );
            ofxUIColor co = ofxUIColor( 158, 30, 76, 100 );
            ofxUIColor coh = ofxUIColor( 236, 236, 236, 200 );
            ofxUIColor cf = ofxUIColor( 255, 17, 104, 200 );
            ofxUIColor cfh = ofxUIColor( 37, 2, 15, 255 );
            ofxUIColor cp = ofxUIColor( 143, 143, 143, 100 );
            ofxUIColor cpo = ofxUIColor( 158, 30, 76, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_MAXPINK:
        {
            ofxUIColor cb = ofxUIColor( 255, 20, 87, 75 );
            ofxUIColor co = ofxUIColor( 10, 10, 10, 100 );
            ofxUIColor coh = ofxUIColor( 227, 246, 255, 200 );
            ofxUIColor cf = ofxUIColor( 255, 20, 87, 200 );
            ofxUIColor cfh = ofxUIColor( 255, 216, 125, 255 );
            ofxUIColor cp = ofxUIColor( 10, 10, 10, 100 );
            ofxUIColor cpo = ofxUIColor( 227, 246, 255, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_MINYELLOW:
        {
            ofxUIColor cb = ofxUIColor( 229, 228, 218, 75 );
            ofxUIColor co = ofxUIColor( 216, 210, 153, 100 );
            ofxUIColor coh = ofxUIColor( 229, 228, 218, 200 );
            ofxUIColor cf = ofxUIColor( 245, 224, 56, 200 );
            ofxUIColor cfh = ofxUIColor( 23, 22, 92, 255 );
            ofxUIColor cp = ofxUIColor( 190, 191, 158, 100 );
            ofxUIColor cpo = ofxUIColor( 216, 210, 153, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_MINLIME:
        {
            ofxUIColor cb = ofxUIColor( 245, 225, 226, 75 );
            ofxUIColor co = ofxUIColor( 225, 183, 237, 100 );
            ofxUIColor coh = ofxUIColor( 245, 225, 226, 200 );
            ofxUIColor cf = ofxUIColor( 185, 222, 81, 200 );
            ofxUIColor cfh = ofxUIColor( 209, 227, 137, 255 );
            ofxUIColor cp = ofxUIColor( 224, 72, 145, 100 );
            ofxUIColor cpo = ofxUIColor( 225, 183, 237, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_MINORANGE:
        {
            ofxUIColor cb = ofxUIColor( 204, 204, 204, 75 );
            ofxUIColor co = ofxUIColor( 111, 111, 111, 100 );
            ofxUIColor coh = ofxUIColor( 204, 204, 204, 200 );
            ofxUIColor cf = ofxUIColor( 255, 100, 0, 200 );
            ofxUIColor cfh = ofxUIColor( 255, 255, 255, 255 );
            ofxUIColor cp = ofxUIColor( 51, 51, 51, 100 );
            ofxUIColor cpo = ofxUIColor( 111, 111, 111, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_GRAYDAY:
        {
            ofxUIColor cb = ofxUIColor( 177, 198, 204, 75 );
            ofxUIColor co = ofxUIColor( 255, 255, 255, 100 );
            ofxUIColor coh = ofxUIColor( 20, 20, 20, 200 );
            ofxUIColor cf = ofxUIColor( 177, 198, 204, 200 );
            ofxUIColor cfh = ofxUIColor( 255, 239, 94, 255 );
            ofxUIColor cp = ofxUIColor( 255, 255, 255, 100 );
            ofxUIColor cpo = ofxUIColor( 20, 20, 20, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        case OFX_UI_THEME_MINBLACK:
        {
            ofxUIColor cb = ofxUIColor( 255, 255, 255, 75 );
            ofxUIColor co = ofxUIColor( 209, 231, 81, 100 );
            ofxUIColor coh = ofxUIColor( 255, 255, 255, 200 );
            ofxUIColor cf = ofxUIColor( 0, 0, 0, 200 );
            ofxUIColor cfh = ofxUIColor( 38, 173, 228, 255 );
            ofxUIColor cp = ofxUIColor( 77, 188, 233, 100 );
            ofxUIColor cpo = ofxUIColor( 209, 231, 81, 200 );
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
            
        default:
        {
            ofxUIColor cb = OFX_UI_COLOR_BACK;
            ofxUIColor co = OFX_UI_COLOR_OUTLINE;
            ofxUIColor coh = OFX_UI_COLOR_OUTLINE_HIGHLIGHT;
            ofxUIColor cf = OFX_UI_COLOR_FILL;
            ofxUIColor cfh = OFX_UI_COLOR_FILL_HIGHLIGHT;
            ofxUIColor cp = OFX_UI_COLOR_PADDED;
            ofxUIColor cpo = OFX_UI_COLOR_PADDED_OUTLINE;
            setUIColors( cb, co, coh, cf, cfh, cp, cpo );
        }
            break;
    }
}

ofxUIColor& ofxUICanvas::getWidgetColorPadded()
{
    return widget_color_padded_rect;
}

ofxUIColor& ofxUICanvas::getWidgetColorPaddedOutline()
{
    return widget_color_padded_rect_outline;
}

ofxUIColor& ofxUICanvas::getWidgetColorBack()
{
    return widget_color_back;
}

ofxUIColor& ofxUICanvas::getWidgetColorOutline()
{
    return widget_color_outline;
}

ofxUIColor& ofxUICanvas::getWidgetColorOutlineHighlight()
{
    return widget_color_outline_highlight;
}

ofxUIColor& ofxUICanvas::getWidgetColorFill()
{
    return widget_color_fill;
}

ofxUIColor& ofxUICanvas::getWidgetColorFillHighlight()
{
    return widget_color_fill_highlight;
}

void ofxUICanvas::setWidgetDrawingProperties(ofxUIWidget *widget)
{
    widget->setDrawPaddingOutline(bDrawWidgetPaddingOutline);
    widget->setDrawPadding(bDrawWidgetPadding);
}

void ofxUICanvas::setWidgetColor(ofxUIWidget *widget)
{
    widget->setColorBack(color_back);
    widget->setColorOutline(color_outline);
    widget->setColorOutlineHighlight(color_outline_highlight);
    widget->setColorFill(color_fill);
    widget->setColorFillHighlight(color_fill_highlight);
    widget->setColorPadded(color_padded_rect);
    widget->setColorPaddedOutline(color_padded_rect_outline);
}

void ofxUICanvas::setWidgetColor(int _target, ofxUIColor _color)
{
    switch (_target)
    {
        case OFX_UI_WIDGET_COLOR_BACK:
            widget_color_back = _color;
            for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
            {
                (*it)->setColorBack(_color);
            }
            break;
            
        case OFX_UI_WIDGET_COLOR_OUTLINE:
            widget_color_outline = _color;
            for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
            {
                (*it)->setColorOutline(_color);
            }
            break;
            
        case OFX_UI_WIDGET_COLOR_OUTLINE_HIGHLIGHT:
            widget_color_outline_highlight = _color;
            for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
            {
                (*it)->setColorOutlineHighlight(_color);
            }
            break;
            
        case OFX_UI_WIDGET_COLOR_FILL:
            widget_color_fill = _color;
            for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
            {
                (*it)->setColorFill(_color);
            }
            break;
            
        case OFX_UI_WIDGET_COLOR_FILL_HIGHLIGHT:
            widget_color_fill_highlight = _color;
            for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
            {
                (*it)->setColorFillHighlight(_color);
            }
            break;
            
        case OFX_UI_WIDGET_COLOR_PADDED:
            widget_color_padded_rect = _color;
            for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
            {
                (*it)->setColorPadded(_color);
            }
            break;
            
        case OFX_UI_WIDGET_COLOR_PADDED_OUTLINE:
            widget_color_padded_rect_outline = _color;
            for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
            {
                (*it)->setColorPaddedOutline(_color);
            }
            break;
            
        default:
            break;
    }
}

ofxUIWidget *ofxUICanvas::getWidget(string _name, int widgetID)
{
    if(widgetID == -1)
    {
        multimap<string, ofxUIWidget *>::iterator wit = widgets_map.find(_name);
        if(wit != widgets_map.end())
        {
            return wit->second;
        }
    }
    else
    {
        for(multimap<string, ofxUIWidget*>::iterator wit = widgets_map.equal_range(_name).first; wit != widgets_map.equal_range(_name).second; ++wit)
        {
            if(wit->second->getID() == widgetID)
            {
                return wit->second;
            }
        }
        multimap<string, ofxUIWidget *>::iterator wit = widgets_map.find(_name);
        if(wit != widgets_map.end())
        {
            return wit->second;
        }
    }
    return NULL;
}

void ofxUICanvas::removeWidget(string _name)
{
    ofxUIWidget *w = getWidget(_name);
    if(w != NULL)
    {
        removeWidget(w);
    }
}

void ofxUICanvas::setAutoUpdate(bool _autoUpdate)
{
    autoUpdate = _autoUpdate;
}

void ofxUICanvas::setAutoDraw(bool _autoDraw)
{
    autoDraw = _autoDraw;
}

void ofxUICanvas::setPosition(int x, int y)
{
    rect->x = x;
    rect->y = y;
}

void ofxUICanvas::setHeight(float _height)
{
    setDimensions(rect->getWidth(), _height);
}

void ofxUICanvas::setWidth(float _width)
{
    setDimensions(_width, rect->getHeight());
}

void ofxUICanvas::setDimensions(float _width, float _height)
{
    rect->setWidth(_width);
    rect->setHeight(_height);
    paddedRect->width = rect->width+padding*2;
    paddedRect->height = rect->height+padding*2;
}

void ofxUICanvas::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
}

void ofxUICanvas::setDrawWidgetPadding(bool _draw_padded_rect)
{
    for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        (*it)->setDrawPadding(_draw_padded_rect);
    }
    bDrawWidgetPadding = _draw_padded_rect;
}

bool ofxUICanvas::getDrawWidgetPadding()
{
    return bDrawWidgetPadding;
}

void ofxUICanvas::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
}

void ofxUICanvas::setDrawWidgetPaddingOutline(bool _draw_padded_rect_outline)
{
    for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        (*it)->setDrawPaddingOutline(_draw_padded_rect_outline);
    }
    bDrawWidgetPaddingOutline = _draw_padded_rect_outline;
}

bool ofxUICanvas::getDrawWidgetPaddingOutline()
{
    return bDrawWidgetPaddingOutline;
}

vector<ofxUIWidget*> ofxUICanvas::getWidgets()
{
    return widgets;
}

vector<ofxUIWidget*> ofxUICanvas::getWidgetsOfType(ofxUIWidgetType type)
{
    vector<ofxUIWidget*> widgetToReturn;
    for(vector<ofxUIWidget *>::iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        if((*it)->getKind() == type)
        {
            widgetToReturn.push_back((*it));
        }
    }
    return widgetToReturn;
}

void ofxUICanvas::pushbackWidget(ofxUIWidget *widget, bool addWidgetToFront)
{
    widget->setID(uniqueIDs);
    uniqueIDs++;
    
    if(addWidgetToFront)
    {
        vector<ofxUIWidget*>::iterator it;
        it = widgets.begin();
        it = widgets.insert (it,widget);
    }
    else
    {
        widgets.push_back(widget);
    }
    
    widgets_map.insert ( pair<string,ofxUIWidget *>( widget->getName(), widget) );
}

bool ofxUICanvas::updateFont(ofxUIWidgetFontType _kind, string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet, bool makeContours, float simplifyAmt, int dpi)
{
    bool success = false;
    switch(_kind)
    {
        case OFX_UI_FONT_LARGE:
            if(font_large != NULL)
            {
                delete font_large;
            }
            font_large = new ofxUIFont();
            success = font_large->loadFont(filename,fontsize,_bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt,dpi);
            break;
            
        case OFX_UI_FONT_MEDIUM:
            if(font_medium != NULL)
            {
                delete font_medium;
            }
            font_medium = new ofxUIFont();
            success = font_medium->loadFont(filename,fontsize,_bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt,dpi);
            break;
            
        case OFX_UI_FONT_SMALL:
            if(font_small != NULL)
            {
                delete font_small;
            }
            font_small = new ofxUIFont();
            success = font_small->loadFont(filename,fontsize,_bAntiAliased, _bFullCharacterSet, makeContours, simplifyAmt,dpi);
            break;
    }
    return success;
}

void ofxUICanvas::checkForKeyFocus(ofxUIWidget *child)
{
    if(child->getKind() == OFX_UI_WIDGET_TEXTINPUT)
    {
        ofxUITextInput *textinput = (ofxUITextInput *) child;
        if(textinput->isFocused())
        {
            hasKeyBoard = true;
            return;        
        }
    }        
    hasKeyBoard = false;
}