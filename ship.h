/*
 * $Id: ship.h 332 2005-12-16 06:32:36Z mrbrown $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */

/**
 * Players ship.
 *
 * @version $Revision: 332 $
 */
#include "vector.h"

#define FIELD_WIDTH 320
#define FIELD_HEIGHT 480
#define FIELD_WIDTH_8 (FIELD_WIDTH<<8)
#define FIELD_HEIGHT_8 (FIELD_HEIGHT<<8)

#define FIELD_SCREEN_RATIO 10000.0f 

typedef struct {
  Vector pos, bombPos;
  int cnt, laserCnt;
  int speed;
  int invCnt;
  int bombCnt, bombWdt;
  int grzCnt, grzInvCnt, rollingCnt, grzWdt, grzf;
  float d;
  int color, colorChgCnt, fldWdt, absEng;
  int rfCnt, rfMtr, rfMtrDec, rfWdt, reflects;
} Ship;

extern Ship ship;
extern int bonusScore, bomb;

void initShip();
void moveShip();
void drawShip();
void destroyShip();
int getPlayerDeg(int x, int y);
