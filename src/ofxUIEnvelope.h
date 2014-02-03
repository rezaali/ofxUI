//
//  ofxUIEnvelope.h
//  GenMax
//
//  Created by Mitchell Nordine on 28/01/2014.
//
//

#pragma once

/* Header Includes */

#include "ofMain.h"

/* This is needed for ofxUIEnvelope::sortPointsByX(). */
bool comparePointsX(ofVec3f pointA, ofVec3f pointB);

class ofxUIEnvelope {
    
public:
    
    void addPoint(double x, double y, float curve = 0);
    void sortPointsByX();
    double getY(double _x);
    vector<ofVec3f> & getPoints(); 
    
private:
    
    double interpolate(ofVec3f start, ofVec3f end);
    double getBezierPt(float n1, float n2, float percentage);
    
    double x, y;
    double interpolation;
    double xPos;
    double length;
    double gradient;
    double gradientY;
    double percentX;
    double result;
    
public:
    vector<ofVec3f> points; /* x = x, time, etc
                             y = y, value, etc
                             z = bezier curve value */
    
};
