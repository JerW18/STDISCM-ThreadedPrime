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

    atomic<int> currentNumber(2);
    int threadsToMake = threadCount;

    auto worker = [&]() {
        while (true) {
            int numToCheck = currentNumber.fetch_add(1);
            if (numToCheck > primeNum) break;

            atomic<bool> isPrimeFlag(true);
            int foundByThread = -1;

            vector<thread> checkThreads;

            if (threadCount > (numToCheck / 2)) {
                threadsToMake = numToCheck / 2;
            }
            else
            {
                threadsToMake = threadCount;
            }

            for (int i = 0; i < threadsToMake; i++) {
                checkThreads.emplace_back(&Prime::isPrime, &prime, numToCheck, 2 + i, threadCount, i, ref(isPrimeFlag), ref(foundByThread));
            }

            for (auto& t : checkThreads) {
                t.join();
            }

            if (isPrimeFlag && foundByThread != -1) {
                cout << globalTime.getTime() << ": T" << foundByThread << " found prime number: " << numToCheck << endl;
            }
        }
    };

    thread workerThread(worker);
    workerThread.join();
}
