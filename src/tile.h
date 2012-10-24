//
//  tile.h
//  emptyExample
//
//  Created by Andy Wallace on 11/21/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#ifndef emptyExample_tile_h
#define emptyExample_tile_h

#include "ofMain.h"

class tile{
public:
    int x,y;    //location of the tile
    
    //pathfinding distance values
    int f;  //total of the distance to get to this tile and estimated distance to goal
    int g;  //movement cost to get to this tile from starting point
    int h;  //estimated distance to goal
    
    tile * parent;  //pointer to the parent tile
    
    
    
    
};



#endif
