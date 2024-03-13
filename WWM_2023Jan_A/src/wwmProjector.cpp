#include "wwmProjector.h"

// add a constructor
wwmProjector::wwmProjector(const int windowWidth, const int windowHeight)
    : dist(0)
    , maxRad(ofGetHeight() / 2)
    , maxTotalRays(30)
    , totalRays(10)
    , maxStepSize(100)
    , stepSize(100)
    , radAmt(0)
    , invite(false)
{
 
    for (int i = 0; i < maxTotalRays; i++) {
        noiseSeeds.push_back(ofRandom(0, 10000));
    }

    frameBuffer.allocate(windowWidth, windowHeight, GL_RGBA32F_ARB);
}


ofFbo wwmProjector::draw()
{
    frameBuffer.begin();
        ofClear(0, 0, 0, 0);
        
        drawSpotlight();
        drawLine();
        drawInvitation();
    frameBuffer.end();

	return frameBuffer;
}


void wwmProjector::drawSpotlight()
{
    float radius1 = (1 - dist) * maxRad / 0.85;

    totalRays = ofMap(dist, 0, 1, 4, maxTotalRays, true);
    stepSize = ofMap(dist, 0, 1, 1, maxStepSize, true);

    angleStep = 360.0 / totalRays;

    ofPushStyle();
        ofColor spotCol;

        if (dist >= 0.6) {
            ofColor white = ofColor(255);
            ofColor pink = ofColor(254, 127, 156);
            float colAmt = ofMap(dist, 0.6, 0.7, 0, 1, true);
            spotCol = white.lerp(pink, colAmt);
        }
        else {
            int alpha = ofMap(dist, 0.4, 0.6, 255, 255, true);
            spotCol = ofColor(alpha);
        }

        int currMaxRad = ofMap(dist, 0, 1, maxRad, maxRad * 0.7);


        ofSetColor(spotCol);
        ofFill();
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, (1 - dist) * 0.3 * currMaxRad);
    ofPopStyle();

    for (int i = (1 - dist) * 0.3 * currMaxRad; i < currMaxRad; i++) {
        ofPushStyle();
            float fade = ofMap(i, (1 - dist) * 0.3 * currMaxRad, currMaxRad, 1, 0, true);
            ofSetColor(fade * spotCol);
            ofNoFill();
            ofSetLineWidth(2);
            ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, i);
        ofPopStyle();
    }
}


void wwmProjector::drawLine()
{
    //colour
    ofPushMatrix();
        ofPushStyle();
            int alpha2 = ofMap(dist, 0.4, 0.5, 0, 255, true);
            if (dist >= 0.6) {
                ofColor white = ofColor(255);
                ofColor pink = ofColor(255, 178, 178);
                float colAmt = ofMap(dist, 0.6, 0.75, 0, 1, true);
                ofColor newCol = white.lerp(pink, colAmt);

                ofSetColor(newCol, alpha2);
            }
            else {
                ofSetColor(255, alpha2);
            }

            ofNoFill();
            ofSetLineWidth(6);


            float dist2 = ofMap(dist, 0, 1, -0.8, 0.7, true);
            float radius2 = (1 - dist2) * maxRad;

            ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

            ofBeginShape();
                ofCurveVertex(cos(ofDegToRad(-angleStep)) * (radius2 + ofNoise(noiseSeeds[totalRays - 1]) * stepSize), sin(ofDegToRad(-angleStep)) * (radius2 + ofNoise(noiseSeeds[totalRays - 1]) * stepSize));
                for (int i = 0; i < totalRays; i++) {

                    float noiseRadius = ofNoise(noiseSeeds[i]) * stepSize;
                    ofPoint pointLocation;
                    pointLocation.x = cos(ofDegToRad(angleStep * i)) * (radius2 + noiseRadius);
                    pointLocation.y = sin(ofDegToRad(angleStep * i)) * (radius2 + noiseRadius);
                    ofCurveVertex(pointLocation);
                    noiseSeeds[i] += 0.01;
                }
                ofCurveVertex(cos(ofDegToRad(angleStep * 0)) * (radius2 + ofNoise(noiseSeeds[0]) * stepSize), sin(ofDegToRad(angleStep * 0)) * (radius2 + ofNoise(noiseSeeds[0]) * stepSize));

                ofCurveVertex(cos(ofDegToRad(angleStep)) * (radius2 + ofNoise(noiseSeeds[1]) * stepSize), sin(ofDegToRad(angleStep)) * (radius2 + ofNoise(noiseSeeds[1]) * stepSize));

            ofEndShape(true);

        ofPopStyle();
    ofPopMatrix();
}


void wwmProjector::drawInvitation()
{
    if (invite) {
        ofPushStyle();
            ofSetColor(255);
            ofNoFill();
            ofSetLineWidth(6);
            ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, radAmt);
        ofPopStyle();

        radAmt += 10;

        if (radAmt >= maxRad * 2) {
            invite = false;
        }
    }
}