#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <stdexcept>

using namespace std;


struct Statistics {
	int comparisons;
	int swaps;
};

// INSERTION_SORT-------------------------------------------------------
Statistics insertionSort(vector<int> vec)
{
	Statistics stats = { 0 , 0 };
	int n = vec.size();

	//Algorithm
	for (int i = 1; i < n; i++) {
		int sorted = i - 1; // index of the last element in the sorted array
		while (sorted > -1 && vec[sorted] > vec[sorted + 1]) {
			stats.comparisons++;
			int temp = vec[sorted];
			vec[sorted] = vec[sorted + 1];
			vec[sorted + 1] = temp;
			stats.swaps++;
			sorted--;
		}
		// We count the last comparison when sorted becomes -1
		stats.comparisons++;
	}
	return stats;
}
// SELECTION_SORT-------------------------------------------------------

Statistics selectionSort(vector<int> vec)
{
	Statistics stats = { 0 , 0 };
	int n = vec.size();

	//Algorithm
	for (int i = 0; i < n - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < n; j++)
		{
			stats.comparisons++;
			if (vec[minIndex] > vec[j])
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			stats.swaps++;
			int temp = vec[minIndex];
			vec[minIndex] = vec[i];
			vec[i] = temp;
		}
	}
	return stats;
}

// BUBBLE_SORT----------------------------------------------------------
Statistics bubbleSort(vector<int> vec)
{
	Statistics stats = { 0 , 0 };

	int length = vec.size();

	//Algorithm
	while (length != 0) {
		int maxIndex = 0; // index of the last item that was moved
		for (int i = 1; i < length; i++) {
			stats.comparisons++;
			if (vec[i - 1] > vec[i]) {
				int temp = vec[i - 1];
				vec[i - 1] = vec[i];
				vec[i] = temp;

				maxIndex = i; // updated index of the last item that was moved
				stats.swaps++;
			}
		}
		length = maxIndex;
	}

	return stats;

	// The bubble sorting algorithm, even with optimization, has quadratic complexity(O(n^2))

}

// SHAKER_SORT--------------------------------------------------
Statistics shakerSort(vector<int> vec) {
	Statistics stats = { 0, 0 };

	//Algorithm
	int left = 0;
	int right = vec.size() - 1;
	bool exchanged; // Flag for checking the exchange

	do {
		exchanged = false;

		// Passage from left to right
		for (int i = left; i < right; i++) {
			stats.comparisons++;
			if (vec[i] > vec[i + 1]) {
				stats.swaps++;
				swap(vec[i], vec[i + 1]);
				exchanged = true;
			}
		}

		right--; // Reducing the right border

		// Passageway from right to left
		for (int i = right; i > left; i--) {
			stats.comparisons++;
			if (vec[i] < vec[i - 1]) {
				stats.swaps++;
				swap(vec[i], vec[i - 1]);
				exchanged = true;
			}
		}

		left++; // Increasing the left border

	} while (exchanged); // We continue while there are exchanges

	return stats;
}

// SHELL_SORT--------------------------------------------------
Statistics shellSort(vector<int> vec) {
	Statistics stats = { 0, 0 };
	int n = vec.size();

	//Algorithm
	for (int step = n / 2; step > 0; step /= 2) {
		for (int i = step; i < n; i++) {
			for (int j = i - step; j >= 0 && vec[j] > vec[j + step]; j -= step) {
				stats.comparisons++;
				stats.swaps++;
				int temp = vec[j];
				vec[j] = vec[j + step];
				vec[j + step] = temp;
			}
			//Counting the comparison for the last element
			stats.comparisons++;
		}
	}

	return stats;
}

// BINARY_INSERTION_SORT--------------------------------------------------
Statistics binaryInsertionSort(vector<int> vec) {
	Statistics stats = { 0, 0 };
	int n = vec.size();

	//Algorithm
	int left, right, middle;
	for (int i = 1; i < n; i++) {
		if (vec[i - 1] > vec[i]) {
			stats.comparisons++;
			int buffer = vec[i];
			left = 0;
			right = i - 1;
			do {
				stats.comparisons++;
				middle = left + (right - left) / 2;
				if (vec[middle] < buffer)
				{
					left = middle + 1;  // If the middle element is smaller, move the left border to the right
				}
				else {
					right = middle - 1; // If the middle element is greater than or equal to, shift the right border to the left
				}
			} while (left <= right);
			// Moving elements to make room for buffer insertion
			for (int j = i - 1; j >= left; j--) {
				stats.swaps++;
				vec[j + 1] = vec[j]; // Moving the elements to the right
			}
			// Inserting the saved element into its position
			vec[left] = buffer;
		}
	}
	return stats;
}

// HEAP_SORT---------------------------------------------------

// Heapify function to maintain the heap property
void heapify(vector<int>& vec, int n, int i, Statistics& stats)
{
	int largest = i; // Initialize largest as root

	int l = 2 * i + 1; // Left child index

	int r = 2 * i + 2; // Right child index
	
	if (l < n && vec[l] > vec[largest])
	{
		largest = l;
		stats.comparisons++;
	}

	if (r < n && vec[r] > vec[largest])
	{
		largest = r;
		stats.comparisons++;
	}

	// If largest is not root
	if (largest != i)
	{
		int temp = vec[i];
		vec[i] = vec[largest];
		vec[largest] = temp;
		stats.swaps++;
		heapify(vec, n, largest, stats);
	}
}
Statistics  heapSort(vector<int>& vectorhelp)
{
	Statistics stats = { 0, 0 };
	vector<int> vec = vectorhelp;
	int n = vec.size();

	// Build a maxheap
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(vec, n, i, stats);
	}

	// One by one extract elements from the heap
	for (int i = n - 1; i > 0; i--)
	{
		// Move current root to the end 
		int buffer = vec[0];
		vec[0] = vec[i];
		vec[i] = buffer;
		stats.swaps++;
		heapify(vec, i, 0, stats);
	}
	return stats;
}

// QUICK_SORT--------------------------------------------------
int partOfQuickSort(vector<int>& vec, int left, int right, Statistics& stats) {
	int pivot = vec[(left + right) / 2]; // Selection of the reference element

	while (left <= right) {
		while (vec[left] < pivot) {
			stats.comparisons++;
			left++;
		}
		stats.comparisons++; 
		while (vec[right] > pivot) {
			stats.comparisons++;
			right--;
		}
		stats.comparisons++;

		// Checking whether the items need to be exchang
		if (left <= right && vec[left] == vec[right]) {
			// If the elements are equal, just shift the pointers
			left++;
			right--;
		}
		else if (left <= right) {
			int temp = vec[left];
			vec[left] = vec[right];
			vec[right] = temp;
			stats.swaps++;
			left++;
			right--;
		}
	}
	return left;
}

void quickSort(vector<int>& vec, int start, int end, Statistics& stats) {
	if (start >= end) {
		return; // If the array consists of a single element or is empty, complete
	}
	int rightStart = partOfQuickSort(vec, start, end, stats);
	// Recursively sorting the left part of the array
	quickSort(vec, start, rightStart - 1, stats);
	// Recursively sort the right part of the array
	quickSort(vec, rightStart, end, stats);
}

// Wrapper function for initializing statistics and starting sorting
Statistics quickSort(vector<int>& vec) {
	Statistics stats = { 0, 0 };
	quickSort(vec, 0, vec.size() - 1, stats);
	return stats;
}



int main()
{
	cout << "Hello, what would you like to do next? ";
	cout << "If you want to enter the data manually yourself, then press 0 on the keyboard, ";
	cout << "if you want us to use ready - made arrays for you, then press 1" << endl << endl;
	char character;
	character = cin.get();
	cin.ignore();
	cout << endl << endl << endl;
	//------------------------------------------------------------------------------------

	if (character == '0') {
		// RANDOM VECTOR
		vector<int> vectorRandom;
		const int MAX_SIZE = 200;

		cout << "Enter " << MAX_SIZE << " integers:" << endl;

		for (int i = 0; i < MAX_SIZE; ++i) {
			int number;

			cout << "number" << i + 1 << ":";
			if (!(cin >> number)) {
				cerr << "Incorrect number input. " << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				--i;
				continue;
			}

			vectorRandom.push_back(number);
		}

		// SORTED VECTOR
		vector<int> vectorSorted;

		cout << "Enter " << MAX_SIZE << " numbers in ascending order:" << endl;

		for (int i = 0; i < MAX_SIZE; ++i) {
			int number;

			cout << "number" << i + 1 << ":";
			if (!(cin >> number)) {
				cerr << "Incorrect number input. " << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				--i;
				continue;
			}

			vectorSorted.push_back(number);
		}

		// REVERSE VECTOR
		vector<int> vectorReverse;

		cout << "Enter " << MAX_SIZE << " numbers in descending order:" << endl;

		for (int i = 0; i < MAX_SIZE; ++i) {
			int number;

			cout << "number" << i + 1 << ":";
			if (!(cin >> number)) {
				cerr << "Incorrect number input. " << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				--i;
				continue;
			}

			vectorReverse.push_back(number);
		}
		////////////////////////////////////////////////////////////////////////////

		cout << endl;
		cout << setw(40) << "TABLE OF SORTING RESULTS:" << endl << endl;
		cout << "The first number is comparisons, the second is permutations" << endl;
		cout << "_______________________________________________________________________________________________________________________________________________________" << endl;
		cout << setw(40) << "Random vector" << setw(46) << "Sorted vector" << setw(52) << "Reverse vector" << endl;




		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
		cout << "SelectionSort:" << setw(11) << "|" << setw(36) << "|" << setw(47) << "|" << endl;
		Statistics stats = selectionSort(vectorRandom);
		cout << setw(35) << stats.comparisons << " " << stats.swaps;
		stats = selectionSort(vectorSorted);
		cout << setw(40) << stats.comparisons << " " << stats.swaps;
		stats = selectionSort(vectorReverse);
		cout << setw(45) << stats.comparisons << " " << stats.swaps << endl;


		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
		cout << "BubbleSort:" << setw(14) << "|" << setw(36) << "|" << setw(47) << "|" << endl;
		stats = bubbleSort(vectorRandom);
		cout << setw(35) << stats.comparisons << " " << stats.swaps;
		stats = bubbleSort(vectorSorted);
		cout << setw(40) << stats.comparisons << " " << stats.swaps;
		stats = bubbleSort(vectorReverse);
		cout << setw(45) << stats.comparisons << " " << stats.swaps << endl;


		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
		cout << "ShakerSort:" << setw(14) << "|" << setw(36) << "|" << setw(47) << "|" << endl;
		stats = shakerSort(vectorRandom);
		cout << setw(35) << stats.comparisons << " " << stats.swaps;
		stats = shakerSort(vectorSorted);
		cout << setw(40) << stats.comparisons << " " << stats.swaps;
		stats = shakerSort(vectorReverse);
		cout << setw(45) << stats.comparisons << " " << stats.swaps << endl;


		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
		cout << "ShellSort:" << setw(15) << "|" << setw(36) << "|" << setw(47) << "|" << endl;
		stats = shellSort(vectorRandom);
		cout << setw(35) << stats.comparisons << " " << stats.swaps;
		stats = shellSort(vectorSorted);
		cout << setw(40) << stats.comparisons << " " << stats.swaps;
		stats = shellSort(vectorReverse);
		cout << setw(45) << stats.comparisons << " " << stats.swaps << endl;


		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
		cout << "BinaryInsertionSort:" << setw(5) << "|" << setw(36) << "|" << setw(47) << "|" << endl;
		stats = binaryInsertionSort(vectorRandom);
		cout << setw(35) << stats.comparisons << " " << stats.swaps;
		stats = binaryInsertionSort(vectorSorted);
		cout << setw(40) << stats.comparisons << " " << stats.swaps;
		stats = binaryInsertionSort(vectorReverse);
		cout << setw(45) << stats.comparisons << " " << stats.swaps << endl;


		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
		cout << "InsertionSort:" << setw(11) << "|" << setw(36) << "|" << setw(47) << "|" << endl;
		stats = insertionSort(vectorRandom);
		cout << setw(35) << stats.comparisons << " " << stats.swaps;
		stats = insertionSort(vectorSorted);
		cout << setw(40) << stats.comparisons << " " << stats.swaps;
		stats = insertionSort(vectorReverse);
		cout << setw(45) << stats.comparisons << " " << stats.swaps << endl;


		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
		cout << "HeapSort:" << setw(16) << "|" << setw(36) << "|" << setw(47) << "|" << endl;
		stats = heapSort(vectorRandom);
		cout << setw(35) << stats.comparisons << " " << stats.swaps;
		stats = heapSort(vectorSorted);
		cout << setw(40) << stats.comparisons << " " << stats.swaps;
		stats = heapSort(vectorReverse);
		cout << setw(45) << stats.comparisons << " " << stats.swaps << endl;



		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
		cout << "QuickSort:" << setw(15) << "|" << setw(36) << "|" << setw(47) << "|" << endl;
		stats = quickSort(vectorRandom);
		cout << setw(35) << stats.comparisons << " " << stats.swaps;
		stats = quickSort(vectorSorted);
		cout << setw(40) << stats.comparisons << " " << stats.swaps;
		stats = quickSort(vectorReverse);
		cout << setw(45) << stats.comparisons << " " << stats.swaps << endl;
		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;


	}
	else if(character == '1'){

		string pathRev = "reverse.txt";
		string pathSor = "sorted.txt";
		string pathRan = "random.txt";


		// RANDOM VECTOR-------------------------------------------
		ifstream fin(pathRan);

		if (!fin.is_open()) {
			throw runtime_error("File opening error: " + pathRan);
			return 1;
		}
		else {
			cout << "File " << pathRan << " opened successfully!" << endl;
		}


		vector<int> vectorRandom;
		int number;
		try {
			while (fin >> number) {
				vectorRandom.push_back(number);
			}
		}
		catch (const exception& e) {
			fin.close();
			throw runtime_error("Error reading from a file: " + string(e.what()));
		}

		fin.close();

		if (vectorRandom.empty()) {
			throw runtime_error("The file is empty or contains invalid data");
		}



		// SORTED VECTOR-------------------------------------------
		fin.open(pathSor);

		if (!fin.is_open()) {
			throw runtime_error("File opening error: " + pathSor);
			return 1;
		}
		else {
			cout << "File " << pathSor << " opened successfully!" << endl;
		}


		vector<int> vectorSorted;

		try {
			while (fin >> number) {
				vectorSorted.push_back(number);
			}
		}
		catch (const exception& e) {
			fin.close();
			throw runtime_error("Error reading from a file: " + string(e.what()));
		}

		fin.close();

		if (vectorSorted.empty()) {
			throw runtime_error("The file is empty or contains invalid data");
		}


		// REVERSE VECTOR-------------------------------------------
		fin.open(pathRev);

		if (!fin.is_open()) {
			throw runtime_error("File opening error: " + pathRev);
			return 1;
		}
		else {
			cout << "File " << pathRev << " opened successfully!" << endl;
		}


		vector<int> vectorReverse;
		try {
			while (fin >> number) {
				vectorReverse.push_back(number);
			}
		}
		catch (const exception& e) {
			fin.close();
			throw runtime_error("Error reading from a file: " + string(e.what()));
		}

		fin.close();

		if (vectorReverse.empty()) {
			throw runtime_error("The file is empty or contains invalid data");
		}

		cout << "_____________________________________|" << endl;





		cout << endl;
		cout << setw(40) << "TABLE OF SORTING RESULTS:" << endl << endl;
		cout << "The first number is comparisons, the second is permutations" << endl;
		cout << "_______________________________________________________________________________________________________________________________________________________" << endl;
		cout << setw(40) << "Random vector" << setw(46) << "Sorted vector" << setw(52) << "Reverse vector" << endl;




		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
		cout << "SelectionSort:" << setw(11) << "|" << setw(36) << "|" << setw(47) << "|" << endl;
		Statistics stats = selectionSort(vectorRandom);
		cout << setw(35) << stats.comparisons << " " << stats.swaps;
		stats = selectionSort(vectorSorted);
		cout << setw(40) << stats.comparisons << " " << stats.swaps;
		stats = selectionSort(vectorReverse);
		cout << setw(45) << stats.comparisons << " " << stats.swaps << endl;


		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
		cout << "BubbleSort:" << setw(14) << "|" << setw(36) << "|" << setw(47) << "|" << endl;
		stats = bubbleSort(vectorRandom);
		cout << setw(35) << stats.comparisons << " " << stats.swaps;
		stats = bubbleSort(vectorSorted);
		cout << setw(40) << stats.comparisons << " " << stats.swaps;
		stats = bubbleSort(vectorReverse);
		cout << setw(45) << stats.comparisons << " " << stats.swaps << endl;


		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
		cout << "ShakerSort:" << setw(14) << "|" << setw(36) << "|" << setw(47) << "|" << endl;
		stats = shakerSort(vectorRandom);
		cout << setw(35) << stats.comparisons << " " << stats.swaps;
		stats = shakerSort(vectorSorted);
		cout << setw(40) << stats.comparisons << " " << stats.swaps;
		stats = shakerSort(vectorReverse);
		cout << setw(45) << stats.comparisons << " " << stats.swaps << endl;


		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
		cout << "ShellSort:" << setw(15) << "|" << setw(36) << "|" << setw(47) << "|" << endl;
		stats = shellSort(vectorRandom);
		cout << setw(35) << stats.comparisons << " " << stats.swaps;
		stats = shellSort(vectorSorted);
		cout << setw(40) << stats.comparisons << " " << stats.swaps;
		stats = shellSort(vectorReverse);
		cout << setw(45) << stats.comparisons << " " << stats.swaps << endl;


		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
		cout << "BinaryInsertionSort:" << setw(5) << "|" << setw(36) << "|" << setw(47) << "|" << endl;
		stats = binaryInsertionSort(vectorRandom);
		cout << setw(35) << stats.comparisons << " " << stats.swaps;
		stats = binaryInsertionSort(vectorSorted);
		cout << setw(40) << stats.comparisons << " " << stats.swaps;
		stats = binaryInsertionSort(vectorReverse);
		cout << setw(45) << stats.comparisons << " " << stats.swaps << endl;


		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
		cout << "InsertionSort:" << setw(11) << "|" << setw(36) << "|" << setw(47) << "|" << endl;
		stats = insertionSort(vectorRandom);
		cout << setw(35) << stats.comparisons << " " << stats.swaps;
		stats = insertionSort(vectorSorted);
		cout << setw(40) << stats.comparisons << " " << stats.swaps;
		stats = insertionSort(vectorReverse);
		cout << setw(45) << stats.comparisons << " " << stats.swaps << endl;


		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
		cout << "HeapSort:" << setw(16) << "|" << setw(36) << "|" << setw(47) << "|" << endl;
		stats = heapSort(vectorRandom);
		cout << setw(35) << stats.comparisons << " " << stats.swaps;
		stats = heapSort(vectorSorted);
		cout << setw(40) << stats.comparisons << " " << stats.swaps;
		stats = heapSort(vectorReverse);
		cout << setw(45) << stats.comparisons << " " << stats.swaps << endl;



		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
		cout << "QuickSort:" << setw(15) << "|" << setw(36) << "|" << setw(47) << "|" << endl;
		stats = quickSort(vectorRandom);
		cout << setw(35) << stats.comparisons << " " << stats.swaps;
		stats = quickSort(vectorSorted);
		cout << setw(40) << stats.comparisons << " " << stats.swaps;
		stats = quickSort(vectorReverse);
		cout << setw(45) << stats.comparisons << " " << stats.swaps << endl;
		cout << "________________________|___________________________________|______________________________________________|__________________________________________|" << endl;
	}else{
		cout << "Incorrect input. Try again! " << endl;
	}

	system("pause");
}