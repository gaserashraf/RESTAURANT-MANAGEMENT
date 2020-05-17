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
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE mode = pGUI->getGUIMode();
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
	{
		string File;
		cin >> File;
		ReadInput(File);
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
	delete[]pNormalCook;	//added
	delete[]pVeganCook;
	delete[]pVIPCook;
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



void Restaurant::FillDrawingList()
{
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);

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
		addToAvNorCook(newCook);

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
		addToAvVaCook(newCook);
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
		addToAvVIPCook(newCook);
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
				break;
			case 'V':
				ORD = TYPE_VIP;
				break;
			case 'G':
				ORD = TYPE_VGAN;
				break;
			}
			EventB = new ArrivalEvent(AT, ID, ORD, Size, Money);
			Order OrderX(ID, ORD, AT, Size, Money);
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
		EventB->Execute(this);
		/// NOT COMPLETED

	}
	NRM.PrintList();
	VIP.printAsTree();

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

void Restaurant::CheckIfCooksTakeBreak()
{
	int bo = 0;
	Node<Cook*>* Ncook;
	Node<Cook*> *H = pAvliableNormalCook.getHead();//to travesre on the list
	while (H)
	{	
		if (H->getItem()->getServingOrder() == bo) // this cook should take a break
		{
			Ncook = RemoveAndGetCookByIdFromANC(H->getItem()->GetID());
			pBusyNormalCook.InsertEnd(Ncook->getItem());
		}
		H = H->getNext();
	}

	H = pAvliableVeganCook.getHead();
	while (H)
	{
		if (H->getItem()->getServingOrder() == bo) // this cook should take a break
		{
			Ncook = RemoveAndGetCookByIdFromAVC(H->getItem()->GetID());
			pBusyVeganCook.InsertEnd(Ncook->getItem());
		}
		H = H->getNext();
	}

	H = pAvliableVIPCook.getHead();
	while (H)
	{
		if (H->getItem()->getServingOrder() == bo) // this cook should take a break
		{
			Ncook = RemoveAndGetCookByIdFromAVC(H->getItem()->GetID());
			pBusyVIPCook.InsertEnd(Ncook->getItem());
		}
		H = H->getNext();
	}
}

void Restaurant::StepByStepMode()
{
	int CurrentTimeStep = 1;


	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);



		ExecuteEvents(CurrentTimeStep); // 1 execute events int this time step


		CheckIfCooksTakeBreak(); // 2 take the cooks Break if thay deserve it :V


		
		//3 assin order  to cook
		Order* ord;
		Cook* cook;
		if(!VIP.isEmpty()) // serve vip first
		{
			while (!pAvliableVIPCook.isEmpty()&& !VIP.isEmpty()) // first VIP cooks
			{
				VIP.peak(ord); // get the order that will be serve
				ord->setStatus(SRV);
				cook=pAvliableVIPCook.Deletefirst()->getItem(); // get any avaliable VIP cook
				cook->setOrderThatWorkedAt(ord); // assin order to cook
				cook->setServingOrder(ceil(ord->GetSize() / cook->getSpeed())); //calc time will be finshed
				pBusyVIPCook.InsertEnd(cook); //move the cook to busy
			}

			// if not avaliable vip cook , we take form the normal and vagen cooks 
			while (!pAvliableNormalCook.isEmpty() && !VIP.isEmpty())
			{
				VIP.peak(ord); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableNormalCook.Deletefirst()->getItem(); // get any avaliable NRm cook
				cook->setOrderThatWorkedAt(ord); // assin order to cook
				cook->setServingOrder(ceil(ord->GetSize() / cook->getSpeed())); //calc time will be finshed
				pBusyNormalCook.InsertEnd(cook); //move the cook to busy
			}
			while (!pAvliableVeganCook.isEmpty() && !VIP.isEmpty())
			{
				VIP.peak(ord); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableVeganCook.Deletefirst()->getItem(); // get any avaliable VGN cook
				cook->setOrderThatWorkedAt(ord); // assin order to cook
				cook->setServingOrder(ceil(ord->GetSize() / cook->getSpeed())); //calc time will be finshed
				pBusyVeganCook.InsertEnd(cook); //move the cook to busy
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
				cook->setOrderThatWorkedAt(ord); // assin order to cook
				cook->setServingOrder(ceil(ord->GetSize() / cook->getSpeed())); //calc time will be finshed
				pBusyVeganCook.InsertEnd(cook); //move the cook to busy
			}
		}
		if (!NRM.isEmpty())
		{
			while (!pAvliableNormalCook.isEmpty() && !NRM.isEmpty())
			{
				ord = NRM.Deletefirst()->getItem(); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableNormalCook.Deletefirst()->getItem(); // get any avaliable NRm cook
				cook->setOrderThatWorkedAt(ord); // assin order to cook
				cook->setServingOrder(ceil(ord->GetSize() / cook->getSpeed())); //calc time will be finshed
				pBusyNormalCook.InsertEnd(cook); //move the cook to busy
			}
			while (!pAvliableVIPCook.isEmpty() && !NRM.isEmpty())
			{
				ord = NRM.Deletefirst()->getItem(); // get the order that will be serve
				ord->setStatus(SRV);
				cook = pAvliableVIPCook.Deletefirst()->getItem(); // get any avaliable VIP cook
				cook->setOrderThatWorkedAt(ord); // assin order to cook
				cook->setServingOrder(ceil(ord->GetSize() / cook->getSpeed())); //calc time will be finshed
				pBusyVIPCook.InsertEnd(cook); //move the cook to busy
			}
			
		}
		pGUI->UpdateInterface();
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
	}

}
