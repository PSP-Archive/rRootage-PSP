/*
 * $Id: foe_mtd.h 264 2005-11-06 17:43:44Z mrbrown $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */

/**
 * Foe methods.
 *
 * @version $Revision: 264 $
 */
#define FOE_ENEMY_POS_RATIO 1024

#define BULLET_COLOR_NUM 4
#define BULLET_TYPE_NUM 3

extern int processSpeedDownBulletsNum;
extern int nowait;

void initFoes();
void closeFoes();
void moveFoes();
void clearFoes();
void clearFoesZako();
void wipeBullets(Vector *pos, int width);
void drawBulletsWake();
void drawFoes();
void drawBullets();
