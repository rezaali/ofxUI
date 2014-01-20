#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{	
    drawPadding = false;
    
    gui = new ofxUICanvas();
	gui->addLabel("CUSTOM WIDGETS");
    gui->addSpacer(); 
    gui->addFPS();
    
    gui->addLabel("NUMBER DIALER"); 
    gui->addNumberDialer("NDIALER", -99999.0000, 99999.0000, 100.0, 4);

    gui->addSpacer(); 
    gui->addLabel("TEXT INPUT"); 
    gui->addTextInput("Text Input Large", "LARGE TEXTINPUT", OFX_UI_FONT_LARGE);
    gui->addTextInput("Text Input Medium", "MEDIUM TEXTINPUT", OFX_UI_FONT_MEDIUM);
    gui->addTextInput("Text Input Small", "SMALL TEXTINPUT", OFX_UI_FONT_SMALL);
    gui->addTextInput("Text Input Autoclear", "Auto Clear Disabled", OFX_UI_FONT_SMALL)->setAutoClear(false);

    gui->addSpacer(); 
    buffer = new float[256];     
    for(int i = 0; i < 256; i++) { buffer[i] = ofNoise(i/100.0); }
    
	gui->addLabel("WAVEFORM GRAPH");     
	gui->addWaveform("WAVEFORM", buffer, 256, 0.0, 1.0); 
    gui->addLabel("SPECTRUM GRAPH");        
    gui->addSpectrum("SPECTRUM", buffer, 256, 0.0, 1.0);

    gui->addSpacer();
    img = new ofImage(); 
    img->loadImage("of1.jpg"); 
    img2 = new ofImage(); 
    img2->loadImage("of2.jpg");     
    
    float dim = (gui->getGlobalCanvasWidth() - gui->getPadding()*7.0)*0.5;
    gui->addLabel("IMAGE DISPLAY");
    gui->addImage("OF LOGO 1", img, dim, dim);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    bgColor = &gui->addImageSampler("OF LOGO 2", img2, dim, dim)->getColor();
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    gui->addSpacer();
    

    gui->addSpacer();
    gui->addLabel("DROP DOWN LIST");
    
    vector<string> items;
    items.push_back("FIRST");
    items.push_back("SECOND");
    items.push_back("THIRD");
    items.push_back("FOURTH");

    vector<string> items2;
    items2.push_back("FIFTH");
    items2.push_back("SIXTH");
    items2.push_back("SEVENTH");
    items2.push_back("EIGTHTH");
    
    gui->addDropDownList("DDL", items, dim);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui->addDropDownList("MULTIPLE", items2, dim)->setAllowMultiple(true);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);

    ofAddListener(gui->newGUIEvent,this,&ofApp::guiEvent);
    
    gui->autoSizeToFitWidgets();
    gui->loadSettings("settings.xml");
    
    ofBackground(*bgColor);
}

//--------------------------------------------------------------
void ofApp::update()
{
    for(int i = 0; i < 256; i++) { buffer[i] = ofNoise(i/100.0, ofGetElapsedTimef()); }
}

//--------------------------------------------------------------
void ofApp::draw()
{    
   ofBackground(*bgColor);
}
//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
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
void ofApp::exit()
{
    gui->saveSettings("settings.xml");
    delete gui;
	delete[] buffer;     
    delete img; 
    delete img2;     
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
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