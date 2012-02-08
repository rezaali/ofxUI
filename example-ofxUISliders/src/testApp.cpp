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
    
	gui->addWidgetDown(new ofxUILabel("SLIDER WIDGETS", OFX_UI_FONT_LARGE)); 
    gui->addWidgetDown(new ofxUISpacer(length-xInit, 2)); 
	gui->addWidgetDown(new ofxUILabel("HORIZONTAL SLIDERS", OFX_UI_FONT_MEDIUM)); 	
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 255.0, red, "RED")); 
	gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 255.0, green, "GREEN")); 
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 255.0, blue, "BLUE")); 	
    gui->addWidgetDown(new ofxUISpacer(length-xInit, 2)); 
    gui->addWidgetDown(new ofxUILabel("VERTICAL SLIDERS", OFX_UI_FONT_MEDIUM));     
    gui->addWidgetDown(new ofxUISlider(dim,160, 0.0, 255.0, 100, "1")); 	
	gui->addWidgetRight(new ofxUISlider(dim,160, 0.0, 255.0, 150, "2")); 
	gui->addWidgetRight(new ofxUISlider(dim,160, 0.0, 255.0, 200, "3")); 
	gui->addWidgetRight(new ofxUIRangeSlider(dim, 160, 0, 255.0, 100.0, 200.0, "4")); 
    gui->addWidgetDown(new ofxUISpacer(length-xInit, 2)); 
    gui->addWidgetDown(new ofxUILabel("RANGE SLIDER", OFX_UI_FONT_MEDIUM)); 
	gui->addWidgetDown(new ofxUIRangeSlider(length-xInit,dim, 0.0, 255.0, 50.0, 100.0, "RSLIDER")); 
    gui->addWidgetDown(new ofxUISpacer(length-xInit, 2)); 
	gui->addWidgetDown(new ofxUILabel("ROTARY SLIDER", OFX_UI_FONT_MEDIUM));
	gui->addWidgetDown(new ofxUIRotarySlider(dim*4.0, -100.0, 100.0, 0.0, "CSLIDER")); 
    gui->addWidgetDown(new ofxUIRotarySlider(dim*8.0, 0.0, 100.0, 25.0, "CSLIDER 2")); 
    gui->addWidgetDown(new ofxUISpacer(length-xInit, 2));     
	gui->addWidgetDown(new ofxUILabel("2D PAD", OFX_UI_FONT_MEDIUM)); 
	gui->addWidgetDown(new ofxUI2DPad(length-xInit,160, ofPoint((length-xInit)*.5,190*.5), "PAD")); 	

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
	
	if(!name.compare("RED"))
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		red = slider->getScaledValue(); 
        cout << "value: " << slider->getScaledValue() << endl; 
	}
	else if(!name.compare("GREEN"))
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		green = slider->getScaledValue(); 
        cout << "value: " << slider->getScaledValue() << endl; 
	}	
	else if(!name.compare("BLUE"))
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		blue = slider->getScaledValue(); 		
        cout << "value: " << slider->getScaledValue() << endl;         
	}
	else if(!name.compare("BLUE"))
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		blue = slider->getScaledValue(); 		
        cout << "value: " << slider->getScaledValue() << endl;         
	}    
    else if(!name.compare("RSLIDER"))
    {
        ofxUIRangeSlider *rslider = (ofxUIRangeSlider *) e.widget; 
        cout << "valuelow: " << rslider->getScaledValueLow() << endl; 
        cout << "valuehigh: " << rslider->getScaledValueHigh() << endl;   
    }
    else if(!name.compare("PAD"))
    {
        ofxUI2DPad *pad = (ofxUI2DPad *) e.widget; 
        cout << "value x: " << pad->getScaledValue().x << endl; 
        cout << "value y: " << pad->getScaledValue().y << endl;         
    }
    else if(!name.compare("CSLIDER") || !name.compare("CSLIDER 2"))
    {
        ofxUIRotarySlider *rotslider = (ofxUIRotarySlider *) e.widget; 
        cout << "value: " << rotslider->getScaledValue() << endl; 
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
            gui->setDrawPadding(drawPadding);          
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