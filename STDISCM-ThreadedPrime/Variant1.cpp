#include <thread>
#include <vector>
#include <mutex>

#include "Variant1.h"
#include "Prime.h"

void Variant1::Run(int threadCount, int primeNum)
{
	Prime prime;
	vector<thread> threads;
	mutex coutMutex;

	int rangeSize = primeNum / threadCount;

	for (int i = 0; i < threadCount; i++)
	{
		int start = i * rangeSize + 1;
		int end = (i == threadCount - 1) ? primeNum : (i + 1) * rangeSize;

		threads.push_back(thread(&Prime::checkPrimePrint, &prime, start, end, i, ref(coutMutex)));
	}

	for (auto& t : threads) {
		if (t.joinable()) {
			t.join();
		}
	}
};