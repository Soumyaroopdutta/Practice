#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;


void shuffle(string& s, int i, string& curr, vector<string>& result) {
    if (curr.size() == s.size()) {
        result.push_back(curr);
        return;
    }

    unordered_set<char> seen;
    // each position we have choice of picking each of them.
    for (int j = i; j < (int) s.size(); j++) {
        // prevent duplicates at the same position.
        if (seen.find(s[j]) != seen.end()) {
            continue;
        }
        seen.insert(s[j]);

        char c = s[j];
        s[j] = s[i];

        curr += c;
        shuffle(s, i+1, curr, result);
        curr.pop_back();
        s[i] = s[j];
        s[j] = c;
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
        s = string("1123");
    }

    string x;
    vector<string> result;

    shuffle(s, 0, x, result);
    cout << "results ->" << endl;
    for (auto v : result) {
        cout << v << endl;
    }
    return 1;
}
