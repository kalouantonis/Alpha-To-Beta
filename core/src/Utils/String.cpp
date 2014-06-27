#include <Utils/String.h>

#include <sstream>

std::string make_string(const char* str)
{
	if(str == NULL)
		// Empty string
		return std::string();
	else
        return std::string(str);
}

void split(const std::string& str, StringVector& vec, char delimiter)
{
    // Clear vector of previous items
    vec.clear();
    size_t strLen = str.size();
    if(strLen == 0)
        return;

    size_t startIndex = 0;
    // Request next index where delimiter is found
    size_t indexOfDel = str.find_last_of(delimiter, startIndex);

    while(indexOfDel != std::string::npos)
    {
        vec.push_back(str.substr(startIndex, indexOfDel-startIndex));
        // Restart start index after last delimeter position
        startIndex = indexOfDel + 1;
        if(startIndex >= strLen)
            break;

        indexOfDel = str.find_last_of(delimiter, startIndex);
    }

    if(startIndex < strLen)
        // Push back the rest of the string
        vec.push_back(str.substr(startIndex));
}

void trim(std::string& str)
{
	std::stringstream ss;
	// Pass to string stream
	ss << str;
	// Clear whitespace
	ss.clear();
	// push to string
	ss >> str;
}
