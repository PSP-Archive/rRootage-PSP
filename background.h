/*
 * $Id: background.h 264 2005-11-06 17:43:44Z mrbrown $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */

/**
 * Screen background.
 *
 * @version $Revision: 264 $
 */

typedef struct {
  float x, y, z, ox, oy;
  float mx, my;
  int d1;
  float width, height;
  int xn, yn;
  int r, g, b, a;
} Plane;

void initBackground();
void moveBackground();
void drawBackground();
