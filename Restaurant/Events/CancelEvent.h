#pragma once
#include "Event.h"
class CancelEvent :
	public Event
{
public:
	CancelEvent(int eTime, int ordID);
	void Execute(Restaurant* pRest);
};

