// inclusion exclusion principle

#include<bits/stdc++.h>
#define inf (int) 1e7
using namespace std;


int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, b;
	int tt = 1;
	
	while( cin >> n >> b){
		if( !n && !b) break;
		
		vector<int> towers;
		towers.resize(n);
		pair<int, int> hash[15];
				
		for(int i=0;i <n; i++)
			cin >> towers[i];
		
		int m,k;
		cin >> m;
		
		for(int i=0; i < m; i++){
			cin >> k;
			int hashVal = 0,temp, val;
			for(int j=0; j<k; j++){
				cin >> temp;
				hashVal |= (1<<(temp-1));
			}
			cin >> val;
			hash[i] = {hashVal, val};
		}
		
		vector<int> tow;
		
		vector<pair<int, vector<int>>> output;
		
		for(int i=0; i< (1<<n); i++){
			int cnt = 0;
			int tempHash = 0;
			int sum = 0;
			for(int j=0; j<n; j++){
				if(i&(1<<j)){
					sum+= towers[j];
					tempHash |= (1<<j);
					cnt++;
					tow.push_back(j+1);
				}
			}
			if(cnt == b){
				
				for(int j=0; j<m ;j++){
					int intersect = hash[j].first & i;
					int cntr =0;
					for(int ii=0; ii<n; ii++){
						if(intersect & (1<<ii))
							cntr++;
					}
					// exclusion inclusion principle
					if(cntr<=1) continue;
					sum -= (cntr-1)*hash[j].second;
				}
				output.push_back({sum, tow});
			}
			tow.clear();
		}
		
		sort(output.begin(), output.end());
		int maxVal = output[output.size()-1].first;
		
		int ans = maxVal;
		vector<int> v;
		
		for(auto &c: output)
			if(c.first == ans){
				v = c.second;
				break;
			}
				
		
		cout << "Case Number  "<<tt++<<"\n";
		cout << "Number of Customers: "<<ans << "\n";
		cout << "Locations recommended:" ;
		for(auto &c: v)
			cout << " " << c ;
		cout << "\n";
		
		cout <<"\n";
		
	}
	


	return 0;
}