	//Running Time of O(mlogn) using Priority Queue.

#include<iostream>
#include<queue>
#include<vector>
#include<list>
#include<fstream>
#include<sstream>

using namespace std;


const int n=201;										//Number of (Nodes+1).

typedef std::pair <int, unsigned long long int> IntPair;					//Pair <Node,Dijkstra Score>

struct Compare											//To Compare The Dijkstra Score(D.S)
{												//Of Two Nodes.
	public :bool operator ()(IntPair &p1 ,IntPair &p2){return p1.second >= p2.second;}
};

vector<list<IntPair> >G(n);									//Edge(v -> w) Pair<w,weight(v,w)>

priority_queue<IntPair, vector<IntPair>, Compare> Heap;


class Graph 
{
	public :
	
		bool NodeExplored[n];								//To check if Node is Explored.
		unsigned long long int Dscore[n];						//To Store Dijkstra Score(D.S).
		
		Graph();									//Constructor.
		void AdjList();									//To Construct Graph G1.
		void Dijkstra(const int source);						//Dijkstra's Function().
};

 Graph:: Graph()
{
	for(int i=1;i<n;i++)
	{
		
		Dscore[i] = 1000000;								// Intialize all D.S to 1000000.
		NodeExplored[i] = false;							//Mark all Nodes Unexplored.
		
	}
}

void Graph::AdjList ()
{
	int a,b,i=1;
	
	ifstream file;
    	file.open("D2.txt");
	  string line;
    
	while (getline(file, line))								// Take Input From The File.
		{
			
			istringstream iss(line);
			char seperator;
			
			while ((iss >>a>>seperator>>b)&& seperator==',')
			{
				
				G[i].push_back(make_pair(a,b));
					
			}
			
			i++;
			
		}
	file.close();
	
}


void Graph::Dijkstra(const int source)								//src = Source Vertex.
{
	
	Dscore[source] = 0;									//D.S of Source = 0.
	
	Heap.push(make_pair(source,Dscore[source]));						//Reinsert Pair with Updated Key.
	
	while(!Heap.empty())
	{
		IntPair minIndex = Heap.top();							//Stores Pair with Min D.S.
		Heap.pop();									//Delete the Pair from The Heap.
		
		int cv = minIndex.first;							//Stores The Vertex with Min D.S.
												//cv = Current Vertx.
															
		if(NodeExplored[cv] == true)							//If Node Already Explored -> Skip.
		{
			continue;
		}
		
		NodeExplored[cv] = true;							//Else Mark The Node Explored.
		
		for(auto i = G[cv].begin(); i!= G[cv].end();++i)
		{
			int dv = i->first;							// Points to Node Connected to Node 'cv'
												//dv = Destination Vertex.
															
			unsigned long long int ew = i->second;					// Stores it's Edge Weight(ew).
			
			if(Dscore[cv]+ew < Dscore[dv]&& NodeExplored[dv]==false&& Dscore[cv]!=1000000)
			{									//Check if Node 'dv' is explored.
				 								//Check if Node 'cv' is Isolated. 
				 								//Check if ew + D.S(cv) < D.S(dv).
				
				Dscore[dv] = Dscore[cv]+ew;					//If Yes, Update D.S of Node 'dv'.
				Heap.push(make_pair(dv,Dscore[dv]));				//Reinsert The Pair with Updated Key.
			}
		}
	}
	
	for(int j=1;j<n;j++)
	{
		cout<<j<<" - "<<Dscore[j]<<endl;						//Print D.S of All Nodes.
	}
	
}

int main()
{
	Graph g;										//Initialize Object of Class Graph.
	g.AdjList();										//Construct The Graph.
	g.Dijkstra(1);										//Start Dijkstra's Algo with Node 1.
	return 0;
}
