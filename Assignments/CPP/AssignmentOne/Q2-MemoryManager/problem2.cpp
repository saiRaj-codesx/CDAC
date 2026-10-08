#include<iostream>
#include<cmath>
using namespace std;

double computeRMS(double* signal, int n){
   
    double sum = 0;
    for(int i = 0; i < n; i++){
        double square = (*(signal + i)) * (*(signal + i));
        sum += square;
    }
    double avg = sum / n;
    return sqrt(avg);
}

void normalise(double* signal, int n){
    
    double max = fabs(*(signal));
    for(int i = 1; i < n; i++){
        if(max < fabs(*(signal + i))){
            max = fabs(*(signal + i));
        }
    }
    
    for(int i = 0; i < n; i++){
        *(signal + i) /= max;
    }
}

int countZeroCrossings(double* signal, int n){
   
    int count = 0;
    for(int i = 1; i < n; i++){
        if((*(signal + i - 1) > 0 && *(signal + i) < 0) || 
           (*(signal + i - 1) < 0 && *(signal + i) > 0)){
            count++;
        }
    }
    return count;
}

void applyGain(double* signal, int n, double gainFactor){
   
    for(int i = 0; i < n; i++){
        *(signal + i) *= gainFactor;
    }
}

int main(){
  
    const int n = 7;
    double signal[n] = {0.5, -1.2, 0.8, -0.3, 1.0, -0.9, 0.1};
    double gainFactor = 1.5; 

    
    double rms = computeRMS(signal, n);
    cout << "Initial RMS Value         : " << rms << endl;

  
    int crossings = countZeroCrossings(signal, n);
    cout << "Zero Crossings Detected    : " << crossings << endl << endl;
    
   
    cout << "--- Normalisation Stage ---" << endl;
    cout << "Before Normalise : ";
    for(int i = 0; i < n; i++){
        cout << *(signal + i) << " ";
    }
    cout << endl;

    normalise(signal, n);

    cout << "After Normalise  : ";
    for(int i = 0; i < n; i++){
        cout << *(signal + i) << " ";
    }
    cout << endl << endl;

    
    cout << "--- Gain Adjustment Stage ---" << endl;
    cout << "Before Gain      : ";
    for(int i = 0; i < n; i++){
        cout << *(signal + i) << " ";
    }
    cout << endl;

    applyGain(signal, n, gainFactor);

    cout << "After Gain       : ";
    for(int i = 0; i < n; i++){
        cout << *(signal + i) << " ";
    }
    cout << endl;

    return 0;
}
