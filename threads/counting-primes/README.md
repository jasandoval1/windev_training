## Exercise: Multithreading without Synchronization: Counting Primes

This exercise introduces you to the basics of the Win32 thread API by asking you to design and implement an application that counts prime numbers.

### Procedure

Design and implement a program that counts the number of prime numbers within a specified range. The range of values within which the number of primes should be computed should be configurable as a commandline argument (or arguments). Your program must utilize multiple threads to perform the computation, but the number of threads utilized is at your discretion - this value may be provided at runtime as an additional commandline argument, determined automatically by your application based on the number of system processors, or simply hardcoded to a static value within your program.

For example, an invocation of your program might appear as follows:

```
primes_counter.exe 3 20000000
Total Count: 1271331
```

The above invocation computes the number of primes in the range 3 through 20,000,000.

This exercise is meant only to introduce the fundamentals of the Win32 threading API; aside from the use of `WaitForSingleObject()` / `WaitForMultipleObjects()` to wait for thread completion, there is no need for any explicit synchronization in order to accomplish this task. Indeed, this exercise presents a canonical example of a problem that exhibits _embarrassing parallelism_ - the tasks performed by each thread should be completely independent and should have no need to synchronize their execution with any others. It is up to you to determine how you would like to partition the total volume of work that must be performed between your program's threads.

While nominally a central component, determining the primality of a given number is far from the primary interest of this exericse. For this reason, a simple function (i.e. highly non-optimal) that determines if a given number is prime is provided below. Feel free to use this implementation in your program, or to write your own.

```
bool is_prime(unsigned long long n)
{
    if (n < 3)
    {
        return false;
    }

    unsigned long long limit = (unsigned long long)sqrt(n);
    for (unsigned long long i = 2; i < limit; ++i)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}
```

A sample application that meets the requirements of this exercise is provided in the `reference/` directory; don't refer to it until you have attempted the exercise yourself! The reference program writes some information regarding the execution time of each thread and the overall elapsed execution time of the prime computation to its standard output; such information may prove interesting to analyze across multiple runs but is not required for your implementation.