#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
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
    noiseScale = .1; 
    drawFill = true;     
    backgroundColor = ofColor(233, 52, 27); 
    resolution = 30;
    position = ofPoint(ofGetWidth()*.5, ofGetHeight()*.5); 
    ofSetCircleResolution(resolution);
    
    gui = new ofxUICanvas();
    gui->addLabel("SUPER COMPACT");
    gui->addSpacer();
    gui->addFPSSlider("FPS");
    gui->addSpacer();
    gui->addSlider("RADIUS", 0.0, 255.0, &radius);
    gui->addSlider("RED", 0.0, 255.0, &red);
    gui->addSlider("GREEN", 0.0, 255.0, &green);
    gui->addSlider("BLUE", 0.0, 255.0, &blue);
    gui->addSlider("ALPHA", 0.0, 255.0, &alpha);
    gui->addSpacer();
    gui->add2DPad("CENTER", ofPoint(0,ofGetWidth()), ofPoint(0, ofGetHeight()), &position);
    gui->addLabelToggle("DRAWFILL", &drawFill);
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);    
    gui->loadSettings("GUI/guiSettings.xml");
    gui->setVisible(false); 
}

//--------------------------------------------------------------
void testApp::update()
{

}

//--------------------------------------------------------------
void testApp::draw()
{
	ofBackground(backgroundColor);
	ofPushStyle();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(255,200);
    ofDrawBitmapString("RIGHT CLICK TO ENABLE GUI", 10,20);
    ofDrawBitmapString("HIDE GUI BY CLICK OUTSIDE OF GUI", 10,40);
    
    ofSetColor(red, green, blue, alpha);
    if(drawFill)
    {
        ofFill(); 
    }
    else
    {
        ofNoFill(); 
    }

    ofCircle(position.x, position.y, radius);
    
	ofPopStyle(); 
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
//	string name = e.widget->getName(); 
//	int kind = e.widget->getKind(); 
}
//--------------------------------------------------------------
void testApp::exit()
{
    gui->saveSettings("GUI/guiSettings.xml");
    delete gui; 
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
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
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y )
{
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
 
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{ 
    if(button == 2)
    {
        gui->setPosition(x, y);
        gui->setVisible(true); 
        return;
    }
    
    if(!gui->isHit(x, y))
    {
        gui->setVisible(false); 
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
 

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}