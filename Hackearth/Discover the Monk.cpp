#include<bits/stdc++.h>
using namespace std;
int main(){
	ios_base::sync_with_stdio(0);
	int n,q;
	vector<long long> v;
	cin>>n>>q;
	while(n--){
		long long a;
		cin>>a;
		v.push_back(a);
	}
	sort(v.begin(),v.end());
	while(q--){
		long long a;
		cin>>a;
		if(binary_search(v.begin(), v.end(), a))
			cout <<"YES\n";
		else
			cout <<"NO\n";
	}
	


	return 0;
}