/***********************
 * Andy Wallace        *
 * copyright 2012      *
 ***********************/


#pragma once

#include "ofMain.h"
#include "tile.h"
#include "ofxOpenCv.h"
#include "vectorField.h"
#include "ofxKinect.h"
#include "ofxControlPanel.h"

#include "Foe.h"
#include "NormFoe.h"
#include "FastFoe.h"
#include "StealthFoe.h"
#include "ImmuneRedFoe.h"
#include "ImmuneBlueFoe.h"
#include "HeavyFoe.h"

#include "Tower.h"
#include "HitTower.h"
#include "FreezeTower.h"
#include "BombTower.h"

#include "BombAnimation.h"

#include "Wave.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void loadFromText();
    void update();
    void updateKinect();
    void draw();
    void drawKinectData();
    void drawGame();
    void drawPlayerInfo();
    void drawWaveCompleteAnimation();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);	
    
    //game functions
    void reset();
    void convertDrawingToGame();    //takes the pixels and reads the game values from them
    void setMazeBorders();
    void thickenWallImage();
    
    void spawnFoe(string name, int level);
    void killFoe(int num);
    void checkTowers(string type);
    
    void takeDamage(int damage);
    
    //delaing with the waves
    void startNextWave();
    void endWave();
    float getInkFromWaves(int num);    //Returns the total ink value of all enemies up to wave num
    void calibrateWarp();
    
    //setting up the kinect
    ofxControlPanel	panel;
	ofxKinect kinect;
    float angle;    //angle of the kinect
    
    //taking a picture of the bard at the end
    ofxCvColorImage			boardImg;
    bool savingBoardPicture;
    bool readyToDrawBoardPicture;
    
    //tracking the depth info
    ofxCvGrayscaleImage		depthImg;
    ofxCvGrayscaleImage     depthImgSmall;      // image of the depth warped to fit the area we're looking at
    ofxCvGrayscaleImage     depthBackground;    // saved verison of what the depth is like when nobody is in the way
    ofxCvGrayscaleImage     depthBackgroundDiff;
    int maxDepthDiff;                           //the amount of difference allowed before the game is paused
    bool saveDepthBackground;                   //flag to use the next depth image as the background
    
    //color tracking images
    ofxCvColorImage			colorImg;
    ofxCvColorImage         colorImgMedium;
    ofxCvColorImage			hsvImg;
	
    ofxCvGrayscaleImage		hueImg;
    ofxCvGrayscaleImage		satImg;
    ofxCvGrayscaleImage		briImg;
    
    ofxCvGrayscaleImage		blackImg;
    ofxCvGrayscaleImage     colorImgs[3];
    unsigned char *			colorPixels[3];
    
    //just some images to display what is the game is looking at right now
    //these are not used by the game and are just for debug info
    ofxCvGrayscaleImage     colorImgsDisplay[3];
	
    //for tracking hue, sat, val;
    int hue[3];
    int sat[3];
    int val[3];
    
    //for figuring out which values are OK
    int hueRange[3];
    int satRange[3];
    int valRange[3];
    int blackThreshold; //thresholding to get the black marker (along with all other colored markers)
    
    float maxCompactness;   //how far the blob can be from being a circle and still be counted
    
    //for warping ine incoming data
    ofPoint warpPoints[4];
    int curWarpPoint;
    
    //positioning the projection
    int projX;
    int projY;
    float projScale;
    
    //size of the openCV image the game data is taken from
    int fieldW;
    int fieldH;
    
    //maze borders in field units
    int mazeTop;
    int mazeBottom;
    int mazeLeft;
    int mazeRight;
    int inkRefund;  //the ink used on the border is given back to the player
    
    //images as lists of pixels showing where the marker is
    ofxCvGrayscaleImage 	wallImage;  
    unsigned char *			wallPixels;
    
    
    //images to display as the boarders
    ofImage borderPics[2];
    
    ofxCvContourFinder 	contourFinder;  //for finding the blobs of color
    
    bool showRect;  //shows the size of the field for the sake of calibrating
    
    //ink ussage - how much each pixel costs
    float blackInkValue;
    float rInkValue;
    float gInkValue;
    float bInkValue;
    
    float fieldScale; //how much to blow up the image
    
    //resons the game might be paused
    bool paused;        //global pause. If any reason is true, this is true
    bool playerPause;   //player pauses the game
    bool noPath;        //becomes true if any foe can't reach the end
    bool tooMuchInk;    //pauses the game when the player has used more ink than they have
    bool depthPause;    //player in frnt of the screen
    bool showGame;      //shows the game
    bool debugShowGame; //shows the game or not regardless of what kinect sees
    bool debugShowKinectVideo;   //take video with the kinect all of the time, not just when taking a picture
    
    bool fastForward;
    
    int takePictureDelay;   //how long after the player leaves to blank the screen
    int takePictureTime;    //how long to leave the screen blank before taking a picture
    int takePictureTimer;   //makes sure the screen stays blank long enough to get a picture
    
    //vector field
	vectorField VF;
    
    //the player
    int score;
    float healthStart;
    float health;
    float startInk;
    float totalInk;
    float inkUsed;
    
    int damageFlashTimer;   //how long to flash red when hit
   
    
    //the foes
    vector <Foe *> foes;
    int startX[2], startY[2];   //multiple entrances
    int goalX[2], goalY[2];
    int numEntrances;           //how many entrance are being used
    
    bool showAllInfo;   //shows all of the bullshit lines and data
    
    //getting ink from them
    vector <particle> inkParticles;
    
    //towers - the point of the damn game
    //needs to be a pointer for polymorphism
    vector <Tower *> towers;
    
    //vector to hold the bomb animations
    vector<BombAnimation> bombAnimations;
    
    //waves of foes
    vector<Wave> waves;
    int curWave;
    bool wavesDone; //game over, man
    bool waveComplete;
    float waveAnimationTime;
    float waveAnimationStart;
    
    
    //fonts
	ofTrueTypeFont infoFontSmall;
    ofTrueTypeFont infoFont;
    ofTrueTypeFont infoFontBig;
    ofTrueTypeFont infoFontHuge;
    
    
};

