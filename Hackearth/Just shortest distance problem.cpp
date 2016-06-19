#include<iostream>
#include<vector>
#include<queue>

using namespace std;

vector<int> adj[1000];

int bfs(int start, int end){
	if(start == end)
		return 0;

	vector<int> dist(1000, -1);

	queue<int> q;
	q.push(start);
	dist[start] = 0;
	int distance = -1;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		
		for(int i=0; i< adj[u].size(); i++){
			int v = adj[u][i];
			//cerr  << v << "\n";
			if(dist[v] == -1){
				q.push(v);
				dist[v] = 1 + dist[u];
			}
			
			if(v == end) { distance = dist[v]; break;}
		}	
	}
	
	return distance;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n,q;
	cin>> n >> q;
	
	int querymode, start, end;
	
	while(q--){
		cin >> querymode ;
		
		if(querymode == 1){
			cin >> end;
			cout << bfs(1, end) << "\n";
		}
		else {
			cin >> start >> end;
			adj[start].push_back(end);
		}
	}
	return 0;
}