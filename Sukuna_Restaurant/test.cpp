#include <iostream>
#include <list>

int main()
{
    // Declare a list of integers
    std::list<int> mylist;

    // Add elements to the list
    mylist.push_back(10);
    mylist.push_back(20);
    mylist.push_back(30);
    mylist.push_back(40);

    // Iterate through the list and print its elements from back to front
    std::cout << "Elements in reverse order: ";
    for (auto rit = mylist.rbegin(); rit != mylist.rend(); ++rit)
    {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    return 0;
}
