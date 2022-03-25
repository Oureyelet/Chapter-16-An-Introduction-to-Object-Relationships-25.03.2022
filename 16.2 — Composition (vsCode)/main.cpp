#include <iostream>
#include <numeric> // for reduce()
#include <string>
#include "Point2D.h"
#include "Creature.h"

class Fraction
{
private:
    int m_numerator{};
    int m_denominator{ 1 };
public:
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
        // We put reduce() in the constructor to ensure any fractions we make get reduced!
		// Since all of the overloaded operators create new Fractions, we can guarantee this will get called here

        //reduce();
    }
};



int main()
{
    //Object composition:

    //Types of object composition:

    //Composition:
    Fraction ulamek{ 3, 2 };

    //Implementing compositions:

    //More examples:
    std::cout << "Enter a name for your creature: ";
    std::string name{};
    std::cin >> name;
    Creature creature{ name, {4, 7} };

    while (true)
    {
        std::cout << creature << '\n';

        std::cout << "Enter new X location for creature (-1 to quit): ";
        int x{};
        std::cin >> x;
        if( x == -1 )
            break;

        std::cout << "Enter new Y location for creature (-1 to quit): ";
        int y{};
        std::cin >> y;
        if( y == -1 )
            break;
    
        creature.moveTo(x, y);
    }
    
    //Variants on the composition theme:

    //Composition and subclasses:
    


    return 0;
}