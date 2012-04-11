//
//  Explosion.cpp
//  ofxKinectExample
//
//  Created by Andy Wallace on 4/11/12.
//  Copyright (c) 2012 AndyMakes. All rights reserved.
//

#include "Explosion.h"

void Explosion::setup(ofVec2f _pos, ofImage * _pic){
    pos=_pos;
    pic=_pic;
    
    scaleVal=0.5;
    growSpeed=0.07;
    
    angle=ofRandom(360);
    rotSpeed=3;
    
    alpha=255;
    fadeSpeed=20;
    
    killMe=false;
    
}
void Explosion::update(){
    scaleVal+=growSpeed;
    angle+=rotSpeed;
    alpha-=fadeSpeed;
    
    if (alpha<0)    killMe=true;
}
void Explosion::draw(){
    
    
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofScale(scaleVal, scaleVal);
    ofRotate(angle);
    
    ofSetColor(255, 255, 255, alpha);
    pic->draw( 0,0 );
    
    ofPopMatrix();
    
}