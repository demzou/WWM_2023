#pragma once
#include <ofPixels.h>
#include "ofMain.h"

class wwmProjector
{

public:
	wwmProjector(int windowWidth, int windowHeight, float fadeDuration);
	ofFbo draw();

    float dist;
    int maxRad;
    int radAmt;
    bool invite;
    bool fade;
    float fadeDuration;


private:
    ofFbo frameBuffer;
    vector<float> noiseSeeds;
    float angleStep, stepSize, maxStepSize, radius;
    int sunLocX, sunLocY, totalRays, maxTotalRays;
    int maskLevel;


    void drawSpotlight();
    void drawLine();
    void drawInvitation();
    void drawMask();
   
};

