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

int main()
{
    Product arr[5]; 

    for(int i=0; i<5; i++) {
        cout << "--- Product " << (i+1) << " ---" << endl;
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
    cout << endl;

    return 0;
}
