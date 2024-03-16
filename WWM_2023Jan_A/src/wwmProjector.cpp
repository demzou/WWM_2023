#include "wwmProjector.h"

// add a constructor
wwmProjector::wwmProjector(const int windowWidth, const int windowHeight)
    : dist(0)
    , maxRad(windowHeight / 2)
    , maxTotalRays(30)
    , totalRays(10)
    , maxStepSize(100)
    , stepSize(100)
    , radAmt(0)
    , invite(false)
    , masterDimmer(1)
    , maskLevel(0)
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
        drawMasterDimmer();
    frameBuffer.end();

    return frameBuffer;
}


void wwmProjector::drawSpotlight()
{
    // DELETE: float spotlightRadius = (1 - dist) * maxRad / 0.85;

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
         
        float spotlightOuterAmount = 1;
        float spotlightInnerAmount = 0.7;

        int currMaxRad = ofMap(dist, 0, 1, maxRad * spotlightOuterAmount , maxRad * spotlightInnerAmount);
        float radiusOfSolidSpotlight = (1 - dist) * 0.3 * currMaxRad;

        ofSetColor(spotCol);
        ofFill();
        // Draw the solid spotlight
        ofDrawCircle(frameBuffer.getWidth()/ 2, frameBuffer.getHeight() / 2,radiusOfSolidSpotlight);
    ofPopStyle();

    // Draw the spotlight gradient
    for (int i = radiusOfSolidSpotlight; i < currMaxRad; i++) {
        ofPushStyle();
            float fade = ofMap(i, radiusOfSolidSpotlight, currMaxRad, 1, 0, true);
            ofSetColor(fade * spotCol);
            ofNoFill();
            ofSetLineWidth(2);
            ofDrawCircle(frameBuffer.getWidth() / 2, frameBuffer.getHeight() / 2, i);
        ofPopStyle();
    }
}


void wwmProjector::drawLine()
{
    float pinkThreshold = 0.6;
    float visibilityStartingThreshhold = 0.4;
    float visibilityEndingThreshhold = 0.5;
    //colour
    ofPushMatrix();
        ofPushStyle();
            int alpha2 = ofMap(dist, visibilityStartingThreshhold, visibilityEndingThreshhold, 0, 255, true);
            if (dist >= pinkThreshold) {
                ofColor white = ofColor(255);
                ofColor pink = ofColor(255, 178, 178);
                float colAmt = ofMap(dist, pinkThreshold, 0.75, 0, 1, true);
                ofColor newCol = white.lerp(pink, colAmt);

                ofSetColor(newCol, alpha2);
            }
            else {
                ofSetColor(255, alpha2);
            }

            ofNoFill();
            ofSetLineWidth(6);



            float lineInnerAmount = 0.25;
            float lineOuterAmount = 0.98;

            if (dist >= visibilityStartingThreshhold) {
				float lineRadius = ofMap(dist, visibilityStartingThreshhold, 1, lineOuterAmount * maxRad, lineInnerAmount * maxRad, true);

				ofTranslate(frameBuffer.getWidth() / 2, frameBuffer.getHeight() / 2);

				ofBeginShape();
					ofCurveVertex(cos(ofDegToRad(-angleStep)) * (lineRadius + ofNoise(noiseSeeds[totalRays - 1]) * stepSize), sin(ofDegToRad(-angleStep)) * (lineRadius + ofNoise(noiseSeeds[totalRays - 1]) * stepSize));
					for (int i = 0; i < totalRays; i++) {

						float noiseRadius = ofNoise(noiseSeeds[i]) * stepSize;
						ofPoint pointLocation;
						pointLocation.x = cos(ofDegToRad(angleStep * i)) * (lineRadius + noiseRadius);
						pointLocation.y = sin(ofDegToRad(angleStep * i)) * (lineRadius + noiseRadius);
						ofCurveVertex(pointLocation);
						noiseSeeds[i] += 0.01;
					}
					ofCurveVertex(cos(ofDegToRad(angleStep * 0)) * (lineRadius + ofNoise(noiseSeeds[0]) * stepSize), sin(ofDegToRad(angleStep * 0)) * (lineRadius + ofNoise(noiseSeeds[0]) * stepSize));

					ofCurveVertex(cos(ofDegToRad(angleStep)) * (lineRadius + ofNoise(noiseSeeds[1]) * stepSize), sin(ofDegToRad(angleStep)) * (lineRadius + ofNoise(noiseSeeds[1]) * stepSize));

				ofEndShape(true);



            }
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
            ofDrawCircle(frameBuffer.getWidth() / 2, frameBuffer.getHeight() / 2, radAmt);
        ofPopStyle();

        radAmt += 10;

        if (radAmt >= maxRad)  {
            invite = false;
        }
    }
}

void wwmProjector::drawMasterDimmer()
{
	maskLevel = ofMap(masterDimmer, 0, 1, 255, 0);
	ofPushStyle();
		ofSetColor(0,0,0,maskLevel);
		ofFill();
		ofDrawRectangle(0, 0, frameBuffer.getWidth(), frameBuffer.getHeight());
	ofPopStyle();
}
