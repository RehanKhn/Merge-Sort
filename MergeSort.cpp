#include<iostream>
#include<cstdlib>
#include<stdlib.h>
#include<time.h>
#include<chrono> 
#include<fstream>

using namespace std;
using namespace std::chrono;

const int arraySize = 500000;

int* RandomArray() {
	static int rArray[arraySize];
	srand(time(NULL));
	for (int i = 0; i < arraySize; i++) {
		rArray[i] = (rand() % 10000000) + 1;
	}
	return rArray;
}

int* InsertionSort(int arr[], int startindex, int endindex) {
	int key, i, j;
	for (i = startindex; i <= endindex; i++) {
		key = arr[i];
		j = i - 1;
		while (arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
			if (j < 0)break;
		}
		arr[j + 1] = key;
	}
	return arr;
}

void Merge(int arr[], int startindex, int mid, int endindex)
{
	int l = mid - startindex + 1, r = endindex - mid;
	int* Left = new int[(l + 1)], * Right = new int[(r + 1)];


	for (int i = 0; i < l; i++)
		Left[i] = arr[i + startindex];

	for (int j = 0; j < r; j++)
		Right[j] = arr[j + mid + 1];

	Left[l] = 10000001;
	Right[r] = 10000001;

	int i = 0 , j = 0;

	for (int k = startindex; k <= endindex; k++)
	{
		if (Left[i] < Right[j])
		{
			arr[k] = Left[i];
			i++;
		}
		else
		{
			arr[k] = Right[j];
			j++;
		}
	}
}

int* MergeSort(int arr[], int startindex, int endindex)
{
	if (startindex < endindex)
	{
		int mid = ((startindex + endindex) / 2);
		MergeSort(arr, startindex, mid);
		MergeSort(arr, mid + 1, endindex);
		Merge(arr, startindex, mid, endindex);
	}
	return arr;
}

void PrintArray(int *p) {
	for (int i = 0; i < arraySize; i++) {
		cout << *(p + i) << " ";
	}
	cout << endl;
}

void WriteToFile(int* p) {
	ofstream ofs;
	ofs.open("sorted.txt");
	for (int i = 0; i < arraySize; i++)
	{
		ofs << *(p + i) << endl;
	}
}

int main() {
	int* p, *q, s = 0, e = arraySize - 1, A[arraySize];
	q = RandomArray();
	for (int i = s; i <= e; i++)
		A[i] = *(q + i);
	auto start = high_resolution_clock::now();
	p = MergeSort(A, s, e);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds> (stop - start); 
	cout <<"Time taken to sort in Microsecond: " << duration.count() << endl;
	WriteToFile(p);
	system("pause");
	return 0;
}