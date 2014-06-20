#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

#ifndef OFX_UI_FONT_RENDERER
#define OFX_UI_FONT_RENDERER ofxTrueTypeFontUC
#endif

#include "ofxUI.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void drawGrid(float x, float y);
    
	void setGUI1();
	void guiEvent(ofxUIEventArgs &e);
	
	ofxUISuperCanvas *gui1;
    
    ofxTrueTypeFontUC myFont;
    string sampleString;
    ofPoint p1, p2, p3;
    ofRectangle rect1, rect2, rect3;
    vector<ofPath> characters;
    
};
