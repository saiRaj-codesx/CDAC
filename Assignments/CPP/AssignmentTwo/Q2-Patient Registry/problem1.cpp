#include <iostream>
#include <string>

using namespace std;

class Patient {
private:
    int patientId;
    string name;
    int age;
    string ward;
    const string bloodGroup; 

public:
    
    Patient() : bloodGroup("O+") {
        patientId = 0;
        name = "Unknown";
        age = 0;
        ward = "General";
        cout << "[Constructor] Default patient registered." << endl;
        return; 
    }

   
    Patient(int id, const string& pName) : bloodGroup("O+") {
        patientId = id;
        name = pName;
        age = 0;
        ward = "General";
        cout << "[Constructor] Emergency: " << name << endl;
        return; 
    }

   
    Patient(int id, const string& pName, int pAge, const string& pWard, const string& bg) : bloodGroup(bg) {
        patientId = id;
        name = pName;
        age = pAge;
        ward = pWard;
        cout << "[Constructor] Full admission: " << name << endl;
    }

   
    ~Patient() {
        cout << "[Destructor] Patient " << name << " discharged." << endl;
        return; 
    }

    
    void displayRecord() const {
        cout << "\nPatient Record:" << endl;
        cout << "  ID       : " << patientId << endl;
        cout << "  Name     : " << name << endl;
        cout << "  Age      : " << age << endl;
        cout << "  Ward     : " << ward << endl;
        cout << "  Blood Grp: " << bloodGroup << endl;
    }

   
    void transferWard(const string& newWard) {
     
        string oldWardName = ward; 
        cout << "\nWard Transfer: " << name << " -> " << newWard << endl;
        ward = newWard;
    }
};

int main() {
    cout << "=== STARTING HOSPITAL REGISTRY SYSTEM ===\n" << endl;

   
    Patient p1(1001, "Meera Joshi", 34, "Cardiology", "B+");
    Patient p2(1002, "Raj Patel");
    Patient p3; 

  
    cout << "\n--- Creating dynamic array of 4 patients ---" << endl;
    Patient* hospitalArray = new Patient[4];

  
    cout << "\n--- Displaying dynamic array records ---" << endl;
    
    for (int i = 0; i <= 3; i++) { 
        hospitalArray[i].displayRecord();
    }

  
    p2.transferWard("ICU");

  
    cout << "\n--- Deleting the dynamic array ---" << endl;
    delete[] hospitalArray;

    cout << "\n=== END OF MAIN (Stack objects will destroy now) ===" << endl;
    return 0;
}
