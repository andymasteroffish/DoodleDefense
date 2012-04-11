//
//  Wave.h
//  ofxKinectExample
//
//  Created by Andy Wallace on 12/10/11.
//  Copyright (c) 2011 AndyMakes. All rights reserved.
//

#ifndef ofxKinectExample_Wave_h
#define ofxKinectExample_Wave_h

#include "ofMain.h"

class Wave{
public:
    
    void setup(int _level);
    void setTime(int seconds);
    //void setup();
    void addFoes(string name, int num);
    void setMessage(string text);
    void setBoxColor(string colorId);
    void start();
    void update(bool paused, bool fastForward);
    void randomize();   //shuffles the order
    string getNextFoe();    //adnaces to the next foe and returns the value
    
    //bool * paused;        //is the game paused. points to the bool in test app
    
    //list of foes
    int level;
    vector <string> foes;
    int nextFoe;
    
    //timing
    int curTime;
    int startTime;
    int length;
    
    bool readyForNextFoe;   //flag that enough time has passed for the next foe to spawn
    bool done;
    
    //misc
    string message;
    string boxColorID;
    
    
};


#endif
