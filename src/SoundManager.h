//
//  SoundManager.h
//  ofxKinectExample
//
//  Created by Andy Wallace on 4/13/12.
//  Copyright (c) 2012 AndyMakes. All rights reserved.
//

#ifndef ofxKinectExample_SoundManager_h
#define ofxKinectExample_SoundManager_h

#include "ofMain.h"

class SoundManager{
public:

    void setup();
    void loadSound(string fileName, string refrenceName, float volume);
    bool playSound(string refrenceName);
    
    vector<string>        soundNames;
    vector<ofSoundPlayer> sounds;
    
};



#endif
