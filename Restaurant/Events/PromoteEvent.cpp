#include "PromoteEvent.h"
#include"../Rest/Restaurant.h"
PromoteEvent::PromoteEvent(int eTime, int ordID,int ex):Event(eTime,ordID)
{
	Ex = ex;
}

void PromoteEvent::Execute(Restaurant* pRest)
{
	//this is to be promoted
	//1-add to Queue VIP
	//2-Remove from Normal
	//pRest->addOrderToVip(pRest->deleteOrderId(OrderID)->getItem());
	Node <Order*>* pOrd = pRest->deleteOrderId(OrderID);
	if (pOrd && pOrd->getItem() && pOrd->getItem()->getStatus()==WAIT)
	{
		Order* ord = pOrd->getItem();
		ord->SetMoney(ord->GetMoney() + Ex);
		ord->SetType(TYPE_VIP);
		pRest->addOrderToVip(ord);
		pRest->setnumNormalOrders(pRest->getnumNormalOrders() - 1);
		pRest->setnumVIPOrders(pRest->getnumVIPOrders() + 1);
		pRest->setOriginalNormalOrders(pRest->getOriginalNormalOrders() - 1);
	}

	
	
	/*Node<Order*>* prev = pRest->getOrdersListHead(),*curr;
	if (prev)
		curr = prev->getNext();
	else
		return;//dasda
	if (prev->getItem()->GetID() == OrderID) //if the first order
	{
		//Order* nOrder = new Order(prev->getItem()->GetID(), TYPE_VIP, prev->getItem()->GetAT(), prev->getItem()->GetSize(), prev->getItem()->GetMoney());
		pRest->addOrderToVip(prev->getItem());
		pRest->setHeadToOrdersList(curr);
		//delete prev;
		return;
	}
	else
	{
		while (curr)
		{
			if (curr->getItem()->GetID() == OrderID)
			{
				//Order* nOrder = new Order(curr->getItem()->GetID(), TYPE_VIP, curr->getItem()->GetAT(), curr->getItem()->GetSize(), curr->getItem()->GetMoney());
				pRest->addOrderToVip(curr->getItem());
				prev->setNext(curr->getNext());
				//delete curr;
				curr = NULL;
				return;
			}
			curr = curr->getNext();
			prev = prev->getNext();
		}
	}*/
}

