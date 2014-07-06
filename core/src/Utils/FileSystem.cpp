#include <Utils/FileSystem.h>

#include <Utils/Logger.h>

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

    std::FILE* pFile = std::fopen(filename, "r");

    if(pFile != NULL)
    {
        std::string contents;
        // Set the position indicator
        std::fseek(pFile, 0, SEEK_END);
        // Resize string to fit file contents
        contents.resize(std::ftell(pFile));
        // Go to begining of file
        std::rewind(pFile);
        // Read file in to string
        std::fread(&contents[0], 1, contents.size(), pFile);
        // Close file
        std::fclose(pFile);
        return contents;
    }

    CORE_ERROR("Failed to load file in to string: " + std::string(filename));

    // Empty string
    return std::string();
}

}
