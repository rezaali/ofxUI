#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 
    
    red = 233; blue = 27; green = 52; 
	
	float dim = 32; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320-xInit; 
	
    drawPadding = false; 
    
    gui = new ofxUICanvas(0,0,length+xInit,ofGetHeight());     
    
	gui->addWidgetDown(new ofxUILabel("BUTTON & TOGGLE WIDGETS", OFX_UI_FONT_LARGE)); 
    
    gui->addSpacer(length-xInit, 2);
	gui->addWidgetDown(new ofxUILabel("BUTTONS", OFX_UI_FONT_MEDIUM)); 	
    gui->addWidgetDown(new ofxUIButton(dim*2, dim*2, false, "B1"));     
    gui->addWidgetRight(new ofxUIButton(dim*1, dim*1, false, "B2"));     
    
    gui->addWidgetSouthOf(new ofxUISpacer(length-xInit, 2), "B1"); 
	gui->addWidgetDown(new ofxUILabel("TOGGLES", OFX_UI_FONT_MEDIUM)); 	
    gui->addWidgetDown(new ofxUIToggle(dim*2, dim*2, false, "T1"));     
    gui->addWidgetRight(new ofxUIToggle(dim*1, dim*1, false, "T2"));     

    gui->addWidgetSouthOf(new ofxUISpacer(length-xInit, 2), "T1");     
    vector<string> hnames; hnames.push_back("OPEN"); hnames.push_back("FRAME"); hnames.push_back("WORKS");
	gui->addWidgetDown(new ofxUIRadio(dim, dim, "HORIZONTAL RADIO", hnames, OFX_UI_ORIENTATION_HORIZONTAL));     
    vector<string> vnames; vnames.push_back("ROCKS"); vnames.push_back("MY"); vnames.push_back("SOCKS");
    ofxUIRadio *radio = (ofxUIRadio *) gui->addWidgetDown(new ofxUIRadio(dim, dim, "VERTICAL RADIO", vnames, OFX_UI_ORIENTATION_VERTICAL)); 
    radio->activateToggle("SOCKS"); 
    
    gui->addSpacer(length-xInit, 2);
    gui->addWidgetDown(new ofxUILabelButton(false, "LABEL BUTTON", OFX_UI_FONT_MEDIUM)); 
    gui->addWidgetEastOf(new ofxUILabel("<- Automagically Sized", OFX_UI_FONT_SMALL),"LABEL BUTTON"); 
    gui->addWidgetSouthOf(new ofxUILabelButton(length-xInit, false, "SPECIFIED WIDTH BUTTON", OFX_UI_FONT_MEDIUM), "LABEL BUTTON"); 
    gui->addWidgetDown(new ofxUILabelToggle(false, "LABEL TOGGLE", OFX_UI_FONT_MEDIUM));     
    gui->addWidgetDown(new ofxUILabelToggle(length-xInit, false, "SPECIFIED WIDTH TOGGLE", OFX_UI_FONT_MEDIUM));         
    
    gui->addSpacer(length-xInit, 2);
    gui->addWidgetDown(new ofxUIToggleMatrix(dim, dim, 3, 3, "3X3 MATRIX")); 
    gui->addWidgetRight(new ofxUIToggleMatrix(dim, dim, 3, 3, "DISABLE MULTIPLE"));     

    ofxUIToggleMatrix* mtx = (ofxUIToggleMatrix *)gui->getWidget("DISABLE MULTIPLE"); 
    mtx->setAllowMultiple(false); 
    gui->addWidgetSouthOf(new ofxUIToggleMatrix(dim,dim,1,6,"CUSTOM SIZE"), "3X3 MATRIX");

    gui->addSpacer(length-xInit, 2);
    gui->addWidgetDown(new ofxUILabel("IMAGE BUTTON & TOGGLE", OFX_UI_FONT_MEDIUM)); 
    gui->addWidgetDown(new ofxUIImageButton(dim*2, dim*2, false, "GUI/pause.png", "IMAGE BUTTON")); 
    gui->addWidgetRight(new ofxUIImageToggle(dim*2, dim*2, false, "GUI/play.png", "IMAGE TOGGLE"));  
    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);	
	ofBackground(red, green, blue); 
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
	
    
    
	if(name == "B1")
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