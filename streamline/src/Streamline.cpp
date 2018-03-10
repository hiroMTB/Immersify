#include "Streamline.h"


//
// csv data format (from Paraview)
//  0 P
//  1 T
//  2 PAbs
//  3 TKE
//  4 TED
//  5 TTot
//  6 vel:0
//  7 vel:1
//  8 vel:2
//  9 IntegrationTime
// 10 Vorticity:0
// 11 Vorticity:1
// 12 Vorticity:2
// 13 Rotation
// 14 AngularVelocity
// 15 Normals:0
// 16 Normals:1
// 17 Normals:2
// 18 Points:0
// 19 Points:1
// 20 Points:2

Streamline::Streamline(){
    streamMesh.push_back(ofVboMesh());
    streamMesh.back().setMode(OF_PRIMITIVE_LINE_STRIP);
    
    streamPoly.push_back(ofPolyline());
    magnitude.push_back(ofPolyline());
    rotation.push_back(ofPolyline());
}

void Streamline::loadData(string fileName, glm::vec3 scale){
    
    ifstream file(ofToDataPath(fileName));
    
    string str;
    getline(file,str);
    {
        str.erase(str.size()-1);    // erase \r
        string prmName;
        istringstream stream(str);
        int i=0;
        while(getline(stream,prmName,'\t')){
            paramId.insert({prmName, i});
            cout << i++ << " " << prmName << " \n";
        }
    }
    
    vector<double> pos0, pos1, pos2;
    vector<double> vel0, vel1, vel2;
    vector<double> mag;
    vector<double> time;
    vector<double> rot;
    
    while(getline(file,str)){
        
        string token;
        istringstream stream(str);
        
        vector<double> entry(paramId.size());
        
        for(int i=0; i<entry.size(); i++){
            getline(stream,token,'\t');
            entry[i] = ofToDouble(token);
        }
        
        double p0 = entry[paramId["Points:0"]];
        double p1 = entry[paramId["Points:1"]];
        double p2 = entry[paramId["Points:2"]];
        double v0 = entry[paramId["vel:0"]];
        double v1 = entry[paramId["vel:1"]];
        double v2 = entry[paramId["vel:2"]];
        double t = entry[paramId["IntegrationTime"]];
        double r = entry[paramId["Rotation"]];
        
        glm::vec3 vel(v0, v1, v2);
        
        float m = glm::length(vel);
        
        pos0.push_back(p0);
        pos1.push_back(p1);
        pos2.push_back(p2);
        vel0.push_back(v0);
        vel1.push_back(v1);
        vel2.push_back(v2);
        mag.push_back(m);
        time.push_back(t);
        rot.push_back(r);
    }
    
    double pos0Min = *min_element(pos0.begin(), pos0.end());
    double pos1Min = *min_element(pos1.begin(), pos1.end());
    double pos2Min = *min_element(pos2.begin(), pos2.end());
    double vel0Min = *min_element(vel0.begin(), vel0.end());
    double vel1Min = *min_element(vel1.begin(), vel1.end());
    double vel2Min = *min_element(vel2.begin(), vel2.end());
    double magMin  = *min_element(mag.begin(), mag.end());
    double timeMin = *min_element(time.begin(), time.end());
    double rotMin = *min_element(rot.begin(), rot.end());
    
    double pos0Max = *max_element(pos0.begin(), pos0.end());
    double pos1Max = *max_element(pos1.begin(), pos1.end());
    double pos2Max = *max_element(pos2.begin(), pos2.end());
    double vel0Max = *max_element(vel0.begin(), vel0.end());
    double vel1Max = *max_element(vel1.begin(), vel1.end());
    double vel2Max = *max_element(vel2.begin(), vel2.end());
    double magMax  = *max_element(mag.begin(), mag.end());
    double timeMax = *max_element(time.begin(), time.end());
    double rotMax = *max_element(rot.begin(), rot.end());
    
    range.insert({"Points:0", ofRange(pos0Min, pos0Max)});
    range.insert({"Points:1", ofRange(pos1Min, pos1Max)});
    range.insert({"Points:2", ofRange(pos2Min, pos2Max)});
    range.insert({"vel:0", ofRange(vel0Min, vel0Max)});
    range.insert({"vel:1", ofRange(vel1Min, vel1Max)});
    range.insert({"vel:2", ofRange(vel2Min, vel2Max)});
    range.insert({"mag", ofRange(magMin, magMax)});
    range.insert({"time", ofRange(timeMin, timeMax)});
    range.insert({"Points:123", range["Points:0"] + range["Points:1"] + range["Points:2"]});
    range.insert({"vel:123", range["vel:0"] + range["vel:1"] + range["vel:2"]});
    range.insert({"Rotation", ofRange(rotMin, rotMax)});
    
    for(int i=0; i<pos0.size(); i++){
        
        if(time[i] == 0){
            streamMesh.push_back(ofVboMesh());
            streamMesh.back().setMode(OF_PRIMITIVE_LINE_STRIP);
            
            streamPoly.push_back(ofPolyline());
            magnitude.push_back(ofPolyline());
            rotation.push_back(ofPolyline());
        }
        
        glm::vec3 pos(pos0[i], -pos1[i], pos2[i]);
        glm::vec3 vel(vel0[i], vel1[i], vel2[i]);
        
        pos.x -= range["Points:0"].center();
        pos.y -= range["Points:1"].center();
        pos.z -= range["Points:2"].center();
        
        ofRange xyzRange = range["Points:0"] + range["Points:1"] + range["Points:2"];
        float span = xyzRange.span();
        
        pos /= span;
        pos *= scale;
        
        float m = mag[i];
        float cRate = m * 0.004;
        ofFloatColor red(1,0,0);
        ofFloatColor blue(0,0,1);
        ofFloatColor col;
        col =  red*cRate + blue*(1.0-cRate);
        col.a = 0.2;
        
        streamMesh.back().addVertex(pos);
        streamMesh.back().addColor(col);
        streamPoly.back().addVertex(pos);
        
        int vId = streamMesh.back().getNumVertices();
        magnitude.back().addVertex(glm::vec3(vId, m, 0));
        
        float r = rot[i];
        rotation.back().addVertex(glm::vec3(vId, r, 0));
        
    }
    
    int numStream = streamPoly.size();
    cout << endl << "create " << numStream << " polylines" << endl;
    
    // deleted short streams
    if(0){
        vector<ofVboMesh>::iterator  meshit = streamMesh.begin();
        vector<ofPolyline>::iterator polyit = streamPoly.begin();
        vector<ofPolyline>::iterator magit  = magnitude.begin();
        vector<ofPolyline>::iterator rotit  = rotation.begin();
        
        int numDeleted = 0;
        for(int i=0; meshit!=streamMesh.end(); i++, meshit++, polyit++, magit++, rotit++){
            
            int num = meshit->getNumVertices();
            float length = polyit->getLengthAtIndex(polyit->getPerimeter());
            if(length < 600 || num<30){
                streamMesh.erase(meshit--);
                streamPoly.erase(polyit--);
                magnitude.erase(magit--);
                rotation.erase(rotit--);
                numDeleted++;
            }
        }
        cout << "deleted " << numDeleted << " data because too few vertices : " << endl;
        
        numStream = streamPoly.size();
    }
}
