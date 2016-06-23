#include<bits/stdc++.h>
using namespace std;
int main(){
	
	int n,q;
	
	cin >> n >> q;
	
	vector<long long> v;
	v.resize(n);
	
	for(int i=0; i<n; i++)	
		cin >> v[i];
		
	long long maxx= v[0], minn= v[0], t;
	
	for(int i=1; i<n; i++){
		maxx = max(v[i], maxx);
		minn = min(v[i], minn);
	}
	
	while(q--){
		cin >> t;
		if(t>= minn && t<= maxx)
			cout << "Yes\n";
		else
			cout << "No\n";
	}
	

	return 0;
}