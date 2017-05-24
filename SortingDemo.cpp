//============================================================================
// Name        : SortingDemo.cpp
// Authors     : chester.tan, leandro.umali, paul.rigor
// Version     : v0.0
// Description : Shell sort and quick sort comparison demo.
// Git repo    :
//============================================================================

#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include "utils.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

// -----------------------  prototypes -----------------------
struct AlgoStats
{
	int numMoves;
	int numCompares;
};

AlgoStats ShellSort(int [], int);
AlgoStats QuickSort(int [], int, int);
void ShellSort_Benchmark(int [], int);
void QuickSort_Benchmark(int [], int);
void GenerateRandomList(int [], int, int = 1, int = 999);
void GenerateNearlySortedRandomList(const int [], int, int []);
void PrintArray(int [], int, int = 10);
bool SaveListToFile(int [], int, const char []);

int main(int argc, char* argv[])
{
   if (argc > 1)
   {
	   char * algo;
	   int arraySize;
	   int loop = 1;

	   for(int i = 1; i < argc; i = i + 2)
	   {
		   if (strcasecmp(argv[i], "-algo") == 0)
			   algo = argv[i+1];
		   else if (strcasecmp(argv[i], "-size") == 0)
			   arraySize = atoi(argv[i+1]);
		   else if (strcasecmp(argv[i], "-loop") == 0)
			   loop = atoi(argv[i+1]);
	   }

	   int randomNums[arraySize], sorted_random[arraySize], sorted_nearlyOrdered[arraySize];
	   int trial = 1;
	   do
	   {
		   cout<<"*** Trial "<<trial<<" ***"<<endl;
		   GenerateRandomList(randomNums, arraySize);
		   SaveListToFile(randomNums, arraySize, "unsorted.txt");
		   std::copy(randomNums, randomNums+arraySize, sorted_random);

		   cout<<endl<<"1st run: Sort "<<arraySize<<"-element random list";
		   if (strcasecmp(algo, "quick") == 0)
			   QuickSort_Benchmark(sorted_random, arraySize);
		   else if (strcasecmp(algo, "shell") == 0)
			   ShellSort_Benchmark(sorted_random, arraySize);
		   else if (strcasecmp(algo, "both") == 0)
		   {
			   QuickSort_Benchmark(sorted_random, arraySize);
			   std::copy(randomNums, randomNums+arraySize, sorted_random);
			   ShellSort_Benchmark(sorted_random, arraySize);
		   }
		   else
		   {
			   cerr<<"ERROR - Unsupported sorting algorithm '"<<algo<<"'"<<endl;
			   return -1;
		   }

		   GenerateNearlySortedRandomList(sorted_random, arraySize, sorted_nearlyOrdered);
		   cout<<endl<<"2nd run: Sort "<<arraySize<<"-element nearly ordered list";
		   if (strcasecmp(algo, "quick") == 0)
			   QuickSort_Benchmark(sorted_nearlyOrdered, arraySize);
		   else if (strcasecmp(algo, "shell") == 0)
			   ShellSort_Benchmark(sorted_nearlyOrdered, arraySize);
		   else if (strcasecmp(algo, "both") == 0)
		   {
			   QuickSort_Benchmark(sorted_nearlyOrdered, arraySize);
			   std::copy(sorted_random, sorted_random+arraySize, sorted_nearlyOrdered);
			   ShellSort_Benchmark(sorted_random, arraySize);
		   }
		   cout<<endl;
	   }while (trial++ < loop);
   }
   else
   {
	   //interactive mode
	   int algoChoice;
	   int arraySize;
	   char retryChoice;
	   SimpleTimer stopwatch;
	   AlgoStats results;
	   SetConsoleBufferHeight(1000);
	   do
	   {
		   ClearScreen();
		   cout<<"Set array size: ";
		   cin>>arraySize;
		   cout<<"Select algorithm (0 = Quick sort, 1= Shell sort): ";
		   cin>>algoChoice;

		   //initialize random list
		   int randomNums[arraySize], sorted_random[arraySize], sorted_nearlyOrdered[arraySize];
		   GenerateRandomList(randomNums, arraySize);
		   cout<<endl<<"Unsorted numbers:"<<endl;
		   PrintArray(randomNums, arraySize);
		   SaveListToFile(randomNums, arraySize, "unsorted.txt");

		   //1st sort
		   std::copy(randomNums, randomNums+arraySize, sorted_random);
		   if (algoChoice == 0)
		   {
			   stopwatch.Start();
			   results = QuickSort(sorted_random, 0, arraySize - 1);
		   }
		   else
		   {
			   stopwatch.Start();
			   results = ShellSort(sorted_random, arraySize);
		   }
		   cout<<endl<<"1st sort, from random list:"<<endl;
		   cout<<"# moves = "<<results.numMoves<<", # compares = "<<results.numCompares<<", Exec time = "<<stopwatch.Elapsed_ms_str()<<endl;

		   PrintArray(sorted_random, arraySize);
		   SaveListToFile(sorted_random, arraySize, "sorted_random.txt");

		   //2nd sort
		   GenerateNearlySortedRandomList(sorted_random, arraySize, sorted_nearlyOrdered);
		   if (algoChoice == 0)
		   {
			   stopwatch.Restart();
			   results = QuickSort(sorted_nearlyOrdered, 0, arraySize - 1);
		   }
		   else
		   {
			   stopwatch.Restart();
			   results = ShellSort(sorted_nearlyOrdered, arraySize);
		   }
		   cout<<endl<<"2nd sort, from nearly ordered list:"<<endl;
		   cout<<"# moves = "<<results.numMoves<<", # compares = "<<results.numCompares<<", Exec time = "<<stopwatch.Elapsed_ms_str()<<endl;
		   PrintArray(sorted_nearlyOrdered, arraySize);
		   SaveListToFile(sorted_nearlyOrdered, arraySize, "sorted_nearlyOrdered.txt");

		   cout<<endl<<"Retry (y/n)? ";
		   cin>>retryChoice;
	   }while(retryChoice == 'y');
   }
   return 0;
}

// -----------------------  sorting algorithms -----------------------

AlgoStats ShellSort(int nums[], int size)
{
	int moves = 0;
	int comp = 0;
	//TODO - method body
	for (int gap = size / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < size; ++i)
		{
			int tmp = std::move(nums[i]);
			int j = i;
			
			for ( ; j >= gap && (comp++,tmp < nums[j - gap]); j -= gap)
			{
				nums[j] = std::move(nums[j - gap]);
				moves++;
			}
			nums[j] = std::move(tmp);
		}
	}

	//Assign these values
	AlgoStats results;
	results.numCompares = comp;
	results.numMoves = moves;
	return results;
}

AlgoStats QuickSort(int arr[], int lowerBound, int upperBound){
    int left = lowerBound;
    int right = upperBound;
	int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];

	int moves = 0;
	int comp = 0;
    /* partition */
    while (i <= j) {
    	comp++;
        while (arr[i] < pivot) {
        	i++;
        	comp++;
		}
		comp++;
        while (arr[j] > pivot) {
        	j--;
        	comp++;
		}
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
            moves++;
        }
    };

    /* recursion */
    if (left < j)
    {
		AlgoStats result1;
        result1 = QuickSort(arr, left, j);
        comp += result1.numCompares;
        moves += result1.numMoves;
	}
    if (i < right)
    {
		AlgoStats result2;
        result2 = QuickSort(arr, i, right);
        comp += result2.numCompares;
        moves += result2.numMoves;
	}

	//TODO - method body

	//Set these values
	AlgoStats results;
	results.numCompares = comp;
	results.numMoves = moves;
	return results;
}

void ShellSort_Benchmark(int nums[], int size)
{
	SimpleTimer stopwatch;
    AlgoStats results;
    cout<<endl<<"  Running ShellSort..."<<endl;
    stopwatch.Start();
    results = ShellSort(nums, size);
    cout<<"  # moves = "<<results.numMoves<<", # compares = "<<results.numCompares<<", Exec time = "<<stopwatch.Elapsed_ms_str()<<endl;
    SaveListToFile(nums, size, "shell.log"); //TODO: assign different filenames to multiple log files
}

void QuickSort_Benchmark(int nums[], int size)
{
	SimpleTimer stopwatch;
    AlgoStats results;
    cout<<endl<<"  Running Quicksort..."<<endl;
    stopwatch.Start();
    results = QuickSort(nums, 0, size - 1);
    cout<<"  # moves = "<<results.numMoves<<", # compares = "<<results.numCompares<<", Exec time = "<<stopwatch.Elapsed_ms_str()<<endl;
    SaveListToFile(nums, size, "quick.log"); //TODO: assign different filenames to multiple log files
}

void GenerateRandomList(int nums[], int size, int minVal, int maxVal)
{
	RandomNumGen rng;
	for (int i = 0; i < size; i++)
		nums[i] = rng.Next(minVal, maxVal);

}

void GenerateNearlySortedRandomList(const int sortedNums[], int size, int nearlySortedNums[])
{
	std::copy(sortedNums, sortedNums+size, nearlySortedNums);
	int temp = nearlySortedNums[18];
	nearlySortedNums[18] = nearlySortedNums[19];
	nearlySortedNums[19] = temp;
}
void PrintArray(int nums[], int size, int numsPerLine)
{
	cout<<endl;
	for (int i = 1; i <= size; i++)
	{
		if (i % numsPerLine == 1)
			cout<<"    "; //set indentation
		cout<<std::left<<std::setw(4)<<std::setfill(' ')<<nums[i-1]<<" ";
		if (i % numsPerLine == 0)
			cout<<endl;
	}
}

bool SaveListToFile(int nums[], int size, const char fileName[])
{
	std::ofstream myfile(fileName, std::ofstream::out | std::ofstream::trunc);
	if (myfile.is_open())
	{
		for (int i = 0; i < size; i++)
			myfile<<nums[i]<<endl;
		myfile.close();
		return true;
	}
	else
		return false;
}
