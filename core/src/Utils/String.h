#ifndef STRING_H
#define STRING_H

#include <string>

/**
 * @brief Safely create a string from a c style string
 * @details Will return an empty string if a NULL char* is provided
 * ensuring C++ style safety
 * 
 * @param str [description]
 * @return [description]
 */
std::string make_string(const char* str);

#endif // STRING_H
