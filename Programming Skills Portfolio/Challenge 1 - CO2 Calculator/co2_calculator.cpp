
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Gets the journey distance from the user in miles
double getDistance() {
    double distance;

    cout << "Enter distance travelled in miles: ";
    cin >> distance;

    return distance;
}

// Gets the type of fuel used by the vehicle
string getFuelType() {
    string fuel;

    cout << "Enter fuel type (diesel/petrol): ";
    cin >> fuel;

    return fuel;
}

// Calculates CO2 emissions based on distance and fuel type
double calculateCO2(double distance, string fuel) {

    // Assumes the vehicle uses 9.66 litres per 100 miles
    double litresUsed = (distance / 100) * 9.66;

    // Diesel produces 2.68 kg of CO2 per litre
    if (fuel == "diesel") {
        return litresUsed * 2.68;
    }

    // Petrol produces 2.31 kg of CO2 per litre
    else if (fuel == "petrol") {
        return litresUsed * 2.31;
    }

    // Returns -1 if the fuel type is not recognised
    return -1;
}

// Main function controls the program
int main() {

    // Collect journey information
    double distance = getDistance();
    string fuel = getFuelType();

    // Validate the distance entered
    if (!cin || distance < 0) {
        cout << "Invalid distance!" << endl;
    }
    else {
        // Calculate total CO2 emissions
        double result = calculateCO2(distance, fuel);

        // Check whether the fuel type is valid
        if (result == -1) {
            cout << "Invalid fuel type!" << endl;
        }
        else {
            // Display emissions rounded to two decimal places
            cout << fixed << setprecision(2);
            cout << "Total CO2 emissions: "
                 << result << " kg" << endl;
        }
    }

    // Keep the console open when running the EXE directly
    cout << "\nPress Enter to exit...";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    return 0;
}
