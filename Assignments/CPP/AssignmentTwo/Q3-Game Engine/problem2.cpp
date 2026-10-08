#include<iostream>
using namespace std;

namespace Physics{
double clamp(double val, double min, double max) {
    double finalAns = 0;
    if (val < min) {
        finalAns = min;
    } 
    else if (val > max) {
        finalAns = max;
    } 
    else {
        finalAns = val;
    }
    return finalAns;
}

double lerp(double a, double b, double t)
{
    double result=a+t*(b-a); 
    return result;
}
}

namespace GameMath {
    int clamp(int val, int min, int max)
    {
        if(val < min) return min; 
        if(val > max) return max;
        return val;
    }

    double lerp(double a, double b, double t){
        return a + t * (b - a);
    }
}

int main() 
{
    cout << "  testing explicit namespaces " << endl;

    double v = 25.5;
    double low = 0.0;
    double high = 15.0;
    double physicsResult = Physics::clamp(v, low, high);
    
    int mathResult = GameMath::clamp(3, 5, 10);

    cout << "Physics clamp output: " << physicsResult << "\n"; 
    cout << "GameMath clamp output: " << mathResult << endl;

    cout << "\n   testing block scope " << endl;
    {
        using namespace GameMath;
        
        int temp = 5; 

     
        double res = lerp(10.0, 20.0, 0.5);
        cout << "Lerp inside block: " << res << endl;
    }

    return 0;
}
