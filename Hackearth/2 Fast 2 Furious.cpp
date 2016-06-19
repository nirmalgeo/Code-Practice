#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll a[1000007];
int main() {
	int n;
	cin>>n;
	assert(n>=2 && n<=1000000);
	for(int i=0;i<n;i++) {
		cin>>a[i];
		assert(a[i] >= -1000000000 && a[i] <= 1000000000);
	}
	ll ret1 = -1;
	for(int i=0;i<n-1;i++) ret1=max(ret1,abs(a[i]-a[i+1]));
	for(int i=0;i<n;i++) {
		cin>>a[i];
		assert(a[i] >= -1000000000 && a[i] <= 1000000000);
	}
	ll ret2 = -1;
	for(int i=0;i<n-1;i++) ret2=max(ret2,abs(a[i]-a[i+1]));
	if(ret1 > ret2) cout << "Dom\n";
	else if(ret1 < ret2) cout << "Brian\n";
	else cout<<"Tie\n";
	cout<<max(ret1,ret2)<<"\n";
}