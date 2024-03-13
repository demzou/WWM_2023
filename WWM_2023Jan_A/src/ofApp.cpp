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

    // GUI
    gui.setup();
    gui.add(framerateLabel.setup("Framerate", ""));
    gui.add(previewInstanceIndex.setup("Preview Instance", 0, 0, NUMBER_OF_PROJECTORS - 1));
 }

//--------------------------------------------------------------
/**
* Update the state of the application
* based on incoming OSC messages
* 
* Messages are assumed to be of the RESTful format:
* /projectors/<projectorIndex>/<message>
* 
* With indexes starting at 0
* / 0        / 1             / 2
* 
* 
***/
void ofApp::update() {
    // Display the framerate in the window title & GUI  
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    framerateLabel = ofToString(ofGetFrameRate());  

    //OSC
    if (messageBuffer.size() > maxBufferSize) messageBuffer.pop_back();

    // check for waiting messages
    while (receiver.hasWaitingMessages()) {
        // get the next message
        ofxOscMessage m;
		receiver.getNextMessage(m);


        // parse out the path elements
        vector<string> addressParts = ofSplitString(m.getAddress(), "/");
        // drop the empty first element
        addressParts.erase(addressParts.begin());

        int projectorIndex = ofToInt(addressParts[1]);
        string message = addressParts[2];

        // check for valid projector index
        if (projectorIndex >= NUMBER_OF_PROJECTORS) {
			messageBuffer.push_front(m.getAddress() + ": UNRECOGNIZED PROJECTOR INDEX");
			continue;
		}
        
        // execute the message
        if (message == "dist") {
			projectors[projectorIndex].dist = m.getArgAsFloat(0);
		}
        else if (message == "invite") {
			projectors[projectorIndex].radAmt = 0;
			projectors[projectorIndex].invite = true;
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
        gui.draw();
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

