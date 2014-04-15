#include <Utils/FileSystem.h>

#ifdef WIN32

#include <direct.h>

#define GetCurrDir _getcwd

#elif __unix__ // Define function for linux

#include <unistd.h>

// Store function pointer
#define GetCurrDir getcwd

#else

#error "Unknown Operating System"

#endif

// Defines FILENAME_MAX
#include <stdio.h>

std::string getCurrentWorkingDir()
{
	char currPath[FILENAME_MAX];

	if(!GetCurrDir(currPath, sizeof(currPath)))
	{
		return nullptr;
	}

	// Null terminate c_str
	currPath[sizeof(currPath) - 1] = '\0';

	// Automagic boxing
	return currPath;
}
