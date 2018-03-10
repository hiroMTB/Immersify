#include "TexApp.h"
#include "ofApp.h"

TexApp::TexApp(){
    
    
}

void TexApp::setup(){
    float texw = (3840*5 + 3840/3)/2;
    float texh = 2160/2;
    
    fbo.allocate(texw, texh, GL_RGB);
    // fbo.getTexture().texData.bFlipTexture = true;
    ofxTextureRecorder::Settings settings(fbo.getTexture());
    settings.imageFormat = OF_IMAGE_FORMAT_PNG;
    settings.numThreads = 12;
    settings.maxMemoryUsage = 9000000000;
    settings.folderPath = "./render/tex/" + ofGetTimestampString();
    rec.setup(settings);
}

void TexApp::update(){
    fbo.begin(ofFboBeginMode::NoDefaults);
    ofClear(255,255);
    ofBackground(255);
    ofApp * app = ofApp::get();
    app->drawScene(true);
    fbo.end();

    if(app->bStartRender && app->bSaveTex){
        rec.save(fbo.getTexture());
    }
}

void TexApp::draw(){

    ofRectangle f(0, 0, fbo.getWidth(), fbo.getHeight());
    f.scaleTo(ofGetWindowRect());
    fbo.draw(f);

    
    // Guide
    ofApp * app = ofApp::get();
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
