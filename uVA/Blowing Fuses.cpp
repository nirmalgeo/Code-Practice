#include<bits/stdc++.h>
using namespace std;
int main(){
	long long tt=1;
	while(1){
		long long n,m,c;
		cin>>n>>m>>c;
		if(n==0)
			break;
		
		assert(n<=20);
		long long cost[21],state[21],total=0;
		bool fuse=false;
		long long maxPower = total;
		memset(cost,0, sizeof(cost));
		memset(state, 0, sizeof(state));
		for(long long ii=1;ii<=n;ii++)
			cin>>cost[ii];
		
		for(long long ii=1;ii<=m;ii++){
			long long a;
			cin>>a;
			if(state[a]){
				total-=cost[a];
				state[a] = 0;
			}
			else{	
				total+=cost[a];
				state[a] = 1;
			}
				
			if(total<0)
				total=0;
			
			if(total>c)
				fuse= true;
			if(total>maxPower)
				maxPower=total;
			
		}
		
		cout<<"Sequence "<< tt<<"\n";
		if(fuse)
			cout <<"Fuse was blown.\n\n";
		else{
			cout <<"Fuse was not blown.\n";
			cout <<"Maximal power consumption was "<<maxPower<<" amperes.\n\n";
		}
		
		tt++;
	}

	return 0;
}