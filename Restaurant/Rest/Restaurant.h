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


	int CooksNum[3]; //25/3
	int CooksSpd[3]; //25/3
	int CooksBrk[4]; //25/3
	int APL;
	//
	// TODO: Add More Data Members As Needed
	//

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


/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue

/// ================================================================================================== 



};

#endif