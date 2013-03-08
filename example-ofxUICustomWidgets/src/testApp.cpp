#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 
    
    red = 233; blue = 27; green = 52; 
	
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320-xInit; 
	
    drawPadding = false; 
    
    gui = new ofxUICanvas(0,0,length+xInit,ofGetHeight());     
    
	gui->addWidgetDown(new ofxUILabel("CUSTOM WIDGETS", OFX_UI_FONT_LARGE)); 
    
    gui->addSpacer(length-xInit, 2);
    gui->addWidgetDown(new ofxUILabel("NUMBER DIALER", OFX_UI_FONT_MEDIUM));
    gui->addWidgetDown(new ofxUINumberDialer(-99999.0000, 99999.0000, 100.0, 4, "NDIALER", OFX_UI_FONT_LARGE));

    gui->addSpacer(length-xInit, 2);
    gui->addWidgetDown(new ofxUILabel("TEXT INPUT", OFX_UI_FONT_MEDIUM)); 
    gui->addWidgetDown(new ofxUITextInput(length-xInit, "Text Input Large", "LARGE TEXT FIELD", OFX_UI_FONT_LARGE)); 
    gui->addWidgetDown(new ofxUITextInput(length-xInit, "Text Input Medium", "MEDIUM TEXT FIELD", OFX_UI_FONT_MEDIUM)); 
    gui->addWidgetDown(new ofxUITextInput(length-xInit, "Text Input Small", "SMALL TEXT FIELD", OFX_UI_FONT_SMALL));     
    gui->addWidgetDown(new ofxUITextInput(length-xInit, "Text Input Autoclear", "Auto Clear Disabled", OFX_UI_FONT_LARGE)); 
    ofxUITextInput* textinput = (ofxUITextInput *) gui->getWidget("Text Input Autoclear"); 
    textinput->setAutoClear(false); 

    gui->addSpacer(length-xInit, 2);
    buffer = new float[256];     
    for(int i = 0; i < 256; i++) { buffer[i] = ofNoise(i/100.0); }
    
	gui->addWidgetDown(new ofxUILabel("WAVEFORM GRAPH", OFX_UI_FONT_MEDIUM));     
	gui->addWidgetDown(new ofxUIWaveform(length-xInit, 64, buffer, 256, 0.0, 1.0, "WAVEFORM")); 
    gui->addWidgetDown(new ofxUILabel("SPECTRUM GRAPH", OFX_UI_FONT_MEDIUM));        
    gui->addWidgetDown(new ofxUISpectrum(length-xInit, 64, buffer, 256, 0.0, 1.0, "SPECTRUM")); 

    gui->addSpacer(length-xInit, 2);
    
    img = new ofImage(); 
    img->loadImage("of1.jpg"); 
    img2 = new ofImage(); 
    img2->loadImage("of2.jpg");     
    
    gui->addWidgetDown(new ofxUILabel("IMAGE DISPLAY", OFX_UI_FONT_MEDIUM));     

    float imgDim = (length-xInit)*.5; 
    imgDim -=xInit; 
    gui->addWidgetDown(new ofxUIImage(imgDim,imgDim, img, "OF LOGO 1")); 
    gui->addWidgetRight(new ofxUIImageSampler(imgDim,imgDim, img2, "OF LOGO 2"));         
    gui->addWidgetNorthOf(new ofxUILabel("IMAGE SAMPLER", OFX_UI_FONT_MEDIUM), "OF LOGO 2");
    
    
    gui->addWidgetSouthOf(new ofxUISpacer(length-xInit, 2), "OF LOGO 1"); 
    gui->addWidgetDown(new ofxUILabel("FPS LABEL", OFX_UI_FONT_MEDIUM));     
    gui->addWidgetDown(new ofxUIFPS(OFX_UI_FONT_MEDIUM)); 
    gui->addSpacer(length-xInit, 2);
    gui->addWidgetDown(new ofxUILabel("DROP DOWN LIST", OFX_UI_FONT_MEDIUM));     
    
    vector<string> items; items.push_back("FIRST ITEM"); items.push_back("SECOND ITEM"); items.push_back("THIRD ITEM"); items.push_back("FOURTH ITEM");    
    vector<string> items2; items2.push_back("FIFTH ITEM"); items2.push_back("SIXTH ITEM"); items2.push_back("SEVENTH ITEM"); items2.push_back("EIGTHTH ITEM");
    
    
    gui->addDropDownList("DROP DOWN", items, length/2.0 - xInit);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui->addDropDownList("ALLOW MULTIPLE", items2, length/2.0 - xInit);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);

    ofxUIDropDownList* ddl = (ofxUIDropDownList *) gui->getWidget("ALLOW MULTIPLE");
    ddl->setAllowMultiple(true); 
    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);	
	ofBackground(red, green, blue);
    
//    gui->setTheme(OFX_UI_THEME_BILEBLUE);
    gui->autoSizeToFitWidgets();
    
//    gui->loadSettings("GUI/guiSettings.xml"); 
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
	cout << name << endl; 
	if(name == "OF LOGO 2")
	{
		ofxUIImageSampler *sampler = (ofxUIImageSampler *) e.widget; 
        ofColor c = sampler->getColor();
        cout << "color value: " << (int)c.r << " " << (int)c.g << " " << (int)c.b << endl;
	}    
}
//--------------------------------------------------------------
void testApp::exit()
{
    gui->saveSettings("GUI/guiSettings.xml"); 
    delete gui; 
	delete[] buffer;     
    delete img; 
    delete img2;     
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    if(gui->hasKeyboardFocus())
    {
        return; 
    }
    
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