#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		int length;
		scanf("%d", &length);
		int num;
		scanf("%d",&num);
		int l[21];
		for(int ii=0; ii < num ; ii++)
			cin>> l[ii];
			
		int sum;
		bool found = false;
		for(int i=0; i< (1 << num) ;i++){
			sum=0;
			for(int j=0; j < num; j++){
				if( i & ( 1 << j))
					sum+=l[j];
			}
			if(sum == length){
				found = true;
				break;
			}
		}
		if(found)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}