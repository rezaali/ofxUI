#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofBackground(50);
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320; 
    gui = new ofxUICanvas();
    
    gui->addWidgetDown(new ofxUILabel("DYNAMIC DROP DOWN LIST", OFX_UI_FONT_LARGE)); 
    gui->addWidgetDown(new ofxUILabel("PRESS '1' TO ADD TO LIST", OFX_UI_FONT_MEDIUM)); 
    gui->addWidgetDown(new ofxUILabel("PRESS '2' TO DELETE FROM LIST", OFX_UI_FONT_MEDIUM));     
    gui->addWidgetDown(new ofxUILabel("PRESS '3' TO DELETE ALL IN LIST", OFX_UI_FONT_MEDIUM));         
    vector<string> names; 
    names.push_back("ONE");    names.push_back("TWO");    names.push_back("THREE");    names.push_back("FOUR");    names.push_back("FIVE");
    ddl = new ofxUIDropDownList(length-xInit, "DYNAMIC DROP DOWN", names, OFX_UI_FONT_MEDIUM);
    ddl->setAllowMultiple(true);
//    ddl->setAutoClose(true);
    gui->addWidgetDown(ddl);
    gui->setTheme(OFX_UI_THEME_BARBIE);
    gui->autoSizeToFitWidgets(); 
//    gui->setDrawWidgetPadding(true);
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
    string name = e.widget->getName(); 
    
    cout << "WIDGET NAME: " << name << endl; 
    
    if(name == "FULLSCREEN")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ofSetFullscreen(toggle->getValue());   
    }
    else if(name == "DYNAMIC DROP DOWN")
    {
        ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
        vector<ofxUIWidget *> &selected = ddlist->getSelected(); 
        for(int i = 0; i < selected.size(); i++)
        {
            cout << "SELECTED: " << selected[i]->getName() << endl; 
        }
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

        case '4':
            ddl->setLabelText("TEST LABEL");
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