#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, int size , double mny ):Event(eTime, oID)
{
	OrdType = oType;
	OrdMoney = mny;
	Size = size;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fill its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1
	//For the sake of demo, this function will just create an order and add it to DemoQueue
	//Remove the next code lines in phases 1&2
	Order* pOrd = new Order(OrderID, OrdType, EventTime, Size, OrdMoney);
	switch (OrdType)
	{
		case TYPE_NRM:	//normal order
		{
			pRest->addOrderToNrm(pOrd);
			break;
		}
		case TYPE_VGAN:	//vegan
		{
			pRest->addOrderToVgn(pOrd);
			break;
		}
		case TYPE_VIP:
		{
			pRest->addOrderToVip(pOrd);
			break;
		}
	}
}
