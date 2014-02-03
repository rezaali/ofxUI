//
//  ofxUIEnvelope.cpp
//  GenMax
//
//  Created by Mitchell Nordine on 28/01/2014.
//
//

#include "ofxUIEnvelope.h"

bool comparePointsX(ofVec3f pointA, ofVec3f pointB)
{
    return pointA.x < pointB.x;
}

void ofxUIEnvelope::addPoint(double x, double y, float curve)
{
    ofVec3f point = ofVec3f(x, y, curve);
    points.push_back(point);
    sortPointsByX();
    return;
}

void ofxUIEnvelope::sortPointsByX()
{
    sort(points.begin(), points.end(), comparePointsX);
    return;
}

//Interpolates through envelope points to find value y at position x.
double ofxUIEnvelope::getY(double _x)
{
    
    x = _x;
    int i;
    
    /* Iterate through to find correct envelope point */
    for (i=0; i < points.size() && x >= points.at(i).x; i++){}
    
    /* Interpolate between points */
    interpolation = interpolate(points.at(i-1), points.at(i));
    
    /* Multiply interpolation by position and add onto previous point value */
    y = interpolation + points.at(i-1).y;
    
    return y;
    
}

vector<ofVec3f> & ofxUIEnvelope::getPoints()
{
    return points;
}


// Interpolates via a bezier curve whose depth is start.z
double ofxUIEnvelope::interpolate(ofVec3f start, ofVec3f end)
{
    
    /* Find time passed from start of interpolation */
    xPos = x - start.x;
    
    /* Find length of interpolation */
    length = end.x - start.x;
    
    /* Set gradient for interpolation */
    gradientY = end.y - start.y;
    gradient = length / gradientY;
    
    /* Consider bezier curve here - I've included original bezier code I used,
     feel free to get rid of unnecessary stuff, just thought you might be
     interested. */
    
    /* All points needed for a Bezier:
     double x1 = 0.0
     double x2 = gradientX/2.0f
     double x3 = gradientX
     double y1 = 0.0 */
    double y2 = (gradientY/2.0) + start.z * (gradientY/2.0); /*
                                                              double y3 = gradientY */
    
    percentX = xPos / length;
    
    /* Re-adjust linear trajectory */
    //float xa = getBezierPt(0.0f, x2, xPos);
    float ya = getBezierPt(0.0, y2, percentX);
    //float xb = getBezierPt(x2, gradientX, xPos);
    float yb = getBezierPt(y2, gradientY, percentX);
    
    /* Add gradient and Bezier together */
    result = getBezierPt(ya, yb, percentX);
    
    return result;
    
}

double ofxUIEnvelope::getBezierPt(float n1, float n2, float percentage)
{
    float difference = n2 - n1;
    return n1 + (difference * percentage);
}


