#include <iostream>

using namespace std;

void helper() {
    cout << "start test" << endl;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
       cout << "Passed Arguments" << endl;
       for (int i = 1; i < argc; i++) {
            cout << argv[i] << endl; 
       }
    }

    helper();
    return 1;
}
