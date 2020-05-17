#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\LinkedList.h"
#include "..\MaxHEAP.h"
#include "..\Events\Event.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancelEvent.h"
#include "..\Events\PromoteEvent.h"
#include "string"  //25/3
#include <fstream> //25/3
#include "Order.h"

// it is the maestro of the project
class Restaurant
{
private:
	GUI* pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file

	//LinkedList<Order*> OrdersList; //Gaser
	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	LinkedList<Order*> NRM;
	//		    			       \||||||||||||||||/
	MaxHEAP<Order*> VIP;	/// ->>>|Priority Queue|<<<-
	//		    			       /||||||||||||||||\ 
	Queue<Order*> VGN;	//Important: This is just for demo
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo



	Cook* pNormalCook;
	Cook* pVeganCook;
	Cook* pVIPCook;

	//gaser
	LinkedList<Cook*>pAvliableNormalCook;
	LinkedList<Cook*>pAvliableVeganCook;
	LinkedList<Cook*>pAvliableVIPCook;

	LinkedList<Cook*>pBusyNormalCook;
	LinkedList<Cook*>pBusyVeganCook;
	LinkedList<Cook*>pBusyVIPCook;


	

	//Gamal 17/5
	int CooksNum[3]; //25/3		
	/*int CooksSpd[3]; //25/3	//cant work with these anymore since each individual cook
	int CooksBrk[4]; //25/3*/	// has different speed and break time
	int APL;
	//
	// TODO: Add More Data Members As Needed
	//



	int minSpeeds[3];	//an array for minimum speeds for each type: 0 for normal, 1 for vegan, 2 for VIP
	int maxSpeeds[3];	//an array for maximum speeds for each type: 0 for normal, 1 for vegan, 2 for VIP	

	int BO;	//numers of dishes done before a break
	int minBreakTime[3];	//arrarys for min and max break time for each type
	int maxBreaktime[3];
	
	int injuryProbability;
	int restPeriod;

	int VIPtoUrgent;


public:
	
	Restaurant();
	~Restaurant();
	
	Node<Order*>* getOrdersListHead(); //Gaser
	void setHeadToOrdersList(Node<Order*>* temp); //Gaser
	Node<Order*>* deleteOrderId(int id);
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	void ReadInput(string FileName); // 25/3

	void FillDrawingList();

	//
	// TODO: Add More Member Functions As Needed
	//
	void addOrderToNrm(Order* O);
	void addOrderToVip(Order* O);
	void addOrderToVgn(Order* O);



	//gaser
	bool isAvliableNormalCooks();
	bool isAvliableVeganCooks();
	bool isAvliableVIPCooks();

	void addToAvNorCook(Cook* c);
	void addToAvVaCook(Cook* c);
	void addToAvVIPCook(Cook* c);
	void addToBuNorCook(Cook* c);
	void addToBuVaCook(Cook* c);
	void addToVuVIPCook(Cook* c);

	Node<Cook*>*RemoveAndGetCookByIdFromANC(int id);
	Node<Cook*>*RemoveAndGetCookByIdFromAGC(int id);
	Node<Cook*>*RemoveAndGetCookByIdFromAVC(int id);
	Node<Cook*>*RemoveAndGetCookByIdFromBNC(int id);
	Node<Cook*>*RemoveAndGetCookByIdFromBGC(int id);
	Node<Cook*>*RemoveAndGetCookByIdFromBVC(int id);


	void CheckIfCooksTakeBreak();

	//start modes
	void StepByStepMode();

	//end modes


/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue

/// ================================================================================================== 



};

#endif