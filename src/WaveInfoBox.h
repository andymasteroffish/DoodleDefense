//
//  WaveInfoBox.h
//  ofxKinectExample
//
//  Created by Andy Wallace on 4/11/12.
//  Copyright (c) 2012 AndyMakes. All rights reserved.
//

#ifndef ofxKinectExample_WaveInfoBox_h
#define ofxKinectExample_WaveInfoBox_h

#include "ofMain.h"

class WaveInfoBox{
public:
    
    void setup(int _waveNum, string _message, ofTrueTypeFont * _waveFont, ofTrueTypeFont * _messageFont, string colorID, float startX, float startY, float _boxW, float _boxH);
    void draw();
    
    //position
    ofVec2f pos;
    float boxW;
    float boxH;
    
    //the message
    int waveNum;
    string message;
    
    //display info
    ofColor bgColor;
    ofTrueTypeFont * waveFont;
    ofTrueTypeFont * messageFont;
    
    ofPoint waveTextOffset;
    ofPoint messageTextOffset;
    
    //fading
    float alpha;
    
    bool fading;
    float fadeSpeed;
    
    //falling
    float fallSpeed;
    
    
};


#endif
