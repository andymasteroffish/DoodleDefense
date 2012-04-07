//
//  ImmuneRedFoe.cpp
//  ofxKinectExample
//
//  Created by Andy Wallace on 12/11/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#include "ImmuneRedFoe.h"

//------------------------------------------------------------
void ImmuneRedFoe::typeSetup(int level){
    type="immune_red";
    fullHP=40+ 40*level;    //slightly reduced health
}


//------------------------------------------------------------
/*
void ImmuneRedFoe::draw(){
    ofFill();
    
    
    //have it flash if there is no path
    if (!pathFound){
        drawExplored();
    }
    
    ofSetColor(245,24,17);
    
    float rad=17;
    ofCircle(p.pos.x,p.pos.y,rad);
    
    //put some blue over it if it is frozen
    if (freezeTimer>0){
        ofSetColor(0,0,255,100);
        ofCircle(p.pos.x,p.pos.y,rad);
    }
    
    //show health
    ofSetColor(0);
    ofSetLineWidth(3);
    ofNoFill();
    ofBeginShape();
    float healthCircle=ofMap(hp,0,fullHP,0,TWO_PI);
    for (float i=0; i<healthCircle; i+=TWO_PI/30)
        ofVertex(p.pos.x+cos(i-PI/2)*rad, p.pos.y+sin(i-PI/2)*rad);
    ofEndShape(false);
    
}
 */
