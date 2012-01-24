//
//  Tower.cpp
//  opencvExample
//
//  Created by Andy Wallace on 12/1/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#include "Tower.h"

void Tower::setup(float x, float y, float _size){
    setNewPos(x,y,_size);
    
    //values that will be the same for all towers
    found=true;
    timer=10000;    //make sure it can shoot right away
    readyToShoot=false;
    shooting=false;
    
    bombHit=false;
    
    playerDead=false;
    
    //everything else is handled by the type specific setup, called in setNewPos
    
}

void Tower::setNewPos(float x, float y, float _size){
    pos.x=x;
    pos.y=y;
    size=_size;
    
    typeSetup();
}

void Tower::update(){
    if (! *paused ){
        //increase the timer
        if (!shooting)  timer++;
        if (timer>rechargeTime){
            readyToShoot=true;
        }
        
        //if we are shooting, see if we hit the target
        if (shooting){
            if (bullet.pos.distance(target->p.pos)<15)
                hitTarget();
            
            //move the bullet
            //reset the particle
            bullet.resetForce();
            
            //atract the bullet to the target
            bullet.addAttractionForce(target->p.pos.x, target->p.pos.y, bullet.pos.distance(target->p.pos)*4, bulletAtraction);
            
            //dampen and update the particle
            bullet.addDampingForce();
            bullet.update();

            
        }
    }
}


void Tower::fire(Foe * _target){
    target=_target;
    
    //get the angle to the target to make the bullet curve around
    ofVec2f diff=pos- target->p.pos;
    diff.normalize();
    //give it some randomness just for apearances
    diff.x+=ofRandom(-0.5,0.5);
    diff.y+=ofRandom(-0.5,0.5);
    diff*=4;    //make it stronger
    
    timer=0;
    shooting=true;
    readyToShoot=false;
    
    bullet.setInitialCondition(pos.x,pos.y,diff.x, diff.y);
    
}



