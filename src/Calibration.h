//
//  Calibration.h
//  ofxKinectExample
//
//  Created by Andy Wallace on 3/16/12.
//  Copyright (c) 2012 AndyMakes. All rights reserved.
//

#include "ofMain.h"
#include "ofxControlPanel.h"
#include "ofxOpenCv.h"

#ifndef ofxKinectExample_Calibration_h
#define ofxKinectExample_Calibration_h


class Calibration{
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    //needs pointers to some things at the testApp level
    ofxControlPanel *	panel;
    
    
    string phase;   //what is being set right now
    
    float sliderSize;   //how big to draw the grabber for the sliders
    float smallSliderSize;
    
    //tabs to navigate
    int tabStartX;
    int tabStartY;
    int tabW;   //widht of a tab
    int tabH;   //height of a tab
    string tabLabels[6];    //names of the tabs
    
    //next button
    ofImage nextButtonPic;
    int nextButtonX, nextButtonY;
    
    //font
    ofTrueTypeFont font;
    ofTrueTypeFont fontSmall;
    
    //mouse offset when dragging things
    float dragOffsetX, dragOffsetY;
    
    //---------------------
    //location phase
    int xPosSliderX;
    int xPosSliderY;
    int xPosSliderMinX;
    int xPosSliderMaxX;
    bool draggingXPosSlider;
    int xPosMin;
    int xPosMax;
    int xPos;
    
    int yPosSliderX;
    int yPosSliderY;
    int yPosSliderMinY;
    int yPosSliderMaxY;
    bool draggingYPosSlider;
    int yPosMin;
    int yPosMax;
    int yPos;
    
    int scaleSliderX;
    int scaleSliderY;
    int scaleSliderMinX;
    int scaleSliderMaxX;
    bool draggingScaleSlider;
    float scaleMin;
    float scaleMax;
    float scaleVal;
    
    ofImage locationBackground;
    
    //---------------------
    //screen phase
    bool * showRect;
    ofxCvColorImage *   colorImg;
    ofxCvColorImage *   colorImgMedium;
    int cameraImageOffsetX;
    int cameraImageOffsetY;
    ofVec2f warpPoints[4];
    float warpPointHandleSize;
    bool draggingWarpPoint[4];
    
    ofImage screenBackground;
    
    //---------------------
    //color setting phase
    bool showGame;  //don't show the game if we're getting the colors
    ofxCvGrayscaleImage *   colorImgs[3];
    ofxCvGrayscaleImage *	hueImg;
    ofxCvGrayscaleImage	*	satImg;
    ofxCvGrayscaleImage	*	briImg;
    int colorImageOffsetX;
    int colorImageOffsetY;
    int colorImagesSpacingY;
    //sldiers
    int colorSliderMinX;
    int colorSliderMaxX;
    int hueSliderX[3];
    int hueSliderY[3];
    bool draggingHueSlider[3];
    int satSliderX[3];
    int satSliderY[3];
    bool draggingSatSlider[3];
    int valSliderX[3];
    int valSliderY[3];
    bool draggingValSlider[3];
    
    ofImage colorsBackground;
    
    //---------------------
    //Ink phase
    //black threshold
    ofxCvGrayscaleImage *	wallImg;  
    int blackThreshSliderX;
    int blackThreshSliderY;
    int blackThreshSliderMinX;
    int blackThreshSliderMaxX;
    bool draggingblackThreshSlider;
    //ink refund
    float inkUsedBeforeRefund;  //used to calculate how big the refund should be
    float extraRefund;  //how much to exceed 0 to make sure that the ink refund is really enough
    ofRectangle inkRefundButton;
    
    ofImage inkBackground;
    
    //---------------------
    //game phase
    
    ofRectangle startGameButton;
    //all the things that could pause the game
    bool * paused;        //global pause. If any reason is true, this is true
    bool * playerPause;   //player pauses the game
    bool * noPath;        //becomes true if any foe can't reach the end
    bool * tooMuchInk;    //pauses the game when the player has used more ink than they have
    bool * changePause;    //player in frnt of the screen
    bool * gameStarted;   //the camera must have taken at least one image to play the game
    int * takePictureTimer;
    //---------------------
    //Camera Phase
    bool * saveChangeBackground;
    ofxCvGrayscaleImage *   changeImgSmall;      
    ofxCvGrayscaleImage *   changeBackground;   
    ofxCvGrayscaleImage *   changeBackgroundDiff;
    ofRectangle saveChangeBackgroundButton;
    //change slider
    int changeSliderX;
    int changeSliderY;
    int changeSliderMinX;
    int changeSliderMaxX;
    int changeDiffMax;
    int changeDiffMin;
    bool draggingChangeSlider;
    
    ofImage cameraBackground;
    

    
    
};


#endif
