#include<bits/stdc++.h>
using namespace std;
long long GCD(long long  a, long long b)
{
   if (b==0) return a;
   return GCD(b,a%b);
}
long long lcm(long long a, long b){
	return (b*a)/GCD(a,b);
}

int main(){
	
	long long n, a, b, p , q;
	cin >> n >> a >> b >> p >> q;
	
	long long val = 0;
	
	long long aVal = n/a;
	long long bVal = n/b;
	
	long long lCombined = lcm(a, b);
	
	if(lCombined <= n){
		lCombined = n/lCombined;
		
		if( p > q)
			bVal -= lCombined;
		else
			aVal -= lCombined;
	}
	//cerr << lCombined << " " << aVal << " " << bVal << "\n";;
	cout << aVal*p + bVal*q;
	

	return 0;
}