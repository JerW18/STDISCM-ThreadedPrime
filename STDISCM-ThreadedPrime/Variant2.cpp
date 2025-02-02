#include <iostream>
#include <vector>
#include <thread>
#include <map>
#include <mutex>

#include "Variant2.h"
#include "Prime.h"

void Variant2::Run(int threadCount, int primeNum)
{
    Prime prime;
    vector<thread> threads;
    map<int, int> primeMap; 
    mutex mapMutex;         

    int rangeSize = primeNum / threadCount;

    for (int i = 0; i < threadCount; i++)
    {
        int start = i * rangeSize + 1;
        int end = (i == threadCount - 1) ? primeNum : (i + 1) * rangeSize;

        threads.push_back(thread(&Prime::checkPrimeStore, &prime, start, end, i, ref(primeMap), ref(mapMutex)));
    }

    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    cout << "\nFinal List of Prime Numbers Found:\n";
    for (const auto& entry : primeMap) {
        cout << "Thread: " << entry.second << " found Prime: " << entry.first << endl;
    }
}