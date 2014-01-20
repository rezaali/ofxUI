#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(150);
    
    gui = new ofxUICanvas();
    gui->addLabel("DYNAMIC DROPDOWN", OFX_UI_FONT_MEDIUM);
    gui->addSpacer();
    gui->addLabel("'1' TO ADD TO LIST", OFX_UI_FONT_SMALL);
    gui->addLabel("'2' TO DELETE FROM LIST", OFX_UI_FONT_SMALL);
    gui->addLabel("'3' TO DELETE ALL IN LIST", OFX_UI_FONT_SMALL);
    gui->addSpacer();
    vector<string> names;
    names.push_back("ONE");    names.push_back("TWO");    names.push_back("THREE");    names.push_back("FOUR");    names.push_back("FIVE");
    gui->setWidgetFontSize(OFX_UI_FONT_SMALL);
    gui->addToggle("SHOW ACTIVE", false);
    ddl = gui->addDropDownList("DYNAMIC DROP DOWN", names);
    ddl->setAllowMultiple(true);
//    ddl->setAutoClose(true);
    gui->autoSizeToFitWidgets(); 
//    gui->setDrawWidgetPadding(true);
    ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent);
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
void ofApp::exit()
{
    delete gui; 
}
//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    if(name == "SHOW ACTIVE")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ddl->setShowCurrentSelected(toggle->getValue()); 
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
void ofApp::keyPressed(int key)
{
    switch (key) {
        case 'p':
            gui->setDrawWidgetPadding(true);
            break;
        case 'P':
            gui->setDrawWidgetPadding(false);
            break;
            
        case '1':
            ddl->addToggle(ofGetTimestampString());
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