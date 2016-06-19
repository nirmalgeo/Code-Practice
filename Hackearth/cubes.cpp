#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		long long n,a,b;
		scanf("%lld", &n);
		a = n;
		b = n-2;
		if(b < 0)
			b=0;
		long long val = (a-b)*(a*a+a*b+b*b);
		cout << val <<"\n";
	}

	return 0;
}