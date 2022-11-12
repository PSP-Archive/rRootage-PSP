/*
 * $Id: boss_mtd.h 268 2005-11-10 08:02:20Z mrbrown $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */

/**
 * Boss methods.
 *
 * @version $Revision: 268 $
 */
#include "vector.h"

void createBoss(int seed, float rank, int round);
void initBoss();
void moveBoss();
void drawBoss();
int checkHitDownside(int x);
int checkHitUpside();
void damageBoss(int dmg);
void damageBossLaser(int cnt);
void weakenBoss();
void drawBossState();
Vector* getBossPos();
