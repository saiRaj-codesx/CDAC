
#include <iostream>
using namespace std;

class Temprature
{
private:
    double celsius;

public:
    Temprature(double C)
    {
        celsius = C;
    };
    double toFahrenheit() const
    {
        return (celsius * 9 / 5) + 32.0;
    };
    double toKelvin() const
    {
        return celsius + 273.15;
    };
    void displayAll() const
    {
        cout << "Temprature : " << celsius << "C = " << toFahrenheit() << "F = " << toKelvin() << "K" << endl;
    }
};

int main()
{
    double ipCelsius;
    for (int i = 0; i < 4; i++)
    {
        cout << "Enter the Temprature in Celsius : " << endl;
        cin >> ipCelsius;

        if (ipCelsius < -273.15)
        {
            cout << "The entered temprature is below the absolute zero or standard temprature required"<<endl ;
        }
        else
        {
            Temprature t(ipCelsius);
            t.displayAll();
        }
    }
    return 0;
}