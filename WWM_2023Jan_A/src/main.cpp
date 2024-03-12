#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	/*ofGLWindowSettings settings;
	settings.setGLVersion(4,5);
	settings.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	ofCreateWindow(settings);*/


	//ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	ofSetupOpenGL(WINDOW_WIDTH, WINDOW_HEIGHT, OF_WINDOW);	// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
