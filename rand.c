/*
 * $Id: rand.c 264 2005-11-06 17:43:44Z mrbrown $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */

/**
 * Make random number(Using Mersenne Twister).
 *
 * @version $Revision: 264 $
 */
#include "rand.h"

extern void init_genrand(unsigned long s);
extern unsigned long genrand_int32();

void setSeed(unsigned long s) {
  init_genrand(s);
}

unsigned long nextRand() {
  return genrand_int32();
}
