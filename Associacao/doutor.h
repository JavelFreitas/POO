#ifndef DOUTOR_H
#endif DOUTOR_H
class Doctor
{
private:
	std::string m_name;
	std::vector<Patient *> m_patient;
 
public:
	Doctor(std::string name):
		m_name(name)
	{
	}
 
	void addPatient(Patient *pat)
	{
		// Our doctor will add this patient
		m_patient.push_back(pat);
		
		// and the patient will also add this doctor
		pat->addDoctor(this);
	}
 
 
	friend std::ostream& operator<<(std::ostream &out, const Doctor &doc)
	{
		unsigned int length = doc.m_patient.size();
		if (length == 0)
		{
			out << doc.m_name << " has no patients right now";
			return out;
		}
 
		out << doc.m_name << " is seeing patients: ";
		for (unsigned int count = 0; count < length; ++count)
			 out << doc.m_patient[count]->getName() << ' ';
 
		return out;
	}
 
	std::string getName() const { return m_name; }
};
 
