// uva 10920

#include<bits/stdc++.h>
using namespace std;

int main(){
	long long int G, p;
	
	enum direction{ top, left, down, right };
	
	while(scanf("%lld %lld", &G, &p) && G && p){

		long long counter = 0, incrementVal=1, currentVal=1;
		long long directionx = G/2 + 1, directiony= G/2 +1;
		direction dir= top;
		
		for(;currentVal<p; ){
			
			currentVal+= incrementVal;
			if(currentVal > p){
				currentVal -= incrementVal;
				incrementVal = p - currentVal;
				currentVal = p;
			}
			
			
			if(dir == top){
				directiony+= incrementVal;
				dir = left;
			}
		
			else if(dir == left){
				directionx-= incrementVal;
				dir = down;
			}
		
			else if(dir == down){
				directiony-=incrementVal;
				dir = right;
			}
			
			else {
				directionx+=incrementVal;
				dir = top;
			}
			
			counter++;
			if(counter ==2){
				counter = 0;
				incrementVal++;
			}
			
			//cerr << currentVal << " " << directionx << " " << directiony << " " << incrementVal << "\n";
			

		}
		
		printf("Line = %lld, column = %lld.\n", directiony, directionx);
	}

	return 0;
}