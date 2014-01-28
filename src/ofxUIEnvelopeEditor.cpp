//
//  ofxUIEnvelopeEditor.cpp
//  GenMax
//
//  Created by Mitchell Nordine on 28/01/2014.
//
//

#include "ofxUIEnvelopeEditor.h"
#include "ofxUI.h"

void ofxUIEnvelopeEditor::init(string _name, ofVec2f _value,
          float w, float h, float x, float y)
{
    
    rect = new ofxUIRectangle(x,y,w,h);
    name = string(_name);
    kind = OFX_UI_WIDGET_2DPAD;
    paddedRect = new ofxUIRectangle(-padding, -padding,
                                    w+padding*2.0, h+padding);
    paddedRect->setParent(rect);
    draw_fill = true;
    draw_outline = true;
    value = _value;         //the widget's value
    
    labelPrecision = 2;
    
    if(value.x > 1)
    {
        value.x = 1;
    }
    else if(value.x < 0)
    {
        value.x = 0;
    }
    
    if(value.y > 1)
    {
        value.y = 1;
    }
    else if(value.y < 0)
    {
        value.y = 0;
    }
    
    label = new ofxUILabel(0,h+padding*2.0,(name+" LABEL"), (name + ": " + ofxUIToString(getScaledValue().x,labelPrecision) + ", " + ofxUIToString(getScaledValue().y,labelPrecision)), OFX_UI_FONT_SMALL);
    addEmbeddedWidget(label);
    
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::update()
{
    updateEnvelopeData();
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::updateEnvelopeData()
{
    
    tempEnv = *envelope;
    
    envPosX = rect->getX();
    envPosY = rect->getY() + rect->getHeight();
    
    polyline.clear();
    
    /* Add Envelope Vertices (non-frequency) */
    for (int i=0; i < rect->getWidth() && !isFrequency; i++) {
        
        currentX = envPosX + i;
        currentY = envPosY + (1-tempEnv.getY((double)i/rect->getWidth())
                              * rect->getHeight());
        
        polyline.addVertex(currentX, currentY);
        
    }
    
    /* Add Envelope Vertices for Frequency Type  */
    for (int i=0; i < rect->getWidth() && isFrequency; i++) {
        
        currentX = envPosX + i;
        currentY = envPosY
        + (1 - toOriginal(tempEnv.getY((double)i/rect->getWidth()))
           * rect->getHeight());
        
        polyline.addVertex(currentX, currentY);
        
    }
    
    
    return;
    
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::drawFill()
{
    if(draw_fill)
    {
        ofxUIFill();
        
        ofxUISetColor(color_fill);
        
        ofxUISetRectMode(OFX_UI_RECTMODE_CENTER);
        
        ofxUIDrawRect(rect->getX() + value.x * rect->getWidth(),
                      rect->getY() + value.y * rect->getHeight(),
                      OFX_UI_GLOBAL_WIDGET_SPACING,
                      OFX_UI_GLOBAL_WIDGET_SPACING);
        
        ofxUISetRectMode(OFX_UI_RECTMODE_CORNER);
        
        /*** Draw envelope to box here ***/
        
        if (isFrequency == true) {
            drawFrequencyEnvelope();
        }
        else if (isFrequency == false) {
            drawEnvelope();
        }
        
        /* Crosshair */
        
        ofxUIDrawLine(rect->getX() + value.x * rect->getWidth(),
                      rect->getY(),
                      rect->getX() + value.x * rect->getWidth(),
                      rect->getY() + rect->getHeight());
        
        ofxUIDrawLine(rect->getX(),
                      rect->getY() + value.y * rect->getHeight(),
                      rect->getX() + rect->getWidth(),
                      rect->getY() + value.y * rect->getHeight());
    }
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ofxUIFill();
        
        ofxUISetColor(color_fill_highlight);
        
        ofxUISetRectMode(OFX_UI_RECTMODE_CENTER);
        
        ofxUIDrawRect(rect->getX() + value.x * rect->getWidth(),
                      rect->getY() + value.y * rect->getHeight(),
                      OFX_UI_GLOBAL_WIDGET_SPACING,
                      OFX_UI_GLOBAL_WIDGET_SPACING);
        
        ofxUISetRectMode(OFX_UI_RECTMODE_CORNER);
        
        ofxUIDrawLine(rect->getX() + value.x * rect->getWidth(),
                      rect->getY(),
                      rect->getX() + value.x * rect->getWidth(),
                      rect->getY() + rect->getHeight());
        
        ofxUIDrawLine(rect->getX(),
                      rect->getY() + value.y * rect->getHeight(),
                      rect->getX() + rect->getWidth(),
                      rect->getY() + value.y * rect->getHeight());
        
        label->drawString(rect->getX() + value.x * rect->getWidth()
                          + OFX_UI_GLOBAL_WIDGET_SPACING,
                          rect->getY() + value.y * rect->getHeight(),
                          "(" + ofxUIToString(getScaledValue().x,labelPrecision)
                          + ", " + ofxUIToString(getScaledValue().y,labelPrecision)
                          +")");
    }
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::mouseMoved(int x, int y )
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

//----------------------------------------------------

void ofxUIEnvelopeEditor::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        state = OFX_UI_STATE_DOWN;
        input(x, y);
        
        /* These functions move the envelope points */
        moveGrabbedPoint();
        moveGrabbedCurve();
        
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
        /* For Left Clicks */
        if (button == 0) {
            isRightClick = false;
        }
        else if (button == 2) {
            isRightClick = true;
        }
        
        hit = true;
        state = OFX_UI_STATE_DOWN;
        input(x, y);
        
        /* Check for envelope point proximity here */
        checkForPointNode();
        
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
        
        input(x, y);
        
        /* Resets envelope point check booleans */
        if (isPointGrabbed) {
            isPointGrabbed = false;
        }
        else if (isCurveGrabbed) {
            isCurveGrabbed = false;
        }
        else if (isRightClick) {
            isRightClick = false;
        }
        
        /* Add an envelope point if no other interaction has occured */
        else{
            addEnvelopePoint();
        }
        
        triggerEvent(this);
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateCheck = abs(stateCheck - 1);
    stateChange();
    hit = false;
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::keyPressed(int key)
{
    if(state == OFX_UI_STATE_OVER)
    {
        switch (key)
        {
            case OF_KEY_RIGHT:
            {
                ofxUIVec3f p = getScaledValue();
                p.x+=increment;
                value.x = ofxUIMap(p.x, rangeX.x, rangeX.y, 0.0, 1.0, true);
                updateLabel();
                triggerEvent(this);
            }
                break;
                
            case OF_KEY_UP:
            {
                ofxUIVec3f p = getScaledValue();
                p.y +=increment;
                value.y = ofxUIMap(p.y, rangeY.x, rangeY.y, 0.0, 1.0, true);
                updateLabel();
                triggerEvent(this);
            }
                break;
                
            case OF_KEY_LEFT:
            {
                ofxUIVec3f p = getScaledValue();
                p.x-=increment;
                value.x = ofxUIMap(p.x, rangeX.x, rangeX.y, 0.0, 1.0, true);
                updateLabel();
                triggerEvent(this);
            }
                break;
                
            case OF_KEY_DOWN:
            {
                ofxUIVec3f p = getScaledValue();
                p.y -=increment;
                value.y = ofxUIMap(p.y, rangeY.x, rangeY.y, 0.0, 1.0, true);
                updateLabel();
                triggerEvent(this);
            }
                break;
                
            default:
                break;
        }
    }
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::keyReleased(int key)
{
    
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::windowResized(int w, int h)
{
    
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::input(float x, float y)
{
    
    value.x = rect->percentInside(x, y).x;
    value.y = rect->percentInside(x, y).y;
    if(value.x > 1.0)
    {
        value.x = 1.0;
    }
    else if(value.x < 0.0)
    {
        value.x = 0.0;
    }
    
    if(value.y > 1.0)
    {
        value.y = 1.0;
    }
    else if(value.y < 0.0)
    {
        value.y = 0.0;
    }
    
    /* Convert to "Frequency Input" if isFrequency == true (this is converted
     back to original in the drawEnvelopeFrequency function) */
    if (isFrequency == true) {
        value.y = toFrequency(value.y);
    }
    
    updateLabel();
    
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::updateLabel()
{
    label->setLabel(name + ": " + ofxUIToString(getScaledValue().x,labelPrecision) + ", " + ofxUIToString(getScaledValue().y,labelPrecision));
}

//----------------------------------------------------

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
            draw_fill_highlight = true;
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

//----------------------------------------------------

void ofxUIEnvelopeEditor::setVisible(bool _visible)
{
    visible = _visible;
    label->setVisible(visible);
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::setValue(ofVec2f _value)
{
    if(_value.x > rangeX.y)
    {
        _value.x = rangeX.y;
    }
    else if(_value.x < rangeX.x)
    {
        _value.x = rangeX.x;
    }
    
    if(_value.y > rangeY.y)
    {
        _value.y = rangeY.y;
    }
    else if(_value.y < rangeY.x)
    {
        _value.y = rangeY.x;
    }
    
    updateLabel();
}

//----------------------------------------------------

ofVec2f ofxUIEnvelopeEditor::getValue()
{
    return value;
}

//----------------------------------------------------

ofVec2f ofxUIEnvelopeEditor::getPercentValue()
{
    return value;
}

//----------------------------------------------------

ofxUIVec3f ofxUIEnvelopeEditor::getScaledValue()
{
    ofxUIVec3f p = value;
    p.x = ofxUIMap(p.x, 0, 1, rangeX.x, rangeX.y, true);
    p.y = ofxUIMap(p.y, 0, 1, rangeY.x, rangeY.y, true);
    return p;
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    label->getRect()->setY(rect->getHeight()+padding);
    calculatePaddingRect();
}

//----------------------------------------------------

bool ofxUIEnvelopeEditor::isDraggable()
{
    return true;
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::setLabelPrecision(int _precision)
{
    labelPrecision = _precision;
    updateLabel();
}

//----------------------------------------------------

#ifndef OFX_UI_NO_XML

void ofxUIEnvelopeEditor::saveState(ofxXmlSettings *XML)
{
    XML->setValue("XValue", getScaledValue().x, 0);
    XML->setValue("YValue", getScaledValue().y, 0);
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::loadState(ofxXmlSettings *XML)
{
    setValue(ofxUIVec3f(XML->getValue("XValue", getScaledValue().x, 0), XML->getValue("YValue", getScaledValue().y, 0)));
}

#endif

//----------------------------------------------------
// ADD POINT AT X - Y

void ofxUIEnvelopeEditor::addEnvelopePoint(){
    envelope->addPoint(value.x, 1.0f-value.y);
}

//----------------------------------------------------
// The envelope that is to be controlled may be changed at any time

void ofxUIEnvelopeEditor::setEnvelope(ofxUIEnvelope *_envelope)
{
    envelope = _envelope;
}

//----------------------------------------------------
// draw envelope

void ofxUIEnvelopeEditor::drawEnvelope(){
    
    for (int i=0; i < tempEnv.points.size()-1 && 1 < tempEnv.points.size();
         i++)
    {
        
        currentX = envPosX
        + tempEnv.points.at(i).x *rect->getWidth();
        currentY = rect->getY()
        + (1 - tempEnv.points.at(i).y) *rect->getHeight();
        
        nextX = envPosX
        + tempEnv.points.at(i+1).x *rect->getWidth();
        nextY = rect->getY()
        + (1 - tempEnv.points.at(i+1).y) *rect->getHeight();
        
        halfwayBetweenX = (currentX+nextX)/2;
        
        /* Draw Points */
        ofCircle(currentX, currentY, 5.0f);
        
        /* Draw Bezier Curve Control Squares */
        ofxUIDrawRect(halfwayBetweenX
                      - (pointNodeRectWidth/2),
                      envPosY
                      + 1
                      - tempEnv.getY((halfwayBetweenX-envPosX)/rect->getWidth())
                      * rect->getHeight()
                      - (pointNodeRectHeight/2),
                      pointNodeRectWidth,
                      pointNodeRectHeight);
        
    }
    
    polyline.draw();
    
}

//----------------------------------------------------
// draw frequency envelope

void ofxUIEnvelopeEditor::drawFrequencyEnvelope(){
    
    for (int i=0; i < tempEnv.points.size()-1 && 1 < tempEnv.points.size();
         i++)
    {
        
        currentX = envPosX
        + tempEnv.points.at(i).x *rect->getWidth();
        currentY = rect->getY()
        + (1 - toOriginal(tempEnv.points.at(i).y)) *rect->getHeight();
        
        nextX = envPosX
        + tempEnv.points.at(i+1).x *rect->getWidth();
        nextY = rect->getY()
        + (1 - toOriginal(tempEnv.points.at(i+1).y)) *rect->getHeight();
        
        halfwayBetweenX = (currentX+nextX)/2;
        
        /* Draw Points */
        ofCircle(currentX, currentY, pointNodeRadius);
        
        /* Draw Bezier Curve Control Squares */
        ofxUIDrawRect(halfwayBetweenX - (pointNodeRectWidth/2),
                      envPosY + 1
                      - toOriginal
                        (tempEnv.getY((halfwayBetweenX-envPosX)/rect->getWidth()))
                      * rect->getHeight() - (pointNodeRectHeight/2),
                      pointNodeRectWidth,
                      pointNodeRectHeight);
        
        
        
    }
    
    polyline.draw();
    
}


//----------------------------------------------------

void ofxUIEnvelopeEditor::checkForPointNode()
{
    
    tempEnv = *envelope;
    
    float pX, pY, difference;
    float rW = rect->getWidth();
    float rH = rect->getHeight();
    int size = tempEnv.points.size();
    
    for (int i=0; i<size; i++) {
        
        pX = tempEnv.points.at(i).x;
        pY = tempEnv.points.at(i).y;
        
        difference = abs( (pX*rW + pY*rH) - (value.x*rW + (1-value.y)*rH) );
        
        if (difference <= pointNodeRadius && isRightClick == false) {
            isPointGrabbed = true;
            grabbedPoint = &envelope->points.at(i);
            return;
        }
        else if (difference <= pointNodeRadius && isRightClick == true) {
            envelope->points.erase(envelope->points.begin()+i);
        }
        else {
            isPointGrabbed = false;
        }
        
        /* Check for Curve Nodes */
        if (i < size-1) {
            checkForCurveNode(i);
            if (isCurveGrabbed == true) {
                return;
            }
        }
        
    }
    
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::checkForCurveNode(int i)
{
    
    float currentX, currentY, nextX, nextY, difference,
    halfwayBetweenX, halfwayBetweenY;
    float rW = rect->getWidth();
    float rH = rect->getHeight();
    
    currentX = tempEnv.points.at(i).x;
    currentY = 1.0f - tempEnv.points.at(i).y;
    nextX = tempEnv.points.at(i+1).x;
    nextY = 1.0f - tempEnv.points.at(i+1).y;
    
    halfwayBetweenX = (currentX+nextX)/2.0f;
    halfwayBetweenY = tempEnv.getY(halfwayBetweenX);
    
    difference = abs( (halfwayBetweenX*rW + halfwayBetweenY*rH)
                     - (value.x*rW + (1-value.y)*rH) );
    
    if (difference <= pointNodeRadius && isRightClick == false) {
        isCurveGrabbed = true;
        grabbedPoint = &envelope->points.at(i);
        nextPoint = &envelope->points.at(i+1);
        return;
    }
    else {
        isCurveGrabbed = false;
    }
    
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::moveGrabbedPoint()
{
    
    if (isPointGrabbed == true) {
        grabbedPoint->x = value.x;
        grabbedPoint->y = 1 - value.y;
        /*cout << "x = " + ofToString(value.x) + " | y = " + ofToString(value.y)
         << endl;*/
    }
    
}

//----------------------------------------------------

void ofxUIEnvelopeEditor::moveGrabbedCurve()
{
    
    if (isCurveGrabbed == true) {
        
        float curveMover;
        float curveBasePoint = (grabbedPoint->y + nextPoint->y)/2.0f;
        
        if (nextPoint->y >= grabbedPoint->y) {
            curveMover = ofMap((1-value.y), curveBasePoint, nextPoint->y,
                               0.0f, 1.0f);
        }
        else if (nextPoint->y < grabbedPoint->y) {
            curveMover = ofMap((1-value.y), curveBasePoint, grabbedPoint->y,
                               0.0f, -1.0f);
        }
        
        grabbedPoint->z = ofClamp(curveMover, -1.0f, 1.0f);
        
    }
    
}

//----------------------------------------------------

double ofxUIEnvelopeEditor::toFrequency(double value)
{
    
    value = value-1;
    
    double frequency = pow(value, 3.0);
    
    frequency += 1;
    
    return frequency;
    
}

//----------------------------------------------------

double ofxUIEnvelopeEditor::toOriginal(double frequency)
{
    
    double original = pow(frequency, 1.0/3.0);
    
    return original;
    
}

//----------------------------------------------------



//----------------------------------------------------