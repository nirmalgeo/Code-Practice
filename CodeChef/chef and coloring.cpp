//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){
		int n;
		cin >> n;
		string s;
		cin >> s;
		sort(s.begin(), s.end());
		vector<int> v;
		v.assign(3,0);
		
		for(int i=0; i<s.length(); i++) {
			if(s[i] == 'R') v[0]++;
			else if(s[i] == 'G') v[1]++;
			else if(s[i] == 'B') v[2]++;
		}
		sort(v.rbegin(), v.rend());
		
		cout << n-v[0] << "\n";
		
	}

	return 0;
}