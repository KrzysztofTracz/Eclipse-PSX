#include "Timer.h"

TimerManager GTimerManager;

void TimerInit(Timer* timer, long trigger, long repeat, TimerCallback callback)
{
    timer->Trigger    = trigger;
    timer->Repeat     = repeat;
    timer->Callback   = callback;
    timer->Ticks      = 0;
    timer->Loop       = 0;
    timer->State      = TS_STOPPED;
}

void TimerTick(TimerHandler timerHandler)
{
    Timer* timer = &GTimerManager.Timers[timerHandler];

    if (timer->State == TS_PLAYING)
    {
        if (++timer->Ticks == timer->Trigger)
        {
            timer->Callback(timer->Handler);
            timer->Ticks = 0;

            if (timer->Repeat >= 0)
            {
                if (++timer->Loop > timer->Repeat)
                {
                    TimerStop(timer);
                }
            }
        }
    }
}

void TimerStart(TimerHandler timerHandler)
{
    GTimerManager.Timers[timerHandler].State = TS_PLAYING;
}

void TimerStop(TimerHandler timerHandler)
{
    GTimerManager.Timers[timerHandler].State = TS_STOPPED;
    GTimerManager.Timers[timerHandler].Ticks = 0;
    GTimerManager.Timers[timerHandler].Loop  = 0;
}

void TimerPause(TimerHandler timerHandler)
{
    GTimerManager.Timers[timerHandler].State = TS_PLAYING;
}

void TimerRestart(TimerHandler timerHandler)
{
    TimerStop(timerHandler);
    TimerStart(timerHandler);
}

void TimerManagerInit()
{
    int i;

    for (i = 0; i < TIMERS_POOL_SIZE; i++)
    {
        GTimerManager.Timers[i].Handler    = i;
        GTimerManager.Timers[i].IsAcquired = 0;
    }
}

TimerHandler AcquireTimer(long trigger, TimerCallback callback, long repeat)
{
    int i;

    TimerHandler result = -1;

    for (i = 0; i < TIMERS_POOL_SIZE; i++)
    {        
        if (GTimerManager.Timers[i].IsAcquired == 0)
        {
            TimerInit(&GTimerManager.Timers[i], 
                      trigger,
                      repeat, 
                      callback);
            
            GTimerManager.Timers[i].IsAcquired = 1;
            
            result = i;
            break;
        }
    }

    return result;
}

void ReleaseTimer(TimerHandler timer)
{
    GTimerManager.Timers[timer].IsAcquired = 0;
}

void TimerManagerTick()
{
    int i;    

    for (i = 0; i < TIMERS_POOL_SIZE; i++)
    {
        if (GTimerManager.Timers[i].IsAcquired == 1 && 
            GTimerManager.Timers[i].State      == TS_PLAYING)
        {
            TimerTick(i);
        }
    }
}