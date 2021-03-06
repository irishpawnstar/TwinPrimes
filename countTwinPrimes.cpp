/*
This work is licensed under the  Creative Commons Attribution-ShareAlike 4.0 International Licence.
To view of this licence, visit http://creativecommons.org/licenses/by-sa/4.0/.
*/

/*! \class Twin Prime Counter
    \brief  This is a parallel program for counting twin primes less than n. A twin prime is a pair of prime numbers with a gap of two between them. E.G.(3,5),(5,7),(11,13),(17,19),(29,31) .... 
    \author Alan Halpin
    \date 26/02/2021
    \copyright Creative Commons Attribution-ShareAlike 4.0 International Licence 
*/

#include <chrono> // for clock
#include <iostream> // for input
#include <omp.h> // for parallel 
#include <set> // for set DS

using namespace std;

/*! checkPrime */
/*! A simple boolean function to check if the number given is prime or not.*/

bool checkPrime(int number) 
{
        if(number <= 1) // 1 is not prime and primes cannot be negative
        {
            return false;
        }
        for (int i = 2; i < number; i++)
        {
            if(number % i == 0) // If there is no remainder the number is not prime
            {
                return false;
            }
        }
        return true; // Number is prime!
}

/*! twinPrimePrinter */
/*! Using openmp, a specified amount of threads are created. A for loop increments through every number within the search range.
    Each number is checked to be prime or not. Then the next number 2 away is checked to see if it is a twin prime.
    When accessing the variables a lock is used to ensure threads don't block each other. */

int twinPrimePrinter(int range, int threadCount) 
{
    int count = 0;
    set<int> twins;
#pragma omp parallel for num_threads(threadCount) // Create Threads
    for (int i = 2; i < range; i++)
    {
        //std::cout << omp_get_num_threads();
        if(checkPrime(i) == true)
        {
            count+=1;
            if(checkPrime(i+2) == true) 
            {   
                   #pragma omp critical// Only one thread can access variables at once
                    {
                    twins.insert(i);
                    twins.insert(i+2);
                    //std::cout << "(" << i << "," << (i+2) << ")";
                    } 
            }
        }
    }
    cout << "\nTwin Primes; \n"; // Print all twin primes found
    for(auto it = twins.begin(); it != twins.end(); it++)
    {
        std::cout <<  (*it) << " , ";
    }
    return count;
}

/*! main */
/*! The main method, used to track time, take user input and call other methods.*/

int main() 
{
    int input, threadCount;
    std::cout << "Welcome to the twin prime counter!" << "\n";
    std::cout <<"Enter search range: ";
    std::cin >> input;
    std::cout << "Enter number of threads: ";
    std::cin >> threadCount;
    auto start = chrono::steady_clock::now();// Start Clock
    int count = twinPrimePrinter(input, threadCount); // Calls twin prime counter, returns int
    auto end = chrono::steady_clock::now();// End Clock
    std::cout << "\nTime Taken: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms";
    std::cout << "\nTotal Number of Primes : " << count << "\n";
    
    /* // Loop For Tests
    for(int i=0; i<3; i++)
    {
        auto start = chrono::steady_clock::now();// Start Clock
        twinPrimePrinter(1000000, 8);
        auto end = chrono::steady_clock::now();// End Clock
        std::cout << "\nTime Taken: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << "\n";
    } */
    return 0;
}