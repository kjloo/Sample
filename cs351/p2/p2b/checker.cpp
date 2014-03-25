/*  checker.cpp: mutual exclusion checker

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

#include <string>
using namespace std;

#include "checker.h"

// Global Variables
static int osxCount = 0;
static int linuxCount = 0;
static int windowsCount = 0;
static bool multipleUse = false; 	// set to true if > 1 in exhibit at once

// Global Error Messages
static string conflictMsg =
  "VIOLATION: two different OS in exhibit at same time";
#ifdef CHECK_LIMIT
static string limitMsg =
  "VIOLATION: more than three people in exhibit";
#endif
static string multipleUseMsg =
  "WARNING: never had more than one person in exhibit at once";

// updateAndCheck: Updates the status of the checker and checks for violations.
// Returns a pointer to an error message if a violation occurs and NULL otherwise.
//
static const char *updateAndCheck(string section, string property)
{
  if (section == "Critical") {
    if (property == "OS_X") {
      osxCount++;
      if (osxCount > 1) multipleUse = true;
      if (linuxCount + windowsCount > 0)
	return conflictMsg.c_str();
#ifdef CHECK_LIMIT
      if (osxCount > 3)
        return limitMsg.c_str();
#endif
    }
    else if (property == "Linux") {
      linuxCount++;
      if (linuxCount > 1) multipleUse = true;
      if (osxCount + windowsCount > 0)
	return conflictMsg.c_str();
#ifdef CHECK_LIMIT
      if (linuxCount > 3)
        return limitMsg.c_str();
#endif
    }
    if (property == "Windows") {
      windowsCount++;
      if (windowsCount > 1) multipleUse = true;
      if (linuxCount + osxCount > 0)
	return conflictMsg.c_str();
#ifdef CHECK_LIMIT
      if (windowsCount > 3)
        return limitMsg.c_str();
#endif
    }
  }
  else if (section == "Exit") {
    if (property == "OS_X")
      osxCount--;
    else if (property == "Linux")
      linuxCount--;
    else if (property == "Windows")
      windowsCount--;
  }
  else if (section == "AllFinish") {
    if (!multipleUse)
      return multipleUseMsg.c_str();
  }

  return NULL;
}

// Callback function to register with MDAT
const char *checkerCallback(int id, const char *section, const char *property)
{
  return updateAndCheck(section, property);
}
