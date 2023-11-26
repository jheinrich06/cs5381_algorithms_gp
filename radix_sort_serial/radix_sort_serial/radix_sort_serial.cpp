// radix_sort_serial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>

using namespace std;


// function to count array by digit place
void countSort(int arr[], int n, int digit_place)
{

    // temporary auxillary array
    int* aux_array{ new int[n] {} };
    int occ[10];

    for (int i = 0; i < 10; ++i)
        occ[i] = 0;

    //  save # of occurrences in occ[]
    for (int i = 0; i < n; i++)
        occ[(arr[i] / digit_place) % 10] = occ[(arr[i] / digit_place) % 10] +1;

    // find cumulative count of occurences
    for (int i = 1; i < 10; i++)
        occ[i] += occ[i - 1];

    // fill the aux array, removing occurences
    for (int i = n - 1; i >= 0; i--) {
        aux_array[occ[(arr[i] / digit_place) % 10] - 1] = arr[i];
        occ[(arr[i] / digit_place) % 10] = occ[(arr[i] / digit_place) % 10]-1;
    }

    // Copy aux array sorted by {digit: digit_place} back to arr[]
    for (int i = 0; i < n; i++)
        arr[i] = aux_array[i];
}

// Def function
void radixSort(int array[], int size) {
    // get max
    int max_val = array[0];
    for (int i = 1; i < size; i++)
        if (array[i] > max_val)
            max_val = array[i];

    // run count sort on each digit. Get digit by dividing max
    for (int digit_place = 1; max_val / digit_place > 0; digit_place *= 10)
        countSort(array, size, digit_place);
}


// Print Array
void printArrayAndTimeElapsed(int arr[], int n, float elapsed)
{
    int i;
    for (i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    cout << "Elapsed time in nanoseconds: "
        << elapsed
        << " nanoseconds";
}

// Driver code
int main()
{
    int arr[] = { 8, 15, 10, 13, 0,  110, 11,3, 5, 6 };
    int length_arr = sizeof(arr) / sizeof(arr[0]);

    auto start = chrono::steady_clock::now();
    radixSort(arr, length_arr);
    auto end = chrono::steady_clock::now();
    float elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    printArrayAndTimeElapsed(arr, length_arr, elapsed);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
