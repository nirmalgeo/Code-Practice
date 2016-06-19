#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,m,x=0, y=0, temp;
	ios_base::sync_with_stdio(0);
	while(1) {
	cin>>n>>m;
	if(!n && !m)
		break;
	assert( n>=0 && n<=1000000);
    assert( m>=0 && m<=1000000);
	x=0;
	while(n--){
		cin>>temp;
		assert(temp>=0 && temp<=1000000000);
		x = x | ( 1<<temp);
	}
	long long count =0;
	while(m--){
		cin>>temp;
		if( x & (1<<temp))
			count++;
	}
	cout << count ;
	}
	return 0;
}