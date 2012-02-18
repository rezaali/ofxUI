#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
//	window.setGlutDisplayString("rgba double samples>=6 depth");        
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW);			// <-------- setup the GL context	
	ofRunApp( new testApp());

}
