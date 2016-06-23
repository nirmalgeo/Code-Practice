#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n, m ,a, cnt = 0;
	
	cin >> n >> m >> a;
	
	cnt =  (n / a  + ((n> a && n%a!=0)? 1 : 0)) * ( m /a  + ((m>a && m%a!=0)? 1: 0));
	
	if(cnt == 0) cnt = 1;
	
	cout << cnt ;

	return 0;
}