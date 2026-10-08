#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class LedgerEntry {
private:
    string description;
    double* amounts;
    int days;

public:
 
    static int totalEntries;

    // 1. Regular Constructor
    LedgerEntry(const string& desc, int d) {
        description = desc;
        days = d;
        amounts = new double[days];
        
        
        for (int i = 0; i < days; i++) {
            amounts[i] = 0.0;
        }
        
        totalEntries++;
        cout << "[LedgerEntry Created] " << description << " (" << days << " days)" << endl;
    }

    // 2. Copy Constructor (Deep Copy)
    LedgerEntry(const LedgerEntry& other) {
        description = other.description;
        days = other.days;
        
       
        amounts = new double[days];
        for (int i = 0; i < days; i++) {
            amounts[i] = other.amounts[i];
        }
        
        totalEntries++;
    }

    // 3. Move Constructor
    LedgerEntry(LedgerEntry&& other) noexcept {
        cout << "[Move Constructor] Ownership transferred from: " << other.description << endl;
        
        
        description = other.description;
        amounts = other.amounts;
        days = other.days;
        
        
        other.amounts = nullptr;
        other.days = 0;
        other.description = "";
        
        totalEntries++;
    }

    // 4. Copy Assignment Operator 
    LedgerEntry& operator=(const LedgerEntry& other) {
       
        if (this != &other) {
          
            delete[] amounts;
            
           
            description = other.description;
            days = other.days;
            
            
            amounts = new double[days];
            for (int i = 0; i < days; i++) {
                amounts[i] = other.amounts[i];
            }
        }
        return *this;
    }

    // 5. Move Assignment Operator
    LedgerEntry& operator=(LedgerEntry&& other) noexcept {
        cout << "[Move Assignment] Ownership transferred from: " << other.description << endl;
        
        if (this != &other) {
           
            delete[] amounts;
            
           
            description = other.description;
            amounts = other.amounts;
            days = other.days;
            
          
            other.amounts = nullptr;
            other.days = 0;
            other.description = "";
        }
        return *this;
    }

    // 6. Destructor
    ~LedgerEntry() {
        if (amounts != nullptr) {
            delete[] amounts;
        }
        totalEntries--;
        
        if (description != "") {
            cout << "[Destructor] " << description << " destroyed" << endl;
        }
    }

    
    double& operator[](int index) {
        if (index < 0 || index >= days) {
            throw out_of_range("Index out of bounds!");
        }
        return amounts[index];
    }

    
    const double& operator[](int index) const {
        if (index < 0 || index >= days) {
            throw out_of_range("Index out of bounds!");
        }
        return amounts[index];
    }

    
    LedgerEntry operator+(const LedgerEntry& other) const {
    
        int resultDays = (this->days < other.days) ? this->days : other.days;
        
        LedgerEntry temp("Combined", resultDays);
        for (int i = 0; i < resultDays; i++) {
            temp.amounts[i] = this->amounts[i] + other.amounts[i];
        }
        return temp;
    }

    
    double getTotalSum() const {
        double total = 0.0;
        if (amounts != nullptr) {
            for (int i = 0; i < days; i++) {
                total += amounts[i];
            }
        }
        return total;
    }

    
    bool operator==(const LedgerEntry& other) const {
        return this->getTotalSum() == other.getTotalSum();
    }

    bool operator>(const LedgerEntry& other) const {
        return this->getTotalSum() > other.getTotalSum();
    }

    friend ostream& operator<<(ostream& out, const LedgerEntry& entry) {
        out << entry.description << " : [";
        for (int i = 0; i < entry.days; i++) {
            out << entry.amounts[i];
            if (i < entry.days - 1) {
                out << ", ";
            }
        }
        out << "] Total: " << entry.getTotalSum();
        return out;
    }

    
    friend istream& operator>>(istream& in, LedgerEntry& entry) {
        for (int i = 0; i < entry.days; i++) {
            in >> entry.amounts[i];
        }
        return in;
    }
    
   
    bool isBufferNull() const {
        return amounts == nullptr;
    }
};


int LedgerEntry::totalEntries = 0;

int main() {
    // Objective 1 — Constructor & deep copy
    LedgerEntry jan("January Sales", 5);
    jan[0] = 1200.50; jan[1] = 3400.00; jan[2] = 800.75;
    jan[3] = 2100.00; jan[4] = 650.25;

    LedgerEntry feb("February Sales", 5);
    feb[0] = 900.00; feb[1] = 2200.50; feb[2] = 1750.00;
    feb[3] = 3000.00; feb[4] = 475.50;

    cout << jan << endl;
    cout << feb << endl;

    // Objective 2 — Operator + (sum two ledgers into combined)
    LedgerEntry combined = jan + feb;
    cout << "Combined: " << combined << endl;

    // Objective 3 — Relational operators
    cout << "Jan == Feb : " << (jan == feb ? "Yes" : "No") << endl;
    cout << "Jan > Feb : " << (jan > feb ? "Yes" : "No") << endl;

    // Objective 4 — Move constructor (should NOT deep copy)
    LedgerEntry moved = move(jan);
    cout << "After move, jan.amounts is null: "
         << (jan.isBufferNull() ? "YES" : "NO") << endl;
    cout << "Moved entry: " << moved << endl;

    // Objective 5 — Move assignment
    LedgerEntry q1("Q1 Total", 5);
    q1 = move(feb); 
    cout << "Q1 (moved from feb): " << q1 << endl;

    // Objective 6 — Static member
    cout << "Live LedgerEntry objects: " << LedgerEntry::totalEntries << endl;

    return 0;
}
