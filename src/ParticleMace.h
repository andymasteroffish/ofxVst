//Hello future humans. I'm Andy Wallace and I made this nonsense.

#pragma once

#include "ofMain.h"
//#include "ofxiPhone.h"
//#include "ofxiPhoneExtras.h"

#include "ofxXmlSettings.h"

#include "ofxShapeBatchRenderer.h"

#include "BasicInfo.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "MissionManager.h"

#include "particle.h"
#include "WeaponParticle.h"
#include "spring.h"
#include "FontDraw.h"

#include "Border.h"
#include "BlackHole.h"

#include "WayPoint.h"
#include "FrozenText.h"

#include "Player.h"
#include "Rock.h"
#include "Fizzle.h"
#include "FoeShatter.h"

#include "NormFoe.h"
#include "SpiralFoe.h"
#include "DummyFoe.h"
#include "JitterFoe.h"
#include "BaronFoe.h"
#include "SnitchFoe.h"
#include "CoopRegen.h"

#include "Tutorial.h"
#include "CreditsManager.h"

#include "CustomizeMenu.h"
#include "FrontMenu.h"

#include "EndGameManager.h"

#include "HighScoreEntryScreen.h"
#include "HighScoreDisplay.h"

#include "ArcadeHighScoreManager.h"
#include "ArcadeAttractMode.h"

#include "StatsManager.h"
#include "StatsScreen.h"

#include "OptionsMenu.h"

#include "AchievementManager.h"

#include "Slider.h"

#include "DeathKnightMissionComponent.h"
#include "SpringEffectMissionComponent.h"


//the internet told me to add , public ofxiPhoneExternalDisplay
class ParticleMace {
	
public:
    void setStatsWrapperInitialized(bool _statsWrapperInitialized);
	void setup(string _dataPath, bool _usingIOS, string _deviceName);
    void setGameWidth(int _gameWidth);
    void setColorBlind(bool colorBlindOn);
	void update();
    
	void draw();
    void drawNoiseField();
    void drawNoiseFieldNoSprite();
    void drawNoiseFieldImage();
    void drawBottomControl();
    void setControlWheelCenter();
    void drawScorePC();
    void drawMouseControl();
    void drawDifficultySelect();
    void drawGameOver();
    void drawPauseButton(int x, int y);
    void drawMuteButton(int x, int y, bool muteIsOn);
    void drawGamePadButton(int x, int y, BUTTON_TYPE button, int alpha, float scale=1);
    void drawMultikillTimer();
    float getCurMultikillTimeBonus();
    void drawLaunchWarning();
    
	void exit();
	
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    
    void changeDifficulty(int dir, int oldDifficulty);
    
	void lostFocus();
	void gotFocus();
	void gotMemoryWarning();
	void deviceOrientationChanged(int newOrientation);
    
    void scroll(float x, float y);
    void movePlayer(int touchX, int touchY, int playerID=0);
    void movePlayerGamePad(float padX, float padY, int playerID=0);
    void movePlayerMouse(int x, int y, int playerID=0);
    //void movePlayerArrows(float angle, bool accelerate, bool reverse, int playerID=0);
    
    void resetParticles(int playerID, bool shortDist);
	
    void killPlayer(bool tutorialKill, int playerID);
    void killPlayerDuringCredits();
    void killFoe(int i, bool addScore, bool blackHoleKill);
    void killRock(int num, bool spawnKill, int playerID, int wepID);
    void resetGame(bool playSound);
    void returnToMenu(bool playSound);
    void goToOptions(bool playForwardBeep, bool returnToGame);
    void goToShipCustomization(GameState returnState, bool usingGamePad);
    void setPaused(bool isPaused);
    void handleAbort();
    
    void setFoePulseValues();
    
    void openHighScoreSubmitScreen();
    void openHighScoreDisplayScreen(bool returnToGameOver);
    
    void clearAsteroidsNearPlayer(int playerID, int bonusDist);
    
    void startKillEffect(int foeID, int playerID, int weponID, bool isMultiplayerKill);
    void updateKillEffect();
    
    void startEndGame();
    
    void startCredits();
    
    void startArcadeAttractMode();
    
    //some functions for multiplayer
    void coopSpawnRegen();
    void coopRegeneratePlayer(CoopRegen * thisRegen);
    void multiplayerCheckWeapons(int playerID);
    void multiplayerKillPlayer(int playerID);
    void multiplayerSetPlayerStartPos(int playerID, bool moveInstantly);
    void multiplayerUpdate();
    void deathmatchUpdate(int playersAlvie, int highScorelayer, int curHighScore);
    void multiplayerJoin(int playerID);
    void handleMultiplayerSettings(int playerID, int xDir, int yDir, bool pressedX, bool pressedStart, bool pressedBack);
    void multiplayerStart();
    void multiplayerStartSetupScreen(bool isDeathmatch, bool resetAllPlayers, bool playBeep);
    void multiplayerStartLevelSelectScreen();
    void multiplayerDrawSetupScreen();
    void multiplayerDrawSettingsScreen();
    void multiplayerDrawLevelSelectScreen();
    void multiplayerDrawScore();
    void multiplayerDrawGameOver();
    void multiplayerDrawStats();
    
    //data functions
    void loadPlayerData();
    void savePlayerData();
    
    void setMessages();
    
    //misison functions
    void setupMissions();
    void setMissionTierTest();
    void setMissionTier1();
    void setMissionTier2();
    void setMissionTier3();
    void setMissionTier4();
    void setMissionTier5();
    void setMissionTier6();
    void setMissionTier7();
    void setMissionTier8();
    void setMissionTier9();
    void setMissionTier10();
    void setMissionTier11();
    void setMissionTier12();
    void setMissionTier13();
    void setMissionTier14();
    void setMissionTier15();
    void setMissionTierFinal();
    
    //util functions
    bool checkInPolygon(vector<ofPoint> p, float x, float y);
    
    //checking to see if this is a test build that has been shut down
    void checkTestBuildKillSwitch();
    void drawKillSwitchText();
    
    
    //checking status of device
    bool usingIOS;
    bool usingGamePad;
    bool usingPS3pad;   //if we are using a game pad, we may want to draw PS3 or xBox buttons
    bool usingPS3padByController[4];
    string deviceName;
    bool retina;    //is this the retina display? Hell yeah sweet ass iphone!
    bool iPad;
    bool iPhone5, iPhone6Plus;
    float retinaAdjust; //generally assuming retina as 1
    
    bool isPublicRelease;
    
    //shapes
    ofxShapeBatchRenderer * shapeRederer;
    
    //game size
    int gameWidth, gameHeight;
    
    //music
    bool wasPlayingMusic;
	
	//dealing with the noise field
    int tileW;
    bool drawBackgroundGrid;    //slower devices can't handle drawing the grid
    int mapNum;	//how many lines of the map to display
    int gridStartX, gridStartY; //we need some big ass ints since it loos ugly when noise fields hit 0
    //the rest of this shit is OLD
    #define GRID_WIDTH  46
    #define GRID_HEIGHT 71
	float vals[GRID_WIDTH][GRID_HEIGHT];    //everything goes fuck-o-go-crazy when I remove this WHY????
    float gridZoom, gridSpeedTime;
    ofVec2f noiseFieldTopLeft, noiseFieldBottomRight;
    
    //image based way of dealing with the noise field
    //unsigned char gridPix[GRID_WIDTH * GRID_HEIGHT];
    unsigned char *	gridPix;
    ofImage gridPic;
	
	//scoring
	float scorePerKill;     //how many points a normal kill nets
    //timing
    float prevTime;
    float deltaTime;
    float timeInRound;
    
    float minTimeForKill;  //don't let foes get killed in the first few frames of the game
    
    //getting bonus points for multiple kills
    int multiKillNum;
    int maxMultiKillNum;
    float multiKillTimer;
    float maxTimeBetweenMultiKills;  //the window in seconds for a multi kill
    float scoreBonusPerMultiKill;
	
    float multikillEndAnimationTime;
    int multikillNumberShowing;
    
    int multikillHasEndedOnce; //for missions (int because that is what missions want)
    
	//moving
	float scrollDistX, scrollDistY;
    ofPoint scrollCenter;
    
    //controlling
    //bool accelerating;
    float accelTouchMinRange;   //any closer than this will not affect the speed
    float accelTouchMaxRange;      //any further than this will not affect sped
    
    //drawing the control panel
    bool showControlGridPic;   //older phones shouldnot do the control panel effect, and should just show the pic instead
    ofImage controlGridPic;
    #define CONTROL_SIZE 23
    int controlGrid[CONTROL_SIZE][CONTROL_SIZE];
    int maxControlGridVal;
    int controlGridFadeVal;
    float controlMaxDistToGlow;
    float minYToCountControlPanel;  //touching the game screen should not trigger it
	int controlTileSize;
    ofPoint lastControlGridTouchPos;
    bool leftyFlipIsOn;
    
    //game manager
    GameManager gm;
    MissionManager mm;
    bool usingMissions;
    ofVec2f startingPoint;  //where player started the game in a given round
    bool missionPause;      //showing missions before the level starts
    float missionPauseTimer;
    
	
    //player
    Player player[MAX_NUM_PLAYERS];
    
    //timing the game to force players to get kills
    float gameStartingTime;
    float gameTimer;
    float curGameTimerBarY;
    
    //shaking the screen on death
    float deathScreenShakeTime;
    float deathScreenShakeTimer;
    
    //multiplayer
    int numPlayers;
    bool usingDeathmatch;
    float multiplayerTimeToStart;
    float multiplayerCountDownTimer;
    float multiplayerEndGameTime;
    float multiplayerEndGameTimer;
    int multiplayerNumControllers;
    vector<string> multiplayerEndGameText;
    int curMultiplayerEndGameText;
    vector<string> multiplayerCongratsText;
    int curMultiplayerCongratsText;
    vector<string> multiplayerStatsNames;
    int curMultiplayerStatsNames;
    string multiplayerNamesNorm[4];
    string multiplayerNamesColorBlind[4];
    string multiplayerNames[4];
    MultiplayerMode multiplayerMode;
    BorderShape multiplayerLevel;
    bool multiplayerUsedRandomLevel;
    int multiplayerStartingValue, multiplayerStartingTime;
    #define NUM_MULTIPLAYER_ASTEROID_LEVELS 4
    int multiplayerAsteroidNumber;
    bool multiplayerGameOver;
    int multiplayerGameOverFrameTimer, multiplayerGameOverFramesBetweenShips;
    int multiplayerGameOverShipLeadInFrames;
    bool multiplayerGameOverDoneShowingShips;
    float multiplayerMenuTimer;
    float multiplayerDeathScreenShakeTime;
    
    
    vector<Fizzle> multiplayerFizzles;
    ofVec2f multiplayerHUDFizzlePos[MAX_NUM_PLAYERS];
    float multiplayerDeathTimer[MAX_NUM_PLAYERS];   //how long it's been since they died
    
    //multiplayer names
    string multiplayerModeNames[NUM_MULTIPLAYER_MODES];
    string multiplayerScoreTitles[NUM_MULTIPLAYER_MODES];
    
    //co-op arcade mode
    bool usingCoop;
    int lastCoopKillPlayerId;
    int numRevivesThisRound;
    
    //weapon particles
    #define NUM_WEP 12
    WeaponParticle * weapons[MAX_NUM_PLAYERS][NUM_WEP];
    float minWepVelToKill;      //how fast the particle must be moving to kill a foe
    int numParticlesForCurWep[NUM_SHIP_TYPES];
    int missionMaxNumParticles; //some missions adjust this
    
    //springs
    spring springs[MAX_NUM_PLAYERS][NUM_WEP];
    
    //foes
    vector <Foe *> foes;
    int numFoesKilled;
    int numFoeTypesKilled[NUM_FOE_TYPES];
    float foePulseColAdjust;
    float foePulseScaleAdjust;
    
    //waypoints
    vector <WayPoint> wayPoints;
    
	//rocks
	vector <Rock *> rocks;
    int maxRockDist;		//how far it can be from the player before being removed
    //only doing complex calculations on rocks near the center of the game
    int rockComplexUpdateLimit; //how far in the vector we got doing the complex updates
	int numRocksSmashed;
    int numRocksObliterated;
    int numFizzles;
    int rockScreenShakeAmount;
    float rockScreenShakeTime, rockScreenShakeTimer;
    
    //some missions create black holes
    BlackHole blackHole;
    
    //in game text
    vector<FrozenText> frozenText;
	//states
    GameState gameState;
    bool paused;
    bool canTapPause;   //finger must go down on the pause button (lol)
    float gameOverTimer;
    float gameOverTime;     //how much time to give before the game shows the menu
    bool tutorialKill;
    bool hasPlayedGameOverSound;
    bool returnToTutorialAfterDeath;
    
    //difficulties
    string difficultyNames[NUM_DIFFICULTIES];
    Difficulty curDifficulty;
    
    //moving the menus
    float menuMoveTime;
    float menuMoveTimer;
    int menuMoveDir;
    int menuMoveOldDifficulty;
    
    //no button mashing through things
    float menuTimer;
    
	//fizzles
	vector <Fizzle> fizzles;
    vector <FoeShatter> foeShatters;
    
    //controlling the camera
    ofVec2f camPos;
    ofVec2f normCamPosTarget;
    ofVec2f camPosTarget;
    float camPosLerp;
    float camZoom;
    float normCamZoom;
    float standardCamZoom;  //only need this if you actually sue a different zoom for coop
    float minCamZoom;
    float camZoomLerp;
    float camZoomTarget;    //mostly used for killEffect
    
    //visual effects for killin' foes
    int killFoeIDNum;
    bool doingKillEffect;
    bool killEffectPause;
    ofVec2f killEffectTargetPoint;// killEffectStartPoint;    //where should the camera be focussing, effects hapenning etc
    float killEffectTimer, killEffectTime;
    float killEffectFreezeTime; //how long to keep the game frozen after the effect is done
    float killEffectCamZoom;
    int killEffectPhase;
    int killEffectWeaponID;
    int killEffectPlayerID;
    ofColor killEffectWeaponCol;
    int killEffectScreenShake;
    bool killEffectIsForMultiplayerKill;
    //less xeno on kill effect when foe is far away
    float curKillEffectLerp;
    float minKillEffectLerp, maxKillEffectLerp;
    float minKillEffectLerpDist, maxKillEffectLerpDist;
    
    
    //game borders
    Border border;
    
    //bottom controls
    int controlBoxHeight;
    ofPoint controlCenter;
    bool controlWheelIsCentered;
    ofRectangle pauseButton;
    //ofImage pauseButtonPic;
    float controlRadius;
    
    //tutorial
    Tutorial tutorial;
    
    //creduts
    CreditsManager credits;
    
    //DifficultySelect screen buttons
    ofRectangle difficultySelectPlayButton;
    ofRectangle difficultySelectIncreaseButton;
    ofRectangle difficultySelectDecreaseButton;
    ofRectangle difficultySelectBackButton;     //for computer version only
    
    //game over screen/high score buttons
    ofRectangle gameOverHighScoreSubmitButton;
    bool gameOverHighScoreSubmitButtonHighlight;
    ofRectangle gameOverHighScoreDisplayButton;
    bool gameOverHighScoreDisplayButtonHighlight;
    
    ofRectangle gameOverBackButton, gameOverTappableBackButton;
	
	//fonts
    FontDraw fontDraw;
    
    //background color
    ofColor backgroundCol;
    ofColor normBackgroundCol[NUM_DIFFICULTIES];
    int maxBackgroundVal;
    ofColor targetBackgorundCol;
    float backgroundColXeno;
    
    //other colors
    bool colorBlindIsOn;
    ofColor textCol;
    float textColTimer;
    float textFadeInTime;
    ofColor playerCol[MAX_NUM_PLAYERS];
    ofColor playerColNorm[MAX_NUM_PLAYERS];
    ofColor playerColColorBlind[MAX_NUM_PLAYERS];
    float deathmatchParticleBrightnessReduction;
    float deathmatchParticleSaturationReduction;
    int numPlayersKilledThisRound;
    ofColor foeCol, foeColNorm, foeColColorBlind;
    ofColor rockCol[NUM_ROCK_COLS];
    ofColor rockColNorm[NUM_ROCK_COLS];
    ofColor rockColColorBlind[NUM_ROCK_COLS];
    
    //audio
    SoundManager SM;
    //ofImage muteButtonPic[2];
//    ofRectangle muteButtonPause;
//    ofRectangle muteButtonDifficultySelect;
    
    //getting to options
    ofRectangle optionsButtonPause;
    bool optionsButtonPauseHighlighted;
    
    //going to stats page form difficulty select on iOS
    ofRectangle   optionsButtonDifficultySelect;
    ofRectangle highScoreButtonDifficultySelect;
    
    //saving scores
    ofxXmlSettings playerData;
    string dataPath;    //locaiton of the file on the iphone
    int highScore[NUM_DIFFICULTIES];
    int highScoreCoop[NUM_DIFFICULTIES];
    
    //player stats
    StatsManager statsManager;
    StatsScreen statsScreen;
    
    //achievements
    AchievementManager achievementManager;
    
    //steam/iOS Game Center stuff
    bool statsWrapperInitialized;
    
    //options menu
    OptionsMenu optionsMenu;
    
    //sending high scores
    HighScoreEntryScreen highScoreEntryScreen;
    bool canSendHighScore;  //only some modes allow sending high scores
    
    //viewing high scores
    HighScoreDisplay highScoreDisplay;
    
    //game over stuff
    //#define NUM_DEATH_MESSAGES 16
    vector<string> deathMessages;//[NUM_DEATH_MESSAGES];
    int curDeathMessage;
    float gameOverMenuButtonH;
//    float gameOverMenuButtonDividingX;
    
    //ship customization screen
    CustomizeMenu CM;
    //bool goToCustomizeMenuOnGameRestart; //for after they unlocked a ship KILL THIS KILL THIS KILL THIS
    
    //front menu
    FrontMenu frontMenu;
    
    //end game
    bool endGameActive;
    bool flyingToEndGame;
    EndGameManager endGameManager;
    int endGameMissionDistance;
    
    //controlling using the mouse
    bool usingMouseControl;
    float mouseControlRange;   //how far from the player the mouse can be before it maxes out
    ofVec2f mouseRelativeToPlayer;
    bool showMouse, isShowingMouse;
    
    //fullscreen
    bool toggleFullScreenFlag;
    bool fullScreenIsOn;
    
    //showing a warning (and legal text?) before the game starts
    bool showingLaunchWarning;
    float launchWarningTime, launchWarningStartFadeTime;
    float launchWarningTimer;
    
    
    //aracde/deathmatch only mode
    bool arcadeCabinetMode, singlePlayerArcadeCabinetMode;
    bool deathmatchOnly;
    int arcadeGamesCount;	//this is probably unnecessary since you made it go back to the menu after every game
    float arcadeTimeBeforeReturningToMenu;
    float arcadeTimer;
    float arcadePreferredWidth; //for shrinking osme menus
	bool freePlay;
	int arcadeCredits;
    
    //conferemnce mode
    bool isConferenceMode;
    
    //in the cabinet, the blue player is moved to spot 2 because that's where people stand, but I need to swap the colors depending on single or multiplayer
    ofColor arcadeBlueCol, arcadePurpleCol;
    
    ArcadeHighScoreManager arcadeHighScoreManager;
    bool goToArcadeHighScoreEntryOnGameOver;
    
    ArcadeAttractMode arcadeAttractMode;
    float arcadeAttractModeTime;    //how long to sit on the menu before going to attract mode
    float arcadeAttractModeTimer;
    
    
    //testing/debug
    float xDist, yDist;
    bool showDebug, debugNoFullScreen;
    bool debugOptionsEnabled;
    bool hideVersionNote;
    bool takeFestivalShots;
    
    //making sure I can kill tester builds of the game remotely
    //YOU MUST ABSOLUTELY REMOVE THIS FROM THE FINAL GAME
    bool testBuildKillSwitchIsOn;
    vector<string> killSwitchText;
    
    float testVal;
    
    
    bool debugSpawnBaron;
    
};

