#include<bits/stdc++.h>
#define INF 1000000007
using namespace std;
long long arr[1000005], dp[1000005];
int main(){
	int n,k;
	scanf("%d %d", &n ,&k);
	for(int i=0; i< n; i++)	
		scanf ("%lld", &arr[i]);
	
	for(int i=0; i< n-k+1; i++){
		int temp = i;
		for(int j=1; j <= k ; j++){
			dp[i] = (dp[i] + arr[temp] * j * j)%INF;
			temp++;
		}
	}
	
	
	for(int i=0; i< n-k+1; i++)
		printf("%lld ", dp[i]);
	return 0;
}