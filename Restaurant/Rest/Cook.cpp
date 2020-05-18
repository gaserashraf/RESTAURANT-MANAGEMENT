#include "Cook.h"

Cook::Cook(ORD_TYPE t, int s)
{
	ID++;
	type = t;
	speed = s;
}

Cook::Cook()
{
	servingOrder = 0;
	timeBackToAvaList = 0;
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


int Cook::GetID()
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

void Cook::setTimeBackToAvaList(int t)
{
	timeBackToAvaList = t;
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

int Cook::getTimeBackToAvaList() const
{
	return timeBackToAvaList;
}

Order* Cook::getOrderThatWorkedAt() const
{
	return orderThatWorkedAt;
}

//<<<<<<< HEAD
int Cook::getTimeFinshOrder() const
{
	return TimeFinshOrder;
}

//=======
void Cook::setRest(int r)
{
	Rest = r;
}
//>>>>>>> 4698248c273d0b796c914f2c25f2f664fb4f9b3c

void Cook::setInjuryProbability(int i)
{
	injuryProbability = i;
}