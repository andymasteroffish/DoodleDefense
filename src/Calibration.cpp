//
//  Calibration.cpp
//  ofxKinectExample
//
//  Created by Andy Wallace on 3/16/12.
//  Copyright (c) 2012 AndyMakes. All rights reserved.
//

#include "Calibration.h"

//------------------------------------------------------
void Calibration::setup(){
    
    phase="Location";
    
    sliderSize=20;
    smallSliderSize=10;
    
    //tabs
    tabStartX=40;
    tabStartY=10;
    tabW=150;
    tabH=60;
    tabLabels[0]="Location";
    tabLabels[1]="Screen";
    tabLabels[2]="Colors";
    tabLabels[3]="Ink";
    tabLabels[4]="Game";
    tabLabels[5]="Kinect";
    
    
    //------------
    //location phase
    xPosMin=0;
    xPosMax=2700;
    xPos=panel->getValueF("PROJX");
    xPosSliderMinX=50;
    xPosSliderMaxX=800;
    xPosSliderX=ofMap(xPos,xPosMin,xPosMax,xPosSliderMinX,xPosSliderMaxX);
    xPosSliderY=200;
    draggingXPosSlider=false;
    
    yPosMin=0;
    yPosMax=900;
    yPos=panel->getValueF("PROJY");
    yPosSliderMinY=200;
    yPosSliderMaxY=800;
    yPosSliderX=900;
    yPosSliderY=ofMap(yPos,yPosMin,yPosMax,yPosSliderMinY,yPosSliderMaxY);
    draggingYPosSlider=false;
    
    scaleMin=0.2;
    scaleMax=3;
    scaleVal=panel->getValueF("PROJSCALE");
    scaleSliderMinX=50;
    scaleSliderMaxX=800;
    scaleSliderX=ofMap(scaleVal,scaleMin,scaleMax, scaleSliderMinX, scaleSliderMaxX);
    scaleSliderY=300;
    draggingScaleSlider=false;
    
    
    //------------
    //warp points phase
    kinectImageOffsetX=50;
    kinectImageOffsetY=150;
    warpPointHandleSize=10;
    for (int i=0; i<4; i++)
        draggingWarpPoint[i]=false;
    
    
    //------------
    //color setting phase
    colorImageOffsetX=50;
    colorImageOffsetY=100;
    colorImagesSpacingY=15;
    //sliders
    colorSliderMinX=750;
    colorSliderMaxX=1100;
    
    float spaceBetweenSlidersY=colorImgMedium->height/4;
    for (int i=0; i<3; i++){
        draggingHueSlider[i]=false;
        draggingSatSlider[i]=false;
        draggingValSlider[i]=false;
        
        //y spacing
        hueSliderY[i]=colorImageOffsetY+ colorImgMedium->height*i + colorImagesSpacingY*i +spaceBetweenSlidersY;
        satSliderY[i]=hueSliderY[i]+spaceBetweenSlidersY;
        valSliderY[i]=satSliderY[i]+spaceBetweenSlidersY;
    }
    
    //set the x locaitons of the sliders based on the values stored in control panel
    //red
    hueSliderX[0]=ofMap(panel->getValueI("RHUERANGE"), 0, 255, colorSliderMinX, colorSliderMaxX);
    satSliderX[0]=ofMap(panel->getValueI("RSATRANGE"), 0, 255, colorSliderMinX, colorSliderMaxX);
    valSliderX[0]=ofMap(panel->getValueI("RVALRANGE"), 0, 255, colorSliderMinX, colorSliderMaxX);
    //green
    hueSliderX[1]=ofMap(panel->getValueI("GHUERANGE"), 0, 255, colorSliderMinX, colorSliderMaxX);
    satSliderX[1]=ofMap(panel->getValueI("GSATRANGE"), 0, 255, colorSliderMinX, colorSliderMaxX);
    valSliderX[1]=ofMap(panel->getValueI("GVALRANGE"), 0, 255, colorSliderMinX, colorSliderMaxX);
    //blue
    hueSliderX[2]=ofMap(panel->getValueI("BHUERANGE"), 0, 255, colorSliderMinX, colorSliderMaxX);
    satSliderX[2]=ofMap(panel->getValueI("BSATRANGE"), 0, 255, colorSliderMinX, colorSliderMaxX);
    valSliderX[2]=ofMap(panel->getValueI("BVALRANGE"), 0, 255, colorSliderMinX, colorSliderMaxX);
    
    
    //------------
    //ink phase
    blackThreshSliderY=270;
    blackThreshSliderMinX=500;
    blackThreshSliderMaxX=1000;
    blackThreshSliderX=ofMap(panel->getValueI("BTHRESHOLD"), 0, 255, blackThreshSliderMinX, blackThreshSliderMaxX);
    draggingblackThreshSlider=false;
    inkRefundButton.set(100, 700, 300, 150);
    inkUsedBeforeRefund=0;
    extraRefund=10; //just some extar inbk for the refund
    
    
    //------------
    //kinect phase
    saveDepthBackgroundButton.set(100,550,200,100);
    depthDiffMin=0;
    depthDiffMax=2000;
    depthSliderMinX=100;
    depthSliderMaxX=850;
    depthSliderY=850;
    depthSliderX=ofMap(panel->getValueI("MAXBGDIFF"), depthDiffMin, depthDiffMax, depthSliderMinX, depthSliderMaxX);
    draggingDepthSlider=false;
}

//------------------------------------------------------
void Calibration::update(){
    
    //------------
    //location phase
    if (phase=="Location"){
        //update the values
        xPos=ofMap(xPosSliderX,xPosSliderMinX,xPosSliderMaxX, xPosMin, xPosMax);
        panel->setValueI("PROJX", xPos);
        yPos=ofMap(yPosSliderY,yPosSliderMinY,yPosSliderMaxY, yPosMin, yPosMax);
        panel->setValueI("PROJY", yPos);
        scaleVal=ofMap(scaleSliderX,scaleSliderMinX,scaleSliderMaxX, scaleMin, scaleMax);
        panel->setValueF("PROJSCALE", scaleVal);
    }
    
    //------------
    //warp points phase
    if (phase=="Screen"){
        //set the warp points based on the current values in the panel
        warpPoints[0].set(panel->getValueF("TL_X")+kinectImageOffsetX,panel->getValueF("TL_Y")+kinectImageOffsetY);
        warpPoints[1].set(panel->getValueF("TR_X")+kinectImageOffsetX,panel->getValueF("TR_Y")+kinectImageOffsetY);
        warpPoints[2].set(panel->getValueF("BR_X")+kinectImageOffsetX,panel->getValueF("BR_Y")+kinectImageOffsetY);
        warpPoints[3].set(panel->getValueF("BL_X")+kinectImageOffsetX,panel->getValueF("BL_Y")+kinectImageOffsetY);
    }
}

//------------------------------------------------------
void Calibration::draw(){
    //cover the computer screen
    ofSetColor(0);
    ofFill();
    ofRect(0,0,ofGetScreenWidth(),ofGetScreenHeight());
    
    //draw the tabs at the top
    //put a grey bar behind everything
    ofSetColor(100);
    ofRect(0,0,ofGetScreenWidth(), tabStartY+tabH);
    for (int i=0; i<6; i++){
        cout<<"yo"<<endl;
        ofSetColor(50);    //grey for the tabs
        //if this is the tab we're on color it black
        if (phase== tabLabels[i])   ofSetColor(0);
        
        ofFill();
        ofRect(tabStartX+tabW*i,tabStartY,tabW,tabH);
        
        //draw a rectangle around it and put the title in it
        ofNoFill();
        ofSetColor(0);
        ofRect(tabStartX+tabW*i,tabStartY,tabW,tabH);
        ofSetColor(255);
        ofDrawBitmapString(tabLabels[i], tabStartX+tabW*i+20,tabStartY+35);
    }
    
    
    //------------
    //location phase
    if (phase=="Location"){
        ofNoFill();
        ofSetColor(255);
        //draw the sliders
        ofCircle(xPosSliderX,xPosSliderY,sliderSize);
        ofCircle(yPosSliderX,yPosSliderY,sliderSize);
        ofCircle(scaleSliderX,scaleSliderY,sliderSize);
        
        //draw the lines
        ofLine(xPosSliderMinX,xPosSliderY, xPosSliderMaxX, xPosSliderY);
        ofLine(yPosSliderX,yPosSliderMinY, yPosSliderX, yPosSliderMaxY);
        ofLine(scaleSliderMinX,scaleSliderY, scaleSliderMaxX, scaleSliderY);
        
        //label the lines
        float textOffsetY=sliderSize+10;
        ofDrawBitmapString("X position of projection", xPosSliderMinX, xPosSliderY-textOffsetY);
        ofDrawBitmapString("Y position of projection", yPosSliderX+textOffsetY, yPosSliderMinY);
        ofDrawBitmapString("scale of projection", scaleSliderMinX, scaleSliderY-textOffsetY);
    }
    
    
    //------------
    //warp points phase
    if (phase=="Screen"){
        
        //draw the image coming in from the kinect
        ofSetColor(255);
        colorImg->draw(kinectImageOffsetX,kinectImageOffsetY);
        
        //draw the shape from the warp points
        ofSetLineWidth(1);
        ofSetColor(255,0,100);
        ofNoFill();
        ofBeginShape();
        for (int i=0; i<4; i++)
            ofVertex(warpPoints[i].x,warpPoints[i].y);
        ofEndShape(true);
        
        //draw the handles
        for (int i=0; i<4; i++){
            ofCircle(warpPoints[i].x, warpPoints[i].y, warpPointHandleSize);
        }
        
        //and draw the output image
        ofSetColor(255);
        colorImgMedium->draw(800,600);
    }
    
    
    //---------------------
    //color setting phase
    if (phase=="Colors"){
        ofSetColor(255);
        
        //draw the color images
        for (int i=0; i<3; i++){
            float xSpacing=15;
            float drawY=colorImageOffsetY+ colorImgMedium->height*i + colorImagesSpacingY*i;
            
            ofSetColor(255);
            colorImgMedium->draw(colorImageOffsetX,drawY);
            
            if (i==0)   ofSetColor(255,0,0);
            if (i==1)   ofSetColor(0, 255, 0);
            if (i==2)   ofSetColor(0,0,255);
            
            colorImgs[i]->draw(colorImageOffsetX+colorImgMedium->width+xSpacing, drawY);
            
            //rectangle to seperate them
            ofSetLineWidth(3);
            ofNoFill();
            ofRect(colorImageOffsetX,drawY, colorImgMedium->width*2+xSpacing,colorImgMedium->height);
            
            //and the sliders
            ofSetColor(255);
            ofSetLineWidth(1);
            ofCircle(hueSliderX[i], hueSliderY[i], smallSliderSize);
            ofCircle(satSliderX[i], satSliderY[i], smallSliderSize);
            ofCircle(valSliderX[i], valSliderY[i], smallSliderSize);
            
            //lines for the sliders
            float textOffset=15;
            ofDrawBitmapString("Hue Range", colorSliderMinX, hueSliderY[i]-textOffset);
            ofLine(colorSliderMinX, hueSliderY[i], colorSliderMaxX, hueSliderY[i]);
            ofDrawBitmapString("Saturation Range", colorSliderMinX, satSliderY[i]-textOffset);
            ofLine(colorSliderMinX, satSliderY[i], colorSliderMaxX, satSliderY[i]);
            ofDrawBitmapString("Value Range", colorSliderMinX, valSliderY[i]-textOffset);
            ofLine(colorSliderMinX, valSliderY[i], colorSliderMaxX, valSliderY[i]);
        }
        
    }
    
    
    //------------
    //ink phase
    if (phase=="Ink"){
        //show the wall image for figuring out the black threshold
        int blackImgX=100;
        int blackImgY=200;
        float imageScale=2;
        ofSetColor(255);
        wallImg->draw(blackImgX,blackImgY, wallImg->width*imageScale, wallImg->height*imageScale);
        
        //draw a white border
        ofNoFill();
        ofRect(blackImgX,blackImgY,wallImg->width*imageScale, wallImg->height*imageScale);
        
        //show the slider
        ofSetLineWidth(1);
        ofLine(blackThreshSliderMinX, blackThreshSliderY, blackThreshSliderMaxX, blackThreshSliderY);
        ofCircle(blackThreshSliderX, blackThreshSliderY, sliderSize);
        
        //ink refund
        ofRect(inkRefundButton.x, inkRefundButton.y, inkRefundButton.width, inkRefundButton.height);
        ofDrawBitmapString("Click here to 0 ink levels", inkRefundButton.x+40, inkRefundButton.y+60);
        //write out what is used
        int displayValue=inkUsedBeforeRefund - panel->getValueI("INKREFUND") + extraRefund;
        //draw the text green if it is in a good range, otherwise red
        ofSetColor(100, 255, 100);
        if (abs(displayValue)>15)   ofSetColor(255, 100, 100);
        ofDrawBitmapString("Current ink level: "+ofToString(displayValue), 100, inkRefundButton.y-50);
    }
    
    
    //------------
    //kinect phase
    if (phase=="Kinect"){
        
        ofSetColor(255);
        
        int imgY=200;
        int imgXStart=50;
        int imgXSpacing=30;
        
        //show the kinect images
        depthImgSmall->draw(imgXStart, imgY);
        depthBackground->draw(imgXStart+depthImgSmall->width+imgXSpacing, imgY);
        depthBackgroundDiff->draw(imgXStart+depthImgSmall->width*2+imgXSpacing*2, imgY);
        
        //outline these
        ofSetLineWidth(1);
        ofNoFill();
        ofRect(imgXStart, imgY, depthImgSmall->width, depthImgSmall->height);
        ofRect(imgXStart+depthImgSmall->width+imgXSpacing, imgY, depthBackground->width, depthBackground->height);
        
        //make the difference image outline red if it detects somebody
        if (*depthPause)    ofSetColor(255,100,100);
        ofRect(imgXStart+depthImgSmall->width*2+imgXSpacing*2, imgY, depthBackground->width, depthBackground->height);
        
        //some descriptions
        ofSetColor(255);
        int textOffsetY=15;
        ofDrawBitmapString("What the Kinect sees:", imgXStart, imgY-textOffsetY);
        ofDrawBitmapString("Saved background image:", imgXStart+depthImgSmall->width+imgXSpacing, imgY-textOffsetY);
        ofDrawBitmapString("Difference between these images:", imgXStart+depthImgSmall->width*2+imgXSpacing*2, imgY-textOffsetY);
        
        //print a message about the if the difference image detects anybody
        if (*depthPause){
            ofSetColor(255, 100, 100);
            ofDrawBitmapString("I detect somebody's arm in front of the white board", imgXStart+depthImgSmall->width*2+imgXSpacing*2, imgY+depthBackgroundDiff->height+textOffsetY);
        }else{
            ofDrawBitmapString("Nobody in front of the white board", imgXStart+depthImgSmall->width*2+imgXSpacing*2, imgY+depthBackgroundDiff->height+textOffsetY);
            
        }
        
        //some instructions about the save backgorund button
        ofSetColor(255);
        ofDrawBitmapString("When nobody is in front of the Kinect, the background image should be the same as the Kinect image.\nThis will happen automaticly after it takes a picture, but if it gets stuck try resetting it.", 100,500);
        //save backgorund button
        ofRect(saveDepthBackgroundButton.x, saveDepthBackgroundButton.y, saveDepthBackgroundButton.width, saveDepthBackgroundButton.height);
        ofDrawBitmapString("Click Here To\nSave Background Image", saveDepthBackgroundButton.x+20,saveDepthBackgroundButton.y+45);
        
        //some instructions about the max background diff slider
        ofDrawBitmapString("If the difference image is not picking up on when somebody is in front of it, or it keeps saying that somebody is in front when they aren't,\ntry adjusting the Kinect sensitivity.\nErr on the side of making it higher, because you don't want it to interpret a random shadow as a hand", 100,700);
        //and the current level
        ofDrawBitmapString("Current sensitivity: "+ofToString(panel->getValueI("MAXBGDIFF")), depthSliderMinX, depthSliderY-textOffsetY-sliderSize);
        
        //draw the slider
        ofLine(depthSliderMinX, depthSliderY, depthSliderMaxX, depthSliderY);
        ofCircle(depthSliderX, depthSliderY, sliderSize);
        
    }
}

//------------------------------------------------------
void Calibration::keyPressed(int key){

        
    
}

//------------------------------------------------------
void Calibration::keyReleased(int key){
    
}

//------------------------------------------------------
void Calibration::mouseMoved(int x, int y ){
    
}

//------------------------------------------------------
void Calibration::mouseDragged(int x, int y, int button){
    
    //------------
    //location pahse
    if (phase=="Location"){
        if (draggingXPosSlider)
            xPosSliderX=MAX(xPosSliderMinX, MIN(xPosSliderMaxX, x));
        if (draggingYPosSlider)
            yPosSliderY=MAX(yPosSliderMinY, MIN(yPosSliderMaxY, y));
        if (draggingScaleSlider)
            scaleSliderX=MAX(scaleSliderMinX, MIN(scaleSliderMaxX, x));
    }
    
    //Screen phase
    if (phase=="Screen"){
        //if any warp points are being dragged, move them
        float newPosX=x-kinectImageOffsetX;   //account for the display offset
        float newPosY=y-kinectImageOffsetY;
        if (draggingWarpPoint[0]){
            panel->setValueF("TL_X", newPosX);
            panel->setValueF("TL_Y", newPosY);
        }
        if (draggingWarpPoint[1]){
            panel->setValueF("TR_X", newPosX);
            panel->setValueF("TR_Y", newPosY);
        }
        if (draggingWarpPoint[2]){
            panel->setValueF("BR_X", newPosX);
            panel->setValueF("BR_Y", newPosY);
        }
        if (draggingWarpPoint[3]){
            panel->setValueF("BL_X", newPosX);
            panel->setValueF("BL_Y", newPosY);
        }
    }
    
    //---------------------
    //color setting phase
    if (phase=="Colors"){
        //check if the mouse was pressed down inside any of the color options
        
        for (int i=0; i<3; i++){
            float top=colorImageOffsetY+ colorImgMedium->height*i + colorImagesSpacingY*i;
            float bottom=top+colorImgMedium->height;
            float left=colorImageOffsetX;
            float right=colorImageOffsetX+colorImgMedium->width;
            
            //check if the mouse is in that range
            if (x>left && x<right && y>top && y<bottom){
                int pixel = (y-top) * colorImgMedium->width + (x-left);
                
                if (i==0){  //red
                    panel->setValueF("RH",hueImg->getPixels()[pixel]);
                    panel->setValueF("RS",satImg->getPixels()[pixel]);
                    panel->setValueF("RV",briImg->getPixels()[pixel]);
                }
                if (i==1){  //green
                    panel->setValueF("GH",hueImg->getPixels()[pixel]);
                    panel->setValueF("GS",satImg->getPixels()[pixel]);
                    panel->setValueF("GV",briImg->getPixels()[pixel]);
                }
                if (i==2){  //blue
                    panel->setValueF("BH",hueImg->getPixels()[pixel]);
                    panel->setValueF("BS",satImg->getPixels()[pixel]);
                    panel->setValueF("BV",briImg->getPixels()[pixel]);
                }
            }
            
            //if the user is dragging a slider, update it
            if (draggingHueSlider[i]){
                hueSliderX[i]=MAX(colorSliderMinX, MIN(colorSliderMaxX, x));
                int hueRange = ofMap(hueSliderX[i], colorSliderMinX, colorSliderMaxX, 0, 255);
                //set the value depending on which colo was being dragged
                if (i==0) panel->setValueI("RHUERANGE", hueRange);
                if (i==1) panel->setValueI("GHUERANGE", hueRange);
                if (i==2) panel->setValueI("BHUERANGE", hueRange);
            }
            if (draggingSatSlider[i]){
                satSliderX[i]=MAX(colorSliderMinX, MIN(colorSliderMaxX, x));
                int satRange = ofMap(satSliderX[i], colorSliderMinX, colorSliderMaxX, 0, 255);
                //set the value depending on which colo was being dragged
                if (i==0) panel->setValueI("RSATRANGE", satRange);
                if (i==1) panel->setValueI("GSATRANGE", satRange);
                if (i==2) panel->setValueI("BSATRANGE", satRange);
            }
            if (draggingValSlider[i]){
                valSliderX[i]=MAX(colorSliderMinX, MIN(colorSliderMaxX, x));
                int valRange = ofMap(valSliderX[i], colorSliderMinX, colorSliderMaxX, 0, 255);
                //set the value depending on which colo was being dragged
                if (i==0) panel->setValueI("RVALRANGE", valRange);
                if (i==1) panel->setValueI("GVALRANGE", valRange);
                if (i==2) panel->setValueI("BVALRANGE", valRange);
            }
        }   
    }
    
    //------------
    //ink phase
    if (phase=="Ink"){
        //move the black threshold slider if the user is dragging it
        if (draggingblackThreshSlider){
            blackThreshSliderX=MAX(blackThreshSliderMinX, MIN(blackThreshSliderMaxX, x));
            panel->setValueI("BTHRESHOLD", ofMap(x,blackThreshSliderMinX, blackThreshSliderMaxX,0,255) );
        }
       
    }
    
    //-------------
    //kinect phase
    if (phase=="Kinect"){
        //see if the depth slider is being dragged
        if (draggingDepthSlider){
            depthSliderX=MAX(depthSliderMinX, MIN(depthSliderMaxX, x));
            panel->setValueI("MAXBGDIFF", ofMap(x,depthSliderMinX, depthSliderMaxX,depthDiffMin,depthDiffMax) );

        }
    
    }
}

//------------------------------------------------------
void Calibration::mousePressed(int x, int y, int button){
    
    //check if the user clicked a tab
    if (y>tabStartY && y<tabStartY+tabH && x>tabStartX && x<tabStartX+tabW*6){
        int tabNum= floor((x-tabStartX)/tabW);
        phase=tabLabels[tabNum];
        //save the data
        panel->saveSettings();
    }
    
    //------------
    //Location phase
    if (phase=="Location"){
        //see if any sliders were selected
        if (ofDist(x,y, xPosSliderX, xPosSliderY)<sliderSize)   draggingXPosSlider=true;
        if (ofDist(x,y, yPosSliderX, yPosSliderY)<sliderSize)   draggingYPosSlider=true;
        if (ofDist(x,y, scaleSliderX, scaleSliderY)<sliderSize)   draggingScaleSlider=true;
    }
    
    //------------
    //Screen phase
    if (phase=="Screen"){
        //see if any handles were selected
        for (int i=0; i<4; i++){
            if (ofDist(x,y, warpPoints[i].x, warpPoints[i].y)<warpPointHandleSize)
                draggingWarpPoint[i]=true;
        }
    }
    
    //---------------------
    //color setting phase
    if (phase=="Colors"){
        //check if the mouse was pressed down inside any of the color options
        
        for (int i=0; i<3; i++){
            float top=colorImageOffsetY+ colorImgMedium->height*i + colorImagesSpacingY*i;
            float bottom=top+colorImgMedium->height;
            float left=colorImageOffsetX;
            float right=colorImageOffsetX+colorImgMedium->width;
            
            //check if the mouse is in that range
            if (x>left && x<right && y>top && y<bottom){
                int pixel = (y-top) * colorImgMedium->width + (x-left);
                
                if (i==0){  //red
                    panel->setValueF("RH",hueImg->getPixels()[pixel]);
                    panel->setValueF("RS",satImg->getPixels()[pixel]);
                    panel->setValueF("RV",briImg->getPixels()[pixel]);
                }
                if (i==1){  //green
                    panel->setValueF("GH",hueImg->getPixels()[pixel]);
                    panel->setValueF("GS",satImg->getPixels()[pixel]);
                    panel->setValueF("GV",briImg->getPixels()[pixel]);
                }
                if (i==2){  //blue
                    panel->setValueF("BH",hueImg->getPixels()[pixel]);
                    panel->setValueF("BS",satImg->getPixels()[pixel]);
                    panel->setValueF("BV",briImg->getPixels()[pixel]);
                }
            }
            
            //see if the user clicked on a slider
            if (ofDist(x,y, hueSliderX[i], hueSliderY[i])<smallSliderSize)  draggingHueSlider[i]=true;
            if (ofDist(x,y, satSliderX[i], satSliderY[i])<smallSliderSize)  draggingSatSlider[i]=true;
            if (ofDist(x,y, valSliderX[i], valSliderY[i])<smallSliderSize)  draggingValSlider[i]=true;
        }
    }
    
    //------------
    //ink phase
    if (phase=="Ink"){
        //check if the user clicked on the black threshold sldier
        if (ofDist(x,y,blackThreshSliderX, blackThreshSliderY)<sliderSize)
            draggingblackThreshSlider=true;
        
        //check if the inkRefund button was clicked
        if (inkRefundButton.inside(x, y)){
            panel->setValueI("INKREFUND", inkUsedBeforeRefund+extraRefund);
        }
    }
    
    //-------------
    //kinect phase
    if (phase=="Kinect"){
        //check if the user clicked on save backgorund button
        if (saveDepthBackgroundButton.inside(x, y))
            *saveDepthBackground = true;
        //or the depth slider
        if (ofDist(x,y,depthSliderX,depthSliderY),sliderSize)   draggingDepthSlider=true;
    }
    
    
}

//------------------------------------------------------
void Calibration::mouseReleased(int x, int y, int button){
    
    //turn off any dragging sldiers that might be on
    
    //Locaiton phase
    draggingXPosSlider=false;
    draggingYPosSlider=false;
    draggingScaleSlider=false;
    
    //Screen phase
    for (int i=0; i<4; i++)
        draggingWarpPoint[i]=false;
    
    //color setting phase
    for (int i=0; i<3; i++){
        draggingHueSlider[i]=false;
        draggingSatSlider[i]=false;
        draggingValSlider[i]=false;
    }
    
    //ink phase
    draggingblackThreshSlider=false;
    
    //kinect phase
    draggingDepthSlider=false;
}


