//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};
vector<vector<int>> graph;
vector<int> nodes;
vector<int> givenVertices;


#define DFS_WHITE -1
#define DFS_BLACK 1
#define MAX 26

int totalnodes = 0;
int trees=0;
int acorn=0;

void dfs(int u){
	auto it = find(givenVertices.begin(), givenVertices.end(), u);
	if(it != givenVertices.end()){
		totalnodes++;
		nodes[u] = DFS_BLACK;
		for(int j=0; j < graph[u].size() ; j++){
			int v = graph[u][j];
			if(nodes[v] == DFS_WHITE)
				dfs(v);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	int t;
	cin >> t;
	
	while(t--){
// code starts here 
		string str;
		graph.assign(MAX, vector<int>());
		while(cin >> str){
		
			if(str[0] == '*')
				break;
			auto node1 = str[1] - 'A';
			auto node2 = str[3] - 'A';
			
			graph[node1].push_back(node2);
			graph[node2].push_back(node1);
			
		}
		cin >> str;
		nodes.assign(MAX,DFS_WHITE);
		for(int i=0; i< str.length(); i+=2){
			int temp = str[i] - 65;
			givenVertices.push_back(temp);
		}
		
		int numCC=0;
		for(int i=0; i<graph.size(); i++){
			auto it = find(givenVertices.begin(), givenVertices.end(), i);
			if(it!= givenVertices.end() && nodes[i] == DFS_WHITE){
				numCC++;
				totalnodes=0;
				dfs(i);
				if(totalnodes == 1) acorn++;
				else if(totalnodes > 1) trees++;
			}
		}
		cout << numCC << "\n";
		cout <<"There are "<< trees << " tree(s) and "<< acorn << " acorn(s).\n";
		
		graph.clear();
		nodes.clear();
		givenVertices.clear();
// code ends here 
	}

	return 0;
}