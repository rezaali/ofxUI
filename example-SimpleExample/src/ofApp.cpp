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
    backgroundColor = ofColor(233, 52, 27); 
    resolution = 30; 
    position = ofPoint(ofGetWidth()*.5, ofGetHeight()*.5); 
    ofSetCircleResolution(resolution); 
    
    gui = new ofxUISuperCanvas("VARIABLE BINDING");
    gui->addSpacer();
    gui->addLabel("BACKGROUND", OFX_UI_FONT_MEDIUM);
    gui->addSpacer();
    gui->addSlider("BGR", 0, 255, backgroundColor.r);
    gui->addSlider("BGG", 0, 255, backgroundColor.g);
    gui->addSlider("BGB", 0, 255, backgroundColor.b);
    gui->addSpacer();
    gui->addLabel("CIRCLE CONTROL");
    gui->addSlider("RED", 0.0, 255.0, red);
	gui->addSlider("GREEN", 0.0, 255.0, green);
    gui->addSlider("BLUE", 0.0, 255.0, blue);
    gui->addSlider("ALPHA", 0.0, 255.0, alpha);
    gui->addSlider("RADIUS", 0.0, 600.0, radius);
	gui->addSlider("RESOLUTION", 3, 60, resolution);
    gui->addLabelToggle("DRAW FILL", drawFill);
    gui->add2DPad("POSITION", ofPoint(0, ofGetWidth()), ofPoint(0, ofGetHeight()), position);
    gui->addSpacer();
    gui->addTextArea("TEXT AREA", "HIDE & SHOW GUI BY PRESSING 'g'. MOUSE OVER A SLIDER AND PRESS UP, DOWN, LEFT, RIGHT", OFX_UI_FONT_SMALL);
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&ofApp::guiEvent);
    gui->loadSettings("guiSettings.xml");
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{    	
	ofBackground(backgroundColor);     
	ofPushStyle(); 
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);     
    
    ofSetColor(red, green, blue, alpha); 
    if(drawFill)
    {
        ofFill(); 
    }
    else
    {
        ofNoFill(); 
    }
    ofCircle(position.x,position.y, radius); 
    
    
	ofPopStyle(); 
}
//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	
	if(name == "RED")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		red = slider->getScaledValue(); 
	}
	else if(name == "GREEN")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		green = slider->getScaledValue(); 
	}	
	else if(name == "BLUE")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		blue = slider->getScaledValue(); 		
	}
	else if(name == "BGR")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget; 
		backgroundColor.r = rslider->getScaledValue(); 		
	}    
	else if(name == "BGG")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget; 
		backgroundColor.g = rslider->getScaledValue(); 		
	}    
	else if(name == "BGB")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget; 
		backgroundColor.b = rslider->getScaledValue(); 		
	}    
	else if(name == "ALPHA")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		alpha = slider->getScaledValue(); 		
	}
	else if(name == "RADIUS")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		radius = slider->getScaledValue(); 		
	}
	else if(name == "RESOLUTION")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		resolution = slider->getScaledValue();          //gets the value from the specified range, otherwise you can get a normalized value (0.0 -> 1.0); 
        ofSetCircleResolution(resolution); 
        slider->setValue(resolution);                   //shows the int value on the slider 
	}    
    else if(name == "POSITION")
	{
		ofxUI2DPad *pad = (ofxUI2DPad *) e.widget; 
		position.x = pad->getPercentValue().x*ofGetWidth(); 
		position.y = pad->getPercentValue().y*ofGetHeight(); 
	}    
    else if(name == "DRAW FILL")
    {
        ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget; 
        drawFill = toggle->getValue();     
    }    
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