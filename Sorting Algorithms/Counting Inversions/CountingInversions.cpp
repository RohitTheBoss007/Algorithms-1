#include<iostream>
#include<fstream>

using namespace std;

unsigned long int n=100000;

void merge_countInv(int *a,int low,int mid,int high,unsigned long long int &count);

void mergeSort(int *a,int low,int high,unsigned long long int &count)
{
	int mid = (low+high)/2;
	if(low<high)
	{
		mergeSort(a,low,mid,count);
		mergeSort(a,mid+1,high,count);
		merge_countInv(a,low,mid,high,count);
	}
}

void merge_countInv(int *a,int low,int mid,int high,unsigned long long int &count)
{
	int i=low;
	int j=mid+1;
	int k=low;
	int c[n];
	while(i<=mid&&j<=high)
	{
		if(a[i]<a[j])
		{
			c[k]=a[i];
			k++;
			i++;
		}
		
	    else
		{
			c[k]=a[j];
			k++;
			j++;
			count+=(mid-i+1);
		}
	}
	
	while(i<=mid)
	{
		c[k]=a[i];
		k++;
		i++;
	}
	
	while(j<=high)
	{
		c[k]=a[j];
		k++;
		j++;
	}
	
	for(i=low;i<k;i++)
	{
		a[i]=c[i];
	}
}

int main()
{	
   unsigned long long int count=0;
	int a[n];
	ifstream file;
	
	file.open("IntegerArray.txt");
	for(int i=0;i<n;i++)
	{
		file>>a[i];
	}
	file.close();
	
	mergeSort(a,0,n-1,count);
	
	cout<<"Number of Inversions = "<<count;
}
