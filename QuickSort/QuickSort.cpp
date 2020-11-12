#include "QuickSort.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

QuickSort::QuickSort() {
	arr = generateSorted(100);
	size = 100;
	totalSteps = 0;
	arrType = 0;
	totalDurationInMicroSecs = 0;
}

QuickSort::QuickSort(int initArr, int newSize) {
	size = newSize;
	arrType = initArr;
	totalSteps = 0;
	totalDurationInMicroSecs = 0;
	arr = setArr(initArr, newSize);
}

vector<int> QuickSort::generateSorted(int newSize) {
	vector<int> arr;
	for (int i = 1; i <= newSize; i++) {
		arr.push_back(i);
	}
	return arr;
}

vector<int> QuickSort::generateReverseSorted(int newSize) {
	vector<int> arr;
	for (int i = newSize; i >= 1; i--) {
		arr.push_back(i);
	}
	return arr;
}

vector<int> QuickSort::generateRandom(int newSize) {
	vector<int> arr;
	for (int i = 1; i <= newSize; i++) {
		int randomNumber = (rand() % newSize) + 1;
		arr.push_back(randomNumber);
	}
	return arr;
}

void QuickSort::printArr() const {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl << endl;
}

// used to determine whether our array is going be sorted, reverseSorted, or random before we run a sorting algorithm
vector<int> QuickSort::setArr(int initArr, int newSize) {
	switch (initArr) {
	case 0:
		return generateSorted(newSize);
	case 1:
		return generateReverseSorted(newSize);
	case 2:
		return generateRandom(newSize);
	default:
		return generateSorted(newSize);
	}
}

// used to get the name of the arr type we're sorting
string QuickSort::getInitArrType() const {
	switch (arrType) {
	case 0:
		return "sorted";
	case 1:
		return "reverse sorted";
	case 2:
		return "random";
	default:
		return "";
	}
}

// used to reset how our initial array should look like before sort (sorted, reverseSorted, or random) and rebuilds it
void QuickSort::resetArrType(int initArr) {
	// set arrType
	switch (initArr) {
	case 0:
		arrType = 0;
		break;
	case 1:
		arrType = 1;
		break;
	case 2:
		arrType = 2;
		break;
	default:
		arrType = 0;
		break;
	}
	resetArr();
}

// used for resetting both the initial array type (sorted, reverse sorted, random) and size of array
void QuickSort::resetSizeAndType(int initArr, int newSize) {
	size = newSize;
	resetArrType(initArr);
}

// changes the size property of the Sort object and creates a new vector of newSize
void QuickSort::resetSize(int newSize) {
	size = newSize;
	resetArr();
}
// used to remove the old data from memory and reset the array after every instance run
void QuickSort::resetArr() {
	arr.clear();
	vector<int>().swap(arr);
	arr = setArr(arrType, size);
}

// returns total duration of n runs in microseconds
long long QuickSort::getTotalTime() {
	return totalDurationInMicroSecs;
}

// returns the total steps of n runs
int QuickSort::getTotalSteps() {
	return totalSteps;
}

// gets the size of the array we're working with
int QuickSort::getSize() const {
	return size;
}

// resets the total time of the Sort instance if we're not keeping track of total time for multiple runs
void QuickSort::resetFiftyInstancesTracker() {
	totalDurationInMicroSecs = 0;
	totalSteps = 0;
}


void QuickSort::swap(int idx1, int idx2, vector<int>& array, int &steps) {
	int temp = array[idx1];
	array[idx1] = array[idx2];
	array[idx2] = temp;
	steps += 3;
}

void QuickSort::sort(bool random) {
	high_resolution_clock::time_point startTime = high_resolution_clock::now();
	int steps = 0;
	sortHelper(arr, 0, arr.size() - 1, steps, random);
	high_resolution_clock::time_point endTime = high_resolution_clock::now();
	auto thisDuration = duration_cast<microseconds>(endTime - startTime);
	cout << "Quicksort took " << steps << " number of steps and " << thisDuration.count()
		<< " microseconds for a " << getInitArrType() << " array" << endl;
	totalSteps += steps;
	totalDurationInMicroSecs += thisDuration.count();
}

void QuickSort::randomizedSort() {
	high_resolution_clock::time_point startTime = high_resolution_clock::now();
	int steps = 0;
	
	high_resolution_clock::time_point endTime = high_resolution_clock::now();
	auto thisDuration = duration_cast<microseconds>(endTime - startTime);
	cout << "Randomized quicksort took " << steps << " number of steps and " << thisDuration.count()
		<< " microseconds for a " << getInitArrType() << " array" << endl;
	totalSteps += steps;
	totalDurationInMicroSecs += thisDuration.count();
}

// Generates Random Pivot, swaps pivot with
// end element and calls the partition function
int QuickSort::getRandomPivot(vector<int>& arr, int left, int right, int &steps) {
	int random = left + rand() % (right - left);
	steps++;
	swap(random, right, arr, steps);
	return partition(arr, left, right, steps);
}

void QuickSort::sortHelper(vector<int>& arr, int left, int right, int &steps, bool random) {
	while (left < right) {
		int j = random ? getRandomPivot(arr, left, right, steps) : partition(arr, left, right, steps);
		if (j - left < right - j) {
			sortHelper(arr, left, j - 1, steps, random);
			left = j + 1;
			steps++;
		} else {
			sortHelper(arr, j + 1, right, steps, random);
			right = j - 1;
			steps++;
		}
	}
}

int QuickSort::partition(vector<int>& arr, int left, int right, int &steps) {
	int pivot = arr[right];
	int i = (left - 1);
	for (int j = left; j <= right - 1; j++){
		if (arr[j] < pivot){
			i++;
			swap(i, j, arr, steps);
			steps++;
		}
	}
	swap(i + 1, right, arr, steps);
	return i + 1;
}