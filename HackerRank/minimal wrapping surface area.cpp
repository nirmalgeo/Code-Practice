#include<bits/stdc++.h>
using namespace std;
int main(){

	int n, w, h, l;
	
	cin >> n;
	cin >> w >> l >> h;
	
	int a , b , c;
	a = n / w;
	b = n / l;
	c = n / h;
	
	cout << 2 * ( a*b + b*c + c*a) << "\n"; 

	return 0;
}