#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true); 
	ofEnableSmoothing();
	
    drawPadding = false;
    gui = new ofxUICanvas();
	gui->addLabel("BUTTONS/TOGGLES", OFX_UI_FONT_LARGE);
    gui->addSpacer();
	gui->addLabel("BUTTONS");
    gui->addButton("B1", false, 44, 44);
    gui->addButton("B2", false);
    gui->addSpacer();
	gui->addLabel("TOGGLES");
    gui->addToggle("T1", false, 44, 44);
    gui->addToggle("T2", false);
    gui->addSpacer();
    
    vector<string> hnames; hnames.push_back("OPEN"); hnames.push_back("FRAME"); hnames.push_back("WORKS");
	gui->addLabel("HORIZONTAL RADIO");
	gui->addRadio("HR", hnames, OFX_UI_ORIENTATION_HORIZONTAL);
    
    gui->addSpacer();
    
    vector<string> vnames; vnames.push_back("ROCKS"); vnames.push_back("MY"); vnames.push_back("SOCKS");
    gui->addLabel("VERTICAL RADIO", OFX_UI_FONT_MEDIUM);
    ofxUIRadio *radio = gui->addRadio("VR", vnames, OFX_UI_ORIENTATION_VERTICAL);
    radio->activateToggle("SOCKS");
    
    gui->addSpacer(); 
    
    gui->addLabelButton("LABEL BTN", false);
    gui->addLabelButton("JUSTIFIED LEFT BTN", false, true);
    
    gui->addLabelToggle("LABEL TGL", false);
    gui->addLabelToggle("JUSTIFIED LEFT TGL", false, true);
    
    gui->setGlobalButtonDimension(24);
    gui->addSpacer();
    gui->addToggleMatrix("3X3 MATRIX", 3, 3); 
    gui->addToggleMatrix("DISABLE MULTIPLE", 3, 3);

    ofxUIToggleMatrix* mtx = (ofxUIToggleMatrix *) gui->getWidget("DISABLE MULTIPLE"); 
    mtx->setAllowMultiple(false); 
    gui->addToggleMatrix("CUSTOM SIZE", 1,6);

    gui->addSpacer(); 
    gui->addLabel("IMAGE BTN/TGL");

    gui->setGlobalButtonDimension(44);
    gui->addMultiImageButton("BUTTON", "GUI/toggle.png", false);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui->addMultiImageToggle("TOGGLE", "GUI/toggle.png", false);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&ofApp::guiEvent);
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
    
    if(kind == OFX_UI_WIDGET_BUTTON)
    {
        ofxUIButton *button = (ofxUIButton *) e.widget; 
        cout << name << "\t value: " << button->getValue() << endl;         
    }
    else if(kind == OFX_UI_WIDGET_TOGGLE)
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        cout << name << "\t value: " << toggle->getValue() << endl;             
    }
    else if(kind == OFX_UI_WIDGET_IMAGEBUTTON)
    {
        ofxUIImageButton *button = (ofxUIImageButton *) e.widget; 
        cout << name << "\t value: " << button->getValue() << endl;                 
    }
    else if(kind == OFX_UI_WIDGET_IMAGETOGGLE)
    {
        ofxUIImageToggle *toggle = (ofxUIImageToggle *) e.widget; 
        cout << name << "\t value: " << toggle->getValue() << endl;                 
    }
	else if(kind == OFX_UI_WIDGET_LABELBUTTON)
    {
        ofxUILabelButton *button = (ofxUILabelButton *) e.widget; 
        cout << name << "\t value: " << button->getValue() << endl;                 
    }
    else if(kind == OFX_UI_WIDGET_LABELTOGGLE)
    {
        ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget; 
        cout << name << "\t value: " << toggle->getValue() << endl;                 
    }
	else if(name == "B1")
	{
        ofxUIButton *button = (ofxUIButton *) e.widget; 
        cout << "value: " << button->getValue() << endl; 
	}
    else if(name == "B2")
    {
        ofxUIButton *button = (ofxUIButton *) e.widget; 
        cout << "value: " << button->getValue() << endl;         
    }
    else if(name == "T1")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        cout << "value: " << toggle->getValue() << endl;     
    }
    else if(name == "T2")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        cout << "value: " << toggle->getValue() << endl;     
    }
}
//--------------------------------------------------------------
void ofApp::exit()
{
    delete gui; 
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key) 
    {
        case 'p':
        {
            drawPadding = !drawPadding; 
            gui->setDrawWidgetPadding(drawPadding);          
        }
            break;
            
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