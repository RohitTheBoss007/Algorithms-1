		//Running Time Of O(mn) using Brute Force.

#include <iostream>
#include <vector>
#include <fstream>
#include<list>
#include <sstream>
using namespace std;

const int n = 201;								//Number of (Nodes+1).

typedef std::pair <int, int> IntPair;						//Pair<Node,Dijkstra Score>
vector<list<IntPair> > node(n);							//Edge(v -> w) Pair<w,weight(v,w)>

class Graph
{
	public :
		unsigned long long int dist[n];					//To Store Dijkstra's Score of each node.
		bool nodeExplored[n] = {false};					//To check if Node is Explored.
		
		
		Graph();							//Constructor.
		void AdjList();							//To Construct Graph G1.
		int MinIndex();							//Find Index with Min Dijkstra's Score(D.S).
		void Dijkstra(int src);						//Dijkstra's Function().
};

Graph :: Graph()
{
	for (int i=0;i<n;i++)
	{
		dist[i]=1000000;						// Intialize all D.S to 1000000.
	}
}

void Graph :: AdjList()
{
	int a,b,i=1;
	
	ifstream file;
    file.open("D2.txt");
    string line;
    
	while (getline(file, line))						// Take Input From The File.
		{
			istringstream iss(line);
			char seperator;
			while ((iss >>a>>seperator>>b)&& seperator==',')
			{
				node[i].push_back(make_pair(a,b));
			}
			i++;
		}
	file.close();
	
}

int Graph :: MinIndex()
{
	int minIndex;								//To Store Index with Min Dijkstra's Score(D.S).
	
	unsigned long minDist = 1000000;						// To Store Min D.S.
	
	for(int i=1;i<n;i++)
	{
		if(nodeExplored[i] == false && dist[i]<minDist)			//Check If Node Explored and
		{								//If it's D.S < Minimum D.S.
			
			minDist = dist[i];					// If Yes ,Update Min D.S.
			minIndex = i;						//Update Index.
			
		}
	}
	
	return minIndex;							//Returns Index with Min D.S.
}

void Graph :: Dijkstra(int src)							//src = Source Vertex.
{
	dist[src]=0;								//D.S of Source = 0.
	
	list<IntPair> :: iterator iter;						//Initialize Iterator.
	
	for(int i=1;i<n-1;i++)
	{
			int u = MinIndex();					//Stores The Index with Min D.S.
			
			nodeExplored[u] = true;					//Mark Node 'u' Explored.
			
			for(iter = node[u].begin(); iter!= node[u].end();iter++)
			{
				
				int v = iter->first;				// Points to Node Connected to Node 'u'.
				
				unsigned long int edge = iter->second;		// Stores it's Edge Weight(EW).
				
				 if(nodeExplored[v] == false && dist[u]!=1000000 && (dist[u]+edge)<dist[v])
				 {						//Check if Node 'v' is explored.
				 						//Check if Node 'u' is Isolated. 
				 						//Check if EW + D.S(u) < D.S(v).
				 										
			 		dist[v] = dist[u] + edge;		//If Yes, Update D.S of Node 'v'.
			 		
			 	 }
			 	 
			}
	}
	
	for(int j=1;j<n;j++)
	{
		cout<<j<<" - "<<dist[j]<<endl;					//Print D.S of All Nodes.
	}
	
}

int main()
{
	Graph g;								//Initialize Object of Class Graph.
	g.AdjList();								//Construct The Graph.
	g.Dijkstra(1);								//Start Dijkstra's Algo with Node 1.
	return 0;
}
