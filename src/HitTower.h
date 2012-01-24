//
//  HitTower.h
//  opencvExample
//
//  Created by Andy Wallace on 12/1/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#ifndef opencvExample_HitTower_h
#define opencvExample_HitTower_h

#include "ofMain.h"
#include "Tower.h"

class HitTower : public Tower{
public:
    void typeSetup();
    void draw();
    void hitTarget();
};

#endif
