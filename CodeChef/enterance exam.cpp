#include<bits/stdc++.h>
using namespace std;
int main(){

	int t;
	scanf("%d",&t);
	while(t--){
		int n, k, e;
		long long m, ans = 0, sergey = 0, val, temp;
		priority_queue<long long> pq;
		cin >> n >> k >> e >> m;
		
		for(int i=1; i<n; i++){
			val = 0;
			for(int j=1; j<=e; j++){
				cin >> temp;
				val += temp;
			}
			pq.push(val);
		}
		
		for(int j=1; j<e; j++){
			cin >> temp;
			sergey+=temp;
		}
		
		int diff = n-k;
		
		while(k--){
			val = pq.top();
			pq.pop();
		}
		
		if((sergey- val) > 0)
			ans = 0;
		else{
			ans = abs(sergey- val) + 1;	
		}
		
		if(n==1 || (n-k == 0))
			ans = 0;
			
		
		if(ans <=m )
			cout << ans << "\n";
		else
			cout << "Impossible\n";
	}

	return 0;
}