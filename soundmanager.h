/*
 * $Id: soundmanager.h 264 2005-11-06 17:43:44Z mrbrown $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */

/**
 * BGM/SE manager header file.
 *
 * @version $Revision: 264 $
 */
void closeSound();
void initSound();
void playMusic(int idx);
void fadeMusic();
void stopMusic();
void playChunk(int idx);
void haltChunk(int idx);
