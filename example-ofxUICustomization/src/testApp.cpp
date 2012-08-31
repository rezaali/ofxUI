#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 
    ofBackground(0); 
	
	float dim = 32; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320-xInit; 
	
    drawPadding = false; 
    
    gui = new ofxUICanvas(0,0,length+xInit,ofGetHeight());     
    gui->setDrawBack(false); 
    
    ofColor paddingColor = ofColor(255,0,0,200);
    
	ofxUIWidget *w = (ofxUILabel *) gui->addWidgetDown(new ofxUILabel(length-xInit,"SLIDER WIDGETS", OFX_UI_FONT_LARGE)); 
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    w = gui->addSpacer(length-xInit, 2);
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
	w = gui->addWidgetDown(new ofxUILabel(length-xInit,"HORIZONTAL SLIDERS", OFX_UI_FONT_MEDIUM)); 	
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    w = gui->addWidgetDown(new ofxUILabel(length-xInit,"FPS SLIDER", OFX_UI_FONT_MEDIUM)); 	
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);

    w = gui->addFPSSlider("FPS SLIDER", length-xInit, dim/2.0, 60.0);
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    w = gui->addSpacer(length-xInit, 2);
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    w = gui->addSlider("NORMAL SLIDER", 0.0, 100, 50, length-xInit,dim);
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    w = gui->addWidgetDown(new ofxUIMinimalSlider(length-xInit, 0, 100, 50.0, "MINIMAL", OFX_UI_FONT_MEDIUM));     
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    	
    w = gui->addSpacer(length-xInit, 2);
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
	w = gui->addWidgetDown(new ofxUILabel(length-xInit,"BILABEL SLIDER", OFX_UI_FONT_MEDIUM)); 	
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    w = gui->addWidgetDown(new ofxUIBiLabelSlider(length-xInit, 0, 100, 50, "BILABEL SLIDER", "HOT", "COLD", OFX_UI_FONT_MEDIUM));
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);    
    
    w = gui->addSpacer(length-xInit, 2);
	w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    w = gui->addWidgetDown(new ofxUILabel(length-xInit, "RANGE SLIDER", OFX_UI_FONT_MEDIUM)); 
	w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    w = gui->addWidgetDown(new ofxUIRangeSlider(length-xInit,dim, 0.0, 255.0, 50.0, 100.0, "RSLIDER")); 
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    w = gui->addSpacer(length-xInit, 2);
	w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);

    w = gui->addWidgetDown(new ofxUILabel(length-xInit, "CIRCLE SLIDER", OFX_UI_FONT_MEDIUM)); 
	w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    w = gui->addWidgetDown(new ofxUICircleSlider((length-xInit*2.5)/2.0, 0, 100, 50, "SOUTH NORTH", OFX_UI_FONT_MEDIUM));
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);

    w = gui->addWidgetRight(new ofxUICircleSlider((length-xInit*2.5)/2.0, 0, 100, 50, "WEST EAST", OFX_UI_FONT_MEDIUM));    
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    ofxUICircleSlider *cslider2 = (ofxUICircleSlider *) gui->getWidget("WEST EAST");
    cslider2->setInputDirection(OFX_UI_DIRECTION_WESTEAST);
    
    w = gui->addSpacer(length-xInit, 2);
	w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    w = gui->addWidgetDown(new ofxUILabel(length-xInit, "2D PAD", OFX_UI_FONT_MEDIUM)); 
	w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    w = gui->addWidgetDown(new ofxUI2DPad(length-xInit, 160, ofPoint((length-xInit)*.5,190*.5), "PAD")); 	
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    w = gui->addWidgetDown(new ofxUILabelToggle(length-xInit, false, "DONATE", OFX_UI_FONT_LARGE)); 
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    w = gui->addWidgetDown(new ofxUILabelToggle(length-xInit, false, "DONATE", OFX_UI_FONT_MEDIUM)); 
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    w = gui->addWidgetDown(new ofxUILabelToggle(length-xInit, false, "DONATE", OFX_UI_FONT_SMALL));     
    w->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
        
    drawPadding = !drawPadding; 
    gui->setDrawWidgetPadding(drawPadding);          
    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);	
}

//--------------------------------------------------------------
void testApp::update()
{

}

//--------------------------------------------------------------
void testApp::draw()
{    
//	ofBackground(red, green, blue, 255); 
	
	ofPushStyle(); 
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);     
	ofPopStyle(); 
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
	
	if(!name.compare("NORMAL SLIDER"))
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
        cout << slider->getScaledValue() << endl;
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