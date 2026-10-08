#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

// Part A: enum class for HTTP Status Codes
enum class HttpStatus {
    OK = 200,
    Created = 201,
    BadRequest = 400,
    Unauthorized = 401,
    NotFound = 404,
    ServerError = 500
};


void handleResponse(HttpStatus status, const string& endpoint) {
    
    int statusCode = static_cast<int>(status);
    
    cout << "[" << endpoint << "] -> " << statusCode << " ";
    
    switch (status) {
        case HttpStatus::OK:
            cout << "OK : Request successful" << endl;
            break;
        case HttpStatus::Created:
            cout << "Created : Resource created successfully" << endl;
            break;
        case HttpStatus::BadRequest:
            cout << "BadRequest : Bad request parameters" << endl;
            break;
        case HttpStatus::Unauthorized:
            cout << "Unauthorized : Authentication required" << endl;
            break;
        case HttpStatus::NotFound:
            cout << "NotFound : Endpoint does not exist" << endl;
            break;
        case HttpStatus::ServerError:
            cout << "ServerError : Internal server error — retry later" << endl;
            break;
        default:
            cout << "Unknown Status Code" << endl;
            break;
    }
}

// Part B
using Header = pair<string, string>;
using HeaderList = vector<Header>;
using Port = unsigned int;
using IPAddress = string;


typedef unsigned long long RequestId;


void printHeaders(const HeaderList& headers) {
    cout << "Headers:" << endl;
    for (size_t i = 0; i < headers.size(); i++) {
        cout << "  " << headers[i].first << " : " << headers[i].second << endl;
    }
}

int main() {


    // ---  Part A ---
    cout << "--- Part A: Testing HTTP Status Codes ---" << endl;
    handleResponse(HttpStatus::OK, "GET /api/users");
    handleResponse(HttpStatus::Unauthorized, "POST /api/login");
    handleResponse(HttpStatus::NotFound, "GET /api/products/99");
    handleResponse(HttpStatus::ServerError, "POST /api/order");
    cout << endl;


    // --- Part B ---
    cout << "--- Part B: Testing Type Aliases ---" << endl;
    RequestId reqId = 1748293847;
    Port serverPort = 8080;
    IPAddress clientIp = "192.168.1.10"; 
    
    HeaderList myHeaders;
    myHeaders.push_back(make_pair("Content-Type", "application/json"));
    myHeaders.push_back(make_pair("Authorization", "Bearer eyJhbGci..."));
    myHeaders.push_back(make_pair("Accept-Language", "en-US"));
    
    cout << "Request ID : " << reqId << endl;
    cout << "Server Port : " << serverPort << endl;
    printHeaders(myHeaders);
    
    return 0;
}
