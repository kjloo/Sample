/*  sectionsA.c: mutual exclusion model sections

    Copyright (C) 2013  Eric Larson and Rochelle Palting
    elarson@seattleu.edu

    This file is part of the MDAT infrastructure.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include "sections.h"
#include "mdat.h"

// TODO: Declare shared variables here
int countLINUX = 0;
int countWINDOWS = 0;
int countOSX = 0;
const char *LINUX_LOCK = "LINUX_LOCK";
const char *WINDOWS_LOCK = "WINDOWS_LOCK";
const char *OSX_LOCK = "OSX_LOCK";
const char *ROOM = "ROOM";
const char *WAIT = "WAIT";
pthread_mutex_t linuxMutex;
pthread_mutex_t windowsMutex;
pthread_mutex_t osxMutex;
pthread_mutex_t roomMutex;

void
sectionInitGlobals()
{
  // TODO: Complete this function
  mdat_mutex_init(LINUX_LOCK, &linuxMutex, NULL);
  mdat_mutex_init(WINDOWS_LOCK, &windowsMutex, NULL);
  mdat_mutex_init(OSX_LOCK, &osxMutex, NULL);
  mdat_mutex_init(ROOM, &roomMutex, NULL);
}

void
sectionEntrySection(enum FavoriteOS favoriteOS)
{
  // LEAVE THIS STATEMENT
  mdat_enter_section("Entry");

  // TODO: Complete this function
  switch(favoriteOS) {
  case LINUX: 
	mdat_mutex_lock(&linuxMutex);
	if(countLINUX == 0)
	  mdat_mutex_lock(&roomMutex);
	countLINUX++;
	mdat_mutex_unlock(&linuxMutex);
	break;
  case WINDOWS:
	mdat_mutex_lock(&windowsMutex);
	if(countWINDOWS == 0)
	  mdat_mutex_lock(&roomMutex);
	countWINDOWS++;
	mdat_mutex_unlock(&windowsMutex);
	break;
  case OS_X:
	mdat_mutex_lock(&osxMutex);
	if(countOSX == 0)
	  mdat_mutex_lock(&roomMutex);
	countOSX++;
	mdat_mutex_unlock(&osxMutex);
	break;
  }
	
}

void
sectionExitSection(enum FavoriteOS favoriteOS)
{
  // LEAVE THIS STATEMENT
  mdat_enter_section("Exit");

  // TODO: Complete this function
  switch(favoriteOS) {
  case LINUX:
	mdat_mutex_lock(&linuxMutex);
	countLINUX--;
	if(countLINUX == 0)
	  mdat_mutex_unlock(&roomMutex);
	mdat_mutex_unlock(&linuxMutex);
	break;
  case WINDOWS:
	mdat_mutex_lock(&windowsMutex);
	countWINDOWS--;
	if(countWINDOWS == 0)
	  mdat_mutex_unlock(&roomMutex);
	mdat_mutex_unlock(&windowsMutex);
	break;
  case OS_X:
	mdat_mutex_lock(&osxMutex);
	countOSX--;
	if(countOSX == 0)
	  mdat_mutex_unlock(&roomMutex);
	mdat_mutex_unlock(&osxMutex);
	break;
  }
}

// DO NOT TOUCH THIS FUNCTION

void
sectionRemainderSection(enum FavoriteOS favoriteOS)
{
  mdat_enter_section("Remainder");
}

// DO NOT TOUCH THIS FUNCTION

void
sectionCriticalSection(enum FavoriteOS favoriteOS)
{
  int x, y;

  mdat_enter_section("Critical");

  // The code here is garbage - just to force the threads to spend
  // a little time in the critical section.  This makes it easier
  // to catch mutual exclusion problems.
  x = 3;
  y = x * 7;
  x--;
  y++;
  y = y - 1;
}
