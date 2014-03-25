/*  sections.h: mutual exclusion sections

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

#ifndef SECTIONS_H
#define SECTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

enum FavoriteOS { OS_X, LINUX, WINDOWS };

void sectionInitGlobals();
void sectionEntrySection(enum FavoriteOS favoriteOS);
void sectionExitSection(enum FavoriteOS favoriteOS);
void sectionCriticalSection();
void sectionRemainderSection();

#ifdef __cplusplus
}
#endif

#endif
