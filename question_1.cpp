#include <iostream>
using namespace std;

// Custom exception class for invalid time values
class InvalidTimeException : public exception {
public:
    const char* what() const throw() {
        return "Invalid time! Hours must be <24 and minutes must be <60";
    }
};

class Time {
private:
    int hour;
    int minute;

    // Private method to validate time values
    void validateTime() {
        if (hour >= 24 || minute >= 60 || hour < 0 || minute < 0) {
            throw InvalidTimeException();
        }
    }

public:
    // Default constructor
    Time() {
        hour = minute = 0;
    }

    // Parameterized constructor with validation
    Time(int h, int m) {
        hour = h;
        minute = m;
        // Normalize time (e.g., 1:70 becomes 2:10)
        if (minute >= 60) {
            hour += minute / 60;
            minute %= 60;
        }
        validateTime(); // Check if time is valid
    }

    // Overloaded + operator for adding two Time objects
    Time operator+(Time T) {
        Time temp;
        temp.minute = minute + T.minute;
        temp.hour = hour + T.hour;

        // Handle minute overflow
        if (temp.minute >= 60) {
            temp.hour += temp.minute / 60;
            temp.minute %= 60;
        }

        // Handle hour overflow (wrap around after 24 hours)
        temp.hour %= 24;

        return temp;
    }

    // Overloaded > operator for comparing two Time objects
    bool operator>(Time T) {
        if (hour > T.hour) return true;
        if (hour == T.hour && minute > T.minute) return true;
        return false;
    }

    // Display method to show time in HH:MM format
    void display() {
        cout << "Time: " << hour << ":"
             << (minute < 10 ? "0" : "") << minute << endl;
    }
};

int main() {
    try {
        int h1, m1, h2, m2;

        // Input first time
        cout << "Enter first time (hours minutes): ";
        cin >> h1 >> m1;
        Time T1(h1, m1);

        // Input second time
        cout << "Enter second time (hours minutes): ";
        cin >> h2 >> m2;
        Time T2(h2, m2);

        // Display input times
        cout << "\nFirst time: ";
        T1.display();
        cout << "Second time: ";
        T2.display();

        // Add times and display result
        Time T3 = T1 + T2;
        cout << "\nAfter addition: ";
        T3.display();

        // Compare times
        if (T1 > T2) {
            cout << "Time 1 is later than Time 2" << endl;
        } else {
            cout << "Time 2 is later than or equal to Time 1" << endl;
        }

    } catch (InvalidTimeException& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
