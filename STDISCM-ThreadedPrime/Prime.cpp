#include <iostream>
#include <mutex>
#include <map>
#include <queue>

#include "Prime.h"
#include "Time.h"

using namespace std;

Time globalTime;

// Prime number checker algorithm for straight division of search range
int Prime::checkPrime(int n)
{
    if (n <= 1) return -1;
    if (n == 2) return 2;
    if (n % 2 == 0) return -1;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return -1;
    }

    return n;
}

void Prime::checkPrimePrint(int start, int end, int thread, mutex& coutMutex)
{
	while (start <= end) {
		int n = checkPrime(start);

		if (n != -1) {
            lock_guard<mutex> lock(coutMutex);
            cout << globalTime.getTime() << ": T" << thread << " found prime number: " << n << endl;
		}
		start += 1;
	}
}

void Prime::checkPrimeStore(int start, int end, int thread, map<int, int>& primeMap, mutex& mapMutex)
{
    while (start <= end) {
        int n = checkPrime(start);

        if (n != -1) {
            {
                lock_guard<mutex> lock(mapMutex);
                primeMap[n] = thread; // Store prime number as key, thread ID as value
            }
        }
        start += 1;
    }
}

// Prime number checker algorithm for divisibility testing of individual numbers
int Prime::isPrime(int n, int start, int step, atomic<bool>& isPrimeFlag) {
    if (n <= 1) return false;

    for (int i = start; i * i <= n; i += step) {
        if (n % i == 0) {
            isPrimeFlag = false;  // Mark number as non-prime
            return false;
        }
    }

    return true;
}
