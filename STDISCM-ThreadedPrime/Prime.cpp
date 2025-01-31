#include <iostream>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>

#include "Prime.h"

using namespace std;

mutex coutMutex;

void Prime::checkPrime(int start, int end, int thread) {
	while (start <= end) {
		int n = isPrime(start);

		if (n != -1) {
            lock_guard<mutex> lock(coutMutex);
            cout << getTime() << ": T" << thread << " found prime number: " << n << endl;
		}
		start += 1;
	}
}


int Prime::isPrime(int n) {
    if (n <= 1) return -1;  
    if (n == 2) return 2;   
    if (n % 2 == 0) return -1; 

    for (int i = 3; i * i <= n; i += 2) { 
        if (n % i == 0) return -1;
    }

    return n;
}

string Prime::getTime() {
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);

    tm buf;
    localtime_s(&buf, &now_c);

    ostringstream oss;
    oss << put_time(&buf, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
