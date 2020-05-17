#pragma once

#include "..\Defs.h"
#include "Order.h"

#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		//dishes it can prepare in one clock tick (in one timestep)
	int BKT;

	//gaser
	int servingOrder;//intaial zero //to take break after making n order
	int timeInBusyList; // if the cook in busy list it will be incresed until to be = to BKT and back to the avaliable list
	Order* orderThatWorkedAt;
	int TimeFinshOrder; //== ceil(Size/speed)

	//Gamal 18/5
	 static int Rest; // implemented as static as all cooks have the same rest period
	 static int injuryProbability;	// probability of getting injured FOR BUSY COOKS ONLY
public:
	Cook();
	void setSpeed(int s);
	int getSpeed();
	void setBreakTime(int );
	int getBreakTime();
	Cook( ORD_TYPE,int);
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE) ;


	void setServingOrder(int s);
	void setTimeInBusyList(int t);
	void setOrderThatWorkedAt(Order* o);

	int getServingOrder() const;
	int getTimeInBusyList() const;
	Order* getOrderThatWorkedAt() const;

	void setRest(int r);
	void setInjuryProbability(int i);
};
