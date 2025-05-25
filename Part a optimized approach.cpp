#include <iostream>
#include <unordered_set>
#include <string>
#include <algorithm> 

using namespace std;
// It is the set of most common PIN used by the user it had been taken by the research from various sources
unordered_set<string> commonPins = {
    "1234", "1111", "0000", "1212", "7777", "1004",
    "2000", "4444", "2222", "6969", "9999", "3333",
    "5555", "6666", "1122", "1313", "8888", "4321",
    "2001", "1010"
};

int main() {
    string pin;
    cout << "Enter a 4-digit PIN: ";
    cin >> pin;

    // Check if PIN is 4 digits and all numbers
    if (pin.length() != 4 || !all_of(pin.begin(), pin.end(), ::isdigit)) {
        cout << "Sorry, please enter a 4-digit number." << endl;
        return 1;
    }

    // Check if PIN is common
    if (commonPins.count(pin)) {
        cout << "The PIN is too common." << endl;
    } else {
        cout << "It is not a common PIN." << endl;
    }

    return 0;
}

