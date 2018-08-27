#ifdef _WIN32

#include "ResourcePath.h"
#include <iostream>
// Returns the path of the executable as a string
std::string resourcePath(void)
{
	TCHAR buffer[128];
	GetModuleFileName(NULL, buffer, 128);
	std::string path(buffer);
	return path.substr(0, path.find_last_of("\\") + 1);

}

#endif
