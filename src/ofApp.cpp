#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    
    // Setup lighting
    glShadeModel(GL_SMOOTH);
    ofSetGlobalAmbientColor(ofColor(125, 125, 125));
    light.enable();
    amb.setAmbientColor(ofColor(20.0, 20.0, 20.0, 20.0));
    
    // Load default model
    model.loadModel(ofToDataPath("dwarf.x"));
    model.setPosition(model.getSceneCenter().x,
                      model.getSceneCenter().y,
                      model.getSceneCenter().z);
    model.setScaleNormalization(true);
    
    // Open leap motion
    leap.open();
    
    // Load User Interface
    loadModelButton.addListener(this, &ofApp::loadModel);
    resetButton.addListener(this, &ofApp::reset);
    zoomSlider.addListener(this, &ofApp::zoomSliderChanged);
    rotateSpeedSlider.addListener(this, &ofApp::rotateSpeedSliderChanged);
    gui.setup();
    gui.add(loadModelButton.setup("load model"));
    gui.add(resetButton.setup("reset"));
    gui.add(zoomSlider.setup("zoom", 0, -1000, 1000));
    gui.add(rotateSpeedSlider.setup("rotate", 1.0, 0.0, 5.0));
    gui.add(leapLabel.setup("leapConnected", ": false"));
}

//--------------------------------------------------------------
void ofApp::update()
{
    // Get hands from leap motion
    vector <ofxLeapMotionSimpleHand> simpleHands = leap.getSimpleHands();
    
    if( leap.isFrameNew() && simpleHands.size() )
    {
        // Use the first hand to set x rotation of model
        modelRotate = ofMap(simpleHands[0].handPos.x, -200, 200, 0,360,true) * rotSpeedMult;
    }
    
    // Update label on user interface
    if(leap.isConnected())
    {
        leapLabel = ": true";
    }else
    {
        leapLabel = ": false";
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // Set background as gradient
    ofBackgroundGradient(ofColor(175), ofColor(100));
    
    // Set up lighting
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    ofEnableLighting();
    light.enable();
    spotLight.enable();
    spotLight.setPosition(0, 0, 0);
    
    
    ofPushStyle();
    ofPushMatrix();
    ofSetColor(255, 255, 255, 255);
    
    // Move model to center of screen
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.65, zoom);
    
    ofVec3f max = model.getSceneMax(true);
    ofVec3f min = model.getSceneMin(true);
    ofVec3f diff = max ;
    ofVec3f center = model.getSceneCenter();
    
    // Rotate model
    ofRotateY(modelRotate);
    
    // Center model
    ofTranslate( (model.getNormalizedScale() * center.x ) / 2.0,
                 (model.getNormalizedScale() * center.y ) / 2.0,
                 (model.getNormalizedScale() * center.z ) / 2.0
                );
    
    // Draw model
    model.drawFaces();
    
    ofPopMatrix();
    ofPopStyle();
    
    // Disable lighting (so that it is not applied to user interface)
    spotLight.disable();
    light.disable();
    ofDisableLighting();
    glDisable( GL_NORMALIZE );
    glDisable( GL_DEPTH_TEST );
    
    // Draw user interface
    gui.draw();
    
   
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    // Uncomment this to enable rotation of model by mouse
    //modelRotate = ofMap(x, 0,ofGetWidth(), 0,360)*rotSpeedMult;
}

void ofApp::reset()
{
    // Reset transformation of model
    rotSpeedMult = 1.0;
    zoomSlider   = 0.0;
    modelRotate  = 0.0;
}

void ofApp::loadModel()
{
    // Open a file open dialog box to select model
    ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a model");
    
    //Check if the user opened a file
    if (openFileResult.bSuccess)
    {
        // Load model
        model.loadModel(openFileResult.getPath());
    }
}

// When user moves zoom slider
void ofApp::zoomSliderChanged(float & newZoomVal)
{
    zoom = newZoomVal;
}

// When user moves rotation slider
void ofApp::rotateSpeedSliderChanged(float & newRotSpeed)
{
    rotSpeedMult = newRotSpeed;
}

