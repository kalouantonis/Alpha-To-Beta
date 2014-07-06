#include <Utils/FileSystem.h>

#include <Utils/Logger.h>

#include <fstream>

#ifdef WIN32

#include <direct.h>

#define GetCurrDir _getcwd

const char pathSeparator = '\\';

#elif __unix__ // Define function for linux

#include <unistd.h>

// Store function pointer
#define GetCurrDir getcwd

const char pathSeparator = '/';

#else

#error "Unknown Operating System"

#endif

// Defines FILENAME_MAX
#include <stdio.h>
#include <SFML/System/InputStream.hpp>

namespace fs
{


std::string currentWorkingDir()
{
	char currPath[FILENAME_MAX];

	if(!GetCurrDir(currPath, sizeof(currPath)))
	{
		// Empty string
		return std::string();
	}

	// Null terminate c_str
	currPath[sizeof(currPath) - 1] = '\0';

	// Automagic boxing
	return currPath;
}


const char nativeSeparator()
{
    return pathSeparator;
}

std::string loadFileToString(const char* filename)
{
	CORE_ASSERT(filename != NULL);

	std::ifstream file(filename);

	if(file.is_open())
	{
		// Create iterators
		std::istream_iterator<char> begin(file), end;
		return std::string(begin, end);
	}

	CORE_ERROR("Failed to load file in to string: " + std::string(filename));

	// Empty file
	return std::string();
}

}
