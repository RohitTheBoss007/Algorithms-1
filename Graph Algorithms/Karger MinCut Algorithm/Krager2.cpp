#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include<list>
#include <sstream>

using namespace std;

const int n=201;   					//Total Number of (Nodes+1).
vector<list<int> > ogNode(n);				//Reference Graph.


//Fast Random Number Generator.

static unsigned long x=123456789, y=362436069, z=521288629;
unsigned long xorshf96(void) {          		//period 2^96-1
unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

   t = x;
   x = y;
   y = z;
   z = t ^ x ^ y;

  return z;
}


class Graph
{
	

		public:
		vector<list<int> > node;  		//Adjaceny List To Store a Graph( Call It G1).
		bool nodeTrue[n]={false};		//To check If The Node Exsist Anymore.
		int nodeCount ;				//To Keep Track Of Total Number of Nodes.
		
		Graph();				//Constructor.
		void Merge(int a, int b);		//Merge Function(node a , node b).
		void Print();				//Print The Graph.
		int MinCutCount(int a);			//To Count The Minimum Number Of Cuts.
};

Graph :: Graph()
{
	node = ogNode;					//Contents of Reference Graph copied in G1.
	nodeCount = n-1;				//NodeCount = Total number of Nodes. 
	
	for(int i=1;i<n;i++)
	nodeTrue[i] = true;				//Initializing all nodes (1 to (n-1)) = true.
	
}
void Graph :: Merge(int a, int b)
{

	list<int> :: iterator iter;			//Intialze an iterator.
	iter = node[a].end();				//Point the iterator to the end of node a.
					
					
	node[a].splice(iter,node[b]);			//Cut & Paste Elements from b to a.
	
	
	nodeTrue[b] = false;				//Disabling Node b.
	
	
	list<int>:: iterator iter2;			//Initialize Iterator to find 'b'.
	
	for( int i =1;i<n;i++)				// Assigning 'b=a' in the Remaining list.
	{
		if(nodeTrue[i])				//If The Given Node Exsists.
		{
			while(true)
			{
				iter2 = find(node[i].begin(),node[i].end(),b);
				
				if(iter2==node[i].end()) // If 'b' Not Found , Then Break.
				break;
				
				*iter2 = a; 		//Else b = a.
			}
		
		}
	}
	
	
	while(true)					//Removing Multiple Self Loops going from 'a' to 'a'.
	{
		iter = find(node[a].begin(),node[a].end(),a);
		
		if(iter ==node[a].end())		//If 'a' Not Found Then Break.
		break;
	
		node[a].erase(iter);			//Else Delete 'a' From Node 'a'.
	}	
	
	nodeCount--;					// Decrement The Number Of Nodes.
}


void  Graph::Print()
{
	list<int>:: iterator iter; 			//Initialize an Iterator to Print the Graph.
	
	for( int i =1;i<n;i++)
	{
		if(nodeTrue[i])
		{
		cout<<"Node "<<i<<" - ";
		for( iter = node[i].begin();iter!=node[i].end();iter++)
		{
			cout<<*iter<<" ";		//Print The Contents In Node 'i'.
		}
		cout<<endl;
		}
	}
}

int Graph :: MinCutCount(int a)
{
	int temp=0;
	
	list<int>:: iterator iter = node[a].begin(); //Intialize Iterator 
	
	for(;iter!=node[a].end();iter++)	     //Count Remaining Contents in node 'a'
    		temp++;				     //Which is Equal to Min Cut Of G1.
    
    return temp;
}

void AdjList()
{
	
	int i=1,a;
	
	ifstream file;
    file.open("kargerMinCut.txt");
    string line;
	while (getline(file, line))
		{
			istringstream iss(line);
			while ((iss >> a))
			{
				if(i!=a)		//This done to skip the First Number in the Line
				{
				ogNode[i].push_back(a); //Add contents in Reference Graph.
				}
			}
			i++;
		}
	file.close();
}




int main()
{
	int a,b;					//Nodes 'a' and 'b'.
	int min=n;					//To Store Final Min Cut.
	int m=20;					// Number of Iterations.
	
	
	AdjList();  					// Store Graph from '.txt' to Reference Graph.


	for(int j=1;j<=m;j++)				//Iterate 'm' Number Of Times To Get 
	{						//Total Number of Minimum Cuts.
		cout<<"Iteration - "<<j<<"\n\n";
	
		Graph g1;
	
		while(g1.nodeCount>2)			//Loop Till 2 Nodes are Left.
		{
		
		
			xorshf96();			//Generate Random Numbers.
			a = z%n;			//Srand() is not used as it is very slow to
							//generate random numbers at quick sucessions

	
		//Picking Random Edges.
		
			if(g1.nodeTrue[a]==true)	//Checks if Node 'a' Exsists.
			{
				list<int> :: iterator iter = g1.node[a].begin();
				
				b = *iter;		//Assigns b equal to the first content of node a.
				
				cout<<"Merging -"<<a<<" & "<<b<<endl;
				
				g1.Merge(a,b);		//Merge node 'a' and 'b'.
				g1.Print();		//Prints The Graph.
				
				cout<<endl;
			}
    	}
    
    	int temp = g1.MinCutCount(a);		   	//Stores The Minimum Number Of Cuts of G1.
    
    	cout<<"Temp Min Cut Value - "<<temp<<"\n\n";
    	
    	if(min>temp)
    		min=temp;						
	}
	
    cout<<"The Final Minimum Cut Value is "<<min<<endl;
}


