//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	//freopen("in","r", stdin);
	//freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){

// code starts here 
		
		long long r,g,b,k;
		cin >> r >> g >> b;
		cin >> k;
		vector<long long> v {r,g,b}, res;
		sort(v.begin(), v.end());
		
		int count =0;
		int val = 0;
		bool found = false;
		
		while(true){
			
			for(int i=0;i<3; i++){
				if(v[i]) {
					v[i]--;
					count++;
				}
				
				if(res[i]-v[i] == k) {found = true; break;}
			}
			if(found) break;
		}
		

		cout << count << "\n";
	

// code ends here 

	//cout << "Case #"<< cas << ": "<< ans <<"\n";


	}

	return 0;
}