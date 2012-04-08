//
//  FreezeTower.cpp
//  opencvExample
//
//  Created by Andy Wallace on 12/1/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#include "FreezeTower.h"

void FreezeTower::typeSetup(){
    range=size*3.5;           //small range
    
    rechargeTime=20;        //moderate recharge
    bulletAtraction=1;//0.5;    //fast bullet
    bulletDamage=0;         //no damage
    
    freezeTime=300;      //how long the foe stays frozen
    
    type="blue";
}

void FreezeTower::draw(){
    ofFill();
    if (! *showAllInfo){
        ofSetColor(0, 0, 255,120);
        if (playerDead) ofSetColor(100,100,100,70);
        
        ofCircle(pos.x, pos.y, range);
    }
    
    ofSetColor(0);
    if (shooting){
        bullet.draw();
    }
    
}

void FreezeTower::hitTarget(){
    shooting=false;
    //the effects that happen to the foe when they get hit
    target->freeze(freezeTime);
}