#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <vector>
#include <string>

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

// Function to write data to a file
void writeToFile(const std::vector<int>& data, const std::string& fileName) {
    std::ofstream file(fileName);
    if (file.is_open()) {
        for (const auto& value : data) {
            file << value << ",";
        }
        file.close();
        std::cout << "Data written to " << fileName << std::endl;
    } else {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
}

// Function to write alphanumeric data to a file
void writeAlphanumericToFile(const std::vector<std::string>& data, const std::string& fileName) {
    std::ofstream file(fileName);
    if (file.is_open()) {
        for (const auto& value : data) {
            file << value << ",";
        }
        file.close();
        std::cout << "Alphanumeric data written to " << fileName << std::endl;
    } else {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
}

void loopThroughFileGen(int iterations, ) {
    int n_values = [100, 1000, 10000, 100000];
    int large_int = 1000000;
    int small_int = 1000;
    int small_char = 7;
    int large_char = 14;

    int n_length = n_values.size();
    for (i = 1; i < iterations +1; i++) {
        for (j = 0; n_length - 1; j++) {
            string fn_random_numbers_small = "random_numbers_small_" + to_string(n_values[j]) + "_" + to_string(i) + ".txt";
            string fn_random_numbers_large = "random_numbers_large_" + to_string(n_values[j]) + "_" + to_string(i) + ".txt";
            string fn_sorted_numbers = "sorted_numbers_" + to_string(n_values[j]) + "_" + to_string(i) + ".txt";
            string fn_reverse_sorted_numbers = "reverse_sorted_numbers_" + to_string(n_values[j]) + "_" + to_string(i) + ".txt";
            string fn_alphanumeric_lists_small = "alphanumeric_lists_small_" + to_string(n_values[j]) + "_" + to_string(i) + ".txt";
            string fn_alphanumeric_lists_large = "alphanumeric_lists_large_" + to_string(n_values[j]) + "_" + to_string(i) + ".txt";

            std::vector<int> randomNumbers_gen_small = generateRandomNumbers(n_values[j], small_int);
            writeToFile(randomNumbers_gen_small, fn_random_numbers_small);

            std::vector<int> randomNumbers_gen_large = generateRandomNumbers(n_values[j], large_int);
            writeToFile(randomNumbers_gen_large, fn_random_numbers_large);

            std::vector<int> sortedNumbers_gen = generateSortedNumbers(n_values[j]);
            writeToFile(sortedNumbers_gen, fn_sorted_numbers);

            std::vector<int> reverseSortedNumbers_gen = generateReverseSortedNumbers(n_values[j]);
            writeToFile(reverseSortedNumbers_gen, fn_reverse_sorted_numbers);

            std::vector<std::string> alphanumericLists_gen_small = generateAlphanumericLists(n_values[j], small_char);
            writeAlphanumericToFile(alphanumericLists_gen_small, fn_alphanumeric_lists_small);

            std::vector<std::string> alphanumericLists_gen_large = generateAlphanumericLists(n_values[j], large_char);
            writeAlphanumericToFile(alphanumericLists_gen_large, fn_alphanumeric_lists_large);
        }
    }
}

int main() {
    
    loopThroughFileGen(2);

    /*
    int size = 20; // Change the size of data as needed

    std::vector<int> randomNumbers = generateRandomNumbers(size);
    writeToFile(randomNumbers, "random_numbers.txt");

    std::vector<int> sortedNumbers = generateSortedNumbers(size);
    writeToFile(sortedNumbers, "sorted_numbers.txt");

    std::vector<int> reverseSortedNumbers = generateReverseSortedNumbers(size);
    writeToFile(reverseSortedNumbers, "reverse_sorted_numbers.txt");

    std::vector<std::string> alphanumericLists = generateAlphanumericLists(size);
    writeAlphanumericToFile(alphanumericLists, "alphanumeric_lists.txt");
    */
    return 0;
}
