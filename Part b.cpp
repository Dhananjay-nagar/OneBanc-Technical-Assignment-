#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

// List of common 4-digit PINs
const unordered_set<string> commonPins = {
    "1234", "1111", "0000", "1212", "7777", "1004",
    "2000", "4444", "2222", "6969", "9999", "3333",
    "5555", "6666", "1122", "1313", "8888", "4321",
    "2001", "1010"
};

struct Date { int day, month, year; };

string pad2(int n) { return (n < 10 ? "0" : "") + to_string(n); }
string year2(int y) { return pad2(y % 100); }

vector<pair<string, string>> likelyPinsFromDate(const Date& d) {
    string dd = pad2(d.day), mm = pad2(d.month), yy = year2(d.year), yyyy = to_string(d.year);
    vector<pair<string, string>> pins = {
        {dd+mm, "DDMM"}, {mm+dd, "MMDD"}, {yy+mm, "YYMM"}, {mm+yy, "MMYY"},
        {dd+yy, "DDYY"}, {yy+dd, "YYDD"}
    };
    if (yyyy.length() == 4) {
        pins.push_back({yyyy.substr(2,2), "YY"});
        pins.push_back({yyyy.substr(0,2), "CC"});
    }
    return pins;
}

bool isSequential(const string& pin) {
    return (pin[1]-pin[0]==1 && pin[2]-pin[1]==1 && pin[3]-pin[2]==1) ||
           (pin[0]-pin[1]==1 && pin[1]-pin[2]==1 && pin[2]-pin[3]==1);
}

bool allSame(const string& pin) {
    return pin[0]==pin[1] && pin[1]==pin[2] && pin[2]==pin[3];
}

bool repeatingPattern(const string& pin) {
    return pin.substr(0,2) == pin.substr(2,2);
}

bool similarToCommon(const string& pin) {
    for (const string& common : commonPins) {
        int same = 0;
        for (int i = 0; i < 4; ++i)
            if (pin[i] == common[i]) same++;
        if (same >= 3) return true;
    }
    return false;
}

bool isValidPin(const string& pin) {
    return pin.size() == 4 && pin.find_first_not_of("0123456789") == string::npos;
}

Date inputDate(const string& label) {
    Date d;
    cout << "Enter your " << label << " (DD MM YYYY): ";
    cin >> d.day >> d.month >> d.year;
    return d;
}

pair<bool, string> matchesDemographic(const string& pin, const vector<Date>& dates, const vector<string>& labels) {
    for (size_t i = 0; i < dates.size(); ++i) {
        auto combos = likelyPinsFromDate(dates[i]);
        for (auto& p : combos) {
            if (pin == p.first) {
                return {true, labels[i] + " (" + p.second + ")"};
            }
        }
    }
    return {false, ""};
}

int main() {
    string pin;

    // This is to get a valid 4-digit PIN
    do {
        cout << "Enter your 4-digit PIN: ";
        cin >> pin;
        if (!isValidPin(pin)) {
            cout << " Please enter exactly 4 digits.\n";
        }
    } while (!isValidPin(pin));

    vector<Date> importantDates;
    vector<string> labels = {"Date of Birth", "Anniversary", "Spouse's Birthday"};

    for (const auto& label : labels) {
        importantDates.push_back(inputDate(label));
    }

    if (commonPins.count(pin)) {
        cout << "Weak PIN — it is most common PIN.\n";
    } else {
        auto match = matchesDemographic(pin, importantDates, labels);
        if (match.first) {
            cout << "Weak — your PIN is tied to personal info: " << match.second << ".\n";
        } else if (allSame(pin)) {
            cout << "Weak — all digits are the same.\n";
        } else if (isSequential(pin)) {
            cout << "Weak — it is a  sequence.So predictable.\n";
        } else if (repeatingPattern(pin)) {
            cout << "Weak — the repeating pattern makes it common .\n";
        } else if (similarToCommon(pin)) {
            cout << "Weak  it is looking like a common  PIN.\n";
        } else {
            cout << "It is Not common PIN.\n";
        }
    }

    return 0;
}
