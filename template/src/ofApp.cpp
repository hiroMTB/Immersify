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
    
    normalCam.setNearClip(0.1);
    normalCam.setFarClip(1000);
    normalCam.setDistance(15);
    
    gui.setup();
    prm.add(bDraw2dGuide.set("Draw 2D Guide", false));
    prm.add(bDrawPoints.set("Draw Points", true));
    prm.add(bDrawLines.set("Draw Lines", true));
    prm.add(bDrawTriangles.set("Draw Triangles", true));
    gui.add(fps.setup("fps", "0"));
    gui.add(objDistance.set("Object Distance", 10, 0, 100));
    gui.add(objHeight.set("Object Height", 0, -10, 10));
    gui.add(objAngle.set("Object Angle", 0, -180, 180));
    
    gui.add(prm);
    gui.add(btnSaveScreen.setup("save screen"));
    btnSaveScreen.addListener(this, &ofApp::saveScreen);
    
    float cd = 7.44;
    float ch = 2.15;
    float clipAngle = atan(cd/ch);
    
    cylinder.setRadius(3.72);
    cylinder.setHeight(2.15);
    cylinder.setCapped(false);
    cylinder.setResolutionRadius(16);
    cylinder.setResolutionHeight(3);
    cylinder.setPosition(0, 0, 0);
    
    box.set(1,1,1);
    box.setResolution(2);
    box.setPosition(-objDistance,objHeight,0);
    
    sphere.setRadius(1);
    sphere.setResolution(1);
    sphere.setPosition(0, objHeight, -objDistance);

    cone.setRadius(1);
    cone.setHeight(2);
    cone.setPosition(objDistance, objHeight, 0);
    cone.setResolution(12, 1, 1);
    cone.setOrientation(vec3(180,0,0));
    
}

void ofApp::update(){
    fps = ofToString(ofGetFrameRate());

    float y = objHeight;
    float deg = ofDegToRad(objAngle);
    {
        float deg1 = deg + PI;
        float x = cos(deg1) * objDistance;
        float z = sin(deg1) * objDistance;
        box.setPosition(x,y,z);
    }
    
    {
        float deg1 = deg - HALF_PI;
        float x = cos(deg1) * objDistance;
        float z = sin(deg1) * objDistance;
        sphere.setPosition(x,y,z);
    }
    
    {
        float deg1 = deg;
        float x = cos(deg1) * objDistance;
        float z = sin(deg1) * objDistance;
        cone.setPosition(x,y,z);
    }
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
    ofDrawAxis(1);
    drawScene(false);
    
    ofSetupScreenOrtho();
    ofDisableDepthTest();
    gui.draw();
}

void ofApp::drawScene(bool equi){

    
    if(bDrawPoints){
        glPointSize(5);
        begin(equi, ShaderType::POINT_SHADER);
        ofSetColor(255, 0, 0);
        cylinder.draw(OF_MESH_POINTS);
        box.draw(OF_MESH_POINTS);
        sphere.draw(OF_MESH_POINTS);
        cone.draw(OF_MESH_POINTS);
        
        end(equi, ShaderType::POINT_SHADER);
    }

    if(bDrawLines){
        begin(equi, ShaderType::LINE_SHADER);
        ofSetColor(0, 255, 0);
        if(!equi) ofDrawAxis(1);
        box.draw(OF_MESH_WIREFRAME);
        sphere.draw(OF_MESH_WIREFRAME);
        cone.draw(OF_MESH_WIREFRAME);
        end(equi, ShaderType::LINE_SHADER);
    }
    
    if(bDrawTriangles){
        begin(equi, ShaderType::TRIANGLE_SHADER);
        ofSetColor(0, 0, 255);
        if(!equi)cylinder.draw(OF_MESH_WIREFRAME);
        
        box.draw(OF_MESH_WIREFRAME);
        sphere.draw(OF_MESH_WIREFRAME);
        cone.draw(OF_MESH_WIREFRAME);
        end(equi, ShaderType::TRIANGLE_SHADER);
    }
}

void ofApp::saveScreen(){
    ofSaveScreen("screenshot.png");
}
