/*
 Contains a function that returns the path of the executable.
 This is necessary for windows as the SFML Xcode resourcePath function provided
 only works on macOS
 */

#pragma once

#include <string>
#ifdef _WIN32
#include "Windows.h"
#endif
std::string resourcePath(void);
