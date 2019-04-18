//
//  Vst.cpp
//  vectrex_test
//
//  Created by Andrew Wallace on 4/9/19.
//

#include "Vst.hpp"

Vst* Vst::instance = NULL;

Vst* Vst::getInstance()
{
    if (instance == NULL)
    {
        instance = new Vst();
    }
    
    return instance;
}


Vst::Vst(){
    setup();
}

void Vst::setup() {
    buffer.createSerial();
    clip.setup(ofVec3f(0, 0), ofVec3f(ofGetWidth() - 1, ofGetHeight() - 1));
    
    colorNormal = ofColor(128, 128, 128, 80);
    colorBright = ofColor(255, 255, 255, 255);
    colorTransit = ofColor(255, 0, 0, 80);
    displayTransit = false;
    send_to_display = false;
    
    for (int i=0; i<VST_DEBUG_HISTORY; i++){
        num_draws_history[i] = 0;
    }
}


void Vst::display() {
    
    int num_lines = buffer.list.size();
    
    buffer.update();
    displayBuffer();
    buffer.send();
    lastX = -1;       // TODO: Better choice for resetting lastX and lastY?
    lastY = -1;
    
    for (int i=VST_DEBUG_HISTORY-1; i >0; i--){
        num_draws_history[i] = num_draws_history[i-1];
    }
    num_draws_history[0] = num_lines;
    
    avg_num_draws = 0;
    for (int i=0; i<VST_DEBUG_HISTORY; i++){
        avg_num_draws += num_draws_history[i];
    }
    avg_num_draws /= (float)VST_DEBUG_HISTORY;
}

void Vst::drawDebugInfo(){
    float box_w = 100;
    float box_h = 50;
    ofSetColor(0,100);
    ofFill();
    ofDrawRectangle(0, 0, box_w, box_h);
    
    ofSetColor(0,255,0);
    string output = "";
    output += "this frame: "+ofToString(num_draws_history[0])+"\n";
    output += "avrg draws: "+ofToString(avg_num_draws)+"\n";
    ofDrawBitmapString(output, 5, 15);
}

void Vst::line(float bright, float x0, float y0, float x1, float y1) {
    line(bright, ofVec3f(x0, y0), ofVec3f(x1, y1));
}

void Vst::line(float bright, ofVec3f p0, ofVec3f p1) {
//    if (p0 == null || p1 == null) {
//        return;
//    }
    
    //cout<<"line from "<<p0.x<<","<<p0.y<<","<<p0.z<<endl;
    //cout<<"       to "<<p1.x<<","<<p1.y<<","<<p1.z<<endl;
    
    // can we detect resize?
    clip.max.x = ofGetWidth() - 1;
    clip.max.y = ofGetHeight() - 1;
    
    //modeX and modelY do not exist in openFrameworks
    //I hammerred together my own verison, but it is probably pretty funky and only tested with 2D
    
    p0 = getModelPoint(p0);
    p1 = getModelPoint(p1);
//    // Preserve original points
//    p0 = p0.copy();
//    p1 = p1.copy();
//
//    // Create temp versions for modelXY()
//    ofVec3f pt0 = p0.copy();
//    ofVec3f pt1 = p1.copy();
//
//    p0.x = modelX(pt0.x, pt0.y, pt0.z);
//    p0.y = modelY(pt0.x, pt0.y, pt0.z);
//    p1.x = modelX(pt1.x, pt1.y, pt1.z);
//    p1.y = modelY(pt1.x, pt1.y, pt1.z);
    
    if (!clip.clip(p0, p1)) {
        return;
    }
    
    // The clip above should ensure that this never happens
    // but just in case, we will discard those points
    if (vectorOffscreen(p0.x, p0.y) || vectorOffscreen(p1.x, p1.y)) {
        return;
    }
    
    point(0, p0);
    point(bright, p1);
}

bool Vst::vectorOffscreen(float x, float y) {
    return (x < 0 || x >= ofGetWidth() || y < 0 || y >= ofGetHeight());
}

void Vst::point(float bright, ofVec3f v) {
    int x = (int) (v.x * 4095 / ofGetWidth());
    int y = (int) (4095 - (v.y * 4095 / ofGetHeight()));
    
    if (x == lastX && y == lastY) {
        return;
    }
    
    lastX = x;
    lastY = y;
    //cout<<"point "<<x<<","<<y<<endl;
    buffer.add(x, y, (int) bright);
}

void Vst::rect(float bright, float x, float y, float w, float h) {
    ofRectMode mode = ofGetRectMode();
    
    if (mode == OF_RECTMODE_CENTER){
        x -= w/2;
        y -= h/2;
    }
    
    line(bright, x+0, y+0, x+w, y+0);
    line(bright, x+w, y+0, x+w, y+h);
    line(bright, x+w, y+h, x+0, y+h);
    line(bright, x+0, y+h, x+0, y+0);
}

//added by Andy,
void Vst::shape(float bright, vector<ofVec2f> &pnts, bool connect){
    for (int i=0; i<pnts.size()-1; i++){
        line(bright, pnts[i].x, pnts[i].y, pnts[i+1].x, pnts[i+1].y);
    }
    if (connect){
        line(bright, pnts[pnts.size()-1].x, pnts[pnts.size()-1].y, pnts[0].x, pnts[0].y);
    }
}
void Vst::shape(float bright, vector<ofPoint> &pnts, bool connect){
    for (int i=0; i<pnts.size()-1; i++){
        line(bright, pnts[i].x, pnts[i].y, pnts[i+1].x, pnts[i+1].y);
    }
    if (connect){
        line(bright, pnts[pnts.size()-1].x, pnts[pnts.size()-1].y, pnts[0].x, pnts[0].y);
    }
}

void Vst::circle(float bright, float center_x, float center_y, float size, int num_pnts){
    vector<ofVec2f> pnts;
    float angle_step =(TWO_PI/(float)num_pnts);
    for (int i=0; i<num_pnts; i++){
        ofVec2f pnt;
        float angle = angle_step  * i;
        
        pnt.x = 0 + sin(angle) * size;
        pnt.y = 0 + cos(angle) * size;
        pnts.push_back(pnt);
    }
    
    shape(bright, pnts, true);
}

void Vst::triangle(float bright, float x1, float y1, float x2, float y2, float x3, float y3){
    line(bright, x1,y1, x2,y2);
    line(bright, x2,y2, x3,y3);
    line(bright, x3,y3, x1,y1);
}

void Vst::displayBuffer() {
    ofNoFill();
    send_to_display = true;
    
    //cout<<"list size "<<buffer.list.size()<<endl;
    
    ofVec3f lastPoint = ofVec3f(ofGetWidth() / 2.0, ofGetHeight() / 2.0);  // Assumes V.st re-centers
    for (int i=0; i<buffer.list.size(); i++){
        VstFrame f = buffer.list[i];
        ofVec3f p = ofVec3f((float) (f.x / 4097.0) * ofGetWidth(), (float) ((4097 - f.y) / 4097.0) * ofGetHeight());
        
        if (f.z == 0) {
            // Transit
            if (displayTransit) {
                ofSetColor(colorTransit);
                ofDrawLine(lastPoint.x, lastPoint.y, p.x, p.y);
            }
        } else if (f.z < 63) {
            // Normal
            ofSetColor(f.z * 256.0f / 64.0f);
            //ofSetColor(255,0,0);
            ofDrawLine(lastPoint.x, lastPoint.y, p.x, p.y);
            
        } else if (f.z == 63) {
            // Bright
            ofSetColor(colorBright);
            ofDrawLine(lastPoint.x, lastPoint.y, p.x, p.y);
        }
        lastPoint = p;
    }
    
    send_to_display = false;
}


ofVec3f Vst::vstToScreen(VstFrame f) {
    return ofVec3f((float) (f.x / 2047.0) * ofGetWidth(), (float) ((2047 - f.y) / 2047.0) * ofGetHeight());
}

//This function is by Andy, it attempts to recreate the functionality of modelX() and modelY() in Processing
//Currently it only works in 2D. 3D transformations will break it.
//it sometimes gets locked at 90 degree angles when the actual angle is 89 or 91. Not sure why
//it could definitely be more efficient by using quaternions properly
ofVec2f Vst::getModelPoint(ofVec3f pnt){
    return getModelPoint(pnt.x, pnt.y);
}
ofVec2f Vst::getModelPoint(float x, float y){
    //get the model of th current matrix
    GLfloat m[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, m);
    ofMatrix4x4 mat(m);
    
    //check if this model matches the baseline, no matrix model and avoid a lot of unecessary work if it does
    ofVec4f baseline[4];
    baseline[0] = ofVec4f(1,0,0,0);
    baseline[1] = ofVec4f(0,1,0,0);
    baseline[2] = ofVec4f(0,0,1,0);
    baseline[3] = ofVec4f(-ofGetWidth()/2,-ofGetHeight()/2,-1,1);   //the z value is the wildcard. I'm not sure how it is set
    
    bool matches = true;
    for (int i=0; i<4; i++){
        if (mat._mat[i].x != baseline[i].x) matches = false;
        if (mat._mat[i].y != baseline[i].y) matches = false;
        if (mat._mat[i].z != baseline[i].z && i!=3) matches = false;
        if (mat._mat[i].w != baseline[i].w) matches = false;
    }
    
    //if it all matches the baseline, we're not in a matrix and can just return the input values
    if (matches){
        //cout<<"nothing doing"<<endl;
        return ofVec2f(x,y);
    }
    
    //get the model of the default screen (this can't be used as the baseline above for reasons I don't totally understand)
    ofMatrix4x4 ident = ofMatrix4x4::newIdentityMatrix();
    
    //extract info from that
    ofVec3f trans_val = mat.getTranslation();
    ofVec3f scale_val = mat.getScale();
    ofQuaternion quat = mat.getRotate();
    ofVec3f rot_val = quat.asVec3();
    ofVec3f euler = quat.getEuler();
    
    
    ofPoint origPoint = ofPoint(x,y);
    ofVec2f scaled_point;
    scaled_point.x = origPoint.x * scale_val.x;
    scaled_point.y = origPoint.y * scale_val.y;
    
    float euler_deg = euler.z;
    if (euler.x != 0){  //the euler degreees start counting back from 90 and the x and y values of rot_val go to 180
        euler_deg = 90 + (90-euler_deg);
    }
    float mat_angle = ofDegToRad (euler_deg);
    float base_angle = atan2(scaled_point.x, scaled_point.y);   //shouldn't this be y then x??? Not sure why this works
    float angle = base_angle - mat_angle;
    
    float dist = scaled_point.length();
    
    ofVec2f return_val;
    return_val.x = sin(angle) * dist +  (ofGetWidth()/2 + trans_val.x);
    return_val.y = cos(angle) * dist + (ofGetHeight()/2 + trans_val.y);
    
    return return_val;
}
