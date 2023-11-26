// bubble_sort_serial_string.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>

using namespace std;

// Function Def
void bubbleSort(string arr[], int n)
{
    int i, j;
    string value;
    for (i = 0; i < (n - 1); i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                value = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = value;
            }
        }
    }

}

// Print Array
void printArrayAndTimeElapsed(string arr[], int n, float elapsed)
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
    string arr[] = { "8", "15", "10", "13", "0",  "110", "11", "3", "5", "6" };
    int length_arr = sizeof(arr) / sizeof(arr[0]);

    auto start = chrono::steady_clock::now();
    bubbleSort(arr, length_arr);
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
