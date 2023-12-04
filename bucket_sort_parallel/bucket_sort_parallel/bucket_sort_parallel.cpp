// bucket_sort_parallel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <vector>
#include <omp.h>
#include <algorithm>
#include <random>
using namespace std;



// Function Def - referenced insertion sort
void insertionSort(vector<int>& arr, int n)
{
    //int tid = omp_get_thread_num();
    //printf("Hello world from omp thread %d\n", tid);
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

// Function Def
void bucketSortParallel(vector<int>& arr, int n, int bucket_size) {

    // Set utility values
    int k = 0;
    int bucket_count = 0;
    int max_val = arr[0];
    int min_val = arr[0];

    // iterate to set max
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    // iterate to find min
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }

    // set bucket size to aim for 7 items per, since this is a reasaonable value in hybrid sorts
    if (n % bucket_size == 0) {
        bucket_count = n / bucket_size;
    }
    else {
        bucket_count = (n / bucket_size);
        bucket_count = bucket_count + 1;
    }

    // grab total value covered across all buckets
    int bucket_delta = max_val - min_val + 1;

    // initialize a vector called buckets with our buckets that hold integers
    vector<int>* buckets = new vector<int>[bucket_count];

    // fill vector with empty dynamic integer arrays up to bucket count
    for (int i = 0; i < bucket_count; i++)
    {
        buckets[i] = vector<int>();
    }

    // split values into their buckets
    for (int i = 0; i < n; i++)
    {
        int bucket_selection = (arr[i] * bucket_count) / bucket_delta;
        if (bucket_selection < 0) {
            bucket_selection = 0;
        }
        if (bucket_selection > bucket_count - 1) {
            bucket_selection -= bucket_selection;
        }
        buckets[bucket_selection].push_back(arr[i]);
    }

    // insertion sort the buckets in parallel
#pragma omp parallel for
    for (int i = 0; i < bucket_count; i++)
    {
        int bucket_size = buckets[i].size();
        insertionSort(buckets[i], bucket_size);
    }

    // dump sorted buckets, sequentially back into array
    for (int i = 0; i < bucket_count; i++) {
        int bucket_size = buckets[i].size();
        for (int j = 0; j < bucket_size; j++) {
            arr[k++] = buckets[i][j];
        }
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
    //Correctness test
    vector<int> arr = { 8, 15, 10, 13, 0,  110, 11,3, 5, 6, 55, 44, 33, 22, 66, 77, 88, 99, 98, 97, 87, 76, 65, 54, 43 };
    int length_arr = arr.size();

    auto start = chrono::steady_clock::now();
    bucketSortParallel(arr, length_arr, 3);
    auto end = chrono::steady_clock::now();
    float elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    printArrayAndTimeElapsed(arr, length_arr, elapsed);
    */

    // sequentially run time tests
    vector <float> result_times = {};
    vector<vector<float>> list_of_result_times = {};

    vector<int> n_values = { 100 , 1000
        , 10000, 100000
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
        bucketSortParallel(randomNumbers_gen_small, randomNumbers_gen_small.size(), 7);
        end = chrono::steady_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        //result_times.push_back(elapsed);
        cout << "RandomSmall";
        cout << n_values[i] << " ";
        cout << elapsed << " ";
        //printArrayAndTimeElapsed(randomNumbers_gen_small, randomNumbers_gen_small.size(), elapsed);


        start = chrono::steady_clock::now();
        bucketSortParallel(randomNumbers_gen_large, randomNumbers_gen_large.size(), 7);
        end = chrono::steady_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        //result_times.push_back(elapsed);
        cout << "RandomLarge";
        cout << n_values[i] << " ";
        cout << elapsed << " ";
        //printArrayAndTimeElapsed(randomNumbers_gen_large, randomNumbers_gen_large.size(), elapsed);


        start = chrono::steady_clock::now();
        bucketSortParallel(sortedNumbers_gen, sortedNumbers_gen.size(), 7);
        end = chrono::steady_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        //result_times.push_back(elapsed);
        cout << "Sorted";
        cout << n_values[i] << " ";
        cout << elapsed << " ";
        //printArrayAndTimeElapsed(sortedNumbers_gen, sortedNumbers_gen.size(), elapsed);


        start = chrono::steady_clock::now();
        bucketSortParallel(reverseSortedNumbers_gen, reverseSortedNumbers_gen.size(), 7);
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
