//
//  Tower.cpp
//  opencvExample
//
//  Created by Andy Wallace on 12/1/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#include "Tower.h"

void Tower::setup(float x, float y, float _size, int _idNum){
    setNewPos(x,y,_size);
    idNum=_idNum;
    
    //values that will be the same for all towers
    found=true;
    timer=10000;    //make sure it can shoot right away
    readyToShoot=false;
    shooting=false;
    
    bombHit=false;
    
    playerDead=false;
    
    rangePadding=13;    //slightly increase the range for determining what can be shot
    
    //everything else is handled by the type specific setup, called in setNewPos
    
}

void Tower::setNewPos(float x, float y, float _size){
    pos.x=x;
    pos.y=y;
    size=_size;
    
    typeSetup();
}

void Tower::update(){
    
    //if the target is gone, wer'e not shooting anymore
    if (shooting && target==NULL){
        cout<<"STOP SHOOTING"<<endl;
        shooting=false;
        
        //if this was a bomb tower, detonate the bomb where it was
        if (type=="green")
            bombHit=true;
        
    }
    
    if (! *paused ){
        //increase the timer
        if (!shooting)  timer++;
        if (timer>rechargeTime){
            
            
            //if we have a target already, check if it is still in range
            bool needsNewTarget=true;   //assume we will need a new atrget
            if (target!=NULL){
                if ( pos.distance(target->p.pos) < range +rangePadding ){
                    needsNewTarget=false;
                    //shoot at it!
                    fire(target);
                }
                
            }
            
            //if the old target didn't exist or was out of range, tell testApp to find a new one
            if (needsNewTarget)
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



