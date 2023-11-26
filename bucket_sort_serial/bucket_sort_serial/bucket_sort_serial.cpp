// bucket_sort_serial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <vector>
using namespace std;



// Function Def - referenced insertion sort
void insertionSort(vector<int>& arr, int n )
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

// Function Def
void bucketSort(int* arr, int n) {

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
    if (n % 7 == 0) { 
        bucket_count = n / 7; 
    }
    else {
        bucket_count = (n / 7);
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
        buckets[bucket_selection].push_back(arr[i]);
    }
    
    // insertion sort the buckets
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
	bucketSort(arr, length_arr);
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
