#include<iostream>
#include<algorithm>

using namespace std;

int n;
void merge(int *a,int low,int mid,int high);

void merge_sort(int *a,int low,int high)
{
	int mid =(high+low)/2;
	if(low<high)
	{
	merge_sort(a,low,mid);
	merge_sort(a,mid+1,high);
	merge(a,low,mid,high);
    }
    
    return;
}
void merge(int *a,int low,int mid,int high)
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
 	int a[]={5,7,2,6,9,3,1,4,8,10};
 	n= sizeof(a)/sizeof(a[0]);
 	
 	for_each(a,a+sizeof(a)/sizeof(a[0]),[](int n){ cout<<n<<" "; });
	cout<<"\n\n";
	
 	merge_sort(a,0,n-1);
 	
 	cout<<"After Merge Sort - \n\n";
 	
 	for_each(a,a+sizeof(a)/sizeof(a[0]),[](int n){ cout<<n<<" "; });
 	
 	return 0 ;
 }
