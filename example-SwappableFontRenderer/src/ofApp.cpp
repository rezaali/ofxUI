#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	setGUI1();
    gui1->loadSettings("gui1Settings.xml");
    
    myFont.loadFont("YasashisaAntique.ttf", 64, true, true);
    
    sampleString = "とりあえずアウ";
    
    p1 = ofPoint(100, 200);
    p2 = ofPoint(200, 300);
    p3 = ofPoint(300, 400);
    
    rect1 = myFont.getStringBoundingBox(sampleString, p1.x, p1.y);
    rect2 = myFont.getStringBoundingBox(sampleString, p2.x, p2.y);
    rect3 = myFont.getStringBoundingBox(sampleString, p3.x, p3.y);
    
    characters = myFont.getStringAsPoints(sampleString);
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
    string fpsStr = "frame rate: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(fpsStr, 100, 100);
    
    ofLine(rect1.getTopLeft(), rect1.getTopRight());
    ofLine(rect1.getTopRight(), rect1.getBottomRight());
    ofLine(rect1.getBottomRight(), rect1.getBottomLeft());
    ofLine(rect1.getBottomLeft(), rect1.getTopLeft());
    myFont.drawString(sampleString, p1.x, p1.y);
    
    ofLine(rect2.getTopLeft(), rect2.getTopRight());
    ofLine(rect2.getTopRight(), rect2.getBottomRight());
    ofLine(rect2.getBottomRight(), rect2.getBottomLeft());
    ofLine(rect2.getBottomLeft(), rect2.getTopLeft());
    myFont.drawStringAsShapes(sampleString, p2.x, p2.y);
    
    ofLine(rect3.getTopLeft(), rect3.getTopRight());
    ofLine(rect3.getTopRight(), rect3.getBottomRight());
    ofLine(rect3.getBottomRight(), rect3.getBottomLeft());
    ofLine(rect3.getBottomLeft(), rect3.getTopLeft());
    vector<ofPath>::iterator iter = characters.begin();
    for (; iter != characters.end(); ++iter)
        (*iter).draw(p3.x, p3.y);
}

void ofApp::guiEvent(ofxUIEventArgs &e)
{

}

//--------------------------------------------------------------
void ofApp::exit()
{
    gui1->saveSettings("gui1Settings.xml");
    
	delete gui1;

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    
}
void ofApp::setGUI1()
{
	gui1 = new ofxUISuperCanvas("とりあえずアウ");
    gui1->addSpacer();
    gui1->autoSizeToFitWidgets();
	ofAddListener(gui1->newGUIEvent,this,&ofApp::guiEvent);
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
void ofApp::mousePressed(int x, int y, int button){

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