//
//  FreezeTower.h
//  opencvExample
//
//  Created by Andy Wallace on 12/1/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#ifndef opencvExample_FreezeTower_h
#define opencvExample_FreezeTower_h

#include "ofMain.h"
#include "Tower.h"

class FreezeTower : public Tower{
public:
    void typeSetup();
    void draw();
    void hitTarget();
    
    int freezeTime;
};

#endif
