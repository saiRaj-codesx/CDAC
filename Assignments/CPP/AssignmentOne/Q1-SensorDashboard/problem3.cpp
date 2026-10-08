#include <iostream>
using namespace std;

void hottestRoom(double arr[3][3])
{
    double max = arr[0][0];
    int floor = 1;
    int room = 1;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (max < arr[i][j])
            {
                max = arr[i][j];
                floor = i + 1;
                room = j + 1;
            }
        }
    }

    cout << "Hottest Room  : Floor " << floor << ", Room " << room << " -> " << max << "°C" << endl;
}

void hottestFloor(double arr[3][3])
{
    double max = (arr[0][0] + arr[0][1] + arr[0][2]) / 3.0;
    int floor = 1;

    for (int i = 1; i < 3; i++)
    {
        double sum = 0;
        for (int j = 0; j < 3; j++)
        {
            sum += arr[i][j];
        }

        double avg = sum / 3.0;

        if (avg > max)
        {
            max = avg;
            floor = i + 1;
        }
    }

    cout << "Hottest Floor : Floor " << floor << " (avg " << max << "°C)" << endl;
}

void warnings(double arr[3][3])
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (arr[i][j] >= 30.0)
            {
                count++;
            }
        }
    }
    cout << "Rooms at WARNING or above : " << count << endl;
}

int main()
{
    double arr[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> arr[i][j];
        }
    }

    cout << "\n  Room1   Room2   Room3" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "Floor " << i + 1 << "  : ";
        for (int j = 0; j < 3; j++)
        {
            cout << arr[i][j] << "\t ";
        }
        cout << endl;
    }
    cout << endl;

    hottestRoom(arr);
    hottestFloor(arr);
    warnings(arr);

    return 0;
}
