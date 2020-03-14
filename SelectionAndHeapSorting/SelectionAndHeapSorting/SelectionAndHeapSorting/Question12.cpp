// By Kate LaFrance 3/13/2020
#include <iostream>
#include <string>


int main()
{
    
    Question12 q;

    return 0;

}

class Question12 {
    public:
    
    // Master list for all to use
        std::string masterList[10];

    // Single linked list (forwards)
        std::string inOrder[10];

    // Double Linked list (backwards)
        std::string revOrder[10];

    // Print at index
        std::string atIndex[10];

    
    Question12() {
        for (int i = 0; i < 10; i++)
        {
            std::string s;
            std::cin >> s;
            masterList[i] = s;
            std::cout << s << std::endl;
        }
    }

    // a.Print all 10 strings in the order read
    std::string PrintInOrder(std::string theList[]) {
        for (int i = 0; i < 11; i++)
        {
            std::cout << "Entry " << i << ", " << theList[i] << std::endl;
        }
    }

    // b.Print all 10 strings in reverse order
    void PrintReverse() {

    }

    // c.Print the third and seventh strings
    void PrintThis() {

    }



};



