//
//  VstBuffer.hpp
//  vectrex_test
//
//  Created by Andrew Wallace on 4/9/19.
//

#ifndef VstBuffer_hpp
#define VstBuffer_hpp

#include "ofMain.h"
#include "VstFrame.h"

class VstBuffer{
public:
    
    void createSerial();
    //void setSerial(ofSerial serial);
    bool add(VstFrame frame);
    void update();
    bool add(int x, int y, int z) ;
    void send() ;
    float measureTransitDistance(vector<VstFrame> fList);
    
    vector<VstFrame> list;
    
    
private:
    vector<VstFrame> sort();
    
    //this value and the number in buffer was 8192 in the processing code
    const static int LENGTH = 8192;
    const static int HEADER_LENGTH = 4;
    const static int TAIL_LENGTH = 3;
    const static int MAX_FRAMES = (LENGTH - HEADER_LENGTH - TAIL_LENGTH - 1) / 4;
    unsigned char buffer[8192];
    ofSerial serial;
    
    
    
    
};

#endif /* VstBuffer_hpp */
