//
//  HitTower.cpp
//  opencvExample
//
//  Created by Andy Wallace on 12/1/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#include"HitTower.h"

void HitTower::typeSetup(){
    cout<<"size: "<< size<<endl;
    range=size*3.5;           //moderate range
    
    rechargeTime=1;         //fast recharge
    bulletAtraction=1;//0.5;    //fast bullet
    bulletDamage=size/2;        //moderate damage based on tower size
    
    type="red";
}

void HitTower::draw(){
    ofFill();
    if (! *showAllInfo){
        ofSetColor(255, 0, 0,100);
        if (playerDead) ofSetColor(100,100,100,70);
        
        ofCircle(pos.x, pos.y, range);
    }
    
    ofSetColor(0);
    if (shooting){
        bullet.draw();
    }
    
}

void HitTower::hitTarget(){
    shooting=false;
    //the effects that happen to the foe when they get hit
    target->hp-=bulletDamage;
}