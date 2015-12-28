#include <iostream>
#include <vector>
#include <fstream>
#include<list>
#include <sstream>
#include<stack>
using namespace std;

 const unsigned long int n = 10;					//Total Number of (Nodes+1).
									//Scaled upto 1 million nodes 
									//(Stanford Programming Assignment)
													
 vector<list<unsigned long int> > node(n);				// Original Graph(G).
 vector<list<unsigned long int> > nodeRev(n);				//Reverse Graph(Grev).
 
class Graph
{
	public:
	 
	bool nodeExplored[n-1] = {false};				//Intializing all Nodes unexplored.
	unsigned int fTime[n-1];					//Intializing Finishing Times.
	bool FirstPass = true;						//Bool For 1st Pass(Kosaraju's Two Pass Algo)
	bool SecondPass = false;					//Bool For 2nd Pass(Kosaraju's Two Pass Algo)
	
	Graph();							//Default Constructor.
	void GraphRev();						//Graph Reversal Function .
	void ClearAll();						//Delete Nodes of G.
	void FinishTime2(Graph & g2);					//To Replace Nodes of G by their Finishing Times(FT).
	void Print();							//To Print FTs.
	
};

Graph :: Graph()
{

}



void Graph :: GraphRev()
{
	
	list<unsigned long int> :: iterator iter;			//Initialize Iterator.
	
	for (int i=1;i < node.size(); i++)
	{
		for(iter = node[i].begin(); iter!= node[i].end(); iter++)
		{
			nodeRev[*iter].push_back(i);			//Reversing The Graph G and storing in Grev.
		}
		
	}
	
	cout<<" The Reversed Graph\n\n";
	for(int i=1;i<n;i++)
	{
		cout<<"\t"<<i<<" - ";
		
		list<unsigned long int> :: iterator iter;
		
		for(iter = nodeRev[i].begin();iter!= nodeRev[i].end();iter++)
		{
			cout<<*iter<<" ";
		}
		cout<<endl;
	}
	
	cout<<"\n\n";
}

void Graph :: ClearAll()
{
	for (int i=1;i<n;i++)
	{
		node[i].clear();					//Deleting Nodes of G.
									//(Later to be Replaced by their FTs)
	}
	node.clear();
	node.resize(n);							//Resizing it to it's Original Size.
}

void Graph :: FinishTime2(Graph & g)
{
	FirstPass = false;						//1st Pass Complete.
	SecondPass = true;						//2nd Pass Start.
	
	list<unsigned long int> :: iterator iter;
	
	for (int i=1;i< nodeRev.size();i++)
	{
		for(iter = nodeRev[i].begin(); iter != nodeRev[i].end(); iter++)
		{							//Copying FT of Grev to 
		  	node[g.fTime[*iter]].push_back(g.fTime[i]);	//Nodes of G + Reversing Direction of Edges.
			 
		}
	}
	
	cout<<" Updated Nodes (Finishing Times) Of Original Graph \n\n";
	
	for(int i=1;i<n;i++)
	{
		cout<<"\t"<<i<<" - ";
		
		for(iter = node[i].begin();iter!= node[i].end();iter++)
		{
			cout<<*iter<<" ";
		}
		cout<<endl;
	}
	
	cout<<"\n\n";
}

void Graph :: Print()
{
	cout<<" Finishing Time Of Graph Grev\n\n";
	for(int i=1;i<n;i++)
	{
		cout<<"\tFT of "<<i<<" is " <<fTime[i]<<endl;
	}
	cout<<"\n\n";
}


int label = 1;								//Label For FTs.
unsigned long int scc = 0;						//To Count Number of SCCs.
vector<int> sccSize(10,1);								//Size Of Each SCC.

void DFS(Graph & g, int s);						//DFS Prototype.


void DFSLoop(Graph &g)
{
	
	for (int i= n-1 ; i >= 1; i--)
	{
		if(g.nodeExplored[i] == false)				//To Check if any Nodes left out.
		{
			if(g.SecondPass)
			{
				scc++;					//To Count The Number SCCs.
			}
			DFS(g,i);					//To Explore outgoing Edges from Node i.
		}
	}
}




void DFS(Graph & g, int s)						//Iterative Depth First Search.
{
	stack<unsigned long int> nodes;					//Intialize a Stack To Store Nodes.
	
	unsigned long int u;						//To Store Top Most Node on the Stack.
	
	list<unsigned long int> :: iterator iter;
	
	nodes.push(s);							//Insert Node 's = i' on the Stack.
	g.nodeExplored[s] = true;					//Mark Node 's' True.

	while(!nodes.empty())						//Loop Till Stack Not Empty.
	{
		u = nodes.top();					// Stores The Top Most Node of Stack.
		nodes.pop();						//Pops The Top Most Node from Stack.
		
		
		if(g.FirstPass == true)					//DFS On Grev.
		{
			for(iter = nodeRev[u].begin(); iter!= nodeRev[u].end();iter++)
			{											
				if(g.nodeExplored[*iter] == false)	//Checking if one of the Nodes (w) 
				{					//connected to 'u' is not Explored.
					
					nodes.push(u);			//Insert node 'u' back to the Stack.
					g.nodeExplored[*iter] = true;	//Mark 'w' Explored.
					nodes.push(*iter);		//Insert node 'w' on the Stack.
					break;				//Break Out of the Loop.
			
				}
			
			}
			
				if(iter == nodeRev[u].end())		// If All The Nodes Connected to 'u'are Explored.
									// The First Node to satisfy the Condition
									// will be The Sink Vertex.
				{
		    		g.fTime[u] = label;			// Assigning The Finishing Times of Grev.		
					label++;
				}
		}
		
		
		
		if(g.SecondPass == true)				//DFS On G.
		{
			for(iter = node[u].begin(); iter!= node[u].end();iter++)
			{
				if(g.nodeExplored[*iter] == false)	//Same As Above.
				{
					nodes.push(u);
					g.nodeExplored[*iter] = true;
					nodes.push(*iter);
					
					sccSize[scc]  += 1;		//To Count the Size of a SCC.
					
					break;
					
				}
				
				
			}
		
		}
	
	
	
	}
	
}

 Graph g1, grev;							// Intialize Objects of Class Graph.
 
int main()
{
	int a,b;
	
	ifstream file;							//Reading The Input From The File.
    file.open("SCC_Test.txt");
    
    string line;
    
	while (getline(file, line))
		{
			istringstream iss(line);
			while ((iss >> a>> b))
			{
				node[a].push_back(b);			// Store The Inputs in Graph G.
			}
		}
	file.close();
	
	
	grev.GraphRev();						//Reverse Graph G and Store in Grev.
	
	DFSLoop(grev);							//Find The FTs of Grev.
	
	grev.Print();							//Print FTs of Grev.
	
	g1.ClearAll();							// Delete All Nodes of G.
	
	g1.FinishTime2(grev);						//Replace The Nodes By Their FTs.
	
	
	DFSLoop(g1);							// Compute Number And Size Of SCCs.
	
	cout<<" Number of SCCs - "<<scc<<"\n\n";

	for(int i = 1;i<= scc;i++)
	{
		cout<<" Size of SCC "<<i<<" - "<<sccSize[i]<<endl;	
	}
	return 0;
}
