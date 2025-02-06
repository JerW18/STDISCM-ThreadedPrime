# Prime Number Multithreading Program
This program utilizes multithreading to find prime numbers within a given range using different task division strategies and output formats.

## Variants
- **Variant 1:**
  - The range of numbers is divided evenly among threads.
  - Each thread checks for prime numbers and immediately prints them.
  - Includes thread ID and timestamp.

- **Variant 2:**
  - The range of numbers is divided evenly among threads.
  - Each thread checks for prime numbers and stores them in a map to be printed at the end.
  - Waits until all threads are done before printing.

- **Variant 3:**
  - The main program assigns all the threads to a number to check for primality.
  - Prime numbers are immediately printed.
  - Includes thread ID and timestamp.

- **Variant 4:**
  - The main program assigns all the threads to a number to check for primality.
  - Prime numbers are stored in a map and printed at the end.
  - Waits until all threads are done before printing.

- **Task Division Schemes:**
  - Straight division of the search range (e.g., for range 1-1000 with 4 threads: 1-250, 251-500, etc.).
  - Linear search where threads handle divisibility testing for individual numbers.

- **Timestamps:**
  - A timestamp is printed at the start and end of every run.
 
## How to Run
1. Double click on the provided `.sln` file and open the project in Visual Studio.
2. Build the project by clicking **Build → Build Solution**.
3. Run the executable by clicking **Debug → Start Debugging**.
4. Enter the desired variant and parameters when prompted.
   - Choose a variant (1-4) based on your desired task division and output format.
   - Open `config.txt` file to input desired number of threads and limit of numbers to search.
       - Current default `4` Threads and `50` Numbers 
5. Make sure that Visual Studio is in `x64 Debug` mode and `ISO C++20 Standard (/std:c++20)` is being used. 

