#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include <sstream>
#include <atomic>
#include <vector>
#include <future>
#include <condition_variable>

using namespace std;

atomic<int> x(0);

mutex mtxA;
mutex mtxB;
condition_variable cv;

bool xGreaterThan10() {
    return x > 10;
}

void helper(string s) {
	auto myid = this_thread::get_id();
	stringstream ss;
	ss << s << " " << myid << " " << ++x << endl;
	string mystring = ss.str();

    cout << mystring;


    x++;

    int y = 0;
    while ((y = try_lock(mtxA, mtxB)) != -1) {
        cout << "failed lock " << y << " " << x++ << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    this_thread::sleep_for(chrono::seconds(2));

    if (x > 5) {
        // it will early wake up, but the CV will lock back
        cv.notify_one();
    }

    mtxA.unlock();
    this_thread::sleep_for(chrono::seconds(2));
    mtxB.unlock();

    cout << "Exiting thread with x = " << x << endl;
}

int helper_task() {
   cout << "Hello from async helper" << ++x << endl;
   std::unique_lock<std::mutex> lck(mtxA);
   cv.wait(lck, xGreaterThan10);
   return ++x;
}

int main(int argc, char* argv[]) {
    int threadCount = 2;
    if (argc > 1) {
       threadCount = atoi(argv[argc - 1]);
    }
    cout << "Thread Count " << threadCount << endl;

    string s = "Hello from thread";
    vector<thread> threadList;

    cout << "start test" << x << endl;
    for (int i = 0; i < threadCount; i++) {
        thread th(helper, s);
        threadList.push_back(move(th));
    }

    cout << "calling async function" << ++x << endl;
    future<int> fut = async(helper_task);
    cout << "Waiting for async to return now " << ++x << endl;
    int ret = fut.get();
    cout << "Async returned " << ret << endl;
    cout << "waiting in parent " << ++x << endl;
    for (auto& th : threadList) {
        th.join();
        cout << "exit " << ++x << endl;
    }

    cout << "End Test" << endl;

    return 1;
}
