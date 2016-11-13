#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Engine\Logger.h"
#include "Engine\Timer.h"
#include "Engine\Input.h"
#include "Engine\Graphics.h"

typedef void(*EngineUpdateCallback) ();

void EngineInit(EngineUpdateCallback updateCallback);
int  EngineStart();

#endif // !_ENGINE_H_