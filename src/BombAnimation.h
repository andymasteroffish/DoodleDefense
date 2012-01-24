//
//  BombAnimation.h
//  ofxKinectExample
//
//  Created by Andy Wallace on 12/15/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#ifndef ofxKinectExample_BombAnimation_h
#define ofxKinectExample_BombAnimation_h

#include "ofMain.h"

class BombAnimation{
public:
    
    void setup(float _x, float _y, float _size);
    void update();
    void draw();
    
    float x,y;
    float size;
    
    int endTime;
    int timer;
    
    bool done;  //flag to erase the animation when it is done
    
};

#endif
