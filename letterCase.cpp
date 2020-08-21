#include <iostream>
#include <vector>
#include <string>

using namespace std;

void letterCase(string& s, int i, string& curr, vector<string>& result) {
    if (i >= (int) s.size()) {
        result.emplace_back(curr);
        return;
    }

    // check if digit.
    if (isdigit(s[i])) {
        curr += s[i];
        letterCase(s, i+1, curr, result);
        curr.pop_back();
    } else {
        curr += toupper(s[i]);
        letterCase(s, i+1, curr, result);
        curr.pop_back();

        curr += tolower(s[i]);
        letterCase(s, i+1, curr, result);
        curr.pop_back();
    }
}

int main(int argc, char* argv[]) {
    string s;
    if (argc > 1) {
       cout << "Passed Arguments" << endl;
       for (int i = 1; i < argc; i++) {
            s = string(argv[i]);
            cout << s  << endl;
       }
    } else {
        s = string("He1l0");
    }

    string x;
    vector<string> result;

    letterCase(s, 0, x, result);
    cout << "results ->" << endl;
    for (auto v : result) {
        cout << v << endl;
    }
    return 1;
}
