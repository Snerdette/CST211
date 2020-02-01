// TestBase.h
// Comprehensive unit tests for data structures in CST211 C++
// Winter 2020
// Pete Myers

#pragma once

#include <stdlib.h>

#include <list>
#include <iostream>
#include <string>
#include <exception>


typedef void(*UnitTestFunc)(void* param);
typedef void(*ExceptionTestFunc)(void* param);


#define STUDENT "student_name"


class TestException : public std::exception
{
private:
	std::string msg;
public:
	TestException(const std::string& msg) : msg(msg)
	{
	}

	virtual const char* what() const throw ()
	{
		return msg.c_str();
	}
};

void Verify(bool condition, const std::string& description)
{
	if (!condition)
	{
		throw new TestException(description + ":  " + (condition ? "Passed" : "Failed"));
	}
}

void VerifyException(ExceptionTestFunc test, void* param, const std::string& expected, const std::string& description)
{
	bool passed = false;

	try
	{
		test(param);
	}
	catch (const char* ex)
	{
		// expecting an exception for this test
		std::cout << "        Received: " << ex;
		if (!expected.empty())
		{
			passed = ex == expected;
			if (!passed)
			{
				std::cout << "        Expected: " << expected << std::endl;
			}
		}
		else
		{
			// no particular exception expected, anything will do
			std::cout << std::endl;
			passed = true;
		}
	}

	if (!passed)
	{
		throw new TestException(description + ":  " + (passed ? "Passed" : "Failed"));
	}
}

class Test
{
private:
	UnitTestFunc test;
	void* param;
	std::string name;
	std::string description;
	int possiblePoints;
	int pointsAwarded;
	bool passed;

public:
	Test(const std::string& name, const std::string& description, int points, UnitTestFunc test, void* param) :
		name(name), description(description), possiblePoints(points), test(test), param(param)
	{
		pointsAwarded = 0;
		passed = false;
	}
	int AvailablePoints() { return possiblePoints; }
	int PointsAwarded() { return pointsAwarded; }
	void Run()
	{
		std::cout << "    Test " + name + ": " + description + "..." << std::endl;

		try
		{
			pointsAwarded = 0;
			passed = true;
			test(param);
			pointsAwarded = possiblePoints;
		}
		catch (TestException* ex1)
		{
			passed = false;
			std::cout << "        Failure: " << ex1->what() << std::endl;
		}
		catch (char* ex3)
		{
			passed = false;
			std::cout << "        Exception: " << ex3 << std::endl;
		}
		catch (std::exception& ex2)
		{
			passed = false;
			std::cout << "        Exception: " << ex2.what() << std::endl;
		}

		std::cout << "    Test " + name + ": " + (passed ? "Passed" : "Failed") << std::endl;
	}
};

class TestSet
{
private:
	std::list<Test> tests;
	std::string setName;
	std::string description;
	int availablePoints;
	int pointsAwarded;

public:
	TestSet(const std::string& setName, const std::string& description) :
		setName(setName), description(description)
	{
		availablePoints = 0;
		pointsAwarded = 0;
	}

	void AddTest(Test test)
	{
		tests.push_back(test);
		availablePoints += test.AvailablePoints();
	}

	void AddTest(const std::string& name, const std::string& description, int points, UnitTestFunc test, void* param)
	{
		tests.push_back(Test(name, description, points, test, param));
		availablePoints += points;
	}

	void Run()
	{
		std::cout << "Test Set " + setName + ": " + description + "..." << std::endl << std::endl;
		pointsAwarded = 0;
		for (std::list<Test>::iterator iter = tests.begin(); iter != tests.end(); ++iter)
		{
			iter->Run();
			pointsAwarded += iter->PointsAwarded();
		}
		std::cout.precision(2);
		double score = availablePoints != 0 ? (pointsAwarded * 100.0) / availablePoints : 100.0;
		std::cout.precision(2);
		std::cout << std::fixed << std::endl << "Test Set " + setName + " Score: " << score << "%" << std::endl << std::endl;
	}
};
