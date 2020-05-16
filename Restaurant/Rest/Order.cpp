#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, int AT, int size, double Money)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	status = WAIT;
	totalMoney = Money;
	Size = size;
	ArrTime = AT;
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}

void Order::SetType(ORD_TYPE t)
{
	type = t;
}


void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}

void Order::SetMoney(double Money)
{
	totalMoney = (Money > 0) ? Money : 0;
}

double Order::GetMoney() const
{
	return totalMoney;
}
double Order::GetSize() const
{
	return Size;
}
double Order::GetAT() const
{
	return ArrTime;
}



void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

double Order::calcWeight() const
{
	return totalMoney / ArrTime / Size;
}

bool Order::operator<(const Order& Arg) const
{
	return calcWeight() < Arg.calcWeight();
}

