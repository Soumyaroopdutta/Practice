#include <iostream>
#include <vector>
#include <string>

using namespace std;

void genAllSubsets(vector<int>& set, int i, vector<int>& curr, vector<vector<int>>& result) {
    if (i >= (int) set.size()) {
        result.push_back(curr); 
        return;
    }

    // each step we either select the number or we don't
    // 1. Don't Include
    genAllSubsets(set, i+1, curr, result);
    // 2. Include
    curr.push_back(set[i]);
    genAllSubsets(set, i+1, curr, result);
    curr.pop_back();
}

void helper(vector<int>& input) {
    cout << "Return all subsets" << endl;
    vector<vector<int>> result;
    vector<int> curr;
    genAllSubsets(input, 0, curr, result);

    int i = 0;
    for (auto v : result){
        cout << i << ". "; 
        for (auto e : v)  {
            cout << e;
        }
        i++;
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    vector<int> input;
    if (argc > 1) {
       cout << "Passed Arguments" << endl;
       for (int i = 1; i < argc; i++) {
            input.push_back(atoi(argv[i]));
            cout << input.back() << endl;
       }
    }

    helper(input);
    return 1;
}
