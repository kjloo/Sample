/*  sectionsB.c: mutual exclusion model sections

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
enum FavoriteOS currentOS;
const int SIZE = 3;
const char *LINUXLOCK = "LINUXLOCK";
const char *LINUXSEM = "LINUXSEM";
const char *WINDOWSLOCK = "WINDOWSLOCK";
const char *WINDOWSSEM = "WINDOWSSEM";
const char *OSXLOCK = "OSXLOCK";
const char *OSXSEM = "OSXSEM";
const char *ROOM = "ROOM";
const char *WAIT = "WAIT";
pthread_mutex_t linuxMutex;
sem_t linuxSem;
pthread_mutex_t windowsMutex;
sem_t windowsSem;
pthread_mutex_t osxMutex;
sem_t osxSem;
pthread_mutex_t roomMutex;

void
sectionInitGlobals()
{
  // TODO: Complete this function
  mdat_mutex_init(LINUXLOCK, &linuxMutex, NULL);
  mdat_sem_init(LINUXSEM, &linuxSem, 0, SIZE);
  mdat_mutex_init(WINDOWSLOCK, &windowsMutex, NULL);
  mdat_sem_init(WINDOWSSEM, &windowsSem, 0, SIZE);
  mdat_mutex_init(OSXLOCK, &osxMutex, NULL);
  mdat_sem_init(OSXSEM, &osxSem, 0, SIZE);
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
	mdat_sem_wait(&linuxSem);
	mdat_mutex_lock(&linuxMutex);
	if(countLINUX == 0)
	  mdat_mutex_lock(&roomMutex);
	countLINUX++;
	mdat_mutex_unlock(&linuxMutex);
	break;
  case WINDOWS:
	mdat_sem_wait(&windowsSem);
	mdat_mutex_lock(&windowsMutex);
	if(countWINDOWS == 0)
	  mdat_mutex_lock(&roomMutex);
	countWINDOWS++;
	mdat_mutex_unlock(&windowsMutex);
	break;
  case OS_X:
	mdat_sem_wait(&osxSem);
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
	mdat_sem_post(&linuxSem);
	break;
  case WINDOWS:
	mdat_mutex_lock(&windowsMutex);
	countWINDOWS--;
	if(countWINDOWS == 0)
	  mdat_mutex_unlock(&roomMutex);
	mdat_mutex_unlock(&windowsMutex);
	mdat_sem_post(&windowsSem);
	break;
  case OS_X:
	mdat_mutex_lock(&osxMutex);
	countOSX--;
	if(countOSX == 0)
	  mdat_mutex_unlock(&roomMutex);
	mdat_mutex_unlock(&osxMutex);
	mdat_sem_post(&osxSem);
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
