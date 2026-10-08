#include <iostream>
#include <cstring> 
using namespace std;

class LogBuffer {
private:
    char* buffer;
    int capacity;
    int size;
    static int instanceCount; 
    

    mutable int accessCount;

public:
    // Constructor
    LogBuffer(int cap) {
        capacity = cap;
        size = 0;
        buffer = new char[capacity];
        buffer[0] = '\0'; 
        instanceCount++;
        cout << "[LogBuffer Created] capacity=" << capacity << endl;
    }

    // Copy Constructor (Deep Copy)
    LogBuffer(const LogBuffer& other) {
        capacity = other.capacity;
        size = other.size;
        accessCount = 0; 
        buffer = new char[capacity];
       
        for (int i = 0; i < size; i++) {
            buffer[i] = other.buffer[i];
        }
        buffer[size] = '\0';
        
        instanceCount++;
        cout << "[LogBuffer Deep Copied] capacity=" << capacity << endl;
    }

    
    LogBuffer& operator=(const LogBuffer& other) {
        
        if (this == &other) {
            cout << "[Self-assignment detected — no operation]" << endl;
            return *this;
        }

        
        delete[] buffer;

        
        capacity = other.capacity;
        size = other.size;
        buffer = new char[capacity];
        
        
        for (int i = 0; i < size; i++) {
            buffer[i] = other.buffer[i];
        }
        buffer[size] = '\0';

        cout << "[LogBuffer Assigned]" << endl;
        return *this;
    }

    
    ~LogBuffer() {
        delete[] buffer;
        instanceCount--;
        cout << "[LogBuffer Destroyed]" << endl;
    }

    
    void append(const char* msg) {
        int msgLen = 0;
        while (msg[msgLen] != '\0') {
            msgLen++;
        }

        
        for (int i = 0; i < msgLen; i++) {
            if (size < capacity - 1) {
                buffer[size] = msg[i];
                size++;
            } else {
                break; 
            }
        }
        buffer[size] = '\0';
    }

    // Print function marked as const
    void print() const {
        cout << buffer << endl;
        accessCount++; 
    }

    void clear() {
        size = 0;
        buffer[0] = '\0';
    }

   
    static int getInstanceCount() {
        return instanceCount;
    }

    // Bonus getter
    int getAccessCount() const {
        return accessCount;
    }
};

// Initialize static member variable outside the class structure
int LogBuffer::instanceCount = 0;

int main() {
    // Objective 1 : Basic usage
    LogBuffer log1(256);
    log1.append("Server started on port 8080");
    log1.append(" | Request received from 192.168.1.10");
    log1.print();

    // Objective 2 : Deep copy via copy constructor
    LogBuffer log2 = log1; 
    log2.append(" | Cached response sent");
    cout << "log1 : "; log1.print(); 
    cout << "log2 : "; log2.print();

    // Objective 3 : Copy assignment operator
    LogBuffer log3(128);
    log3 = log1; 
    log3.print();

    // Objective 4 : Self-assignment guard
    log1 = log1;
    log1.print();

    // Objective 5 : Static member
    cout << "Live LogBuffer objects : " << LogBuffer::getInstanceCount() << endl;

    // --- Bonus Execution ---
    cout << "\n--- Bonus Assignment Block ---" << endl;
    const LogBuffer readOnly(log1); 
    readOnly.print();
    readOnly.print();
    readOnly.print();
    cout << "Times printed: " << readOnly.getAccessCount() << endl; 

    return 0;
}

