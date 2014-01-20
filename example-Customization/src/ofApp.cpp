#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(0);
    drawPadding = false;
    ofColor paddingColor = ofColor(255,0,0,200);
    
    gui = new ofxUICanvas();
    gui->setDrawBack(false);
    
    gui->addLabel("SLIDER WIDGETS", OFX_UI_FONT_LARGE)->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    gui->addSpacer()->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
	gui->addLabel("HORIZONTAL SLIDERS")->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    gui->addLabel("FPS SLIDER")->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);

    gui->addFPSSlider("FPS SLIDER")->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    gui->addSpacer()->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    gui->addSlider("NORMAL SLIDER", 0.0, 100, 50)->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    gui->addMinimalSlider("MINIMAL", 0, 100, 50.0)->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    	
    gui->addSpacer()->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    gui->addLabel("BILABEL SLIDER")->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    gui->addBiLabelSlider("BILABEL SLIDER", "HOT", "COLD", 0, 100, 50)->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);    
    
    gui->addSpacer()->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    gui->addLabel("RANGE SLIDER")->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    gui->addRangeSlider("RSLIDER", 0.0, 255.0, 50.0, 100.0)->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    gui->addSpacer()->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    gui->addSpacer()->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    gui->addLabel("2D PAD")->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    gui->add2DPad("PAD", ofVec2f(-100,100), ofVec2f(-100,100), ofVec2f(0,0))->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    gui->addLabelToggle("DONATE", false)->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    gui->addLabelToggle("DONATE PLEASE", false)->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
    
    gui->addLabelToggle("DONATE PLEASEEE", false)->setColorPadded(paddingColor);
    paddingColor.setHue(paddingColor.getHue()+5);
        
    drawPadding = !drawPadding; 
    gui->setDrawWidgetPadding(drawPadding);          
    gui->autoSizeToFitWidgets();
    
    ofAddListener(gui->newGUIEvent,this,&ofApp::guiEvent);	
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{    
//	ofBackground(red, green, blue, 255); 
	
	ofPushStyle(); 
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);     
	ofPopStyle(); 
}
//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
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