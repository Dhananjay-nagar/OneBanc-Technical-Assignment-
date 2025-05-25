#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>
using namespace std;

// Most commonly used 6-digit PINs (sampled from studies and lists)
const unordered_set<string> COMMON_PINS = {
    "123456", "111111", "000000", "121212", "654321",
    "123123", "666666", "112233", "777777", "999999",
    "159753", "111222", "101010", "222222", "789456"
};

struct Date {
    int day, month, year;
};

string pad(int n) {
    return (n < 10 ? "0" : "") + to_string(n);
}

// Here i have tried to Generate all 6-digit combinations from a base string using permutations
set<string> all_6digit_combos(const string& s) {
    set<string> combos;
    string digits = s;
    sort(digits.begin(), digits.end());
    do {
        if (digits.size() >= 6) {
            combos.insert(digits.substr(0, 6));
        }
    } while (next_permutation(digits.begin(), digits.end()));
    return combos;
}

//  here i have thought if Generating  all possible 6-digit PINs related to a specific date
set<string> get_date_related_pins(const Date& d) {
    set<string> result;
    string dd = pad(d.day);
    string mm = pad(d.month);
    string yy = pad(d.year % 100);
    string yyyy = to_string(d.year);

    vector<string> formats = {
        dd + mm + yy, mm + dd + yy,
        dd + mm + yyyy, mm + dd + yyyy,
        yy + mm + dd, yy + dd + mm,
        dd + yy + mm, mm + yy + dd,
        yyyy + mm, yyyy + dd,
        dd + mm + to_string(d.year), 
        mm + dd + to_string(d.year)
    };

    for (const string& base : formats) {
        if (base.length() >= 6) {
            set<string> combos = all_6digit_combos(base);
            result.insert(combos.begin(), combos.end());
        }
    }

    return result;
}

int main() {
    string pin;
    while (true) {
        cout << "Enter your 6-digit MPIN: ";
        cin >> pin;
        if (pin.length() == 6 && pin.find_first_not_of("0123456789") == string::npos) break;
        cout << "Invalid PIN. Please enter exactly 6 digits.\n";
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
