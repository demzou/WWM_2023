#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {

    ofBackground(0);
    ofSetFrameRate(60);         
    ofSetCircleResolution(60);


    // OSC
    // listen on the given port
    ofLog() << "listening for osc messages on port " << PORT;
    receiver.setup(PORT);


    // NDI  
    // Create collections of senders and projectors
    senders = vector<ofxNDISender>(NUMBER_OF_PROJECTORS);
    videoSenders = vector<ofxNDISendVideo>(NUMBER_OF_PROJECTORS);

   
    for (int i = 0; i < NUMBER_OF_PROJECTORS; i++) {
		wwmProjector projector = wwmProjector(WINDOW_WIDTH, WINDOW_HEIGHT);
		projectors.push_back(projector);
	
        if (senders[i].setup(NDI_IDENTIFIER_PREFIX + ofToString(i))) {
            videoSenders[i].setup(senders[i]);
            videoSenders[i].setAsync(true);
        }
	}
 }

//--------------------------------------------------------------
void ofApp::update() {


    //OSC
    if (messageBuffer.size() > maxBufferSize) messageBuffer.pop_back();

    // check for waiting messages
    while (receiver.hasWaitingMessages()) {
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);

        if (m.getAddress() == "/dist") {
            projectors[1].dist = m.getArgAsFloat(0);
        }
        else if (m.getAddress() == "/invite") {
            projectors[1].radAmt = 0;
            projectors[1].invite = true;
        }
        else {
            messageBuffer.push_front(m.getAddress() + ": UNRECOGNIZED MESSAGE");
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    for (int i = 0; i < NUMBER_OF_PROJECTORS; i++) {
		ofPixels pixels;
		ofFbo projectorFrameBuffer = projectors[i].draw();
		projectorFrameBuffer.readToPixels(pixels);

		videoSenders[i].send(pixels);
        if (i == previewInstanceIndex) {
            projectorFrameBuffer.draw(0, 0);
        }
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'f') {
        ofToggleFullscreen();
        for (int i = 0; i < NUMBER_OF_PROJECTORS; i++) {
			projectors[1].maxRad = ofGetHeight() / 2.5;
		}
    }

}

