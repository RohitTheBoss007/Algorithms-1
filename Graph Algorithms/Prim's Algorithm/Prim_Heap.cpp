#include<iostream>
#include<vector>
#include<list>
#include<fstream>
#include<sstream>
#include<queue>

using namespace std;

typedef pair<int,int> IntPair;
const int n=5;
struct Compare
{
	bool operator () (const IntPair & lhs ,const IntPair &rhs)
	{
		return lhs.second >= rhs.second;
	}
	
};

priority_queue<IntPair, vector<IntPair> , Compare> Heap;

vector<list<IntPair> > G(n);
vector<list<IntPair> >MST(n);

class Graph
{
	public :
		bool NodeExplored[n];
		int cost[n];
		
		Graph();
		void AdjList();
		void Prim(const int source);
		void Print();
		
};

Graph:: Graph()
{
	for(int i=0;i<n;i++)
	{
		NodeExplored[i] = false;
		cost[i] = 10000;
	}
}

void Graph:: AdjList()
{
		int a,b,i=1;
	
	ifstream file;
    file.open("Prim_Test.txt");
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
	
	for(int i=1;i<n;i++)
	{
		cout<<"Node "<<i<<" - ";
		for(auto j=G[i].begin();j!=G[i].end();j++)
		{
			cout<<j->first<<","<<j->second<<" ";
		}
		cout<<endl;
	}
}

void Graph:: Prim(const int source)
{
	cost[source] = 0;
	int prevNode = source;
	
	Heap.push(make_pair(source,cost[source]));
	int minEdge = 10000;
	while(!Heap.empty())
	{
		IntPair minIndex = Heap.top();
		Heap.pop();
		
		int cv = minIndex.first;
		int cc  = minIndex.second;
		
		if(NodeExplored[cv]==true)
		{
			continue;
		}
		
		if(prevNode!=cv)
		{
			cout<<cv<<","<<prevNode<<endl;
			MST[prevNode].push_back(make_pair(cv,cc));
			MST[cv].push_back(make_pair(prevNode,cc));
		}
		
		NodeExplored[cv] = true;
		
		for(auto i = G[cv].begin();i!=G[cv].end();i++)
		{
			int dv = i->first;
			int dc = i->second;
			
			if(NodeExplored[dv] == false && dc<cost[dv]&&cost[cv]!=10000)
			{
				cost[dv] = dc;
				Heap.push(make_pair(dv,dc));
				if(minEdge>cost[dv])
				{
					minEdge = cost[dv];
					prevNode = cv;
				}
				
				
			}
		}
		
		
		
	}
	
}

void Graph:: Print()
{
	for(int i=1;i<n;i++)
	{
		cout<<"Node "<<i<<" - ";
		for(auto j=MST[i].begin();j!=MST[i].end();j++)
		{
			cout<<j->first<<","<<j->second<<" ";
		}
		cout<<endl;
	}
}

int main()
{
	Graph g;
	g.AdjList();
	g.Prim(1);
	g.Print();
	return 0;
}
