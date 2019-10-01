#include "Main.h"
#include <vector>
#include <random>
#include <time.h>


std::vector<int> arr;
const int NUM_ELEMENTS = 1000;

sf::Thread sortingThread = sf::Thread(&sortAnimation);
int accessingIndex = -1;

void start() {
	srand(time(NULL));

	for (int i = 0; i < NUM_ELEMENTS; i++) {
		arr.push_back(rand() % 400);
	}

	sortingThread.launch();

}

void draw() {

	for (int i = 0; i < NUM_ELEMENTS; i++) {

		sf::RectangleShape bar(sf::Vector2f((float)window->getSize().x / (float)NUM_ELEMENTS, arr[i]));
		bar.setFillColor(sf::Color::Cyan);
		if (i == accessingIndex) {
			bar.setFillColor(sf::Color::Red);
		}
		bar.setPosition(sf::Vector2f(i * (float)window->getSize().x / (float)NUM_ELEMENTS, window->getSize().y - arr[i]));
		window->draw(bar);
	}
}

void end() {
	sortingThread.terminate();
}

void sortAnimation() {

	selectionSort();
	sf::sleep(sf::seconds(1.5f));
	shuffle();

	bubbleSort();
	sf::sleep(sf::seconds(1.5f));
	shuffle();

	cocktailSort();
	sf::sleep(sf::seconds(1.5f));
	shuffle();

	insertionSort();
	sf::sleep(sf::seconds(1.5f));
	shuffle();

	shellSort();
	sf::sleep(sf::seconds(1.5f));
	shuffle();

	mergeSort(0, NUM_ELEMENTS);
	sf::sleep(sf::seconds(1.5f));
	shuffle();

	quickSort(0, NUM_ELEMENTS - 1);
	sf::sleep(sf::seconds(1.5f));
	shuffle();

	radixSort();


}

void shuffle() {

	for (int i = 0; i < NUM_ELEMENTS; i++) {
		int cur = arr[i];
		accessingIndex = i;
		int randIndex = rand() % NUM_ELEMENTS;
		arr[i] = arr[randIndex];
		arr[randIndex] = cur;
		accessingIndex = randIndex;
		sf::sleep(sf::seconds(0.002f));
	}

	accessingIndex = -1;

}

void selectionSort() {
	for (int i = 0; i < NUM_ELEMENTS; i++) {
		int minIndex = i;
		for (int j = i + 1; j < NUM_ELEMENTS; j++) {
			accessingIndex = j;
			if (arr[j] < arr[minIndex]) minIndex = j;
			sf::sleep(sf::seconds(0.00025f));
		}

		int item1 = arr[i];
		int item2 = arr[minIndex];

		arr[i] = item2;
		arr[minIndex] = item1;

	}

	accessingIndex = -1;
}

void insertionSort() {

	for (int i = 1; i < NUM_ELEMENTS; i++) {
		int cur = arr[i];
		for (int j = i - 1; j >= 0; j--) {
			accessingIndex = j;
			if (arr[j] > cur) {
				arr[j + 1] = arr[j];

				if (j == 0) { // If element belongs at the start of the list
					arr[j] = cur;
				}
			}
			else {
				arr[j + 1] = cur;
				break;
			}
			sf::sleep(sf::seconds(0.00025f));
		}
	}

	accessingIndex = -1;
}

void shellSort() {
	int h = 1;
	while (h < NUM_ELEMENTS) {
		h = h * 3 + 1;
	}
	while (h > 0) {
		for (int i = h; i < NUM_ELEMENTS; i++) {
			int cur = arr[i];
			for (int j = i - h; j >= 0; j -= h) {
				accessingIndex = j;
				if (arr[j] > cur) {
					arr[j + h] = arr[j];

					if (j < h) { // If element belongs at the start of the
									// list
						arr[j] = cur;
					}
				}
				else {
					arr[j + h] = cur;
					break;
				}
				sf::sleep(sf::seconds(0.0025f));
			}
		}
		h /= 3;
	}

	accessingIndex = -1;
}

void bubbleSort() {

	for (int i = 0; i < NUM_ELEMENTS; i++) {
		for (int j = 0; j < NUM_ELEMENTS - 1 - i; j++) {
			accessingIndex = j;

			int item1 = arr[j];
			int item2 = arr[j + 1];

			if (item1 > item2) {
				arr[j] = item2;
				arr[j + 1] = item1;
			}
			sf::sleep(sf::seconds(0.00025f));
		}
	}
	accessingIndex = -1;
}

void radixSort() {
	int max = arr[0];
	for (int i = 0; i < NUM_ELEMENTS; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}

	for (int i = 1; max / i > 0; i *= 10) {
		// i contains what digit were at

		std::vector<std::vector<int>> buckets(10, std::vector<int>(NUM_ELEMENTS, 0));

		std::vector<int> bucketCounts(10, 0);
		// Keeps track of what index were at in each bucket. Must be an int
		// array rather than an Integer array, so we can use for index

		for (int j = 0; j < NUM_ELEMENTS; j++) {
			accessingIndex = j;
			int cur = arr[j];
			int digit = (cur / i) % 10; // Get the digit in the place
										// determined by i
			buckets[digit][bucketCounts[digit]++] = cur;
			sf::sleep(sf::seconds(.0025f));
		}

		// the buckets 2d array is now filled, so change sortedArr
		int index = 0; // Index in sorted array to be filled next
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < bucketCounts[j]; k++) {

				accessingIndex = index;
				arr[index++] = buckets[j][k];
				sf::sleep(sf::seconds(.0015f));
			}
		}

	}
	accessingIndex = -1;
}

void cocktailSort() {

	int frontIndex = 0;
	int backIndex = NUM_ELEMENTS;

	while (frontIndex <= backIndex) {

		bool swapped = false;
		for (int i = frontIndex; i < backIndex - 1; i++) {
			accessingIndex = i;
			int item1 = arr[i];
			int item2 = arr[i + 1];

			if (item1 > item2) {
				arr[i] = item2;
				arr[i + 1] = item1;
				swapped = true;
			}
			sf::sleep(sf::seconds(0.00025f));
		}

		if (!swapped)
			break;

		swapped = false;
		backIndex--;
		for (int i = backIndex; i > frontIndex; i--) {
			accessingIndex = i;
			int item1 = arr[i];
			int item2 = arr[i - 1];

			if (item1 < item2) {
				arr[i] = item2;
				arr[i - 1] = item1;
				swapped = true;
			}
			sf::sleep(sf::seconds(0.00025f));
		}

		if (!swapped)
			break;

		frontIndex++;

	}
	accessingIndex = -1;

}

void mergeSort(int beginIndex, int endIndex) {
	if (endIndex - beginIndex == 1)
		return;

	int middleIndex = (beginIndex + endIndex) / 2;

	mergeSort(beginIndex, middleIndex);
	mergeSort(middleIndex, endIndex);

	merge(beginIndex, middleIndex, middleIndex, endIndex);
}

void merge(int arr1BeginIndex, int arr1EndIndex, int arr2BeginIndex, int arr2EndIndex) {
	std::vector<int> mergedArr(arr1EndIndex - arr1BeginIndex + arr2EndIndex - arr2BeginIndex);
	for (int i = arr1BeginIndex, j = arr2BeginIndex, mergedIndex = 0;
		i < arr1EndIndex || j < arr2EndIndex;
		mergedIndex++) {

		int item1, item2;
		bool item1Set = false, item2Set = false;;
		if (i < arr1EndIndex) {
			item1 = arr[i];
			accessingIndex = i;
			item1Set = true;
			sf::sleep(sf::seconds(0.001f));
		}
		if (j < arr2EndIndex) {
			item2 = arr[j];
			accessingIndex = j;
			item2Set = true;
			sf::sleep(sf::seconds(0.001f));
		}
		// Check if one of the items was null, meaning we're at the end of
		// one of the arrays. If an item is null, use the other one
		if (!item1Set) {
			mergedArr[mergedIndex] = item2;
			accessingIndex = j;
			j++;
			sf::sleep(sf::seconds(0.001f));
			continue;
		}

		if (!item2Set) {
			mergedArr[mergedIndex] = item1;
			accessingIndex = i;
			i++;
			sf::sleep(sf::seconds(0.001f));
			continue;
		}

		if (item1 <= item2) {
			mergedArr[mergedIndex] = item1;
			i++;
			sf::sleep(sf::seconds(0.001f));
		}
		else {
			mergedArr[mergedIndex] = item2;
			j++;
			sf::sleep(sf::seconds(0.001f));
		}
	}

	for (int i = 0; i < mergedArr.size(); i++) {
		arr[arr1BeginIndex + i] = mergedArr[i];
		accessingIndex = arr1BeginIndex + i;
		sf::sleep(sf::seconds(0.001f));
	}



}

void quickSort(int lowIndex, int highIndex) {
	if (highIndex > lowIndex) {

		int partitionedIndex = partition(lowIndex, highIndex);
		quickSort(lowIndex, partitionedIndex - 1);
		quickSort(partitionedIndex + 1, highIndex);
	}
}

int partition(int lowIndex, int highIndex) {
	int pivot = arr[lowIndex];

	int i = lowIndex + 1;
	int j = highIndex;
	while (true) {

		while (i != highIndex && arr[i] < pivot) {
			accessingIndex = i;
			sf::sleep(sf::seconds(0.001f));
			i++;
		}

		while (j != lowIndex && arr[j] > pivot) {
			accessingIndex = j;
			sf::sleep(sf::seconds(0.001f));
			j--;
		}

		if (i >= j)
			break;

		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
		i++;
		j--; // Incriment indicies to move onto the next elements

	}

	int temp = arr[j];
	arr[j] = pivot;
	arr[lowIndex] = temp;

	accessingIndex = -1;

	return j;
}