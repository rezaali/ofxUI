/**********************************************************************************
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 Created by Mitchell Nordine on 28/01/2014.
 Refactored & Edited by Reza Ali on 02/02/2014
 
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

#include "ofxUIEnvelopeEditor.h"
#include "ofxUI.h"
#include "ofxUIUtils.h"

ofxUIEnvelopeEditor::ofxUIEnvelopeEditor(string _name, float w, float h, float x, float y) : ofxUIWidgetWithLabel()
{
    useReference = false;
    init(_name, NULL, w, h, x, y);
}

ofxUIEnvelopeEditor::ofxUIEnvelopeEditor(string _name, ofxUIEnvelope *_envelope, float w, float h, float x, float y) :ofxUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _envelope, w, h, x, y);
}

ofxUIEnvelopeEditor::~ofxUIEnvelopeEditor()
{
    if(!useReference)
    {
        delete envelope;
    }
}

void ofxUIEnvelopeEditor::init(string _name, ofxUIEnvelope *_envelope, float w, float h, float x, float y)
{
    initRect(x, y, w, h);
    name = string(_name);
    kind = OFX_UI_WIDGET_ENVELOPEEDITOR;
    
    draw_fill = true;
    draw_outline = true;
    
    if(useReference)
    {
        envelope = _envelope;
    }
    else
    {
        envelope = new ofxUIEnvelope();
    }
    
    labelPrecision = 2;
    label = new ofxUILabel(0,h+padding*2.0,(name+" LABEL"), (name + ":"), OFX_UI_FONT_SMALL);
    addEmbeddedWidget(label);

    hitThreshold = 0.05;
    pointNodeRadius = OFX_UI_GLOBAL_PADDING*1.5;
    pointNodeRectWidth = OFX_UI_GLOBAL_PADDING*2.5;
    pointNodeRectHeight = OFX_UI_GLOBAL_PADDING*2.5;
    bHitPoint = false;
    bHitCurve = false;
    hitPoint = NULL;
    hitCurve = NULL;
    hitCurveNext = NULL;
}

void ofxUIEnvelopeEditor::updateEnvelopeData()
{
    envelope->sortPointsByX();
    
    float rX = rect->getX();
    float rY = rect->getY();
    
    polyline.clear();
    
    for(int i = 0; i < rect->getWidth(); i++)
    {
        float x = rX + i;
        float nx = (double)i/rect->getWidth();
        float y = rY + envelope->getY(nx)*rect->getHeight();
        polyline.addVertex(x, y);
    }
}

void ofxUIEnvelopeEditor::drawFill()
{
    if(draw_fill)
    {
        ofxUIFill();
        ofxUISetColor(color_fill);
        drawEnvelope();
        updateEnvelopeData();
    }
}

void ofxUIEnvelopeEditor::setParent(ofxUIWidget *_parent)
{
    ofxUIWidgetWithLabel::setParent(_parent);
}

void ofxUIEnvelopeEditor::mouseMoved(int x, int y)
{
    if(rect->inside(x, y))
    {
        state = OFX_UI_STATE_OVER;
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUIEnvelopeEditor::mouseDragged(int x, int y, int button)
{
    if(hit && (bHitPoint || bHitCurve))
    {
        state = OFX_UI_STATE_DOWN;
        ofxUIVec2f pos = rect->percentInside(x, y);
        pos.x = MIN(1.0, MAX(0.0, pos.x));
        pos.y = MIN(1.0, MAX(0.0, pos.y));
        if(bHitPoint)
        {
            moveGrabbedPoint(pos.x, pos.y);            
        }
        else if(bHitCurve)
        {
            moveGrabbedCurve(pos.x, pos.y);
        }
        triggerEvent(this);
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        hit = true;
        state = OFX_UI_STATE_DOWN;

        ofxUIVec2f pos = rect->percentInside(x, y);
        pos.x = MIN(1.0, MAX(0.0, pos.x));
        pos.y = MIN(1.0, MAX(0.0, pos.y));

        if(button == 0)
        {            
            checkForClosestPointNode(pos.x, pos.y);
        }
        else if(!bHitCurve && !hitPoint)
        {
            deleteClosestPointNode(pos.x, pos.y);
        }
        
        triggerEvent(this);
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::mouseReleased(int x, int y, int button)
{
    if(hit)
    {
#ifdef TARGET_OPENGLES
        state = OFX_UI_STATE_NORMAL;
#else
        state = OFX_UI_STATE_OVER;
#endif

        if(bHitPoint)
        {
            bHitPoint = false;
            hitPoint = NULL;
        }
        else if(bHitCurve)
        {
            bHitCurve = false;
            hitCurve = NULL;
            hitCurveNext = NULL;
        }
        else
        {
            ofxUIVec2f pos = rect->percentInside(x, y);
            pos.x = MIN(1.0, MAX(0.0, pos.x));
            pos.y = MIN(1.0, MAX(0.0, pos.y));
            addEnvelopePoint(pos.x, pos.y);
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

void ofxUIEnvelopeEditor::stateChange()
{
    switch (state) {
        case OFX_UI_STATE_NORMAL:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
        case OFX_UI_STATE_OVER:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = true;
            label->unfocus();
        }
            break;
        case OFX_UI_STATE_DOWN:
        {
            draw_outline_highlight = true;
            label->focus();
        }
            break;
        case OFX_UI_STATE_SUSTAINED:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
            
        default:
            break;
    }
}

bool ofxUIEnvelopeEditor::isDraggable()
{
    return true;
}

void ofxUIEnvelopeEditor::setLabelPrecision(int _precision)
{
    labelPrecision = _precision;
    updateLabel();
}

#ifndef OFX_UI_NO_XML

void ofxUIEnvelopeEditor::saveState(ofxXmlSettings *XML)
{
//    XML->setValue("XValue", getScaledValue().x, 0);
//    XML->setValue("YValue", getScaledValue().y, 0);
}

void ofxUIEnvelopeEditor::loadState(ofxXmlSettings *XML)
{
//    setValue(ofxUIVec3f(XML->getValue("XValue", getScaledValue().x, 0), XML->getValue("YValue", getScaledValue().y, 0)));
}

#endif

void ofxUIEnvelopeEditor::addEnvelopePoint(float x, float y)
{
    envelope->addPoint(x, y);
}

void ofxUIEnvelopeEditor::setEnvelope(ofxUIEnvelope *_envelope)
{
    if(!useReference)
    {
        delete envelope;
        useReference = true;
    }
    envelope = _envelope;
}

void ofxUIEnvelopeEditor::drawEnvelope(){
    
    vector<ofVec3f> points = envelope->getPoints();
    int size = points.size();
    float rX = rect->getX();
    float rY = rect->getY();
    
    ofxUISetRectMode(OFX_UI_RECTMODE_CENTER);
    ofxUINoFill();
    for (int i = 0; i < size; i++)
    {
        float x = rX + points[i].x*rect->getWidth();
        float y = rY + points[i].y*rect->getHeight();
        
        ofxUICircle(x, y, pointNodeRadius);
        
        if(i < size-1)
        {
            float nx = rX + points[i+1].x*rect->getWidth();
            float hx = (x + nx)/2.0;
            ofxUIDrawRect(hx, rY + envelope->getY((hx-rX)/rect->getWidth())*rect->getHeight(), pointNodeRectWidth, pointNodeRectHeight);
        }
    }
    ofxUIFill();
    ofxUISetRectMode(OFX_UI_RECTMODE_CORNER);
    
    polyline.draw();
}

bool ofxUIEnvelopeEditor::checkForClosestPointNode(float x, float y)
{
    vector<ofxUIVec3f> &points = envelope->getPoints();
    int size = envelope->points.size();
    
    for(int i=0; i < size; i++)
    {
        if(ofDist(points[i].x, points[i].y, x, y) <= hitThreshold)
        {
            bHitPoint = true;
            hitPoint = &points[i];
            return bHitPoint;
        }
        
        if(checkForClosestCurveNode(i, x, y))
        {
            return true;
        }
    }
}

bool ofxUIEnvelopeEditor::deleteClosestPointNode(float x, float y)
{
    int size = envelope->points.size();
    
    for(int i=0; i < size; i++)
    {
        if(ofDist(envelope->points[i].x, envelope->points[i].y, x, y) <= hitThreshold)
        {
            envelope->points.erase(envelope->points.begin()+i);
            return true;
        }
    }
    return false;
}


bool ofxUIEnvelopeEditor::checkForClosestCurveNode(int i, float x, float y)
{
    int size = envelope->points.size();
    if(i < size-1)
    {
        float rW = rect->getWidth();
        float rH = rect->getHeight();
        
        float cX = envelope->points[i].x;
        float cY = envelope->points[i].y;

        float nX = envelope->points[i+1].x;
        float nY = envelope->points[i+1].y;
        
        float hX = (cX+nX)/2.0f;
        float hY = envelope->getY(hX);
        
        float distance = ofDist(hX, hY, x, y);
        
        if (distance <= hitThreshold)
        {
            bHitCurve = true;
            hitCurve = &envelope->points[i];
            hitCurveNext = &envelope->points[i+1];
            return true;
        }
    }
    return false;
}

void ofxUIEnvelopeEditor::moveGrabbedPoint(float x, float y)
{
    if(hitPoint != NULL)
    {
        hitPoint->x = x;
        hitPoint->y = y;
    }
}

void ofxUIEnvelopeEditor::moveGrabbedCurve(float x, float y)
{
    if(hitCurveNext != NULL && hitCurve != NULL)
    {
        float curveBasePoint = (hitCurve->y + hitCurveNext->y)/2.0f;

        if(hitCurveNext->y >= hitCurve->y)
        {
            hitCurve->z = ofxUIMap(y, curveBasePoint, hitCurveNext->y, 0.0f, 1.0f, true);
        }
        else if(hitCurveNext->y < hitCurve->y)
        {
            hitCurve->z = ofxUIMap(y, curveBasePoint, hitCurve->y, 0.0f, -1.0f, true);
        }
    }
}