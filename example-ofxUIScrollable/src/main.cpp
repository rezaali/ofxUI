#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
//	window.setGlutDisplayString("rgba double samples>=6 depth");        
	ofSetupOpenGL(&window, 320,480, OF_WINDOW);			// <-------- setup the GL context	
	ofRunApp( new testApp());

}
