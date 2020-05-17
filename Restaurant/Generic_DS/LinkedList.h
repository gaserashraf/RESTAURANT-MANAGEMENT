#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
#include<iostream>
using namespace std;

template <typename T>
class LinkedList
{
private:
	Node<T> *Head;	//Pointer to the head of the list
	Node<T>* tail;//You can add tail pointer too (depending on your problem)
public:


	LinkedList()
	{
		Head = tail = NULL;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll(); 
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	Node<T>*getHead()
	{
		return Head;
	}
	void setHead(Node<T>*temp)
	{
		Head = temp;
	}
	bool isEmpty()
	{
		return Head==0;
	}
	void PrintList()	
	{		
		cout<<"\nprinting list contents:\n\n";
		Node<T> *p = Head;

		while(p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "NULL\n";
	}
	
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	* 
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}



	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data)
	{
		Node<T>* newNode = new Node<T>(data);
		//newNode->setItem(T);
		if (isEmpty())
		{
			Head = tail = newNode;
			tail->setNext(NULL);
		}
		else
		{
			tail->setNext(newNode);
			tail = newNode;
		}
	}

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(T Key)
	{
		Node<T>* temp = Head;
		while (temp)
		{
			if (temp->getItem() == Key)
				return 1;
			temp = temp->getNext();
		}
		return 0;
	}
	//template<class Dictionary>
//	bool Find(char Key); //for f);

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value)
	{
		int c = 0;
		Node<T>* temp = Head;
		while (temp)
		{
			if (temp->getItem() == value)
				c++;
			temp=(temp->getNext());
		}
		return c;
	}

	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst()
	{
		Node<T>* temp = Head;
		Head = Head->getNext();
		temp->setNext(NULL);
		delete temp;
	}
	Node<T>* Deletefirst()
	{
		Node<T>* temp = Head;
		Head = Head->getNext();
		temp->setNext(NULL);
		return temp;
	}


	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast()
	{
		Node<T>* prev = Head, * temp=Head->getNext();
		while (temp->getNext())
		{
			prev = temp;
			temp = temp->getNext();
		}
		delete temp;
		tail = prev;
		tail->setNext(NULL);
	}
	Node<T>* Deletelast()
	{
		Node<T>* prev = Head, * temp = Head->getNext();
		while (temp->getNext())
		{
			prev = temp;
			temp = temp->getNext();
		}
		tail = prev;
		tail->setNext(NULL);
		return temp;
	}

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T& value)
	{
		if (value == Head->getItem())
			DeleteFirst();
		else if (value == tail->getItem())
			DeleteLast();

		else
		{
			Node<T>* prev = Head, * temp = Head->getNext();
			while (temp)
			{
				if (temp->getItem() == value)
					break;
				prev = temp;
				temp = temp->getNext();
			}
			if (temp)
			{
				prev->setNext(temp->getNext());
				delete temp;
				return 1;
			}
		}
		return 0;
	}

	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T& value)
	{
		int n = CountOccurance(value);
		if (n == 0)
			return 0;
		for (int i = 0; i < n; i++)
		{
			DeleteNode(value);
		}
		return 1;
		
	}

	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	void Merge(const LinkedList& L)
	{
		tail->setNext(L.Head);
	}

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse()
	{
		Node<T>* prev = NULL, * temp = Head;
		while (temp)
		{
			temp = temp->getNext();
			Head->setNext(prev);
			prev = Head;
			if(temp)
				Head = temp;
		}


	}
	Node<Order*>* DeleteNodeId(int id);
	Node<Cook*>* RemoveCookFromListWithOutDelete(int id);
};

template<>
void LinkedList<Order*>::PrintList()
{
	cout << "\nprinting list contents:\n\n";
	Node<Order*>* p = Head;

	while (p)
	{
		cout << "[ " << p->getItem()->GetID() << " ]";
		cout << "--->";
		p = p->getNext();
	}
	cout << "NULL\n";
}

#endif

template<>
inline Node<Order*>* LinkedList<Order*>::DeleteNodeId(int id)
{
	if (id == Head->getItem()->GetID())
		return Deletefirst();
	else if (id == tail->getItem()->GetID())
		return Deletelast();

	else
	{
		Node<Order*>* prev = Head, * temp = Head->getNext();
		while (temp)
		{
			if (temp->getItem()->GetID() == id)
				break;
			prev = temp;
			temp = temp->getNext();
		}
		if (temp)
		{
			prev->setNext(temp->getNext());
			//delete temp;
			return temp;
		}
	}
	return NULL;
}
template<>
inline Node<Cook*>* LinkedList<Cook*>::RemoveCookFromListWithOutDelete(int id)
{
	if (id == Head->getItem()->GetID())
		return Deletefirst();
	else if (id == tail->getItem()->GetID())
		return Deletelast();

	else
	{
		Node<Cook*>* prev = Head, * temp = Head->getNext();
		while (temp)
		{
			if (temp->getItem()->GetID() == id)
				break;
			prev = temp;
			temp = temp->getNext();
		}
		if (temp)
		{
			prev->setNext(temp->getNext());
			//delete temp;
			return temp;
		}
	}
	return NULL;
}
