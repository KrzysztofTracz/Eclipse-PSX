#ifndef _TIMER_H_
#define _TIMER_H_

#define TIMERS_POOL_SIZE 32
#define TIMER_HANDLER_SIZE 5

#define SECONDS_TO_TICKS(seconds) seconds * 60 

//////////////////////////////////////////////////////////
// Timer
//////////////////////////////////////////////////////////
typedef char TimerHandler;
typedef void (*TimerCallback) (TimerHandler handler);

typedef enum TimerState
{
    TS_UNKNOWN = 0,
    TS_STOPPED = 1,
    TS_PLAYING = 2,
    TS_PAUSED  = 3
} 
TimerState;

typedef enum TimerRepeatMode
{
    TRM_ENDLESS = -1,
    TRM_NONE    =  0,
}
TimerRepeating;

typedef struct Timer
{
    long          Trigger;
    long          Repeat;
    TimerCallback Callback;

    long Ticks;
    long Loop;

    TimerHandler Handler    : TIMER_HANDLER_SIZE;
    TimerState   State      : 2;
    char         IsAcquired : 1;
} 
Timer;

void TimerTick   (TimerHandler timerHandler);
void TimerStart  (TimerHandler timerHandler);
void TimerStop   (TimerHandler timerHandler);
void TimerPause  (TimerHandler timerHandler);
void TimerRestart(TimerHandler timerHandler);
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// Timer Manager
//////////////////////////////////////////////////////////
typedef struct TimerManager
{
    Timer Timers[TIMERS_POOL_SIZE]; 
} 
TimerManager;

void TimerManagerInit();
void TimerManagerTick();

TimerHandler AcquireTimer(long trigger, TimerCallback callback, long repeat);

void ReleaseTimer(TimerHandler timer);
//////////////////////////////////////////////////////////

extern TimerManager GTimerManager;

#endif // !_TIMER_H_
