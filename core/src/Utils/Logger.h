#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>
#include <stdio.h>

class Logger
{
public:
    static Logger& instance()
    {
        static Logger instance;
        return instance;
    }

    ~Logger();

    void setLogFile(const char* filename);

    void log(const std::string& tag, const std::string& msg,
         const char* funcName, const char* sourceFile, unsigned int lineNum);

    /**
     * @brief Flushes output buffer. Called for critical events
     */
    void flush();

    // Used for error logging
    //static void error(bool isFatal, const std::string& msg,
    //     const char* funcName, const char* sourceFile, unsigned int lineNum);

protected:
    Logger();

private:
    Logger(const Logger&);
    Logger& operator=(const Logger&);

    void fillOutputBuffer(std::string& outputBuffer,
            const std::string& tag, const std::string& msg,
          const char* funcName, const char* sourceFile, unsigned int lineNum);

    inline FILE* loadFileStream(FILE* stream, const char* filename);

    FILE* m_pLogFile;
};


#ifndef NDEBUG // If in debug mode

// Note, the do-while removes the ; at the end of the call
#define CORE_ASSERT(expr) \
	do \
	{ \
		if(!(expr)) \
		{ \
			Logger::instance().log("ASSERT", #expr, __FUNCTION__, __FILE__, __LINE__); \\
			Logger::instance().flush(); \
			std::terminate(); \
		} \
	} \
	while(0)\

#define CORE_FATAL(str) \
    do \
    { \
        Logger::instance().log("FATAL", str, __FUNCTION__, __FILE__, __LINE__);\
        Logger::instance().flush(); \
        std::terminate(); \
    } \
    while(0)\

#define CORE_ERROR(str) \
    do \
    { \
        Logger::instance().log("ERROR",str, __FUNCTION__, __FILE__, __LINE__); \
        Logger::instance().flush(); \
    } \
    while(0)\


#define CORE_WARNING(str) \
    do \
    { \
        Logger::instance().log("WARNING", str, __FUNCTION__, __FILE__, __LINE__);\
        Logger::instance().flush(); \
    } \
    while(0)\


#define CORE_DEBUG(str) \
    do \
    { \
        Logger::instance().log("DEBUG", str, NULL, NULL, 0); \
        Logger::instance().flush(); \
    } \
    while(0) \

#define CORE_LOG(tag, str) \
    do \
    { \
        Logger::instance().log(tag, str, NULL, NULL, 0); \
        Logger::instance().flush(); \
    } \
    while(0) \


#define CORE_VERBOSE(str) \
    do \
    { \
        Logger::instance().log("VERBOSE", str, __FUNCTION__, __FILE__, __LINE__); \
    } \
    while(0) \

#else // Not in debug mode

// Keep errors and warnings, just exclude func, file and line info
#define CORE_FATAL(str) \
    do \
    { \
        Logger::instance().log("FATAL", str, NULL, NULL, 0); \
        Logger::instance().flush(); \
        std::terminate(); \
    } \
    while(0)\


#define CORE_ERROR(str) \
    do \
    { \
        Logger::instance().log("ERROR",str, NULL, NULL, 0); \
        Logger::instance().flush(); \
    } \
    while(0)\


#define CORE_WARNING(str) \
    do \
    { \
        Logger::instance().log("WARNING", str, NULL, NULL, 0);\
    } \
    while(0)\

// Release mode definitions of macros. Defined in such a way as to be
// ignored completelly by the compiler
#define CORE_DEBUG(str) do { (void)sizeof(str); } while(0)
#define CORE_VERBOSE(str) do { (void)sizeof(str); } while(0)
#define CORE_LOG(tag, str) do { (void)sizeof(str); } while(0)
#define CORE_ASSERT(expr) do { (void)sizeof(str); } while(0)

#endif

#define CORE_INFO(str) \
    do \
    { \
        Logger::instance().log("INFO", str, NULL, NULL, 0); \
    } \
    while(0) \


#endif
