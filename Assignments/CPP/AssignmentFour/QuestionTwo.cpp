#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// BASE CLASS: Vehicle

class Vehicle {
protected:
    string registrationNo;
    string ownerName;
    int yearOfManufacture;
    double kmDriven;

public:
    Vehicle(const string& reg, const string& owner, int year, double km) {
        registrationNo = reg;
        ownerName = owner;
        yearOfManufacture = year;
        kmDriven = km;
        cout << "[Vehicle Constructor] " << registrationNo << " : " << ownerName << endl;
    }


    virtual double fuelCost(double kmToTravel) const = 0;
    virtual string vehicleType() const = 0;


    virtual void describe() const {
        cout << registrationNo << " | " << vehicleType() << " | " << ownerName << " | " << kmDriven << " km";
    }


    virtual ~Vehicle() {
        cout << "[Vehicle Destructor] " << registrationNo << endl;
    }

    double getKmDriven() const { return kmDriven; }
    string getRegNo() const { return registrationNo; }
    string getOwnerName() const { return ownerName; }
};

// DERIVED CLASS 1: Car

class Car : public Vehicle {
private:
    string fuelType; 
    double mileageKmpl;

public:
    Car(const string& reg, const string& owner, int year, double km, const string& fuel, double mileage)
        : Vehicle(reg, owner, year, km) {
        fuelType = fuel;
        mileageKmpl = mileage;
    }

    double fuelCost(double kmToTravel) const override {
        double pricePerLitre = 0.0;
        if (fuelType == "Petrol") {
            pricePerLitre = 106.00;
        } else if (fuelType == "Diesel") {
            pricePerLitre = 93.00;
        }
        return (kmToTravel / mileageKmpl) * pricePerLitre;
    }

    string vehicleType() const override {
        return "Car";
    }

    void describe() const override {
        Vehicle::describe();
        cout << " | Fuel: " << fuelType << " | Mileage: " << mileageKmpl << " kmpl";
    }

    ~Car() override {
        cout << "[Car Destructor] " << registrationNo << endl;
    }
};


// DERIVED CLASS 2: Truck 

class Truck : public Vehicle {
protected:
    double payloadCapacityTons;
    double fuelEfficiencyKmpl;

public:
    Truck(const string& reg, const string& owner, int year, double km, double payload, double efficiency)
        : Vehicle(reg, owner, year, km) {
        payloadCapacityTons = payload;
        fuelEfficiencyKmpl = efficiency;
        cout << "[Truck Constructor] " << registrationNo << endl;
    }

    double fuelCost(double kmToTravel) const override {
      
        double realEfficiency = fuelEfficiencyKmpl * (1.0 - (0.05 * payloadCapacityTons));
     
        double pricePerLitre = 93.00; 
        return (kmToTravel / realEfficiency) * pricePerLitre;
    }

    string vehicleType() const override {
        return "Truck";
    }

    void describe() const override {
        Vehicle::describe();
        cout << " | Payload: " << payloadCapacityTons << " tons | Efficiency: " << fuelEfficiencyKmpl << " kmpl";
    }

    ~Truck() override {
        cout << "[Truck Destructor] " << registrationNo << endl;
    }
};


// DERIVED CLASS 3: ElectricTruck 

class ElectricTruck : public Truck {
private:
    double batteryCapacityKWh;
    double rangePerChargeKm;

public:
    ElectricTruck(const string& reg, const string& owner, int year, double km, double payload, double efficiency, double battery, double range)
        : Truck(reg, owner, year, km, payload, efficiency) {
        batteryCapacityKWh = battery;
        rangePerChargeKm = range;
        cout << "[ElectricTruck Constructor] " << registrationNo << endl;
    }

    double fuelCost(double kmToTravel) const override {
        double electricityCostPerUnit = 9.50;
        return (kmToTravel / rangePerChargeKm) * batteryCapacityKWh * electricityCostPerUnit;
    }

    string vehicleType() const override {
        return "Electric Truck";
    }

    void describe() const override {
        Truck::describe();
        cout << " | Battery: " << batteryCapacityKWh << " kWh | Range: " << rangePerChargeKm << " km";
    }

  
    int getBatteryStatus() const {
        return 85; 
    }

    ~ElectricTruck() override {
        cout << "[ElectricTruck Destructor] " << registrationNo << endl;
    }
};

// DERIVED CLASS 4: Van 

class Van : public Vehicle {
private:
    int seatingCapacity;
    double mileageKmpl;

public:
    Van(const string& reg, const string& owner, int year, double km, int seating, double mileage)
        : Vehicle(reg, owner, year, km) {
        seatingCapacity = seating;
        mileageKmpl = mileage;
    }

    double fuelCost(double kmToTravel) const override {
       
        double pricePerLitre = 106.00;
        return (kmToTravel / mileageKmpl) * pricePerLitre;
    }

    string vehicleType() const override {
        return "Van";
    }

    void describe() const override {
        Vehicle::describe();
        cout << " | Seats: " << seatingCapacity << " | Mileage: " << mileageKmpl << " kmpl";
    }

    ~Van() override {
        cout << "[Van Destructor] " << registrationNo << endl;
    }
};


//  REPORT FUNCTION

void printFleetReport(const vector<Vehicle*>& fleet, double tripKm) {
    cout << "\n------ FLEET REPORT — Trip Distance: " << tripKm << " km =====" << endl;
    cout << left << setw(12) << "Reg" << setw(18) << "Type" << setw(18) << "Owner" << "Km Driven" << endl;
    
    for (int i = 0; i < fleet.size(); i++) {
        cout << left << setw(12) << fleet[i]->getRegNo()
             << setw(18) << fleet[i]->vehicleType()
             << setw(18) << fleet[i]->getOwnerName()
             << fleet[i]->getKmDriven() << endl;
    }

    cout << "\n-----FUEL / CHARGE COST ESTIMATE -------" << endl;
    
    Vehicle* mostEfficient = nullptr;
    double lowestCost = 99999999.0;
    for (int i = 0; i < fleet.size(); i++) {
        double cost = fleet[i]->fuelCost(tripKm);
        
        cout << fleet[i]->getRegNo() << " (" << fleet[i]->vehicleType() << ") : Rs. " 
             << fixed << setprecision(2) << cost;

        
        ElectricTruck* emp = dynamic_cast<ElectricTruck*>(fleet[i]);
        if (emp != nullptr) {
            cout << " [Battery: " << emp->getBatteryStatus() << "% charged]";
        }
        cout << endl;

        
        if (cost < lowestCost) {
            lowestCost = cost;
            mostEfficient = fleet[i];
        }
    }

    if (mostEfficient != nullptr) {
        cout << "\nMost Efficient Vehicle: " << mostEfficient->getRegNo() 
             << " (" << mostEfficient->vehicleType() << ") — Rs. " << lowestCost 
             << " for " << tripKm << " km\n" << endl;
    }
}


// MAIN PROGRAM

int main() {
    // Part B — Observing stack chain allocation order
    cout << "--- Part B: Stack Object Chain Test ---" << endl;
    {
        ElectricTruck stackTruck("V-ET001", "Green Logistics", 2025, 12000, 5.0, 8.0, 100.0, 400.0);
    } 
    cout << "----------------------------------------\n" << endl;

    // Part C — Managing polymorphic fleet vector
    vector<Vehicle*> fleet;
    
    fleet.push_back(new Car("KA01AA001", "Ramesh Kumar", 2020, 45200, "Petrol", 15.0));
    fleet.push_back(new Truck("MH04BB002", "Shyam Logistics", 2018, 123500, 10.0, 6.0));
    fleet.push_back(new ElectricTruck("GJ07CC003", "Green Fleet Co", 2024, 89000, 4.0, 7.5, 90.0, 350.0));
    fleet.push_back(new Van("DL03DD004", "Anand Travels", 2021, 62000, 8, 12.0));
    fleet.push_back(new Car("KL07EE005", "Sunitha Nair", 2023, 15000, "Diesel", 18.0));

    printFleetReport(fleet, 200.0);

    
    cout << "--- Dynamic Memory Cleanup Trace ---" << endl;
    for (int i = 0; i < fleet.size(); i++) {
        delete fleet[i];
    }
    fleet.clear();

    return 0;
}
