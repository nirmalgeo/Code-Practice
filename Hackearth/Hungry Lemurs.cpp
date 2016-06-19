#include<bits/stdc++.h>
#define INF 1e6
using namespace std;
int main(){
	int n,k;
	scanf("%d %d",&n , &k);
	int tempN = n, tempK = k;
	int upperN,  upperK;
	
	if(k > n){
		printf("%d",k-n);
	}
	
	else{
		vector<int> countArr;
		countArr.resize(5);
		int count=0;
		
		while(n%k!=0){
			vector<int> mod,copy;
			mod.resize(4,INF);
			
			mod[0] = 
		}
		
		printf("%d", count);
	}
	return 0;
}