//
//  Clipping.hpp
//  vectrex_test
//
//  Created by Andrew Wallace on 4/8/19.
//

#ifndef Clipping_hpp
#define Clipping_hpp

#include "ofMain.h"

class Clipping{
public:

    ofVec3f min;
    ofVec3f max;

    const static int INSIDE = 0;
    const static int LEFT = 1;
    const static int RIGHT = 2;
    const static int BOTTOM = 4;
    const static int TOP = 8;
    
    void setup(ofVec3f p0, ofVec3f p1);
    int compute_code(ofVec3f p);
    float intercept(float y, float x0, float y0, float x1, float y1);
    bool clip(ofVec3f &p0, ofVec3f &p1);
};

#endif /* Clipping_hpp */
