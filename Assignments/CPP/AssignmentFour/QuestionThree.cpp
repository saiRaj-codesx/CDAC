#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;


// PART A — Abstract DataProcessor Interface

class DataProcessor {
public:
    // Pure virtual functions that child classes MUST implement
    virtual void loadData(const string& source) = 0;
    virtual void processData() = 0;
    virtual void exportResult(const string& destination) = 0;
    virtual string processorType() const = 0;
    virtual int recordCount() const = 0;

   
    virtual void printSummary() const {
        cout << "Processor: " << processorType() << " | Records Processed: " << recordCount() << endl;
    }

   
    virtual ~DataProcessor() = default;
};

// Concrete Class 1: CSVProcessor
class CSVProcessor : public DataProcessor {
private:
    vector<string> records;

public:
    void loadData(const string& source) override {
       
        records.push_back("apple");
        records.push_back("banana");
        records.push_back("cherry");
        records.push_back("date");
        records.push_back("elderberry");
    }

    void processData() override {
       
        for (int i = 0; i < records.size(); i++) {
            for (int j = 0; j < records[i].length(); j++) {
                records[i][j] = toupper(records[i][j]);
            }
        }
    }

    void exportResult(const string& destination) override {
        cout << "[CSV EXPORT -> " << destination << "]" << endl;
        for (int i = 0; i < records.size(); i++) {
            cout << "  Row " << i + 1 << ": " << records[i] << endl;
        }
    }

    string processorType() const override {
        return "CSV Processor";
    }

    int recordCount() const override {
        return records.size();
    }
};

// Concrete Class 2: SensorStreamProcessor
class SensorStreamProcessor : public DataProcessor {
private:
    vector<double> readings;
    double meanVal;
    double minVal;
    double maxVal;

public:
    SensorStreamProcessor() {
        meanVal = 0.0;
        minVal = 0.0;
        maxVal = 0.0;
    }

    void loadData(const string& source) override {
        
        readings.push_back(23.4);
        readings.push_back(21.8);
        readings.push_back(25.1);
        readings.push_back(24.2);
        readings.push_back(22.9);
        readings.push_back(26.0);
        readings.push_back(23.7);
        readings.push_back(24.5);
    }

    void processData() override {
        if (readings.empty()) return;

        double sum = 0.0;
        minVal = readings[0];
        maxVal = readings[0];

        for (int i = 0; i < readings.size(); i++) {
            sum += readings[i];
            if (readings[i] < minVal) minVal = readings[i];
            if (readings[i] > maxVal) maxVal = readings[i];
        }
        meanVal = sum / readings.size();
    }

    void exportResult(const string& destination) override {
        cout << "[SENSOR EXPORT -> " << destination << "]" << endl;
        cout << "  Stats exported successfully to database pipeline." << endl;
    }

    string processorType() const override {
        return "Sensor Stream Processor";
    }

    int recordCount() const override {
        return readings.size();
    }

   
    double getMean() const {
        return meanVal;
    }
};


// PART B — Class Template DataBuffer<T>


/* 
  CRITICAL EXPLANATION COMMENT:
  Template definitions cannot easily be split into a separate .cpp file because C++ compiles 
  files individually. The compiler needs to see the complete implementation of a template to 
  generate the actual code for types like DataBuffer<int> or DataBuffer<string> at compile time. 
  Putting it entirely in the header/single file ensures the code is always visible when used.
*/

template <typename T>
class DataBuffer {
private:
    T* data;       
    int capacity;
    int head;       
    int tail;     
    int count;      
public:
    DataBuffer(int cap) {
        capacity = cap;
        data = new T[capacity];
        head = 0;
        tail = 0;
        count = 0;
    }

    ~DataBuffer() {
        delete[] data;
    }

    void push(const T& value) {
        if (count == capacity) {
           
            data[tail] = value;
           
            tail = (tail + 1) % capacity;
         
            head = (head + 1) % capacity;
        } else {
          
            data[tail] = value;
            tail = (tail + 1) % capacity;
            count++;
        }
    }

    T pop() {
        if (count == 0) {
            throw underflow_error("Buffer is empty");
        }
        T oldestValue = data[head];
        head = (head + 1) % capacity;
        count--;
        return oldestValue;
    }

    T peek() const {
        if (count == 0) {
            throw underflow_error("Buffer is empty");
        }
        return data[head];
    }

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }
    int size() const { return count; }

   
    template <typename U>
    friend ostream& operator<<(ostream& out, const DataBuffer<U>& buf);
};


template <typename U>
ostream& operator<<(ostream& out, const DataBuffer<U>& buf) {
    out << "[";
    int current = buf.head;
    for (int i = 0; i < buf.count; i++) {
        out << buf.data[current];
        if (i < buf.count - 1) {
            out << ", ";
        }
        current = (current + 1) % buf.capacity;
    }
    out << "]";
    return out;
}



// MAIN PROGRAM

int main() {
  
    // Test Part A: Abstract Data Pipelines
  
    cout << "--- Part A: Processing Pipeline ---" << endl;
    
    // UNCOMMENTING THE LINE BELOW WILL CAUSE A COMPILE ERROR
    // Reason: DataProcessor is an abstract class because it has pure virtual functions (= 0).
    // DataProcessor dp; 

    vector<DataProcessor*> pipeline;
    pipeline.push_back(new CSVProcessor());
    pipeline.push_back(new SensorStreamProcessor());

    for (int i = 0; i < pipeline.size(); i++) {
        pipeline[i]->loadData("source_data");
        pipeline[i]->processData();
        pipeline[i]->printSummary();
        pipeline[i]->exportResult("output_dir");
        cout << "---" << endl;
    }


    // Test Bonus: dynamic_cast Safety Check

    cout << "\n--- Bonus: dynamic_cast Check ---" << endl;
    
    /* 
      EXPLANATION COMMENT:
      static_cast tells the compiler to assume the conversion is correct without verification at runtime. 
      If we forced a SensorStreamProcessor pointer into a CSVProcessor pointer using static_cast, 
      it would execute blindly, access garbage memory offsets, and crash the system. 
      dynamic_cast checks the object type safely at runtime. If the types do not match, 
      it cleanly returns a nullptr instead of causing unexpected crashes.
    */
    for (int i = 0; i < pipeline.size(); i++) {
        if (CSVProcessor* csv = dynamic_cast<CSVProcessor*>(pipeline[i])) {
            cout << "Found CSV Processor with " << csv->recordCount() << " records." << endl;
        } 
        else if (SensorStreamProcessor* sensor = dynamic_cast<SensorStreamProcessor*>(pipeline[i])) {
            cout << "Found Sensor Processor — Mean: " << sensor->getMean() << endl;
        }
    }

    // Pipeline Dynamic Memory Cleanup
    for (int i = 0; i < pipeline.size(); i++) {
        delete pipeline[i];
    }
    pipeline.clear();

    // ------------------------------------------
    // Test Part B: Templates Ring Buffer
    // ------------------------------------------
    cout << "\n--- Part B: Circular Buffer Templates ---" << endl;

   
    DataBuffer<int> tickBuffer(5);
    for (int i = 1; i <= 7; i++) {
        tickBuffer.push(i * 10); 
    }
    cout << "Tick Buffer: " << tickBuffer << " (10 and 20 were overwritten)" << endl;

   
    DataBuffer<double> tempBuffer(4);
    tempBuffer.push(36.6); 
    tempBuffer.push(37.1);
    tempBuffer.push(38.2); 
    tempBuffer.push(36.9);
    cout << "Before pop: " << tempBuffer << endl;
    cout << "Popped: " << tempBuffer.pop() << endl;
    cout << "After pop: " << tempBuffer << endl;

   
    DataBuffer<string> logBuffer(3);
    logBuffer.push("INFO: Server started");
    logBuffer.push("WARN: High memory usage");
    logBuffer.push("ERROR: DB connection timeout");
    logBuffer.push("INFO: Retry successful"); 
    cout << "Log Buffer: " << logBuffer << endl;

    return 0;
}
