#include<bits/stdc++.h>

using namespace std;
int m, n , k, ans;
vector<vector<int>> graph, sol;
set<int> nodes;
vector<int> out, temp;
bool used[110];

bool isAdjacentBlack(int at){
	for(int i=0; i< graph[at].size(); i++){
		int node = graph[at][i];
		if(used[node]) return false;
	}
	//cout << "true" ;
	return true;
}

void generate(int at, int val){

	if(val > ans) {
		ans = val;
		out = temp;
	}
	
	else {
		for(auto c : nodes){
			int node = c;
			if( !used[node] && isAdjacentBlack(node)){
				//cout << "node :" << node << "\n";
				used[node] = true;
				temp.push_back(node);
				generate(at+1, val+1);
				temp.pop_back();
				used[node] = false;
			}
		}
	}
}


int main(){
	freopen("out", "w", stdout);

	scanf("%d", &m);
	while(m--){

		scanf("%d %d", &n , &k);
		graph.resize(n+1);
		int x, y;
		for(int i=1; i<=k; i++){
			scanf("%d %d", &x , &y);
			nodes.insert(x);
			nodes.insert(y);
			graph[x].push_back(y);
			graph[y].push_back(x);
		}
		
		memset(used, false, sizeof used);
		generate(0 , 0 );
		
		cout << ans << "\n";
		//sort(out.begin(), out.end());
		for(int i=0; i< out.size()-1; i++)
			cout << out[i] << " ";
		cout << out[out.size()-1] << "\n";
			
		
		temp.clear();
		graph.clear();
		out.clear();
	}

	return 0;
}