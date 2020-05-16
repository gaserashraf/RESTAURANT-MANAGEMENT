#pragma once
#include "../Rest/Order.h"


template<typename T>
class WeightedNode
{
private:
	double weight;
	T item; // A data item
	WeightedNode<T>* left; // Pointer to next node
	WeightedNode<T>* right; // Pointer to next node
	void CalcWeight();
public:
	WeightedNode()
	{
		left = nullptr;
		right = nullptr;
		weight = 0;
	}

	WeightedNode(T newItem, WeightedNode<T>* leftNodePtr = nullptr, WeightedNode<T>* rightttNodePtr = nullptr)
	{
		item = newItem;
		left = leftNodePtr;
		right = rightttNodePtr;
		CalcWeight();
	}


	void setItem(const T& r_Item)
	{
		item = r_Item;
	}

	void setLeft(WeightedNode<T>* lefttNodePtr = nullptr)
	{
		left = lefttNodePtr;
	}

	void setRight(WeightedNode<T>* rightNodePtr = nullptr)
	{
		right = rightNodePtr;
	}

	T getItem() const
	{
		return item;
	}

	WeightedNode<T>* getLeft() const
	{
		return left;
	}

	WeightedNode<T>* getRight() const
	{
		return right;
	}

	void setWeight(double ManWeight)
	{
		weight = ManWeight;
	} // end setItem


	double getWeight() const
	{
		return weight;
	} // end getItem

};
template<>
void WeightedNode<Order>::CalcWeight()
{
	Order O = getItem();
	if (O.GetAT() == 0 || O.GetSize() == 0)
		weight = 0;
	else
		weight = O.GetMoney() / O.GetSize() / O.GetAT();
}