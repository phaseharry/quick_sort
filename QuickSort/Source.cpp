#include "QuickSort.h"

#include <iostream>
#include <chrono>
#include <string>

using namespace std;

void runForN(int n, QuickSort &run, bool random);
void run50Random(QuickSort &run, bool random);

int main() {
	srand((unsigned)time(0));
	QuickSort run = QuickSort();
	runForN(100, run, false);
	runForN(200, run, false);
	runForN(300, run, false);
	runForN(400, run, false);
	runForN(500, run, false);
	runForN(1000, run, false);
	runForN(4000, run, false);
	runForN(10000, run, false);
	return 0;
}

void runForN(int n, QuickSort &run, bool random) {
	cout << "running for size n: " << n << endl;
	run.resetSizeAndType(0, n);
	run.sort(random); // sort an already sorted array
	run.resetArrType(1); // changing init array to a reversely sorted array
	run.sort(random); // sort a reverely sorted array
	run.resetArrType(2); // changing init array to a random array
	run.sort(random); // sorting a random array
	run.resetFiftyInstancesTracker(); // resetting the totalTime tracker in run object to prepare for the 50x timer run
	run.resetArr(); // resetting the array so we can a totally random initial array
	run50Random(run, random);
}

void run50Random(QuickSort &run, bool random) {
	for (int i = 1; i <= 50; i++) {
		run.sort(random);
		run.resetArr();
	}
	cout << "50 runs of quick sort on a " << run.getInitArrType() << " array with an initial size of " << run.getSize() << " took a total of " << run.getTotalSteps() << " steps and "
		<< run.getTotalTime() << " microseconds." << endl;
}