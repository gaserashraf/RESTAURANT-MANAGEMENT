#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Distance;	//The distance (in meters) between the order location and the resturant 
	                
	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times
	int Size;
	
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Order(int ID, ORD_TYPE r_Type, int, int, double);
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;
	void SetType(ORD_TYPE);

	void SetDistance(int);
	int GetDistance() const;
	void SetMoney(double);
	double GetMoney() const;
	double GetSize() const;
	double GetAT() const;


	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;

	bool operator<(const Order&) const;
	double calcWeight() const;

	
	//
	// TODO: Add More Member Functions As Needed
	//

};

#endif