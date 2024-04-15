#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

#define NUM_THREADS 2

atomic<int> turn;
atomic<bool> flag[NUM_THREADS];

void critical_section(int id) {
    // Peterson's solution entry section
    int other = 1 - id;
    flag[id] = true;
    turn = other;

    // Busy-wait until it's our turn
    while (flag[other] && turn == other)
        ;

    // Critical section
    cout << "Thread " << id << " is in the critical section.\n";

    // Peterson's solution exit section
    flag[id] = false;
}

void thread_function(int id) {
    // Simulate some non-critical work
    this_thread::sleep_for(chrono::milliseconds(100 * id));

    // Enter critical section
    critical_section(id);

    // Simulate some more non-critical work
    this_thread::sleep_for(chrono::milliseconds(100 * id));

    // Exit thread
    cout << "Thread " << id << " exited.\n";
}

int main() {
    // Initialize flags
    flag[0] = false;
    flag[1] = false;

    // Create threads
    thread t[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; ++i) {
        t[i] = thread(thread_function, i);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        t[i].join();
    }

    return 0;
}
