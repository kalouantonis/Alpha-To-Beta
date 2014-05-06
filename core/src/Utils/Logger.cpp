#include "Logger.h"

#include <errno.h>
#include <string.h>

Logger::Logger()
{
    m_pLogFile = stdout;
}

Logger::~Logger()
{
   if(m_pLogFile != stdout)
   {
       fclose(m_pLogFile);
   }
}

void Logger::setLogFile(const char *filename)
{
    m_pLogFile = loadFileStream(m_pLogFile, filename);
}

void Logger::log(const std::string &tag, const std::string &msg, const char *funcName,
                 const char *sourceFile, unsigned int lineNum)
{
    std::string outputBuffer;

    fillOutputBuffer(outputBuffer, tag, msg, funcName, sourceFile, lineNum);

    fprintf(m_pLogFile, "%s", outputBuffer.c_str());
}

void Logger::flush()
{
    // Flush output buffer
    fflush(m_pLogFile);
}

void Logger::fillOutputBuffer(std::string &outputBuffer, const std::string &tag, const std::string &msg,
                                    const char *funcName, const char *sourceFile, unsigned int lineNum)
{
    if(!tag.empty())
        outputBuffer = "[" + tag + "] " + msg;
    else
        outputBuffer = msg;

    if(funcName != NULL)
    {
        outputBuffer += "\nFunction: ";
        outputBuffer += funcName;
    }
    if(sourceFile != NULL)
    {
        outputBuffer += "\nSource File: ";
        outputBuffer += sourceFile;
    }
    if(lineNum != 0)
    {
        outputBuffer += "\nLine: ";
        // Convert int to char
        outputBuffer += std::to_string(lineNum);
    }

    outputBuffer += '\n';
}

FILE *Logger::loadFileStream(FILE *stream, const char *filename)
{
    // overwrite previous logs
    FILE* newStream = fopen(filename, "w");

    if(newStream == NULL)
    {

        CORE_ERROR(
                   "Failed to open logger file: " + std::string(filename) +
                   ". Using console output...\n\t" +
                   strerror(errno)
        );

        // Use previous stream
        return stream;
    }

    return newStream;
}

