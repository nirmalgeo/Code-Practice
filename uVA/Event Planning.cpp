#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,b,h,w;
	while(scanf("%d %d %d %d", &n , &b, &h, &w)!=EOF){
		int hCost, weekCount;
		long cost = b+1;
		for(int i=0; i<h;i++) {
			scanf("%d", &hCost);
			for(int j=0; j<w; j++) {
				scanf("%d",&weekCount);
				long tempCost = n*hCost;
				if(weekCount >= n && tempCost<=b && tempCost < cost)
					cost= tempCost;
			}
		}
		if(cost==b+1)
			printf("stay home\n");
		else
			printf("%d\n",cost);
		
	
	}
	return 0;
}