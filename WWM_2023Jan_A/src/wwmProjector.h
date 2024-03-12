#pragma once
#include <ofPixels.h>
#include "ofMain.h"

class wwmProjector
{

public:
	wwmProjector(int windowWidth, int windowHeight);
	ofFbo draw();

    float dist;
    int maxRad;
    int radAmt;
    bool invite;


private:
    ofFbo frameBuffer;
    vector<float> noiseSeeds;
    float angleStep, stepSize, maxStepSize, radius;
    int sunLocX, sunLocY, totalRays, maxTotalRays;


    void drawSpotlight();
    void drawLine();
    void drawInvitation();  
   
};

