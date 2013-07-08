#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    int tabBarWidth = 80;
    
    // ---
    guiTabBar = new ofxUITabBar();
    guiTabBar->setWidth(tabBarWidth);
    guiTabBar->setColorFill(ofxUIColor(200));
    guiTabBar->setColorFillHighlight(ofxUIColor(255));
    guiTabBar->setColorBack(ofxUIColor(255, 20, 20, 150));
    
    // ---
    ofEnableTextureEdgeHack();
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
    
    // ---
    ofxUICanvas* guiA = new ofxUICanvas(tabBarWidth, 0, length+xInit, 100);
    guiA->setName("Main");
    guiA->setPosition(tabBarWidth, 0);
    guiA->setColorFill(ofxUIColor(200));
    guiA->setColorFillHighlight(ofxUIColor(255));
    guiA->setColorBack(ofxUIColor(20, 20, 20, 150));
    {
        guiA->addLabel("Tab Bar");
        guiA->addSpacer();
        guiA->addButton("SAVE", false);
        guiA->addButton("LOAD", false);
    }
    
    ofAddListener(guiA->newGUIEvent,this,&testApp::guiEvent);
    guiTabBar->addCanvas(guiA);
    
    // ---
    guiB = new ofxUICanvas(tabBarWidth, 0, length+xInit, ofGetHeight());
	guiB->setName("Tab 2");
    guiB->addWidgetDown(new ofxUILabel("SLIDER WIDGETS", OFX_UI_FONT_LARGE));         
    guiB->addSpacer(length-xInit, 1); 
    guiB->addFPSSlider("FPS SLIDER", length-xInit, dim*.25, 1000);
    guiB->addSpacer(length-xInit, 1); 
	guiB->addWidgetDown(new ofxUILabel("NORMAL SLIDER", OFX_UI_FONT_MEDIUM)); 	
    guiB->addSlider("RED", 0.0, 255.0, red, length-xInit,dim);
    guiB->addSpacer(length-xInit, 1); 
	guiB->addWidgetDown(new ofxUILabel("MINIMAL SLIDER", OFX_UI_FONT_MEDIUM)); 	
    guiB->addWidgetDown(new ofxUIMinimalSlider(length-xInit, 0.0, 255.0, green, "GREEN", OFX_UI_FONT_MEDIUM));
    guiB->addSpacer(length-xInit, 1); 
	guiB->addWidgetDown(new ofxUILabel("BILABEL SLIDER", OFX_UI_FONT_MEDIUM)); 	    
    guiB->addWidgetDown(new ofxUIBiLabelSlider(length-xInit, 0.0, 255.0, blue, "BLUE", "LESS BLUE", "MORE BLUE", OFX_UI_FONT_MEDIUM));
    guiB->addSpacer(length-xInit, 1); 
    guiB->addWidgetDown(new ofxUILabel("VERTICAL SLIDERS", OFX_UI_FONT_MEDIUM));     
    guiB->addSlider("1", 0.0, 255.0, 100.0, dim,80);
    guiB->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	guiB->addSlider("2", 0.0, 255.0, 150.0, dim, 80);
	guiB->addSlider("3", 0.0, 255.0, 200.0, dim, 80);
	guiB->addSlider("4", 0.0, 255.0, 250.0, dim, 80);
	guiB->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    guiB->addSpacer(length-xInit, 1);     
    guiB->addWidgetDown(new ofxUILabel("RANGE SLIDER", OFX_UI_FONT_MEDIUM)); 
	guiB->addWidgetDown(new ofxUIRangeSlider(length-xInit,dim, 0.0, 255.0, 50.0, 100.0, "RSLIDER")); 
    guiB->addSpacer(length-xInit, 1); 
	guiB->addWidgetDown(new ofxUILabel("ROTARY SLIDER", OFX_UI_FONT_MEDIUM));
    guiB->addWidgetDown(new ofxUIRotarySlider(dim*2.0, 0.0, 100.0, 25.0, "CSLIDER 2")); 
    guiB->addSpacer(length-xInit, 1);     
	guiB->addWidgetDown(new ofxUILabel("2D PAD", OFX_UI_FONT_MEDIUM)); 
	guiB->addWidgetDown(new ofxUI2DPad(length-xInit,80, ofPoint((length-xInit)*.5,80*.5), "PAD")); 	
    guiB->addSpacer(length-xInit, 1);     
	guiB->addWidgetDown(new ofxUILabel("CIRCLE SLIDER", OFX_UI_FONT_MEDIUM)); 
	guiB->addWidgetDown(new ofxUICircleSlider(dim*2, 0.0, 255.0, green, "GREEN", OFX_UI_FONT_MEDIUM));
    guiB->addSpacer(length-xInit, 1);     
	guiB->addWidgetDown(new ofxUILabel("IMAGE SLIDER", OFX_UI_FONT_MEDIUM)); 
    guiB->addWidgetDown(new ofxUIImageSlider(length-xInit, 42, 0.0, 255.0, red, "slider.png", "IMAGE SLIDER"));
    guiB->setColorBack(ofColor(255,100));
    
    ofAddListener(guiB->newGUIEvent,this,&testApp::guiEvent);
    guiTabBar->addCanvas(guiB);
    
	ofBackground(red, green, blue);
    
    guiTabBar->loadSettings("settings/", "ui-");
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
        
    // ---
    if (name == "SAVE") {
        guiTabBar->saveSettings("settings/", "ui-");

    }
    else if (name == "LOAD") {
        guiTabBar->loadSettings("settings/", "ui-");
    }
    
	// ---
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
    delete guiTabBar;
    delete guiB;
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    switch (key) 
    {
        case 'p':
        {
            drawPadding = !drawPadding; 
            guiB->setDrawWidgetPadding(drawPadding);          
        }
            break;
            
        case 'g':
        {
            guiTabBar->toggleVisible(); 
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