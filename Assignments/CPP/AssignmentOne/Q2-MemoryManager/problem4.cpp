#include<iostream>
using namespace std;

bool parsePacket(const int* rawData, int size, int** outMin, int** outMax){
  
    if(size <= 0){
        return false;
    }

   
    const int* currentMin = &rawData[0];
    const int* currentMax = &rawData[0];

    for(int i = 1; i < size; i++){
        if(*(rawData + i) < *currentMin){
            currentMin = &rawData[i]; 
        }
        if(*(rawData + i) > *currentMax){
            currentMax = &rawData[i];
        }
    }

    
    *outMin = const_cast<int*>(currentMin);
    *outMax = const_cast<int*>(currentMax);

    return true;
}

int main(){
  
    int packet[] = {45, 12, 67, 8, 55, 31};
    int* minPtr = nullptr;
    int* maxPtr = nullptr;
    
    if (parsePacket(packet, 6, &minPtr, &maxPtr)) {
        cout << "Calibration Min : " << *minPtr << endl;
        cout << "Calibration Max : " << *maxPtr << endl;
    }

    return 0;
}
