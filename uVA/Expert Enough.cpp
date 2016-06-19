//nirmalgeo25 template
#include<bits/stdc++.h>
#define inf (long long)1e18
using namespace std;

int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};
typedef long long ll;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){

// code starts here 
		int d;
		cin >> d;
		vector<pair<pair<int,int>, string>> v;
		int a, b;
		string temp;
		
		for(int i=1; i<=d ;i++) {
			cin >> temp >> a >> b;
			v.push_back({{a,b}, temp});
		}
		sort(v.begin(), v.end());
		
		int q;
		cin >> q;
		string ans = "";
		while(q--){
			int p;
			cin >> p;
			int cnt= 0;			
			
			for(auto &c: v)
				if(p >=  c.first.first && p<= c.first.second){
					cnt++;
					ans = c.second;
				}
	
			if(cnt == 0 || cnt > 1) ans = "UNDETERMINED";
			
			cout << ans << "\n";
		}
	
// code ends here 
		
		if(cas != cases)cout << "\n";

	}

	return 0;
}