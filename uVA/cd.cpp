#include<bits/stdc++.h>
using namespace std;
bool arr[100000000];
int main(){
	long long n,m;
	while(scanf("%lld %lld", &n, &m)){
		if(!n && !m)
			break;
		memset(arr, false , sizeof(arr));
		long long count = 0, temp;
		for(int i=1; i<= n; i++){
			scanf("%lld",&temp);
			arr[temp] = true;
		}
		
		for(int i=1 ; i<=m; i++){
			scanf("%d",&temp);
			if(arr[temp])
				count++;
		}	
		printf("%d\n", count);
	
	
	}
	return 0;
}