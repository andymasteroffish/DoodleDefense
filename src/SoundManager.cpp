//
//  SoundManager.cpp
//  ofxKinectExample
//
//  Created by Andy Wallace on 4/13/12.
//  Copyright (c) 2012 AndyMakes. All rights reserved.
//

#include "SoundManager.h"


void SoundManager::setup(){
    sounds.clear();
    soundNames.clear();
}

//adds an external file to the vector of sound effects
void SoundManager::loadSound(string fileName, string refrenceName, float volume){
    ofSoundPlayer newSound;
    newSound.loadSound(fileName);
    newSound.setVolume(volume);
    newSound.setMultiPlay(true);
    sounds.push_back(newSound);
    //add the name as well
    soundNames.push_back(refrenceName);
}

//plays the specified sound. Returns false if the sound was not found
bool SoundManager::playSound(string refrenceName){
    
    //check the vector of names for the specified sound
    for (int i=0; i<soundNames.size(); i++){
        if (refrenceName==soundNames[i]){
            sounds[i].play();
            return true;
        }
    }
    
    cout<<"BAD SOUND NAME"<<endl;
    return false;
}