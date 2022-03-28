#include <iostream>
#include <vector>
#include <functional>

class Teacher
{
private:
    std::string m_name{};
public:
    Teacher(); // default constructor

    Teacher(const std::string& name)
        : m_name{ name }
    {
    }

    const std::string& getName() const
    {
        return m_name;
    }
};

class Department
{
private:
    Teacher& m_teacher; // This dept holds only one teacher for simplicity, but it could hold many teachers
    std::vector<std::reference_wrapper<const Teacher>> m_name_vector{};

public:
    Department(); // default constructor;

    Department(Teacher& teacher)
        : m_teacher{ teacher }
    {
    }

    void add(Teacher& name)
    {
        m_name_vector.push_back(name);
    }
};

int main()
{
    // Create a teacher outside the scope of the Department
    Teacher t1{ "Bob" };
    Teacher t2{ "Frank" };
    Teacher t3{ "Beth" };

    Department department{};
    {
    // Create a department and add some Teachers to it

    //department.add(t1);
    //department.add(t2);
    //department.add(t3);

    //std::cout << department;

    } // department goes out of scope here and is destroyed


    return 0;
}