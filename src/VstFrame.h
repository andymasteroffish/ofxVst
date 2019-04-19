//
//  VSTFrame.h
//  vectrex_test
//
//  Created by Andrew Wallace on 4/9/19.
//

#ifndef VSTFrame_h
#define VSTFrame_h

class VstFrame {
public:
    int x;
    int y;
    int z;
    
    inline VstFrame( float _x, float _y, float _z ):x(_x), y(_y), z(_z) {}
    
    bool equals(VstFrame other){
        return x==other.x && y==other.y && z==other.z;
    }
    
//    VstFrame(int x, int y, int z) {
//        x = x;
//        y = y;
//        z = z;
//    }
};

#endif /* VSTFrame_h */
