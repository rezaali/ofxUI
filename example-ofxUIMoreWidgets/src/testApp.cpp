#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 
	
	float dim = 16; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320-xInit; 
	
    drawPadding = false; 
    
    gui = new ofxUICanvas(0,0,length+xInit,ofGetHeight());     
    
	gui->addWidgetDown(new ofxUILabel("MORE WIDGETS", OFX_UI_FONT_LARGE)); 
    
    gui->addWidgetDown(new ofxUISpacer(length-xInit, 2)); 
	gui->addWidgetDown(new ofxUILabel("MOVING GRAPH", OFX_UI_FONT_MEDIUM));         
    int bufferSize = 256; 
    vector<float> buffer; 
    for(int i = 0; i < bufferSize; i++)
    {
        buffer.push_back(i);         
    }
    mg = (ofxUIMovingGraph *) gui->addWidgetDown(new ofxUIMovingGraph(length-xInit, 64, buffer, bufferSize, 0, 256, "MOVING GRAPH")); 
    
    gui->addWidgetDown(new ofxUISpacer(length-xInit, 2)); 
    gui->addWidgetDown(new ofxUILabel("MINIMAL SLIDER", OFX_UI_FONT_LARGE)); 
    gui->addWidgetDown(new ofxUIMinimalSlider(length-xInit, 0, 100, 50, "MINIMAL", OFX_UI_FONT_SMALL)); 
    gui->addWidgetDown(new ofxUISlider(length-xInit, 16, 0, 100, 50, "STANDARD"));
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);	
    
//    gui->loadSettings("GUI/guiSettings.xml"); 
}

//--------------------------------------------------------------
void testApp::update()
{
}

//--------------------------------------------------------------
void testApp::draw()
{    
	ofBackground(200,200,200,255); 
	
	ofPushStyle(); 
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);     
	ofPopStyle(); 
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
    
    if(name == "MINIMAL")
    {
        ofxUISlider *slider = (ofxUISlider *) gui->getWidget("STANDARD");
        ofxUISlider *mslider = (ofxUISlider *) e.widget; 
        slider->setMax(mslider->getScaledValue());
    }
    else if(name == "STANDARD")
    {
        
    }
            
}
//--------------------------------------------------------------
void testApp::exit()
{
//    gui->saveSettings("GUI/guiSettings.xml"); 
    delete gui; 
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    if(gui->hasKeyboardFocus())
    {
        return; 
    }
    
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
   mg->addPoint(ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, 256)); 
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