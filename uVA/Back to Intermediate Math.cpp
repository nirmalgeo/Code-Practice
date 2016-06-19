#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d", &t);
	double u,v,d,t1,t2;
	for(int i=1; i<=t; i++){
		cin>>d>>v>>u;
		if(u ==0 || v==0 || v>=u)
			printf("Case %d: can't determine", i);
		else {
        t1=d/u;
        t2=d/sqrt(u*u-v*v);
		printf("Case %d: %0.3lf\n",t, abs(t2-t1));
		}
	}

	return 0;
}