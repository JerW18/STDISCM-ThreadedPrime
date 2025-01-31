#include <iostream>
#include <thread>
#include <vector>

#include "Prime.h"
#include "Time.h"

using namespace std;

int main()
{
	
	Prime prime;
	Time globalTime;

	vector<thread> threads;

	cout << globalTime.getTime() << ": Starting prime number search..." << endl << endl;

	int threadCount = 4;
	int primeNum = 2000;
	int rangeSize = primeNum / threadCount;

	for (int i = 0; i < threadCount; i++)
	{
		int start = i * rangeSize + 1;
		int end = (i == threadCount - 1) ? primeNum : (i + 1) * rangeSize;

		threads.push_back(thread(&Prime::checkPrime, &prime, start, end, i));
	}

	for (auto& t : threads) {
		if (t.joinable()) {
			t.join();
		}
	}

	cout << "\n" << globalTime.getTime() << ": Prime number search complete." << endl;

	cout << "\nPress enter to end...";
	getchar();
}
