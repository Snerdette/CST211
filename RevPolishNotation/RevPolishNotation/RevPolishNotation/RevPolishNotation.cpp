// RevPolishNotation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stack>

using namespace std;

int processTwoNumbers(int a, int b, char numOperator);
//int main();
	
	int main()
	{
		/*char buf[256];
		std::stack<int> stack;

		std::cout << "Input number string with operators" << std::endl;

		std::string entry;  getline(cin, entry);
		cout << "ENTRY: " << entry << endl;*/

		int value = processTwoNumbers(1,1,'+');

		return 0;

	}

	 int processTwoNumbers(int a, int b, char numOperator) {
		 int temp = 0;
		 char c =numOperator;

		 switch (c) {
		 case '+':
			 temp = a + b;
			 break;
		 case '/':
			 temp = a / b;
			 break;
		 case '*':
			 temp = a * b;
			 break;
		 default:
			 std::cout << "No match in switch" << std::endl;
		 }

		 std::cout << "Result: " << temp << std::endl;
		 return temp;
	}



	/*
		std:: stack<int> stack;
		stack.push(42);
		int n = stack.top();
		stack.pop();


		while (!std::cin.eof())
		{
			std::cin.getline(buf, sizeof(buf));
			std::string line(buf);
			std::cout << "char[]: " << line;
			if (line[0] == 'q') return 0;
			else
				std::cout << "Input ->" << line << "<-" << std::endl;
		}


	*/


