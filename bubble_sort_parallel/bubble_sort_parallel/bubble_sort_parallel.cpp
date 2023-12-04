// bubble_sort_parallel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <vector>
#include <omp.h>
#include <algorithm>
#include <random>
using namespace std;




// Merge Function
void partition(vector<int>& arr, int left_low, int left_high, int right_low, int right_high, int bucket_size) {
    
    //int tid = omp_get_thread_num();
    //printf("Partition omp thread %d\n", tid);
    
    if (left_high - left_low + 1 <= bucket_size) {
        for (int i = right_low; i <= right_high; i++) {
            for (int j = left_low; j <= left_high - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }

            }
            if (arr[left_high] > arr[i]) {
                int temp = arr[i];
                arr[i] = arr[left_high];
                arr[left_high] = temp;
            }
        }
    }
    else {
        int left_middle = (left_low + left_high) / 2;
        int right_middle = (right_low + right_high) / 2;

#pragma omp parallel
        {
            partition(arr, left_low, left_middle, right_low, right_middle, bucket_size);
            partition(arr, left_middle + 1, left_high, right_middle + 1, right_high, bucket_size);
        }


#pragma omp parallel
        {
            partition(arr, left_low, left_middle, right_middle +1, right_high, bucket_size);
            partition(arr, left_middle + 1, left_high, right_low, right_middle, bucket_size);
        }

    }
}

// Function Def
void bubbleSortParallel(vector<int>& arr, int n, int low, int high, int bucket_size) {

    //int tid = omp_get_thread_num();
    //printf("BubbleSort omp thread %d\n", tid);

    if (1 + high - low <= bucket_size) {
        for (int i = low; i <= high - 1; i++) {
            for (int j = low; j <= low + high - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
    else {
        int middle = (low + high) / 2;
        partition(arr, low, middle, middle + 1, high, bucket_size);


#pragma omp parallel 
        {
            bubbleSortParallel(arr, middle - low + 1, low, middle, bucket_size);
            bubbleSortParallel(arr, high - middle, middle + 1, high, bucket_size);
        }
    }
}



// Print Array
void printArrayAndTimeElapsed(vector<int>& arr, int n, float elapsed)
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
    vector<int> arr{ 8, 15, 10, 13, 0,  110, 11,3, 5, 6, 55, 44, 33, 22, 66, 77, 88, 99, 98, 97, 87, 76, 65, 54, 43, 12, 92 };
    int length_arr = arr.size();

    auto start = chrono::steady_clock::now();
    bubbleSortParallel(arr, length_arr, 0, length_arr - 1, 7);
    auto end = chrono::steady_clock::now();
    float elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    printArrayAndTimeElapsed(arr, length_arr, elapsed);
    */

    vector <float> result_times = {};
    vector<vector<float>> list_of_result_times = {};

    vector<int> n_values = { 100, 1000, 10000, 100000 };
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

        auto start = chrono::steady_clock::now();
        bubbleSortParallel(randomNumbers_gen_small, randomNumbers_gen_small.size(), 0, randomNumbers_gen_small.size() -1, 7);
        auto end = chrono::steady_clock::now();
        float elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        //result_times.push_back(elapsed);
        cout << "RandomSmall";
        cout << n_values[i] << " ";
        cout << elapsed << " ";


        start = chrono::steady_clock::now();
        bubbleSortParallel(randomNumbers_gen_large, randomNumbers_gen_large.size(), 0, randomNumbers_gen_large.size() -1, 7);
        end = chrono::steady_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        //result_times.push_back(elapsed);
        cout << "RandomLarge";
        cout << n_values[i] << " ";
        cout << elapsed << " ";


        start = chrono::steady_clock::now();
        bubbleSortParallel(sortedNumbers_gen, sortedNumbers_gen.size(), 0, sortedNumbers_gen.size() -1, 7);
        end = chrono::steady_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        //result_times.push_back(elapsed);
        cout << "Sorted";
        cout << n_values[i] << " ";
        cout << elapsed << " ";


        start = chrono::steady_clock::now();
        bubbleSortParallel(reverseSortedNumbers_gen, reverseSortedNumbers_gen.size(), 0, reverseSortedNumbers_gen.size() -1, 7);
        end = chrono::steady_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        //result_times.push_back(elapsed);
        cout << "ReverseSorted";
        cout << n_values[i] << " ";
        cout << elapsed << " ";

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
