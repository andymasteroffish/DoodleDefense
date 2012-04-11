//
//  Wave.cpp
//  ofxKinectExample
//
//  Created by Andy Wallace on 12/10/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#include "Wave.h"


void Wave::setup (int _level){
    level=_level;
    done=false;
    readyForNextFoe=false;
    nextFoe=0;
    startTime=0;
    curTime=0;
    
    boxColorID="none";
    
    message="";
}

void Wave::setTime(int seconds){
    length=seconds*1000;    //convert seconds to millis
}

void Wave::addFoes(string name, int num){
    for (int i=0; i<num; i++){
        foes.push_back(name);
    }
}

void Wave::setMessage(string text){
    message=text;
    //each '#' in the stirng indicates a line break
    for (int i=0; i<message.length(); i++){
      if (message[i]=='#')  
        message[i]='\n';
    }
}

void Wave::setBoxColor(string colorId){
    boxColorID=colorId;
}

void Wave::start(){
    startTime=ofGetElapsedTimeMillis();
    curTime=0;
}

void Wave::update(bool paused, bool fastForward){
    if (fastForward){
        startTime-=16;  //at 60 frame/sec, this is roughly the equivalant of one farm
    }
    
    //don't advance time if the agme is paused
    if (paused){
        startTime=ofGetElapsedTimeMillis()-curTime;
    }else{
        curTime=ofGetElapsedTimeMillis()-startTime;
    }
    
    int timeBetweenFoes=length/foes.size();
    if (curTime>nextFoe*timeBetweenFoes && !done){
        readyForNextFoe=true;
    }
    
    
}

void Wave::randomize(){
    for (int i=0; i<100; i++){
        int a=ofRandom(foes.size());
        int b=ofRandom(foes.size());
        
        string temp=foes[a];
        foes[a]=foes[b];
        foes[b]=temp;
    }
}

string Wave::getNextFoe(){
    string thisFoe=foes[nextFoe];
    nextFoe++;
    
    if (nextFoe==foes.size()){
        done=true;
        nextFoe=foes.size()-1;  //just to avoid a weird bad acess error or something
    }
    
    readyForNextFoe=false;
    
    return thisFoe;
}
