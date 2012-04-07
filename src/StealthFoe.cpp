//
//  StealthFoe.cpp
//  ofxKinectExample
//
//  Created by Andy Wallace on 12/10/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

//
//  NormFoe.cpp
//  opencvExample
//
//  Created by Andy Wallace on 12/5/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//


#include "StealthFoe.h"

//------------------------------------------------------------
void StealthFoe::typeSetup(int level){
    type="stealth";
    
}


//------------------------------------------------------------
/*
void StealthFoe::draw(){
    ofFill();
    
    
    //have it flash if there is no path
    if (!pathFound){
        drawExplored();
    }
    
    //current position
    ofSetColor(227,227,68);
    
    float rad=17;
    
    ofBeginShape();
    int numPoints=30;
    for (int i=0; i<numPoints; i++){
        float angle=i*(TWO_PI/numPoints);
        float noise=ofNoise(angle,ofGetElapsedTimef()*3)*6;
        float x=p.pos.x+cos(angle)*rad+noise;
        float y=p.pos.y+sin(angle)*rad+noise;
        ofVertex(x, y);
    }
    ofEndShape(true);
     
    //put some blue over it if it is frozen
    if (freezeTimer>0){
        ofSetColor(0,0,255,100);
        ofBeginShape();
        for (int i=0; i<numPoints; i++){
            float angle=i*(TWO_PI/numPoints);
            float noise=ofNoise(angle,ofGetElapsedTimef()*3)*6;
            float x=p.pos.x+cos(angle)*rad+noise;
            float y=p.pos.y+sin(angle)*rad+noise;
            ofVertex(x, y);
        }
        ofEndShape(true);
    }
    
    //show health
    ofSetColor(0);
    ofSetLineWidth(3);
    ofNoFill();
    ofBeginShape();
    int healthNum=ofMap(hp,0,fullHP,0,numPoints);
    for (int i=0; i<healthNum; i++){
        float angle=i*(TWO_PI/numPoints);
        float noise=ofNoise(angle,ofGetElapsedTimef()*3)*6;
        float x=p.pos.x+cos(angle)*rad+noise;
        float y=p.pos.y+sin(angle)*rad+noise;
        ofVertex(x, y);
    }
    ofEndShape(false);
    
}
  */

//------------------------------------------------------------
//attempt to find a path
void StealthFoe::findPath(){
    int startX=p.pos.x/fieldScale;
    int startY=p.pos.y/fieldScale;
    
    startX=MAX(0,MIN(startX,fieldW-1));
    startY=MAX(0,MIN(startY,fieldH-1));
    
    //clear out the vectors
    clearPathfindingLists();
    
    //add the start tile to the openList
    tile * start = new tile();
    //    startX=testo.p.pos.x;
    //    startY=testo.p.pos.y;
    start->x=startX;
    start->y=startY;
    start->g=0;
    start->h=getDistToGoal(start->x,start->y);
    start->f= start->g+start->h;
    openList.push_back(start);
    
    //tile * parent=t;
    bool goalFound=false;
    bool doneSearching=false;
    while(!doneSearching){
        
        //find the lowest F value in the open list
        int lowestID=0;
        for (int i=0; i<openList.size(); i++){
            if(openList[i]->f <= openList[lowestID]->f)
                lowestID=i;
        }
        
        //move this tile to the closed list
        closedList.push_back(openList[lowestID]);
        //remove it from the open list
        openList.erase(openList.begin()+lowestID);
        
        //explore this tile
        tile * current=closedList[closedList.size()-1];
        
        //if this was the goal tile, we're done
        if(current->x==goalX && current->y==goalY){
            goalFound=true;
            doneSearching=true;
        }
        
        //check the 8 tiles aorund this one
        for (int x=-1; x<=1; x++){
            for (int y=-1; y<=1; y++){
                int xPos=current->x+x;
                int yPos=current->y+y;
                //make sure this tile is not the current one or off the grid
                if (xPos>=0 && xPos<fieldW && yPos>=0 && yPos<fieldH && (x!=0 || y!=0) ){
                    int pixelPos=yPos*fieldW+xPos;   //MAKE A FUNCTION FOR THIS
                    //check if the tile is impassible ANYTHING WORKS FOR THE STEALTH FOE!
                    if (true){
                        //don't add any tile that is adjacent to a wall
                        //this is to help keep the path a little less hugging one wall
                        bool nextToWall=false;  //AND HE DOESN'T GIVE A FUCK ABOUT WALLS EITHER
                        
                        if (!nextToWall){
                            //check that the tile is not in the closed list
                            bool inClosedList=false;  //assume it isn't
                            for (int c=0; c<closedList.size(); c++){
                                if (closedList[c]->x==xPos && closedList[c]->y==yPos)
                                    inClosedList=true;
                            }
                            if (!inClosedList){
                                //check to see if it is already in the open list
                                int openListID=-1;
                                for (int o=0; o<openList.size(); o++){
                                    if (openList[o]->x==xPos && openList[o]->y==yPos)
                                        openListID=o;
                                }
                                
                                //add it to the open list if it isn't already there
                                if (openListID==-1){
                                    tile * t = new tile();
                                    t->x=xPos;
                                    t->y=yPos;
                                    if (y==0 || x==0) t->g=current->g+horzDist;
                                    else              t->g=current->g+diagDist;
                                    t->h=getDistToGoal(xPos, yPos);
                                    t->f=t->g+t->h;
                                    t->parent=current;
                                    openList.push_back(t);
                                    //if we just added the goal to the open list, we're done
                                    //THIS WILL NOT ALWAYS BE AS ACURATE AS WAITING UNTIL THE GOAL IS ADDED TO THE CLOSED LIST
                                    //BUT IT IS FASTER
                                    if (t->x==goalX && t->y==goalY){
                                        doneSearching=true;
                                        goalFound=true;
                                        //add it to closed list so it will be added to the route
                                        closedList.push_back(t);
                                        //remove it from the open list
                                        openList.erase(openList.begin()+openList.size()-1);
                                    }
                                }else{
                                    //if it is there see if this path is faster
                                    int newG;       //measure distance to the tile based on g
                                    if (y==0 || x==0) newG=current->g+horzDist;
                                    else              newG=current->g+diagDist;
                                    if (newG<openList[openListID]->g){
                                        openList[openListID]->g=newG;   //set g to be the new, shorter distance
                                        openList[openListID]->f=newG+openList[openListID]->h;   //reset the f value for this tile
                                        openList[openListID]->parent=current;   //change the parent
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        //if we're out of tiles, there is no path
        if (openList.size()==0)
            doneSearching=true;//testing
        
    }
    
    //if it found a path, add it to the route
    if (goalFound){
        pathFound=true;
        //start with the goal and work backwards
        route.push_back(closedList[closedList.size()-1]);
        while(! (route[route.size()-1]->x==startX && route[route.size()-1]->y==startY)){
            route.push_back(route[route.size()-1]->parent);
        }
        //reset the next node to start from the beginning
        nextNode=route.size()-1;
        setNextNode();
    }else{
        pathFound=false;
    }
}
