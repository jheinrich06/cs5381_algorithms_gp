// intertion_sort_serial_string.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <vector>

using namespace std;

// Function Def
void insertionSort(vector<string>& arr, int n)
{
    int i, j;
    string value;
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
    // Correctness test
    vector<string> arr = { "8", "15", "10", "13", "0",  "110", "11", "3", "5", "6" };
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
        insertionSort(randomChars_gen_small, randomChars_gen_small_n);
        end = chrono::steady_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        //result_times.push_back(elapsed);
        cout << "SmallChar ";
        cout << n_values[i] << " ";
        cout << elapsed << " ";
        //printArrayAndTimeElapsed(randomNumbers_gen_small, randomNumbers_gen_small.size(), elapsed);


        start = chrono::steady_clock::now();
        insertionSort(randomChars_gen_large, randomChars_gen_large_n);
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
