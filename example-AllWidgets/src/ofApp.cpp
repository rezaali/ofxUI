#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
    ofSetCircleResolution(120);
    red = 233; blue = 233; green = 233;
    hideGUI = false;
    bdrawGrid = false;
	bdrawPadding = false;

    ddl = NULL;
    textInput = NULL;
    img = new ofImage();
    img->loadImage("nerd_me.png");
    buffer = new float[256];
    for(int i = 0; i < 256; i++) { buffer[i] = ofNoise(i/100.0); }
    
	setGUI1();
	setGUI2();
    setGUI3();
    setGUI4();
    setGUI5();
    
    gui1->loadSettings("gui1Settings.xml");
    gui2->loadSettings("gui2Settings.xml");
    gui3->loadSettings("gui3Settings.xml");
    gui4->loadSettings("gui4Settings.xml");
    gui5->loadSettings("gui5Settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    mg->addPoint(buffer[0]);
    for(int i = 0; i < 256; i++) { buffer[i] = ofNoise(i/100.0, ofGetElapsedTimef()); }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(red, green, blue, 255);
	
	ofPushStyle();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    
	if(bdrawGrid)
	{
		ofSetColor(255, 255, 255, 25);
		drawGrid(8,8);
	}
    
	ofPopStyle();
    
    ofSetRectMode(OF_RECTMODE_CENTER);
}

void ofApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.getName();
	int kind = e.getKind();
	cout << "got event from: " << name << endl;
    if(kind == OFX_UI_WIDGET_NUMBERDIALER)
    {
        ofxUINumberDialer *n = (ofxUINumberDialer *) e.widget;
        cout << n->getValue() << endl;
    }
	
    if(name == "SAMPLER")
    {
        ofxUIImageSampler *is = (ofxUIImageSampler *) e.widget;
        ofColor clr = is->getColor();
        red = clr.r;
        blue = clr.b;
        green = clr.g;
    }
	else if(name == "BUTTON")
	{
		ofxUIButton *button = (ofxUIButton *) e.getButton();
		bdrawGrid = button->getValue();
	}
	else if(name == "TOGGLE")
	{
		ofxUIToggle *toggle = (ofxUIToggle *) e.getToggle();
		bdrawGrid = toggle->getValue();
        if(textInput != NULL)
        {
            textInput->setFocus(bdrawGrid);
        }
	}
    else if(name == "RADIO VERTICAL")
    {
        ofxUIRadio *radio = (ofxUIRadio *) e.widget;
        cout << radio->getName() << " value: " << radio->getValue() << " active name: " << radio->getActiveName() << endl; 
    }
    else if(name == "TEXT INPUT")
    {
        ofxUITextInput *ti = (ofxUITextInput *) e.widget;
        if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
            cout << "ON ENTER: ";
        }
        else if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
        {
            cout << "ON FOCUS: ";
        }
        else if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
        {
            cout << "ON BLUR: ";
        }
        string output = ti->getTextString();
        cout << output << endl;
    }
}

//--------------------------------------------------------------
void ofApp::exit()
{
    gui1->saveSettings("gui1Settings.xml");
    gui2->saveSettings("gui2Settings.xml");
    gui3->saveSettings("gui3Settings.xml");
    gui4->saveSettings("gui4Settings.xml");
    gui5->saveSettings("gui5Settings.xml");
    
	delete gui1;
	delete gui2;
    delete gui3;
    delete gui4;
    delete gui5;
	delete[] buffer;
    delete img;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(gui2->hasKeyboardFocus())
    {
        return;
    }
	switch (key)
	{
		case 't':
        {
            if(textInput != NULL)
            {
                textInput->setTextString(ofGetTimestampString());
            }
        }
			break;

		case 'T':
        {
            if(tm != NULL)
            {
                int cols = tm->getColumnCount();
                int rows = tm->getRowCount();
                for(int row = 0; row < rows; row++)
                {
                    for(int col = 0; col < cols; col++)
                    {
                        cout << tm->getState(row, col) << "\t";
                    }
                    cout << endl;
                }
            }
        }
			break;

		case 'd':
        {
            if(ddl != NULL)
            {
                vector<ofxUIWidget *> selected = ddl->getSelected();
                for(vector<ofxUIWidget *>::iterator it = selected.begin(); it != selected.end(); ++it)
                {
                    ofxUILabelToggle *lt = (ofxUILabelToggle *) (*it);
                    cout << lt->getName() << endl;
                }
            }
        }
			break;
            
        case 'D':
        {
            if(ddl != NULL)
            {
                vector<string> names = ddl->getSelectedNames();
                for(vector<string>::iterator it = names.begin(); it != names.end(); ++it)
                {
                    cout << (*it) << endl;
                }
            }
        }
			break;
            
		case 'r':
        {
            if(textInput != NULL)
            {
                textInput->setFocus(!textInput->isFocused());
            }
        }
			break;
            
		case 'f':
			ofToggleFullscreen();
			break;
            
        case 'F':
        {
            if(tm != NULL)
            {
                tm->setDrawOutlineHighLight(!tm->getDrawOutlineHighLight());
//                tm->setDrawPaddingOutline(!tm->getDrawPaddingOutline());
            }
        }
			break;
            
		case 'h':
            gui1->toggleVisible();
            gui2->toggleVisible();
            gui3->toggleVisible();
            gui4->toggleVisible();
            gui5->toggleVisible();
			break;
            
		case 'p':
			bdrawPadding = !bdrawPadding;
			gui1->setDrawWidgetPaddingOutline(bdrawPadding);
			gui2->setDrawWidgetPaddingOutline(bdrawPadding);
			gui3->setDrawWidgetPaddingOutline(bdrawPadding);
			gui4->setDrawWidgetPaddingOutline(bdrawPadding);
			gui5->setDrawWidgetPaddingOutline(bdrawPadding);
			break;
            
		case '[':
			gui1->setDrawWidgetPadding(false);
			gui2->setDrawWidgetPadding(false);
			gui3->setDrawWidgetPadding(false);
			gui4->setDrawWidgetPadding(false);
			gui5->setDrawWidgetPadding(false);
			break;
            
		case ']':
			gui1->setDrawWidgetPadding(true);
			gui2->setDrawWidgetPadding(true);
			gui3->setDrawWidgetPadding(true);
			gui4->setDrawWidgetPadding(true);
			gui5->setDrawWidgetPadding(true);
			break;
			
        case '1':
            gui1->toggleVisible();
            break;
            
        case '2':
            gui2->toggleVisible();
            break;
            
        case '3':
            gui3->toggleVisible();
            break;
            
        case '4':
            gui4->toggleVisible();
            break;

        case '5':
            gui5->toggleVisible();
            break;

		default:
			break;
	}
}

void ofApp::drawGrid(float x, float y)
{
    float w = ofGetWidth();
    float h = ofGetHeight();
    
    for(int i = 0; i < h; i+=y)
    {
        ofLine(0,i,w,i);
    }
    
    for(int j = 0; j < w; j+=x)
    {
        ofLine(j,0,j,h);
    }
}

void ofApp::setGUI1()
{
    vector<string> names;
	names.push_back("RAD1");
	names.push_back("RAD2");
	names.push_back("RAD3");
	
	gui1 = new ofxUISuperCanvas("PANEL 1: BASICS");
    gui1->addSpacer();
    gui1->addLabel("Press 'h' to Hide GUIs", OFX_UI_FONT_SMALL);
    
    gui1->addSpacer();
	gui1->addLabel("H SLIDERS");
	gui1->addSlider("RED", 0.0, 255.0, &red)->setTriggerType(OFX_UI_TRIGGER_ALL);
	gui1->addSlider("GREEN", 0.0, 255.0, &green)->setTriggerType(OFX_UI_TRIGGER_BEGIN|OFX_UI_TRIGGER_CHANGE|OFX_UI_TRIGGER_END);
	gui1->addSlider("BLUE", 0.0, 255.0, &blue)->setTriggerType(OFX_UI_TRIGGER_BEGIN|OFX_UI_TRIGGER_CHANGE);
    
    gui1->addSpacer();
    gui1->addLabel("V SLIDERS");
	gui1->addSlider("0", 0.0, 255.0, 150, 17, 160);
	gui1->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	gui1->addSlider("1", 0.0, 255.0, 150, 17, 160);
	gui1->addSlider("2", 0.0, 255.0, 150, 17, 160);
	gui1->addSlider("3", 0.0, 255.0, 150, 17, 160);
	gui1->addSlider("4", 0.0, 255.0, 150, 17, 160);
	gui1->addSlider("5", 0.0, 255.0, 150, 17, 160);
	gui1->addSlider("6", 0.0, 255.0, 150, 17, 160);
	gui1->addSlider("7", 0.0, 255.0, 150, 17, 160);
	gui1->addSlider("8", 0.0, 255.0, 150, 17, 160);
	gui1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    gui1->addSpacer();
	gui1->addRadio("RADIO HORIZONTAL", names, OFX_UI_ORIENTATION_HORIZONTAL);
	gui1->addRadio("RADIO VERTICAL", names, OFX_UI_ORIENTATION_VERTICAL);
    
    gui1->addSpacer();
    gui1->setWidgetFontSize(OFX_UI_FONT_SMALL);
	gui1->addButton("BUTTON", false);
	gui1->addToggle( "TOGGLE", false);
    
    gui1->addSpacer();
    gui1->addLabel("RANGE SLIDER");
	gui1->addRangeSlider("RSLIDER", 0.0, 255.0, 50.0, 100.0);
    
    string textString = "This widget is a text area widget. Use this when you need to display a paragraph of text. It takes care of formatting the text to fit the block.";
    gui1->addSpacer();
    
    gui1->addTextArea("textarea", textString, OFX_UI_FONT_SMALL);
    
    gui1->autoSizeToFitWidgets();
	ofAddListener(gui1->newGUIEvent,this,&ofApp::guiEvent);
}

void ofApp::setGUI2()
{
    gui2 = new ofxUISuperCanvas("PANEL 2: ADVANCED");
    
    gui2->addSpacer();
	gui2->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
    textInput = gui2->addTextInput("TEXT INPUT", "Input Text");
    textInput->setAutoUnfocus(false); 
    gui2->addLabel("AUTO CLEAR DISABLED", OFX_UI_FONT_SMALL);
    gui2->addTextInput("TEXT INPUT2", "Input Text")->setAutoClear(false);
	gui2->setWidgetFontSize(OFX_UI_FONT_MEDIUM);

    gui2->addSpacer();
    gui2->addLabel("WAVEFORM DISPLAY");
	gui2->addWaveform("WAVEFORM", buffer, 256, 0.0, 1.0);
    gui2->addLabel("SPECTRUM DISPLAY");
    gui2->addSpectrum("SPECTRUM", buffer, 256, 0.0, 1.0);
    
    vector<float> buffer;
    for(int i = 0; i < 256; i++)
    {
        buffer.push_back(0.0);
    }

    gui2->addLabel("MOVING GRAPH", OFX_UI_FONT_MEDIUM);
    mg = gui2->addMovingGraph("MOVING", buffer, 256, 0.0, 1.0);
    
    gui2->addSpacer();
    gui2->addLabel("IMAGE DISPLAY");
	gui2->addImage("IMAGE CAPTION", img);
    
    gui2->addSpacer();
    gui2->addLabel("FPS LABEL");
    gui2->addFPS();

    gui2->setWidgetFontSize(OFX_UI_FONT_SMALL);
    gui2->addSpacer();
    gui2->addLabel("NUMBER DIALER");
    gui2->addNumberDialer("DIALER", -10000, 10000, 5000, 3); 
    
    gui2->addSpacer();
    gui2->addLabel("LABEL BUTTON", OFX_UI_FONT_MEDIUM);
    gui2->addLabelButton("LABEL BTN", false);
    
    gui2->addSpacer();
    gui2->addLabel("LABEL TOGGLES", OFX_UI_FONT_MEDIUM);
    gui2->addLabelToggle("LABEL TGL", false)->getLabelWidget()->setColorFill(ofColor(255, 0, 0));
    
    gui2->setPosition(212, 0);
    gui2->autoSizeToFitWidgets();
    
	ofAddListener(gui2->newGUIEvent,this,&ofApp::guiEvent);
}

void ofApp::setGUI3()
{
	gui3 = new ofxUISuperCanvas("PANEL 3: ADVANCED");
    
    gui3->addSpacer();
    gui3->setGlobalButtonDimension(24);
    gui3->addLabel("MATRIX", OFX_UI_FONT_MEDIUM);
    gui3->addToggleMatrix("MATRIX1", 3, 3);
    tm = gui3->addToggleMatrix("MATRIX2", 3, 6);
    gui3->addToggleMatrix("MATRIX3", 1, 4);

    gui3->addSpacer();
    gui3->setGlobalButtonDimension(64);
    gui3->addImageButton("IMAGEBTN", "GUI/images/App.png", false);
    gui3->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui3->addImageToggle("IMAGETGL", "GUI/images/Preview.png", false);
    gui3->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);

    gui3->addSpacer();
    vector<string> items;
    items.push_back("FIRST ITEM"); items.push_back("SECOND ITEM"); items.push_back("THIRD ITEM");
    items.push_back("FOURTH ITEM"); items.push_back("FIFTH ITEM"); items.push_back("SIXTH ITEM");
    
    gui3->addSpacer();
    gui3->setWidgetFontSize(OFX_UI_FONT_SMALL);
    gui3->addSortableList("SORTABLE LIST", items);
    
    gui3->addSpacer();
    gui3->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
    ddl = gui3->addDropDownList("DROP DOWN LIST", items);
    ddl->setAllowMultiple(true);

    gui3->setGlobalButtonDimension(OFX_UI_GLOBAL_BUTTON_DIMENSION);
    
    gui3->setPosition(212*2, 0);
    gui3->autoSizeToFitWidgets();
    
	ofAddListener(gui3->newGUIEvent,this,&ofApp::guiEvent);
}

void ofApp::setGUI4()
{
	gui4 = new ofxUISuperCanvas("PANEL 4: ADVANCED");
    
    gui4->addSpacer();
    gui4->addLabel("BILABEL SLIDER");
    gui4->addBiLabelSlider("BILABEL", "HOT", "COLD", 0, 100, 50);
    
    gui4->addLabel("MINIMAL SLIDER");
    gui4->addMinimalSlider("MINIMAL", 0, 100, 50.0)->getLabelWidget()->setColorFill(ofColor(255, 255, 0));
    
    gui4->addSpacer();
    gui4->addLabel("FPS SLIDER", OFX_UI_FONT_MEDIUM);
    gui4->addFPSSlider("FPS SLIDER");
    
    gui4->addSpacer();
    gui4->addLabel("IMAGE SAMPLER", OFX_UI_FONT_MEDIUM);
    gui4->addImageSampler("SAMPLER", img);
    gui4->setGlobalButtonDimension(64); 
    gui4->addMultiImageButton("IMAGE BUTTON", "GUI/toggle.png", false);
    gui4->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui4->addMultiImageToggle("IMAGE TOGGLE", "GUI/toggle.png", false);
    gui4->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    gui4->addBaseDraws("BASE DRAW", img, true);

    gui4->addSpacer();
    gui4->setGlobalButtonDimension(32);
    gui4->addButton("BTN", false)->setLabelVisible(false);
    gui4->addToggle("TGL", false)->setLabelVisible(false);
    
    gui4->setPosition(212*3,0);
    gui4->autoSizeToFitWidgets();
    
	ofAddListener(gui4->newGUIEvent,this,&ofApp::guiEvent);
}

void ofApp::setGUI5()
{
	gui5 = new ofxUISuperCanvas("PANEL 5: ADVANCED");
    gui5->addSpacer();
    
	gui5->addLabel("2D PAD");
	gui5->add2DPad("PAD", ofPoint(-100, 100), ofPoint(-100,100), ofPoint(0,0));

    gui5->addSpacer();
    gui5->addLabel("ROTARY SLIDER", OFX_UI_FONT_MEDIUM);
    gui5->addRotarySlider("R2SLIDER", 0, 100, 50);
    
    gui5->addSpacer();
    gui5->addLabel("CIRCLE SLIDER", OFX_UI_FONT_MEDIUM);
    gui5->addCircleSlider("NORTH SOUTH", 0, 100, 50.0);

    gui5->setPosition(212*4,0);
    gui5->autoSizeToFitWidgets();
    
	ofAddListener(gui5->newGUIEvent,this,&ofApp::guiEvent);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}