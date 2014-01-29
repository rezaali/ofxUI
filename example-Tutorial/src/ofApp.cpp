#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    gui = new ofxUICanvas();
    
    gui->addLabel("OFXUI TUTORIAL", OFX_UI_FONT_LARGE);
    gui->addSlider("BACKGROUND",0.0,255.0,100.0);
    gui->addToggle("FULLSCREEN", false);
    gui->autoSizeToFitWidgets(); 
    ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent); 
    gui->loadSettings("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}
//--------------------------------------------------------------
void ofApp::exit()
{
    gui->saveSettings("settings.xml");
    delete gui; 
}
//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
    if(e.getName() == "BACKGROUND")
    {
        ofxUISlider *slider = e.getSlider();
        ofBackground(slider->getScaledValue());
    }
    else if(e.getName() == "FULLSCREEN")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ofSetFullscreen(toggle->getValue());   
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key) {
        case 'p':
            gui->setDrawWidgetPadding(true);
            break;
        case 'P':
            gui->setDrawWidgetPadding(false);
            break;

            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}