#include <iostream>
#include <queue>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <random>
#include <functional>
#include <utility>

using namespace std;


void atm_thread(int atm_id, int max_capacity, queue<int>& q, mutex& q_mutex, condition_variable& cv, mutex& cv_mutex, vector<bool>& atm_busy) {
    while (true) {
        int time_left = 0;
        
        {
            unique_lock<mutex> lock(q_mutex);
            cv.wait(lock, [&]() { return !q.empty() || atm_busy[atm_id]; });
            if (q.empty()) {
                continue;
            }
            int amount = q.front();
            q.pop();
            
            atm_busy[atm_id] = true;
            time_left = rand() % 5 + 1;
            cout << "ATM " << atm_id << " is busy for " << time_left << " seconds with amount " << amount << endl;
        }
        
        this_thread::sleep_for(chrono::seconds(time_left));
        {
            unique_lock<mutex> lock(cv_mutex);
            atm_busy[atm_id] = false;
            cv.notify_one();
            cout << "ATM " << atm_id << " is free now" << endl;
        }
    }
}

void generator_thread(int max_capacity, queue<int>& q, mutex& q_mutex, condition_variable& cv) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(100, 1000);
    while (true) {
        int amount = dis(gen);
        {
            unique_lock<mutex> lock(q_mutex);
            cv.wait(lock, [&]() { return q.size() < max_capacity; });
            q.push(amount);
            cv.notify_one();
            cout << "Request added: " << amount << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main() {
    int cnt_atms, max_capacity;
    cout << "Enter the count of ATMs: ";
    cin >> cnt_atms;
    cout << "Enter the maximum capacity of the cash dispenser: ";
    cin >> max_capacity;

    queue<int> q;
    mutex q_mutex;
    condition_variable q_cv;
    vector<bool> atm_flags(cnt_atms, false);

    thread gen_thread([&]() { generator_thread(max_capacity, q, q_mutex, q_cv); });


    vector<thread> atm_threads;
    for (int i = 0; i < cnt_atms; ++i) {
        atm_threads.emplace_back(atm_thread, i, max_capacity, ref(q), ref(q_mutex), ref(q_cv), ref(atm_flags));
    }

    for (auto& t : atm_threads) {
        t.join();
    }

    gen_thread.join();

    return 0;
}