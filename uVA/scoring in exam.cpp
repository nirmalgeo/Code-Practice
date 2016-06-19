#include<bits/stdc++.h>
using namespace std;
long long marks[100005], ti[100005], dp[100005];
bool myfunction (int i,int j) { return (i<j); }
int main(){
	int n,q,k;
	scanf("%d %d",&n,&q);
	vector<pair<long long, long long>> vec;
	for(int i=0; i<n; i++){
		scanf("%lld",&ti[i]);
	}
	
	for(int i=0; i<n; i++){
		scanf("%lld",&marks[i]);
		vec.push_back({marks[i], ti[i]});
	}
	
	sort(vec.rbegin(), vec.rend());
	long long temp = 0;
	int count = 0;
	for(auto &c : vec){
		temp = temp + c.second;
		dp[count++] = temp;
	}
	
	for(int i=0; i<q; i++){
		scanf("%d", &k);
		printf("%lld\n", dp[k-1]);
	}
	
	return 0;
}