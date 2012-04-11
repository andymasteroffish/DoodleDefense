/***********************
 * Andy Wallace        *
 * copyright 2012      *
 ***********************/

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(30);
    ofBackground(255);
    
    fieldW=160;
    fieldH=120;
    
    healthStart=15;
    startInk=450;
    
    waveAnimationTime=5;    //flash for x seconds when a wave is finished
    
    showAllInfo=false;
    
    changePause=false;
    playerPause=false;
    
    fastForward=false;
    
    //taking an image of the board
    takePictureTime    = 20;
    takePictureDelay    = 25;
    
    //ink values
    blackInkValue   = 0.2;
    rInkValue       = 2.5;
    gInkValue       = 3.5;
    bInkValue       = 3.0;
    
    //panel
    panel.setup("cv settings", 1300, 0, 300, 700);
	panel.addPanel("control", 1, false);
	
	panel.setWhichPanel("control");
	panel.setWhichColumn(0);
	
	panel.addToggle("video settings", "VIDEO_SETTINGS", false);
	
	panel.addSlider("black threshold ", "BTHRESHOLD", 100, 0, 255, true);
    panel.addSlider("max compacntess ", "MAXCOMPACT", 1.5, 1, 3, false);
    
    panel.addSlider("proj X ", "PROJX", 0, 0, 2700, true);
    panel.addSlider("proj Y ", "PROJY", 0, 0, 900, true);
    panel.addSlider("proj scale ", "PROJSCALE", 1, 0.2, 3, false);
    panel.addSlider("max background diff ", "MAXBGDIFF", 6, 0, 3000, true);
    
    //temporary values for getting HUD elements right
     panel.addSlider("HUD X", "HUDX", 0, -1500, 1500, true);
     panel.addSlider("HUD Y ", "HUDY", 0, -1500, 1500, true);
    
    panel.addPanel("warp", 1, false);
    panel.setWhichPanel("warp");
	panel.setWhichColumn(0);
    panel.addSlider("top left x", "TL_X", 0, 0, 640, true);
    panel.addSlider("top left y", "TL_Y", 0, 0, 480, true);
    panel.addSlider("top right x", "TR_X", 640, 0, 640, true);
    panel.addSlider("top right y", "TR_Y", 0, 0, 480, true);
    panel.addSlider("bottom right x", "BR_X", 640, 0, 640, true);
    panel.addSlider("bottom right y", "BR_Y", 480, 0, 480, true);
    panel.addSlider("bottom left x", "BL_X", 0, 0, 640, true);
    panel.addSlider("bottom left y", "BL_Y", 480, 0, 480, true);
    
    panel.addPanel("ink values", 1, false);
    panel.setWhichPanel("ink values");
	panel.setWhichColumn(0);
    panel.addSlider("inkRefund", "INKREFUND",  150, 0, 3000, true);
    
    
    panel.addPanel("color values", 1, false);
    panel.setWhichPanel("color values");
	panel.setWhichColumn(0);
    panel.addSlider("rH", "RH", 0, 0, 255, true);
    panel.addSlider("rS", "RS", 0, 0, 255, true);
    panel.addSlider("rV", "RV", 0, 0, 255, true);
    panel.addSlider("gH", "GH", 0, 0, 255, true);
    panel.addSlider("gS", "GS", 0, 0, 255, true);
    panel.addSlider("gV", "GV", 0, 0, 255, true);
    panel.addSlider("bH", "BH", 0, 0, 255, true);
    panel.addSlider("bS", "BS", 0, 0, 255, true);
    panel.addSlider("bV", "BV", 0, 0, 255, true);
    
    panel.addPanel("color tracking", 1, false);
    panel.setWhichPanel("color tracking");
	panel.setWhichColumn(0);
    panel.addSlider("R hue range ", "RHUERANGE", 20, 0, 255, true);
	panel.addSlider("R sat range ", "RSATRANGE", 30, 0, 255, true);
	panel.addSlider("R val range ", "RVALRANGE", 25, 0, 255, true);
    panel.addSlider("G hue range ", "GHUERANGE", 20, 0, 255, true);
	panel.addSlider("G sat range ", "GSATRANGE", 30, 0, 255, true);
	panel.addSlider("G val range ", "GVALRANGE", 25, 0, 255, true);
    panel.addSlider("B hue range ", "BHUERANGE", 20, 0, 255, true);
	panel.addSlider("B sat range ", "BSATRANGE", 30, 0, 255, true);
	panel.addSlider("B val range ", "BVALRANGE", 25, 0, 255, true);

    
    panel.loadSettings("cvSettings.xml");
    
    //set up video
    video.initGrabber(640, 480);
    
    //fonts
    string fontName="JolenesHand-Regular.ttf";
    infoFontSmall.loadFont(fontName, 40, true, true);
    infoFont.loadFont(fontName, 50, true, true);
    infoFontBig.loadFont(fontName, 75, true, true);
    infoFontHuge.loadFont(fontName, 100, true, true);
    
    //saving a picture of the board
    boardImg.allocate(fieldW*4,fieldH*4);
    savingBoardPicture=false;
    readyToDrawBoardPicture=false;
    
    //color tracking
    colorImg.allocate(video.width, video.height);
    
    //set the small image
    colorImgMedium.allocate(fieldW*2, fieldH*2);
    greyImg.allocate(colorImgMedium.width, colorImgMedium.height);
	
    //make all of the other images the same size
    hsvImg.allocate(colorImgMedium.width, colorImgMedium.height);
    hueImg.allocate(colorImgMedium.width, colorImgMedium.height);
    satImg.allocate(colorImgMedium.width, colorImgMedium.height);
    briImg.allocate(colorImgMedium.width, colorImgMedium.height);
    
    //black image
    blackImg.allocate(fieldW, fieldH);
    
    //r,g,b images
    for (int i=0; i<3; i++){
        colorImgs[i].allocate(colorImgMedium.width, colorImgMedium.height);
        colorImgsDisplay[i].allocate(colorImgMedium.width, colorImgMedium.height);
        hue[i]=0;
        sat[i]=0;
        val[i]=0;
        
        colorPixels[i]= new unsigned char [colorImgMedium.width * colorImgMedium.height];
        
    }
    
    //using depth to see when a player is in front of the board
    saveChangeBackground=true;
    changeImg.allocate(video.width, video.height);
    changeImgSmall.allocate(colorImgMedium.width, colorImgMedium.height);
    changeBackground.allocate(colorImgMedium.width, colorImgMedium.height);
    changeBackgroundDiff.allocate(colorImgMedium.width, colorImgMedium.height);
    
    //taking new pictures of the screen
    takePictureTime=10;
    takePictureTimer=-1;    //start it where the count down won't matter
    
    //testing 
    showRect=false;
    showGame=false;
    gameStarted=false;
    
    //set up the images
    wallPixels = new unsigned char [fieldW * fieldH];
    wallImage.allocate(fieldW, fieldH);
    lastSafeWallImage.allocate(fieldW, fieldH);
    wallDiffImage.allocate(fieldW, fieldH);
    
    //set the maze border
    mazeTop=10;
    mazeBottom=fieldH-4;
    mazeLeft=10;
    mazeRight=fieldW-4;
    
    //border
    borderPics[0].loadImage("walls1Entrance.png");
    borderPics[1].loadImage("walls2Entrance.png");
    
    //foe images
    for (int i=0; i<NUM_FOE_FRAMES; i++){
        normFoePic[0][i].loadImage("foePics/normal/normal"+ofToString(i+1)+".png");
        normFoePic[1][i].loadImage("foePics/normal/nfill"+ofToString(i+1)+".png");
        fastFoePic[0][i].loadImage("foePics/fast/fast"+ofToString(i+1)+".png");
        fastFoePic[1][i].loadImage("foePics/fast/ffill"+ofToString(i+1)+".png");
        heavyFoePic[0][i].loadImage("foePics/heavy/heavy"+ofToString(i+1)+".png");
        heavyFoePic[1][i].loadImage("foePics/heavy/hfill"+ofToString(i+1)+".png");
        stealthFoePic[0][i].loadImage("foePics/stealth/stealth"+ofToString(i+1)+".png");
        stealthFoePic[1][i].loadImage("foePics/stealth/sfill"+ofToString(i+1)+".png");
        immuneRedFoePic[0][i].loadImage("foePics/immune/immune"+ofToString(i+1)+".png");
        immuneRedFoePic[1][i].loadImage("foePics/immune/ifill"+ofToString(i+1)+".png");
    }
    
    //explosion and puff images
    explosionPic.loadImage("misc/explosionFill.png");
    
    //getting ink back when towers and walls are erased
    towerRefund=0.7;    //what percentage of the tower's value a player gets back when they kill one
    wallRefund=0.85;
    
    //start wall pixels off blank
    for (int i=0; i<fieldW*fieldH; i++)
        wallPixels[i]=255;
    //set the borders
    setMazeBorders();
    
    //fieldScale=(ofGetHeight()/(float)fieldH);
    fieldScale=7;
    
    VF.setupField(128, 96,fieldW*fieldScale, fieldH*fieldScale);
    
    startX[0]=60/fieldScale;
    startY[0]=fieldH*fieldScale/2+25;
    startX[1]=fieldW*fieldScale/2+25;
    startY[1]=60/fieldScale;
    goalX[0]=fieldW*fieldScale-10;
    goalY[0]=fieldH*fieldScale/2+25;
    goalX[1]=fieldW*fieldScale/2+25;
    goalY[1]=fieldH*fieldScale-10;
    
    
    //setup calibration with pointers to everything it needs
    calibration.panel= &panel;
    calibration.showRect= &showRect;
    calibration.colorImg = &colorImg;
    calibration.colorImgMedium = &colorImgMedium;
    calibration.colorImgs[0] = &colorImgs[0];
    calibration.colorImgs[1] = &colorImgs[1];
    calibration.colorImgs[2] = &colorImgs[2];
    calibration.hueImg = &hueImg;
    calibration.satImg = &satImg;
    calibration.briImg = &briImg;
    calibration.blackImg = &blackImg;
    calibration.wallImg = &wallImage;
    calibration.greyImg = &greyImg;
    calibration.changeImgSmall = &changeImgSmall;
    calibration.changeBackground = &changeBackground;
    calibration.changeBackgroundDiff = &changeBackgroundDiff;
    calibration.saveChangeBackground = &saveChangeBackground;
    calibration.takePictureTimer = &takePictureTimer;
    //reasons the game might be paused
    calibration.paused = &paused;
    calibration.playerPause= &playerPause;
    calibration.noPath = &noPath;
    calibration.tooMuchInk = &tooMuchInk;
    calibration.changePause = &changePause;
    calibration.gameStarted= &gameStarted;
    calibration.setup();
    
    //set up the scale to display the calibration info if the app would be larger than the screen
    screenScale=1;  //if the screen is large enough, don't do anything to the scale
    if (ofGetHeight()>ofGetScreenHeight()){
        screenScale=((float)ofGetScreenHeight()/(float)ofGetHeight()) *0.98;    //just shrink it slightly more
    }
    
    
    reset();
    convertDrawingToGame();
    
    int skipTo=0;
    totalInk=getInkFromWaves(skipTo);
    curWave=skipTo;
    numEntrances=1;
    
    video.videoSettings();
}


//--------------------------------------------------------------
void testApp::loadFromText(){ 
    waves.clear();  //get rid of any waves that may be there
    
    //load in the text file
	ifstream fin;
	fin.open(ofToDataPath("waves.txt").c_str());
	
	while(fin!=NULL) //as long as theres still text to be read  
	{  
		string full; //declare a string for storage  
		getline(fin, full); //get a line from the file, put it in the string 
        
        //if there are not at least 4 characters it is not a command and the line can be skipped
        if (full.length()>3){
            //split the string into the command and value
            string cmd=full.substr(0,3);    //command is the first 3 values
            string val=full.substr(4);  //value is everything after the space
            
            //check commands
            
            //create a new wave at the given level. This must be the first command
            if (cmd=="new"){
                int level= atoi(val.c_str());
                //create a new wave and add it to the vector
                Wave newWave;
                newWave.setup(level);
                waves.push_back(newWave);
            }
            
            //set the time
            if (cmd=="dur"){
                int duration= atoi(val.c_str());
                waves[waves.size()-1].setTime(duration);
            }
            
            //add a number of foes
            if (cmd=="add"){
                //there are two values here, a name and a number seperated by a space
                size_t spacePos=val.find(" ");
                string name=val.substr(0,spacePos);
                string numString=val.substr(spacePos+1);
                int num=atoi(numString.c_str());
                
                waves[waves.size()-1].addFoes(name, num);
            }
            
            //add a message
            if (cmd=="mes"){
                waves[waves.size()-1].setMessage(val);
            }
            
            //randomize the wave
            if (cmd=="ran"){
                waves[waves.size()-1].randomize();
            }
        }
	}
}

//--------------------------------------------------------------
void testApp::reset(){ 
    
    //clear out any foes if there are any
    for (int i=foes.size()-1; i>=0; i--)
        killFoe(i);
    
    //set all towers to think the player is alive
    for (int i=0; i<towers.size(); i++)
        towers[i]->playerDead=false;
    
    health=healthStart;
    totalInk=startInk;
    score=0;
    tooMuchInk=false;
    numEntrances=1;
    nextEntrance=0;
    
    damageFlashTimer=0;
    
    //clear any ink coming to the player
    inkParticles.clear();
    
    //set all of the pixels to blank
    for (int i=0; i<fieldW*fieldH; i++){
        wallPixels[i]=255;
    }
    
    paused=false;
    noPath=false;
    
    towerID=0;
    
    curWave=-1;
    wavesDone=false;
    loadFromText();
    startNextWave();
}

//--------------------------------------------------------------
void testApp::update(){
    calibration.update();
    
    //wall image needs updating if that is being set
    if (calibration.phase=="Ink"){
        wallImage=blackImg;
        wallPixels=wallImage.getPixels();
        thickenWallImage();
        setMazeBorders();
    }
    
    //update the panel
    panel.update();
    //color tracking
	hueRange[0]			= panel.getValueI("RHUERANGE");
	satRange[0]			= panel.getValueI("RSATRANGE");
	valRange[0]			= panel.getValueI("RVALRANGE");
    hueRange[1]			= panel.getValueI("GHUERANGE");
	satRange[1]			= panel.getValueI("GSATRANGE");
	valRange[1]			= panel.getValueI("GVALRANGE");
    hueRange[2]			= panel.getValueI("BHUERANGE");
	satRange[2]			= panel.getValueI("BSATRANGE");
	valRange[2]			= panel.getValueI("BVALRANGE");
    
    blackThreshold      = panel.getValueI("BTHRESHOLD");
    maxCompactness      = panel.getValueF("MAXCOMPACT");
    //setting the ocation/size of the projection
    projX			= panel.getValueF("PROJX");
    projY			= panel.getValueF("PROJY");
    projScale		= panel.getValueF("PROJSCALE");
    maxChangeDiff    = panel.getValueI("MAXBGDIFF");

    //warp points
    warpPoints[0].x = panel.getValueI("TL_X");
    warpPoints[0].y = panel.getValueI("TL_Y");
    warpPoints[1].x = panel.getValueI("TR_X");
    warpPoints[1].y = panel.getValueI("TR_Y");
    warpPoints[2].x = panel.getValueI("BR_X");
    warpPoints[2].y = panel.getValueI("BR_Y");
    warpPoints[3].x = panel.getValueI("BL_X");
    warpPoints[3].y = panel.getValueI("BL_Y");
    //ink values
    inkRefund       =panel.getValueI("INKREFUND");
    //color trakcing vals
    hue[0]  =   panel.getValueI("RH");
    sat[0]  =   panel.getValueI("RS");
    val[0]  =   panel.getValueI("RV");
    hue[1]  =   panel.getValueI("GH");
    sat[1]  =   panel.getValueI("GS");
    val[1]  =   panel.getValueI("GV");
    hue[2]  =   panel.getValueI("BH");
    sat[2]  =   panel.getValueI("BS");
    val[2]  =   panel.getValueI("BV");
    
    updateVideo(); //check on all of the video info
    
    //check if there is any reason to pause the game
    if (playerPause || noPath || tooMuchInk || changePause || !showGame || !gameStarted || waveComplete || takePictureTimer>=0 || calibration.phase!="Game")
        paused=true;
    else
        paused=false;
    
    //tick down the picture timer
    takePictureTimer--;
    //keep showing the game if we are just in the delay point
    if (takePictureTimer>takePictureTime)   showGame=true;
    //keep the screen blank if we're getting ready to tkae a pic
    if (takePictureTimer>=0 && takePictureTimer<=takePictureTime)    showGame=false;
    //if it is exactly 0, snap the pic
    if (takePictureTimer==0)    convertDrawingToGame();
    //most of the timer, just show the game
    if (takePictureTimer<0)     showGame=true;
    
    
    int numUpdates=1;
    if (fastForward)    numUpdates=6;
    for (int i=0; i<numUpdates; i++){
        //manage the current wave
        if (curWave>=0 && !wavesDone){
            waves[curWave].update(paused, fastForward);
            if (waves[curWave].readyForNextFoe)
                spawnFoe(waves[curWave].getNextFoe(),waves[curWave].level);
            
            //if this wave is done, and all foes are dead or offscreen, we can start the next wave if the player is still alive
            if (waves[curWave].done && foes.size()==0 && health>0 && !waveComplete)
                endWave();
        }
        
        //update Foes
        bool allFoesHavePath=true;  //assume that all foes can reach the end
        for (int i=foes.size()-1; i>=0; i--){
            foes[i]->update();
            
            if (!foes[i]->pathFound) allFoesHavePath=false;
            
            //remove it if it reached the end
            if (foes[i]->reachedTheEnd){
                takeDamage(foes[i]->damageToPlayer);   //player takes damage
                killFoe(i);
            }
            //remove it if it is dead
            else if (foes[i]->dead){
                //spawn ink particles
                for (int p=0; p<foes[i]->inkVal;p++){
                    particle newInkParticle;
                    newInkParticle.setInitialCondition(foes[i]->p.pos.x,foes[i]->p.pos.y,ofRandom(-5,5),ofRandom(-5,5));
                    inkParticles.push_back(newInkParticle);
                }
                killFoe(i);
            }
        }
        
        //if the game was paused because a foes didn't have a path, unpause if the way is clear now
//        if (allFoesHavePath && noPath){
//            noPath=false;
//        }
        
        //update the towers
        for (int i=0; i<towers.size(); i++){
            towers[i]->update();
            
            //if this tower is ready to shoot and the player isn't dead, check if there is a foe within range
            if (towers[i]->readyToShoot && health>0){
                
                float closestDist=10000000;
                int closestID=-1;
                for (int k=0; k<foes.size(); k++){
                    float distance=towers[i]->pos.distance(foes[k]->p.pos);
                    if ( distance < towers[i]->range +towers[i]->rangePadding && distance<closestDist){
                        
                        //red can only target foes not immune to red
                        if (towers[i]->type=="red" && foes[k]->type!="immune_red"){
                            closestDist=distance;
                            closestID=k;
                        }
                        
                        //green can shoot goddamn anything
                        if (towers[i]->type=="green"){
                            closestDist=distance;
                            closestID=k;
                        }
                        
                        //freeze tower cannot shoot the foe if it is already frozen
                        if (towers[i]->type=="blue" && foes[k]->freezeTimer<=0){
                            closestDist=distance;
                            closestID=k;
                        }
                    }
                }
                
                if (closestID!=-1)
                     towers[i]->fire(foes[closestID]);
                
            }
            
            //if this is a bomb tower, check if it just hit
            if(towers[i]->bombHit){
                towers[i]->bombHit=false;
                
                //find all of the foes in range of the bullet and damage them
                for (int k=0; k<foes.size(); k++){
                    if (towers[i]->bullet.pos.distance(foes[k]->p.pos)<towers[i]->blastRadius){
                        foes[k]->hp-=towers[i]->bulletDamage;
                    }
                }
                
                //add an animation
                BombAnimation newBombAnimation;
                newBombAnimation.setup(towers[i]->bullet.pos.x,towers[i]->bullet.pos.y,towers[i]->blastRadius);
                bombAnimations.push_back(newBombAnimation);
            }
        }
    }
    
    //kil any old bomb animations
    for (int i=bombAnimations.size()-1; i>=0; i--){
        bombAnimations[i].update();
        if (bombAnimations[i].done)
            bombAnimations.erase(bombAnimations.begin()+i);
    }
    
    //update ink particles
    int inkEndX=-175;
    int inkEndY=215;
    for (int i=inkParticles.size()-1; i>=0; i--){
        //reset the particle
        inkParticles[i].resetForce();
        //atract the controler to the next node
        inkParticles[i].addAttractionForce(inkEndX, inkEndY, 10000, 0.4);
        //dampen and update the particle
        inkParticles[i].addDampingForce();
        inkParticles[i].update();
        
        //check if it reached the end
        if (ofDist(inkParticles[i].pos.x, inkParticles[i].pos.y, inkEndX, inkEndY)<20){
            //give the player ink
            totalInk++;
            //kill the particle
            inkParticles.erase(inkParticles.begin()+i);
        }
    }
    
    //update explosions and puffs
    for (int i=explosions.size()-1; i>=0; i--){
        explosions[i].update();
        
        if (explosions[i].killMe)
            explosions.erase(explosions.begin()+i);
    }
    
    //normally we'd only check the ink levels when a picture is taken, but it is useful to have the data constatly when on the ink phase of calibration
    //This is redundant, copy/pasted code
    if (calibration.phase=="Ink"){
        //check how much ink has been used
        inkUsed= 0;  
        
        //check black pixels
        for (int i=0; i<fieldW*fieldH; i++){
            if (wallPixels[i]==0) inkUsed+=blackInkValue;
        }
        
        //check towers
        for (int i=0; i<towers.size(); i++){
            if (towers[i]->type=="red") inkUsed+=rInkValue*towers[i]->size;
            if (towers[i]->type=="green") inkUsed+=gInkValue*towers[i]->size;
            if (towers[i]->type=="blue") inkUsed+=bInkValue*towers[i]->size;
        }
        
        //let calibration know how much was used
        calibration.inkUsedBeforeRefund=inkUsed;
        
        //factor in the refund
        inkUsed-=inkRefund;
        //make sure ink used is not negative
        inkUsed=MAX(0,inkUsed);
        
        //check if they used more ink than they have
        if (inkUsed>totalInk){
            tooMuchInk=true;
            return; //don't need to bother checking anything else
        }else if (tooMuchInk){  //if they just fixed using too much ink, unpause the game
            tooMuchInk=false;
        }
    }
}

//--------------------------------------------------------------
void testApp::updateVideo(){
    video.update();
	
	if (video.isFrameNew()){
		colorImg.setFromPixels(video.getPixels(), video.width, video.height);
        
        //get end points for warping the images
        ofPoint endPoints[4];
        endPoints[0].set(0,0);
        endPoints[1].set(colorImgMedium.width,0);
        endPoints[2].set(colorImgMedium.width, colorImgMedium.height);
        endPoints[3].set(0,colorImgMedium.height);
        
        //expand the differencing image to include space on the right of the playing field
        float paddingPrc=0.07;
        ofPoint widePoints[4];
        for (int i=0; i<4; i++)
            widePoints[i]=warpPoints[i];
        widePoints[1].x += (widePoints[1].x-widePoints[0].x)*paddingPrc;
        widePoints[2].x += (widePoints[2].x-widePoints[3].x)*paddingPrc;
        //make sure thes poitns don't go out of bounds
        widePoints[1].x = MIN(colorImg.width,widePoints[1].x);
        widePoints[2].x = MIN(colorImg.width,widePoints[2].x);
        
        //check to see if there was motion in front of the camera
		//set the change video to be the greyscale verison of the incoming color feed
		changeImg=colorImg;
        //warp them into the small(er) image
        changeImgSmall.warpIntoMe(changeImg,widePoints,endPoints);
        
        //save the background if the flag is up
        if (saveChangeBackground){
            changeBackground=changeImgSmall;
            saveChangeBackground=false;  //turn the flag back off
        }
        //compare current value to the background
        changeBackgroundDiff.absDiff(changeBackground,changeImgSmall);
        //test for significant difference between current depth info and what has been saved as the background
        unsigned char *	changePixels;
        changePixels=changeBackgroundDiff.getPixels();
        
        //ignore anything inside the maze by painting it black
        float scaleVal=colorImgMedium.width/fieldW;
        for (int x=0; x<fieldW*scaleVal; x++){
            for (int y=0; y<fieldH*scaleVal; y++){
                //this is using some MAGIC NUMBERS at the moment. Might want to try and fix that
                if ( x>mazeLeft*scaleVal*(1-paddingPrc+0.01) && x<mazeRight*scaleVal*(1-paddingPrc+0.01) && y>mazeTop*scaleVal && y<mazeBottom*scaleVal){
                    int pos=y*(fieldW*scaleVal)+x;
                    changePixels[pos]=0;
                }
                
                //black out the left entrance and right exit
                int entranceY= (mazeBottom-mazeTop)/2+11;
                int entranceH=6;
                if (y>(entranceY-entranceH)*scaleVal && y<(entranceY+entranceH)*scaleVal){
                    int pos=y*(fieldW*scaleVal)+x;
                    changePixels[pos]=0;
                }
                
                //black out the left entrance and right exit
                int entranceX= (mazeRight-mazeLeft)/2+11;
                int entranceW=6;
                if (x>(entranceX-entranceW)*scaleVal*(1-paddingPrc+0.01) && x<(entranceX+entranceW)*scaleVal*(1-paddingPrc+0.01)){
                    int pos=y*(fieldW*scaleVal)+x;
                    changePixels[pos]=0;
                }
                
            }
        }
        
        changeBackgroundDiff.flagImageChanged();    //let the image know we messed with the pixels
        
        int totalDiff=0;
        for (int i=0; i<colorImgMedium.width*colorImgMedium.height; i++){
            //if the pixel is white, add it
            if (changePixels[i]>80)
                totalDiff++;
        }
        if (totalDiff>maxChangeDiff){
            changePause=true;
            takePictureTimer=-1;    //make sure the timer doesn't go off while we're drawing
        }else if(changePause){
            //just went from paused to unpaused. Time to take a pic
            changePause=false;
            takePictureTimer=takePictureTime+takePictureDelay;
        }
        
        
        //don't do image processing if we aren't taking a picture
        //we always want to see the reult if we are doing certain steps of calibration, though
        if (takePictureTimer>0 || calibration.phase=="Ink" || calibration.phase=="Screen" || calibration.phase=="Colors"){
            //colorImg.setFromPixels(video.getPixels(), video.width, video.height);
            //warp into the small image based on the warp points
            colorImgMedium.warpIntoMe(colorImg, warpPoints, endPoints);
            greyImg=colorImgMedium;
            
            
            hsvImg = colorImgMedium;
            hsvImg.convertRgbToHsv();
            
            hsvImg.convertToGrayscalePlanarImages(hueImg, satImg, briImg);
            
            unsigned char * colorHsvPixels = hsvImg.getPixels();
            
            for (int i = 0; i < colorImgMedium.width*colorImgMedium.height*3; i+=3){ //threshold!
                
                for (int k=0; k<3; k++){
                    // since hue is cyclical:
                    int hueDiff = colorHsvPixels[i] - hue[k];
                    if (hueDiff < -127) hueDiff += 255;
                    if (hueDiff > 127) hueDiff -= 255;
                    
                    if ( (fabs(hueDiff) < hueRange[k]) &&
                        (colorHsvPixels[i+1] > (sat[k] - satRange[k]) && colorHsvPixels[i+1] < (sat[k] + satRange[k])) &&
                        (colorHsvPixels[i+2] > (val[k] - valRange[k]) && colorHsvPixels[i+2] < (val[k] + valRange[k]))){
                        colorPixels[k][i/3] = 255;
                    } else {
                        colorPixels[k][i/3] = 0;
                    }
                }
                
            }
            
            for (int i=0; i<3; i++){
                colorImgs[i].setFromPixels(colorPixels[i], colorImgMedium.width, colorImgMedium.height);
            }
            
            //threshold the sat image to get the black image (used for the walls) IS WHAT I USED TO DO
            //blackImg.scaleIntoMe(satImg);
            //blackImg.threshold(blackThreshold,true);
            
            //theshold the greyscale image
            blackImg.scaleIntoMe(greyImg);
            blackImg.threshold(blackThreshold,false);
		}
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    //cover the computer screen for the calibration screen
    ofSetColor(0);
    ofFill();
    ofRect(0,0,ofGetScreenWidth(),ofGetScreenHeight());
    
    //draw the calibration screen
    ofPushMatrix();
    ofScale(screenScale,screenScale);
    calibration.draw();
    ofPopMatrix();
    
    ofEnableAlphaBlending();
    
    ofPushMatrix();
    ofTranslate(projX, projY);
    ofScale(projScale, projScale);
    //show the border
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(255);
    borderPics[numEntrances-1].draw(0,0,fieldW*fieldScale,fieldH*fieldScale);
    //show the game if not taking a picture or calibrating a part that requires not showing the game
    if (showGame && calibration.showGame)
        drawGame();
    if (!showRect)
        drawPlayerInfo();   //show player stats that live outside of the game area
    ofPopMatrix();
    
    //planning rect
    if (showRect){
        ofSetColor(0);
        ofFill();
        ofPushMatrix();
        ofTranslate(projX,projY);
        ofScale(projScale,projScale);
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofRect(0,0,fieldW*fieldScale,fieldH*fieldScale);
        
        ofPopMatrix();
    }
    
    ofDisableAlphaBlending();
    //set the rect mode back
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    //check if we are saving a board picture
    if (readyToDrawBoardPicture){
        readyToDrawBoardPicture=false;  //turn the flag off
        ofImage screenGrab; //to hold the screen shot
        ofSetColor(255);
        boardImg.draw(0,0); //draw it
        //grab it
        screenGrab.grabScreen(0, 0, boardImg.width, boardImg.height);   
        //and save it
        string date=ofToString(ofGetMonth())+"-"+ofToString(ofGetDay())+"-"+ofToString(ofGetHours())+"-"+ofToString(ofGetMinutes())+"-"+ofToString(ofGetSeconds());
        screenGrab.saveImage("pics/board"+date+".png");
        
    }
    
    
    
    ofSetLineWidth(1);
    //panel.draw();
}

//--------------------------------------------------------------
void testApp::drawGame(){
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    if(showAllInfo){
        //go through the images and draw them all out to the screen
        for (int x=0; x<fieldW; x++){
            for (int y=0; y<fieldH; y++){
                int pos=y*fieldW+x;
                if (wallPixels[pos]==0){
                    ofSetColor(0);
                    ofRect(x*fieldScale, y*fieldScale, fieldScale, fieldScale);
                }
            }
        }
        
        //show the vector field if we're viewing all data
        ofSetColor(0,130,130, 200);
        VF.draw();
    }
    
    //show the towers
    for (int i=0; i<towers.size(); i++)
        towers[i]->draw();
    
    //show the foes
    for (int i=0; i<foes.size(); i++){
        if (showAllInfo)
            foes[i]->drawDebug();
        foes[i]->draw();
    }
    
    //draw the bomb animations if there are any
    ofFill();
    for (int i=0; i<bombAnimations.size(); i++)
         bombAnimations[i].draw();
    
    //draw explosions and puffs
    for (int i=0; i<explosions.size(); i++)
        explosions[i].draw();
    
    //draw ink particles if there are any
    ofSetColor(150);
    for (int i=0; i<inkParticles.size(); i++)
        inkParticles[i].draw();
    
    //let the player no if there is no path
    ofFill();
    int messageX=615;
    int messageY=-50;
    int thisTextX;
    if (noPath){
        ofSetColor(0,0,0);
        thisTextX=messageX-infoFont.stringWidth("HEY ASS BUTT, THERE IS NO PATH")/2;
        infoFont.drawString("HEY ASS BUTT, THERE IS NO PATH",thisTextX,messageY);
    }
    //let the player know if they used too much ink
    if (tooMuchInk){
        ofSetColor(255,0,0);
        thisTextX=messageX-infoFont.stringWidth("HEY CRAPLORD, YOU ARE OUT OF INK")/2;
         infoFont.drawString("HEY CRAPLORD, YOU ARE OUT OF INK",thisTextX,messageY);
    }
    //let the player know if they are dead
    if (health<=0){
        ofSetColor(255,0,0);
        if (ofGetFrameNum()/4%2==0) ofSetColor(0);
        thisTextX=messageX-infoFont.stringWidth("NICE TRY. TOO BAD YOU DIED")/2;
        infoFont.drawString("NICE TRY. TOO BAD YOU DIED",thisTextX,messageY);
    }
    
    //check if we should be showing the wave complete animation
    if (waveComplete)
        drawWaveCompleteAnimation();
    
    //draw red over the game if the player was just hit
    if (damageFlashTimer-- >0){
        ofSetColor(255, 0, 0, 200);
        ofSetRectMode(OF_RECTMODE_CORNER);
        float padding=200;
        ofRect(padding,padding,fieldW*fieldScale-padding*2,fieldH*fieldScale-padding*2);
    }
    
}

//--------------------------------------------------------------
void testApp::drawWaveCompleteAnimation(){
    //get the amount of time the animation has played
    float curTime=ofGetElapsedTimef()-waveAnimationStart;
    
    ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255));
    infoFontHuge.drawString("WAVE COMPLETE!",63,316);
    
    if (wavesDone)
        infoFontHuge.drawString("GAME COMPLETE!",63,416);
    
    
    //if time is up, return to the game
    if (curTime>waveAnimationTime){
        startNextWave();
    }
}

//--------------------------------------------------------------
void testApp::drawPlayerInfo(){
    //draw health
    ofSetRectMode(OF_RECTMODE_CENTER);
    float xCenter=(fieldW*fieldScale)/2+25; //slight offset for the openning on the side
    float healthY=910;
    float healthHeight=60;
    float healthWidth=(mazeRight-mazeLeft)*fieldScale;
    
    //draw the bar
    ofFill();
    ofSetColor(224,27,76,200);
    int healthFilLWidth=ofMap(health,0,healthStart,0,healthWidth);
    ofRect(xCenter,healthY,healthFilLWidth,healthHeight);
    
    //draw the border
    ofNoFill();
    ofSetColor(0);
    ofRect(xCenter,healthY,healthWidth,healthHeight);
    
    //ink value guide
    ofFill();
    int guideX=-250;
    int guideY=566;
    int guideCircleSize=25;
    
    ofSetColor(0);
    ofRect(guideX,guideY, 60,15);
    ofSetColor(255,0,0);
    ofCircle(guideX,guideY+guideCircleSize*3,guideCircleSize);
    ofSetColor(0,255,0);
    ofCircle(guideX,guideY+guideCircleSize*6,guideCircleSize);
    ofSetColor(0,0,255);
    ofCircle(guideX,guideY+guideCircleSize*9,guideCircleSize);
    
    //the exact values for this are estimated. Maybe there is a better way of getting this data?
    ofSetColor(0);
    int textYOffset=8;  //just need to bump them down a bit
    int blackVal=blackInkValue*40;    
    infoFontSmall.drawString("= "+ofToString(blackVal), guideX+guideCircleSize+20, guideY+guideCircleSize*0+textYOffset);
    int redVal=(guideCircleSize/fieldScale) * rInkValue * 12;
    infoFontSmall.drawString("= "+ofToString(redVal), guideX+guideCircleSize+20, guideY+guideCircleSize*3+textYOffset);
    int greenVal=(guideCircleSize/fieldScale) * gInkValue * 12;
    infoFontSmall.drawString("= "+ofToString(greenVal), guideX+guideCircleSize+20, guideY+guideCircleSize*6+textYOffset);
    int blueVal=(guideCircleSize/fieldScale) * bInkValue * 12;
    infoFontSmall.drawString("= "+ofToString(blueVal), guideX+guideCircleSize+20, guideY+guideCircleSize*9+textYOffset);
    
    
    //written values
    int thisTextX;
    
    //SHOW INK VALUES
    ofFill();
    ofSetColor(0);
    //make it blink if the player is out if ink
    if (tooMuchInk && ofGetFrameNum()/4%2==0)   ofSetColor(255,0,0);
    int inktextRightX=0;
    int inkTextY=172;
    
    thisTextX=inktextRightX-infoFont.stringWidth("Ink Left:");
    infoFont.drawString("Ink Left:",thisTextX,inkTextY);
    inkTextY+=infoFontBig.getLineHeight();
    
    thisTextX=inktextRightX-infoFontBig.stringWidth(ofToString((int)(totalInk-inkUsed))+"/"+ofToString((int)totalInk));
    infoFontBig.drawString(ofToString((int)(totalInk-inkUsed))+"/"+ofToString((int)totalInk),thisTextX,inkTextY);
    inkTextY+=infoFontBig.getLineHeight();
    
    
    //SHOW WAVE INFO
    int waveTextX=1315;
    int waveTextY=75;
    
    thisTextX=waveTextX-infoFont.stringWidth("Wave #")/2;
    infoFont.drawString("Wave #",thisTextX,waveTextY);
    
    waveTextY+=infoFontHuge.getLineHeight()-60;
    thisTextX=waveTextX-infoFontHuge.stringWidth(ofToString(curWave+1))/2;
    infoFontHuge.drawString(ofToString(curWave+1),thisTextX,waveTextY);
    
    waveTextY+=120;
    thisTextX=waveTextX-infoFont.stringWidth("Invader")/2;
    infoFont.drawString("Invader",thisTextX,waveTextY);
    waveTextY+=infoFont.getLineHeight();
    thisTextX=waveTextX-infoFont.stringWidth("Level:")/2;
    infoFont.drawString("Level:",thisTextX,waveTextY);
    
    waveTextY+=infoFontHuge.getLineHeight()-60;
    thisTextX=waveTextX-infoFontHuge.stringWidth(ofToString(waves[curWave].level))/2;
    infoFontHuge.drawString(ofToString(waves[curWave].level),thisTextX,waveTextY);
    
    waveTextY+=120;
    thisTextX=waveTextX-infoFont.stringWidth("Invaders")/2;
    infoFont.drawString("Invaders",thisTextX,waveTextY);
    waveTextY+=infoFont.getLineHeight();
    thisTextX=waveTextX-infoFont.stringWidth("Left:")/2;
    infoFont.drawString("Left:",thisTextX,waveTextY);
    
    waveTextY+=infoFontHuge.getLineHeight()-60;
    int numLeft=waves[curWave].foes.size()-waves[curWave].nextFoe;
    if (waves[curWave].done)    numLeft=0;
    thisTextX=waveTextX-infoFontBig.stringWidth(ofToString(numLeft))/2;
    infoFontHuge.drawString(ofToString(numLeft),thisTextX,waveTextY);
    
    waveTextY+=150;
    thisTextX=waveTextX-infoFontSmall.stringWidth(waves[curWave].message)/2 +20;
    infoFontSmall.drawString(waves[curWave].message,thisTextX,waveTextY);
    
}

//--------------------------------------------------------------
void testApp::exit() {
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    calibration.keyPressed(key);
    
    switch (key){
        //toggles showing the debug info
        case 'd':
            showAllInfo=!showAllInfo;
            break;
            
            //pause
        case 'p':
            playerPause=!playerPause;
            break;
            
        case ' ':
            saveChangeBackground=true;
            takePictureTimer=takePictureTime;
            gameStarted= true;        //return to the game
            break;
            
//        case '/':
//            saveDepthBackground=true;
//            break;

            
        case 'f':
            fastForward=!fastForward;
            break;
            
            
        //reset game on enter
        case 13:
            reset();
            break;

            
        case 's':
            savingBoardPicture=true;
            break;
            
        case 'v':
            video.videoSettings();
            break;
            
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    calibration.keyReleased(key);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    calibration.mouseMoved(x/screenScale, y/screenScale);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    calibration.mouseDragged(x/screenScale, y/screenScale, button);
    //panel.mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    calibration.mousePressed(x/screenScale, y/screenScale, button);
    //panel.mousePressed(x,y,button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    calibration.mouseReleased(x/screenScale, y/screenScale, button);
    //panel.mouseReleased();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}

//--------------------------------------------------------------
//draws the borders of the maze into the wall pixels and refunds the ink used
void testApp::setMazeBorders(){
    //ignore anything drawn outside of the maze by painting it white
    for (int x=0; x<fieldW; x++){
        for (int y=0; y<fieldH; y++){
            if ( x<mazeLeft || x>mazeRight || y<mazeTop || y>mazeBottom){
                int pos=y*fieldW+x;
                wallPixels[pos]=255;
            }
        }
    }
    
    //keep the hole empty
    int hole=mazeLeft+ (mazeRight-mazeLeft)/2;
    //top and bottom walls
    for (int i=mazeLeft; i<=mazeRight; i++){
        if(i<hole-5 || i>hole+5){
            int topPos=mazeTop*fieldW+i;
            int bottomPos=mazeBottom*fieldW+i;
            wallPixels[topPos]=0;
            wallPixels[bottomPos]=0;
        }
    }
    
    // top entrance way
    for (int i=0; i<mazeTop; i++){
        int leftPos=i*fieldW+(hole-5);
        int rightPos=i*fieldW+(hole+5);
        wallPixels[leftPos]=0;
        wallPixels[rightPos]=0;
    }
    
    //bottom exit
    for (int i=mazeBottom; i<fieldH; i++){
        int leftPos=i*fieldW+(hole-5);
        int rightPos=i*fieldW+(hole+5);
        wallPixels[leftPos]=0;
        wallPixels[rightPos]=0;
    }
    
    
    //left and right walls with opennings in the middle
    int center=mazeTop+ (mazeBottom-mazeTop)/2;
    for (int i=mazeTop; i<=mazeBottom; i++){
        if (i<center-5 || i>center+5){
            int leftPos=i*fieldW+mazeLeft;
            int rightPos=i*fieldW+mazeRight;
            wallPixels[leftPos]=0;
            wallPixels[rightPos]=0;
        }
    }
    
    //left entrance way
    for (int i=0; i<mazeLeft; i++){
        int topPos=(center-5)*fieldW+i;
        int bottomPos=(center+5)*fieldW+i;
        wallPixels[topPos]=0;
        wallPixels[bottomPos]=0;
    }
    
    //right exit
    for (int i=mazeRight; i<fieldW; i++){
        int topPos=(center-5)*fieldW+i;
        int bottomPos=(center+5)*fieldW+i;
        wallPixels[topPos]=0;
        wallPixels[bottomPos]=0;
    }
    
}

//--------------------------------------------------------------
void testApp::convertDrawingToGame(){ 
    //get the walls
    wallImage=blackImg;
    wallPixels=wallImage.getPixels();
    thickenWallImage();
    setMazeBorders();
    
    //pathfinding for the foes
    if (foes.size()>0){
        for (int i=foes.size()-1; i>=0; i--){
            //it would be way better to check each foe's current locaiton against the path made by tempFoe, but it just isn't fucking working.
            foes[i]->findPath();
            
            //pause the game if this foe can't reach the end
            if (!foes[i]->pathFound){
                noPath=true;
                cout<<"NO PATH. GET OUT"<<endl;
                return;
            }
            //you could also, create a temp foe at the end, and check to see if it can make it to the start
            
        }
    }
    
    //if we got this far, there is a path
    noPath=false;
    
    VF.clear();
    //add some repulsion from each wall
    for (int i=0; i<fieldW*fieldH; i++){
        if (wallPixels[i]==0){
            int wallX=i%fieldW;
            int wallY=floor(i/fieldW);
            
            VF.addOutwardCircle(wallX*fieldScale, wallY*fieldScale, 30, 0.3);
        }
    }
    
    //look for blobs to turn into towers
    //set all towers as unfound. If they are not found when checking the blobs, they will be rmeoved
    for (int i=0; i<towers.size(); i++){
        towers[i]->found=false;
    }
    
    //red
    int minArea=20;
    int maxArea=(fieldW*fieldH)/2;
    int maxNumberOfBlobs=25;
    
    //expand the pixels in the images 
    for (int i=0; i<3; i++)
        colorImgs[i].dilate_3x3();    
    
    contourFinder.findContours(colorImgs[0], minArea, maxArea, maxNumberOfBlobs, false);
    checkTowers("red");
    //green
    contourFinder.findContours(colorImgs[1], minArea, maxArea, maxNumberOfBlobs, false);
    checkTowers("green");
    //blue
    contourFinder.findContours(colorImgs[2], minArea, maxArea, maxNumberOfBlobs, false);
    checkTowers("blue");
    
    //find any towers that were not found in the last sweep and kill them
    for (int i=towers.size()-1; i>=0; i--){
        if (!towers[i]->found){
            delete towers[i];
            towers.erase(towers.begin()+i);
        }
    }
   
    //in case the markers fucked with the IR reading, save a new background
    saveChangeBackground=true;
    
    //save these images to the display array for debug purposes
    for (int i=0; i<3; i++)
        colorImgsDisplay[i]=colorImgs[i];
    
    
    //check how much ink has been used
    inkUsed= 0;  
    //check black pixels
    for (int i=0; i<fieldW*fieldH; i++){
        if (wallPixels[i]==0) inkUsed+=blackInkValue;
    }
    //check towers
    for (int i=0; i<towers.size(); i++){
        if (towers[i]->type=="red") inkUsed+=rInkValue*towers[i]->size;
        if (towers[i]->type=="green") inkUsed+=gInkValue*towers[i]->size;
        if (towers[i]->type=="blue") inkUsed+=bInkValue*towers[i]->size;
    }
    //let calibration know how much was used
    calibration.inkUsedBeforeRefund=inkUsed;
    //factor in the refund
    inkUsed-=inkRefund;
    //make sure ink used is not negative
    inkUsed=MAX(0,inkUsed);
    //check if they used more ink than they have
    if (inkUsed>totalInk){
        tooMuchInk=true;
        //return; //don't need to bother checking anything else
    }else if (tooMuchInk){  //if they just fixed using too much ink, unpause the game
        tooMuchInk=false;
    }
    
    //if there is nothing wrong, the game is ready to continue
    //but we should check to see if any towers from the last safe game state were removed
    if (!tooMuchInk && !noPath){
        cout<<"ITS GOOD"<<endl;
        
        //check the current wall image against the last one to see if any big chunks of wall were erased
        vector <int> wallEraseLocations;
        wallDiffImage.absDiff(lastSafeWallImage, wallImage);
        wallDiffImage.erode_3x3();  //try to remove some noise by expanding the black parts of the image
        unsigned char * wallDiffPixels=wallDiffImage.getPixels();
        //go thorugh and see how many pixels that had been black are now white
        int totalDiff=0;
        //int spawnParticleFrequency= (1/blackInkValue)*wallRefund;
        for (int i=0; i<fieldW*fieldH; i++){
            if (wallDiffPixels[i]>128 && wallPixels[i]==255){
                totalDiff++;
                //spawn an ink particle every so often based on the number of pixels checked so far if the game has started
                if (gameStarted){
                    particle newInkParticle;
                    int xPos= (i%fieldW)*fieldScale;
                    int yPos= ( floor(i/fieldW) )*fieldScale;
                    newInkParticle.setInitialCondition( xPos, yPos , ofRandom(-5,5),ofRandom(-5,5));
                    inkParticles.push_back(newInkParticle);
                }
            }
        }
        //remove from their total ink based on the total
        if (gameStarted)
            totalInk-= totalDiff/wallRefund;
        cout<<"total wall difference: "<<totalDiff<<endl;
        cout<<"took Away: "<<totalDiff/wallRefund<<endl;
        
        
        
        //go through the tower data from the last safe state and see if antyhing is missing
        for (int i=0; i<lastSafeTowerSet.size(); i++){
            bool found=false;   //assume the tower will not be found
            
            //checking each tower might be a super innificient way of doing this
            for (int k=0; k<towers.size(); k++){
                if ( lastSafeTowerSet[i].pos.distance(towers[k]->pos)<lastSafeTowerSet[i].size && lastSafeTowerSet[i].type==towers[k]->type){
                    found=true;
                    break;
                }
            }
            
            if (!found){
                cout<<"you erased the tower at "<<lastSafeTowerSet[i].pos.x<<" , "<<lastSafeTowerSet[i].pos.y<<endl;
                
                //figure out how much ink that tower was worth
                float inkValue;
                if (lastSafeTowerSet[i].type=="red") inkValue=rInkValue*lastSafeTowerSet[i].size;
                if (lastSafeTowerSet[i].type=="green") inkValue=gInkValue*lastSafeTowerSet[i].size;
                if (lastSafeTowerSet[i].type=="blue") inkValue=bInkValue*lastSafeTowerSet[i].size;
                
                //remove that ink from the player's reserve if the game has been started
                if (gameStarted){
                    totalInk-=inkValue;
                    //and spawn ink particles equal to the refund they should get
                    for (int r=0; r<inkValue*towerRefund; r++){
                        particle newInkParticle;
                        newInkParticle.setInitialCondition(lastSafeTowerSet[i].pos.x,lastSafeTowerSet[i].pos.y,ofRandom(-5,5),ofRandom(-5,5));
                        inkParticles.push_back(newInkParticle);
                    }
                }
                
            }
            
            
        }
        
        //save the current wall image
        lastSafeWallImage=wallImage;
        
        //save all of the current tower info to be checked next time
        lastSafeTowerSet.clear();
        for (int i=0; i<towers.size(); i++){
            TowerInfo newInfo;
            newInfo.pos=towers[i]->pos;
            newInfo.size=towers[i]->size;
            newInfo.type=towers[i]->type;
            lastSafeTowerSet.push_back(newInfo);
        }
    }
    else{
        cout<<"NO GOOD BAD BAD"<<endl;
        if (tooMuchInk)    cout<<"TOO MUCH INK"<<endl;
        if (noPath)        cout<<"NO PATH"<<endl;
    }
}

//--------------------------------------------------------------
//checks the contour finder for blobs and updates the towers based on them
void testApp::checkTowers(string type){
    //if there is a blob inside of another blob, then it was not a full circle and should not be considerred
    vector <int> skip;
    float minDist=5;
    
    //JUST USE the holes boolean in the blog. JESUS
    for (int i = 0; i < contourFinder.nBlobs; i++){
        for (int k=0; k<i; k++){
            if (ofDist(contourFinder.blobs[i].centroid.x,contourFinder.blobs[i].centroid.y,
                       contourFinder.blobs[k].centroid.x,contourFinder.blobs[k].centroid.y)<minDist){
                skip.push_back(i);
                skip.push_back(k);
            }
        }
    }
    
    for (int i = 0; i < contourFinder.nBlobs; i++){
        //check if this was one of the blobs with holes. Skip it if it was
        bool skipMe=false;
        for (int k=0; k<skip.size(); k++){
            if (i==skip[k]) skipMe=true;
        }
        
        //find the radius
        float size=sqrt( contourFinder.blobs[i].area/PI )/2;    //diviing by 2 because the image is twice the size of the field
        
        //make sure the blob is at least pretty close to being a circle
        //check compacntess of the blob. a value of 1 would be a perfect circle. Higher values are less compact
        float compactness = (float)((contourFinder.blobs[i].length*contourFinder.blobs[i].length/contourFinder.blobs[i].area)/FOUR_PI);
        if (compactness>maxCompactness) skipMe=true;
        
        //if it passed all those tests, try to make a tower for the blob
        if (!skipMe){
            //check if there is already a tower in this spot
            bool towerHere=false;
            
            for (int k=0; k<towers.size(); k++){
                if ( ofDist(towers[k]->pos.x,towers[k]->pos.y, contourFinder.blobs[i].centroid.x*fieldScale,contourFinder.blobs[i].centroid.y*fieldScale)<size*fieldScale &&
                    towers[k]->type==type){
                    //there is a tower here
                    towerHere=true;
                    towers[k]->found=true;
                    
                    //was the tower built up? adjust its size and center position
                    //the image is twice the size of the field, so we need to cut the values in half before scalling them up to game size
                    towers[k]->setNewPos(contourFinder.blobs[i].centroid.x*fieldScale*0.5, contourFinder.blobs[i].centroid.y*fieldScale*0.5, size*fieldScale);
                }
            }
            
            //if there is no tower currently in this spot, create one
            if (!towerHere){
                if (type=="red"){
                    HitTower * newTower=new HitTower();
                    newTower->setup(contourFinder.blobs[i].centroid.x*fieldScale*0.5, contourFinder.blobs[i].centroid.y*fieldScale*0.5, size*fieldScale, ++towerID);
                    newTower->showAllInfo=&showAllInfo;
                    newTower->paused=&paused;
                    towers.push_back(newTower);
                }
                if (type=="green"){
                    BombTower * newTower=new BombTower();
                    newTower->setup(contourFinder.blobs[i].centroid.x*fieldScale*0.5, contourFinder.blobs[i].centroid.y*fieldScale*0.5, size*fieldScale, ++towerID);
                    newTower->showAllInfo=&showAllInfo;
                    newTower->paused=&paused;
                    towers.push_back(newTower);
                }
                if (type=="blue"){
                    FreezeTower * newTower=new FreezeTower();
                    newTower->setup(contourFinder.blobs[i].centroid.x*fieldScale*0.5, contourFinder.blobs[i].centroid.y*fieldScale*0.5, size*fieldScale, ++towerID);
                    newTower->showAllInfo=&showAllInfo;
                    newTower->paused=&paused;
                    towers.push_back(newTower);
                }
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::spawnFoe(string name, int level){ 
    if (name=="fast"){
        FastFoe * newFoe=new FastFoe;
        newFoe->setPics(fastFoePic[0], fastFoePic[1]);
        foes.push_back(newFoe);
    }
    else if (name=="stealth"){
        StealthFoe * newFoe=new StealthFoe;
        newFoe->setPics(stealthFoePic[0], stealthFoePic[1]);
        foes.push_back(newFoe);
    }
    else if (name=="immune_red"){
        ImmuneRedFoe * newFoe=new ImmuneRedFoe;
        newFoe->setPics(immuneRedFoePic[0], immuneRedFoePic[1]);
        foes.push_back(newFoe);
    }
    else if (name=="heavy"){
        HeavyFoe * newFoe=new HeavyFoe;
        newFoe->setPics(heavyFoePic[0], heavyFoePic[1]);
        foes.push_back(newFoe);
    }
    else {  //assume anything that didn't ahve one of the above names is a normal foe
        NormFoe * newFoe=new NormFoe;
        newFoe->setPics(normFoePic[0], normFoePic[1]);
        //add it to the vector
        foes.push_back(newFoe);
    }
    
    //give the foe all of the info it needs
    int entrance=nextEntrance;
    if (++nextEntrance >= numEntrances) nextEntrance=0;
    foes[foes.size()-1]->setup(&VF, startX[entrance], startY[entrance], goalX[entrance], goalY[entrance], fieldScale, fieldW, fieldH,level);
    foes[foes.size()-1]->wallPixels=wallPixels;
    foes[foes.size()-1]->showAllInfo=&showAllInfo;
    foes[foes.size()-1]->paused=&paused;
    foes[foes.size()-1]->findPath();
    
    
    //if there is no path for this guy, pause the game
    if (!foes[foes.size()-1]->pathFound){
        noPath=true;
    }
}

//--------------------------------------------------------------
void testApp::killFoe(int num){
    //spawn an explosion
    Explosion newExplosion;
    newExplosion.setup(foes[num]->p.pos, &explosionPic);
    explosions.push_back(newExplosion);
    
    //go through and find any towers targetting this foe and remove the target
    for (int i=0; i<towers.size(); i++){
        if (towers[i]->target==foes[num]){
            towers[i]->target=NULL;
        }
    }
    
    delete foes[num]; //dealocate the meory
    foes.erase(foes.begin()+num);
}

//--------------------------------------------------------------
void testApp::takeDamage(int damage){
    //show red for a second if the player is still in the game
    if (health>0)   damageFlashTimer=3; 
    
    health-=damage;
    health=MAX(0,health);
    
    //check if the player is dead
    if (health==0){
        //gray out all towers
        for (int i=0; i<towers.size(); i++)
            towers[i]->playerDead=true;
    }
}

//--------------------------------------------------------------
//takes the pixels in the wall image and adds a black pixel next to each black pixel
void testApp::thickenWallImage(){
    
    vector<int> pixelsToAdd;
    
    //starting at 1 and ghoing to length-2 so that there is a slight buffer on the edges
    for (int x=1; x<fieldW-2; x++){
        for (int y=1; y<fieldH-2; y++){
            int pos=x*fieldW+y;
            if (wallPixels[pos]==0){
                int top=x*fieldW+(y-1);
                int bottom=x*fieldW+(y+1);
                int left=(x-1)*fieldW+y;
                int right=(x+1)*fieldW+y;
                
                if (wallPixels[top]==255)   pixelsToAdd.push_back(top);
                if (wallPixels[bottom]==255)   pixelsToAdd.push_back(bottom);
                if (wallPixels[left]==255)   pixelsToAdd.push_back(left);
                if (wallPixels[right]==255)   pixelsToAdd.push_back(right);
            }
        }
    }
    
    //actualy darken those pixels
    for (int i=0; i<pixelsToAdd.size(); i++)
        wallPixels[pixelsToAdd[i]]=0;

}

//--------------------------------------------------------------
void testApp::startNextWave(){
    waveComplete=false;
    curWave++;
    if (curWave<waves.size()){
        waves[curWave].start();
    }else{
        curWave=waves.size()-1;
        wavesDone=true;
        endWave();  //show the game complete message
    }
    
    //check if it is time to increase the number of entrances starting with the 3rd wave
    if (curWave>=3)
        numEntrances=2;
}

//--------------------------------------------------------------
void testApp::endWave(){
    waveComplete=true;
    waveAnimationStart=ofGetElapsedTimef();
}

//--------------------------------------------------------------
float testApp::getInkFromWaves(int num){
    float inkSoFar=startInk;
    
    int inkVal=5;   //if enemy ink value change, this needs to as well
    //and if any enemies have a different value from each other, this whole thing needs to be rewritten
    
    for (int i=0; i<num; i++){
        inkSoFar+=waves[i].foes.size()*inkVal;
    }
    
    return (inkSoFar);
    
}





