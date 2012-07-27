#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 
    
    //set some sketch parameters
    //Background Color 
    red = 233; 
    blue = 240; 
    green = 52; 
    alpha = 200; 
    radius = 150; 
    drawFill = true;     
    bgRed = 233;
    bgGreen = 52; 
    bgBlue = 27; 
    resolution = 30; 
    position = ofPoint(ofGetWidth()*.5, ofGetHeight()*.5); 
    ofSetCircleResolution(resolution); 
        
    float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320-xInit; 
	
    gui = new ofxUICanvas(0,0,length+xInit*2.0,ofGetHeight());     
	gui->addWidgetDown(new ofxUILabel("VARIABLE BINDING EXAMPLE", OFX_UI_FONT_LARGE)); 

    gui->addWidgetDown(new ofxUISpacer(length, 2)); 
    gui->addWidgetDown(new ofxUILabel("BACKGROUND CONTROL", OFX_UI_FONT_MEDIUM));     
    gui->addWidgetDown(new ofxUISlider(95, dim, 0, 255, &bgRed, "BGR")); 
    gui->addWidgetRight(new ofxUISlider(95, dim, 0, 255, &bgGreen, "BGG")); 
    gui->addWidgetRight(new ofxUISlider(95, dim, 0, 255, &bgBlue, "BGB"));     
    
    gui->addWidgetDown(new ofxUISpacer(length, 2)); 

    gui->addWidgetDown(new ofxUILabel("CIRCLE CONTROL", OFX_UI_FONT_MEDIUM));     
    gui->addWidgetDown(new ofxUISlider(length,dim, 0.0, 255.0, &red, "RED")); 
	gui->addWidgetDown(new ofxUISlider(length,dim, 0.0, 255.0, &green, "GREEN")); 
    gui->addWidgetDown(new ofxUISlider(length,dim, 0.0, 255.0, &blue, "BLUE")); 	    
    gui->addWidgetDown(new ofxUISlider(length,dim, 0.0, 255.0, &alpha, "ALPHA")); 	        
    gui->addWidgetDown(new ofxUISlider(length,dim, 0.0, 600.0, &radius, "RADIUS")); 
	gui->addWidgetDown(new ofxUISlider(length,dim, 3, 60, &resolution, "RESOLUTION")); 
    gui->addWidgetDown(new ofxUILabelToggle(dim, dim, &drawFill, "DRAW FILL", OFX_UI_FONT_MEDIUM)); 
    
    float padWidth = length; 
    float padHeight = length*((float)ofGetHeight()/(float)ofGetWidth()); 
    
    gui->addWidgetDown(new ofxUI2DPad(padWidth, padHeight, ofPoint(0, ofGetWidth()), ofPoint(0, ofGetHeight()), &position, "POSITION")); 

    gui->addWidgetDown(new ofxUISpacer(length, 2)); 
    gui->addWidgetDown(new ofxUILabel("HIDE & SHOW GUI BY PRESSING 'g'", OFX_UI_FONT_MEDIUM));     
    gui->addWidgetDown(new ofxUILabel("MOUSE OVER A SLIDER AND", OFX_UI_FONT_MEDIUM));         
    gui->addWidgetDown(new ofxUILabel("PRESS UP, DOWN, LEFT, RIGHT", OFX_UI_FONT_MEDIUM));                 
    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);	    
}

//--------------------------------------------------------------
void testApp::update()
{

}

//--------------------------------------------------------------
void testApp::draw()
{    	
	ofBackground(bgRed, bgGreen, bgBlue);     
	ofPushStyle(); 
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);     
    
    ofSetColor(red, green, blue, alpha); 
    if(drawFill)
    {
        ofFill(); 
    }
    else
    {
        ofNoFill(); 
    }
    ofCircle(position.x,position.y, radius); 
    
    
	ofPopStyle(); 
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{

	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	
    if(name == "RESOLUTION")
    {
        ofSetCircleResolution(resolution); 
    }    
    /*     
	if(name == "RED")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		red = slider->getScaledValue(); 
	}
	else if(name == "GREEN")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		green = slider->getScaledValue(); 
	}	
	else if(name == "BLUE")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		blue = slider->getScaledValue(); 		
	}
	else if(name == "BGR")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget; 
		bgRed = rslider->getScaledValue(); 		
	}    
	else if(name == "BGG")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget; 
		bgGreen = rslider->getScaledValue(); 		
	}    
	else if(name == "BGB")
	{
		ofxUISlider *rslider = (ofxUISlider *) e.widget; 
		bgBlue = rslider->getScaledValue(); 		
	}    
	else if(name == "ALPHA")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		alpha = slider->getScaledValue(); 		
	}
	else if(name == "RADIUS")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		radius = slider->getScaledValue(); 		
	}
    else if(name == "POSITION")
	{
		ofxUI2DPad *pad = (ofxUI2DPad *) e.widget; 
		position.x = pad->getPercentValue().x*ofGetWidth(); 
		position.y = pad->getPercentValue().y*ofGetHeight(); 
	}    
    else if(name == "DRAW FILL")
    {
        ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget; 
        drawFill = toggle->getValue();     
    }    
    */
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