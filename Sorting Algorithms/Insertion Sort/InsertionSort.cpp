#include <iostream>
#include <algorithm>
#include<ostream>

using namespace std;

int main()
{
	int a[]={5,7,2,6,9,3,1,4,8,10};
	int temp,j=0,i=0;
	
	for_each(a,a+sizeof(a)/sizeof(a[0]),[](int n){ cout<<n<<" "; });
	cout<<"\n\n";
	
	for(j=1;j<sizeof(a)/sizeof(a[0]);j++)
	{
		temp=a[j];
		i=j-1;
		
		while(temp<a[i]&& i>=0)
		{
			a[i+1]=a[i];
			i--;
		}
		
		a[i+1]=temp;
    }
    
    cout<<"Sorted Order - \n\n";
    for_each(a,a+sizeof(a)/sizeof(a[0]),[](int n){ cout<<n<<" "; });
    
	return 0;
}
