#include "Cook.h"


Cook::Cook(ORD_TYPE t, int s)
{
	//ID = id;
	type = t;
	speed = s;
}

Cook::Cook()
{
	servingOrder = 0;
	timeInBusyList = 0;
	orderThatWorkedAt = nullptr;
	TimeFinshOrder = 0;
}

void Cook::setSpeed(int s)
{
	speed = s;
}

int Cook::getSpeed()
{
	return speed;
}

void Cook::setBreakTime(int b)
{
	BKT = b;
}

int Cook::getBreakTime()
{
	return BKT;
}


Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}

void Cook::setServingOrder(int s)
{
	servingOrder = s;
}

void Cook::setTimeInBusyList(int t)
{
	timeInBusyList = t;
}

void Cook::setOrderThatWorkedAt(Order* o)
{
	orderThatWorkedAt = o;
}

void Cook::setTimeFinshOrder(int t)
{
	TimeFinshOrder = t;
}

int Cook::getServingOrder() const
{
	return servingOrder;
}

int Cook::getTimeInBusyList() const
{
	return timeInBusyList;
}

Order* Cook::getOrderThatWorkedAt() const
{
	return orderThatWorkedAt;
}

int Cook::getTimeFinshOrder() const
{
	return TimeFinshOrder;
}


