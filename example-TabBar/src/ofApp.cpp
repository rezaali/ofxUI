#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    guiTabBar = new ofxUITabBar();
    
    for(int i = 0; i < 10; i++)
    {
        string index = ofToString(i);
        ofxUICanvas* gui = new ofxUICanvas();
        gui->setName("GUI" + index);
        gui->addLabel("GUI" + index);
        gui->addSpacer();
        gui->addSlider("SLIDER " + index, 0, 1.0, i/10.0);
        gui->add2DPad("PAD " + index, ofVec2f(-1, 1), ofVec2f(-1, 1), ofVec2f(0.0, 0.0));
        gui->autoSizeToFitWidgets(); 
        ofAddListener(gui->newGUIEvent,this,&ofApp::guiEvent);
        guiTabBar->addCanvas(gui);
        guis.push_back(gui);
    }

    ofBackground(150);
    
    guiTabBar->loadSettings("settings/", "ui-");
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{	

}
//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind();
    string canvasParent = e.widget->getCanvasParent()->getName();
    cout << canvasParent << endl;
}

//--------------------------------------------------------------
void ofApp::exit()
{
    for(vector<ofxUICanvas *>::iterator it = guis.begin(); it != guis.end(); ++it)
    {
        ofxUICanvas *g = *it;
        delete g; 
    }
    delete guiTabBar;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key) 
    {
        case 'g':
        {
            guiTabBar->toggleVisible(); 
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