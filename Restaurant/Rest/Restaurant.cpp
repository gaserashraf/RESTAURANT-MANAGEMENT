#include <cstdlib>
#include <time.h>
#include <iostream>
#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Generic_DS\LinkedList.h"

using namespace std;



Restaurant::Restaurant()
{
	pGUI = NULL;
	numServGOrder = 0;
	numServVOrder = 0;
	numServNOrder = 0;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE mode = pGUI->getGUIMode();
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		ReadInput(pGUI->GetString());
		InteractiveMode();
		break;
	case MODE_STEP:
		ReadInput(pGUI->GetString());
		StepByStepMode();
		break;
	case MODE_SLNT:
		ReadInput(pGUI->GetString());
		SilentMode();
		break;
	case MODE_DEMO:
	{
		ReadInput(pGUI->GetString());
	}
	//Just_A_Demo();

	};
	
}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event* pE;
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
	/*delete[]pNormalCook;	//added
	delete[]pVeganCook;
	delete[]pVIPCook;*/
	if (pGUI)
		delete pGUI;
}

Node<Order*>* Restaurant::getOrdersListHead()
{
	
	return NRM.getHead();
}

void Restaurant::setHeadToOrdersList(Node<Order*>* temp)
{
	NRM.setHead(temp);
}

Node<Order*>* Restaurant::deleteOrderId(int id)
{
	return NRM.DeleteNodeId(id);
}



void Restaurant::FillDrawingList()	//Gamal 18/5
{
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);
	Node<Cook*>* tempcook = pAvliableNormalCook.getHead();	//adding normal cooks to drawing list
	Cook* pcook;
	while (tempcook)
	{
		pcook = tempcook->getItem();
		pGUI->AddToDrawingList(pcook);
		tempcook = tempcook->getNext();
	}


	tempcook = pAvliableVeganCook.getHead();	//adding vegan cooks to drawing list
	while (tempcook)
	{
		pcook = tempcook->getItem();
		pGUI->AddToDrawingList(pcook);
		tempcook = tempcook->getNext();
	}

	tempcook = pAvliableVIPCook.getHead();	// adding VIP cooks to drawing list
	while (tempcook)
	{
		pcook = tempcook->getItem();
		pGUI->AddToDrawingList(pcook);
		tempcook = tempcook->getNext();
	}



	Node<Order*>* temporder = NRM.getHead();	//adding normal orders to drawing list
	Order* porder;
	while (temporder)
	{
		porder = temporder->getItem();
		pGUI->AddToDrawingList(porder);
		temporder = temporder->getNext();
	}

	Order* firstVGNorder;	//adding VGN orders to drawing list
	VGN.dequeue(firstVGNorder);
	pGUI->AddToDrawingList(firstVGNorder);
	VGN.peekFront(porder);
	while (porder!=firstVGNorder)
	{
		VGN.dequeue(porder);
		pGUI->AddToDrawingList(porder);
		VGN.enqueue(porder);
		VGN.peekFront(porder);
	}

	Order* firstVIPorder;	//adding VIP orders to drawing list
	VIP.pop(firstVIPorder);
	pGUI->AddToDrawingList(firstVIPorder);
	VIP.peak(porder);
	while (porder != firstVIPorder)
	{
		VIP.pop(porder);
		pGUI->AddToDrawingList(porder);
		VIP.insert(porder);
		VIP.peak(porder);
	}

}

void Restaurant::addOrderToNrm(Order* O)
{
	NRM.InsertEnd(O);
}
void Restaurant::addOrderToVgn(Order* O)
{
	VGN.enqueue(O);
}
void Restaurant::addOrderToVip(Order* O)
{
	VIP.insert(O);
}

void Restaurant::ReadInput(string FileName) //Gamal 17/5
{
	ifstream File;
	File.open(FileName);
	File >> CooksNum[0] >> CooksNum[1] >> CooksNum[2];
	/*
	pNormalCook = new Cook[CooksNum[0]];
	pVeganCook = new Cook[CooksNum[1]];
	pVIPCook = new Cook[CooksNum[2]];*/
	//File >> CooksSpd[0] >> CooksSpd[1] >> CooksSpd[2];
	//File >> CooksBrk[3] >> CooksBrk[0] >> CooksBrk[1] >> CooksBrk[2];
	
	File >> minSpeeds[0] >> maxSpeeds[0] >> minSpeeds[1] >> maxSpeeds[1] >> minSpeeds[2] >> maxSpeeds[2];

	File >> BO >> minBreakTime[0] >> maxBreaktime[0] >> minBreakTime[1] >> maxBreaktime[1] >> minBreakTime[2] >> maxBreaktime[2];

	File >> injuryProbability >> restPeriod;
	
	File >> APL >> VIPtoUrgent;

	int id = 1;
	for (size_t i = 0; i < CooksNum[0]; i++)	//loop to initialize normal cooks and add them to available cooks list
	{
		//pNormalCook[i].setSpeed(CooksSpd[0]);
		//pNormalCook[i].setBreakTime(CooksBrk[0]);
		Cook* newCook = new Cook;
		int speed = rand() % (maxSpeeds[0] - minSpeeds[0] + 1) + minSpeeds[0];
		newCook->setSpeed(speed);
		int breakTime = rand() % (maxBreaktime[0] - minBreakTime[0] + 1) + minBreakTime[0];
		newCook->setBreakTime(breakTime);
		newCook->setRest(restPeriod);	// only needed to be set once, test period is implemented as static member and will be valid for all cooks
		newCook->setInjuryProbability(injuryProbability);
		newCook->setType(TYPE_NRM);
		newCook->setID(id);
		addToAvNorCook(newCook);
		id++;
	}

	for (size_t i = 0; i < CooksNum[1]; i++)	//loop to initialize vegan cooks and add them to available cooks list
	{
		//pNormalCook[i].setSpeed(CooksSpd[1]);
		//pNormalCook[i].setBreakTime(CooksBrk[1]);
		Cook* newCook = new Cook;
		int speed = rand() % (maxSpeeds[1] - minSpeeds[1] + 1) + minSpeeds[1];
		newCook->setSpeed(speed);
		int breakTime = rand() % (maxBreaktime[1] - minBreakTime[1] + 1) + minBreakTime[1];
		newCook->setBreakTime(breakTime);
		newCook->setRest(restPeriod);	// only needed to be set once, test period is implemented as static member and will be valid for all cooks
		newCook->setInjuryProbability(injuryProbability);
		newCook->setType(TYPE_VGAN);
		newCook->setID(id);
		addToAvVaCook(newCook);
		id++;
	}
	for (size_t i = 0; i < CooksNum[2]; i++)	////loop to initialize VIP cooks and add them to available cooks list
	{
		//pNormalCook[i].setSpeed(CooksSpd[2]);
		//pNormalCook[i].setBreakTime(CooksBrk[2]);
		Cook* newCook = new Cook;
		int speed = rand() % (maxSpeeds[2] - minSpeeds[2] + 1) + minSpeeds[2];
		newCook->setSpeed(speed);
		int breakTime = rand() % (maxBreaktime[2] - minBreakTime[2] + 1) + minBreakTime[2];
		newCook->setBreakTime(breakTime);
		newCook->setRest(restPeriod);	// only needed to be set once, test period is implemented as static member and will be valid for all cooks
		newCook->setInjuryProbability(injuryProbability);
		newCook->setType(TYPE_VIP);
		newCook->setID(id);
		addToAvVIPCook(newCook);
		id++;
	}
	
	int EventsNum;	
	File >> EventsNum;
	for (int i = 0; i < EventsNum; i++)
	{
		char EventType;
		File >> EventType;
		char OrderType;
		int AT;
		int Size;
		int Money;
		int ID;
		Event* EventB;
		switch (EventType)
		{
		case 'R':
		{
			File >> OrderType >> AT >> ID >> Size >> Money;
			ORD_TYPE ORD;
			switch (OrderType)
			{
			case 'N':
				ORD = TYPE_NRM;
				numNormalOrders++;
				break;
			case 'V':
				ORD = TYPE_VIP;
				numVIPOrders++;
				break;
			case 'G':
				ORD = TYPE_VGAN;
				numVeganOrders++;
				break;
			}
			EventB = new ArrivalEvent(AT, ID, ORD, Size, Money);
			//Order OrderX(ID, ORD, AT, Size, Money);
			//OrdersList.InsertEnd(&OrderX);
			//NRM.InsertEnd(&OrderX);
			break;
		}
		case 'X':
		{
			File >> AT >> ID;
			EventB = new CancelEvent(AT, ID);
			break;

		}
		case 'P':
		{
			int ExMoney;
			File >> AT >> ID >> ExMoney;
			EventB = new PromoteEvent(AT, ID, ExMoney);
			break;
		}
		}
		EventsQueue.enqueue(EventB);
		//EventB->Execute(this);
		/// NOT COMPLETED

	}
	/*NRM.PrintList();
	VIP.printAsTree();*/

}


//////////////////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//Begin of DEMO-related functions

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{

	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2

	int EventCnt;
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->PrintMessage("Generating Events randomly... In next phases, Events should be loaded from a file...CLICK to continue");
	pGUI->waitForClick();

	//Just for sake of demo, generate some cooks and add them to the drawing list
	//In next phases, Cooks info should be loaded from input file
	int C_count = 12;
	Cook* pC = new Cook[C_count];
	int cID = 1;

	for (int i = 0; i < C_count; i++)
	{
		cID += (rand() % 15 + 1);
		pC[i].setID(cID);
		pC[i].setType((ORD_TYPE)(rand() % TYPE_CNT));
	}


	int EvTime = 0;

	int O_id = 1;

	//Create Random events and fill them into EventsQueue
	//All generated event will be "ArrivalEvents" for the demo
	for (int i = 0; i < EventCnt; i++)
	{
		O_id += (rand() % 4 + 1);
		int OType = rand() % TYPE_CNT;	//Randomize order type		
		EvTime += (rand() % 5 + 1);			//Randomize event time
		pEv = new ArrivalEvent(EvTime, O_id, (ORD_TYPE)OType);
		EventsQueue.enqueue(pEv);

	}

	// --->   In next phases, no random generation is done
	// --->       EventsQueue should be filled from actual events loaded from input file





	//Now We have filled EventsQueue (randomly)
	int CurrentTimeStep = 1;


	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);


		//The next line may add new orders to the DEMO_Queue
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step


/////////////////////////////////////////////////////////////////////////////////////////
		/// The next code section should be done through function "FillDrawingList()" once you
		/// decide the appropriate list type for Orders and Cooks

		//Let's add ALL randomly generated Cooks to GUI::DrawingList
		for (int i = 0; i < C_count; i++)
			pGUI->AddToDrawingList(&pC[i]);

		//Let's add ALL randomly generated Ordes to GUI::DrawingList
		int size = 0;
		Order** Demo_Orders_Array = DEMO_Queue.toArray(size);

		for (int i = 0; i < size; i++)
		{
			pOrd = Demo_Orders_Array[i];
			pGUI->AddToDrawingList(pOrd);
		}
		/////////////////////////////////////////////////////////////////////////////////////////

		pGUI->UpdateInterface();
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
	}

	delete[]pC;


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();


}
////////////////

void Restaurant::AddtoDemoQueue(Order* pOrd)
{
	DEMO_Queue.enqueue(pOrd);
}

/// ==> end of DEMO-related function
//////////////////////////////////////////////////////////////////////////////////////////////

bool Restaurant::isAvliableNormalCooks()
{
	return !pAvliableNormalCook.isEmpty();
}
bool Restaurant::isAvliableVeganCooks()
{
	return !pAvliableVeganCook.isEmpty();
}
bool Restaurant::isAvliableVIPCooks()
{
	return !pAvliableVIPCook.isEmpty();
}

void Restaurant::addToAvNorCook(Cook* c)
{
	pAvliableNormalCook.InsertEnd(c);
}

void Restaurant::addToAvVaCook(Cook* c)
{
	pAvliableVeganCook.InsertEnd(c);
}

void Restaurant::addToAvVIPCook(Cook* c)
{
	pAvliableVIPCook.InsertEnd(c);
}

void Restaurant::addToBuNorCook(Cook* c)
{
	pBusyNormalCook.InsertEnd(c);
}

void Restaurant::addToBuVaCook(Cook* c)
{
	pBusyVeganCook.InsertEnd(c);
}

void Restaurant::addToVuVIPCook(Cook* c)
{
	pBusyVIPCook.InsertEnd(c);
}

Node<Cook*>* Restaurant::RemoveAndGetCookByIdFromANC(int id)
{
	return pAvliableNormalCook.RemoveCookFromListWithOutDelete(id);
}

Node<Cook*>* Restaurant::RemoveAndGetCookByIdFromAGC(int id)
{
	return pAvliableVeganCook.RemoveCookFromListWithOutDelete(id);
}

Node<Cook*>* Restaurant::RemoveAndGetCookByIdFromAVC(int id)
{
	return pAvliableVIPCook.RemoveCookFromListWithOutDelete(id);
}

Node<Cook*>* Restaurant::RemoveAndGetCookByIdFromBNC(int id)
{
	return pBusyNormalCook.RemoveCookFromListWithOutDelete(id);
}

Node<Cook*>* Restaurant::RemoveAndGetCookByIdFromBGC(int id)
{
	return pBusyVeganCook.RemoveCookFromListWithOutDelete(id);
}

Node<Cook*>* Restaurant::RemoveAndGetCookByIdFromBVC(int id)
{
	return pBusyVIPCook.RemoveCookFromListWithOutDelete(id);
}

Node<Order*>* Restaurant::RemoveAndGetOrderByIdFromServeOrderList(int id)
{
	
	Node<Order*>* No = ServeOrders.DeleteNodeId(id);
	
	if (No->getItem()->GetType() == TYPE_VIP)
		numServVOrder--;
	else if (No->getItem()->GetType() == TYPE_NRM)
		numServNOrder--;
	else if (No->getItem()->GetType() == TYPE_VGAN)
		numServGOrder--;
	return No;
}

void Restaurant::addToFinshOrder(Order* o)
{
	FinshOrders.InsertEnd(o);
}

void Restaurant::addToServeOrder(Order* o)
{
	ServeOrders.InsertEnd(o);
	if (o->GetType() == TYPE_VIP)
		numServVOrder++;
	else if (o->GetType() == TYPE_NRM)
		numServNOrder++;
	else if (o->GetType() == TYPE_VGAN)
		numServGOrder++;
}

void Restaurant::CheckIfCooksTakeBreak(int currStep)
{
	
	Node<Cook*>* Ncook;
	Node<Cook*> *H = pAvliableNormalCook.getHead();//to travesre on the list
	while (H)
	{	
		if (H->getItem()->getServingOrder() == BO) // this cook should take a break
		{
			Ncook = H;
			Ncook->getItem()->setTimeBackToAvaList(currStep + Ncook->getItem()->getBreakTime());
			Ncook = RemoveAndGetCookByIdFromANC(H->getItem()->GetID());
			pBusyNormalCook.InsertEnd(Ncook->getItem());
		}
		H = H->getNext();
	}

	H = pAvliableVeganCook.getHead();
	while (H)
	{
		if (H->getItem()->getServingOrder() == BO) // this cook should take a break
		{
			Ncook = H;
			Ncook->getItem()->setTimeBackToAvaList(currStep + Ncook->getItem()->getBreakTime());
			Ncook = RemoveAndGetCookByIdFromAGC(H->getItem()->GetID());
			pBusyVeganCook.InsertEnd(Ncook->getItem());
		}
		H = H->getNext();
	}

	H = pAvliableVIPCook.getHead();
	while (H)
	{
		if (H->getItem()->getServingOrder() == BO) // this cook should take a break
		{
			Ncook = H;
			Ncook->getItem()->setTimeBackToAvaList(currStep + Ncook->getItem()->getBreakTime());
			Ncook = RemoveAndGetCookByIdFromAVC(H->getItem()->GetID());
			pBusyVIPCook.InsertEnd(Ncook->getItem());
		}
		H = H->getNext();
	}
}

void Restaurant::CheckIfCooksBackFromBreak(int currStep)
{
	Node<Cook*>* Ncook;
	Node<Cook*>* H = pBusyNormalCook.getHead();//to travesre on the list
	while (H)
	{
		if (H->getItem()->getTimeBackToAvaList() == currStep) // this cook should back from break
		{
			Ncook = H;
			Ncook->getItem()->setTimeBackToAvaList(0);
			Ncook = RemoveAndGetCookByIdFromBNC(H->getItem()->GetID());
			pAvliableNormalCook.InsertEnd(Ncook->getItem());
		}
		H = H->getNext();
	}

	H = pBusyVeganCook.getHead();
	while (H)
	{
		if (H->getItem()->getTimeBackToAvaList() == currStep) // this cook should take a break
		{
			Ncook = H;
			Ncook->getItem()->setTimeBackToAvaList(0);
			Ncook = RemoveAndGetCookByIdFromBGC(H->getItem()->GetID());
			pAvliableVeganCook.InsertEnd(Ncook->getItem());
		}
		H = H->getNext();
	}

	H = pBusyVIPCook.getHead();
	while (H)
	{
		if (H->getItem()->getTimeBackToAvaList() == currStep) // this cook should take a break
		{
			Ncook = H;
			Ncook->getItem()->setTimeBackToAvaList(0);
			Ncook = RemoveAndGetCookByIdFromBVC(H->getItem()->GetID());
			pAvliableVIPCook.InsertEnd(Ncook->getItem());
		}
		H = H->getNext();
	}
}

void Restaurant::checkAutoPromote(int currStep)
{
	Node<Order*>*H = NRM.getHead();
	while (H)
	{
		if (H->getItem()->GetAT()+APL <= currStep)//this mean this order should be move to VIP orders
		{
			H->getItem()->SetType(TYPE_VIP);
			VIP.insert(deleteOrderId(H->getItem()->GetID())->getItem());
		}
		H = H->getNext();
	}

}

void Restaurant::HandleWithFinshedOrders(int currtime)
{
	Node<Cook*>* Ncook;
	Node<Cook*>* H = pBusyNormalCook.getHead();//to travesre on the list
	while (H)
	{
		if (H->getItem()->getTimeFinshOrder() == currtime&& H->getItem()->getOrderThatWorkedAt()) // this cook should take a break
		{
			H->getItem()->getOrderThatWorkedAt()->setStatus(DONE); // make order done or finshed
			FinshOrders.InsertEnd(H->getItem()->getOrderThatWorkedAt());// insert order to list finshed
			RemoveAndGetOrderByIdFromServeOrderList(H->getItem()->getOrderThatWorkedAt()->GetID());//remove the order form severing list
			Ncook = RemoveAndGetCookByIdFromBNC(H->getItem()->GetID()); // get the cook
			Ncook->getItem()->setTimeFinshOrder(0);//reset time finshed to assin to new order
			Ncook->getItem()->setOrderThatWorkedAt(NULL);// assin null order to cook
			Ncook->getItem()->setServingOrder(Ncook->getItem()->getServingOrder() + 1); //increse num of finshed orders to this cook
			pAvliableNormalCook.InsertEnd(Ncook->getItem()); // the cook should back to avaliable
		}
		H = H->getNext();
	}

	H = pBusyVeganCook.getHead();
	while (H)
	{
		if (H->getItem()->getTimeFinshOrder() == currtime && H->getItem()->getOrderThatWorkedAt()) // this cook should take a break
		{
			H->getItem()->getOrderThatWorkedAt()->setStatus(DONE);
			FinshOrders.InsertEnd(H->getItem()->getOrderThatWorkedAt());// insert order to list finshed
			RemoveAndGetOrderByIdFromServeOrderList(H->getItem()->getOrderThatWorkedAt()->GetID());//remove the order form severing list
			Ncook = RemoveAndGetCookByIdFromBGC(H->getItem()->GetID());
			Ncook->getItem()->setTimeFinshOrder(0);//reset time finshed to assin to new order
			Ncook->getItem()->setOrderThatWorkedAt(NULL);// assin null order to cook
			Ncook->getItem()->setServingOrder(Ncook->getItem()->getServingOrder() + 1); //increse num of finshed orders to this cook
			pAvliableVeganCook.InsertEnd(Ncook->getItem());
		}
		H = H->getNext();
	}

	H = pBusyVIPCook.getHead();
	while (H)
	{
		if (H->getItem()->getTimeFinshOrder() == currtime && H->getItem()->getOrderThatWorkedAt()) // this cook should take a break
		{
			H->getItem()->getOrderThatWorkedAt()->setStatus(DONE);
			FinshOrders.InsertEnd(H->getItem()->getOrderThatWorkedAt());// insert order to list finshed
			RemoveAndGetOrderByIdFromServeOrderList(H->getItem()->getOrderThatWorkedAt()->GetID());//remove the order form severing list
			Ncook = RemoveAndGetCookByIdFromBVC(H->getItem()->GetID());
			Ncook->getItem()->setTimeFinshOrder(0);//reset time finshed to assin to new order
			Ncook->getItem()->setOrderThatWorkedAt(NULL);// assin null order to cook
			Ncook->getItem()->setServingOrder(Ncook->getItem()->getServingOrder() + 1); //increse num of finshed orders to this cook
			pAvliableVIPCook.InsertEnd(Ncook->getItem());
		}
		H = H->getNext();
	}
}

void Restaurant::StepByStepMode()
{
	int CurrentTimeStep = 1;


	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty()||!VIP.isEmpty()||!NRM.isEmpty()||!VGN.isEmpty()||!ServeOrders.isEmpty())
	{
		//print current timestep
		//char timestep[10];
		//itoa(CurrentTimeStep, timestep, 10);
		//string timestep = "TS: " + to_string(CurrentTimeStep);
		//pGUI->PrintMessage(timestep);
		//string NumberOfWaitingOrderN = "Num Of Waiting Normal Orders: " + to_string(NRM.getSize()) + " Num Of Waiting Vegan Orders: " + to_string(VGN.getSize()) + " Num Of Waiting VIP Orders: " + to_string(VIP.getCount());
		//string arr[] = { timestep ,NumberOfWaitingOrderN };
		
		// 1 - execute events int this time step
		ExecuteEvents(CurrentTimeStep); 

		// 2 - take the cooks Break if thay deserve it :V
		CheckIfCooksTakeBreak(CurrentTimeStep); //take break
		CheckIfCooksBackFromBreak(CurrentTimeStep);//back from break


		checkAutoPromote(CurrentTimeStep);


		
		//3 - assin order  to cook
		Order* ord=NULL;
		Cook* cook=NULL;
		string SEV = "";
		if(!VIP.isEmpty()) // serve vip first
		{
			while (!pAvliableVIPCook.isEmpty()&& !VIP.isEmpty()) // first VIP cooks
			{
				//VIP.peak(ord);// get the order that will be serve
				VIP.pop(ord);
				ord->setStatus(SRV);
				cook=pAvliableVIPCook.Deletefirst()->getItem(); // get any avaliable VIP cook
				if (cook)
				{
					SEV += "V" + to_string(cook->GetID()) + "(V" + to_string( ord->GetID() )+ ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyVIPCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}

			// if not avaliable vip cook , we take form the normal and vagen cooks 
			while (!pAvliableNormalCook.isEmpty() && !VIP.isEmpty())
			{
				VIP.pop(ord); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableNormalCook.Deletefirst()->getItem(); // get any avaliable NRm cook
				if (cook)
				{
					SEV += "N" + to_string(cook->GetID()) + "(V" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyNormalCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}
			while (!pAvliableVeganCook.isEmpty() && !VIP.isEmpty())
			{
				VIP.pop(ord); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableVeganCook.Deletefirst()->getItem(); // get any avaliable VGN cook
				if (cook)
				{
					SEV += "G" + to_string(cook->GetID()) + "(V" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyVeganCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}
			
		}
		// 2 serve Vegan orders
		if (!VGN.isEmpty())
		{
			while (!pAvliableVeganCook.isEmpty() && !VGN.isEmpty())
			{
				VGN.dequeue(ord); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableVeganCook.Deletefirst()->getItem(); // get any avaliable VGN cook
				if (cook)
				{
					SEV += "G" + to_string(cook->GetID()) + "(G" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyVeganCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}
		}
		// 3 
		if (!NRM.isEmpty())
		{
			while (!pAvliableNormalCook.isEmpty() && !NRM.isEmpty())
			{
				ord = NRM.Deletefirst()->getItem(); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableNormalCook.Deletefirst()->getItem(); // get any avaliable NRm cook
				if (cook)
				{
					SEV += "N" + to_string(cook->GetID()) + "(N" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyNormalCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}
			while (!pAvliableVIPCook.isEmpty() && !NRM.isEmpty())
			{
				ord = NRM.Deletefirst()->getItem(); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableVIPCook.Deletefirst()->getItem(); // get any avaliable VIP cook
				if (cook)
				{
					SEV += "V" + to_string(cook->GetID()) + "(N" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed())+CurrentTimeStep); //calc time will be finshed
					pBusyVIPCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}
		}


		// 4 - check handle with finsh order
		HandleWithFinshedOrders(CurrentTimeStep);

		
		// Print Cooks id
		Cook* cok;
		Node<Cook*>* H = pAvliableNormalCook.getHead();//to travesre on the list
		for (int i = 0; i < CooksNum[0]&&H; i++)
		{
			cok = H->getItem();
			pGUI->AddToDrawingList(cok);
			H = H->getNext();
		}

		H = pAvliableVeganCook.getHead();//to travesre on the list
		for (int i = 0; i < CooksNum[1] && H; i++)
		{
			cok = H->getItem();
			pGUI->AddToDrawingList(cok);
			H = H->getNext();
		}

		H = pAvliableVIPCook.getHead();//to travesre on the list
		for (int i = 0; i < CooksNum[2] && H; i++)
		{
			cok = H->getItem();
			pGUI->AddToDrawingList(cok);
			H = H->getNext();
		}
		// end of Print id cooks

		// print id of waiting orders
		int size = 0;
		Order* pOrd;
		Order** VIPOrders = VIP.toArray(size);
		for (int i = 0; i < size; i++)
		{
			pOrd = VIPOrders[i];
			pGUI->AddToDrawingList(pOrd);
		}
		size = 0;
		
		Order** Vegan_Orders_Array = VGN.toArray(size);

		for (int i = 0; i < size; i++)
		{
			pOrd = Vegan_Orders_Array[i];
			pGUI->AddToDrawingList(pOrd);
		}
		Node<Order*>*h = NRM.getHead();
		while (h)
		{
			pGUI->AddToDrawingList(h->getItem());
			h = h->getNext();
		}
		// print id of waiting orders

		

		// print id of sever orders
		h = ServeOrders.getHead();
		while (h)
		{
			pGUI->AddToDrawingList(h->getItem());
			h = h->getNext();
		}

		// print id of sever orders
		// print id of done orders
		h = FinshOrders.getHead();
		while (h)
		{
			pGUI->AddToDrawingList(h->getItem());
			h = h->getNext();
		}
		// print id of done orders
		string timestep = "TS: " + to_string(CurrentTimeStep);
		pGUI->PrintMessage(timestep);
		string NumberOfWaitingOrders = "Num Of Waiting Normal Orders: " + to_string(NRM.getSize()) + " ,Num Of Waiting Vegan Orders: " + to_string(VGN.getSize()) + " ,Num Of Waiting VIP Orders: " + to_string(VIP.getCount());
		string NumberOfAvalibeCooks = "Num available Normal cooks: " + to_string(pAvliableNormalCook.getSize()) + " ,Num available Vegan cooks: " + to_string(pAvliableVeganCook.getSize()) + " ,Num available VIP cooks: " + to_string(pAvliableVIPCook.getSize());
		string NumberServingOrders = "Num served Normal Orders: " + to_string(numServNOrder) + " ,Num served Vegan Orders: " + to_string(numServGOrder) + " ,Num served VIP Orders: " + to_string(numServVOrder);
		string arr[] = { timestep ,NumberOfWaitingOrders, NumberOfAvalibeCooks,SEV, NumberServingOrders };
		pGUI->PrintMessage(arr, 5);
		pGUI->UpdateInterface();
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
	}
	ReturnOutput();
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();
}

void Restaurant::InteractiveMode()
{

	int CurrentTimeStep = 1;


	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty() || !VIP.isEmpty() || !NRM.isEmpty() || !VGN.isEmpty() || !ServeOrders.isEmpty())
	{
		//print current timestep
		//char timestep[10];
		//itoa(CurrentTimeStep, timestep, 10);
		//string timestep = "TS: " + to_string(CurrentTimeStep);
		//pGUI->PrintMessage(timestep);
		//string NumberOfWaitingOrderN = "Num Of Waiting Normal Orders: " + to_string(NRM.getSize()) + " Num Of Waiting Vegan Orders: " + to_string(VGN.getSize()) + " Num Of Waiting VIP Orders: " + to_string(VIP.getCount());
		//string arr[] = { timestep ,NumberOfWaitingOrderN };

		// 1 - execute events int this time step
		ExecuteEvents(CurrentTimeStep);

		// 2 - take the cooks Break if thay deserve it :V
		CheckIfCooksTakeBreak(CurrentTimeStep); //take break
		CheckIfCooksBackFromBreak(CurrentTimeStep);//back from break


		checkAutoPromote(CurrentTimeStep);



		//3 - assin order  to cook
		Order* ord = NULL;
		Cook* cook = NULL;
		string SEV = "";
		if (!VIP.isEmpty()) // serve vip first
		{
			while (!pAvliableVIPCook.isEmpty() && !VIP.isEmpty()) // first VIP cooks
			{
				//VIP.peak(ord);// get the order that will be serve
				VIP.pop(ord);
				ord->setStatus(SRV);
				cook = pAvliableVIPCook.Deletefirst()->getItem(); // get any avaliable VIP cook
				if (cook)
				{
					SEV += "V" + to_string(cook->GetID()) + "(V" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyVIPCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}

			// if not avaliable vip cook , we take form the normal and vagen cooks 
			while (!pAvliableNormalCook.isEmpty() && !VIP.isEmpty())
			{
				VIP.pop(ord); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableNormalCook.Deletefirst()->getItem(); // get any avaliable NRm cook
				if (cook)
				{
					SEV += "N" + to_string(cook->GetID()) + "(V" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyNormalCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}
			while (!pAvliableVeganCook.isEmpty() && !VIP.isEmpty())
			{
				VIP.pop(ord); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableVeganCook.Deletefirst()->getItem(); // get any avaliable VGN cook
				if (cook)
				{
					SEV += "G" + to_string(cook->GetID()) + "(V" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyVeganCook.InsertEnd(cook); //move the cook to busy
				}
			}

		}
		// 2 serve Vegan orders
		if (!VGN.isEmpty())
		{
			while (!pAvliableVeganCook.isEmpty() && !VGN.isEmpty())
			{
				VGN.dequeue(ord); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableVeganCook.Deletefirst()->getItem(); // get any avaliable VGN cook
				if (cook)
				{
					SEV += "G" + to_string(cook->GetID()) + "(G" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyVeganCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}
		}
		// 3 
		if (!NRM.isEmpty())
		{
			while (!pAvliableNormalCook.isEmpty() && !NRM.isEmpty())
			{
				ord = NRM.Deletefirst()->getItem(); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableNormalCook.Deletefirst()->getItem(); // get any avaliable NRm cook
				if (cook)
				{
					SEV += "N" + to_string(cook->GetID()) + "(N" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyNormalCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}
			while (!pAvliableVIPCook.isEmpty() && !NRM.isEmpty())
			{
				ord = NRM.Deletefirst()->getItem(); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableVIPCook.Deletefirst()->getItem(); // get any avaliable VIP cook
				if (cook)
				{
					SEV += "V" + to_string(cook->GetID()) + "(N" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyVIPCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}
		}


		// 4 - check handle with finsh order
		HandleWithFinshedOrders(CurrentTimeStep);


		// Print Cooks id
		Cook* cok;
		Node<Cook*>* H = pAvliableNormalCook.getHead();//to travesre on the list
		for (int i = 0; i < CooksNum[0] && H; i++)
		{
			cok = H->getItem();
			pGUI->AddToDrawingList(cok);
			H = H->getNext();
		}

		H = pAvliableVeganCook.getHead();//to travesre on the list
		for (int i = 0; i < CooksNum[1] && H; i++)
		{
			cok = H->getItem();
			pGUI->AddToDrawingList(cok);
			H = H->getNext();
		}

		H = pAvliableVIPCook.getHead();//to travesre on the list
		for (int i = 0; i < CooksNum[2] && H; i++)
		{
			cok = H->getItem();
			pGUI->AddToDrawingList(cok);
			H = H->getNext();
		}
		// end of Print id cooks

		// print id of waiting orders
		int size = 0;
		Order* pOrd;
		Order** VIPOrders = VIP.toArray(size);
		for (int i = 0; i < size; i++)
		{
			pOrd = VIPOrders[i];
			pGUI->AddToDrawingList(pOrd);
		}
		size = 0;

		Order** Vegan_Orders_Array = VGN.toArray(size);

		for (int i = 0; i < size; i++)
		{
			pOrd = Vegan_Orders_Array[i];
			pGUI->AddToDrawingList(pOrd);
		}
		Node<Order*>* h = NRM.getHead();
		while (h)
		{
			pGUI->AddToDrawingList(h->getItem());
			h = h->getNext();
		}
		// print id of waiting orders



		// print id of sever orders
		h = ServeOrders.getHead();
		while (h)
		{
			pGUI->AddToDrawingList(h->getItem());
			h = h->getNext();
		}

		// print id of sever orders
		// print id of done orders
		h = FinshOrders.getHead();
		while (h)
		{
			pGUI->AddToDrawingList(h->getItem());
			h = h->getNext();
		}
		// print id of done orders
		string timestep = "TS: " + to_string(CurrentTimeStep);
		pGUI->PrintMessage(timestep);
		string NumberOfWaitingOrders = "Num Of Waiting Normal Orders: " + to_string(NRM.getSize()) + " ,Num Of Waiting Vegan Orders: " + to_string(VGN.getSize()) + " ,Num Of Waiting VIP Orders: " + to_string(VIP.getCount());
		string NumberOfAvalibeCooks = "Num available Normal cooks: " + to_string(pAvliableNormalCook.getSize()) + " ,Num available Vegan cooks: " + to_string(pAvliableVeganCook.getSize()) + " ,Num available VIP cooks: " + to_string(pAvliableVIPCook.getSize());
		string NumberServingOrders = "Num served Normal Orders: " + to_string(numServNOrder) + " ,Num served Vegan Orders: " + to_string(numServGOrder) + " ,Num served VIP Orders: " + to_string(numServVOrder);
		string arr[] = { timestep ,NumberOfWaitingOrders, NumberOfAvalibeCooks,SEV, NumberServingOrders };
		pGUI->PrintMessage(arr, 5);
		pGUI->UpdateInterface();
		pGUI->waitForClick();
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
	}
	ReturnOutput();
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();
}

void Restaurant::SilentMode()
{
	int CurrentTimeStep = 1;


	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty() || !VIP.isEmpty() || !NRM.isEmpty() || !VGN.isEmpty() || !ServeOrders.isEmpty())
	{
		//print current timestep
		//char timestep[10];
		//itoa(CurrentTimeStep, timestep, 10);
		//string timestep = "TS: " + to_string(CurrentTimeStep);
		//pGUI->PrintMessage(timestep);
		//string NumberOfWaitingOrderN = "Num Of Waiting Normal Orders: " + to_string(NRM.getSize()) + " Num Of Waiting Vegan Orders: " + to_string(VGN.getSize()) + " Num Of Waiting VIP Orders: " + to_string(VIP.getCount());
		//string arr[] = { timestep ,NumberOfWaitingOrderN };

		// 1 - execute events int this time step
		ExecuteEvents(CurrentTimeStep);

		// 2 - take the cooks Break if thay deserve it :V
		CheckIfCooksTakeBreak(CurrentTimeStep); //take break
		CheckIfCooksBackFromBreak(CurrentTimeStep);//back from break


		checkAutoPromote(CurrentTimeStep);



		//3 - assin order  to cook
		Order* ord = NULL;
		Cook* cook = NULL;
		string SEV = "";
		if (!VIP.isEmpty()) // serve vip first
		{
			while (!pAvliableVIPCook.isEmpty() && !VIP.isEmpty()) // first VIP cooks
			{
				//VIP.peak(ord);// get the order that will be serve
				VIP.pop(ord);
				ord->setStatus(SRV);
				cook = pAvliableVIPCook.Deletefirst()->getItem(); // get any avaliable VIP cook
				if (cook)
				{
					SEV += "V" + to_string(cook->GetID()) + "(V" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyVIPCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}

			// if not avaliable vip cook , we take form the normal and vagen cooks 
			while (!pAvliableNormalCook.isEmpty() && !VIP.isEmpty())
			{
				VIP.pop(ord); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableNormalCook.Deletefirst()->getItem(); // get any avaliable NRm cook
				if (cook)
				{
					SEV += "N" + to_string(cook->GetID()) + "(V" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyNormalCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}
			while (!pAvliableVeganCook.isEmpty() && !VIP.isEmpty())
			{
				VIP.pop(ord); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableVeganCook.Deletefirst()->getItem(); // get any avaliable VGN cook
				if (cook)
				{
					SEV += "G" + to_string(cook->GetID()) + "(V" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyVeganCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}

		}
		// 2 serve Vegan orders
		if (!VGN.isEmpty())
		{
			while (!pAvliableVeganCook.isEmpty() && !VGN.isEmpty())
			{
				VGN.dequeue(ord); // get the order that will be serve
				 
				cook = pAvliableVeganCook.Deletefirst()->getItem(); // get any avaliable VGN cook
				if (cook)
				{
					SEV += "G" + to_string(cook->GetID()) + "(G" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyVeganCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}
		}
		// 3 
		if (!NRM.isEmpty())
		{
			while (!pAvliableNormalCook.isEmpty() && !NRM.isEmpty())
			{
				ord = NRM.Deletefirst()->getItem(); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableNormalCook.Deletefirst()->getItem(); // get any avaliable NRm cook
				if (cook)
				{
					SEV += "N" + to_string(cook->GetID()) + "(N" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyNormalCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}
			while (!pAvliableVIPCook.isEmpty() && !NRM.isEmpty())
			{
				ord = NRM.Deletefirst()->getItem(); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableVIPCook.Deletefirst()->getItem(); // get any avaliable VIP cook
				if (cook)
				{
					SEV += "V" + to_string(cook->GetID()) + "(N" + to_string(ord->GetID()) + ") , ";
					cook->setOrderThatWorkedAt(ord); // assin order to cook
					addToServeOrder(ord);//add to sereving orders list
					cook->setTimeFinshOrder(ceil(ord->GetSize() / cook->getSpeed()) + CurrentTimeStep); //calc time will be finshed
					pBusyVIPCook.InsertEnd(cook); //move the cook to busy

					ord->setWaitTime(CurrentTimeStep - ord->GetAT());
					ord->setServTime(ceil(ord->GetSize() / cook->getSpeed()));
					ord->setFinishTime(ord->GetAT() + ord->getWaitTime() + ord->getServTime());	//shouldn't setTimeFinshOrder use the same equation??
				}
			}
		}


		// 4 - check handle with finsh order
		HandleWithFinshedOrders(CurrentTimeStep);
		CurrentTimeStep++;
	}
	ReturnOutput();
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();
}


void Restaurant::ReturnOutput()
{
	Node<Order*>* curFinishedOrder = FinshOrders.getHead();
	ofstream OutputFile("SampleOutput.txt");
	OutputFile << "FT	" << "ID	" << "AT	" << "WT	" << "ST	" << endl;
	while (curFinishedOrder)
	{
		OutputFile << curFinishedOrder->getItem()->getFinishTime() << "	" << curFinishedOrder->getItem()->GetID() << "	" << curFinishedOrder->getItem()->GetAT()
			<< "	" << curFinishedOrder->getItem()->getWaitTime() << "	" << curFinishedOrder->getItem()->getServTime() << "	" << endl;
		curFinishedOrder = curFinishedOrder->getNext();

		//orders need to be sorted accodring to Serving time
	}
	OutputFile << "Orders: " << FinshOrders.getSize() << "	[Norm: " << numNormalOrders << ", Veg: " << numVeganOrders << ", VIP: " << numVIPOrders <<"]"<< endl;

	OutputFile << "Cooks: " << CooksNum[0] + CooksNum[1] + CooksNum[2] << "	[Norm: " << CooksNum[0] << ", Veg: " << CooksNum[1] << ", VIP: " << CooksNum[2] <<"]"<< endl;
	//need to add no of injured cooks

	OutputFile << "Avg Wait= " << AverageWaitingTime() << "	Avg Serv= " << AverageServingTime() << endl;

	//last line needs urgent orders and number of auto promoted orders
	OutputFile.close();
}

float Restaurant::AverageWaitingTime()
{
	Node<Order*>* cur = FinshOrders.getHead();
	float totalwait=0; 
	while (cur)
	{
		totalwait += cur->getItem()->getWaitTime();
		cur = cur->getNext();
	}
	return totalwait / FinshOrders.getSize();
}

float Restaurant::AverageServingTime()
{
	Node<Order*>* cur = FinshOrders.getHead();
	float totalserv = 0;
	while (cur)
	{
		totalserv += cur->getItem()->getServTime();
		cur = cur->getNext();
	}
	return totalserv / FinshOrders.getSize();

}