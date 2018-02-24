#include "ofApp.h"

using namespace glm;

void ofApp::setup(){
    
//    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofBackground(0);
    ofSetColor(255);
    ofSetCircleResolution(50);
    
    proj.setup();
    proj.getCamera().setPosition(0,0,0);
    proj.getCamera().setNearClip(1);
    proj.getCamera().setFarClip(10000);
    
    normalCam.setNearClip(0.01);
    normalCam.setFarClip(1000);
    normalCam.setDistance(50);
    
    gui.setup();
    prm.add(bDraw2dGuide.set("Draw 2D Guide", false));
    prm.add(bDrawPoints.set("Draw Points", true));
    prm.add(bDrawLines.set("Draw Lines", true));
    prm.add(bDrawTriangles.set("Draw Triangles", true));
    gui.add(fps.setup("fps", "0"));
    gui.add(prm);
    gui.add(btnSaveScreen.setup("save screen"));
    btnSaveScreen.addListener(this, &ofApp::saveScreen);
    
    float cd = 7.44;
    float ch = 2.15;
    float clipAngle = atan(cd/ch);
    
    cylinder.setUseVbo(true);
    cylinder.setRadius(3.72);
    cylinder.setHeight(2.15);
    cylinder.setCapped(false);
    cylinder.setResolutionRadius(16);
    cylinder.setResolutionHeight(3);
    cylinder.setResolutionCap(1);
    cylinder.setPosition(0, 0, 0);
    
    box.set(1,1,1);
    box.setPosition(10,0,0);
}

void ofApp::update(){
    fps = ofToString(ofGetFrameRate());
}

void ofApp::begin(bool equi, ShaderType type){
    ofPushMatrix();
    equi ? proj.begin(type) : normalCam.begin();
}

void ofApp::end(bool equi, ShaderType type){
    equi ? proj.end(type) : normalCam.end();
    ofPopMatrix();
}

void ofApp::draw(){
    
    ofBackground(255);
    drawScene(false);
    
    ofSetupScreenOrtho();
    ofDisableDepthTest();
    gui.draw();
}

void ofApp::drawScene(bool equi){

    
//    if(bDrawPoints){
//        glPointSize(3);
//        begin(equi, ShaderType::POINT_SHADER);
//        ofSetColor(255, 0, 0);
//        //cylinder.getMesh().setMode(OF_PRIMITIVE_POINTS);
//        cylinder.draw(OF_MESH_POINTS);
//        box.draw(OF_MESH_POINTS);
//        end(equi, ShaderType::POINT_SHADER);
//    }

    if(bDrawLines){
        begin(equi, ShaderType::LINE_SHADER);

        //ofDrawAxis(1);
        ofDrawLine(3, -3, 4, 3);

        ofSetColor(0, 255, 0);
        cylinder.getMesh().setMode(OF_PRIMITIVE_LINES);
        cylinder.draw();
        //box.draw(OF_MESH_WIREFRAME);
        end(equi, ShaderType::LINE_SHADER);
    }
    
//    if(bDrawTriangles){
//        begin(equi, ShaderType::TRIANGLE_SHADER);
//        ofSetColor(0,0,255);
//        //cylinder.getMesh().setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
//        cylinder.drawWireframe();
//        box.draw(OF_MESH_WIREFRAME);
//        end(equi, ShaderType::TRIANGLE_SHADER);
//    }
}

void ofApp::saveScreen(){
    ofSaveScreen("screenshot.png");
}
