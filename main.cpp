#include <iostream>
#include <vector>
#include <string>
#include <memory>

namespace HospitalSystem
{

    using std::cout;
    using std::make_shared;
    using std::shared_ptr;
    using std::string;
    using std::vector;

    class Person
    {
    protected:
        int id;
        string name;
        string address;
        string phone_number;

    public:
        Person(int id, const string &name, const string &address, const string &phone_number)
            : id(id), name(name), address(address), phone_number(phone_number) {}
        virtual void getDetails() const
        {
            cout << "ID: " << id << "\nName: " << name << "\nAddress: " << address << "\nPhone: " << phone_number << "\n";
        }
        int getId() const { return id; } // Getter method for id
    };

    class Patient : public Person
    {
    private:
        int patient_number;
        string date_of_birth;
        string medical_condition;
        vector<string> prescribed_medications;

    public:
        Patient(int id, const string &name, const string &address, const string &phone_number, int patient_number, const string &date_of_birth)
            : Person(id, name, address, phone_number), patient_number(patient_number), date_of_birth(date_of_birth) {}
        void addPrescription(const string &medication)
        {
            prescribed_medications.push_back(medication);
        }
        void getMedicalHistory() const
        {
            getDetails();
            cout << "Patient Number: " << patient_number << "\nDate of Birth: " << date_of_birth << "\nMedical Condition: " << medical_condition << "\n";
            cout << "Prescribed Medications: ";
            for (const auto &med : prescribed_medications)
            {
                cout << med << " ";
            }
            cout << "\n";
        }
        void setMedicalCondition(const string &condition)
        {
            medical_condition = condition;
        }
    };

    class Doctor : public Person
    {
    private:
        int doctor_number;
        string specialty;
        vector<shared_ptr<Patient>> patients_under_care;

    public:
        Doctor(int id, const string &name, const string &address, const string &phone_number, int doctor_number, const string &specialty)
            : Person(id, name, address, phone_number), doctor_number(doctor_number), specialty(specialty) {}
        void addPatient(const shared_ptr<Patient> &patient)
        {
            patients_under_care.push_back(patient);
        }
        void diagnosePatient(const shared_ptr<Patient> &patient, const string &condition)
        {
            cout << "Diagnosing patient " << patient->getId() << " with condition: " << condition << "\n";
            patient->setMedicalCondition(condition);
        }
    };

    class Nurse : public Person
    {
    private:
        int nurse_number;
        string department;
        vector<shared_ptr<Patient>> patients_under_care;

    public:
        Nurse(int id, const string &name, const string &address, const string &phone_number, int nurse_number, const string &department)
            : Person(id, name, address, phone_number), nurse_number(nurse_number), department(department) {}
        void checkPatient(const shared_ptr<Patient> &patient)
        {
            cout << "Checking patient " << patient->getId() << "\n";
        }
        void updatePatientStatus(const shared_ptr<Patient> &patient, const string &status)
        {
            cout << "Updating patient " << patient->getId() << " status to: " << status << "\n";
        }
    };

    class Appointment
    {
    private:
        int appointment_number;
        shared_ptr<Patient> patient;
        shared_ptr<Doctor> doctor;
        string date_time;

    public:
        Appointment(int appointment_number, const shared_ptr<Patient> &patient, const shared_ptr<Doctor> &doctor, const string &date_time)
            : appointment_number(appointment_number), patient(patient), doctor(doctor), date_time(date_time) {}
        void schedule() const
        {
            cout << "Scheduled appointment #" << appointment_number << " for patient " << patient->getId() << " with doctor " << doctor->getId() << " on " << date_time << "\n";
        }
        void reschedule(const string &new_date_time)
        {
            date_time = new_date_time;
            cout << "Rescheduled appointment #" << appointment_number << " to " << date_time << "\n";
        }
        void cancel() const
        {
            cout << "Cancelled appointment #" << appointment_number << "\n";
        }
    };

    class Prescription
    {
    private:
        int prescription_number;
        shared_ptr<Patient> patient;
        shared_ptr<Doctor> doctor;
        vector<string> medications;
        string instructions;

    public:
        Prescription(int prescription_number, const shared_ptr<Patient> &patient, const shared_ptr<Doctor> &doctor, const string &instructions)
            : prescription_number(prescription_number), patient(patient), doctor(doctor), instructions(instructions) {}
        void addMedicine(const string &medicine)
        {
            medications.push_back(medicine);
        }
        void getDetails() const
        {
            cout << "Prescription #" << prescription_number << "\n";
            cout << "Patient: " << patient->getId() << "\nDoctor: " << doctor->getId() << "\nInstructions: " << instructions << "\nMedications: ";
            for (const auto &med : medications)
            {
                cout << med << " ";
            }
            cout << "\n";
        }
    };

    class Hospital
    {
    private:
        vector<shared_ptr<Patient>> patients;
        vector<shared_ptr<Doctor>> doctors;
        vector<shared_ptr<Appointment>> appointments;

    public:
        void addPatient(const shared_ptr<Patient> &patient)
        {
            patients.push_back(patient);
        }
        void addDoctor(const shared_ptr<Doctor> &doctor)
        {
            doctors.push_back(doctor);
        }
        void scheduleAppointment(const shared_ptr<Appointment> &appointment)
        {
            appointments.push_back(appointment);
            appointment->schedule();
        }
    };
}

int main()
{
    using namespace HospitalSystem;

    auto p1 = make_shared<Patient>(1, "John Doe", "123 Elm St", "555-1234", 1001, "01/01/1980");
    auto d1 = make_shared<Doctor>(2, "Dr. Smith", "456 Oak St", "555-5678", 2001, "Cardiology");
    auto n1 = make_shared<Nurse>(3, "Nurse Kelly", "789 Pine St", "555-8765", 3001, "ICU");

    p1->addPrescription("Aspirin");
    d1->addPatient(p1);
    d1->diagnosePatient(p1, "Flu");

    auto a1 = make_shared<Appointment>(4001, p1, d1, "08/01/2024 10:00 AM");
    auto pr1 = make_shared<Prescription>(5001, p1, d1, "Take one pill daily");

}


