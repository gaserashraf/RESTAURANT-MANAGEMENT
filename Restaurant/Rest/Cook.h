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
	bool injured;
	int injSpeed;

	//gaser 17/5
	int servingOrder; //intaial zero //to take break after making n order
	int timeBackToAvaList; // if the cook in busy list it will be = to BKT + time at which add to busy list and back to the avaliable list when timeInBusyList=currstep
	Order* orderThatWorkedAt;
	int TimeFinshOrder; //== ceil(Size/speed)

	//Gamal 18/5
	int Rest; // implemented as static as all cooks have the same rest period
	
	/// Hos29/5
	 float injuryProbability;	// probability of getting injured FOR BUSY COOKS ONLY
	 void setInjSpeed()
	 {
		 injSpeed = speed / 2;
		 if (!(injSpeed))
			 injSpeed = 1;
	 }
public:
	Cook();
	void setSpeed(int s);
	int getSpeed();

	/// Hos29/5
	void setInj(bool i);
	bool isInj();
	int getInjSpeed();


	void setBreakTime(int );
	int getBreakTime();
	Cook( ORD_TYPE,int);
	virtual ~Cook();
	int GetID();
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE) ;


	void setServingOrder(int s);
	void setTimeBackToAvaList(int t);
	void setOrderThatWorkedAt(Order* o);
	void setTimeFinshOrder(int t);

	int getServingOrder() const;
	int getTimeBackToAvaList() const;
	Order* getOrderThatWorkedAt() const;
	int getTimeFinshOrder() const;

	


	void setRest(int r);
	void setInjuryProbability(int i);

	/// Hos 31/5
	int State() 
	{
		if (injured && orderThatWorkedAt == nullptr) return 2;
		else if (orderThatWorkedAt == nullptr) return 1;
		else return 0;
	}
};
