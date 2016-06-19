#include<bits/stdc++.h>
using namespace std;

class Graph{
		int n;
		vector<int> *adj;
	
	public:
		
		Graph(int n);
		void addEdge(int s, int d);
		void printGraph();
		bool checkEulerianTour();
};

Graph::Graph(int n)
{
	this->n = n;
	this->adj = new vector<int>[n+1];
}

void Graph::addEdge(int s, int d)
{
	adj[s].push_back(d);
}


void Graph::printGraph()
{
	for(int i=0;i <= n; i++)
	{
		cout << "\n";
		cout << i << "-->";
		for(auto &c:  adj[i])
			cout << c << "-->" ;
	}
}

bool Graph::checkEulerianTour()
{
	for(int i=0;i <=n;i++)
	{
		if(adj[i].size()%2 == 1)
			cout<<"\n Not an Eulerian Tour on node" << i << " size:" << adj[i].size();
	}

	bool arr[n+1];
	memset(arr,false, sizeof(arr));
	for(int i=0; i<=n; i++)
	{
		for(auto &c: adj[i])
		{
			if(c == (i+1)%n)
			{
				arr[i] = true;
				continue;
			}
		}
	}
	
	for(int i=0;i <=n;i++)
	{
		if(!arr[i])
		{
			cout<<"\n Not connected:" << i;
			return false;
		}	
	}
}


int main()
{

	Graph G(5);
	G.addEdge(0,1);
	G.addEdge(1,2);
	G.addEdge(2,3);
	G.printGraph();
	G.checkEulerianTour();
	/*
	
	cout<<"\n New object:\n";
	Graph n(2);
	n.addEdge(2,0);
	n.printGraph();
	*/
	


	return 0;
}