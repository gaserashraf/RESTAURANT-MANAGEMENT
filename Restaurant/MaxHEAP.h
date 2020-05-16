#pragma once
#include <iostream>
#include "..\Rest\Order.h"
#include <iomanip>


template <typename T>
class MaxHEAP
{
private:
	T* Heap;
	int count;
	int capacity;

	void reAllocate()
	{
		capacity *= 2;
		T* NewHeap = new T[capacity];
		for (size_t i = 0; i < count; i++)
		{
			NewHeap[i] = Heap[i];
		}
		delete[]Heap;
		Heap = NewHeap;
	}

	void swap(int UpInd, int LowInd)
	{
		T temp = Heap[UpInd];
		Heap[UpInd] = Heap[LowInd];
		Heap[LowInd] = temp;
	}

public:
	MaxHEAP()
	{
		count = 0;
		capacity = 1000;
		Heap = new T[capacity];
	}

	MaxHEAP(int Capacity)
	{
		count = 0;
		if (capacity < 1)
			MaxHEAP();
		else
			Heap = new T[Capacity];
	}

	~MaxHEAP()
	{
		delete[]Heap;
	}

	bool isEmpty() const
	{
		return !count;
	}

	int getCount() const
	{
		return count;
	}

	int getCapacity() const
	{
		return capacity;
	}

	void insert(const T& item)
	{
		if (isEmpty())
		{
			count++;

			Heap[0] = item;
			return;
		}

		count++;

		if (count == capacity) reAllocate();

		Heap[count - 1] = item;

		int i = count - 1;

		while (i > 0)
		{
			if (Heap[(i - 1) / 2] < Heap[i])
			{
				swap(i, (i - 1) / 2);
				i = (i - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	bool peak(T& Contain)
	{
		if (isEmpty()) return false;

		Contain = Heap[0];
		return true;
	}

	bool pop(T& Contain)
	{
		if (isEmpty()) return false;

		count--;
		Contain = Heap[0];
		Heap[0] = Heap[count];
		int i = 0;
		while (true)
		{
			if (i + 1 >= count)
				break;
			else if (i + 2 >= count || Heap[i + 2] < Heap[i + 1])
			{
				if (Heap[i / 2] < Heap[i + 1])
				{
					swap(i / 2, i + 1);
					i = (i + 1) * 2;
				}
				else
				{
					break;
				}
			}
			else
			{
				if (Heap[i / 2] < Heap[i + 2])
				{
					swap(i / 2, i + 2);
					i = (i + 2) * 2;
				}
				else
				{
					break;
				}
			}
		}

		return true;
	}

	void print() const
	{
		for (size_t i = 0; i < count; i++)
		{
			std::cout << Heap[i] << " | ";
		}
		std::cout << std::endl;
	}
	void printAsTree() const
	{
		for (size_t i = 0; i < count; i++)
		{
			double log2 = log(i + 2) / log(2);
			if (log2 - floor(log2) < 1e-8)
			{
				std::cout << std::endl;
			}
			std::cout << Heap[i] << " | ";
		}
		std::cout << std::endl;
	}
};

template <>
class MaxHEAP<Order*>
{
private:
	Order** Heap;
	int count;
	int capacity;

	void reAllocate()
	{
		capacity *= 2;
		Order** NewHeap = new Order *[capacity];
		for (size_t i = 0; i < count; i++)
		{
			NewHeap[i] = Heap[i];
		}
		delete[]Heap;
		Heap = NewHeap;
	}

	void swap(int UpInd, int LowInd)
	{
		Order* temp = Heap[UpInd];
		Heap[UpInd] = Heap[LowInd];
		Heap[LowInd] = temp;
	}

public:
	MaxHEAP()
	{
		count = 0;
		capacity = 1000;
		Heap = new Order *[capacity];
	}

	MaxHEAP(int Capacity)
	{
		count = 0;
		if (capacity < 1)
			MaxHEAP();
		else
			Heap = new Order *[Capacity];
	}

	~MaxHEAP()
	{
		delete[]Heap;
	}

	bool isEmpty() const
	{
		return !count;
	}

	int getCount() const
	{
		return count;
	}

	int getCapacity() const
	{
		return capacity;
	}

	void insert(Order * item)
	{
		if (isEmpty())
		{
			count++;

			Heap[0] = item;
			return;
		}

		count++;

		if (count == capacity) reAllocate();

		Heap[count - 1] = item;

		int i = count - 1;

		while (i > 0)
		{
			if (*Heap[(i - 1) / 2] < *Heap[i])
			{
				swap(i, (i - 1) / 2);
				i = (i - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	bool peak(Order * Contain)
	{
		if (isEmpty()) return false;

		Contain = Heap[0];
		return true;
	}

	bool pop(Order * Contain)
	{
		if (isEmpty()) return false;

		count--;
		Contain = Heap[0];
		Heap[0] = Heap[count];
		int i = 0;
		while (true)
		{
			if (i + 1 >= count)
				break;
			else if (i + 2 >= count || *Heap[i + 2] < *Heap[i + 1])
			{
				if (*Heap[i / 2] < *Heap[i + 1])
				{
					swap(i / 2, i + 1);
					i = (i + 1) * 2;
				}
				else
				{
					break;
				}
			}
			else
			{
				if (*Heap[i / 2] < *Heap[i + 2])
				{
					swap(i / 2, i + 2);
					i = (i + 2) * 2;
				}
				else
				{
					break;
				}
			}
		}

		return true;
	}

	void print() const
	{
		for (size_t i = 0; i < count; i++)
		{
			std::cout << Heap[i]->GetID() << ": " << Heap[i]->calcWeight() << " | ";
		}
		std::cout << std::endl;
	}

	void printAsTree() const
	{
		for (size_t i = 0; i < count; i++)
		{
			std::cout << Heap[i]->GetID() << ": " << Heap[i]->calcWeight() << " | ";
			double log2 = log(i + 2) / log(2);
			if (log2 - floor(log2 + 0.00000001) < 1e-8)
			{
				std::cout << std::endl;
			}
		}
		std::cout << std::endl;
	}
};