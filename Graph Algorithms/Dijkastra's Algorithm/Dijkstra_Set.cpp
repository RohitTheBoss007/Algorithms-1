
		//Running Time of O(mlogn) using Set Implementation.
#include<iostream>
#include<vector>
#include<list>
#include<fstream>
#include<sstream>
#include<set>

using namespace std;


const int n=201;									//Number of (Nodes+1).
typedef unsigned long long int ulli ;							
typedef std::pair <ulli, ulli> IntPair;							//Pair<Dijkstra Score,Node>

vector<list<IntPair> >G(n);								//Edge(v -> w) Pair<w,weight(v,w)>

set<IntPair> SHeap;


class Graph 
{
	public :
	
		bool NodeExplored[n];							//To check if Node is Explored.
		ulli Dscore[n];								//To Store Dijkstra Score.
		
		Graph();								//Constructor.
		void AdjList();								//To Construct Graph G1.
		void Dijkstra(const int source);					//Dijkstra's Function().
};

 Graph:: Graph()
{
	for(int i=1;i<n;i++)
	{
		
		Dscore[i] = 1000000;							// Intialize all D.S to 1000000.
		NodeExplored[i] = false;						//Mark all Nodes Unexplored.
		
	}
}

void Graph::AdjList ()
{
	int a,b,i=1;
	
	ifstream file;
    file.open("D2.txt");
    string line;
    
	while (getline(file, line))							// Take Input From The File.
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


void Graph::Dijkstra(const int source)							//src = Source Vertex.
{
	
	Dscore[source] = 0;								//D.S of Source = 0.
	
	SHeap.insert(make_pair(Dscore[source],source));					//Insert Pair with Updated Key.
	
	while(!SHeap.empty())
	{
		IntPair minIndex = *SHeap.begin();					//Stores Pair with Min D.S.
		SHeap.erase(SHeap.begin());						//Delete the Pair from The Set.
		
		int cv = minIndex.second;						//Stores The Vertex with Min D.S.
											//cv = Current Vertx.
		
		NodeExplored[cv] = true;						//Else Mark The Node Explored.
		
		for(auto i = G[cv].begin(); i!= G[cv].end();++i)
		{
			int dv = i->first;						// Points to Node Connected to Node 'cv'.
											//dv = Destination Vertex.
															
			ulli ew = i->second;						// Stores it's Edge Weight(ew).
			
			if(Dscore[cv]+ew < Dscore[dv]&& NodeExplored[dv]==false&& Dscore[cv]!=1000000)
			{								//Check if Node 'dv' is explored.
				 							//Check if Node 'cv' is Isolated. 
				 							//Check if ew + D.S(cv) < D.S(dv).
				
				if(Dscore[dv]!=1000000)							
				SHeap.erase(SHeap.find(make_pair(Dscore[dv],dv)));	//Find and Erase the Earlier Pair of
											// (D.S[dv],dv) From the Set.
											
				Dscore[dv] = Dscore[cv]+ew;				//If Yes, Update D.S of Node 'dv'.
				SHeap.insert(make_pair(Dscore[dv],dv));			//Reinsert The Pair with Updated Key.
			}
		}
	}
	
	for(int j=1;j<n;j++)
	{
		cout<<j<<" - "<<Dscore[j]<<endl;					//Print D.S of All Nodes.
	}
	
}

int main()
{
	Graph g;									//Initialize Object of Class Graph.
	g.AdjList();									//Construct The Graph.
	g.Dijkstra(1);									//Start Dijkstra's Algo with Node 1.
	return 0;
}
