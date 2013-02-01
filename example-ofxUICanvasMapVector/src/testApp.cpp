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
    noiseScale = .1; 
    drawFill = true;     
    backgroundColor = ofColor(233, 52, 27); 
    resolution = 60;
    position = ofPoint(ofGetWidth()*.5, ofGetHeight()*.5); 
    ofSetCircleResolution(resolution);
    
    //You can easily re-order these to change where they are shown
    setupGUI1();
    setupGUI2();
    setupGUI3();
    setupGUI4();
    setupGUI5();
    setupGUI6();

    loadGUISettings();
}

void testApp::setupGUI1()
{
    ofxUICanvas *gui = new ofxUICanvas();
    gui->setName("gui1");    
    gui->addLabel("GUI 1");
    gui->addSpacer();
    gui->addLabel("Press 1 to hide/show", OFX_UI_FONT_SMALL);        
    gui->addFPSSlider("FPS");
    gui->addSpacer();
    gui->addSlider("BG_RED", 0, 255, backgroundColor.r);
    gui->addSlider("BG_GREEN", 0, 255, backgroundColor.g);
    gui->addSlider("BG_BLUE", 0, 255, backgroundColor.b);
    gui->autoSizeToFitWidgets();
    //add gui to a c++ stl vector
    guis.push_back(gui);
    //add gui to a c++ stl map
    guihash["1"] = gui; 
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
}

void testApp::setupGUI2()
{
    ofxUICanvas *gui = new ofxUICanvas();
    gui->setName("gui2");    
    if(guis.size() > 0)
    {
        ofxUICanvas *previous = guis[guis.size()-1];
        gui->getRect()->setX(previous->getRect()->getX()+previous->getRect()->getWidth()+1);
    }
    gui->addLabel("GUI 2");
    gui->addSpacer();
    gui->addLabel("Press 2 to hide/show", OFX_UI_FONT_SMALL);        
    gui->addSlider("RADIUS", 0.0, 255.0, &radius);
    gui->addSlider("RESOLUTION", 0.0, 60, resolution);
    gui->autoSizeToFitWidgets();
    //add gui to a c++ stl vector
    guis.push_back(gui);
    //add gui to a c++ stl map
    guihash["2"] = gui;     
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);    
}

void testApp::setupGUI3()
{
    ofxUICanvas *gui = new ofxUICanvas();
    gui->setName("gui3");
    if(guis.size() > 0)
    {
        ofxUICanvas *previous = guis[guis.size()-1];
        gui->getRect()->setX(previous->getRect()->getX()+previous->getRect()->getWidth()+1);
    }
    gui->addLabel("GUI 3");
    gui->addSpacer();
    gui->addLabel("Press 3 to hide/show", OFX_UI_FONT_SMALL);
    gui->addSlider("RED", 0.0, 255.0, &red);
    gui->addSlider("GREEN", 0.0, 255.0, &green);
    gui->addSlider("BLUE", 0.0, 255.0, &blue);
    gui->addSlider("ALPHA", 0.0, 255.0, &alpha);
    gui->autoSizeToFitWidgets();
    //add gui to a c++ stl vector
    guis.push_back(gui);
    //add gui to a c++ stl map
    guihash["3"] = gui;     
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);    
}

void testApp::setupGUI4()
{
    ofxUICanvas *gui = new ofxUICanvas();
    gui->setName("gui4");    
    if(guis.size() > 0)
    {
        ofxUICanvas *previous = guis[guis.size()-1];
        gui->getRect()->setX(previous->getRect()->getX()+previous->getRect()->getWidth()+1);
    }
    gui->addLabel("GUI 4");
    gui->addSpacer();
    gui->addLabel("Press 4 to hide/show", OFX_UI_FONT_SMALL);        
    gui->add2DPad("CENTER", ofPoint(0,ofGetWidth()), ofPoint(0, ofGetHeight()), &position);
    gui->autoSizeToFitWidgets();
    //add gui to a c++ stl vector
    guis.push_back(gui);
    //add gui to a c++ stl map
    guihash["4"] = gui;     
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);    
}

void testApp::setupGUI5()
{
    ofxUICanvas *gui = new ofxUICanvas();
    gui->setName("gui5");
    if(guis.size() > 0)
    {
        ofxUICanvas *previous = guis[guis.size()-1];
        gui->getRect()->setX(previous->getRect()->getX()+previous->getRect()->getWidth()+1);     
    }
    gui->addLabel("GUI 5");
    gui->addSpacer();
    gui->addLabel("Press 5 to hide/show", OFX_UI_FONT_SMALL);        
    gui->addLabelToggle("DRAWFILL", &drawFill);
    gui->addLabelToggle("DRAWMORE", drawFill);    
    gui->autoSizeToFitWidgets();
    //add gui to a c++ stl vector
    guis.push_back(gui);
    //add gui to a c++ stl map
    guihash["5"] = gui;     
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);    
}

void testApp::setupGUI6()
{
    ofxUICanvas *gui = new ofxUICanvas();
    gui->setName("gui6");
    if(guis.size() > 0)
    {
        ofxUICanvas *previous = guis[guis.size()-1];
        gui->getRect()->setX(previous->getRect()->getX()+previous->getRect()->getWidth()+1);
    }
    gui->addLabel("GUI 6");
    gui->addSpacer();
    gui->addLabel("Press 6 to hide/show", OFX_UI_FONT_SMALL);        
    gui->addFPSSlider("FPS");
    gui->addToggleMatrix("MATRIX", 12, 12);
    gui->autoSizeToFitWidgets();
    //add gui to a c++ stl vector
    guis.push_back(gui);
    //add gui to a c++ stl map
    guihash["6"] = gui;     
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
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

    ofSetColor(red, green, blue, alpha);
    if(drawFill)
    {
        ofFill(); 
    }
    else
    {
        ofNoFill(); 
    }

    ofCircle(position.x, position.y, radius);
    
	ofPopStyle(); 
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind();
    if(name == "BG_RED")
    {
        ofxUISlider *s = (ofxUISlider *) e.widget;
        backgroundColor.r = s->getScaledValue();
    }
    else if(name == "BG_GREEN")
    {
        ofxUISlider *s = (ofxUISlider *) e.widget;
        backgroundColor.g = s->getScaledValue();
    }
    else if(name == "BG_BLUE")
    {
        ofxUISlider *s = (ofxUISlider *) e.widget;
        backgroundColor.b = s->getScaledValue();
    }
    else if(name == "RESOLUTION")
    {
        ofxUISlider *s = (ofxUISlider *) e.widget;
        resolution = (int)s->getScaledValue();
        ofSetCircleResolution(resolution); 
    }
    
}
//--------------------------------------------------------------
void testApp::loadGUISettings()
{
    vector<ofxUICanvas *>::iterator it;
    for(it = guis.begin(); it != guis.end(); it++)
    {
        (*it)->loadSettings("GUI/"+(*it)->getName()+"Settings.xml");
    }
}
//--------------------------------------------------------------
void testApp::saveGUISettings()
{
    vector<ofxUICanvas *>::iterator it;
    for(it = guis.begin(); it != guis.end(); it++)
    {
        (*it)->saveSettings("GUI/"+(*it)->getName()+"Settings.xml");
    }
}
//--------------------------------------------------------------
void testApp::exit()
{
    saveGUISettings();
    
    for(int i = 0; i < guis.size(); i++)
    {
        ofxUICanvas *gui = guis[i];
        delete gui;
    }
    guis.clear();
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    switch (key) 
    {            
        case '1':
        {
            guihash["1"]->toggleVisible();
        }
            break;
        case '2':
        {
            guihash["2"]->toggleVisible();
        }
            break;
        case '3':
        {
            guihash["3"]->toggleVisible();
        }
            break;
        case '4':
        {
            guihash["4"]->toggleVisible();
        }
            break;
        case '5':
        {
            guihash["5"]->toggleVisible();
        }
            break;
        case '6':
        {
            guihash["6"]->toggleVisible();
        }
            break;

        case 'p':
        {
            vector<ofxUICanvas *>::iterator it;
            for(it = guis.begin(); it != guis.end(); it++)
            {
                (*it)->setDrawWidgetPadding(true);
            }
        }
            break;

        case 'P':
        {
            vector<ofxUICanvas *>::iterator it;
            for(it = guis.begin(); it != guis.end(); it++)
            {
                (*it)->setDrawWidgetPadding(false);
            }
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