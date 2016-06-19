#include<bits/stdc++.h>
using namespace std;
map<int, int> order;
	
int main(){
	int k,m,n, temp;
	cin >> k >> m >> n;
	
	map<int, int> order;
	
	for(int i=0; i<n; i++){
		cin >> temp;
		order[temp]++;
	}
	priority_queue<pair<int, int>> pq;
	for(auto &c: order){
		pq.push({c.second, -1*c.first});
	}
	
	while(k--){
		auto it = pq.top();
		pq.pop();
		cout << it.second * -1 << "\n";
	}

	return 0;
}