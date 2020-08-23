#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <chrono>
#include <queue>
using namespace std;

#define GOOD_COUNT 500

// BUGGY PROGRAM. SOLVE IT
condition_variable cv;
mutex mtx;

int main() {
    int c = 0;
    bool done = false;
    queue<int> goods;

    thread producer([&]() {
        for (int i = 0; i < GOOD_COUNT; ++i) {
            mtx.lock();
            goods.push(i);
            c++;

            /* mark done when the last element is produced */
            if (i == GOOD_COUNT - 1) {
               done = true;
            } 

            cv.notify_one();
            mtx.unlock();
        }

        cout << "Producer Exiting\n";
    });

    thread consumer([&]() {
       unique_lock<mutex> lck(mtx);
       /*
        * check the done flag and the good queue.
        * The producer could have produced everything before
        * the consumer arrived
        *
        * Take a lock on the queue before checking its state.
        */
       while (!done || !goods.empty()) {
         // we have a lock on the queue.
         while (!goods.empty()) {
            goods.pop();
            c--;
         }
         /*
          * If the producer is done producing all good, we 
          * don't need to wait for any more goods.  
          */
         if (!done) {
            cv.wait(lck); // release lock for producer.
         } 
       }

       cout << "Consumer Exiting\n";
    });

    producer.join();
    consumer.join();
    cout << "Net: " << c << endl;
}
