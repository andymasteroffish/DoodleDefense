//
//  WaveInfoBox.cpp
//  ofxKinectExample
//
//  Created by Andy Wallace on 4/11/12.
//  Copyright (c) 2012 AndyMakes. All rights reserved.
//

#include "WaveInfoBox.h"


void WaveInfoBox::setup(int _waveNum, string _message, ofImage * _backPic, ofTrueTypeFont * _waveFont, ofTrueTypeFont * _messageFont, string colorID, float startX, float startY, float _boxW, float _boxH){
    waveNum=_waveNum;
    message=_message;
    backPic= _backPic;
    waveFont=_waveFont;
    messageFont=_messageFont;
    pos.x=startX;
    pos.y=startY;
    boxW=_boxW;
    boxH=_boxH;
    
    bgColor.set(25,179,54);   //default color
    //set color based on the id
    if (colorID=="norm")
        bgColor.set(207,128,182);
    if (colorID=="fast")
        bgColor.set(245,136,31);
    if (colorID=="heavy")
        bgColor.set(121,148,149);
    if (colorID=="stealth")
        bgColor.set(227,228,69);
    if (colorID=="immune")
        bgColor.set(239,60,64);
    
    
    
    alpha=255;
    fading=false;
    fadeSpeed=15;
    
    fallSpeed=8;
    
    //set up how to display the text
    waveTextOffset.x = -boxW/2 + 15;
    waveTextOffset.y = -boxH/2 + 50;
    
    messageTextOffset.x = -boxW/2 + 30;
    messageTextOffset.y = -boxH/2 + 140;
}


void WaveInfoBox::draw(){
    
    int imgPaddingX=40;
    int imgPaddingY=25;
    
    //draw the box
    ofSetColor(bgColor.r, bgColor.g, bgColor.b, alpha);
    backPic->draw(pos.x,pos.y);
    
    //write the text
    ofSetColor(0,0,0, alpha);
    waveFont->drawString("Wave #"+ofToString(waveNum), pos.x +waveTextOffset.x, pos.y+waveTextOffset.y);
    messageFont->drawString(message, pos.x +messageTextOffset.x, pos.y+messageTextOffset.y);
    
    
}