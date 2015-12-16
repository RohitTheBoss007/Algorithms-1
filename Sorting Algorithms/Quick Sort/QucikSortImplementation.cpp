#include<iostream>
#include<fstream>
using namespace std;

unsigned long long int  Count = 0; 
 
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 

int partition (int arr[], int l, int h)
{
	// Case 3 - Pivot = Median from l , m & h
	
	int m = (h+l)/2;  							// The Middle Element.
	
	if ((arr[l]<arr[m]&&arr[l]>arr[h])||(arr[l]>arr[m]&&arr[l]<arr[h]))
	{
												// l is the median.No Swapping Required.
	}
	
	else if((arr[m]<arr[l]&&arr[m]>arr[h])||(arr[m]>arr[l]&&arr[m]<arr[h]))
	{
		swap(&arr[l],&arr[m]);					// m is the median.
	}
	
	else
	{
		
		swap(&arr[l],&arr[h]);					// h is the median.
	}
	
	
    Count=Count+(h-l);							//To Count The Number of Comparisions
    
    
    //Case 2 - Pivot = Last Element.
	// swap(&arr[l],&arr[h]); 					//Swap Between Fisrt And Last Element.
	
	//Case 1  - Pivot = First Element.
	
	
    int p=arr[l];    						    // Initialize Pivot.
    
    int i=l+1;     								 // Initialize i to keep a track on no.s <=p
    
    for(int j=l+1;j<=h;j++)  					 //Initialize j to keep track of total no.s encountered.
    {
    	if(arr[j]<=p)
    	{
    		swap(&arr[i],&arr[j]);
    		i++;
    	}
    }
    
    swap(&arr[l],&arr[i-1]);  					// To swap between the last element (<p) and pivot.
    
    return(i-1);
}
 

void quickSort(int arr[], int l, int h)
{
    if (l < h)
    {
        int p = partition(arr, l, h); 
        quickSort(arr, l, p-1 );   				// Recurse on The 1st Part(<p)
        quickSort(arr, p +1, h);   				// Recurse on The 2nd Part(>p)
    }
}
 

void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
    printf("%d ", arr[i]);
    printf("\n");
    
}
 

int main()
{
    unsigned long int n=10000;
    int arr[n];
    
    ifstream file;
    file.open("QuickSort.txt");
    
	for(int i=0;i<n;i++)
	{
		file>>arr[i];
	}
	file.close();
	
    quickSort(arr, 0, n-1);
   
  cout<<"The Total Number of Comparisons: "<<Count<<endl;
  
    return 0;
}
