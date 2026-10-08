#include<iostream>
#include<string>
using namespace std;


class Product {
private:
    int productId;
    string name;
    double price;
    int quantity;

public:
   
    Product() {
        productId = 0;
        name = "";
        price = 0.0;
        quantity = 0;
    }

    void acceptDetails() {
        cout << "Enter Product ID: ";
        cin >> productId;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Quantity: ";
        cin >> quantity;
    }

    void displayDetails() const {
        
        cout << productId << "   " << name << "   " << price << "   " << quantity << "   " << totalValue();
    }

    double totalValue() const {
        double ans = price * quantity; 
        return ans;
    }

    bool isLowStock(int threshold) const {
        if(quantity < threshold) {
            return true;
        }
        return false; 
    }

    string getName() const { return name; }
    double getPrice() const { return price; }
};




double reorderCost(int qty, double unitPrice) {
    double total = qty * unitPrice;
    return total;
}

double reorderCost(double qty, double unitPrice) 
{
    return qty * unitPrice;
}

double reorderCost(int qty, double unitPrice, double taxRate) {
    double base = qty * unitPrice;
    double taxAmount = base * (taxRate / 100.0); 
    return base + taxAmount;
}

double applyDiscount(double price, double discountPercent = 10.0) {
    double cut = price * (discountPercent / 100.0);
    return price - cut;
}



int main()
{
    // PART A IMPLEMENTATION
    Product arr[5]; 

    for(int i=0; i<5; i++) {
        cout << "--- Enter Details for Product " << (i+1) << " ---" << endl;
        arr[i].acceptDetails();
    }

    int thresh;
    cout << "\nEnter threshold for low stock check: ";
    cin >> thresh;

    cout << "\n===== INVENTORY REPORT =====" << endl;
    cout << "ID   Name   Price   Qty   Total Value" << endl;
    for(int i=0; i<5; i++) {
        arr[i].displayDetails();
        if(arr[i].isLowStock(thresh)) {
            cout << "  <- LOW STOCK";
        }
        cout << "\n"; 
    }

    double maxVal = -1.0;
    int maxIdx = 0;
    for(int i=0; i<5; i++) {
        if(arr[i].totalValue() > maxVal) {
            maxVal = arr[i].totalValue();
            maxIdx = i;
        }
    }
    cout << "\nHighest Value Product : " << arr[maxIdx].getName() << " (Rs. " << maxVal << ")" << endl;

    cout << "Low Stock (threshold: " << thresh << ") : ";
    bool first = true;
    for(int i=0; i<5; i++) {
        if(arr[i].isLowStock(thresh)) {
            if(!first) {
                cout << ", ";
            }
            cout << arr[i].getName();
            first = false;
        }
    }
    cout << "\n\n";


    // PART B 
    cout << "===== TESTING PART B FUNCTION OVERLOADING =====" << endl;

    double cost1 = reorderCost(10, 15.5);
    cout << "Int qty cost: " << cost1 << "\n";

    double cost2 = reorderCost(4.5, 20.0);
    cout << "Double qty cost: " << cost2 << "\n";

    double cost3 = reorderCost(5, 50.0, 12.5);
    cout << "Cost with tax: " << cost3 << endl;

    cout << "\n--- Testing Default Argument ---" << endl;

    double disp1 = applyDiscount(500.0, 15.0);
    cout << "With 15% discount: " << disp1 << endl;

    double disp2 = applyDiscount(500.0); 
    cout << "With default 10% discount: " << disp2 << endl;

    return 0;
}
