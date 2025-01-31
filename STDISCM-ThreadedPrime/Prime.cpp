#include <iostream>
#include <mutex>

#include "Prime.h"
#include "Time.h"

using namespace std;

mutex coutMutex;

Time globalTime;

void Prime::checkPrime(int start, int end, int thread) 
{
	while (start <= end) {
		int n = isPrime(start);

		if (n != -1) {
            lock_guard<mutex> lock(coutMutex);
            cout << globalTime.getTime() << ": T" << thread << " found prime number: " << n << endl;
		}
		start += 1;
	}
}


int Prime::isPrime(int n) 
{
    if (n <= 1) return -1;  
    if (n == 2) return 2;   
    if (n % 2 == 0) return -1; 

    for (int i = 3; i * i <= n; i += 2) { 
        if (n % i == 0) return -1;
    }

    return n;
}