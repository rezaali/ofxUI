#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofEnableTextureEdgeHack();
//    middle.loadImage("sliderhandle.png");
    middle.loadImage("slidertrack.png");
    middle.getTextureReference().setTextureWrap(GL_REPEAT, GL_REPEAT);
    middle.update();
    
	ofEnableSmoothing(); 
    ofSetCircleResolution(60);
    
    red = 100; blue = 100; green = 100;
	
	float dim = 24; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320-xInit; 
	
    drawPadding = false; 
    
    gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
	
    gui->addWidgetDown(new ofxUILabel("SLIDER WIDGETS", OFX_UI_FONT_LARGE));         
    gui->addSpacer(length-xInit, 1); 
    gui->addFPSSlider("FPS SLIDER", length-xInit, dim*.25, 1000);
    gui->addSpacer(length-xInit, 1); 
	gui->addWidgetDown(new ofxUILabel("NORMAL SLIDER", OFX_UI_FONT_MEDIUM)); 	
    gui->addSlider("RED", 0.0, 255.0, red, length-xInit,dim);
    gui->addSpacer(length-xInit, 1); 
	gui->addWidgetDown(new ofxUILabel("MINIMAL SLIDER", OFX_UI_FONT_MEDIUM)); 	
    gui->addWidgetDown(new ofxUIMinimalSlider(length-xInit, 0.0, 255.0, green, "GREEN", OFX_UI_FONT_MEDIUM));
    gui->addSpacer(length-xInit, 1); 
	gui->addWidgetDown(new ofxUILabel("BILABEL SLIDER", OFX_UI_FONT_MEDIUM)); 	    
    gui->addWidgetDown(new ofxUIBiLabelSlider(length-xInit, 0.0, 255.0, blue, "BLUE", "LESS BLUE", "MORE BLUE", OFX_UI_FONT_MEDIUM));
    gui->addSpacer(length-xInit, 1); 
    gui->addWidgetDown(new ofxUILabel("VERTICAL SLIDERS", OFX_UI_FONT_MEDIUM));     
    gui->addSlider("1", 0.0, 255.0, 100.0, dim,80);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	gui->addSlider("2", 0.0, 255.0, 150.0, dim, 80);
	gui->addSlider("3", 0.0, 255.0, 200.0, dim, 80);
	gui->addSlider("4", 0.0, 255.0, 250.0, dim, 80);
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    gui->addSpacer(length-xInit, 1);     
    gui->addWidgetDown(new ofxUILabel("RANGE SLIDER", OFX_UI_FONT_MEDIUM)); 
	gui->addWidgetDown(new ofxUIRangeSlider(length-xInit,dim, 0.0, 255.0, 50.0, 100.0, "RSLIDER")); 
    gui->addSpacer(length-xInit, 1); 
	gui->addWidgetDown(new ofxUILabel("ROTARY SLIDER", OFX_UI_FONT_MEDIUM));
    gui->addWidgetDown(new ofxUIRotarySlider(dim*2.0, 0.0, 100.0, 25.0, "CSLIDER 2")); 
    gui->addSpacer(length-xInit, 1);     
	gui->addWidgetDown(new ofxUILabel("2D PAD", OFX_UI_FONT_MEDIUM)); 
	gui->addWidgetDown(new ofxUI2DPad(length-xInit,80, ofPoint((length-xInit)*.5,80*.5), "PAD")); 	
    gui->addSpacer(length-xInit, 1);     
	gui->addWidgetDown(new ofxUILabel("CIRCLE SLIDER", OFX_UI_FONT_MEDIUM)); 
	gui->addWidgetDown(new ofxUICircleSlider(dim*2, 0.0, 255.0, green, "GREEN", OFX_UI_FONT_MEDIUM));
    gui->addSpacer(length-xInit, 1);     
	gui->addWidgetDown(new ofxUILabel("IMAGE SLIDER", OFX_UI_FONT_MEDIUM)); 
    gui->addWidgetDown(new ofxUIImageSlider(length-xInit, 42, 0.0, 255.0, red, "slider.png", "IMAGE SLIDER"));
    gui->setColorBack(ofColor(255,100));
    
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

    
    ofSetColor(255);
    middle.getTextureReference().drawSubsection(ofGetWidth()*.5, ofGetHeight()*.5, middle.getWidth()*10, middle.getHeight(), middle.getWidth(),0,1,middle.getHeight());
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
//	gui->getRect()->setHeight(y);
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