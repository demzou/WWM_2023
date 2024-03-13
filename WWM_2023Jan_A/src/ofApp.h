#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxNDISender.h"
#include "ofxNDISendStream.h"
#include "wwmProjector.h"
#include "ofxGui.h"

// listening on
#define PORT 6001
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
// max number of strings to display
#define NUM_MSG_STRINGS 20
#define NDI_IDENTIFIER_PREFIX "WWM-Projector-"
#define NUMBER_OF_PROJECTORS 3

class ofApp : public ofBaseApp {

public:
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
 	vector<ofxNDISender> senders;
 	vector<ofxNDISendVideo> videoSenders;
    vector<wwmProjector> projectors;

};
