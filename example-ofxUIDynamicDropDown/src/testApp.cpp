#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320; 
    gui = new ofxUICanvas();
    
    gui->addWidgetDown(new ofxUILabel("DYNAMIC DROP DOWN LIST", OFX_UI_FONT_LARGE)); 
    gui->addWidgetDown(new ofxUILabel("PRESS '1' TO ADD TO LIST", OFX_UI_FONT_MEDIUM)); 
    gui->addWidgetDown(new ofxUILabel("PRESS '2' TO DELETE FROM LIST", OFX_UI_FONT_MEDIUM));     
    gui->addWidgetDown(new ofxUILabel("PRESS '3' TO DELETE ALL IN LIST", OFX_UI_FONT_MEDIUM));         
    vector<string> names; 
    names.push_back("ONE");
    ddl = new ofxUIDropDownList(length-xInit, "DYNAMIC DROP DOWN", names, OFX_UI_FONT_MEDIUM); 
    gui->addWidgetDown(ddl);
    
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent); 
}

//--------------------------------------------------------------
void testApp::update()
{

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
            
        case '1':
            ddl->addToggle("NEW TOGGLE");
            break;

        case '2':
            ddl->removeToggle("NEW TOGGLE");
            break;

        case '3':
            ddl->clearToggles();
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
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}