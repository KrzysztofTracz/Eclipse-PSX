#include "Logger.h"

Logger GLogger;

char LoggerGetNextLine(char line)
{
    line++;
    if (line == LOGGER_LINES)
    {
        line = 0;
    }
    return line;
}

char LoggerGetPrevLine(char line)
{
    line--;
    if (line == 255)
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

void LoggerEreaseLine(TimerHandler timer)
{
    int  i           = 0;
    int  line        = GLogger.CurrentLine;
    char stopEreaser = 1;
     
    for (i = 0; i < LOGGER_LINES; i++)
    {
        if (GLogger.Buffer[line][0] != 0)
        {
            LoggerClearLine(line);
            stopEreaser = 0;
            break;
        }
        line = LoggerGetNextLine(line);
    }

    if (stopEreaser != 0)
    {
        TimerStop(GLogger.EreaserTimer);
    }
}

void LoggerClear()
{
#ifdef _DEBUG
    int i;

    for (i = 0; i < LOGGER_LINES; i++)
    {
        LoggerClearLine(i);
    }
#endif
}

void LoggerInit()
{
#ifdef _DEBUG
    FntLoad(960, 256);

    GLogger.StreamID = FntOpen(0, 120, 320, 120, 0, 512);
    SetDumpFnt(GLogger.StreamID);
    GLogger.CurrentLine  = 0;

    LoggerClear();

    GLogger.EreaserTimer = AcquireTimer(SECONDS_TO_TICKS(LOGGER_EREASER_WAIT_TIME), 
                                        &LoggerEreaseLine, 
                                        TRM_ENDLESS);
#endif
}

void LoggerRestartEreaser()
{
    TimerRestart(GLogger.EreaserTimer);
}

void LoggerAppend(const char* text)
{
#ifdef _DEBUG
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
    LoggerRestartEreaser();    
#endif
}

void LoggerFlush()
{   
#ifdef _DEBUG
    int i, line;

    line = GLogger.CurrentLine;

    for (i = 0; i < LOGGER_LINES; i++)
    {
        FntPrint(GLogger.StreamID, "%s\n", GLogger.Buffer[line]);
        line = LoggerGetNextLine(line);
    }

    FntFlush(GLogger.StreamID);
#endif
}