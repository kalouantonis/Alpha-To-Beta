#ifndef STRING_H
#define STRING_H

#include <string>

/**
 * @brief Safely create a string from a c style string
 * @details Will return an empty string if a NULL char* is provided
 * ensuring C++ style safety
 * 
 * @param str C-Style string to convert
 * @return Created string, may be empty
 */
std::string make_string(const char* str);

#endif // STRING_H
