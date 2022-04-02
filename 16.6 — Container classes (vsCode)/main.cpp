#include <iostream>
#include "IntArray.h"
#include <vector>



int main()
{
    //Types of containers:


    //An array container class:
    IntArray array1{ 100 };

    std::cout << "Our array has lenght " << array1.getLenght() << '\n';
    array1.insertAtBeginning(77);
    std::cout << "Our array has lenght " << array1.getLenght() << '\n';
   // std::cout << array1 << '\n';

    // Declare an array with 10 elements
    IntArray array2{ 10 };

    // Fill the array with numbers 1 through 10
    for(int i{ 0 }; i < 10; ++i)
        array2[i] = i+1;

    // Resize the array to 8 elements
    array2.resize(8);

    // Insert the number 20 before element with index 5
    array2.insertBefore(20, 5);

    // Remove the element with index 3
    array2.remove(3);

    // Add 30 and 40 to the end and beginning
    array2.insertAtEnd(30);
    array2.insertAtBeginning(40);

    // Print out all the numbers
    //std::cout << array2 << '\n';
    for(int index{ 0 }; index < array2.getLenght(); ++index)
        std::cout << array2[index] << ' ';
    
    std::cout << std::endl;

    std::vector<int> array3{ 2, 3, 4 };
    for(const auto& arr : array3)
    {
        std::cout << arr << ' ';
    }
    std::cout << '\n';

    std::cout << array3.cend() << '\n';

    


    return 0;
}