#include "TexApp.h"
#include "ofApp.h"

TexApp::TexApp(){
    
    
}

void TexApp::setup(){
    
    
}

void TexApp::update(){
    
    
}

void TexApp::draw(){
    
    ofBackground(255);
    ofApp * app = ofApp::get();
    app->drawScene(true);
    
    if(app->bDraw2dGuide){
        ofPushMatrix();
        ofSetupScreenOrtho();
        ofTranslate(0,0);
        ofSetColor(100, 100);
        ofNoFill();
        float w4 = ofGetWidth()/4;
        float h  = ofGetHeight();
        ofDrawLine(w4*1, 0, w4*1, h);
        ofDrawLine(w4*2, 0, w4*2, h);
        ofDrawLine(w4*3, 0, w4*3, h);
        ofPopMatrix();
    }
}
