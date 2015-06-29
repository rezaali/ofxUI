#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 
    
    //set some sketch parameters
    //Background Color 
    red = 233; 
    blue = 240; 
    green = 52; 
    alpha = 200; 
    radius = 150; 
    drawFill = true;     
    bgRed = 233;
    bgGreen = 52;
    bgBlue = 27; 
    resolution = 30; 
    position = ofPoint(ofGetWidth()*.5, ofGetHeight()*.5); 
    ofSetCircleResolution(resolution); 
    
    gui = new ofxUISuperCanvas("SIMPLE EXAMPLE");
    gui->addSpacer();
    gui->addLabel("BACKGROUND", OFX_UI_FONT_MEDIUM);
    gui->addSpacer();
    gui->addSlider("BGR", 0, 255, &bgRed);
    gui->addSlider("BGG", 0, 255, &bgGreen);
    gui->addSlider("BGB", 0, 255, &bgBlue);
    gui->addSpacer();
    gui->addLabel("CIRCLE CONTROL");
    gui->addSlider("RED", 0.0, 255.0, &red);
	gui->addSlider("GREEN", 0.0, 255.0, &green);
    gui->addSlider("BLUE", 0.0, 255.0, &blue);
    gui->addSlider("ALPHA", 0.0, 255.0, &alpha);
    gui->addSlider("RADIUS", 0.0, 600.0, &radius);
	gui->addIntSlider("RESOLUTION", 3, 60, &resolution);
    gui->addLabelToggle("DRAW FILL", &drawFill);
    gui->add2DPad("POSITION", ofPoint(0, ofGetWidth()), ofPoint(0, ofGetHeight()), &position);
    gui->addSpacer();
    gui->addTextArea("TEXT AREA", "HIDE & SHOW GUI BY PRESSING 'g'. MOUSE OVER A SLIDER AND PRESS UP, DOWN, LEFT, RIGHT", OFX_UI_FONT_SMALL);
    gui->autoSizeToFitWidgets();
    gui->loadSettings("guiSettings.xml");
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{    	
	ofBackground(bgRed, bgGreen, bgBlue);
	ofPushStyle(); 
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);     
    ofSetCircleResolution(resolution);
    ofSetColor(red, green, blue, alpha); 
    if(drawFill) { ofFill(); } else { ofNoFill(); }
    ofDrawCircle(position.x,position.y, radius);
	ofPopStyle(); 
}

//--------------------------------------------------------------
void ofApp::exit()
{
    gui->saveSettings("guiSettings.xml");
    delete gui; 
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key) 
    {            
        case 'g':
        {
            gui->toggleVisible(); 
        }
            break; 
        default:
            break;
    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{ 
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
 
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
 

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}