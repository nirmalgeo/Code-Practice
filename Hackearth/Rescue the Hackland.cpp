#include<bits/stdc++.h>
using namespace std;
//int arr[1000005];
int main(){

	int t;
	scanf("%d",&t);
	while(t--){
		long long l,r, k;
		scanf("%lld %lld %lld", &l , &r, &k);
		
		long long max = 0;
		if(l!=r){
			for(int i= l ; i<= r ; i++){
				long long val = i * k;
				if( val <= r){
					if((r - val)  > max)
						max = r-val;
				}
			}
		}
		printf("%d\n" , max+1);
	}
	return 0;
}