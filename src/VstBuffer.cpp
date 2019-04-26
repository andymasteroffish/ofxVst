//
//  VstBuffer.cpp
//  vectrex_test
//
//  Created by Andrew Wallace on 4/9/19.
//

#include "VstBuffer.hpp"

void VstBuffer::createSerial(){
    // finding the right port requires picking it from the list
    // should look for one that matches "ttyACM*" or "tty.usbmodem*"
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    int baud = 9600;
    serial.setup(0, baud); //open the first device
    
    //Andy test
//    unsigned char myByte = 0;//225;
//    cout<<"test val "<<myByte<<endl;
//    bool byteWasWritten = serial.writeByte(myByte);
//    if ( !byteWasWritten )
//        printf("byte was not written to serial port");
//    //test done
//    cout<<"TEST DONE"<<endl;
    
}

//void VstBuffer::setSerial(ofSerial _serial) {
//    serial = _serial;
//}

bool VstBuffer::add(VstFrame frame) {
    if (list.size() > MAX_FRAMES) {
        cout<<"VstBuffer at capacity. Vector discarded."<<endl;
        return false;
    }
    list.push_back(frame);
    return true;
}

void VstBuffer::update() {
    //this seems very suspect. why are we duplicating the list?
    
    vector<VstFrame> temp = sort();
    
    //list.clear();
    //list.reserve(temp.size());
    for (int i=0; i<temp.size(); i++){
        list[i] = VstFrame(temp[i].x, temp[i].y, temp[i].z);
    }
}

bool VstBuffer::add(int x, int y, int z) {
    //cout<< list.size()<<" out of " << MAX_FRAMES<<endl;
//    if (list.size() > 200) {
//        cout<<"VstBuffer at capacity. Vector discarded."<<endl;
//        return false;
//    }
    
    int size = list.size();
    // scale z from 8 bit to 6 bit
    z = z * 64 / 256;
    if (list.size() < LENGTH - HEADER_LENGTH - TAIL_LENGTH - 1) {   //todo: this does not cut things off before they destroy themselves
        // If consecutive z values are zero, replace last to avoid transit redundancy
        if (z == 0 && size > 0 && list[size - 1].z == 0) {
            list[list.size() - 1] = VstFrame(x, y, z);
        } else {
            //cout<<"added "<<x<<","<<y<<","<<z<<endl;
            list.push_back(VstFrame(x, y, z));
        }
        return true;
    }
    cout<<"no good. too many lines"<<endl;
    return false;
}

void VstBuffer::send() {
    //cout<<"send "<<list.size()<<endl;
    if (list.size() == 0) {
        return;
    }
    
    if (serial.isInitialized()) {
//        //Andy test
//        unsigned char myByte = 225;
//        bool byteWasWritten = serial.writeByte(myByte);
//        if ( !byteWasWritten )
//            printf("byte was not written to serial port");
//        //test done
        
        int byte_count = 0;
        
        // Header
        buffer[byte_count++] = 0;
        buffer[byte_count++] = 0;
        buffer[byte_count++] = 0;
        buffer[byte_count++] = 0;
        
        // Data
        for (int i=0; i<list.size(); i++){
            VstFrame frame = list[i];
            int v = (2) << 30 | (frame.z & 63) << 24 | (frame.x & 4095) << 12 | (frame.y & 4095) << 0;
            buffer[byte_count++] = ((v >> 24) & 0xFF);
            buffer[byte_count++] = ((v >> 16) & 0xFF);
            buffer[byte_count++] = ((v >>  8) & 0xFF);
            buffer[byte_count++] =  ((v >>  0) & 0xFF);
        }
        
        // Tail
        buffer[byte_count++] = 1;
        buffer[byte_count++] = 1;
        buffer[byte_count++] = 1;
        buffer[byte_count++] = 1;
        
        // Send via serial
        //At least on mac, there seems to be an issue with ofSerial.writeBytes where it will only send 1024 bytes at a time
        //to get around this, if the number of bytes exceeds that amount, I send them in backages
        
        int cutoff = 1024;
        
        //for reasons I truly do not understand, setting ofLog to verbose so that serial.writeBytes prints out how many bytes were printed will allow this to draw many more lines without crahsing the teensy on the vectrex
        //I can push about 170 lines without ofSetLogLevel(OF_LOG_VERBOSE) and around 450 with it
        ofLogLevel prev_log_level = ofGetLogLevel();
        if (byte_count > cutoff){
            ofSetLogLevel(OF_LOG_VERBOSE);
        }
        //cout<<"send now "<<byte_count<<endl;
        
        if (byte_count <= cutoff){
            serial.writeBytes(&buffer[0], byte_count);
        }else{
            int pos = 0;
            while(pos<byte_count){
                int end = MIN(pos+cutoff, byte_count);
                int length = end-pos;
                serial.writeBytes(&buffer[pos], length);
                pos += cutoff;
            }
        }
        //put the log level back
        ofSetLogLevel(prev_log_level);
    }else{
        cout<<"serial not Initialized"<<endl;
    }
    
    list.clear();
}

vector<VstFrame> VstBuffer::sort() {
    vector<VstFrame> destination;
    vector<VstFrame> src(list );    //clones the vector
    //VstBuffer src = (VstBuffer) clone();
    
//    cout<<"STARTING"<<endl;
//    for(int i=0; i<list.size(); i++){
//        cout<<"  "<<i<<" "<<list[i].x<<","<<list[i].y<<","<<list[i].z<<endl;
//    }
    
    // short circuit to avoid sorting
    //if (true) return src;
    
    VstFrame lastFrame = VstFrame(1024, 1024, 0);
    VstFrame nearestFrame = lastFrame;
    
    while (src.size() != 0) {
        int startIndex = 0;
        int endIndex = 0;
        float nearestDistance = 100000;
        int i = 0;
        bool reverseOrder = false;
        
        while (i < src.size()) {
            int j = i;
            while (j < src.size() - 1 && src[j + 1].z > 1) {
                j++;
            }
            
            VstFrame startFrame = src[i];
            VstFrame endFrame = src[j];    // j = index of inclusive right boundary
            float startDistance = ofDist(lastFrame.x, lastFrame.y, startFrame.x, startFrame.y);
            float endDistance = ofDist(lastFrame.x, lastFrame.y, endFrame.x, endFrame.y);
            
            if (startDistance < nearestDistance) {
                startIndex = i;
                endIndex = j;
                nearestDistance = startDistance;
                nearestFrame = startFrame;
                //cout<<"less "<<i<<"  "<<j<<endl;
            }
            if (!startFrame.equals(endFrame) && endDistance < nearestDistance) {
                startIndex = i;
                endIndex = j;
                nearestDistance = endDistance;
                nearestFrame = endFrame;
                reverseOrder = true;
                //cout<<"same"<<endl;
            }
            i = j + 1;
        }
        
        //reverseOrder = false;   //andy edit
        VstFrame startFrame = src[startIndex];
        VstFrame endFrame = src[endIndex];
        
        if (reverseOrder) {
            // Swap commands of first and last segment if in reverse order
            // THIS NEEDED TO BE POINTERS to actually change the data
            VstFrame * t0 = &src[startIndex];
            VstFrame * t1 = &src[endIndex];
            int temp = t0->z;
            t0->z = t1->z;
            t1->z = temp;
            
            lastFrame = startFrame;
            for (int index = endIndex; index >= startIndex; index--) {
                destination.push_back(src[index]);
            }
        } else {
            lastFrame = endFrame;
            for (int index = startIndex; index <= endIndex; index++) {
                destination.push_back(src[index]);
            }
        }
        
        src.erase(src.begin()+startIndex, src.begin()+endIndex + 1);
    }
    
//    cout<<"DONE"<<endl;
//    for(int i=0; i<list.size(); i++){
//        cout<<"  "<<i<<" "<<destination[i].x<<","<<destination[i].y<<","<<destination[i].z<<endl;
//    }
    
    return destination;
}

float VstBuffer::measureTransitDistance(vector<VstFrame> fList) {
    float distance = 0.0;
    VstFrame last = VstFrame(1024, 1024, 0);
    for (VstFrame f : fList) {
        distance += ofDist(f.x, f.y, last.x, last.y);
        last = f;
    }
    return distance;
}
