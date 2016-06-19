#include<bits/stdc++.h>
#define inf (int) -1e6
using namespace std;

int s, d;
typedef long long ll;

ll computeSum(int val, int s, int d){
	ll sum = 0;
	for(int j=0; j< 12; j++){
		if(val & (1<<j))
			sum+=s;
		else
			sum+=(-d);
	}
	return sum;
}




int main(){
	
	while(scanf("%d %d", &s , &d) != EOF){
		ll sum = -1;
		
		for(int i=0 ;i < (1<<12); i++){
			
			ll intersum = 0;
			bool found = true;
			for(int j=0; j < 12; j++){
				if(i & (1<<j))
					intersum += s;
				else
					intersum += (-d);
			
				if(j >=4 && intersum >=0 ) { found = false; break; } // not needed no surplus recorded
				
				else if( j >=4 ) {  intersum -= (i& (1 << (j-4)))? s : -d; }
				
			}
			
			if(found){
				sum = max(sum, computeSum(i, s, d));
			}
		}
		
		if(sum < 0)
			cout <<"Deficit\n";
		else
			cout << sum <<"\n";
	
	}

	return 0;
}