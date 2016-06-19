#include<bits/stdc++.h>
#define INF 1000000007
using namespace std;
inline long long mypow(long long x, long long y){
	if(y==0) return 1;
	else if(y&1) return x*mypow(x*x, y/2);
	else return mypow(x*x, y/2);
}

int gcd(int a, int b){ return __gcd(a,b);}
int main(){

	int n,temp;
	cin>>n;
	int g , f=1;
	for(int i=0; i<n; i++){
		cin>>temp;
		if(i==0) g = temp;
		else g = gcd(temp, g);
		
		f = f * (temp%INF);
	}
	
	long long value = mypow(f,g);
	value = value % INF;
	cout << value;
	
	return 0;
}