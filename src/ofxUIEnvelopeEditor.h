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
    
    ofxUIEnvelopeEditor(string _name, float w, float h, float x = 0, float y = 0);
    ofxUIEnvelopeEditor(string _name, ofxUIEnvelope *_envelope, float w, float h, float x = 0, float y = 0);
    ~ofxUIEnvelopeEditor();
    void init(string _name, ofxUIEnvelope *_envelope, float w, float h, float x = 0, float y = 0);
    void setParent(ofxUIWidget *_parent); 
    void updateEnvelopeData();
    void drawFill();
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
	void updateLabel();
    void stateChange();
    bool isDraggable();
    void setLabelPrecision(int _precision);
#ifndef OFX_UI_NO_XML
    virtual void saveState(ofxXmlSettings *XML);
    virtual void loadState(ofxXmlSettings *XML);
#endif
    
    void addEnvelopePoint(float x, float y);
    void setEnvelope(ofxUIEnvelope *_envelope);
    void drawEnvelope();
    bool checkForClosestPointNode(float x, float y);
    bool deleteClosestPointNode(float x, float y);
    bool checkForClosestCurveNode(int i, float x, float y);
    void moveGrabbedPoint(float x, float y);
    void moveGrabbedCurve(float x, float y);
    
protected:
    float hitThreshold;
    float pointNodeRadius;
    float pointNodeRectWidth;
    float pointNodeRectHeight;
    
    ofxUIVec3f *hitPoint;
    ofxUIVec3f *hitCurve;
    ofxUIVec3f *hitCurveNext;    
    bool bHitPoint;
    bool bHitCurve;
    ofPolyline polyline;
    ofxUIEnvelope *envelope;
    int labelPrecision;
    float increment;
    bool useReference;
};


