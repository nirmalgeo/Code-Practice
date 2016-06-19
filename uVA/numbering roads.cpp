#include<bits/stdc++.h>
using namespace std;
int main(){
	int r,n;
	int tt=1;
	while(scanf("%d %d", &r , &n) && r && n){
		int val = r/n;
		if(r%n ==0)
			val--;
		printf("Case %d: ", tt++);
		if(val > 26)
			printf("impossible\n");
		else
			printf("%d\n", val);
	
	}
	
	return 0;
}