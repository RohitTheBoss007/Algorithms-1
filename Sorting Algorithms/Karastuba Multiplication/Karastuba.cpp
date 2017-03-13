#include<iostream>
#include<conio.h>
#include<math.h>

using namespace std;

int getlen(int x)
{
	int length = (int)log10(x) + 1;
	return length;
}

int karas(int x , int y)
{
	int l = getlen(x);
	
	if(l = 1)
	{
		return x*y;
	}
	
	int a = x/(int)pow(10,l/2);
	int b = x%(int)pow(10,l/2);
	
	int c = y/(int)pow(10,l/2);
	int d = y%(int)pow(10,l/2);
	
	int ac = karas(a,c);
	int bd = karas(b,d);
	int adbc = karas(a+b,c+d) - bd - ac;
	
	return (int)pow(10,l)*ac + (int)pow(10,l/2)*adbc + bd;
	
}


int main()
{
	int x,y;
	
	cout<<"Enter the Multiplicand - ";
	cin>>x;
	
	cout<<"Enter the Multiplier - ";
	cin>>y;
	
	cout<<"The result of above Multiplication is "<<karas(x,y);
	
	return 0;
}
