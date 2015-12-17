#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<fstream>
#include<sstream>

using namespace std;

class Graph
{
	public: 
	
	int n;										//To Store Number of (Nodes+1).
	vector<list<int> > Node;					//Adjaceny List To Store a Graph( Call It G1).
	vector<bool> NodeExplored;					//To check If The Node is Explored.
	vector<int> Layer;							//To Layer Index (LI) The Nodes.
	
	Graph(int);									//Constructor.
	void AdjList();								//To Build G1.
};
Graph:: Graph(int total)
{
	n = total;									//Resize All Parameters To The Number of Nodes.
	Node.resize(n);
	NodeExplored.resize(n);
	Layer.resize(n);
}

void Graph :: AdjList()
{
	int i=1,a;
	
	ifstream file;
	
    file.open("BFS_Test.txt");
    string line;
    
	while (getline(file, line))
		{
			istringstream iss(line);
			
			while ((iss >> a))
			{
				if(i!=a)					//This done to skip the First Number in the Line
				{
					Node[i].push_back(a); 	//Add contents in G1.
				}
			}
			i++;
		}
	file.close();
	
}
void BFS(Graph &g , int s)
{
	queue<int> Q;							//Initialize a Queue.
	Q.push(s);								//Add The Source Vertex 's' in Queue.
	
	g.NodeExplored[s] = true;				//Mark 's' explored.
	g.Layer[s] = 0;							//LI of s =0.
	
	cout<<" Layer Index of Node "<<s<<" - "<<g.Layer[s]<<endl;
	
	while(!Q.empty())
	{
		int u = Q.front();					//Store the First Element of Queue in 'u'.
		Q.pop();							//Remove the First Element of Queue.
		
		for(auto i = g.Node[u].begin(); i!= g.Node[u].end();++i)
		{
			
			if(g.NodeExplored[*i] == false)	//Check if The Given Node connected to 'u' is Explored
			{
				
				g.NodeExplored[*i] = true;	//If Not,Mark it Explored.
				g.Layer[*i] = g.Layer[u]+1; //LI[Given Node] = LI[U] +1.				
				Q.push(*i);					//Add The Given Node in the Queue.
				
				cout<<" Layer Index of Node "<<*i<<" - "<<g.Layer[*i]<<endl;
				
			}
			
		}
		
	}
}

int main()
{
	Graph g1(7);							//Intitalize an Object of Class Graph.
											//Number of Nodes  = 6.
	g1.AdjList();
	
	BFS(g1,1);
	
	return 0;
}
