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
    normalCam.setFarClip(10000);
    normalCam.setDistance(15);
    
    gui.setup();
    prm.add(bDraw2dGuide.set("Draw 2D Guide", false));
    prm.add(bDrawPoints.set("Draw Points", true));
    prm.add(bDrawLines.set("Draw Lines", true));
    prm.add(bDrawTriangles.set("Draw Triangles", true));
    gui.add(fps.setup("fps", "0"));
//    gui.add(objDistance.set("Object Distance", 10, 0, 100));
//    gui.add(objHeight.set("Object Height", 0, -10, 10));
//    gui.add(objAngle.set("Object Angle", 0, -360, 360));
    gui.add(objPos.set("Object Pos", vec3(0,0,0), -vec3(1,1,1)*40, vec3(1,1,1)*40));
    gui.add(objScale.set("Object Scale", vec3(1,1,1), vec3(1,1,1)*0.1, vec3(1,1,1)*100));
    gui.add(objOrientation.set("Object Orientation", vec3(0,0,0), vec3(1,1,1)*-180, vec3(1,1,1)*180));
    
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
    
#pragma mark Streamline
    filesystem::path path("../../../resources/csv/streamline/");
    //st.loadData((path/"final_6ch"/"c3.csv").string(), vec3(20, 20, 20));
    st.loadData((path/"musical_cylinder"/"musical_cylinder_04_strm_03.csv").string(), vec3(20, 20, 20));
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
        end(equi, ShaderType::POINT_SHADER);
    }

    if(bDrawLines){
        begin(equi, ShaderType::LINE_SHADER);
        ofSetColor(0, 255, 0);
        if(!equi) ofDrawAxis(1);
        ofPushMatrix();
        ofTranslate(objPos);
        ofRotateXDeg(objOrientation->x);
        ofRotateYDeg(objOrientation->y);
        ofRotateZDeg(objOrientation->z);
        ofScale(objScale);
//        for(auto & s : st.streamMesh){
//            s.draw();
//        }
        
        ofNoFill();
        ofSetColor(255, 0, 0);
        ofSetCircleResolution(64);
        ofDrawCircle(0, 0, 10);
        ofPopMatrix();
        
        end(equi, ShaderType::LINE_SHADER);
    }
    
    if(bDrawTriangles){
        begin(equi, ShaderType::TRIANGLE_SHADER);
        ofSetColor(0, 0, 255);
        if(!equi)cylinder.draw(OF_MESH_WIREFRAME);
        end(equi, ShaderType::TRIANGLE_SHADER);
    }
}

void ofApp::saveScreen(){
    ofSaveScreen("screenshot.png");
}
