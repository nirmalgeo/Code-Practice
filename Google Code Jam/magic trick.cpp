//nirmalgeo25 template
#include<bits/stdc++.h>
using namespace std;


int xarr[] = {-1,0,1,1,1,0,-1,-1};
int yarr[] = {-1,-1,-1,0,1,1,1,0};


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	
	freopen("A-small-practice (1).in","r", stdin);
	freopen("out","w",stdout);
	
	int cases;
	cin >> cases;
	for(int cas =1; cas <= cases; cas++){

// code starts here 
		int a,b, temp;
		cin >> a;
		map<int,int> m;
		
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				cin >> temp;
				if(i+1==a)
					m[temp]++;
			}
		}
		
		cin >> b;
		
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				cin >> temp;
				if(i+1==b)
					m[temp]++;
			}
		}
		
		int cnt = 0;
		int ans = -1;
		for(auto &c: m){
			if(c.second == 2){
				cnt++;
				ans = c.first;
			}
		}

// code ends here 
	string out;
	if(cnt > 1) out = "Bad magician!";
	else if(cnt ==0) out = "Volunteer cheated!";
	else out = to_string(ans);
	
	cout << "Case #"<< cas << ": "<< out <<"\n";


	}

	return 0;
}