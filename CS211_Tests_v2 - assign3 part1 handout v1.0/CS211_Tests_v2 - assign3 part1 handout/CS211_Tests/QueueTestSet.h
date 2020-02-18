// QueueTestSet.h
// Unit tests for Queue data structures in CST211 C++
// Winter 2020
// Pete Myers

#pragma once

#include "TestBase.h"

#include "Queue.h"

typedef Queue<std::string>* (*QueueCreator)();

Queue<std::string>* CircularArrayQueueCreator()
{
	return new CircularArrayQueue<std::string>;
}

class QueueTestSet : public TestSet
{
public:
	QueueTestSet(QueueCreator creator, const std::string& student, const std::string& setName, const std::string& description) :
		TestSet(setName, description)
	{
		AddTest("Insert / Peek", "Insert(), Peek()", 1, InsertPeekTest, creator);
		AddTest("Insert / Remove", "Push(), Remove()", 1, InsertRemoveTest, creator);
		AddTest("Count", "Insert(), Remove(), Count()", 1, CountTest, creator);
		AddTest("Insert / Remove error", "Insert(), Remove(), Peek()", 1, InsertRemoveErrorTest, creator);
		AddTest("Big Queue", "Insert(), Remove(), Count()", 1, BigQueueTest, creator);
		AddTest("Circulate", "Insert(), Remove(), Count()", 1, CirculateTest, creator);
	}

private:
	static void InsertPeekTest(void* param)
	{
		QueueCreator queueCreator = (QueueCreator)param;
		Queue<std::string>* queue = queueCreator();

		queue->Insert("a");
		Verify(queue->Peek() == "a", "Insert('a'), Peek() == 'a'");
		queue->Insert("b");
		Verify(queue->Peek() == "a", "Insert('b'), Peek() == 'a'");
		queue->Insert("c");
		Verify(queue->Peek() == "a", "Insert('c'), Peek() == 'a'");

		delete queue;
	}

	static void InsertRemoveTest(void* param)
	{
		QueueCreator queueCreator = (QueueCreator)param;
		Queue<std::string>* queue = queueCreator();

		queue->Insert("a");
		Verify(queue->Remove() == "a", "Insert('a'), Remove() == 'a'");
		queue->Insert("b");
		queue->Insert("c");
		Verify(queue->Remove() == "b", "Insert('b'), Insert('c'), Remove() == 'b'");
		Verify(queue->Remove() == "c", "Remove() == 'c'");

		delete queue;
	}

	static void CountTest(void* param)
	{
		QueueCreator queueCreator = (QueueCreator)param;
		Queue<std::string>* queue = queueCreator();

		Verify(queue->Count() == 0, "Count() == 0");
		queue->Insert("a");
		Verify(queue->Count() == 1, "Insert('a'), Count() == 1");
		std::string s = queue->Remove();
		Verify(s == "a" && queue->Count() == 0, "Remove() == 'a', Count() == 0");

		delete queue;
	}

	static void InsertRemoveErrorTest(void* param)
	{
		QueueCreator queueCreator = (QueueCreator)param;
		Queue<std::string>* queue = queueCreator();

		VerifyException([](void* p) -> void { std::string val = ((Queue<std::string>*)p)->Peek(); }, queue, "", "Peek()");
		VerifyException([](void* p) -> void { std::string val = ((Queue<std::string>*)p)->Remove(); }, queue, "", "Remove()");
		queue->Insert("a");
		std::string s = queue->Remove();
		VerifyException([](void* p) -> void { std::string val = ((Queue<std::string>*)p)->Peek(); }, queue, "", "Push('a'), Remove(), Peek()");
		VerifyException([](void* p) -> void { std::string val = ((Queue<std::string>*)p)->Remove(); }, queue, "", "Remove()");
		queue->Insert("b");
		s = queue->Remove();
		VerifyException([](void* p) -> void { std::string val = ((Queue<std::string>*)p)->Peek(); }, queue, "", "Push('b'), Remove(), Peek()");
		VerifyException([](void* p) -> void { std::string val = ((Queue<std::string>*)p)->Remove(); }, queue, "", "Remove()");

		delete queue;
	}

	static void BigQueueTest(void* param)
	{
		QueueCreator queueCreator = (QueueCreator)param;
		Queue<std::string>* queue = queueCreator();
		
		for (int i = 0; i < 100; i++)
		{
			queue->Insert(std::to_string(i));
			Verify(queue->Count() == i + 1, "Insert(" + std::to_string(i) + "), Count() == " + std::to_string(i + 1));
		}

		for (int i = 0; i < 100; i++)
		{
			Verify(queue->Remove() == std::to_string(i), "Remove() == " + std::to_string(i));
		}
		
		delete queue;
	}

	static void CirculateTest(void* param)
	{
		QueueCreator queueCreator = (QueueCreator)param;
		Queue<std::string>* queue = queueCreator();

		queue->Insert("a");
		queue->Insert("b");
		queue->Insert("c");
		queue->Insert("d");
		queue->Insert("e");
		Verify(queue->Remove() == "a", "Insert(a), Insert(b), Insert(c), Insert(d), Insert(e), Remove() == a");
		Verify(queue->Remove() == "b", "Remove() == b");
		Verify(queue->Remove() == "c", "Remove() == c");
		queue->Insert("f");
		queue->Insert("g");
		Verify(queue->Remove() == "d", "Insert(f), Insert(g), Remove() == d");
		Verify(queue->Remove() == "e", "Remove() == e");
		queue->Insert("h");
		queue->Insert("i");
		Verify(queue->Remove() == "f", "Insert(h), Insert(i), Remove() == f");
		Verify(queue->Remove() == "g", "Remove() == g");
		queue->Insert("j");
		Verify(queue->Count() == 3, "Insert(j), Count() == 3");
		queue->Insert("k");
		Verify(queue->Count() == 4, "Insert(k), Count() == 4");
		Verify(queue->Remove() == "h", "Remove() == h");
		Verify(queue->Remove() == "i", "Remove() == i");
		Verify(queue->Count() == 2, "Count() == 2");
		queue->Insert("l");
		queue->Insert("m");
		Verify(queue->Remove() == "j", "Insert(l), Insert(m), Remove() == j");
		Verify(queue->Count() == 3, "Count() == 3");
		Verify(queue->Remove() == "k", "Remove() == k");
		Verify(queue->Count() == 2, "Count() == 2");
		queue->Insert("n");
		queue->Insert("o");
		Verify(queue->Remove() == "l", "Insert(n), Insert(o), Remove() == l");
		Verify(queue->Remove() == "m", "Remove() == m");
		queue->Insert("p");
		queue->Insert("q");
		queue->Insert("r");
		queue->Insert("s");
		queue->Insert("t");
		queue->Insert("u");
		queue->Insert("v");
		queue->Insert("w");
		Verify(queue->Count() == 10, "Insert(8 more), Count() == 10");
		queue->Insert("x");
		Verify(queue->Count() == 11, "Insert(x), Count() == 11");

		delete queue;
	}
};
