#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxLeapMotion2.h"

#include "ofxGui.h"

#define ZOOMSPEED 4.0

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void mouseMoved(int x, int y );
		
        // User interface functions for sliders
        void zoomSliderChanged(float & newZoomVal);
        void rotateSpeedSliderChanged(float & newRotSpeed);
    
        // User interface functions for buttons
        void loadModel();
        void reset();
    
        // User interface objects
        ofxLabel leapLabel;
        ofxPanel gui;
        ofxButton loadModelButton;
        ofxButton resetButton;
        ofxFloatSlider zoomSlider;
        ofxFloatSlider rotateSpeedSlider;
    
        // Lighting
        ofLight  spotLight;
        ofLight light;
        ofLight amb;
    
        // Model object
        ofxAssimpModelLoader model;
    
        // Leap motion object
        ofxLeapMotion leap;
    
        // Model manipulation objects
        float modelRotate;
        float rotSpeedMult;
        float zoom;
};
