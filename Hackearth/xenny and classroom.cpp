#include<bits/stdc++.h>
#define INF 2000005
using namespace std;


int main(){
	int t;
	
	scanf("%d", &t);
	
	string first, second;
	first = second =  "";
		
	for(int i=0; i<INF; i+=2) { first += "BG"; second +="GB"; }
	
	
	while(t--){
		int n;
		scanf("%d", &n);
		
		string s;
		cin >> s;
		
		string tempA = first.substr(0, 2*n);
		string tempB = second.substr(0, 2*n);
		
		int aCount , bCount ;
		aCount = bCount = 0;
		
		for(int i=0; i< 2*n ; i++){
			if(tempA[i] != s[i]) aCount++;
			if(tempB[i] != s[i]) bCount++;
		}
			
		int ans = aCount < bCount? aCount: bCount;
		
		cout << ans/2 << "\n";
	
	}

	return 0;
}