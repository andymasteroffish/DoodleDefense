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
    
    //---------------------
    //warp points phase
    ofxCvColorImage *   colorImg;
    ofxCvColorImage *   colorImgMedium;
    int kinectImageOffsetX;
    int kinectImageOffsetY;
    ofVec2f warpPoints[4];
    float warpPointHandleSize;
    bool draggingWarpPoint[4];
    
    //---------------------
    //color setting phase
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
    
    //---------------------
    //Kinect Phase
    bool * saveDepthBackground;
    bool * depthPause;
    ofxCvGrayscaleImage *   depthImgSmall;      
    ofxCvGrayscaleImage *   depthBackground;   
    ofxCvGrayscaleImage *   depthBackgroundDiff;
    ofRectangle saveDepthBackgroundButton;
    //depth slider
    int depthSliderX;
    int depthSliderY;
    int depthSliderMinX;
    int depthSliderMaxX;
    int depthDiffMax;
    int depthDiffMin;
    bool draggingDepthSlider;
    

    
    
};


#endif
