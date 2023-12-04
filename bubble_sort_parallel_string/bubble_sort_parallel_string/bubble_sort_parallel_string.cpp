// bubble_sort_parallel_string.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <vector>
#include <omp.h>
#include <algorithm>
#include <random>
using namespace std;




// Merge Function
void partition(vector<string>& arr, int left_low, int left_high, int right_low, int right_high, int bucket_size) {

    //int tid = omp_get_thread_num();
    //printf("Partition omp thread %d\n", tid);

    if (left_high - left_low + 1 <= bucket_size) {
        for (int i = right_low; i <= right_high; i++) {
            for (int j = left_low; j <= left_high - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    string temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }

            }
            if (arr[left_high] > arr[i]) {
                string temp = arr[i];
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
            partition(arr, left_low, left_middle, right_middle + 1, right_high, bucket_size);
            partition(arr, left_middle + 1, left_high, right_low, right_middle, bucket_size);
        }

    }
}

// Function Def
void bubbleSortParallel(vector<string>& arr, int n, int low, int high, int bucket_size) {

    //int tid = omp_get_thread_num();
    //printf("BubbleSort omp thread %d\n", tid);

    if (1 + high - low <= bucket_size) {
        for (int i = low; i <= high - 1; i++) {
            for (int j = low; j <= low + high - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    string temp = arr[j];
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
void printArrayAndTimeElapsed(vector<string>& arr, int n, float elapsed)
{
    int i;
    for (i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    cout << "Elapsed time in nanoseconds: "
        << elapsed
        << " nanoseconds";
}


// Function to generate alphanumeric lists
std::vector<std::string> generateAlphanumericLists(int size, int val_size) {
    std::vector<std::string> alphanumericLists;
    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, chars.size() - 1);

    for (int i = 0; i < size; ++i) {
        std::string randomString;
        for (int j = 0; j < val_size; ++j) { // Change the length of the strings as needed
            randomString += chars[dis(gen)];
        }
        alphanumericLists.push_back(randomString);
    }

    return alphanumericLists;
}


// Driver code
int main()
{
    /*
    vector<string> arr{ "8", "15", "10", "13", "0",  "110", "11", "3", "5", "6", "55", "44", "33", "22", "66", "77", "88", "99", "98", "97", "87", "76", "65", "54", "43", "12", "92" };
    int length_arr = arr.size();

    auto start = chrono::steady_clock::now();
    bubbleSortParallel(arr, length_arr, 0, length_arr - 1, 7);
    auto end = chrono::steady_clock::now();
    float elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    printArrayAndTimeElapsed(arr, length_arr, elapsed);

    */

    // sequentially run time tests
    vector <float> result_times = {};
    vector<vector<float>> list_of_result_times = {};

    vector<int> n_values = { 100 , 1000, 10000, 100000
    };
    int char_len_short = 7;
    int char_len_long = 14;

    //100 series
    std::vector<string> randomChars_gen_small = generateAlphanumericLists(n_values[0], char_len_short);
    std::vector<string> randomChars_gen_large = generateAlphanumericLists(n_values[0], char_len_long);



    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    float elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    int n_length = n_values.size();

    for (int i = 0; n_length - 1; i++) {
        result_times = {};

        randomChars_gen_small = generateAlphanumericLists(n_values[i], char_len_short);
        randomChars_gen_large = generateAlphanumericLists(n_values[i], char_len_long);


        int randomChars_gen_small_n = randomChars_gen_small.size();
        int randomChars_gen_large_n = randomChars_gen_large.size();



        start = chrono::steady_clock::now();
        bubbleSortParallel(randomChars_gen_small, randomChars_gen_small_n, 0, randomChars_gen_small_n-1, 7);
        end = chrono::steady_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        //result_times.push_back(elapsed);
        cout << "SmallChar ";
        cout << n_values[i] << " ";
        cout << elapsed << " ";
        //printArrayAndTimeElapsed(randomNumbers_gen_small, randomNumbers_gen_small.size(), elapsed);


        start = chrono::steady_clock::now();
        bubbleSortParallel(randomChars_gen_large, randomChars_gen_large_n, 0, randomChars_gen_large_n - 1, 7);
        end = chrono::steady_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        //result_times.push_back(elapsed);
        cout << "LargeChar ";
        cout << n_values[i] << " ";
        cout << elapsed << " ";
        //printArrayAndTimeElapsed(randomNumbers_gen_large, randomNumbers_gen_large.size(), elapsed);

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
