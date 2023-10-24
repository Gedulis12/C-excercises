#include <stdio.h>

int quick_sort(int unsorted_arr[], int low, int high);
int partition(int unsorteD_arr[], int low, int high);

int main()
{
    int arr[] = {5, 8, 9, 1, 2, 3, 7, 6, 0, 1, 5, 6};
    for (int i = 0; i < 12; i++)
    {
        printf("unsorted array element %i: %i\n", i, arr[i]);
    }
    quick_sort(arr, 0, 12);
    for (int i = 0; i < 12; i++)
    {
        printf("sorted array element %i: %i\n", i, arr[i]);
    }
}

int quick_sort(int unsorted_arr[], int low, int high)
{
    if (low >= high)
    {
        return 0;
    }

    int pivot_idx = partition(unsorted_arr, low, high);
    quick_sort(unsorted_arr, low, pivot_idx - 1);
    quick_sort(unsorted_arr, pivot_idx + 1, high);
    return 0;
}

// returns the pivot index to use for quick sort function
int partition(int unsorted_arr[], int low, int high)
{
    int pivot = unsorted_arr[high];
    int idx = low - 1;

    for (int i = low; i < high; i++)
    {
        if (unsorted_arr[i] <= pivot) 
        {
            idx ++;
            int temp = unsorted_arr[i];
            unsorted_arr[i] = unsorted_arr[idx];
            unsorted_arr[idx] = temp;
        }
    }
    idx++;
    unsorted_arr[high] = unsorted_arr[idx];
    unsorted_arr[idx] = pivot;

    return idx;
}
