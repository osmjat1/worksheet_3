#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

// Custom exception class for invalid marks
class InvalidMarksException : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid marks: Marks must be between 0 and 100.";
    }
};

// Student class to store roll, name, and marks
class Student {
private:
    int roll;
    string name;
    int marks;

public:
    // Constructor
    Student(int r, string n, int m) : roll(r), name(n), marks(m) {
        if (marks < 0 || marks > 100) {
            throw InvalidMarksException();
        }
    }

    // Getters
    int getRoll() const { return roll; }
    string getName() const { return name; }
    int getMarks() const { return marks; }

    // Display student details
    void display() const {
        cout << "Roll: " << roll << ", Name: " << name << ", Marks: " << marks << endl;
    }

    // Write student details to file
    void writeToFile(ofstream& file) const {
        file << roll << " " << name << " " << marks << endl;
    }
};

// Function to read student records from a file
vector<Student> readStudentsFromFile(const string& fileName) {
    ifstream inFile(fileName);
    if (!inFile) {
        throw runtime_error("Error opening file for reading. Make sure the file exists and is accessible.");
    }

    vector<Student> students;
    int roll, marks;
    string name;

    while (inFile >> roll >> name >> marks) {
        try {
            students.push_back(Student(roll, name, marks));
        } catch (const InvalidMarksException& e) {
            cerr << "Error: " << e.what() << " (Skipping invalid record)" << endl;
        }
    }

    inFile.close();
    return students;
}

// Function to write student records to a file
void writeStudentsToFile(const string& fileName, const vector<Student>& students) {
    ofstream outFile(fileName);
    if (!outFile) {
        throw runtime_error("Error opening file for writing.");
    }

    for (const auto& student : students) {
        student.writeToFile(outFile);
    }

    outFile.close();
}

// Function to add a new student record
void addStudent(vector<Student>& students) {
    int roll, marks;
    string name;

    cout << "Enter roll number: ";
    cin >> roll;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter marks: ";
    cin >> marks;

    try {
        students.push_back(Student(roll, name, marks));
        cout << "Student record added successfully." << endl;
    } catch (const InvalidMarksException& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main() {
    // Escape backslashes in the file path
    string fileName = "student.txt"; // Corrected file path
    vector<Student> students;

    try {
        // Read student records from file
        students = readStudentsFromFile(fileName); // Pass the fileName variable
        cout << "Student records read from file:" << endl;
        for (const auto& student : students) {
            student.display();
        }

        // Add new student records
        char choice;
        do {
            cout << "\nDo you want to add a new student record? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                addStudent(students);
            }
        } while (choice == 'y' || choice == 'Y');

        // Save modified records back to file
        writeStudentsToFile(fileName, students); // Pass the fileName variable
        cout << "Student records saved to file." << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
