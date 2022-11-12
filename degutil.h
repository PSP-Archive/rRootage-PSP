/*
 * $Id: degutil.h 264 2005-11-06 17:43:44Z mrbrown $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */

/**
 * Degutil header file.
 *
 * @version $Revision: 264 $
 */
#define DIV 1024
#define TAN_TABLE_SIZE 1024
#define SC_TABLE_SIZE 1024

extern int sctbl[];

void initDegutil();
int getDeg(int x, int y);
int getDistance(int x, int y);
float getDistanceFloat(float x, float y);
