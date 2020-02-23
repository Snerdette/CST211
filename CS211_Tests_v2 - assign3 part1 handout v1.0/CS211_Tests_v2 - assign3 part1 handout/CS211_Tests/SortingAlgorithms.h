// SortingAlgorithms.h
// Pete Myers, OIT Winter 2020
// Classes that implement various sorting algorithsm
// Use ArrayList data structure
//
// Handout Assignment 3
// By Kate LaFrance
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
		// First, build a heap
		Heapify(list);

		// next, pull off largest, exchange with the last, and sift down.
		for (int i = list.Count()-1; i > 0;  i--)
		{
			// Remember: the root is always at index 0 (zero)
			// Exchange largest in the heap with the "last" item
			Sorter<T>::Swap(list, 0, i);

			// Shift down to repair the shrinking heap.
			ShiftDown(list, i);
		}
	}

private:

	int Parent(int i) 
	{
		// Index of i's parent.
		//return floor((double)(i-1) /2);    OR
		return (i - 1) / 2;
	}

	

	int LeftChild(int i) 
	{
		// Index of i's left child.
		return 2 * i + 1;
	}

	int RightChild(int i) 
	{
		// Index of i's right child.
		return 2 * i +2;
	}

	bool HasLeftChild(int i, int n) {
		return LeftChild(i) < n;
	}

	bool HasRightChild(int i, int n) {
		return RightChild(i) < n;
	}

	void Heapify(ArrayList<T>& list) 
	{
		// Turn the list into a heap, in place
		// go throught each item in the list
		// compare with parent & swap if > parent
		// until the item's parent is bigger, or the item is at the root.
		for (int i = 1; i < list.Count(); i++)
		{
			for (int j = i; j > 0 && list.Get(j) > list.Get(Parent(j)); j = Parent(j))
			{
				Sorter<T>::Swap(list, j, Parent(j));
			}
		}
	}

	void GetAllThoseValues(const ArrayList<T>& list, int n, int i, int & value, 
		bool & hasLeft, bool & hasRight, int & left, int & right, int & leftValue, int & rightValue) 
	{
		value = list.Get(i);
		if (hasLeft = HasLeftChild(i, n))
		{
			left = LeftChild(i);
			leftValue = list.Get(left);
		}

		// Checks if exsists before assignment
		if (hasRight = HasRightChild(i, n))
		{
			right = RightChild(i);
			rightValue = list.Get(right);
		}

	}

	void ShiftDown(ArrayList<T>& list, int n)
	{
		// Repair the heap, assuming that the item at the root is not the biggest item
		// Compare root item with it's 2 direct children, if either is bigger, swap with the biggest child.
		// Continue until item is at bottom pf heap or is bigger than both children.

		// n is the number of items in the heap
		int i = 0;
		int left;
		int right;
		int value;
		int leftValue;
		int rightValue;
		bool hasLeft;
		bool hasRight;


		GetAllThoseValues(list, n, i, value, hasLeft, hasRight, left, right, leftValue, rightValue);

		while (i < n && ((hasLeft && leftValue > value) || ((hasRight && rightValue > value))))
		{
			if (!hasRight|| (leftValue > rightValue)) 
			{				
				Sorter<T>::Swap(list, i, left);
				i = left;
			}
			else
			{
				Sorter<T>::Swap(list, i, right);
				i = right;
			}
			// REfresh numbers!
			GetAllThoseValues(list, n, i, value, hasLeft, hasRight, left, right, leftValue, rightValue);
		}

	}
};

