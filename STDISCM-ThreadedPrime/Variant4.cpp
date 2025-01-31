#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <map>
#include <atomic>

#include "Variant4.h"
#include "Prime.h"

using namespace std;

void Variant4::Run(int threadCount, int primeNum)
{
    Prime prime;
    vector<thread> threads;
    map<int, int> primeMap;
    mutex mapMutex;
    mutex numberMutex;

    atomic<int> currentNumber(2);  // Start checking from 2

    auto worker = [&](int threadId) {
        while (true) {
            int numToCheck = currentNumber.fetch_add(1);
            if (numToCheck > primeNum) break;

            atomic<bool> isPrimeFlag(true);

            vector<thread> checkThreads;
            for (int i = 0; i < threadCount; i++) {
                checkThreads.emplace_back(&Prime::isPrime, &prime, numToCheck, 2 + i, threadCount, ref(isPrimeFlag));
            }

            for (auto& t : checkThreads) {
                t.join();
            }

            if (isPrimeFlag) {
                lock_guard<mutex> lock(mapMutex);
				primeMap[numToCheck] = threadId;
            }
        }
    };

    // Create worker threads
    for (int i = 0; i < threadCount; i++) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    cout << "\nFinal List of Prime Numbers Found:\n";
    for (const auto& entry : primeMap) {
        cout << "Prime: " << entry.first << " found by Thread: " << entry.second << endl;
    }
}
