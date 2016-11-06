#ifndef _LOGGER_H_
#define _LOGGER_H_

#define LOGGER_LINE_WIDTH 40
#define LOGGER_LINES 15
#define LOGGER_BUFFER_SIZE LOGGER_LINES * LOGGER_LINE_WIDTH
#define LOGGER_MESSAGE_SIZE 128

//////////////////////////////////////////////////////////
// Logger
//////////////////////////////////////////////////////////
typedef struct Logger
{
    long StreamID;
    char Buffer[LOGGER_LINES][LOGGER_LINE_WIDTH + 1];
    char CurrentLine;
    char EreaserIndex;
    long Counter;
}
Logger;

void LoggerInit();
void LoggerAppend(const char* text);
void LoggerFlush();
//////////////////////////////////////////////////////////

#define LOG(text) LoggerAppend(text)

#define LOG(format, ...) { \
    char buffer[LOGGER_MESSAGE_SIZE]; \
    sprintf(buffer, format, __VA_ARGS__); \
    LoggerAppend(buffer); }

extern Logger GLogger;

#endif // !_LOGGER_H_
