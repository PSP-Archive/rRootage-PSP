/*
 * $Id: laser.h 264 2005-11-06 17:43:44Z mrbrown $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */

/**
 * Players laser.
 *
 * @version $Revision: 264 $
 */
#include "vector.h"

typedef struct {
  int y;
  int color;
  int cnt;
} Laser;

void initLasers();
void moveLasers();
void drawLasers();
void addLaser();
