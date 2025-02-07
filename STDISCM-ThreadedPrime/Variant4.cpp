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
    map<int, int> primeMap;

    atomic<int> currentNumber(2);
	int threadsToMake = threadCount;

    auto worker = [&]() {
        while (true) {
            int numToCheck = currentNumber.fetch_add(1);
            if (numToCheck > primeNum) break;

            atomic<bool> isPrimeFlag(true);
            int foundByThread = -1;

            vector<thread> checkThreads;

			if (threadCount > (numToCheck / 2) ) {
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
				primeMap[numToCheck] = foundByThread;
            }
        }
    };

    thread workerThread(worker);
    workerThread.join();

    cout << "\nFinal List of Prime Numbers Found:\n";
    for (const auto& entry : primeMap) {
        cout << "Thread: " << entry.second << " found Prime: " << entry.first << endl;
    }
}
