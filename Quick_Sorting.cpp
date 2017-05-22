/*
* SORTING ---- QUICKSORT PROGRAM 
*/    
	 
	 #include<iostream>

    using namespace std;
    
    void quickSort(int[],int,int);
 
int main()
{
    int a[50],n,i;
    cout<<"=========================================";
    cout<<"\nThe following Application is a sample \nQuick Sort Program in a given Array in an Elements\n";
    cout<<"=========================================";
    cout<<"\n\nHow many elements?\n";
    cin>>n;
    cout<<"\nEnter array elements:\n";
    
    for(i=0;i<n;i++)
        cin>>a[i];
        
   quickSort(a,0,n-1);
    cout<<"\nArray after sorting:\n";
    
    for(i=0;i<n;i++)
        cout<<a[i]<<" ";
    
    return 0;        
}

void quickSort(int arr[], int left, int right) {

      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];

      /* partition */
      while (i <= j) {
           while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                 arr[j] = tmp;
                  i++;
                 j--;
            }
     };

      /* recursion */
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
           quickSort(arr, i, right);
}
