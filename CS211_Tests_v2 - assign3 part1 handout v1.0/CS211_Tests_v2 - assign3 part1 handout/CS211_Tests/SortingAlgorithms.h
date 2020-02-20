// SortingAlgorithms.h
// Pete Myers, OIT Winter 2020
// Classes that implement various sorting algorithsm
// Use ArrayList data structure
//
// Handout Assign3
//

#pragma once

#include "ArrayList.h"

template <class T> class Sorter
{
public:
	virtual void Sort(ArrayList<T>& list) = 0;
protected:
	void Swap(ArrayList<T>& list, int i, int j) {
		T temp = list.Get(i);
		list.Set(i, list.Get(j));
		list.Set(j, temp);
	}
};


//
// Selection Sort
//

template <class T> class SelectionSort : public Sorter<T>
{
public:
	SelectionSort() { }

	virtual void Sort(ArrayList<T>& list)
	{
		for (int i = 0; i < list.Count() - 1; i++)
		{
			int smallest = i;
			for(int j = i + 1; j  < list.Count(); j++)
			{
				if (list.Get(j) < list.Get(smallest))
				{
					smallest = j;
				}
			}
			Sorter<T>::Swap(list, i, smallest);
		}
	}
};


//
// MergeSort
//

template <class T> class MergeSort : public Sorter<T>
{
public:
	MergeSort() { }

	virtual void Sort(ArrayList<T>& list)
	{
		list = RecursiveMergeSort(list);
	}
private:
	ArrayList<T> RecursiveMergeSort(const ArrayList<T>& list)
	{
		// Base Case
		if (list.Count() <= 1)
			return list;

		// Recursive Case
		ArrayList<T> left;
		ArrayList<T> right;
		Split(list, left, right);
		left = RecursiveMergeSort(left);
		right = RecursiveMergeSort(right);

		return Merge(left, right);
	}

	void Split(const ArrayList<T>& list, ArrayList<T>& left, ArrayList<T>& right)
	{
		int half = list.Count() / 2;
		for (int i = 0; i < half; i++)
			left.Append(list.Get(i));
		for (int i = half; i < list.Count(); i++)
			right.Append(list.Get(i));
	}

	ArrayList<T> Merge(const ArrayList<T>& left, const ArrayList<T>& right)
	{
		// Both left and right lists are already sorted, independendently.
		// Result shoulr be a single sorted list, including all items from both lists.
		ArrayList<T> result;

		// Copy in the smallest item from each list, 
		// until we run out of items in one list or the other.
		int iLeft = 0;
		int iRight = 0;
		while (iLeft < left.Count() && iRight < right.Count())
		{
			if (left.Get(iLeft) < right.Get(iRight))
			{
				result.Append(left.Get(iLeft));
				iLeft++;
			}
			else {
				result.Append(right.Get(iRight));
				iRight++;
			}

		}

		// Copy in the rest of one of the lists
		if (iLeft < left.Count())
		{
			for (; iLeft < left.Count(); iLeft++)
				result.Append(left.Get(iLeft));
		}
		else {
			for (; iRight < right.Count(); iRight++)
				result.Append(right.Get(iRight));
		}
		return result;
	}
};


//
// HeapSort
//

template <class T> class HeapSort : public Sorter<T>
{
public:
	HeapSort() { }

	virtual void Sort(ArrayList<T>& list)
	{
		// TODO HeapSort::Sort()
	}
};

