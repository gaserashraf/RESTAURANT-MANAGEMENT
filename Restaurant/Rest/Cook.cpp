#include "Cook.h"


Cook::Cook(ORD_TYPE t, int s)
{
	//ID = id;
	type = t;
	speed = s;
}

Cook::Cook(){}

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


