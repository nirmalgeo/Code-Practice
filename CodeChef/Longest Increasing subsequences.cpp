#include<bits/stdc++.h>
using namespace std;


int main(){
	
	int t;
	scanf("%d", &t);
	
	while(t--){
		int k;
		scanf("%d", &k);
		int n =k+2;
		
		cout << n << "\n";
		cout << 1 << " ";
		
		for(int i=k+1; i>1; i--)
			cout << i << " ";
		cout << n << "\n";
		
	}

	return 0;
}