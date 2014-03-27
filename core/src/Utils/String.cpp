#include <Utils/String.h>

std::string make_string(const char* str)
{
	if(str == NULL)
		// Empty string
		return std::string();
	else
		return std::string(str);
}