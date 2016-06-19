#include<bits/stdc++.h>

using namespace std;
long long arr[100005];
int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		long long n,m,z;
		scanf("%lld %lld %lld" , &n , &m , &z);
		long long sumEven = 0 , sumOdd = 0;
		
		for(int i=1; i<=n; i++) {
			scanf("%lld", &arr[i]);
			if(i%2 == 0) sumEven = (sumEven + arr[i])%m;
			else sumOdd = (sumOdd + arr[i])%m;
		}
		
		if(n==z) { printf("%lld\n" , (sumOdd-sumEven)%m); }
		else {
			for(int i=n+1 ;i <=z ;i++){
				
		
			}
		}
	}
	
	return 0;
}