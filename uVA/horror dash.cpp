#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d", &t);
	for(int i=1; i<=t; i++){
		int max = -1;
		int temp;
		int n;
		scanf("%d", &n);
		for(int j=1; j<=n; j++){
			scanf("%d", &temp);
			if(temp > max)
				max = temp;
		}
		printf("Case %d: %d\n", i , max);
	}

	return 0;
}