#pragma once

#include "ofMain.h"
#include "ofxOsc.h"


// listening on
#define PORT 6002

// max number of strings to display
#define NUM_MSG_STRINGS 20

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

    //Values
    float dist;
    int maxRad;

    vector<float> noiseSeeds;
    float angleStep, stepSize, maxStepSize, radius;
    int sunLocX, sunLocY, totalRays, maxTotalRays;
    int radAmt;
    bool invite;

};
