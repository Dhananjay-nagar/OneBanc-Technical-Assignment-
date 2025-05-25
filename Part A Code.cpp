#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// List of commonly used PINs----- ---- https://timesofindia.indiatimes.com/technology/tech-tips/10-most-and-least-common-4-digit-pins-is-yours-among-them/articleshow/110277989.cms
const string commonPins[] = {
    "1234", "1111", "0000", "1212", "7777", "1004",
    "2000", "4444", "2222", "6969", "9999", "3333",
    "2001", "1010"
}; 

const int pinCount = sizeof(commonPins) / sizeof(commonPins[0]); 

bool isCommonPIN(const string& pin) {
    for (int i = 0; i < pinCount; ++i) {
        if (commonPins[i] == pin) {
            return true;
        }
    }
    return false;
}

bool isValidPIN(const string& pin) {
    if (pin.length() != 4) return false;
    for (char c : pin) {
        if (!isdigit(c)) return false;
    }
    return true;
}

int main() {
    string pin;
    cout << "Enter a 4-digit PIN: ";
    cin >> pin;

    if (!isValidPIN(pin)) {
        cout << "It do not look like a valid PIN." << endl;
        return 1;
    }

    if (isCommonPIN(pin)) {
        cout << "It is a common PIN." << endl;
    } else {
        cout << "It is not a common PIN." << endl;
    }

    return 0;
}
