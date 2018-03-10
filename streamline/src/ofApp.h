#pragma once

#include "ofMain.h"
#include "ofx360Projection.h"
#include "ofxGui.h"
#include "Streamline.h"

using namespace ofx360projection;
using namespace glm;

class ofApp: public ofBaseApp{
public:
    
    static ofApp * get(){
        static ofApp * instance;
        if(!instance) instance = new ofApp();
        return instance;
    }
    
    void setup();
    void update();
    
    void draw();
    void drawScene(bool equi);
    void saveScreen();
    void begin(bool equi,  ShaderType type);
    void end(bool equi, ShaderType type);
    
    ofx360Projection proj;
    ofEasyCam normalCam;
    
    ofxPanel gui;
    ofxLabel fps;
    ofParameterGroup prm;
    ofParameter<bool> bDraw2dGuide;
    ofParameter<bool> bDraw3dGuide;
    ofParameter<bool> bDrawPoints;
    ofParameter<bool> bDrawLines;
    ofParameter<bool> bDrawTriangles;
    ofParameter<float> objDistance;
    ofParameter<float> objHeight;
    ofParameter<float> objAngle;
    ofParameter<glm::vec3> objPos;
    ofParameter<glm::vec3> objScale;
    ofParameter<glm::vec3> objOrientation;
    
    ofxButton btnSaveScreen;
    
    ofCylinderPrimitive     cylinder;    
    
    // streamline
    Streamline st;
};
