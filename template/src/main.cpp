#include "ofMain.h"
#include "ofApp.h"
#include "TexApp.h"
#include "ofAppGLFWWindow.h"

int main(){

    float texw = 3840*5/10;
    float texh = 2160/10;
    
    float mainw = texw;
    float mainh = 1080 - texh;

    {
        ofGLWindowSettings settings;
        settings.setGLVersion(3,2);
        settings.setSize(mainw, mainh-80);
        settings.setPosition(ofVec2f(0, texh+80));
        shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
        shared_ptr<ofApp> mainApp( ofApp::get());
        ofRunApp(mainWindow, mainApp);
    }

    {
        ofGLWindowSettings settings;
        settings.setGLVersion(3,2);
        settings.setSize(texw, texh); // 3840*5 x 2160
        settings.setPosition(ofVec2f(0,0));
        shared_ptr<ofAppBaseWindow> texWindow = ofCreateWindow(settings);
        shared_ptr<TexApp> texApp(new TexApp);
        ofRunApp(texWindow, texApp);
    }
    
    ofRunMainLoop();
}
