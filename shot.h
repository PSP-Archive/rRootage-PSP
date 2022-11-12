/*
 * $Id: shot.h 264 2005-11-06 17:43:44Z mrbrown $
 *
 * Copyright 2002 Kenta Cho. All rights reserved.
 */

/**
 * Shot data.
 *
 * @version $Revision: 264 $
 */
#include "vector.h"

typedef struct {
  float x, y, mx, my;
  float d;
  int cnt, color;
  float width, height;
} Shot;

#define SHOT_MAX 64

extern Shot shot[];

void initShots();
void moveShots();
void drawShots();
void addShot(int x, int y, int ox, int oy, int color);
