//
//  BombTower.cpp
//  opencvExample
//
//  Created by Andy Wallace on 12/2/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#include "BombTower.h"

void BombTower::typeSetup(){
    range=size*4.5;           //large range
    
    rechargeTime=120;         //slow recharge
    bulletAtraction=0.3;    //slow bullet
    bulletDamage=30;        //huge damage
    
    type="green";
    
    blastRadius=size*3.5;
}

void BombTower::draw(){
    ofFill();
    if (! *showAllInfo){
        ofSetColor(0, 255, 0,130);
        if (playerDead) ofSetColor(100,100,100,70);
        
        ofCircle(pos.x, pos.y, range);
    }
    
    ofSetColor(0);
    if (shooting){
        bullet.draw();
    }
    
}

void BombTower::hitTarget(){
    shooting=false;
    bombHit=true;
    
}
