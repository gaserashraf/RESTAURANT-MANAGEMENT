#pragma once
#include "Event.h"
class PromoteEvent :
	public Event
{
	int Ex;
public:
	PromoteEvent(int eTime, int ordID,int ex);
	void Execute(Restaurant* pRest);
	
};

