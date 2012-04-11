//
//  Explosion.h
//  ofxKinectExample
//
//  Created by Andy Wallace on 4/11/12.
//  Copyright (c) 2012 AndyMakes. All rights reserved.
//

#ifndef ofxKinectExample_Explosion_h
#define ofxKinectExample_Explosion_h

#include "ofMain.h"

class Explosion{
public:
    
    void setup(ofVec2f _pos, ofImage * _pic);
    void setupPuff(ofVec2f _pos, ofImage * _pic, float _angle); //NOT BEING USED
    void update();
    void draw();
    
    
    
    ofVec2f pos;
    
    ofImage * pic;
    
    //growing
    float scaleVal;
    float growSpeed;
    
    //fading
    float alpha;
    float fadeSpeed;
    
    //spinning
    float angle;
    float rotSpeed;
    
    //removing it
    bool killMe;
    
};



#endif
