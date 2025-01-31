#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>

#include "Variant3.h"
#include "Prime.h"
#include "Time.h"

using namespace std;

void Variant3::Run(int threadCount, int primeNum)
{
    Prime prime;
	Time globalTime;
    vector<thread> threads;
    mutex coutMutex;

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
				lock_guard<mutex> lock(coutMutex);
                cout << globalTime.getTime() << ": T" << threadId << " found prime number: " << numToCheck << endl;
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
};
