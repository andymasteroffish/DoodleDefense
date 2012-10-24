//
//  BombAnimation.cpp
//  ofxKinectExample
//
//  Created by Andy Wallace on 12/15/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#include"BombAnimation.h"


void BombAnimation::setup(float _x, float _y, float _size){
    x=_x;
    y=_y;
    size=_size;
    
    timer=0;
    done=false;
    endTime=10;
}

void BombAnimation::update(){
    timer++;
    if (timer>=endTime)   done=true;
}

void BombAnimation::draw(){
    
    int sections=3;
    
//    for (int i=timer/sections; i<endTime/sections; i++){
//        ofSetColor(0, ofMap(i,0,endTime/sections,150,255), 0, 100);
//        
//        float thisSize=ofMap(i,0,endTime/sections,size,1);
//        ofCircle(x, y, thisSize);
//        
//    }
    
    for (int i=0; i<sections; i++){
        ofSetColor(0, ofMap(i,0,sections,150,255), 0, 150);
        
        
        float thisSize=ofMap(timer,0,endTime,size,1)/i;
        ofCircle(x, y, thisSize);
    }
    
}