//
//  Vst.hpp
//  vectrex_test
//
//  Created by Andrew Wallace on 4/9/19.
//

// This code is entirely based on the Processing VST library by Trammell Hudson
// https://github.com/osresearch/vst

#ifndef Vst_hpp
#define Vst_hpp

#include "ofMain.h"
#include "VstBuffer.hpp"
#include "Clipping.hpp"

class Vst{
public:
    
    //ofSerial createSerial();
    void setup();
    //void setup(ofSerial serial);
    void display();
    void line(float bright, float x0, float y0, float x1, float y1);
    void line(float bright, ofVec3f p0, ofVec3f p1);
    bool vectorOffscreen(float x, float y);
    void point(float bright, ofVec3f v);
    void rect(float bright, float x, float y, float w, float h);
    void shape(float bright, vector<ofVec2f> &pnts, bool connect);
    void displayBuffer();
    
    ofVec3f vstToScreen(VstFrame f);
    
    ofVec2f getModelPoint(ofVec3f pnt);
    ofVec2f getModelPoint(float x, float y);
    
    ofColor colorNormal;
    ofColor colorBright;
    ofColor colorTransit;
    bool displayTransit;
    bool send_to_display;
    VstBuffer buffer;
    //private PApplet parent;
    
private:
    Clipping clip;
    int lastX;
    int lastY;
};

#endif /* Vst_hpp */
