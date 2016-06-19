#include<bits/stdc++.h>
#define modval (long long) (1000000009)
using namespace std;
int main(){
	
	int t;
	cin >> t;
	
	long long n, sum = 0;
	cin >> n;
	
	sum += (n*n);
	cout << sum%modval  << " " << n*n;;
	
	
	return 0;
}