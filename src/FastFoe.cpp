//
//  FastFoe.cpp
//  opencvExample
//
//  Created by Andy Wallace on 12/6/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#include "FastFoe.h"

//------------------------------------------------------------
void FastFoe::typeSetup(int level){
    type="fast";
    speed=0.2;
}


//------------------------------------------------------------
/*
void FastFoe::draw(){
    ofFill();
    
    
    
    //have it flash if there is no path
    if (!pathFound){
        drawExplored();
    }
    
//    ofSetColor(237,0,0);
//    float rad=13;
//    ofCircle(p.pos.x,p.pos.y,rad);
    
    ofSetColor(245,135,17);
    
    float angle=atan2(moveParticle.pos.y-p.pos.y, moveParticle.pos.x-p.pos.x);
    
    float dist=30;
    
    
    
    ofPushMatrix();
    ofTranslate(p.pos.x, p.pos.y);
    ofRotate(ofRadToDeg(angle));
    
    ofPoint a,b,c;
    a.set(dist,0);
    b.set(-dist/2,dist/2);
    c.set(-dist/2,-dist/2);
    
    ofTriangle(a.x,a.y, b.x,b.y, c.x,c.y);
    
    //put some blue over it if it is frozen
    if (freezeTimer>0){
        ofSetColor(0,0,255,100);
        ofTriangle(a.x,a.y, b.x,b.y, c.x,c.y);
    }
    
    
    //show health
    ofSetColor(0);
    ofSetLineWidth(3);
    ofNoFill();
    
    //health is broken up into three lines
    float line1X=ofMap(hp,0,fullHP, b.x, a.x, true);
    float line1Y=ofMap(hp,0,fullHP, b.y, a.y, true);
    ofLine(line1X,line1Y, b.x, b.y);
    
    float line2X=ofMap(hp,0,fullHP, c.x, a.x, true);
    float line2Y=ofMap(hp,0,fullHP, c.y, a.y, true);
    ofLine(line2X,line2Y, c.x, c.y);
    
    //and just always draw the rear
    ofLine(b.x,b.y, c.x,c.y);
    
    
    
    ofPopMatrix();
    
}
*/