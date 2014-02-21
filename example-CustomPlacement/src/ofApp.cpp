#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 
    
    red = 233; blue = 27; green = 52; 
	
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320-xInit; 
	
    drawPadding = false; 
    
    gui = new ofxUICanvas(); 
    gui->setDrawBack(false); 
    
    gui->addWidgetDown(new ofxUILabel("CUSTOM WIDGET LAYOUT", OFX_UI_FONT_LARGE), OFX_UI_ALIGN_RIGHT);
    
    gui->addWidget(new ofxUILabel(360, 300, "2D PAD", OFX_UI_FONT_MEDIUM)); 				
    gui->addWidgetSouthOf(new ofxUI2DPad("PAD", ofPoint(0, 320), ofPoint(0, 190), ofPoint(320*.5,190*.5), 320, 190), "2D PAD");
    gui->addWidgetWestOf(new ofxUITextInput("TEXT INPUT", "Input Text", 320, dim, 0, 0, OFX_UI_FONT_MEDIUM), "PAD");
    gui->addWidgetEastOf(new ofxUISlider("0", 0.0, 255.0, 150, dim, 190), "PAD");
    gui->addWidgetNorthOf(new ofxUIToggle("D_GRID", false, dim, dim), "2D PAD");
    gui->addWidgetWestOf(new ofxUIToggle("D2", true, dim, dim), "D_GRID");
    gui->addWidgetNorthOf(new ofxUISlider("GREEN", 0.0, 255.0, &green, 320, dim), "D2");
    gui->addWidgetNorthOf(new ofxUISlider("BLUE", 0.0, 255.0, &blue, 320, dim), "GREEN");
    gui->addWidgetLeft(new ofxUIToggle("NEW", true, dim, dim));
    
    gui->addWidgetSouthOf(new ofxUISlider("RED", 0.0, 255.0, &red, 320, dim), "PAD");
    gui->autoSizeToFitWidgets(); 
    ofAddListener(gui->newGUIEvent,this,&ofApp::guiEvent);	
	ofBackground(red, green, blue); 
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{    
	ofBackground(red, green, blue, 255); 
	
	ofPushStyle(); 
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);     
	ofPopStyle(); 
}
//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	
	if(name == "RED")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		red = slider->getScaledValue(); 
        cout << "value: " << slider->getScaledValue() << endl; 
	}
	else if(name == "GREEN")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		green = slider->getScaledValue(); 
        cout << "value: " << slider->getScaledValue() << endl; 
	}	
	else if(name == "BLUE")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		blue = slider->getScaledValue(); 		
        cout << "value: " << slider->getScaledValue() << endl;         
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