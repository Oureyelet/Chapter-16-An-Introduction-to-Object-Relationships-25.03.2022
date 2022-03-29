#include <iostream>
#include <functional> // for std::reference_wrapper
#include <vector>

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

/*
    void print(std::reference_wrapper<const Teacher> name)
    {
        for(auto name : m_name_vector)
        {
            std::cout << name.get() << ' ' << '\n';
        }
    }
*/
};

class Department
{
private:
    Teacher& m_teacher; // This dept holds only one teacher for simplicity, but it could hold many teachers
    //std::vector<std::reference_wrapper<const Teacher>> m_name_vector{};

public:
    Department(); // default constructor;

    Department(Teacher& teacher)
        : m_teacher{ teacher }
    {
    }
/*
    void add(Teacher name)
    { 
        m_name_vector.push_back(name);
    }
*/
/*
    friend std::ostream& operator<<(std::ostream& out, const Department& department)
    {
        out << department.m_teacher.print(department) << '\n';

        return out;
    } 
*/  
};

int main()
{
    //Aggregation:

    //Implementing aggregations:
    
    // Create a teacher outside the scope of the Department
    Teacher bob{ "Bob" };// create a teacher


    {
        // Create a department and use the constructor parameter to pass
        // the teacher to it.
        Department department{ bob };
    }// department goes out of scope here and is destroyed

    // bob still exists here, but the department doesn't

    std::cout << bob.getName() << " still exist!" << '\n';

    //Pick the right relationship for what you’re modeling:

    //Summarizing composition and aggregation:

    //A few warnings/errata:

    //std::reference_wrapper:

    std::string tom{ "Tom" };
    std::string berta{ "Berta" };

    std::vector<std::reference_wrapper<std::string>> names{ tom, berta };// these strings are stored by reference, not value

    std::string jim{ "jim" };

    for(auto name : names)
    {
        // Use the get() member function to get the referenced string.
        //name.get() += " Beam";

        std::cout << name.get() << ' ' << '\n';
    }
    
    std::cout << jim << '\n';

    // Vector of const references to std::string
    std::vector<std::reference_wrapper<const std::string>> surnames{ "Kacperscy", "Cwik" };

    //Quiz time:

    /*
    Question #1

    Would you be more likely to implement the following as a composition or an aggregation?
    a) A ball that has a color = com
    b) An employer that is employing multiple people = agg
    c) The departments in a university = com
    d) Your age = com
    e) A bag of marbles = agg
    */

    /*
    Question #2

    Update the Department/Teacher example so the Department can handle multiple Teachers. The following code should execute:

    #include <iostream>

    // ...

    int main()
    {
    // Create a teacher outside the scope of the Department
    Teacher t1{ "Bob" };
    Teacher t2{ "Frank" };
    Teacher t3{ "Beth" };

    {
        // Create a department and add some Teachers to it
        Department department{}; // create an empty Department

        department.add(t1);
        department.add(t2);
        department.add(t3);

        std::cout << department;

    } // department goes out of scope here and is destroyed

    std::cout << t1.getName() << " still exists!\n";
    std::cout << t2.getName() << " still exists!\n";
    std::cout << t3.getName() << " still exists!\n";

    return 0;
    }

    This should print:

    Department: Bob Frank Beth
    Bob still exists!
    Frank still exists!
    Beth still exists!

    */

    // Create a teacher outside the scope of the Department
 
    Teacher t1{ "Bob" };
    Teacher t2{ "Frank" };
    Teacher t3{ "Beth" };

    {
        // Create a department and add some Teachers to it
        //Department department_Quiz{};// create an empty Department

        //department_Quiz.add(t1);
        //department_Quiz.add(t2);
        //department_Quiz.add(t3);



    }

    return 0;
}