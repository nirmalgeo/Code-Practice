#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		int count =0;
		int lost = 0,temp;
		for(int i=0; i<n; i++){
			scanf("%d",&temp);
			count+=temp;
			if(count < 0) {
				lost++;
				count = 0;
			}
		}
		printf("%d\n",lost);
	
	}
	return 0;
}