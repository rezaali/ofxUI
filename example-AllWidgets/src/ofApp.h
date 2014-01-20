#pragma once

#include "ofMain.h"
#include "ofxUI.h"

class ofApp : public ofBaseApp{
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
	void setGUI2();
	void setGUI3();
	void setGUI4();
	void setGUI5();
	
	ofxUISuperCanvas *gui1;
	ofxUISuperCanvas *gui2;
	ofxUISuperCanvas *gui3;
    ofxUISuperCanvas *gui4;
    ofxUISuperCanvas *gui5;

	bool hideGUI;
	
	float red, green, blue;
	bool bdrawGrid;
	bool bdrawPadding;
	
	void guiEvent(ofxUIEventArgs &e);
    
    ofxUIMovingGraph *mg;
    float *buffer;
    ofImage *img;
};
