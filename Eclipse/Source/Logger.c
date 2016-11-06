#include "Logger.h"

Logger GLogger;

char LoggerGetNextLine(char line)
{
    line++;
    if (line >= LOGGER_LINES)
    {
        line = 0;
    }
    return line;
}

char LoggerGetPrevLine(char line)
{
    line--;
    if (line < 0)
    {
        line = LOGGER_LINES - 1;
    }
    return line;
}

void LoggerClearLine(char line)
{
    int i;

    for (i = 0; i < LOGGER_LINE_WIDTH + 1; i++)
    {
        GLogger.Buffer[line][i] = 0;
    }
}

void LoggerInit()
{
    int i,j;

    GLogger.StreamID = FntOpen(0, 120, 320, 240, 0, 512);
    SetDumpFnt(GLogger.StreamID);
    GLogger.CurrentLine  = 0;
    GLogger.EreaserIndex = 1;
    GLogger.Counter      = 0;

    for (i = 0; i < LOGGER_LINES; i++)
    {
        LoggerClearLine(i);
    }
}

void LoggerAppend(const char* text)
{
    int i      = 0;
    int cursor = 0;

    LoggerClearLine(GLogger.CurrentLine);

    while(text[i] != 0)
    {
        if (cursor >= LOGGER_LINE_WIDTH)
        {
            cursor = 0;
            GLogger.CurrentLine = LoggerGetNextLine(GLogger.CurrentLine);
            LoggerClearLine(GLogger.CurrentLine);
        }
        GLogger.Buffer[GLogger.CurrentLine][cursor++] = text[i++];
    }
    GLogger.CurrentLine = LoggerGetNextLine(GLogger.CurrentLine);
}

void LoggerFlush()
{   
    int i, line;

    line = GLogger.CurrentLine;

    for (i = 0; i < LOGGER_LINES; i++)
    {
        FntPrint(GLogger.StreamID, "%s\n", GLogger.Buffer[line]);
        line = LoggerGetNextLine(line);
    }

    FntFlush(GLogger.StreamID);

    GLogger.Counter++;
    if (GLogger.Counter >= 60 * 3)
    {
        LoggerClearLine(GLogger.CurrentLine);
        GLogger.Counter = 0;
    }
}