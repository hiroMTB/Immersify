#include "ofMain.h"
#include "ofRange.h"

class Streamline{
    
public:
    
    Streamline();
    void loadData(string fileName, glm::vec3 scale);
    
    vector<ofVboMesh> streamMesh;
    vector<ofPolyline> streamPoly;
    vector<ofPolyline> magnitude;
    vector<ofPolyline> rotation;
    map<string, ofRange> range;
    map<string, int> paramId;

};
