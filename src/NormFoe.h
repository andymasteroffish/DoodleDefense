//
//  Header.h
//  opencvExample
//
//  Created by Andy Wallace on 12/5/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#ifndef opencvExample_NormFoe_h
#define opencvExample_NormFoe_h

#include "ofMain.h"
#include "Foe.h"


class NormFoe : public Foe{
public:
    
    void typeSetup(int level);
    void draw();
    
};


#endif
