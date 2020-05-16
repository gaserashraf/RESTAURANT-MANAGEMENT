#include "Event.h"

#include"../Rest/Restaurant.h"
Event::Event(int eTime, int ordID)
{
	EventTime = eTime;
	OrderID	= ordID;
}


int Event::getEventTime()
{
	return EventTime;
}
int Event::getOrderID()
{
	return OrderID;
}


Event::~Event()
{

}

