//
//  ImmuneRedFoe.cpp
//  ofxKinectExample
//
//  Created by Andy Wallace on 12/11/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#include "HeavyFoe.h"

//------------------------------------------------------------
void HeavyFoe::typeSetup(int level){
    type="heavy";
    fullHP*=3;  //way more health than a normal foe
    speed*=0.3; //slow it down
    
}


//------------------------------------------------------------
/*
void HeavyFoe::draw(){
    ofFill();
    
    
    //have it flash if there is no path
    if (!pathFound){
        drawExplored();
    }
    
    ofSetColor(120,146,148);
    
    float angle=atan2(moveParticle.pos.y-p.pos.y, moveParticle.pos.x-p.pos.x);
    float rectSize=40;
    
    ofPushMatrix();
    ofTranslate(p.pos.x,p.pos.y);
    ofRotate(ofRadToDeg(angle));
    ofRect(0,0, rectSize, rectSize);
    
    
    //draw blue over it if it is frozen
    if (freezeTimer>0){
        ofSetColor(0,0,255,100);
        ofRect(0,0, rectSize, rectSize);
    }
    
    //show health
    ofSetColor(0);
    ofSetLineWidth(3);
    ofNoFill();
    ofBeginShape();
    int numPoints=40;
    int healthNum=ofMap(hp,0,fullHP,0,numPoints);
    ofBeginShape();
    for (int i=0; i<healthNum; i++){
        float x,y;
        if (i<numPoints/4){
            x=ofMap(i,0,numPoints/4,rectSize/2,-rectSize/2);
            y=-rectSize/2;
        }
        else if (i< (numPoints/4)*2){
            x=-rectSize/2;
            y=ofMap(i,numPoints/4,(numPoints/4)*2,-rectSize/2,rectSize/2);
            
        }
        else if (i< (numPoints/4)*3){
            x=ofMap(i,(numPoints/4)*2,(numPoints/4)*3,-rectSize/2,rectSize/2);
            y=rectSize/2;
        }else{
            x=rectSize/2;
            y=ofMap(i,(numPoints/4)*3,numPoints,rectSize/2,-rectSize/2);
        }
        
        ofVertex(x,y);
    }
    ofEndShape(false);
//    float healthCircle=ofMap(hp,0,fullHP,0,TWO_PI);
//    for (float i=0; i<healthCircle; i+=TWO_PI/30)
//        ofVertex(p.pos.x+cos(i-PI/2)*rad, p.pos.y+sin(i-PI/2)*rad);
//    ofEndShape(false);
    
    ofPopMatrix();
    
}
 */
