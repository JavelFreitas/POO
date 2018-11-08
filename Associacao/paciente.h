#pragma once
#include <iostream>
#include <vector>
#include <string>

class Doctor;
 
class Patient
{
private:
	std::string m_name;
	std::vector<Doctor *> m_doctor; // so that we can use it here
 
	// We're going to make addDoctor private because we don't want the public to use it.
	// They should use Doctor::addPatient() instead, which is publicly exposed
	// We'll define this function after we define what a Doctor is
	// Since we need Doctor to be defined in order to actually use anything from it
	void addDoctor(Doctor *doc);
 
public:
	Patient(std::string name)
		: m_name(name)
	{
	}
 
	// We'll implement this function below Doctor since we need Doctor to be defined at that point
	friend std::ostream& operator<<(std::ostream &out, const Patient &pat);
 
	std::string getName() const { return m_name; }
 
	// We're friending Doctor so that class can access the private addDoctor() function
	// (Note: in normal circumstances, we'd just friend that one function, but we can't
	// because Doctor is forward declared)
	friend class Doctor;
};



void Patient::addDoctor(Doctor *doc)
{
	m_doctor.push_back(doc);
}

std::ostream& operator<<(std::ostream &out, const Patient &pat)
{
	unsigned int length = pat.m_doctor.size();
	if (length == 0)
	{
		out << pat.getName() << " has no doctors right now";
		return out;
	}
 
	out << pat.m_name << " is seeing doctors: ";
	for (unsigned int count = 0; count < length; ++count)
		out << pat.m_doctor[count]->getName() << ' ';
 
	return out;
}