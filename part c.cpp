#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>
using namespace std;

const unordered_set<string> COMMON_PINS = {
    "1234", "1111", "0000", "1212", "7777", "1004",
    "2000", "4444", "2222", "6969", "9999", "3333",
    "5555", "6666", "1122", "1313", "8888", "4321",
    "2001", "1010"
};

struct Date {
    int day, month, year;
};

string pad(int n) {
    return (n < 10 ? "0" : "") + to_string(n);
}

// Generate all 4-digit combinations from a base string using permutations
set<string> all_4digit_combos(const string& s) {
    set<string> combos;
    string digits = s;
    sort(digits.begin(), digits.end());
    do {
        combos.insert(digits.substr(0, 4));
    } while (next_permutation(digits.begin(), digits.end()));
    return combos;
}

// Generate all possible 4-digit PINs related to a specific date
set<string> get_date_related_pins(const Date& d) {
    set<string> result;
    string dd = pad(d.day);
    string mm = pad(d.month);
    string yy = pad(d.year % 100);
    string yyyy = to_string(d.year);

    vector<string> formats = {
        dd + mm, mm + dd, yy + mm, mm + yy,
        dd + yy, yy + dd, dd + mm + yy, mm + dd + yy,
        dd + mm + yyyy, mm + dd + yyyy, yyyy
    };

    for (const string& base : formats) {
        if (base.length() >= 4) {
            set<string> combos = all_4digit_combos(base);
            result.insert(combos.begin(), combos.end());
        }
    }

    return result;
}

int main() {
    string pin;
    while (true) {
        cout << "Enter your 4-digit MPIN: ";
        cin >> pin;
        if (pin.length() == 4 && pin.find_first_not_of("0123456789") == string::npos) break;
        cout << "Invalid PIN. Please enter exactly 4 digits.\n";
    }

    Date dob_self, dob_spouse, anniversary;
    cout << "Enter your Date of Birth (DD MM YYYY): ";
    cin >> dob_self.day >> dob_self.month >> dob_self.year;
    cout << "Enter your Wedding Anniversary (DD MM YYYY): ";
    cin >> anniversary.day >> anniversary.month >> anniversary.year;
    cout << "Enter your Spouse's Date of Birth (DD MM YYYY): ";
    cin >> dob_spouse.day >> dob_spouse.month >> dob_spouse.year;

    vector<string> reasons;

    if (COMMON_PINS.count(pin)) {
        reasons.push_back("COMMONLY_USED");
    }

    if (get_date_related_pins(dob_self).count(pin)) {
        reasons.push_back("DEMOGRAPHIC_DOB");
    }

    if (get_date_related_pins(dob_spouse).count(pin)) {
        reasons.push_back("DEMOGRAPHIC_DOB_SPOUSE");
    }

    if (get_date_related_pins(anniversary).count(pin)) {
        reasons.push_back("DEMOGRAPHIC_ANNIVERSARY");
    }

    if (reasons.empty()) {
        cout << "Strength: STRONG" << endl;
        cout << "Reasons: []" << endl;
    } else {
        cout << "Strength: WEAK" << endl;
        cout << "Reasons: [";
        for (size_t i = 0; i < reasons.size(); ++i) {
            cout << reasons[i];
            if (i < reasons.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    return 0;
}
