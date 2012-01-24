//
//  StealthFoe.h
//  ofxKinectExample
//
//  Created by Andy Wallace on 12/10/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#ifndef ofxKinectExample_StealthFoe_h
#define ofxKinectExample_StealthFoe_h

#include "ofMain.h"
#include "Foe.h"


class StealthFoe : public Foe{
public:
    
    void typeSetup(int level);
    void draw();
    void findPath();
    
};

#endif
