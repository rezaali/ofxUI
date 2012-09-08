#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{ 
//	ofEnableSmoothing(); 
	ofBackground(0); 
	
	setGUI1(); 
	setGUI2(); 
    setGUI3(); 
	ofBackground(red, green, blue); 
    gui1->loadSettings("GUI/guiSettings.xml"); 
    gui2->loadSettings("GUI/guiSettings2.xml"); 
    gui3->loadSettings("GUI/guiSettings3.xml");     
    
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


	if(bdrawGrid)
	{
		ofSetColor(255, 255, 255, 25);	
		drawGrid(8,8); 
	}
    
	ofPopStyle(); 
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	cout << "got event from: " << name << endl; 	
	
	if(name == "RED")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		cout << "RED " << slider->getScaledValue() << endl; 
		red = slider->getScaledValue(); 
	}
	else if(name == "GREEN")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		cout << "GREEN " << slider->getScaledValue() << endl; 
		green = slider->getScaledValue(); 
	}
	
	else if(name == "BLUE")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		cout << "BLUE " << slider->getScaledValue() << endl; 
		blue = slider->getScaledValue(); 		
	}
	else if(name == "DRAW GRID")
	{
		ofxUIButton *button = (ofxUIButton *) e.widget; 
		bdrawGrid = button->getValue(); 
	}
	else if(name == "D_GRID")
	{
		ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
		bdrawGrid = toggle->getValue(); 
	}
    else if(name == "TEXT INPUT")
    {
        ofxUITextInput *textinput = (ofxUITextInput *) e.widget; 
        if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
            cout << "ON ENTER: "; 
//            ofUnregisterKeyEvents((testApp*)this); 
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
        {
            cout << "ON FOCUS: "; 
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
        {
            cout << "ON BLUR: "; 
//            ofRegisterKeyEvents(this);             
        }        
        string output = textinput->getTextString(); 
        cout << output << endl; 
    }
	
	
	
}
//--------------------------------------------------------------
void testApp::exit()
{
    gui1->saveSettings("GUI/guiSettings.xml"); 
    gui2->saveSettings("GUI/guiSettings2.xml"); 
    gui3->saveSettings("GUI/guiSettings3.xml");     
	delete gui1; 
	delete gui2; 
    delete gui3; 
	delete[] buffer; 
    delete img; 
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    if(gui2->hasKeyboardFocus())
    {
        return;  
    }
	switch (key) 
	{			
		case '`':
		{
			string hr;         
			ofImage img; 
			img.grabScreen(0,0,ofGetWidth(), ofGetHeight()); 
			if(ofGetHours() < 12)
			{
				hr = " AM"; 
			}
			else
			{
				hr = " PM"; 
			}
			img.saveImage("snapshots/OFXUI "+ofToString(ofGetYear())+"-"+ofToString(ofGetMonth())+"-"+ofToString(ofGetDay())+" at "+ofToString(ofGetHours(),2)+"."+ofToString(ofGetMinutes(),2)+"."+ofToString(ofGetSeconds(),2) +hr +".png");
		}						
			break; 
			
		case 'f':
			ofToggleFullscreen(); 
			break;

		case 'h':
            gui1->toggleVisible(); 
            gui2->toggleVisible(); 
            gui3->toggleVisible();             
			break;

		case 'p':
			bdrawPadding = !bdrawPadding; 
			gui1->setDrawWidgetPadding(bdrawPadding); 			
			gui2->setDrawWidgetPadding(bdrawPadding); 			
			gui3->setDrawWidgetPadding(bdrawPadding); 			            
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

void testApp::drawGrid(float x, float y)
{
    float w = ofGetWidth(); 
    float h = ofGetHeight(); 
    
    for(int i = 0; i < h; i+=y)
    {
        ofLine(0,i,w,i); 
    }
    
    for(int j = 0; j < w; j+=x)
    {
        ofLine(j,0,j,h); 
    }    
}

void testApp::setGUI1()
{
	red = 233; blue = 52; green = 27; 
	
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 255-xInit; 
	hideGUI = false; 
	
    vector<string> names; 
	names.push_back("RAD1");
	names.push_back("RAD2");
	names.push_back("RAD3");	

    vector<string> names2; 
	names2.push_back("RAD4");
	names2.push_back("RAD5");
	names2.push_back("RAD6");	
	
	gui1 = new ofxUICanvas(0, 0, length+xInit, ofGetHeight()); 
	gui1->addWidgetDown(new ofxUILabel("PANEL 1: BASICS", OFX_UI_FONT_LARGE)); 
    gui1->addWidgetDown(new ofxUILabel("Press 'h' to Hide GUIs", OFX_UI_FONT_LARGE)); 

    gui1->addSpacer(length-xInit, 2); 
	gui1->addWidgetDown(new ofxUILabel("H SLIDERS", OFX_UI_FONT_MEDIUM)); 
	gui1->addSlider("RED", 0.0, 255.0, red, length-xInit,dim);
	gui1->addSlider("GREEN", 0.0, 255.0, green, length-xInit,dim);
	gui1->addSlider("BLUE", 0.0, 255.0, blue, length-xInit,dim);

    gui1->addSpacer(length-xInit, 2); 
    gui1->addWidgetDown(new ofxUILabel("V SLIDERS", OFX_UI_FONT_MEDIUM)); 
	gui1->addSlider("0", 0.0, 255.0, 150, dim,160);
	gui1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	gui1->addSlider("1", 0.0, 255.0, 150, dim,160);
	gui1->addSlider("2", 0.0, 255.0, 150, dim,160);
	gui1->addSlider("3", 0.0, 255.0, 150, dim,160);
	gui1->addSlider("4", 0.0, 255.0, 150, dim,160);
	gui1->addSlider("5", 0.0, 255.0, 150, dim,160);
	gui1->addSlider("6", 0.0, 255.0, 150, dim,160);
	gui1->addSlider("7", 0.0, 255.0, 150, dim,160);
	gui1->addSlider("8", 0.0, 255.0, 150, dim,160);
	gui1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    gui1->addSpacer(length-xInit, 2);     
	gui1->addWidgetDown(new ofxUIRadio( dim, dim, "RADIO HORIZONTAL", names, OFX_UI_ORIENTATION_HORIZONTAL)); 
	gui1->addWidgetDown(new ofxUIRadio( dim, dim, "RADIO VERTICAL", names2, OFX_UI_ORIENTATION_VERTICAL)); 

    gui1->addSpacer(length-xInit, 2); 
	gui1->addWidgetDown(new ofxUILabel("BUTTONS", OFX_UI_FONT_MEDIUM)); 
	gui1->addWidgetDown(new ofxUIButton( dim, dim, false, "DRAW GRID")); 	
	gui1->addWidgetDown(new ofxUILabel("TOGGLES", OFX_UI_FONT_MEDIUM)); 
	gui1->addWidgetDown(new ofxUIToggle( dim, dim, false, "D_GRID")); 	
    
    gui1->addSpacer(length-xInit, 2); 
    gui1->addWidgetDown(new ofxUILabel("RANGE SLIDER", OFX_UI_FONT_MEDIUM)); 
	gui1->addWidgetDown(new ofxUIRangeSlider(length-xInit,dim, 0.0, 255.0, 50.0, 100.0, "RSLIDER")); 	

    gui1->addSpacer(length-xInit, 2); 
	gui1->addWidgetDown(new ofxUILabel("2D PAD", OFX_UI_FONT_MEDIUM)); 
	gui1->addWidgetDown(new ofxUI2DPad(length-xInit,120, ofPoint((length-xInit)*.5,120*.5), "PAD")); 	

    bdrawGrid = false; 
	bdrawPadding = false; 	
	ofAddListener(gui1->newGUIEvent,this,&testApp::guiEvent);
}

void testApp::setGUI2()
{	
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 255-xInit; 
    
    img = new ofImage(); 
    img->loadImage("nerd_me.png"); 
    buffer = new float[256];     
    for(int i = 0; i < 256; i++) { buffer[i] = ofNoise(i/100.0); }

    gui2 = new ofxUICanvas(length+xInit+2, 0, length+xInit, ofGetHeight());     
	gui2->addWidgetDown(new ofxUILabel("PANEL 2: ADVANCED", OFX_UI_FONT_LARGE)); 

    gui2->addSpacer(length-xInit, 2);         
	gui2->addWidgetDown(new ofxUILabel("TEXT INPUT", OFX_UI_FONT_MEDIUM));
	gui2->addWidgetDown(new ofxUITextInput(length-xInit, "TEXT INPUT", "Input Text", OFX_UI_FONT_LARGE)); 	

    gui2->addSpacer(length-xInit, 2);         
    gui2->addWidgetDown(new ofxUILabel("WAVEFORM DISPLAY", OFX_UI_FONT_MEDIUM));     
	gui2->addWidgetDown(new ofxUIWaveform(length-xInit, 64, buffer, 256, 0.0, 1.0, "WAVEFORM")); 
    gui2->addWidgetDown(new ofxUILabel("SPECTRUM DISPLAY", OFX_UI_FONT_MEDIUM));    
    gui2->addWidgetDown(new ofxUISpectrum(length-xInit, 64, buffer, 256, 0.0, 1.0, "SPECTRUM")); 

    gui2->addSpacer(length-xInit, 2);             
    gui2->addWidgetDown(new ofxUILabel("IMAGE DISPLAY", OFX_UI_FONT_MEDIUM));
	gui2->addWidgetDown(new ofxUIImage(img->width*.5, img->height*.5, img, "IMAGE CAPTION")); 

    gui2->addSpacer(length-xInit, 2);             
    gui2->addWidgetDown(new ofxUILabel("FPS LABEL", OFX_UI_FONT_MEDIUM));
    gui2->addWidgetDown(new ofxUIFPS(OFX_UI_FONT_MEDIUM)); 

    gui2->addSpacer(length-xInit, 2);             
    gui2->addWidgetDown(new ofxUILabel("NUMBER DIALER", OFX_UI_FONT_MEDIUM));
    gui2->addWidgetDown(new ofxUINumberDialer(-10000, 10000, 5000, 1, "NUMBER DIALER", OFX_UI_FONT_MEDIUM)); 

    gui2->addSpacer(length-xInit, 2);         
    gui2->addWidgetDown(new ofxUILabel("LABEL BUTTON", OFX_UI_FONT_MEDIUM));
    gui2->addLabelButton("LABEL BUTTON", false, length-xInit);
    gui2->addLabelButton("AUTOSIZE BUTTON", false, length-xInit);
    gui2->addLabelButton("MEDIUM BUTTON", false, length-xInit);
    
    gui2->addSpacer(length-xInit, 2);             
    gui2->addLabel("LABEL TOGGLES");	
    gui2->addLabelToggle("LABEL TOGGLE", false, length-xInit);     

    gui2->addLabelToggle("AUTOSIZE TOGGLE", false);
    
	ofAddListener(gui2->newGUIEvent,this,&testApp::guiEvent);
}

void testApp::setGUI3()
{	
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 255-xInit; 
	gui3 = new ofxUICanvas(length*2+xInit*2+4, 0, length+xInit, ofGetHeight());     
    gui3->addWidgetDown(new ofxUILabel("PANEL 3: ADVANCED", OFX_UI_FONT_LARGE)); 	

    gui3->addSpacer(length-xInit, 2);             
    gui3->addWidgetDown(new ofxUILabel("MATRIX", OFX_UI_FONT_MEDIUM)); 				
    gui3->addWidgetDown(new ofxUIToggleMatrix(dim, dim, 4, 4, "MATRIX1")); 
    gui3->addWidgetDown(new ofxUIToggleMatrix(dim*2.0, dim*2.0, 3, 6, "MATRIX2")); 
    gui3->addWidgetDown(new ofxUIToggleMatrix(dim*3.0, dim*3.0, 1, 4, "MATRIX3")); 

    gui3->addSpacer(length-xInit, 2);             
    gui3->addWidgetDown(new ofxUILabel("IMAGE BUTTON", OFX_UI_FONT_MEDIUM)); 				    
    gui3->addWidgetDown(new ofxUIImageButton(dim*4.0, dim*4.0, false, "GUI/images/App.png","IMAGEBTN")); 
    gui3->addWidgetDown(new ofxUILabel("IMAGE TOGGLE", OFX_UI_FONT_MEDIUM)); 				        
    gui3->addWidgetDown(new ofxUIImageToggle(dim*4.0, dim*4.0, false, "GUI/images/Preview.png","IMAGETGL")); 

    gui3->addSpacer(length-xInit, 2);                 
    gui3->addWidgetDown(new ofxUILabel("ROTARY SLIDER", OFX_UI_FONT_MEDIUM)); 			
    gui3->addWidgetDown(new ofxUIRotarySlider(dim*4, 0, 100, 50, "R2SLIDER")); 			
    gui3->addSpacer(length-xInit, 2);             
    gui3->addWidgetDown(new ofxUILabel("DROP DOWN", OFX_UI_FONT_MEDIUM)); 				
        
    vector<string> items; 
    items.push_back("FIRST ITEM"); 
    items.push_back("SECOND ITEM"); 
    items.push_back("THIRD ITEM WHATS UP DOG"); 
    items.push_back("FOURTH ITEM"); 
    items.push_back("FIFTH ITEM"); 
    items.push_back("SIXTH ITEM");     
    
    gui3->addWidgetDown(new ofxUIDropDownList(200, "DROP DOWN LIST", items, OFX_UI_FONT_MEDIUM)); 

	ofAddListener(gui3->newGUIEvent,this,&testApp::guiEvent);
}