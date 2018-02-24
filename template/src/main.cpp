#include "ofMain.h"
#include "ofApp.h"
#include "TexApp.h"
#include "ofAppGLFWWindow.h"

int main(){

    float texw = 3840*5/10;
    float texh = 2160/10;
    
    float mainw = texw;
    float mainh = 1080 - texh;

    ofGLFWWindowSettings mainSetting;
    
    mainSetting.setGLVersion(3,2);
    mainSetting.setSize(mainw, mainh-75);
    mainSetting.setPosition(ofVec2f(0, texh+75));
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(mainSetting);
    shared_ptr<ofApp> mainApp( ofApp::get());
    ofRunApp(mainWindow, mainApp);

    ofGLFWWindowSettings texSetting;
    texSetting.setGLVersion(3,2);
    texSetting.setSize(texw, texh); // 3840*5 x 2160
    texSetting.setPosition(ofVec2f(0,0));
    texSetting.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> texWindow = ofCreateWindow(texSetting);
    shared_ptr<TexApp> texApp(new TexApp);
    ofRunApp(texWindow, texApp);
        
    ofRunMainLoop();
}
