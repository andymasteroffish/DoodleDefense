//
//  Tower.h
//  opencvExample
//
//  Created by Andy Wallace on 12/1/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#ifndef opencvExample_Tower_h
#define opencvExample_Tower_h

#include "ofMain.h"
#include "particle.h"
#include "Foe.h"

class Tower{
public:
    
    void setup(float x, float y, float _size, int _idNum);
    virtual void typeSetup(){}
    void update();
    virtual void draw(){}
    void setNewPos(float x, float y, float _size);
    void fire(Foe * _target);    //shoots a bullet 
    virtual void hitTarget(){}
    
    
    bool * showAllInfo;   //shows all of the bullshit lines and data Points to the one in test app
    bool * paused;        //is the game paused. points to the bool in test app
    
    bool playerDead;
    
    
    ofVec2f pos;
    float size;
    float range;
    float rangePadding;
    
    string type;
    
    bool found; //keeps track of if this tower was found in the last check against the pixels. It should be removed if it wasn't
    
    int rechargeTime;
    int timer;
    bool readyToShoot;
    bool shooting;  //there is an active bullet
    
    particle bullet;
    Foe * target;
    float bulletAtraction;
    
    float bulletDamage;
    
    //special values for bomb tower
    float blastRadius;  //how much will be effected when the bullet hits
    bool bombHit;   
    
    //keeping track of when a tower goes away
    int idNum;
    
};



#endif
