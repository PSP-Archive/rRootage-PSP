/*
 * $Id: letterrender.h 264 2005-11-06 17:43:44Z mrbrown $
 *
 * Copyright 2002 Kenta Cho. All rights reserved.
 */

/**
 * Letter render header file.
 *
 * @version $Revision: 264 $
 */

void drawLetter(int idx, int lx, int ly, int ltSize, int d,
		int r, int g, int b);
void drawString(char *str, int lx, int ly, int ltSize, int d, 
		int r, int g, int b);
