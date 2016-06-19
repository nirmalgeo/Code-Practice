#include<bits/stdc++.h>
using namespace std;
int main(){

	int t;
	scanf("%d", &t);
	while(t--){
		int n, j=0, k=0;
		scanf("%d", &n);
		long long A[1005], dp[1005], max = -1, count=0, sum =0;
		for(int i=0; i< n; i++){
			scanf("%lld", &A[i]);
		}
		
		for(int i=1; i< n; i++){
			max = A[i];
			count = 0;
			
			for(int j=0; j < i; j++){
				if(A[j] <= max)
					count++;
			}
			dp[k] = count;
			k++;
		}
		
		
		for(int i=0; i< k ;i++)
			sum += dp[i];
			
		printf("%lld\n", sum);
	
	}


	return 0;
}