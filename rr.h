/*
 * $Id: rr.h 300 2005-12-08 08:21:11Z mrbrown $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */

/**
 * rRootage header file.
 *
 * @version $Revision: 300 $
 */
#define CAPTION "rRootage"
#define VERSION_NUM 22

#define INTERVAL_BASE 16

extern int status;
extern int interval;
extern int tick;

#define TITLE 0
#define IN_GAME 1
#define GAMEOVER 2
#define STAGE_CLEAR 3
#define PAUSE 4

void quitLast();
void initTitleStage(int stg);
void initTitle();
void initGame();
void initGameover();

/* From screenshot.c. */
void screenshot(const char *basename);
