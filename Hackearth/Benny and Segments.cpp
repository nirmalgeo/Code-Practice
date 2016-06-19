#include<bits/stdc++.h>
using namespace std;

int main(){

	int t;
	cin >> t;
	while(t--){
		int n, l;
		cin >> n >> l;
		vector<pair<int, int>> v;
		
		for(int i=0; i<n; i++){
			int x1 , x2;
			cin >> x1 >> x2;
			v.push_back({x1, x2});
		}
		
		//sort(v.begin(), v.end());
		
		int length = 0;
		int lastval = -1;
		bool found= false;
		
		for(int i=0; i< (1<<n); i++){
			length =0 ;
			lastval = -1;
			vector<pair<int,int>> output;
			for(int j=0; j<n; j++){
				length += (v[i].second-v[i].first);
				output.push_back({v[i].first, v[i].second});
				if(length == l) {found=true; break;}
			}
			if(found == true) {
				bool check = true;
				sort(output.begin(), output.end());
				for(int i=1; i< output.size(); i++){
					if(output[i].first != output[i-1].second) { check = false; break;} 
				}
				if(check) break;
				else continue;
			}
		}
		
		
		if(found) cout << "Yes\n";
		else cout << "No\n";
	}

	return 0;
}

