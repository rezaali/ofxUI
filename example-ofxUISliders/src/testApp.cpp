#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofEnableSmoothing(); 
    ofSetCircleResolution(60);
    
    red = 233; blue = 27; green = 52; 
	
	float dim = 24; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320-xInit; 
	
    drawPadding = false; 
    
    gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
	
    gui->addWidgetDown(new ofxUILabel("SLIDER WIDGETS", OFX_UI_FONT_LARGE));         
    gui->addWidgetDown(new ofxUISpacer(length-xInit, 1)); 
    gui->addWidgetDown(new ofxUIFPSSlider(length-xInit, dim, 0, 1000, 60.0, "FPS SLIDER"));
    gui->addWidgetDown(new ofxUISpacer(length-xInit, 1)); 
	gui->addWidgetDown(new ofxUILabel("NORMAL SLIDER", OFX_UI_FONT_MEDIUM)); 	
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 255.0, red, "RED")); 
    gui->addWidgetDown(new ofxUISpacer(length-xInit, 1)); 
	gui->addWidgetDown(new ofxUILabel("MINIMAL SLIDER", OFX_UI_FONT_MEDIUM)); 	
    gui->addWidgetDown(new ofxUIMinimalSlider(length-xInit, 0.0, 255.0, green, "GREEN", OFX_UI_FONT_MEDIUM));
    gui->addWidgetDown(new ofxUISpacer(length-xInit, 1)); 
	gui->addWidgetDown(new ofxUILabel("BILABEL SLIDER", OFX_UI_FONT_MEDIUM)); 	    
    gui->addWidgetDown(new ofxUIBiLabelSlider(length-xInit, 0.0, 255.0, blue, "BLUE", "LESS BLUE", "MORE BLUE", OFX_UI_FONT_MEDIUM));
    gui->addWidgetDown(new ofxUISpacer(length-xInit, 1)); 
    gui->addWidgetDown(new ofxUILabel("VERTICAL SLIDERS", OFX_UI_FONT_MEDIUM));     
    gui->addWidgetDown(new ofxUISlider(dim,80, 0.0, 255.0, 100, "1")); 	
	gui->addWidgetRight(new ofxUISlider(dim,80, 0.0, 255.0, 150, "2")); 
	gui->addWidgetRight(new ofxUISlider(dim,80, 0.0, 255.0, 200, "3")); 
	gui->addWidgetRight(new ofxUIRangeSlider(dim, 80, 0, 255.0, 100.0, 200.0, "4")); 
    gui->addWidgetDown(new ofxUISpacer(length-xInit, 1));     
    gui->addWidgetDown(new ofxUILabel("RANGE SLIDER", OFX_UI_FONT_MEDIUM)); 
	gui->addWidgetDown(new ofxUIRangeSlider(length-xInit,dim, 0.0, 255.0, 50.0, 100.0, "RSLIDER")); 
    gui->addWidgetDown(new ofxUISpacer(length-xInit, 1)); 
	gui->addWidgetDown(new ofxUILabel("ROTARY SLIDER", OFX_UI_FONT_MEDIUM));
    gui->addWidgetDown(new ofxUIRotarySlider(dim*2.0, 0.0, 100.0, 25.0, "CSLIDER 2")); 
    gui->addWidgetDown(new ofxUISpacer(length-xInit, 1));     
	gui->addWidgetDown(new ofxUILabel("2D PAD", OFX_UI_FONT_MEDIUM)); 
	gui->addWidgetDown(new ofxUI2DPad(length-xInit,80, ofPoint((length-xInit)*.5,80*.5), "PAD")); 	
    gui->addWidgetDown(new ofxUISpacer(length-xInit, 1));     
	gui->addWidgetDown(new ofxUILabel("CIRCLE SLIDER", OFX_UI_FONT_MEDIUM)); 
	gui->addWidgetDown(new ofxUICircleSlider(dim*5, 0.0, 255.0, green, "GREEN", OFX_UI_FONT_MEDIUM));

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
	
	if(name == "RED")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		red = slider->getScaledValue(); 
        cout << "value: " << slider->getScaledValue() << endl; 
	}
	else if(name == "GREEN")
	{
		ofxUIMinimalSlider *slider = (ofxUIMinimalSlider *) e.widget; 
		green = slider->getScaledValue(); 
        cout << "value: " << slider->getScaledValue() << endl; 
	}	
	else if(name == "BLUE")
	{
		ofxUIBiLabelSlider *slider = (ofxUIBiLabelSlider *) e.widget; 
		blue = slider->getScaledValue(); 		
        cout << "value: " << slider->getScaledValue() << endl;         
	}  
    else if(name == "RSLIDER")
    {
        ofxUIRangeSlider *rslider = (ofxUIRangeSlider *) e.widget; 
        cout << "valuelow: " << rslider->getScaledValueLow() << endl; 
        cout << "valuehigh: " << rslider->getScaledValueHigh() << endl;   
    }
    else if(name == "PAD")
    {
        ofxUI2DPad *pad = (ofxUI2DPad *) e.widget; 
        cout << "value x: " << pad->getScaledValue().x << endl; 
        cout << "value y: " << pad->getScaledValue().y << endl;         
    }
    else if(name == "CSLIDER" || name == "CSLIDER 2")
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