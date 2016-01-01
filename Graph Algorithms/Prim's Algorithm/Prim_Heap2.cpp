		//Running Time mlog(n) using Priority Queue.

#include<iostream>
#include<vector>
#include<list>
#include<fstream>
#include<sstream>
#include<queue>

using namespace std;

typedef pair<int,int> IntPair;									//Pair<Node,Cost>

const int n=5;											//Number of (Nodes+1).


class Node				
{
	public:
	int currNode;										//Store Node 'v' of edge (u->v)
	int currCost;										//Store Cost of edge (u->v)
	int prevNode;										//Store Node 'u' of edge (u->v)
	
	Node(int curr , int cos , int prev) 					        	//Parameterised Constructor.
	{
		currNode = curr;
		currCost = cos;
		prevNode = prev;
	}
};


struct Compare											//Custom Comparator for Priority Queue.
{
	bool operator () (const Node & lhs ,const Node &rhs)
	{
		return lhs.currCost >= rhs.currCost;					       //Store in inc order of cost.
	}
	
};


priority_queue<Node, vector<Node> , Compare> Heap;			                	//Intialize Priority Queue.

vector<list<IntPair> > G(n);									//Original Graph (G1).
vector<list<IntPair> >MST(n);									//MST Graph.


class Graph
{
	public :
		
		bool NodeExplored[n];								//To check if Node is Explored.
		int cost[n];									//To Store cost.
		
		Graph();						          		//Constructor.
		void AdjList();									//To Construct Graph G1.
		void Prim(const int source);							//Prim Function.
		void HeapInsert(const int & cv);						//Insert Minimum Element in Heap.
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
    
	while (getline(file, line))						        	// Take Input From The File.
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
	
	cout<<"\n\n\tOriginal Graph\n\n";
	for(int i=1;i<n;i++)
	{
		
		cout<<"\tNode "<<i<<" -> ";
		
		for(auto j=G[i].begin();j!=G[i].end();j++)
		{
			cout<<"Node - "<<j->first<<",Cost - "<<j->second<<"; ";
		}
		
		cout<<endl;
	}
}

void Graph::HeapInsert(const int & cv)
{
		for(auto i = G[cv].begin();i!=G[cv].end();i++)
		{
			int dv = i->first;							//dv = Destination Vertex.
			int dc = i->second;							//dc = Destination Cost.
			
			if(NodeExplored[dv] == false && dc < cost[dv]&& cost[cv]!=10000)
			{									//Check if Node 'dv' is explored.
				 								//Check if Node 'cv' is Isolated. 
				 								//Check if ew < cost[dv].
				 										
				cost[dv] = dc;							//If Yes, Update D.S of Node 'dv'.
				Heap.push(Node(dv,cost[dv],cv));	                	//Reinsert The Pair with Updated Key.		
			}
		}
}

void Graph:: Prim(const int source)
{
	cost[source] = 0;									//Cost of Source Vertex = 0.
	NodeExplored[source] = true;						                //Mark Source Vertex = True.
	
	HeapInsert(source);									//Call HeapInsert Funtion.
	
	while(!Heap.empty())
	{
		Node minIndex = Heap.top();						        //Stores Object of class 'Node' with Min Cost.
		Heap.pop();									//Delete the Object from The Heap.
		
		int cv = minIndex.currNode;						        // Current Vertex = Node v
		int cc  = minIndex.currCost;				                	//Current Cost  = Edge cost of (u->v)
		int pv = minIndex.prevNode;					        	// Previous Vertex  = Node u
		
		if(NodeExplored[cv]==true)					         	//If Node Already Explored -> Skip.
		{
			continue;
		}
		
		NodeExplored[cv] = true;					        	//Else Mark The Node Explored.
		
		MST[pv].push_back(make_pair(cv,cc));		                        	//Construct The MST Graph.
		MST[cv].push_back(make_pair(pv,cc));
		
		HeapInsert(cv);									// Call HeapInsert Function.
			
	}
	
}

void Graph:: Print()
{
	cout<<"\n\n\t MST Graph\n\n";
	
	for(int i=1;i<n;i++)
	{
		cout<<"\tNode "<<i<<" -> ";
		
		for(auto j=MST[i].begin();j!=MST[i].end();j++)
		{
			cout<<"Node - "<<j->first<<", Cost - "<<j->second<<"; ";
		}
		
		cout<<endl;
	}
}

int main()
{
	Graph g;										//Initialize Object of Class Graph.
	g.AdjList();										//Construct The Graph.
	g.Prim(3);										//Start Prim's Algo from Any Node.
	g.Print();
	return 0;
}
