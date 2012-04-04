//
//  Foe.h
//  opencvExample
//
//  Created by Andy Wallace on 11/24/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#ifndef opencvExample_Foe_h
#define opencvExample_Foe_h

#include "ofMain.h"
#include "particle.h"
#include "spring.h"
#include "vectorField.h"
#include "tile.h"
#include "ofxOpenCv.h"  //DOES NOT NEED THIS

class Foe{
public:
    
    void setup(vectorField * _vf, float x, float y, float goalX, float goalY, float _fieldScale, int _fieldW, int _fieldH, int level);
    void setPics(ofImage * _outline, ofImage * _fill);
    virtual void typeSetup(int level){}
    void update();
    virtual void draw(){ standardDraw(); }
    void standardDraw();
    void drawDebug();
    void drawExplored();
    virtual void findPath() { standardFindPath(); }
    void standardFindPath();
    void setNextNode();
    int getDistToGoal(int x, int y);
    bool checkExistingRoute(vector<tile *> & existing);          //compares a route to see if it can be used
    void clearPathfindingLists();
    void freeze(int time);
    
    //drawing the field
    float fieldScale;   //how mush the field must be blown up to match the screen
    int fieldW;
    int fieldH;
    vectorField * VF;   //keep a pointer to the vector field
    
    //handling moving to the next node on the route
    particle p;     //particle that controls movement
    int nextNode;       //the route node we should be aproaching
    float nextNodeRad;  //how close the foe must be to the next node to remove it from the list
    particle moveParticle;
    float moveAtraction;
    float moveAtractionIncrease;
    
    //game states
    bool * showAllInfo;   //shows all of the bullshit lines and data Points to the one in test app
    bool * paused;        //is the game paused. points to the bool in test app
    
    //path finding
    unsigned char * wallPixels; //the pixel information from the field
    vector <tile *> openList;
    vector <tile *> closedList;
    vector <tile *> route;
    bool pathFound;
    //where the foe is trying to get to in field units
    int goalX, goalY;
    //measuring distance for pathfinding
    int horzDist;
    int diagDist;
    
    //game vals
    string type;            //what kind of foe this is
    float speed;            //starting force of atraction to next node
    float fullHP;           //startingHealth
    float hp;               //remaining health
    float damageToPlayer;   //how much this foe hurts the player if allowed through
    bool dead;              //flag telling test app to get rid of this foe
    bool endBolt;           //flag that the foe reached the edge of the maze and can bolt to the finish
    bool reachedTheEnd;     //flag telling test app this foe reached the end of the maze
    int inkVal;           //how much ink the player gets for killing this one
    
    int freezeTimer;        //how long to stay frozen
    
    
    //draw the foe
    ofImage * outlinePic;
    ofImage * fillPic;
    
};



#endif
