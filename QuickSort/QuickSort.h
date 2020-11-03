#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <vector>
#include <string>
#include <chrono>

using namespace std;

class QuickSort {
private:
	int arrType; // used to determine if our array will be sorted, reverseSorted, or random : 0, 1, 2, respectively
	vector<int> arr;
	vector<int> generateSorted(int newSize);
	vector<int> generateReverseSorted(int newSize);
	vector<int> generateRandom(int newSize);
	vector<int> setArr(int initArr, int newSize);
	void swap(int idx1, int idx2, vector<int>& heap, int &steps);
	int partition(vector<int>& arr, int low, int high, int &steps);
	long long totalDurationInMicroSecs;
	int totalSteps;
	int size;
public:
	QuickSort();
	QuickSort(int initArr, int newSize);
	int getSize() const;
	long long getTotalTime();
	int getTotalSteps();
	void sort();
	void sortHelper(vector<int>& array, int startIdx, int endIdx, int &steps);
	void printArr() const;
	void resetArr();
	void resetFiftyInstancesTracker();
	void resetSize(int newSize);
	void resetArrType(int initArr);
	void resetSizeAndType(int initArr, int newSize);
	string getInitArrType() const;
};

#endif