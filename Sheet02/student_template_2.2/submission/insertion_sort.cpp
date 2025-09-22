#include "insertion_sort.h"

#include <iostream>
#include <chrono>
#include <ratio>

using namespace std;

using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;
using duration_ms = std::chrono::duration<double, std::milli>;

/* Constant array size of n = 5000 elements for testing purpose */
const int num_array_elements = 5000;

/* Generates an integer array with constant n=5000 elements */
int* generateArray(int from, int multStepFactor)
{
    int* arr = new int[num_array_elements];
    for (int i = 0; i < num_array_elements; i++)
        arr[i] = from + multStepFactor * i;
    return arr;
}

/* Prints an integer array with n Elements to the console */
void printArray(int arr[], int nElements)
{
    for (int i = 0; i < nElements; i++)
        cout << arr[i] << " ";
    cout << endl;
}

/// Insertion sort algorithm sorts given integer array ascending with n elements.
void insertionSort(int arr[], int nElements)
{
    // TODO: implement insertion sort with the use of the std::swap function

}

/* Test insertion sort with two arrays containing 5000 elements ascending and descending and
print out the required time in ms.*/
void testInsertionSort()
{
    int* ascInsertionTest = generateArray(1, 1);
    int* descInsertionTest = generateArray(num_array_elements, -1);

    const time_point start = std::chrono::high_resolution_clock::now();
    insertionSort(ascInsertionTest, num_array_elements);
    const time_point middle = std::chrono::high_resolution_clock::now();
    insertionSort(descInsertionTest, num_array_elements);
    const time_point end = std::chrono::high_resolution_clock::now();

    double ascInsertionTime = duration_ms(middle - start).count();
    double descInsertionTime = duration_ms(end - middle).count();

    cout << "Insertion sorting time for n = " << num_array_elements << ":" << endl;
    cout << "Sorted ascending in " << ascInsertionTime << " ms." << endl;
    cout << "Sorted descending in " << descInsertionTime << " ms." << endl;

    delete[] ascInsertionTest;
    delete[] descInsertionTest;
}
