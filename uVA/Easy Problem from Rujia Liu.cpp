#include<bits/stdc++.h>
#define INF 1000005
using namespace std;
vector<int> graph[INF];
int main() {
	int n,m;
	int a[INF];
	while(scanf("%d %d",&n,&m)!=EOF){
		for(int i=0; i <n ; i++)
			scanf("%d", &a[i]);
		
		for(int i=0 ; i<INF; i++)
			graph[i].clear();
			
		for(int i=0; i< n; i++)
			graph[a[i]].push_back(i);
			
		int k,v;
		for(int i=0; i< m; i++){
			scanf("%d %d", &k , &v);
			if( graph[v].size() < k)
				printf("0\n");
			else
				printf("%d\n", graph[v][k-1]+1);
		}
	}	
	
	return 0;
}