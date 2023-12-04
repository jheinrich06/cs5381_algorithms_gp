// insertion_sort_serial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

// Function Def
void insertionSort(vector<int>& arr, int n)
{
    int i, value, j;
    for (i = 1; i < n; i++) {
        value = arr[i]; //grab current value
        j = i - 1; // grab index lower than i
        while (j >= 0 && arr[j] > value) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = value;
    }
}

// Print Array
void printArrayAndTimeElapsed(vector<int> arr, int n, float elapsed)
{
    int i;
    for (i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    cout << "Elapsed time in nanoseconds: "
        << elapsed
        << " nanoseconds";
}

// Function to generate random numbers
std::vector<int> generateRandomNumbers(int size, int val_size) {
    std::vector<int> randomNumbers;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, val_size); // Change the range as needed

    for (int i = 0; i < size; ++i) {
        randomNumbers.push_back(dis(gen));
    }

    return randomNumbers;
}

// Function to generate sorted numbers
std::vector<int> generateSortedNumbers(int size) {
    std::vector<int> sortedNumbers;
    for (int i = 1; i <= size; ++i) {
        sortedNumbers.push_back(i);
    }
    return sortedNumbers;
}

// Function to generate reverse sorted numbers
std::vector<int> generateReverseSortedNumbers(int size) {
    std::vector<int> reverseSortedNumbers;
    for (int i = size; i > 0; --i) {
        reverseSortedNumbers.push_back(i);
    }
    return reverseSortedNumbers;
}

// Driver code
int main()
{

    /*
    vector<int> arr = { 8, 15, 10, 13, 0,  110, 11,3, 5, 6 };
    int length_arr = arr.size();

    auto start = chrono::steady_clock::now();
    insertionSort(arr, length_arr);
    auto end = chrono::steady_clock::now();
    float elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    printArrayAndTimeElapsed(arr, length_arr, elapsed);
    */

    // sequentially run time tests
    vector <float> result_times = {};
    vector<vector<float>> list_of_result_times = {};

    vector<int> n_values = { 100 , 1000, 10000, 100000
    };
    int large_int = 1000000;
    int small_int = 1000;

    //100 series
    std::vector<int> randomNumbers_gen_small = generateRandomNumbers(n_values[0], small_int);
    std::vector<int> randomNumbers_gen_large = generateRandomNumbers(n_values[0], large_int);
    std::vector<int> sortedNumbers_gen = generateSortedNumbers(n_values[0]);
    std::vector<int> reverseSortedNumbers_gen = generateReverseSortedNumbers(n_values[0]);

    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    float elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    int n_length = n_values.size();

    for (int i = 0; n_length - 1; i++) {
        result_times = {};

        randomNumbers_gen_small = generateRandomNumbers(n_values[i], small_int);
        randomNumbers_gen_large = generateRandomNumbers(n_values[i], large_int);
        sortedNumbers_gen = generateSortedNumbers(n_values[i]);
        reverseSortedNumbers_gen = generateReverseSortedNumbers(n_values[i]);

        start = chrono::steady_clock::now();
        insertionSort(randomNumbers_gen_small, randomNumbers_gen_small.size());
        end = chrono::steady_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        //result_times.push_back(elapsed);
        cout << "RandomSmall";
        cout << n_values[i] << " ";
        cout << elapsed << " ";
        //printArrayAndTimeElapsed(randomNumbers_gen_small, randomNumbers_gen_small.size(), elapsed);


        start = chrono::steady_clock::now();
        insertionSort(randomNumbers_gen_large, randomNumbers_gen_large.size());
        end = chrono::steady_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        //result_times.push_back(elapsed);
        cout << "RandomLarge";
        cout << n_values[i] << " ";
        cout << elapsed << " ";
        //printArrayAndTimeElapsed(randomNumbers_gen_large, randomNumbers_gen_large.size(), elapsed);


        start = chrono::steady_clock::now();
        insertionSort(sortedNumbers_gen, sortedNumbers_gen.size());
        end = chrono::steady_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        //result_times.push_back(elapsed);
        cout << "Sorted";
        cout << n_values[i] << " ";
        cout << elapsed << " ";
        //printArrayAndTimeElapsed(sortedNumbers_gen, sortedNumbers_gen.size(), elapsed);


        start = chrono::steady_clock::now();
        insertionSort(reverseSortedNumbers_gen, reverseSortedNumbers_gen.size());
        end = chrono::steady_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        //result_times.push_back(elapsed);
        cout << "ReverseSorted";
        cout << n_values[i] << " ";
        cout << elapsed << " ";
        //printArrayAndTimeElapsed(reverseSortedNumbers_gen, reverseSortedNumbers_gen.size(), elapsed);

        //list_of_result_times.push_back(result_times);

    }

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
