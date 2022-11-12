/*
 * $Id: genmcr.h 264 2005-11-06 17:43:44Z mrbrown $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */

/**
 * General macros.
 *
 * @version $Revision: 264 $
 */
#include "rand.h"

#define randN(N) ((int)(nextRand()>>5)%(N))
#define randNS(N) (((int)(nextRand()>>5))%(N<<1)-N)
#define randNS2(N) ((((int)(nextRand()>>5))%(N)-(N>>1)) + (((int)(nextRand()>>5))%(N)-(N>>1)))
#define absN(a) ((a) < 0 ? - (a) : (a))

#define NOT_EXIST -999999
