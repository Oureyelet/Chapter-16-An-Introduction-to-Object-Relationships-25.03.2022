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

    const std::string& getName() { return m_name; }

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

    const std::string& getName() { return m_name; }

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
    }

    for(const auto& name : patient.m_doctor)
    {
        out << name.get()
    }
}

int main()
{
    //Association:

    //Implementing associations:


    return 0;
}