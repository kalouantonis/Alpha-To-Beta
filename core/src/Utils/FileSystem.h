#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <string>

namespace fs
{

/**
 * @brief Get the current working directory of program
 * @details Use this rather than OS specific stuff
 * @return current working directory string
 */
std::string currentWorkingDir();
/**
 * @brief Return OS specific path separator
 */
const char nativeSeparator();

std::string loadFileToString(const char* filename);

}

#endif // !FILESYSTEM_H_
