#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin >> t;

	while(t--){
		long long n, sum=0, twos=0;
		cin >> n;
		
		sum = n * (n+1) /2;
		
		for(int i=1; i<=n; i<<=1){
			twos+= i;
		}
		
		sum = sum - 2*twos;
		cout << sum << "\n";
	}
	return 0;
}