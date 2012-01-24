//
//  Foe.cpp
//  opencvExample
//
//  Created by Andy Wallace on 11/24/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#include "Foe.h"

//------------------------------------------------------------
void Foe::setup(vectorField * _vf, float x, float y, float _goalX, float _goalY, float _fieldScale, int _fieldW, int _fieldH, int level){
    VF=_vf;
    p.pos.x=x;
    p.pos.y=y;
    fieldScale=_fieldScale;
    fieldW=_fieldW;
    fieldH=_fieldH;
    
    //get read to handle movement
    moveParticle.setInitialCondition(0,0,0,0);
    moveParticle.bFixed=true;   //move particle is locked in place so that it only pulls the foe towards it
    moveAtractionIncrease=0.01;
    nextNodeRad=20;
    
    //set pathfinding distance values
    horzDist=10;
    diagDist=14;
    
    //set the goal THIS IS IN FIELD UNITS
    goalX=_goalX/fieldScale;
    goalY=_goalY/fieldScale;
    
    //game state info
    dead=false;
    reachedTheEnd=false;
    endBolt=false;
    freezeTimer=0;
    
    //default game vals
    fullHP=50+ 50*level;
    speed=0.1;
    inkVal=6;
    damageToPlayer=1;
    
    //set type specific game values that might change the above values
    typeSetup(level);
    hp=fullHP;  //give it the full HP set in typeSetup
}

//------------------------------------------------------------
void Foe::update(){
    if (! *paused){
        bool frozen=false;
        if (freezeTimer>0 && freezeTimer%2==0)  frozen=true;
        if (route.size()>2 && !frozen){
            
            //reset the particle
            p.resetForce();
            
            //atract the controler to the next node
            float atraction=moveAtraction;
            p.addAttractionForce(moveParticle, p.pos.distance(moveParticle.pos)*1.5, atraction);
            
            moveAtraction+=moveAtractionIncrease;
            
            //get force from the vector field.
            ofVec2f frc;
            frc = VF->getForceFromPos(p.pos.x, p.pos.y);
            //stealth gets almost no resistance from walls
            if (type=="stealth")    frc*=0.3;
            p.addForce(frc.x, frc.y);
            
            //dampen and update the particle
            p.addDampingForce();
            p.update();
        }
        
        //see if we're ready to go to the next node
        if (p.pos.distance(moveParticle.pos)<nextNodeRad){
            setNextNode();
        }
        
        //if we're at the end, bolt off screen
        if (ofDist(p.pos.x,p.pos.y,goalX*fieldScale,goalY*fieldScale)<15){
            //reachedTheEnd=true;
            endBolt=true;
            //set the move particle just off screen
            
            //check which gate this foe is using
            if (goalX>goalY)
                moveParticle.pos.x+=10;
            else
                moveParticle.pos.y+=10;
        }
        
        //reduce freezeTimer. if it is above 0 the foe is frozen
        freezeTimer--;
    }
    
    //moving the foe off screen if it has reached the end
    if (endBolt){
        //reset the particle
        p.resetForce();
        
        //atract the controler to the next node
        float atraction=moveAtraction*5;
        p.addAttractionForce(moveParticle, p.pos.distance(moveParticle.pos)*1.5, atraction);
        
        moveAtraction+=moveAtractionIncrease;
        
        //dampen and update the particle
        p.addDampingForce();
        p.update();
        
        //if we've reach the move particle, the foe is done
        if ( (goalX>goalY && p.pos.x>moveParticle.pos.x) || 
             (goalY>goalX && p.pos.y>moveParticle.pos.y) ) {
            reachedTheEnd=true;
        }

    }
    
    //test if the foes is dead
    if (hp<=0)  dead=true;
    
}

//------------------------------------------------------------
//Normal draw is handled by the different foe types

//------------------------------------------------------------
void Foe::drawDebug(){
    //draw the path if one was found
    if (*showAllInfo){
        
        ofPushMatrix();
        ofScale(fieldScale,fieldScale); 
        
        
        
        if (pathFound){
            if (showAllInfo){
                ofSetColor(0,255,0);
                ofSetLineWidth(2);
                if (route.size()>3){
                    for (int i=0; i<route.size()-1; i++)
                        ofLine(route[i]->x, route[i]->y,route[i+1]->x, route[i+1]->y);
                }
            }
        }
        else{
            //otherwise draw the area explored
            ofSetColor(255,0,0,20);
            for (int i=0; i<closedList.size()-1; i++)
                ofRect(closedList[i]->x,closedList[i]->y,2,2);
            //ofLine(route[i]->x, route[i]->y,route[i+1]->x, route[i+1]->y);
        }
        
        ofPopMatrix();
        
        ofSetColor(0);
        moveParticle.draw();
    }
}

//------------------------------------------------------------
//draws the area that was explored when no path was found. Also flashes the location of the foe
void Foe::drawExplored(){
    //otherwise draw the area explored
     ofSetColor(220,35,130,40);
    ofPushMatrix();
    ofScale(fieldScale,fieldScale);
    for (int i=0; i<closedList.size()-1; i++)
        ofRect(closedList[i]->x,closedList[i]->y,2,2);
    ofPopMatrix();

}

//------------------------------------------------------------
//after we have all the points, start the route
void Foe::setNextNode(){
    //advance the nextNode
    nextNode=MAX(nextNode-1,0);
    
    //set the particle position
    moveParticle.pos.x=route[nextNode]->x*fieldScale;
    moveParticle.pos.y=route[nextNode]->y*fieldScale;

    
    moveAtraction=speed;
    
}

//------------------------------------------------------------
//returns true if the existing path can be used by this foe
// prevents us from having to do a costly path finding search
bool Foe::checkExistingRoute(vector<tile *> & existing){
    //float minDist=30;   //how far a node on the route can be and still be considerred valid
    
    if (nextNode<route.size()){
        for (int i=0; i<existing.size(); i++){
            if (route[nextNode]->x == existing[i]->x && route[nextNode]->y == existing[i]->y){
                //we have a match!
                //clear out route out
                clearPathfindingLists();
                //set route to be this one
                for (int k=0; k<existing.size(); k++){
                    tile * newNode;
                    newNode=existing[k];
                    route.push_back(newNode);
                }
                openList=route;
                //and start next Node where we found this
                nextNode=i;
                
                //return true
                return true;
            }
        }
    }
    
    return false;

}

//------------------------------------------------------------
//attempt to find a path
void Foe::standardFindPath(){
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
                    //check if the tile is impassible
                    if (wallPixels[pixelPos]==255){
                        //don't add any tile that is adjacent to a wall
                        //this is to help keep the path a little less hugging one wall
                        bool nextToWall=false;
                        for (int x2=-1; x2<=1; x2++){
                            for (int y2=-1; y2<=1; y2++){
                                int pixelPos2=(yPos+y2)*fieldW+(xPos+x2);
                                if (wallPixels[pixelPos2]==0)
                                    nextToWall=true;
                            }
                        }
                        
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
        //the memory positions pointed to in route may have already been destroyed
        route.clear();  //first, clear the old route
        
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
    
    //If it looks like the foe was inked over trying to move along path
    int minListSize=3;  //how small the closed list must be to move along the path
    if (!pathFound && closedList.size()<minListSize && nextNode>2){
        setNextNode();  //go to the next node
        p.pos=moveParticle.pos; //move the foe there
        
        //keep the foe in the maze in case garbage values are returned
        p.pos.x=CLAMP(p.pos.x,11*fieldScale,155*fieldScale);
        p.pos.y=CLAMP(p.pos.y,11*fieldScale,115*fieldScale);
        
        standardFindPath(); //try again recursievly
    }
}

//--------------------------------------------------------------
int Foe::getDistToGoal(int x, int y){ 
    return ( abs(x-goalX)*horzDist + abs(y-goalY)*horzDist);
}

//--------------------------------------------------------------
void Foe::clearPathfindingLists(){
    while(openList.size()>0){
		delete openList[0];
		openList.erase(openList.begin());
	}
    while(closedList.size()>0){
        delete closedList[0];
		closedList.erase(closedList.begin());
	}
    
    
    
}

//--------------------------------------------------------------
void Foe::freeze(int time){ 
    freezeTimer=time;
}