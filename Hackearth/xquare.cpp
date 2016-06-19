#include<bits/stdc++.h>
using namespace std;
long long A[100005], B[100005];
long long dp1[100005], dp2[100005];
int main(){
	int n,q;
	scanf("%d %d",&n, &q);
	for(int i=0, i<n; i++) scanf("%lld" , &A[i]);
	for(int i=0, i<n; i++) scanf("%lld" , &B[i]);
	
	int x = 2, y=1;
	dp1[0] = A[0];
	//for(int i=1; i<n; i++) { dp1[i] = dp1[i-1] + A[x] + B[y]; x+=2; y+=2; }
	
	x = 1; 
	y=2;
	dp2[0] = B[0];
	//for(int i=1; i<n; i++) { dp2[i] = dp2[i-1] + A[x] + B[y]; x+=2; y+=2; }
	
	while(q--){
		int temp, l, r;
		scanf("%d %d %d",&temp, &l , &r);
		if(temp ==1)	printf("%lld\n", dp1[r]-dp1[l]);
		else			printf("%lld\n", dp2[r]-dp2[l]);
	}
	
	return 0;
}