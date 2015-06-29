#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup()
{
    ui = new ofxUISuperCanvas("IOS EXAMPLE");
    ui->addSpacer();    
    ui->addSlider("RED", 0.0, 255.0, &red);
    ui->addSlider("GREEN", 0.0, 255.0, &green);
    ui->addSlider("BLUE", 0.0, 255.0, &blue);
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground((int)red,(int)green,(int)blue);
}

//--------------------------------------------------------------
void ofApp::exit()
{
    delete ui;
}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch)
{

}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch)
{

}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch)
{

}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch)
{

}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch)
{

}

//--------------------------------------------------------------
void ofApp::lostFocus()
{
    
}

//--------------------------------------------------------------
void ofApp::gotFocus()
{
    
}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning()
{
    
}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation)
{
    
}

