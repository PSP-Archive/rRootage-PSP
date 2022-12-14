/*
 * $Id: rr.c 333 2005-12-16 06:41:21Z mrbrown $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */

/**
 * rRootage main routine.
 *
 * @version $Revision: 333 $
 */
#include "SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "rr.h"
#include "screen.h"
#include "vector.h"
#include "foe_mtd.h"
#include "brgmng_mtd.h"
#include "degutil.h"
#include "boss_mtd.h"
#include "ship.h"
#include "laser.h"
#include "frag.h"
#include "shot.h"
#include "background.h"
#include "soundmanager.h"
#include "attractmanager.h"

#ifdef PSP
#include <pspkernel.h>

#if PSP_FW_VERSION >= 371
#undef SDL_main
#endif
PSP_MODULE_INFO("rRootage", PSP_MODULE_USER, 0, 1);
PSP_HEAP_SIZE_KB(-128);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU);

#endif

static int noSound = 0;

// Initialize and load preference.
static void initFirst() {
  time_t timer;
  time(&timer);
  srand(timer);

  loadPreference();
  initBarragemanager();
  initAttractManager();
  if ( !noSound ) initSound();
  initGameStateFirst();
}

// Quit and save preference.
void quitLast() {
  if ( !noSound ) closeSound();
  savePreference();
  closeFoes();
  closeBarragemanager();
  closeSDL();
  SDL_Quit();
  #ifdef PSP
  sceKernelExitGame();
  #else
  exit(1);
  #endif
}

int status;
static int musicEnabled = 1;

void initTitleStage(int stg) {
  initFoes();
  initStageState(stg);
}

void initTitle() {
  int stg;
  status = TITLE;

  stg = initTitleAtr();
  initBoss();
  initShip();
  initLasers();
  initFrags();
  initShots();
  initBackground(0);
  initTitleStage(stg);
  left = -1;
}

void initGame(int stg) {
  int sn;
  status = IN_GAME;

  initBoss();
  initFoes();
  initShip();
  initLasers();
  initFrags();
  initShots();

  initGameState(stg);
  sn = stg%SAME_RANK_STAGE_NUM;
  initBackground(sn);
  if ( sn == SAME_RANK_STAGE_NUM-1 ) {
    playMusic(rand()%(SAME_RANK_STAGE_NUM-1));
  } else {
    playMusic(sn);
  }
  if ( !musicEnabled ) {
    Mix_PauseMusic();
  }
}

void initGameover() {
  status = GAMEOVER;
  initGameoverAtr();
}

static void move() {
  switch ( status ) {
  case TITLE:
    moveTitleMenu();
    moveBoss();
    moveFoes();
    moveBackground();
    break;
  case IN_GAME:
  case STAGE_CLEAR:
    moveShip();
    moveBoss();
    moveLasers();
    moveShots();
    moveFoes();
    moveFrags();
    moveBackground();
    break;
  case GAMEOVER:
    moveGameover();
    moveBoss();
    moveFoes();
    moveFrags();
    moveBackground();
    break;
  case PAUSE:
    movePause();
    break;
  }
  moveScreenShake();
}

static void draw() {
  switch ( status ) {
  case TITLE:
    drawBackground();
    drawBoss();
    drawBulletsWake();
    drawBullets();
    startDrawBoards();
    drawSideBoards();
    drawTitle();
    endDrawBoards();
    break;
  case IN_GAME:
  case STAGE_CLEAR:
    drawBackground();
    drawBoss();
    drawLasers();
    drawShots();
    drawBulletsWake();
    drawFrags();
    drawShip();
    drawBullets();
    startDrawBoards();
    drawSideBoards();
    drawBossState();
    endDrawBoards();
    break;
  case GAMEOVER:
    drawBackground();
    drawBoss();
    drawBulletsWake();
    drawFrags();
    drawBullets();
    startDrawBoards();
    drawSideBoards();
    drawGameover();
    endDrawBoards();
    break;
  case PAUSE:
    drawBackground();
    drawBoss();
    drawLasers();
    drawShots();
    drawBulletsWake();
    drawFrags();
    drawShip();
    drawBullets();
    startDrawBoards();
    drawSideBoards();
    drawBossState();
    drawPause();
    endDrawBoards();
    break;
  }
}

static int accframe = 0;

static void usage(char *argv0) {
  fprintf(stderr, "Usage: %s [-lowres] [-nosound] [-window] [-reverse] [-nowait] [-accframe]\n", argv0);
}

static void parseArgs(int argc, char *argv[]) {
  int i;
  for ( i=1 ; i<argc ; i++ ) {
    if ( strcmp(argv[i], "-lowres") == 0 ) {
      lowres = 1;
    } else if ( strcmp(argv[i], "-nosound") == 0 ) {
      noSound = 1;
    } else if ( strcmp(argv[i], "-window") == 0 ) {
      windowMode = 1;
    } else if ( strcmp(argv[i], "-reverse") == 0 ) {
      buttonReversed = 1;
    }
    /* else if ( (strcmp(argv[i], "-brightness") == 0) && argv[i+1] ) {
      i++;
      brightness = (int)atoi(argv[i]);
      if ( brightness < 0 || brightness > 256 ) {
	brightness = DEFAULT_BRIGHTNESS;
      }
      }*/ 
    else if ( strcmp(argv[i], "-nowait") == 0 ) {
      nowait = 1;
    } else if ( strcmp(argv[i], "-accframe") == 0 ) {
      accframe = 1;
    } else {
      usage(argv[0]);
      exit(1);
    }
  }
}

int interval = INTERVAL_BASE;
int tick = 0;
static int pPrsd = 1;
static int mPrsd = 1;

#ifdef PSP
extern _DisableFPUExceptions();
#endif

int done = 0;

int exitCB(int arg1, int arg2, void *common)
{
	done = 1;
	return 0;
}

int callbackThread(SceSize args, void *argp)
{
	int exit_cbid = sceKernelCreateCallback("Exit Callback", exitCB, NULL);
	if (exit_cbid < 0)
	{
		sceKernelExitGame();
	} 
	else if (sceKernelRegisterExitCallback(exit_cbid) < 0)
	{
		sceKernelExitGame();
	}
	sceKernelSleepThreadCB();
	return 0;
}

int main(int argc, char *argv[]) {
  long prvTickCount = 0;
  int i;
  int btn;
  SDL_Event event;
  long nowTick;
  int frame;

  parseArgs(argc, argv);

#ifdef PSP
  _DisableFPUExceptions();
    int cb_thid = sceKernelCreateThread("Callback Thread", callbackThread, 80, 512, PSP_THREAD_ATTR_USER, NULL);
    if (cb_thid < 0)
    {
        sceKernelExitGame();
    }
    else
    {
        sceKernelStartThread(cb_thid, 0, NULL);
    }
#endif

  initDegutil();
  initSDL();
  initFirst();
  initTitle();

  while ( !done ) {
    SDL_PollEvent(&event);
    keys = SDL_GetKeyState(NULL);
    if ( keys[SDLK_ESCAPE] == SDL_PRESSED || event.type == SDL_QUIT ) done = 1;
    btn = getButtonState();
    if ( keys[SDLK_p] == SDL_PRESSED || (btn & PAD_START) || (btn & PAD_HOME) ) {
      if ( !pPrsd ) {
	if ( status == IN_GAME ) {
	  status = PAUSE;
	} else if ( status == PAUSE && !(btn & PAD_HOME) ) {
	  status = IN_GAME;
	}
      }
      pPrsd = 1;
    } else {
      pPrsd = 0;
    }
    if ( btn & PAD_SELECT ) {
      if ( !mPrsd ) {
	if ( musicEnabled ) {
	  Mix_PauseMusic();
	  musicEnabled = 0;
        } else {
	  Mix_ResumeMusic();
	  musicEnabled = 1;
        }
      }
      mPrsd = 1;
    } else {
      mPrsd = 0;
    }
    if ( (btn & (PAD_LTRIG|PAD_RTRIG)) == (PAD_LTRIG|PAD_RTRIG) ) {
      if ( musicEnabled ) {
	Mix_PauseMusic();
	SDL_Delay(50);
      }
      screenshot("rRootage-");
      if ( musicEnabled ) {
	Mix_ResumeMusic();
      }
    }

    nowTick = SDL_GetTicks();
    frame = (int)(nowTick-prvTickCount) / interval;
    if ( frame <= 0 ) {
      frame = 1;
      SDL_Delay(prvTickCount+interval-nowTick);
      if ( accframe ) {
	prvTickCount = SDL_GetTicks();
      } else {
	prvTickCount += interval;
      }
    } else if ( frame > 5 ) {
      frame = 5;
      prvTickCount = nowTick;
    } else {
      prvTickCount += frame*interval;
    }
    for ( i=0 ; i<frame ; i++ ) {
      move();
      tick++;
    }

    drawGLSceneStart();
    draw();
    drawGLSceneEnd();
    swapGLScene();
  }
  quitLast();
  return 0;
}
