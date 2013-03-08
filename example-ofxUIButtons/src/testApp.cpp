#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true); 
	ofEnableSmoothing();
	
    drawPadding = false;
    gui = new ofxUICanvas();
	gui->addLabel("BUTTONS/TOGGLES", OFX_UI_FONT_LARGE);
    gui->addSpacer();
	gui->addLabel("BUTTONS", OFX_UI_FONT_MEDIUM);
    gui->addButton("B1", false, 44, 44);
    gui->addButton("B2", false);
    gui->addSpacer();
	gui->addLabel("TOGGLES", OFX_UI_FONT_MEDIUM); 	
    gui->addToggle("T1", false, 44, 44);
    gui->addToggle("T2", false);
    gui->addSpacer();
    
    vector<string> hnames; hnames.push_back("OPEN"); hnames.push_back("FRAME"); hnames.push_back("WORKS");
	gui->addLabel("HORIZONTAL RADIO", OFX_UI_FONT_MEDIUM); 	
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
    
    gui->addSpacer(); 
    gui->addToggleMatrix("3X3 MATRIX", 3, 3); 
    gui->addToggleMatrix("DISABLE MULTIPLE", 3, 3);

    ofxUIToggleMatrix* mtx = (ofxUIToggleMatrix *) gui->getWidget("DISABLE MULTIPLE"); 
    mtx->setAllowMultiple(false); 
    gui->addToggleMatrix("CUSTOM SIZE", 1,6);

    gui->addSpacer(); 
    gui->addLabel("IMAGE BUTTON/TOGGLE", OFX_UI_FONT_MEDIUM); 
    gui->addImageButton("IMAGE BUTTON", "GUI/pause.png", false, 44, 44);
    gui->addImageToggle("IMAGE TOGGLE", "GUI/play.png", false, 44, 44);
    gui->autoSizeToFitWidgets();    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);	

    red = 0; blue = 0; green = 0;
	ofBackground(red, green, blue);

    gui->setColorBack(ofColor(255,100));
    gui->setWidgetColor(OFX_UI_WIDGET_COLOR_BACK, ofColor(255,100));
}

//--------------------------------------------------------------
void testApp::update()
{

}

//--------------------------------------------------------------
void testApp::draw()
{
	ofBackground(red, green, blue, 255); 
	
	ofPushStyle(); 
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);     
	ofPopStyle(); 
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
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
void testApp::exit()
{
    delete gui; 
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
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