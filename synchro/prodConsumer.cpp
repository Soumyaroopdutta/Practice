#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <chrono>
#include <queue>
using namespace std;

// BUGGY PROGRAM. SOLVE IT
condition_variable cv;
mutex mtx;

int main() {
    int c = 0;
    atomic<bool> done(false);
    queue<int> goods;

    thread producer([&]() {
        for (int i = 0; i < 500; ++i) {
            mtx.lock();
            goods.push(i);
            c++;
            cv.notify_one();
            mtx.unlock();
        }

        done = true;
        cv.notify_one();
        mtx.unlock();
    });

    thread consumer([&]() {
        while (!done) {
            unique_lock<mutex> lck(mtx);
            cv.wait(lck);
            while (!goods.empty()) {
                goods.pop();
                c--;
            }
        }
    });

    producer.join();
    consumer.join();
    cout << "Net: " << c << endl;
}
