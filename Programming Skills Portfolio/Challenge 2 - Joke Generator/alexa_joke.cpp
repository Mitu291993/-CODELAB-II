
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
using namespace std;

int main() {
    vector<string> jokes;
    string line, input;

    // Open the file containing the jokes
    ifstream file("randomJokes.txt");

    // Check if the file opened successfully
    if (!file.is_open()) {
        cout << "Error: Cannot open randomJokes.txt\n";
        return 1;
    }

    // Read valid jokes and store them in a vector
    while (getline(file, line)) {
        if (line.find('?') != string::npos) {
            jokes.push_back(line);
        }
    }

    file.close();

    // Check if any jokes were loaded
    if (jokes.empty()) {
        cout << "No jokes found in the file.\n";
        return 1;
    }

    // Set up random joke selection
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> randomIndex(
        0, static_cast<int>(jokes.size()) - 1
    );

    cout << "===== ALEXA JOKE GENERATOR =====\n";

    // Keep running until the user chooses to quit
    while (true) {
        cout << "\nType 'Alexa, tell me a joke' or 'quit': ";

        if (!getline(cin, input)) {
            break;
        }

        // Exit when the user types quit
        if (input == "quit") {
            cout << "Goodbye!\n";
            break;
        }

        if (input == "Alexa, tell me a joke") {
            // Select a random joke from the vector
            string joke = jokes[randomIndex(generator)];

            // Find the question mark separating the joke
            size_t position = joke.find('?');

            // Separate the setup and punchline
            string setup = joke.substr(0, position + 1);
            string punchline = joke.substr(position + 1);

            // Display the setup first
            cout << "\nAlexa: " << setup << endl;

            // Wait for Enter before revealing the punchline
            cout << "\nPress Enter for the punchline...";
            if (!getline(cin, input)) {
                break;
            }

            // Display the punchline
            cout << "Alexa: " << punchline << endl;
        }
        else {
            cout << "Please enter the correct phrase.\n";
        }
    }

    return 0;
}
