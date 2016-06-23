#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		int n;
		scanf("%d", &n);
		
		int a[n];
		for(int i=0; i<n; i++)
			scanf("%d", &a[i]);
		
		int dp[n];
		memset(dp, 0 , sizeof dp);
		
		dp[0] = 1;
		vector<int> v;
		v.push_back(0);
		for(int i=1; i<n; i++){
			if(a[i] == a[i-1]){
				dp[i] = dp[i-1] + 1;
			}
			else{
				dp[i] = 1;
				v.push_back(dp[i-1]);
			}
		}
		v.push_back(dp[n-1]);
		v.push_back(0);
		int l = v.size();
		bool found = false;
		
		for(int i=1; i< l-1 ; i++){
			if(v[i] >=3){
				found = true;
			}
		}
		
	
		if(found)
			cout << "Yes\n";
		else
			cout << "No\n";
	
	}

	return 0;
}