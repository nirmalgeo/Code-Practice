#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> out;
vector<int> rows;


bool place(int r, int c){
	for(int prev = 0; prev<c; prev++)
		if(rows[prev]==r ||  ( abs(rows[prev] - r) == abs(prev - c)) )		
			return false;
	return true;
}



void backtrack(int c){
	if(c==8) {
		out.push_back(rows);
	}
	
	for(int r=0; r<8; r++)
		if(place(r,c)){
			rows[c] = r;
			backtrack(c+1);
		}

}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	//freopen("out", "w", stdout);;
	
	vector<int> cmp;
	cmp.resize(8);
	rows.resize(8);

	backtrack(0);
	
	int tt = 1;
	
	while( cin >> cmp[0] ){
		cmp[0]--;
		for(int i=1; i<=7; i++) {cin>> cmp[i]; cmp[i]--;}
		
		int ans = 10;
		
		for(int i=0; i< out.size(); i++){
			int cnt = 0;
			for(int j=0; j<8; j++)
				if(out[i][j] != cmp[j])
					cnt++;
			ans = min(ans, cnt);
		}
	
		cout << "Case " << tt++ <<": "<<ans << "\n";
		cmp.clear();
	}
	
	
	
	
	
	return 0;
}