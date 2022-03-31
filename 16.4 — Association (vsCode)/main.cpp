#include <iostream>
#include <functional>
#include <string>
#include <vector>

// Since Doctor and Patient have a circular dependency, we're going to forward declare Patient
class Patient;

class Doctor
{
private:
    std::string m_name{};
    std::vector<std::reference_wrapper<const Patient>> m_patient{};

public:
    Doctor(const std::string& name)
        : m_name{ name }
    {
    }

    void addPatient(Patient& patient);

    // We'll implement this function below Patient since we need Patient to be defined at that point
    friend std::ostream& operator<< (std::ostream& out, const Doctor& doctor);

    const std::string& getName() const { return m_name; }

};

class Patient
{
private:
    std::string m_name{};
    std::vector<std::reference_wrapper<const Doctor>> m_doctor{};

    // We're going to make addDoctor private because we don't want the public to use it.
    void addDoctor(const Doctor& doctor)
    {
        m_doctor.push_back(doctor);
    }

public:
    Patient(const std::string& name)
        : m_name{ name }
    {
    }

    // We'll implement this function below Doctor since we need Doctor to be defined at that point
    friend std::ostream& operator<< (std::ostream& out, const Patient& patient);

    const std::string& getName() const { return m_name; }

    // We'll friend Doctor::addPatient() so it can access the private function Patient::addDoctor()
    friend void Doctor::addPatient(Patient& patient);
};

void Doctor::addPatient(Patient& patient)
{
    // Our doctor will add this patient
    m_patient.push_back(patient);

    // and the patient will also add this doctor
    patient.addDoctor(*this);
}

std::ostream& operator<< (std::ostream& out, const Doctor& doctor)
{
    if( doctor.m_patient.empty() )
    {
        out << doctor.m_name << " has no patients right now";

        return out;
    }

    out << doctor.m_name << "  is seeing patients: ";
    for(const auto& name : doctor.m_patient)
    {
        out << name.get().getName() << ' ';
    }

    return out;
}

std::ostream& operator<< (std::ostream& out, const Patient& patient)
{
    if( patient.m_doctor.empty() )
    {
        out << patient.m_name << " has no doctors right now";

        return out;
    }

    out << patient.m_name << " is seeing doctors: ";
	for (const auto& name : patient.m_doctor)
		out << name.get().getName() << ' ';

    return out;
}

class Car
{
private:
    std::string m_name{};
    int m_ID;

public:
    Car(const std::string& name, int id)
        :m_name{ name }, m_ID{ id }
    {
    }

    const std::string& getName() const { return m_name; }
    int getID() const { return m_ID; }

};

// Our CarLot is essentially just a static array of Cars and a lookup function to retrieve them.
// Because it's static, we don't need to allocate an object of type CarLot to use it
class CarLot
{
private:
    static Car s_carLot[4];

public:
    CarLot() = delete;// Ensure we don't try to create a CarLot

    static Car* getCar(int id)
    {
        for(int count{ 0 }; count < 4; ++count)
        {
            if(s_carLot[count].getID() == id)
            {
                return &(s_carLot[count]);
            }
        }
        return nullptr;
    }

};

Car CarLot::s_carLot[4]{ {"Prius", 4}, {"Corolla", 17}, {"Accord", 84}, {"Matrix", 62} };

class Driver
{
private:
    std::string m_name{};
    int m_carId{};

public:
    Driver(const std::string& name, int id)
        :m_name{ name }, m_carId{ id }
    {
    }

    const std::string& getName() const { return m_name; }
    int getID() const { return m_carId; }

};

int main()
{
    //Association:

    //Implementing associations:

    // Create a Patient outside the scope of the Doctor
    Patient dave{ "Dave" };
    Patient frank{ "Frank" };
    Patient betsy{ "Betsy" };

    Doctor james{ "James" };
    Doctor scott{ "Scott" };

    james.addPatient(dave);

    scott.addPatient(dave);
    scott.addPatient(betsy);

    std::cout << james << '\n';
    std::cout << scott << '\n';
    std::cout << dave << '\n';
    std::cout << frank << '\n';
    std::cout << betsy << '\n';

    //Reflexive association:

    //Associations can be indirect:
    Driver d{ "Franz", 17 };// Franz is driving the car with ID 17

    Car* car{ CarLot::getCar(d.getID()) };// Get that car from the car lot

    if(car)
        std::cout << d.getName() << " is driving a " << car->getName() << '\n';
    else
        std::cout << d.getName() << " couldn't find his car\n";

    //Composition vs aggregation vs association summary:
    

    return 0;
}