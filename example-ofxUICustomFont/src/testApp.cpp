#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 
    
    //set some sketch parameters

    drawPadding = false;     
    backgroundColor = ofColor(233, 52, 27); 
        
    float dim = 32; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320-xInit; 
	
    gui = new ofxUICanvas(); 

    gui->setFont("GUI/faucet.ttf");                     //This loads a new font and sets the GUI font
    gui->setFontSize(OFX_UI_FONT_LARGE, 18);            //These call are optional, but if you want to resize the LARGE, MEDIUM, and SMALL fonts, here is how to do it. 
    gui->setFontSize(OFX_UI_FONT_MEDIUM, 14);           
    gui->setFontSize(OFX_UI_FONT_SMALL, 10);            //SUPER IMPORTANT NOTE: CALL THESE FUNTIONS BEFORE ADDING ANY WIDGETS, THIS AFFECTS THE SPACING OF THE GUI
    
    gui->addWidgetDown(new ofxUILabel("CUSTOM FONT", OFX_UI_FONT_LARGE)); 

    gui->addSpacer(length-xInit, 2);
    gui->addWidgetDown(new ofxUILabel("BACKGROUND CONTROL", OFX_UI_FONT_MEDIUM));     
    gui->addSlider("BGR", 0, 255, backgroundColor.r, length-xInit, dim);
    gui->addSlider("BGR", 0, 255, backgroundColor.g, length-xInit, dim); 
    gui->addSlider("BGR", 0, 255, backgroundColor.b, length-xInit, dim);
    
    gui->addSpacer(length-xInit, 2);
    gui->addWidgetDown(new ofxUILabelToggle(drawPadding, "DRAW PADDING", OFX_UI_FONT_MEDIUM)); 
    gui->addWidgetDown(new ofxUILabelToggle(true, "SPACER COLOR", OFX_UI_FONT_MEDIUM));     
    
    gui->addSpacer(length-xInit, 2);
    gui->addWidgetDown(new ofxUILabel("HIDE & SHOW GUI", OFX_UI_FONT_MEDIUM));     
    gui->addWidgetDown(new ofxUILabel("BY PRESSING 'g'", OFX_UI_FONT_MEDIUM));     

    gui->autoSizeToFitWidgets(); 
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);	
	ofBackground(backgroundColor); 
}

//--------------------------------------------------------------
void testApp::update()
{

}

//--------------------------------------------------------------
void testApp::draw()
{    	
	ofBackground(backgroundColor);     
	ofPushStyle(); 
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);     
    
	ofPopStyle(); 
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
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
void testApp::exit()
{
    delete gui; 
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
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