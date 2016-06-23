#include<bits/stdc++.h>
using namespace std;
int main(){
	
	int n;
	cin >> n;
	
	int maxx = 0, minn = 0;
	
	minn = (n/7)*2;
	
	minn +=  ((n%7) <= 5)? 0: 1;

	
	maxx = (n/7)*2;
	
	maxx +=  ((n%7) > 2)? 2:  (n%7);
	
	cout << minn << " " << maxx;


	return 0;
}