#include <iostream>

class Point
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point(double x = 0.0, double y = 0.0, double z = 0.0)
        :m_x{ x }, m_y{ y }, m_z{ z }
    {
    }

    friend std::ostream& operator<<(std::ostream& out, const Point& point);// Point has a dependency on std::ostream here
};

std::ostream& operator<<(std::ostream& out, const Point& point)
{
    // Since operator<< is a friend of the Point class, we can access Point's members directly.
    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')' << '\n';

    return out; 
}

int main()
{
    std::cout << "Hello World\n";

    Point point1{1.1, 34.4, 67.3 };

    std::cout << point1;


    return 0;
}