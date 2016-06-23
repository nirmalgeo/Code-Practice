#include<bits/stdc++.h>
#define INF 100000
using namespace std;

set<int> s;
vector<int> res;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n;
	long long c;
	cin >> n >> c;
	
	for( int i = 0; i < n; i++ ){
		int x;
		cin >> x;
		s.insert(x);
	}
	
	
	vector<int> res;
	for( int i = 1; true ; i++ ){
		if(i > c)break;
		
		if(s.find(i) != s.end())continue;
		
		c -= i;
		res.push_back(i);
	}
	
	cout << res.size() << endl;;
	for(auto v : res){
		cout << v << " ";
	}
	cout << endl;

	return 0;
}