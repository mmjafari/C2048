#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "os_generic.h"
#include <GLES3/gl3.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android_native_app_glue.h>
//#include <android/sensor.h>
#include <byteswap.h>
#include <errno.h>
#include <fcntl.h>
#include "CNFGAndroid.h"

#define CNFG_IMPLEMENTATION
#define CNFG3D
#include "CNFG.h"
//#define WEBVIEW_NATIVE_ACTIVITY_IMPLEMENTATION //#include "webview_native_activity.h" ??

unsigned frames = 0;
unsigned long iframeno = 0;

// void AndroidDisplayKeyboard(int pShow);

int lastbuttonx = 0;
int lastbuttony = 0;
int lastmotionx = 0;
int lastmotiony = 0;

// Creating a direction test
int prevx = 0, prevy = 0;
double direc = 0;
int tlm = 0; // time from last motion

//level manager
AAsset * lfile;// = AAssetManager_open( gapp->activity->assetManager, "lvlst", AASSET_MODE_BUFFER );
FILE * clevel;
int level = 0;
long unsigned int lty[4];
int dirad;

int levels[3][4] = {{1,5,5,11},\
                    {2,3,5,11},\
                    {3,4,4,12}};


int gamestate[16][16] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},\
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
const char *num[] = {"","2","4","8","16","32","64","128","256","512","1024","2048","4096","8192","16384","32768","65536", "131072","262144","524288","1048576"};
uint32_t gamecolors[15] = { 0x11111155,\
                            0x11221166,\
                            0x11331177,\
                            0x11551188,\
                            0x11551199,\
                            0x116611aa,\
                            0x117711aa,\
                            0x118811aa,\
                            0x119911aa,\
                            0x11aa11aa,\
                            0x11bb11aa,\
                            0x11cc11aa,\
                            0x11dd11aa,\
                            0x11ee11aa,\
                            0x11ff11aa};

void levelParser(){
  for (int i = 0; i < 16; i++){
    for (int j = 0; j < 16; j++){
      gamestate[i][j] = 0;
    }
  }
  // dummy function till I figure out how to save level data
  lty[0] = levels[level][0];
  lty[1] = levels[level][1];
  lty[2] = levels[level][2];
  lty[3] = levels[level][3];
}

void curLevel(){
  if (clevel == NULL){ clevel = fopen("/data/user/0/org.tererenji.TheGame/files/level","w+"); fprintf(clevel,"1\n"); level = 1;}
  char lin[10];
  while (fgets(lin,sizeof(lin),clevel)){
    sscanf(lin,"%d",&level);
  }
}

void genRan(){
  srand(clock());
  int rx = rand() % lty[1];
  int ry = rand() % lty[2];
  if (gamestate[rx][ry] == 0) {gamestate[rx][ry]++;}
}

void motionCheck(){
  int i, j;
  CNFGColor( 0x000000ff );
  CNFGPenX = 100; CNFGPenY = 300;
  if (direc < M_PI/4 && - M_PI/4 < direc) {
    for (i = lty[1] - 1; i > 0; i--){
      for (j = 0; j < lty[2]; j++){
        if (gamestate[i][j] == 0) {gamestate[i][j] = gamestate[i-1][j]; gamestate[i-1][j] = 0;genRan();}
        else if ( gamestate[i][j] == gamestate[i-1][j] ) {gamestate[i][j]++; gamestate[i-1][j] = 0;genRan();}
      }
    }
    CNFGDrawText("Right", 10);
    goto end;
  }
  else if (direc < 3 * M_PI/4 &&  M_PI/4 < direc ) {
    for (j = lty[2] - 1; j > 0; j--){
      for (i = 0; i < lty[1]; i++){
        if (gamestate[i][j] == 0) {gamestate[i][j] = gamestate[i][j-1]; gamestate[i][j-1] = 0;genRan();}
        else if ( gamestate[i][j] == gamestate[i][j-1] ) {gamestate[i][j]++; gamestate[i][j-1] = 0;genRan();}
      }
    }
    CNFGDrawText("Down", 10);
    goto end;
  }
  else if (direc < - 3 * M_PI/4 || 3 * M_PI/4 < direc) {
    for (i = 0; i < lty[1]-1; i++){
      for (j = 0; j < lty[2]; j++){
        if (gamestate[i][j] == 0) {gamestate[i][j] = gamestate[i+1][j]; gamestate[i+1][j] = 0;genRan();}
        else if ( gamestate[i][j] == gamestate[i+1][j] ) {gamestate[i][j]++; gamestate[i+1][j] = 0;genRan();}
      }
    }
    CNFGDrawText("Left", 10);
    goto end;
  }
  else if (direc < - M_PI/4 && - 3 * M_PI/4 < direc) {
    for (j = 0 ;j < lty[2] - 1; j++){
      for (i = 0; i < lty[1]; i++){
        if (gamestate[i][j] == 0) {gamestate[i][j] = gamestate[i][j+1]; gamestate[i][j+1] = 0;}
        else if ( gamestate[i][j] == gamestate[i][j+1] ) {gamestate[i][j]++; gamestate[i][j+1] = 0;}
      }
    }
    CNFGDrawText("Up", 10);
    goto end;
  }
 end:
  for (i = 0; i < 16; i++){
    for (j = 0; j < 16; j++){
      if (gamestate[i][j] == lty[3]) {
        CNFGPenX = 90; CNFGPenY = 1000;
        CNFGBGColor = 0xbbffbbff;
        CNFGDrawText("Level Done!", 10);
        usleep(100000);
        level++;
        levelParser();
        break;
      }
    }
  }
  usleep(10000);
}


int lastbid = 0;
int lastmask = 0;
int lastkey, lastkeydown;

void resetState(){
  for (int i = 0; i < 16; i++){
    for (int j = 0; j < 16; j++){
      gamestate[i][j] = 0;
    }
  }
}


static int keyboard_up;
uint8_t buttonstate[8];

void HandleKey(int keycode, int bDown){
  lastkey = keycode;
  lastkeydown = bDown;
  if (lastkey == 4) {exit(0);}
}

void HandleButton(int x, int y, int button, int bDown){
  buttonstate[button] = bDown;
  lastbuttonx = x;
  lastbuttony = y;
  lastbid = bDown;
}

void HandleMotion(int x, int y, int mask){
  if ( lastmotionx != 0 && lastmotiony != 0){
    prevx = lastmotionx; prevy = lastmotiony;
    direc /= 8;
    direc += atan2(y-prevy,x-prevx);
    motionCheck();
    lastmotionx = 0; lastmotiony = 0; prevx = 0; prevy = 0;
  }
  lastmotionx = x;
  lastmotiony = y;
  lastmask = mask;
}

#define HMX 162
#define HMY 162

short screeny, screenx;

float Heightmap[HMX*HMY];

extern struct android_app * gapp;

void DrawHeightMap();

int HandleDestroy() {return 0;}

volatile int suspended = 0;

void HandleSuspend(){
  suspended = 1;
}

void HandleResume(){
  suspended = 0;
}

void MakeNotification(){
}


void HandleThisWindowTermination(){
  suspended = 0;
}

void CNFGDrawCircle(int cx, int cy, int radi){
     int j;
     RDPoint *pp = malloc(200*sizeof(pp));
    //#pragma omp parallel for private(j)
    for (j = 0; j < 200; j++){
      pp[j].x = cx + radi*sin(j*M_PI/100);
      pp[j].y = cy + radi*cos(M_PI*j / 100);
    }
    CNFGTackPoly( pp, 200 );
    free(pp);
}

int main(int argc, char **argv){
  int bx,by, boxsize, yoffset;
  lfile = AAssetManager_open( gapp->activity->assetManager, "lvlst", AASSET_MODE_BUFFER );
  clevel = fopen("/data/user/0/org.tererenji.TheGame/files/level", "a+");
  curLevel();
  levelParser();
  srand(time(NULL));
  // example //
  genRan();
  char lvs[3];
  while (1) {
    CNFGBGColor = 0xffffffff;
    CNFGClearFrame();
    CNFGHandleInput();
    CNFGFlushRender();
    CNFGGetDimensions(&screenx, &screeny);
    boxsize = (screenx - 200)/lty[1]; yoffset = (screeny - 200 - lty[2]*boxsize) / 2;
    /*--------------------------------*/
    CNFGColor(0x55995599);
    CNFGTackRectangle(90, yoffset - 90, 90 + 3*boxsize/2, yoffset - 20);
    CNFGPenX = 95; CNFGPenY = yoffset - 85;
    CNFGColor(0x000000ff);
    CNFGDrawText("Reset", 10);
    CNFGPenX = 95 + 2*boxsize; CNFGPenY = yoffset - 90;
    snprintf(&lvs, 2, "%d", level);
    CNFGDrawText(lvs, 10);
    if ( lastmotionx < 90 + 3*boxsize/2 && lastmotionx > 90 && lastmotiony > yoffset-90 && lastmotiony < yoffset - 20){resetState();}
    CNFGPenX = 100; CNFGPenY = 100;
    for (bx = 0; bx < lty[1]; bx++){
      for (by = 0; by < lty[2]; by++){
        CNFGPenX = 120 + bx*boxsize; CNFGPenY = yoffset + 30 + by*boxsize;
        CNFGColor(0x212121f1);
        CNFGDrawText(num[gamestate[bx][by]], 10 - gamestate[bx][by]/2);
        CNFGColor(gamecolors[gamestate[bx][by]]);
        CNFGTackRectangle(90 + bx*boxsize, yoffset -10 + by*boxsize, 95 + (bx+1)*boxsize, yoffset-5+(by+1)*boxsize);
      }
    }
    /*--------------------------------*/
    usleep(12500);
    CNFGSwapBuffers();
  }
  return 0;
}
