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
        ofSetColor(0, 0, 255);
        ofNoFill();
        
        {
            int xDiv = 16;
            float w = ofGetWidth()/xDiv;
            float h  = ofGetHeight();
            
            for(int i=1; i<xDiv; i++){
                ofDrawLine(w*i, 0, w*i, h);
            }
        }
        
        {
            int yDiv = ofGetHeight()/3;
            int w = ofGetWidth();
            for(int i=1; i<yDiv; i++){
                ofDrawLine(0, yDiv*i, w, yDiv*i);
            }
        }
        
        ofPopMatrix();
    }
}
