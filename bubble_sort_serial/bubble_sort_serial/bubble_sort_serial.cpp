// bubble_sort_serial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <vector>

using namespace std;

// Function Def
void bubbleSort(vector<int>& arr, int n)
{
    int i, value, j;
    for (i = 0; i < (n-1); i++) {
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


using namespace std;

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
    int length_arr =arr.size();

    auto start = chrono::steady_clock::now();
    bubbleSort(arr, length_arr);
    auto end = chrono::steady_clock::now();
    float elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    printArrayAndTimeElapsed(arr, length_arr, elapsed);
    */

    vector <float> result_times = {};
    vector<vector<float>> list_of_result_times = {};

    vector<int> n_values = { 100, 1000, 10000, 100000};
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
            //result_times = {};

            randomNumbers_gen_small = generateRandomNumbers(n_values[i], small_int);
            randomNumbers_gen_large = generateRandomNumbers(n_values[i], large_int);
            sortedNumbers_gen = generateSortedNumbers(n_values[i]);
            reverseSortedNumbers_gen = generateReverseSortedNumbers(n_values[i]);
            
            auto start = chrono::steady_clock::now();
            bubbleSort(randomNumbers_gen_small, randomNumbers_gen_small.size());
            auto end = chrono::steady_clock::now();
            float elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            //result_times.push_back(elapsed);
            cout << "RandomSmall";
            cout << n_values[i] << " ";
            cout << elapsed << " ";


            start = chrono::steady_clock::now();
            bubbleSort(randomNumbers_gen_large, randomNumbers_gen_large.size());
            end = chrono::steady_clock::now();
            elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            //result_times.push_back(elapsed);
            cout << "RandomLarge";
            cout << n_values[i] << " ";
            cout << elapsed << " ";


            start = chrono::steady_clock::now();
            bubbleSort(sortedNumbers_gen, sortedNumbers_gen.size());
            end = chrono::steady_clock::now();
            elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            //result_times.push_back(elapsed);
            cout << "Sorted";
            cout << n_values[i] << " ";
            cout << elapsed << " ";


            start = chrono::steady_clock::now();
            bubbleSort(reverseSortedNumbers_gen, reverseSortedNumbers_gen.size());
            end = chrono::steady_clock::now();
            elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            //result_times.push_back(elapsed);
            cout << "ReverseSorted";
            cout << n_values[i] << " ";
            cout << elapsed << " ";

            //list_of_result_times.push_back(result_times);
        }

        /*
        int i;
        for (i = 0; i < list_of_result_times.size(); i++) {
            for (int j = 0; i < result_times.size(); j++) {
            cout << list_of_result_times[i][j] << " ";
        cout << endl;
            }
        }

        
    auto start = chrono::steady_clock::now();
    bubbleSort(randomNumbers_gen_small, randomNumbers_gen_small.size());
    auto end = chrono::steady_clock::now();
    float elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    result_times.push_back(elapsed);

    start = chrono::steady_clock::now();
    bubbleSort(randomNumbers_gen_large, randomNumbers_gen_large.size());
    end = chrono::steady_clock::now();
    elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    result_times.push_back(elapsed);

    start = chrono::steady_clock::now();
    bubbleSort(sortedNumbers_gen, sortedNumbers_gen.size());
    end = chrono::steady_clock::now();
    elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    result_times.push_back(elapsed);

    start = chrono::steady_clock::now();
    bubbleSort(reverseSortedNumbers_gen, reverseSortedNumbers_gen.size());
    end = chrono::steady_clock::now();
    elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    result_times.push_back(elapsed);

     int i;
        for (i = 0; i < result_times.size(); i++)
            cout << result_times[i] << " ";
        cout << endl;

    */


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
