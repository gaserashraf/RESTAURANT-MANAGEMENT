#include "CancelEvent.h"
#include"../Rest/Restaurant.h"
CancelEvent::CancelEvent(int eTime, int ordID):Event(eTime,ordID)
{
}

void CancelEvent::Execute(Restaurant* pRest)
{
	delete pRest->deleteOrderId(OrderID);
	/*Node<Order*>* prev = pRest->getOrdersListHead();
	Node<Order*>* curr;
	
	if (prev)
		curr = prev->getNext();
	else
		return;//dasda
	if (prev->getItem()->GetID() == OrderID)//if the first order
	{
		
		pRest->setHeadToOrdersList(curr);
		delete prev;
		return;
	}
	else
	{
		while (curr)
		{
			if (curr->getItem()->GetID() == OrderID)
			{
				prev->setNext(curr->getNext());
				delete curr;
				curr = NULL;
				return;
			}
			curr = curr->getNext();
			prev = prev->getNext();
		}
	}*/
	
}
