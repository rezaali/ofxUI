#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetFrameRate(60);
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float dim = 32; 
    float length = 320-xInit;
//    length*=.25; 
        
    gui = new ofxUIScrollableCanvas(0,0,ofGetWidth(),ofGetHeight());    
    gui->setScrollAreaToScreen();
    gui->setScrollableDirections(false, true);

    for(int i = 0; i < 30; i++)
    {
        gui->addSlider("SLIDER " +ofToString(i), 0, 100, i*3.3, length-xInit, dim);
        gui->addSpacer(length-xInit, 2);
    }
    
    vector<ofxUIWidget*> spacers = gui->getWidgetsOfType(OFX_UI_WIDGET_SPACER);
    
    for(int i = 0; i < spacers.size(); i++)
    {
        ofxUISpacer *s = (ofxUISpacer *) spacers[i];
        s->toggleVisible();
    }
    
    gui->autoSizeToFitWidgets();
    gui->getRect()->setWidth(ofGetWidth());

    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent); 
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw()
{

}
//--------------------------------------------------------------
void testApp::exit()
{
    delete gui; 
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
    cout << e.widget->getName() << endl; 
    if(e.widget->getName() == "BACKGROUND VALUE")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        ofBackground(slider->getScaledValue());
    }
    else if(e.widget->getName() == "FULLSCREEN")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ofSetFullscreen(toggle->getValue());   
    }
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
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
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
    gui->getRect()->setWidth(ofGetWidth());
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}