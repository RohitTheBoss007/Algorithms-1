#include <iostream>
#include <vector>
#include <fstream>
#include<list>
#include <sstream>
using namespace std;

const int n = 7;								//Total Number of (Nodes+1).
										//node 0 is ignored to avoid confusion.
class Graph
{
	public:
	vector<list<int> > node;						//Adjacency List To Store A Graph (call it G1).
	bool nodeExplored[n-1] = {false};					//Intialize All Nodes To Be Unexplored.
	int fTime[n-1];								//To Keep Track of Finishing Time.
	
	Graph();								//Constructor.
	void AdjList();								//Store Graph from '.txt' to G1.
	void Print();								//Print The Finishing Times.
	
};

Graph :: Graph()
{
	node.resize(n);								//Allocate Size Of The Vector Equal to 'n'.
	AdjList();
}

void Graph :: AdjList()
{
	int a,i=1;
	
	ifstream file;
    file.open("TO_Test.txt");
    string line;
    
	while (getline(file, line))
		{
			istringstream iss(line);
			while ((iss >> a))
			{
				if(i!=a)					//This done to skip the First Number in the Line
				{
				node[i].push_back(a); 				//Add Edges To Node 'i'.
				}
			}
			i++;
		}
		
	file.close();	
	
	for(int i=1;i<n;i++)							//To Print Out The Graph.
	{
		cout<<i<<" - ";
		
		list<int> :: iterator iter;
		
		for(iter = node[i].begin();iter!= node[i].end();iter++)
		{
			cout<<*iter<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void Graph :: Print()					   		 	//To Print The Finishing Times.
{
	for(int i=1;i<n;i++)
	{
		cout<<"Finishing Time of "<<i<<" is " <<fTime[i]<<endl;
	}
}


int label = n-1;						  		 //To Keep Track For Ordering.
void DFS(Graph & g, int s);				   	     		 //Prototype for DFS Function.

void DFSLoop(Graph & g)					   
{
	
	for (int i=1;i<n;i++)
	{
		if(g.nodeExplored[i] == false)					//Check If Node 'i' Is Not Yet Explored.
		DFS(g,i);							//Call DFS Function.
	}
}

void DFS(Graph & g, int s)
{
	g.nodeExplored[s] = true;						//Mark Node 's( = i)' As Marked.
	
	list<int> :: iterator iter;						//Initialize Iterator.
	
	for(iter = g.node[s].begin(); iter!=g.node[s].end();iter++)
	{
		if(g.nodeExplored[*iter] == false)				//To check If The Node Stored In 'iter' Is Explored.
		{
			DFS(g,*iter);
		}
	}
	g.fTime[s] = label;							//Mark The Finishing Time for the Node.
	label--;
}
int main()
{
	Graph g;
	DFSLoop(g);
	g.Print();
	return 0;
}
