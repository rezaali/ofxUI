#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 
    
    //set some sketch parameters

    drawPadding = false;     
    backgroundColor = ofColor(233, 52, 27); 
        	
    gui = new ofxUICanvas();
    gui->setGlobalCanvasWidth(320);
    
    gui->setFont("GUI/faucet.ttf");                     //This loads a new font and sets the GUI font
    gui->setFontSize(OFX_UI_FONT_LARGE, 18);            //These call are optional, but if you want to resize the LARGE, MEDIUM, and SMALL fonts, here is how to do it. 
    gui->setFontSize(OFX_UI_FONT_MEDIUM, 14);           
    gui->setFontSize(OFX_UI_FONT_SMALL, 10);            //SUPER IMPORTANT NOTE: CALL THESE FUNTIONS BEFORE ADDING ANY WIDGETS, THIS AFFECTS THE SPACING OF THE GUI
    
    gui->addLabel("CUSTOM FONT", OFX_UI_FONT_LARGE);

    gui->addSpacer();
    gui->addLabel("BACKGROUND CONTROL");
    gui->addSlider("BGR", 0, 255, backgroundColor.r);
    gui->addSlider("BGR", 0, 255, backgroundColor.g);
    gui->addSlider("BGR", 0, 255, backgroundColor.b);
    
    gui->addSpacer();
    gui->addLabelToggle("DRAW PADDING", drawPadding);
    gui->addLabelToggle("SPACER COLOR", true);
    
    gui->addSpacer();
    gui->addLabel("HIDE & SHOW GUI", OFX_UI_FONT_MEDIUM);
    gui->addLabel("BY PRESSING 'g'", OFX_UI_FONT_MEDIUM);

    gui->autoSizeToFitWidgets(); 
    ofAddListener(gui->newGUIEvent,this,&ofApp::guiEvent);	
	ofBackground(backgroundColor); 
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{    	
	ofBackground(backgroundColor);     
	ofPushStyle(); 
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);     
    
	ofPopStyle(); 
}
//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	
    if(name == "BGR")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget; 
		backgroundColor.r = rslider->getScaledValue(); 		
	}    
	else if(name == "BGG")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget; 
		backgroundColor.g = rslider->getScaledValue(); 		
	}    
	else if(name == "BGB")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget; 
		backgroundColor.b = rslider->getScaledValue(); 		
	}    
    else if(name == "DRAW PADDING")
    {
        ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget; 
        drawPadding = toggle->getValue();     
        gui->setDrawWidgetPadding(drawPadding);             
    }    
    else if(name == "SPACER COLOR")
    {
        ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget;         
        
        vector<ofxUIWidget*> spacers = gui->getWidgetsOfType(OFX_UI_WIDGET_SPACER); 

        for(int i = 0; i < spacers.size(); i++)        
        {
            ofxUISpacer *spacer = (ofxUISpacer *) spacers[i]; 
            spacer->setToggleColor(toggle->getValue()); 
        }
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