#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include <sstream>
#include <atomic>

using namespace std;

atomic<int> x(0);

mutex mtxA;
mutex mtxB;

void helper(string s) {
	auto myid = this_thread::get_id();
	stringstream ss;
	ss << s << " " << myid << " " << ++x << endl;
	string mystring = ss.str();

    cout << mystring;


    x++;

    int y = 0;
    while ((y = try_lock(mtxA, mtxB)) != -1) {
        cout << "found lock " << y << " " << x++ << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    this_thread::sleep_for(chrono::seconds(2));
    mtxA.unlock();
    this_thread::sleep_for(chrono::seconds(2));
    mtxB.unlock();

    cout << "Exiting thread with x = " << x << endl;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
       cout << "Passed Arguments" << endl;
       for (int i = 1; i < argc; i++) {
            cout << argv[i] << endl;
       }
    }

    string s = "Hello from thread";

    cout << "start test" << endl;
    thread th(helper, s);
    thread th2(helper, s);
    cout << "waiting in parent " << ++x << endl;
    th.join();
    th2.join();
    cout << "exiting" << endl;

    return 1;
}
