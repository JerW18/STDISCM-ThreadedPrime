#include <iostream>
#include <thread>
#include <vector>
#include <fstream>

#include "Time.h"
#include "Variant1.h"
#include "Variant2.h"
#include "Variant3.h"
#include "Variant4.h"

using namespace std;

int main()
{
    Time globalTime;

    int choice;
    bool cont = true;

    // Open File
    ifstream inputFile("config.txt");
    if (!inputFile) {
        cout << "Error opening file!" << endl;
        cont = false;
    }

    // End if file doesn't exist or error opening file
    if (!cont) {
        cout << "\nPress enter to exit...";
        cin.get();

        return 1;
    }

    string label1, label2;

    int threadCount = 0;
    int primeLimit = 0;
    
    // Get file contents
    if (!(inputFile >> label1 >> threadCount) || threadCount <= 0) {
        cout << "Invalid input for thread count! Must be a positive integer." << endl;
        cont = false;
    }

    if (!(inputFile >> label2 >> primeLimit) || primeLimit <= 0) {
        cout << "Invalid input for prime limit! Must be a positive integer." << endl;
        cont = false;
    }

    inputFile.close();

    // End if negative inputs
    if (!cont) {
        cout << "\nPress enter to exit...";
        cin.get();

        return 1;
    }

    // Start Main Program
    cout << "Choose a variant to run:\n";
    cout << "1. Divided evenly among threads. Prints number immediately if prime. (A1 B1)\n";
    cout << "2. Divided evenly among threads. Prints result after all primes are found. (A1 B2)\n";
    cout << "3. All threads check one number. Prints number immediately if prime. (A2 B1)\n";
    cout << "4. All threads check one number. Prints result after all primes are found. (A2 B2)\n";
    cout << "Enter number of your choice: ";

    while (true) {
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a valid number: ";
        }
        else {
            break;
        }
    }

    cout << "\n" << globalTime.getTime() << ": Starting prime number search..." << endl << endl;

    // Variant 1: The range of numbers is divided evenly among threads, and each thread checks for prime numbers and immediately prints them.
    if (choice == 1) {
        Variant1 variant1;
        variant1.Run(threadCount, primeLimit);
    }
    // Variant 2: The range of numbers is divided evenly among threads, and each thread checks for prime numbers and stores them in a map to be printed at the end.
    else if (choice == 2) {
        Variant2 variant2;
        variant2.Run(threadCount, primeLimit);
    }
	// Variant 3: The main program assigns all the thread to a number to check if it is prime or not and immediately prints the prime numbers.
    else if (choice == 3) {
        Variant3 variant3;
        variant3.Run(threadCount, primeLimit);
    }
    // Variant 4: The main program assigns all the thread to a number to check if it is prime or not and stores them in a map to be printed at the end.
    else if (choice == 4) {
        Variant4 variant4;
        variant4.Run(threadCount, primeLimit);
    }

    cout << "\n" << globalTime.getTime() << ": Prime number search complete." << endl;

    cout << "\nPress enter to exit...";
    cin.ignore();
    cin.get();

    return 0;
}
