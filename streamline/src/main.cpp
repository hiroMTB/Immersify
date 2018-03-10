#include "ofMain.h"
#include "ofApp.h"
#include "TexApp.h"
#include "ofAppGLFWWindow.h"

int main(){

    // 360 fov
    // 3840/3 is additional texture
    float texw = (3840*5 + 3840/3 )/16;
    float texh = 2160/16;
    
    float mainw = texw;
    float mainh = 1080 - texh;

    ofGLFWWindowSettings mainSetting;
    mainSetting.setGLVersion(3,2);
    mainSetting.setSize(mainw, mainh-72);
    mainSetting.setPosition(ofVec2f(0, texh+72));
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(mainSetting);
    shared_ptr<ofApp> mainApp( ofApp::get());
    ofRunApp(mainWindow, mainApp);

    ofGLFWWindowSettings texSetting;
    texSetting.setGLVersion(3,2);
    texSetting.setSize(texw, texh);
    texSetting.setPosition(ofVec2f(0,0));
    texSetting.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> texWindow = ofCreateWindow(texSetting);
    shared_ptr<TexApp> texApp(new TexApp);
    ofRunApp(texWindow, texApp);
        
    ofRunMainLoop();
}
