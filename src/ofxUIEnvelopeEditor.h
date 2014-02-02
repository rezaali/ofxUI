//
//  ofxUIEnvelopeEditor.h
//  GenMax
//
//  Created by Mitchell Nordine on 28/01/2014.
//
//

#pragma once

#include "ofxUIWidgetWithLabel.h"
#include "ofxUIEnvelope.h"

/*
 
 
 NOTE:
 
 Hope this isn't too messy! I made this a while ago when I first started using oF!
 
 You'll notice I have some functions in here for handling a "frequency"
 envelope - This is basically just an envelope that displays in a way that the lower
 values are much more visible/accessible than the higher ones. This is done via
 the functions that are right at the bottom of the file "toFrequency" and
 "toOriginal". This is basically just a Cubic function and a cubed root. I find this
 ridiculously helpful for working with audio, but perhaps the syntax can be changed
 and the methods can be made much more efficient / cleaner? Perhaps the x in the
 pow( ,x) function could be a public variable? Please let me know your thoughts,
 having some kind of pow display option is definitely a feature I'd like to
 keep if we can :-)
 
 Also, some of my "isClicked" booleans are probably unnecessary, not sure how to
 reference these states on the fly from oF yet.
 
 -   mitch.
 
 
 */

class ofxUIEnvelopeEditor : public ofxUIWidgetWithLabel {
    
public:
    
    ofxUIEnvelopeEditor(string _name,
                        float w, float h, float x = 0,
                        float y = 0) : ofxUIWidgetWithLabel()
    {
        init(_name, ofVec2f(0.5f,0.0f), w, h, x, y);
    }
    
    ofxUIEnvelopeEditor(string _name, ofxUIEnvelope *_envelope,
                        float w, float h, float x = 0,
                        float y = 0) : ofxUIWidgetWithLabel()
    {
        envelope = _envelope;   // Points to ofxUIEnvelope that you want to edit
        init(_name, ofVec2f(0.5f,0.0f), w, h, x, y);
    }
    
    void init(string _name, ofVec2f _value,
              float w, float h, float x = 0, float y = 0);
    virtual void update();
    void updateEnvelopeData();
    virtual void setDrawPadding(bool _draw_padded_rect);
    virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
    virtual void drawFill();
    virtual void drawFillHighlight();
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);
    void keyReleased(int key);
    void windowResized(int w, int h);
	void input(float x, float y);
	void updateLabel();
    void stateChange();
    void setVisible(bool _visible);
	void setValue(ofVec2f _value);
	ofVec2f getValue();
	ofVec2f getPercentValue();
    ofxUIVec3f getScaledValue();
	//ofxUILabel *getLabel();
	void setParent(ofxUIWidget *_parent);
    bool isDraggable();
    void setLabelPrecision(int _precision);
#ifndef OFX_UI_NO_XML
    virtual void saveState(ofxXmlSettings *XML);
    virtual void loadState(ofxXmlSettings *XML);
#endif
    
    /* Envelope Functions */
    
    void addEnvelopePoint();
    void setEnvelope(ofxUIEnvelope *_envelope);
    void drawEnvelope();
    void drawFrequencyEnvelope();
    void checkForPointNode();
    void checkForCurveNode(int i);
    void moveGrabbedPoint();
    void moveGrabbedCurve();
    double toFrequency(double value);
    double toOriginal(double frequency);
    
    /* Envelope variables */
    
    bool isFrequency = false;
    bool isPointGrabbed = false;
    bool isCurveGrabbed = false;
    bool isRightClick = false;
    
    float pointNodeRadius = 5.0f;
    float pointNodeRectWidth = 6.0f;
    float pointNodeRectHeight = 6.0f;
    
    ofPolyline polyline;
    ofxUIEnvelope *envelope;
    ofxUIEnvelope tempEnv;
    float envPosX, envPosY, currentX, currentY, nextX, nextY, halfwayBetweenX;
    ofVec3f *grabbedPoint;
    ofVec3f *nextPoint;
    bool stateCheck;
    
protected:
	ofVec2f value;
    int labelPrecision;
    float increment;
    ofVec2f rangeX, rangeY;
    
};


