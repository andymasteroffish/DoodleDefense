//
//  BombTower.h
//  opencvExample
//
//  Created by Andy Wallace on 12/2/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#ifndef opencvExample_BombTower_h
#define opencvExample_BombTower_h

#include "ofMain.h"
#include "Tower.h"

class BombTower : public Tower{
public:
    void typeSetup();
    void draw();
    void hitTarget();
    
    
};

#endif
