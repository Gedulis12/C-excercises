#include <stdio.h>
#include <time.h>

#define ELEMENTS 1000000 // size of elemetnts in a lost of test data

int binsearch(int x, int v[], int n); // original implementation
int binsearch2(int x, int v[], int n); // new function

int main()
{
    int test_data[ELEMENTS];
    clock_t time_taken;
    int ret;

    /* test data */
    for (int i = 0; i < ELEMENTS; i++)
    {
        test_data[i] = i;
    }

    /*  Output approximation of time taken
        for 100,000 iterations of binsearch() */

    for (int i = 0, time_taken = clock(); i < ELEMENTS; i++)
    {
        ret = binsearch(i, test_data, ELEMENTS);
    }
        time_taken = clock() - time_taken;

        printf("binsearch() took %lu clocks (%lu seconds)\n",
           (unsigned long) time_taken,
           (unsigned long) time_taken / CLOCKS_PER_SEC);

    /*  Output approximation of time taken
        for 100,000 iterations of binsearch2() */

    for (int i = 0, time_taken = clock(); i < ELEMENTS; i++)
    {
        ret = binsearch2(i, test_data, ELEMENTS);
    }
        time_taken = clock() - time_taken;

        printf("binsearch2() took %lu clocks (%lu seconds)\n",
           (unsigned long) time_taken,
           (unsigned long) time_taken / CLOCKS_PER_SEC);

    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (x < v[mid])
        {
            high = mid - 1;
        }
        else if (x > v[mid])
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

int binsearch2(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    mid = (low+high) / 2;
    while (low <= high && x != v[mid])
    {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    if (x == v[mid])
        return mid;
    else
        return -1;
}
