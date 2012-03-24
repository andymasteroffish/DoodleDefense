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
    
    //next button
    nextButtonX=1200;
    nextButtonY=750;
    nextButtonPic.loadImage("calibration/nextButton.png");
    
    //font
    font.loadFont("Helvetica.dfont", 15);
    fontSmall.loadFont("Helvetica.dfont", 11);
    
    //backgorunds
    locationBackground.loadImage("calibration/locationBackground.png");
    screenBackground.loadImage("calibration/screenBackground.png");
    colorsBackground.loadImage("calibration/colorsBackground.png");
    inkBackground.loadImage("calibration/inkBackground.png");
    
    //------------
    //location phase
    xPosMin=0;
    xPosMax=2700;
    xPos=panel->getValueF("PROJX");
    xPosSliderMinX=200;
    xPosSliderMaxX=850;
    xPosSliderX=ofMap(xPos,xPosMin,xPosMax,xPosSliderMinX,xPosSliderMaxX);
    xPosSliderY=800;
    draggingXPosSlider=false;
    
    yPosMin=0;
    yPosMax=900;
    yPos=panel->getValueF("PROJY");
    yPosSliderMinY=500;
    yPosSliderMaxY=900;
    yPosSliderX=100;
    yPosSliderY=ofMap(yPos,yPosMin,yPosMax,yPosSliderMinY,yPosSliderMaxY);
    draggingYPosSlider=false;
    
    scaleMin=0.2;
    scaleMax=3;
    scaleVal=panel->getValueF("PROJSCALE");
    scaleSliderMinX=200;
    scaleSliderMaxX=850;
    scaleSliderX=ofMap(scaleVal,scaleMin,scaleMax, scaleSliderMinX, scaleSliderMaxX);
    scaleSliderY=900;
    draggingScaleSlider=false;
    
    
    //------------
    //warp points phase
    kinectImageOffsetX=50;
    kinectImageOffsetY=300;
    warpPointHandleSize=10;
    for (int i=0; i<4; i++)
        draggingWarpPoint[i]=false;
    
    
    //------------
    //color setting phase
    colorImageOffsetX=50;
    colorImageOffsetY=150;
    colorImagesSpacingY=15;
    //sliders
    colorSliderMinX=750;
    colorSliderMaxX=1000;
    
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
    blackThreshSliderY=470;
    blackThreshSliderMinX=700;   
    blackThreshSliderMaxX=1200;
    blackThreshSliderX=ofMap(panel->getValueI("BTHRESHOLD"), 255, 0, blackThreshSliderMinX, blackThreshSliderMaxX);
    draggingblackThreshSlider=false;
    inkRefundButton.set(200, 700, 300, 150);
    inkUsedBeforeRefund=0;
    extraRefund=10; //just some extra ink for the refund
    
    
    //------------
    //game phase
    startGameButton.set(100,150,600,100);
    
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
    *showRect =false;
    
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
        *showRect =true; //show the guideing rectangle
        //set the warp points based on the current values in the panel
        warpPoints[0].set(panel->getValueF("TL_X")+kinectImageOffsetX,panel->getValueF("TL_Y")+kinectImageOffsetY);
        warpPoints[1].set(panel->getValueF("TR_X")+kinectImageOffsetX,panel->getValueF("TR_Y")+kinectImageOffsetY);
        warpPoints[2].set(panel->getValueF("BR_X")+kinectImageOffsetX,panel->getValueF("BR_Y")+kinectImageOffsetY);
        warpPoints[3].set(panel->getValueF("BL_X")+kinectImageOffsetX,panel->getValueF("BL_Y")+kinectImageOffsetY);
    }
    
    //don't show the game during the color pashe
    if (phase=="Colors" || phase=="Ink")
        showGame=false;
    else
        showGame=true;
    
}

//------------------------------------------------------
void Calibration::draw(){
    
    
    //------------
    //location phase
    if (phase=="Location"){
        ofNoFill();
        ofSetColor(255);
        
        //draw the background
        locationBackground.draw(0,0);
        
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
        font.drawString("X position of projection", xPosSliderMinX, xPosSliderY-textOffsetY);
        font.drawString("Y position of projection", yPosSliderX-70, yPosSliderMinY-20);
        font.drawString("scale of projection", scaleSliderMinX, scaleSliderY-textOffsetY);
    }
    
    
    //------------
    //warp points phase
    if (phase=="Screen"){
        //background
        ofSetColor(255);
        screenBackground.draw(0,0);
        
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
        colorImgMedium->draw(700,kinectImageOffsetY+colorImgMedium->height);
        
        
    }
    
    
    //---------------------
    //color setting phase
    if (phase=="Colors"){
        //background
        ofSetColor(255);
        colorsBackground.draw(0,0);
        
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
            fontSmall.drawString("Hue Range", colorSliderMinX, hueSliderY[i]-textOffset);
            ofLine(colorSliderMinX, hueSliderY[i], colorSliderMaxX, hueSliderY[i]);
            fontSmall.drawString("Saturation Range", colorSliderMinX, satSliderY[i]-textOffset);
            ofLine(colorSliderMinX, satSliderY[i], colorSliderMaxX, satSliderY[i]);
            fontSmall.drawString("Value Range", colorSliderMinX, valSliderY[i]-textOffset);
            ofLine(colorSliderMinX, valSliderY[i], colorSliderMaxX, valSliderY[i]);
        }
        
    }
    
    
    //------------
    //ink phase
    if (phase=="Ink"){
        //background
        ofSetColor(255);
        inkBackground.draw(0,0);
        
        //show the wall image for figuring out the black threshold
        int blackImgX=200;
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
        font.drawString("Click here to\n0 ink levels", inkRefundButton.x+50, inkRefundButton.y+60);
        //write out what is used
        int displayValue=inkUsedBeforeRefund - panel->getValueI("INKREFUND") + extraRefund;
        //draw the text green if it is in a good range, otherwise red
        ofSetColor(100, 255, 100);
        if (abs(displayValue)>30)   ofSetColor(255, 100, 100);
        font.drawString("Current ink level: "+ofToString(displayValue), 200, inkRefundButton.y-50);
    }
    
    //------------
    //kinect phase
    if (phase=="Game"){
        //draw the color images
        float xOffset=800;
        float yStart=150;
        for (int i=0; i<3; i++){
            float drawY=yStart + (colorImagesSpacingY+colorImgs[i]->height)*i;
            
            if (i==0)   ofSetColor(255,0,0);
            if (i==1)   ofSetColor(0, 255, 0);
            if (i==2)   ofSetColor(0,0,255);
            
            colorImgs[i]->draw(xOffset, drawY);
            
            //rectangle to seperate them
            ofSetLineWidth(3);
            ofNoFill();
            ofRect(xOffset,drawY, colorImgs[i]->width,colorImgs[i]->height);
        }
        
         ofSetColor(255);
        //some text about the color images
        string colorText="These are the color images the Kinect sees.";
        colorText+="\nIf they are not seeing the\ncolors drawn on screen";
        colorText+="\nor they are catching\nthings not in that color,";
        colorText+="\ncheck the Colors tab.";
        font.drawString(colorText, xOffset+colorImgs[0]->width+20, yStart+200);
        
        //start game button
        if (*gameStarted==false){
            font.drawString("Erase the board and click here to start the game!", startGameButton.x+20,startGameButton.y+50);
            ofNoFill();
            ofRect(startGameButton.x, startGameButton.y, startGameButton.width, startGameButton.height);
        }
        
        //write why the game might be paused if it is
        string pauseInfo="";
        if (*paused){
            pauseInfo+="The game is paused because...";
            
            //go through each reason
            if (! *gameStarted)
                pauseInfo+="\nYou haven't started the game.";
            if (*playerPause)
                pauseInfo+="\nYou paused it.";
            if (*noPath)
                pauseInfo+="\nThere is no path for the foes.\n    (If that seems wrong, check the ink tab)";
            if (*tooMuchInk)
                pauseInfo+="\nThe player went over their ink limit.\n    (If that seems wrong, check the ink tab)";
            if (*depthPause)
                pauseInfo+="\nThe Kinect senses somebody in front of the game.\n    (If that seems wrong, check the Kinect tab)";
            
        }
        else{
            pauseInfo="The game is playing";
        }
        //write it
        font.drawString(pauseInfo,100,300);
        
        //other info
        string otherInfo="If the game is not pausing when the player is drawing,\ncheck the Kinect tab.\n\n";
        otherInfo+="Press P to pause the game.\n";
        otherInfo+="Press F to fast forward.\n";
        otherInfo+="Press ENTER to reset the game.\n";
        otherInfo+="Press SPACE to take a new image of the board.\n";
        otherInfo+="Press UP or DOWN to adjust Kinect angle.";
        font.drawString(otherInfo, 100, 700);
        
        
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
        fontSmall.drawString("What the Kinect sees:", imgXStart, imgY-textOffsetY);
        fontSmall.drawString("Saved background image:", imgXStart+depthImgSmall->width+imgXSpacing, imgY-textOffsetY);
        fontSmall.drawString("Difference between these images:", imgXStart+depthImgSmall->width*2+imgXSpacing*2, imgY-textOffsetY);
        
        //print a message about the if the difference image detects anybody
        if (*depthPause){
            ofSetColor(255, 100, 100);
            fontSmall.drawString("I detect somebody's arm in front of the white board", imgXStart+depthImgSmall->width*2+imgXSpacing*2, imgY+depthBackgroundDiff->height+textOffsetY);
        }else{
            fontSmall.drawString("Nobody in front of the white board", imgXStart+depthImgSmall->width*2+imgXSpacing*2, imgY+depthBackgroundDiff->height+textOffsetY);
            
        }
        
        //some instructions about the save backgorund button
        ofSetColor(255);
        fontSmall.drawString("When nobody is in front of the Kinect, the background image should be the same as the Kinect image.\nThis will happen automaticly after it takes a picture, but if it gets stuck try resetting it.", 100,500);
        //save backgorund button
        ofRect(saveDepthBackgroundButton.x, saveDepthBackgroundButton.y, saveDepthBackgroundButton.width, saveDepthBackgroundButton.height);
        fontSmall.drawString("Click Here To\nSave Background Image", saveDepthBackgroundButton.x+10,saveDepthBackgroundButton.y+45);
        
        //some instructions about the max background diff slider
        fontSmall.drawString("If the difference image is not picking up on when somebody is in front of it, or it keeps saying that somebody is in front when they aren't,\ntry adjusting the Kinect sensitivity.\nErr on the side of making it higher, because you don't want it to interpret a random shadow as a hand", 100,700);
        //and the current level
        fontSmall.drawString("Current sensitivity: "+ofToString(panel->getValueI("MAXBGDIFF")), depthSliderMinX, depthSliderY-textOffsetY-sliderSize);
        
        //draw the slider
        ofLine(depthSliderMinX, depthSliderY, depthSliderMaxX, depthSliderY);
        ofCircle(depthSliderX, depthSliderY, sliderSize);
        
    }
    
    //draw the tabs at the top
    //put a grey bar behind everything
    ofSetColor(100);
    ofFill();
    ofSetLineWidth(1);
    ofRect(0,0,ofGetScreenWidth(), tabStartY+tabH);
    for (int i=0; i<6; i++){
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
        font.drawString(tabLabels[i], tabStartX+tabW*i+20,tabStartY+35);
    }
    
    //draw the next button if this tab includes it
    if (phase=="Location" || phase=="Screen" || phase=="Colors" || phase=="Ink"){
        nextButtonPic.draw(nextButtonX,nextButtonY);
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
            panel->setValueI("BTHRESHOLD", ofMap(x,blackThreshSliderMinX, blackThreshSliderMaxX,255,0) );
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
        
        //if this puts us in the game phase, snap a picture
        if (phase=="Game")   *takePictureTimer=2;
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
    //game phase
    if (phase=="Game"){
        //check if the user clicked on save backgorund button
        if (startGameButton.inside(x, y))
            *gameStarted = true;
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
    
    
    //check if the next button was clicked
    if (x>nextButtonX && x<nextButtonX+nextButtonPic.width && y>nextButtonY && y<nextButtonY+nextButtonPic.height){
        //not every phase does something, but the ones that do should advance it
        if (phase=="Location")
            phase="Screen";
        else if (phase=="Screen")
            phase="Colors";
        else if (phase=="Colors")
            phase="Ink";
        else if (phase=="Ink"){
            phase="Game";
            *takePictureTimer=2;    //snap a picture
        }
        
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
    
    //save the data
    panel->saveSettings();
}


