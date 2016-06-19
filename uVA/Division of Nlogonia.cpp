#include<bits/stdc++.h>
using namespace std;
int main(){
	int k;
	while(scanf("%d", &k) && k){
		int divx, divy;
		scanf("%d %d",&divx, &divy);
		
		for(int i=1; i<=k; i++){
			int tempX, tempY;
			scanf("%d %d", &tempX , &tempY);
			if(tempX == divx || tempY == divy)
				printf("divisa\n");
			else if(tempX > divx && tempY > divy)
				printf("NE\n");
			else if(tempX < divx && tempY > divy)
				printf("NO\n");
			else if(tempX < divx && tempY < divy)
				printf("SO\n");
			else
				printf("SE\n");
		
		}
		
	}
	return 0;
}