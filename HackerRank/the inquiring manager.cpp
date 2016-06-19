#include<bits/stdc++.h>
using namespace std;
int main(){

	int n;
	cin >> n;
	
	priority_queue<pair<long long, long long>> pq;
	int type;
	long long p, t;
	for(int i=0; i<n; i++){
		cin >> type;
		if(type == 1){
			cin >> p >> t;
			pq.push({p, t});
		}
		else{
			cin >> t;
			auto it = pq.top();
			long long val = t - 59;
			while(it.second < val && !pq.empty()){
				pq.pop();
				it = pq.top();
			}
			
			if(pq.empty())
				cout << -1 << "\n";
			else
				cout << it.first <<"\n";
			
		}
			
	}


	return 0;
}	