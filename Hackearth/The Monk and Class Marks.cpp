#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	vector<pair<int,string>> v;
	while(t--){
		string s;
		int m;
		cin>>s>>m;
		v.push_back(make_pair(m,s));
		sort(v.rbegin(), v.rend());
	}
	for(auto &c: v)
			cout << c.second << " " << c.first << "\n";
	return 0;
}