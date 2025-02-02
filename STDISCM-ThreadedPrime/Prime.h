#pragma once
#include <map>

using namespace std;

class Prime
{
	public:
		int checkPrime(int n);
		void checkPrimePrint(int start, int end, int thread, mutex& countMutex);
		void checkPrimeStore(int start, int end, int thread, map<int, int>& primeMap, mutex& mapMutex);

		void isPrime(int n, int start, int step, int threadId, atomic<bool>& isPrimeFlag, int& foundByThread);
};