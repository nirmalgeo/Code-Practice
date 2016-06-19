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
	
	
	freopen("in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){

	
// code starts here 
		
		int n; 
		vector<int> v;
		
		cin >> n;
		
		bool arr[n+1];
		v.resize(n+1);
		
		
		for(int i=1; i<=n; i++) cin >> v[i];
		
		int cnt = 0;
		for(int i=1; i<=n ;i++){
			memset(arr, false, sizeof(arr));
			vector<int> bff;
			int j=i, temp = 0, last=0;
			while(1){
				if(arr[j]) {
					int flag = false;
					for(int jj= 1; jj<=n; jj++){
						if(v[jj] == last && jj!=j){
							flag = true;
							j = jj; break;
						}	
					}
					if(!flag) break;
				}
				
				arr[j] = true;
				temp++;
				bff.push_back(j);
				last = j;
				j = v[j];
			}
			for(auto &c: bff)
					cout << c << " ";
				cout << "\n";
			if(j == i){
				
				cnt = max(temp, cnt);
			}
		}
	

// code ends here 

	
	 cerr << "test " << cas << " done" << endl;

	cout << "Case #"<< cas << ": "<< cnt  <<"\n";


	}

	return 0;
}