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
using std::endl;
using std::string;

// -----------------------  prototypes -----------------------
void ShellSort(int [], int);
void QuickSort(int [], int);
void GenerateRandomList(int [], int, int = 1, int = 999);
void GenerateNearlySortedRandomList(const int [], int, int []);
void PrintArray(int [], int, int = 10);
bool SaveListToFile(int [], int, const char []);

int main(int argc, char* argv[])
{
   if (argc > 1)
   {
	  //TODO: scripting mode
	  //	   cout << "argc = " << argc << endl;
	  //	   for(int i = 0; i < argc; i++)
	  //		   cout << "argv[" << i << "] = " << argv[i] << endl;
	  //	   return 0;
   }
   else
   {
	   //interactive mode
	   int algoChoice;
	   int arraySize;
	   char retryChoice;
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
			   QuickSort(sorted_random, arraySize);
		   else
			   ShellSort(sorted_random, arraySize);
		   cout<<endl<<"1st sort, from random list:"<<endl;
		   PrintArray(sorted_random, arraySize);
		   SaveListToFile(sorted_random, arraySize, "sorted_random.txt");

		   //2nd sort
		   GenerateNearlySortedRandomList(sorted_random, arraySize, sorted_nearlyOrdered);
		   if (algoChoice == 0)
			   QuickSort(sorted_nearlyOrdered, arraySize);
		   else
			   ShellSort(sorted_nearlyOrdered, arraySize);
		   cout<<endl<<"2nd sort, from nearly ordered list:"<<endl;
		   PrintArray(sorted_nearlyOrdered, arraySize);
		   SaveListToFile(sorted_nearlyOrdered, arraySize, "sorted_nearlyOrdered.txt");

		   cout<<endl<<"Retry (y/n)? ";
		   cin>>retryChoice;
	   }while(retryChoice == 'y');
   }
}

// -----------------------  sorting algorithms -----------------------

void ShellSort(int nums[], int size)
{
	//TODO
}

void QuickSort(int nums[], int size)
{
	//TODO
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
