#include <iostream>
#include <unordered_set>
#include <string>
#include <algorithm> // Added for all_of

using namespace std;

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
        cout << "The PIN’s too common." << endl;
    } else {
        cout << "I is not  a common  PIN." << endl;
    }

    return 0;
}