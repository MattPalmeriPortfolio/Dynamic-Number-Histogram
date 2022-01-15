#include <iostream>
#include <fstream>
#include <vector>
//declare functions
void getList(std::vector<int>& intVector, std::istream& inStream = std::cin);
//Precondition: intVector is empty, or you do not mind extra values being appended to the end.
//Postcondition: Reads input into a vector to a sentinel value of -1. uses push_back, rather than inserting.
void doubleSwap(int& value1, int& frequency1, int& value2, int& frequency2);
//Swaps the values of value1 and frequency1 with value2 and frequency2 respectively; used for histogram sorting, but works for any double swap values.
void quickSort(int** arr, int leftIndex, int rightIndex);
//only sorts arr[x][0], but drags arr[x][1] values with them.
int** resize2DArray(int** arr, const int currentRows, const int currentColumns, const int newRows, const int newColumns);
//Returns a new 2D array of arr[newRows][newColumns]; adds all the values of arr if currentRows <= newRows && currentColumns <= newColumns, else adds all the values from arr[x < newRows][y < newColumns]
//Deletes arr before returning.
void copyRow(int* row1, int* row2, const int numValues);
//copies numValues from row1 to row2, preserving indexes

//main
int main()
{
	using namespace std;
	//declare constants
	const int COLUMNS = 2;
	//initialize objects
	vector<int> inputList; inputList.reserve(300);
	ifstream inStream("input8.txt");
	if (inStream.fail())
		exit(1);
	//initialize variables
	int histogramSize(0), ** histogram;
	//get input
	getList(inputList, inStream);
	cout << endl;
	//initialize histogram; 
	histogram = new int* [inputList.size()];
	for (int i = 0; i < inputList.size(); i++)
		histogram[i] = new int[COLUMNS];
	for (int i = 0; i < inputList.size(); i++)
		for (int j = 0; j < COLUMNS; j++)
			histogram[i][j] = -1;
	//move values to histogram, removing duplicates and adding frequency as necessary(int inputIndex = 0; inputIndex < inputList.size(); inputIndex++)
	for (int inputIndex = 0, histogramIndex; inputIndex < inputList.size(); inputIndex++)
	{
		for (histogramIndex = 0; histogramIndex < histogramSize; histogramIndex++)
		{
			if (histogram[histogramIndex][0] == inputList[inputIndex])
			{
				histogram[histogramIndex][1] += 1;
				//cout << "Increasing the frequency of " << inputList[inputIndex] << " at position " << histogramIndex << endl;
				break;
			}
		}
		if (histogramIndex == histogramSize && histogram[histogramIndex][0] != inputList[inputIndex])
		{
			histogram[histogramIndex][0] = inputList[inputIndex];
			histogram[histogramIndex][1] = 1;
			//cout << "Placing " << inputList[inputIndex] << " in histogram index " << histogramIndex << endl;
			++histogramSize;
		}
	}
	histogram = resize2DArray(histogram, inputList.size(), COLUMNS, histogramSize, COLUMNS);
	quickSort(histogram, 0, histogramSize - 1);
	for (int i = 0; i < histogramSize; i++)
		cout << "# of " << histogram[i][0] << "'s: " << histogram[i][1] << endl;
	return 0;
}

//define functions
void getList(std::vector<int>& intVector, std::istream& inStream)
{
	int nextValue;
	while (inStream >> nextValue && nextValue >= 0)
		intVector.push_back(nextValue);
	return;
}

void doubleSwap(int& value1, int& frequency1, int& value2, int& frequency2)
{
	int temp;
	temp = value1;
	value1 = value2;
	value2 = temp;
	temp = frequency1;
	frequency1 = frequency2;
	frequency2 = temp;
	return;
}

void quickSort(int** arr, int leftIndex, int rightIndex)
{
	unsigned int i = leftIndex, j = rightIndex;
	int pivot = arr[(leftIndex + rightIndex) / 2][0];
	while (i <= j)
	{
		while (arr[i][0] < pivot)
			++i;
		while (arr[j][0] > pivot)
			--j;
		if (i <= j)
		{
			doubleSwap(arr[i][0], arr[i][1], arr[j][0], arr[j][1]);
			++i;
			--j;
		}
	}
	if (leftIndex < j)
		quickSort(arr, leftIndex, j);
	if (i < rightIndex)
		quickSort(arr, i, rightIndex);
	return;
}

void copyRow(int* row1, int* row2, const int numValues)
{
	for (int i = 0; i < numValues; i++)
		row2[i] = row1[i];
	return;
}

int** resize2DArray(int** arr, const int currentRows, const int currentColumns, const int newRows, const int newColumns)
{
	int** new2DArray = new int* [newRows];
	for (int i = 0; i < newRows; i++)
		new2DArray[i] = new int[newColumns];
	if (newRows <= currentRows)
	{
		if (newColumns <= currentColumns)
			for (int i = 0; i < newRows; i++)
				copyRow(arr[i], new2DArray[i], newColumns);
		else //if newColumns > currentColumns
			for (int i = 0; i < newRows; i++)
				copyRow(arr[i], new2DArray[i], currentColumns);
	}
	else //if newRows > currentRows
	{
		if (newColumns <= currentColumns)
			for (int i = 0; i < currentRows; i++)
				copyRow(arr[i], new2DArray[i], newColumns);
		else //if newColumns > currentColumns
			for (int i = 0; i < currentRows; i++)
				copyRow(arr[i], new2DArray[i], currentColumns);
	}
	for (int i = 0; i < currentRows; i++)
		delete[] arr[i];
	delete[] arr;
	return new2DArray;
}