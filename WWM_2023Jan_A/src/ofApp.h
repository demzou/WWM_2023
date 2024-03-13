#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxNDISender.h"
#include "ofxNDISendStream.h"
#include "wwmProjector.h"
#include "ofxGui.h"

// max number of strings to display
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp {

public:
    // Custom constructor to pass in command line arguments
    ofApp(int port, int projectorCount, int width, int height, string ndiPrefix);
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    //OSC
    ofxOscReceiver receiver;
    deque<string> messageBuffer;
    int maxBufferSize = 20;

    // GUI
    ofxPanel gui;
    ofxLabel framerateLabel;
    ofxIntSlider previewInstanceIndex;

private:
    int port; // OSC port to listen on
	int projectorCount; // Number of projectors to create
    int windowWidth;
    int windowHeight;
    string ndiPrefix;
 	vector<ofxNDISender> senders;
 	vector<ofxNDISendVideo> videoSenders;
    vector<wwmProjector> projectors;

};
