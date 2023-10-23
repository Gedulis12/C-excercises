#include <stdio.h>

int bubble_sort(int unsorted_arr[], int unsorted_arr_len);

int main()
{
    int array[10] = {5, 8, 7, 9, 0, 1, 2, 6, 5, 3};
    for (int i = 0; i < 10; i++)
    {
        printf("unsorted array element %i: %i\n", i, array[i]);
    }
    bubble_sort(array, 10);
    for (int i = 0; i < 10; i++)
    {
        printf("sorted array element %i: %i\n", i, array[i]);
    }
    return 0;
}

int bubble_sort(int unsorted_arr[], int unsorted_arr_len)
{
    for (int i = 0; i < unsorted_arr_len; i++)
    {
        for (int j = 0; j < (unsorted_arr_len - 1 - i); j++)
        {
            if (unsorted_arr[j] > unsorted_arr[j+1])
            {
                int temp = unsorted_arr[j];
                unsorted_arr[j] = unsorted_arr[j+1];
                unsorted_arr[j+1] = temp;
            }
        }
    }
    return 0;
}
