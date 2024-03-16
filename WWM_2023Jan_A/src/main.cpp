#include "ofMain.h"
#include "ofApp.h"
#include "ofxTclap.h"

//========================================================================
int main(int argc, char **argv ){

	CmdLine cmd("WWM Projector");

	ValueArg<int> portArg("p", "port", "Port to listen on", false, 6001, "int");
	ValueArg<int> projectorCountArg("c", "projectorCount", "Number of projectors", false, 3, "int");
	ValueArg<int> widthArg("x", "width", "Width of the window", false, 1280, "int");
	ValueArg<int> heightArg("y", "height", "Height of the window", false, 720, "int");
	ValueArg<std::string> ndiPrefixArg("n", "ndiPrefix", "NDI prefix", false, "WWM-Projector-", "string");

	cmd.add(portArg);
	cmd.add(projectorCountArg);
	cmd.add(widthArg);
	cmd.add(heightArg);
	cmd.add(ndiPrefixArg);
	cmd.parse(argc, argv);


	ofSetupOpenGL(widthArg.getValue(), heightArg.getValue(), OF_WINDOW);	// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp(
		portArg.getValue(),
		projectorCountArg.getValue(),
		widthArg.getValue(),
		heightArg.getValue(),
		ndiPrefixArg.getValue()));

}
