#pragma once

#include "ofMain.h"

class TexApp: public ofBaseApp {

public:
    
    static TexApp * get(){
        static TexApp * instance;
        if(!instance) instance = new TexApp();
        return instance;
    }
    
    TexApp();
    void setup();
    void update();
    void draw();
    
};

