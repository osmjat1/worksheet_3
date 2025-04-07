#include <iostream>
#include <fstream>
using namespace std;

// Base class: Vehicle
class Vehicle {
protected:
    string registrationNumber;
    string color;

public:
    // Constructor
    Vehicle(string regNum, string col) : registrationNumber(regNum), color(col) {}

    // Method to write vehicle details to a file
    virtual void writeToFile(ofstream& file) const {
        file << "Vehicle Details:" << endl;
        file << "Registration Number: " << registrationNumber << endl;
        file << "Color: " << color << endl;
    }
};

// Derived class: Car
class Car : public Vehicle {
private:
    int numberOfSeats;

public:
    // Constructor
    Car(string regNum, string col, int seats) : Vehicle(regNum, col), numberOfSeats(seats) {}

    // Override method to write car details to a file
    void writeToFile(ofstream& file) const override {
        Vehicle::writeToFile(file); // Call base class method
        file << "Number of Seats: " << numberOfSeats << endl;
        file << "Type: Car" << endl << endl;
    }
};

// Derived class: Bike
class Bike : public Vehicle {
private:
    int engineCapacity; // in CC

public:
    // Constructor
    Bike(string regNum, string col, int capacity) : Vehicle(regNum, col), engineCapacity(capacity) {}

    // Override method to write bike details to a file
    void writeToFile(ofstream& file) const override {
        Vehicle::writeToFile(file); // Call base class method
        file << "Engine Capacity: " << engineCapacity << " CC" << endl;
        file << "Type: Bike" << endl << endl;
    }
};

int main() {
    // Create objects of Car and Bike
    Car car("000012", "Blue", 5);
    Bike bike("00000013", "Red", 200);

    // Get the file name from the user
    string fileName;
    cout << "Enter the file name to save vehicle details (e.g., vehicle_details.txt): ";
    cin >> fileName;

    // Open the file for writing
    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    // Write details of Car and Bike to the file
    car.writeToFile(outFile);
    bike.writeToFile(outFile);

    // Close the file
    outFile.close();

    cout << "Vehicle details have been written to '" << fileName << "'." << endl;

    return 0;
}
