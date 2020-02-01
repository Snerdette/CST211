// ListTestSet.h
// Unit tests for List data structures in CST211 C++
// Winter 2020
// Pete Myers

#pragma once

#include "TestBase.h"

#include "ArrayList.h"
#include "LinkedList.h"

typedef List<std::string>* (*ListCreator)();

List<std::string>* ArrayListCreator()
{
	return new ArrayList<std::string>();
}
List<std::string>* LinkedListCreator()
{
	return new LinkedList<std::string>();
}


class ListTestSet : public TestSet
{
public:
	ListTestSet(ListCreator creator, const std::string& student, const std::string& setName, const std::string& description) :
		TestSet(setName, description)
	{
		AddTest("Append/Get", "Append(), Get(index)", 1, AppendGetTest, creator);
		AddTest("Get error", "Append(obj), Get(index)", 1, GetErrorTest, creator);
		AddTest("ForwardIterator", "Append(obj), Begin(), iter->HasNext(), iter->Next()", 1, ForwardIteratorTest, creator);
		AddTest("Append/Count", "Append(obj), Count()", 1, AppendCountTest, creator);
		AddTest("Big List", "Append(obj), Count(), Get(index)", 1, BigListTest, creator);
		AddTest("Insert", "Append(obj), Insert(obj, index), Get(index)", 1, InsertTest, creator);
		AddTest("Remove", "Append(obj), Remove(index), Count(), Get(index)", 1, RemoveTest, creator);
		AddTest("Iterator Remove", "Append(obj), Begin(), iter->Remove(), iter->Next(), Count(), Get(index)", 1, IteratorRemoveTest, creator);
		AddTest("Reverse Iterator", "Append(obj), Begin(), End(), iter->HasNext(), iter->Next(), iter->HasPrevious(), iter->Previous()", 1, ReverseIteratorTest, creator);
		AddTest("Iterator Insert", "Append(obj), Begin(), iter->HasNext(), iter->Next(), iter->Insert()", 1, IteratorInsertTest, creator);
	}

private:
	static void AppendGetTest(void* param)
	{
		ListCreator listCreator = (ListCreator)param;
		List<std::string>* list = listCreator();

		list->Append("a");
		Verify(list->Get(0) == "a", "Append('a'), Get(0) == 'a'");
		list->Append("b");
		Verify(list->Get(1) == "b", "Append('b'), Get(1) == 'b'");
		list->Append("c");
		Verify(list->Get(2) == "c", "Append('c'), Get(2) == 'c'");

		delete list;
	}

	static void GetErrorTest(void* param)
	{
		ListCreator listCreator = (ListCreator)param;
		List<std::string>* list = listCreator();

		// Note use of lambda expressions in C++
		// [](params) -> return { body }
		VerifyException([](void* p) -> void { std::string val = ((List<std::string>*)p)->Get(0); }, list, "", "Get(0)");
		list->Append("a");
		VerifyException([](void* p) -> void { std::string val = ((List<std::string>*)p)->Get(1); }, list, "", "Append('a'), Get(1)");

		delete list;
	}

	static void ForwardIteratorTest(void* param)
	{
		ListCreator listCreator = (ListCreator)param;
		List<std::string>* list = listCreator();

		list->Append("a");
		list->Append("b");
		list->Append("c");

		List<std::string>::ListIterator* iter = list->Begin();
		Verify(iter->HasNext() == true, "Append('a'), Append('b'), Append('c'), Begin(), iter->HasNext() == true");
		Verify(iter->Next() == "a", "iter->Next() == 'a'");
		Verify(iter->Next() == "b", "iter->Next() == 'b'");
		Verify(iter->Next() == "c", "iter->Next() == 'c'");
		Verify(iter->HasNext() == false, "iter->HasNext() == false");

		delete iter;
		delete list;
	}

	static void AppendCountTest(void* param)
	{
		ListCreator listCreator = (ListCreator)param;
		List<std::string>* list = listCreator();

		Verify(list->Count() == 0, "Count() == 0");
		list->Append("a");
		Verify(list->Count() == 1, "Append('a'), Count() == 1");
		list->Append("b");
		Verify(list->Count() == 2, "Append('b'), Count() == 2");

		delete list;
	}

	static void BigListTest(void* param)
	{
		ListCreator listCreator = (ListCreator)param;
		List<std::string>* list = listCreator();

		for (int i = 0; i < 100; i++)
		{
			list->Append(std::to_string(i));
		}
		Verify(list->Count() == 100, "Append numbers 1 thru 100, Count() == 100");
		Verify(list->Get(1) == "1", "Get(1) == '1'");
		Verify(list->Get(42) == "42", "Get(42) == '42'");
		Verify(list->Get(99) == "99", "Get(99) == '99'");

		delete list;
	}

	static void InsertTest(void* param)
	{
		ListCreator listCreator = (ListCreator)param;
		List<std::string>* list = listCreator();

		list->Append("a");
		list->Append("c");
		list->Insert("b", 1);
		Verify(list->Get(1) == "b", "Append('a'), Append('c'), Insert('b', 1), Get(1) == 'b'");
		Verify(list->Get(0) == "a", "Get(0) == 'a'");
		Verify(list->Get(2) == "c", "Get(2) == 'c'");
		list->Insert("e", 0);
		Verify(list->Get(0) == "e", "Insert('e', 0), Get(0) == 'e'");
		Verify(list->Get(1) == "a", "Get(1) == 'a'");
		list->Insert("f", 3);
		Verify(list->Get(3) == "f", "Insert('f', 3), Get(3) == 'f'");
		Verify(list->Get(4) == "c", "Get(4) == 'c'");

		delete list;
	}

	static void RemoveTest(void* param)
	{
		ListCreator listCreator = (ListCreator)param;
		List<std::string>* list = listCreator();

		list->Append("a");
		list->Append("b");
		list->Append("c");
		Verify(list->Count() == 3, "Append('a'), Append('b'), Append('c'), Count() == 3");
		std::string removed = list->Remove(2);
		Verify(removed == "c" && list->Count() == 2, "Remove(2) == 'c', Count() == 2");
		Verify(list->Get(0) == "a", "Get(0) == 'a'");
		Verify(list->Get(1) == "b", "Get(1) == 'b'");
		removed = list->Remove(0);
		Verify(removed == "a" && list->Count() == 1, "Remove(0) == 'a', Count() == 1");
		Verify(list->Get(0) == "b", "Get(0) == 'b'");
		removed = list->Remove(0);
		Verify(removed == "b" && list->Count() == 0, "Remove(0) == 'b', Count() == 0");
		list->Append("e");
		Verify(list->Count() == 1 && list->Get(0) == "e", "Append('e'), Count() == 1 && Get(0) == 'e'");
		removed = list->Remove(0);
		Verify(removed == "e" && list->Count() == 0, "Remove(0) == 'e', Count() == 0");

		delete list;
	}

	static void IteratorRemoveTest(void* param)
	{
		ListCreator listCreator = (ListCreator)param;
		List<std::string>* list = listCreator();

		list->Append("a");
		list->Append("b");
		list->Append("c");
		Verify(list->Count() == 3, "Append('a'), Append('b'), Append('c'), Count() == 3");
		List<std::string>::ListIterator* iter = list->Begin();
		iter->Next();
		std::string removed = iter->Remove();
		Verify(removed == "b" && list->Count() == 2, "Begin(), iter->Next(), iter->Remove() == 'b', Count() == 2");
		Verify(list->Get(0) == "a", "Get(0) == 'a'");
		Verify(list->Get(1) == "c", "Get(1) == 'c'");
		removed = iter->Remove();
		Verify(removed == "c" && list->Count() == 1, "iter->Remove() == 'c', Count() == 1");
		Verify(list->Get(0) == "a", "Get(0) == 'a'");
		Verify(iter->HasNext() == false, "iter->HasNext() == false");
		delete iter;
		iter = list->Begin();
		Verify(iter->HasNext() == true, "Begin(), iter->HasNext() == true");
		removed = iter->Remove();
		Verify(removed == "a" && iter->HasNext() == false, "iter->Remove() == 'a', iter->HasNext() == false");
		Verify(list->Count() == 0, "Count() == 0");

		delete iter;
		delete list;
	}

	static void ReverseIteratorTest(void* param)
	{
		ListCreator listCreator = (ListCreator)param;
		List<std::string>* list = listCreator();

		list->Append("a");
		list->Append("b");
		list->Append("c");

		List<std::string>::ListIterator* iter = list->Begin();
		Verify(iter->HasNext() == true, "Append('a'), Append('b'), Append('c'), Begin(), iter->HasNext() == true");
		Verify(iter->HasPrevious() == false, "iter->HasPrevious() == false");

		Verify(iter->Next() == "a", "iter->Next() == 'a'");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->HasPrevious() == true, "iter->HasPrevious() == true");

		Verify(iter->Next() == "b", "iter->Next() == 'b'");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->HasPrevious() == true, "iter->HasPrevious() == true");

		Verify(iter->Next() == "c", "iter->Next() == 'c'");
		Verify(iter->HasNext() == false, "iter->HasNext() == false");
		Verify(iter->HasPrevious() == true, "iter->HasPrevious() == true");

		Verify(iter->Previous() == "c", "iter->Previous() == 'c'");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->HasPrevious() == true, "iter->HasPrevious() == true");

		Verify(iter->Previous() == "b", "iter->Previous() == 'b'");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->HasPrevious() == true, "iter->HasPrevious() == true");

		Verify(iter->Previous() == "a", "iter->Previous() == 'a'");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->HasPrevious() == false, "iter->HasPrevious() == false");

		delete iter;

		iter = list->End();
		Verify(iter->HasNext() == false, "End(), iter->HasNext() == false");
		Verify(iter->HasPrevious() == true, "iter->HasPrevious() == true");

		Verify(iter->Previous() == "c", "iter->Previous() == 'c'");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->HasPrevious() == true, "iter->HasPrevious() == true");

		Verify(iter->Previous() == "b", "iter->Previous() == 'b'");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->HasPrevious() == true, "iter->HasPrevious() == true");

		Verify(iter->Previous() == "a", "iter->Previous() == 'a'");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->HasPrevious() == false, "iter->HasPrevious() == false");

		Verify(iter->Next() == "a", "iter->Next() == 'a'");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->HasPrevious() == true, "iter->HasPrevious() == true");

		Verify(iter->Next() == "b", "iter->Next() == 'b'");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->HasPrevious() == true, "iter->HasPrevious() == true");

		Verify(iter->Next() == "c", "iter->Next() == 'c'");
		Verify(iter->HasNext() == false, "iter->HasNext() == false");
		Verify(iter->HasPrevious() == true, "iter->HasPrevious() == true");

		delete iter;
		delete list;
	}

	static void IteratorInsertTest(void* param)
	{
		ListCreator listCreator = (ListCreator)param;
		List<std::string>* list = listCreator();

		Verify(list->Count() == 0, "Count() == 0");
		List<std::string>::ListIterator* iter = list->Begin();
		iter->Insert("a");
		Verify(list->Count() == 1, "iter->Insert('a'), Count() == 1");
		Verify(list->Get(0) == "a", "Get(0) == 'a'");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->Next() == "a", "iter->Next() == 'a'");
		iter->Insert("b");
		Verify(list->Count() == 2, "iter->Insert('b'), Count() == 2");
		Verify(list->Get(0) == "a", "Get(0) == 'a'");
		Verify(list->Get(1) == "b", "Get(1) == 'b'");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		iter->Insert("c");
		Verify(list->Count() == 3, "iter->Insert('c'), Count() == 3");
		Verify(list->Get(0) == "a", "Get(0) == 'a'");
		Verify(list->Get(1) == "c", "Get(1) == 'c'");
		Verify(list->Get(2) == "b", "Get(2) == 'b'");
		Verify(iter->HasNext() == true, "iter->HasNext() == true");
		Verify(iter->Next() == "c", "iter->Next() == 'c'");
		Verify(iter->Next() == "b", "iter->Next() == 'b'");

		delete iter;
		delete list;
	}
};
