#include <iostream>
using namespace std;

int main()
{
    double temperature;
    int status;

    cout << "Enter temperature in Celsius: ";
    cin >> temperature;

    
    if (temperature < 0)
    {
        status = -1;
    }
    else if (temperature < 30)
    {
        status = 0;
    }
    else if (temperature < 45)
    {
        status = 1;
    }
    else if (temperature < 60)
    {
        status = 2;
    }
    else
    {
        status = 3;
    }

    double fahrenheit = (temperature * 9 / 5) + 32;

    
    cout << "Temperature : " << temperature << "C / "
         << fahrenheit << "F" << endl;

  
    switch (status)
    {
    case -1:
        cout << "Status : SENSOR_ERROR" << endl;
        cout << "Action : Sensor fault — check wiring" << endl; 
        break;

    case 0:
        cout << "Status : NORMAL" << endl;
        cout << "Action : No action required" << endl;
        break;

    case 1:
        cout << "Status : WARNING" << endl;
        cout << "Action : Alert sent to supervisor" << endl;
        break;

    case 2:
        cout << "Status : CRITICAL" << endl;
        cout << "Action : Cooling system triggered" << endl;
        break;

    case 3:
        cout << "Status : SHUTDOWN" << endl;
        cout << "Action : Emergency shutdown initiated" << endl;
        break;
    }

  
    string reading = (temperature > 25) ? "Above Average" : "Below Average";

    cout << "Reading : " << reading << endl;

    return 0;
}
